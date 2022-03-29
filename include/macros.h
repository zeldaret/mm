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
#define CAM_ID_MAIN 0

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
#define LINK_IS_CHILD (gSaveContext.save.linkAge == 1)
#define LINK_IS_ADULT (gSaveContext.save.linkAge == 0)

#define CURRENT_DAY (((void)0, gSaveContext.save.day) % 5)

#define CLOCK_TIME(hr, min) (s32)(((hr) * 60 + (min)) * 0x10000 / (24 * 60))
#define CLOCK_TIME_MINUTE  (CLOCK_TIME(0, 1))

#define TIME_TO_MINUTES_F(time) ((time) * ((24.0f * 60.0f) / 0x10000)) // 0.021972656f
#define CLOCK_TIME_F(hr, min) (((hr) * 60.0f + (min)) * (0x10000 / (24.0f * 60.0f)))

#define TIME_TO_MINUTES_ALT_F(time) ((time) / (0x10000 / (24.0f * 60.0f)))
#define CLOCK_TIME_ALT_F(hr, min) (((hr) * 60.0f + (min)) / (24.0f * 60.0f / 0x10000))

#define SLOT(item) gItemSlots[item]
#define AMMO(item) gSaveContext.save.inventory.ammo[SLOT(item)]
#define INV_CONTENT(item) gSaveContext.save.inventory.items[SLOT(item)]
#define GET_INV_CONTENT(item) ((void)0, gSaveContext.save.inventory.items)[SLOT(item)]

#define CUR_FORM ((gSaveContext.save.playerForm == PLAYER_FORM_HUMAN) ? 0 : gSaveContext.save.playerForm)

#define GET_SAVE_EQUIPS_EQUIPMENT ((void)0, gSaveContext.save.equips.equipment)
#define GET_SAVE_INVENTORY_UPGRADES ((void)0, gSaveContext.save.inventory.upgrades)
#define GET_SAVE_INVENTORY_QUEST_ITEMS ((void)0, gSaveContext.save.inventory.questItems)

#define GET_CUR_EQUIP_VALUE(equip) ((GET_SAVE_EQUIPS_EQUIPMENT & gEquipMasks[equip]) >> gEquipShifts[equip])

#define CUR_UPG_VALUE(upg) ((gSaveContext.save.inventory.upgrades & gUpgradeMasks[upg]) >> gUpgradeShifts[upg])
#define GET_CUR_UPG_VALUE(upg) ((GET_SAVE_INVENTORY_UPGRADES & gUpgradeMasks[upg]) >> gUpgradeShifts[upg])

#define SET_EQUIP_VALUE(equip, value) (gSaveContext.save.equips.equipment = ((GET_SAVE_EQUIPS_EQUIPMENT & gEquipNegMasks[equip]) | (u16)((u16)(value) << gEquipShifts[equip])))

#define BUTTON_ITEM_EQUIP(form, button) (gSaveContext.save.equips.buttonItems[form][button])
#define CUR_FORM_EQUIP(button) BUTTON_ITEM_EQUIP(CUR_FORM, button)

#define C_SLOT_EQUIP(form, button) (gSaveContext.save.equips.cButtonSlots[form][button])
#define CHECK_QUEST_ITEM(item) (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[item])
#define REMOVE_QUEST_ITEM(item) (gSaveContext.save.inventory.questItems = (GET_SAVE_INVENTORY_QUEST_ITEMS & (-1 - gBitFlags[item])))

#define CHECK_DUNGEON_ITEM(item, dungeonIndex) (gSaveContext.save.inventory.dungeonItems[(void)0, dungeonIndex] & gBitFlags[item])
#define DUNGEON_KEY_COUNT(dungeonIndex) (gSaveContext.save.inventory.dungeonKeys[(void)0, dungeonIndex])

#define GET_CUR_FORM_BTN_ITEM(btn) ((u8)((btn) == EQUIP_SLOT_B ? BUTTON_ITEM_EQUIP(CUR_FORM, btn) : BUTTON_ITEM_EQUIP(0, btn)))

#define SET_CUR_FORM_BTN_ITEM(btn, item)                 \
    do {                                                 \
        if ((btn) == EQUIP_SLOT_B) {                     \
            BUTTON_ITEM_EQUIP(CUR_FORM, (btn)) = (item); \
        } else {                                         \
            BUTTON_ITEM_EQUIP(0, (btn)) = (item);        \
        }                                                \
    } while (0)

#define STOLEN_ITEM_NONE (0)

#define STOLEN_ITEM_1 ((gSaveContext.save.stolenItems & 0xFF000000) >> 0x18)
#define STOLEN_ITEM_2 ((gSaveContext.save.stolenItems & 0x00FF0000) >> 0x10)

#define SET_STOLEN_ITEM_1(itemId) \
    (gSaveContext.save.stolenItems = (gSaveContext.save.stolenItems & ~0xFF000000) | ((itemId & 0xFF) << 0x18))
#define SET_STOLEN_ITEM_2(itemId) \
    (gSaveContext.save.stolenItems = (gSaveContext.save.stolenItems & ~0x00FF0000) | ((itemId & 0xFF) << 0x10))

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
#define ALIGN256(val) (((val) + 0xFF) & ~0xFF)

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

#endif // MACROS_H
