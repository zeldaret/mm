# N64 Japanese 1.1 research extraction

The `n64-jp-1.1` target is still a work in progress. The normal `assets` target currently reuses the US baserom for non-US assets, text, and audio because the shared XML and text tooling do not yet describe every Japanese-layout difference.

This document records Japanese Rev A / Japan 1.1 resources whose layout has been independently verified against the retail ROM. The associated extractor reads only the user's baserom-derived segments and writes generated data under `extracted/`, so no retail ROM data is committed to the repository.

## Required ROM

Use the Japanese Rev A ROM expected by the existing `n64-jp-1.1` configuration:

- Version: `Zelda no Densetsu - Mujura no Kamen (Japan) (Rev A)`
- MD5: `c38a7f6f6b61862ea383a75cdf888279`

Place it at:

```text
baseroms/n64-jp-1.1/baserom.z64
```

The path is already ignored by git.

## Usage

Prepare the Python environment and extract the Japanese baserom segments using the normal project setup flow:

```sh
make venv
make setup VERSION=n64-jp-1.1
```

Then run the verified research extractor:

```sh
make jp-rev1-research VERSION=n64-jp-1.1
```

The direct equivalent is:

```sh
.venv/bin/python3 tools/jp_rev1/extract_research.py
```

Generated output is written to:

```text
extracted/n64-jp-1.1/research/
```

## Japanese message format

The Japanese Rev A message system is not the NES/US byte-oriented format currently hardcoded in `tools/text/msgdis.py`.

Verified properties:

- code VRAM: `0x800A75E0`
- message table: `sMessageTableJPN` at `0x801C1C48`
- message segment: `jpn_message_data_static`
- table entry size: 8 bytes
- table entry layout: text ID (`u16`), box info (`u8`), pad (`u8`), segmented address (`u32`)
- message header: 12 bytes
- message body: big-endian 16-bit words
- text encoding: two-byte Shift-JIS words plus 16-bit control codes
- verified message count: **4529**

The extractor preserves, for every message:

- text ID and table address
- box type and position
- exact 12-byte header
- decoded Japanese representation
- control/button tokens
- full 16-bit word stream
- exact raw bytes

The extracted 4529 entries were byte-compared with the independent localization research dataset: text IDs, message headers, and raw message bytes matched 4529/4529. Display-string differences in that older dataset were limited to later editorial Unicode normalization such as wave-dash/fullwidth-tilde substitutions; the research extractor keeps the retail Shift-JIS decoding.

One uncommon `0x037E` word remains intentionally labeled as an unknown control in message `0x08CA` rather than assigning an unsupported semantic name.

## Item-name archive

`item_name_static` in Japanese 1.1 is a small archive rather than a flat texture sheet:

- archive size: `0x12C10`
- SHA-256: `3a1c37d72a6b60fa4e6d3b70f53cf89959fcd4536bb46876f168e1ab1177e31a`
- entry count: **155**
- table/data boundary: `0x270`
- each entry is individually Yaz0-compressed
- each decoded entry is a `128x16` IA4 texture (`0x400` bytes)

The research extractor expands all 155 entries and writes both exact IA4 bytes and local PGM previews under `extracted/n64-jp-1.1/research/item_names/`.

## Verified boss title cards

These offsets agree with the existing object XML and were independently read back from Japanese Rev A. Every card is `128x40` IA8 (`0x1400` bytes).

| Resource | Segment | Offset |
| --- | --- | ---: |
| `gOdolwaTitleCardTex` | `object_boss01` | `0xC7F8` |
| `gTwinmoldTitleCardTex` | `object_boss02` | `0x8650` |
| `gGyorgTitleCardTex` | `object_boss03` | `0x7EC8` |
| `gMajorasMaskTitleCardTex` | `object_boss07` | `0x2F840` |
| `gMajorasIncarnationTitleCardTex` | `object_boss07` | `0x30C40` |
| `gMajorasWrathTitleCardTex` | `object_boss07` | `0x32040` |
| `gGohtTitleCardTex` | `object_boss_hakugin` | `0x14040` |

The Japanese source labels visible in these cards are:

- `密林仮面戦士 / オドルワ`
- `仮面機械獣 / ゴート`
- `巨大仮面魚 / グヨーグ`
- `大型仮面虫 / ツインモルド`
- `ムジュラの仮面`
- `ムジュラの化身`
- `ムジュラの魔人`

## Japanese title-screen layout

`object_mag` differs substantially between Japanese 1.1 and the shared US XML. The Japanese decoded object is `0x20550` bytes. The following Japanese offsets were verified directly:

| Resource | JP 1.1 format / size | JP 1.1 offset | Shared US XML |
| --- | --- | ---: | --- |
| `gTitleScreenControllerNotConnectedTextTex` | I4 `256x9` | `0x00000` | offset `0x11740` |
| `gTitleScreenInsertControllerTextTex` | I4 `144x9` | `0x00480` | offset `0x11BC0` |
| `gTitleScreenMajorasMaskSubtitleTex` | I8 `120x16` | `0x15F10` | I8 `104x16`, offset `0x9000` |
| `gTitleScreenMajorasMaskSubtitleMaskTex` | I8 `120x16` | `0x16690` | I8 `104x16`, offset `0x9680` |
| `gTitleScreenTheLegendOfTextTex` | I8 `80x16` | `0x16E10` | I8 `72x8`, offset `0x9D00` |

For this reason the normal Japanese `assets` target must not simply point all existing XML at the Japanese baserom. Version-specific XML coverage needs to be introduced resource-by-resource after each layout is verified.

## Research manifest

The committed source of truth for currently verified ranges is:

```text
tools/jp_rev1/research_manifest.json
```

The extractor validates every declared offset against the extracted segment size and records SHA-256 hashes in its generated `report.json`. It also records hashes and sizes for important Japanese segments that were encountered during localization research, including `code`, `jpn_message_data_static`, `item_name_static`, `do_action_static`, title/error/parameter/day-telop assets, and the boss objects listed above.

## Scope and next steps

This first stage is deliberately non-invasive: it adds reproducible Japanese-source analysis without replacing the US-oriented build assets. The next migration steps are:

1. add a native Japanese message decoder/encoder to the normal text pipeline;
2. introduce version-specific `object_mag` XML instead of reusing the US layout;
3. promote verified Japanese UI archives (`title_static`, `memerrmsg`, `locerrmsg`, `parameter_static`, `jpn_daytelop_static`, `do_action_static`) into version-aware asset definitions;
4. extend `tools/filelists` and matching support for `n64-jp-1.1` as coverage increases.

Keeping the research extractor separate makes each of those changes reviewable while preserving the current US matching target.
