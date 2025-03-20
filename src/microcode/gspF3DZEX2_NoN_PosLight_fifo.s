.include "macro.inc"

.section .rodata

.balign 16

dlabel gspF3DZEX2_NoN_PosLight_fifoTextStart
    .incbin "incbin/gspF3DZEX2_NoN_PosLight_fifoText"
dlabel gspF3DZEX2_NoN_PosLight_fifoTextEnd

.balign 16

dlabel gspF3DZEX2_NoN_PosLight_fifoDataStart
    .incbin "incbin/gspF3DZEX2_NoN_PosLight_fifoData"
dlabel gspF3DZEX2_NoN_PosLight_fifoDataEnd
