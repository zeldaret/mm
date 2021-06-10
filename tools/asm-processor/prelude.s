.set noat
.set noreorder
.set gp=64
.macro glabel label
    .global \label
    \label:
.endm

