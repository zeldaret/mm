#include "gfxalloc.h"

#include "alignment.h"

Gfx* Gfx_Open(Gfx* gfx) {
    return &gfx[1];
}

Gfx* Gfx_Close(Gfx* gfx, Gfx* dst) {
    gSPBranchList(gfx, dst);
    return dst;
}

/**
 * Allocates a structure of `size` into the display list buffer`gfx`,
 * returning a pointer to the start of the buffer.
 * Since the alloc may not itself be display list commands, a BranchList
 * command is used to step over this region.
 */
void* Gfx_Alloc(Gfx** gfxP, size_t size) {
    u8* start;
    Gfx* gfx;

    size = ALIGN8(size);
    start = (u8*)&(*gfxP)[1];
    gfx = (Gfx*)(start + size);
    gSPBranchList(*gfxP, gfx);

    *gfxP = gfx;
    return start;
}
