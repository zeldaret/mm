/*
 * File: z_bg_ikana_mirror.c
 * Overlay: ovl_Bg_Ikana_Mirror
 * Description: Stone Tower Temple - Mirror
 */

// credits for documentation: Anon58, EllipticEllipsis

#include "z_bg_ikana_mirror.h"
#include "objects/object_ikana_obj/object_ikana_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkanaMirror*)thisx)

void BgIkanaMirror_Init(Actor* thisx, PlayState* play);
void BgIkanaMirror_Destroy(Actor* thisx, PlayState* play);
void BgIkanaMirror_Update(Actor* thisx, PlayState* play);
void BgIkanaMirror_Draw(Actor* thisx, PlayState* play);

const ActorInit Bg_Ikana_Mirror_InitVars = {
    ACTOR_BG_IKANA_MIRROR,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaMirror),
    (ActorFunc)BgIkanaMirror_Init,
    (ActorFunc)BgIkanaMirror_Destroy,
    (ActorFunc)BgIkanaMirror_Update,
    (ActorFunc)BgIkanaMirror_Draw,
};

static ColliderTrisElementInit sTrisElementsInit[9] = {
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00200000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 21.6f, 13.7f }, { -25.3f, 6.0f, 8.4f }, { 25.3f, 6.0f, 8.4f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00200000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 45.0f, 13.7f }, { -25.3f, 6.0f, 8.4f }, { 0.0f, 21.6f, 13.7f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00200000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 45.0f, 13.7f }, { 0.0f, 21.6f, 13.7f }, { 25.3f, 6.0f, 8.4f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00200000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 45.0f, 13.7f }, { -25.3f, 45.0f, 8.4f }, { -25.3f, 6.0f, 8.4f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00200000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 45.0f, 13.7f }, { 25.3f, 6.0f, 8.4f }, { 25.3f, 45.0f, 8.4f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00200000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 45.0f, 13.7f }, { -17.9f, 64.1f, 8.4f }, { -25.3f, 45.0f, 8.4f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00200000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 45.0f, 13.7f }, { 25.3f, 45.0f, 8.4f }, { 17.9f, 64.1f, 8.4f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00200000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 45.0f, 13.7f }, { 0.0f, 72.0f, 8.4f }, { -17.9f, 64.1f, 8.4f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x00200000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 0.0f, 45.0f, 13.7f }, { 17.9f, 64.1f, 8.4f }, { 0.0f, 72.0f, 8.4f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    9,
    sTrisElementsInit,
};

static ColliderQuadInit sQuadInit[2] = {
    {
        {
            COLTYPE_NONE,
            AT_ON | AT_TYPE_OTHER,
            AC_NONE,
            OC1_NONE,
            OC2_NONE,
            COLSHAPE_QUAD,
        },
        {
            ELEMTYPE_UNK0,
            { 0x00200000, 0x00, 0x00 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { { { 0.0f, 72.0f, 20.0f }, { 0.0f, 72.0f, 240.0f }, { 0.0f, 6.0f, 20.0f }, { 0.0f, 6.0f, 240.0f } } },
    },
    {
        {
            COLTYPE_NONE,
            AT_ON | AT_TYPE_OTHER,
            AC_NONE,
            OC1_NONE,
            OC2_NONE,
            COLSHAPE_QUAD,
        },
        {
            ELEMTYPE_UNK0,
            { 0x00200000, 0x00, 0x00 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { { { 25.3f, 20.0f, 20.0f }, { 25.3f, 20.0f, 240.0f }, { -25.3f, 20.0f, 20.0f }, { -25.3f, 20.0f, 240.0f } } },
    }
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 220, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void BgIkanaMirror_SetupWait(BgIkanaMirror* this);
void BgIkanaMirror_Wait(BgIkanaMirror* this, GlobalContext* globalCtx);
void BgIkanaMirror_SetupEmitLight(BgIkanaMirror* this);
void BgIkanaMirror_EmitLight(BgIkanaMirror* this, GlobalContext* globalCtx);

void BgIkanaMirror_SetQuadVertices(BgIkanaMirror* this) {
    ColliderQuadDimInit* dim;
    ColliderQuad* collider;
    Vec3f a;
    Vec3f b;
    Vec3f c;
    Vec3f d;
    s32 i;

    Matrix_Push();
    Matrix_SetTranslateRotateYXZ(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                 this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    for (i = 0; i < ARRAY_COUNT(this->colliderQuad); i++) {
        dim = &sQuadInit[i].dim;
        Matrix_MultVec3f(&dim->quad[0], &a);
        Matrix_MultVec3f(&dim->quad[1], &b);
        Matrix_MultVec3f(&dim->quad[2], &c);
        Matrix_MultVec3f(&dim->quad[3], &d);
        collider = &this->colliderQuad[i];
        Collider_SetQuadVertices(collider, &a, &b, &c, &d);
    }

    Matrix_Pop();
}

void BgIkanaMirror_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgIkanaMirror* this = THIS;
    Vec3f* vtx;
    Vec3f vertices[3];
    ColliderTrisElementInit* colliderElement;
    s32 i;
    s32 j;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gStoneTowerTempleMirrorCol);
    Collider_InitTris(globalCtx, &this->colliderTris);
    Collider_SetTris(globalCtx, &this->colliderTris, &this->dyna.actor, &sTrisInit, this->colliderTrisElements);
    Matrix_SetTranslateRotateYXZ(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                 this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);

    for (i = 0; i < ARRAY_COUNT(sTrisElementsInit); i++) {
        colliderElement = &sTrisInit.elements[i];
        vtx = &colliderElement->dim.vtx[0];
        for (j = 0; j < 3; j++) {
            Matrix_MultVec3f(vtx, &vertices[j]);
            vtx++;
        }
        Collider_SetTrisVertices(&this->colliderTris, i, &vertices[0], &vertices[1], &vertices[2]);
    }

    for (i = 0; i < ARRAY_COUNT(this->colliderQuad); i++) {
        Collider_InitQuad(globalCtx, &this->colliderQuad[i]);
        Collider_SetQuad(globalCtx, &this->colliderQuad[i], &this->dyna.actor, &sQuadInit[i]);
    }

    BgIkanaMirror_SetQuadVertices(this);
    this->lightAbsorptionAnimatedTexture = Lib_SegmentedToVirtual(&gStoneTowerTempleMirrorLightAbsorptionTexAnim);
    this->lightEmissionAnimatedTexture = Lib_SegmentedToVirtual(&gStoneTowerTempleMirrorLightEmissionTexAnim);
    BgIkanaMirror_SetupWait(this);
}

void BgIkanaMirror_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaMirror* this = THIS;
    s32 i;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyTris(globalCtx, &this->colliderTris);

    for (i = 0; i < ARRAY_COUNT(this->colliderQuad); i++) {
        Collider_DestroyQuad(globalCtx, &this->colliderQuad[i]);
    }
}

void BgIkanaMirror_SetupWait(BgIkanaMirror* this) {
    this->isEmittingLight = 0;
    this->actionFunc = BgIkanaMirror_Wait;
}

void BgIkanaMirror_Wait(BgIkanaMirror* this, GlobalContext* globalCtx) {
    s8 isEmittingLight;
    s32 startEmittingLight = false;

    // The light emission texture should gradually disappear from sight.
    if (this->lightEmissionAlpha >= 101) {
        this->lightEmissionAlpha -= 100;
    } else {
        this->lightEmissionAlpha = 0;
    }

    // This checks if light is touching the mirror.
    if (this->colliderTris.base.acFlags & AC_HIT) {
        this->colliderTris.base.acFlags &= ~AC_HIT;
        this->isEmittingLight = 0;
        if (this->timer < 400) {
            this->timer++;
        }
        if (this->lightAbsorptionAlpha < 195) {
            this->lightAbsorptionAlpha += 60;
        } else {
            this->lightAbsorptionAlpha = 255;
        }
    } else {
        isEmittingLight = this->isEmittingLight;
        if (isEmittingLight > 0) {
            startEmittingLight = true;
        } else if (this->timer > 0) {
            this->isEmittingLight = isEmittingLight + 1;
        }
    }

    if (startEmittingLight) {
        BgIkanaMirror_SetupEmitLight(this);
    } else {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderTris.base);
    }
}

void BgIkanaMirror_SetupEmitLight(BgIkanaMirror* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_20;
    this->actionFunc = BgIkanaMirror_EmitLight;
}

void BgIkanaMirror_EmitLight(BgIkanaMirror* this, GlobalContext* globalCtx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->colliderQuad); i++) {
        if ((this->colliderQuad[i].base.atFlags & AT_HIT)) {
            this->colliderQuad[i].base.atFlags &= ~AT_HIT;
        }
    }

    if (this->lightEmissionAlpha < 155) {
        this->lightEmissionAlpha += 100;
    } else {
        this->lightEmissionAlpha = 255;
    }

    if (this->lightAbsorptionAlpha >= 61) {
        this->lightAbsorptionAlpha -= 60;
    } else {
        this->lightAbsorptionAlpha = 0;
    }

    if (this->timer > 0) {
        this->timer--;

        for (i = 0; i < ARRAY_COUNT(this->colliderQuad); i++) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderQuad[i].base);
        }

    } else {
        this->dyna.actor.flags &= ~ACTOR_FLAG_20;
        BgIkanaMirror_SetupWait(this);
    }
}

void BgIkanaMirror_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaMirror* this = THIS;

    this->actionFunc(this, globalCtx);
}

void BgIkanaMirror_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgIkanaMirror* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gStoneTowerTempleMirrorDL);

    if (this->lightAbsorptionAlpha > 0) {
        AnimatedMat_Draw(globalCtx, this->lightAbsorptionAnimatedTexture);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, this->lightAbsorptionAlpha);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gStoneTowerTempleMirrorLightEmissionDL);
    }

    if (this->lightEmissionAlpha > 0) {
        f32 temp_fv0 = this->lightEmissionAlpha * (1.0f / 255.0f);
        s32 pad2[2];

        AnimatedMat_Draw(globalCtx, this->lightEmissionAnimatedTexture);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, (s32)(temp_fv0 * 123.0f));
        gDPSetEnvColor(POLY_XLU_DISP++, 215, 215, 255, (s32)(temp_fv0 * 185.0f));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gStoneTowerTempleMirrorLightAbsorptionDL);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
