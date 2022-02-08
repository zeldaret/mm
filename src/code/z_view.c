#include "global.h"

void View_ViewportToVp(Vp* dest, Viewport* src) {
    s32 width = src->rightX - src->leftX;
    s32 height = src->bottomY - src->topY;

    dest->vp.vscale[0] = width * 2;
    dest->vp.vscale[1] = height * 2;
    dest->vp.vscale[2] = 0x01FF;
    dest->vp.vscale[3] = 0;
    dest->vp.vtrans[0] = ((src->leftX * 2) + width) * 2;
    dest->vp.vtrans[1] = ((src->topY * 2) + height) * 2;
    dest->vp.vtrans[2] = 0x01FF;
    dest->vp.vtrans[3] = 0;

    if (src->leftX == 0 && src->rightX == 576 && src->topY == 0 && src->bottomY) {}
}

void View_Init(View* view, GraphicsContext* gfxCtx) {
    view->gfxCtx = gfxCtx;
    view->viewport.topY = 0;
    view->viewport.bottomY = 240;
    view->viewport.leftX = 0;
    view->viewport.rightX = 320;
    view->magic = 0x56494557; // "VIEW"

    view->unk164 = 0;
    view->flags = 1 | 2 | 4;

    if (1) {
        ;
    }

    view->scale = 1.0f;
    view->up.y = 1.0f;
    view->fovy = 60.0f;
    view->eye.x = 0.0f;
    view->eye.y = 0.0f;
    view->at.x = 0.0f;
    view->up.x = 0.0f;
    view->up.z = 0.0f;
    view->zNear = 10.0f;
    view->zFar = 12800.0f;
    view->eye.z = -1.0f;

    View_InitDistortion(view);
}

void View_SetViewOrientation(View* view, Vec3f* eye, Vec3f* at, Vec3f* up) {
    if (eye->x == at->x && eye->z == at->z) {
        eye->z += 0.1f;
        up->z = 0.0f;
        up->x = 0.0f;
        up->y = 1.0f;
    }

    view->eye = *eye;
    view->at = *at;
    view->up = *up;
    view->flags |= 1;
}

void func_8013F050(View* view, Vec3f* eye, Vec3f* at, Vec3f* up) {
    view->eye = *eye;
    view->at = *at;
    view->up = *up;
}

void View_SetScale(View* view, f32 scale) {
    view->flags |= 4;
    view->scale = scale;
}

void View_GetScale(View* view, f32* scale) {
    *scale = view->scale;
}

void func_8013F0D0(View* view, f32 fovy, f32 zNear, f32 zFar) {
    view->fovy = fovy;
    view->zNear = zNear;
    view->zFar = zFar;
    view->flags |= 4;
}

void func_8013F100(View* view, f32* fovy, f32* zNear, f32* zFar) {
    *fovy = view->fovy;
    *zNear = view->zNear;
    *zFar = view->zFar;
}

void func_8013F120(View* view, f32 fovy, f32 zNear, f32 zFar) {
    view->fovy = fovy;
    view->zNear = zNear;
    view->zFar = zFar;
    view->flags |= 8;
    view->scale = 1.0f;
}

void func_8013F15C(View* view, f32* fovy, f32* zNear, f32* zFar) {
    *fovy = view->fovy;
    *zNear = view->zNear;
    *zFar = view->zFar;
}

void View_SetViewport(View* view, Viewport* viewport) {
    view->viewport = *viewport;
    view->flags |= 2;
}

void View_GetViewport(View* view, Viewport* viewport) {
    *viewport = view->viewport;
}

void View_WriteScissor(Gfx** gfx, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    Gfx* gfxp = *gfx;

    gDPSetScissor(gfxp++, G_SC_NON_INTERLACE, ulx, uly, lrx, lry);

    *gfx = gfxp;
}

void View_SyncAndWriteScissor(View* view, Gfx** gfx) {
    Gfx* gfxp = *gfx;
    s32 ulx = view->viewport.leftX;
    s32 uly = view->viewport.topY;
    s32 lrx = view->viewport.rightX;
    s32 lry = view->viewport.bottomY;

    gDPPipeSync(gfxp++);
    View_WriteScissor(&gfxp, ulx, uly, lrx, lry);

    *gfx = gfxp;
}

void View_SetScissorForLetterbox(View* view) {
    s32 letterboxY;
    s32 letterboxX;
    s32 pad1;
    s32 ulx;
    s32 uly;
    s32 lrx;
    s32 lry;

    OPEN_DISPS(view->gfxCtx);

    letterboxY = ShrinkWindow_GetLetterboxMagnitude();
    letterboxX = -1; // The following is optimized to varX = 0 but affects codegen

    if (letterboxX < 0) {
        letterboxX = 0;
    }
    if (letterboxX > 160) {
        letterboxX = 160;
    }

    if (letterboxY < 0) {
        letterboxY = 0;
    } else if (letterboxY > 120) {
        letterboxY = 120;
    }

    ulx = view->viewport.leftX + letterboxX;
    uly = view->viewport.topY + letterboxY;
    lrx = view->viewport.rightX - letterboxX;
    lry = view->viewport.bottomY - letterboxY;

    gDPPipeSync(POLY_OPA_DISP++);
    {
        s32 pad3;
        Gfx* polyOpa;

        polyOpa = POLY_OPA_DISP;
        View_WriteScissor(&polyOpa, ulx, uly, lrx, lry);
        POLY_OPA_DISP = polyOpa;
    }

    gDPPipeSync(POLY_XLU_DISP++);
    {
        Gfx* polyXlu;
        s32 pad4;

        polyXlu = POLY_XLU_DISP;
        View_WriteScissor(&polyXlu, ulx, uly, lrx, lry);
        POLY_XLU_DISP = polyXlu;
    }

    CLOSE_DISPS(view->gfxCtx);
}

s32 View_SetDistortionDirRot(View* view, f32 dirRotX, f32 dirRotY, f32 dirRotZ) {
    view->distortionDirRot.x = dirRotX;
    view->distortionDirRot.y = dirRotY;
    view->distortionDirRot.z = dirRotZ;
    return 1;
}

s32 View_SetDistortionScale(View* view, f32 scaleX, f32 scaleY, f32 scaleZ) {
    view->distortionScale.x = scaleX;
    view->distortionScale.y = scaleY;
    view->distortionScale.z = scaleZ;
    return 1;
}

s32 View_SetDistortionSpeed(View* view, f32 speed) {
    view->distortionSpeed = speed;
    return 1;
}

s32 View_InitDistortion(View* view) {
    view->distortionDirRot.x = 0.0f;
    view->distortionDirRot.y = 0.0f;
    view->distortionDirRot.z = 0.0f;
    view->distortionScale.x = 1.0f;
    view->distortionScale.y = 1.0f;
    view->distortionScale.z = 1.0f;
    view->curDistortionDirRot = view->distortionDirRot;
    view->curDistortionScale = view->distortionScale;
    view->distortionSpeed = 0.0f;
    return 1;
}

s32 View_ClearDistortion(View* view) {
    view->distortionDirRot.x = 0.0f;
    view->distortionDirRot.y = 0.0f;
    view->distortionDirRot.z = 0.0f;
    view->distortionScale.x = 1.0f;
    view->distortionScale.y = 1.0f;
    view->distortionScale.z = 1.0f;
    view->distortionSpeed = 1.0f;
    return 1;
}

s32 View_SetDistortion(View* view, Vec3f dirRot, Vec3f scale, f32 speed) {
    view->distortionDirRot = dirRot;
    view->distortionScale = scale;
    view->distortionSpeed = speed;
    return 1;
}

s32 View_StepDistortion(View* view, Mtx* projectionMtx) {
    MtxF projectionMtxF;

    if (view->distortionSpeed == 0.0f) {
        return false;
    } else if (view->distortionSpeed == 1.0f) {
        view->curDistortionDirRot = view->distortionDirRot;
        view->curDistortionScale = view->distortionScale;
        view->distortionSpeed = 0.0f;
    } else {
        view->curDistortionDirRot.x =
            F32_LERPIMP(view->curDistortionDirRot.x, view->distortionDirRot.x, view->distortionSpeed);
        view->curDistortionDirRot.y =
            F32_LERPIMP(view->curDistortionDirRot.y, view->distortionDirRot.y, view->distortionSpeed);
        view->curDistortionDirRot.z =
            F32_LERPIMP(view->curDistortionDirRot.z, view->distortionDirRot.z, view->distortionSpeed);

        view->curDistortionScale.x =
            F32_LERPIMP(view->curDistortionScale.x, view->distortionScale.x, view->distortionSpeed);
        view->curDistortionScale.y =
            F32_LERPIMP(view->curDistortionScale.y, view->distortionScale.y, view->distortionSpeed);
        view->curDistortionScale.z =
            F32_LERPIMP(view->curDistortionScale.z, view->distortionScale.z, view->distortionSpeed);
    }

    Matrix_FromRSPMatrix(projectionMtx, &projectionMtxF);
    Matrix_SetCurrentState(&projectionMtxF);
    Matrix_RotateStateAroundXAxis(view->curDistortionDirRot.x);
    Matrix_InsertYRotation_f(view->curDistortionDirRot.y, MTXMODE_APPLY);
    Matrix_InsertZRotation_f(view->curDistortionDirRot.z, MTXMODE_APPLY);
    Matrix_Scale(view->curDistortionScale.x, view->curDistortionScale.y, view->curDistortionScale.z, MTXMODE_APPLY);
    Matrix_InsertZRotation_f(-view->curDistortionDirRot.z, MTXMODE_APPLY);
    Matrix_InsertYRotation_f(-view->curDistortionDirRot.y, MTXMODE_APPLY);
    Matrix_RotateStateAroundXAxis(-view->curDistortionDirRot.x);
    Matrix_ToMtx(projectionMtx);

    return true;
}

void View_RenderView(View* view, s32 uParm2) {
    uParm2 = (view->flags & uParm2) | uParm2 >> 4;

    if (uParm2 & 8) {
        View_RenderToOrthographicMatrix(view);
    } else {
        View_RenderToPerspectiveMatrix(view);
    }
}

s32 View_RenderToPerspectiveMatrix(View* view) {
    f32 aspect;
    s32 width;
    s32 height;
    Vp* vp;
    Mtx* projection;
    Mtx* viewing;
    GraphicsContext* gfxCtx = view->gfxCtx;

    OPEN_DISPS(gfxCtx);

    vp = GRAPH_ALLOC(gfxCtx, sizeof(*vp));
    View_ViewportToVp(vp, &view->viewport);
    view->vp = *vp;

    View_SetScissorForLetterbox(view);

    gSPViewport(POLY_OPA_DISP++, vp);
    gSPViewport(POLY_XLU_DISP++, vp);

    projection = GRAPH_ALLOC(gfxCtx, sizeof(*projection));
    view->projectionPtr = projection;

    width = view->viewport.rightX - view->viewport.leftX;
    height = view->viewport.bottomY - view->viewport.topY;
    aspect = (f32)width / (f32)height;

    guPerspective(projection, &view->normal, view->fovy, aspect, view->zNear, view->zFar, view->scale);
    view->projection = *projection;

    View_StepDistortion(view, projection);

    gSPPerspNormalize(POLY_OPA_DISP++, view->normal);
    gSPMatrix(POLY_OPA_DISP++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNormalize(POLY_XLU_DISP++, view->normal);
    gSPMatrix(POLY_XLU_DISP++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    viewing = GRAPH_ALLOC(gfxCtx, sizeof(*viewing));
    view->viewingPtr = viewing;

    if (view->eye.x == view->at.x && view->eye.y == view->at.y && view->eye.z == view->at.z) {
        view->eye.z += 2.0f;
    }

    guLookAt(viewing, view->eye.x, view->eye.y, view->eye.z, view->at.x, view->at.y, view->at.z, view->up.x, view->up.y,
             view->up.z);

    view->viewing = *viewing;

    gSPMatrix(POLY_OPA_DISP++, viewing, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    gSPMatrix(POLY_XLU_DISP++, viewing, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    CLOSE_DISPS(gfxCtx);

    return 1;
}

s32 View_RenderToOrthographicMatrix(View* view) {
    Vp* vp;
    Mtx* projection;
    GraphicsContext* gfxCtx = view->gfxCtx;

    OPEN_DISPS(gfxCtx);

    vp = GRAPH_ALLOC(gfxCtx, sizeof(*vp));
    View_ViewportToVp(vp, &view->viewport);
    view->vp = *vp;

    View_SetScissorForLetterbox(view);

    gSPViewport(POLY_OPA_DISP++, vp);
    gSPViewport(POLY_XLU_DISP++, vp);
    gSPViewport(OVERLAY_DISP++, vp);

    projection = GRAPH_ALLOC(gfxCtx, sizeof(*projection));
    view->projectionPtr = projection;

    guOrtho(projection, gScreenWidth * -0.5f, gScreenWidth * 0.5f, gScreenHeight * -0.5f, gScreenHeight * 0.5f,
            view->zNear, view->zFar, view->scale);

    view->projection = *projection;

    gSPMatrix(POLY_OPA_DISP++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(POLY_XLU_DISP++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    CLOSE_DISPS(gfxCtx);

    return 1;
}

s32 func_8013FBC8(View* view) {
    Vp* vp;
    Mtx* projection;
    GraphicsContext* gfxCtx;

    gfxCtx = view->gfxCtx;

    OPEN_DISPS(gfxCtx);

    vp = GRAPH_ALLOC(gfxCtx, sizeof(*vp));
    View_ViewportToVp(vp, &view->viewport);
    view->vp = *vp;

    gDPPipeSync(OVERLAY_DISP++);
    {
        Gfx* overlay;
        s32 pad;

        overlay = OVERLAY_DISP;
        View_WriteScissor(&overlay, view->viewport.leftX, view->viewport.topY, view->viewport.rightX,
                          view->viewport.bottomY);
        OVERLAY_DISP = overlay;
    }

    gSPViewport(OVERLAY_DISP++, vp);
    projection = GRAPH_ALLOC(gfxCtx, sizeof(*projection));
    view->projectionPtr = projection;

    guOrtho(projection, gScreenWidth * -0.5f, gScreenWidth * 0.5f, gScreenHeight * -0.5f, gScreenHeight * 0.5f,
            view->zNear, view->zFar, view->scale);
    view->projection = *projection;

    gSPMatrix(OVERLAY_DISP++, projection, G_MTX_LOAD | G_MTX_PROJECTION);

    CLOSE_DISPS(gfxCtx);
    return 1;
}

s32 func_8013FD74(View* view) {
    f32 aspect;
    s32 width;
    s32 height;
    Vp* vp;
    Mtx* projection;
    Mtx* viewing;
    GraphicsContext* gfxCtx;
    s32 pad;

    gfxCtx = view->gfxCtx;

    OPEN_DISPS(gfxCtx);

    vp = GRAPH_ALLOC(gfxCtx, sizeof(*vp));
    View_ViewportToVp(vp, &view->viewport);
    view->vp = *vp;

    gDPPipeSync(OVERLAY_DISP++);
    {
        s32 pad;
        Gfx* overlay;

        overlay = OVERLAY_DISP;
        View_WriteScissor(&overlay, view->viewport.leftX, view->viewport.topY, view->viewport.rightX,
                          view->viewport.bottomY);
        OVERLAY_DISP = overlay;
    }

    gSPViewport(OVERLAY_DISP++, vp);
    projection = GRAPH_ALLOC(gfxCtx, sizeof(*projection));
    view->projectionPtr = projection;

    width = view->viewport.rightX - view->viewport.leftX;
    height = view->viewport.bottomY - view->viewport.topY;
    aspect = (f32)width / (f32)height;

    guPerspective(projection, &view->normal, view->fovy, aspect, view->zNear, view->zFar, view->scale);
    view->projection = *projection;

    gSPPerspNormalize(OVERLAY_DISP++, view->normal);
    gSPMatrix(OVERLAY_DISP++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    viewing = GRAPH_ALLOC(gfxCtx, sizeof(*viewing));
    view->viewingPtr = viewing;

    if (view->eye.x == view->at.x && view->eye.y == view->at.y && view->eye.z == view->at.z) {
        view->eye.z += 2.0f;
    }

    guLookAt(viewing, view->eye.x, view->eye.y, view->eye.z, view->at.x, view->at.y, view->at.z, view->up.x, view->up.y,
             view->up.z);

    view->viewing = *viewing;

    gSPMatrix(OVERLAY_DISP++, viewing, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    CLOSE_DISPS(gfxCtx);

    return 1;
}

s32 func_80140024(View* view) {
    guLookAt(view->viewingPtr, view->eye.x, view->eye.y, view->eye.z, view->at.x, view->at.y, view->at.z, view->up.x,
             view->up.y, view->up.z);

    view->unkE0 = *view->viewingPtr;
    view->viewingPtr = &view->unkE0;

    return 1;
}

s32 func_801400CC(View* view, Gfx** gfxp) {
    Gfx* gfx = *gfxp;
    GraphicsContext* gfxCtx = view->gfxCtx;
    Viewport* viewport = &view->viewport;
    Mtx* projection;
    Vp* vp;

    vp = GRAPH_ALLOC(gfxCtx, sizeof(*vp));
    View_ViewportToVp(vp, viewport);
    view->vp = *vp;

    View_SyncAndWriteScissor(view, &gfx);

    gSPViewport(gfx++, vp);

    projection = GRAPH_ALLOC(gfxCtx, sizeof(*projection));
    view->projectionPtr = projection;

    guOrtho(projection, gScreenWidth * -0.5f, gScreenWidth * 0.5f, gScreenHeight * -0.5f, gScreenHeight * 0.5f,
            view->zNear, view->zFar, view->scale);

    view->projection = *projection;

    gSPMatrix(gfx++, projection, G_MTX_LOAD | G_MTX_PROJECTION);
    *gfxp = gfx;

    return 1;
}
