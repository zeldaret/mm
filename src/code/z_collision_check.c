#include "prevent_bss_reordering.h"
#include "global.h"
#include "z64collision_check.h"

typedef s32 (*ColChkResetFunc)(struct PlayState*, Collider*);
typedef void (*ColChkBloodFunc)(struct PlayState*, Collider*, Vec3f*);
typedef void (*ColChkApplyFunc)(struct PlayState*, CollisionCheckContext*, Collider*);
typedef void (*ColChkVsFunc)(struct PlayState*, CollisionCheckContext*, Collider*, Collider*);
typedef s32 (*ColChkLineFunc)(struct PlayState*, CollisionCheckContext*, Collider*, Vec3f*, Vec3f*);

Vec3f D_801EDE00;
Vec3f D_801EDE10;
Vec3f D_801EDE20;
Vec3f D_801EDE30;
TriNorm D_801EDE40;
TriNorm D_801EDE78;
LineSegment D_801EDEB0;
TriNorm D_801EDEC8;
TriNorm D_801EDF00;
Vec3f D_801EDF38;
Vec3f D_801EDF48;
TriNorm D_801EDF58;
TriNorm D_801EDF90;
LineSegment D_801EDFC8;
Vec3f D_801EDFE0;
Vec3f D_801EDFF0;
TriNorm D_801EE000;
TriNorm D_801EE038;
TriNorm D_801EE070[2];
Vec3f D_801EE0D8;
TriNorm D_801EE0E8[2];
TriNorm D_801EE150;
TriNorm D_801EE188;

#ifndef NON_MATCHING
Vec3f D_801EE1C0;
Vec3f D_801EE1D0;
Vec3f D_801EE1E0;
Vec3f D_801EE1F0;
EffectSparkInit D_801EE200;
#endif

TriNorm D_801EE6C8;
TriNorm D_801EE700;

#ifndef NON_MATCHING
EffectSparkInit D_801EE738;
EffectSparkInit D_801EEC00;
EffectSparkInit D_801EF0C8;
#endif

TriNorm D_801EF590;
TriNorm D_801EF5C8;
TriNorm D_801EF600;
TriNorm D_801EF638;

/**
 * Gets the damage and effect that should be applied for the collision between
 * `at` and `ac`, referring to the ac actor's damage chart if applicable.
 */
f32 CollisionCheck_GetDamageAndEffectOnBumper(Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo,
                                              u32* effect) {
    static f32 damageMultipliers[] = {
        0.0f, 1.0f, 2.0f, 0.5f, 0.25f, 3.0f, 4.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    };
    u32 dmgFlags;
    s32 i;
    f32 damage;

    *effect = 0;
    damage = CollisionCheck_GetToucherDamage(at, atInfo, ac, acInfo);

    if (ac->actor->colChkInfo.damageTable != NULL) {
        dmgFlags = atInfo->toucher.dmgFlags;

        for (i = 0; i != ARRAY_COUNT(ac->actor->colChkInfo.damageTable->attack); i++) {
            if (dmgFlags == 1) {
                break;
            }
            dmgFlags >>= 1;
        }

        damage *= damageMultipliers[ac->actor->colChkInfo.damageTable->attack[i] & 0xF];
        *effect = (ac->actor->colChkInfo.damageTable->attack[i] >> 4) & 0xF;
    }
    return damage;
}

/**
 * Calculates damage after factoring in the ac collider's defense
 */
f32 CollisionCheck_ApplyBumperDefense(f32 damage, ColliderInfo* ac) {
    f32 finalDamage = damage - ac->bumper.defense;

    return finalDamage;
}

/**
 * Gets the damage to be inflicted by `at` on `ac`, before applying other
 * factors such as the ac collider's defense.
 */
s32 CollisionCheck_GetToucherDamage(Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo) {
    if ((at->actor != NULL) && (at->actor->id == ACTOR_EN_BOM) && (ac->actor != NULL) &&
        (ac->actor->id == ACTOR_PLAYER)) {
        return 8;
    }
    return atInfo->toucher.damage;
}

s32 Collider_InitBase(PlayState* play, Collider* collider) {
    static Collider defaultCollider = {
        NULL, NULL, NULL, NULL, AT_NONE, AC_NONE, OC1_NONE, OC2_NONE, COLTYPE_HIT3, COLSHAPE_MAX,
    };

    *collider = defaultCollider;
    return 1;
}

s32 Collider_DestroyBase(PlayState* play, Collider* collider) {
    return 1;
}

/**
 * Uses default OC2_TYPE_1 and COLTYPE_HIT0
 */
s32 Collider_SetBaseToActor(PlayState* play, Collider* collider, ColliderInitToActor* src) {
    collider->actor = src->actor;
    collider->atFlags = src->atFlags;
    collider->acFlags = src->acFlags;
    collider->ocFlags1 = src->ocFlags1;
    collider->ocFlags2 = OC2_TYPE_1;
    collider->shape = src->shape;
    return 1;
}

/**
 * Uses default OC2_TYPE_1
 */
s32 Collider_SetBaseType1(PlayState* play, Collider* collider, Actor* actor, ColliderInitType1* src) {
    collider->actor = actor;
    collider->colType = src->colType;
    collider->atFlags = src->atFlags;
    collider->acFlags = src->acFlags;
    collider->ocFlags1 = src->ocFlags1;
    collider->ocFlags2 = OC2_TYPE_1;
    collider->shape = src->shape;
    return 1;
}

s32 Collider_SetBase(PlayState* play, Collider* collider, Actor* actor, ColliderInit* src) {
    collider->actor = actor;
    collider->colType = src->colType;
    collider->atFlags = src->atFlags;
    collider->acFlags = src->acFlags;
    collider->ocFlags1 = src->ocFlags1;
    collider->ocFlags2 = src->ocFlags2;
    collider->shape = src->shape;
    return 1;
}

void Collider_ResetATBase(PlayState* play, Collider* collider) {
    collider->at = NULL;
    collider->atFlags &= ~(AT_HIT | AT_BOUNCED);
}

void Collider_ResetACBase(PlayState* play, Collider* collider) {
    collider->ac = NULL;
    collider->acFlags &= ~(AC_HIT | AC_BOUNCED);
}

void Collider_ResetOCBase(PlayState* play, Collider* collider) {
    collider->oc = NULL;
    collider->ocFlags1 &= ~OC1_HIT;
    collider->ocFlags2 &= ~OC2_HIT_PLAYER;
}

s32 Collider_InitTouch(PlayState* play, ColliderTouch* touch) {
    static ColliderTouch defaultColliderTouch = { 0x00000000, 0, 0 };

    *touch = defaultColliderTouch;
    return 1;
}

s32 Collider_DestroyTouch(PlayState* play, ColliderTouch* touch) {
    return 1;
}

s32 Collider_SetTouch(PlayState* play, ColliderTouch* touch, ColliderTouchInit* src) {
    touch->dmgFlags = src->dmgFlags;
    touch->effect = src->effect;
    touch->damage = src->damage;
    return 1;
}

void Collider_ResetATInfoUnk(PlayState* play, ColliderInfo* info) {
}

s32 Collider_InitBump(PlayState* play, ColliderBump* bump) {
    static ColliderBump defaultColliderBump = { 0xF7CFFFFF, 0, 0, { 0, 0, 0 } };

    *bump = defaultColliderBump;
    return 1;
}

s32 Collider_DestroyBump(PlayState* play, ColliderBump* bump) {
    return 1;
}

s32 Collider_SetBump(PlayState* play, ColliderBump* bump, ColliderBumpInit* src) {
    bump->dmgFlags = src->dmgFlags;
    bump->effect = src->effect;
    bump->defense = src->defense;
    return 1;
}

s32 Collider_InitInfo(PlayState* play, ColliderInfo* info) {
    static ColliderInfo defaultColliderInfo = {
        { 0, 0, 0 },   { 0xF7CFFFFF, 0, 0, { 0, 0, 0 } },
        ELEMTYPE_UNK0, TOUCH_NONE,
        BUMP_NONE,     OCELEM_NONE,
        NULL,          NULL,
        NULL,          NULL,
    };

    *info = defaultColliderInfo;
    Collider_InitTouch(play, &info->toucher);
    Collider_InitBump(play, &info->bumper);
    return 1;
}

s32 Collider_DestroyInfo(PlayState* play, ColliderInfo* info) {
    Collider_DestroyTouch(play, &info->toucher);
    Collider_DestroyBump(play, &info->bumper);
    return 1;
}

s32 Collider_SetInfo(PlayState* play, ColliderInfo* info, ColliderInfoInit* src) {
    info->elemType = src->elemType;
    Collider_SetTouch(play, &info->toucher, &src->toucher);
    Collider_SetBump(play, &info->bumper, &src->bumper);
    info->toucherFlags = src->toucherFlags;
    info->bumperFlags = src->bumperFlags;
    info->ocElemFlags = src->ocElemFlags;
    return 1;
}

void Collider_ResetATInfo(PlayState* play, ColliderInfo* info) {
    info->atHit = NULL;
    info->atHitInfo = NULL;
    info->toucherFlags &= ~TOUCH_HIT;
    info->toucherFlags &= ~TOUCH_DREW_HITMARK;
    Collider_ResetATInfoUnk(play, info);
}

void Collider_ResetACInfo(PlayState* play, ColliderInfo* info) {
    info->bumper.hitPos.x = info->bumper.hitPos.y = info->bumper.hitPos.z = 0;
    info->bumperFlags &= ~BUMP_HIT;
    info->bumperFlags &= ~BUMP_DRAW_HITMARK;
    info->acHit = NULL;
    info->acHitInfo = NULL;
}

void Collider_ResetOCInfo(PlayState* play, ColliderInfo* info) {
    info->ocElemFlags &= ~OCELEM_HIT;
}

s32 Collider_InitJntSphElementDim(PlayState* play, ColliderJntSphElementDim* dim) {
    static ColliderJntSphElementDim defaultColliderJntSphElementDim = {
        { { 0, 0, 0 }, 0 },
        { { 0, 0, 0 }, 0 },
        0.0f,
        0,
    };

    *dim = defaultColliderJntSphElementDim;
    return 1;
}

s32 Collider_DestroyJntSphElementDim(PlayState* play, ColliderJntSphElementDim* dim) {
    return 1;
}

s32 Collider_SetJntSphElementDim(PlayState* play, ColliderJntSphElementDim* dest, ColliderJntSphElementDimInit* src) {
    dest->limb = src->limb;
    dest->modelSphere = src->modelSphere;
    dest->scale = src->scale * 0.01f;
    return 1;
}

s32 Collider_InitJntSphElement(PlayState* play, ColliderJntSphElement* element) {
    Collider_InitInfo(play, &element->info);
    Collider_InitJntSphElementDim(play, &element->dim);
    return 1;
}

s32 Collider_DestroyJntSphElement(PlayState* play, ColliderJntSphElement* element) {
    Collider_DestroyInfo(play, &element->info);
    Collider_DestroyJntSphElementDim(play, &element->dim);
    return 1;
}

s32 Collider_SetJntSphElement(PlayState* play, ColliderJntSphElement* dest, ColliderJntSphElementInit* src) {
    Collider_SetInfo(play, &dest->info, &src->info);
    Collider_SetJntSphElementDim(play, &dest->dim, &src->dim);
    return 1;
}

s32 Collider_ResetJntSphElementAT(PlayState* play, ColliderJntSphElement* collider) {
    Collider_ResetATInfo(play, &collider->info);
    return 1;
}

s32 Collider_ResetJntSphElementAC(PlayState* play, ColliderJntSphElement* collider) {
    Collider_ResetACInfo(play, &collider->info);
    return 1;
}

s32 Collider_ResetJntSphElementOC(PlayState* play, ColliderJntSphElement* collider) {
    Collider_ResetOCInfo(play, &collider->info);
    return 1;
}

/**
 * Initializes a ColliderJntSph to default values
 */
s32 Collider_InitJntSph(PlayState* play, ColliderJntSph* collider) {
    Collider_InitBase(play, &collider->base);
    collider->count = 0;
    collider->elements = NULL;
    return 1;
}

/**
 * Destroys a dynamically allocated ColliderJntSph
 */
s32 Collider_FreeJntSph(PlayState* play, ColliderJntSph* collider) {
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
s32 Collider_DestroyJntSph(PlayState* play, ColliderJntSph* collider) {
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
s32 Collider_SetJntSphToActor(PlayState* play, ColliderJntSph* collider, ColliderJntSphInitToActor* src) {
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
s32 Collider_SetJntSphAllocType1(PlayState* play, ColliderJntSph* sphereGroup, Actor* actor,
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
s32 Collider_SetJntSph(PlayState* play, ColliderJntSph* sphereGroup, Actor* actor, ColliderJntSphInit* src,
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
s32 Collider_InitAndSetJntSph(PlayState* play, ColliderJntSph* sphereGroup, Actor* actor, ColliderJntSphInit* src,
                              ColliderJntSphElement* elements) {
    Collider_InitJntSph(play, sphereGroup);
    Collider_SetJntSph(play, sphereGroup, actor, src, elements);
    return 0;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetJntSphAT(PlayState* play, Collider* collider) {
    ColliderJntSphElement* element;
    ColliderJntSph* jntSph = (ColliderJntSph*)collider;

    Collider_ResetATBase(play, &jntSph->base);

    for (element = jntSph->elements; element < &jntSph->elements[jntSph->count]; element++) {
        Collider_ResetJntSphElementAT(play, element);
    }
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetJntSphAC(PlayState* play, Collider* collider) {
    ColliderJntSphElement* element;
    ColliderJntSph* jntSph = (ColliderJntSph*)collider;

    Collider_ResetACBase(play, &jntSph->base);

    for (element = jntSph->elements; element < &jntSph->elements[jntSph->count]; element++) {
        Collider_ResetJntSphElementAC(play, element);
    }
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetJntSphOC(PlayState* play, Collider* collider) {
    ColliderJntSphElement* element;
    ColliderJntSph* jntSph = (ColliderJntSph*)collider;

    Collider_ResetOCBase(play, &jntSph->base);

    for (element = jntSph->elements; element < &jntSph->elements[jntSph->count]; element++) {
        Collider_ResetJntSphElementOC(play, element);
    }
    return 1;
}

s32 Collider_InitCylinderDim(PlayState* play, Cylinder16* dim) {
    static Cylinder16 defaultColliderCylinderDim = { 0, 0, 0, { 0, 0, 0 } };

    *dim = defaultColliderCylinderDim;
    return 1;
}

s32 Collider_DestroyCylinderDim(PlayState* play, Cylinder16* dim) {
    return 1;
}

s32 Collider_SetCylinderDim(PlayState* play, Cylinder16* dim, Cylinder16* src) {
    *dim = *src;
    return 1;
}

/**
 * Initializes a ColliderCylinder to default values
 */
s32 Collider_InitCylinder(PlayState* play, ColliderCylinder* collider) {
    Collider_InitBase(play, &collider->base);
    Collider_InitInfo(play, &collider->info);
    Collider_InitCylinderDim(play, &collider->dim);
    return 1;
}

/**
 * Destroys a ColliderCylinder
 */
s32 Collider_DestroyCylinder(PlayState* play, ColliderCylinder* collider) {
    Collider_DestroyBase(play, &collider->base);
    Collider_DestroyInfo(play, &collider->info);
    Collider_DestroyCylinderDim(play, &collider->dim);
    return 1;
}

/**
 * Sets up the ColliderCylinder using the values in src and sets it to the actor specified in src. Uses default
 * OC2_TYPE_1 and COLTYPE_0.
 */
s32 Collider_SetCylinderToActor(PlayState* play, ColliderCylinder* collider, ColliderCylinderInitToActor* src) {
    Collider_SetBaseToActor(play, &collider->base, &src->base);
    Collider_SetInfo(play, &collider->info, &src->info);
    Collider_SetCylinderDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Sets up the ColliderCylinder using the values in src. Uses default OC2_TYPE_1
 */
s32 Collider_SetCylinderType1(PlayState* play, ColliderCylinder* collider, Actor* actor,
                              ColliderCylinderInitType1* src) {
    Collider_SetBaseType1(play, &collider->base, actor, &src->base);
    Collider_SetInfo(play, &collider->info, &src->info);
    Collider_SetCylinderDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Sets up the ColliderCylinder using the values in src.
 */
s32 Collider_SetCylinder(PlayState* play, ColliderCylinder* collider, Actor* actor, ColliderCylinderInit* src) {
    Collider_SetBase(play, &collider->base, actor, &src->base);
    Collider_SetInfo(play, &collider->info, &src->info);
    Collider_SetCylinderDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Fully initializes a ColliderCylinder using the values in src.
 */
s32 Collider_InitAndSetCylinder(PlayState* play, ColliderCylinder* collider, Actor* actor, ColliderCylinderInit* src) {
    Collider_InitCylinder(play, collider);
    Collider_SetCylinder(play, collider, actor, src);
    return 1;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetCylinderAT(PlayState* play, Collider* collider) {
    ColliderCylinder* cylinder = (ColliderCylinder*)collider;

    Collider_ResetATBase(play, &cylinder->base);
    Collider_ResetATInfo(play, &cylinder->info);
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetCylinderAC(PlayState* play, Collider* collider) {
    ColliderCylinder* cylinder = (ColliderCylinder*)collider;

    Collider_ResetACBase(play, &cylinder->base);
    Collider_ResetACInfo(play, &cylinder->info);
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetCylinderOC(PlayState* play, Collider* collider) {
    ColliderCylinder* cylinder = (ColliderCylinder*)collider;

    Collider_ResetOCBase(play, &cylinder->base);
    Collider_ResetOCInfo(play, &cylinder->info);
    return 1;
}

s32 Collider_InitTrisElementDim(PlayState* play, TriNorm* dim) {
    static TriNorm defaultColliderTrisElementDim = {
        { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f }, 0.0f },
    };

    *dim = defaultColliderTrisElementDim;
    return 1;
}

s32 Collider_DestroyTrisElementDim(PlayState* play, TriNorm* dim) {
    return 1;
}

s32 Collider_SetTrisElementDim(PlayState* play, TriNorm* dim, ColliderTrisElementDimInit* src) {
    Vec3f* destVtx;
    Vec3f* srcVtx;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 originDist;

    for (destVtx = dim->vtx, srcVtx = &src->vtx[0]; destVtx < &dim->vtx[3]; destVtx++, srcVtx++) {
        *destVtx = *srcVtx;
    }

    Math3D_UnitNormalVector(&src->vtx[0], &src->vtx[1], &src->vtx[2], &nx, &ny, &nz, &originDist);

    dim->plane.normal.x = nx;
    dim->plane.normal.y = ny;
    dim->plane.normal.z = nz;
    dim->plane.originDist = originDist;
    return 1;
}

s32 Collider_InitTrisElement(PlayState* play, ColliderTrisElement* element) {
    Collider_InitInfo(play, &element->info);
    Collider_InitTrisElementDim(play, &element->dim);
    return 1;
}

s32 Collider_DestroyTrisElement(PlayState* play, ColliderTrisElement* element) {
    Collider_DestroyInfo(play, &element->info);
    Collider_DestroyTrisElementDim(play, &element->dim);
    return 1;
}

s32 Collider_SetTrisElement(PlayState* play, ColliderTrisElement* element, ColliderTrisElementInit* src) {
    Collider_SetInfo(play, &element->info, &src->info);
    Collider_SetTrisElementDim(play, &element->dim, &src->dim);
    return 1;
}

s32 Collider_ResetTrisElementAT(PlayState* play, ColliderTrisElement* element) {
    Collider_ResetATInfo(play, &element->info);
    return 1;
}

s32 Collider_ResetTrisElementAC(PlayState* play, ColliderTrisElement* element) {
    Collider_ResetACInfo(play, &element->info);
    return 1;
}

s32 Collider_ResetTrisElementOC(PlayState* play, ColliderTrisElement* element) {
    Collider_ResetOCInfo(play, &element->info);
    return 1;
}

/**
 * Initializes a ColliderTris to default values
 */
s32 Collider_InitTris(PlayState* play, ColliderTris* tris) {
    Collider_InitBase(play, &tris->base);
    tris->count = 0;
    tris->elements = NULL;
    return 1;
}

/**
 * Destroys a dynamically allocated ColliderTris
 */
s32 Collider_FreeTris(PlayState* play, ColliderTris* tris) {
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
s32 Collider_DestroyTris(PlayState* play, ColliderTris* tris) {
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
s32 Collider_SetTrisAllocType1(PlayState* play, ColliderTris* tris, Actor* actor, ColliderTrisInitType1* src) {
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
s32 Collider_SetTris(PlayState* play, ColliderTris* triGroup, Actor* actor, ColliderTrisInit* src,
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
s32 Collider_InitAndSetTris(PlayState* play, ColliderTris* tris, Actor* actor, ColliderTrisInit* src,
                            ColliderTrisElement* elements) {
    Collider_InitTris(play, tris);
    Collider_SetTris(play, tris, actor, src, elements);
    return 0;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetTrisAT(PlayState* play, Collider* collider) {
    ColliderTrisElement* element;
    ColliderTris* tris = (ColliderTris*)collider;

    Collider_ResetATBase(play, &tris->base);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        Collider_ResetTrisElementAT(play, element);
    }
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetTrisAC(PlayState* play, Collider* collider) {
    ColliderTrisElement* element;
    ColliderTris* tris = (ColliderTris*)collider;

    Collider_ResetACBase(play, &tris->base);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        Collider_ResetTrisElementAC(play, element);
    }
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetTrisOC(PlayState* play, Collider* collider) {
    ColliderTrisElement* element;
    ColliderTris* tris = (ColliderTris*)collider;

    Collider_ResetOCBase(play, &tris->base);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        Collider_ResetTrisElementOC(play, element);
    }
    return 1;
}

s32 Collider_InitQuadDim(PlayState* play, ColliderQuadDim* dim) {
    static ColliderQuadDim defaultColliderQuadDim = {
        { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        { 0, 0, 0 },
        { 0, 0, 0 },
        1.0E38f,
    };

    *dim = defaultColliderQuadDim;
    return 1;
}

s32 Collider_DestroyQuadDim(PlayState* play, ColliderQuadDim* dim) {
    return 1;
}

s32 Collider_ResetQuadACDist(PlayState* play, ColliderQuadDim* dim) {
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

s32 Collider_SetQuadDim(PlayState* play, ColliderQuadDim* dim, ColliderQuadDimInit* init) {
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
s32 Collider_InitQuad(PlayState* play, ColliderQuad* collider) {
    Collider_InitBase(play, &collider->base);
    Collider_InitInfo(play, &collider->info);
    Collider_InitQuadDim(play, &collider->dim);
    return 1;
}

/**
 * Destroys a ColliderQuad.
 */
s32 Collider_DestroyQuad(PlayState* play, ColliderQuad* collider) {
    Collider_DestroyBase(play, &collider->base);
    Collider_DestroyInfo(play, &collider->info);
    Collider_DestroyQuadDim(play, &collider->dim);
    return 1;
}

/**
 * Sets up the ColliderQuad using the values in src. Uses the default OC2_TYPE_1
 */
s32 Collider_SetQuadType1(PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInitType1* src) {
    Collider_SetBaseType1(play, &collider->base, actor, &src->base);
    Collider_SetInfo(play, &collider->info, &src->info);
    Collider_SetQuadDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Sets up the ColliderQuad using the values in src.
 */
s32 Collider_SetQuad(PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src) {
    Collider_SetBase(play, &collider->base, actor, &src->base);
    Collider_SetInfo(play, &collider->info, &src->info);
    Collider_SetQuadDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Fully initializes a ColliderQuad using the values in src.
 */
s32 Collider_InitAndSetQuad(PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src) {
    Collider_InitQuad(play, collider);
    Collider_SetQuad(play, collider, actor, src);
    return 0;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetQuadAT(PlayState* play, Collider* collider) {
    ColliderQuad* quad = (ColliderQuad*)collider;

    Collider_ResetATBase(play, &quad->base);
    Collider_ResetATInfo(play, &quad->info);
    Collider_ResetQuadACDist(play, &quad->dim);
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetQuadAC(PlayState* play, Collider* collider) {
    ColliderQuad* quad = (ColliderQuad*)collider;

    Collider_ResetACBase(play, &quad->base);
    Collider_ResetACInfo(play, &quad->info);
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetQuadOC(PlayState* play, Collider* collider) {
    ColliderQuad* quad = (ColliderQuad*)collider;

    Collider_ResetOCBase(play, &quad->base);
    Collider_ResetOCInfo(play, &quad->info);
    return 1;
}

/**
 * For quad colliders with TOUCH_NEAREST, resets the previous AC collider it hit if the current element is closer,
 * otherwise returns false. Used on player AT colliders to prevent multiple collisions from registering.
 */
s32 Collider_QuadSetNearestAC(PlayState* play, ColliderQuad* quad, Vec3f* hitPos) {
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
        if (quad->info.atHitInfo != NULL) {
            Collider_ResetACInfo(play, quad->info.atHitInfo);
        }
        return 1;
    } else {
        return 0;
    }
}

/**
 * Initializes a ColliderSphere to default values.
 */
s32 Collider_InitSphere(PlayState* play, ColliderSphere* collider) {
    Collider_InitBase(play, &collider->base);
    Collider_InitInfo(play, &collider->info);
    Collider_InitJntSphElementDim(play, &collider->dim);
    return 1;
}

/**
 * Destroys a ColliderSphere.
 */
s32 Collider_DestroySphere(PlayState* play, ColliderSphere* collider) {
    Collider_DestroyBase(play, &collider->base);
    Collider_DestroyInfo(play, &collider->info);
    Collider_DestroyJntSphElementDim(play, &collider->dim);
    return 1;
}

/**
 * Sets up the ColliderSphere using the values in src.
 */
s32 Collider_SetSphere(PlayState* play, ColliderSphere* collider, Actor* actor, ColliderSphereInit* src) {
    Collider_SetBase(play, &collider->base, actor, &src->base);
    Collider_SetInfo(play, &collider->info, &src->info);
    Collider_SetJntSphElementDim(play, &collider->dim, &src->dim);
    return 1;
}

/**
 * Fully initializes a ColliderSphere using the values in src.
 */
s32 Collider_InitAndSetSphere(PlayState* play, ColliderSphere* collider, Actor* actor, ColliderSphereInit* src) {
    Collider_InitSphere(play, collider);
    Collider_SetSphere(play, collider, actor, src);
    return 0;
}

/**
 * Resets the collider's AT collision flags.
 */
s32 Collider_ResetSphereAT(PlayState* play, Collider* collider) {
    ColliderSphere* sphere = (ColliderSphere*)collider;

    Collider_ResetATBase(play, &sphere->base);
    Collider_ResetATInfo(play, &sphere->info);
    return 1;
}

/**
 * Resets the collider's AC collision flags.
 */
s32 Collider_ResetSphereAC(PlayState* play, Collider* collider) {
    ColliderSphere* sphere = (ColliderSphere*)collider;

    Collider_ResetACBase(play, &sphere->base);
    Collider_ResetACInfo(play, &sphere->info);
    return 1;
}

/**
 * Resets the collider's OC collision flags.
 */
s32 Collider_ResetSphereOC(PlayState* play, Collider* collider) {
    ColliderSphere* sphere = (ColliderSphere*)collider;

    Collider_ResetOCBase(play, &sphere->base);
    Collider_ResetOCInfo(play, &sphere->info);
    return 1;
}

/**
 * Initializes an OcLine to default values
 */
s32 Collider_InitLine(PlayState* play, OcLine* line) {
    static Vec3f defaultLinePoint = { 0.0f, 0.0f, 0.0f };

    Math_Vec3f_Copy(&line->line.a, &defaultLinePoint);
    Math_Vec3f_Copy(&line->line.b, &defaultLinePoint);
    return 1;
}

/**
 * Destroys an OcLine
 */
s32 Collider_DestroyLine(PlayState* play, OcLine* line) {
    return 1;
}

/**
 * Sets up an OcLine with endpoints a and b.
 */
s32 Collider_SetLinePoints(PlayState* play, OcLine* line, Vec3f* a, Vec3f* b) {
    Math_Vec3f_Copy(&line->line.a, a);
    Math_Vec3f_Copy(&line->line.b, b);
    return 1;
}

/**
 * Sets up an OcLine using the values in src.
 */
s32 Collider_SetLine(PlayState* play, OcLine* line, OcLine* src) {
    line->ocFlags = src->ocFlags;
    Collider_SetLinePoints(play, line, &src->line.a, &src->line.b);
    return 1;
}

/**
 * Resets the OcLine's collision flags.
 */
s32 Collider_ResetLineOC(PlayState* play, OcLine* line) {
    line->ocFlags &= ~OCLINE_HIT;
    return 1;
}

/**
 * Initializes CollisionCheckContext.
 * Clears all collider arrays, disables SAC, and sets flags for drawing colliders.
 */
void CollisionCheck_InitContext(PlayState* play, CollisionCheckContext* colCtxt) {
    colCtxt->sacFlags = 0;
    CollisionCheck_ClearContext(play, colCtxt);
}

void CollisionCheck_DestroyContext(PlayState* play, CollisionCheckContext* colCtxt) {
}

/**
 * Clears all collider lists in CollisionCheckContext when not in SAC mode.
 */
void CollisionCheck_ClearContext(PlayState* play, CollisionCheckContext* colCtxt) {
    Collider** col;
    OcLine** line;

    if (colCtxt->sacFlags & SAC_ON) {
        return;
    }

    colCtxt->colATCount = 0;
    colCtxt->colACCount = 0;
    colCtxt->colOCCount = 0;
    colCtxt->colLineCount = 0;

    for (col = &colCtxt->colAT[0]; col < &colCtxt->colAT[ARRAY_COUNT(colCtxt->colAT)]; col++) {
        *col = NULL;
    }

    for (col = &colCtxt->colAC[0]; col < &colCtxt->colAC[ARRAY_COUNT(colCtxt->colAC)]; col++) {
        *col = NULL;
    }

    for (col = &colCtxt->colOC[0]; col < &colCtxt->colOC[ARRAY_COUNT(colCtxt->colOC)]; col++) {
        *col = NULL;
    }

    for (line = &colCtxt->colLine[0]; line < &colCtxt->colLine[ARRAY_COUNT(colCtxt->colLine)]; line++) {
        *line = NULL;
    }
}

/**
 * Enables SAC, an alternate collision check mode that allows direct management of collider lists.
 */
void CollisionCheck_EnableSAC(PlayState* play, CollisionCheckContext* colCtxt) {
    colCtxt->sacFlags |= SAC_ON;
}

/**
 * Disables SAC, an alternate collision check mode that allows direct management of collider lists.
 */
void CollisionCheck_DisableSAC(PlayState* play, CollisionCheckContext* colCtxt) {
    colCtxt->sacFlags &= ~SAC_ON;
}

ColChkResetFunc sATResetFuncs[] = {
    Collider_ResetJntSphAT, Collider_ResetCylinderAT, Collider_ResetTrisAT,
    Collider_ResetQuadAT,   Collider_ResetSphereAT,
};

/**
 * Sets collider as an AT (attack) for the current frame, which will be checked against ACs (attack colliders)
 */
s32 CollisionCheck_SetAT(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    s32 index;

    if (FrameAdvance_IsEnabled(&play->state)) {
        return -1;
    }
    sATResetFuncs[collider->shape](play, collider);

    if ((collider->actor != NULL) && (collider->actor->update == NULL)) {
        return -1;
    }
    if (colCtxt->colATCount >= ARRAY_COUNT(colCtxt->colAT)) {
        return -1;
    }
    if (colCtxt->sacFlags & SAC_ON) {
        return -1;
    }
    index = colCtxt->colATCount;
    colCtxt->colAT[colCtxt->colATCount++] = collider;

    return index;
}

/**
 * Sets collider as an AT (attack) for the current frame, which will be checked against ACs (attack colliders).
 * If CollisionCheck_SAC is enabled, the collider will be inserted into the list at the specified index, otherwise it
 * will be inserted into the next slot.
 */
s32 CollisionCheck_SetAT_SAC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider, s32 index) {
    if (FrameAdvance_IsEnabled(&play->state)) {
        return -1;
    }
    sATResetFuncs[collider->shape](play, collider);

    if ((collider->actor != NULL) && (collider->actor->update == NULL)) {
        return -1;
    }
    if (colCtxt->sacFlags & SAC_ON) {
        if (index >= colCtxt->colATCount) {
            return -1;
        }
        colCtxt->colAT[index] = collider;
    } else {
        if (colCtxt->colATCount >= ARRAY_COUNT(colCtxt->colAT)) {
            return -1;
        }
        index = colCtxt->colATCount;
        colCtxt->colAT[colCtxt->colATCount++] = collider;
    }
    return index;
}

ColChkResetFunc sACResetFuncs[] = {
    Collider_ResetJntSphAC, Collider_ResetCylinderAC, Collider_ResetTrisAC,
    Collider_ResetQuadAC,   Collider_ResetSphereAC,
};

/**
 * Sets collider as an AC (attack collider) for the current frame, allowing it to detect ATs (attacks)
 */
s32 CollisionCheck_SetAC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    s32 index;

    if (FrameAdvance_IsEnabled(&play->state)) {
        return -1;
    }
    sACResetFuncs[collider->shape](play, collider);

    if ((collider->actor != NULL) && (collider->actor->update == NULL)) {
        return -1;
    }
    if (colCtxt->colACCount >= ARRAY_COUNT(colCtxt->colAC)) {
        return -1;
    }
    if (colCtxt->sacFlags & SAC_ON) {
        return -1;
    }
    index = colCtxt->colACCount;
    colCtxt->colAC[colCtxt->colACCount++] = collider;

    return index;
}

/**
 * Sets collider as an AC (attack collider) for the current frame, allowing it to detect ATs (attacks).
 * If CollisionCheck_SAC is enabled, the collider will be inserted into the list at the specified index, otherwise it
 * will be inserted into the next slot
 */
s32 CollisionCheck_SetAC_SAC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider, s32 index) {
    if (FrameAdvance_IsEnabled(&play->state)) {
        return -1;
    }
    sACResetFuncs[collider->shape](play, collider);

    if ((collider->actor != NULL) && (collider->actor->update == NULL)) {
        return -1;
    }
    if (colCtxt->sacFlags & SAC_ON) {
        if (index >= colCtxt->colACCount) {
            return -1;
        }
        colCtxt->colAC[index] = collider;
    } else {
        if (colCtxt->colACCount >= ARRAY_COUNT(colCtxt->colAC)) {
            return -1;
        }
        index = colCtxt->colACCount;
        colCtxt->colAC[colCtxt->colACCount++] = collider;
    }
    return index;
}

ColChkResetFunc sOCResetFuncs[] = {
    Collider_ResetJntSphOC, Collider_ResetCylinderOC, Collider_ResetTrisOC,
    Collider_ResetQuadOC,   Collider_ResetSphereOC,
};

/**
 * Sets collider as an OC (object collider) for the current frame, allowing it to detect other OCs.
 */
s32 CollisionCheck_SetOC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    s32 index;

    if (FrameAdvance_IsEnabled(&play->state)) {
        return -1;
    }
    sOCResetFuncs[collider->shape](play, collider);

    if ((collider->actor != NULL) && (collider->actor->update == NULL)) {
        return -1;
    }
    if (colCtxt->colOCCount >= ARRAY_COUNT(colCtxt->colOC)) {
        return -1;
    }
    if (colCtxt->sacFlags & SAC_ON) {
        return -1;
    }
    index = colCtxt->colOCCount;
    colCtxt->colOC[colCtxt->colOCCount++] = collider;

    return index;
}

/**
 * Sets collider as an OC (object collider) for the current frame, allowing it to detect other OCs.
 * If CollisionCheck_SAC is enabled, the collider will be inserted into the list at the specified index, otherwise it
 * will be inserted into the next slot.
 */
s32 CollisionCheck_SetOC_SAC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider, s32 index) {
    if (FrameAdvance_IsEnabled(&play->state)) {
        return -1;
    }
    sOCResetFuncs[collider->shape](play, collider);

    if ((collider->actor != NULL) && (collider->actor->update == NULL)) {
        return -1;
    }
    if (colCtxt->sacFlags & SAC_ON) {
        if (index >= colCtxt->colOCCount) {
            return -1;
        }
        //! @bug should be colOC
        colCtxt->colAT[index] = collider;
    } else {
        if (colCtxt->colOCCount >= ARRAY_COUNT(colCtxt->colOC)) {
            return -1;
        }
        index = colCtxt->colOCCount;

        colCtxt->colOC[colCtxt->colOCCount] = collider;
        colCtxt->colOCCount++;
    }
    return index;
}

/**
 * Sets a line as an OC collider for this frame.
 */
s32 CollisionCheck_SetOCLine(PlayState* play, CollisionCheckContext* colCtxt, OcLine* line) {
    s32 index;

    if (FrameAdvance_IsEnabled(&play->state)) {
        return -1;
    }

    Collider_ResetLineOC(play, line);

    if (colCtxt->colLineCount >= ARRAY_COUNT(colCtxt->colLine)) {
        return -1;
    }
    index = colCtxt->colLineCount;
    colCtxt->colLine[colCtxt->colLineCount++] = line;

    return index;
}

/**
 * Skips AT elements that are off.
 */
s32 CollisionCheck_SkipTouch(ColliderInfo* info) {
    if (!(info->toucherFlags & TOUCH_ON)) {
        return 1;
    }
    return 0;
}

/**
 * Skips AC elements that are off.
 */
s32 CollisionCheck_SkipBump(ColliderInfo* info) {
    if (!(info->bumperFlags & BUMP_ON)) {
        return 1;
    }
    return 0;
}

/**
 * If the AT element has no dmgFlags in common with the AC element, no collision happens.
 */
s32 CollisionCheck_NoSharedFlags(ColliderInfo* toucher, ColliderInfo* bumper) {
    if (!(toucher->toucher.dmgFlags & bumper->bumper.dmgFlags)) {
        return 1;
    }
    return 0;
}

/**
 * Spawns no blood drops.
 * Used by collider types HIT1, HIT3, HIT5, METAL, NONE, WOOD, HARD, and TREE
 */
void CollisionCheck_NoBlood(PlayState* play, Collider* collider, Vec3f* v) {
}

/**
 * Spawns blue blood drops.
 * Used by collider types HIT0 and HIT8.
 */
#ifdef NON_MATCHING
// needs in-function static bss
void CollisionCheck_BlueBlood(PlayState* play, Collider* collider, Vec3f* v) {
    static EffectSparkInit D_801EEC00;
    s32 effectIndex;

    D_801EEC00.position.x = v->x;
    D_801EEC00.position.x = v->y;
    D_801EEC00.position.x = v->z;
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_collision_check/CollisionCheck_BlueBlood.s")
#endif

/**
 * Spawns green blood drops.
 * Used by collider types HIT2 and HIT6. No actor has type HIT2.
 */
#ifdef NON_MATCHING
// needs in-function static bss
void CollisionCheck_GreenBlood(PlayState* play, Collider* collider, Vec3f* v) {
    static EffectSparkInit D_801EF0C8;
    s32 effectIndex;

    D_801EF0C8.position.x = v->x;
    D_801EF0C8.position.x = v->y;
    D_801EF0C8.position.x = v->z;
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_collision_check/CollisionCheck_GreenBlood.s")
#endif

/**
 * Spawns a burst of water.
 * Used by collider type HIT4.
 */
void CollisionCheck_WaterBurst(PlayState* play, Collider* collider, Vec3f* v) {
    EffectSsSibuki_SpawnBurst(play, v);
    CollisionCheck_SpawnWaterDroplets(play, v);
}

/**
 * Spawns red blood drops.
 * Used by collider type HIT7.
 */
void CollisionCheck_RedBlood(PlayState* play, Collider* collider, Vec3f* v) {
    CollisionCheck_SpawnRedBlood(play, v);
}

/**
 * Spawns red blood drops.
 */
void CollisionCheck_RedBloodUnused(PlayState* play, Collider* collider, Vec3f* v) {
    CollisionCheck_SpawnRedBlood(play, v);
}

/**
 * Plays sound effects and displays hitmarks for solid-type AC colliders (METAL, WOOD, HARD, and TREE)
 */
void CollisionCheck_HitSolid(PlayState* play, ColliderInfo* info, Collider* collider, Vec3f* hitPos) {
    s32 flags = info->toucherFlags & TOUCH_SFX_NONE;

    if ((flags == TOUCH_SFX_NORMAL) && (collider->colType != COLTYPE_METAL)) {
        EffectSsHitmark_SpawnFixedScale(play, 0, hitPos);
        if (collider->actor == NULL) {
            Audio_PlaySfx(NA_SE_IT_SHIELD_BOUND);
        } else {
            Audio_PlaySfx_AtPos(&collider->actor->projectedPos, NA_SE_IT_SHIELD_BOUND);
        }
    } else if (flags == TOUCH_SFX_NORMAL) {
        EffectSsHitmark_SpawnFixedScale(play, 3, hitPos);
        if (collider->actor == NULL) {
            CollisionCheck_SpawnShieldParticlesMetal(play, hitPos);
        } else {
            CollisionCheck_SpawnShieldParticlesMetalSound(play, hitPos, &collider->actor->projectedPos);
        }
    } else if (flags == TOUCH_SFX_HARD) {
        EffectSsHitmark_SpawnFixedScale(play, 0, hitPos);
        if (collider->actor == NULL) {
            Audio_PlaySfx(NA_SE_IT_SHIELD_BOUND);
        } else {
            Audio_PlaySfx_AtPos(&collider->actor->projectedPos, NA_SE_IT_SHIELD_BOUND);
        }
    } else if (flags == TOUCH_SFX_WOOD) {
        EffectSsHitmark_SpawnFixedScale(play, 1, hitPos);
        if (collider->actor == NULL) {
            Audio_PlaySfx(NA_SE_IT_REFLECTION_WOOD);
        } else {
            Audio_PlaySfx_AtPos(&collider->actor->projectedPos, NA_SE_IT_REFLECTION_WOOD);
        }
    }
}

/**
 * Plays a hit sound effect for AT colliders attached to Player based on the AC element's elemType.
 */
s32 CollisionCheck_SwordHitAudio(Collider* at, ColliderInfo* acInfo) {
    if ((at->actor != NULL) && (at->actor->category == ACTORCAT_PLAYER)) {
        if (acInfo->elemType == ELEMTYPE_UNK0) {
            Audio_PlaySfx_AtPos(&at->actor->projectedPos, NA_SE_IT_SWORD_STRIKE);
        } else if (acInfo->elemType == ELEMTYPE_UNK1) {
            Audio_PlaySfx_AtPos(&at->actor->projectedPos, NA_SE_IT_SWORD_STRIKE_HARD);
        } else if (acInfo->elemType == ELEMTYPE_UNK2) {
            Audio_PlaySfx_AtPos(&at->actor->projectedPos, 0);
        } else if (acInfo->elemType == ELEMTYPE_UNK3) {
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
void CollisionCheck_HitEffects(PlayState* play, Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo,
                               Vec3f* hitPos) {
    if (acInfo->bumperFlags & BUMP_NO_HITMARK) {
        return;
    }

    if (!(atInfo->toucherFlags & TOUCH_AT_HITMARK) && (atInfo->toucherFlags & TOUCH_DREW_HITMARK)) {
        return;
    }

    if (ac->actor != NULL) {
        sBloodFuncs[sHitInfo[ac->colType].blood](play, ac, hitPos);
    }
    if (ac->actor != NULL) {
        if (sHitInfo[ac->colType].effect == HIT_SOLID) {
            CollisionCheck_HitSolid(play, atInfo, ac, hitPos);
        } else if (sHitInfo[ac->colType].effect == HIT_WOOD) {
            if (at->actor == NULL) {
                CollisionCheck_SpawnShieldParticles(play, hitPos);
                Audio_PlaySfx(NA_SE_IT_REFLECTION_WOOD);
            } else {
                CollisionCheck_SpawnShieldParticlesWood(play, hitPos, &at->actor->projectedPos);
            }
        } else if (sHitInfo[ac->colType].effect != HIT_NONE) {
            EffectSsHitmark_SpawnFixedScale(play, sHitInfo[ac->colType].effect, hitPos);
            if (!(acInfo->bumperFlags & BUMP_NO_SWORD_SFX)) {
                CollisionCheck_SwordHitAudio(at, acInfo);
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
s32 CollisionCheck_SetATvsAC(PlayState* play, Collider* at, ColliderInfo* atInfo, Vec3f* atPos, Collider* ac,
                             ColliderInfo* acInfo, Vec3f* acPos, Vec3f* hitPos) {
    f32 damage;
    u32 effect;

    if (CollisionCheck_GetToucherDamage(at, atInfo, ac, acInfo) != 0) {
        damage = CollisionCheck_GetDamageAndEffectOnBumper(at, atInfo, ac, acInfo, &effect);
        if (damage < 1.0f) {
            if (effect == 0) {
                return 0;
            }
        } else if (CollisionCheck_ApplyBumperDefense(damage, acInfo) < 1.0f && effect == 0) {
            return 0;
        }
    }
    if ((ac->acFlags & AC_HARD) && (at->actor != NULL) && (ac->actor != NULL)) {
        CollisionCheck_SetBounce(at, ac);
    }
    if (!(acInfo->bumperFlags & BUMP_NO_AT_INFO)) {
        at->atFlags |= AT_HIT;
        at->at = ac->actor;
        atInfo->atHit = ac;
        atInfo->toucherFlags |= TOUCH_HIT;
        atInfo->atHitInfo = acInfo;
        if (!(atInfo->bumperFlags & BUMP_HIT)) {
            atInfo->bumper.hitPos.x = hitPos->x;
            atInfo->bumper.hitPos.y = hitPos->y;
            atInfo->bumper.hitPos.z = hitPos->z;
        }
        if (at->actor != NULL) {
            at->actor->colChkInfo.atHitEffect = acInfo->bumper.effect;
        }
    }
    if (!(atInfo->ocElemFlags & OCELEM_UNK2)) {
        ac->acFlags |= AC_HIT;
        ac->ac = at->actor;
        acInfo->acHit = at;
        acInfo->acHitInfo = atInfo;
        acInfo->bumperFlags |= BUMP_HIT;
        if (ac->actor != NULL) {
            ac->actor->colChkInfo.acHitEffect = atInfo->toucher.effect;
        }
        acInfo->bumper.hitPos.x = hitPos->x;
        acInfo->bumper.hitPos.y = hitPos->y;
        acInfo->bumper.hitPos.z = hitPos->z;
    }
    if (!(atInfo->toucherFlags & TOUCH_AT_HITMARK) && (ac->colType != COLTYPE_METAL) && (ac->colType != COLTYPE_WOOD) &&
        (ac->colType != COLTYPE_HARD)) {
        acInfo->bumperFlags |= BUMP_DRAW_HITMARK;
    } else {
        CollisionCheck_HitEffects(play, at, atInfo, ac, acInfo, hitPos);
        atInfo->toucherFlags |= TOUCH_DREW_HITMARK;
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

/**
 * AC overlap check. Calculates the center of each collider element and the point of contact.
 */
void CollisionCheck_AC_JntSphVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC) {
    ColliderJntSph* at = (ColliderJntSph*)colAT;
    ColliderJntSphElement* atElem;
    ColliderJntSph* ac = (ColliderJntSph*)colAC;
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

                if (Math3D_ColSphereSphereIntersectAndDistance(&atElem->dim.worldSphere, &acElem->dim.worldSphere,
                                                               &overlapSize, &centerDist) != 0) {
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
void CollisionCheck_AC_JntSphVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderJntSph* at = (ColliderJntSph*)colAT;
    ColliderJntSphElement* atElem;
    ColliderCylinder* ac = (ColliderCylinder*)colAC;
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
            if (Math3D_ColSphereCylinderDistanceAndAmount(&atElem->dim.worldSphere, &ac->dim, &overlapSize,
                                                          &centerDist)) {
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
void CollisionCheck_AC_JntSphVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderJntSph* at = (ColliderJntSph*)colAT;
    ColliderJntSphElement* atElem;
    ColliderTris* ac = (ColliderTris*)colAC;
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
                if (Math3D_ColSphereTri(&atElem->dim.worldSphere, &acElem->dim, &hitPos) != 0) {
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
void CollisionCheck_AC_JntSphVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderJntSph* at = (ColliderJntSph*)colAT;
    ColliderQuad* ac = (ColliderQuad*)colAC;
    Vec3f hitPos;
    ColliderJntSphElement* sphElem;

    if ((at->count > 0) && (at->elements != NULL)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }
        Math3D_TriSetCoords(&D_801EF590, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EF5C8, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

        for (sphElem = at->elements; sphElem < &at->elements[at->count]; sphElem++) {
            if (CollisionCheck_SkipTouch(&sphElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&sphElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_ColSphereTri(&sphElem->dim.worldSphere, &D_801EF590, &hitPos) != 0 ||
                Math3D_ColSphereTri(&sphElem->dim.worldSphere, &D_801EF5C8, &hitPos) != 0) {
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
void CollisionCheck_AC_JntSphVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC) {
    ColliderJntSph* at = (ColliderJntSph*)colAT;
    ColliderSphere* ac = (ColliderSphere*)colAC;
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
            if (Math3D_ColSphereSphereIntersectAndDistance(&sphElem->dim.worldSphere, &ac->dim.worldSphere,
                                                           &overlapSize, &centerDist) != 0) {
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
void CollisionCheck_AC_CylVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderCylinder* at = (ColliderCylinder*)colAT;
    ColliderJntSph* ac = (ColliderJntSph*)colAC;
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
            if (Math3D_ColSphereCylinderDistanceAndAmount(&sphElem->dim.worldSphere, &at->dim, &overlapSize,
                                                          &centerDist) != 0) {
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
void CollisionCheck_AC_CylVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderCylinder* at = (ColliderCylinder*)colAT;
    ColliderCylinder* ac = (ColliderCylinder*)colAC;
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

        if (Math3D_ColCylinderCylinderAmountAndDistance(&at->dim, &ac->dim, &overlapSize, &centerDist) != 0) {
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
void CollisionCheck_AC_CylVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderCylinder* at = (ColliderCylinder*)colAT;
    ColliderTris* ac = (ColliderTris*)colAC;
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

            if (Math3D_ColCylinderTri(&at->dim, &acElem->dim, &hitPos) != 0) {
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
void CollisionCheck_AC_CylVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderCylinder* at = (ColliderCylinder*)colAT;
    ColliderQuad* ac = (ColliderQuad*)colAC;

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
        Math3D_TriSetCoords(&D_801EF600, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EF638, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

        if (Math3D_ColCylinderTri(&at->dim, &D_801EF600, &D_801EDE00) != 0) {
            Vec3f atPos;
            Vec3f acPos;

            Math_Vec3s_ToVec3f(&atPos, &at->dim.pos);
            CollisionCheck_QuadAvgPoint(ac, &acPos);
            CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &D_801EDE00);
        } else if (Math3D_ColCylinderTri(&at->dim, &D_801EF638, &D_801EDE00) != 0) {
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
void CollisionCheck_AC_CylVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderCylinder* at = (ColliderCylinder*)colAT;
    ColliderSphere* ac = (ColliderSphere*)colAC;
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

        if (Math3D_ColSphereCylinderDistanceAndAmount(&ac->dim.worldSphere, &at->dim, &overlapSize, &centerDist) != 0) {
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
void CollisionCheck_AC_TrisVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderTris* at = (ColliderTris*)colAT;
    ColliderJntSphElement* acElem;
    ColliderJntSph* ac = (ColliderJntSph*)colAC;
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
                if (Math3D_ColSphereTri(&acElem->dim.worldSphere, &atElem->dim, &hitPos)) {
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
void CollisionCheck_AC_TrisVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderTris* at = (ColliderTris*)colAT;
    ColliderCylinder* ac = (ColliderCylinder*)colAC;
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
            if (Math3D_ColCylinderTri(&ac->dim, &atElem->dim, &D_801EDE10) != 0) {
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
void CollisionCheck_AC_TrisVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderTris* at = (ColliderTris*)colAT;
    ColliderTrisElement* atElem;
    ColliderTris* ac = (ColliderTris*)colAC;
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
                if (Math3d_ColTriTri(&atElem->dim, &acElem->dim, &D_801EDE20) != 0) {
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
void CollisionCheck_AC_TrisVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderTris* at = (ColliderTris*)colAT;
    ColliderQuad* ac = (ColliderQuad*)colAC;
    ColliderTrisElement* atElem;

    if ((at->count > 0) && (at->elements != NULL)) {
        if (CollisionCheck_SkipBump(&ac->info)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EDE40, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EDE78, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

        for (atElem = at->elements; atElem < &at->elements[at->count]; atElem++) {
            if (CollisionCheck_SkipTouch(&atElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&atElem->info, &ac->info)) {
                continue;
            }
            if (Math3d_ColTriTri(&D_801EDE40, &atElem->dim, &D_801EDE30) != 0 ||
                Math3d_ColTriTri(&D_801EDE78, &atElem->dim, &D_801EDE30) != 0) {
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
void CollisionCheck_AC_TrisVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderTris* at = (ColliderTris*)colAT;
    ColliderTrisElement* atElem;
    ColliderSphere* ac = (ColliderSphere*)colAC;
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
            if (Math3D_ColSphereTri(&ac->dim.worldSphere, &atElem->dim, &hitPos) != 0) {
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
void CollisionCheck_AC_QuadVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderJntSphElement* acElem;
    Vec3f hitPos;
    ColliderQuad* at = (ColliderQuad*)colAT;
    ColliderJntSph* ac = (ColliderJntSph*)colAC;

    if ((ac->count > 0) && (ac->elements != NULL)) {
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }
        Math3D_TriSetCoords(&D_801EDEC8, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EDF00, &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);

        for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
            if (CollisionCheck_SkipBump(&acElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&at->info, &acElem->info)) {
                continue;
            }
            if (Math3D_ColSphereTri(&acElem->dim.worldSphere, &D_801EDEC8, &hitPos) != 0 ||
                Math3D_ColSphereTri(&acElem->dim.worldSphere, &D_801EDF00, &hitPos) != 0) {
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
void CollisionCheck_AC_QuadVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderQuad* at = (ColliderQuad*)colAT;
    ColliderCylinder* ac = (ColliderCylinder*)colAC;

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

        Math3D_TriSetCoords(&D_801EDF58, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EDF90, &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);

        if (Math3D_ColCylinderTri(&ac->dim, &D_801EDF58, &D_801EDFE0) != 0) {
            if (Collider_QuadSetNearestAC(play, at, &D_801EDFE0)) {
                Vec3f atPos;
                Vec3f acPos;

                CollisionCheck_QuadAvgPoint(at, &atPos);
                Math_Vec3s_ToVec3f(&acPos, &ac->dim.pos);
                CollisionCheck_SetATvsAC(play, &at->base, &at->info, &atPos, &ac->base, &ac->info, &acPos, &D_801EDFE0);
                return;
            }
        }
        if (Math3D_ColCylinderTri(&ac->dim, &D_801EDF90, &D_801EDFE0) != 0) {
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
void CollisionCheck_AC_QuadVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderQuad* at = (ColliderQuad*)colAT;
    ColliderTris* ac = (ColliderTris*)colAC;
    ColliderTrisElement* acElem;

    if ((ac->count > 0) && (ac->elements != NULL)) {
        if (CollisionCheck_SkipTouch(&at->info)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EE000, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EE038, &at->dim.quad[1], &at->dim.quad[0], &at->dim.quad[2]);

        for (acElem = ac->elements; acElem < &ac->elements[ac->count]; acElem++) {
            if (CollisionCheck_SkipBump(&acElem->info)) {
                continue;
            }
            if (CollisionCheck_NoSharedFlags(&at->info, &acElem->info)) {
                continue;
            }

            if ((Math3d_ColTriTri(&D_801EE000, &acElem->dim, &D_801EDFF0) != 0) ||
                (Math3d_ColTriTri(&D_801EE038, &acElem->dim, &D_801EDFF0) != 0)) {
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
void CollisionCheck_AC_QuadVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderQuad* at = (ColliderQuad*)colAT;
    ColliderQuad* ac = (ColliderQuad*)colAC;
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

    Math3D_TriSetCoords(&D_801EE0E8[0], &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
    Math3D_TriSetCoords(&D_801EE0E8[1], &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);
    Math3D_TriSetCoords(&D_801EE070[0], &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
    Math3D_TriSetCoords(&D_801EE070[1], &ac->dim.quad[2], &ac->dim.quad[1], &ac->dim.quad[0]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (Math3d_ColTriTri(&D_801EE0E8[j], &D_801EE070[i], &D_801EE0D8) != 0 &&
                Collider_QuadSetNearestAC(play, at, &D_801EE0D8) != 0) {
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
void CollisionCheck_AC_QuadVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderQuad* at = (ColliderQuad*)colAT;
    Vec3f hitPos;
    ColliderSphere* ac = (ColliderSphere*)colAC;

    if (CollisionCheck_SkipTouch(&at->info)) {
        return;
    }
    if (CollisionCheck_SkipBump(&ac->info) || CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
        return;
    }

    Math3D_TriSetCoords(&D_801EE150, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
    Math3D_TriSetCoords(&D_801EE188, &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);

    if ((Math3D_ColSphereTri(&ac->dim.worldSphere, &D_801EE150, &hitPos) != 0) ||
        (Math3D_ColSphereTri(&ac->dim.worldSphere, &D_801EE188, &hitPos) != 0)) {
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
void CollisionCheck_AC_SphereVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC) {
    ColliderSphere* at = (ColliderSphere*)colAT;
    ColliderJntSph* ac = (ColliderJntSph*)colAC;
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

            if (Math3D_ColSphereSphereIntersectAndDistance(&at->dim.worldSphere, &acElem->dim.worldSphere, &overlapSize,
                                                           &centerDist) != 0) {
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
void CollisionCheck_AC_SphereVsCylinder(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                        Collider* colAC) {
    ColliderCylinder* ac = (ColliderCylinder*)colAC;
    ColliderSphere* at = (ColliderSphere*)colAT;
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

    if (Math3D_ColSphereCylinderDistanceAndAmount(&at->dim.worldSphere, &ac->dim, &overlapSize, &centerDist) != 0) {
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
void CollisionCheck_AC_SphereVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderSphere* at = (ColliderSphere*)colAT;
    ColliderTris* ac = (ColliderTris*)colAC;
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
        if (Math3D_ColSphereTri(&at->dim.worldSphere, &acElem->dim, &hitPos) != 0) {
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
void CollisionCheck_AC_SphereVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC) {
    ColliderSphere* at = (ColliderSphere*)colAT;
    Vec3f hitPos;
    ColliderQuad* ac = (ColliderQuad*)colAC;

    if (CollisionCheck_SkipTouch(&at->info)) {
        return;
    }
    if (CollisionCheck_SkipBump(&ac->info) || CollisionCheck_NoSharedFlags(&at->info, &ac->info)) {
        return;
    }

    Math3D_TriSetCoords(&D_801EE6C8, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
    Math3D_TriSetCoords(&D_801EE700, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

    if (Math3D_ColSphereTri(&at->dim.worldSphere, &D_801EE6C8, &hitPos) != 0 ||
        Math3D_ColSphereTri(&at->dim.worldSphere, &D_801EE700, &hitPos) != 0) {
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
void CollisionCheck_AC_SphereVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC) {
    ColliderSphere* at = (ColliderSphere*)colAT;
    ColliderSphere* ac = (ColliderSphere*)colAC;
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

    if (Math3D_ColSphereSphereIntersectAndDistance(&at->dim.worldSphere, &ac->dim.worldSphere, &overlapSize,
                                                   &centerDist) != 0) {
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
void CollisionCheck_SetJntSphHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderJntSph* jntSph = (ColliderJntSph*)collider;
    ColliderJntSphElement* element;

    for (element = jntSph->elements; element < &jntSph->elements[jntSph->count]; element++) {
        if ((element->info.bumperFlags & BUMP_DRAW_HITMARK) && (element->info.acHitInfo != NULL) &&
            !(element->info.acHitInfo->toucherFlags & TOUCH_DREW_HITMARK)) {
            Vec3f hitPos;

            Math_Vec3s_ToVec3f(&hitPos, &element->info.bumper.hitPos);
            CollisionCheck_HitEffects(play, element->info.acHit, element->info.acHitInfo, &jntSph->base, &element->info,
                                      &hitPos);
            element->info.acHitInfo->toucherFlags |= TOUCH_DREW_HITMARK;
            return;
        }
    }
}

/**
 * Sets a ColliderCylinder's hit effects
 */
void CollisionCheck_SetCylHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderCylinder* cylinder = (ColliderCylinder*)collider;

    if ((cylinder->info.bumperFlags & BUMP_DRAW_HITMARK) && (cylinder->info.acHitInfo != NULL) &&
        !(cylinder->info.acHitInfo->toucherFlags & TOUCH_DREW_HITMARK)) {
        Vec3f hitPos;

        Math_Vec3s_ToVec3f(&hitPos, &cylinder->info.bumper.hitPos);
        CollisionCheck_HitEffects(play, cylinder->info.acHit, cylinder->info.acHitInfo, &cylinder->base,
                                  &cylinder->info, &hitPos);
        cylinder->info.acHitInfo->toucherFlags |= TOUCH_DREW_HITMARK;
    }
}

/**
 * Sets a ColliderTris's hit effects
 */
void CollisionCheck_SetTrisHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderTris* tris = (ColliderTris*)collider;
    ColliderTrisElement* element;

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        if ((element->info.bumperFlags & BUMP_DRAW_HITMARK) && (element->info.acHitInfo != NULL) &&
            !(element->info.acHitInfo->toucherFlags & TOUCH_DREW_HITMARK)) {
            Vec3f hitPos;

            Math_Vec3s_ToVec3f(&hitPos, &element->info.bumper.hitPos);
            CollisionCheck_HitEffects(play, element->info.acHit, element->info.acHitInfo, &tris->base, &element->info,
                                      &hitPos);
            element->info.acHitInfo->toucherFlags |= TOUCH_DREW_HITMARK;
            return;
        }
    }
}

/**
 * Sets a ColliderQuad's hit effects
 */
void CollisionCheck_SetQuadHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderQuad* quad = (ColliderQuad*)collider;

    if ((quad->info.bumperFlags & BUMP_DRAW_HITMARK) && (quad->info.acHitInfo != NULL) &&
        !(quad->info.acHitInfo->toucherFlags & TOUCH_DREW_HITMARK)) {
        Vec3f hitPos;

        Math_Vec3s_ToVec3f(&hitPos, &quad->info.bumper.hitPos);
        CollisionCheck_HitEffects(play, quad->info.acHit, quad->info.acHitInfo, &quad->base, &quad->info, &hitPos);
        quad->info.acHitInfo->toucherFlags |= TOUCH_DREW_HITMARK;
    }
}

/**
 * Sets a ColliderSphere's hit effects
 */
void CollisionCheck_SetSphereHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderSphere* sphere = (ColliderSphere*)collider;

    if ((sphere->info.bumperFlags & BUMP_DRAW_HITMARK) && (sphere->info.acHitInfo != NULL) &&
        !(sphere->info.acHitInfo->toucherFlags & TOUCH_DREW_HITMARK)) {
        Vec3f hitPos;

        Math_Vec3s_ToVec3f(&hitPos, &sphere->info.bumper.hitPos);
        CollisionCheck_HitEffects(play, sphere->info.acHit, sphere->info.acHitInfo, &sphere->base, &sphere->info,
                                  &hitPos);
        sphere->info.acHitInfo->toucherFlags |= TOUCH_DREW_HITMARK;
    }
}

ColChkApplyFunc sColChkApplyFuncs[] = {
    CollisionCheck_SetJntSphHitFX, CollisionCheck_SetCylHitFX,    CollisionCheck_SetTrisHitFX,
    CollisionCheck_SetQuadHitFX,   CollisionCheck_SetSphereHitFX,
};

/**
 * Handles hit effects for each AC collider that had an AC collision. Spawns hitmarks and plays sound effects.
 */
void CollisionCheck_SetHitEffects(PlayState* play, CollisionCheckContext* colCtxt) {
    Collider** col;

    for (col = &colCtxt->colAC[0]; col < &colCtxt->colAC[colCtxt->colACCount]; col++) {
        Collider* colAC = *col;

        if ((colAC != NULL) && (colAC->acFlags & AC_ON)) {
            if ((colAC->actor != NULL) && (colAC->actor->update == NULL)) {
                continue;
            }
            sColChkApplyFuncs[colAC->shape](play, colCtxt, colAC);
        }
    }
}

ColChkVsFunc sACVsFuncs[COLSHAPE_MAX][COLSHAPE_MAX] = {
    { CollisionCheck_AC_JntSphVsJntSph, CollisionCheck_AC_JntSphVsCyl, CollisionCheck_AC_JntSphVsTris,
      CollisionCheck_AC_JntSphVsQuad, CollisionCheck_AC_JntSphVsSphere },
    { CollisionCheck_AC_CylVsJntSph, CollisionCheck_AC_CylVsCyl, CollisionCheck_AC_CylVsTris,
      CollisionCheck_AC_CylVsQuad, CollisionCheck_AC_CylVsSphere },
    { CollisionCheck_AC_TrisVsJntSph, CollisionCheck_AC_TrisVsCyl, CollisionCheck_AC_TrisVsTris,
      CollisionCheck_AC_TrisVsQuad, CollisionCheck_AC_TrisVsSphere },
    { CollisionCheck_AC_QuadVsJntSph, CollisionCheck_AC_QuadVsCyl, CollisionCheck_AC_QuadVsTris,
      CollisionCheck_AC_QuadVsQuad, CollisionCheck_AC_QuadVsSphere },
    { CollisionCheck_AC_SphereVsJntSph, CollisionCheck_AC_SphereVsCylinder, CollisionCheck_AC_SphereVsTris,
      CollisionCheck_AC_SphereVsQuad, CollisionCheck_AC_SphereVsSphere },
};

/**
 * Iterates through all AC colliders, performing AC collisions with the AT collider.
 */
void CollisionCheck_AC(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT) {
    Collider** col;

    for (col = &colCtxt->colAC[0]; col < &colCtxt->colAC[colCtxt->colACCount]; col++) {
        Collider* colAC = *col;

        if ((colAC != NULL) && (colAC->acFlags & AC_ON)) {
            if ((colAC->actor != NULL) && (colAC->actor->update == NULL)) {
                continue;
            }
            if ((colAC->acFlags & colAT->atFlags & AC_TYPE_ALL) && (colAT != colAC)) {
                if (!(colAT->atFlags & AT_SELF) && (colAT->actor != NULL) && (colAC->actor == colAT->actor)) {
                    continue;
                }
                sACVsFuncs[colAT->shape][colAC->shape](play, colCtxt, colAT, colAC);
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
void CollisionCheck_AT(PlayState* play, CollisionCheckContext* colCtxt) {
    Collider** col;

    if ((colCtxt->colATCount == 0) || (colCtxt->colACCount == 0)) {
        return;
    }

    for (col = &colCtxt->colAT[0]; col < &colCtxt->colAT[colCtxt->colATCount]; col++) {
        Collider* colAC = *col;

        if ((colAC != NULL) && (colAC->atFlags & AT_ON)) {
            if ((colAC->actor != NULL) && (colAC->actor->update == NULL)) {
                continue;
            }
            CollisionCheck_AC(play, colCtxt, colAC);
        }
    }

    CollisionCheck_SetHitEffects(play, colCtxt);
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
void CollisionCheck_SetOCvsOC(PlayState* play, Collider* left, ColliderInfo* leftInfo, Vec3f* leftPos, Collider* right,
                              ColliderInfo* rightInfo, Vec3f* rightPos, f32 overlap) {
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
    Actor* leftActor = left->actor;
    Actor* rightActor = right->actor;
    s32 leftMassType;
    s32 rightMassType;

    left->ocFlags1 |= OC1_HIT;
    left->oc = rightActor;
    leftInfo->ocElemFlags |= OCELEM_HIT;
    if (right->ocFlags2 & OC2_TYPE_PLAYER) {
        left->ocFlags2 |= OC2_HIT_PLAYER;
    }

    right->ocFlags1 |= OC1_HIT;
    right->oc = leftActor;
    rightInfo->ocElemFlags |= OCELEM_HIT;
    if (left->ocFlags2 & OC2_TYPE_PLAYER) {
        right->ocFlags2 |= OC2_HIT_PLAYER;
    }

    if ((leftActor == NULL) || (rightActor == NULL) || (left->ocFlags1 & OC1_NO_PUSH) ||
        (right->ocFlags1 & OC1_NO_PUSH)) {
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
        xDelta *= overlap / xzDist;
        zDelta *= overlap / xzDist;
        leftActor->colChkInfo.displacement.x += -xDelta * leftDispRatio;
        leftActor->colChkInfo.displacement.z += -zDelta * leftDispRatio;
        rightActor->colChkInfo.displacement.x += xDelta * rightDispRatio;
        rightActor->colChkInfo.displacement.z += zDelta * rightDispRatio;
    } else if (overlap != 0.0f) {
        leftActor->colChkInfo.displacement.x += -overlap * leftDispRatio;
        rightActor->colChkInfo.displacement.x += overlap * rightDispRatio;
    } else {
        leftActor->colChkInfo.displacement.x += -leftDispRatio;
        rightActor->colChkInfo.displacement.x += rightDispRatio;
    }
}

/**
 * OC overlap check for two JntSphs
 */
void CollisionCheck_OC_JntSphVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r) {
    ColliderJntSph* left = (ColliderJntSph*)l;
    ColliderJntSph* right = (ColliderJntSph*)r;
    ColliderJntSphElement* leftElem;
    ColliderJntSphElement* rightElem;
    f32 overlap;

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
                if (Math3D_ColSphereSphereIntersect(&leftElem->dim.worldSphere, &rightElem->dim.worldSphere,
                                                    &overlap) != 0) {
                    Vec3f leftPos;
                    Vec3f rightPos;

                    Math_Vec3s_ToVec3f(&leftPos, &leftElem->dim.worldSphere.center);
                    Math_Vec3s_ToVec3f(&rightPos, &rightElem->dim.worldSphere.center);
                    CollisionCheck_SetOCvsOC(play, &left->base, &leftElem->info, &leftPos, &right->base,
                                             &rightElem->info, &rightPos, overlap);
                }
            }
        }
    }
}

/**
 * OC overlap check for a JntSph and Cylinder
 */
void CollisionCheck_OC_JntSphVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r) {
    ColliderJntSph* left = (ColliderJntSph*)l;
    ColliderCylinder* right = (ColliderCylinder*)r;
    ColliderJntSphElement* leftElem;
    f32 overlap;

    if ((left->count > 0) && (left->elements != NULL) && (left->base.ocFlags1 & OCELEM_ON) &&
        (right->base.ocFlags1 & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {

        for (leftElem = left->elements; leftElem < &left->elements[left->count]; leftElem++) {
            if (!(leftElem->info.ocElemFlags & OCELEM_ON)) {
                continue;
            }
            if (Math3D_ColSphereCylinderDistance(&leftElem->dim.worldSphere, &right->dim, &overlap) != 0) {
                Vec3f leftPos;
                Vec3f rightPos;

                Math_Vec3s_ToVec3f(&leftPos, &leftElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&rightPos, &right->dim.pos);
                CollisionCheck_SetOCvsOC(play, &left->base, &leftElem->info, &leftPos, &right->base, &right->info,
                                         &rightPos, overlap);
            }
        }
    }
}

/**
 * OC overlap check for a JntSph and Sphere
 */
void CollisionCheck_OC_JntSphVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r) {
    ColliderJntSph* left = (ColliderJntSph*)l;
    ColliderSphere* right = (ColliderSphere*)r;
    ColliderJntSphElement* leftElem;
    f32 overlap;

    if ((left->count > 0) && (left->elements != NULL) && (left->base.ocFlags1 & OCELEM_ON) &&
        (right->base.ocFlags1 & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {

        for (leftElem = left->elements; leftElem < &left->elements[left->count]; leftElem++) {
            if (!(leftElem->info.ocElemFlags & OCELEM_ON)) {
                continue;
            }
            if (Math3D_ColSphereSphereIntersect(&leftElem->dim.worldSphere, &right->dim.worldSphere, &overlap) != 0) {
                Vec3f leftPos;
                Vec3f rightPos;

                Math_Vec3s_ToVec3f(&leftPos, &leftElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&rightPos, &right->dim.worldSphere.center);
                CollisionCheck_SetOCvsOC(play, &left->base, &leftElem->info, &leftPos, &right->base, &right->info,
                                         &rightPos, overlap);
            }
        }
    }
}

/**
 * OC overlap check for a Cylinder and JntSph
 */
void CollisionCheck_OC_CylVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r) {
    CollisionCheck_OC_JntSphVsCyl(play, colCtxt, r, l);
}

/**
 * OC overlap check for two Cylinders
 */
void CollisionCheck_OC_CylVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r) {
    ColliderCylinder* left = (ColliderCylinder*)l;
    ColliderCylinder* right = (ColliderCylinder*)r;
    f32 overlap;

    if ((left->base.ocFlags1 & OCELEM_ON) && (right->base.ocFlags1 & OCELEM_ON) &&
        (left->info.ocElemFlags & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {
        if (Math3D_ColCylinderCylinderAmount(&left->dim, &right->dim, &overlap) != 0) {
            Vec3f leftPos;
            Vec3f rightPos;

            Math_Vec3s_ToVec3f(&leftPos, &left->dim.pos);
            Math_Vec3s_ToVec3f(&rightPos, &right->dim.pos);
            CollisionCheck_SetOCvsOC(play, &left->base, &left->info, &leftPos, &right->base, &right->info, &rightPos,
                                     overlap);
        }
    }
}

/**
 * OC overlap check for a Cylinder and Sphere
 */
void CollisionCheck_OC_CylVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r) {
    ColliderCylinder* left = (ColliderCylinder*)l;
    ColliderSphere* right = (ColliderSphere*)r;
    f32 overlap;

    if ((left->base.ocFlags1 & OCELEM_ON) && (left->info.ocElemFlags & OCELEM_ON) &&
        (right->base.ocFlags1 & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {
        if (Math3D_ColSphereCylinderDistance(&right->dim.worldSphere, &left->dim, &overlap) != 0) {
            Vec3f leftPos;
            Vec3f rightPos;

            Math_Vec3s_ToVec3f(&leftPos, &left->dim.pos);
            Math_Vec3s_ToVec3f(&rightPos, &right->dim.worldSphere.center);
            CollisionCheck_SetOCvsOC(play, &left->base, &left->info, &leftPos, &right->base, &right->info, &rightPos,
                                     overlap);
        }
    }
}

/**
 * OC overlap check for a Sphere and JntSph
 */
void CollisionCheck_OC_SphereVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r) {
    CollisionCheck_OC_JntSphVsSphere(play, colCtxt, r, l);
}

/**
 * OC overlap check for a Sphere and Cylinder
 */
void CollisionCheck_OC_SphereVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r) {
    CollisionCheck_OC_CylVsSphere(play, colCtxt, r, l);
}

/**
 * OC overlap check for two Spheres
 */
void CollisionCheck_OC_SphereVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r) {
    ColliderSphere* left = (ColliderSphere*)l;
    ColliderSphere* right = (ColliderSphere*)r;
    f32 overlap;

    if ((left->base.ocFlags1 & OCELEM_ON) && (left->info.ocElemFlags & OCELEM_ON) &&
        (right->base.ocFlags1 & OCELEM_ON) && (right->info.ocElemFlags & OCELEM_ON)) {
        if (Math3D_ColSphereSphereIntersect(&left->dim.worldSphere, &right->dim.worldSphere, &overlap) != 0) {
            Vec3f leftPos;
            Vec3f rightPos;

            Math_Vec3s_ToVec3f(&leftPos, &left->dim.worldSphere.center);
            Math_Vec3s_ToVec3f(&rightPos, &right->dim.worldSphere.center);
            CollisionCheck_SetOCvsOC(play, &left->base, &left->info, &leftPos, &right->base, &right->info, &rightPos,
                                     overlap);
        }
    }
}

/**
 *  Skip any OC colliders that are off
 */
s32 CollisionCheck_SkipOC(Collider* collider) {
    if (!(collider->ocFlags1 & OCELEM_ON)) {
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
s32 CollisionCheck_Incompatible(Collider* left, Collider* right) {
    if (!(left->ocFlags1 & right->ocFlags2 & OC1_TYPE_ALL) || !(left->ocFlags2 & right->ocFlags1 & OC1_TYPE_ALL) ||
        ((left->ocFlags2 & OC2_UNK1) && (right->ocFlags2 & OC2_UNK2)) ||
        ((right->ocFlags2 & OC2_UNK1) && (left->ocFlags2 & OC2_UNK2))) {
        return 1;
    }
    if (left->actor == right->actor) {
        return 1;
    }
    return 0;
}

ColChkVsFunc sOCVsFuncs[COLSHAPE_MAX][COLSHAPE_MAX] = {
    { CollisionCheck_OC_JntSphVsJntSph, CollisionCheck_OC_JntSphVsCyl, NULL, NULL, CollisionCheck_OC_JntSphVsSphere },
    { CollisionCheck_OC_CylVsJntSph, CollisionCheck_OC_CylVsCyl, NULL, NULL, CollisionCheck_OC_CylVsSphere },
    { NULL, NULL, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL },
    { CollisionCheck_OC_SphereVsJntSph, CollisionCheck_OC_SphereVsCyl, NULL, NULL, CollisionCheck_OC_SphereVsSphere },
};

/**
 * Iterates through all OC colliders and collides them with all subsequent OC colliders on the list. During an OC
 * collision, colliders with overlapping elements move away from each other so that their elements no longer overlap.
 * The relative amount each collider is pushed is determined by the collider's mass. Only JntSph, Cylinder and Sphere
 * colliders can collide, and each collider must have the OC flag corresponding to the other's OC type. Additionally,
 * OC2_UNK1 cannot collide with OC2_UNK2, nor can two colliders that share an actor.
 */
void CollisionCheck_OC(PlayState* play, CollisionCheckContext* colCtxt) {
    Collider** left;
    Collider** right;
    ColChkVsFunc vsFunc;

    for (left = colCtxt->colOC; left < colCtxt->colOC + colCtxt->colOCCount; left++) {
        if ((*left == NULL) || CollisionCheck_SkipOC(*left)) {
            continue;
        }
        for (right = left + 1; right < colCtxt->colOC + colCtxt->colOCCount; right++) {
            if ((*right == NULL) || CollisionCheck_SkipOC(*right) || CollisionCheck_Incompatible(*left, *right)) {
                continue;
            }
            vsFunc = sOCVsFuncs[(*left)->shape][(*right)->shape];
            if (vsFunc == NULL) {
                continue;
            }
            vsFunc(play, colCtxt, *left, *right);
        }
    }
}

/**
 * Initializes CollisionCheckInfo to default values
 */
void CollisionCheck_InitInfo(CollisionCheckInfo* info) {
    static CollisionCheckInfo defaultColChkInfo = {
        NULL, { 0.0f, 0.0f, 0.0f }, 10, 10, 0, MASS_IMMOVABLE, 8, 0, 0, 0, 0,
    };

    *info = defaultColChkInfo;
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
void CollisionCheck_ApplyDamage(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider,
                                ColliderInfo* info) {
    f32 damage;
    f32 finalDamage = 0.0f;
    s32 pad;
    Collider* at;
    ColliderInfo* atInfo;
    s32 pad1;
    u32 effect;

    if ((collider->actor == NULL) || !(collider->acFlags & AC_HIT)) {
        return;
    }
    if (!(info->bumperFlags & BUMP_HIT) || (info->bumperFlags & BUMP_NO_DAMAGE)) {
        return;
    }

    at = info->acHit;
    atInfo = info->acHitInfo;

    if ((at != NULL) && (atInfo != NULL) && (collider != NULL) && (info != NULL)) {
        damage = CollisionCheck_GetDamageAndEffectOnBumper(at, atInfo, collider, info, &effect);

        if (CollisionCheck_GetToucherDamage(at, atInfo, collider, info) != 0) {
            if (damage < 1.0f) {
                finalDamage = 0.0f;
                if (effect == 0) {
                    return;
                }
            } else {
                finalDamage = CollisionCheck_ApplyBumperDefense(damage, info);
                if (finalDamage < 1.0f && effect == 0) {
                    return;
                }
            }
        }
        if (collider->actor->colChkInfo.damageTable != NULL) {
            collider->actor->colChkInfo.damageEffect = effect;
        }
        if (!(collider->acFlags & AC_HARD) ||
            ((collider->acFlags & AC_HARD) && (atInfo->toucher.dmgFlags == 0x20000000))) {
            if (collider->actor->colChkInfo.damage < finalDamage) {
                collider->actor->colChkInfo.damage = finalDamage;
            }
        }
    }
}

/**
 * Apply ColliderJntSph AC damage effect
 */
void CollisionCheck_ApplyDamageJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderJntSph* jntSph = (ColliderJntSph*)collider;
    s32 i;

    if ((jntSph->count > 0) && (jntSph->elements != NULL)) {
        for (i = 0; i < jntSph->count; i++) {
            CollisionCheck_ApplyDamage(play, colCtxt, &jntSph->base, &jntSph->elements[i].info);
        }
    }
}

/**
 * Apply ColliderCylinder AC damage effect
 */
void CollisionCheck_ApplyDamageCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderCylinder* cylinder = (ColliderCylinder*)collider;

    CollisionCheck_ApplyDamage(play, colCtxt, &cylinder->base, &cylinder->info);
}

/**
 * Apply ColliderTris AC damage effect
 */
void CollisionCheck_ApplyDamageTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderTris* tris = (ColliderTris*)collider;
    s32 i;

    // unlike sphere groups above, tri groups are not guarded against
    //  tris->elements being NULL
    for (i = 0; i < tris->count; i++) {
        CollisionCheck_ApplyDamage(play, colCtxt, &tris->base, &tris->elements[i].info);
    }
}

/**
 * Apply ColliderQuad AC damage effect
 */
void CollisionCheck_ApplyDamageQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderQuad* quad = (ColliderQuad*)collider;

    CollisionCheck_ApplyDamage(play, colCtxt, &quad->base, &quad->info);
}

/**
 * Apply ColliderSphere AC damage effect
 */
void CollisionCheck_ApplyDamageSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider) {
    ColliderSphere* sphere = (ColliderSphere*)collider;

    CollisionCheck_ApplyDamage(play, colCtxt, &sphere->base, &sphere->info);
}

ColChkApplyFunc sApplyDamageFuncs[] = {
    CollisionCheck_ApplyDamageJntSph, CollisionCheck_ApplyDamageCyl,    CollisionCheck_ApplyDamageTris,
    CollisionCheck_ApplyDamageQuad,   CollisionCheck_ApplyDamageSphere,
};

/**
 * For all AC colliders, sets any damage effects from collisions with AT colliders to their corresponding actor's
 * CollisionCheckInfo.
 */
void CollisionCheck_Damage(PlayState* play, CollisionCheckContext* colCtxt) {
    s32 i;

    for (i = 0; i < colCtxt->colACCount; i++) {
        Collider* col = colCtxt->colAC[i];

        if (col == NULL) {
            continue;
        }
        if (col->acFlags & AC_NO_DAMAGE) {
            continue;
        }
        sApplyDamageFuncs[col->shape](play, colCtxt, col);
    }
}

/**
 * Checks if the line segment ab intersects any of the ColliderJntSph's elements
 */
s32 CollisionCheck_LineOC_JntSph(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a,
                                 Vec3f* b) {
    ColliderJntSph* jntSph = (ColliderJntSph*)collider;
    s32 i;

    for (i = 0; i < jntSph->count; i++) {
        ColliderJntSphElement* element = &jntSph->elements[i];

        if (!(element->info.ocElemFlags & OCELEM_ON)) {
            continue;
        }

        D_801EDEB0.a = *a;
        D_801EDEB0.b = *b;
        if (Math3D_LineVsSph(&element->dim.worldSphere, &D_801EDEB0) != 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * Checks if the line segment ab intersects the ColliderCylinder
 */
s32 CollisionCheck_LineOC_Cyl(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a,
                              Vec3f* b) {
    ColliderCylinder* cylinder = (ColliderCylinder*)collider;

    if (!(cylinder->info.ocElemFlags & OCELEM_ON)) {
        return 0;
    }

    if (func_8017E350(&cylinder->dim, a, b, &D_801EDF38, &D_801EDF48) != 0) {
        return 1;
    }

    return 0;
}

/**
 * Checks if the line segment ab intersects the ColliderSphere
 */
s32 CollisionCheck_LineOC_Sphere(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a,
                                 Vec3f* b) {
    ColliderSphere* sphere = (ColliderSphere*)collider;

    if (!(sphere->info.ocElemFlags & OCELEM_ON)) {
        return 0;
    }

    D_801EDFC8.a = *a;
    D_801EDFC8.b = *b;
    if (Math3D_LineVsSph(&sphere->dim.worldSphere, &D_801EDFC8) != 0) {
        return 1;
    }

    return 0;
}

ColChkLineFunc sOCLineCheckFuncs[] = {
    CollisionCheck_LineOC_JntSph, CollisionCheck_LineOC_Cyl, NULL, NULL, CollisionCheck_LineOC_Sphere,
};

/**
 * Checks if the line segment ab intersects any OC colliders, excluding those attached to actors
 * on the exclusion list. Returns true if there are any intersections and false otherwise.
 */
s32 CollisionCheck_LineOC(PlayState* play, CollisionCheckContext* colChkCtx, Vec3f* a, Vec3f* b, Actor** exclusions,
                          s32 numExclusions) {
    ColChkLineFunc lineCheck;
    Collider** col;
    s32 i;
    s32 exclude;
    s32 result = 0;

    for (col = colChkCtx->colOC; col < &colChkCtx->colOC[colChkCtx->colOCCount]; col++) {
        if (CollisionCheck_SkipOC(*col)) {
            continue;
        }

        exclude = 0;
        for (i = 0; i < numExclusions; i++) {
            if ((*col)->actor == exclusions[i]) {
                exclude = 1;
                break;
            }
        }
        if (exclude) {
            continue;
        }

        lineCheck = sOCLineCheckFuncs[(*col)->shape];
        if (lineCheck == NULL) {
            continue;
        }

        result = lineCheck(play, colChkCtx, (*col), a, b);
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
s32 CollisionCheck_LineOCCheckAll(PlayState* play, CollisionCheckContext* colCtxt, Vec3f* a, Vec3f* b) {
    return CollisionCheck_LineOC(play, colCtxt, a, b, NULL, 0);
}

/**
 * Checks if the line segment ab intersects any OC colliders, excluding those attached to actors on the exclusion list.
 * Returns true if there are any intersections and false otherwise.
 */
s32 CollisionCheck_LineOCCheck(PlayState* play, CollisionCheckContext* colCtxt, Vec3f* a, Vec3f* b, Actor** exclusions,
                               s32 numExclusions) {
    return CollisionCheck_LineOC(play, colCtxt, a, b, exclusions, numExclusions);
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
    Math3D_UnitNormalVector(a, b, c, &nx, &ny, &nz, &originDist);
    element->dim.plane.normal.x = nx;
    element->dim.plane.normal.y = ny;
    element->dim.plane.normal.z = nz;
    element->dim.plane.originDist = originDist;
}

/**
 * Sets the specified ColliderTrisElement's dim using the values in src
 */
void Collider_SetTrisDim(PlayState* play, ColliderTris* collider, s32 index, ColliderTrisElementDimInit* init) {
    ColliderTrisElement* element = &collider->elements[index];

    Collider_SetTrisElementDim(play, &element->dim, init);
}

/**
 * Updates the world spheres for all of the collider's JntSph elements attached to the specified limb
 */
#ifdef NON_MATCHING
// needs in-function static bss
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_collision_check/Collider_UpdateSpheres.s")
#endif

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
#ifdef NON_MATCHING
// needs in-function static bss
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_collision_check/Collider_UpdateSphere.s")
#endif

/**
 * Spawns red blood droplets.
 * No actor has a collision type that spawns red blood.
 */
#ifdef NON_MATCHING
// needs in-function static bss
void CollisionCheck_SpawnRedBlood(PlayState* play, Vec3f* v) {
    static EffectSparkInit D_801EE200;
    s32 effectIndex;

    D_801EE200.position.x = v->x;
    D_801EE200.position.x = v->y;
    D_801EE200.position.x = v->z;
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_collision_check/CollisionCheck_SpawnRedBlood.s")
#endif

/**
 * Spawns water droplets.
 * No actor has a collision type that spawns water droplets.
 */
#ifdef NON_MATCHING
// needs in-function static bss
void CollisionCheck_SpawnWaterDroplets(PlayState* play, Vec3f* v) {
    static EffectSparkInit D_801EE738;
    s32 effectIndex;

    D_801EE738.position.x = v->x;
    D_801EE738.position.x = v->y;
    D_801EE738.position.x = v->z;
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_collision_check/CollisionCheck_SpawnWaterDroplets.s")
#endif

/**
 * Spawns streaks of light from hits against solid objects
 */
void CollisionCheck_SpawnShieldParticles(PlayState* play, Vec3f* v) {
    static EffectShieldParticleInit shieldParticleInitMetal = {
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

    shieldParticleInitMetal.position.x = v->x;
    shieldParticleInitMetal.position.y = v->y;
    shieldParticleInitMetal.position.z = v->z;
    shieldParticleInitMetal.lightPoint.x = shieldParticleInitMetal.position.x;
    shieldParticleInitMetal.lightPoint.y = shieldParticleInitMetal.position.y;
    shieldParticleInitMetal.lightPoint.z = shieldParticleInitMetal.position.z;

    Effect_Add(play, &effectIndex, EFFECT_SHIELD_PARTICLE, 0, 1, &shieldParticleInitMetal);
}

/**
 * Spawns streaks of light and makes a metallic sound
 */
void CollisionCheck_SpawnShieldParticlesMetal(PlayState* play, Vec3f* v) {
    CollisionCheck_SpawnShieldParticles(play, v);
    Audio_PlaySfx(NA_SE_IT_SHIELD_REFLECT_SW);
}

/**
 * Spawns streaks of light and makes a metallic sound at the specified position
 */
void CollisionCheck_SpawnShieldParticlesMetalSound(PlayState* play, Vec3f* v, Vec3f* pos) {
    CollisionCheck_SpawnShieldParticles(play, v);
    Audio_PlaySfx_AtPos(pos, NA_SE_IT_SHIELD_REFLECT_SW);
}

/**
 * Spawns streaks of light and makes a metallic sound
 */
void CollisionCheck_SpawnShieldParticlesMetal2(PlayState* play, Vec3f* v) {
    CollisionCheck_SpawnShieldParticlesMetal(play, v);
}

/**
 * Spawns streaks of light and makes a wooden sound
 */
void CollisionCheck_SpawnShieldParticlesWood(PlayState* play, Vec3f* v, Vec3f* pos) {
    static EffectShieldParticleInit shieldParticleInitWood = {
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

    shieldParticleInitWood.position.x = v->x;
    shieldParticleInitWood.position.y = v->y;
    shieldParticleInitWood.position.z = v->z;
    shieldParticleInitWood.lightPoint.x = shieldParticleInitWood.position.x;
    shieldParticleInitWood.lightPoint.y = shieldParticleInitWood.position.y;
    shieldParticleInitWood.lightPoint.z = shieldParticleInitWood.position.z;

    Effect_Add(play, &effectIndex, EFFECT_SHIELD_PARTICLE, 0, 1, &shieldParticleInitWood);
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
            intersect1 = intersect2 = 1;
        } else {
            intersect1 = 1;
            intersect2 = 0;
        }
        closeDist = sqrtf(SQ(actorDotItemXZ) - (4.0f * SQXZ(itemStep) * radSqDiff));
        if (intersect1 != 0) {
            frac1 = (closeDist - actorDotItemXZ) / (2.0f * SQXZ(itemStep));
        }
        if (intersect2 != 0) {
            frac2 = (-actorDotItemXZ - closeDist) / (2.0f * SQXZ(itemStep));
        }
    } else if (!IS_ZERO(DOTXZ(2.0f * itemStep, actorToItem))) {
        intersect1 = 1;
        intersect2 = 0;
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

    if (intersect2 == 0) {
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
            intersect1 = 0;
        }
        if (test2) {
            intersect2 = 0;
        }
    }

    if ((intersect1 != 0) &&
        (((frac1 * itemStep.y + actorToItem.y) < 0.0f) || (height < (frac1 * itemStep.y + actorToItem.y)))) {
        intersect1 = 0;
    }
    if ((intersect2 != 0) &&
        (((frac2 * itemStep.y + actorToItem.y) < 0.0f) || (height < (frac2 * itemStep.y + actorToItem.y)))) {
        intersect2 = 0;
    }
    if ((intersect1 == 0) && (intersect2 == 0)) {
        return 0;
    } else if ((intersect1 != 0) && (intersect2 != 0)) {
        out1->x = frac1 * itemStep.x + actorToItem.x + actorPos->x;
        out1->y = frac1 * itemStep.y + actorToItem.y + actorPos->y;
        out1->z = frac1 * itemStep.z + actorToItem.z + actorPos->z;
        out2->x = frac2 * itemStep.x + actorToItem.x + actorPos->x;
        out2->y = frac2 * itemStep.y + actorToItem.y + actorPos->y;
        out2->z = frac2 * itemStep.z + actorToItem.z + actorPos->z;
        return 2;
    } else if (intersect1 != 0) {
        out1->x = frac1 * itemStep.x + actorToItem.x + actorPos->x;
        out1->y = frac1 * itemStep.y + actorToItem.y + actorPos->y;
        out1->z = frac1 * itemStep.z + actorToItem.z + actorPos->z;
        return 1;
    } else if (intersect2 != 0) {
        out1->x = frac2 * itemStep.x + actorToItem.x + actorPos->x;
        out1->y = frac2 * itemStep.y + actorToItem.y + actorPos->y;
        out1->z = frac2 * itemStep.z + actorToItem.z + actorPos->z;
        return 1;
    }
    return 1;
}
