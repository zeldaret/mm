#include "global.h"
#include "z64skin.h"

void func_80138410(PSkinAwb* skin) {
    skin->skeletonHeader = NULL;
    skin->avbCount = 0;
    skin->avbTbl = NULL;
}

void Skin_InitAnimatedLimb(GameState* gameState, PSkinAwb* skin, s32 limbIndex) {
    s32 i;
    SkinLimb** skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    SkinAnimatedLimbData* animatedLimbData = Lib_SegmentedToVirtual(((SkinLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]))->limbData);
    Struct_800A598C* temp_v0 = Lib_SegmentedToVirtual(animatedLimbData->unk_4);

    for (i = 0; i < ARRAY_COUNT(skin->avbTbl->buf); i++) {
        Vtx* vertices = skin->avbTbl[limbIndex].buf[i];
        Struct_800A598C* phi_s0;

        for (phi_s0 = temp_v0; phi_s0 < temp_v0 + animatedLimbData->unk_2; phi_s0++) {
            SkinVtx* skinVertices = Lib_SegmentedToVirtual(phi_s0->skinVertices);
            SkinVtx* skinVtxEntry;

            for (skinVtxEntry = skinVertices; skinVtxEntry < skinVertices + phi_s0->skinVerticesCount; ) {
                Vtx* vtx = &vertices[skinVtxEntry->vtxIndex];

                skinVtxEntry++;

                vtx->n.flag = 0;
                vtx->n.tc[0] = skinVtxEntry[-1].u;
                vtx->n.tc[1] = skinVtxEntry[-1].v;
                vtx->n.a = skinVtxEntry[-1].alpha;
            }
        }
    }
}

void Skin_Init(GameState* gameState, PSkinAwb* skin, SkeletonHeader* skeletonHeader,
                   AnimationHeader* animationHeader) {
    s32 limbCount;
    s32 i;
    SkinLimb** skeleton;
    SkeletonHeader* virtSkelHeader = Lib_SegmentedToVirtual(skeletonHeader);

    skin->avbCount = virtSkelHeader->limbCount;
    skin->skeletonHeader = virtSkelHeader;
    limbCount = skin->skeletonHeader->limbCount;

    skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    skin->avbTbl = ZeldaArena_Malloc(limbCount * sizeof(SkinAvb));

    for (i = 0; i < limbCount; i++) {
        SkinAvb* avbEntry = &skin->avbTbl[i];

        if ((((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->segmentType != SKIN_LIMB_TYPE_ANIMATED) || (((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->segment == NULL)) {
            avbEntry->index = 0;

            avbEntry->buf[0] = NULL;
            avbEntry->buf[1] = NULL;
        } else {
            SkinAnimatedLimbData* temp_s1 = Lib_SegmentedToVirtual((((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->limbData));

            {
                s32 tmp;
            }
            avbEntry->index = 0;
            avbEntry->buf[0] = ZeldaArena_Malloc(temp_s1->vtxCount * sizeof(Vtx));
            avbEntry->buf[1] = ZeldaArena_Malloc(temp_s1->vtxCount * sizeof(Vtx));

            Skin_InitAnimatedLimb(gameState, skin, i);
        }
    }

    SkelAnime_InitSkin(gameState, &skin->skelAnime, skeletonHeader, animationHeader);
}

void Skin_Free(GameState* gameState, PSkinAwb* skin) {
    if (skin->avbTbl != NULL) {
        s32 i;

        for (i = 0; i < skin->avbCount; i++) {
            if (skin->avbTbl[i].buf[0] != NULL) {
                ZeldaArena_Free(skin->avbTbl[i].buf[0]);
                skin->avbTbl[i].buf[0] = NULL;
            }
            if (skin->avbTbl[i].buf[1] != NULL) {
                ZeldaArena_Free(skin->avbTbl[i].buf[1]);
                skin->avbTbl[i].buf[1] = NULL;
            }
        }

        if (skin->avbTbl != NULL) {
            ZeldaArena_Free(skin->avbTbl);
        }

        SkelAnime_Free(&skin->skelAnime, (GlobalContext*)gameState);
    }
}

s32 func_801387D4(PSkinAwb* skin, SkinLimb** skeleton, MtxF* mf, u8 parentIndex, u8 limbIndex) {
    s32 pad;
    SkinLimb* limb = Lib_SegmentedToVirtual(skeleton[limbIndex]);
    MtxF* mtx;
    s32 temp_ret;
    MtxF sp28;

    if (parentIndex == 0xFF) {
        SkinMatrix_GetClear(&mtx);
    } else {
        mtx = &mf[(s32)parentIndex];
    }

    SkinMatrix_MtxFMtxFMult(mtx, &mf[limbIndex], &sp28);
    SkinMatrix_MtxFCopy(&sp28, &mf[limbIndex]);

    if (limb->child != 0xFF) {
        temp_ret = func_801387D4(skin, skeleton, mf, limbIndex, limb->child);
        if (temp_ret) { // func_801387D4 only returns false
            return temp_ret;
        }
    }

    if (limb->sibling != 0xFF) {
        temp_ret = func_801387D4(skin, skeleton, mf, parentIndex, limb->sibling);
        if (temp_ret) { // func_801387D4 only returns false
            return temp_ret;
        }
    }

    return false;
}

s32 func_801388E4(PSkinAwb* skin, MtxF* arg1, Actor* actor, s32 arg3) {
    s32 i;
    s32 pad;
    f32 yRot;
    f32 xRot;
    f32 zRot;
    s32 temp_ret;
    f32 yTransl;
    f32 xTransl;
    f32 zTransl;
    SkinLimb** skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    Vec3s* jointRot = &skin->skelAnime.jointTable[0];

    jointRot++;
    xRot = jointRot[0].x;
    yRot = jointRot[0].y;
    zRot = jointRot[0].z;

    if (arg3 != 0) {
        jointRot--;
        xTransl = jointRot[0].x;
        yTransl = jointRot[0].y;
        zTransl = jointRot[0].z;
        jointRot++;

        SkinMatrix_SetRotateRPYTranslate(arg1, xRot, yRot, zRot, xTransl, yTransl, zTransl);
    } else {
        SkinMatrix_SetRotateRPYTranslate(arg1, xRot, yRot, zRot, 0.0f, 0.0f, 0.0f);
    }
    jointRot++;

    for (i = 1; i < skin->skeletonHeader->limbCount; i++) {
        SkinLimb* limb = Lib_SegmentedToVirtual(skeleton[i]);

        xTransl = limb->jointPos.x;
        yTransl = limb->jointPos.y;
        zTransl = limb->jointPos.z;
        xRot = jointRot->x;
        yRot = jointRot->y;
        zRot = jointRot->z;
        jointRot++;
        SkinMatrix_SetRotateRPYTranslate(&arg1[i], xRot, yRot, zRot, xTransl, yTransl, zTransl);
    }

    SkinMatrix_SetScaleRotateYRPTranslate(
        &skin->mtx, actor->scale.x, actor->scale.y, actor->scale.z, actor->shape.rot.x, actor->shape.rot.y,
        actor->shape.rot.z, actor->world.pos.x, actor->world.pos.y + (actor->shape.yOffset * actor->scale.y),
        actor->world.pos.z);

    temp_ret = func_801387D4(skin, Lib_SegmentedToVirtual(skin->skeletonHeader->segment), arg1, 0xFF, 0);
    if (!temp_ret) { // func_801387D4 only returns false
        return temp_ret;
    }
    return false;
}
