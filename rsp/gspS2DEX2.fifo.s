.include "macro.inc"

.section .text

.balign 16

glabel gspS2DEX2_fifoTextStart
    .incbin "incbin/gspS2DEX2_fifoText"
endlabel gspS2DEX2_fifoTextStart
dlabel gspS2DEX2_fifoTextEnd

.section .rodata

.balign 16

dlabel gspS2DEX2_fifoDataStart
    .incbin "incbin/gspS2DEX2_fifoData"
dlabel gspS2DEX2_fifoDataEnd
