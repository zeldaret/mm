/*
 * File: z_dm_char01.c
 * Overlay: ovl_Dm_Char01
 * Description: Woodfall scene objects (temple, water, walls, etc)
 */

#include "z_dm_char01.h"
#include "objects/object_mtoride/object_mtoride.h"

#define FLAGS 0x02000030

#define THIS ((DmChar01*)thisx)

void DmChar01_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AA8698(DmChar01* this, GlobalContext* globalCtx);
void func_80AA884C(DmChar01* this, GlobalContext* globalCtx);
void func_80AA88A8(DmChar01* this, GlobalContext* globalCtx);
void func_80AA892C(DmChar01* this, GlobalContext* globalCtx);
void func_80AA8C28(DmChar01* this, GlobalContext* globalCtx);
void func_80AA8F1C(DmChar01* this, GlobalContext* globalCtx);
void func_80AA8F2C(DmChar01* this, GlobalContext* globalCtx);
void func_80AA9020(DmChar01* this, GlobalContext* globalCtx);
void func_80AA90AC(DmChar01* this, GlobalContext* globalCtx);
void func_80AA90F4(DmChar01* this, GlobalContext* globalCtx);

static s16 D_80AAAE20;
static s16 D_80AAAE22;
static s16 D_80AAAE24;
static s16 D_80AAAE26;

static s16 D_80AA9DC0[][8] = {
    {
        0x0764,
        0xFFD8,
        0x001B,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x060A,
        0x0028,
        0x0242,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0x05EB,
        0xFFD8,
        0x046E,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x0629,
        0xFFD8,
        0x0016,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },

    {
        0x04EE,
        0xFFD8,
        0x03B1,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0x04EE,
        0x0028,
        0x01E1,
        0x0000,
        0x1029,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0x04ED,
        0xFFD8,
        0x0012,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0x03F2,
        0xFFD8,
        0x02F4,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0x03D2,
        0x0028,
        0x0181,
        0x0000,
        0x1029,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0x03B2,
        0xFFD8,
        0x000D,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0x02F5,
        0xFFD8,
        0x0237,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0x02B6,
        0x0028,
        0x0120,
        0x0000,
        0x1029,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0x0277,
        0xFFD8,
        0x0009,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x01F9,
        0xFFD8,
        0x017A,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x019A,
        0x0028,
        0x00BF,
        0x0000,
        0x1029,
        0xE191,
        0xC5B2,
        0xFFFF,
    },
    {
        0x013B,
        0xFFD8,
        0x0004,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x00FC,
        0xFFD8,
        0x00BD,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },

    {
        0x0764,
        0xFFD8,
        0x001B,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x0636,
        0x0028,
        0xFE47,
        0x0000,
        0x0DAD,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0x0629,
        0xFFD8,
        0x0016,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0x0509,
        0xFFD8,
        0xFC73,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0x060A,
        0xFFD8,
        0xFBBD,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x0518,
        0x0028,
        0xFEA0,
        0x0000,
        0x0DAD,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0x0407,
        0xFFD8,
        0xFD29,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0x04ED,
        0xFFD8,
        0x0012,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0x03F9,
        0x0028,
        0xFEF8,
        0x0000,
        0x0DAD,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0x0305,
        0xFFD8,
        0xFDDF,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0x03B2,
        0xFFD8,
        0x000D,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0x02DB,
        0x0028,
        0xFF51,
        0x0000,
        0x0DAD,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0x0203,
        0xFFD8,
        0xFE94,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x0277,
        0xFFD8,
        0x0009,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x0203,
        0xFFD8,
        0xFE94,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x01BC,
        0x0028,
        0xFFAA,
        0x0000,
        0x0DAD,
        0xE191,
        0xC5B2,
        0xFFFF,
    },

    {
        0x0277,
        0xFFD8,
        0x0009,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x0102,
        0xFFD8,
        0xFF4A,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x013B,
        0xFFD8,
        0x0004,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },
    {
        0x060A,
        0xFFD8,
        0xFBBD,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x0403,
        0x0028,
        0xFAF4,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0x0509,
        0xFFD8,
        0xFC73,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0x01FC,
        0xFFD8,
        0xFA2B,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0x0262,
        0xFFD8,
        0xF901,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x0403,
        0x0028,
        0xFAF4,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0x0350,
        0x0028,
        0xFBE5,
        0x0000,
        0x1029,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0x0197,
        0xFFD8,
        0xFB56,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0x0407,
        0xFFD8,
        0xFD29,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0x029C,
        0x0028,
        0xFCD5,
        0x0000,
        0x1029,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0x0131,
        0xFFD8,
        0xFC80,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0x0305,
        0xFFD8,
        0xFDDF,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0x01E8,
        0x0028,
        0xFDC5,
        0x0000,
        0x1029,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0x00CB,
        0xFFD8,
        0xFDAB,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x0203,
        0xFFD8,
        0xFE94,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x0135,
        0x0028,
        0xFEB5,
        0x0000,
        0x1029,
        0xE191,
        0xC5B2,
        0xFFFF,
    },
    {
        0x0066,
        0xFFD8,
        0xFED5,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },

    {
        0x0102,
        0xFFD8,
        0xFF4A,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },
    {
        0x005D,
        0xFFD8,
        0x012D,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x00FC,
        0xFFD8,
        0x00BD,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x00DB,
        0x0028,
        0x018C,
        0x0000,
        0x0DAD,
        0xE191,
        0xC5B2,
        0xFFFF,
    },
    {
        0x00BA,
        0xFFD8,
        0x025B,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x01F9,
        0xFFD8,
        0x017A,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x0188,
        0x0028,
        0x0281,
        0x0000,
        0x0DAD,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0x00BA,
        0xFFD8,
        0x025B,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x0118,
        0xFFD8,
        0x0388,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0x0188,
        0x0028,
        0x0281,
        0x0000,
        0x0DAD,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0x02F5,
        0xFFD8,
        0x0237,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0x01F9,
        0xFFD8,
        0x017A,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x0235,
        0x0028,
        0x0376,
        0x0000,
        0x0DAD,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0x0175,
        0xFFD8,
        0x04B5,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0x03F2,
        0xFFD8,
        0x02F4,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0x02E2,
        0x0028,
        0x046B,
        0x0000,
        0x0DAD,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0x01D2,
        0xFFD8,
        0x05E2,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0x04EE,
        0xFFD8,
        0x03B1,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0x038F,
        0x0028,
        0x0560,
        0x0000,
        0x0DAD,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0x022F,
        0xFFD8,
        0x0710,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x05EB,
        0xFFD8,
        0x046E,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x038F,
        0x0028,
        0x0560,
        0x0000,
        0x0DAD,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },
    {
        0xFF9A,
        0xFFD8,
        0x012B,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x005D,
        0xFFD8,
        0x012D,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0xFFC9,
        0x0028,
        0x01C1,
        0x0000,
        0x1029,
        0xE191,
        0xC5B2,
        0xFFFF,
    },
    {
        0xFF35,
        0xFFD8,
        0x0255,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0x00BA,
        0xFFD8,
        0x025B,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFFC5,
        0x0028,
        0x02ED,
        0x0000,
        0x1029,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0xFECF,
        0xFFD8,
        0x0380,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0x0118,
        0xFFD8,
        0x0388,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFFC0,
        0x0028,
        0x0419,
        0x0000,
        0x1029,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0xFE69,
        0xFFD8,
        0x04AA,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0x0175,
        0xFFD8,
        0x04B5,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFFC0,
        0x0028,
        0x0419,
        0x0000,
        0x1029,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0xFFBC,
        0x0028,
        0x0545,
        0x0000,
        0x1029,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0xFE04,
        0xFFD8,
        0x05D5,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0x01D2,
        0xFFD8,
        0x05E2,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFFBC,
        0x0028,
        0x0545,
        0x0000,
        0x1029,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0xFE04,
        0xFFD8,
        0x05D5,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFFB8,
        0x0028,
        0x0671,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0x01D2,
        0xFFD8,
        0x05E2,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFD9E,
        0xFFD8,
        0x06FF,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x022F,
        0xFFD8,
        0x0710,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0x0262,
        0xFFD8,
        0xF901,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0xFFE7,
        0x0028,
        0xF98E,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0x01FC,
        0xFFD8,
        0xFA2B,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFDD1,
        0xFFD8,
        0xF8F0,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0xFE2E,
        0xFFD8,
        0xFA1E,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFFE7,
        0x0028,
        0xF98E,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0xFFE2,
        0x0028,
        0xFABA,
        0x0000,
        0x1029,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0x0197,
        0xFFD8,
        0xFB56,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFE8B,
        0xFFD8,
        0xFB4B,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFFDE,
        0x0028,
        0xFBE6,
        0x0000,
        0x1029,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0x0131,
        0xFFD8,
        0xFC80,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFEE8,
        0xFFD8,
        0xFC78,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFFDA,
        0x0028,
        0xFD12,
        0x0000,
        0x1029,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0x00CB,
        0xFFD8,
        0xFDAB,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFF46,
        0xFFD8,
        0xFDA5,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFFD6,
        0x0028,
        0xFE3D,
        0x0000,
        0x1029,
        0xE191,
        0xC5B2,
        0xFFFF,
    },
    {
        0x0066,
        0xFFD8,
        0xFED5,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0xFFA3,
        0xFFD8,
        0xFED3,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },
    {
        0xFDD1,
        0xFFD8,
        0xF8F0,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0xFC21,
        0x0028,
        0xFAD8,
        0x0000,
        0x0DAD,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0xFE2E,
        0xFFD8,
        0xFA1E,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFA15,
        0xFFD8,
        0xFB92,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0xFB12,
        0xFFD8,
        0xFC4F,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFC21,
        0x0028,
        0xFAD8,
        0x0000,
        0x0DAD,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0xFCCE,
        0x0028,
        0xFBCD,
        0x0000,
        0x0DAD,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0xFE8B,
        0xFFD8,
        0xFB4B,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFB12,
        0xFFD8,
        0xFC4F,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFC0E,
        0xFFD8,
        0xFD0C,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFCCE,
        0x0028,
        0xFBCD,
        0x0000,
        0x0DAD,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0xFE8B,
        0xFFD8,
        0xFB4B,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFD7B,
        0x0028,
        0xFCC2,
        0x0000,
        0x0DAD,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0xFEE8,
        0xFFD8,
        0xFC78,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFD0B,
        0xFFD8,
        0xFDC9,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFE28,
        0x0028,
        0xFDB7,
        0x0000,
        0x0DAD,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0xFF46,
        0xFFD8,
        0xFDA5,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFE07,
        0xFFD8,
        0xFE86,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFED5,
        0x0028,
        0xFEAC,
        0x0000,
        0x0DAD,
        0xE191,
        0xC5B2,
        0xFFFF,
    },
    {
        0xFFA3,
        0xFFD8,
        0xFED3,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0xFF04,
        0xFFD8,
        0xFF43,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },
    {
        0xFA15,
        0xFFD8,
        0xFB92,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },

    {
        0xF9D7,
        0x0028,
        0xFE1A,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0xFB12,
        0xFFD8,
        0xFC4F,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xF89C,
        0xFFD8,
        0xFFE5,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0xF9D7,
        0xFFD8,
        0xFFEA,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xF9D7,
        0x0028,
        0xFE1A,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0xFAF3,
        0x0028,
        0xFE7B,
        0x0000,
        0x1029,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0xFC0E,
        0xFFD8,
        0xFD0C,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFB13,
        0xFFD8,
        0xFFEE,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFC0F,
        0x0028,
        0xFEDC,
        0x0000,
        0x1029,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0xFD0B,
        0xFFD8,
        0xFDC9,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFC4E,
        0xFFD8,
        0xFFF3,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFD2A,
        0x0028,
        0xFF3C,
        0x0000,
        0x1029,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0xFE07,
        0xFFD8,
        0xFE86,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFD89,
        0xFFD8,
        0xFFF7,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFE46,
        0x0028,
        0xFF9D,
        0x0000,
        0x1029,
        0xE191,
        0xC5B2,
        0xFFFF,
    },
    {
        0xFF04,
        0xFFD8,
        0xFF43,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0xFEC5,
        0xFFD8,
        0xFFFC,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0xFEC5,
        0xFFD8,
        0xFFFC,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },
    {
        0xFF04,
        0xFFD8,
        0xFF43,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0xF89C,
        0xFFD8,
        0xFFE5,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0xF9E6,
        0x0028,
        0x0216,
        0x0000,
        0x0DAD,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0xF9D7,
        0xFFD8,
        0xFFEA,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xF9F6,
        0xFFD8,
        0x0443,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0xFAF7,
        0xFFD8,
        0x038D,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xF9E6,
        0x0028,
        0x0216,
        0x0000,
        0x0DAD,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0xFB05,
        0x0028,
        0x01BD,
        0x0000,
        0x0DAD,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0xFB13,
        0xFFD8,
        0xFFEE,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFBF9,
        0xFFD8,
        0x02D7,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFB05,
        0x0028,
        0x01BD,
        0x0000,
        0x0DAD,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0xFC24,
        0x0028,
        0x0165,
        0x0000,
        0x0DAD,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0xFC4E,
        0xFFD8,
        0xFFF3,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFCFB,
        0xFFD8,
        0x0221,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFD42,
        0x0028,
        0x010C,
        0x0000,
        0x0DAD,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0xFD89,
        0xFFD8,
        0xFFF7,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFDFD,
        0xFFD8,
        0x016C,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFE61,
        0x0028,
        0x00B4,
        0x0000,
        0x0DAD,
        0xE191,
        0xC5B2,
        0xFFFF,
    },
    {
        0xFEC5,
        0xFFD8,
        0xFFFC,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0xFEFE,
        0xFFD8,
        0x00B6,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },
    {
        0xF9F6,
        0xFFD8,
        0x0443,
        0x0000,
        0x0000,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0xFC4B,
        0x0028,
        0x0546,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0xFAF7,
        0xFFD8,
        0x038D,
        0x0000,
        0x027D,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFD9E,
        0xFFD8,
        0x06FF,
        0x0000,
        0x1DD6,
        0x0400,
        0xA568,
        0x59FF,
    },
    {
        0xFE04,
        0xFFD8,
        0x05D5,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFC4B,
        0x0028,
        0x0546,
        0x0000,
        0x1029,
        0x002D,
        0xAD72,
        0x6EFF,
    },
    {
        0xFCFE,
        0x0028,
        0x0456,
        0x0000,
        0x1029,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0xFBF9,
        0xFFD8,
        0x02D7,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFE04,
        0xFFD8,
        0x05D5,
        0x0000,
        0x1B5A,
        0xFC59,
        0xB880,
        0x8FFF,
    },
    {
        0xFE69,
        0xFFD8,
        0x04AA,
        0x0000,
        0x18DD,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFCFE,
        0x0028,
        0x0456,
        0x0000,
        0x1029,
        0xF886,
        0xC28D,
        0xABFF,
    },
    {
        0xFBF9,
        0xFFD8,
        0x02D7,
        0x0000,
        0x04F9,
        0xF4B2,
        0xCD9B,
        0xCBFF,
    },
    {
        0xFDB2,
        0x0028,
        0x0366,
        0x0000,
        0x1029,
        0xF0DF,
        0xD8A8,
        0xE9FF,
    },
    {
        0xFCFB,
        0xFFD8,
        0x0221,
        0x0000,
        0x0776,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFECF,
        0xFFD8,
        0x0380,
        0x0000,
        0x1661,
        0xED0B,
        0xE0B2,
        0xFFFF,
    },
    {
        0xFE66,
        0x0028,
        0x0276,
        0x0000,
        0x1029,
        0xE938,
        0xDCB2,
        0xFFFF,
    },
    {
        0xFDFD,
        0xFFD8,
        0x016C,
        0x0000,
        0x09F2,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFF35,
        0xFFD8,
        0x0255,
        0x0000,
        0x13E4,
        0xE564,
        0xD8B2,
        0xFFFF,
    },
    {
        0xFF19,
        0x0028,
        0x0185,
        0x0000,
        0x1029,
        0xE191,
        0xC5B2,
        0xFFFF,
    },
    {
        0xFEFE,
        0xFFD8,
        0x00B6,
        0x0000,
        0x0C6F,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0xFF9A,
        0xFFD8,
        0x012B,
        0x0000,
        0x1168,
        0xDDBD,
        0xC9B2,
        0xFFFF,
    },
    {
        0x0000,
        0x0028,
        0x0000,
        0x0000,
        0x0EEB,
        0xD616,
        0xC1B2,
        0xFFFF,
    },
};

const ActorInit Dm_Char01_InitVars = {
    ACTOR_DM_CHAR01,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MTORIDE,
    sizeof(DmChar01),
    (ActorFunc)DmChar01_Init,
    (ActorFunc)DmChar01_Destroy,
    (ActorFunc)DmChar01_Update,
    (ActorFunc)DmChar01_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_STOP),
};

static s16 D_80AAAAB4 = 0;

void DmChar01_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmChar01* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Actor_SetScale(&this->dyna.actor, 1.0f);

    this->unk_346 = 0;
    this->unk_34D = 0;
    D_80AAAE24 = 0;
    D_80AAAE26 = 0;

    switch (this->dyna.actor.params) {
        case 0:
            if (gSaveContext.weekEventReg[20] & 2) {
                this->unk_34C = 2;
                this->actionFunc = func_80AA8F1C;
                break;
            }

            if (gSaveContext.sceneSetupIndex == 0) {
                globalCtx->envCtx.unk_1F = 5;
                globalCtx->envCtx.unk_20 = 5;
            }
            this->unk_348 = 255.0f;

            for (i = 0; i < ARRAY_COUNT(this->unk_1AC); i++) {
                this->unk_1AC[i] = D_80AA9DC0[i][1] * 409.6f;
            }

            DynaPolyActor_Init(&this->dyna, 0);
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_mtoride_Colheader_009E4C);

            this->unk_34D = 1;
            if (gSaveContext.sceneSetupIndex == 1) {
                this->unk_34C = 1;
                this->actionFunc = func_80AA8C28;
            } else {
                this->unk_34C = 0;
                this->actionFunc = func_80AA892C;
            }
            break;

        case 1:
            if ((gSaveContext.weekEventReg[20] & 2) || (gSaveContext.sceneSetupIndex == 1)) {
                this->unk_34C = 1;
                this->actionFunc = func_80AA8F1C;
            } else {
                this->actionFunc = func_80AA8698;
            }
            break;

        case 2:
            this->unk_34C = 0;
            if (!(gSaveContext.weekEventReg[20] & 1)) {
                this->unk_34C = 1;
                this->dyna.actor.world.pos.y -= 400.0f;
            }
            this->dyna.actor.world.rot.y += 0x8000;
            this->dyna.actor.shape.rot.y += 0x8000;
            DynaPolyActor_Init(&this->dyna, 0);
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_mtoride_Colheader_010C3C);
            this->unk_34D = 1;
            this->unk_348 = 200.0f;
            this->actionFunc = func_80AA8F2C;
            break;

        case 3:
            this->dyna.actor.world.rot.y += 0x8000;
            this->dyna.actor.shape.rot.y += 0x8000;
            if (!(gSaveContext.weekEventReg[20] & 1)) {
                Actor_MarkForDeath(&this->dyna.actor);
                return;
            }

            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ETCETERA, 5.0f, 202.0f, 294.0f, 0, 0, 0, 0x80);
            DynaPolyActor_Init(&this->dyna, 0);
            DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_mtoride_Colheader_00FE5C);

            this->unk_34D = 1;
            if (!(gSaveContext.weekEventReg[20] & 2)) {
                this->actionFunc = func_80AA9020;
                this->dyna.actor.world.pos.y -= 120.0f;
            } else {
                this->actionFunc = func_80AA8F1C;
            }
            break;

        default:
            this->actionFunc = func_80AA88A8;
            break;
    }
}

void DmChar01_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DmChar01* this = THIS;

    if (this->unk_34D != 0) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void func_80AA8698(DmChar01* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Player* player2 = GET_PLAYER(globalCtx);

    if (gSaveContext.weekEventReg[20] & 1) {
        return;
    }

    if ((player->stateFlags2 & 0x8000000) && (player2->actor.world.pos.x > -40.0f) &&
        (player2->actor.world.pos.x < 40.0f) && (player2->actor.world.pos.z > 1000.0f) &&
        (player2->actor.world.pos.z < 1078.0f)) {
        if (D_80AAAAB4 == 0) {
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            D_80AAAAB4 = 1;
        }
    } else {
        D_80AAAAB4 = 0;
    }

    if ((player->transformation == PLAYER_FORM_DEKU) && (globalCtx->msgCtx.unk1202A == 3) &&
        (globalCtx->msgCtx.unk1202E == 0)) {

        if ((player2->actor.world.pos.x > -40.0f) && (player2->actor.world.pos.x < 40.0f) &&
            (player2->actor.world.pos.z > 1000.0f) && (player2->actor.world.pos.z < 1078.0f)) {
            gSaveContext.weekEventReg[20] |= 1;
            this->actionFunc = func_80AA884C;
        }
    }
}

void func_80AA884C(DmChar01* this, GlobalContext* globalCtx) {
    s16 sp1E = this->dyna.actor.cutscene;

    if (ActorCutscene_GetCanPlayNext(sp1E)) {
        ActorCutscene_Start(sp1E, &this->dyna.actor);
        this->actionFunc = func_80AA88A8;
    } else {
        ActorCutscene_SetIntentToPlay(sp1E);
    }
}

void func_80AA88A8(DmChar01* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x87)) {
        if (globalCtx->csCtx.frames == globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x87)]->startFrame) {
            D_80AAAE24 = 1;
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_FORT_RISING);
        }
    } else {
        D_80AAAE24 = 0;
    }
}

void func_80AA892C(DmChar01* this, GlobalContext* globalCtx) {
    f32 temp_f18;
    s32 temp_v0_4;
    s32 i;

    switch (this->unk_346) {
        case 0:
            D_80AAAE22 = -2200;
            D_80AAAE20 = 380;
            this->unk_346++;
            break;

        case 1:
            if (D_80AAAE24 != 0) {
                this->unk_34C = 1;
                if (D_80AAAE22 > -2000) {
                    D_80AAAE26 = 1;
                }

                D_80AAAE22 += 40;
                if (D_80AAAE22 > 3400) {
                    if (D_80AAAE20 > 100) {
                        D_80AAAE20 -= 230;
                    }
                    this->unk_346++;
                }
            }
            break;

        case 2:
            D_80AAAE22 -= 40;
            if (D_80AAAE22 <= -2200) {
                if (D_80AAAE20 > 100) {
                    D_80AAAE20 -= 70;
                }
                this->unk_346--;
            }
            break;
    }

    if (D_80AAAE24 == 0) {
        this->unk_34C = 0;
    }

    for (i = 0; i < ARRAY_COUNT(D_80AA9DC0); i++) {
        s32 temp_s2 = sqrtf(SQ((f32)D_80AA9DC0[i][2]) + SQ((f32)D_80AA9DC0[i][0]));
        f32 cos = Math_CosS((temp_s2 / 1892.0f) * 0x4000);
        f32 temp_f20 = (1.0f - (ABS_ALT(temp_s2 - D_80AAAE22) / 1892.0f)) * D_80AAAE20 * cos;

        if (temp_f20 < 0.0f) {
            temp_f20 = 0.0f;
        }

        temp_f18 = Math_SinS(this->unk_1AC[i]) * 15.0f;
        temp_f20 += temp_f18;

        this->unk_1AC[i] += 1600;
        D_80AA9DC0[i][1] = temp_f20;
    }
}

void func_80AA8C28(DmChar01* this, GlobalContext* globalCtx) {
    f32 temp_f18;
    s32 temp_v0_4;
    s32 i;

    switch (this->unk_346) {
        case 0:
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_WATER_PURIFICATION);
            D_80AAAE22 = -2200;
            D_80AAAE20 = 100;
            this->unk_346++;
            break;

        case 1:
            D_80AAAE22 += 40;
            if (D_80AAAE22 > 3400) {
                this->unk_346++;
            }
            break;

        case 2:
            D_80AAAE22 -= 40;
            if (D_80AAAE22 <= -2200) {
                this->unk_346--;
            }
            break;
    }

    for (i = 0; i < ARRAY_COUNT(D_80AA9DC0); i++) {
        s32 temp_s2 = sqrtf(SQ((f32)D_80AA9DC0[i][2]) + SQ((f32)D_80AA9DC0[i][0]));
        f32 cos = Math_CosS((temp_s2 / 1892.0f) * 0x4000);
        f32 temp_f20 = (1.0f - (ABS_ALT(temp_s2 - D_80AAAE22) / 1892.0f)) * D_80AAAE20 * cos;

        if (temp_f20 < 0.0f) {
            temp_f20 = 0.0f;
        }

        temp_f18 = Math_SinS(this->unk_1AC[i]) * 15.0f;
        temp_f20 += temp_f18;

        this->unk_1AC[i] += 1600;
        D_80AA9DC0[i][1] = temp_f20;
    }

    Math_SmoothStepToF(&this->unk_348, 0.0f, 0.02f, 0.6f, 0.4f);

    if (this->unk_348 < 0.01f) {
        this->unk_34C = 2;
        this->actionFunc = func_80AA8F1C;
    }
}

void func_80AA8F0C(DmChar01* this, GlobalContext* globalCtx) {
}

void func_80AA8F1C(DmChar01* this, GlobalContext* globalCtx) {
}

void func_80AA8F2C(DmChar01* this, GlobalContext* globalCtx) {
    if (D_80AAAE26 != 0) {
        Math_SmoothStepToF(&this->dyna.actor.world.pos.y, 0.0f, 0.05f, 6.0f, 0.001f);
        Math_SmoothStepToF(&this->unk_348, 0.0f, 0.01f, 0.5f, 0.4f);
        if ((s32)this->dyna.actor.world.pos.y >= 0) {
            D_80AAAE26 = 2;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ETCETERA, 5.0f, 202.0f, 294.0f, 0, 0, 0, 0x80);
            this->actionFunc = func_80AA90F4;
        }
    }
    func_80AA8F0C(this, globalCtx);
}

void func_80AA9020(DmChar01* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x87)) {
        CsCmdActorAction* temp_v1 = globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x87)];

        if ((temp_v1->startFrame == globalCtx->csCtx.frames) && (temp_v1->unk0 == 2)) {
            gSaveContext.weekEventReg[20] |= 2;
            this->actionFunc = func_80AA90AC;
        }
    }
}

void func_80AA90AC(DmChar01* this, GlobalContext* globalCtx) {
    Math_SmoothStepToF(&this->dyna.actor.world.pos.y, 0.0f, 0.05f, 2.0f, 0.001f);
}

void func_80AA90F4(DmChar01* this, GlobalContext* globalCtx) {
    Math_SmoothStepToF(&this->unk_348, 0.0f, 0.02f, 0.8f, 0.4f);
}

void DmChar01_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    DmChar01* this = THIS;

    this->actionFunc(this, globalCtx);

    if (this->unk_34D != 0) {
        if (this->dyna.actor.params == 0) {
            Player* player = GET_PLAYER(globalCtx);

            if (player->actor.world.pos.y > 5.0f) {
                func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            } else {
                func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            }
        }

        if (this->dyna.actor.params == 2) {
            if (this->dyna.actor.xzDistToPlayer > 600.0f) {
                func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            } else {
                func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            }
        }
    }
}

void DmChar01_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static f32 D_80AAAAB8 = 0.0f;
    static f32 D_80AAAABC = 0.0f;
    static s16 D_80AAAAC0 = 0;
    static s16 D_80AAAAC4 = 0;
    static s16 D_80AAAAC8 = 0;
    static s16 D_80AAAACC = 0;
    DmChar01* this = THIS;
    f32 temp_f12;
    f32 spBC;
    s32 i;
    u8 spB7 = 0;

    switch (thisx->params) {
        case 0:
            switch (this->unk_34C) {
                case 0:
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00AA50));
                    func_800BDFC0(globalCtx, object_mtoride_DL_00A8F8);
                    break;

                case 1:
                    if (gSaveContext.sceneSetupIndex == 1) {
                        AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_0110B8));
                        func_800BDFC0(globalCtx, object_mtoride_DL_010FD8);
                        func_800BE03C(globalCtx, object_mtoride_DL_010EF0);
                        Matrix_InsertTranslation(0.0f, 10.0f, 0.0f, MTXMODE_APPLY);
                    }
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_009D70));

                    OPEN_DISPS(globalCtx->state.gfxCtx);

                    if ((u8)this->unk_348 == 255) {
                        func_8012C28C(globalCtx->state.gfxCtx);

                        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
                        gDPPipeSync(POLY_OPA_DISP++);
                        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x96, 255, 255, 255, 255);
                        gSPSegment(POLY_OPA_DISP++, 0x0B, Lib_SegmentedToVirtual(D_80AA9DC0));
                        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gSPDisplayList(POLY_OPA_DISP++, object_mtoride_DL_009928);
                    } else {
                        func_8012C2DC(globalCtx->state.gfxCtx);

                        gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2);
                        gDPPipeSync(POLY_XLU_DISP++);
                        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, (u8)this->unk_348);
                        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x96, 255, 255, 255, (u8)this->unk_348);
                        gSPSegment(POLY_XLU_DISP++, 0x0B, Lib_SegmentedToVirtual(D_80AA9DC0));
                        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gSPDisplayList(POLY_XLU_DISP++, object_mtoride_DL_009928);
                    }

                    CLOSE_DISPS(globalCtx->state.gfxCtx);
                    break;

                case 2:
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_0110B8));
                    func_800BDFC0(globalCtx, object_mtoride_DL_010FD8);
                    func_800BE03C(globalCtx, object_mtoride_DL_010EF0);
                    break;
            }
            break;

        case 1:
            switch (this->unk_34C) {
                case 0:
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00A5C0));
                    func_800BDFC0(globalCtx, object_mtoride_DL_00A398);
                    break;

                case 1:
                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00B1A0));
                    func_800BDFC0(globalCtx, object_mtoride_DL_00AF98);
                    break;
            }
            break;

        case 2:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00FE90));
            func_800BDFC0(globalCtx, object_mtoride_DL_00DF18);

            if ((this->unk_34C != 0) && ((u8)this->unk_348 != 0)) {
                AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&object_mtoride_Matanimheader_00F768));

                OPEN_DISPS(globalCtx->state.gfxCtx);

                func_8012C2DC(globalCtx->state.gfxCtx);

                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, (u8)this->unk_348);
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, (u8)this->unk_348);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, object_mtoride_DL_00F3C0);

                CLOSE_DISPS(globalCtx->state.gfxCtx);
            }

            if (D_80AAAE24 != 0) {
                if ((D_80AAAE22 > -1800) && (D_80AAAE22 < 3000)) {
                    temp_f12 = D_80AAAE22 - 640.0f;
                    if ((D_80AAAE20 == 380) && (D_80AAAE22 > 640)) {
                        D_80AAAAC0 = 2;
                        D_80AAAAC4 = 0;
                        D_80AAAAC8 = 900;
                        D_80AAAACC = 700;
                        spB7 = 1;
                        if (D_80AAAE22 < 1350) {
                            f32 temp_f0 = temp_f12 / 2000.0f;
                            D_80AAAAB8 = 420.0f - (420.0f * temp_f0);
                            D_80AAAABC = (200.0f * temp_f0) + 200.0f;
                        } else {
                            f32 temp_f0 = temp_f12 / 2000.0f;
                            D_80AAAAB8 = 420.0f - (420.0f * temp_f0);
                            D_80AAAABC = 400.0f;
                        }
                    }
                }

                if (spB7 != 0) {
                    for (i = 0; i < D_80AAAAC0 * 2; i++) {
                        Vec3f sp44;
                        f32 phi_f2 = D_80AAAABC;
                        s16 temp;

                        spBC = Rand_ZeroOne() * D_80AAAAC8;
                        if ((globalCtx->state.frames % 2) != 0) {
                            sp44.x = (Rand_ZeroOne() - 0.5f) * (2.0f * phi_f2);
                            sp44.y = D_80AAAAB8;
                            sp44.z = (Rand_ZeroOne() * D_80AAAAC4) + phi_f2;
                            temp = (s16)spBC + D_80AAAACC;
                            EffectSsGSplash_Spawn(globalCtx, &sp44, NULL, NULL, 0, temp);
                        } else {
                            sp44.x = -phi_f2 - (Rand_ZeroOne() * D_80AAAAC4);
                            sp44.y = D_80AAAAB8;
                            sp44.z = (Rand_ZeroOne() - 0.5f) * (2.0f * phi_f2);
                            temp = (s16)spBC + D_80AAAACC;
                            EffectSsGSplash_Spawn(globalCtx, &sp44, NULL, NULL, 0, temp);
                        }
                    }
                }
            }

            func_800BE03C(globalCtx, object_mtoride_DL_00DE50);
            break;

        case 3:
            if (thisx->world.pos.y > -120.0f) {
                func_800BDFC0(globalCtx, object_mtoride_DL_00FAE8);
            }
            break;
    }
}
