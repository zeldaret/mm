.include "macro.inc"

.section .text

.balign 16

glabel njpgdspMainTextStart
    .incbin "incbin/njpgdspMainText"
endlabel njpgdspMainTextStart
dlabel njpgdspMainTextEnd

.section .rodata

.balign 16

dlabel njpgdspMainDataStart
    .incbin "incbin/njpgdspMainData"
dlabel njpgdspMainDataEnd
