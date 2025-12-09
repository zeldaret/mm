.include "macro.inc"

.section .rodata

.balign 16

dlabel gspF3DZEX2_NoN_PosLight_fifo_legacyTextStart
    .incbin "incbin/gspF3DZEX2_NoN_PosLight_fifo_legacyText"
dlabel gspF3DZEX2_NoN_PosLight_fifo_legacyTextEnd

.section .rodata

.balign 16

dlabel gspF3DZEX2_NoN_PosLight_fifo_legacyDataStart
    .incbin "incbin/gspF3DZEX2_NoN_PosLight_fifo_legacyData"
dlabel gspF3DZEX2_NoN_PosLight_fifo_legacyDataEnd
