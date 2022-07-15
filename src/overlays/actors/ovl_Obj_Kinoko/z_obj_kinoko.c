/*
 * File: z_obj_kinoko.c
 * Overlay: ovl_Obj_Kinoko
 * Description: Mushroom
 */

#include "z_obj_kinoko.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjKinoko*)thisx)

void ObjKinoko_Init(Actor* thisx, PlayState* play);
void ObjKinoko_Destroy(Actor* thisx, PlayState* play);
void ObjKinoko_Update(Actor* thisx, PlayState* play);
void ObjKinoko_Draw(Actor* thisx, PlayState* play);

const ActorInit Obj_Kinoko_InitVars = {
    ACTOR_OBJ_KINOKO,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjKinoko),
    (ActorFunc)ObjKinoko_Init,
    (ActorFunc)ObjKinoko_Destroy,
    (ActorFunc)ObjKinoko_Update,
    (ActorFunc)ObjKinoko_Draw,
};

void ObjKinoko_Init(Actor* thisx, PlayState* play) {
    thisx->world.pos.y += 4.0f;
}

void ObjKinoko_Destroy(Actor* thisx, PlayState* play) {
}

void ObjKinoko_Update(Actor* thisx, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 pad;

    if (player->currentMask != PLAYER_MASK_SCENTS) {
        thisx->draw = NULL;
        thisx->hintId = 0xFF;
        thisx->flags &= ~ACTOR_FLAG_1;
    } else {
        thisx->draw = ObjKinoko_Draw;
        thisx->hintId = 0x64;
        thisx->flags |= ACTOR_FLAG_1;
        if (Actor_HasParent(thisx, play)) {
            Flags_SetCollectible(play, OBJ_KINOKO_GET_FLAG(thisx));
            Actor_MarkForDeath(thisx);
            return;
        }
        Actor_PickUp(thisx, play, GI_MAX, 20.0f, 10.0f);
        if (Math_SmoothStepToF(&thisx->speedXZ, 0.0f, 0.04f, 2.0f, 0.5f) < 0.5f) {
            thisx->scale.x = 0.0f;
            thisx->speedXZ = 110.0f;
            thisx->velocity.x = 0.2f;
        }
        if (Math_SmoothStepToF(&thisx->scale.x, thisx->velocity.x, 0.04f, 0.004f, 0.001f) <
            ((thisx->velocity.x == 0.0f) ? 0.0f : 0.05f)) {
            thisx->velocity.x = 0.0f;
        }
        thisx->scale.y = thisx->scale.x;
        thisx->scale.z = thisx->scale.x;
        thisx->shape.rot.y = Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000;
    }
}

void ObjKinoko_Draw(Actor* thisx, PlayState* play) {
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    gfx = POLY_XLU_DISP;
    gDPSetPrimColor(&gfx[0], 0, 0, 169, 63, 186, (u8)thisx->speedXZ);
    gDPSetEnvColor(&gfx[1], 110, 44, 200, 100);
    gDPSetRenderMode(&gfx[2], G_RM_PASS, G_RM_ZB_CLD_SURF2);
    gSPMatrix(&gfx[3], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&gfx[4], &gameplay_keep_DL_029D10[2]);
    Matrix_RotateXS(-0x4000, MTXMODE_APPLY);
    gSPMatrix(&gfx[5], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&gfx[6], &gameplay_keep_DL_029D10[2]);
    POLY_XLU_DISP = &gfx[7];

    CLOSE_DISPS(play->state.gfxCtx);
}
