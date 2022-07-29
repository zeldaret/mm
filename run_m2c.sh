#!/usr/bin/env bash

./tools/m2ctx.py -c src/overlays/actors/ovl_player_actor/z_player.c 

./../mips_to_c/m2c.py --pointer-style left --context ctx.c --unk-underscore --hex-case --target mips-ido-c asm/overlays/ovl_player_actor/ovl_player_actor.text.s data/ovl_player_actor/ovl_player_actor.* --globals all > player.c 
