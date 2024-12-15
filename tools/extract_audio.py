#!/usr/bin/env python3
# SPDX-FileCopyrightText: © 2024 ZeldaRET
# SPDX-License-Identifier: CC0-1.0
#
#   Configures and runs baserom audio extraction
#

import argparse

from version import version_config

from audio.extraction.audio_extract import extract_audio_for_version, GameVersionInfo
from audio.extraction.disassemble_sequence import MMLVersion, SequenceTableSpec, SqSection

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="baserom audio asset extractor")
    parser.add_argument("-o", "--extracted-dir", required=True, help="path to extracted directory")
    parser.add_argument("-v", "--version", required=True, help="version name")
    parser.add_argument("--read-xml", required=False, action="store_true", help="Read extraction xml files")
    parser.add_argument("--write-xml", required=False, action="store_true", help="Write extraction xml files")
    args = parser.parse_args()

    version = args.version

    config = version_config.load_version_config(version)

    code_vram = config.dmadata_segments["code"].vram
    soundfont_table_code_offset = config.variables["gSoundFontTable"] - code_vram
    seq_font_table_code_offset = config.variables["gSequenceFontTable"] - code_vram
    seq_table_code_offset = config.variables["gSequenceTable"] - code_vram
    sample_bank_table_code_offset = config.variables["gSampleBankTable"] - code_vram

    # List any sequences that are "handwritten", we don't extract these by
    # default as we want these checked in for documentation.
    handwritten_sequences = (0, 1)

    # Sequence enum names for extraction purposes.
    seq_enum_names = (
        "NA_BGM_GENERAL_SFX",
        "NA_BGM_AMBIENCE",
        "NA_BGM_TERMINA_FIELD",
        "NA_BGM_CHASE",
        "NA_BGM_MAJORAS_THEME",
        "NA_BGM_CLOCK_TOWER",
        "NA_BGM_STONE_TOWER_TEMPLE",
        "NA_BGM_INV_STONE_TOWER_TEMPLE",
        "NA_BGM_FAILURE_0",
        "NA_BGM_FAILURE_1",
        "NA_BGM_HAPPY_MASK_SALESMAN",
        "NA_BGM_SONG_OF_HEALING",
        "NA_BGM_SWAMP_REGION",
        "NA_BGM_ALIEN_INVASION",
        "NA_BGM_SWAMP_CRUISE",
        "NA_BGM_SHARPS_CURSE",
        "NA_BGM_GREAT_BAY_REGION",
        "NA_BGM_IKANA_REGION",
        "NA_BGM_DEKU_PALACE",
        "NA_BGM_MOUNTAIN_REGION",
        "NA_BGM_PIRATES_FORTRESS",
        "NA_BGM_CLOCK_TOWN_DAY_1",
        "NA_BGM_CLOCK_TOWN_DAY_2",
        "NA_BGM_CLOCK_TOWN_DAY_3",
        "NA_BGM_FILE_SELECT",
        "NA_BGM_CLEAR_EVENT",
        "NA_BGM_ENEMY",
        "NA_BGM_BOSS",
        "NA_BGM_WOODFALL_TEMPLE",
        "NA_BGM_CLOCK_TOWN_MAIN_SEQUENCE",
        "NA_BGM_OPENING",
        "NA_BGM_INSIDE_A_HOUSE",
        "NA_BGM_GAME_OVER",
        "NA_BGM_CLEAR_BOSS",
        "NA_BGM_GET_ITEM",
        "NA_BGM_CLOCK_TOWN_DAY_2_PTR",
        "NA_BGM_GET_HEART",
        "NA_BGM_TIMED_MINI_GAME",
        "NA_BGM_GORON_RACE",
        "NA_BGM_MUSIC_BOX_HOUSE",
        "NA_BGM_FAIRY_FOUNTAIN",
        "NA_BGM_ZELDAS_LULLABY",
        "NA_BGM_ROSA_SISTERS",
        "NA_BGM_OPEN_CHEST",
        "NA_BGM_MARINE_RESEARCH_LAB",
        "NA_BGM_GIANTS_THEME",
        "NA_BGM_SONG_OF_STORMS",
        "NA_BGM_ROMANI_RANCH",
        "NA_BGM_GORON_VILLAGE",
        "NA_BGM_MAYORS_OFFICE",
        "NA_BGM_OCARINA_EPONA",
        "NA_BGM_OCARINA_SUNS",
        "NA_BGM_OCARINA_TIME",
        "NA_BGM_OCARINA_STORM",
        "NA_BGM_ZORA_HALL",
        "NA_BGM_GET_NEW_MASK",
        "NA_BGM_MINI_BOSS",
        "NA_BGM_GET_SMALL_ITEM",
        "NA_BGM_ASTRAL_OBSERVATORY",
        "NA_BGM_CAVERN",
        "NA_BGM_MILK_BAR",
        "NA_BGM_ZELDA_APPEAR",
        "NA_BGM_SARIAS_SONG",
        "NA_BGM_GORON_GOAL",
        "NA_BGM_HORSE",
        "NA_BGM_HORSE_GOAL",
        "NA_BGM_INGO",
        "NA_BGM_KOTAKE_POTION_SHOP",
        "NA_BGM_SHOP",
        "NA_BGM_OWL",
        "NA_BGM_SHOOTING_GALLERY",
        "NA_BGM_OCARINA_SOARING",
        "NA_BGM_OCARINA_HEALING",
        "NA_BGM_INVERTED_SONG_OF_TIME",
        "NA_BGM_SONG_OF_DOUBLE_TIME",
        "NA_BGM_SONATA_OF_AWAKENING",
        "NA_BGM_GORON_LULLABY",
        "NA_BGM_NEW_WAVE_BOSSA_NOVA",
        "NA_BGM_ELEGY_OF_EMPTINESS",
        "NA_BGM_OATH_TO_ORDER",
        "NA_BGM_SWORD_TRAINING_HALL",
        "NA_BGM_OCARINA_LULLABY_INTRO",
        "NA_BGM_LEARNED_NEW_SONG",
        "NA_BGM_BREMEN_MARCH",
        "NA_BGM_BALLAD_OF_THE_WIND_FISH",
        "NA_BGM_SONG_OF_SOARING",
        "NA_BGM_MILK_BAR_DUPLICATE",
        "NA_BGM_FINAL_HOURS",
        "NA_BGM_MIKAU_RIFF",
        "NA_BGM_MIKAU_FINALE",
        "NA_BGM_FROG_SONG",
        "NA_BGM_OCARINA_SONATA",
        "NA_BGM_OCARINA_LULLABY",
        "NA_BGM_OCARINA_NEW_WAVE",
        "NA_BGM_OCARINA_ELEGY",
        "NA_BGM_OCARINA_OATH",
        "NA_BGM_MAJORAS_LAIR",
        "NA_BGM_OCARINA_LULLABY_INTRO_PTR",
        "NA_BGM_OCARINA_GUITAR_BASS_SESSION",
        "NA_BGM_PIANO_SESSION",
        "NA_BGM_INDIGO_GO_SESSION",
        "NA_BGM_SNOWHEAD_TEMPLE",
        "NA_BGM_GREAT_BAY_TEMPLE",
        "NA_BGM_NEW_WAVE_SAXOPHONE",
        "NA_BGM_NEW_WAVE_VOCAL",
        "NA_BGM_MAJORAS_WRATH",
        "NA_BGM_MAJORAS_INCARNATION",
        "NA_BGM_MAJORAS_MASK",
        "NA_BGM_BASS_PLAY",
        "NA_BGM_DRUMS_PLAY",
        "NA_BGM_PIANO_PLAY",
        "NA_BGM_IKANA_CASTLE",
        "NA_BGM_GATHERING_GIANTS",
        "NA_BGM_KAMARO_DANCE",
        "NA_BGM_CREMIA_CARRIAGE",
        "NA_BGM_KEATON_QUIZ",
        "NA_BGM_END_CREDITS",
        "NA_BGM_OPENING_LOOP",
        "NA_BGM_TITLE_THEME",
        "NA_BGM_DUNGEON_APPEAR",
        "NA_BGM_WOODFALL_CLEAR",
        "NA_BGM_SNOWHEAD_CLEAR",
        "NA_BGM_SEQ_122",
        "NA_BGM_INTO_THE_MOON",
        "NA_BGM_GOODBYE_GIANT",
        "NA_BGM_TATL_AND_TAEL",
        "NA_BGM_MOONS_DESTRUCTION",
        "NA_BGM_END_CREDITS_SECOND_HALF",
    )

    # Some bugged soundfonts report the wrong samplebank. Map them to the correct samplebank for proper sample discovery.
    fake_banks = {
        "n64-jp-1.0" : { 37 : 2 },
    }.get(version, { 40 : 2 })

    # Some audiotable banks have a buffer clearing bug. Indicate which banks suffer from this.
    audiotable_buffer_bugs = ()

    # Tables have no clear start and end in a sequence. Mark the locations of all tables that appear in sequences.
    seq_disas_tables = {
        # sequence number : (spec, ...)
        0 : (
                SequenceTableSpec(0x011E,   8, 0, SqSection.TABLE),
                SequenceTableSpec(0x012E, 464, 0, SqSection.CHAN),
                SequenceTableSpec(0x18B2,  48, 0, SqSection.LAYER),
                SequenceTableSpec(0x1990, 112, 0, SqSection.CHAN),
                SequenceTableSpec(0x23D8,   8, 0, SqSection.TABLE),
                SequenceTableSpec(0x23E8, 464, 0, SqSection.CHAN),
                SequenceTableSpec(0x566E,   8, 0, SqSection.TABLE),
                SequenceTableSpec(0x567E, 733, 0, SqSection.CHAN),
                SequenceTableSpec(0xA4C1,  96, 0, SqSection.CHAN),
                SequenceTableSpec(0xB163,  16, 0, SqSection.CHAN),
                SequenceTableSpec(0xB2FE,   8, 0, SqSection.TABLE),
                SequenceTableSpec(0xB30E, 390, 0, SqSection.CHAN),

            ),
        1 : (
                SequenceTableSpec(0x018A, 20, 0, SqSection.LAYER),
                SequenceTableSpec(0x01B2, 20, 0, SqSection.LAYER),
                SequenceTableSpec(0x01DA, 20, 0, SqSection.LAYER),
                SequenceTableSpec(0x0202, 20, 0, SqSection.LAYER),
                SequenceTableSpec(0x022A, 20, 1, SqSection.LAYER),
                SequenceTableSpec(0x0252, 20, 1, SqSection.LAYER),
                SequenceTableSpec(0x027A, 20, 1, SqSection.LAYER),
            ),
    }

    version_info = GameVersionInfo(version,
                                   MMLVersion.MM,
                                   soundfont_table_code_offset,
                                   seq_font_table_code_offset,
                                   seq_table_code_offset,
                                   sample_bank_table_code_offset,
                                   seq_enum_names,
                                   handwritten_sequences,
                                   fake_banks,
                                   audiotable_buffer_bugs,
                                   seq_disas_tables)

    extract_audio_for_version(version_info, args.extracted_dir, args.read_xml, args.write_xml)
