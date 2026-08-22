#!/usr/bin/env python3
"""Extract verified Japanese N64 1.1 text and graphics for decomp research.

This tool intentionally writes only to extracted/ by default. The committed
manifest contains offsets and formats; ROM-derived bytes and previews remain
local and are regenerated from the user's baserom.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import struct
from collections import Counter
from pathlib import Path
from typing import Any

import crunch64
import yaml


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_MANIFEST = Path(__file__).with_name("research_manifest.json")
DEFAULT_BASEROM_DIR = REPO_ROOT / "extracted/n64-jp-1.1/baserom"
DEFAULT_OUTPUT_DIR = REPO_ROOT / "extracted/n64-jp-1.1/research"
VERSION_CONFIG = REPO_ROOT / "baseroms/n64-jp-1.1/config.yml"
SEGMENTS_CSV = REPO_ROOT / "baseroms/n64-jp-1.1/segments.csv"

BUTTON_INFO = {
    0x839F: "A",
    0x83A0: "B",
    0x83A1: "C",
    0x83A2: "L",
    0x83A3: "R",
    0x83A4: "Z",
    0x83A5: "C-UP",
    0x83A6: "C-DOWN",
    0x83A7: "C-LEFT",
    0x83A8: "C-RIGHT",
    0x83A9: "ADVANCE",
    0x83AA: "CONTROL-PAD",
}

CONTROL_INFO = {
    0x0009: "BOX_BREAK",
    0x000A: "NEWLINE",
    0x000B: "BOX_BREAK_ALT",
    0x000C: "CARRIAGE_RETURN",
    0x001F: "SHIFT",
    0x0100: "NAME",
    0x0101: "QUICKTEXT_ENABLE",
    0x0102: "QUICKTEXT_DISABLE",
    0x0103: "EVENT",
    0x0104: "PERSISTENT",
    0x0110: "BOX_BREAK_DELAYED",
    0x0111: "FADE",
    0x0112: "FADE_SKIPPABLE",
    0x0120: "SFX",
    0x0128: "DELAY",
    0x0201: "BACKGROUND",
    0x0202: "TWO_CHOICE",
    0x0203: "THREE_CHOICE",
    0x0220: "DOG_RACE_BET",
    0x0221: "BOMBER_INPUT",
    0x0222: "PAUSE_MENU",
    0x0223: "TIME_SPEED",
    0x0224: "OWL_WARP",
    0x0225: "LOTTERY_INPUT",
    0x0230: "EVENT2",
    0x0237: "HOURS_LEFT",
    0x0238: "TIME_LEFT",
    0x0240: "END_ALT",
    0x0500: "END",
}

FINAL_CODES = {0x0103, 0x0104, 0x0111, 0x0112, 0x0230, 0x0240, 0x0500}
ARG_COUNTS = {0x001F: 1, 0x0110: 1, 0x0111: 1, 0x0112: 1, 0x0120: 1, 0x0128: 1}
FORMAT_BPP = {"i4": 4, "ia4": 4, "i8": 8, "ia8": 8, "rgba16": 16, "rgba32": 32}


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def parse_int(value: int | str) -> int:
    if isinstance(value, int):
        return value
    return int(value, 0)


def hex4(value: int) -> str:
    return f"0x{value:04X}"


def load_code_vram() -> int:
    with SEGMENTS_CSV.open(newline="", encoding="utf-8-sig") as f:
        for row in csv.DictReader(f):
            if row["Name"] == "code":
                return int(row["VRAM start"], 16)
    raise RuntimeError("code VRAM not found in segments.csv")


def control_name(word: int) -> str:
    if 0x0130 <= word <= 0x0136:
        return f"TEXT_SPEED:{word - 0x0130}"
    if 0x2000 <= word <= 0x2008:
        return f"COLOR:{word - 0x2000}"
    if 0x0204 <= word <= 0x0238:
        return f"DYNAMIC:{word:04X}"
    if 0x0300 <= word <= 0x0310:
        return f"HIGHSCORE:{word:04X}"
    return CONTROL_INFO.get(word, f"CTRL_{word:04X}")


def decode_sjis_word(word: int) -> str | None:
    try:
        return bytes((word >> 8, word & 0xFF)).decode("shift_jis")
    except UnicodeDecodeError:
        return None


def decode_message(raw: bytes, header_size: int) -> dict[str, Any]:
    if len(raw) < header_size or len(raw) % 2:
        raise ValueError(f"invalid message size {len(raw)}")

    words = [struct.unpack_from(">H", raw, pos)[0] for pos in range(header_size, len(raw), 2)]
    source: list[str] = []
    tokens: list[dict[str, Any]] = []
    controls: list[int] = []
    undecoded: list[int] = []
    final_at = -1

    i = 0
    while i < len(words):
        word = words[i]
        if word == 0 and final_at >= 0:
            i += 1
            continue
        if word == 0x000A:
            source.append("\\n")
            tokens.append({"type": "newline", "word": hex4(word)})
            controls.append(word)
            i += 1
            continue
        if word == 0x0020:
            source.append(" ")
            tokens.append({"type": "text", "word": hex4(word), "text": " "})
            i += 1
            continue

        button = BUTTON_INFO.get(word)
        if button is not None:
            text = f"[{button}]"
            source.append(text)
            tokens.append({"type": "button", "word": hex4(word), "name": button, "text": text})
            i += 1
            continue

        is_control = (
            word in CONTROL_INFO
            or word < 0x0800
            or 0x2000 <= word <= 0x2008
            or 0x0300 <= word <= 0x0310
        )
        if is_control:
            arg_count = ARG_COUNTS.get(word, 0)
            args = words[i + 1 : i + 1 + arg_count]
            if len(args) != arg_count:
                raise ValueError(f"truncated control {word:04X}")
            label = control_name(word)
            if args:
                label += ":" + ",".join(f"{arg:04X}" for arg in args)
            text = "{" + label + "}"
            source.append(text)
            tokens.append(
                {
                    "type": "control",
                    "word": hex4(word),
                    "args": [hex4(arg) for arg in args],
                    "text": text,
                }
            )
            controls.append(word)
            i += 1 + arg_count
            if word in FINAL_CODES:
                final_at = i - 1
            continue

        text = decode_sjis_word(word)
        if text is None:
            text = f"{{SJIS:{word:04X}}}"
            undecoded.append(word)
            token_type = "sjis_raw"
        else:
            token_type = "text"
        source.append(text)
        tokens.append({"type": token_type, "word": hex4(word), "text": text})
        i += 1

    padding = words[final_at + 1 :] if final_at >= 0 else []
    if any(word != 0 for word in padding):
        preview = " ".join(f"{word:04X}" for word in padding[:12])
        raise ValueError(f"nonzero data after final control: {preview}")

    return {
        "header_hex": raw[:header_size].hex().upper(),
        "source_jp": "".join(source),
        "tokens": tokens,
        "controls": controls,
        "undecoded": undecoded,
        "final_control": None if final_at < 0 else hex4(words[final_at]),
        "padding_words": len(padding),
        "words": [hex4(word) for word in words],
    }


def extract_messages(
    baserom_dir: Path,
    output_dir: Path,
    manifest: dict[str, Any],
) -> dict[str, Any]:
    desc = manifest["message_data"]
    config = yaml.safe_load(VERSION_CONFIG.read_text(encoding="utf-8"))
    table_addr = int(config["variables"][desc["table_variable"]])
    code_vram = load_code_vram()
    table_offset = table_addr - code_vram
    code = (baserom_dir / desc["code_segment"]).read_bytes()
    data = (baserom_dir / desc["data_segment"]).read_bytes()
    header_size = int(desc["header_size"])

    entries: list[dict[str, int]] = []
    pos = table_offset
    for index in range(10000):
        if pos + 8 > len(code):
            raise RuntimeError("message table runs beyond code segment")
        text_id, info, pad, address = struct.unpack_from(">HBBI", code, pos)
        if pad != 0:
            raise RuntimeError(f"message table entry {index} has nonzero pad {pad:#x}")
        entries.append({"text_id": text_id, "info": info, "address": address, "offset": address & 0x00FFFFFF})
        pos += 8
        if text_id == 0xFFFF:
            break
    else:
        raise RuntimeError("message table terminator not found")

    if entries[-1]["text_id"] != 0xFFFF:
        raise RuntimeError("message table terminator not found")

    messages: list[dict[str, Any]] = []
    control_counts: Counter[str] = Counter()
    button_counts: Counter[str] = Counter()
    undecoded_counts: Counter[str] = Counter()
    unknown_control_usages: list[dict[str, Any]] = []

    for index, entry in enumerate(entries[:-1]):
        next_entry = entries[index + 1]
        start = entry["offset"]
        end = len(data) if next_entry["text_id"] == 0xFFFF else next_entry["offset"]
        if start > end or end > len(data):
            raise RuntimeError(f"invalid message range for {entry['text_id']:#06x}: {start:#x}..{end:#x}")
        raw = data[start:end]
        decoded = decode_message(raw, header_size)
        for control in decoded["controls"]:
            control_counts[f"0x{control:04X}"] += 1
        for word in decoded["undecoded"]:
            undecoded_counts[f"0x{word:04X}"] += 1
        for token_index, token in enumerate(decoded["tokens"]):
            if token["type"] == "button":
                button_counts[token["name"]] += 1
            elif token["type"] == "control" and token["text"].startswith("{CTRL_"):
                unknown_control_usages.append(
                    {
                        "text_id": f"0x{entry['text_id']:04X}",
                        "token_index": token_index,
                        "code": token["word"],
                        "source_jp": decoded["source_jp"],
                    }
                )

        header = raw[:header_size]
        message = {
            "index": index,
            "text_id": f"0x{entry['text_id']:04X}",
            "box_type": entry["info"] >> 4,
            "box_position": entry["info"] & 0xF,
            "table_address": f"0x{entry['address']:08X}",
            "data_offset": f"0x{start:08X}",
            "byte_size": len(raw),
            "header_hex": decoded["header_hex"],
            "header": {
                "properties": f"0x{struct.unpack_from('>H', header, 0)[0]:04X}",
                "item_id": f"0x{header[2]:02X}",
                "next_text_id": f"0x{struct.unpack_from('>H', header, 3)[0]:04X}",
                "first_choice_price": f"0x{struct.unpack_from('>H', header, 5)[0]:04X}",
                "second_choice_price": f"0x{struct.unpack_from('>H', header, 7)[0]:04X}",
                "unknown": f"0x{struct.unpack_from('>H', header, 9)[0]:04X}",
                "alignment_byte": f"0x{header[11]:02X}",
            },
            "source_jp": decoded["source_jp"],
            "final_control": decoded["final_control"],
            "padding_words": decoded["padding_words"],
            "raw_hex": raw.hex().upper(),
            "words": decoded["words"],
            "tokens": decoded["tokens"],
        }
        messages.append(message)

    expected_count = int(desc["expected_message_count"])
    if len(messages) != expected_count:
        raise RuntimeError(f"message count {len(messages)} != expected {expected_count}")

    msg_dir = output_dir / "messages"
    msg_dir.mkdir(parents=True, exist_ok=True)
    payload = {
        "format": manifest["format"],
        "version": manifest["version"],
        "code_vram": f"0x{code_vram:08X}",
        "table_vram": f"0x{table_addr:08X}",
        "table_code_offset": f"0x{table_offset:08X}",
        "source_segment": desc["data_segment"],
        "source_size": len(data),
        "source_sha256": sha256(data),
        "message_count": len(messages),
        "messages": messages,
    }
    (msg_dir / "messages.json").write_text(json.dumps(payload, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

    columns = ("index", "text_id", "box_type", "box_position", "byte_size", "header_hex", "source_jp")
    with (msg_dir / "messages.tsv").open("w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f, delimiter="\t", lineterminator="\n")
        writer.writerow(columns)
        for message in messages:
            writer.writerow([str(message[column]).replace("\r", "").replace("\n", "\\n") for column in columns])

    stats = {
        "message_count": len(messages),
        "text_id_first": messages[0]["text_id"],
        "text_id_last": messages[-1]["text_id"],
        "missing_final_control": [m["text_id"] for m in messages if m["final_control"] is None],
        "control_counts": dict(sorted(control_counts.items())),
        "button_counts": dict(sorted(button_counts.items())),
        "undecoded_sjis_counts": dict(sorted(undecoded_counts.items())),
        "unknown_control_usages": unknown_control_usages,
    }
    (msg_dir / "stats.json").write_text(json.dumps(stats, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    return stats


def texture_byte_size(fmt: str, width: int, height: int) -> int:
    try:
        bpp = FORMAT_BPP[fmt]
    except KeyError as exc:
        raise ValueError(f"unsupported texture format {fmt}") from exc
    bits = width * height * bpp
    if bits % 8:
        raise ValueError(f"non-byte-aligned texture {fmt} {width}x{height}")
    return bits // 8


def texture_to_gray(raw: bytes, fmt: str, width: int, height: int) -> bytes | None:
    if fmt == "i8":
        return raw
    if fmt == "i4":
        pixels = bytearray()
        for value in raw:
            pixels.extend(((value >> 4) * 17, (value & 0xF) * 17))
        return bytes(pixels[: width * height])
    if fmt == "ia8":
        pixels = bytearray()
        for value in raw:
            intensity = value >> 4
            alpha = value & 0xF
            pixels.append(round(intensity * 17 * alpha / 15))
        return bytes(pixels)
    if fmt == "ia4":
        pixels = bytearray()
        for value in raw:
            for nibble in (value >> 4, value & 0xF):
                intensity = nibble >> 1
                alpha = nibble & 1
                pixels.append(round(intensity * 255 / 7) if alpha else 0)
        return bytes(pixels[: width * height])
    return None


def write_pgm(path: Path, pixels: bytes, width: int, height: int) -> None:
    if len(pixels) != width * height:
        raise ValueError(f"PGM pixel count {len(pixels)} != {width * height}")
    path.write_bytes(f"P5\n{width} {height}\n255\n".encode("ascii") + pixels)


def extract_textures(baserom_dir: Path, output_dir: Path, manifest: dict[str, Any]) -> list[dict[str, Any]]:
    tex_dir = output_dir / "textures"
    tex_dir.mkdir(parents=True, exist_ok=True)
    results: list[dict[str, Any]] = []
    segment_cache: dict[str, bytes] = {}

    for item in manifest["textures"]:
        segment_name = item["segment"]
        segment = segment_cache.setdefault(segment_name, (baserom_dir / segment_name).read_bytes())
        offset = parse_int(item["offset"])
        width = int(item["width"])
        height = int(item["height"])
        fmt = item["format"].lower()
        size = texture_byte_size(fmt, width, height)
        end = offset + size
        if end > len(segment):
            raise RuntimeError(f"{item['name']} exceeds {segment_name}: {end:#x} > {len(segment):#x}")
        raw = segment[offset:end]
        raw_path = tex_dir / f"{item['name']}.{fmt}.bin"
        raw_path.write_bytes(raw)
        preview_path: Path | None = None
        pixels = texture_to_gray(raw, fmt, width, height)
        if pixels is not None:
            preview_path = tex_dir / f"{item['name']}.pgm"
            write_pgm(preview_path, pixels, width, height)
        results.append(
            {
                **item,
                "offset": f"0x{offset:X}",
                "byte_size": size,
                "segment_size": len(segment),
                "segment_sha256": sha256(segment),
                "raw_sha256": sha256(raw),
                "raw_output": str(raw_path.relative_to(REPO_ROOT)),
                "preview_output": None if preview_path is None else str(preview_path.relative_to(REPO_ROOT)),
            }
        )
    return results


def extract_item_names(baserom_dir: Path, output_dir: Path, manifest: dict[str, Any]) -> dict[str, Any]:
    desc = manifest["item_name_archive"]
    source = (baserom_dir / desc["segment"]).read_bytes()
    data_base = struct.unpack_from(">I", source, 0)[0]
    expected_base = parse_int(desc["data_base"])
    if data_base != expected_base:
        raise RuntimeError(f"item-name data base {data_base:#x} != {expected_base:#x}")
    count = int(desc["entry_count"])
    ends = [struct.unpack_from(">I", source, 4 * (i + 1))[0] for i in range(count)]
    out_dir = output_dir / "item_names"
    out_dir.mkdir(parents=True, exist_ok=True)
    width = int(desc["width"])
    height = int(desc["height"])
    expected_decoded = int(desc["decoded_bytes_per_entry"])
    entries: list[dict[str, Any]] = []
    prev = 0
    for index, end in enumerate(ends):
        if end <= prev or data_base + end > len(source):
            raise RuntimeError(f"invalid item-name cumulative end {index}: {end:#x}")
        stored = source[data_base + prev : data_base + end]
        if not stored.startswith(b"Yaz0"):
            raise RuntimeError(f"item-name entry {index} is not Yaz0")
        decoded = bytes(crunch64.yaz0.decompress(stored))
        if len(decoded) != expected_decoded:
            raise RuntimeError(f"item-name entry {index} decoded {len(decoded)} != {expected_decoded}")
        raw_path = out_dir / f"{index:03d}.ia4.bin"
        pgm_path = out_dir / f"{index:03d}.pgm"
        raw_path.write_bytes(decoded)
        pixels = texture_to_gray(decoded, "ia4", width, height)
        assert pixels is not None
        write_pgm(pgm_path, pixels, width, height)
        entries.append(
            {
                "index": index,
                "stored_offset": f"0x{data_base + prev:X}",
                "stored_size": len(stored),
                "stored_sha256": sha256(stored),
                "decoded_size": len(decoded),
                "decoded_sha256": sha256(decoded),
            }
        )
        prev = end
    return {
        "segment": desc["segment"],
        "segment_size": len(source),
        "segment_sha256": sha256(source),
        "data_base": f"0x{data_base:X}",
        "entry_count": len(entries),
        "entries": entries,
    }


def build_segment_inventory(baserom_dir: Path, manifest: dict[str, Any]) -> list[dict[str, Any]]:
    results = []
    for name in manifest["segment_inventory"]:
        path = baserom_dir / name
        data = path.read_bytes()
        results.append({"name": name, "size": len(data), "size_hex": f"0x{len(data):X}", "sha256": sha256(data)})
    return results


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baserom-dir", type=Path, default=DEFAULT_BASEROM_DIR)
    parser.add_argument("--output-dir", type=Path, default=DEFAULT_OUTPUT_DIR)
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    args = parser.parse_args()
    args.baserom_dir = args.baserom_dir.resolve()
    args.output_dir = args.output_dir.resolve()
    args.manifest = args.manifest.resolve()

    manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
    if manifest.get("version") != "n64-jp-1.1":
        raise RuntimeError(f"unexpected manifest version {manifest.get('version')}")
    if not args.baserom_dir.is_dir():
        raise FileNotFoundError(args.baserom_dir)
    args.output_dir.mkdir(parents=True, exist_ok=True)

    message_stats = extract_messages(args.baserom_dir, args.output_dir, manifest)
    texture_results = extract_textures(args.baserom_dir, args.output_dir, manifest)
    item_name_results = extract_item_names(args.baserom_dir, args.output_dir, manifest)
    segment_inventory = build_segment_inventory(args.baserom_dir, manifest)

    report = {
        "format": manifest["format"],
        "version": manifest["version"],
        "manifest_sha256": sha256(args.manifest.read_bytes()),
        "baserom_segments_dir": str(args.baserom_dir),
        "output_dir": str(args.output_dir),
        "messages": message_stats,
        "textures": texture_results,
        "item_names": item_name_results,
        "segment_inventory": segment_inventory,
        "invariants": {
            "message_count_is_4529": message_stats["message_count"] == 4529,
            "texture_count": len(texture_results),
            "item_name_count_is_155": item_name_results["entry_count"] == 155,
            "rom_derived_output_is_under_extracted": "extracted" in args.output_dir.parts,
        },
    }
    report_path = args.output_dir / "report.json"
    report_path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"report": str(report_path), "invariants": report["invariants"]}, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
