#!/usr/bin/env python3
"""Verify the native JP 1.1 message build against the retail segment."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import yaml
from elftools.elf.elffile import ELFFile


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_BASEROM_DIR = REPO_ROOT / "extracted/n64-jp-1.1/baserom"
DEFAULT_OBJECT = REPO_ROOT / "build/n64-jp-1.1/assets/text/message_data_static.o"
DEFAULT_REPORT = REPO_ROOT / "extracted/n64-jp-1.1/research/text_roundtrip_report.json"
VERSION_CONFIG = REPO_ROOT / "baseroms/n64-jp-1.1/config.yml"
SEGMENTS_CSV = REPO_ROOT / "baseroms/n64-jp-1.1/segments.csv"
EXPECTED_COUNT = 4529
EXPECTED_SHA256 = "90c872f3f76aad47d83bbc1acb247a96f51cf09a489a237f65bfdac2ad71fed9"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def code_vram() -> int:
    import csv

    with SEGMENTS_CSV.open(newline="", encoding="utf-8-sig") as f:
        for row in csv.DictReader(f):
            if row["Name"] == "code":
                return int(row["VRAM start"], 16)
    raise RuntimeError("code VRAM not found")


def retail_entries(code: bytes, data_size: int) -> list[dict[str, int]]:
    config = yaml.safe_load(VERSION_CONFIG.read_text(encoding="utf-8"))
    table_vram = int(config["variables"]["sMessageTableJPN"])
    pos = table_vram - code_vram()
    entries: list[dict[str, int]] = []

    for _ in range(10000):
        if pos + 8 > len(code):
            raise RuntimeError("message table exceeds code segment")
        text_id, info, pad, address = struct.unpack_from(">HBBI", code, pos)
        pos += 8
        if pad != 0:
            raise RuntimeError(f"nonzero table pad for {text_id:#06x}: {pad:#x}")
        if text_id == 0xFFFF:
            break
        entries.append(
            {
                "text_id": text_id,
                "info": info,
                "address": address,
                "offset": address & 0x00FFFFFF,
            }
        )
    else:
        raise RuntimeError("message table terminator not found")

    if len(entries) != EXPECTED_COUNT:
        raise RuntimeError(f"retail table count {len(entries)} != {EXPECTED_COUNT}")

    for index, entry in enumerate(entries):
        next_offset = entries[index + 1]["offset"] if index + 1 < len(entries) else data_size
        if not (0 <= entry["offset"] <= next_offset <= data_size):
            raise RuntimeError(f"bad retail message range at {entry['text_id']:#06x}")
        entry["size"] = next_offset - entry["offset"]
    return entries


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baserom-dir", type=Path, default=DEFAULT_BASEROM_DIR)
    parser.add_argument("--object", type=Path, default=DEFAULT_OBJECT)
    parser.add_argument("--report", type=Path, default=DEFAULT_REPORT)
    args = parser.parse_args()

    baserom_dir = args.baserom_dir.resolve()
    object_path = args.object.resolve()
    report_path = args.report.resolve()

    retail = (baserom_dir / "jpn_message_data_static").read_bytes()
    code = (baserom_dir / "code").read_bytes()
    entries = retail_entries(code, len(retail))

    with object_path.open("rb") as f:
        elf = ELFFile(f)
        rodata = elf.get_section_by_name(".rodata")
        symtab = elf.get_section_by_name(".symtab")
        if rodata is None or symtab is None:
            raise RuntimeError("message object is missing .rodata or .symtab")
        built = rodata.data()
        symbols = {
            symbol.name: int(symbol["st_value"])
            for symbol in symtab.iter_symbols()
            if symbol.name.startswith("_message_0x")
        }

    offset_mismatches = []
    byte_mismatches = []
    missing_symbols = []
    for entry in entries:
        name = f"_message_0x{entry['text_id']:04X}"
        symbol_offset = symbols.get(name)
        if symbol_offset is None:
            missing_symbols.append(name)
            continue
        if symbol_offset != entry["offset"]:
            offset_mismatches.append(
                {
                    "text_id": f"0x{entry['text_id']:04X}",
                    "retail": f"0x{entry['offset']:X}",
                    "symbol": f"0x{symbol_offset:X}",
                }
            )
        expected = retail[entry["offset"] : entry["offset"] + entry["size"]]
        actual = built[symbol_offset : symbol_offset + entry["size"]]
        if actual != expected:
            byte_mismatches.append(
                {
                    "text_id": f"0x{entry['text_id']:04X}",
                    "offset": f"0x{entry['offset']:X}",
                    "size": entry["size"],
                    "retail_sha256": sha256(expected),
                    "built_sha256": sha256(actual),
                }
            )

    retail_sha = sha256(retail)
    built_sha = sha256(built)
    report = {
        "format": "mm-n64-jp-1.1-text-roundtrip-v1",
        "retail_segment": {
            "bytes": len(retail),
            "sha256": retail_sha,
        },
        "built_rodata": {
            "object": str(object_path),
            "bytes": len(built),
            "sha256": built_sha,
        },
        "message_count": len(entries),
        "symbol_count": len(symbols),
        "missing_symbols": missing_symbols,
        "offset_mismatches": offset_mismatches,
        "byte_mismatches": byte_mismatches,
        "invariants": {
            "retail_sha256_expected": retail_sha == EXPECTED_SHA256,
            "rodata_byte_exact": built == retail,
            "all_4529_symbols_present": len(symbols) == EXPECTED_COUNT and not missing_symbols,
            "all_symbol_offsets_match_retail_table": not offset_mismatches,
            "all_message_bytes_match": not byte_mismatches,
        },
    }
    report["pass"] = all(report["invariants"].values())

    report_path.parent.mkdir(parents=True, exist_ok=True)
    report_path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report, ensure_ascii=False, indent=2))
    if not report["pass"]:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
