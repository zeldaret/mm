#ifndef MACROS_H
#define MACROS_H

#include "libc/stdint.h"
#include "ultra64/convert.h"
#include "z64.h"

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define SCREEN_WIDTH_HIGH_RES  576
#define SCREEN_HEIGHT_HIGH_RES 454

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

// TODO: After uintptr_t cast change should have an AVOID_UB target that just toggles the KSEG0 bit in the address rather than add/sub 0x80000000
#define PHYSICAL_TO_VIRTUAL(addr) ((uintptr_t)(addr) + RDRAM_CACHED)
#define PHYSICAL_TO_VIRTUAL2(addr) ((uintptr_t)(addr) - RDRAM_CACHED)
#define VIRTUAL_TO_PHYSICAL(addr) (uintptr_t)((u8*)(addr) - RDRAM_CACHED)
#define SEGMENTED_TO_VIRTUAL(addr) (void*)(PHYSICAL_TO_VIRTUAL(gSegments[SEGMENT_NUMBER(addr)]) + SEGMENT_OFFSET(addr))

#define GET_ACTIVE_CAM(globalCtx) ((globalCtx)->cameraPtrs[(globalCtx)->activeCamera])
#define MAIN_CAM 0
#define SUBCAM_FREE 0

#define SET_NEXT_GAMESTATE(curState, newInit, newStruct)    \
    (curState)->nextGameStateInit = (GameStateFunc)newInit; \
    (curState)->nextGameStateSize = sizeof(newStruct)

#define SET_FULLSCREEN_VIEWPORT(view)      \
    {                                      \
        Viewport viewport;                 \
        viewport.bottomY = SCREEN_HEIGHT;  \
        viewport.rightX = SCREEN_WIDTH;    \
        viewport.topY = 0;                 \
        viewport.leftX = 0;                \
        View_SetViewport(view, &viewport); \
    }                                      \
    (void)0

#define GET_PLAYER(globalCtx) ((Player*)(globalCtx)->actorCtx.actorLists[ACTORCAT_PLAYER].first)

#define GET_FIRST_ENEMY(globalCtx) ((Actor*)(globalCtx)->actorCtx.actorLists[ACTORCAT_ENEMY].first)

// linkAge still exists in MM, but is always set to 0 (always adult)
// There are remnants of these macros from OOT, but they are essentially useless
#define LINK_IS_CHILD (gSaveContext.linkAge == 1)
#define LINK_IS_ADULT (gSaveContext.linkAge == 0)

#define CURRENT_DAY (((void)0, gSaveContext.day) % 5)

#define TIME_TO_MINUTES(time) (s32)((time) * ((24 * 60) / 0x10000))
#define CLOCK_TIME(hr, min) (s32)(((hr) * 60 + (min)) * 0x10000 / (24 * 60))
#define CLOCK_TIME_MINUTE  (CLOCK_TIME(0, 1))

#define TIME_TO_MINUTES_F(time) ((time) * ((24.0f * 60.0f) / 0x10000))
#define CLOCK_TIME_F(hr, min) (((hr) * 60.0f + (min)) * (0x10000 / (24.0f * 60.0f)))

#define TIME_TO_MINUTES_ALT_F(time) ((time) / (24.0f * 60.0f / 0x10000))
#define CLOCK_TIME_ALT_F(hr, min) (((hr) * 60.0f + (min)) / (24.0f * 60.0f / 0x10000))

#define SLOT(item) gItemSlots[item]
#define AMMO(item) gSaveContext.inventory.ammo[SLOT(item)]
#define INV_CONTENT(item) gSaveContext.inventory.items[SLOT(item)]

#define ALL_EQUIP_VALUE_VOID(equip) \
    ((((void)0, gSaveContext.inventory.equipment) & gEquipMasks[equip]) >> gEquipShifts[equip])
#define CUR_EQUIP_VALUE_VOID(equip) \
    ((((void)0, gSaveContext.equips.equipment) & gEquipMasks[equip]) >> gEquipShifts[equip])
#define CUR_UPG_VALUE_VOID(upg) \
    ((((void)0, gSaveContext.inventory.upgrades) & gUpgradeMasks[upg]) >> gUpgradeShifts[upg])
#define INV_CONTENT_VOID(item) ((void)0, gSaveContext.inventory.items)[SLOT(item)]

#define CUR_FORM ((gSaveContext.playerForm == PLAYER_FORM_HUMAN) ? 0 : gSaveContext.playerForm)

#define ALL_EQUIP_VALUE(equip) ((gSaveContext.inventory.equipment & gEquipMasks[equip]) >> gEquipShifts[equip])
#define CUR_EQUIP_VALUE(equip) ((gSaveContext.equips.equipment & gEquipMasks[equip]) >> gEquipShifts[equip])
#define CUR_UPG_VALUE(upg) ((gSaveContext.inventory.upgrades & gUpgradeMasks[upg]) >> gUpgradeShifts[upg])
#define SET_EQUIP_VALUE(equip, value) (gSaveContext.equips.equipment = ((((void)0, gSaveContext.equips.equipment) & (gEquipNegMasks[equip])) | (u16)((u16)(value) << gEquipShifts[equip])))
#define CUR_FORM_EQUIP(button) (gSaveContext.equips.buttonItems[CUR_FORM][button])
#define CHECK_QUEST_ITEM(item) (((void)0, gSaveContext.inventory.questItems) & gBitFlags[item])
#define REMOVE_QUEST_ITEM(item) (gSaveContext.inventory.questItems = (((void)0, gSaveContext.inventory.questItems) & (-1 - gBitFlags[item])))

#define CAPACITY(upg, value) gUpgradeCapacities[upg][value]
#define CUR_CAPACITY(upg) CAPACITY(upg, CUR_UPG_VALUE(upg))

#define CONTROLLER1(globalCtx) (&(globalCtx)->state.input[0])
#define CONTROLLER2(globalCtx) (&(globalCtx)->state.input[1])
#define CONTROLLER3(globalCtx) (&(globalCtx)->state.input[2])
#define CONTROLLER4(globalCtx) (&(globalCtx)->state.input[3])

#define CHECK_BTN_ALL(state, combo) (~((state) | ~(combo)) == 0)
#define CHECK_BTN_ANY(state, combo) (((state) & (combo)) != 0)

#define CHECK_FLAG_ALL(flags, mask) (((flags) & (mask)) == (mask))

extern GraphicsContext* __gfxCtx;

#define WORK_DISP __gfxCtx->work.p
#define POLY_OPA_DISP __gfxCtx->polyOpa.p
#define POLY_XLU_DISP __gfxCtx->polyXlu.p
#define OVERLAY_DISP __gfxCtx->overlay.p
#define DEBUG_DISP __gfxCtx->debug.p

// __gfxCtx shouldn't be used directly.
// Use the DISP macros defined above when writing to display buffers.
#define OPEN_DISPS(gfxCtx)                  \
    {                                       \
        GraphicsContext* __gfxCtx = gfxCtx; \
        s32 __dispPad

#define CLOSE_DISPS(gfxCtx) \
    (void)0;                \
    }                       \
    (void)0

/**
 * `x` vertex x
 * `y` vertex y
 * `z` vertex z
 * `s` texture s coordinate
 * `t` texture t coordinate
 * `crnx` red component of color vertex, or x component of normal vertex
 * `cgny` green component of color vertex, or y component of normal vertex
 * `cbnz` blue component of color vertex, or z component of normal vertex
 * `a` alpha
 */
#define VTX(x, y, z, s, t, crnx, cgny, cbnz, a) \
    { { { x, y, z }, 0, { s, t }, { crnx, cgny, cbnz, a } }, }

#define VTX_T(x, y, z, s, t, cr, cg, cb, a) \
    { { x, y, z }, 0, { s, t }, { cr, cg, cb, a }, }

#define GRAPH_ALLOC(gfxCtx, size) ((void*)((gfxCtx)->polyOpa.d = (Gfx*)((u8*)(gfxCtx)->polyOpa.d - (size))))

// Custom gbi macro
#define gDPSetTileCustom(pkt, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)                    \
    {                                                                                                                  \
        gDPPipeSync(pkt);                                                                                              \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, \
                   masks, shifts);                                                                                     \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_RENDERTILE, pal, cmt, maskt, shiftt,  \
                   cms, masks, shifts);                                                                                \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,                                \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC);                                                          \
    }                                                                                                                  \
    (void)0

#define ALIGN8(val) (((val) + 7) & ~7)
#define ALIGN16(val) (((val) + 0xF) & ~0xF)
#define ALIGN64(val) (((val) + 0x3F) & ~0x3F)

#define SQ(x) ((x) * (x))
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define ABS_ALT(x) ((x) < 0 ? -(x) : (x))
#define DECR(x) ((x) == 0 ? 0 : --(x))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max) ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))

#define ROUND(x) (s32)(((x) >= 0.0) ? ((x) + 0.5) : ((x) - 0.5))

#define SWAP(type, a, b)  \
    {                     \
        type _temp = (a); \
        (a) = (b);        \
        (b) = _temp;      \
    }

#define OVERLAY_RELOCATION_OFFSET(overlayEntry) ((uintptr_t)((overlayEntry)->vramStart) - (uintptr_t)((overlayEntry)->loadedRamAddr))
#define VRAM_PTR_SIZE(entry) ((uintptr_t)((entry)->vramEnd) - (uintptr_t)((entry)->vramStart))

#ifdef __GNUC__
#define ALIGNED8 __attribute__ ((aligned (8)))
#else
#define ALIGNED8
#endif

#endif // _MACROS_H_
