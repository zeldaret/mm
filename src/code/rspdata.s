.include "macro.inc"

.section .rodata

dlabel aspMainDataStart
    .incbin "incbin/aspMainData"
dlabel aspMainDataEnd

dlabel gspF3DZEX2_NoN_PosLight_fifoTextStart
    .incbin "incbin/gspF3DZEX2_NoN_PosLight_fifoText"
dlabel gspF3DZEX2_NoN_PosLight_fifoTextEnd

dlabel gspF3DZEX2_NoN_PosLight_fifoDataStart
    .incbin "incbin/gspF3DZEX2_NoN_PosLight_fifoData"
dlabel gspF3DZEX2_NoN_PosLight_fifoDataEnd

dlabel gspS2DEX2_fifoDataStart
    .incbin "incbin/gspS2DEX2_fifoData"
dlabel gspS2DEX2_fifoDataEnd

dlabel njpgdspMainDataStart
    .incbin "incbin/njpgdspMainData"
dlabel njpgdspMainDataEnd
