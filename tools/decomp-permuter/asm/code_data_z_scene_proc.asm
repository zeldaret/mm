.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel gSceneProcDefaultDl
/* 292904 0x801C3B60 */ .word	0xDB060020
/* 292905 0x801C3B64 */ .word	gEmptyDL
/* 292906 0x801C3B68 */ .word	0xDB060024
/* 292907 0x801C3B6C */ .word	gEmptyDL
/* 292908 0x801C3B70 */ .word	0xDB060028
/* 292909 0x801C3B74 */ .word	gEmptyDL
/* 292910 0x801C3B78 */ .word	0xDB06002C
/* 292911 0x801C3B7C */ .word	gEmptyDL
/* 292912 0x801C3B80 */ .word	0xDB060030
/* 292913 0x801C3B84 */ .word	gEmptyDL
/* 292914 0x801C3B88 */ .word	0xDB060034
/* 292915 0x801C3B8C */ .word	gEmptyDL
/* 292916 0x801C3B90 */ .word	0xDB060018
/* 292917 0x801C3B94 */ .word	gEmptyDL
/* 292918 0x801C3B98 */ .word	0xE7000000
/* 292919 0x801C3B9C */ .word	0x00000000
/* 292920 0x801C3BA0 */ .word	0xFA000000
/* 292921 0x801C3BA4 */ .word	0x80808080
/* 292922 0x801C3BA8 */ .word	0xFB000000
/* 292923 0x801C3BAC */ .word	0x80808080
/* 292924 0x801C3BB0 */ .word	0xDF000000
/* 292925 0x801C3BB4 */ .word	0x00000000
glabel gSceneProcSceneDrawFuncs
/* 292926 0x801C3BB8 */ .word	SceneProc_DrawSceneConfig0
/* 292927 0x801C3BBC */ .word	SceneProc_DrawSceneConfig1
/* 292928 0x801C3BC0 */ .word	SceneProc_DrawSceneConfig2
/* 292929 0x801C3BC4 */ .word	SceneProc_DrawSceneConfig3
/* 292930 0x801C3BC8 */ .word	SceneProc_DrawSceneConfig4
/* 292931 0x801C3BCC */ .word	SceneProc_DrawSceneConfig5
/* 292932 0x801C3BD0 */ .word	SceneProc_DrawSceneConfig6
/* 292933 0x801C3BD4 */ .word	SceneProc_DrawSceneConfig7
glabel gSceneProcDrawFuncs
/* 292934 0x801C3BD8 */ .word	SceneProc_DrawType0Texture
/* 292935 0x801C3BDC */ .word	SceneProc_DrawType1Texture
/* 292936 0x801C3BE0 */ .word	SceneProc_DrawType2Texture
/* 292937 0x801C3BE4 */ .word	SceneProc_DrawType3Texture
/* 292938 0x801C3BE8 */ .word	SceneProc_DrawType4Texture
/* 292939 0x801C3BEC */ .word	SceneProc_DrawType5Texture
glabel D_801C3BF0
/* 292940 0x801C3BF0 */ .word	0xDF000000
/* 292941 0x801C3BF4 */ .word	0x00000000
/* 292942 0x801C3BF8 */ .word	0xDF000000
/* 292943 0x801C3BFC */ .word	0x00000000
/* 292944 0x801C3C00 */ .word	0xDF000000
/* 292945 0x801C3C04 */ .word	0x00000000
/* 292946 0x801C3C08 */ .word	0xDF000000
/* 292947 0x801C3C0C */ .word	0x00000000
glabel D_801C3C10
/* 292948 0x801C3C10 */ .word	0xE200001C
/* 292949 0x801C3C14 */ .word	0x0C1849D8
/* 292950 0x801C3C18 */ .word	0xDF000000
/* 292951 0x801C3C1C */ .word	0x00000000
/* 292952 0x801C3C20 */ .word	0xE200001C
/* 292953 0x801C3C24 */ .word	0xC81049D8
/* 292954 0x801C3C28 */ .word	0xDF000000
/* 292955 0x801C3C2C */ .word	0x00000000
glabel D_801C3C30
/* 292956 0x801C3C30 */ .word	0xE200001C
/* 292957 0x801C3C34 */ .word	0x0C1849F8
/* 292958 0x801C3C38 */ .word	0xDF000000
/* 292959 0x801C3C3C */ .word	0x00000000
/* 292960 0x801C3C40 */ .word	0xE200001C
/* 292961 0x801C3C44 */ .word	0xC81049F8
/* 292962 0x801C3C48 */ .word	0xDF000000
/* 292963 0x801C3C4C */ .word	0x00000000
glabel D_801C3C50
/* 292964 0x801C3C50 */ .word	D_801C3BF0
/* 292965 0x801C3C54 */ .word	D_801C3C10
/* 292966 0x801C3C58 */ .word	D_801C3C30
/* 292967 0x801C3C5C */ .word	0x00000000
glabel D_801C3C60
/* 292968 0x801C3C60 */ .word	0xD9FFFFFF
/* 292969 0x801C3C64 */ .word	0x00000400
/* 292970 0x801C3C68 */ .word	0xDF000000
/* 292971 0x801C3C6C */ .word	0x00000000
glabel D_801C3C70
/* 292972 0x801C3C70 */ .word	0xD9FFFFFF
/* 292973 0x801C3C74 */ .word	0x00000200
/* 292974 0x801C3C78 */ .word	0xDF000000
/* 292975 0x801C3C7C */ .word	0x00000000
glabel D_801C3C80
/* 292976 0x801C3C80 */ .word	D_801C3C60
/* 292977 0x801C3C84 */ .word	D_801C3C70
glabel D_801C3C88
/* 292978 0x801C3C88 */ .word	0xFA0000FF
/* 292979 0x801C3C8C */ .word	0xFFFFFFFF
/* 292980 0x801C3C90 */ .word	0xDF000000
/* 292981 0x801C3C94 */ .word	0x00000000
/* 292982 0x801C3C98 */ .word	0x00000000
/* 292983 0x801C3C9C */ .word	0x00000000
