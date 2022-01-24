/*
 * File: z_en_pm.c
 * Overlay: ovl_En_Pm
 * Description: Postman
 */

#include "z_en_pm.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "objects/object_mm/object_mm.h"

#define FLAGS 0x00000039

#define THIS ((EnPm*)thisx)

void EnPm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AFA4D0(EnPm* this, GlobalContext* globalCtx);
void func_80AFA5FC(EnPm* this, GlobalContext* globalCtx);

static u8 D_80AFAD80[] = {
/* 0x0000 */ SCHEDULE_CMD_DAY_CHECK_L(1, 0x0240 - 0x0005),
/* 0x0005 */ SCHEDULE_CMD_TIME_RANGE_CHECK_L( 9,  0, 12,  0, 0x0117 - 0x000C),
/* 0x000C */ SCHEDULE_CMD_TIME_RANGE_CHECK_L(12,  0, 13,  1, 0x010C - 0x0013),
/* 0x0013 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  1, 15,  0, 0x002B - 0x0019),
/* 0x0019 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(15,  0,  0,  5, 0x0020 - 0x001F),
/* 0x001F */ SCHEDULE_CMD_END(),
/* 0x0020 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x002A - 0x0024),
/* 0x0024 */ SCHEDULE_CMD_RETURN_TIME(15,  0,  0,  5,  8),
/* 0x002A */ SCHEDULE_CMD_END(),
/* 0x002B */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_ICHIBA, 0x0060 - 0x002F),
/* 0x002F */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  1, 13,  4, 0x005A - 0x0035),
/* 0x0035 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  4, 13, 21, 0x0054 - 0x003B),
/* 0x003B */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 48, 14, 56, 0x004E - 0x0041),
/* 0x0041 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 56, 15,  0, 0x0048 - 0x0047),
/* 0x0047 */ SCHEDULE_CMD_END(),
/* 0x0048 */ SCHEDULE_CMD_RETURN_TIME(14, 56, 15,  0,  2),
/* 0x004E */ SCHEDULE_CMD_RETURN_TIME(14, 48, 14, 56, 62),
/* 0x0054 */ SCHEDULE_CMD_RETURN_TIME(13,  4, 13, 21, 53),
/* 0x005A */ SCHEDULE_CMD_RETURN_TIME(13,  1, 13,  4,  1),
/* 0x0060 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_CLOCKTOWER, 0x0095 - 0x0064),
/* 0x0064 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  4, 13, 21, 0x008F - 0x006A),
/* 0x006A */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 21, 13, 39, 0x0089 - 0x0070),
/* 0x0070 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 38, 14, 48, 0x0083 - 0x0076),
/* 0x0076 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 48, 14, 56, 0x007D - 0x007C),
/* 0x007C */ SCHEDULE_CMD_END(),
/* 0x007D */ SCHEDULE_CMD_RETURN_TIME(14, 48, 14, 56, 61),
/* 0x0083 */ SCHEDULE_CMD_RETURN_TIME(14, 38, 14, 48, 60),
/* 0x0089 */ SCHEDULE_CMD_RETURN_TIME(13, 21, 13, 39, 55),
/* 0x008F */ SCHEDULE_CMD_RETURN_TIME(13,  4, 13, 21, 54),
/* 0x0095 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_TOWN, 0x00CA - 0x0099),
/* 0x0099 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 39, 13, 56, 0x00C4 - 0x009F),
/* 0x009F */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 56, 14,  0, 0x00BE - 0x00A5),
/* 0x00A5 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 26, 14, 30, 0x00B8 - 0x00AB),
/* 0x00AB */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 30, 14, 38, 0x00B2 - 0x00B1),
/* 0x00B1 */ SCHEDULE_CMD_END(),
/* 0x00B2 */ SCHEDULE_CMD_RETURN_TIME(14, 30, 14, 38, 59),
/* 0x00B8 */ SCHEDULE_CMD_RETURN_TIME(14, 26, 14, 30, 11),
/* 0x00BE */ SCHEDULE_CMD_RETURN_TIME(13, 56, 14,  0, 10),
/* 0x00C4 */ SCHEDULE_CMD_RETURN_TIME(13, 39, 13, 56, 56),
/* 0x00CA */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_YADOYA, 0x010B - 0x00CE),
/* 0x00CE */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 56, 14,  0, 0x0105 - 0x00D4),
/* 0x00D4 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14,  0, 14,  8, 0x00FF - 0x00DA),
/* 0x00DA */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14,  8, 14, 18, 0x00F9 - 0x00E0),
/* 0x00E0 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 18, 14, 26, 0x00F3 - 0x00E6),
/* 0x00E6 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 26, 14, 30, 0x00ED - 0x00EC),
/* 0x00EC */ SCHEDULE_CMD_END(),
/* 0x00ED */ SCHEDULE_CMD_RETURN_TIME(14, 26, 14, 30, 13),
/* 0x00F3 */ SCHEDULE_CMD_RETURN_TIME(14, 18, 14, 26, 58),
/* 0x00F9 */ SCHEDULE_CMD_RETURN_TIME(14,  8, 14, 18, 16),
/* 0x00FF */ SCHEDULE_CMD_RETURN_TIME(14,  0, 14,  8, 57),
/* 0x0105 */ SCHEDULE_CMD_RETURN_TIME(13, 56, 14,  0, 12),
/* 0x010B */ SCHEDULE_CMD_END(),
/* 0x010C */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x0116 - 0x0110),
/* 0x0110 */ SCHEDULE_CMD_RETURN_TIME(12,  0, 13,  1,  9),
/* 0x0116 */ SCHEDULE_CMD_END(),
/* 0x0117 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_ICHIBA, 0x014C - 0x011B),
/* 0x011B */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 9,  0,  9,  3, 0x0146 - 0x0121),
/* 0x0121 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 9,  3,  9, 17, 0x0140 - 0x0127),
/* 0x0127 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(11, 43, 11, 57, 0x013A - 0x012D),
/* 0x012D */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(11, 57, 12,  0, 0x0134 - 0x0133),
/* 0x0133 */ SCHEDULE_CMD_END(),
/* 0x0134 */ SCHEDULE_CMD_RETURN_TIME(11, 57, 12,  0,  2),
/* 0x013A */ SCHEDULE_CMD_RETURN_TIME(11, 43, 11, 57, 52),
/* 0x0140 */ SCHEDULE_CMD_RETURN_TIME( 9,  3,  9, 17, 38),
/* 0x0146 */ SCHEDULE_CMD_RETURN_TIME( 9,  0,  9,  3,  1),
/* 0x014C */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_CLOCKTOWER, 0x01B1 - 0x0150),
/* 0x0150 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 9,  3,  9, 17, 0x01AB - 0x0156),
/* 0x0156 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 9, 17,  9, 31, 0x01A5 - 0x015C),
/* 0x015C */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 9, 31,  9, 35, 0x019F - 0x0162),
/* 0x0162 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 9, 35,  9, 49, 0x0199 - 0x0168),
/* 0x0168 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(10, 57, 11, 11, 0x0193 - 0x016E),
/* 0x016E */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(11, 11, 11, 25, 0x018D - 0x0174),
/* 0x0174 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(11, 25, 11, 29, 0x0187 - 0x017A),
/* 0x017A */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(11, 29, 11, 43, 0x0181 - 0x0180),
/* 0x0180 */ SCHEDULE_CMD_END(),
/* 0x0181 */ SCHEDULE_CMD_RETURN_TIME(11, 29, 11, 43, 50),
/* 0x0187 */ SCHEDULE_CMD_RETURN_TIME(11, 25, 11, 29,  7),
/* 0x018D */ SCHEDULE_CMD_RETURN_TIME(11, 11, 11, 25, 48),
/* 0x0193 */ SCHEDULE_CMD_RETURN_TIME(10, 57, 11, 11, 47),
/* 0x0199 */ SCHEDULE_CMD_RETURN_TIME( 9, 35,  9, 49, 41),
/* 0x019F */ SCHEDULE_CMD_RETURN_TIME( 9, 31,  9, 35,  3),
/* 0x01A5 */ SCHEDULE_CMD_RETURN_TIME( 9, 17,  9, 31, 40),
/* 0x01AB */ SCHEDULE_CMD_RETURN_TIME( 9,  3,  9, 17, 39),
/* 0x01B1 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_BACKTOWN, 0x01DA - 0x01B5),
/* 0x01B5 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 9, 49, 10,  3, 0x01D4 - 0x01BB),
/* 0x01BB */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(10,  3, 10,  7, 0x01CE - 0x01C1),
/* 0x01C1 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(10,  7, 10, 21, 0x01C8 - 0x01C7),
/* 0x01C7 */ SCHEDULE_CMD_END(),
/* 0x01C8 */ SCHEDULE_CMD_RETURN_TIME(10,  7, 10, 21, 43),
/* 0x01CE */ SCHEDULE_CMD_RETURN_TIME(10,  3, 10,  7,  4),
/* 0x01D4 */ SCHEDULE_CMD_RETURN_TIME( 9, 49, 10,  3, 42),
/* 0x01DA */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_TOWN, 0x023F - 0x01DE),
/* 0x01DE */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(10, 21, 10, 35, 0x0239 - 0x01E4),
/* 0x01E4 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(10, 35, 10, 39, 0x0233 - 0x01EA),
/* 0x01EA */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(10, 39, 10, 53, 0x022D - 0x01F0),
/* 0x01F0 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(10, 53, 10, 57, 0x0227 - 0x01F6),
/* 0x01F6 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(10, 57, 11, 11, 0x0221 - 0x01FC),
/* 0x01FC */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(11, 11, 11, 25, 0x021B - 0x0202),
/* 0x0202 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(11, 25, 11, 29, 0x0215 - 0x0208),
/* 0x0208 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(11, 29, 11, 43, 0x020F - 0x020E),
/* 0x020E */ SCHEDULE_CMD_END(),
/* 0x020F */ SCHEDULE_CMD_RETURN_TIME(11, 29, 11, 43, 51),
/* 0x0215 */ SCHEDULE_CMD_RETURN_TIME(11, 25, 11, 29,  7),
/* 0x021B */ SCHEDULE_CMD_RETURN_TIME(11, 11, 11, 25, 49),
/* 0x0221 */ SCHEDULE_CMD_RETURN_TIME(10, 57, 11, 11, 46),
/* 0x0227 */ SCHEDULE_CMD_RETURN_TIME(10, 53, 10, 57,  6),
/* 0x022D */ SCHEDULE_CMD_RETURN_TIME(10, 39, 10, 53, 45),
/* 0x0233 */ SCHEDULE_CMD_RETURN_TIME(10, 35, 10, 39,  5),
/* 0x0239 */ SCHEDULE_CMD_RETURN_TIME(10, 21, 10, 35, 44),
/* 0x023F */ SCHEDULE_CMD_END(),
/* 0x0240 */ SCHEDULE_CMD_DAY_CHECK_L(2, 0x0414 - 0x0245),
/* 0x0245 */ SCHEDULE_CMD_FLAG_CHECK_L(0x1C, 0x08, 0x02EF - 0x024A),
/* 0x024A */ SCHEDULE_CMD_TIME_RANGE_CHECK_L( 9,  0, 12,  0, 0x0117 - 0x0251),
/* 0x0251 */ SCHEDULE_CMD_TIME_RANGE_CHECK_L(12,  0, 13,  1, 0x02E4 - 0x0258),
/* 0x0258 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  1, 15,  0, 0x02DC - 0x025E),
/* 0x025E */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0,  0,  2,  0, 0x0265 - 0x0264),
/* 0x0264 */ SCHEDULE_CMD_END(),
/* 0x0265 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_ICHIBA, 0x029A - 0x0269),
/* 0x0269 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0,  0,  0,  4, 0x0294 - 0x026F),
/* 0x026F */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0,  4,  0, 31, 0x028E - 0x0275),
/* 0x0275 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 1, 29,  1, 56, 0x0288 - 0x027B),
/* 0x027B */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 1, 56,  2,  0, 0x0282 - 0x0281),
/* 0x0281 */ SCHEDULE_CMD_END(),
/* 0x0282 */ SCHEDULE_CMD_RETURN_TIME( 1, 56,  2,  0,  2),
/* 0x0288 */ SCHEDULE_CMD_RETURN_TIME( 1, 29,  1, 56, 79),
/* 0x028E */ SCHEDULE_CMD_RETURN_TIME( 0,  4,  0, 31, 74),
/* 0x0294 */ SCHEDULE_CMD_RETURN_TIME( 0,  0,  0,  4,  1),
/* 0x029A */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_CLOCKTOWER, 0x02DB - 0x029E),
/* 0x029E */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0,  4,  0, 31, 0x02D5 - 0x02A4),
/* 0x02A4 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 31,  0, 58, 0x02CF - 0x02AA),
/* 0x02AA */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 58,  1,  2, 0x02C9 - 0x02B0),
/* 0x02B0 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 1,  2,  1, 29, 0x02C3 - 0x02B6),
/* 0x02B6 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 1, 29,  1, 56, 0x02BD - 0x02BC),
/* 0x02BC */ SCHEDULE_CMD_END(),
/* 0x02BD */ SCHEDULE_CMD_RETURN_TIME( 1, 29,  1, 56, 78),
/* 0x02C3 */ SCHEDULE_CMD_RETURN_TIME( 1,  2,  1, 29, 77),
/* 0x02C9 */ SCHEDULE_CMD_RETURN_TIME( 0, 58,  1,  2, 18),
/* 0x02CF */ SCHEDULE_CMD_RETURN_TIME( 0, 31,  0, 58, 76),
/* 0x02D5 */ SCHEDULE_CMD_RETURN_TIME( 0,  4,  0, 31, 75),
/* 0x02DB */ SCHEDULE_CMD_END(),
/* 0x02DC */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x02E3 - 0x02E0),
/* 0x02E0 */ SCHEDULE_CMD_RETURN_L(14),
/* 0x02E3 */ SCHEDULE_CMD_END(),
/* 0x02E4 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x02EE - 0x02E8),
/* 0x02E8 */ SCHEDULE_CMD_RETURN_TIME(12,  0, 13,  1, 20),
/* 0x02EE */ SCHEDULE_CMD_END(),
/* 0x02EF */ SCHEDULE_CMD_TIME_RANGE_CHECK_L( 9,  0, 12,  0, 0x0117 - 0x02F6),
/* 0x02F6 */ SCHEDULE_CMD_TIME_RANGE_CHECK_L(12,  0, 13,  1, 0x0409 - 0x02FD),
/* 0x02FD */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  1, 17,  0, 0x0315 - 0x0303),
/* 0x0303 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(17,  0,  0,  5, 0x030A - 0x0309),
/* 0x0309 */ SCHEDULE_CMD_END(),
/* 0x030A */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x0314 - 0x030E),
/* 0x030E */ SCHEDULE_CMD_RETURN_TIME(17,  0,  0,  5,  8),
/* 0x0314 */ SCHEDULE_CMD_END(),
/* 0x0315 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_ICHIBA, 0x034A - 0x0319),
/* 0x0319 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  1, 13,  4, 0x0344 - 0x031F),
/* 0x031F */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  4, 13, 15, 0x033E - 0x0325),
/* 0x0325 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(16, 35, 16, 57, 0x0338 - 0x032B),
/* 0x032B */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(16, 57, 17,  0, 0x0332 - 0x0331),
/* 0x0331 */ SCHEDULE_CMD_END(),
/* 0x0332 */ SCHEDULE_CMD_RETURN_TIME(16, 57, 17,  0,  2),
/* 0x0338 */ SCHEDULE_CMD_RETURN_TIME(16, 35, 16, 57, 73),
/* 0x033E */ SCHEDULE_CMD_RETURN_TIME(13,  4, 13, 15, 63),
/* 0x0344 */ SCHEDULE_CMD_RETURN_TIME(13,  1, 13,  4,  1),
/* 0x034A */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_CLOCKTOWER, 0x037F - 0x034E),
/* 0x034E */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  4, 13, 15, 0x0379 - 0x0354),
/* 0x0354 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 15, 13, 30, 0x0373 - 0x035A),
/* 0x035A */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 52, 14, 45, 0x036D - 0x0360),
/* 0x0360 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(16, 15, 16, 35, 0x0367 - 0x0366),
/* 0x0366 */ SCHEDULE_CMD_END(),
/* 0x0367 */ SCHEDULE_CMD_RETURN_TIME(16, 15, 16, 35, 72),
/* 0x036D */ SCHEDULE_CMD_RETURN_TIME(13, 52, 14, 45, 67),
/* 0x0373 */ SCHEDULE_CMD_RETURN_TIME(13, 15, 13, 30, 65),
/* 0x0379 */ SCHEDULE_CMD_RETURN_TIME(13,  4, 13, 15, 64),
/* 0x037F */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_TOWN, 0x039C - 0x0383),
/* 0x0383 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 30, 13, 52, 0x0396 - 0x0389),
/* 0x0389 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 52, 14, 50, 0x0390 - 0x038F),
/* 0x038F */ SCHEDULE_CMD_END(),
/* 0x0390 */ SCHEDULE_CMD_RETURN_TIME(13, 52, 14, 50, 68),
/* 0x0396 */ SCHEDULE_CMD_RETURN_TIME(13, 30, 13, 52, 66),
/* 0x039C */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_ALLEY, 0x0408 - 0x03A0),
/* 0x03A0 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 45, 15,  5, 0x0402 - 0x03A6),
/* 0x03A6 */ SCHEDULE_CMD_DAY_CHECK_S(2, 0x03DB - 0x03AA),
/* 0x03AA */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(15,  5, 15, 20, 0x03D5 - 0x03B0),
/* 0x03B0 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(15, 20, 15, 25, 0x03CF - 0x03B6),
/* 0x03B6 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(15, 25, 15, 40, 0x03C9 - 0x03BC),
/* 0x03BC */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(15, 40, 16, 15, 0x03C3 - 0x03C2),
/* 0x03C2 */ SCHEDULE_CMD_END(),
/* 0x03C3 */ SCHEDULE_CMD_RETURN_TIME(15, 40, 16, 15, 81),
/* 0x03C9 */ SCHEDULE_CMD_RETURN_TIME(15, 25, 15, 40, 17),
/* 0x03CF */ SCHEDULE_CMD_RETURN_TIME(15, 20, 15, 25, 80),
/* 0x03D5 */ SCHEDULE_CMD_RETURN_TIME(15,  5, 15, 20, 23),
/* 0x03DB */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(15,  5, 15, 20, 0x03FC - 0x03E1),
/* 0x03E1 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(15, 20, 15, 50, 0x03F6 - 0x03E7),
/* 0x03E7 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(15, 50, 16, 15, 0x03F0 - 0x03ED),
/* 0x03ED */ SCHEDULE_CMD_RETURN_L(0),
/* 0x03F0 */ SCHEDULE_CMD_RETURN_TIME(15, 50, 16, 15, 71),
/* 0x03F6 */ SCHEDULE_CMD_RETURN_TIME(15, 20, 15, 50, 25),
/* 0x03FC */ SCHEDULE_CMD_RETURN_TIME(15,  5, 15, 20, 23),
/* 0x0402 */ SCHEDULE_CMD_RETURN_TIME(14, 45, 15,  5, 70),
/* 0x0408 */ SCHEDULE_CMD_END(),
/* 0x0409 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x0413 - 0x040D),
/* 0x040D */ SCHEDULE_CMD_RETURN_TIME(12,  0, 13,  1, 21),
/* 0x0413 */ SCHEDULE_CMD_END(),
/* 0x0414 */ SCHEDULE_CMD_DAY_CHECK_L(3, 0x0588 - 0x0419),
/* 0x0419 */ SCHEDULE_CMD_FLAG_CHECK_L(0x1C, 0x08, 0x055D - 0x041E),
/* 0x041E */ SCHEDULE_CMD_FLAG_CHECK_L(0x1C, 0x10, 0x052F - 0x0423),
/* 0x0423 */ SCHEDULE_CMD_TIME_RANGE_CHECK_L( 9,  0, 12,  0, 0x0117 - 0x042A),
/* 0x042A */ SCHEDULE_CMD_TIME_RANGE_CHECK_L(12,  0, 13,  1, 0x0527 - 0x0431),
/* 0x0431 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  1, 15,  0, 0x0446 - 0x0437),
/* 0x0437 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(18,  0,  6,  0, 0x043E - 0x043D),
/* 0x043D */ SCHEDULE_CMD_END(),
/* 0x043E */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x0445 - 0x0442),
/* 0x0442 */ SCHEDULE_CMD_RETURN_L(24),
/* 0x0445 */ SCHEDULE_CMD_END(),
/* 0x0446 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_ICHIBA, 0x047B - 0x044A),
/* 0x044A */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  0, 13,  1, 0x0475 - 0x0450),
/* 0x0450 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  5, 13, 15, 0x046F - 0x0456),
/* 0x0456 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 45, 14, 55, 0x0469 - 0x045C),
/* 0x045C */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 55, 15,  0, 0x0463 - 0x0462),
/* 0x0462 */ SCHEDULE_CMD_END(),
/* 0x0463 */ SCHEDULE_CMD_RETURN_TIME(14, 55, 15,  0,  2),
/* 0x0469 */ SCHEDULE_CMD_RETURN_TIME(14, 45, 14, 55, 52),
/* 0x046F */ SCHEDULE_CMD_RETURN_TIME(13,  5, 13, 15, 38),
/* 0x0475 */ SCHEDULE_CMD_RETURN_TIME(13,  0, 13,  1,  1),
/* 0x047B */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_CLOCKTOWER, 0x04C8 - 0x047F),
/* 0x047F */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13,  5, 13, 15, 0x04C2 - 0x0485),
/* 0x0485 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 15, 13, 25, 0x04BC - 0x048B),
/* 0x048B */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 25, 13, 35, 0x04B6 - 0x0491),
/* 0x0491 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 15, 14, 25, 0x04B0 - 0x0497),
/* 0x0497 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 25, 14, 35, 0x04AA - 0x049D),
/* 0x049D */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 35, 14, 45, 0x04A4 - 0x04A3),
/* 0x04A3 */ SCHEDULE_CMD_END(),
/* 0x04A4 */ SCHEDULE_CMD_RETURN_TIME(14, 35, 14, 45, 50),
/* 0x04AA */ SCHEDULE_CMD_RETURN_TIME(14, 25, 14, 35, 48),
/* 0x04B0 */ SCHEDULE_CMD_RETURN_TIME(14, 15, 14, 25, 47),
/* 0x04B6 */ SCHEDULE_CMD_RETURN_TIME(13, 25, 13, 35, 41),
/* 0x04BC */ SCHEDULE_CMD_RETURN_TIME(13, 15, 13, 25, 40),
/* 0x04C2 */ SCHEDULE_CMD_RETURN_TIME(13,  5, 13, 15, 39),
/* 0x04C8 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_BACKTOWN, 0x04E5 - 0x04CC),
/* 0x04CC */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 35, 13, 45, 0x04DF - 0x04D2),
/* 0x04D2 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 45, 13, 55, 0x04D9 - 0x04D8),
/* 0x04D8 */ SCHEDULE_CMD_END(),
/* 0x04D9 */ SCHEDULE_CMD_RETURN_TIME(13, 45, 13, 55, 43),
/* 0x04DF */ SCHEDULE_CMD_RETURN_TIME(13, 35, 13, 45, 42),
/* 0x04E5 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_TOWN, 0x0526 - 0x04E9),
/* 0x04E9 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(13, 55, 14,  5, 0x0520 - 0x04EF),
/* 0x04EF */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14,  5, 14, 15, 0x051A - 0x04F5),
/* 0x04F5 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 15, 14, 25, 0x0514 - 0x04FB),
/* 0x04FB */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 25, 14, 35, 0x050E - 0x0501),
/* 0x0501 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(14, 35, 14, 45, 0x0508 - 0x0507),
/* 0x0507 */ SCHEDULE_CMD_END(),
/* 0x0508 */ SCHEDULE_CMD_RETURN_TIME(14, 35, 14, 45, 51),
/* 0x050E */ SCHEDULE_CMD_RETURN_TIME(14, 25, 14, 35, 49),
/* 0x0514 */ SCHEDULE_CMD_RETURN_TIME(14, 15, 14, 25, 46),
/* 0x051A */ SCHEDULE_CMD_RETURN_TIME(14,  5, 14, 15, 45),
/* 0x0520 */ SCHEDULE_CMD_RETURN_TIME(13, 55, 14,  5, 44),
/* 0x0526 */ SCHEDULE_CMD_END(),
/* 0x0527 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x052E - 0x052B),
/* 0x052B */ SCHEDULE_CMD_RETURN_L(22),
/* 0x052E */ SCHEDULE_CMD_END(),
/* 0x052F */ SCHEDULE_CMD_TIME_RANGE_CHECK_L( 9,  0, 12,  0, 0x0117 - 0x0536),
/* 0x0536 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(12,  0, 13,  1, 0x0552 - 0x053C),
/* 0x053C */ SCHEDULE_CMD_TIME_RANGE_CHECK_L(13,  1, 17,  0, 0x0315 - 0x0543),
/* 0x0543 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(18,  0,  6,  0, 0x054A - 0x0549),
/* 0x0549 */ SCHEDULE_CMD_END(),
/* 0x054A */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x0551 - 0x054E),
/* 0x054E */ SCHEDULE_CMD_RETURN_L(24),
/* 0x0551 */ SCHEDULE_CMD_END(),
/* 0x0552 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x055C - 0x0556),
/* 0x0556 */ SCHEDULE_CMD_RETURN_TIME(12,  0, 13,  1, 21),
/* 0x055C */ SCHEDULE_CMD_END(),
/* 0x055D */ SCHEDULE_CMD_TIME_RANGE_CHECK_L( 9,  0, 12,  0, 0x0117 - 0x0564),
/* 0x0564 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(12,  0, 13,  1, 0x0580 - 0x056A),
/* 0x056A */ SCHEDULE_CMD_TIME_RANGE_CHECK_L(13,  1, 15,  0, 0x0446 - 0x0571),
/* 0x0571 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(18,  0,  6,  0, 0x0578 - 0x0577),
/* 0x0577 */ SCHEDULE_CMD_END(),
/* 0x0578 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x057F - 0x057C),
/* 0x057C */ SCHEDULE_CMD_RETURN_L(24),
/* 0x057F */ SCHEDULE_CMD_END(),
/* 0x0580 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x0587 - 0x0584),
/* 0x0584 */ SCHEDULE_CMD_RETURN_L(20),
/* 0x0587 */ SCHEDULE_CMD_END(),
/* 0x0588 */ SCHEDULE_CMD_END(),
};

static u8 D_80AFB30C[] = {
/* 0x0000 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_POSTHOUSE, 0x0032 - 0x0004),
/* 0x0004 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0,  0,  0, 10, 0x002C - 0x000A),
/* 0x000A */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 10,  0, 13, 0x0029 - 0x0010),
/* 0x0010 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 13,  0, 23, 0x0023 - 0x0016),
/* 0x0016 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 23,  0, 26, 0x001D - 0x001C),
/* 0x001C */ SCHEDULE_CMD_END(),
/* 0x001D */ SCHEDULE_CMD_RETURN_TIME( 0, 23,  0, 26, 32),
/* 0x0023 */ SCHEDULE_CMD_RETURN_TIME( 0, 13,  0, 23, 83),
/* 0x0029 */ SCHEDULE_CMD_RETURN_L(27),
/* 0x002C */ SCHEDULE_CMD_RETURN_TIME( 0,  0,  0, 10, 82),
/* 0x0032 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_ICHIBA, 0x004F - 0x0036),
/* 0x0036 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 23,  0, 26, 0x0049 - 0x003C),
/* 0x003C */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 26,  0, 36, 0x0043 - 0x0042),
/* 0x0042 */ SCHEDULE_CMD_END(),
/* 0x0043 */ SCHEDULE_CMD_RETURN_TIME( 0, 26,  0, 36, 84),
/* 0x0049 */ SCHEDULE_CMD_RETURN_TIME( 0, 23,  0, 26, 33),
/* 0x004F */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_CLOCKTOWER, 0x006C - 0x0053),
/* 0x0053 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 26,  0, 36, 0x0066 - 0x0059),
/* 0x0059 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 36,  0, 46, 0x0060 - 0x005F),
/* 0x005F */ SCHEDULE_CMD_END(),
/* 0x0060 */ SCHEDULE_CMD_RETURN_TIME( 0, 36,  0, 46, 86),
/* 0x0066 */ SCHEDULE_CMD_RETURN_TIME( 0, 26,  0, 36, 85),
/* 0x006C */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_TOWN, 0x0089 - 0x0070),
/* 0x0070 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 46,  0, 56, 0x0083 - 0x0076),
/* 0x0076 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 56,  0, 59, 0x007D - 0x007C),
/* 0x007C */ SCHEDULE_CMD_END(),
/* 0x007D */ SCHEDULE_CMD_RETURN_TIME( 0, 56,  0, 59, 34),
/* 0x0083 */ SCHEDULE_CMD_RETURN_TIME( 0, 46,  0, 56, 87),
/* 0x0089 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_MILK_BAR, 0x00B2 - 0x008D),
/* 0x008D */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 56,  0, 59, 0x00AC - 0x0093),
/* 0x0093 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 59,  1,  9, 0x00A6 - 0x0099),
/* 0x0099 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 1,  9,  1, 40, 0x00A0 - 0x009F),
/* 0x009F */ SCHEDULE_CMD_END(),
/* 0x00A0 */ SCHEDULE_CMD_RETURN_TIME( 1,  9,  1, 40, 28),
/* 0x00A6 */ SCHEDULE_CMD_RETURN_TIME( 0, 59,  1,  9, 88),
/* 0x00AC */ SCHEDULE_CMD_RETURN_TIME( 0, 56,  0, 59, 36),
/* 0x00B2 */ SCHEDULE_CMD_END(),
};

static u8 D_80AFB3C0[] = {
/* 0x0000 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_TOWN, 0x001D - 0x0004),
/* 0x0004 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 10,  0, 13, 0x0017 - 0x000A),
/* 0x000A */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 13,  0, 23, 0x0011 - 0x0010),
/* 0x0010 */ SCHEDULE_CMD_END(),
/* 0x0011 */ SCHEDULE_CMD_RETURN_TIME( 0, 13,  0, 23, 90),
/* 0x0017 */ SCHEDULE_CMD_RETURN_TIME( 0, 10,  0, 13, 35),
/* 0x001D */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_MILK_BAR, 0x003A - 0x0021),
/* 0x0021 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0,  0,  0, 10, 0x0034 - 0x0027),
/* 0x0027 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0, 10,  0, 13, 0x002E - 0x002D),
/* 0x002D */ SCHEDULE_CMD_END(),
/* 0x002E */ SCHEDULE_CMD_RETURN_TIME( 0, 10,  0, 13, 37),
/* 0x0034 */ SCHEDULE_CMD_RETURN_TIME( 0,  0,  0, 10, 89),
/* 0x003A */ SCHEDULE_CMD_END(),
};

static u8 D_80AFB3FC[] = {
/* 0x0000 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_TOWN, 0x001D - 0x0004),
/* 0x0004 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S(18,  0,  6,  0, 0x0017 - 0x000A),
/* 0x000A */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 5,  0,  5, 10, 0x0011 - 0x0010),
/* 0x0010 */ SCHEDULE_CMD_END(),
/* 0x0011 */ SCHEDULE_CMD_RETURN_TIME( 5,  0,  5, 10, 91),
/* 0x0017 */ SCHEDULE_CMD_RETURN_TIME(18,  0,  6,  0, 29),
/* 0x001D */ SCHEDULE_CMD_END(),
};

static u8 D_80AFB41C[] = {
/* 0x0000 */ SCHEDULE_CMD_SCENE_CHECK_S(SCENE_TOWN, 0X0011 - 0X0004),
/* 0x0004 */ SCHEDULE_CMD_TIME_RANGE_CHECK_S( 0,  0,  0, 10, 0X000B - 0X000A),
/* 0x000A */ SCHEDULE_CMD_END(),
/* 0x000B */ SCHEDULE_CMD_RETURN_TIME( 0,  0,  0, 10, 91),
/* 0x0011 */ SCHEDULE_CMD_END(),
};

static s32 D_80AFB430[] = {
    -1, 0, 4, 1,  0,  0, 1, 4,  -1, -1, 15, 5, 0, 3, -1, -1, 1, 2, 11, 3, -1, -1, -1, 0, 0, 0, 0, 0, 1,  12, -1,
    -1, 2, 0, 10, 11, 0, 3, 1,  0,  1,  2,  0, 1, 0, 1,  2,  3, 4, 3,  5, 14, 3,  1,  0, 6, 4, 1, 2, 6,  7,  8,
    2,  1, 0, 6,  7,  9, 8, -1, 0,  1,  10, 3, 1, 0, 11, 12, 8, 2, 2,  3, 0,  1,  1,  0, 6, 9, 1, 2, 12, 13,
};

// Game scripts
static UNK_TYPE D_80AFB5A0[] = {
    0x00560800, 0x45090000, 0x170E28BA, 0x0C090000, 0x180E28BB, 0x0C090000, 0x170E28BC, 0x0C090000, 0x180E28BD,
    0x0C090000, 0x170E28BE, 0x0C090000, 0x180E28BF, 0x0C090000, 0x170E28C0, 0x2D00012D, 0x000B0C09, 0x00001156,
    0x08100900, 0x00170E29, 0x5C0C0900, 0x00180E29, 0x5D0C0900, 0x00170E29, 0x5E2D0001, 0x2D000B0C, 0x09000010,
};

static UNK_TYPE D_80AFB60C[] = {
    0x0E27742D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB614[] = {
    0x0E27752D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB61C[] = {
    0x0E27772D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB624[] = {
    0x0E27782D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB62C[] = {
    0x0E27792D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB634[] = {
    0x0E27812D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB63C[] = {
    0x0E277A2D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB644[] = {
    0x0E27822D,
    0x000B0C11,
    0x58021000,
};

static UNK_TYPE D_80AFB650[] = {
    0x0E27832D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB658[] = {
    0x25002E00, 0x1A005280, 0x000C0E27, 0x7C2D000B, 0x0C115280, 0x12100E27, 0x7D2D000B, 0x0C12100E, 0x277C0C0E,
    0x00FF1E00, 0x33000000, 0x1800282C, 0xFFFF0900, 0x000E277E, 0x2D000B0C, 0x11528011, 0x56012A00, 0x2E12102C,
    0x277D0C2F, 0x00002D00, 0x0B0C1152, 0x8012100E, 0x277D2D00, 0x0B0C1152, 0x80121000,
};

static UNK_TYPE D_80AFB6BC[] = {
    0x0900000E, 0x27A50C09, 0x0000170E, 0x27A60C09, 0x0000180E, 0x27A70C09, 0x0000170E,
    0x27A80C09, 0x0000180E, 0x27A90C09, 0x0000170E, 0x27AA0C09, 0x0000180E, 0x27AB0C09,
    0x0000170E, 0x27AC0C09, 0x0000180E, 0x27AD2D00, 0x0B2D0008, 0x0C115908, 0x09000010,
};

static UNK_TYPE D_80AFB710[] = {
    0x25003E00, 0x230E2780, 0x0C0F27AE, 0x0C120600, 0x84000013, 0x0084115A, 0x042F0000,
    0x2E2D000B, 0x2D00310C, 0x115A0110, 0x0E27802D, 0x000B0C11, 0x5A011210,
};

static UNK_TYPE D_80AFB744[] = {
    0x0E23692D,
    0x000B0C10,
};

static UNK_TYPE D_80AFB74C[] = {
    0x2CFFFF09, 0x00000E27, 0x7E2D000B, 0x0C115280, 0x1156012A, 0x002E1210,
};

static UNK_TYPE D_80AFB764[] = {
    0x2C277D2D,
    0x000B0C11,
    0x52801210,
};

const ActorInit En_Pm_InitVars = {
    ACTOR_EN_PM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MM,
    sizeof(EnPm),
    (ActorFunc)EnPm_Init,
    (ActorFunc)EnPm_Destroy,
    (ActorFunc)EnPm_Update,
    (ActorFunc)EnPm_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 14, 62, 0, { 0, 0, 0 } },
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 26 }, 100 },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static ActorAnimationEntryS sAnimations[] = {
    { &object_mm_Anim_002238, 1.0f, 0, -1, 0, 0 },  { &object_mm_Anim_002238, 1.0f, 0, -1, 0, -4 },
    { &object_mm_Anim_00A4E0, 1.0f, 0, -1, 2, 0 },  { &object_mm_Anim_00B09C, 1.0f, 0, -1, 0, 0 },
    { &object_mm_Anim_00B09C, 1.0f, 0, -1, 0, -4 }, { &object_mm_Anim_00BA78, 1.0f, 0, -1, 2, 0 },
    { &object_mm_Anim_00C32C, 1.0f, 0, -1, 0, -4 }, { &object_mm_Anim_0099B4, 1.0f, 0, -1, 0, 0 },
    { &object_mm_Anim_000FC4, 1.0f, 0, -1, 0, 0 },  { &object_mm_Anim_00A8D8, 1.0f, 0, -1, 0, 0 },
    { &object_mm_Anim_00099C, 1.0f, 0, -1, 0, 0 },  { &object_mm_Anim_001F84, 1.0f, 0, -1, 2, 0 },
    { &object_mm_Anim_000468, 1.0f, 0, -1, 0, 0 },  { &object_mm_Anim_00C640, 1.0f, 0, -1, 0, 0 },
};

s32 func_80AF7B40(void) {
    if (gSaveContext.weekEventReg[90] & 1) {
        return 4;
    }

    if (gSaveContext.weekEventReg[89] & 0x40) {
        return 3;
    }

    if (gSaveContext.weekEventReg[89] & 8) {
        return 2;
    }

    if (gSaveContext.weekEventReg[86] & 1) {
        return 1;
    }

    return 0;
}

s32 func_80AF7BAC(EnPm* this) {
    switch (this->unk_38C) {
        case 0:
            if (gSaveContext.weekEventReg[86] & 1) {
                D_801F4E78 = gSaveContext.time;
                this->unk_38C++;
            }
            break;

        case 1:
            if (gSaveContext.weekEventReg[89] & 8) {
                D_801F4E78 = gSaveContext.time;
                this->unk_38C++;
            }
            break;

        case 2:
            if (gSaveContext.weekEventReg[89] & 0x40) {
                D_801F4E78 = 0;
                this->unk_38C++;
            }
            break;

        case 3:
            if (gSaveContext.weekEventReg[90] & 1) {
                D_801F4E78 = gSaveContext.time;
                this->unk_38C++;
            }
            break;
    }

    return true;
}

Actor* func_80AF7CB0(EnPm* this, GlobalContext* globalCtx, u8 actorCat, s16 actorId) {
    Actor* phi_s0 = NULL;
    Actor* actor;

    while (true) {
        actor = SubS_FindActor(globalCtx, phi_s0, actorCat, actorId);
        phi_s0 = actor;

        if (actor == NULL) {
            break;
        }

        if (((EnPm*)phi_s0 != this) && (actor->update != NULL)) {
            break;
        }

        actor = actor->next;
        if (actor == NULL) {
            phi_s0 = NULL;
            break;
        }

        phi_s0 = actor;
    }

    return phi_s0;
}

EnDoor* func_80AF7D60(GlobalContext* globalCtx, s32 arg1) {
    s32 phi_a1;

    switch (arg1) {
        case 1:
        case 2:
        case 32:
        case 33:
            phi_a1 = 1;
            break;

        case 34:
        case 35:
        case 36:
        case 37:
            phi_a1 = 10;
            break;

        case 10:
        case 11:
        case 12:
        case 13:
            phi_a1 = 11;
            break;

        default:
            return NULL;
    }

    return SubS_FindDoor(globalCtx, phi_a1);
}

Actor* func_80AF7DC4(EnPm* this, GlobalContext* globalCtx, s32 arg2) {
    Actor* phi_s0 = NULL;
    Actor* actor;

    while (true) {
        actor = SubS_FindActor(globalCtx, phi_s0, ACTORCAT_PROP, ACTOR_EN_PST);
        phi_s0 = actor;

        if (actor == NULL) {
            break;
        }

        if (((EnPm*)actor != this) && (actor->update != NULL) && (actor->params == (s16)arg2)) {
            break;
        }

        actor = actor->next;
        if (actor == NULL) {
            phi_s0 = NULL;
            break;
        }

        phi_s0 = actor;
    }

    return phi_s0;
}

void func_80AF7E6C(EnPm* this) {
    this->skelAnime.playSpeed = this->unk_35C;
    SkelAnime_Update(&this->skelAnime);
}

s32 func_80AF7E98(EnPm* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 ret = false;

    switch (arg1) {
        case 0:
        case 1:
            if ((this->unk_384 != 0) && (this->unk_384 != 1)) {
                phi_v1 = true;
            }
            break;

        case 3:
        case 4:
            if ((this->unk_384 != 3) && (this->unk_384 != 4)) {
                phi_v1 = true;
            }
            break;

        default:
            if (arg1 != this->unk_384) {
                phi_v1 = true;
            }
            break;
    }

    if (phi_v1) {
        this->unk_384 = arg1;
        ret = func_8013BC6C(&this->skelAnime, sAnimations, arg1);
        this->unk_35C = this->skelAnime.playSpeed;
    }

    return ret;
}

void func_80AF7F68(EnPm* this, GlobalContext* globalCtx) {
    f32 temp;
    s32 pad;

    switch (this->unk_258) {
        case 9:
        case 20:
        case 21:
        case 22:
        case 24:
            temp = this->colliderSphere.dim.modelSphere.radius * this->colliderSphere.dim.scale;
            this->colliderSphere.dim.worldSphere.radius = temp;
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderSphere.base);
            break;

        default:
            Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
            temp = this->actor.focus.pos.y - this->actor.world.pos.y;
            this->colliderCylinder.dim.height = temp;
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
            break;
    }
}

Actor* func_80AF8040(EnPm* this, GlobalContext* globalCtx) {
    Actor* actor;

    switch (this->unk_258) {
        case 16:
            actor = func_80AF7CB0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AN);
            break;

        case 17:
            actor = func_80AF7CB0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_TEST3);
            break;

        case 28:
            actor = func_80AF7CB0(this, globalCtx, ACTORCAT_NPC, ACTOR_EN_AL);
            break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            actor = func_80AF7DC4(this, globalCtx, this->unk_258 - 3);
            break;

        case 19:
            actor = func_80AF7DC4(this, globalCtx, 4);
            break;

        case 18:
            actor = func_80AF7DC4(this, globalCtx, 4);
            break;

        default:
            actor = &GET_PLAYER(globalCtx)->actor;
            break;
    }

    return actor;
}

s32 func_80AF80F4(EnPm* this, s16 arg1) {
    s32 ret = false;

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(arg1);
    } else if (ActorCutscene_GetCanPlayNext(arg1)) {
        ActorCutscene_StartAndSetUnkLinkFields(arg1, &this->actor);
        ret = true;
    } else {
        ActorCutscene_SetIntentToPlay(arg1);
    }
    return ret;
}

s16 func_80AF8170(EnPm* this, s32 arg1) {
    s32 i;
    s16 cs = -1;

    if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
        cs = this->actor.child->cutscene;

        for (i = 0; i < arg1; i++) {
            cs = ActorCutscene_GetAdditionalCutscene(cs);
        }
    }
    return cs;
}

s32 func_80AF81E8(EnPm* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp2A = func_80AF8170(this, 0);
    s32 ret = false;

    switch (this->unk_378) {
        case 0:
            if (!func_80AF80F4(this, sp2A)) {
                break;
            }

        case 2:
        case 4:
        case 6:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                func_800E0308(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), this->actor.child);
            }
            this->unk_378++;
            ret = true;
            break;

        case 1:
        case 3:
        case 5:
            if ((gSaveContext.weekEventReg[86] & 8) && (this->unk_378 == 3)) {
                ActorCutscene_Stop(sp2A);
            } else {
                func_800E0308(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), &this->actor);
            }
            this->unk_378++;
            ret = true;
            break;

        case 7:
            ActorCutscene_Stop(sp2A);
            this->unk_378++;
            ret = true;
            break;
    }
    return ret;
}

s32 func_80AF8348(EnPm* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp2A = func_80AF8170(this, 0);
    s32 ret = false;

    switch (this->unk_378) {
        case 0:
            if (!func_80AF80F4(this, sp2A)) {
                break;
            }

        case 2:
        case 4:
        case 6:
        case 8:
            func_800E0308(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), &this->actor);
            this->unk_378++;
            ret = true;
            break;

        case 1:
        case 3:
        case 5:
        case 7:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                func_800E0308(Play_GetCamera(globalCtx, ActorCutscene_GetCurrentCamera(sp2A)), this->actor.child);
            }
            this->unk_378++;
            ret = true;
            break;

        case 9:
            ActorCutscene_Stop(sp2A);
            this->unk_378++;
            ret = true;
            break;
    }

    return ret;
}

s32 func_80AF8478(EnPm* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 ret = false;

    switch (this->unk_378) {
        case 0:
            func_80AF7E98(this, 2);
            this->unk_356 &= ~0x20;
            this->unk_356 |= 0x200;
            this->unk_378++;
            break;

        case 1:
            if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                func_80AF7E98(this, 4);
                this->unk_356 &= ~0x200;
                this->unk_356 |= 0x20;
                this->unk_378++;
                ret = true;
            }
            break;
    }
    return ret;
}

UNK_TYPE* func_80AF8540(EnPm* this, GlobalContext* globalCtx) {
    switch (this->unk_258) {
        case 28:
            this->unk_37C = func_80AF8348;
            return D_80AFB6BC;

        case 29:
            return D_80AFB710;

        case 16:
            this->unk_37C = func_80AF81E8;
            return D_80AFB5A0;

        case 17:
            return D_80AFB644;

        case 24:
            if (this->unk_356 & 0x2000) {
                this->unk_37C = func_80AF8478;
                return D_80AFB74C;
            } else if (this->unk_356 & 0x4000) {
                return D_80AFB764;
            } else {
                this->unk_37C = func_80AF8478;
                return D_80AFB658;
            }
            break;

        case 25:
            return D_80AFB650;

        default:
            if (Player_GetMask(globalCtx) == PLAYER_MASK_KAFEIS_MASK) {
                return D_80AFB744;
            }

            switch (this->unk_258) {
                case 9:
                    return D_80AFB614;

                case 14:
                    return D_80AFB624;

                case 20:
                    return D_80AFB61C;

                case 21:
                    return D_80AFB634;

                case 22:
                    return D_80AFB63C;

                case 18:
                case 74:
                case 75:
                case 76:
                case 77:
                case 78:
                case 79:
                    return D_80AFB62C;

                default:
                    return D_80AFB60C;
            }
            break;
    }
}

s32 func_80AF86F0(EnPm* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((this->unk_356 & 7) && Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_8013AED4(&this->unk_356, 0, 7);
        this->unk_398 = 0;
        this->unk_378 = 0;
        this->unk_37C = NULL;
        this->actor.child = this->unk_268;
        this->unk_25C = func_80AF8540(this, globalCtx);
        if ((this->unk_258 != 24) && (this->unk_258 != 9) && (this->unk_258 != 20) && (this->unk_258 != 21) &&
            (this->unk_258 != 22)) {
            this->unk_356 |= 0x20;
        }
        this->actionFunc = func_80AFA5FC;
        ret = true;
    }
    return ret;
}

s32 func_80AF87C4(EnPm* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((globalCtx->csCtx.state != 0) && (globalCtx->sceneNum == SCENE_00KEIKOKU) &&
        (gSaveContext.sceneSetupIndex == 9) && (globalCtx->curSpawn == 1)) {
        if (!this->unk_380) {
            func_80AF7E98(this, 0);
            this->unk_258 = 255;
            this->unk_380 = true;
            this->actor.speedXZ = 4.0f;
            this->actor.gravity = -1.0f;
        }
        ret = true;
    } else if (this->unk_380) {
        this->unk_258 = 0;
        this->unk_380 = false;
        this->actor.speedXZ = 0.0f;
    }
    return ret;
}

void func_80AF8890(EnPm* this, Gfx** gfx, s32 arg2) {
    Matrix_StatePush();

    switch (arg2) {
        case 0:
            if (this->unk_356 & 0x800) {
                gSPDisplayList((*gfx)++, object_mm_DL_008348);
            }
            break;

        case 1:
            if (this->unk_356 & 0x1000) {
                gSPDisplayList((*gfx)++, object_mm_DL_0085C8);
            }
            break;

        case 2:
            if (this->unk_356 & 0x1000) {
                gSPDisplayList((*gfx)++, object_mm_DL_0083E0);
            }
            break;
    }

    Matrix_StatePop();
}

void func_80AF898C(EnPm* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    s32 pad2;

    Math_Vec3f_Copy(&sp40, &this->unk_268->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->unk_372, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);
    this->unk_372 = CLAMP(this->unk_372, -0x1FFE, 0x1FFE);
    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);
    if (this->unk_268->id == ACTOR_PLAYER) {
        sp40.y = ((Player*)this->unk_268)->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_268->focus.pos);
    }
    Math_ApproachS(&this->unk_370, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);
    this->unk_370 = CLAMP(this->unk_370, -0x1554, 0x1554);
}

void func_80AF8AC8(EnPm* this) {
    if ((this->unk_356 & 0x20) && (this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
        if (DECR(this->unk_376) == 0) {
            func_80AF898C(this);
            this->unk_356 &= ~0x200;
            this->unk_356 |= 0x80;
            return;
        }
    }

    if (this->unk_356 & 0x80) {
        this->unk_356 &= ~0x80;
        this->unk_370 = 0;
        this->unk_372 = 0;
        this->unk_376 = 20;
    } else if (DECR(this->unk_376) == 0) {
        this->unk_356 |= 0x200;
    }
}

void func_80AF8BA8(s32 arg0) {
    static u16 D_80AFB8D4[] = {
        0x1B02, 0x1B04, 0x1B08, 0x1B10, 0x1B20, 0x0000,
    };
    static u16 D_80AFB8E0[] = {
        0x1B40, 0x1B80, 0x1C01, 0x1C02, 0x1C04, 0x0000,
    };
    s32 temp;

    if (!(gSaveContext.weekEventReg[88] & 2)) {
        if (gSaveContext.weekEventReg[D_80AFB8D4[arg0] >> 8] & (D_80AFB8D4[arg0] & 0xFF)) {
            switch (gSaveContext.day) {
                case 2:
                    gSaveContext.weekEventReg[28] |= 8;
                    break;

                case 3:
                    gSaveContext.weekEventReg[28] |= 0x10;
                    break;
            }
            gSaveContext.weekEventReg[51] |= 2;
            gSaveContext.weekEventReg[90] |= 8;
        }
    }

    temp = gSaveContext.weekEventReg[D_80AFB8E0[arg0] >> 8];
    gSaveContext.weekEventReg[D_80AFB8E0[arg0] >> 8] = temp | (D_80AFB8E0[arg0] & 0xFF);
}

void func_80AF8C68(EnPm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 sp28 = Message_GetState(&globalCtx->msgCtx);
    u16 temp_a0 = globalCtx->msgCtx.unk11F04;

    if ((player->targetActor == &this->actor) && ((temp_a0 < 255) || (temp_a0 > 512)) && (sp28 == 3) &&
        (this->unk_388 == 3)) {
        if ((globalCtx->state.frames % 3) == 0) {
            if (this->unk_360 == 120.0f) {
                this->unk_360 = 0.0f;
            } else {
                this->unk_360 = 120.0f;
            }
        }
    } else {
        this->unk_360 = 0.0f;
    }
    Math_SmoothStepToF(&this->unk_364, this->unk_360, 0.8f, 40.0f, 10.0f);
    Matrix_InsertTranslation(this->unk_364, 0.0f, 0.0f, MTXMODE_APPLY);
    this->unk_388 = sp28;
}

s32 func_80AF8D84(EnPm* this, GlobalContext* globalCtx) {
    switch (this->unk_384) {
        case 10:
            func_80AF7E98(this, 9);
            break;

        case 7:
            func_80AF7E98(this, 0);
            break;
    }
    return true;
}

s32 func_80AF8DD4(EnPm* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 temp = globalCtx->msgCtx.unk11F04;
    s32 pad;

    if (player->stateFlags1 & (0x400 | 0x40)) {
        this->unk_356 |= 0x400;
        if (this->unk_358 != temp) {
            if ((this->unk_384 == 0) || (this->unk_384 == 1)) {
                func_80AF7E98(this, 7);
            }
            if ((temp == 0x277C) || (temp == 0x277D)) {
                func_80AF7E98(this, 10);
            }
        }
        this->unk_358 = temp;
    } else {
        if (this->unk_356 & 0x400) {
            this->unk_358 = 0;
            this->unk_356 &= ~0x400;
            func_80AF8D84(this, globalCtx);
        }
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, globalCtx);
    }

    return 0;
}

s32 func_80AF8ED4(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2, u8 actorCat, s16 actorId) {
    u8 sp4F = this->actor.params & 0xFF;
    Vec3s* sp48;
    Vec3f sp3C;
    Vec3f sp30;
    Actor* sp2C;
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;
    sp2C = func_80AF7CB0(this, globalCtx, actorCat, actorId);
    if (D_80AFB430[arg2->result] >= 0) {
        this->unk_234 = func_8013BB34(globalCtx, sp4F, D_80AFB430[arg2->result]);
    }

    if ((sp2C != NULL) && (sp2C->update != NULL)) {
        if (this->unk_234 != NULL) {
            sp48 = (Vec3s*)Lib_SegmentedToVirtual(this->unk_234->points);
            Math_Vec3s_ToVec3f(&sp3C, &sp48[this->unk_234->count - 2]);
            Math_Vec3s_ToVec3f(&sp30, &sp48[this->unk_234->count - 1]);
            this->actor.shape.shadowDraw = NULL;
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp3C, &sp30);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp30);
            ret = true;
        }
    }

    return ret;
}

s32 func_80AF9008(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    u16 sp56 = SCHEDULE_TIME_NOW;
    u8 sp55 = this->actor.params & 0xFF;
    EnDoor* sp50;
    Vec3s* sp4C;
    Vec3f sp40;
    Vec3f sp34;
    s16 temp;
    s32 ret = false;

    this->unk_234 = NULL;
    sp50 = func_80AF7D60(globalCtx, arg2->result);
    if (D_80AFB430[arg2->result] >= 0) {
        this->unk_234 = func_8013BB34(globalCtx, sp55, D_80AFB430[arg2->result]);
    }

    if ((sp50 != NULL) && (sp50->actor.update != NULL)) {
        if (this->unk_234 != 0) {
            sp4C = (Vec3s*)Lib_SegmentedToVirtual(this->unk_234->points);
            Math_Vec3s_ToVec3f(&sp40, &sp4C[0]);
            Math_Vec3s_ToVec3f(&sp34, &sp4C[1]);
            Math_Vec3f_Copy(&this->unk_26C, &sp40);
            Math_Vec3f_Copy(&this->unk_278, &sp34);
            this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
            Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
            temp = this->actor.world.rot.y - sp50->actor.shape.rot.y;
            if (ABS_ALT(temp) <= 0x4000) {
                this->unk_260 = -0x4B;
            } else {
                this->unk_260 = 0x4B;
            }

            this->unk_36C = arg2->time1 - arg2->time0;
            this->unk_36E = sp56 - arg2->time0;
            this->actor.flags &= ~1;
            if (gSaveContext.weekEventReg[90] & 8) {
                this->unk_356 |= 0x800;
            }
            this->unk_356 |= 0x9000;
            this->unk_356 |= 0x200;
            func_80AF7E98(this, 0);
            this->actor.gravity = 0.0f;
            ret = true;
        }
    }
    return ret;
}

s32 func_80AF91E8(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    u16 sp2E = SCHEDULE_TIME_NOW;
    u16 phi_v1;
    u8 sp2B = this->actor.params & 0xFF;
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;

    if (D_80AFB430[arg2->result] >= 0) {
        this->unk_234 = func_8013BB34(globalCtx, sp2B, D_80AFB430[arg2->result]);
    }

    if ((this->unk_234 != NULL) && (this->unk_234->count < 3)) {
        this->unk_234 = NULL;
    }

    if (this->unk_234 != 0) {
        if ((this->unk_258 < 38) && (this->unk_258 != 0) && (this->unk_374 >= 0)) {
            phi_v1 = sp2E;
        } else {
            phi_v1 = arg2->time0;
        }

        if (arg2->time1 < phi_v1) {
            this->unk_248 = (phi_v1 - arg2->time1) + 0xFFFF;
        } else {
            this->unk_248 = arg2->time1 - phi_v1;
        }

        this->unk_254 = sp2E - phi_v1;
        phi_v1 = this->unk_234->count - 2;
        this->unk_24C = this->unk_248 / phi_v1;
        this->unk_250 = (this->unk_254 / this->unk_24C) + 2;
        this->unk_356 &= ~8;
        this->unk_356 &= ~0x10;
        if (this->unk_258 == 27) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ROOM_CARTAIN);
            Flags_UnsetSwitch(globalCtx, 0);
        }

        switch (arg2->result) {
            case 83:
            case 84:
            case 85:
            case 86:
            case 87:
            case 88:
            case 89:
            case 90:
                this->unk_356 |= 0x9000;
                this->unk_356 |= 0x200;

            case 82:
                func_80AF7E98(this, 0);
                break;

            case 91:
                this->unk_356 |= 0x9000;
                func_80AF7E98(this, 12);
                break;

            default:
                func_8013AED4(&this->unk_356, 3, 7);
                func_80AF7E98(this, 0);
                if (gSaveContext.weekEventReg[90] & 8) {
                    this->unk_356 |= 0x800;
                }
                this->unk_356 |= 0x9000;
                this->unk_356 |= 0x200;
                break;
        }

        this->actor.gravity = -1.0f;
        ret = true;
    }

    return ret;
}

s32 func_80AF94AC(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    u8 sp4F = this->actor.params & 0xFF;
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* sp30;
    s32 pad;
    s32 ret = false;

    this->unk_234 = NULL;
    if (D_80AFB430[arg2->result] >= 0) {
        this->unk_234 = func_8013BB34(globalCtx, sp4F, D_80AFB430[arg2->result]);
    }

    if ((this->unk_234 != 0) && (this->unk_234->count >= 2)) {
        sp30 = (Vec3s*)Lib_SegmentedToVirtual(this->unk_234->points);
        Math_Vec3s_ToVec3f(&sp40, &sp30[0]);
        Math_Vec3s_ToVec3f(&sp34, &sp30[1]);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp40, &sp34);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);
        if (arg2->result == 24) {
            Flags_UnsetSwitch(globalCtx, 0);
            Flags_UnsetSwitch(globalCtx, 1);
            this->unk_394 = 0;
            this->unk_368 = 60.0f;
            func_80AF7E98(this, 9);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF95E8(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    u8 sp4F = this->actor.params & 0xFF;
    Vec3f sp40;
    Vec3f sp34;
    Vec3s* sp30;
    s32 pad;
    s32 ret = false;
    s32 phi_a3 = -1;

    switch (arg2->result) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            phi_a3 = arg2->result - 3;
            break;

        case 19:
            phi_a3 = 4;
            break;
    }

    if ((phi_a3 >= 0) && !func_80AF7DC4(this, globalCtx, phi_a3)) {
        return ret;
    }

    this->unk_234 = NULL;
    phi_a3 = D_80AFB430[arg2->result];
    if (phi_a3 >= 0) {
        this->unk_234 = func_8013BB34(globalCtx, sp4F, phi_a3);
    }

    if ((this->unk_234 != 0) && (this->unk_234->count >= 2)) {
        sp30 = (Vec3s*)Lib_SegmentedToVirtual(this->unk_234->points);
        Math_Vec3s_ToVec3f(&sp40, &sp30[this->unk_234->count - 1]);
        Math_Vec3s_ToVec3f(&sp34, &sp30[this->unk_234->count - 2]);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp34, &sp40);
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
        Math_Vec3f_Copy(&this->actor.world.pos, &sp40);
        Math_Vec3f_Copy(&this->actor.prevPos, &sp40);

        switch (arg2->result) {
            case 27:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ROOM_CARTAIN);
                Flags_SetSwitch(globalCtx, 0);
                this->unk_36C = 20;
                func_8013AED4(&this->unk_356, 3, 7);
                func_80AF7E98(this, 3);
                break;

            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 19:
                this->unk_356 |= 0x9000;
                func_80AF7E98(this, 11);
                break;

            case 18:
                this->unk_356 |= 0x9000;
                this->unk_356 |= 0x800;
                func_80AF7E98(this, 5);
                break;

            case 23:
                if (gSaveContext.weekEventReg[90] & 8) {
                    this->unk_356 |= 0x800;
                }
                gSaveContext.weekEventReg[60] |= 4;

            default:
                if (arg2->result == 0x1D) {
                    this->actor.world.rot.y = BINANG_ROT180(this->actor.world.rot.y);
                }
                func_8013AED4(&this->unk_356, 3, 7);
                this->unk_356 |= 0x9000;
                func_80AF7E98(this, 3);
                break;
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF98A0(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    s32 ret = false;

    if (Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_MM3, 116.0f, 26.0f, -219.0f, 0,
                           -0x3F46, 0, 0) != NULL) {
        Actor_MarkForDeath(&this->actor);
        ret = true;
    }
    return ret;
}

s32 func_80AF992C(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    static Vec3f D_80AFB8EC = { 116.0f, 26.0f, -219.0f };
    static Vec3s D_80AFB8F8 = { 0x0000, 0xC0BA, 0x0000 };
    s32 pad;

    Math_Vec3f_Copy(&this->actor.world.pos, &D_80AFB8EC);
    Math_Vec3s_Copy(&this->actor.world.rot, &D_80AFB8F8);
    Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    func_8013AED4(&this->unk_356, 3, 7);
    this->actor.targetMode = 6;
    this->actor.gravity = -1.0f;
    this->unk_368 = 80.0f;
    if (arg2->result == 14) {
        this->unk_356 &= ~0x200;
        func_80AF7E98(this, 13);
    } else {
        this->unk_356 &= ~0x200;
        func_80AF7E98(this, 8);
    }
    return true;
}

s32 func_80AF9A0C(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    s32 ret = false;

    if (func_80AF8ED4(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_AN)) {
        func_8013AED4(&this->unk_356, 3, 7);
        this->unk_356 |= 0x20;
        this->unk_356 |= 0x9000;
        if (this->unk_258 != 0) {
            this->unk_356 |= 0x800;
            func_80AF7E98(this, 5);
        } else {
            func_80AF7E98(this, 3);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF9AB0(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    s32 ret = false;

    if (func_80AF8ED4(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_TEST3)) {
        func_8013AED4(&this->unk_356, 3, 7);
        this->unk_356 |= 0x20;
        this->unk_356 |= 0x9000;
        if (this->unk_258 != 0) {
            this->unk_356 |= 0x800;
            func_80AF7E98(this, 5);
        } else {
            func_80AF7E98(this, 3);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF9B54(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    s32 ret = false;

    if (func_80AF8ED4(this, globalCtx, arg2, ACTORCAT_NPC, ACTOR_EN_AL)) {
        func_8013AED4(&this->unk_356, 3, 7);
        this->unk_356 |= 0x9000;
        this->unk_356 |= 0x20;
        if (this->unk_258 != 0) {
            this->unk_356 |= 0x800;
            func_80AF7E98(this, 5);
        } else {
            func_80AF7E98(this, 3);
        }
        ret = true;
    }
    return ret;
}

s32 func_80AF9BF8(EnPm* this, GlobalContext* globalCtx, ScheduleResult* arg2) {
    s32 ret;

    this->actor.flags |= 1;
    this->actor.targetMode = 0;
    this->unk_394 = 0;
    this->unk_356 = 0;
    this->unk_368 = 40.0f;

    switch (arg2->result) {
        case 16:
            ret = func_80AF9A0C(this, globalCtx, arg2);
            break;

        case 17:
            ret = func_80AF9AB0(this, globalCtx, arg2);
            break;

        case 28:
            ret = func_80AF9B54(this, globalCtx, arg2);
            break;

        case 24:
            ret = func_80AF94AC(this, globalCtx, arg2);
            break;

        case 29:
            ret = func_80AF95E8(this, globalCtx, arg2);
            break;

        case 1:
        case 2:
        case 10:
        case 11:
        case 12:
        case 13:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
            ret = func_80AF9008(this, globalCtx, arg2);
            break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 18:
        case 19:
        case 23:
        case 25:
        case 27:
            ret = func_80AF95E8(this, globalCtx, arg2);
            break;

        case 8:
            ret = func_80AF98A0(this, globalCtx, arg2);
            break;

        case 9:
        case 14:
        case 20:
        case 21:
        case 22:
            ret = func_80AF992C(this, globalCtx, arg2);
            break;

        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
        case 91:
            ret = func_80AF91E8(this, globalCtx, arg2);
            break;

        default:
            ret = false;
            break;
    }
    return ret;
}

s32 func_80AF9D04(EnPm* this, GlobalContext* globalCtx) {
    EnDoor* sp44 = func_80AF7D60(globalCtx, this->unk_258);
    Vec3f sp38;
    Vec3f* sp28;
    f32 temp;

    if (!func_8013AD6C(globalCtx) && (this->unk_374 != 0)) {
        if ((sp44 != NULL) && (sp44->actor.update != NULL)) {
            if (((f32)this->unk_36E / this->unk_36C) <= 0.9f) {
                sp44->unk_1A7 = this->unk_260;
            } else {
                sp44->unk_1A7 = 0;
            }
        }
        this->unk_36E = CLAMP(this->unk_36E, 0, this->unk_36C);
        temp = Math_Vec3f_DistXZ(&this->unk_26C, &this->unk_278) / this->unk_36C;
        sp38.x = 0.0f;
        sp38.y = 0.0f;
        sp38.z = this->unk_36E * temp;
        Lib_Vec3f_TranslateAndRotateY(&this->unk_26C, this->actor.world.rot.y, &sp38, &this->actor.world.pos);
        this->unk_36E += this->unk_374;
        if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 8.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_POSTMAN_WALK);
        }
    }
    return false;
}

s32 func_80AF9E7C(EnPm* this, GlobalContext* globalCtx) {
    f32 sp7C[265];
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    s32 sp54;
    s32 sp50;

    sp50 = 0;
    sp54 = 0;

    func_8013AF00(sp7C, 3, this->unk_234->count + 3);
    if (!(this->unk_356 & 8)) {
        sp58 = gZeroVec3f;
        func_8013B6B0(this->unk_234, &this->unk_244, &this->unk_254, this->unk_24C, this->unk_248, &this->unk_250, sp7C,
                      &sp58, this->unk_374);
        func_8013B878(globalCtx, this->unk_234, this->unk_250, &sp58);
        this->actor.world.pos.y = sp58.y;
        this->unk_356 |= 8;
    } else {
        sp58 = this->unk_238;
    }

    this->actor.world.pos.x = sp58.x;
    this->actor.world.pos.z = sp58.z;

    if (func_8013AD6C(globalCtx)) {
        sp54 = this->unk_254;
        sp50 = this->unk_250;
        sp58 = this->actor.world.pos;
    }

    this->unk_238 = gZeroVec3f;

    if (func_8013B6B0(this->unk_234, &this->unk_244, &this->unk_254, this->unk_24C, this->unk_248, &this->unk_250, sp7C,
                      &this->unk_238, this->unk_374)) {
        this->unk_356 |= 0x10;
    } else {
        sp70 = this->actor.world.pos;
        sp64 = this->unk_238;
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp70, &sp64);
    }

    if (func_8013AD6C(globalCtx)) {
        this->unk_254 = sp54;
        this->unk_250 = sp50;
        this->unk_238 = sp58;
    } else if ((this->unk_258 != 91) &&
               (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 8.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_POSTMAN_WALK);
    }

    if ((this->unk_356 & 0x10) && (this->unk_258 == 90)) {
        u8 val = gSaveContext.weekEventReg[89] | 0x40;

        gSaveContext.weekEventReg[89] = val;
        if (val == 0) {
            gSaveContext.weekEventReg[89] |= 0x40;
        }
    }

    return false;
}

s32 func_80AFA170(EnPm* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    Vec3f sp28;

    switch (this->unk_258) {
        case 28:
            if (gSaveContext.time >= CLOCK_TIME(1, 39)) {
                gSaveContext.weekEventReg[89] |= 8;
            }

        case 16:
        case 17:
        case 18:
            if ((this->unk_384 == 5) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                func_80AF7E98(this, 6);
                this->unk_36C = 40;
            } else if ((this->unk_384 == 6) && (DECR(this->unk_36C) == 0)) {
                this->unk_356 &= ~0x800;
                func_80AF7E98(this, 4);
            }
            break;

        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 19:
            if ((this->unk_384 == 11) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
                func_80AF7E98(this, 4);
            }

            if ((this->unk_384 == 11) && Animation_OnFrame(&this->skelAnime, 8.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_POSTMACHINE_HIT_OPEN);
            }

            if (this->unk_258 == 19) {
                func_80AF8BA8(4);
            } else {
                func_80AF8BA8(this->unk_258 - 3);
            }
            break;
    }

    if ((this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
        Math_Vec3f_Copy(&sp34, &this->unk_268->world.pos);
        Math_Vec3f_Copy(&sp28, &this->actor.world.pos);
        this->actor.world.rot.y = Math_Vec3f_Yaw(&sp28, &sp34);
    }

    return true;
}

s32 func_80AFA334(EnPm* this, GlobalContext* globalCtx) {
    s16 temp_v0;

    switch (this->unk_258) {
        case 14:
        case 24:
            temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
            if (ABS_ALT(temp_v0) < 0x4000) {
                func_8013AED4(&this->unk_356, 3, 7);
            } else {
                func_8013AED4(&this->unk_356, 0, 7);
            }
            break;

        case 27:
            if (DECR(this->unk_36C) == 0) {
                Flags_SetSwitch(globalCtx, 1);
            }
            break;

        case 9:
        case 20:
        case 21:
        case 22:
            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_NP_SLEEP_OUT);
            }
            break;

        case 29:
            break;
    }

    return false;
}

void func_80AFA438(EnPm* this, GlobalContext* globalCtx) {
    switch (this->unk_258) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 16:
        case 17:
        case 18:
        case 28:
            func_80AFA170(this, globalCtx);
            break;

        case 1:
        case 2:
        case 10:
        case 11:
        case 12:
        case 13:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
            func_80AF9D04(this, globalCtx);
            break;

        case 9:
        case 14:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 27:
        case 29:
            func_80AFA334(this, globalCtx);
            break;

        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
        case 91:
            func_80AF9E7C(this, globalCtx);
            break;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void func_80AFA4D0(EnPm* this, GlobalContext* globalCtx) {
    static u8* D_80AFB900[] = {
        D_80AFAD80, D_80AFB30C, D_80AFB3C0, D_80AFB3FC, D_80AFB41C,
    };
    u16 time = gSaveContext.time;
    u16 sp3C = 0;
    ScheduleResult sp2C;
    u32* unk_14 = &gSaveContext.unk_14;

    this->unk_374 = REG(15) + *unk_14;
    if (this->unk_38C != 0) {
        time = gSaveContext.time - D_801F4E78;
        sp3C = gSaveContext.time;
        gSaveContext.time = time;
    }

    if (!Schedule_RunScript(globalCtx, D_80AFB900[this->unk_38C], &sp2C) ||
        ((this->unk_258 != sp2C.result) && !func_80AF9BF8(this, globalCtx, &sp2C))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~1;
        sp2C.result = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= 1;
    }

    this->unk_258 = sp2C.result;
    this->unk_268 = func_80AF8040(this, globalCtx);
    func_80AFA438(this, globalCtx);
    if (this->unk_38C != 0) {
        gSaveContext.time = sp3C;
    }
}

void func_80AFA5FC(EnPm* this, GlobalContext* globalCtx) {
    s16 yaw;
    Vec3f sp38;
    Vec3f sp2C;

    if (func_8010BF58(&this->actor, globalCtx, this->unk_25C, this->unk_37C, &this->unk_264)) {
        func_8013AED4(&this->unk_356, 3, 7);
        this->unk_356 &= ~0x20;
        this->unk_356 |= 0x200;
        this->actor.child = NULL;
        this->unk_376 = 20;
        this->unk_264 = 0;
        this->actionFunc = func_80AFA4D0;
        return;
    }

    if ((this->unk_258 != 9) && (this->unk_258 != 14) && (this->unk_258 != 16) && (this->unk_258 != 17) &&
        (this->unk_258 != 20) && (this->unk_258 != 21) && (this->unk_258 != 22) && (this->unk_258 != 24) &&
        (this->unk_258 != 25)) {
        if ((this->unk_268 != NULL) && (this->unk_268->update != NULL)) {
            Math_Vec3f_Copy(&sp38, &this->unk_268->world.pos);
            Math_Vec3f_Copy(&sp2C, &this->actor.world.pos);
            yaw = Math_Vec3f_Yaw(&sp2C, &sp38);
            Math_ApproachS(&this->actor.shape.rot.y, yaw, 4, 0x2AA8);
        }
    }
}

void func_80AFA724(EnPm* this, GlobalContext* globalCtx) {
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
    if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 8.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_POSTMAN_WALK);
    }
}

void EnPm_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPm* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_mm_Skel_0096E8, NULL, this->jointTable, this->morphTable,
                       16);
    this->unk_384 = -1;
    func_80AF7E98(this, 0);
    Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    Collider_InitAndSetSphere(globalCtx, &this->colliderSphere, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_38C = func_80AF7B40();
    this->unk_258 = 0;
    this->unk_356 = 0;
    this->actionFunc = func_80AFA4D0;
    this->actionFunc(this, globalCtx);
}

void EnPm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPm* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroySphere(globalCtx, &this->colliderSphere);
}

void EnPm_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnPm* this = THIS;

    if (!func_80AF86F0(this, globalCtx) && func_80AF87C4(this, globalCtx)) {
        func_80AFA724(this, globalCtx);
        func_80AF7E6C(this);
        func_80AF8AC8(this);
    } else {
        this->actionFunc(this, globalCtx);
        func_80AF7BAC(this);
        if (this->unk_258 != 0) {
            func_80AF8DD4(this, globalCtx);
            func_80AF7E6C(this);
            func_80AF8AC8(this);
            func_8013C964(&this->actor, globalCtx, this->unk_368, 30.0f, this->unk_394, this->unk_356 & 7);
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 12.0f, 0.0f, 4);
            func_80AF7F68(this, globalCtx);
        }
    }
}

s32 EnPm_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                          Gfx** gfx) {
    EnPm* this = THIS;

    if (limbIndex == 15) {
        func_80AF8C68(this, globalCtx);
    }
    return false;
}

void EnPm_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnPm* this = THIS;
    s32 pad;
    Vec3f sp2C;

    switch (limbIndex) {
        case 15:
            if (ActorCutscene_GetCurrentIndex() == -1) {
                Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->actor.focus.pos);
                Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
            }
            if ((this->unk_356 & 0x8000) && !(gSaveContext.weekEventReg[90] & 4)) {
                func_80AF8890(this, gfx, 1);
            }
            break;

        case 11:
            if (this->unk_356 & 0x800) {
                func_80AF8890(this, gfx, 0);
            }
            break;

        case 8:
            if ((this->unk_258 == 9) || (this->unk_258 == 20) || (this->unk_258 == 21) || (this->unk_258 == 22)) {
                Matrix_MultiplyVector3fByState(&gZeroVec3f, &sp2C);
                Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &sp2C);
            } else if (this->unk_258 == 24) {
                Matrix_MultiplyVector3fByState(&gZeroVec3f, &sp2C);
                Math_Vec3f_ToVec3s(&this->colliderSphere.dim.worldSphere.center, &sp2C);
            }
            func_80AF8890(this, gfx, 2);
            break;
    }
}

void EnPm_TransformLimbDraw(GlobalContext* globalCtx, s32 arg1, Actor* thisx, Gfx** gfx) {
    EnPm* this = THIS;
    s32 phi_v0;
    s32 phi_v1;

    if (!(this->unk_356 & 0x200)) {
        if (this->unk_356 & 0x80) {
            phi_v1 = 1;
        } else {
            phi_v1 = 0;
        }
        phi_v0 = 1;
    } else {
        phi_v1 = 0;
        phi_v0 = 0;
    }

    if (arg1 == 15) {
        func_8013AD9C(this->unk_370 + 0x4000, this->unk_372 + this->actor.shape.rot.y + 0x4000, &this->unk_284,
                      &this->unk_290, phi_v0, phi_v1);
        Matrix_StatePop();
        Matrix_InsertTranslation(this->unk_284.x, this->unk_284.y, this->unk_284.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk_290.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_290.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_290.z, MTXMODE_APPLY);
        Matrix_StatePush();
    }
}

void EnPm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80AFB914[] = {
        object_mm_Tex_002950,
        object_mm_Tex_002750,
    };
    EnPm* this = THIS;
    s32 pad;

    if (this->unk_258 != 0) {
        func_8012C28C(globalCtx->state.gfxCtx);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        Scene_SetRenderModeXlu(globalCtx, 0, 1);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AFB914[0]));

        POLY_OPA_DISP = SubS_DrawTransformFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                               this->skelAnime.dListCount, EnPm_OverrideLimbDraw, EnPm_PostLimbDraw,
                                               EnPm_TransformLimbDraw, &this->actor, POLY_OPA_DISP);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
