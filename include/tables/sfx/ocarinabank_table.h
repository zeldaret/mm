/**
 * Sfx Ocarina Bank
 *
 * DEFINE_SFX should be used for all sfx define in the ocarina bank from sequence 0
 *    - Argument 0: Channel name for sequence 0
 *    - Argument 1: Enum value for this sfx
 *    - Argument 2: Importance for deciding which sfx to prioritize. Higher values have greater importance
 *    - Argument 3: Slows the decay of volume with distance (a 3-bit number ranging from 0-7)
 *    - Argument 4: Applies increasingly random offsets to frequency (a 2-bit number ranging from 0-3)
 *    - Argument 5: Various flags to add properties to the sfx
 *    - Argument 6: Various flags to add properties to the sfx
 */
/* 0x5800 */ DEFINE_SFX(CHAN_B183, NA_SE_OC_OCARINA, 0x30, 0, 0, 0, 0)
/* 0x5801 */ DEFINE_SFX(CHAN_B237, NA_SE_OC_ABYSS, 0x30, 0, 0, 0, SFX_FLAG_BLOCK_EQUAL_IMPORTANCE)
/* 0x5802 */ DEFINE_SFX(CHAN_2788, NA_SE_OC_DOOR_OPEN, 0x30, 2, 1, 0, SFX_FLAG_BEHIND_SCREEN_Z_INDEX | SFX_FLAG_SURROUND_LOWPASS_FILTER)
/* 0x5803 */ DEFINE_SFX(CHAN_B233, NA_SE_OC_SECRET_WARP_IN, 0x30, 0, 0, 0, 0)
/* 0x5804 */ DEFINE_SFX(CHAN_B20E, NA_SE_OC_SECRET_WARP_OUT, 0x30, 0, 0, 0, 0)
/* 0x5805 */ DEFINE_SFX(CHAN_35A9, NA_SE_OC_SECRET_HOLE_OUT, 0x30, 0, 0, 0, 0)
/* 0x5806 */ DEFINE_SFX(CHAN_B264, NA_SE_OC_REVENGE, 0x30, 0, 0, 0, 0)
/* 0x5807 */ DEFINE_SFX(CHAN_B26E, NA_SE_OC_TUNAMI, 0x30, 0, 0, 0, 0)
/* 0x5808 */ DEFINE_SFX(CHAN_A87F, NA_SE_OC_TELOP_IMPACT, 0x30, 0, 0, 0, 0)
/* 0x5809 */ DEFINE_SFX(CHAN_42EF, NA_SE_OC_WOOD_GATE_OPEN, 0x30, 0, 0, 0, 0)
/* 0x580A */ DEFINE_SFX(CHAN_1776, NA_SE_OC_FIREWORKS, 0x30, 0, 0, 0, SFX_FLAG_VOLUME_NO_DIST)
/* 0x580B */ DEFINE_SFX(CHAN_B28A, NA_SE_OC_WHITE_OUT_INTO_KYOJIN, 0x30, 0, 0, 0, SFX_FLAG_VOLUME_NO_DIST)
/* 0x580C */ DEFINE_SFX(CHAN_B20E, NA_SE_OC_12, 0x30, 0, 0, 0, 0)
/* 0x580D */ DEFINE_SFX(CHAN_35A9, NA_SE_OC_13, 0x30, 0, 0, 0, 0)
/* 0x580E */ DEFINE_SFX(CHAN_B264, NA_SE_OC_14, 0x30, 0, 0, 0, 0)
/* 0x580F */ DEFINE_SFX(CHAN_B183, NA_SE_OC_15, 0x30, 0, 0, 0, 0)
