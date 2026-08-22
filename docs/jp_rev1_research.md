# N64 Japanese 1.1 research extraction

The `n64-jp-1.1` target is still a work in progress. Japanese message text is now extracted and rebuilt natively from the JP 1.1 baserom, while most graphics and audio still reuse the US extraction because their version-specific layouts are not yet fully described.

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

Additional verification targets exercise the native Japanese paths:

```sh
make jp-rev1-text-roundtrip VERSION=n64-jp-1.1
make jp-rev1-ui-roundtrip VERSION=n64-jp-1.1
make jp-rev1-object-mag VERSION=n64-jp-1.1
```

`jp-rev1-text-roundtrip` extracts all Japanese messages, encodes and compiles them with the normal build tools, then verifies the resulting `.rodata` against the retail `jpn_message_data_static` segment. `jp-rev1-ui-roundtrip` extracts the fully modeled JP UI segments and runs every PNG back through ZAPD `btex` before comparing the reconstructed segments byte-for-byte with retail. `jp-rev1-object-mag` remains a research-only partial extraction of the verified title-screen resources because the complete JP `object_mag` layout has not yet been modeled.

The direct research-extractor equivalent is:

```sh
.venv/bin/python3 tools/jp_rev1/extract_research.py
```

Generated output is written to:

```text
extracted/n64-jp-1.1/research/
```

## Japanese message format

The Japanese Rev A message system is not the NES/US byte-oriented format. `tools/text/msgdis.py` now selects a native `MessageDecoderJPN` for versions that define `sMessageTableJPN`, and the normal message build selects the `jpn` encoder for `n64-jp-1.1`.

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

The native decomp round-trip is also byte-exact. `make jp-rev1-text-roundtrip VERSION=n64-jp-1.1` regenerates `message_data_static.o` and verifies:

- retail and built `.rodata` are both 409,840 bytes;
- both SHA-256 hashes are `90c872f3f76aad47d83bbc1acb247a96f51cf09a489a237f65bfdac2ad71fed9`;
- all **4529** `_message_0xNNNN` symbols exist;
- all **4529** symbol offsets match the retail `sMessageTableJPN` addresses;
- all **4529** message byte ranges match retail exactly.

Japanese retail messages `0xFFFC` and `0xFFFD` are preserved from ROM instead of using the US committed debugger placeholders. In JP 1.1, `0xFFFC` contains the ordered-font character test and `0xFFFD` contains `おしまい！！！`.

One uncommon `0x037E` word remains intentionally labeled as an unknown control in message `0x08CA` rather than assigning an unsupported semantic name.

## Fully modeled Japanese UI segments

Four Japanese UI segments are now complete enough to participate in the normal JP asset extraction path. `make jp-rev1-ui-roundtrip VERSION=n64-jp-1.1` extracts each one, re-encodes every PNG with ZAPD `btex`, reconstructs the complete segment from its XML offsets, and requires a byte-exact match with retail.

| Segment | XML | Textures | Bytes | Retail SHA-256 |
| --- | --- | ---: | ---: | --- |
| `memerrmsg` | shared `misc/memerrmsg.xml` | 2 | 4,736 | `a334f9656e07a090342ca66555e26bbba91039048712adcfd06c9aa63f0d49a3` |
| `locerrmsg` | shared `misc/locerrmsg.xml` | 1 | 1,664 | `1d972c31291fe7d1c207fc186613c82a7a87d5a49015c2baf8090ef6ce392e9c` |
| `do_action_static` | shared `interface/do_action_static.xml` | 42 | 16,128 | `f84b53aa3b77777cc952e7b12c6f3b5d695e14a8ef28b723a5d5785cb935df87` |
| `jpn_daytelop_static` | JP-specific `n64-jp-1.1/misc/jpn_daytelop_static.xml` | 11 | 39,680 | `2eede8825620189331ff563475c944d714ab90239325182d5cbe020bee8d2a94` |

For `n64-jp-1.1`, the normal `assets` target still begins with the US fallback extraction, then overwrites these verified full segments from the Japanese baserom. The spec, ROM-segment declarations, DayTelop include, and DayTelop DMA source are version-split so JP uses the retail `jpn_daytelop_static` segment while the US target retains its original `daytelop_static` plus GER/FRA/ESP segments.

Version-specific XML directories are filtered by `tools/extract_assets.py`: shared XML remains available to every version, while `assets/xml/n64-jp-1.1/...` is ignored for a US extraction. This prevents partial JP research XML such as `object_mag` from contaminating the US asset pass.

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

These five resources now have a version-specific XML at `assets/xml/n64-jp-1.1/objects/object_mag.xml`. `make jp-rev1-object-mag VERSION=n64-jp-1.1` extracts them directly from the Japanese baserom with ZAPD. The three I8 outputs matched the independently extracted pixels exactly; the two I4 outputs repack byte-exact after accounting for ZAPD's preview scaling of 4-bit intensity values.

The rest of the normal Japanese `assets` target must not simply point all existing XML at the Japanese baserom. Version-specific XML coverage still needs to be introduced resource-by-resource after each layout is verified.

## Research manifest

The committed source of truth for currently verified ranges is:

```text
tools/jp_rev1/research_manifest.json
```

The extractor validates every declared offset against the extracted segment size and records SHA-256 hashes in its generated `report.json`. It also records hashes and sizes for important Japanese segments that were encountered during localization research, including `code`, `jpn_message_data_static`, `item_name_static`, `do_action_static`, title/error/parameter/day-telop assets, and the boss objects listed above.

## Scope and next steps

The native Japanese message pipeline and four complete UI segments are now promoted into the JP build path, while the verified `object_mag` subset remains research-only because it is not a complete object definition. Remaining work is broader version coverage rather than message-format discovery:

1. reconstruct the complete Japanese `title_static` layout and model the currently unaccounted tail/layout differences in `parameter_static`;
2. complete JP `object_mag` and expand Japanese XML coverage for other assets whose layouts differ from US;
3. extend `tools/filelists`, code/data matching, and full-ROM build support for `n64-jp-1.1`;
4. remove the remaining dependency on a US baserom for Japanese asset/audio setup as each subsystem becomes native.

The research extractor remains useful as an independent readback oracle while those pieces are migrated into the normal build.
