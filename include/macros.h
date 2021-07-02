#ifndef _MACROS_H_
#define _MACROS_H_

#include "convert.h"
#include "stdint.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define HW_REG(reg, type) *(volatile type*)((reg) | 0xa0000000)

// TODO: After uintptr_t cast change should have an AVOID_UB target that just toggles the KSEG0 bit in the address
// rather than add/sub 0x80000000
#define PHYSICAL_TO_VIRTUAL(addr) ((uintptr_t)(addr) + 0x80000000)
#define PHYSICAL_TO_VIRTUAL2(addr) ((uintptr_t)(addr)-0x80000000)
#define VIRTUAL_TO_PHYSICAL(addr) (uintptr_t)((u8*)(addr)-0x80000000)
#define SEGMENTED_TO_VIRTUAL(addr) (void*)(PHYSICAL_TO_VIRTUAL(gSegments[SEGMENT_NUMBER(addr)]) + SEGMENT_OFFSET(addr))

// Currently most often called ctxt in MM, TODO: Refactor names when its used
#define ACTIVE_CAM globalCtx->cameraPtrs[globalCtx->activeCamera]

#define SET_NEXT_GAMESTATE(curState, newInit, newStruct)    \
    (curState)->nextGameStateInit = (GameStateFunc)newInit; \
    (curState)->nextGameStateSize = sizeof(newStruct);

#define PLAYER ((Player*)globalCtx->actorCtx.actorList[ACTORCAT_PLAYER].first)

// linkAge still exists in MM, but is always set to 0 (always adult)
// There are remnants of these macros from OOT, but they are essentially useless
//#define LINK_IS_CHILD (gSaveContext.linkAge != 0)
#define LINK_IS_ADULT (gSaveContext.linkAge == 0)

#define CURRENT_DAY (gSaveContext.day % 5)

#define SLOT(item) gItemSlots[item]
#define AMMO(item) gSaveContext.inventory.ammo[SLOT(item)]
#define INV_CONTENT(item) gSaveContext.inventory.items[SLOT(item)]

#define ALL_EQUIP_VALUE_VOID(equip) \
    ((((void)0, gSaveContext.inventory.equipment) & gEquipMasks[equip]) >> gEquipShifts[equip])
#define CUR_EQUIP_VALUE_VOID(equip) \
    ((((void)0, gSaveContext.equips.equipment) & gEquipMasks[equip]) >> gEquipShifts[equip])
#define CUR_UPG_VALUE_VOID(upg) \
    ((((void)0, gSaveContext.inventory.upgrades) & gUpgradeMasks[upg]) >> gUpgradeShifts[upg])

#define ALL_EQUIP_VALUE(equip) ((gSaveContext.inventory.equipment & gEquipMasks[equip]) >> gEquipShifts[equip])
#define CUR_EQUIP_VALUE(equip) ((gSaveContext.equips.equipment & gEquipMasks[equip]) >> gEquipShifts[equip])
#define CUR_UPG_VALUE(upg) ((gSaveContext.inventory.upgrades & gUpgradeMasks[upg]) >> gUpgradeShifts[upg])

#define CAPACITY(upg, value) gUpgradeCapacities[upg][value]
#define CUR_CAPACITY(upg) CAPACITY(upg, CUR_UPG_VALUE(upg) - 4)

#define CHECK_BTN_ALL(state, combo) (~((state) | ~(combo)) == 0)
#define CHECK_BTN_ANY(state, combo) (((state) & (combo)) != 0)

extern GraphicsContext* __gfxCtx;

#define WORK_DISP __gfxCtx->work.p
#define POLY_OPA_DISP __gfxCtx->polyOpa.p
#define POLY_XLU_DISP __gfxCtx->polyXlu.p
#define OVERLAY_DISP __gfxCtx->overlay.p

// __gfxCtx shouldn't be used directly.
// Use the DISP macros defined above when writing to display buffers.
#define OPEN_DISPS(gfxCtx)                  \
    {                                       \
        GraphicsContext* __gfxCtx = gfxCtx; \
        s32 __dispPad;

#define CLOSE_DISPS(gfxCtx) \
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

#define ALIGN8(val) (((val) + 7) & ~7)
#define ALIGN16(val) (((val) + 0xF) & ~0xF)

#define SQ(x) ((x) * (x))
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define ABS_ALT(x) ((x) < 0 ? -(x) : (x))
#define DECR(x) ((x) == 0 ? 0 : ((x) -= 1))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max) ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))

#define SWAP(type, a, b)  \
    {                     \
        type _temp = (a); \
        (a) = (b);        \
        (b) = _temp;      \
    }

#endif // _MACROS_H_
