.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

.section .data

glabel D_801AE8F0
/* 271244 0x801AE8F0 */ .word	(gSaveContext + 0x00000EF8)
/* 271245 0x801AE8F4 */ .word	D_801DC120
/* 271246 0x801AE8F8 */ .word	(gSaveContext + 0x00000EF9)
/* 271247 0x801AE8FC */ .word	D_801DC134
/* 271248 0x801AE900 */ .word	(gSaveContext + 0x00000EFA)
/* 271249 0x801AE904 */ .word	D_801DC148
/* 271250 0x801AE908 */ .word	(gSaveContext + 0x00000EFB)
/* 271251 0x801AE90C */ .word	D_801DC15C
/* 271252 0x801AE910 */ .word	(gSaveContext + 0x00000EFC)
/* 271253 0x801AE914 */ .word	D_801DC170
/* 271254 0x801AE918 */ .word	(gSaveContext + 0x00000EFD)
/* 271255 0x801AE91C */ .word	D_801DC184
/* 271256 0x801AE920 */ .word	(gSaveContext + 0x00000EFE)
/* 271257 0x801AE924 */ .word	D_801DC198
/* 271258 0x801AE928 */ .word	(gSaveContext + 0x00000EFF)
/* 271259 0x801AE92C */ .word	D_801DC1AC
/* 271260 0x801AE930 */ .word	(gSaveContext + 0x00000F00)
/* 271261 0x801AE934 */ .word	D_801DC1C0
/* 271262 0x801AE938 */ .word	(gSaveContext + 0x00000F01)
/* 271263 0x801AE93C */ .word	D_801DC1D4
/* 271264 0x801AE940 */ .word	(gSaveContext + 0x00000F02)
/* 271265 0x801AE944 */ .word	D_801DC1E8
/* 271266 0x801AE948 */ .word	(gSaveContext + 0x00000F03)
/* 271267 0x801AE94C */ .word	D_801DC1FC
/* 271268 0x801AE950 */ .word	(gSaveContext + 0x00000F04)
/* 271269 0x801AE954 */ .word	D_801DC210
/* 271270 0x801AE958 */ .word	(gSaveContext + 0x00000F05)
/* 271271 0x801AE95C */ .word	D_801DC224
/* 271272 0x801AE960 */ .word	(gSaveContext + 0x00000F06)
/* 271273 0x801AE964 */ .word	D_801DC238
/* 271274 0x801AE968 */ .word	(gSaveContext + 0x00000F07)
/* 271275 0x801AE96C */ .word	D_801DC24C
/* 271276 0x801AE970 */ .word	(gSaveContext + 0x00000F08)
/* 271277 0x801AE974 */ .word	D_801DC260
/* 271278 0x801AE978 */ .word	(gSaveContext + 0x00000F09)
/* 271279 0x801AE97C */ .word	D_801DC274
/* 271280 0x801AE980 */ .word	(gSaveContext + 0x00000F0A)
/* 271281 0x801AE984 */ .word	D_801DC288
/* 271282 0x801AE988 */ .word	(gSaveContext + 0x00000F0B)
/* 271283 0x801AE98C */ .word	D_801DC29C
/* 271284 0x801AE990 */ .word	(gSaveContext + 0x00000F0C)
/* 271285 0x801AE994 */ .word	D_801DC2B0
/* 271286 0x801AE998 */ .word	(gSaveContext + 0x00000F0D)
/* 271287 0x801AE99C */ .word	D_801DC2C4
/* 271288 0x801AE9A0 */ .word	(gSaveContext + 0x00000F0E)
/* 271289 0x801AE9A4 */ .word	D_801DC2D8
/* 271290 0x801AE9A8 */ .word	(gSaveContext + 0x00000F0F)
/* 271291 0x801AE9AC */ .word	D_801DC2EC
/* 271292 0x801AE9B0 */ .word	(gSaveContext + 0x00000F10)
/* 271293 0x801AE9B4 */ .word	D_801DC300
/* 271294 0x801AE9B8 */ .word	(gSaveContext + 0x00000F11)
/* 271295 0x801AE9BC */ .word	D_801DC314
/* 271296 0x801AE9C0 */ .word	(gSaveContext + 0x00000F12)
/* 271297 0x801AE9C4 */ .word	D_801DC328
/* 271298 0x801AE9C8 */ .word	(gSaveContext + 0x00000F13)
/* 271299 0x801AE9CC */ .word	D_801DC33C
/* 271300 0x801AE9D0 */ .word	(gSaveContext + 0x00000F14)
/* 271301 0x801AE9D4 */ .word	D_801DC350
/* 271302 0x801AE9D8 */ .word	(gSaveContext + 0x00000F15)
/* 271303 0x801AE9DC */ .word	D_801DC364
/* 271304 0x801AE9E0 */ .word	(gSaveContext + 0x00000F16)
/* 271305 0x801AE9E4 */ .word	D_801DC378
/* 271306 0x801AE9E8 */ .word	(gSaveContext + 0x00000F17)
/* 271307 0x801AE9EC */ .word	D_801DC38C
/* 271308 0x801AE9F0 */ .word	(gSaveContext + 0x00000F18)
/* 271309 0x801AE9F4 */ .word	D_801DC3A0
/* 271310 0x801AE9F8 */ .word	(gSaveContext + 0x00000F19)
/* 271311 0x801AE9FC */ .word	D_801DC3B4
/* 271312 0x801AEA00 */ .word	(gSaveContext + 0x00000F1A)
/* 271313 0x801AEA04 */ .word	D_801DC3C8
/* 271314 0x801AEA08 */ .word	(gSaveContext + 0x00000F1B)
/* 271315 0x801AEA0C */ .word	D_801DC3DC
/* 271316 0x801AEA10 */ .word	(gSaveContext + 0x00000F1C)
/* 271317 0x801AEA14 */ .word	D_801DC3F0
/* 271318 0x801AEA18 */ .word	(gSaveContext + 0x00000F1D)
/* 271319 0x801AEA1C */ .word	D_801DC404
/* 271320 0x801AEA20 */ .word	(gSaveContext + 0x00000F1E)
/* 271321 0x801AEA24 */ .word	D_801DC418
/* 271322 0x801AEA28 */ .word	(gSaveContext + 0x00000F1F)
/* 271323 0x801AEA2C */ .word	D_801DC42C
/* 271324 0x801AEA30 */ .word	(gSaveContext + 0x00000F20)
/* 271325 0x801AEA34 */ .word	D_801DC440
/* 271326 0x801AEA38 */ .word	(gSaveContext + 0x00000F21)
/* 271327 0x801AEA3C */ .word	D_801DC454
/* 271328 0x801AEA40 */ .word	(gSaveContext + 0x00000F22)
/* 271329 0x801AEA44 */ .word	D_801DC468
/* 271330 0x801AEA48 */ .word	(gSaveContext + 0x00000F23)
/* 271331 0x801AEA4C */ .word	D_801DC47C
/* 271332 0x801AEA50 */ .word	(gSaveContext + 0x00000F24)
/* 271333 0x801AEA54 */ .word	D_801DC490
/* 271334 0x801AEA58 */ .word	(gSaveContext + 0x00000F25)
/* 271335 0x801AEA5C */ .word	D_801DC4A4
/* 271336 0x801AEA60 */ .word	(gSaveContext + 0x00000F26)
/* 271337 0x801AEA64 */ .word	D_801DC4B8
/* 271338 0x801AEA68 */ .word	(gSaveContext + 0x00000F27)
/* 271339 0x801AEA6C */ .word	D_801DC4CC
/* 271340 0x801AEA70 */ .word	(gSaveContext + 0x00000F28)
/* 271341 0x801AEA74 */ .word	D_801DC4E0
/* 271342 0x801AEA78 */ .word	(gSaveContext + 0x00000F29)
/* 271343 0x801AEA7C */ .word	D_801DC4F4
/* 271344 0x801AEA80 */ .word	(gSaveContext + 0x00000F2A)
/* 271345 0x801AEA84 */ .word	D_801DC508
/* 271346 0x801AEA88 */ .word	(gSaveContext + 0x00000F2B)
/* 271347 0x801AEA8C */ .word	D_801DC51C
/* 271348 0x801AEA90 */ .word	(gSaveContext + 0x00000F2C)
/* 271349 0x801AEA94 */ .word	D_801DC530
/* 271350 0x801AEA98 */ .word	(gSaveContext + 0x00000F2D)
/* 271351 0x801AEA9C */ .word	D_801DC544
/* 271352 0x801AEAA0 */ .word	(gSaveContext + 0x00000F2E)
/* 271353 0x801AEAA4 */ .word	D_801DC558
/* 271354 0x801AEAA8 */ .word	(gSaveContext + 0x00000F2F)
/* 271355 0x801AEAAC */ .word	D_801DC56C
/* 271356 0x801AEAB0 */ .word	(gSaveContext + 0x00000F30)
/* 271357 0x801AEAB4 */ .word	D_801DC580
/* 271358 0x801AEAB8 */ .word	(gSaveContext + 0x00000F31)
/* 271359 0x801AEABC */ .word	D_801DC594
/* 271360 0x801AEAC0 */ .word	(gSaveContext + 0x00000F32)
/* 271361 0x801AEAC4 */ .word	D_801DC5A8
/* 271362 0x801AEAC8 */ .word	(gSaveContext + 0x00000F33)
/* 271363 0x801AEACC */ .word	D_801DC5BC
/* 271364 0x801AEAD0 */ .word	(gSaveContext + 0x00000F34)
/* 271365 0x801AEAD4 */ .word	D_801DC5D0
/* 271366 0x801AEAD8 */ .word	(gSaveContext + 0x00000F35)
/* 271367 0x801AEADC */ .word	D_801DC5E4
/* 271368 0x801AEAE0 */ .word	(gSaveContext + 0x00000F36)
/* 271369 0x801AEAE4 */ .word	D_801DC5F8
/* 271370 0x801AEAE8 */ .word	(gSaveContext + 0x00000F37)
/* 271371 0x801AEAEC */ .word	D_801DC60C
/* 271372 0x801AEAF0 */ .word	(gSaveContext + 0x00000F38)
/* 271373 0x801AEAF4 */ .word	D_801DC620
/* 271374 0x801AEAF8 */ .word	(gSaveContext + 0x00000F39)
/* 271375 0x801AEAFC */ .word	D_801DC634
/* 271376 0x801AEB00 */ .word	(gSaveContext + 0x00000F3A)
/* 271377 0x801AEB04 */ .word	D_801DC648
/* 271378 0x801AEB08 */ .word	(gSaveContext + 0x00000F3B)
/* 271379 0x801AEB0C */ .word	D_801DC65C
/* 271380 0x801AEB10 */ .word	(gSaveContext + 0x00000F3C)
/* 271381 0x801AEB14 */ .word	D_801DC670
/* 271382 0x801AEB18 */ .word	(gSaveContext + 0x00000F3D)
/* 271383 0x801AEB1C */ .word	D_801DC684
/* 271384 0x801AEB20 */ .word	(gSaveContext + 0x00000F3E)
/* 271385 0x801AEB24 */ .word	D_801DC698
/* 271386 0x801AEB28 */ .word	(gSaveContext + 0x00000F3F)
/* 271387 0x801AEB2C */ .word	D_801DC6AC
/* 271388 0x801AEB30 */ .word	(gSaveContext + 0x00000F40)
/* 271389 0x801AEB34 */ .word	D_801DC6C0
/* 271390 0x801AEB38 */ .word	(gSaveContext + 0x00000F41)
/* 271391 0x801AEB3C */ .word	D_801DC6D4
/* 271392 0x801AEB40 */ .word	(gSaveContext + 0x00000F42)
/* 271393 0x801AEB44 */ .word	D_801DC6E8
/* 271394 0x801AEB48 */ .word	(gSaveContext + 0x00000F43)
/* 271395 0x801AEB4C */ .word	D_801DC6FC
/* 271396 0x801AEB50 */ .word	(gSaveContext + 0x00000F44)
/* 271397 0x801AEB54 */ .word	D_801DC710
/* 271398 0x801AEB58 */ .word	(gSaveContext + 0x00000F45)
/* 271399 0x801AEB5C */ .word	D_801DC724
/* 271400 0x801AEB60 */ .word	(gSaveContext + 0x00000F46)
/* 271401 0x801AEB64 */ .word	D_801DC738
/* 271402 0x801AEB68 */ .word	(gSaveContext + 0x00000F47)
/* 271403 0x801AEB6C */ .word	D_801DC74C
/* 271404 0x801AEB70 */ .word	(gSaveContext + 0x00000F48)
/* 271405 0x801AEB74 */ .word	D_801DC760
/* 271406 0x801AEB78 */ .word	(gSaveContext + 0x00000F49)
/* 271407 0x801AEB7C */ .word	D_801DC774
/* 271408 0x801AEB80 */ .word	(gSaveContext + 0x00000F4A)
/* 271409 0x801AEB84 */ .word	D_801DC788
/* 271410 0x801AEB88 */ .word	(gSaveContext + 0x00000F4B)
/* 271411 0x801AEB8C */ .word	D_801DC79C
/* 271412 0x801AEB90 */ .word	(gSaveContext + 0x00000F4C)
/* 271413 0x801AEB94 */ .word	D_801DC7B0
/* 271414 0x801AEB98 */ .word	(gSaveContext + 0x00000F4D)
/* 271415 0x801AEB9C */ .word	D_801DC7C4
/* 271416 0x801AEBA0 */ .word	(gSaveContext + 0x00000F4E)
/* 271417 0x801AEBA4 */ .word	D_801DC7D8
/* 271418 0x801AEBA8 */ .word	(gSaveContext + 0x00000F4F)
/* 271419 0x801AEBAC */ .word	D_801DC7EC
/* 271420 0x801AEBB0 */ .word	(gSaveContext + 0x00000F50)
/* 271421 0x801AEBB4 */ .word	D_801DC800
/* 271422 0x801AEBB8 */ .word	(gSaveContext + 0x00000F51)
/* 271423 0x801AEBBC */ .word	D_801DC814
/* 271424 0x801AEBC0 */ .word	(gSaveContext + 0x00000F52)
/* 271425 0x801AEBC4 */ .word	D_801DC828
/* 271426 0x801AEBC8 */ .word	(gSaveContext + 0x00000F53)
/* 271427 0x801AEBCC */ .word	D_801DC83C
/* 271428 0x801AEBD0 */ .word	(gSaveContext + 0x00000F54)
/* 271429 0x801AEBD4 */ .word	D_801DC850
/* 271430 0x801AEBD8 */ .word	(gSaveContext + 0x00000F55)
/* 271431 0x801AEBDC */ .word	D_801DC864
/* 271432 0x801AEBE0 */ .word	(gSaveContext + 0x00000F56)
/* 271433 0x801AEBE4 */ .word	D_801DC878
/* 271434 0x801AEBE8 */ .word	(gSaveContext + 0x00000F57)
/* 271435 0x801AEBEC */ .word	D_801DC88C
/* 271436 0x801AEBF0 */ .word	(gSaveContext + 0x00000F58)
/* 271437 0x801AEBF4 */ .word	D_801DC8A0
/* 271438 0x801AEBF8 */ .word	(gSaveContext + 0x00000F59)
/* 271439 0x801AEBFC */ .word	D_801DC8B4
/* 271440 0x801AEC00 */ .word	(gSaveContext + 0x00000F5A)
/* 271441 0x801AEC04 */ .word	D_801DC8C8
/* 271442 0x801AEC08 */ .word	(gSaveContext + 0x00000F5B)
/* 271443 0x801AEC0C */ .word	D_801DC8DC
/* 271444 0x801AEC10 */ .word	(gSaveContext + 0x0000100C)
/* 271445 0x801AEC14 */ .word	D_801DC8F0
/* 271446 0x801AEC18 */ .word	(gSaveContext + 0x0000100D)
/* 271447 0x801AEC1C */ .word	D_801DC900
/* 271448 0x801AEC20 */ .word	(gSaveContext + 0x0000100E)
/* 271449 0x801AEC24 */ .word	D_801DC910
/* 271450 0x801AEC28 */ .word	(gSaveContext + 0x0000100F)
/* 271451 0x801AEC2C */ .word	D_801DC920
/* 271452 0x801AEC30 */ .word	(gSaveContext + 0x00001010)
/* 271453 0x801AEC34 */ .word	D_801DC930
/* 271454 0x801AEC38 */ .word	(gSaveContext + 0x00001011)
/* 271455 0x801AEC3C */ .word	D_801DC940
/* 271456 0x801AEC40 */ .word	(gSaveContext + 0x00001012)
/* 271457 0x801AEC44 */ .word	D_801DC950
/* 271458 0x801AEC48 */ .word	(gSaveContext + 0x00001013)
/* 271459 0x801AEC4C */ .word	D_801DC960
/* 271460 0x801AEC50 */ .word	D_801F3F3A
/* 271461 0x801AEC54 */ .word	D_801DC970
/* 271462 0x801AEC58 */ .word	D_801F3F3B
/* 271463 0x801AEC5C */ .word	D_801DC984
/* 271464 0x801AEC60 */ .word	D_801F3F3C
/* 271465 0x801AEC64 */ .word	D_801DC998
/* 271466 0x801AEC68 */ .word	0x00000000
/* 271467 0x801AEC6C */ .word	0x00000000
