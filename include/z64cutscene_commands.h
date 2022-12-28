#ifndef Z64CUTSCENE_COMMANDS_H
#define Z64CUTSCENE_COMMANDS_H

#include "command_macros_base.h"
#include "z64cutscene.h"

/**
 * Cutscene scripts are arrays of `CutsceneData` words, including bit-packed integers and floats.
 */

/**
 * Marks the beginning of a cutscene script.
 * 
 * ARGS
 *   s32 totalEntries (e), s32 frameCount (n)
 * FORMAT
 *   eeeeeeee nnnnnnnn
 *   size = 0x8
 */
#define CS_BEGIN_CUTSCENE(totalEntries, frameCount) { CMD_W(totalEntries) }, { CMD_W(frameCount) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000000A eeeeeeee
 *   size = 0x8
 */
#define CS_TEXT_LIST(entries) { CS_CMD_TEXT }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 messageId (i), s16 startFrame (s), s16 endFrame (e), s16 type (o),
 *   s16 topOptionBranch (y), s16 bottomOptionBranch (n)
 * FORMAT
 *   iiiissss eeeeoooo yyyynnnn
 *   size = 0xC
 */
#define CS_TEXT_DISPLAY_TEXTBOX(messageId, startFrame, endFrame, type, topOptionBranch, bottomOptionBranch) \
    { CMD_HH(messageId, startFrame) }, { CMD_HH(endFrame, type) }, { CMD_HH(topOptionBranch, bottomOptionBranch) }

/**
 * ARGS
 *   s16 messageId (i), s16 startFrame (s), s16 endFrame (e),
 *   s16 topOptionBranch (y), s16 bottomOptionBranch (n)
 * FORMAT
 *   iiiissss eeee0000 yyyynnnn
 *   size = 0xC
 */
#define CS_TEXT_DEFAULT(messageId, startFrame, endFrame, topOptionBranch, bottomOptionBranch) \
    CS_TEXT_DISPLAY_TEXTBOX(messageId, startFrame, endFrame, CS_TEXTBOX_TYPE_DEFAULT, topOptionBranch, bottomOptionBranch)

/**
 * ARGS
 *   s16 messageId (i), s16 startFrame (s), s16 endFrame (e),
 *   s16 topOptionBranch (y), s16 bottomOptionBranch (n)
 * FORMAT
 *   iiiissss eeee0001 yyyynnnn
 *   size = 0xC
 */
#define CS_TEXT_TYPE_1(messageId, startFrame, endFrame, topOptionBranch, bottomOptionBranch) \
    CS_TEXT_DISPLAY_TEXTBOX(messageId, startFrame, endFrame, CS_TEXTBOX_TYPE_1, topOptionBranch, bottomOptionBranch)

/**
 * ARGS
 *   s16 ocarinaSongAction (o), s16 startFrame (s), s16 endFrame (e), s16 messageId (i)
 * FORMAT
 *   oooossss eeee0002 iiiiFFFF
 *   size = 0xC
 */
#define CS_TEXT_OCARINA_ACTION(ocarinaSongAction, startFrame, endFrame, messageId) \
    CS_TEXT_DISPLAY_TEXTBOX(ocarinaSongAction, startFrame, endFrame, CS_TEXT_OCARINA_ACTION, messageId, 0xFFFF)

/**
 * ARGS
 *   s16 messageId (i), s16 startFrame (s), s16 endFrame (e),
 *   s16 topOptionBranch (y), s16 bottomOptionBranch (n)
 * FORMAT
 *   iiiissss eeee0003 yyyynnnn
 *   size = 0xC
 */
#define CS_TEXT_TYPE_3(messageId, startFrame, endFrame, topOptionBranch, bottomOptionBranch) \
    CS_TEXT_DISPLAY_TEXTBOX(messageId, startFrame, endFrame, CS_TEXTBOX_TYPE_3, topOptionBranch, bottomOptionBranch)

/**
 * If Player has all 4 bosses' remains then alternativeMessageId is used, otherwise defaultMessageId is used
 * ARGS
 *   s16 defaultMessageId (d), s16 startFrame (s), s16 endFrame (e), s16 alternativeMessageId (a)
 * FORMAT
 *   ddddssss eeee0004 aaaaFFFF
 *   size = 0xC
 */
#define CS_TEXT_BOSSES_REMAINS(defaultMessageId, startFrame, endFrame, alternativeMessageId) \
    CS_TEXT_DISPLAY_TEXTBOX(defaultMessageId, startFrame, endFrame, CS_TEXTBOX_TYPE_BOSSES_REMAINS, alternativeMessageId, 0xFFFF)

/**
 * If Player has every non-transformation mask then alternativeMessageId is used, otherwise defaultMessageId is used
 * ARGS
 *   s16 defaultMessageId (d), s16 startFrame (s), s16 endFrame (e), s16 alternativeMessageId (a)
 * FORMAT
 *   ddddssss eeee0005 aaaaFFFF
 *   size = 0xC
 */
#define CS_TEXT_ALL_NORMAL_MASKS(defaultMessageId, startFrame, endFrame, alternativeMessageId) \
    CS_TEXT_DISPLAY_TEXTBOX(defaultMessageId, startFrame, endFrame, CS_TEXTBOX_TYPE_ALL_NORMAL_MASKS, alternativeMessageId, 0xFFFF)

/**
 * ARGS
 *   s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   FFFFssss eeeeFFFF FFFFFFFF
 *   size = 0xC
 */
#define CS_TEXT_NONE(startFrame, endFrame) \
    CS_TEXT_DISPLAY_TEXTBOX(0xFFFF, startFrame, endFrame, CS_TEXTBOX_TYPE_NONE, 0xFFFF, 0xFFFF)


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000005A eeeeeeee
 *   size = 0x8
 */
#define CS_CAM_SPLINE_LIST(entries) { CS_CMD_CAMERA_SPLINE }, { CMD_W(entries) }

#define CS_CAM_SPLINE(numEntries, unused0, unused1, unk_06) \
    { CMD_HH(numEntries, unused0) }, { CMD_HH(unused1, unk_06) }

#define CS_CAM_POINT(interp, unk_01, unk_02, posX, posY, posZ, unk_0A) \
    { CMD_BBH(interp, unk_01, unk_02) }, { CMD_HH(posX, posY) }, { CMD_HH(posZ, unk_0A) }

#define CS_CAM_MISC(unused0, roll, fov, unused1) \
    { CMD_HH(unused0, roll) }, { CMD_HH(fov, unused1) }

#define CS_CAM_END() { CMD_HH(0xFFFF, 4) }


/**
 * Declares a list of `CS_MISC` entries.
 * 
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000096 eeeeeeee
 *   size = 0x8
 */
#define CS_MISC_LIST(entries) { CS_CMD_MISC }, { CMD_W(entries) }

/**
 * Various miscellaneous commands.
 * @see `CutsceneMiscType` enum for the different types of commands.
 * @note setting `endFrame` to same value as `startFrame` will not behave as expected.
 * For commands that only need to last one frame, set `endFrame` to `startFrame + 1`.
 * 
 * ARGS
 *   s16 unk (u), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   uuuussss eeeeUUUU
 *   size = 0x8
 */
#define CS_MISC(unk, startFrame, endFrame, unk_06) \
    { CMD_HH(unk, startFrame) }, { CMD_HH(endFrame, unk_06) }


/**
 * Declares a list of `CS_LIGHT_SETTING` entries.
 * 
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000097 eeeeeeee
 *   size = 0x8
 */
#define CS_LIGHT_SETTING_LIST(entries) { CS_CMD_LIGHT_SETTING }, { CMD_W(entries) }

/**
 * Changes the environment lights to the specified setting.
 * The lighting change will take place immediately with no blending.
 * 
 * ARGS
 *   s16 setting (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_LIGHTING(lightSetting, startFrame, endFrame) \
    { CMD_HH(lightSetting, startFrame) }, { CMD_HH(endFrame, endFrame) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000098 eeeeeeee
 *   size = 0x8
 */
#define CS_TRANSITION_LIST(entries) { CS_CMD_TRANSITION }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 transitionType (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_TRANSITION(transitionType, startFrame, endFrame) \
    { CMD_HH(transitionType, startFrame) }, { CMD_HH(endFrame, endFrame) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000099 eeeeeeee
 *   size = 0x8
 */
#define CS_MOTION_BLUR_LIST(entries) { CS_CMD_MOTION_BLUR }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_MOTION_BLUR(base, startFrame, endFrame) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, endFrame) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000009A eeeeeeee
 *   size = 0x8
 */
#define CS_GIVETATL_LIST(entries) { CS_CMD_GIVE_TATL }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_GIVETATL(base, startFrame, endFrame) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, endFrame) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000009B eeeeeeee
 *   size = 0x8
 */
#define CS_FADESCREEN_LIST(entries) { CS_CMD_FADE_SCREEN }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e),
 *   u8 red (r), u8 green (g), blue (b)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeerrgg bbUUUUUU
 *   size = 0x0C
 */
#define CS_FADESCREEN(base, startFrame, endFrame, red, green, blue) \
    { CMD_HH(base, startFrame) }, { CMD_HBB(endFrame, red, green) }, { CMD_BBBB(blue, 0, 0, 0) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000009C eeeeeeee
 *   size = 0x8
 */
#define CS_FADESEQ_LIST(entries) { CS_CMD_FADE_OUT_SEQ }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU UUUUUUUU
 *   size = 0x0C
 */
#define CS_FADESEQ(base, startFrame, endFrame) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, 0) }, { CMD_W(0) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000009D eeeeeeee
 *   size = 0x8
 */
#define CS_TIME_LIST(entries) { CS_CMD_TIME }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 unk (u), s16 startFrame (s), s16 endFrame (e), s8 hour (h), s8 min (m)
 * FORMAT
 *   Capital U is Unused
 *   uuuussss eeeehhmm UUUUUUUU
 *   size = 0xC
 */
#define CS_TIME(unk, startFrame, endFrame, hour, min, unused) \
    { CMD_HH(unk, startFrame) }, { CMD_HBB(endFrame, hour, min) }, { CMD_W(unused) }


/**
 * ARGS
 *   s32 cmdType (c), s32 entries (e)
 * FORMAT
 *   cccccccc eeeeeeee
 *   size = 0x8
 */
#define CS_ACTOR_ACTION_LIST(cmdType, entries) { CMD_W(cmdType) }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 npcAction (a), s16 startFrame (s), s16 endFrame (e),
 *   s16 rotX (u),      s16 rotY (v),       s16 rotZ (w),
 *   s32 startX (i),    s32 startY (j),     s32 startZ (k),
 *   s32 endX (l),      s32 endY (m),       s32 endZ (n),
 *   f32 normX (x),     f32 normY (y),      f32 normZ (z),
 * FORMAT
 *   aaaassss eeeeuuuu vvvvwwww iiiiiiii jjjjjjjj kkkkkkkk llllllll mmmmmmmm nnnnnnnn xxxxxxxx yyyyyyyy zzzzzzzz
 *   size = 0x30
 */
#define CS_ACTOR_ACTION(npcAction, startFrame, endFrame, rotX, rotY, rotZ, startX, startY, startZ, endX, endY, endZ, normX, normY, normZ) \
    { CMD_HH(npcAction, startFrame) }, { CMD_HH(endFrame, rotX) }, { CMD_HH(rotY, rotZ) }, \
    { CMD_W(startX) }, { CMD_W(startY) }, { CMD_W(startZ) }, \
    { CMD_W(endX) }, { CMD_W(endY) }, { CMD_W(endZ) }, \
    { CMD_F(normX) }, { CMD_F(normY) }, { CMD_F(normZ) }


/**
 * ARGS
 *   s32 cmdType (c), s32 entries (e)
 * FORMAT
 *   000000C8 eeeeeeee
 *   size = 0x8
 */
#define CS_PLAYER_ACTION_LIST(entries) { CS_CMD_PLAYER_CUE }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 playerCue (a), s16 startFrame (s), s16 endFrame (e),
 *   s16 rotX (u),       s16 rotY (v),       s16 rotZ (w),
 *   s32 startX (i),     s32 startY (j),     s32 startZ (k),
 *   s32 endX (l),       s32 endY (m),       s32 endZ (n),
 *   f32 normX (x),      f32 normY (y),      f32 normZ (z),
 * FORMAT
 *   aaaassss eeeeuuuu vvvvwwww iiiiiiii jjjjjjjj kkkkkkkk llllllll mmmmmmmm nnnnnnnn xxxxxxxx yyyyyyyy zzzzzzzz
 *   size = 0x30
 */
#define CS_PLAYER_ACTION(playerCue, startFrame, endFrame, rotX, rotY, rotZ, startX, startY, startZ, endX, endY, endZ, normX, normY, normZ) \
    CS_ACTOR_ACTION(playerCue, startFrame, endFrame, rotX, rotY, rotZ, startX, startY, startZ, endX, endY, endZ, normX, normY, normZ)


/**
 * Declares a list of `CS_START_SEQ` entries.
 * 
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000012C eeeeeeee
 *   size = 0x8
 */
#define CS_START_SEQ_LIST(entries) \
    { CS_CMD_START_SEQ }, { CMD_W(entries) }

/**
 * Starts a sequence at the specified time.
 * @note `endFrame` is not used in the implementation of the command, so its value does not matter
 * 
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_START_SEQ(sequence, startFrame, endFrame) \
    { CMD_HH((sequence + 1), startFrame) }, { CMD_HH(endFrame, endFrame) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000130 eeeeeeee
 *   size = 0x8
 */
#define CS_SFX_REVERB_INDEX_2_LIST(entries) { CS_CMD_SFX_REVERB_INDEX_2 }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SFX_REVERB_INDEX_2(base, startFrame, endFrame, unk_06) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, unk_06) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000131 eeeeeeee
 *   size = 0x8
 */
#define CS_SFX_REVERB_INDEX_1_LIST(entries) { CS_CMD_SFX_REVERB_INDEX_1 }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_SFX_REVERB_INDEX_1(base, startFrame, endFrame, unk_06) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, unk_06) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000132 eeeeeeee
 *   size = 0x8
 */
#define CS_MODIFY_SEQ_LIST(entries) { CS_CMD_MODIFY_SEQ }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_MODIFY_SEQ(base, startFrame, endFrame) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, endFrame) }


/**
 * Declares a list of `CS_STOP_SEQ` entries.
 * 
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000133 eeeeeeee
 *   size = 0x8
 */
#define CS_STOP_SEQ_LIST(entries) { CS_CMD_STOP_SEQ }, { CMD_W(entries) }

/**
 * Stops a sequence at the specified time.
 * 
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_STOP_SEQ(seqId, startFrame, endFrame, unk_06) \
    { CMD_HH((seqId + 1), startFrame) }, { CMD_HH(endFrame, unk_06) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000134 eeeeeeee
 *   size = 0x8
 */
#define CS_PLAYAMBIENCE_LIST(entries) { CS_CMD_START_AMBIENCE }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_PLAYAMBIENCE(base, startFrame, endFrame, unk_06) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, unk_06) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000135 eeeeeeee
 *   size = 0x8
 */
#define CS_FADEAMBIENCE_LIST(entries) { CS_CMD_FADE_OUT_AMBIENCE }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_FADEAMBIENCE(base, startFrame, endFrame, unk_06) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, unk_06) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000015E eeeeeeee
 *   size = 0x8
 */
#define CS_TERMINATOR_LIST(entries) { CS_CMD_DESTINATION }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_TERMINATOR(base, startFrame, endFrame) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, endFrame) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000015F eeeeeeee
 *   size = 0x8
 */
#define CS_CHOOSE_CREDITS_SCENES_LIST(entries) { CS_CMD_CHOOSE_CREDITS_SCENES }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_CHOOSE_CREDITS_SCENES(base, startFrame, endFrame) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, endFrame) }


/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_RUMBLE_LIST(entries) { CS_CMD_RUMBLE }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_RUMBLE(base, startFrame, endFrame, intensity, decayTimer, decayStep) \
    { CMD_HH(base, startFrame) }, { CMD_HBB(endFrame, intensity, decayTimer) }, { CMD_BBBB(decayStep, 0, 0, 0) }


/**
 * ARGS
 *   s32 cmd (c), s32 entries (e)
 * FORMAT
 *   cccccccc eeeeeeee
 *   size = 0x8
 */
#define CS_UNK_DATA_LIST(cmd, entries) { CMD_W(cmd) }, { CMD_W(entries) }

/**
 * ARGS
 *   s16 base (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x8
 */
#define CS_UNK_DATA(base, startFrame, endFrame, unk_06) \
    { CMD_HH(base, startFrame) }, { CMD_HH(endFrame, unk_06) }


/**
 * Marks the end of a cutscene
 */
#define CS_END() { CMD_W(0xFFFFFFFF) }

// TODO: Fix ZAPD and delete these
#define CS_LIGHTING_LIST               CS_LIGHT_SETTING_LIST
#define CS_CAMERA_LIST                 CS_CAM_SPLINE_LIST
#define CS_TEXT_LEARN_SONG             CS_TEXT_OCARINA_ACTION
#define CS_SCENE_TRANS_FX_LIST         CS_TRANSITION_LIST
#define CS_SCENE_TRANS_FX              CS_TRANSITION
#define CS_PLAYSEQ_LIST                CS_START_SEQ_LIST
#define CS_STOPSEQ_LIST                CS_STOP_SEQ_LIST
#define CS_FADE_BGM_LIST               CS_FADE_OUT_SEQ_LIST
#define CS_FADE_BGM                    CS_FADE_OUT_SEQ
#define CS_SCENE_UNK_130_LIST          CS_SFX_REVERB_INDEX_2_LIST
#define CS_SCENE_UNK_130               CS_SFX_REVERB_INDEX_2
#define CS_SCENE_UNK_131_LIST          CS_SFX_REVERB_INDEX_1_LIST
#define CS_SCENE_UNK_131               CS_SFX_REVERB_INDEX_1
#define CS_SCENE_UNK_132_LIST          CS_MODIFY_SEQ_LIST
#define CS_SCENE_UNK_132               CS_MODIFY_SEQ
#define CS_MOTIONBLUR_LIST             CS_MOTION_BLUR_LIST
#define CS_MOTIONBLUR                  CS_MOTION_BLUR
// #define CS_TERMINATOR                  CS_DESTINATION

#define CS_PLAYSEQ(seqId, startFrame, endFrame) \
CS_START_SEQ((seqId)-1, startFrame, endFrame)

#define CS_STOPSEQ(seqId, startFrame, endFrame, unk_06) \
CS_STOP_SEQ((seqId)-1, startFrame, endFrame, unk_06)


#endif
