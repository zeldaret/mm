#ifndef MESSAGE_DATA_FMT_H
#define MESSAGE_DATA_FMT_H

/*
 * Macros to create both a constant and a string literal from a magic value
 *   The constants are used in code files when parsing text for various purposes
 *   The strings are used in the message_data_static files themselves, as you can only concat strings with other strings
 */

#ifndef GLUE
#define GLUE(a, b) a##b
#endif

#define STRINGIFY(s) #s
#define EXPAND_AND_STRINGIFY(s) STRINGIFY(s)

#define HEX(N) GLUE(0x, N)
#define STR(N) EXPAND_AND_STRINGIFY(GLUE(\x, N))

/*
 * Text control characters
 */

// Control character magic values, in 2-digit hex without prefix
#define CTRL_COLOR_0 00
#define CTRL_COLOR_1 01
#define CTRL_COLOR_2 02
#define CTRL_COLOR_3 03
#define CTRL_COLOR_4 04
#define CTRL_COLOR_5 05
#define CTRL_COLOR_6 06
#define CTRL_COLOR_7 07
#define CTRL_COLOR_8 08
#define CTRL_0A 0A
#define CTRL_0B 0B
#define CTRL_0C 0C
#define CTRL_0D 0D
#define CTRL_0E 0E
#define CTRL_0F 0F
#define CTRL_BOX_BREAK 10
#define CTRL_BOX_BREAK2 12
#define CTRL_13 13
#define CTRL_SHIFT 14
#define CTRL_15 15
#define CTRL_PLAYERNAME 16
#define CTRL_QUICKTEXT_ENABLE 17
#define CTRL_QUICKTEXT_DISABLE 18
#define CTRL_19 19
#define CTRL_1A 1A
#define CTRL_1B 1B
#define CTRL_1C 1C
#define CTRL_1D 1D
#define CTRL_SOUND 1E
#define CTRL_1F 1F
#define CTRL_END BF
#define CTRL_BACKGROUND C1
#define CTRL_TWO_CHOICE C2
#define CTRL_THREE_CHOICE C3
#define CTRL_C4 C4
#define CTRL_C5 C5
#define CTRL_C6 C6
#define CTRL_C7 C7
#define CTRL_C8 C8
#define CTRL_C9 C9
#define CTRL_CA CA
#define CTRL_CB CB
#define CTRL_CC CC
#define CTRL_CD CD
#define CTRL_CE CE
#define CTRL_CF CF
#define CTRL_D0 D0
#define CTRL_D1 D1
#define CTRL_D2 D2
#define CTRL_D3 D3
#define CTRL_D4 D4
#define CTRL_D5 D5
#define CTRL_D6 D6
#define CTRL_D7 D7
#define CTRL_D8 D8
#define CTRL_D9 D9
#define CTRL_DA DA
#define CTRL_DB DB
#define CTRL_DC DC
#define CTRL_DD DD
#define CTRL_DE DE
#define CTRL_DF DF
#define CTRL_END_CONVERSATION E0
#define CTRL_E1 E1
#define CTRL_E2 E2
#define CTRL_E3 E3
#define CTRL_E4 E4
#define CTRL_E5 E5
#define CTRL_E6 E6
#define CTRL_E7 E7
#define CTRL_E8 E8
#define CTRL_F0 F0
#define CTRL_F1 F1
#define CTRL_F2 F2
#define CTRL_F3 F3
#define CTRL_F4 F4
#define CTRL_F5 F5
#define CTRL_F6 F6
#define CTRL_F7 F7
#define CTRL_F8 F8
#define CTRL_F9 F9
#define CTRL_FA FA
#define CTRL_FB FB
#define CTRL_FC FC
#define CTRL_FD FD
#define CTRL_FE FE
#define CTRL_FF FF

#ifdef MESSAGE_DATA_STATIC
// For use in message_data_static files

#define ARG(x) x

// while a control character, newlines are handled in the charmap conversion
// stage to allow normal newline \n usage in message_data_static files

#define CMD_COLOR_0 STR(CTRL_COLOR_0)
#define CMD_COLOR_1 STR(CTRL_COLOR_1)
#define CMD_COLOR_2 STR(CTRL_COLOR_2)
#define CMD_COLOR_3 STR(CTRL_COLOR_3)
#define CMD_COLOR_4 STR(CTRL_COLOR_4)
#define CMD_COLOR_5 STR(CTRL_COLOR_5)
#define CMD_COLOR_6 STR(CTRL_COLOR_6)
#define CMD_COLOR_7 STR(CTRL_COLOR_7)
#define CMD_COLOR_8 STR(CTRL_COLOR_8)
#define CMD_0A STR(CTRL_0A)
#define CMD_0B STR(CTRL_0B)
#define CMD_0C STR(CTRL_0C)
#define CMD_0D STR(CTRL_0D)
#define CMD_0E STR(CTRL_0E)
#define CMD_0F STR(CTRL_0F)
#define CMD_BOX_BREAK STR(CTRL_BOX_BREAK)
#define CMD_BOX_BREAK2 STR(CTRL_BOX_BREAK2)
#define CMD_13 STR(CTRL_13)
#define CMD_SHIFT(x) STR(CTRL_SHIFT) ARG(x) // 1
#define CMD_15 STR(CTRL_15)
#define CMD_PLAYERNAME STR(CTRL_PLAYERNAME)
#define CMD_QUICKTEXT_ENABLE STR(CTRL_QUICKTEXT_ENABLE)
#define CMD_QUICKTEXT_DISABLE STR(CTRL_QUICKTEXT_DISABLE)
#define CMD_19 STR(CTRL_19)
#define CMD_1A STR(CTRL_1A)
#define CMD_1B(x) STR(CTRL_1B) ARG(x) // 2
#define CMD_1C(x) STR(CTRL_1C) ARG(x) // 2
#define CMD_1D(x) STR(CTRL_1D) ARG(x) // 2
#define CMD_SOUND(x) STR(CTRL_SOUND) ARG(x) // 2
#define CMD_1F(x) STR(CTRL_1F) ARG(x) // 2
#define CMD_END STR(CTRL_END)
#define CMD_BACKGROUND STR(CTRL_BACKGROUND)
#define CMD_TWO_CHOICE STR(CTRL_TWO_CHOICE)
#define CMD_THREE_CHOICE STR(CTRL_THREE_CHOICE)
#define CMD_C4 STR(CTRL_C4)
#define CMD_C5 STR(CTRL_C5)
#define CMD_C6 STR(CTRL_C6)
#define CMD_C7 STR(CTRL_C7)
#define CMD_C8 STR(CTRL_C8)
#define CMD_C9 STR(CTRL_C9)
#define CMD_CA STR(CTRL_CA)
#define CMD_CB STR(CTRL_CB)
#define CMD_CC STR(CTRL_CC)
#define CMD_CD STR(CTRL_CD)
#define CMD_CE STR(CTRL_CE)
#define CMD_CF STR(CTRL_CF)
#define CMD_D0 STR(CTRL_D0)
#define CMD_D1 STR(CTRL_D1)
#define CMD_D2 STR(CTRL_D2)
#define CMD_D3 STR(CTRL_D3)
#define CMD_D4 STR(CTRL_D4)
#define CMD_D5 STR(CTRL_D5)
#define CMD_D6 STR(CTRL_D6)
#define CMD_D7 STR(CTRL_D7)
#define CMD_D8 STR(CTRL_D8)
#define CMD_D9 STR(CTRL_D9)
#define CMD_DA STR(CTRL_DA)
#define CMD_DB STR(CTRL_DB)
#define CMD_DC STR(CTRL_DC)
#define CMD_DD STR(CTRL_DD)
#define CMD_DE STR(CTRL_DE)
#define CMD_DF STR(CTRL_DF)
#define CMD_END_CONVERSATION STR(CTRL_END_CONVERSATION)
#define CMD_E1 STR(CTRL_E1)
#define CMD_E2 STR(CTRL_E2)
#define CMD_E3 STR(CTRL_E3)
#define CMD_E4 STR(CTRL_E4)
#define CMD_E5 STR(CTRL_E5)
#define CMD_E6 STR(CTRL_E6)
#define CMD_E7 STR(CTRL_E7)
#define CMD_E8 STR(CTRL_E8)
#define CMD_F0 STR(CTRL_F0)
#define CMD_F1 STR(CTRL_F1)
#define CMD_F2 STR(CTRL_F2)
#define CMD_F3 STR(CTRL_F3)
#define CMD_F4 STR(CTRL_F4)
#define CMD_F5 STR(CTRL_F5)
#define CMD_F6 STR(CTRL_F6)
#define CMD_F7 STR(CTRL_F7)
#define CMD_F8 STR(CTRL_F8)
#define CMD_F9 STR(CTRL_F9)
#define CMD_FA STR(CTRL_FA)
#define CMD_FB STR(CTRL_FB)
#define CMD_FC STR(CTRL_FC)
#define CMD_FD STR(CTRL_FD)
#define CMD_FE STR(CTRL_FE)
#define CMD_FF STR(CTRL_FF)

#else

#endif

#endif
