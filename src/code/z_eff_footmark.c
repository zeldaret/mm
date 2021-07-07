#include <ultra64.h>
#include <global.h>

void EffFootmark_Init(GlobalContext* globalCtx) {
    EffFootmark* footmark;
    s32 i;

    for (footmark = globalCtx->footprintInfo, i = 0; i < 100; i++, footmark++) {
        footmark->actor = NULL;
        footmark->location.x = 0;
        footmark->location.y = 0;
        footmark->location.z = 0;
        footmark->flags = 0;
        footmark->id = 0;
        footmark->alpha = 0;
        footmark->alphaChange = 0;
    }
}

void EffFootmark_Add(GlobalContext* globalCtx, MtxF* displayMatrix, Actor* actor, u8 id, Vec3f* location, u16 size,
                     u8 red, u8 green, u8 blue, u16 alpha, u16 alphaChange, u16 fadeoutDelay) {
    s32 i;
    EffFootmark* footmark;
    EffFootmark* destination = NULL;
    EffFootmark* oldest = NULL;
    s32 isNew = 1;

    for (footmark = globalCtx->footprintInfo, i = 0; i < 100; i++, footmark++) {
        if (((actor == footmark->actor) && (footmark->id == id)) && ((footmark->flags & 1) == 0)) {
            if (fabsf((footmark->location).x - location->x) <= 1) {
                if (fabsf((footmark->location).z - location->z) <= 1) {
                    isNew = 0;
                    break;
                }
            }

            // This footmark is being re-added at a new location. Let's mark this one to start fading out.
            footmark->flags = 1;
        }

        if (footmark->actor == NULL) {
            destination = footmark;
        } else {
            if (destination == NULL) {
                if ((oldest != NULL && footmark->age > oldest->age) || (oldest == NULL)) {
                    oldest = footmark;
                }
            }
        }
    }

    if ((isNew) && ((destination != NULL || (oldest != NULL)))) {
        if (destination == NULL) {
            destination = oldest;
        }
        Matrix_MtxFCopy(&destination->displayMatrix, displayMatrix);
        destination->actor = actor;
        destination->location.x = location->x;
        destination->location.y = location->y;
        destination->location.z = location->z;
        destination->flags = 0;
        destination->id = id;
        destination->red = red;
        destination->green = green;
        destination->blue = blue;
        destination->alpha = alpha;
        destination->alphaChange = alphaChange;
        destination->size = size;
        destination->fadeoutDelay = fadeoutDelay;
        destination->age = 0;
    }
}

void EffFootmark_Update(GlobalContext* globalCtx) {
    EffFootmark* footmark;
    s32 i;

    for (footmark = globalCtx->footprintInfo, i = 0; i < 100; i++, footmark++) {
        if (footmark->actor != NULL) {
            if ((footmark->flags & 1) == 1) {
                if (footmark->age < 0xFFFFu) { // TODO replace with MAX_U16 or something
                    footmark->age++;
                }

                if (footmark->fadeoutDelay == 0) {
                    if (footmark->alpha >= footmark->alphaChange + 0x1000) {
                        footmark->alpha -= footmark->alphaChange;
                    } else {
                        footmark->actor = NULL;
                    }
                } else if (footmark->fadeoutDelay > 0) {
                    footmark->fadeoutDelay--;
                }
            }
        }
    }
}

void EffFootmark_Draw(GlobalContext* globalCtx) {
    EffFootmark* footmark;
    s32 i;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    func_8012C448(globalCtx->state.gfxCtx);

    gSPDisplayList(gfxCtx->polyXlu.p++, D_801BC240);

    for (footmark = globalCtx->footprintInfo, i = 0; i < 100; i++, footmark++) {
        if (footmark->actor != NULL) {
            SysMatrix_SetCurrentState(&footmark->displayMatrix);
            Matrix_Scale(footmark->size * 0.00390625f * 0.7f, 1, footmark->size * 0.00390625f, 1);

            gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD);

            gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, footmark->red, footmark->green, footmark->blue,
                            footmark->alpha >> 8);

            gSPDisplayList(gfxCtx->polyXlu.p++, D_801BC288);
        }
    }
}
