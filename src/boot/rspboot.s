.include "macro.inc"

.section .text

.balign 16

glabel rspbootTextStart
    .incbin "incbin/rspbootText"
glabel rspbootTextEnd
