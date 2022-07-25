#ifndef Z64VIEW_H
#define Z64VIEW_H

#include "PR/ultratypes.h"
#include "PR/gbi.h"
#include "z64math.h"
#include "unk.h"

struct GraphicsContext;

typedef struct Viewport {
    /* 0x00 */ s32 topY;    // uly (upper left y)
    /* 0x04 */ s32 bottomY; // lry (lower right y)
    /* 0x08 */ s32 leftX;   // ulx (upper left x)
    /* 0x0C */ s32 rightX;  // lrx (lower right x)
} Viewport; // size = 0x10

typedef struct View {
    /* 0x000 */ u32 magic; // string literal "VIEW" / 0x56494557
    /* 0x004 */ struct GraphicsContext* gfxCtx;
    /* 0x008 */ Viewport viewport;
    /* 0x018 */ f32 fovy;  // vertical field of view in degrees
    /* 0x01C */ f32 zNear; // distance to near clipping plane
    /* 0x020 */ f32 zFar;  // distance to far clipping plane
    /* 0x024 */ f32 scale; // scale for matrix elements
    /* 0x028 */ Vec3f eye;
    /* 0x034 */ Vec3f at;
    /* 0x040 */ Vec3f up;
    /* 0x04C */ UNK_TYPE1 pad4C[0x4];
    /* 0x050 */ Vp vp;
    /* 0x060 */ Mtx projection;
    /* 0x0A0 */ Mtx viewing;
    /* 0x0E0 */ Mtx unkE0;
    /* 0x120 */ Mtx* projectionPtr;
    /* 0x124 */ Mtx* viewingPtr;
    /* 0x128 */ Vec3f distortionDirRot;
    /* 0x134 */ Vec3f distortionScale;
    /* 0x140 */ f32 distortionSpeed;
    /* 0x144 */ Vec3f curDistortionDirRot;
    /* 0x150 */ Vec3f curDistortionScale;
    /* 0x15C */ u16 normal; // used to normalize the projection matrix
    /* 0x160 */ u32 flags;  // bit 3: Render to an orthographic perspective
    /* 0x164 */ s32 unk164;
} View; // size = 0x168

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

#endif
