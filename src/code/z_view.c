#include <ultra64.h>
#include <global.h>

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

    if (1);

    view->scale = 1.0f;
    view->upDir.y = 1.0f;
    view->fovy = 60.0f;
    view->eye.x = 0.0f;
    view->eye.y = 0.0f;
    view->focalPoint.x = 0.0f;
    view->upDir.x = 0.0f;
    view->upDir.z = 0.0f;
    view->zNear = 10.0f;
    view->zFar = 12800.0f;
    view->eye.z = -1.0f;

    View_InitCameraQuake(view);
}

void View_SetViewOrientation(View* view, Vec3f* eye, Vec3f* focalPoint, Vec3f* upDir) {
    if (eye->x == focalPoint->x && eye->z == focalPoint->z) {
        eye->z += 0.1f;
        upDir->z = 0.0f;
        upDir->x = 0.0f;
        upDir->y = 1.0f;
    }

    view->eye = *eye;
    view->focalPoint = *focalPoint;
    view->upDir = *upDir;
    view->flags |= 1;
}

void func_8013F050(View* view, Vec3f* eye, Vec3f* focalPoint, Vec3f* upDir) {
    view->eye = *eye;
    view->focalPoint = *focalPoint;
    view->upDir = *upDir;
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
    s32 pad2;
    GraphicsContext* gfxCtx;

    gfxCtx = view->gfxCtx;

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

    gDPPipeSync(gfxCtx->polyOpa.p++);
    {
        s32 pad3;
        Gfx* polyOpa;

        polyOpa = gfxCtx->polyOpa.p;
        View_WriteScissor(&polyOpa, ulx, uly, lrx, lry);
        gfxCtx->polyOpa.p = polyOpa;
    }

    gDPPipeSync(gfxCtx->polyXlu.p++);
    {
        Gfx* polyXlu;
        s32 pad4;

        polyXlu = gfxCtx->polyXlu.p;
        View_WriteScissor(&polyXlu, ulx, uly, lrx, lry);
        gfxCtx->polyXlu.p = polyXlu;
    }
}

s32 View_SetQuakeRotation(View* view, f32 x, f32 y, f32 z) {
    view->quakeRot.x = x;
    view->quakeRot.y = y;
    view->quakeRot.z = z;
    return 1;
}

s32 View_SetQuakeScale(View* view, f32 x, f32 y, f32 z) {
    view->quakeScale.x = x;
    view->quakeScale.y = y;
    view->quakeScale.z = z;
    return 1;
}

s32 View_SetQuakeSpeed(View* view, f32 speed) {
    view->quakeSpeed = speed;
    return 1;
}

s32 View_InitCameraQuake(View* view) {
    view->quakeRot.x = 0.0f;
    view->quakeRot.y = 0.0f;
    view->quakeRot.z = 0.0f;
    view->quakeScale.x = 1.0f;
    view->quakeScale.y = 1.0f;
    view->quakeScale.z = 1.0f;
    view->currQuakeRot = view->quakeRot;
    view->currQuakeScale = view->quakeScale;
    view->quakeSpeed = 0.0f;
    return 1;
}

s32 View_ClearQuake(View* view) {
    view->quakeRot.x = 0.0f;
    view->quakeRot.y = 0.0f;
    view->quakeRot.z = 0.0f;
    view->quakeScale.x = 1.0f;
    view->quakeScale.y = 1.0f;
    view->quakeScale.z = 1.0f;
    view->quakeSpeed = 1.0f;
    return 1;
}

s32 View_SetQuake(View* view, Vec3f rot, Vec3f scale, f32 speed) {
    view->quakeRot = rot;
    view->quakeScale = scale;
    view->quakeSpeed = speed;
    return 1;
}

s32 View_StepQuake(View* view, RSPMatrix* matrix) {
    MtxF mf;

    if (view->quakeSpeed == 0.0f) {
        return 0;
    } else if (view->quakeSpeed == 1.0f) {
        view->currQuakeRot = view->quakeRot;
        view->currQuakeScale = view->quakeScale;
        view->quakeSpeed = 0.0f;
    } else {
        view->currQuakeRot.x += ((view->quakeRot.x - view->currQuakeRot.x) * view->quakeSpeed);
        view->currQuakeRot.y += ((view->quakeRot.y - view->currQuakeRot.y) * view->quakeSpeed);
        view->currQuakeRot.z += ((view->quakeRot.z - view->currQuakeRot.z) * view->quakeSpeed);

        view->currQuakeScale.x += ((view->quakeScale.x - view->currQuakeScale.x) * view->quakeSpeed);
        view->currQuakeScale.y += ((view->quakeScale.y - view->currQuakeScale.y) * view->quakeSpeed);
        view->currQuakeScale.z += ((view->quakeScale.z - view->currQuakeScale.z) * view->quakeSpeed);
    }

    SysMatrix_FromRSPMatrix(matrix, &mf);
    Matrix_Put(&mf);
    SysMatrix_RotateStateAroundXAxis(view->currQuakeRot.x);
    SysMatrix_InsertYRotation_f(view->currQuakeRot.y, 1);
    SysMatrix_InsertZRotation_f(view->currQuakeRot.z, 1);
    Matrix_Scale(view->currQuakeScale.x, view->currQuakeScale.y, view->currQuakeScale.z, 1);
    SysMatrix_InsertZRotation_f(-view->currQuakeRot.z, 1);
    SysMatrix_InsertYRotation_f(-view->currQuakeRot.y, 1);
    SysMatrix_RotateStateAroundXAxis(-view->currQuakeRot.x);
    SysMatrix_GetStateAsRSPMatrix(matrix);

    return 1;
}

void View_RenderView(View* view, s32 uParm2) {
    uParm2 = (view->flags & uParm2) | uParm2 >> 4;

    if (uParm2 & 8) {
        View_RenderToOrthographicMatrix(view);
    } else {
        View_RenderToPerspectiveMatrix(view);
    }
}

#ifdef NON_MATCHING
// saved register usage is wrong, stack, regalloc
s32 View_RenderToPerspectiveMatrix(View* view) {
    f32 aspect;
    s32 width;
    s32 height;
    Vp* vp;
    Mtx* projection;
    Mtx* viewing;
    GraphicsContext* gfxCtx;

    gfxCtx = view->gfxCtx;

    {
        Vp* _vp = (Vp*)gfxCtx->polyOpa.d - 1;
        vp = _vp;
        gfxCtx->polyOpa.d = (Gfx*)_vp;
    }
    View_ViewportToVp(vp, &view->viewport);
    view->vp = *vp;

    View_SetScissorForLetterbox(view);

    gSPViewport(gfxCtx->polyOpa.p++, vp);
    gSPViewport(gfxCtx->polyXlu.p++, vp);

    {
        Mtx* _m = (Mtx*)gfxCtx->polyOpa.d - 1;
        projection = _m;
        gfxCtx->polyOpa.d = (Gfx*)_m;
    }
    view->projectionPtr = projection;

    width = view->viewport.rightX - view->viewport.leftX;
    height = view->viewport.bottomY - view->viewport.topY;
    aspect = (f32)width / (f32)height;

    guPerspective(projection, &view->normal, view->fovy, aspect, view->zNear, view->zFar, view->scale);

    view->projection = *projection;

    View_StepQuake(view, projection);

    gSPPerspNormalize(gfxCtx->polyOpa.p++, view->normal);
    gSPMatrix(gfxCtx->polyOpa.p++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNormalize(gfxCtx->polyXlu.p++, view->normal);
    gSPMatrix(gfxCtx->polyXlu.p++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    {
        Mtx* _m = (Mtx*)gfxCtx->polyOpa.d - 1;
        viewing = _m;
        gfxCtx->polyOpa.d = (Gfx*)_m;
    }
    view->viewingPtr = viewing;

    if (view->eye.x == view->focalPoint.x && view->eye.y == view->focalPoint.y && view->eye.z == view->focalPoint.z) {
        view->eye.z += 2.0f;
    }

    guLookAt(viewing, view->eye.x, view->eye.y, view->eye.z, view->focalPoint.x, view->focalPoint.y, view->focalPoint.z,
                  view->upDir.x, view->upDir.y, view->upDir.z);

    view->viewing = *viewing;

    gSPMatrix(gfxCtx->polyOpa.p++, viewing, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    gSPMatrix(gfxCtx->polyXlu.p++, viewing, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    return 1;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_view/View_RenderToPerspectiveMatrix.asm")
#endif

#ifdef NON_MATCHING
// this needs a momumental amount of work
s32 View_RenderToOrthographicMatrix(View* view) {
    Vp* vp;
    Mtx* projection;
    GraphicsContext* gfxCtx;

    gfxCtx = view->gfxCtx;

    {
        Vp* _vp = (Vp*)gfxCtx->polyOpa.d - 1;
        vp = _vp;
        gfxCtx->polyOpa.d = (Gfx*)_vp;
    }
    View_ViewportToVp(vp, &view->viewport);
    view->vp = *vp;

    View_SetScissorForLetterbox(view);

    gSPViewport(gfxCtx->polyOpa.p++, vp);
    gSPViewport(gfxCtx->polyXlu.p++, vp);
    gSPViewport(gfxCtx->overlay.p++, vp);

    {
        Mtx* _m = (Mtx*)gfxCtx->polyOpa.d - 1;
        projection = _m;
        gfxCtx->polyOpa.d = (Gfx*)_m;
    }
    view->projectionPtr = projection;

    guOrtho(projection, -0.5f ,0.5f, screenWidth * -0.5f, screenWidth * 0.5f,
            screenHeight * -0.5f, screenHeight * 0.5f, view->zNear);

    view->projection = *projection;

    gSPMatrix(gfxCtx->polyOpa.p++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gfxCtx->polyXlu.p++, projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    return 1;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_view/View_RenderToOrthographicMatrix.asm")
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_view/func_8013FBC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_view/func_8013FD74.asm")

s32 func_80140024(View* view) {
    guLookAt(view->viewingPtr, view->eye.x, view->eye.y, view->eye.z,
             view->focalPoint.x, view->focalPoint.y, view->focalPoint.z,
             view->upDir.x, view->upDir.y, view->upDir.z);

    view->unkE0 = *view->viewingPtr;
    view->viewingPtr = &view->unkE0;

    return 1;
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_view/func_801400CC.asm")

