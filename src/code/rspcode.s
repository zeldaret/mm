.include "macro.inc"

.section .text

.balign 16

glabel aspMainTextStart
    .incbin "incbin/aspMainText"
endlabel aspMainTextStart
dlabel aspMainTextEnd

glabel gspS2DEX2_fifoTextStart
    .incbin "incbin/gspS2DEX2_fifoText"
endlabel gspS2DEX2_fifoTextStart
dlabel gspS2DEX2_fifoTextEnd

glabel njpgdspMainTextStart
    .incbin "incbin/njpgdspMainText"
endlabel njpgdspMainTextStart
dlabel njpgdspMainTextEnd

.section .rodata

.balign 16

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
