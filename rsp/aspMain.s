.include "macro.inc"

.section .text

.balign 16

glabel aspMainTextStart
    .incbin "incbin/aspMainText"
endlabel aspMainTextStart
dlabel aspMainTextEnd

.section .rodata

.balign 16

dlabel aspMainDataStart
    .incbin "incbin/aspMainData"
dlabel aspMainDataEnd
