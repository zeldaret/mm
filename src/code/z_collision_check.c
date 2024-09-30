#include "z64collision_check.h"

#include "stdbool.h"

#include "macros.h"
#include "sfx.h"
#include "sys_matrix.h"

#include "z64actor.h"
#include "z64effect.h"
#include "z64frameadvance.h"
#include "zelda_arena.h"
#include "z64math.h"

typedef s32 (*ColChkResetFunc)(struct PlayState*, Collider*);
typedef void (*ColChkBloodFunc)(struct PlayState*, Collider*, Vec3f*);
typedef void (*ColChkApplyFunc)(struct PlayState*, CollisionCheckContext*, Collider*);
typedef void (*ColChkVsFunc)(struct PlayState*, CollisionCheckContext*, Collider*, Collider*);
typedef s32 (*ColChkLineFunc)(struct PlayState*, CollisionCheckContext*, Collider*, Vec3f*, Vec3f*);

#include "prevent_bss_reordering2.h"
// clang-format off
// Partial structs taken from "prevent_bss_reordering.h"
struct Dummy200 { int x; };
struct Dummy201 { int x; };
struct Dummy202 { int x; };
struct Dummy203 { int x; };
struct Dummy204 { int x; };
struct Dummy205 { int x; };
struct Dummy206 { int x; };
struct Dummy207 { int x; };
struct Dummy208 { int x; };
struct Dummy209 { int x; };
struct Dummy210 { int x; };
struct Dummy211 { int x; };
struct Dummy212 { int x; };
struct Dummy213 { int x; };
struct Dummy214 { int x; };
struct Dummy215 { int x; };
struct Dummy216 { int x; };
struct Dummy217 { int x; };
struct Dummy218 { int x; };
struct Dummy219 { int x; };
struct Dummy220 { int x; };
struct Dummy221 { int x; };
struct Dummy222 { int x; };
struct Dummy223 { int x; };
struct Dummy224 { int x; };
struct Dummy225 { int x; };
struct Dummy226 { int x; };
struct Dummy227 { int x; };
struct Dummy228 { int x; };
struct Dummy229 { int x; };
struct Dummy230 { int x; };
struct Dummy231 { int x; };
struct Dummy232 { int x; };
struct Dummy233 { int x; };
struct Dummy234 { int x; };
struct Dummy235 { int x; };
struct Dummy236 { int x; };
struct Dummy237 { int x; };
struct Dummy238 { int x; };
struct Dummy239 { int x; };
struct Dummy240 { int x; };
struct Dummy241 { int x; };
struct Dummy242 { int x; };
struct Dummy243 { int x; };
struct Dummy244 { int x; };
struct Dummy245 { int x; };
struct Dummy246 { int x; };
struct Dummy247 { int x; };
struct Dummy248 { int x; };
struct Dummy249 { int x; };
struct Dummy250 { int x; };
struct Dummy251 { int x; };
struct Dummy252 { int x; };
struct Dummy253 { int x; };
struct Dummy254 { int x; };
struct Dummy255 { int x; };
// clang-format on

Vec3f D_801EDE00;
Vec3f D_801EDE10;
Vec3f D_801EDE20;
Vec3f D_801EDE30;
TriNorm D_801EDE40;
TriNorm D_801EDE78;
Linef D_801EDEB0;
TriNorm D_801EDEC8;
TriNorm D_801EDF00;
Vec3f D_801EDF38;
Vec3f D_801EDF48;
TriNorm D_801EDF58;
TriNorm D_801EDF90;
Linef D_801EDFC8;
Vec3f D_801EDFE0;
Vec3f D_801EDFF0;
TriNorm D_801EE000;
TriNorm D_801EE038;
TriNorm D_801EE070[2];
Vec3f D_801EE0D8;
TriNorm D_801EE0E8[2];
TriNorm D_801EE150;
TriNorm D_801EE188;

#include "prevent_bss_reordering.h"

/**
 * Gets the damage and effect that should be applied for the collision between
 * `at` and `ac`, referring to the ac actor's damage chart if applicable.
 */
f32 CollisionCheck_GetDamageAndEffectOnBumper(Collider* atCol, ColliderElement* atElem, Collider* acCol,
                                              ColliderElement* acElem, u32* effect) {
    static f32 sDamageMultipliers[] = {
        0.0f, 1.0f, 2.0f, 0.5f, 0.25f, 3.0f, 4.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    };
    u32 dmgFlags;
    s32 i;
    f32 damage;

    *effect = 0;
    damage = CollisionCheck_GetToucherDamage(atCol, atElem, acCol, acElem);

    if (acCol->actor->colChkInfo.damageTable != NULL) {
        dmgFlags = atElem->toucher.dmgFlags;

        for (i = 0; i < ARRAY_COUNT(acCol->actor->colChkInfo.damageTable->attack); i++) {
            if (dmgFlags == 1) {
                break;
            }
            dmgFlags >>= 1;
        }

        damage *= sDamageMultipliers[acCol->actor->colChkInfo.damageTable->attack[i] & 0xF];
        *effect = (acCol->actor->colChkInfo.damageTable->attack[i] >> 4) & 0xF;
    }
    return damage;
}

/**
 * Calculates damage after factoring in the ac collider's defense
 */
f32 CollisionCheck_ApplyBumperDefense(f32 damage, ColliderElement* acElem) {
    f32 finalDamage = damage - acElem->bumper.defense;

    return finalDamage;
}

/**
 * Gets the damage to be inflicted by `at` on `ac`, before applying other
 * factors such as the ac collider's defense.
 */
s32 CollisionCheck_GetToucherDamage(Collider* atCol, ColliderElement* atElem, Collider* acCol,
                                    ColliderElement* acElem) {
    if ((atCol->actor != NULL) && (atCol->actor->id == ACTOR_EN_BOM) && (acCol->actor != NULL) &&
        (acCol->actor->id == ACTOR_PLAYER)) {
        return 8;
    }
    return atElem->toucher.damage;
}

s32 Collider_InitBase(struct PlayState* play, Collider* col) {
    static Collider sDefaultCollider = {
        NULL, NULL, NULL, NULL, AT_NONE, AC_NONE, OC1_NONE, OC2_NONE, COLTYPE_HIT3, COLSHAPE_MAX,
    };

    *col = sDefaultCollider;
    return 1;
}

s32 Collider_DestroyBase(struct PlayState* play, Collider* col) {
    return 1;
}

/**
 * Uses default OC2_TYPE_1 and COLTYPE_HIT0
 */
s32 Collider_SetBaseToActor(struct PlayState* play, Collider* col, ColliderInitToActor* src) {
    col->actor = src->actor;
    col->atFlags = src->atFlags;
    col->acFlags = src->acFlags;
    col->ocFlags1 = src->ocFlags1;
    col->ocFlags2 = OC2_TYPE_1;
    col->shape = src->shape;
    return 1;
}

/**
 * Uses default OC2_TYPE_1
 */
s32 Collider_SetBaseType1(struct PlayState* play, Collider* col, Actor* actor, ColliderInitType1* src) {
    col->actor = actor;
    col->colType = src->colType;
    col->atFlags = src->atFlags;
    col->acFlags = src->acFlags;
    col->ocFlags1 = src->ocFlags1;
    col->ocFlags2 = OC2_TYPE_1;
    col->shape = src->shape;
    return 1;
}

s32 Collider_SetBase(struct PlayState* play, Collider* col, Actor* actor, ColliderInit* src) {
    col->actor = actor;
    col->colType = src->colType;
    col->atFlags = src->atFlags;
    col->acFlags = src->acFlags;
    col->ocFlags1 = src->ocFlags1;
    col->ocFlags2 = src->ocFlags2;
    col->shape = src->shape;
    return 1;
}

void Collider_ResetATBase(struct PlayState* play, Collider* col) {
    col->at = NULL;
    col->atFlags &= ~(AT_HIT | AT_BOUNCED);
}

void Collider_ResetACBase(struct PlayState* play, Collider* col) {
    col->ac = NULL;
    col->acFlags &= ~(AC_HIT | AC_BOUNCED);
}

void Collider_ResetOCBase(struct PlayState* play, Collider* col) {
    col->oc = NULL;
    col->ocFlags1 &= ~OC1_HIT;
    col->ocFlags2 &= ~OC2_HIT_PLAYER;
}

s32 Collider_InitTouch(struct PlayState* play, ColliderTouch* touch) {
    static ColliderTouch sDefaultColliderTouch = { 0x00000000, 0, 0 };

    *touch = sDefaultColliderTouch;
    return 1;
}

s32 Collider_DestroyTouch(struct PlayState* play, ColliderTouch* touch) {
    return 1;
}

s32 Collider_SetTouch(struct PlayState* play, ColliderTouch* touch, ColliderTouchInit* src) {
    touch->dmgFlags = src->dmgFlags;
    touch->effect = src->effect;
    touch->damage = src->damage;
    return 1;
}

void Collider_ResetATElementUnk(struct PlayState* play, ColliderElement* elem) {
}

s32 Collider_InitBump(struct PlayState* play, ColliderBump* bump) {
    static ColliderBump sDefaultColliderBump = { 0xF7CFFFFF, 0, 0, { 0, 0, 0 } };

    *bump = sDefaultColliderBump;
    return 1;
}

s32 Collider_DestroyBump(struct PlayState* play, ColliderBump* bump) {
    return 1;
}

s32 Collider_SetBump(struct PlayState* play, ColliderBump* bump, ColliderBumpInit* src) {
    bump->dmgFlags = src->dmgFlags;
    bump->effect = src->effect;
    bump->defense = src->defense;
    return 1;
}

s32 Collider_InitElement(struct PlayState* play, ColliderElement* elem) {
    static ColliderElement sDefaultColliderElement = {
        { 0, 0, 0 },   { 0xF7CFFFFF, 0, 0, { 0, 0, 0 } },
        ELEMTYPE_UNK0, TOUCH_NONE,
        BUMP_NONE,     OCELEM_NONE,
        NULL,          NULL,
        NULL,          NULL,
    };

    *elem = sDefaultColliderElement;
    Collider_InitTouch(play, &elem->toucher);
    Collider_InitBump(play, &elem->bumper);
    return 1;
}

s32 Collider_DestroyElement(struct PlayState* play, ColliderElement* elem) {
    Collider_DestroyTouch(play, &elem->toucher);
    Collider_DestroyBump(play, &elem->bumper);
    return 1;
}

s32 Collider_SetElement(struct PlayState* play, ColliderElement* elem, ColliderElementInit* elemInit) {
    elem->elemType = elemInit->elemType;
    Collider_SetTouch(play, &elem->toucher, &elemInit->toucher);
    Collider_SetBump(play, &elem->bumper, &elemInit->bumper);
    elem->toucherFlags = elemInit->toucherFlags;
    elem->bumperFlags = elemInit->bumperFlags;
    elem->ocElemFlags = elemInit->ocElemFlags;
    return 1;
}

void Collider_ResetATElement(struct PlayState* play, ColliderElement* elem) {
    elem->atHit = NULL;
    elem->atHitElem = NULL;
    elem->toucherFlags &= ~TOUCH_HIT;
    elem->toucherFlags &= ~TOUCH_DREW_HITMARK;
    Collider_ResetATElementUnk(play, elem);
}

void Collider_ResetACElement(struct PlayState* play, ColliderElement* elem) {
    elem->bumper.hitPos.x = elem->bumper.hitPos.y = elem->bumper.hitPos.z = 0;
    elem->bumperFlags &= ~BUMP_HIT;
    elem->bumperFlags &= ~BUMP_DRAW_HITMARK;
    elem->acHit = NULL;
    elem->acHitElem = NULL;
}

void Collider_ResetOCElement(struct PlayState* play, ColliderElement* elem) {
    elem->ocElemFlags &= ~OCELEM_HIT;
}

s32 Collider_InitJntSphElementDim(struct PlayState* play, ColliderJntSphElementDim* dim) {
    static ColliderJntSphElementDim sDefaultColliderJntSphElementDim = {
        { { 0, 0, 0 }, 0 },
        { { 0, 0, 0 }, 0 },
        0.0f,
        0,
    };

    *dim = sDefaultColliderJntSphElementDim;
    return 1;
}

s32 Collider_DestroyJntSphElementDim(struct PlayState* play, ColliderJntSphElementDim* dim) {
    return 1;
}

s32 Collider_SetJntSphElementDim(struct PlayState* play, ColliderJntSphElementDim* dest,
                                 ColliderJntSphElementDimInit* src) {
    dest->limb = src->limb;
    dest->modelSphere = src->modelSphere;
    dest->scale = src->scale * 0.01f;
    return 1;
}

s32 Collider_InitJntSphElement(struct PlayState* play, ColliderJntSphElement* element) {
    Collider_InitElement(play, &element->info);
    Collider_InitJntSphElementDim(play, &element->dim);
    return 1;
}

s32 Collider_DestroyJntSphElement(struct PlayState* play, ColliderJntSphElement* element) {
    Collider_DestroyElement(play, &element->info);
    Collider_DestroyJntSphElementDim(play, &element->dim);
    return 1;
}

s32 Collider_SetJntSphElement(struct PlayState* play, ColliderJntSphElement* dest, ColliderJntSphElementInit* src) {
    Collider_SetElement(play, &dest->info, &src->info);
    Collider_SetJntSphElementDim(play, &dest->dim, &src->dim);
    return 1;
}

s32 Collider_ResetJntSphElementAT(struct PlayState* play, ColliderJntSphElement* collider) {
    Collider_ResetATElement(play, &collider->info);
    return 1;
}

s32 Collider_ResetJntSphElementAC(struct PlayState* play, ColliderJntSphElement* collider) {
    Collider_ResetACElement(play, &collider->info);
    return 1;
}

s32 Collider_ResetJntSphElementOC(struct PlayState* play, ColliderJntSphElement* collider) {
    Collider_ResetOCElement(play, &collider->info);
    return 1;
}

/**
 * Initializes a ColliderJntSph to default values
 */
s32 Collider_InitJntSph(struct PlayState* play, ColliderJntSph* collider) {
    Collider_InitBase(play, &collider->base);
    collider->count = 0;
    collider->elements = NULL;
    return 1;
}

/**
 * Destroys a dynamically allocated ColliderJntSph
 */
s32 Collider_FreeJntSph(struct PlayState* play, ColliderJntSph* collider) {
    ColliderJntSphElement* element;

    Collider_DestroyBase(play, &collider->base);
    for (element = collider->elements; element < &collider->elements[collider->count]; element++) {
        Collider_DestroyJntSphElement(play, element);
    }

    collider->count = 0;
    if (collider->elements != NULL) {
        ZeldaArena_Free(collider->elements);
    }
    collider->elements = NULL;
    return 1;
}

/**
 * Destroys a preallocated ColliderJntSph
 */
s32 Collider_DestroyJntSph(struct PlayState* play, ColliderJntSph* collider) {
    ColliderJntSphElement* element;

    Collider_DestroyBase(play, &collider->base);

    for (element = collider->elements; element < &collider->elements[collider->count]; element++) {
        Collider_DestroyJntSphElement(play, element);
    }
    collider->count = 0;
    collider->elements = NULL;
    return 1;
}

/**
 * Sets up the ColliderJntSph using the values in src, sets it to the actor specified in src, and dynamically allocates
 * the element array. Uses default OC2_TYPE_1 and COLTYPE_HIT0.
 */
s32 Collider_SetJntSphToActor(struct PlayState* play, ColliderJntSph* collider, ColliderJntSphInitToActor* src) {
    ColliderJntSphElement* destElem;
    ColliderJntSphElementInit* srcElem;

    Collider_SetBaseToActor(play, &collider->base, &src->base);
    collider->count = src->count;
    collider->elements = ZeldaArena_Malloc(src->count * sizeof(ColliderJntSphElement));

    if (collider->elements == NULL) {
        collider->count = 0;
        return 0;
    }

    for (destElem = collider->elements, srcElem = src->elements; destElem < &collider->elements[collider->count];
         destElem++, srcElem++) {
        Collider_InitJntSphElement(play, destElem);
        Collider_SetJntSphElement(play, destElem, srcElem);
    }
    return 1;
}

/**
 * Sets up the ColliderJntSph using the values in src and dynamically allocates the element array. Uses default
 * OC2_TYPE_1.
 */
s32 Collider_SetJntSphAllocType1(struct PlayState* play, ColliderJntSph* sphereGroup, Actor* actor,
                                 ColliderJntSphInitType1* src) {
    ColliderJntSphElement* destElem;
    ColliderJntSphElementInit* srcElem;

    Collider_SetBaseType1(play, &sphereGroup->base, actor, &src->base);
    sphereGroup->count = src->count;
    sphereGroup->elements = ZeldaArena_Malloc(src->count * sizeof(ColliderJntSphElement));

    if (sphereGroup->elements == NULL) {
        sphereGroup->count = 0;
        return 0;
    }

    for (destElem = sphereGroup->elements, srcElem = src->elements;
         destElem < &sphereGroup->elements[sphereGroup->count]; destElem++, srcElem++) {
        Collider_InitJntSphElement(play, destElem);
        Collider_SetJntSphElement(play, destElem, srcElem);
    }
    return 1;
}

/**
 * Sets up the ColliderJntSph using the values in src, placing the element array in elements.
 */
s32 Collider_SetJntSph(struct PlayState* play, ColliderJntSph* sphereGroup, Actor* actor, ColliderJntSphInit* src,
                       ColliderJntSphElement* elements) {
    ColliderJntSphElement* destElem;
    ColliderJntSphElementInit* srcElem;

    Collider_SetBase(play, &sphereGroup->base, actor, &src->base);
    sphereGroup->count = src->count;
    sphereGroup->elements = elements;

    for (destElem = sphereGroup->elements, srcElem = src->elements;
         destElem < &sphereGroup->elements[sphereGroup->count]; destElem++, srcElem++) {
        Collider_InitJntSphElement(play, destElem);
        Collider_SetJntSphElement(play, destElem, srcElem);
    }

    return 1;
}

/**
 * Fully initializes a ColliderJntSph using the values in `src`, placing the element array in elements.
 */
s32 Collider_InitAndSetJntSph(struct PlayState* play, ColliderJntSph* sphereGroup, Actor* actor,
                              ColliderJntSphInit* src, ColliderJntSphElement* elements) {
    Collider_InitJntSph(play, sphereGroup);
    Collider_SetJntSph(play, sphereGroup, actor, src, elements);
    return 0;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetJntSphAT(struct PlayState* play, Collider* col) {
    ColliderJntSphElement* element;
    ColliderJntSph* jntSph = (ColliderJntSph*)col;

    Collider_ResetATBase(play, &jntSph->base);

    for (element = jntSph->elements; element < &jntSph->elements[jntSph->count]; element++) {
        Collider_ResetJntSphElementAT(play, element);
    }
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetJntSphAC(struct PlayState* play, Collider* col) {
    ColliderJntSphElement* element;
    ColliderJntSph* jntSph = (ColliderJntSph*)col;

    Collider_ResetACBase(play, &jntSph->base);

    for (element = jntSph->elements; element < &jntSph->elements[jntSph->count]; element++) {
        Collider_ResetJntSphElementAC(play, element);
    }
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetJntSphOC(struct PlayState* play, Collider* col) {
    ColliderJntSphElement* element;
    ColliderJntSph* jntSph = (ColliderJntSph*)col;

    Collider_ResetOCBase(play, &jntSph->base);

    for (element = jntSph->elements; element < &jntSph->elements[jntSph->count]; element++) {
        Collider_ResetJntSphElementOC(play, element);
    }
    return 1;
}

s32 Collider_InitCylinderDim(struct PlayState* play, Cylinder16* dim) {
    static Cylinder16 sDefaultColliderCylinderDim = { 0, 0, 0, { 0, 0, 0 } };

    *dim = sDefaultColliderCylinderDim;
    return 1;
}

s32 Collider_DestroyCylinderDim(struct PlayState* play, Cylinder16* dim) {
    return 1;
}

s32 Collider_SetCylinderDim(struct PlayState* play, Cylinder16* dim, Cylinder16* src) {
    *dim = *src;
    return 1;
}

/**
 * Initializes a ColliderCylinder to default values
 */
s32 Collider_InitCylinder(struct PlayState* play, ColliderCylinder* collider) {
    Collider_InitBase(play, &collider->base);
    Collider_InitElement(play, &collider->info);
    Collider_InitCylinderDim(play, &collider->dim);
    return 1;
}

/**
 * Destroys a ColliderCylinder
 */
s32 Collider_DestroyCylinder(struct PlayState* play, ColliderCylinder* collider) {
    Collider_DestroyBase(play, &collider->base);
    Collider_DestroyElement(play, &collider->info);
    Collider_DestroyCylinderDim(play, &collider->dim);
    return 1;
}

/**
 * Sets up the ColliderCylinder using the values in src and sets it to the actor specified in src. Uses default
 * OC2_TYPE_1 and COLTYPE_0.
 */
s32 Collider_SetCylinderToActor(struct PlayState* play, ColliderCylinder* collider, ColliderCylinderInitToActor* src) {
    Collider_SetBaseToActor(play, &collider->base, &src->base);
    Collider_SetElement(play, &collider->info, &src->info);
    Collider_SetCylinderDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Sets up the ColliderCylinder using the values in src. Uses default OC2_TYPE_1
 */
s32 Collider_SetCylinderType1(struct PlayState* play, ColliderCylinder* collider, Actor* actor,
                              ColliderCylinderInitType1* src) {
    Collider_SetBaseType1(play, &collider->base, actor, &src->base);
    Collider_SetElement(play, &collider->info, &src->info);
    Collider_SetCylinderDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Sets up the ColliderCylinder using the values in src.
 */
s32 Collider_SetCylinder(struct PlayState* play, ColliderCylinder* collider, Actor* actor, ColliderCylinderInit* src) {
    Collider_SetBase(play, &collider->base, actor, &src->base);
    Collider_SetElement(play, &collider->info, &src->info);
    Collider_SetCylinderDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Fully initializes a ColliderCylinder using the values in src.
 */
s32 Collider_InitAndSetCylinder(struct PlayState* play, ColliderCylinder* collider, Actor* actor,
                                ColliderCylinderInit* src) {
    Collider_InitCylinder(play, collider);
    Collider_SetCylinder(play, collider, actor, src);
    return 1;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetCylinderAT(struct PlayState* play, Collider* col) {
    ColliderCylinder* cylinder = (ColliderCylinder*)col;

    Collider_ResetATBase(play, &cylinder->base);
    Collider_ResetATElement(play, &cylinder->info);
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetCylinderAC(struct PlayState* play, Collider* col) {
    ColliderCylinder* cylinder = (ColliderCylinder*)col;

    Collider_ResetACBase(play, &cylinder->base);
    Collider_ResetACElement(play, &cylinder->info);
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetCylinderOC(struct PlayState* play, Collider* col) {
    ColliderCylinder* cylinder = (ColliderCylinder*)col;

    Collider_ResetOCBase(play, &cylinder->base);
    Collider_ResetOCElement(play, &cylinder->info);
    return 1;
}

s32 Collider_InitTrisElementDim(struct PlayState* play, TriNorm* dim) {
    static TriNorm sDefaultColliderTrisElementDim = {
        { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f }, 0.0f },
    };

    *dim = sDefaultColliderTrisElementDim;
    return 1;
}

s32 Collider_DestroyTrisElementDim(struct PlayState* play, TriNorm* dim) {
    return 1;
}

s32 Collider_SetTrisElementDim(struct PlayState* play, TriNorm* dim, ColliderTrisElementDimInit* src) {
    Vec3f* destVtx;
    Vec3f* srcVtx;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 originDist;

    for (destVtx = dim->vtx, srcVtx = &src->vtx[0]; destVtx < &dim->vtx[3]; destVtx++, srcVtx++) {
        *destVtx = *srcVtx;
    }

    Math3D_DefPlane(&src->vtx[0], &src->vtx[1], &src->vtx[2], &nx, &ny, &nz, &originDist);

    dim->plane.normal.x = nx;
    dim->plane.normal.y = ny;
    dim->plane.normal.z = nz;
    dim->plane.originDist = originDist;
    return 1;
}

s32 Collider_InitTrisElement(struct PlayState* play, ColliderTrisElement* element) {
    Collider_InitElement(play, &element->info);
    Collider_InitTrisElementDim(play, &element->dim);
    return 1;
}

s32 Collider_DestroyTrisElement(struct PlayState* play, ColliderTrisElement* element) {
    Collider_DestroyElement(play, &element->info);
    Collider_DestroyTrisElementDim(play, &element->dim);
    return 1;
}

s32 Collider_SetTrisElement(struct PlayState* play, ColliderTrisElement* element, ColliderTrisElementInit* src) {
    Collider_SetElement(play, &element->info, &src->info);
    Collider_SetTrisElementDim(play, &element->dim, &src->dim);
    return 1;
}

s32 Collider_ResetTrisElementAT(struct PlayState* play, ColliderTrisElement* element) {
    Collider_ResetATElement(play, &element->info);
    return 1;
}

s32 Collider_ResetTrisElementAC(struct PlayState* play, ColliderTrisElement* element) {
    Collider_ResetACElement(play, &element->info);
    return 1;
}

s32 Collider_ResetTrisElementOC(struct PlayState* play, ColliderTrisElement* element) {
    Collider_ResetOCElement(play, &element->info);
    return 1;
}

/**
 * Initializes a ColliderTris to default values
 */
s32 Collider_InitTris(struct PlayState* play, ColliderTris* tris) {
    Collider_InitBase(play, &tris->base);
    tris->count = 0;
    tris->elements = NULL;
    return 1;
}

/**
 * Destroys a dynamically allocated ColliderTris
 */
s32 Collider_FreeTris(struct PlayState* play, ColliderTris* tris) {
    ColliderTrisElement* element;

    Collider_DestroyBase(play, &tris->base);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        Collider_DestroyTrisElement(play, element);
    }

    tris->count = 0;
    if (tris->elements != NULL) {
        ZeldaArena_Free(tris->elements);
    }
    tris->elements = NULL;

    return 1;
}

/**
 * Destroys a preallocated ColliderTris
 */
s32 Collider_DestroyTris(struct PlayState* play, ColliderTris* tris) {
    ColliderTrisElement* element;

    Collider_DestroyBase(play, &tris->base);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        Collider_DestroyTrisElement(play, element);
    }
    tris->count = 0;
    tris->elements = NULL;
    return 1;
}

/**
 * Sets up the ColliderTris using the values in src and dynamically allocates the element array. Uses default
 * OC2_TYPE_1.
 */
s32 Collider_SetTrisAllocType1(struct PlayState* play, ColliderTris* tris, Actor* actor, ColliderTrisInitType1* src) {
    ColliderTrisElement* element;
    ColliderTrisElementInit* srcElem;

    Collider_SetBaseType1(play, &tris->base, actor, &src->base);
    tris->count = src->count;
    tris->elements = ZeldaArena_Malloc(tris->count * sizeof(ColliderTrisElement));

    if (tris->elements == NULL) {
        tris->count = 0;
        return 0;
    }

    for (element = tris->elements, srcElem = src->elements; element < &tris->elements[tris->count];
         element++, srcElem++) {
        Collider_InitTrisElement(play, element);
        Collider_SetTrisElement(play, element, srcElem);
    }

    return 1;
}

/**
 * Sets up the ColliderTris using the values in src, placing the element array in elements.
 */
s32 Collider_SetTris(struct PlayState* play, ColliderTris* triGroup, Actor* actor, ColliderTrisInit* src,
                     ColliderTrisElement* tris) {
    ColliderTrisElement* element;
    ColliderTrisElementInit* srcElem;

    Collider_SetBase(play, &triGroup->base, actor, &src->base);
    triGroup->count = src->count;
    triGroup->elements = tris;

    for (element = triGroup->elements, srcElem = src->elements; element < &triGroup->elements[triGroup->count];
         element++, srcElem++) {
        Collider_InitTrisElement(play, element);
        Collider_SetTrisElement(play, element, srcElem);
    }

    return 1;
}

/**
 * Fully initializes a ColliderTris using the values in src, placing the element array in elements.
 */
s32 Collider_InitAndSetTris(struct PlayState* play, ColliderTris* tris, Actor* actor, ColliderTrisInit* src,
                            ColliderTrisElement* elements) {
    Collider_InitTris(play, tris);
    Collider_SetTris(play, tris, actor, src, elements);
    return 0;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetTrisAT(struct PlayState* play, Collider* col) {
    ColliderTrisElement* element;
    ColliderTris* tris = (ColliderTris*)col;

    Collider_ResetATBase(play, &tris->base);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        Collider_ResetTrisElementAT(play, element);
    }
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetTrisAC(struct PlayState* play, Collider* col) {
    ColliderTrisElement* element;
    ColliderTris* tris = (ColliderTris*)col;

    Collider_ResetACBase(play, &tris->base);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        Collider_ResetTrisElementAC(play, element);
    }
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetTrisOC(struct PlayState* play, Collider* col) {
    ColliderTrisElement* element;
    ColliderTris* tris = (ColliderTris*)col;

    Collider_ResetOCBase(play, &tris->base);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        Collider_ResetTrisElementOC(play, element);
    }
    return 1;
}

s32 Collider_InitQuadDim(struct PlayState* play, ColliderQuadDim* dim) {
    static ColliderQuadDim sDefaultColliderQuadDim = {
        { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        { 0, 0, 0 },
        { 0, 0, 0 },
        1.0E38f,
    };

    *dim = sDefaultColliderQuadDim;
    return 1;
}

s32 Collider_DestroyQuadDim(struct PlayState* play, ColliderQuadDim* dim) {
    return 1;
}

s32 Collider_ResetQuadACDist(struct PlayState* play, ColliderQuadDim* dim) {
    dim->acDist = 1.0E38f;
    return 1;
}

void Collider_SetQuadMidpoints(ColliderQuadDim* dim) {
    dim->dcMid.x = (dim->quad[3].x + dim->quad[2].x) * 0.5f;
    dim->dcMid.y = (dim->quad[3].y + dim->quad[2].y) * 0.5f;
    dim->dcMid.z = (dim->quad[3].z + dim->quad[2].z) * 0.5f;
    dim->baMid.x = (dim->quad[1].x + dim->quad[0].x) * 0.5f;
    dim->baMid.y = (dim->quad[1].y + dim->quad[0].y) * 0.5f;
    dim->baMid.z = (dim->quad[1].z + dim->quad[0].z) * 0.5f;
}

s32 Collider_SetQuadDim(struct PlayState* play, ColliderQuadDim* dim, ColliderQuadDimInit* init) {
    dim->quad[0] = init->quad[0];
    dim->quad[1] = init->quad[1];
    dim->quad[2] = init->quad[2];
    dim->quad[3] = init->quad[3];

    Collider_SetQuadMidpoints(dim);
    return 1;
}

/**
 * Initializes a ColliderQuad to default values.
 */
s32 Collider_InitQuad(struct PlayState* play, ColliderQuad* collider) {
    Collider_InitBase(play, &collider->base);
    Collider_InitElement(play, &collider->info);
    Collider_InitQuadDim(play, &collider->dim);
    return 1;
}

/**
 * Destroys a ColliderQuad.
 */
s32 Collider_DestroyQuad(struct PlayState* play, ColliderQuad* collider) {
    Collider_DestroyBase(play, &collider->base);
    Collider_DestroyElement(play, &collider->info);
    Collider_DestroyQuadDim(play, &collider->dim);
    return 1;
}

/**
 * Sets up the ColliderQuad using the values in src. Uses the default OC2_TYPE_1
 */
s32 Collider_SetQuadType1(struct PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInitType1* src) {
    Collider_SetBaseType1(play, &collider->base, actor, &src->base);
    Collider_SetElement(play, &collider->info, &src->info);
    Collider_SetQuadDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Sets up the ColliderQuad using the values in src.
 */
s32 Collider_SetQuad(struct PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src) {
    Collider_SetBase(play, &collider->base, actor, &src->base);
    Collider_SetElement(play, &collider->info, &src->info);
    Collider_SetQuadDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Fully initializes a ColliderQuad using the values in src.
 */
s32 Collider_InitAndSetQuad(struct PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src) {
    Collider_InitQuad(play, collider);
    Collider_SetQuad(play, collider, actor, src);
    return 0;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetQuadAT(struct PlayState* play, Collider* col) {
    ColliderQuad* quad = (ColliderQuad*)col;

    Collider_ResetATBase(play, &quad->base);
    Collider_ResetATElement(play, &quad->info);
    Collider_ResetQuadACDist(play, &quad->dim);
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetQuadAC(struct PlayState* play, Collider* col) {
    ColliderQuad* quad = (ColliderQuad*)col;

    Collider_ResetACBase(play, &quad->base);
    Collider_ResetACElement(play, &quad->info);
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetQuadOC(struct PlayState* play, Collider* col) {
    ColliderQuad* quad = (ColliderQuad*)col;

    Collider_ResetOCBase(play, &quad->base);
    Collider_ResetOCElement(play, &quad->info);
    return 1;
}

/**
 * For quad colliders with TOUCH_NEAREST, resets the previous AC collider it hit if the current element is closer,
 * otherwise returns false. Used on player AT colliders to prevent multiple collisions from registering.
 */
s32 Collider_QuadSetNearestAC(struct PlayState* play, ColliderQuad* quad, Vec3f* hitPos) {
    f32 acDist;
    Vec3f dcMid;

    if (!(quad->info.toucherFlags & TOUCH_NEAREST)) {
        return 1;
    }
    Math_Vec3s_ToVec3f(&dcMid, &quad->dim.dcMid);
    acDist = Math3D_Vec3fDistSq(&dcMid, hitPos);

    if (acDist < quad->dim.acDist) {
        quad->dim.acDist = acDist;

        if (quad->info.atHit != NULL) {
            Collider_ResetACBase(play, quad->info.atHit);
        }
        if (quad->info.atHitElem != NULL) {
            Collider_ResetACElement(play, quad->info.atHitElem);
        }
        return 1;
    } else {
        return 0;
    }
}

/**
 * Initializes a ColliderSphere to default values.
 */
s32 Collider_InitSphere(struct PlayState* play, ColliderSphere* collider) {
    Collider_InitBase(play, &collider->base);
    Collider_InitElement(play, &collider->info);
    Collider_InitJntSphElementDim(play, &collider->dim);
    return 1;
}

/**
 * Destroys a ColliderSphere.
 */
s32 Collider_DestroySphere(struct PlayState* play, ColliderSphere* collider) {
    Collider_DestroyBase(play, &collider->base);
    Collider_DestroyElement(play, &collider->info);
    Collider_DestroyJntSphElementDim(play, &collider->dim);
    return 1;
}

/**
 * Sets up the ColliderSphere using the values in src.
 */
s32 Collider_SetSphere(struct PlayState* play, ColliderSphere* collider, Actor* actor, ColliderSphereInit* src) {
    Collider_SetBase(play, &collider->base, actor, &src->base);
    Collider_SetElement(play, &collider->info, &src->info);
    Collider_SetJntSphElementDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Fully initializes a ColliderSphere using the values in src.
 */
s32 Collider_InitAndSetSphere(struct PlayState* play, ColliderSphere* collider, Actor* actor, ColliderSphereInit* src) {
    Collider_InitSphere(play, collider);
    Collider_SetSphere(play, collider, actor, src);
    return 0;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetSphereAT(struct PlayState* play, Collider* col) {
    ColliderSphere* sphere = (ColliderSphere*)col;

    Collider_ResetATBase(play, &sphere->base);
    Collider_ResetATElement(play, &sphere->info);
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetSphereAC(struct PlayState* play, Collider* col) {
    ColliderSphere* sphere = (ColliderSphere*)col;

    Collider_ResetACBase(play, &sphere->base);
    Collider_ResetACElement(play, &sphere->info);
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetSphereOC(struct PlayState* play, Collider* col) {
    ColliderSphere* sphere = (ColliderSphere*)col;

    Collider_ResetOCBase(play, &sphere->base);
    Collider_ResetOCElement(play, &sphere->info);
    return 1;
}

/**
 * Initializes an OcLine to default values
 */
s32 Collider_InitLine(struct PlayState* play, OcLine* line) {
    static Vec3f sDefaultLinePoint = { 0.0f, 0.0f, 0.0f };

    Math_Vec3f_Copy(&line->line.a, &sDefaultLinePoint);
    Math_Vec3f_Copy(&line->line.b, &sDefaultLinePoint);
    return 1;
}

/**
 * Destroys an OcLine
 */
s32 Collider_DestroyLine(struct PlayState* play, OcLine* line) {
    return 1;
}

/**
 * Sets up an OcLine with endpoints a and b.
 */
s32 Collider_SetLinePoints(struct PlayState* play, OcLine* line, Vec3f* a, Vec3f* b) {
    Math_Vec3f_Copy(&line->line.a, a);
    Math_Vec3f_Copy(&line->line.b, b);
    return 1;
}

/**
 * Sets up an OcLine using the values in src.
 */
s32 Collider_SetLine(struct PlayState* play, OcLine* line, OcLine* src) {
    line->ocFlags = src->ocFlags;
    Collider_SetLinePoints(play, line, &src->line.a, &src->line.b);
    return 1;
}

/**
 * Resets the OcLine's collision flags.
 */
s32 Collider_ResetLineOC(struct PlayState* play, OcLine* line) {
    line->ocFlags &= ~OCLINE_HIT;
    return 1;
}

/**
 * Initializes CollisionCheckContext.
 * Clears all collider arrays, disables SAC, and sets flags for drawing colliders.
 */
void CollisionCheck_InitContext(struct PlayState* play, CollisionCheckContext* colChkCtx) {
    colChkCtx->sacFlags = 0;
    CollisionCheck_ClearContext(play, colChkCtx);
}

void CollisionCheck_DestroyContext(struct PlayState* play, CollisionCheckContext* colChkCtx) {
}

/**
 * Clears all collider lists in CollisionCheckContext when not in SAC mode.
 */
void CollisionCheck_ClearContext(struct PlayState* play, CollisionCheckContext* colChkCtx) {
    Collider** colP;
    OcLine** line;

    if (colChkCtx->sacFlags & SAC_ON) {
        return;
    }

    colChkCtx->colATCount = 0;
    colChkCtx->colACCount = 0;
    colChkCtx->colOCCount = 0;
    colChkCtx->colLineCount = 0;

    for (colP = &colChkCtx->colAT[0]; colP < &colChkCtx->colAT[ARRAY_COUNT(colChkCtx->colAT)]; colP++) {
        *colP = NULL;
    }

    for (colP = &colChkCtx->colAC[0]; colP < &colChkCtx->colAC[ARRAY_COUNT(colChkCtx->colAC)]; colP++) {
        *colP = NULL;
    }

    for (colP = &colChkCtx->colOC[0]; colP < &colChkCtx->colOC[ARRAY_COUNT(colChkCtx->colOC)]; colP++) {
        *colP = NULL;
    }

    for (line = &colChkCtx->colLine[0]; line < &colChkCtx->colLine[ARRAY_COUNT(colChkCtx->colLine)]; line++) {
        *line = NULL;
    }
}

/**
 * Enables SAC, an alternate collision check mode that allows direct management of collider lists.
 */
void CollisionCheck_EnableSAC(struct PlayState* play, CollisionCheckContext* colChkCtx) {
    colChkCtx->sacFlags |= SAC_ON;
}

/**
 * Disables SAC, an alternate collision check mode that allows direct management of collider lists.
 */
void CollisionCheck_DisableSAC(struct PlayState* play, CollisionCheckContext* colChkCtx) {
    colChkCtx->sacFlags &= ~SAC_ON;
}

ColChkResetFunc sATResetFuncs[COLSHAPE_MAX] = {
    Collider_ResetJntSphAT,   // COLSHAPE_JNTSPH
    Collider_ResetCylinderAT, // COLSHAPE_CYLINDER
    Collider_ResetTrisAT,     // COLSHAPE_TRIS
    Collider_ResetQuadAT,     // COLSHAPE_QUAD
    Collider_ResetSphereAT,   // COLSHAPE_SPHERE
};

/**
 * Sets collider as an AT (attack) for the current frame, which will be checked against ACs (attack colliders)
 */
s32 CollisionCheck_SetAT(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    s32 index;

    if (FrameAdvance_IsEnabled(play)) {
        return -1;
    }
    sATResetFuncs[col->shape](play, col);

    if ((col->actor != NULL) && (col->actor->update == NULL)) {
        return -1;
    }
    if (colChkCtx->colATCount >= ARRAY_COUNT(colChkCtx->colAT)) {
        return -1;
    }
    if (colChkCtx->sacFlags & SAC_ON) {
        return -1;
    }
    index = colChkCtx->colATCount;
    colChkCtx->colAT[colChkCtx->colATCount++] = col;

    return index;
}

/**
 * Sets collider as an AT (attack) for the current frame, which will be checked against ACs (attack colliders).
 * If CollisionCheck_SAC is enabled, the collider will be inserted into the list at the specified index, otherwise it
 * will be inserted into the next slot.
 */
s32 CollisionCheck_SetAT_SAC(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col, s32 index) {
    if (FrameAdvance_IsEnabled(play)) {
        return -1;
    }
    sATResetFuncs[col->shape](play, col);

    if ((col->actor != NULL) && (col->actor->update == NULL)) {
        return -1;
    }
    if (colChkCtx->sacFlags & SAC_ON) {
        if (index >= colChkCtx->colATCount) {
            return -1;
        }
        colChkCtx->colAT[index] = col;
    } else {
        if (colChkCtx->colATCount >= ARRAY_COUNT(colChkCtx->colAT)) {
            return -1;
        }
        index = colChkCtx->colATCount;
        colChkCtx->colAT[colChkCtx->colATCount++] = col;
    }
    return index;
}

ColChkResetFunc sACResetFuncs[COLSHAPE_MAX] = {
    Collider_ResetJntSphAC,   // COLSHAPE_JNTSPH
    Collider_ResetCylinderAC, // COLSHAPE_CYLINDER
    Collider_ResetTrisAC,     // COLSHAPE_TRIS
    Collider_ResetQuadAC,     // COLSHAPE_QUAD
    Collider_ResetSphereAC,   // COLSHAPE_SPHERE
};

/**
 * Sets collider as an AC (attack collider) for the current frame, allowing it to detect ATs (attacks)
 */
s32 CollisionCheck_SetAC(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    s32 index;

    if (FrameAdvance_IsEnabled(play)) {
        return -1;
    }
    sACResetFuncs[col->shape](play, col);

    if ((col->actor != NULL) && (col->actor->update == NULL)) {
        return -1;
    }
    if (colChkCtx->colACCount >= ARRAY_COUNT(colChkCtx->colAC)) {
        return -1;
    }
    if (colChkCtx->sacFlags & SAC_ON) {
        return -1;
    }
    index = colChkCtx->colACCount;
    colChkCtx->colAC[colChkCtx->colACCount++] = col;

    return index;
}

/**
 * Sets collider as an AC (attack collider) for the current frame, allowing it to detect ATs (attacks).
 * If CollisionCheck_SAC is enabled, the collider will be inserted into the list at the specified index, otherwise it
 * will be inserted into the next slot
 */
s32 CollisionCheck_SetAC_SAC(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col, s32 index) {
    if (FrameAdvance_IsEnabled(play)) {
        return -1;
    }
    sACResetFuncs[col->shape](play, col);

    if ((col->actor != NULL) && (col->actor->update == NULL)) {
        return -1;
    }
    if (colChkCtx->sacFlags & SAC_ON) {
        if (index >= colChkCtx->colACCount) {
            return -1;
        }
        colChkCtx->colAC[index] = col;
    } else {
        if (colChkCtx->colACCount >= ARRAY_COUNT(colChkCtx->colAC)) {
            return -1;
        }
        index = colChkCtx->colACCount;
        colChkCtx->colAC[colChkCtx->colACCount++] = col;
    }
    return index;
}

static ColChkResetFunc sOCResetFuncs[COLSHAPE_MAX] = {
    Collider_ResetJntSphOC,   // COLSHAPE_JNTSPH
    Collider_ResetCylinderOC, // COLSHAPE_CYLINDER
    Collider_ResetTrisOC,     // COLSHAPE_TRIS
    Collider_ResetQuadOC,     // COLSHAPE_QUAD
    Collider_ResetSphereOC,   // COLSHAPE_SPHERE
};

TriNorm D_801EE6C8;
TriNorm D_801EE700;

/**
 * Sets collider as an OC (object collider) for the current frame, allowing it to detect other OCs.
 */
s32 CollisionCheck_SetOC(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    s32 index;

    if (FrameAdvance_IsEnabled(play)) {
        return -1;
    }
    sOCResetFuncs[col->shape](play, col);

    if ((col->actor != NULL) && (col->actor->update == NULL)) {
        return -1;
    }
    if (colChkCtx->colOCCount >= ARRAY_COUNT(colChkCtx->colOC)) {
        return -1;
    }
    if (colChkCtx->sacFlags & SAC_ON) {
        return -1;
    }
    index = colChkCtx->colOCCount;
    colChkCtx->colOC[colChkCtx->colOCCount++] = col;

    return index;
}

/**
 * Sets collider as an OC (object collider) for the current frame, allowing it to detect other OCs.
 * If CollisionCheck_SAC is enabled, the collider will be inserted into the list at the specified index, otherwise it
 * will be inserted into the next slot.
 */
s32 CollisionCheck_SetOC_SAC(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col, s32 index) {
    if (FrameAdvance_IsEnabled(play)) {
        return -1;
    }
    sOCResetFuncs[col->shape](play, col);

    if ((col->actor != NULL) && (col->actor->update == NULL)) {
        return -1;
    }
    if (colChkCtx->sacFlags & SAC_ON) {
        if (index >= colChkCtx->colOCCount) {
            return -1;
        }
        //! @bug should be colOC
        colChkCtx->colAT[index] = col;
    } else {
        if (colChkCtx->colOCCount >= ARRAY_COUNT(colChkCtx->colOC)) {
            return -1;
        }
        index = colChkCtx->colOCCount;

        colChkCtx->colOC[colChkCtx->colOCCount] = col;
        colChkCtx->colOCCount++;
    }
    return index;
}

/**
 * Sets a line as an OC collider for this frame.
 */
s32 CollisionCheck_SetOCLine(struct PlayState* play, CollisionCheckContext* colChkCtx, OcLine* line) {
    s32 index;

    if (FrameAdvance_IsEnabled(play)) {
        return -1;
    }

    Collider_ResetLineOC(play, line);

    if (colChkCtx->colLineCount >= ARRAY_COUNT(colChkCtx->colLine)) {
        return -1;
    }
    index = colChkCtx->colLineCount;
    colChkCtx->colLine[colChkCtx->colLineCount++] = line;

    return index;
}

/**
 * Skips AT elements that are off.
 */
s32 CollisionCheck_SkipTouch(ColliderElement* elem) {
    if (!(elem->toucherFlags & TOUCH_ON)) {
        return 1;
    }
    return 0;
}

/**
 * Skips AC elements that are off.
 */
s32 CollisionCheck_SkipBump(ColliderElement* elem) {
    if (!(elem->bumperFlags & BUMP_ON)) {
        return 1;
    }
    return 0;
}

/**
 * If the AT element has no dmgFlags in common with the AC element, no collision happens.
 */
s32 CollisionCheck_NoSharedFlags(ColliderElement* atElem, ColliderElement* acElem) {
    if (!(atElem->toucher.dmgFlags & acElem->bumper.dmgFlags)) {
        return true;
    }
    return false;
}

/**
 * Spawns no blood drops.
 * Used by collider types HIT1, HIT3, HIT5, METAL, NONE, WOOD, HARD, and TREE
 */
void CollisionCheck_NoBlood(struct PlayState* play, Collider* col, Vec3f* v) {
}

/**
 * Spawns blue blood drops.
 * Used by collider types HIT0 and HIT8.
 */
void CollisionCheck_BlueBlood(struct PlayState* play, Collider* col, Vec3f* v) {
    static EffectSparkInit D_801EEC00;
    s32 effectIndex;

    D_801EEC00.position.x = v->x;
    D_801EEC00.position.y = v->y;
    D_801EEC00.position.z = v->z;
    D_801EEC00.uDiv = 5;
    D_801EEC00.vDiv = 5;
    D_801EEC00.colorStart[0].r = 10;
    D_801EEC00.colorStart[0].g = 10;
    D_801EEC00.colorStart[0].b = 200;
    D_801EEC00.colorStart[0].a = 255;
    D_801EEC00.colorStart[1].r = 0;
    D_801EEC00.colorStart[1].g = 0;
    D_801EEC00.colorStart[1].b = 128;
    D_801EEC00.colorStart[1].a = 255;
    D_801EEC00.colorStart[2].r = 0;
    D_801EEC00.colorStart[2].g = 0;
    D_801EEC00.colorStart[2].b = 128;
    D_801EEC00.colorStart[2].a = 255;
    D_801EEC00.colorStart[3].r = 0;
    D_801EEC00.colorStart[3].g = 0;
    D_801EEC00.colorStart[3].b = 128;
    D_801EEC00.colorStart[3].a = 255;
    D_801EEC00.colorEnd[0].r = 0;
    D_801EEC00.colorEnd[0].g = 0;
    D_801EEC00.colorEnd[0].b = 32;
    D_801EEC00.colorEnd[0].a = 0;
    D_801EEC00.colorEnd[1].r = 0;
    D_801EEC00.colorEnd[1].g = 0;
    D_801EEC00.colorEnd[1].b = 32;
    D_801EEC00.colorEnd[1].a = 0;
    D_801EEC00.colorEnd[2].r = 0;
    D_801EEC00.colorEnd[2].g = 0;
    D_801EEC00.colorEnd[2].b = 64;
    D_801EEC00.colorEnd[2].a = 0;
    D_801EEC00.colorEnd[3].r = 0;
    D_801EEC00.colorEnd[3].g = 0;
    D_801EEC00.colorEnd[3].b = 64;
    D_801EEC00.colorEnd[3].a = 0;
    D_801EEC00.timer = 0;
    D_801EEC00.duration = 16;
    D_801EEC00.speed = 8.0f;
    D_801EEC00.gravity = -1.0f;

    Effect_Add(play, &effectIndex, EFFECT_SPARK, 0, 1, &D_801EEC00);
}

/**
 * Spawns green blood drops.
 * Used by collider types HIT2 and HIT6. No actor has type HIT2.
 */
void CollisionCheck_GreenBlood(struct PlayState* play, Collider* col, Vec3f* v) {
    static EffectSparkInit D_801EF0C8;
    s32 effectIndex;

    D_801EF0C8.position.x = v->x;
    D_801EF0C8.position.y = v->y;
    D_801EF0C8.position.z = v->z;
    D_801EF0C8.uDiv = 5;
    D_801EF0C8.vDiv = 5;
    D_801EF0C8.colorStart[0].r = 10;
    D_801EF0C8.colorStart[0].g = 200;
    D_801EF0C8.colorStart[0].b = 10;
    D_801EF0C8.colorStart[0].a = 255;
    D_801EF0C8.colorStart[1].r = 0;
    D_801EF0C8.colorStart[1].g = 128;
    D_801EF0C8.colorStart[1].b = 0;
    D_801EF0C8.colorStart[1].a = 255;
    D_801EF0C8.colorStart[2].r = 0;
    D_801EF0C8.colorStart[2].g = 128;
    D_801EF0C8.colorStart[2].b = 0;
    D_801EF0C8.colorStart[2].a = 255;
    D_801EF0C8.colorStart[3].r = 0;
    D_801EF0C8.colorStart[3].g = 128;
    D_801EF0C8.colorStart[3].b = 0;
    D_801EF0C8.colorStart[3].a = 255;
    D_801EF0C8.colorEnd[0].r = 0;
    D_801EF0C8.colorEnd[0].g = 32;
    D_801EF0C8.colorEnd[0].b = 0;
    D_801EF0C8.colorEnd[0].a = 0;
    D_801EF0C8.colorEnd[1].r = 0;
    D_801EF0C8.colorEnd[1].g = 32;
    D_801EF0C8.colorEnd[1].b = 0;
    D_801EF0C8.colorEnd[1].a = 0;
    D_801EF0C8.colorEnd[2].r = 0;
    D_801EF0C8.colorEnd[2].g = 64;
    D_801EF0C8.colorEnd[2].b = 0;
    D_801EF0C8.colorEnd[2].a = 0;
    D_801EF0C8.colorEnd[3].r = 0;
    D_801EF0C8.colorEnd[3].g = 64;
    D_801EF0C8.colorEnd[3].b = 0;
    D_801EF0C8.colorEnd[3].a = 0;
    D_801EF0C8.timer = 0;
    D_801EF0C8.duration = 16;
    D_801EF0C8.speed = 8.0f;
    D_801EF0C8.gravity = -1.0f;
    Effect_Add(play, &effectIndex, EFFECT_SPARK, 0, 1, &D_801EF0C8);
}

TriNorm D_801EF590;
TriNorm D_801EF5C8;

/**
 * Spawns a burst of water.
 * Used by collider type HIT4.
 */
void CollisionCheck_WaterBurst(struct PlayState* play, Collider* col, Vec3f* v) {
    EffectSsSibuki_SpawnBurst(play, v);
    CollisionCheck_SpawnWaterDroplets(play, v);
}

/**
 * Spawns red blood drops.
 * Used by collider type HIT7.
 */
void CollisionCheck_RedBlood(struct PlayState* play, Collider* col, Vec3f* v) {
    CollisionCheck_SpawnRedBlood(play, v);
}

/**
 * Spawns red blood drops.
 */
void CollisionCheck_RedBloodUnused(struct PlayState* play, Collider* col, Vec3f* v) {
    CollisionCheck_SpawnRedBlood(play, v);
}

/**
 * Plays sound effects and displays hitmarks for solid-type AC colliders (METAL, WOOD, HARD, and TREE)
 */
void CollisionCheck_HitSolid(struct PlayState* play, ColliderElement* elem, Collider* col, Vec3f* hitPos) {
    s32 flags = elem->toucherFlags & TOUCH_SFX_NONE;

    if ((flags == TOUCH_SFX_NORMAL) && (col->colType != COLTYPE_METAL)) {
        EffectSsHitmark_SpawnFixedScale(play, 0, hitPos);
        if (col->actor == NULL) {
            Audio_PlaySfx(NA_SE_IT_SHIELD_BOUND);
        } else {
            Audio_PlaySfx_AtPos(&col->actor->projectedPos, NA_SE_IT_SHIELD_BOUND);
        }
    } else if (flags == TOUCH_SFX_NORMAL) {
        EffectSsHitmark_SpawnFixedScale(play, 3, hitPos);
        if (col->actor == NULL) {
            CollisionCheck_SpawnShieldParticlesMetal(play, hitPos);
        } else {
            CollisionCheck_SpawnShieldParticlesMetalSound(play, hitPos, &col->actor->projectedPos);
        }
    } else if (flags == TOUCH_SFX_HARD) {
        EffectSsHitmark_SpawnFixedScale(play, 0, hitPos);
        if (col->actor == NULL) {
            Audio_PlaySfx(NA_SE_IT_SHIELD_BOUND);
        } else {
            Audio_PlaySfx_AtPos(&col->actor->projectedPos, NA_SE_IT_SHIELD_BOUND);
        }
    } else if (flags == TOUCH_SFX_WOOD) {
        EffectSsHitmark_SpawnFixedScale(play, 1, hitPos);
        if (col->actor == NULL) {
            Audio_PlaySfx(NA_SE_IT_REFLECTION_WOOD);
        } else {
            Audio_PlaySfx_AtPos(&col->actor->projectedPos, NA_SE_IT_REFLECTION_WOOD);
        }
    }
}

/**
 * Plays a hit sound effect for AT colliders attached to Player based on the AC element's elemType.
 */
s32 CollisionCheck_SwordHitAudio(Collider* at, ColliderElement* acElem) {
    if ((at->actor != NULL) && (at->actor->category == ACTORCAT_PLAYER)) {
        if (acElem->elemType == ELEMTYPE_UNK0) {
            Audio_PlaySfx_AtPos(&at->actor->projectedPos, NA_SE_IT_SWORD_STRIKE);
        } else if (acElem->elemType == ELEMTYPE_UNK1) {
            Audio_PlaySfx_AtPos(&at->actor->projectedPos, NA_SE_IT_SWORD_STRIKE_HARD);
        } else if (acElem->elemType == ELEMTYPE_UNK2) {
            Audio_PlaySfx_AtPos(&at->actor->projectedPos, 0);
        } else if (acElem->elemType == ELEMTYPE_UNK3) {
            Audio_PlaySfx_AtPos(&at->actor->projectedPos, 0);
        }
    }
    return 1;
}

ColChkBloodFunc sBloodFuncs[] = {
    CollisionCheck_NoBlood,    CollisionCheck_BlueBlood, CollisionCheck_GreenBlood,
    CollisionCheck_WaterBurst, CollisionCheck_RedBlood,  CollisionCheck_RedBloodUnused,
};

HitInfo sHitInfo[] = {
    { BLOOD_BLUE, HIT_WHITE }, { BLOOD_NONE, HIT_DUST },  { BLOOD_GREEN, HIT_DUST },  { BLOOD_NONE, HIT_WHITE },
    { BLOOD_WATER, HIT_NONE }, { BLOOD_NONE, HIT_RED },   { BLOOD_GREEN, HIT_WHITE }, { BLOOD_RED, HIT_WHITE },
    { BLOOD_BLUE, HIT_RED },   { BLOOD_NONE, HIT_SOLID }, { BLOOD_NONE, HIT_NONE },   { BLOOD_NONE, HIT_SOLID },
    { BLOOD_NONE, HIT_SOLID }, { BLOOD_NONE, HIT_WOOD },
};

/**
 * Handles hitmarks, blood, and sound effects for each AC collision, determined by the AC collider's colType
 */
void CollisionCheck_HitEffects(struct PlayState* play, Collider* at, ColliderElement* atElem, Collider* ac,
                               ColliderElement* acElem, Vec3f* hitPos) {
    if (acElem->bumperFlags & BUMP_NO_HITMARK) {
        return;
    }

    if (!(atElem->toucherFlags & TOUCH_AT_HITMARK) && (atElem->toucherFlags & TOUCH_DREW_HITMARK)) {
        return;
    }

    if (ac->actor != NULL) {
        sBloodFuncs[sHitInfo[ac->colType].blood](play, ac, hitPos);
    }
    if (ac->actor != NULL) {
        if (sHitInfo[ac->colType].effect == HIT_SOLID) {
            CollisionCheck_HitSolid(play, atElem, ac, hitPos);
        } else if (sHitInfo[ac->colType].effect == HIT_WOOD) {
            if (at->actor == NULL) {
                CollisionCheck_SpawnShieldParticles(play, hitPos);
                Audio_PlaySfx(NA_SE_IT_REFLECTION_WOOD);
            } else {
                CollisionCheck_SpawnShieldParticlesWood(play, hitPos, &at->actor->projectedPos);
            }
        } else if (sHitInfo[ac->colType].effect != HIT_NONE) {
            EffectSsHitmark_SpawnFixedScale(play, sHitInfo[ac->colType].effect, hitPos);
            if (!(acElem->bumperFlags & BUMP_NO_SWORD_SFX)) {
                CollisionCheck_SwordHitAudio(at, acElem);
            }
        }
    } else {
        EffectSsHitmark_SpawnFixedScale(play, 0, hitPos);
        if (ac->actor == NULL) {
            Audio_PlaySfx(NA_SE_IT_SHIELD_BOUND);
        } else {
            Audio_PlaySfx_AtPos(&ac->actor->projectedPos, NA_SE_IT_SHIELD_BOUND);
        }
    }
}

/**
 * Sets the flags to indicate an attack bounced off an AC_HARD collider.
 */
void CollisionCheck_SetBounce(Collider* at, Collider* ac) {
    at->atFlags |= AT_BOUNCED;
    ac->acFlags |= AC_BOUNCED;
}

/**
 * Performs the AC collision between the AT element and AC element that collided.
 */
s32 CollisionCheck_SetATvsAC(struct PlayState* play, Collider* atCol, ColliderElement* atElem, Vec3f* atPos,
                             Collider* acCol, ColliderElement* acElem, Vec3f* acPos, Vec3f* hitPos) {
    f32 damage;
    u32 effect;

    if (CollisionCheck_GetToucherDamage(atCol, atElem, acCol, acElem) != 0) {
        damage = CollisionCheck_GetDamageAndEffectOnBumper(atCol, atElem, acCol, acElem, &effect);
        if (damage < 1.0f) {
            if (effect == 0) {
                return 0;
            }
        } else if ((CollisionCheck_ApplyBumperDefense(damage, acElem) < 1.0f) && (effect == 0)) {
            return 0;
        }
    }
    if ((acCol->acFlags & AC_HARD) && (atCol->actor != NULL) && (acCol->actor != NULL)) {
        CollisionCheck_SetBounce(atCol, acCol);
    }
    if (!(acElem->bumperFlags & BUMP_NO_AT_INFO)) {
        atCol->atFlags |= AT_HIT;
        atCol->at = acCol->actor;
        atElem->atHit = acCol;
        atElem->toucherFlags |= TOUCH_HIT;
        atElem->atHitElem = acElem;
        if (!(atElem->bumperFlags & BUMP_HIT)) {
            atElem->bumper.hitPos.x = hitPos->x;
            atElem->bumper.hitPos.y = hitPos->y;
            atElem->bumper.hitPos.z = hitPos->z;
        }
        if (atCol->actor != NULL) {
            atCol->actor->colChkInfo.atHitEffect = acElem->bumper.effect;
        }
    }
    if (!(atElem->ocElemFlags & OCELEM_UNK2)) {
        acCol->acFlags |= AC_HIT;
        acCol->ac = atCol->actor;
        acElem->acHit = atCol;
        acElem->acHitElem = atElem;
        acElem->bumperFlags |= BUMP_HIT;
        if (acCol->actor != NULL) {
            acCol->actor->colChkInfo.acHitEffect = atElem->toucher.effect;
        }
        acElem->bumper.hitPos.x = hitPos->x;
        acElem->bumper.hitPos.y = hitPos->y;
        acElem->bumper.hitPos.z = hitPos->z;
    }
    if (!(atElem->toucherFlags & TOUCH_AT_HITMARK) && (acCol->colType != COLTYPE_METAL) &&
        (acCol->colType != COLTYPE_WOOD) && (acCol->colType != COLTYPE_HARD)) {
        acElem->bumperFlags |= BUMP_DRAW_HITMARK;
    } else {
        CollisionCheck_HitEffects(play, atCol, atElem, acCol, acElem, hitPos);
        atElem->toucherFlags |= TOUCH_DREW_HITMARK;
    }
    return 1;
}

void CollisionCheck_TrisAvgPoint(ColliderTrisElement* tri, Vec3f* avg) {
    f32 oneThird = 1.0f / 3;

    avg->x = (tri->dim.vtx[0].x + tri->dim.vtx[1].x + tri->dim.vtx[2].x) * oneThird;
    avg->y = (tri->dim.vtx[0].y + tri->dim.vtx[1].y + tri->dim.vtx[2].y) * oneThird;
    avg->z = (tri->dim.vtx[0].z + tri->dim.vtx[1].z + tri->dim.vtx[2].z) * oneThird;
}

void CollisionCheck_QuadAvgPoint(ColliderQuad* quad, Vec3f* avg) {
    avg->x = (quad->dim.quad[0].x + (quad->dim.quad[1].x + (quad->dim.quad[3].x + quad->dim.quad[2].x))) / 4.0f;
    avg->y = (quad->dim.quad[0].y + (quad->dim.quad[1].y + (quad->dim.quad[3].y + quad->dim.quad[2].y))) / 4.0f;
    avg->z = (quad->dim.quad[0].z + (quad->dim.quad[1].z + (quad->dim.quad[3].z + quad->dim.quad[2].z))) / 4.0f;
}

TriNorm D_801EF600;
TriNorm D_801EF638;

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_JntSphVsJntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                      Collider* acCol) {
    ColliderJntSph* at = (ColliderJntSph*)atCol;
    ColliderJntSphElement* atElem;
    ColliderJntSph* ac = (ColliderJntSph*)acCol;
    ColliderJntSphElement* acElem;
    f32 overlapSize;
    f32 centerDist;

    if ((at->count > 0) && (at->elements != NULL) && (ac->count > 0) && (ac->elements != NULL)) {
        for (atElem = at->elements; atElem < &at->elements[at->count]; atElem++) {
            if (CollisionCheck_SkipTouch(&atElem->info)) {
                continue;
            }

            for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
                if (CollisionCheck_SkipBump(&acElem->info)) {
                    continue;
                }
                if (CollisionCheck_NoSharedFlags(&atElem->info, &acElem->info)) {
                    continue;
                }

                if (Math3D_SphVsSphOverlapCenterDist(&atElem->dim.worldSphere, &acElem->dim.worldSphere, &overlapSize,
                                                     &centerDist)) {
                    f32 acToHit;
                    Vec3f hitPos;
                    Vec3f atPos;
                    Vec3f acPos;

                    Math_Vec3s_ToVec3f(&atPos, &atElem->dim.worldSphere.center);
                    Math_Vec3s_ToVec3f(&acPos, &acElem->dim.worldSphere.center);

                    if (!IS_ZERO(centerDist)) {
                        acToHit = acElem->dim.worldSphere.radius / centerDist;
                        hitPos.x = ((atPos.x - acPos.x) * acToHit) + acPos.x;
                        hitPos.y = ((atPos.y - acPos.y) * acToHit) + acPos.y;
                        hitPos.z = ((atPos.z - acPos.z) * acToHit) + acPos.z;
                    } else {
                        Math_Vec3f_Copy(&hitPos, &atPos);
                    }
                    CollisionCheck_SetATvsAC(play, &at->base, &atElem->info, &atPos, &ac->base, &acElem->info, &acPos,
                                             &hitPos);

                    if (!(ac->base.ocFlags2 & OC2_FIRST_ONLY)) {
                        return;
                    }
                }
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_JntSphVsCyl(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                   Collider* acCol) {
    ColliderJntSph* at = (ColliderJntSph*)atCol;
    ColliderJntSphElement* atElem;
    ColliderCylinder* ac = (ColliderCylinder*)acCol;
    f32 overlapSize;
    f32 centerDist;

    if ((at->count > 0) && (at->elements != NULL) && (ac->dim.radius > 0) && (ac->dim.height > 0)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        for (atElem = at->elements; atElem < &at->elements[at->count]; atElem++) {
            if (CollisionCheck_SkipTouch(&atElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&atElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_SphVsCylOverlapCenterDist(&atElem->dim.worldSphere, &ac->dim, &overlapSize, &centerDist)) {
                Vec3f hitPos;
                Vec3f atPos;
                Vec3f acPos;
                f32 acToHit;

                Math_Vec3s_ToVec3f(&atPos, &atElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&acPos, &ac->dim.pos);
                if (!IS_ZERO(centerDist)) {
                    acToHit = ac->dim.radius / centerDist;
                    if (acToHit <= 1.0f) {
                        hitPos.x = ((atPos.x - acPos.x) * acToHit) + acPos.x;
                        hitPos.y = ((atPos.y - acPos.y) * acToHit) + acPos.y;
                        hitPos.z = ((atPos.z - acPos.z) * acToHit) + acPos.z;
                    } else {
                        Math_Vec3f_Copy(&hitPos, &atPos);
                    }
                } else {
                    Math_Vec3f_Copy(&hitPos, &atPos);
                }
                CollisionCheck_SetATvsAC(play, &at->base, &atElem->info, &atPos, &ac->base, &ac->info, &acPos, &hitPos);
                return;
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_JntSphVsTris(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                    Collider* acCol) {
    ColliderJntSph* at = (ColliderJntSph*)atCol;
    ColliderJntSphElement* atElem;
    ColliderTris* ac = (ColliderTris*)acCol;
    ColliderTrisElement* acElem;
    Vec3f hitPos;

    if ((at->count > 0) && (at->elements != NULL) && (ac->count > 0) && (ac->elements != NULL)) {
        for (atElem = at->elements; atElem < &at->elements[at->count]; atElem++) {
            if (CollisionCheck_SkipTouch(&atElem->info)) {
                continue;
            }
            for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
                if (CollisionCheck_SkipBump(&acElem->info)) {
                    continue;
                }
                if (CollisionCheck_NoSharedFlags(&atElem->info, &acElem->info)) {
                    continue;
                }
                if (Math3D_TriVsSphIntersect(&atElem->dim.worldSphere, &acElem->dim, &hitPos)) {
                    Vec3f atPos;
                    Vec3f acPos;

                    Math_Vec3s_ToVec3f(&atPos, &atElem->dim.worldSphere.center);
                    CollisionCheck_TrisAvgPoint(acElem, &acPos);
                    CollisionCheck_SetATvsAC(play, &at->base, &atElem->info, &atPos, &ac->base, &acElem->info, &acPos,
                                             &hitPos);
                    return;
                }
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_JntSphVsQuad(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                    Collider* acCol) {
    ColliderJntSph* at = (ColliderJntSph*)atCol;
    ColliderQuad* ac = (ColliderQuad*)acCol;
    Vec3f hitPos;
    ColliderJntSphElement* sphElem;

    if ((at->count > 0) && (at->elements != NULL)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        Math3D_TriNorm(&D_801EF590, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
        Math3D_TriNorm(&D_801EF5C8, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

        for (sphElem = at->elements; sphElem < &at->elements[at->count]; sphElem++) {
            if (CollisionCheck_SkipTouch(&sphElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&sphElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_TriVsSphIntersect(&sphElem->dim.worldSphere, &D_801EF590, &hitPos) ||
                Math3D_TriVsSphIntersect(&sphElem->dim.worldSphere, &D_801EF5C8, &hitPos)) {
                Vec3f atPos;
                Vec3f acPos;

                Math_Vec3s_ToVec3f(&atPos, &sphElem->dim.worldSphere.center);
                CollisionCheck_QuadAvgPoint(ac, &acPos);
                CollisionCheck_SetATvsAC(play, &at->base, &sphElem->info, &atPos, &ac->base, &ac->info, &acPos,
                                         &hitPos);
                return;
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_JntSphVsSphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                      Collider* acCol) {
    ColliderJntSph* at = (ColliderJntSph*)atCol;
    ColliderSphere* ac = (ColliderSphere*)acCol;
    ColliderJntSphElement* sphElem;
    f32 overlapSize;
    f32 centerDist;

    if ((at->count > 0) && (at->elements != NULL)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        for (sphElem = at->elements; sphElem < &at->elements[at->count]; sphElem++) {
            if (CollisionCheck_SkipTouch(&sphElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&sphElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_SphVsSphOverlapCenterDist(&sphElem->dim.worldSphere, &ac->dim.worldSphere, &overlapSize,
                                                 &centerDist)) {
                f32 acToHit;
                Vec3f hitPos;
                Vec3f atPos;
                Vec3f acPos;

                Math_Vec3s_ToVec3f(&atPos, &sphElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&acPos, &ac->dim.worldSphere.center);
                if (!IS_ZERO(centerDist)) {
                    acToHit = ac->dim.worldSphere.radius / centerDist;
                    hitPos.x = ((atPos.x - acPos.x) * acToHit) + acPos.x;
                    hitPos.y = ((atPos.y - acPos.y) * acToHit) + acPos.y;
                    hitPos.z = ((atPos.z - acPos.z) * acToHit) + acPos.z;
                } else {
                    Math_Vec3f_Copy(&hitPos, &atPos);
                }
                CollisionCheck_SetATvsAC(play, &at->base, &sphElem->info, &atPos, &ac->base, &ac->info, &acPos,
                                         &hitPos);
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_CylVsJntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                   Collider* acCol) {
    ColliderCylinder* at = (ColliderCylinder*)atCol;
    ColliderJntSph* ac = (ColliderJntSph*)acCol;
    f32 overlapSize;
    f32 centerDist;
    ColliderJntSphElement* sphElem;

    if ((ac->count > 0) && (ac->elements != NULL) && (at->dim.radius > 0) && (at->dim.height > 0)) {
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }
        for (sphElem = ac->elements; sphElem < &ac->elements[ac->count]; sphElem++) {
            if (CollisionCheck_SkipBump(&sphElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&at->info, &sphElem->info)) {
                continue;
            }
            if (Math3D_SphVsCylOverlapCenterDist(&sphElem->dim.worldSphere, &at->dim, &overlapSize, &centerDist)) {
                Vec3f hitPos;
                Vec3f atPos;
                Vec3f acPos;
                f32 acToHit;

                Math_Vec3s_ToVec3f(&atPos, &at->dim.pos);
                Math_Vec3s_ToVec3f(&acPos, &sphElem->dim.worldSphere.center);
                if (!IS_ZERO(centerDist)) {
                    acToHit = sphElem->dim.worldSphere.radius / centerDist;
                    if (acToHit <= 1.0f) {
                        hitPos.x = ((atPos.x - acPos.x) * acToHit) + acPos.x;
                        hitPos.y = ((atPos.y - acPos.y) * acToHit) + acPos.y;
                        hitPos.z = ((atPos.z - acPos.z) * acToHit) + acPos.z;
                    } else {
                        Math_Vec3f_Copy(&hitPos, &atPos);
                    }
                } else {
                    Math_Vec3f_Copy(&hitPos, &atPos);
                }
                CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &sphElem->info, &acPos,
                                         &hitPos);
                if (!(ac->base.ocFlags2 & OC2_FIRST_ONLY)) {
                    break;
                }
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_CylVsCyl(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                Collider* acCol) {
    ColliderCylinder* at = (ColliderCylinder*)atCol;
    ColliderCylinder* ac = (ColliderCylinder*)acCol;
    f32 overlapSize;
    f32 centerDist;

    if ((at->dim.radius > 0) && (at->dim.height > 0) && (ac->dim.radius > 0) && (ac->dim.height > 0)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }
        if (CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
            return;
        }

        if (Math3D_CylVsCylOverlapCenterDist(&at->dim, &ac->dim, &overlapSize, &centerDist)) {
            Vec3f hitPos;
            Vec3f atPos;
            Vec3f acPos;

            Math_Vec3s_ToVec3f(&atPos, &at->dim.pos);
            Math_Vec3s_ToVec3f(&acPos, &ac->dim.pos);
            if (!IS_ZERO(centerDist)) {
                f32 acToHit = ac->dim.radius / centerDist;
                f32 height;

                hitPos.y = (f32)at->dim.pos.y + at->dim.yShift + at->dim.height * 0.5f;
                height = (f32)ac->dim.pos.y + ac->dim.yShift;

                if (hitPos.y < height) {
                    hitPos.y = height;
                } else {
                    height += ac->dim.height;
                    if (hitPos.y > height) {
                        hitPos.y = height;
                    }
                }
                hitPos.x = ((f32)at->dim.pos.x - ac->dim.pos.x) * acToHit + ac->dim.pos.x;
                hitPos.z = ((f32)at->dim.pos.z - ac->dim.pos.z) * acToHit + ac->dim.pos.z;
            } else {
                Math_Vec3s_ToVec3f(&hitPos, &ac->dim.pos);
            }
            CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &hitPos);
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_CylVsTris(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                 Collider* acCol) {
    ColliderCylinder* at = (ColliderCylinder*)atCol;
    ColliderTris* ac = (ColliderTris*)acCol;
    ColliderTrisElement* acElem;
    Vec3f hitPos;

    if ((at->dim.radius > 0) && (at->dim.height > 0) && (ac->count > 0) && (ac->elements != NULL)) {
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }

        for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
            if (CollisionCheck_SkipBump(&acElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&at->info, &acElem->info)) {
                continue;
            }

            if (Math3D_CylTriVsIntersect(&at->dim, &acElem->dim, &hitPos)) {
                Vec3f atPos;
                Vec3f acPos;

                Math_Vec3s_ToVec3f(&atPos, &at->dim.pos);
                CollisionCheck_TrisAvgPoint(acElem, &acPos);
                CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &acElem->info, &acPos, &hitPos);
                return;
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_CylVsQuad(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                 Collider* acCol) {
    ColliderCylinder* at = (ColliderCylinder*)atCol;
    ColliderQuad* ac = (ColliderQuad*)acCol;

    if ((at->dim.height > 0) && (at->dim.radius > 0)) {
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        if (CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
            return;
        }
        Math3D_TriNorm(&D_801EF600, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
        Math3D_TriNorm(&D_801EF638, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

        if (Math3D_CylTriVsIntersect(&at->dim, &D_801EF600, &D_801EDE00)) {
            Vec3f atPos;
            Vec3f acPos;

            Math_Vec3s_ToVec3f(&atPos, &at->dim.pos);
            CollisionCheck_QuadAvgPoint(ac, &acPos);
            CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &D_801EDE00);
        } else if (Math3D_CylTriVsIntersect(&at->dim, &D_801EF638, &D_801EDE00)) {
            Vec3f atPos;
            Vec3f acPos;

            Math_Vec3s_ToVec3f(&atPos, &at->dim.pos);
            CollisionCheck_QuadAvgPoint(ac, &acPos);
            CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &D_801EDE00);
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_CylVsSphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                   Collider* acCol) {
    ColliderCylinder* at = (ColliderCylinder*)atCol;
    ColliderSphere* ac = (ColliderSphere*)acCol;
    f32 overlapSize;
    f32 centerDist;

    if ((at->dim.radius > 0) && (at->dim.height > 0)) {
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        if (CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
            return;
        }

        if (Math3D_SphVsCylOverlapCenterDist(&ac->dim.worldSphere, &at->dim, &overlapSize, &centerDist)) {
            Vec3f hitPos;
            Vec3f atPos;
            Vec3f acPos;
            f32 acToHit;

            Math_Vec3s_ToVec3f(&atPos, &at->dim.pos);
            Math_Vec3s_ToVec3f(&acPos, &ac->dim.worldSphere.center);

            if (!IS_ZERO(centerDist)) {
                acToHit = ac->dim.worldSphere.radius / centerDist;
                if (acToHit <= 1.0f) {
                    hitPos.x = ((atPos.x - acPos.x) * acToHit) + acPos.x;
                    hitPos.y = ((atPos.y - acPos.y) * acToHit) + acPos.y;
                    hitPos.z = ((atPos.z - acPos.z) * acToHit) + acPos.z;
                } else {
                    Math_Vec3f_Copy(&hitPos, &atPos);
                }
            } else {
                Math_Vec3f_Copy(&hitPos, &atPos);
            }
            CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &hitPos);
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_TrisVsJntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                    Collider* acCol) {
    ColliderTris* at = (ColliderTris*)atCol;
    ColliderJntSphElement* acElem;
    ColliderJntSph* ac = (ColliderJntSph*)acCol;
    ColliderTrisElement* atElem;
    Vec3f hitPos;

    if ((ac->count > 0) && (ac->elements != NULL) && (at->count > 0) && (at->elements != NULL)) {
        for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
            if (CollisionCheck_SkipBump(&acElem->info)) {
                continue;
            }
            for (atElem = at->elements; atElem < &at->elements[at->count]; atElem++) {
                if (CollisionCheck_SkipTouch(&atElem->info)) {
                    continue;
                }
                if (CollisionCheck_NoSharedFlags(&atElem->info, &acElem->info)) {
                    continue;
                }
                if (Math3D_TriVsSphIntersect(&acElem->dim.worldSphere, &atElem->dim, &hitPos)) {
                    Vec3f atPos;
                    Vec3f acPos;

                    Math_Vec3s_ToVec3f(&acPos, &acElem->dim.worldSphere.center);
                    CollisionCheck_TrisAvgPoint(atElem, &atPos);
                    CollisionCheck_SetATvsAC(play, &at->base, &atElem->info, &atPos, &ac->base, &acElem->info, &acPos,
                                             &hitPos);

                    if (!(ac->base.ocFlags2 & OC2_FIRST_ONLY)) {
                        return;
                    }
                }
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_TrisVsCyl(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                 Collider* acCol) {
    ColliderTris* at = (ColliderTris*)atCol;
    ColliderCylinder* ac = (ColliderCylinder*)acCol;
    ColliderTrisElement* atElem;

    if ((ac->dim.radius > 0) && (ac->dim.height > 0) && (at->count > 0) && (at->elements != NULL)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        for (atElem = at->elements; atElem < &at->elements[at->count]; atElem++) {
            if (CollisionCheck_SkipTouch(&atElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&atElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_CylTriVsIntersect(&ac->dim, &atElem->dim, &D_801EDE10)) {
                Vec3f atPos;
                Vec3f acPos;

                CollisionCheck_TrisAvgPoint(atElem, &atPos);
                Math_Vec3s_ToVec3f(&acPos, &ac->dim.pos);
                CollisionCheck_SetATvsAC(play, &at->base, &atElem->info, &atPos, &ac->base, &ac->info, &acPos,
                                         &D_801EDE10);
                return;
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_TrisVsTris(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                  Collider* acCol) {
    ColliderTris* at = (ColliderTris*)atCol;
    ColliderTrisElement* atElem;
    ColliderTris* ac = (ColliderTris*)acCol;
    ColliderTrisElement* acElem;

    if ((ac->count > 0) && (ac->elements != NULL) && (at->count > 0) && (at->elements != NULL)) {
        for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
            if (CollisionCheck_SkipBump(&acElem->info)) {
                continue;
            }
            for (atElem = at->elements; atElem < &at->elements[at->count]; atElem++) {
                if (CollisionCheck_SkipTouch(&atElem->info)) {
                    continue;
                }
                if (CollisionCheck_NoSharedFlags(&atElem->info, &acElem->info)) {
                    continue;
                }
                if (Math3D_TriVsTriIntersect(&atElem->dim, &acElem->dim, &D_801EDE20)) {
                    Vec3f atPos;
                    Vec3f acPos;

                    CollisionCheck_TrisAvgPoint(atElem, &atPos);
                    CollisionCheck_TrisAvgPoint(acElem, &acPos);
                    CollisionCheck_SetATvsAC(play, &at->base, &atElem->info, &atPos, &ac->base, &acElem->info, &acPos,
                                             &D_801EDE20);
                    return;
                }
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_TrisVsQuad(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                  Collider* acCol) {
    ColliderTris* at = (ColliderTris*)atCol;
    ColliderQuad* ac = (ColliderQuad*)acCol;
    ColliderTrisElement* atElem;

    if ((at->count > 0) && (at->elements != NULL)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }

        Math3D_TriNorm(&D_801EDE40, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
        Math3D_TriNorm(&D_801EDE78, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

        for (atElem = at->elements; atElem < &at->elements[at->count]; atElem++) {
            if (CollisionCheck_SkipTouch(&atElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&atElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_TriVsTriIntersect(&D_801EDE40, &atElem->dim, &D_801EDE30) ||
                Math3D_TriVsTriIntersect(&D_801EDE78, &atElem->dim, &D_801EDE30)) {
                Vec3f atPos;
                Vec3f acPos;

                CollisionCheck_TrisAvgPoint(atElem, &atPos);
                CollisionCheck_QuadAvgPoint(ac, &acPos);
                CollisionCheck_SetATvsAC(play, &at->base, &atElem->info, &atPos, &ac->base, &ac->info, &acPos,
                                         &D_801EDE30);
                return;
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_TrisVsSphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                    Collider* acCol) {
    ColliderTris* at = (ColliderTris*)atCol;
    ColliderTrisElement* atElem;
    ColliderSphere* ac = (ColliderSphere*)acCol;
    Vec3f hitPos;

    if ((at->count > 0) && (at->elements != NULL)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        for (atElem = at->elements; atElem < &at->elements[at->count]; atElem++) {
            if (CollisionCheck_SkipTouch(&atElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&atElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_TriVsSphIntersect(&ac->dim.worldSphere, &atElem->dim, &hitPos)) {
                Vec3f atPos;
                Vec3f acPos;

                Math_Vec3s_ToVec3f(&acPos, &ac->dim.worldSphere.center);
                CollisionCheck_TrisAvgPoint(atElem, &atPos);
                CollisionCheck_SetATvsAC(play, &at->base, &atElem->info, &atPos, &ac->base, &ac->info, &acPos, &hitPos);
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_QuadVsJntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                    Collider* acCol) {
    ColliderJntSphElement* acElem;
    Vec3f hitPos;
    ColliderQuad* at = (ColliderQuad*)atCol;
    ColliderJntSph* ac = (ColliderJntSph*)acCol;

    if ((ac->count > 0) && (ac->elements != NULL)) {
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }
        Math3D_TriNorm(&D_801EDEC8, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
        Math3D_TriNorm(&D_801EDF00, &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);

        for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
            if (CollisionCheck_SkipBump(&acElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&at->info, &acElem->info)) {
                continue;
            }
            if (Math3D_TriVsSphIntersect(&acElem->dim.worldSphere, &D_801EDEC8, &hitPos) ||
                Math3D_TriVsSphIntersect(&acElem->dim.worldSphere, &D_801EDF00, &hitPos)) {
                Vec3f atPos;
                Vec3f acPos;

                if (!Collider_QuadSetNearestAC(play, at, &hitPos)) {
                    continue;
                }
                Math_Vec3s_ToVec3f(&acPos, &acElem->dim.worldSphere.center);
                CollisionCheck_QuadAvgPoint(at, &atPos);
                CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &acElem->info, &acPos, &hitPos);

                if (!(ac->base.ocFlags2 & OC2_FIRST_ONLY)) {
                    break;
                }
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_QuadVsCyl(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                 Collider* acCol) {
    ColliderQuad* at = (ColliderQuad*)atCol;
    ColliderCylinder* ac = (ColliderCylinder*)acCol;

    if ((ac->dim.height > 0) && (ac->dim.radius > 0)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }
        if (CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
            return;
        }

        Math3D_TriNorm(&D_801EDF58, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
        Math3D_TriNorm(&D_801EDF90, &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);

        if (Math3D_CylTriVsIntersect(&ac->dim, &D_801EDF58, &D_801EDFE0)) {
            if (Collider_QuadSetNearestAC(play, at, &D_801EDFE0)) {
                Vec3f atPos;
                Vec3f acPos;

                CollisionCheck_QuadAvgPoint(at, &atPos);
                Math_Vec3s_ToVec3f(&acPos, &ac->dim.pos);
                CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &D_801EDFE0);
                return;
            }
        }
        if (Math3D_CylTriVsIntersect(&ac->dim, &D_801EDF90, &D_801EDFE0)) {
            if (Collider_QuadSetNearestAC(play, at, &D_801EDFE0)) {
                Vec3f atPos;
                Vec3f acPos;

                CollisionCheck_QuadAvgPoint(at, &atPos);
                Math_Vec3s_ToVec3f(&acPos, &ac->dim.pos);
                CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &D_801EDFE0);
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_QuadVsTris(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                  Collider* acCol) {
    ColliderQuad* at = (ColliderQuad*)atCol;
    ColliderTris* ac = (ColliderTris*)acCol;
    ColliderTrisElement* acElem;

    if ((ac->count > 0) && (ac->elements != NULL)) {
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }

        Math3D_TriNorm(&D_801EE000, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
        Math3D_TriNorm(&D_801EE038, &at->dim.quad[1], &at->dim.quad[0], &at->dim.quad[2]);

        for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
            if (CollisionCheck_SkipBump(&acElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&at->info, &acElem->info)) {
                continue;
            }

            if ((Math3D_TriVsTriIntersect(&D_801EE000, &acElem->dim, &D_801EDFF0)) ||
                (Math3D_TriVsTriIntersect(&D_801EE038, &acElem->dim, &D_801EDFF0))) {
                if (Collider_QuadSetNearestAC(play, at, &D_801EDFF0)) {
                    Vec3f atPos;
                    Vec3f acPos;

                    CollisionCheck_TrisAvgPoint(acElem, &acPos);
                    CollisionCheck_QuadAvgPoint(at, &atPos);
                    CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &acElem->info, &acPos,
                                             &D_801EDFF0);
                    return;
                }
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_QuadVsQuad(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                  Collider* acCol) {
    ColliderQuad* at = (ColliderQuad*)atCol;
    ColliderQuad* ac = (ColliderQuad*)acCol;
    s32 i;
    s32 j;

    if (CollisionCheck_SkipTouch(&at->info)) {
        return;
    }
    if (CollisionCheck_SkipBump(&ac->info)) {
        return;
    }
    if (CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
        return;
    }

    Math3D_TriNorm(&D_801EE0E8[0], &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
    Math3D_TriNorm(&D_801EE0E8[1], &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);
    Math3D_TriNorm(&D_801EE070[0], &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
    Math3D_TriNorm(&D_801EE070[1], &ac->dim.quad[2], &ac->dim.quad[1], &ac->dim.quad[0]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (Math3D_TriVsTriIntersect(&D_801EE0E8[j], &D_801EE070[i], &D_801EE0D8) &&
                Collider_QuadSetNearestAC(play, at, &D_801EE0D8)) {
                Vec3f atPos;
                Vec3f acPos;

                CollisionCheck_QuadAvgPoint(at, &atPos);
                CollisionCheck_QuadAvgPoint(ac, &acPos);
                CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &D_801EE0D8);
                return;
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_QuadVsSphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                    Collider* acCol) {
    ColliderQuad* at = (ColliderQuad*)atCol;
    Vec3f hitPos;
    ColliderSphere* ac = (ColliderSphere*)acCol;

    if (CollisionCheck_SkipTouch(&at->info)) {
        return;
    }
    if (CollisionCheck_SkipBump(&ac->info) || CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
        return;
    }

    Math3D_TriNorm(&D_801EE150, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
    Math3D_TriNorm(&D_801EE188, &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);

    if ((Math3D_TriVsSphIntersect(&ac->dim.worldSphere, &D_801EE150, &hitPos)) ||
        (Math3D_TriVsSphIntersect(&ac->dim.worldSphere, &D_801EE188, &hitPos))) {
        if (Collider_QuadSetNearestAC(play, at, &hitPos)) {
            Vec3f atPos;
            Vec3f acPos;

            Math_Vec3s_ToVec3f(&acPos, &ac->dim.worldSphere.center);
            CollisionCheck_QuadAvgPoint(at, &atPos);
            CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &hitPos);
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_SphereVsJntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                      Collider* acCol) {
    ColliderSphere* at = (ColliderSphere*)atCol;
    ColliderJntSph* ac = (ColliderJntSph*)acCol;
    ColliderJntSphElement* acElem;
    f32 overlapSize;
    f32 centerDist;

    if ((ac->count > 0) && (ac->elements != NULL)) {
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }

        for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
            if (CollisionCheck_SkipBump(&acElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&at->info, &acElem->info)) {
                continue;
            }

            if (Math3D_SphVsSphOverlapCenterDist(&at->dim.worldSphere, &acElem->dim.worldSphere, &overlapSize,
                                                 &centerDist)) {
                f32 acToHit;
                Vec3f hitPos;
                Vec3f atPos;
                Vec3f acPos;

                Math_Vec3s_ToVec3f(&atPos, &at->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&acPos, &acElem->dim.worldSphere.center);
                if (!IS_ZERO(centerDist)) {
                    acToHit = acElem->dim.worldSphere.radius / centerDist;
                    hitPos.x = (atPos.x - acPos.x) * acToHit + acPos.x;
                    hitPos.y = (atPos.y - acPos.y) * acToHit + acPos.y;
                    hitPos.z = (atPos.z - acPos.z) * acToHit + acPos.z;
                } else {
                    Math_Vec3f_Copy(&hitPos, &atPos);
                }
                CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &acElem->info, &acPos, &hitPos);
            }
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_SphereVsCylinder(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                        Collider* acCol) {
    ColliderCylinder* ac = (ColliderCylinder*)acCol;
    ColliderSphere* at = (ColliderSphere*)atCol;
    f32 overlapSize;
    f32 centerDist;

    if (CollisionCheck_SkipTouch(&at->info)) {
        return;
    }
    if (CollisionCheck_SkipBump(&ac->info)) {
        return;
    }
    if (CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
        return;
    }

    if (Math3D_SphVsCylOverlapCenterDist(&at->dim.worldSphere, &ac->dim, &overlapSize, &centerDist)) {
        Vec3f hitPos;
        Vec3f atPos;
        Vec3f acPos;

        Math_Vec3s_ToVec3f(&atPos, &at->dim.worldSphere.center);
        Math_Vec3s_ToVec3f(&acPos, &ac->dim.pos);

        if (!IS_ZERO(centerDist)) {
            f32 acToHit = ac->dim.radius / centerDist;

            if (acToHit <= 1.0f) {
                hitPos.x = (atPos.x - acPos.x) * acToHit + acPos.x;
                hitPos.y = (atPos.y - acPos.y) * acToHit + acPos.y;
                hitPos.z = (atPos.z - acPos.z) * acToHit + acPos.z;
            } else {
                Math_Vec3f_Copy(&hitPos, &atPos);
            }
        } else {
            Math_Vec3f_Copy(&hitPos, &atPos);
        }
        CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &hitPos);
    }

    if (at) {}
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_SphereVsTris(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                    Collider* acCol) {
    ColliderSphere* at = (ColliderSphere*)atCol;
    ColliderTris* ac = (ColliderTris*)acCol;
    ColliderTrisElement* acElem;
    Vec3f hitPos;

    if (CollisionCheck_SkipTouch(&at->info)) {
        return;
    }

    for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
        if (CollisionCheck_SkipBump(&acElem->info)) {
            continue;
        }
        if (CollisionCheck_NoSharedFlags(&at->info, &acElem->info)) {
            continue;
        }
        if (Math3D_TriVsSphIntersect(&at->dim.worldSphere, &acElem->dim, &hitPos)) {
            Vec3f atPos;
            Vec3f acPos;

            Math_Vec3s_ToVec3f(&atPos, &at->dim.worldSphere.center);
            CollisionCheck_TrisAvgPoint(acElem, &acPos);
            CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &acElem->info, &acPos, &hitPos);
            return;
        }
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_SphereVsQuad(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                    Collider* acCol) {
    ColliderSphere* at = (ColliderSphere*)atCol;
    Vec3f hitPos;
    ColliderQuad* ac = (ColliderQuad*)acCol;

    if (CollisionCheck_SkipTouch(&at->info)) {
        return;
    }
    if (CollisionCheck_SkipBump(&ac->info) || CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
        return;
    }

    Math3D_TriNorm(&D_801EE6C8, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
    Math3D_TriNorm(&D_801EE700, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

    if (Math3D_TriVsSphIntersect(&at->dim.worldSphere, &D_801EE6C8, &hitPos) ||
        Math3D_TriVsSphIntersect(&at->dim.worldSphere, &D_801EE700, &hitPos)) {
        Vec3f atPos;
        Vec3f acPos;

        Math_Vec3s_ToVec3f(&atPos, &at->dim.worldSphere.center);
        CollisionCheck_QuadAvgPoint(ac, &acPos);
        CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &hitPos);
    }
}

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_SphereVsSphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol,
                                      Collider* acCol) {
    ColliderSphere* at = (ColliderSphere*)atCol;
    ColliderSphere* ac = (ColliderSphere*)acCol;
    f32 overlapSize;
    f32 centerDist;

    if (CollisionCheck_SkipTouch(&at->info)) {
        return;
    }
    if (CollisionCheck_SkipBump(&ac->info)) {
        return;
    }
    if (CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
        return;
    }

    if (Math3D_SphVsSphOverlapCenterDist(&at->dim.worldSphere, &ac->dim.worldSphere, &overlapSize, &centerDist)) {
        f32 acToHit;
        Vec3f hitPos;
        Vec3f atPos;
        Vec3f acPos;

        Math_Vec3s_ToVec3f(&atPos, &at->dim.worldSphere.center);
        Math_Vec3s_ToVec3f(&acPos, &ac->dim.worldSphere.center);
        if (!IS_ZERO(centerDist)) {
            acToHit = ac->dim.worldSphere.radius / centerDist;
            hitPos.x = (atPos.x - acPos.x) * acToHit + acPos.x;
            hitPos.y = (atPos.y - acPos.y) * acToHit + acPos.y;
            hitPos.z = (atPos.z - acPos.z) * acToHit + acPos.z;
        } else {
            Math_Vec3f_Copy(&hitPos, &atPos);
        }
        CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &hitPos);
    }
}

/**
 * Sets a ColliderJntSph's hit effects
 */
void CollisionCheck_SetJntSphHitFX(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderJntSph* jntSph = (ColliderJntSph*)col;
    ColliderJntSphElement* element;

    for (element = jntSph->elements; element < &jntSph->elements[jntSph->count]; element++) {
        if ((element->info.bumperFlags & BUMP_DRAW_HITMARK) && (element->info.acHitElem != NULL) &&
            !(element->info.acHitElem->toucherFlags & TOUCH_DREW_HITMARK)) {
            Vec3f hitPos;

            Math_Vec3s_ToVec3f(&hitPos, &element->info.bumper.hitPos);
            CollisionCheck_HitEffects(play, element->info.acHit, element->info.acHitElem, &jntSph->base, &element->info,
                                      &hitPos);
            element->info.acHitElem->toucherFlags |= TOUCH_DREW_HITMARK;
            return;
        }
    }
}

/**
 * Sets a ColliderCylinder's hit effects
 */
void CollisionCheck_SetCylHitFX(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderCylinder* cylinder = (ColliderCylinder*)col;

    if ((cylinder->info.bumperFlags & BUMP_DRAW_HITMARK) && (cylinder->info.acHitElem != NULL) &&
        !(cylinder->info.acHitElem->toucherFlags & TOUCH_DREW_HITMARK)) {
        Vec3f hitPos;

        Math_Vec3s_ToVec3f(&hitPos, &cylinder->info.bumper.hitPos);
        CollisionCheck_HitEffects(play, cylinder->info.acHit, cylinder->info.acHitElem, &cylinder->base,
                                  &cylinder->info, &hitPos);
        cylinder->info.acHitElem->toucherFlags |= TOUCH_DREW_HITMARK;
    }
}

/**
 * Sets a ColliderTris's hit effects
 */
void CollisionCheck_SetTrisHitFX(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderTris* tris = (ColliderTris*)col;
    ColliderTrisElement* element;

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        if ((element->info.bumperFlags & BUMP_DRAW_HITMARK) && (element->info.acHitElem != NULL) &&
            !(element->info.acHitElem->toucherFlags & TOUCH_DREW_HITMARK)) {
            Vec3f hitPos;

            Math_Vec3s_ToVec3f(&hitPos, &element->info.bumper.hitPos);
            CollisionCheck_HitEffects(play, element->info.acHit, element->info.acHitElem, &tris->base, &element->info,
                                      &hitPos);
            element->info.acHitElem->toucherFlags |= TOUCH_DREW_HITMARK;
            return;
        }
    }
}

/**
 * Sets a ColliderQuad's hit effects
 */
void CollisionCheck_SetQuadHitFX(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderQuad* quad = (ColliderQuad*)col;

    if ((quad->info.bumperFlags & BUMP_DRAW_HITMARK) && (quad->info.acHitElem != NULL) &&
        !(quad->info.acHitElem->toucherFlags & TOUCH_DREW_HITMARK)) {
        Vec3f hitPos;

        Math_Vec3s_ToVec3f(&hitPos, &quad->info.bumper.hitPos);
        CollisionCheck_HitEffects(play, quad->info.acHit, quad->info.acHitElem, &quad->base, &quad->info, &hitPos);
        quad->info.acHitElem->toucherFlags |= TOUCH_DREW_HITMARK;
    }
}

/**
 * Sets a ColliderSphere's hit effects
 */
void CollisionCheck_SetSphereHitFX(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderSphere* sphere = (ColliderSphere*)col;

    if ((sphere->info.bumperFlags & BUMP_DRAW_HITMARK) && (sphere->info.acHitElem != NULL) &&
        !(sphere->info.acHitElem->toucherFlags & TOUCH_DREW_HITMARK)) {
        Vec3f hitPos;

        Math_Vec3s_ToVec3f(&hitPos, &sphere->info.bumper.hitPos);
        CollisionCheck_HitEffects(play, sphere->info.acHit, sphere->info.acHitElem, &sphere->base, &sphere->info,
                                  &hitPos);
        sphere->info.acHitElem->toucherFlags |= TOUCH_DREW_HITMARK;
    }
}

ColChkApplyFunc sColChkApplyFuncs[COLSHAPE_MAX] = {
    CollisionCheck_SetJntSphHitFX, // COLSHAPE_JNTSPH
    CollisionCheck_SetCylHitFX,    // COLSHAPE_CYLINDER
    CollisionCheck_SetTrisHitFX,   // COLSHAPE_TRIS
    CollisionCheck_SetQuadHitFX,   // COLSHAPE_QUAD
    CollisionCheck_SetSphereHitFX, // COLSHAPE_SPHERE
};

/**
 * Handles hit effects for each AC collider that had an AC collision. Spawns hitmarks and plays sound effects.
 */
void CollisionCheck_SetHitEffects(struct PlayState* play, CollisionCheckContext* colChkCtx) {
    Collider** acColP;

    for (acColP = &colChkCtx->colAC[0]; acColP < &colChkCtx->colAC[colChkCtx->colACCount]; acColP++) {
        Collider* acCol = *acColP;

        if ((acCol != NULL) && (acCol->acFlags & AC_ON)) {
            if ((acCol->actor != NULL) && (acCol->actor->update == NULL)) {
                continue;
            }
            sColChkApplyFuncs[acCol->shape](play, colChkCtx, acCol);
        }
    }
}

ColChkVsFunc sACVsFuncs[COLSHAPE_MAX][COLSHAPE_MAX] = {
    // COLSHAPE_JNTSPH
    {
        CollisionCheck_AC_JntSphVsJntSph, // COLSHAPE_JNTSPH
        CollisionCheck_AC_JntSphVsCyl,    // COLSHAPE_CYLINDER
        CollisionCheck_AC_JntSphVsTris,   // COLSHAPE_TRIS
        CollisionCheck_AC_JntSphVsQuad,   // COLSHAPE_QUAD
        CollisionCheck_AC_JntSphVsSphere  // COLSHAPE_SPHERE
    },
    // COLSHAPE_CYLINDER
    {
        CollisionCheck_AC_CylVsJntSph, // COLSHAPE_JNTSPH
        CollisionCheck_AC_CylVsCyl,    // COLSHAPE_CYLINDER
        CollisionCheck_AC_CylVsTris,   // COLSHAPE_TRIS
        CollisionCheck_AC_CylVsQuad,   // COLSHAPE_QUAD
        CollisionCheck_AC_CylVsSphere  // COLSHAPE_SPHERE
    },
    // COLSHAPE_TRIS
    {
        CollisionCheck_AC_TrisVsJntSph, // COLSHAPE_JNTSPH
        CollisionCheck_AC_TrisVsCyl,    // COLSHAPE_CYLINDER
        CollisionCheck_AC_TrisVsTris,   // COLSHAPE_TRIS
        CollisionCheck_AC_TrisVsQuad,   // COLSHAPE_QUAD
        CollisionCheck_AC_TrisVsSphere  // COLSHAPE_SPHERE
    },
    // COLSHAPE_QUAD
    {
        CollisionCheck_AC_QuadVsJntSph, // COLSHAPE_JNTSPH
        CollisionCheck_AC_QuadVsCyl,    // COLSHAPE_CYLINDER
        CollisionCheck_AC_QuadVsTris,   // COLSHAPE_TRIS
        CollisionCheck_AC_QuadVsQuad,   // COLSHAPE_QUAD
        CollisionCheck_AC_QuadVsSphere  // COLSHAPE_SPHERE
    },
    // COLSHAPE_SPHERE
    {
        CollisionCheck_AC_SphereVsJntSph,   // COLSHAPE_JNTSPH
        CollisionCheck_AC_SphereVsCylinder, // COLSHAPE_CYLINDER
        CollisionCheck_AC_SphereVsTris,     // COLSHAPE_TRIS
        CollisionCheck_AC_SphereVsQuad,     // COLSHAPE_QUAD
        CollisionCheck_AC_SphereVsSphere    // COLSHAPE_SPHERE
    },
};

/**
 * Iterates through all AC colliders, performing AC collisions with the AT collider.
 */
void CollisionCheck_AC(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* atCol) {
    Collider** acColP;

    for (acColP = &colChkCtx->colAC[0]; acColP < &colChkCtx->colAC[colChkCtx->colACCount]; acColP++) {
        Collider* acCol = *acColP;

        if ((acCol != NULL) && (acCol->acFlags & AC_ON)) {
            if ((acCol->actor != NULL) && (acCol->actor->update == NULL)) {
                continue;
            }
            if ((acCol->acFlags & atCol->atFlags & AC_TYPE_ALL) && (atCol != acCol)) {
                if (!(atCol->atFlags & AT_SELF) && (atCol->actor != NULL) && (acCol->actor == atCol->actor)) {
                    continue;
                }
                sACVsFuncs[atCol->shape][acCol->shape](play, colChkCtx, atCol, acCol);
            }
        }
    }
}

/**
 * Iterates through all AT colliders, testing them for AC collisions with each AC collider, setting the info regarding
 * the collision for each AC and AT collider that collided. Then spawns hitmarks and plays sound effects for each
 * successful collision. To collide, an AT collider must share a type (AC_TYPE_PLAYER, AC_TYPE_ENEMY, or AC_TYPE_OTHER)
 * with the AC collider and the toucher and bumper elements that overlapped must share a dmgFlag.
 */
void CollisionCheck_AT(struct PlayState* play, CollisionCheckContext* colChkCtx) {
    Collider** acColP;

    if ((colChkCtx->colATCount == 0) || (colChkCtx->colACCount == 0)) {
        return;
    }

    for (acColP = &colChkCtx->colAT[0]; acColP < &colChkCtx->colAT[colChkCtx->colATCount]; acColP++) {
        Collider* acCol = *acColP;

        if ((acCol != NULL) && (acCol->atFlags & AT_ON)) {
            if ((acCol->actor != NULL) && (acCol->actor->update == NULL)) {
                continue;
            }
            CollisionCheck_AC(play, colChkCtx, acCol);
        }
    }

    CollisionCheck_SetHitEffects(play, colChkCtx);
}

/**
 * Get mass type. Immobile colliders cannot be pushed, while heavy colliders can only be pushed by heavy and immobile
 * colliders.
 */
s32 CollisionCheck_GetMassType(u8 mass) {
    if (mass == MASS_IMMOVABLE) {
        return MASSTYPE_IMMOVABLE;
    }
    if (mass == MASS_HEAVY) {
        return MASSTYPE_HEAVY;
    }
    return MASSTYPE_NORMAL;
}

/**
 * Sets OC collision flags for OC collider overlaps. If both colliders are attached to actors and can push,
 * also performs an elastic collision where both colliders are moved apart in proportion to their masses.
 */
void CollisionCheck_SetOCvsOC(struct PlayState* play, Collider* leftCol, ColliderElement* leftElem, Vec3f* leftPos,
                              Collider* rightCol, ColliderElement* rightElem, Vec3f* rightPos, f32 overlapSize) {
    f32 pad;
    f32 leftDispRatio;
    f32 rightDispRatio;
    f32 xzDist;
    f32 leftMass;
    f32 rightMass;
    f32 totalMass;
    f32 inverseTotalMass;
    f32 xDelta;
    f32 zDelta;
    Actor* leftActor = leftCol->actor;
    Actor* rightActor = rightCol->actor;
    s32 leftMassType;
    s32 rightMassType;

    leftCol->ocFlags1 |= OC1_HIT;
    leftCol->oc = rightActor;
    leftElem->ocElemFlags |= OCELEM_HIT;
    if (rightCol->ocFlags2 & OC2_TYPE_PLAYER) {
        leftCol->ocFlags2 |= OC2_HIT_PLAYER;
    }

    rightCol->ocFlags1 |= OC1_HIT;
    rightCol->oc = leftActor;
    rightElem->ocElemFlags |= OCELEM_HIT;
    if (leftCol->ocFlags2 & OC2_TYPE_PLAYER) {
        rightCol->ocFlags2 |= OC2_HIT_PLAYER;
    }

    if ((leftActor == NULL) || (rightActor == NULL) || (leftCol->ocFlags1 & OC1_NO_PUSH) ||
        (rightCol->ocFlags1 & OC1_NO_PUSH)) {
        return;
    }

    rightMassType = CollisionCheck_GetMassType(leftActor->colChkInfo.mass);
    leftMassType = CollisionCheck_GetMassType(rightActor->colChkInfo.mass);
    leftMass = leftActor->colChkInfo.mass;
    rightMass = rightActor->colChkInfo.mass;
    totalMass = leftMass + rightMass;

    if (IS_ZERO(totalMass)) {
        leftMass = rightMass = 1.0f;
        totalMass = 2.0f;
    }
    xDelta = rightPos->x - leftPos->x;
    zDelta = rightPos->z - leftPos->z;

    xzDist = sqrtf(SQ(xDelta) + SQ(zDelta));

    if (rightMassType == MASSTYPE_IMMOVABLE) {
        if (leftMassType == MASSTYPE_IMMOVABLE) {
            return;
        } else {
            leftDispRatio = 0;
            rightDispRatio = 1;
        }
    } else if (rightMassType == MASSTYPE_HEAVY) {
        if (leftMassType == MASSTYPE_IMMOVABLE) {
            leftDispRatio = 1;
            rightDispRatio = 0;
        } else if (leftMassType == MASSTYPE_HEAVY) {
            leftDispRatio = 0.5f;
            rightDispRatio = 0.5f;
        } else {
            leftDispRatio = 0;
            rightDispRatio = 1;
        }
    } else {
        if (leftMassType == MASSTYPE_NORMAL) {
            inverseTotalMass = 1.0f / totalMass;
            leftDispRatio = rightMass * inverseTotalMass;
            rightDispRatio = leftMass * inverseTotalMass;
        } else {
            leftDispRatio = 1;
            rightDispRatio = 0;
        }
    }

    if (!IS_ZERO(xzDist)) {
        xDelta *= overlapSize / xzDist;
        zDelta *= overlapSize / xzDist;
        leftActor->colChkInfo.displacement.x += -xDelta * leftDispRatio;
        leftActor->colChkInfo.displacement.z += -zDelta * leftDispRatio;
        rightActor->colChkInfo.displacement.x += xDelta * rightDispRatio;
        rightActor->colChkInfo.displacement.z += zDelta * rightDispRatio;
    } else if (overlapSize != 0.0f) {
        leftActor->colChkInfo.displacement.x += -overlapSize * leftDispRatio;
        rightActor->colChkInfo.displacement.x += overlapSize * rightDispRatio;
    } else {
        leftActor->colChkInfo.displacement.x += -leftDispRatio;
        rightActor->colChkInfo.displacement.x += rightDispRatio;
    }
}

/**
 * OC overlap check for two JntSphs
 */
void CollisionCheck_OC_JntSphVsJntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* leftCol,
                                      Collider* rightCol) {
    ColliderJntSph* left = (ColliderJntSph*)leftCol;
    ColliderJntSph* right = (ColliderJntSph*)rightCol;
    ColliderJntSphElement* leftElem;
    ColliderJntSphElement* rightElem;
    f32 overlapSize;

    if ((left->count > 0) && (left->elements != NULL) && (right->count > 0) && (right->elements != NULL) &&
        (left->base.ocFlags1 & OCELEM_ON) && (right->base.ocFlags1 & OCELEM_ON)) {

        for (leftElem = left->elements; leftElem < &left->elements[left->count]; leftElem++) {
            if (!(leftElem->info.ocElemFlags & OCELEM_ON)) {
                continue;
            }
            for (rightElem = right->elements; rightElem < &right->elements[right->count]; rightElem++) {
                if (!(rightElem->info.ocElemFlags & OCELEM_ON)) {
                    continue;
                }
                if (Math3D_SphVsSphOverlap(&leftElem->dim.worldSphere, &rightElem->dim.worldSphere, &overlapSize)) {
                    Vec3f leftPos;
                    Vec3f rightPos;

                    Math_Vec3s_ToVec3f(&leftPos, &leftElem->dim.worldSphere.center);
                    Math_Vec3s_ToVec3f(&rightPos, &rightElem->dim.worldSphere.center);
                    CollisionCheck_SetOCvsOC(play, &left->base, &leftElem->info, &leftPos, &right->base,
                                             &rightElem->info, &rightPos, overlapSize);
                }
            }
        }
    }
}

/**
 * OC overlap check for a JntSph and Cylinder
 */
void CollisionCheck_OC_JntSphVsCyl(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* leftCol,
                                   Collider* rightCol) {
    ColliderJntSph* left = (ColliderJntSph*)leftCol;
    ColliderCylinder* right = (ColliderCylinder*)rightCol;
    ColliderJntSphElement* leftElem;
    f32 overlapSize;

    if ((left->count > 0) && (left->elements != NULL) && (left->base.ocFlags1 & OCELEM_ON) &&
        (right->base.ocFlags1 & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {

        for (leftElem = left->elements; leftElem < &left->elements[left->count]; leftElem++) {
            if (!(leftElem->info.ocElemFlags & OCELEM_ON)) {
                continue;
            }
            if (Math3D_SphVsCylOverlap(&leftElem->dim.worldSphere, &right->dim, &overlapSize)) {
                Vec3f leftPos;
                Vec3f rightPos;

                Math_Vec3s_ToVec3f(&leftPos, &leftElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&rightPos, &right->dim.pos);
                CollisionCheck_SetOCvsOC(play, &left->base, &leftElem->info, &leftPos, &right->base, &right->info,
                                         &rightPos, overlapSize);
            }
        }
    }
}

/**
 * OC overlap check for a JntSph and Sphere
 */
void CollisionCheck_OC_JntSphVsSphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* leftCol,
                                      Collider* rightCol) {
    ColliderJntSph* left = (ColliderJntSph*)leftCol;
    ColliderSphere* right = (ColliderSphere*)rightCol;
    ColliderJntSphElement* leftElem;
    f32 overlapSize;

    if ((left->count > 0) && (left->elements != NULL) && (left->base.ocFlags1 & OCELEM_ON) &&
        (right->base.ocFlags1 & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {

        for (leftElem = left->elements; leftElem < &left->elements[left->count]; leftElem++) {
            if (!(leftElem->info.ocElemFlags & OCELEM_ON)) {
                continue;
            }
            if (Math3D_SphVsSphOverlap(&leftElem->dim.worldSphere, &right->dim.worldSphere, &overlapSize)) {
                Vec3f leftPos;
                Vec3f rightPos;

                Math_Vec3s_ToVec3f(&leftPos, &leftElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&rightPos, &right->dim.worldSphere.center);
                CollisionCheck_SetOCvsOC(play, &left->base, &leftElem->info, &leftPos, &right->base, &right->info,
                                         &rightPos, overlapSize);
            }
        }
    }
}

/**
 * OC overlap check for a Cylinder and JntSph
 */
void CollisionCheck_OC_CylVsJntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* leftCol,
                                   Collider* rightCol) {
    CollisionCheck_OC_JntSphVsCyl(play, colChkCtx, rightCol, leftCol);
}

/**
 * OC overlap check for two Cylinders
 */
void CollisionCheck_OC_CylVsCyl(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* leftCol,
                                Collider* rightCol) {
    ColliderCylinder* left = (ColliderCylinder*)leftCol;
    ColliderCylinder* right = (ColliderCylinder*)rightCol;
    f32 overlapSize;

    if ((left->base.ocFlags1 & OCELEM_ON) && (right->base.ocFlags1 & OCELEM_ON) &&
        (left->info.ocElemFlags & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {
        if (Math3D_CylVsCylOverlap(&left->dim, &right->dim, &overlapSize)) {
            Vec3f leftPos;
            Vec3f rightPos;

            Math_Vec3s_ToVec3f(&leftPos, &left->dim.pos);
            Math_Vec3s_ToVec3f(&rightPos, &right->dim.pos);
            CollisionCheck_SetOCvsOC(play, &left->base, &left->info, &leftPos, &right->base, &right->info, &rightPos,
                                     overlapSize);
        }
    }
}

/**
 * OC overlap check for a Cylinder and Sphere
 */
void CollisionCheck_OC_CylVsSphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* leftCol,
                                   Collider* rightCol) {
    ColliderCylinder* left = (ColliderCylinder*)leftCol;
    ColliderSphere* right = (ColliderSphere*)rightCol;
    f32 overlapSize;

    if ((left->base.ocFlags1 & OCELEM_ON) && (left->info.ocElemFlags & OCELEM_ON) &&
        (right->base.ocFlags1 & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {
        if (Math3D_SphVsCylOverlap(&right->dim.worldSphere, &left->dim, &overlapSize)) {
            Vec3f leftPos;
            Vec3f rightPos;

            Math_Vec3s_ToVec3f(&leftPos, &left->dim.pos);
            Math_Vec3s_ToVec3f(&rightPos, &right->dim.worldSphere.center);
            CollisionCheck_SetOCvsOC(play, &left->base, &left->info, &leftPos, &right->base, &right->info, &rightPos,
                                     overlapSize);
        }
    }
}

/**
 * OC overlap check for a Sphere and JntSph
 */
void CollisionCheck_OC_SphereVsJntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* leftCol,
                                      Collider* rightCol) {
    CollisionCheck_OC_JntSphVsSphere(play, colChkCtx, rightCol, leftCol);
}

/**
 * OC overlap check for a Sphere and Cylinder
 */
void CollisionCheck_OC_SphereVsCyl(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* leftCol,
                                   Collider* rightCol) {
    CollisionCheck_OC_CylVsSphere(play, colChkCtx, rightCol, leftCol);
}

/**
 * OC overlap check for two Spheres
 */
void CollisionCheck_OC_SphereVsSphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* leftCol,
                                      Collider* rightCol) {
    ColliderSphere* left = (ColliderSphere*)leftCol;
    ColliderSphere* right = (ColliderSphere*)rightCol;
    f32 overlapSize;

    if ((left->base.ocFlags1 & OCELEM_ON) && (left->info.ocElemFlags & OCELEM_ON) &&
        (right->base.ocFlags1 & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {
        if (Math3D_SphVsSphOverlap(&left->dim.worldSphere, &right->dim.worldSphere, &overlapSize)) {
            Vec3f leftPos;
            Vec3f rightPos;

            Math_Vec3s_ToVec3f(&leftPos, &left->dim.worldSphere.center);
            Math_Vec3s_ToVec3f(&rightPos, &right->dim.worldSphere.center);
            CollisionCheck_SetOCvsOC(play, &left->base, &left->info, &leftPos, &right->base, &right->info, &rightPos,
                                     overlapSize);
        }
    }
}

/**
 *  Skip any OC colliders that are off
 */
s32 CollisionCheck_SkipOC(Collider* col) {
    if (!(col->ocFlags1 & OCELEM_ON)) {
        return 1;
    }
    return 0;
}

/**
 * Checks for OC compatibility. There are three conditions:
 * First, each collider must have an OC flag corresponding to the other's OC type.
 * Second, OC2_UNK1 and OC2_UNK2 can't collide with each other (has something to do with horses?)
 * Third, the colliders can't collide if they belong to the same actor
 */
s32 CollisionCheck_Incompatible(Collider* leftCol, Collider* rightCol) {
    if (!(leftCol->ocFlags1 & rightCol->ocFlags2 & OC1_TYPE_ALL) ||
        !(leftCol->ocFlags2 & rightCol->ocFlags1 & OC1_TYPE_ALL) ||
        ((leftCol->ocFlags2 & OC2_UNK1) && (rightCol->ocFlags2 & OC2_UNK2)) ||
        ((rightCol->ocFlags2 & OC2_UNK1) && (leftCol->ocFlags2 & OC2_UNK2))) {
        return 1;
    }
    if (leftCol->actor == rightCol->actor) {
        return 1;
    }
    return 0;
}

ColChkVsFunc sOCVsFuncs[COLSHAPE_MAX][COLSHAPE_MAX] = {
    // COLSHAPE_JNTSPH
    {
        CollisionCheck_OC_JntSphVsJntSph, // COLSHAPE_JNTSPH
        CollisionCheck_OC_JntSphVsCyl,    // COLSHAPE_CYLINDER
        NULL,                             // COLSHAPE_TRIS
        NULL,                             // COLSHAPE_QUAD
        CollisionCheck_OC_JntSphVsSphere  // COLSHAPE_SPHERE
    },
    // COLSHAPE_CYLINDER
    {
        CollisionCheck_OC_CylVsJntSph, // COLSHAPE_JNTSPH
        CollisionCheck_OC_CylVsCyl,    // COLSHAPE_CYLINDER
        NULL,                          // COLSHAPE_TRIS
        NULL,                          // COLSHAPE_QUAD
        CollisionCheck_OC_CylVsSphere  // COLSHAPE_SPHERE
    },
    // COLSHAPE_TRIS
    {
        NULL, // COLSHAPE_JNTSPH
        NULL, // COLSHAPE_CYLINDER
        NULL, // COLSHAPE_TRIS
        NULL, // COLSHAPE_QUAD
        NULL  // COLSHAPE_SPHERE
    },
    // COLSHAPE_QUAD
    {
        NULL, // COLSHAPE_JNTSPH
        NULL, // COLSHAPE_CYLINDER
        NULL, // COLSHAPE_TRIS
        NULL, // COLSHAPE_QUAD
        NULL  // COLSHAPE_SPHERE
    },
    // COLSHAPE_SPHERE
    {
        CollisionCheck_OC_SphereVsJntSph, // COLSHAPE_JNTSPH
        CollisionCheck_OC_SphereVsCyl,    // COLSHAPE_CYLINDER
        NULL,                             // COLSHAPE_TRIS
        NULL,                             // COLSHAPE_QUAD
        CollisionCheck_OC_SphereVsSphere  // COLSHAPE_SPHERE
    },
};

/**
 * Iterates through all OC colliders and collides them with all subsequent OC colliders on the list. During an OC
 * collision, colliders with overlapping elements move away from each other so that their elements no longer overlap.
 * The relative amount each collider is pushed is determined by the collider's mass. Only JntSph, Cylinder and Sphere
 * colliders can collide, and each collider must have the OC flag corresponding to the other's OC type. Additionally,
 * OC2_UNK1 cannot collide with OC2_UNK2, nor can two colliders that share an actor.
 */
void CollisionCheck_OC(struct PlayState* play, CollisionCheckContext* colChkCtx) {
    Collider** leftColP;
    Collider** rightColP;
    ColChkVsFunc vsFunc;

    for (leftColP = colChkCtx->colOC; leftColP < colChkCtx->colOC + colChkCtx->colOCCount; leftColP++) {
        if ((*leftColP == NULL) || CollisionCheck_SkipOC(*leftColP)) {
            continue;
        }
        for (rightColP = leftColP + 1; rightColP < colChkCtx->colOC + colChkCtx->colOCCount; rightColP++) {
            if ((*rightColP == NULL) || CollisionCheck_SkipOC(*rightColP) ||
                CollisionCheck_Incompatible(*leftColP, *rightColP)) {
                continue;
            }
            vsFunc = sOCVsFuncs[(*leftColP)->shape][(*rightColP)->shape];
            if (vsFunc == NULL) {
                continue;
            }
            vsFunc(play, colChkCtx, *leftColP, *rightColP);
        }
    }
}

/**
 * Initializes CollisionCheckInfo to default values
 */
void CollisionCheck_InitInfo(CollisionCheckInfo* info) {
    static CollisionCheckInfo sDefaultColChkInfo = {
        NULL, { 0.0f, 0.0f, 0.0f }, 10, 10, 0, MASS_IMMOVABLE, 8, 0, 0, 0, 0,
    };

    *info = sDefaultColChkInfo;
}

/**
 * Resets ColisionCheckInfo fields other than DamageTable, mass, and dim.
 */
void CollisionCheck_ResetDamage(CollisionCheckInfo* info) {
    info->damage = 0;
    info->damageEffect = 0;
    info->atHitEffect = 0;
    info->acHitEffect = 0;
    info->displacement.x = info->displacement.y = info->displacement.z = 0.0f;
}

/**
 * Sets up CollisionCheckInfo using the values in init. Does not set a damage table or the unused unk_14.
 */
void CollisionCheck_SetInfoNoDamageTable(CollisionCheckInfo* info, CollisionCheckInfoInit* init) {
    info->health = init->health;
    info->cylRadius = init->cylRadius;
    info->cylHeight = init->cylHeight;
    info->mass = init->mass;
}

/**
 * Sets up CollisionCheckInfo using the values in init. Does not set the unused unk_14
 */
void CollisionCheck_SetInfo(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit* init) {
    info->health = init->health;
    info->damageTable = damageTable;
    info->cylRadius = init->cylRadius;
    info->cylHeight = init->cylHeight;
    info->mass = init->mass;
}

/**
 * Sets up CollisionCheckInfo using the values in init. Sets the unused unk_14
 */
void CollisionCheck_SetInfo2(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit2* init) {
    info->health = init->health;
    info->damageTable = damageTable;
    info->cylRadius = init->cylRadius;
    info->cylHeight = init->cylHeight;
    info->cylYShift = init->cylYShift;
    info->mass = init->mass;
}

/**
 * Sets up CollisionCheckInfo using the values in Init and a preset damage table. Sets the unused unk_14.
 */
void CollisionCheck_SetInfoGetDamageTable(CollisionCheckInfo* info, s32 index, CollisionCheckInfoInit2* init) {
    CollisionCheck_SetInfo2(info, DamageTable_Get(index), init);
}

/**
 * Apply AC damage effect
 */
void CollisionCheck_ApplyDamage(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col,
                                ColliderElement* elem) {
    f32 damage;
    f32 finalDamage = 0.0f;
    s32 pad;
    Collider* atCol;
    ColliderElement* atElem;
    s32 pad1;
    u32 effect;

    if ((col->actor == NULL) || !(col->acFlags & AC_HIT)) {
        return;
    }
    if (!(elem->bumperFlags & BUMP_HIT) || (elem->bumperFlags & BUMP_NO_DAMAGE)) {
        return;
    }

    atCol = elem->acHit;
    atElem = elem->acHitElem;

    if ((atCol != NULL) && (atElem != NULL) && (col != NULL) && (elem != NULL)) {
        damage = CollisionCheck_GetDamageAndEffectOnBumper(atCol, atElem, col, elem, &effect);

        if (CollisionCheck_GetToucherDamage(atCol, atElem, col, elem) != 0) {
            if (damage < 1.0f) {
                finalDamage = 0.0f;
                if (effect == 0) {
                    return;
                }
            } else {
                finalDamage = CollisionCheck_ApplyBumperDefense(damage, elem);
                if ((finalDamage < 1.0f) && (effect == 0)) {
                    return;
                }
            }
        }
        if (col->actor->colChkInfo.damageTable != NULL) {
            col->actor->colChkInfo.damageEffect = effect;
        }
        if (!(col->acFlags & AC_HARD) || ((col->acFlags & AC_HARD) && (atElem->toucher.dmgFlags == 0x20000000))) {
            if (col->actor->colChkInfo.damage < finalDamage) {
                col->actor->colChkInfo.damage = finalDamage;
            }
        }
    }
}

/**
 * Apply ColliderJntSph AC damage effect
 */
void CollisionCheck_ApplyDamageJntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderJntSph* jntSph = (ColliderJntSph*)col;
    s32 i;

    if ((jntSph->count > 0) && (jntSph->elements != NULL)) {
        for (i = 0; i < jntSph->count; i++) {
            CollisionCheck_ApplyDamage(play, colChkCtx, &jntSph->base, &jntSph->elements[i].info);
        }
    }
}

/**
 * Apply ColliderCylinder AC damage effect
 */
void CollisionCheck_ApplyDamageCyl(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderCylinder* cylinder = (ColliderCylinder*)col;

    CollisionCheck_ApplyDamage(play, colChkCtx, &cylinder->base, &cylinder->info);
}

/**
 * Apply ColliderTris AC damage effect
 */
void CollisionCheck_ApplyDamageTris(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderTris* tris = (ColliderTris*)col;
    s32 i;

    // unlike sphere groups above, tri groups are not guarded against
    //  tris->elements being NULL
    for (i = 0; i < tris->count; i++) {
        CollisionCheck_ApplyDamage(play, colChkCtx, &tris->base, &tris->elements[i].info);
    }
}

/**
 * Apply ColliderQuad AC damage effect
 */
void CollisionCheck_ApplyDamageQuad(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderQuad* quad = (ColliderQuad*)col;

    CollisionCheck_ApplyDamage(play, colChkCtx, &quad->base, &quad->info);
}

/**
 * Apply ColliderSphere AC damage effect
 */
void CollisionCheck_ApplyDamageSphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col) {
    ColliderSphere* sphere = (ColliderSphere*)col;

    CollisionCheck_ApplyDamage(play, colChkCtx, &sphere->base, &sphere->info);
}

ColChkApplyFunc sApplyDamageFuncs[COLSHAPE_MAX] = {
    CollisionCheck_ApplyDamageJntSph, // COLSHAPE_JNTSPH
    CollisionCheck_ApplyDamageCyl,    // COLSHAPE_CYLINDER
    CollisionCheck_ApplyDamageTris,   // COLSHAPE_TRIS
    CollisionCheck_ApplyDamageQuad,   // COLSHAPE_QUAD
    CollisionCheck_ApplyDamageSphere, // COLSHAPE_SPHERE
};

/**
 * For all AC colliders, sets any damage effects from collisions with AT colliders to their corresponding actor's
 * CollisionCheckInfo.
 */
void CollisionCheck_Damage(struct PlayState* play, CollisionCheckContext* colChkCtx) {
    s32 i;

    for (i = 0; i < colChkCtx->colACCount; i++) {
        Collider* col = colChkCtx->colAC[i];

        if (col == NULL) {
            continue;
        }
        if (col->acFlags & AC_NO_DAMAGE) {
            continue;
        }
        sApplyDamageFuncs[col->shape](play, colChkCtx, col);
    }
}

/**
 * Checks if the line segment ab intersects any of the ColliderJntSph's elements
 */
s32 CollisionCheck_LineOC_JntSph(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col, Vec3f* a,
                                 Vec3f* b) {
    ColliderJntSph* jntSph = (ColliderJntSph*)col;
    s32 i;

    for (i = 0; i < jntSph->count; i++) {
        ColliderJntSphElement* element = &jntSph->elements[i];

        if (!(element->info.ocElemFlags & OCELEM_ON)) {
            continue;
        }

        D_801EDEB0.a = *a;
        D_801EDEB0.b = *b;
        if (Math3D_LineVsSph(&element->dim.worldSphere, &D_801EDEB0)) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if the line segment ab intersects the ColliderCylinder
 */
s32 CollisionCheck_LineOC_Cyl(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col, Vec3f* a,
                              Vec3f* b) {
    ColliderCylinder* cylinder = (ColliderCylinder*)col;

    if (!(cylinder->info.ocElemFlags & OCELEM_ON)) {
        return false;
    }

    if (Math3D_CylVsLineSeg(&cylinder->dim, a, b, &D_801EDF38, &D_801EDF48)) {
        return true;
    }

    return false;
}

/**
 * Checks if the line segment ab intersects the ColliderSphere
 */
s32 CollisionCheck_LineOC_Sphere(struct PlayState* play, CollisionCheckContext* colChkCtx, Collider* col, Vec3f* a,
                                 Vec3f* b) {
    ColliderSphere* sphere = (ColliderSphere*)col;

    if (!(sphere->info.ocElemFlags & OCELEM_ON)) {
        return false;
    }

    D_801EDFC8.a = *a;
    D_801EDFC8.b = *b;
    if (Math3D_LineVsSph(&sphere->dim.worldSphere, &D_801EDFC8)) {
        return true;
    }

    return false;
}

static ColChkLineFunc sOCLineCheckFuncs[COLSHAPE_MAX] = {
    CollisionCheck_LineOC_JntSph, // COLSHAPE_JNTSPH
    CollisionCheck_LineOC_Cyl,    // COLSHAPE_CYLINDER
    NULL,                         // COLSHAPE_TRIS
    NULL,                         // COLSHAPE_QUAD
    CollisionCheck_LineOC_Sphere, // COLSHAPE_SPHERE
};

/**
 * Checks if the line segment ab intersects any OC colliders, excluding those attached to actors
 * on the exclusion list. Returns true if there are any intersections and false otherwise.
 */
s32 CollisionCheck_LineOC(struct PlayState* play, CollisionCheckContext* colChkCtx, Vec3f* a, Vec3f* b,
                          Actor** exclusions, s32 numExclusions) {
    ColChkLineFunc lineCheck;
    Collider** colP;
    s32 i;
    s32 exclude;
    s32 result = false;

    for (colP = colChkCtx->colOC; colP < &colChkCtx->colOC[colChkCtx->colOCCount]; colP++) {
        if (CollisionCheck_SkipOC(*colP)) {
            continue;
        }

        exclude = false;
        for (i = 0; i < numExclusions; i++) {
            if ((*colP)->actor == exclusions[i]) {
                exclude = 1;
                break;
            }
        }
        if (exclude) {
            continue;
        }

        lineCheck = sOCLineCheckFuncs[(*colP)->shape];
        if (lineCheck == NULL) {
            continue;
        }

        result = lineCheck(play, colChkCtx, *colP, a, b);
        if (result) {
            break;
        }
    }
    return result;
}

/**
 * Checks if the line segment ab intersects any OC colliders. Returns true if there are any intersections and false
 * otherwise.
 */
s32 CollisionCheck_LineOCCheckAll(struct PlayState* play, CollisionCheckContext* colChkCtx, Vec3f* a, Vec3f* b) {
    return CollisionCheck_LineOC(play, colChkCtx, a, b, NULL, 0);
}

/**
 * Checks if the line segment ab intersects any OC colliders, excluding those attached to actors on the exclusion list.
 * Returns true if there are any intersections and false otherwise.
 */
s32 CollisionCheck_LineOCCheck(struct PlayState* play, CollisionCheckContext* colChkCtx, Vec3f* a, Vec3f* b,
                               Actor** exclusions, s32 numExclusions) {
    return CollisionCheck_LineOC(play, colChkCtx, a, b, exclusions, numExclusions);
}

/**
 * Moves the ColliderCylinder's position to the actor's position
 */
void Collider_UpdateCylinder(Actor* actor, ColliderCylinder* collider) {
    collider->dim.pos.x = actor->world.pos.x;
    collider->dim.pos.y = actor->world.pos.y;
    collider->dim.pos.z = actor->world.pos.z;
}

/**
 * Sets the ColliderCylinder's position
 */
void Collider_SetCylinderPosition(ColliderCylinder* collider, Vec3s* pos) {
    collider->dim.pos.x = pos->x;
    collider->dim.pos.y = pos->y;
    collider->dim.pos.z = pos->z;
}

/**
 * Sets the ColliderQuad's vertices
 */
void Collider_SetQuadVertices(ColliderQuad* collider, Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* d) {
    Math_Vec3f_Copy(&collider->dim.quad[2], c);
    Math_Vec3f_Copy(&collider->dim.quad[3], d);
    Math_Vec3f_Copy(&collider->dim.quad[0], a);
    Math_Vec3f_Copy(&collider->dim.quad[1], b);
    Collider_SetQuadMidpoints(&collider->dim);
}

/**
 * Sets the specified ColliderTrisElement's vertices
 */
void Collider_SetTrisVertices(ColliderTris* collider, s32 index, Vec3f* a, Vec3f* b, Vec3f* c) {
    ColliderTrisElement* element = &collider->elements[index];
    f32 nx;
    f32 ny;
    f32 nz;
    f32 originDist;

    Math_Vec3f_Copy(&element->dim.vtx[0], a);
    Math_Vec3f_Copy(&element->dim.vtx[1], b);
    Math_Vec3f_Copy(&element->dim.vtx[2], c);
    Math3D_DefPlane(a, b, c, &nx, &ny, &nz, &originDist);
    element->dim.plane.normal.x = nx;
    element->dim.plane.normal.y = ny;
    element->dim.plane.normal.z = nz;
    element->dim.plane.originDist = originDist;
}

/**
 * Sets the specified ColliderTrisElement's dim using the values in src
 */
void Collider_SetTrisDim(struct PlayState* play, ColliderTris* collider, s32 index, ColliderTrisElementDimInit* init) {
    ColliderTrisElement* element = &collider->elements[index];

    Collider_SetTrisElementDim(play, &element->dim, init);
}

/**
 * Updates the world spheres for all of the collider's JntSph elements attached to the specified limb
 */
void Collider_UpdateSpheres(s32 limb, ColliderJntSph* collider) {
    static Vec3f D_801EE1C0;
    static Vec3f D_801EE1D0;
    s32 i;

    for (i = 0; i < collider->count; i++) {
        if (limb == collider->elements[i].dim.limb) {
            D_801EE1C0.x = collider->elements[i].dim.modelSphere.center.x;
            D_801EE1C0.y = collider->elements[i].dim.modelSphere.center.y;
            D_801EE1C0.z = collider->elements[i].dim.modelSphere.center.z;
            Matrix_MultVec3f(&D_801EE1C0, &D_801EE1D0);
            collider->elements[i].dim.worldSphere.center.x = D_801EE1D0.x;
            collider->elements[i].dim.worldSphere.center.y = D_801EE1D0.y;
            collider->elements[i].dim.worldSphere.center.z = D_801EE1D0.z;
            collider->elements[i].dim.worldSphere.radius =
                collider->elements[i].dim.modelSphere.radius * collider->elements[i].dim.scale;
        }
    }
}

/**
 * Updates the world spheres for the specified ColliderJntSph element
 */
void Collider_UpdateSpheresElement(ColliderJntSph* collider, s32 index, Actor* actor) {
    if (index < collider->count) {
        collider->elements[index].dim.worldSphere.center.x =
            collider->elements[index].dim.modelSphere.center.x + actor->world.pos.x;
        collider->elements[index].dim.worldSphere.center.y =
            collider->elements[index].dim.modelSphere.center.y + actor->world.pos.y;
        collider->elements[index].dim.worldSphere.center.z =
            collider->elements[index].dim.modelSphere.center.z + actor->world.pos.z;
        collider->elements[index].dim.worldSphere.radius =
            collider->elements[index].dim.modelSphere.radius * collider->elements[index].dim.scale;
    }
}

/**
 * Updates the world sphere for the ColliderSphere if it is attached to the specified limb
 */
void Collider_UpdateSphere(s32 limb, ColliderSphere* collider) {
    static Vec3f D_801EE1E0;
    static Vec3f D_801EE1F0;

    if (limb == collider->dim.limb) {
        D_801EE1E0.x = collider->dim.modelSphere.center.x;
        D_801EE1E0.y = collider->dim.modelSphere.center.y;
        D_801EE1E0.z = collider->dim.modelSphere.center.z;
        Matrix_MultVec3f(&D_801EE1E0, &D_801EE1F0);
        collider->dim.worldSphere.center.x = D_801EE1F0.x;
        collider->dim.worldSphere.center.y = D_801EE1F0.y;
        collider->dim.worldSphere.center.z = D_801EE1F0.z;
        collider->dim.worldSphere.radius = collider->dim.modelSphere.radius * collider->dim.scale;
    }
}

/**
 * Spawns red blood droplets.
 * No actor has a collision type that spawns red blood.
 */
void CollisionCheck_SpawnRedBlood(struct PlayState* play, Vec3f* v) {
    static EffectSparkInit D_801EE200;
    s32 effectIndex;

    D_801EE200.position.x = v->x;
    D_801EE200.position.y = v->y;
    D_801EE200.position.z = v->z;
    D_801EE200.uDiv = 5;
    D_801EE200.vDiv = 5;
    D_801EE200.colorStart[0].r = 128;
    D_801EE200.colorStart[0].g = 0;
    D_801EE200.colorStart[0].b = 64;
    D_801EE200.colorStart[0].a = 255;
    D_801EE200.colorStart[1].r = 128;
    D_801EE200.colorStart[1].g = 0;
    D_801EE200.colorStart[1].b = 64;
    D_801EE200.colorStart[1].a = 255;
    D_801EE200.colorStart[2].r = 255;
    D_801EE200.colorStart[2].g = 128;
    D_801EE200.colorStart[2].b = 0;
    D_801EE200.colorStart[2].a = 255;
    D_801EE200.colorStart[3].r = 255;
    D_801EE200.colorStart[3].g = 128;
    D_801EE200.colorStart[3].b = 0;
    D_801EE200.colorStart[3].a = 255;
    D_801EE200.colorEnd[0].r = 64;
    D_801EE200.colorEnd[0].g = 0;
    D_801EE200.colorEnd[0].b = 32;
    D_801EE200.colorEnd[0].a = 0;
    D_801EE200.colorEnd[1].r = 64;
    D_801EE200.colorEnd[1].g = 0;
    D_801EE200.colorEnd[1].b = 32;
    D_801EE200.colorEnd[1].a = 0;
    D_801EE200.colorEnd[2].r = 128;
    D_801EE200.colorEnd[2].g = 0;
    D_801EE200.colorEnd[2].b = 64;
    D_801EE200.colorEnd[2].a = 0;
    D_801EE200.colorEnd[3].r = 128;
    D_801EE200.colorEnd[3].g = 0;
    D_801EE200.colorEnd[3].b = 64;
    D_801EE200.colorEnd[3].a = 0;
    D_801EE200.timer = 0;
    D_801EE200.duration = 16;
    D_801EE200.speed = 8.0f;
    D_801EE200.gravity = -1.0f;

    Effect_Add(play, &effectIndex, EFFECT_SPARK, 0, 1, &D_801EE200);
}

/**
 * Spawns water droplets.
 * No actor has a collision type that spawns water droplets.
 */
void CollisionCheck_SpawnWaterDroplets(struct PlayState* play, Vec3f* v) {
    static EffectSparkInit D_801EE738;
    s32 effectIndex;

    D_801EE738.position.x = v->x;
    D_801EE738.position.y = v->y;
    D_801EE738.position.z = v->z;
    D_801EE738.uDiv = 5;
    D_801EE738.vDiv = 5;
    D_801EE738.colorStart[0].r = 255;
    D_801EE738.colorStart[0].g = 255;
    D_801EE738.colorStart[0].b = 255;
    D_801EE738.colorStart[0].a = 255;
    D_801EE738.colorStart[1].r = 100;
    D_801EE738.colorStart[1].g = 100;
    D_801EE738.colorStart[1].b = 100;
    D_801EE738.colorStart[1].a = 100;
    D_801EE738.colorStart[2].r = 100;
    D_801EE738.colorStart[2].g = 100;
    D_801EE738.colorStart[2].b = 100;
    D_801EE738.colorStart[2].a = 100;
    D_801EE738.colorStart[3].r = 100;
    D_801EE738.colorStart[3].g = 100;
    D_801EE738.colorStart[3].b = 100;
    D_801EE738.colorStart[3].a = 100;
    D_801EE738.colorEnd[0].r = 50;
    D_801EE738.colorEnd[0].g = 50;
    D_801EE738.colorEnd[0].b = 50;
    D_801EE738.colorEnd[0].a = 50;
    D_801EE738.colorEnd[1].r = 50;
    D_801EE738.colorEnd[1].g = 50;
    D_801EE738.colorEnd[1].b = 50;
    D_801EE738.colorEnd[1].a = 50;
    D_801EE738.colorEnd[2].r = 50;
    D_801EE738.colorEnd[2].g = 50;
    D_801EE738.colorEnd[2].b = 50;
    D_801EE738.colorEnd[2].a = 50;
    D_801EE738.colorEnd[3].r = 0;
    D_801EE738.colorEnd[3].g = 0;
    D_801EE738.colorEnd[3].b = 0;
    D_801EE738.colorEnd[3].a = 0;
    D_801EE738.timer = 0;
    D_801EE738.duration = 16;
    D_801EE738.speed = 8.0f;
    D_801EE738.gravity = -1.0f;

    Effect_Add(play, &effectIndex, EFFECT_SPARK, 0, 1, &D_801EE738);
}

/**
 * Spawns streaks of light from hits against solid objects
 */
void CollisionCheck_SpawnShieldParticles(struct PlayState* play, Vec3f* v) {
    static EffectShieldParticleInit sShieldParticleInitMetal = {
        16,
        { 0, 0, 0 },
        { 0, 200, 255, 255 },
        { 255, 255, 255, 255 },
        { 255, 255, 128, 255 },
        { 255, 255, 0, 255 },
        { 255, 64, 0, 200 },
        { 255, 0, 0, 255 },
        2.1f,
        35.0f,
        30.0f,
        8,
        { 0, 0, 0, { 0, 128, 255 }, 0, 300 },
        1,
    };
    s32 effectIndex;

    sShieldParticleInitMetal.position.x = v->x;
    sShieldParticleInitMetal.position.y = v->y;
    sShieldParticleInitMetal.position.z = v->z;
    sShieldParticleInitMetal.lightPoint.x = sShieldParticleInitMetal.position.x;
    sShieldParticleInitMetal.lightPoint.y = sShieldParticleInitMetal.position.y;
    sShieldParticleInitMetal.lightPoint.z = sShieldParticleInitMetal.position.z;

    Effect_Add(play, &effectIndex, EFFECT_SHIELD_PARTICLE, 0, 1, &sShieldParticleInitMetal);
}

/**
 * Spawns streaks of light and makes a metallic sound
 */
void CollisionCheck_SpawnShieldParticlesMetal(struct PlayState* play, Vec3f* v) {
    CollisionCheck_SpawnShieldParticles(play, v);
    Audio_PlaySfx(NA_SE_IT_SHIELD_REFLECT_SW);
}

/**
 * Spawns streaks of light and makes a metallic sound at the specified position
 */
void CollisionCheck_SpawnShieldParticlesMetalSound(struct PlayState* play, Vec3f* v, Vec3f* pos) {
    CollisionCheck_SpawnShieldParticles(play, v);
    Audio_PlaySfx_AtPos(pos, NA_SE_IT_SHIELD_REFLECT_SW);
}

/**
 * Spawns streaks of light and makes a metallic sound
 */
void CollisionCheck_SpawnShieldParticlesMetal2(struct PlayState* play, Vec3f* v) {
    CollisionCheck_SpawnShieldParticlesMetal(play, v);
}

/**
 * Spawns streaks of light and makes a wooden sound
 */
void CollisionCheck_SpawnShieldParticlesWood(struct PlayState* play, Vec3f* v, Vec3f* pos) {
    static EffectShieldParticleInit sShieldParticleInitWood = {
        16,
        { 0, 0, 0 },
        { 0, 200, 255, 255 },
        { 255, 255, 255, 255 },
        { 255, 255, 128, 255 },
        { 255, 255, 0, 255 },
        { 255, 64, 0, 200 },
        { 255, 0, 0, 255 },
        2.1f,
        35.0f,
        30.0f,
        8,
        { 0, 0, 0, { 0, 128, 255 }, 0, 300 },
        0,
    };
    s32 effectIndex;

    sShieldParticleInitWood.position.x = v->x;
    sShieldParticleInitWood.position.y = v->y;
    sShieldParticleInitWood.position.z = v->z;
    sShieldParticleInitWood.lightPoint.x = sShieldParticleInitWood.position.x;
    sShieldParticleInitWood.lightPoint.y = sShieldParticleInitWood.position.y;
    sShieldParticleInitWood.lightPoint.z = sShieldParticleInitWood.position.z;

    Effect_Add(play, &effectIndex, EFFECT_SHIELD_PARTICLE, 0, 1, &sShieldParticleInitWood);
    Audio_PlaySfx_AtPos(pos, NA_SE_IT_REFLECTION_WOOD);
}

/**
 * Determines if the line segment connecting `itemPos` and `itemProjPos` intersects the side of a cylinder with the
 * given `radius`, `height`, and `offset` at `actorPos`. Returns 3 if either endpoint is inside the cylinder, otherwise
 * returns the number of points of intersection with the side of the cylinder. The locations of those points are put in
 * `out1` and `out2`, with `out1` being closer to `itemPos`. Line segments that pass through both bases of the cylinder
 * are not detected.
 */
s32 CollisionCheck_CylSideVsLineSeg(f32 radius, f32 height, f32 offset, Vec3f* actorPos, Vec3f* itemPos,
                                    Vec3f* itemProjPos, Vec3f* out1, Vec3f* out2) {
    Vec3f actorToItem;
    Vec3f actorToItemProj;
    Vec3f itemStep;
    f32 frac1 = 0.0f;
    f32 frac2 = 0.0f;
    u32 intersect2;
    u32 intersect1;
    u32 test1;
    u32 test2;
    f32 radSqDiff;
    f32 actorDotItemXZ;
    f32 zero = 0.0f;
    f32 closeDist;
    s32 pad1;
    s32 pad2;

    actorToItem.x = itemPos->x - actorPos->x;
    actorToItem.y = itemPos->y - actorPos->y - offset;
    actorToItem.z = itemPos->z - actorPos->z;

    actorToItemProj.x = itemProjPos->x - actorPos->x;
    actorToItemProj.y = itemProjPos->y - actorPos->y - offset;
    actorToItemProj.z = itemProjPos->z - actorPos->z;

    itemStep.x = actorToItemProj.x - actorToItem.x;
    itemStep.y = actorToItemProj.y - actorToItem.y;
    itemStep.z = actorToItemProj.z - actorToItem.z;

    if ((actorToItem.y > 0.0f) && (actorToItem.y < height) && (sqrtf(SQXZ(actorToItem)) < radius)) {
        return 3;
    }

    if ((actorToItemProj.y > 0.0f) && (actorToItemProj.y < height) && (sqrtf(SQXZ(actorToItemProj)) < radius)) {
        return 3;
    }
    radSqDiff = SQXZ(actorToItem) - SQ(radius);
    if (!IS_ZERO(SQXZ(itemStep))) {
        actorDotItemXZ = DOTXZ(2.0f * itemStep, actorToItem);
        if (SQ(actorDotItemXZ) < (4.0f * SQXZ(itemStep) * radSqDiff)) {
            return 0;
        }
        if ((SQ(actorDotItemXZ) - (4.0f * SQXZ(itemStep) * radSqDiff)) > zero) {
            intersect1 = intersect2 = true;
        } else {
            intersect1 = true;
            intersect2 = false;
        }
        closeDist = sqrtf(SQ(actorDotItemXZ) - (4.0f * SQXZ(itemStep) * radSqDiff));
        if (intersect1) {
            frac1 = (closeDist - actorDotItemXZ) / (2.0f * SQXZ(itemStep));
        }
        if (intersect2) {
            frac2 = (-actorDotItemXZ - closeDist) / (2.0f * SQXZ(itemStep));
        }
    } else if (!IS_ZERO(DOTXZ(2.0f * itemStep, actorToItem))) {
        intersect1 = true;
        intersect2 = false;
        frac1 = -radSqDiff / DOTXZ(2.0f * itemStep, actorToItem);
    } else {
        if (radSqDiff <= 0.0f) {
            test1 = (0.0f < actorToItem.y) && (actorToItem.y < height);
            test2 = (0.0f < actorToItemProj.y) && (actorToItemProj.y < height);

            if (test1 && test2) {
                *out1 = actorToItem;
                *out2 = actorToItemProj;
                return 2;
            }
            if (test1) {
                *out1 = actorToItem;
                return 1;
            }
            if (test2) {
                *out1 = actorToItemProj;
                return 1;
            }
        }
        return 0;
    }

    if (!intersect2) {
        if ((frac1 < 0.0f) || (1.0f < frac1)) {
            return 0;
        }
    } else {
        test1 = (frac1 < 0.0f) || (1.0f < frac1);
        test2 = (frac2 < 0.0f) || (1.0f < frac2);

        if (test1 && test2) {
            return 0;
        }
        if (test1) {
            intersect1 = false;
        }
        if (test2) {
            intersect2 = false;
        }
    }

    if (intersect1 &&
        (((frac1 * itemStep.y + actorToItem.y) < 0.0f) || (height < (frac1 * itemStep.y + actorToItem.y)))) {
        intersect1 = false;
    }
    if (intersect2 &&
        (((frac2 * itemStep.y + actorToItem.y) < 0.0f) || (height < (frac2 * itemStep.y + actorToItem.y)))) {
        intersect2 = false;
    }
    if (!intersect1 && !intersect2) {
        return 0;
    } else if (intersect1 && intersect2) {
        out1->x = frac1 * itemStep.x + actorToItem.x + actorPos->x;
        out1->y = frac1 * itemStep.y + actorToItem.y + actorPos->y;
        out1->z = frac1 * itemStep.z + actorToItem.z + actorPos->z;
        out2->x = frac2 * itemStep.x + actorToItem.x + actorPos->x;
        out2->y = frac2 * itemStep.y + actorToItem.y + actorPos->y;
        out2->z = frac2 * itemStep.z + actorToItem.z + actorPos->z;
        return 2;
    } else if (intersect1) {
        out1->x = frac1 * itemStep.x + actorToItem.x + actorPos->x;
        out1->y = frac1 * itemStep.y + actorToItem.y + actorPos->y;
        out1->z = frac1 * itemStep.z + actorToItem.z + actorPos->z;
        return 1;
    } else if (intersect2) {
        out1->x = frac2 * itemStep.x + actorToItem.x + actorPos->x;
        out1->y = frac2 * itemStep.y + actorToItem.y + actorPos->y;
        out1->z = frac2 * itemStep.z + actorToItem.z + actorPos->z;
        return 1;
    }
    return 1;
}
