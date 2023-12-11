#include "segment_symbols.h"
#include "z64dma.h"

// Linker symbol declarations (used in the table below)
#define DEFINE_DMA_ENTRY(name, _nameString) DECLARE_ROM_SEGMENT(name)
#define DEFINE_DMA_ENTRY_UNSET(name, _nameString) DECLARE_ROM_SEGMENT(name)

#include "tables/dmadata_table.h"

#undef DEFINE_DMA_ENTRY
#undef DEFINE_DMA_ENTRY_UNSET

// dmadata Table definition
#define DEFINE_DMA_ENTRY(name, _nameString) \
    { SEGMENT_ROM_START(name), SEGMENT_ROM_END(name), SEGMENT_ROM_START(name), 0 },
#define DEFINE_DMA_ENTRY_UNSET(name, _nameString) \
    { SEGMENT_ROM_START(name), SEGMENT_ROM_END(name), 0xFFFFFFFF, 0xFFFFFFFF },

DmaEntry gDmaDataTable[] = {
#include "tables/dmadata_table.h"
    { 0 },
};

#undef DEFINE_DMA_ENTRY
#undef DEFINE_DMA_ENTRY_UNSET

u8 sDmaDataPadding[0xF0] = { 0 };
static s32 sBssPad;
