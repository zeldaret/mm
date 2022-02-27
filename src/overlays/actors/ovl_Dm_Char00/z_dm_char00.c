/*
 * File: z_dm_char00.c
 * Overlay: ovl_Dm_Char00
 * Description: Tatl and Tael (cutscene)
 */

#include "z_dm_char00.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_delf/object_delf.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar00*)thisx)

void DmChar00_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar00_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar00_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar00_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AA67F8(DmChar00* this, GlobalContext* globalCtx);
void func_80AA695C(DmChar00* this, GlobalContext* globalCtx);

const ActorInit Dm_Char00_InitVars = {
    ACTOR_DM_CHAR00,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_DELF,
    sizeof(DmChar00),
    (ActorFunc)DmChar00_Init,
    (ActorFunc)DmChar00_Destroy,
    (ActorFunc)DmChar00_Update,
    (ActorFunc)DmChar00_Draw,
};

static AnimationInfo sAnimations[] = {
    { &gameplay_keep_Anim_02B2E8, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &gameplay_keep_Anim_029140, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_004FF4, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_0053A4, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_005B68, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_006328, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00FB30, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_010590, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_005B68, 1.0f, 37.0f, 56.0f, 4, 0.0f },
    { &object_delf_Anim_006328, 1.0f, 37.0f, 56.0f, 4, 0.0f },
    { &object_delf_Anim_00E024, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00F0D0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_011C70, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_011FE0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_011088, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_0118FC, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_012388, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_012738, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_013BE0, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_013E80, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_007B04, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_0080A4, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00859C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_008A44, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00EB18, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00EBB0, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00EE30, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_012BBC, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_012EF8, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00C248, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00C588, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00BDFC, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00C0BC, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_013040, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_013378, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_0091BC, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_0094B0, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_009C4C, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_009F40, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_009010, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_0097C4, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00A7B4, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00C588, 1.0f, 0.0f, -1.0f, 0, -10.0f },
    { &object_delf_Anim_004FF4, 1.0f, 0.0f, -1.0f, 2, -10.0f },
    { &object_delf_Anim_011C70, 1.0f, 0.0f, -1.0f, 0, -10.0f },
    { &object_delf_Anim_006B28, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_014190, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_01447C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_003FAC, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_004798, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_0042E8, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_004C44, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_01088C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_01498C, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_014E9C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00CEE0, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00D260, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00C690, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00C790, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00AF78, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00B2B8, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00BCD8, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_006D74, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00706C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_0072B0, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_007570, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00A2A4, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00A4B4, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_006614, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_015114, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00CCD4, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00046C, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_00065C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00377C, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_003148, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_001410, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_0010F8, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_00199C, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_003BB4, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_001754, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_0008E0, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_000A94, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_001ED4, 1.0f, 0.0f, -1.0f, 0, 0.0f },
    { &object_delf_Anim_001B28, 1.0f, 0.0f, -1.0f, 2, 0.0f },
    { &object_delf_Anim_000E44, 1.0f, 0.0f, -1.0f, 0, 0.0f },
};

DmChar00Struct D_80AA77A8[] = {
    { 250.0f, 255.0f, 230.0f, 255.0f },
    { 63.0f, 18.0f, 93.0f, 255.0f },
    { 255.0f, 235.0f, 220.0f, 255.0f },
};

DmChar00Struct D_80AA77D8[] = {
    { 220.0f, 160.0f, 80.0f, 255.0f },
    { 250.0f, 40.0f, 10.0f, 255.0f },
    { 255.0f, 235.0f, 220.0f, 255.0f },
};

Vec3f D_80AA7808 = { 0.0f, 0.0f, 0.0f };

void func_80AA5580(SkelAnime* skelAnime, AnimationInfo* animation, u16 idx) {
    f32 phi_f2;

    animation += idx;

    if (animation->frameCount < 0.0f) {
        phi_f2 = Animation_GetLastFrame(animation->animation);
    } else {
        phi_f2 = animation->frameCount;
    }
    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, phi_f2,
                     animation->mode, animation->morphFrames);
}

void func_80AA561C(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        switch (globalCtx->csCtx.frames + 20) {
            case 503:
            case 926:
            case 979:
            case 1222:
            case 1682:
            case 2194:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                break;

            case 1858:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_ATTACK);
                break;

            case 2043:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_SURPRISE);
                break;
        }
    } else {
        switch (globalCtx->csCtx.frames + 20) {
            case 503:
            case 926:
            case 979:
            case 1234:
            case 1687:
            case 2194:
            case 2210:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
                break;

            case 2043:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MONDO_SURPRISE);
                break;
        }
    }
}

void func_80AA5720(DmChar00* this, GlobalContext* globalCtx) {
    if ((DMCHAR00_GET(&this->actor) == DMCHAR00_0) && (globalCtx->csCtx.frames == 505)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SPOT_LIGHT_OPEN);
    }
}

void func_80AA575C(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        switch (globalCtx->csCtx.frames) {
            case 474:
            case 489:
            case 495:
            case 505:
            case 854:
            case 860:
            case 866:
            case 872:
            case 877:
            case 882:
            case 887:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_ATTACK);
                break;

            case 520:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BELL_SPIT);
                break;

            case 774:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_SURPRISE);
                break;

            case 904:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BELL_SIGH);
                break;

            case 813:
            case 972:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BELL_BRAKE);
                break;
        }
    } else if (globalCtx->csCtx.frames == 660) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MONDO_SURPRISE);
    }
}

void func_80AA5890(DmChar00* this, GlobalContext* globalCtx) {
    if ((DMCHAR00_GET(&this->actor) == DMCHAR00_0) && (globalCtx->csCtx.frames == 20)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
    }
}

void func_80AA58CC(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        if (globalCtx->csCtx.frames == 568) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_SURPRISE);
        }
    } else {
        switch (globalCtx->csCtx.frames) {
            case 375:
            case 479:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
                break;

            case 534:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_ATTACK);
                break;
        }
    }
}

void func_80AA5950(DmChar00* this, GlobalContext* globalCtx) {
}

void func_80AA5960(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        if (globalCtx->csCtx.frames == 280) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_SURPRISE);
        }
    } else {
        switch (globalCtx->csCtx.frames) {
            case 87:
            case 190:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
                break;

            case 244:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_ATTACK);
                break;
        }
    }
}

void func_80AA59E4(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        switch (globalCtx->csCtx.frames) {
            case 125:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                break;

            case 1832:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_WHITE_OUT_INTO_MOON);
                break;
        }
    } else if (globalCtx->csCtx.frames == 125) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
    }
}

void func_80AA5A6C(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        switch (globalCtx->csCtx.frames) {
            case 44:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                break;

            case 891:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_SY_WHITE_OUT_INTO_MOON);
                break;
        }
    } else if (globalCtx->csCtx.frames == 44) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
    }
}

void func_80AA5AF4(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        switch (globalCtx->csCtx.frames) {
            case 352:
            case 401:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                break;

            case 440:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                break;

            case 550:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BELL_BRAKE);
                break;
        }
    } else {
        switch (globalCtx->csCtx.frames) {
            case 362:
            case 401:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
                break;

            case 454:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
                break;
        }

        if ((globalCtx->csCtx.frames >= 500) && (globalCtx->csCtx.frames < 602)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_SHIVER - SFX_FLAG);
        }
    }
}

void func_80AA5BF8(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        switch (globalCtx->csCtx.frames) {
            case 762:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_SHOT_DASH);
                break;
            case 797:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                break;
        }
    } else {
        switch (globalCtx->csCtx.frames) {
            case 762:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_SHOT_DASH);
                break;

            case 797:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
                break;
        }
    }

    if ((this->unk_261 == 53) && Animation_OnFrame(&this->skelAnime, 16.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
    }
}

void func_80AA5CD4(DmChar00* this, GlobalContext* globalCtx) {
    if ((DMCHAR00_GET(&this->actor) != DMCHAR00_0) && (globalCtx->csCtx.frames == 467)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
    }
}

void func_80AA5D10(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        switch (globalCtx->csCtx.frames) {
            case 8:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_SURPRISE);
                break;

            case 130:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_NAVY_VANISH);
                break;
        }
    }
}

void func_80AA5D6C(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        switch (globalCtx->csCtx.frames) {
            case 2:
            case 166:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                break;

            case 31:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FAIRY_SURPRISE);
                break;
        }
    }
}

void func_80AA5DC8(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_0) {
        switch (globalCtx->csCtx.frames) {
            case 233:
            case 415:
            case 593:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                break;

            case 130:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_NAVY_VANISH);
                break;
        }
    }
}

void func_80AA5E2C(DmChar00* this, GlobalContext* globalCtx) {
    if (DMCHAR00_GET(&this->actor) == DMCHAR00_1) {
        switch (globalCtx->csCtx.frames) {
            case 32:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WHITE_FAIRY_DASH);
                break;

            case 42:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BLACK_FAIRY_DASH);
                break;

            case 192:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BELL_BRAKE);
                break;

            case 215:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DIVE_INTO_WEED);
                break;
        }
    }
}

void func_80AA5EBC(DmChar00* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state != 0) {
        switch (globalCtx->sceneNum) {
            case SCENE_LOST_WOODS:
                if (gSaveContext.sceneSetupIndex == 1) {
                    func_80AA561C(this, globalCtx);
                }
                break;

            case SCENE_OPENINGDAN:
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA5720(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 1) {
                        func_80AA575C(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 2) {
                        func_80AA5890(this, globalCtx);
                    }
                }
                break;

            case SCENE_OKUJOU:
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA58CC(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 1) {
                        func_80AA5950(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 2) {
                        func_80AA5960(this, globalCtx);
                    }
                } else if (gSaveContext.sceneSetupIndex == 2) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA59E4(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 1) {
                        func_80AA5A6C(this, globalCtx);
                    }
                }
                break;

            case SCENE_00KEIKOKU:
                if (gSaveContext.sceneSetupIndex == 3) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA5AF4(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 2) {
                        func_80AA5E2C(this, globalCtx);
                    }
                } else if (gSaveContext.sceneSetupIndex == 7) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA5BF8(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 1) {
                        func_80AA5CD4(this, globalCtx);
                    }
                }
                break;

            case SCENE_MITURIN:
                if ((gSaveContext.sceneSetupIndex == 0) && (globalCtx->csCtx.currentCsIndex == 1)) {
                    func_80AA5DC8(this, globalCtx);
                }
                break;

            case SCENE_INSIDETOWER:
                if ((gSaveContext.sceneSetupIndex == 0) && (globalCtx->csCtx.currentCsIndex == 0)) {
                    func_80AA5D10(this, globalCtx);
                }
                break;

            case SCENE_PIRATE:
                if ((gSaveContext.sceneSetupIndex == 0) && (globalCtx->csCtx.currentCsIndex == 0)) {
                    func_80AA5D6C(this, globalCtx);
                }
                break;
        }
    }
}

void DmChar00_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DmChar00* this = THIS;

    if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && !Cutscene_IsPlaying(globalCtx)) {
        Actor_MarkForDeath(thisx);
    }

    this->unk_240 = D_80AA77A8[DMCHAR00_GET(thisx)];
    this->unk_250 = D_80AA77D8[DMCHAR00_GET(thisx)];

    thisx->targetArrowOffset = 3000.0f;
    this->unk_260 = 99;
    this->unk_262 = DMCHAR00_GET_F800(thisx);

    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gameplay_keep_Skel_02AF58.sh, &gameplay_keep_Anim_029140,
                   this->jointTable, this->morphTable, 7);
    ActorShape_Init(&thisx->shape, 0.0f, NULL, 15.0f);
    func_80AA5580(&this->skelAnime, sAnimations, 0);
    Actor_SetScale(thisx, 0.01f);
    this->actionFunc = func_80AA67F8;
}

void DmChar00_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80AA62FC(DmChar00* this, GlobalContext* globalCtx) {
    u16 sp26 = DMCHAR00_GET(&this->actor) + 113;
    s32 temp_v0;
    s32 pad;

    if (Cutscene_CheckActorAction(globalCtx, sp26)) {
        temp_v0 = Cutscene_GetActorActionIndex(globalCtx, sp26);

        if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[temp_v0]->startFrame) {
            if (this->unk_260 != globalCtx->csCtx.actorActions[temp_v0]->action) {
                this->unk_260 = globalCtx->csCtx.actorActions[temp_v0]->action;

                switch (globalCtx->csCtx.actorActions[temp_v0]->action) {
                    case 0x1:
                        this->unk_261 = 0;
                        break;

                    case 0x2:
                        this->unk_261 = 2;
                        break;

                    case 0x3:
                        this->unk_261 = 3;
                        break;

                    case 0x4:
                        this->unk_261 = 4;
                        break;

                    case 0x5:
                        this->unk_261 = 5;
                        break;

                    case 0x6:
                        this->unk_261 = 6;
                        break;

                    case 0x7:
                        this->unk_261 = 7;
                        break;

                    case 0x8:
                        this->unk_261 = 20;
                        break;

                    case 0x9:
                        this->unk_261 = 21;
                        break;

                    case 0xA:
                        this->unk_261 = 14;
                        break;

                    case 0xB:
                        this->unk_261 = 15;
                        break;

                    case 0xC:
                        this->unk_261 = 18;
                        break;

                    case 0xD:
                        this->unk_261 = 25;
                        break;

                    case 0xE:
                        this->unk_261 = 27;
                        break;

                    case 0xF:
                        this->unk_261 = 24;
                        break;

                    case 0x10:
                        this->unk_261 = 10;
                        break;

                    case 0x11:
                        this->unk_261 = 12;
                        break;

                    case 0x12:
                        this->unk_261 = 13;
                        break;

                    case 0x13:
                        this->unk_261 = 29;
                        break;

                    case 0x14:
                        this->unk_261 = 31;
                        break;

                    case 0x15:
                        this->unk_261 = 33;
                        break;

                    case 0x16:
                        Actor_MarkForDeath(&this->actor);
                        break;

                    case 0x17:
                        this->unk_261 = 35;
                        break;

                    case 0x18:
                        this->unk_261 = 37;
                        break;

                    case 0x19:
                        this->unk_261 = 39;
                        break;

                    case 0x1A:
                        this->unk_261 = 41;
                        break;

                    case 0x1B:
                        this->unk_261 = 45;
                        break;

                    case 0x1C:
                        this->unk_261 = 46;
                        break;

                    case 0x1E:
                        this->unk_261 = 48;
                        break;

                    case 0x1F:
                        this->unk_261 = 50;
                        break;

                    case 0x20:
                        this->unk_261 = 52;
                        break;

                    case 0x21:
                        this->unk_261 = 53;
                        break;

                    case 0x23:
                        this->unk_261 = 55;
                        break;

                    case 0x24:
                        this->unk_261 = 57;
                        break;

                    case 0x25:
                        this->unk_261 = 58;
                        break;

                    case 0x26:
                        this->unk_261 = 59;
                        break;

                    case 0x27:
                        this->unk_261 = 61;
                        break;

                    case 0x28:
                        this->unk_261 = 62;
                        break;

                    case 0x29:
                        this->unk_261 = 64;
                        break;

                    case 0x2A:
                        this->unk_261 = 66;
                        break;

                    case 0x2B:
                        this->unk_261 = 68;
                        break;

                    case 0x2C:
                        this->unk_261 = 69;
                        break;

                    case 0x2D:
                        this->unk_261 = 70;
                        break;

                    case 0x2E:
                        this->unk_261 = 67;
                        break;

                    case 0x2F:
                        this->unk_261 = 71;
                        break;

                    case 0x30:
                        this->unk_261 = 73;
                        break;

                    case 0x31:
                        this->unk_261 = 74;
                        break;

                    case 0x32:
                        this->unk_261 = 75;
                        break;

                    case 0x33:
                        this->unk_261 = 77;
                        break;

                    case 0x34:
                        this->unk_261 = 78;
                        break;

                    case 0x35:
                        this->unk_261 = 79;
                        break;

                    case 0x36:
                        this->unk_261 = 80;
                        break;

                    case 0x37:
                        this->unk_261 = 82;
                        break;

                    case 0x38:
                        this->unk_261 = 83;
                        break;

                    default:
                        this->unk_261 = 0;
                        break;
                }
                func_80AA5580(&this->skelAnime, &sAnimations[this->unk_261], 0);
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, temp_v0);
    } else {
        this->unk_260 = 99;
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        switch (this->unk_261) {
            case 0x4:
            case 0x5:
                this->unk_261 += 4;
                func_80AA5580(&this->skelAnime, &sAnimations[this->unk_261], 0);
                this->skelAnime.curFrame = 37.0f;
                break;

            case 0xE:
            case 0xF:
            case 0x14:
            case 0x15:
                this->unk_261 += 2;
                func_80AA5580(&this->skelAnime, &sAnimations[this->unk_261], 0);
                break;

            case 0xA:
            case 0x12:
            case 0x19:
            case 0x1B:
            case 0x1D:
            case 0x1F:
            case 0x21:
            case 0x23:
            case 0x25:
            case 0x27:
            case 0x2B:
            case 0x2E:
            case 0x30:
            case 0x32:
            case 0x35:
            case 0x37:
            case 0x3B:
            case 0x3E:
            case 0x40:
            case 0x42:
            case 0x47:
            case 0x4B:
            case 0x50:
            case 0x53:
                this->unk_261 += 1;
                func_80AA5580(&this->skelAnime, &sAnimations[this->unk_261], 0);
                break;

            case 0x2D:
                this->unk_261 = 19;
                func_80AA5580(&this->skelAnime, &sAnimations[this->unk_261], 0);
                break;

            case 0x46:
            case 0x4D:
                this->unk_261 = 0;
                func_80AA5580(&this->skelAnime, &sAnimations[this->unk_261], 0);
                break;
        }
    }
}

void func_80AA67F8(DmChar00* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((globalCtx->csCtx.state == 0) && (gSaveContext.sceneSetupIndex == 0) &&
        (globalCtx->csCtx.currentCsIndex == 1)) {
        if (this->unk_261 != 42) {
            this->unk_261 = 42;
            func_80AA5580(&this->skelAnime, &sAnimations[this->unk_261], 0);
        }

        Math_SmoothStepToF(&this->actor.world.pos.x, 0.0f, 0.5f, 0.5f, 0.001f);
        Math_SmoothStepToF(&this->actor.world.pos.y, 30.0f, 0.5f, 0.5f, 0.001f);
        Math_SmoothStepToF(&this->actor.world.pos.z, -560.0f, 0.5f, 20.0f, 0.001f);

        if (player->actor.world.pos.z < -625.0f) {
            this->unk_261 = 43;
            func_80AA5580(&this->skelAnime, &sAnimations[this->unk_261], 0);
            this->actionFunc = func_80AA695C;
            this->skelAnime.playSpeed = 1.5f;
        }
    }
}

void func_80AA695C(DmChar00* this, GlobalContext* globalCtx) {
    if (this->unk_261 == 44) {
        Math_SmoothStepToF(&this->actor.world.pos.x, 0.0f, 0.5f, 0.5f, 0.001f);
        Math_SmoothStepToF(&this->actor.world.pos.y, 30.0f, 0.5f, 0.5f, 0.001f);
        Math_SmoothStepToF(&this->actor.world.pos.z, -680.0f, 0.5f, 10.0f, 0.001f);
    }
}

void DmChar00_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmChar00* this = THIS;

    SkelAnime_Update(&this->skelAnime);

    this->actionFunc(this, globalCtx);

    this->unk_262++;
    func_80AA5EBC(this, globalCtx);
    func_80AA62FC(this, globalCtx);
}

s32 DmChar00_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              Actor* thisx, Gfx** gfx) {
    DmChar00* this = THIS;
    f32 sp28;
    Vec3f sp1C;

    if (limbIndex == 6) {
        sp28 = ((Math_SinS(this->unk_262 * 0x1000) * 0.1f) + 1.0f) * 0.012f * (this->actor.scale.x * 124.99999f);
        Matrix_MultiplyVector3fByState(&D_80AA7808, &sp1C);
        Matrix_InsertTranslation(sp1C.x, sp1C.y, sp1C.z, MTXMODE_NEW);
        Matrix_Scale(sp28, sp28, sp28, MTXMODE_APPLY);
    }
    return false;
}

void DmChar00_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    DmChar00* this = THIS;
    s32 phi_a0;
    s32 pad;
    Gfx* gfx = GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(Gfx) * 4);

    if ((globalCtx->csCtx.state == 0) &&
        ((globalCtx->sceneNum != SCENE_OPENINGDAN) || (gSaveContext.sceneSetupIndex != 0) ||
         (globalCtx->roomCtx.currRoom.num != 0) || (globalCtx->csCtx.currentCsIndex != 1) ||
         (DMCHAR00_GET(&this->actor) != DMCHAR00_0))) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C94C(globalCtx->state.gfxCtx);

    do {
        phi_a0 = (this->unk_262 * 50) & 511;
        if (phi_a0 >= 256) {
            phi_a0 = 511 - phi_a0;
        }
    } while (0);

    gSPSegment(POLY_XLU_DISP++, 0x08, &gfx[0]);

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0x01, (u8)this->unk_240.unk_00, (u8)this->unk_240.unk_04, (u8)this->unk_240.unk_08,
                    (u8)(this->unk_240.unk_0C * 1));
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_ZB_CLD_SURF2);
    gSPEndDisplayList(gfx);

    gDPSetEnvColor(POLY_XLU_DISP++, (u8)(s8)this->unk_250.unk_00, (u8)(s8)this->unk_250.unk_04,
                   (u8)(s8)this->unk_250.unk_08, (u8)(s8)((f32)phi_a0 * 1));
    gDPSetDither(POLY_XLU_DISP++, G_CD_BAYER);

    POLY_XLU_DISP = SkelAnime_Draw(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   DmChar00_OverrideLimbDraw, NULL, &this->actor, POLY_XLU_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
