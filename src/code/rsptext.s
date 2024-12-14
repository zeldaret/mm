.include "macro.inc"

.section .data

dlabel aspMainTextStart
    .incbin "incbin/aspMainText"
dlabel aspMainTextEnd

dlabel gspS2DEX2_fifoTextStart
    .incbin "incbin/gspS2DEX2_fifoText"
dlabel gspS2DEX2_fifoTextEnd

dlabel njpgdspMainTextStart
    .incbin "incbin/njpgdspMainText"
dlabel njpgdspMainTextEnd
