#!/usr/bin/env python3
"""Verify ZAPD texture extraction/repacking against a JP 1.1 retail segment.

The verifier can consume either existing `btex` include files or extracted PNGs.
In PNG mode it invokes ZAPD `btex` itself, reconstructs every XML-declared
texture range, and compares the complete segment with the baserom-derived data.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_ZAPD = REPO_ROOT / "tools/ZAPD/ZAPD.out"
HEX64_RE = re.compile(r"0x([0-9A-Fa-f]{16})\s*,")


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def parse_btex_include(path: Path) -> bytes:
    text = path.read_text(encoding="utf-8")
    words = HEX64_RE.findall(text)
    if not words:
        raise RuntimeError(f"no 64-bit texture words found in {path}")
    return b"".join(int(word, 16).to_bytes(8, "big") for word in words)


def expected_texture_size(fmt: str, width: int, height: int) -> int:
    bits_per_pixel = {
        "i4": 4,
        "ia4": 4,
        "i8": 8,
        "ia8": 8,
        "i16": 16,
        "ia16": 16,
        "rgba16": 16,
        "rgba32": 32,
        "ci4": 4,
        "ci8": 8,
    }.get(fmt.lower())
    if bits_per_pixel is None:
        raise RuntimeError(f"unsupported texture format for roundtrip verifier: {fmt}")
    bits = width * height * bits_per_pixel
    if bits % 8:
        raise RuntimeError(f"texture size is not byte-aligned: {fmt} {width}x{height}")
    return bits // 8


def resolve_repo_path(path: Path) -> Path:
    return path if path.is_absolute() else REPO_ROOT / path


def build_texture_from_png(zapd: Path, png: Path, fmt: str, out_path: Path) -> bytes:
    subprocess.run(
        [str(zapd), "btex", "-eh", "-tt", fmt, "-i", str(png), "-o", str(out_path)],
        cwd=REPO_ROOT,
        check=True,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.PIPE,
        text=True,
    )
    return parse_btex_include(out_path)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--segment", required=True, help="baserom segment name")
    parser.add_argument("--xml", type=Path, required=True, help="asset XML path")
    source_group = parser.add_mutually_exclusive_group(required=True)
    source_group.add_argument(
        "--build-dir",
        type=Path,
        help="directory containing generated *.inc.c files for this asset",
    )
    source_group.add_argument(
        "--asset-dir",
        type=Path,
        help="directory containing ZAPD-extracted PNGs; btex is run automatically",
    )
    parser.add_argument(
        "--baserom-dir",
        type=Path,
        default=REPO_ROOT / "extracted/n64-jp-1.1/baserom",
    )
    parser.add_argument("--zapd", type=Path, default=DEFAULT_ZAPD)
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()

    xml_path = resolve_repo_path(args.xml)
    baserom_dir = resolve_repo_path(args.baserom_dir)
    build_dir = resolve_repo_path(args.build_dir) if args.build_dir else None
    asset_dir = resolve_repo_path(args.asset_dir) if args.asset_dir else None
    zapd = resolve_repo_path(args.zapd)

    if asset_dir is not None and not zapd.is_file():
        raise RuntimeError(f"ZAPD not found: {zapd}")

    retail = (baserom_dir / args.segment).read_bytes()
    reconstructed = bytearray(len(retail))
    coverage = bytearray(len(retail))

    root = ET.parse(xml_path).getroot()
    file_node = root.find("File")
    if file_node is None:
        raise RuntimeError(f"no <File> node in {xml_path}")

    textures: list[dict[str, object]] = []
    with tempfile.TemporaryDirectory(prefix="mm-jp11-btex-") as temp_dir_name:
        temp_dir = Path(temp_dir_name)
        for node in file_node:
            if node.tag != "Texture":
                raise RuntimeError(
                    f"roundtrip verifier currently requires texture-only XML; found <{node.tag}> in {xml_path}"
                )

            name = node.attrib["Name"]
            out_name = node.attrib["OutName"]
            fmt = node.attrib["Format"]
            width = int(node.attrib["Width"], 0)
            height = int(node.attrib["Height"], 0)
            offset = int(node.attrib["Offset"], 0)
            expected_size = expected_texture_size(fmt, width, height)

            if asset_dir is not None:
                png_path = asset_dir / f"{out_name}.{fmt}.png"
                if not png_path.is_file():
                    raise RuntimeError(f"extracted texture not found: {png_path}")
                include_path = temp_dir / f"{out_name}.{fmt}.inc.c"
                data = build_texture_from_png(zapd, png_path, fmt, include_path)
            else:
                assert build_dir is not None
                include_path = build_dir / f"{out_name}.{fmt}.inc.c"
                data = parse_btex_include(include_path)

            if len(data) != expected_size:
                raise RuntimeError(
                    f"{name}: btex size {len(data)} != expected {expected_size} for {fmt} {width}x{height}"
                )
            end = offset + len(data)
            if end > len(retail):
                raise RuntimeError(f"{name}: range 0x{offset:X}-0x{end:X} exceeds {args.segment}")
            if any(coverage[offset:end]):
                raise RuntimeError(f"{name}: overlaps another declared texture range")

            reconstructed[offset:end] = data
            coverage[offset:end] = b"\x01" * len(data)
            expected = retail[offset:end]
            textures.append(
                {
                    "name": name,
                    "offset": f"0x{offset:X}",
                    "bytes": len(data),
                    "sha256": sha256(data),
                    "matches_retail_range": data == expected,
                }
            )

    uncovered = [i for i, marked in enumerate(coverage) if not marked]
    full_coverage = not uncovered
    reconstructed_bytes = bytes(reconstructed)
    report = {
        "format": "mm-n64-jp-1.1-asset-roundtrip-v1",
        "segment": args.segment,
        "xml": str(xml_path.relative_to(REPO_ROOT)),
        "source_mode": "png-btex" if asset_dir is not None else "existing-btex",
        "segment_bytes": len(retail),
        "retail_sha256": sha256(retail),
        "reconstructed_sha256": sha256(reconstructed_bytes),
        "texture_count": len(textures),
        "covered_bytes": int(sum(coverage)),
        "full_coverage": full_coverage,
        "uncovered_first": None if full_coverage else f"0x{uncovered[0]:X}",
        "textures": textures,
        "byte_exact": full_coverage and reconstructed_bytes == retail,
    }
    report["pass"] = report["byte_exact"] and all(
        bool(texture["matches_retail_range"]) for texture in textures
    )

    if args.report:
        report_path = resolve_repo_path(args.report)
        report_path.parent.mkdir(parents=True, exist_ok=True)
        report_path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

    print(json.dumps(report, ensure_ascii=False, indent=2))
    if not report["pass"]:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
