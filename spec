/*
 * ROM spec file
 */

beginseg
    name "makerom"
    include "build/asm/makerom/rom_header.o"
    include "build/asm/makerom/ipl3.o"
    include "build/asm/makerom/entry.o"
endseg

beginseg
    name "boot"
    include "build/baserom/boot.o"
endseg

beginseg
    name "dmadata"
    include "build/baserom/dmadata.o"
endseg

beginseg
    name "Audiobank"
    include "build/baserom/Audiobank.o"
endseg

beginseg
    name "Audioseq"
    include "build/baserom/Audioseq.o"
endseg

beginseg
    name "Audiotable"
    include "build/baserom/Audiotable.o"
endseg

beginseg
    name "kanji"
    include "build/baserom/kanji.o"
endseg

beginseg
    name "link_animetion"
    romalign 0x1000
    include "build/baserom/link_animetion.o"
endseg

beginseg
    name "009ECEC0_00957000"
    romalign 0x1000
    include "build/baserom/009ECEC0_00957000.o"
endseg

beginseg
    name "009F4700_009ED000"
    romalign 0x1000
    include "build/baserom/009F4700_009ED000.o"
endseg

beginseg
    name "icon_item_field_static"
    compress
    romalign 0x1000
    include "build/baserom/icon_item_field_static.o"
endseg

beginseg
    name "icon_item_dungeon_static"
    compress
    romalign 0x1000
    include "build/baserom/icon_item_dungeon_static.o"
endseg

beginseg
    name "icon_item_gameover_static"
    compress
    romalign 0x1000
    include "build/baserom/icon_item_gameover_static.o"
endseg

beginseg
    name "icon_item_jpn_static"
    compress
    romalign 0x1000
    include "build/baserom/icon_item_jpn_static.o"
endseg

beginseg
    name "icon_item_vtx_static"
    compress
    romalign 0x1000
    include "build/baserom/icon_item_vtx_static.o"
endseg

beginseg
    name "map_i_static"
    include "build/baserom/map_i_static.o"
endseg

beginseg
    name "map_grand_static"
    include "build/baserom/map_grand_static.o"
endseg

beginseg
    name "item_name_static"
    include "build/baserom/item_name_static.o"
endseg

beginseg
    name "map_name_static"
    include "build/baserom/map_name_static.o"
endseg

beginseg
    name "icon_item_static_test"
    include "build/baserom/icon_item_static_test.o"
endseg

beginseg
    name "icon_item_24_static_test"
    include "build/baserom/icon_item_24_static_test.o"
endseg

beginseg
    name "00A8B9C0_00A807A0"
    include "build/baserom/00A8B9C0_00A807A0.o"
endseg

beginseg
    name "schedule_dma_static_test"
    increment 0x1000
    include "build/baserom/schedule_dma_static_test.o"
endseg

beginseg
    name "schedule_static"
    compress
    include "build/baserom/schedule_static.o"
endseg

beginseg
    name "story_static"
    compress
    romalign 0x1000
    include "build/baserom/story_static.o"
endseg

beginseg
    name "do_action_static"
    romalign 0x1000
    include "build/baserom/do_action_static.o"
endseg

beginseg
    name "message_static"
    romalign 0x1000
    include "build/baserom/message_static.o"
endseg

beginseg
    name "message_texture_static"
    romalign 0x1000
    include "build/baserom/message_texture_static.o"
endseg

beginseg
    name "nes_font_static"
    romalign 0x1000
    include "build/baserom/nes_font_static.o"
endseg

beginseg
    name "message_data_static"
    romalign 0x1000
    include "build/baserom/message_data_static.o"
endseg

beginseg
    name "staff_message_data_static"
    romalign 0x1000
    include "build/baserom/staff_message_data_static.o"
endseg

beginseg
    name "code"
    compress
    include "build/baserom/code.o"
endseg

beginseg
    name "ovl_title"
    compress
    include "build/baserom/ovl_title.o"
endseg

beginseg
    name "ovl_select"
    compress
    include "build/baserom/ovl_select.o"
endseg

beginseg
    name "ovl_opening"
    compress
    include "build/baserom/ovl_opening.o"
endseg

beginseg
    name "ovl_file_choose"
    compress
    include "build/baserom/ovl_file_choose.o"
endseg

beginseg
    name "ovl_daytelop"
    compress
    include "build/baserom/ovl_daytelop.o"
endseg

beginseg
    name "ovl_kaleido_scope"
    compress
    include "build/baserom/ovl_kaleido_scope.o"
endseg

beginseg
    name "ovl_Player_Actor"
    compress
    include "build/baserom/ovl_Player_Actor.o"
endseg

beginseg
    name "ovl_En_Test"
    compress
    include "build/baserom/ovl_En_Test.o"
endseg

beginseg
    name "ovl_En_GirlA"
    compress
    include "build/baserom/ovl_En_GirlA.o"
endseg

beginseg
    name "ovl_En_Part"
    compress
    include "build/baserom/ovl_En_Part.o"
endseg

beginseg
    name "ovl_En_Light"
    compress
    include "build/baserom/ovl_En_Light.o"
endseg

beginseg
    name "ovl_En_Door"
    compress
    include "build/baserom/ovl_En_Door.o"
endseg

beginseg
    name "ovl_En_Box"
    compress
    include "build/baserom/ovl_En_Box.o"
endseg

beginseg
    name "ovl_En_Pametfrog"
    compress
    include "build/baserom/ovl_En_Pametfrog.o"
endseg

beginseg
    name "ovl_En_Okuta"
    compress
    include "build/baserom/ovl_En_Okuta.o"
endseg

beginseg
    name "ovl_En_Bom"
    compress
    include "build/baserom/ovl_En_Bom.o"
endseg

beginseg
    name "ovl_En_Wallmas"
    compress
    include "build/baserom/ovl_En_Wallmas.o"
endseg

beginseg
    name "ovl_En_Dodongo"
    compress
    include "build/baserom/ovl_En_Dodongo.o"
endseg

beginseg
    name "ovl_En_Firefly"
    compress
    include "build/baserom/ovl_En_Firefly.o"
endseg

beginseg
    name "ovl_En_Horse"
    compress
    include "build/baserom/ovl_En_Horse.o"
endseg

beginseg
    name "ovl_En_Arrow"
    compress
    include "build/baserom/ovl_En_Arrow.o"
endseg

beginseg
    name "ovl_En_Elf"
    compress
    include "build/baserom/ovl_En_Elf.o"
endseg

beginseg
    name "ovl_En_Niw"
    compress
    include "build/baserom/ovl_En_Niw.o"
endseg

beginseg
    name "ovl_En_Tite"
    compress
    include "build/baserom/ovl_En_Tite.o"
endseg

beginseg
    name "ovl_En_Peehat"
    compress
    include "build/baserom/ovl_En_Peehat.o"
endseg

beginseg
    name "ovl_En_Holl"
    compress
    include "build/baserom/ovl_En_Holl.o"
endseg

beginseg
    name "ovl_En_Dinofos"
    compress
    include "build/baserom/ovl_En_Dinofos.o"
endseg

beginseg
    name "ovl_En_Hata"
    compress
    include "build/baserom/ovl_En_Hata.o"
endseg

beginseg
    name "ovl_En_Zl1"
    compress
    include "build/baserom/ovl_En_Zl1.o"
endseg

beginseg
    name "ovl_En_Viewer"
    compress
    include "build/baserom/ovl_En_Viewer.o"
endseg

beginseg
    name "ovl_En_Bubble"
    compress
    include "build/baserom/ovl_En_Bubble.o"
endseg

beginseg
    name "ovl_Door_Shutter"
    compress
    include "build/baserom/ovl_Door_Shutter.o"
endseg

beginseg
    name "ovl_En_Boom"
    compress
    include "build/baserom/ovl_En_Boom.o"
endseg

beginseg
    name "ovl_En_Torch2"
    compress
    include "build/baserom/ovl_En_Torch2.o"
endseg

beginseg
    name "ovl_En_Minifrog"
    compress
    include "build/baserom/ovl_En_Minifrog.o"
endseg

beginseg
    name "ovl_En_St"
    compress
    include "build/baserom/ovl_En_St.o"
endseg

beginseg
    name "ovl_Obj_Wturn"
    compress
    include "build/baserom/ovl_Obj_Wturn.o"
endseg

beginseg
    name "ovl_En_River_Sound"
    compress
    include "build/baserom/ovl_En_River_Sound.o"
endseg

beginseg
    name "ovl_En_Ossan"
    compress
    include "build/baserom/ovl_En_Ossan.o"
endseg

beginseg
    name "ovl_En_Famos"
    compress
    include "build/baserom/ovl_En_Famos.o"
endseg

beginseg
    name "ovl_En_Bombf"
    compress
    include "build/baserom/ovl_En_Bombf.o"
endseg

beginseg
    name "ovl_En_Am"
    compress
    include "build/baserom/ovl_En_Am.o"
endseg

beginseg
    name "ovl_En_Dekubaba"
    compress
    include "build/baserom/ovl_En_Dekubaba.o"
endseg

beginseg
    name "ovl_En_M_Fire1"
    compress
    include "build/baserom/ovl_En_M_Fire1.o"
endseg

beginseg
    name "ovl_En_M_Thunder"
    compress
    include "build/baserom/ovl_En_M_Thunder.o"
endseg

beginseg
    name "ovl_Bg_Breakwall"
    compress
    include "build/baserom/ovl_Bg_Breakwall.o"
endseg

beginseg
    name "ovl_Door_Warp1"
    compress
    include "build/baserom/ovl_Door_Warp1.o"
endseg

beginseg
    name "ovl_Obj_Syokudai"
    compress
    include "build/baserom/ovl_Obj_Syokudai.o"
endseg

beginseg
    name "ovl_Item_B_Heart"
    compress
    include "build/baserom/ovl_Item_B_Heart.o"
endseg

beginseg
    name "ovl_En_Dekunuts"
    compress
    include "build/baserom/ovl_En_Dekunuts.o"
endseg

beginseg
    name "ovl_En_Bbfall"
    compress
    include "build/baserom/ovl_En_Bbfall.o"
endseg

beginseg
    name "ovl_Arms_Hook"
    compress
    include "build/baserom/ovl_Arms_Hook.o"
endseg

beginseg
    name "ovl_En_Bb"
    compress
    include "build/baserom/ovl_En_Bb.o"
endseg

beginseg
    name "ovl_Bg_Keikoku_Spr"
    compress
    include "build/baserom/ovl_Bg_Keikoku_Spr.o"
endseg

beginseg
    name "ovl_En_Wood02"
    compress
    include "build/baserom/ovl_En_Wood02.o"
endseg

beginseg
    name "ovl_En_Death"
    compress
    include "build/baserom/ovl_En_Death.o"
endseg

beginseg
    name "ovl_En_Minideath"
    compress
    include "build/baserom/ovl_En_Minideath.o"
endseg

beginseg
    name "ovl_En_Vm"
    compress
    include "build/baserom/ovl_En_Vm.o"
endseg

beginseg
    name "ovl_Demo_Effect"
    compress
    include "build/baserom/ovl_Demo_Effect.o"
endseg

beginseg
    name "ovl_Demo_Kankyo"
    compress
    include "build/baserom/ovl_Demo_Kankyo.o"
endseg

beginseg
    name "ovl_En_Floormas"
    compress
    include "build/baserom/ovl_En_Floormas.o"
endseg

beginseg
    name "ovl_En_Rd"
    compress
    include "build/baserom/ovl_En_Rd.o"
endseg

beginseg
    name "ovl_Bg_F40_Flift"
    compress
    include "build/baserom/ovl_Bg_F40_Flift.o"
endseg

beginseg
    name "ovl_Obj_Mure"
    compress
    include "build/baserom/ovl_Obj_Mure.o"
endseg

beginseg
    name "ovl_En_Sw"
    compress
    include "build/baserom/ovl_En_Sw.o"
endseg

beginseg
    name "ovl_Object_Kankyo"
    compress
    include "build/baserom/ovl_Object_Kankyo.o"
endseg

beginseg
    name "ovl_En_Horse_Link_Child"
    compress
    include "build/baserom/ovl_En_Horse_Link_Child.o"
endseg

beginseg
    name "ovl_Door_Ana"
    compress
    include "build/baserom/ovl_Door_Ana.o"
endseg

beginseg
    name "ovl_En_Encount1"
    compress
    include "build/baserom/ovl_En_Encount1.o"
endseg

beginseg
    name "ovl_Demo_Tre_Lgt"
    compress
    include "build/baserom/ovl_Demo_Tre_Lgt.o"
endseg

beginseg
    name "ovl_En_Encount2"
    compress
    include "build/baserom/ovl_En_Encount2.o"
endseg

beginseg
    name "ovl_En_Fire_Rock"
    compress
    include "build/baserom/ovl_En_Fire_Rock.o"
endseg

beginseg
    name "ovl_Bg_Ctower_Rot"
    compress
    include "build/baserom/ovl_Bg_Ctower_Rot.o"
endseg

beginseg
    name "ovl_Mir_Ray"
    compress
    include "build/baserom/ovl_Mir_Ray.o"
endseg

beginseg
    name "ovl_En_Sb"
    compress
    include "build/baserom/ovl_En_Sb.o"
endseg

beginseg
    name "ovl_En_Bigslime"
    compress
    include "build/baserom/ovl_En_Bigslime.o"
endseg

beginseg
    name "ovl_En_Karebaba"
    compress
    include "build/baserom/ovl_En_Karebaba.o"
endseg

beginseg
    name "ovl_En_In"
    compress
    include "build/baserom/ovl_En_In.o"
endseg

beginseg
    name "ovl_En_Bom_Chu"
    compress
    include "build/baserom/ovl_En_Bom_Chu.o"
endseg

beginseg
    name "ovl_En_Horse_Game_Check"
    compress
    include "build/baserom/ovl_En_Horse_Game_Check.o"
endseg

beginseg
    name "ovl_En_Rr"
    compress
    include "build/baserom/ovl_En_Rr.o"
endseg

beginseg
    name "ovl_En_Fr"
    compress
    include "build/baserom/ovl_En_Fr.o"
endseg

beginseg
    name "ovl_En_Fishing"
    compress
    include "build/baserom/ovl_En_Fishing.o"
endseg

beginseg
    name "ovl_Obj_Oshihiki"
    compress
    include "build/baserom/ovl_Obj_Oshihiki.o"
endseg

beginseg
    name "ovl_Eff_Dust"
    compress
    include "build/baserom/ovl_Eff_Dust.o"
endseg

beginseg
    name "ovl_Bg_Umajump"
    compress
    include "build/baserom/ovl_Bg_Umajump.o"
endseg

beginseg
    name "ovl_En_Insect"
    compress
    include "build/baserom/ovl_En_Insect.o"
endseg

beginseg
    name "ovl_En_Butte"
    compress
    include "build/baserom/ovl_En_Butte.o"
endseg

beginseg
    name "ovl_En_Fish"
    compress
    include "build/baserom/ovl_En_Fish.o"
endseg

beginseg
    name "ovl_Item_Etcetera"
    compress
    include "build/baserom/ovl_Item_Etcetera.o"
endseg

beginseg
    name "ovl_Arrow_Fire"
    compress
    include "build/baserom/ovl_Arrow_Fire.o"
endseg

beginseg
    name "ovl_Arrow_Ice"
    compress
    include "build/baserom/ovl_Arrow_Ice.o"
endseg

beginseg
    name "ovl_Arrow_Light"
    compress
    include "build/baserom/ovl_Arrow_Light.o"
endseg

beginseg
    name "ovl_Obj_Kibako"
    compress
    include "build/baserom/ovl_Obj_Kibako.o"
endseg

beginseg
    name "ovl_Obj_Tsubo"
    compress
    include "build/baserom/ovl_Obj_Tsubo.o"
endseg

beginseg
    name "ovl_En_Ik"
    compress
    include "build/baserom/ovl_En_Ik.o"
endseg

beginseg
    name "ovl_Demo_Shd"
    compress
    include "build/baserom/ovl_Demo_Shd.o"
endseg

beginseg
    name "ovl_En_Dns"
    compress
    include "build/baserom/ovl_En_Dns.o"
endseg

beginseg
    name "ovl_Elf_Msg"
    compress
    include "build/baserom/ovl_Elf_Msg.o"
endseg

beginseg
    name "ovl_En_Honotrap"
    compress
    include "build/baserom/ovl_En_Honotrap.o"
endseg

beginseg
    name "ovl_En_Tubo_Trap"
    compress
    include "build/baserom/ovl_En_Tubo_Trap.o"
endseg

beginseg
    name "ovl_Obj_Ice_Poly"
    compress
    include "build/baserom/ovl_Obj_Ice_Poly.o"
endseg

beginseg
    name "ovl_En_Fz"
    compress
    include "build/baserom/ovl_En_Fz.o"
endseg

beginseg
    name "ovl_En_Kusa"
    compress
    include "build/baserom/ovl_En_Kusa.o"
endseg

beginseg
    name "ovl_Obj_Bean"
    compress
    include "build/baserom/ovl_Obj_Bean.o"
endseg

beginseg
    name "ovl_Obj_Bombiwa"
    compress
    include "build/baserom/ovl_Obj_Bombiwa.o"
endseg

beginseg
    name "ovl_Obj_Switch"
    compress
    include "build/baserom/ovl_Obj_Switch.o"
endseg

beginseg
    name "ovl_Obj_Lift"
    compress
    include "build/baserom/ovl_Obj_Lift.o"
endseg

beginseg
    name "ovl_Obj_Hsblock"
    compress
    include "build/baserom/ovl_Obj_Hsblock.o"
endseg

beginseg
    name "ovl_En_Okarina_Tag"
    compress
    include "build/baserom/ovl_En_Okarina_Tag.o"
endseg

beginseg
    name "ovl_En_Goroiwa"
    compress
    include "build/baserom/ovl_En_Goroiwa.o"
endseg

beginseg
    name "ovl_En_Daiku"
    compress
    include "build/baserom/ovl_En_Daiku.o"
endseg

beginseg
    name "ovl_En_Nwc"
    compress
    include "build/baserom/ovl_En_Nwc.o"
endseg

beginseg
    name "ovl_Item_Inbox"
    compress
    include "build/baserom/ovl_Item_Inbox.o"
endseg

beginseg
    name "ovl_En_Ge1"
    compress
    include "build/baserom/ovl_En_Ge1.o"
endseg

beginseg
    name "ovl_Obj_Blockstop"
    compress
    include "build/baserom/ovl_Obj_Blockstop.o"
endseg

beginseg
    name "ovl_En_Sda"
    compress
    include "build/baserom/ovl_En_Sda.o"
endseg

beginseg
    name "ovl_En_Clear_Tag"
    compress
    include "build/baserom/ovl_En_Clear_Tag.o"
endseg

beginseg
    name "ovl_En_Gm"
    compress
    include "build/baserom/ovl_En_Gm.o"
endseg

beginseg
    name "ovl_En_Ms"
    compress
    include "build/baserom/ovl_En_Ms.o"
endseg

beginseg
    name "ovl_En_Hs"
    compress
    include "build/baserom/ovl_En_Hs.o"
endseg

beginseg
    name "ovl_Bg_Ingate"
    compress
    include "build/baserom/ovl_Bg_Ingate.o"
endseg

beginseg
    name "ovl_En_Kanban"
    compress
    include "build/baserom/ovl_En_Kanban.o"
endseg

beginseg
    name "ovl_En_Attack_Niw"
    compress
    include "build/baserom/ovl_En_Attack_Niw.o"
endseg

beginseg
    name "ovl_En_Mk"
    compress
    include "build/baserom/ovl_En_Mk.o"
endseg

beginseg
    name "ovl_En_Owl"
    compress
    include "build/baserom/ovl_En_Owl.o"
endseg

beginseg
    name "ovl_En_Ishi"
    compress
    include "build/baserom/ovl_En_Ishi.o"
endseg

beginseg
    name "ovl_Obj_Hana"
    compress
    include "build/baserom/ovl_Obj_Hana.o"
endseg

beginseg
    name "ovl_Obj_Lightswitch"
    compress
    include "build/baserom/ovl_Obj_Lightswitch.o"
endseg

beginseg
    name "ovl_Obj_Mure2"
    compress
    include "build/baserom/ovl_Obj_Mure2.o"
endseg

beginseg
    name "ovl_En_Fu"
    compress
    include "build/baserom/ovl_En_Fu.o"
endseg

beginseg
    name "ovl_En_Stream"
    compress
    include "build/baserom/ovl_En_Stream.o"
endseg

beginseg
    name "ovl_En_Mm"
    compress
    include "build/baserom/ovl_En_Mm.o"
endseg

beginseg
    name "ovl_En_Weather_Tag"
    compress
    include "build/baserom/ovl_En_Weather_Tag.o"
endseg

beginseg
    name "ovl_En_Ani"
    compress
    include "build/baserom/ovl_En_Ani.o"
endseg

beginseg
    name "ovl_En_Js"
    compress
    include "build/baserom/ovl_En_Js.o"
endseg

beginseg
    name "ovl_En_Okarina_Effect"
    compress
    include "build/baserom/ovl_En_Okarina_Effect.o"
endseg

beginseg
    name "ovl_En_Mag"
    compress
    include "build/baserom/ovl_En_Mag.o"
endseg

beginseg
    name "ovl_Elf_Msg2"
    compress
    include "build/baserom/ovl_Elf_Msg2.o"
endseg

beginseg
    name "ovl_Bg_F40_Swlift"
    compress
    include "build/baserom/ovl_Bg_F40_Swlift.o"
endseg

beginseg
    name "ovl_En_Kakasi"
    compress
    include "build/baserom/ovl_En_Kakasi.o"
endseg

beginseg
    name "ovl_Obj_Makeoshihiki"
    compress
    include "build/baserom/ovl_Obj_Makeoshihiki.o"
endseg

beginseg
    name "ovl_Oceff_Spot"
    compress
    include "build/baserom/ovl_Oceff_Spot.o"
endseg

beginseg
    name "ovl_En_Torch"
    compress
    include "build/baserom/ovl_En_Torch.o"
endseg

beginseg
    name "ovl_Shot_Sun"
    compress
    include "build/baserom/ovl_Shot_Sun.o"
endseg

beginseg
    name "ovl_Obj_Roomtimer"
    compress
    include "build/baserom/ovl_Obj_Roomtimer.o"
endseg

beginseg
    name "ovl_En_Ssh"
    compress
    include "build/baserom/ovl_En_Ssh.o"
endseg

beginseg
    name "ovl_Oceff_Wipe"
    compress
    include "build/baserom/ovl_Oceff_Wipe.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dust"
    compress
    include "build/baserom/ovl_Effect_Ss_Dust.o"
endseg

beginseg
    name "ovl_Effect_Ss_Kirakira"
    compress
    include "build/baserom/ovl_Effect_Ss_Kirakira.o"
endseg

beginseg
    name "ovl_Effect_Ss_Bomb2"
    compress
    include "build/baserom/ovl_Effect_Ss_Bomb2.o"
endseg

beginseg
    name "ovl_Effect_Ss_Blast"
    compress
    include "build/baserom/ovl_Effect_Ss_Blast.o"
endseg

beginseg
    name "ovl_Effect_Ss_G_Spk"
    compress
    include "build/baserom/ovl_Effect_Ss_G_Spk.o"
endseg

beginseg
    name "ovl_Effect_Ss_D_Fire"
    compress
    include "build/baserom/ovl_Effect_Ss_D_Fire.o"
endseg

beginseg
    name "ovl_Effect_Ss_Bubble"
    compress
    include "build/baserom/ovl_Effect_Ss_Bubble.o"
endseg

beginseg
    name "ovl_Effect_Ss_G_Ripple"
    compress
    include "build/baserom/ovl_Effect_Ss_G_Ripple.o"
endseg

beginseg
    name "ovl_Effect_Ss_G_Splash"
    compress
    include "build/baserom/ovl_Effect_Ss_G_Splash.o"
endseg

beginseg
    name "ovl_Effect_Ss_G_Fire"
    compress
    include "build/baserom/ovl_Effect_Ss_G_Fire.o"
endseg

beginseg
    name "ovl_Effect_Ss_Lightning"
    compress
    include "build/baserom/ovl_Effect_Ss_Lightning.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dt_Bubble"
    compress
    include "build/baserom/ovl_Effect_Ss_Dt_Bubble.o"
endseg

beginseg
    name "ovl_Effect_Ss_Hahen"
    compress
    include "build/baserom/ovl_Effect_Ss_Hahen.o"
endseg

beginseg
    name "ovl_Effect_Ss_Stick"
    compress
    include "build/baserom/ovl_Effect_Ss_Stick.o"
endseg

beginseg
    name "ovl_Effect_Ss_Sibuki"
    compress
    include "build/baserom/ovl_Effect_Ss_Sibuki.o"
endseg

beginseg
    name "ovl_Effect_Ss_Stone1"
    compress
    include "build/baserom/ovl_Effect_Ss_Stone1.o"
endseg

beginseg
    name "ovl_Effect_Ss_Hitmark"
    compress
    include "build/baserom/ovl_Effect_Ss_Hitmark.o"
endseg

beginseg
    name "ovl_Effect_Ss_Fhg_Flash"
    compress
    include "build/baserom/ovl_Effect_Ss_Fhg_Flash.o"
endseg

beginseg
    name "ovl_Effect_Ss_K_Fire"
    compress
    include "build/baserom/ovl_Effect_Ss_K_Fire.o"
endseg

beginseg
    name "ovl_Effect_Ss_Solder_Srch_Ball"
    compress
    include "build/baserom/ovl_Effect_Ss_Solder_Srch_Ball.o"
endseg

beginseg
    name "ovl_Effect_Ss_Kakera"
    compress
    include "build/baserom/ovl_Effect_Ss_Kakera.o"
endseg

beginseg
    name "ovl_Effect_Ss_Ice_Piece"
    compress
    include "build/baserom/ovl_Effect_Ss_Ice_Piece.o"
endseg

beginseg
    name "ovl_Effect_Ss_En_Ice"
    compress
    include "build/baserom/ovl_Effect_Ss_En_Ice.o"
endseg

beginseg
    name "ovl_Effect_Ss_Fire_Tail"
    compress
    include "build/baserom/ovl_Effect_Ss_Fire_Tail.o"
endseg

beginseg
    name "ovl_Effect_Ss_En_Fire"
    compress
    include "build/baserom/ovl_Effect_Ss_En_Fire.o"
endseg

beginseg
    name "ovl_Effect_Ss_Extra"
    compress
    include "build/baserom/ovl_Effect_Ss_Extra.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dead_Db"
    compress
    include "build/baserom/ovl_Effect_Ss_Dead_Db.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dead_Dd"
    compress
    include "build/baserom/ovl_Effect_Ss_Dead_Dd.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dead_Ds"
    compress
    include "build/baserom/ovl_Effect_Ss_Dead_Ds.o"
endseg

beginseg
    name "ovl_Oceff_Storm"
    compress
    include "build/baserom/ovl_Oceff_Storm.o"
endseg

beginseg
    name "ovl_Obj_Demo"
    compress
    include "build/baserom/ovl_Obj_Demo.o"
endseg

beginseg
    name "ovl_En_Minislime"
    compress
    include "build/baserom/ovl_En_Minislime.o"
endseg

beginseg
    name "ovl_En_Nutsball"
    compress
    include "build/baserom/ovl_En_Nutsball.o"
endseg

beginseg
    name "ovl_Oceff_Wipe2"
    compress
    include "build/baserom/ovl_Oceff_Wipe2.o"
endseg

beginseg
    name "ovl_Oceff_Wipe3"
    compress
    include "build/baserom/ovl_Oceff_Wipe3.o"
endseg

beginseg
    name "ovl_En_Dg"
    compress
    include "build/baserom/ovl_En_Dg.o"
endseg

beginseg
    name "ovl_En_Si"
    compress
    include "build/baserom/ovl_En_Si.o"
endseg

beginseg
    name "ovl_Obj_Comb"
    compress
    include "build/baserom/ovl_Obj_Comb.o"
endseg

beginseg
    name "ovl_Obj_Kibako2"
    compress
    include "build/baserom/ovl_Obj_Kibako2.o"
endseg

beginseg
    name "ovl_En_Hs2"
    compress
    include "build/baserom/ovl_En_Hs2.o"
endseg

beginseg
    name "ovl_Obj_Mure3"
    compress
    include "build/baserom/ovl_Obj_Mure3.o"
endseg

beginseg
    name "ovl_En_Tg"
    compress
    include "build/baserom/ovl_En_Tg.o"
endseg

beginseg
    name "ovl_En_Wf"
    compress
    include "build/baserom/ovl_En_Wf.o"
endseg

beginseg
    name "ovl_En_Skb"
    compress
    include "build/baserom/ovl_En_Skb.o"
endseg

beginseg
    name "ovl_En_Gs"
    compress
    include "build/baserom/ovl_En_Gs.o"
endseg

beginseg
    name "ovl_Obj_Sound"
    compress
    include "build/baserom/ovl_Obj_Sound.o"
endseg

beginseg
    name "ovl_En_Crow"
    compress
    include "build/baserom/ovl_En_Crow.o"
endseg

beginseg
    name "ovl_En_Cow"
    compress
    include "build/baserom/ovl_En_Cow.o"
endseg

beginseg
    name "ovl_Oceff_Wipe4"
    compress
    include "build/baserom/ovl_Oceff_Wipe4.o"
endseg

beginseg
    name "ovl_En_Zo"
    compress
    include "build/baserom/ovl_En_Zo.o"
endseg

beginseg
    name "ovl_Effect_Ss_Ice_Smoke"
    compress
    include "build/baserom/ovl_Effect_Ss_Ice_Smoke.o"
endseg

beginseg
    name "ovl_Obj_Makekinsuta"
    compress
    include "build/baserom/ovl_Obj_Makekinsuta.o"
endseg

beginseg
    name "ovl_En_Ge3"
    compress
    include "build/baserom/ovl_En_Ge3.o"
endseg

beginseg
    name "ovl_Obj_Hamishi"
    compress
    include "build/baserom/ovl_Obj_Hamishi.o"
endseg

beginseg
    name "ovl_En_Zl4"
    compress
    include "build/baserom/ovl_En_Zl4.o"
endseg

beginseg
    name "ovl_En_Mm2"
    compress
    include "build/baserom/ovl_En_Mm2.o"
endseg

beginseg
    name "ovl_Door_Spiral"
    compress
    include "build/baserom/ovl_Door_Spiral.o"
endseg

beginseg
    name "ovl_Obj_Pzlblock"
    compress
    include "build/baserom/ovl_Obj_Pzlblock.o"
endseg

beginseg
    name "ovl_Obj_Toge"
    compress
    include "build/baserom/ovl_Obj_Toge.o"
endseg

beginseg
    name "ovl_Obj_Armos"
    compress
    include "build/baserom/ovl_Obj_Armos.o"
endseg

beginseg
    name "ovl_Obj_Boyo"
    compress
    include "build/baserom/ovl_Obj_Boyo.o"
endseg

beginseg
    name "ovl_En_Grasshopper"
    compress
    include "build/baserom/ovl_En_Grasshopper.o"
endseg

beginseg
    name "ovl_Obj_Grass"
    compress
    include "build/baserom/ovl_Obj_Grass.o"
endseg

beginseg
    name "ovl_Obj_Grass_Carry"
    compress
    include "build/baserom/ovl_Obj_Grass_Carry.o"
endseg

beginseg
    name "ovl_Obj_Grass_Unit"
    compress
    include "build/baserom/ovl_Obj_Grass_Unit.o"
endseg

beginseg
    name "ovl_Bg_Fire_Wall"
    compress
    include "build/baserom/ovl_Bg_Fire_Wall.o"
endseg

beginseg
    name "ovl_En_Bu"
    compress
    include "build/baserom/ovl_En_Bu.o"
endseg

beginseg
    name "ovl_En_Encount3"
    compress
    include "build/baserom/ovl_En_Encount3.o"
endseg

beginseg
    name "ovl_En_Jso"
    compress
    include "build/baserom/ovl_En_Jso.o"
endseg

beginseg
    name "ovl_Obj_Chikuwa"
    compress
    include "build/baserom/ovl_Obj_Chikuwa.o"
endseg

beginseg
    name "ovl_En_Knight"
    compress
    include "build/baserom/ovl_En_Knight.o"
endseg

beginseg
    name "ovl_En_Warp_tag"
    compress
    include "build/baserom/ovl_En_Warp_tag.o"
endseg

beginseg
    name "ovl_En_Aob_01"
    compress
    include "build/baserom/ovl_En_Aob_01.o"
endseg

beginseg
    name "ovl_En_Boj_01"
    compress
    include "build/baserom/ovl_En_Boj_01.o"
endseg

beginseg
    name "ovl_En_Boj_02"
    compress
    include "build/baserom/ovl_En_Boj_02.o"
endseg

beginseg
    name "ovl_En_Boj_03"
    compress
    include "build/baserom/ovl_En_Boj_03.o"
endseg

beginseg
    name "ovl_En_Encount4"
    compress
    include "build/baserom/ovl_En_Encount4.o"
endseg

beginseg
    name "ovl_En_Bom_Bowl_Man"
    compress
    include "build/baserom/ovl_En_Bom_Bowl_Man.o"
endseg

beginseg
    name "ovl_En_Syateki_Man"
    compress
    include "build/baserom/ovl_En_Syateki_Man.o"
endseg

beginseg
    name "ovl_Bg_Icicle"
    compress
    include "build/baserom/ovl_Bg_Icicle.o"
endseg

beginseg
    name "ovl_En_Syateki_Crow"
    compress
    include "build/baserom/ovl_En_Syateki_Crow.o"
endseg

beginseg
    name "ovl_En_Boj_04"
    compress
    include "build/baserom/ovl_En_Boj_04.o"
endseg

beginseg
    name "ovl_En_Cne_01"
    compress
    include "build/baserom/ovl_En_Cne_01.o"
endseg

beginseg
    name "ovl_En_Bba_01"
    compress
    include "build/baserom/ovl_En_Bba_01.o"
endseg

beginseg
    name "ovl_En_Bji_01"
    compress
    include "build/baserom/ovl_En_Bji_01.o"
endseg

beginseg
    name "ovl_Bg_Spdweb"
    compress
    include "build/baserom/ovl_Bg_Spdweb.o"
endseg

beginseg
    name "ovl_En_Mt_tag"
    compress
    include "build/baserom/ovl_En_Mt_tag.o"
endseg

beginseg
    name "ovl_Boss_01"
    compress
    include "build/baserom/ovl_Boss_01.o"
endseg

beginseg
    name "ovl_Boss_02"
    compress
    include "build/baserom/ovl_Boss_02.o"
endseg

beginseg
    name "ovl_Boss_03"
    compress
    include "build/baserom/ovl_Boss_03.o"
endseg

beginseg
    name "ovl_Boss_04"
    compress
    include "build/baserom/ovl_Boss_04.o"
endseg

beginseg
    name "ovl_Boss_05"
    compress
    include "build/baserom/ovl_Boss_05.o"
endseg

beginseg
    name "ovl_Boss_06"
    compress
    include "build/baserom/ovl_Boss_06.o"
endseg

beginseg
    name "ovl_Boss_07"
    compress
    include "build/baserom/ovl_Boss_07.o"
endseg

beginseg
    name "ovl_Bg_Dy_Yoseizo"
    compress
    include "build/baserom/ovl_Bg_Dy_Yoseizo.o"
endseg

beginseg
    name "ovl_En_Boj_05"
    compress
    include "build/baserom/ovl_En_Boj_05.o"
endseg

beginseg
    name "ovl_En_Sob1"
    compress
    include "build/baserom/ovl_En_Sob1.o"
endseg

beginseg
    name "ovl_En_Go"
    compress
    include "build/baserom/ovl_En_Go.o"
endseg

beginseg
    name "ovl_En_Raf"
    compress
    include "build/baserom/ovl_En_Raf.o"
endseg

beginseg
    name "ovl_Obj_Funen"
    compress
    include "build/baserom/ovl_Obj_Funen.o"
endseg

beginseg
    name "ovl_Obj_Raillift"
    compress
    include "build/baserom/ovl_Obj_Raillift.o"
endseg

beginseg
    name "ovl_Bg_Numa_Hana"
    compress
    include "build/baserom/ovl_Bg_Numa_Hana.o"
endseg

beginseg
    name "ovl_Obj_Flowerpot"
    compress
    include "build/baserom/ovl_Obj_Flowerpot.o"
endseg

beginseg
    name "ovl_Obj_Spinyroll"
    compress
    include "build/baserom/ovl_Obj_Spinyroll.o"
endseg

beginseg
    name "ovl_Dm_Hina"
    compress
    include "build/baserom/ovl_Dm_Hina.o"
endseg

beginseg
    name "ovl_En_Syateki_Wf"
    compress
    include "build/baserom/ovl_En_Syateki_Wf.o"
endseg

beginseg
    name "ovl_Obj_Skateblock"
    compress
    include "build/baserom/ovl_Obj_Skateblock.o"
endseg

beginseg
    name "ovl_Effect_En_Ice_Block"
    compress
    include "build/baserom/ovl_Effect_En_Ice_Block.o"
endseg

beginseg
    name "ovl_Obj_Iceblock"
    compress
    include "build/baserom/ovl_Obj_Iceblock.o"
endseg

beginseg
    name "ovl_En_Bigpamet"
    compress
    include "build/baserom/ovl_En_Bigpamet.o"
endseg

beginseg
    name "ovl_Bg_Dblue_Movebg"
    compress
    include "build/baserom/ovl_Bg_Dblue_Movebg.o"
endseg

beginseg
    name "ovl_En_Syateki_Dekunuts"
    compress
    include "build/baserom/ovl_En_Syateki_Dekunuts.o"
endseg

beginseg
    name "ovl_Elf_Msg3"
    compress
    include "build/baserom/ovl_Elf_Msg3.o"
endseg

beginseg
    name "ovl_En_Fg"
    compress
    include "build/baserom/ovl_En_Fg.o"
endseg

beginseg
    name "ovl_Dm_Ravine"
    compress
    include "build/baserom/ovl_Dm_Ravine.o"
endseg

beginseg
    name "ovl_Dm_Sa"
    compress
    include "build/baserom/ovl_Dm_Sa.o"
endseg

beginseg
    name "ovl_En_Slime"
    compress
    include "build/baserom/ovl_En_Slime.o"
endseg

beginseg
    name "ovl_En_Pr"
    compress
    include "build/baserom/ovl_En_Pr.o"
endseg

beginseg
    name "ovl_Obj_Toudai"
    compress
    include "build/baserom/ovl_Obj_Toudai.o"
endseg

beginseg
    name "ovl_Obj_Entotu"
    compress
    include "build/baserom/ovl_Obj_Entotu.o"
endseg

beginseg
    name "ovl_Obj_Bell"
    compress
    include "build/baserom/ovl_Obj_Bell.o"
endseg

beginseg
    name "ovl_En_Syateki_Okuta"
    compress
    include "build/baserom/ovl_En_Syateki_Okuta.o"
endseg

beginseg
    name "ovl_Obj_Shutter"
    compress
    include "build/baserom/ovl_Obj_Shutter.o"
endseg

beginseg
    name "ovl_Dm_Zl"
    compress
    include "build/baserom/ovl_Dm_Zl.o"
endseg

beginseg
    name "ovl_En_Ru"
    compress
    include "build/baserom/ovl_En_Ru.o"
endseg

beginseg
    name "ovl_En_Elfgrp"
    compress
    include "build/baserom/ovl_En_Elfgrp.o"
endseg

beginseg
    name "ovl_Dm_Tsg"
    compress
    include "build/baserom/ovl_Dm_Tsg.o"
endseg

beginseg
    name "ovl_En_Baguo"
    compress
    include "build/baserom/ovl_En_Baguo.o"
endseg

beginseg
    name "ovl_Obj_Vspinyroll"
    compress
    include "build/baserom/ovl_Obj_Vspinyroll.o"
endseg

beginseg
    name "ovl_Obj_Smork"
    compress
    include "build/baserom/ovl_Obj_Smork.o"
endseg

beginseg
    name "ovl_En_Test2"
    compress
    include "build/baserom/ovl_En_Test2.o"
endseg

beginseg
    name "ovl_En_Test3"
    compress
    include "build/baserom/ovl_En_Test3.o"
endseg

beginseg
    name "ovl_En_Test4"
    compress
    include "build/baserom/ovl_En_Test4.o"
endseg

beginseg
    name "ovl_En_Bat"
    compress
    include "build/baserom/ovl_En_Bat.o"
endseg

beginseg
    name "ovl_En_Sekihi"
    compress
    include "build/baserom/ovl_En_Sekihi.o"
endseg

beginseg
    name "ovl_En_Wiz"
    compress
    include "build/baserom/ovl_En_Wiz.o"
endseg

beginseg
    name "ovl_En_Wiz_Brock"
    compress
    include "build/baserom/ovl_En_Wiz_Brock.o"
endseg

beginseg
    name "ovl_En_Wiz_Fire"
    compress
    include "build/baserom/ovl_En_Wiz_Fire.o"
endseg

beginseg
    name "ovl_Eff_Change"
    compress
    include "build/baserom/ovl_Eff_Change.o"
endseg

beginseg
    name "ovl_Dm_Statue"
    compress
    include "build/baserom/ovl_Dm_Statue.o"
endseg

beginseg
    name "ovl_Obj_Fireshield"
    compress
    include "build/baserom/ovl_Obj_Fireshield.o"
endseg

beginseg
    name "ovl_Bg_Ladder"
    compress
    include "build/baserom/ovl_Bg_Ladder.o"
endseg

beginseg
    name "ovl_En_Mkk"
    compress
    include "build/baserom/ovl_En_Mkk.o"
endseg

beginseg
    name "ovl_Demo_Getitem"
    compress
    include "build/baserom/ovl_Demo_Getitem.o"
endseg

beginseg
    name "ovl_En_Dnb"
    compress
    include "build/baserom/ovl_En_Dnb.o"
endseg

beginseg
    name "ovl_En_Dnh"
    compress
    include "build/baserom/ovl_En_Dnh.o"
endseg

beginseg
    name "ovl_En_Dnk"
    compress
    include "build/baserom/ovl_En_Dnk.o"
endseg

beginseg
    name "ovl_En_Dnq"
    compress
    include "build/baserom/ovl_En_Dnq.o"
endseg

beginseg
    name "ovl_Bg_Keikoku_Saku"
    compress
    include "build/baserom/ovl_Bg_Keikoku_Saku.o"
endseg

beginseg
    name "ovl_Obj_Hugebombiwa"
    compress
    include "build/baserom/ovl_Obj_Hugebombiwa.o"
endseg

beginseg
    name "ovl_En_Firefly2"
    compress
    include "build/baserom/ovl_En_Firefly2.o"
endseg

beginseg
    name "ovl_En_Rat"
    compress
    include "build/baserom/ovl_En_Rat.o"
endseg

beginseg
    name "ovl_En_Water_Effect"
    compress
    include "build/baserom/ovl_En_Water_Effect.o"
endseg

beginseg
    name "ovl_En_Kusa2"
    compress
    include "build/baserom/ovl_En_Kusa2.o"
endseg

beginseg
    name "ovl_Bg_Spout_Fire"
    compress
    include "build/baserom/ovl_Bg_Spout_Fire.o"
endseg

beginseg
    name "ovl_En_Dy_Extra"
    compress
    include "build/baserom/ovl_En_Dy_Extra.o"
endseg

beginseg
    name "ovl_En_Bal"
    compress
    include "build/baserom/ovl_En_Bal.o"
endseg

beginseg
    name "ovl_En_Ginko_Man"
    compress
    include "build/baserom/ovl_En_Ginko_Man.o"
endseg

beginseg
    name "ovl_En_Warp_Uzu"
    compress
    include "build/baserom/ovl_En_Warp_Uzu.o"
endseg

beginseg
    name "ovl_Obj_Driftice"
    compress
    include "build/baserom/ovl_Obj_Driftice.o"
endseg

beginseg
    name "ovl_En_Look_Nuts"
    compress
    include "build/baserom/ovl_En_Look_Nuts.o"
endseg

beginseg
    name "ovl_En_Mushi2"
    compress
    include "build/baserom/ovl_En_Mushi2.o"
endseg

beginseg
    name "ovl_En_Fall"
    compress
    include "build/baserom/ovl_En_Fall.o"
endseg

beginseg
    name "ovl_En_Mm3"
    compress
    include "build/baserom/ovl_En_Mm3.o"
endseg

beginseg
    name "ovl_Bg_Crace_Movebg"
    compress
    include "build/baserom/ovl_Bg_Crace_Movebg.o"
endseg

beginseg
    name "ovl_En_Dno"
    compress
    include "build/baserom/ovl_En_Dno.o"
endseg

beginseg
    name "ovl_En_Pr2"
    compress
    include "build/baserom/ovl_En_Pr2.o"
endseg

beginseg
    name "ovl_En_Prz"
    compress
    include "build/baserom/ovl_En_Prz.o"
endseg

beginseg
    name "ovl_En_Jso2"
    compress
    include "build/baserom/ovl_En_Jso2.o"
endseg

beginseg
    name "ovl_Obj_Etcetera"
    compress
    include "build/baserom/ovl_Obj_Etcetera.o"
endseg

beginseg
    name "ovl_En_Egol"
    compress
    include "build/baserom/ovl_En_Egol.o"
endseg

beginseg
    name "ovl_Obj_Mine"
    compress
    include "build/baserom/ovl_Obj_Mine.o"
endseg

beginseg
    name "ovl_Obj_Purify"
    compress
    include "build/baserom/ovl_Obj_Purify.o"
endseg

beginseg
    name "ovl_En_Tru"
    compress
    include "build/baserom/ovl_En_Tru.o"
endseg

beginseg
    name "ovl_En_Trt"
    compress
    include "build/baserom/ovl_En_Trt.o"
endseg

beginseg
    name "ovl_En_Test5"
    compress
    include "build/baserom/ovl_En_Test5.o"
endseg

beginseg
    name "ovl_En_Test6"
    compress
    include "build/baserom/ovl_En_Test6.o"
endseg

beginseg
    name "ovl_En_Az"
    compress
    include "build/baserom/ovl_En_Az.o"
endseg

beginseg
    name "ovl_En_Estone"
    compress
    include "build/baserom/ovl_En_Estone.o"
endseg

beginseg
    name "ovl_Bg_Hakugin_Post"
    compress
    include "build/baserom/ovl_Bg_Hakugin_Post.o"
endseg

beginseg
    name "ovl_Dm_Opstage"
    compress
    include "build/baserom/ovl_Dm_Opstage.o"
endseg

beginseg
    name "ovl_Dm_Stk"
    compress
    include "build/baserom/ovl_Dm_Stk.o"
endseg

beginseg
    name "ovl_Dm_Char00"
    compress
    include "build/baserom/ovl_Dm_Char00.o"
endseg

beginseg
    name "ovl_Dm_Char01"
    compress
    include "build/baserom/ovl_Dm_Char01.o"
endseg

beginseg
    name "ovl_Dm_Char02"
    compress
    include "build/baserom/ovl_Dm_Char02.o"
endseg

beginseg
    name "ovl_Dm_Char03"
    compress
    include "build/baserom/ovl_Dm_Char03.o"
endseg

beginseg
    name "ovl_Dm_Char04"
    compress
    include "build/baserom/ovl_Dm_Char04.o"
endseg

beginseg
    name "ovl_Dm_Char05"
    compress
    include "build/baserom/ovl_Dm_Char05.o"
endseg

beginseg
    name "ovl_Dm_Char06"
    compress
    include "build/baserom/ovl_Dm_Char06.o"
endseg

beginseg
    name "ovl_Dm_Char07"
    compress
    include "build/baserom/ovl_Dm_Char07.o"
endseg

beginseg
    name "ovl_Dm_Char08"
    compress
    include "build/baserom/ovl_Dm_Char08.o"
endseg

beginseg
    name "ovl_Dm_Char09"
    compress
    include "build/baserom/ovl_Dm_Char09.o"
endseg

beginseg
    name "ovl_Obj_Tokeidai"
    compress
    include "build/baserom/ovl_Obj_Tokeidai.o"
endseg

beginseg
    name "ovl_En_Mnk"
    compress
    include "build/baserom/ovl_En_Mnk.o"
endseg

beginseg
    name "ovl_En_Egblock"
    compress
    include "build/baserom/ovl_En_Egblock.o"
endseg

beginseg
    name "ovl_En_Guard_Nuts"
    compress
    include "build/baserom/ovl_En_Guard_Nuts.o"
endseg

beginseg
    name "ovl_Bg_Hakugin_Bombwall"
    compress
    include "build/baserom/ovl_Bg_Hakugin_Bombwall.o"
endseg

beginseg
    name "ovl_Obj_Tokei_Tobira"
    compress
    include "build/baserom/ovl_Obj_Tokei_Tobira.o"
endseg

beginseg
    name "ovl_Bg_Hakugin_Elvpole"
    compress
    include "build/baserom/ovl_Bg_Hakugin_Elvpole.o"
endseg

beginseg
    name "ovl_En_Ma4"
    compress
    include "build/baserom/ovl_En_Ma4.o"
endseg

beginseg
    name "ovl_En_Twig"
    compress
    include "build/baserom/ovl_En_Twig.o"
endseg

beginseg
    name "ovl_En_Po_Fusen"
    compress
    include "build/baserom/ovl_En_Po_Fusen.o"
endseg

beginseg
    name "ovl_En_Door_Etc"
    compress
    include "build/baserom/ovl_En_Door_Etc.o"
endseg

beginseg
    name "ovl_En_Bigokuta"
    compress
    include "build/baserom/ovl_En_Bigokuta.o"
endseg

beginseg
    name "ovl_Bg_Icefloe"
    compress
    include "build/baserom/ovl_Bg_Icefloe.o"
endseg

beginseg
    name "ovl_fbdemo_triforce"
    compress
    include "build/baserom/ovl_fbdemo_triforce.o"
endseg

beginseg
    name "ovl_fbdemo_wipe1"
    compress
    include "build/baserom/ovl_fbdemo_wipe1.o"
endseg

beginseg
    name "ovl_fbdemo_wipe3"
    compress
    include "build/baserom/ovl_fbdemo_wipe3.o"
endseg

beginseg
    name "ovl_fbdemo_wipe4"
    compress
    include "build/baserom/ovl_fbdemo_wipe4.o"
endseg

beginseg
    name "ovl_fbdemo_wipe5"
    compress
    include "build/baserom/ovl_fbdemo_wipe5.o"
endseg

beginseg
    name "ovl_Effect_Ss_Sbn"
    compress
    include "build/baserom/ovl_Effect_Ss_Sbn.o"
endseg

beginseg
    name "ovl_Obj_Ocarinalift"
    compress
    include "build/baserom/ovl_Obj_Ocarinalift.o"
endseg

beginseg
    name "ovl_En_Time_Tag"
    compress
    include "build/baserom/ovl_En_Time_Tag.o"
endseg

beginseg
    name "ovl_Bg_Open_Shutter"
    compress
    include "build/baserom/ovl_Bg_Open_Shutter.o"
endseg

beginseg
    name "ovl_Bg_Open_Spot"
    compress
    include "build/baserom/ovl_Bg_Open_Spot.o"
endseg

beginseg
    name "ovl_Bg_Fu_Kaiten"
    compress
    include "build/baserom/ovl_Bg_Fu_Kaiten.o"
endseg

beginseg
    name "ovl_Obj_Aqua"
    compress
    include "build/baserom/ovl_Obj_Aqua.o"
endseg

beginseg
    name "ovl_En_Elforg"
    compress
    include "build/baserom/ovl_En_Elforg.o"
endseg

beginseg
    name "ovl_En_Elfbub"
    compress
    include "build/baserom/ovl_En_Elfbub.o"
endseg

beginseg
    name "ovl_En_Fu_Mato"
    compress
    include "build/baserom/ovl_En_Fu_Mato.o"
endseg

beginseg
    name "ovl_En_Fu_Kago"
    compress
    include "build/baserom/ovl_En_Fu_Kago.o"
endseg

beginseg
    name "ovl_En_Osn"
    compress
    include "build/baserom/ovl_En_Osn.o"
endseg

beginseg
    name "ovl_Bg_Ctower_Gear"
    compress
    include "build/baserom/ovl_Bg_Ctower_Gear.o"
endseg

beginseg
    name "ovl_En_Trt2"
    compress
    include "build/baserom/ovl_En_Trt2.o"
endseg

beginseg
    name "ovl_Obj_Tokei_Step"
    compress
    include "build/baserom/ovl_Obj_Tokei_Step.o"
endseg

beginseg
    name "ovl_Bg_Lotus"
    compress
    include "build/baserom/ovl_Bg_Lotus.o"
endseg

beginseg
    name "ovl_En_Kame"
    compress
    include "build/baserom/ovl_En_Kame.o"
endseg

beginseg
    name "ovl_Obj_Takaraya_Wall"
    compress
    include "build/baserom/ovl_Obj_Takaraya_Wall.o"
endseg

beginseg
    name "ovl_Bg_Fu_Mizu"
    compress
    include "build/baserom/ovl_Bg_Fu_Mizu.o"
endseg

beginseg
    name "ovl_En_Sellnuts"
    compress
    include "build/baserom/ovl_En_Sellnuts.o"
endseg

beginseg
    name "ovl_Bg_Dkjail_Ivy"
    compress
    include "build/baserom/ovl_Bg_Dkjail_Ivy.o"
endseg

beginseg
    name "ovl_Obj_Visiblock"
    compress
    include "build/baserom/ovl_Obj_Visiblock.o"
endseg

beginseg
    name "ovl_En_Takaraya"
    compress
    include "build/baserom/ovl_En_Takaraya.o"
endseg

beginseg
    name "ovl_En_Tsn"
    compress
    include "build/baserom/ovl_En_Tsn.o"
endseg

beginseg
    name "ovl_En_Ds2n"
    compress
    include "build/baserom/ovl_En_Ds2n.o"
endseg

beginseg
    name "ovl_En_Fsn"
    compress
    include "build/baserom/ovl_En_Fsn.o"
endseg

beginseg
    name "ovl_En_Shn"
    compress
    include "build/baserom/ovl_En_Shn.o"
endseg

beginseg
    name "ovl_En_Stop_heishi"
    compress
    include "build/baserom/ovl_En_Stop_heishi.o"
endseg

beginseg
    name "ovl_Obj_Bigicicle"
    compress
    include "build/baserom/ovl_Obj_Bigicicle.o"
endseg

beginseg
    name "ovl_En_Lift_Nuts"
    compress
    include "build/baserom/ovl_En_Lift_Nuts.o"
endseg

beginseg
    name "ovl_En_Tk"
    compress
    include "build/baserom/ovl_En_Tk.o"
endseg

beginseg
    name "ovl_Bg_Market_Step"
    compress
    include "build/baserom/ovl_Bg_Market_Step.o"
endseg

beginseg
    name "ovl_Obj_Lupygamelift"
    compress
    include "build/baserom/ovl_Obj_Lupygamelift.o"
endseg

beginseg
    name "ovl_En_Test7"
    compress
    include "build/baserom/ovl_En_Test7.o"
endseg

beginseg
    name "ovl_Obj_Lightblock"
    compress
    include "build/baserom/ovl_Obj_Lightblock.o"
endseg

beginseg
    name "ovl_Mir_Ray2"
    compress
    include "build/baserom/ovl_Mir_Ray2.o"
endseg

beginseg
    name "ovl_En_Wdhand"
    compress
    include "build/baserom/ovl_En_Wdhand.o"
endseg

beginseg
    name "ovl_En_Gamelupy"
    compress
    include "build/baserom/ovl_En_Gamelupy.o"
endseg

beginseg
    name "ovl_Bg_Danpei_Movebg"
    compress
    include "build/baserom/ovl_Bg_Danpei_Movebg.o"
endseg

beginseg
    name "ovl_En_Snowwd"
    compress
    include "build/baserom/ovl_En_Snowwd.o"
endseg

beginseg
    name "ovl_En_Pm"
    compress
    include "build/baserom/ovl_En_Pm.o"
endseg

beginseg
    name "ovl_En_Gakufu"
    compress
    include "build/baserom/ovl_En_Gakufu.o"
endseg

beginseg
    name "ovl_Elf_Msg4"
    compress
    include "build/baserom/ovl_Elf_Msg4.o"
endseg

beginseg
    name "ovl_Elf_Msg5"
    compress
    include "build/baserom/ovl_Elf_Msg5.o"
endseg

beginseg
    name "ovl_En_Col_Man"
    compress
    include "build/baserom/ovl_En_Col_Man.o"
endseg

beginseg
    name "ovl_En_Talk_Gibud"
    compress
    include "build/baserom/ovl_En_Talk_Gibud.o"
endseg

beginseg
    name "ovl_En_Giant"
    compress
    include "build/baserom/ovl_En_Giant.o"
endseg

beginseg
    name "ovl_Obj_Snowball"
    compress
    include "build/baserom/ovl_Obj_Snowball.o"
endseg

beginseg
    name "ovl_Boss_Hakugin"
    compress
    include "build/baserom/ovl_Boss_Hakugin.o"
endseg

beginseg
    name "ovl_En_Gb2"
    compress
    include "build/baserom/ovl_En_Gb2.o"
endseg

beginseg
    name "ovl_En_Onpuman"
    compress
    include "build/baserom/ovl_En_Onpuman.o"
endseg

beginseg
    name "ovl_Bg_Tobira01"
    compress
    include "build/baserom/ovl_Bg_Tobira01.o"
endseg

beginseg
    name "ovl_En_Tag_Obj"
    compress
    include "build/baserom/ovl_En_Tag_Obj.o"
endseg

beginseg
    name "ovl_Obj_Dhouse"
    compress
    include "build/baserom/ovl_Obj_Dhouse.o"
endseg

beginseg
    name "ovl_Obj_Hakaisi"
    compress
    include "build/baserom/ovl_Obj_Hakaisi.o"
endseg

beginseg
    name "ovl_Bg_Hakugin_Switch"
    compress
    include "build/baserom/ovl_Bg_Hakugin_Switch.o"
endseg

beginseg
    name "ovl_En_Snowman"
    compress
    include "build/baserom/ovl_En_Snowman.o"
endseg

beginseg
    name "ovl_TG_Sw"
    compress
    include "build/baserom/ovl_TG_Sw.o"
endseg

beginseg
    name "ovl_En_Po_Sisters"
    compress
    include "build/baserom/ovl_En_Po_Sisters.o"
endseg

beginseg
    name "ovl_En_Pp"
    compress
    include "build/baserom/ovl_En_Pp.o"
endseg

beginseg
    name "ovl_En_Hakurock"
    compress
    include "build/baserom/ovl_En_Hakurock.o"
endseg

beginseg
    name "ovl_En_Hanabi"
    compress
    include "build/baserom/ovl_En_Hanabi.o"
endseg

beginseg
    name "ovl_Obj_Dowsing"
    compress
    include "build/baserom/ovl_Obj_Dowsing.o"
endseg

beginseg
    name "ovl_Obj_Wind"
    compress
    include "build/baserom/ovl_Obj_Wind.o"
endseg

beginseg
    name "ovl_En_Racedog"
    compress
    include "build/baserom/ovl_En_Racedog.o"
endseg

beginseg
    name "ovl_En_Kendo_Js"
    compress
    include "build/baserom/ovl_En_Kendo_Js.o"
endseg

beginseg
    name "ovl_Bg_Botihasira"
    compress
    include "build/baserom/ovl_Bg_Botihasira.o"
endseg

beginseg
    name "ovl_En_Fish2"
    compress
    include "build/baserom/ovl_En_Fish2.o"
endseg

beginseg
    name "ovl_En_Pst"
    compress
    include "build/baserom/ovl_En_Pst.o"
endseg

beginseg
    name "ovl_En_Poh"
    compress
    include "build/baserom/ovl_En_Poh.o"
endseg

beginseg
    name "ovl_Obj_Spidertent"
    compress
    include "build/baserom/ovl_Obj_Spidertent.o"
endseg

beginseg
    name "ovl_En_Zoraegg"
    compress
    include "build/baserom/ovl_En_Zoraegg.o"
endseg

beginseg
    name "ovl_En_Kbt"
    compress
    include "build/baserom/ovl_En_Kbt.o"
endseg

beginseg
    name "ovl_En_Gg"
    compress
    include "build/baserom/ovl_En_Gg.o"
endseg

beginseg
    name "ovl_En_Maruta"
    compress
    include "build/baserom/ovl_En_Maruta.o"
endseg

beginseg
    name "ovl_Obj_Snowball2"
    compress
    include "build/baserom/ovl_Obj_Snowball2.o"
endseg

beginseg
    name "ovl_En_Gg2"
    compress
    include "build/baserom/ovl_En_Gg2.o"
endseg

beginseg
    name "ovl_Obj_Ghaka"
    compress
    include "build/baserom/ovl_Obj_Ghaka.o"
endseg

beginseg
    name "ovl_En_Dnp"
    compress
    include "build/baserom/ovl_En_Dnp.o"
endseg

beginseg
    name "ovl_En_Dai"
    compress
    include "build/baserom/ovl_En_Dai.o"
endseg

beginseg
    name "ovl_Bg_Goron_Oyu"
    compress
    include "build/baserom/ovl_Bg_Goron_Oyu.o"
endseg

beginseg
    name "ovl_En_Kgy"
    compress
    include "build/baserom/ovl_En_Kgy.o"
endseg

beginseg
    name "ovl_En_Invadepoh"
    compress
    include "build/baserom/ovl_En_Invadepoh.o"
endseg

beginseg
    name "ovl_En_Gk"
    compress
    include "build/baserom/ovl_En_Gk.o"
endseg

beginseg
    name "ovl_En_An"
    compress
    include "build/baserom/ovl_En_An.o"
endseg

beginseg
    name "ovl_En_Bee"
    compress
    include "build/baserom/ovl_En_Bee.o"
endseg

beginseg
    name "ovl_En_Ot"
    compress
    include "build/baserom/ovl_En_Ot.o"
endseg

beginseg
    name "ovl_En_Dragon"
    compress
    include "build/baserom/ovl_En_Dragon.o"
endseg

beginseg
    name "ovl_Obj_Dora"
    compress
    include "build/baserom/ovl_Obj_Dora.o"
endseg

beginseg
    name "ovl_En_Bigpo"
    compress
    include "build/baserom/ovl_En_Bigpo.o"
endseg

beginseg
    name "ovl_Obj_Kendo_Kanban"
    compress
    include "build/baserom/ovl_Obj_Kendo_Kanban.o"
endseg

beginseg
    name "ovl_Obj_Hariko"
    compress
    include "build/baserom/ovl_Obj_Hariko.o"
endseg

beginseg
    name "ovl_En_Sth"
    compress
    include "build/baserom/ovl_En_Sth.o"
endseg

beginseg
    name "ovl_Bg_Sinkai_Kabe"
    compress
    include "build/baserom/ovl_Bg_Sinkai_Kabe.o"
endseg

beginseg
    name "ovl_Bg_Haka_Curtain"
    compress
    include "build/baserom/ovl_Bg_Haka_Curtain.o"
endseg

beginseg
    name "ovl_Bg_Kin2_Bombwall"
    compress
    include "build/baserom/ovl_Bg_Kin2_Bombwall.o"
endseg

beginseg
    name "ovl_Bg_Kin2_Fence"
    compress
    include "build/baserom/ovl_Bg_Kin2_Fence.o"
endseg

beginseg
    name "ovl_Bg_Kin2_Picture"
    compress
    include "build/baserom/ovl_Bg_Kin2_Picture.o"
endseg

beginseg
    name "ovl_Bg_Kin2_Shelf"
    compress
    include "build/baserom/ovl_Bg_Kin2_Shelf.o"
endseg

beginseg
    name "ovl_En_Rail_Skb"
    compress
    include "build/baserom/ovl_En_Rail_Skb.o"
endseg

beginseg
    name "ovl_En_Jg"
    compress
    include "build/baserom/ovl_En_Jg.o"
endseg

beginseg
    name "ovl_En_Tru_Mt"
    compress
    include "build/baserom/ovl_En_Tru_Mt.o"
endseg

beginseg
    name "ovl_Obj_Um"
    compress
    include "build/baserom/ovl_Obj_Um.o"
endseg

beginseg
    name "ovl_En_Neo_Reeba"
    compress
    include "build/baserom/ovl_En_Neo_Reeba.o"
endseg

beginseg
    name "ovl_Bg_Mbar_Chair"
    compress
    include "build/baserom/ovl_Bg_Mbar_Chair.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Block"
    compress
    include "build/baserom/ovl_Bg_Ikana_Block.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Mirror"
    compress
    include "build/baserom/ovl_Bg_Ikana_Mirror.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Rotaryroom"
    compress
    include "build/baserom/ovl_Bg_Ikana_Rotaryroom.o"
endseg

beginseg
    name "ovl_Bg_Dblue_Balance"
    compress
    include "build/baserom/ovl_Bg_Dblue_Balance.o"
endseg

beginseg
    name "ovl_Bg_Dblue_Waterfall"
    compress
    include "build/baserom/ovl_Bg_Dblue_Waterfall.o"
endseg

beginseg
    name "ovl_En_Kaizoku"
    compress
    include "build/baserom/ovl_En_Kaizoku.o"
endseg

beginseg
    name "ovl_En_Ge2"
    compress
    include "build/baserom/ovl_En_Ge2.o"
endseg

beginseg
    name "ovl_En_Ma_Yts"
    compress
    include "build/baserom/ovl_En_Ma_Yts.o"
endseg

beginseg
    name "ovl_En_Ma_Yto"
    compress
    include "build/baserom/ovl_En_Ma_Yto.o"
endseg

beginseg
    name "ovl_Obj_Tokei_Turret"
    compress
    include "build/baserom/ovl_Obj_Tokei_Turret.o"
endseg

beginseg
    name "ovl_Bg_Dblue_Elevator"
    compress
    include "build/baserom/ovl_Bg_Dblue_Elevator.o"
endseg

beginseg
    name "ovl_Obj_Warpstone"
    compress
    include "build/baserom/ovl_Obj_Warpstone.o"
endseg

beginseg
    name "ovl_En_Zog"
    compress
    include "build/baserom/ovl_En_Zog.o"
endseg

beginseg
    name "ovl_Obj_Rotlift"
    compress
    include "build/baserom/ovl_Obj_Rotlift.o"
endseg

beginseg
    name "ovl_Obj_Jg_Gakki"
    compress
    include "build/baserom/ovl_Obj_Jg_Gakki.o"
endseg

beginseg
    name "ovl_Bg_Inibs_Movebg"
    compress
    include "build/baserom/ovl_Bg_Inibs_Movebg.o"
endseg

beginseg
    name "ovl_En_Zot"
    compress
    include "build/baserom/ovl_En_Zot.o"
endseg

beginseg
    name "ovl_Obj_Tree"
    compress
    include "build/baserom/ovl_Obj_Tree.o"
endseg

beginseg
    name "ovl_Obj_Y2lift"
    compress
    include "build/baserom/ovl_Obj_Y2lift.o"
endseg

beginseg
    name "ovl_Obj_Y2shutter"
    compress
    include "build/baserom/ovl_Obj_Y2shutter.o"
endseg

beginseg
    name "ovl_Obj_Boat"
    compress
    include "build/baserom/ovl_Obj_Boat.o"
endseg

beginseg
    name "ovl_Obj_Taru"
    compress
    include "build/baserom/ovl_Obj_Taru.o"
endseg

beginseg
    name "ovl_Obj_Hunsui"
    compress
    include "build/baserom/ovl_Obj_Hunsui.o"
endseg

beginseg
    name "ovl_En_Jc_Mato"
    compress
    include "build/baserom/ovl_En_Jc_Mato.o"
endseg

beginseg
    name "ovl_Mir_Ray3"
    compress
    include "build/baserom/ovl_Mir_Ray3.o"
endseg

beginseg
    name "ovl_En_Zob"
    compress
    include "build/baserom/ovl_En_Zob.o"
endseg

beginseg
    name "ovl_Elf_Msg6"
    compress
    include "build/baserom/ovl_Elf_Msg6.o"
endseg

beginseg
    name "ovl_Obj_Nozoki"
    compress
    include "build/baserom/ovl_Obj_Nozoki.o"
endseg

beginseg
    name "ovl_En_Toto"
    compress
    include "build/baserom/ovl_En_Toto.o"
endseg

beginseg
    name "ovl_En_Railgibud"
    compress
    include "build/baserom/ovl_En_Railgibud.o"
endseg

beginseg
    name "ovl_En_Baba"
    compress
    include "build/baserom/ovl_En_Baba.o"
endseg

beginseg
    name "ovl_En_Suttari"
    compress
    include "build/baserom/ovl_En_Suttari.o"
endseg

beginseg
    name "ovl_En_Zod"
    compress
    include "build/baserom/ovl_En_Zod.o"
endseg

beginseg
    name "ovl_En_Kujiya"
    compress
    include "build/baserom/ovl_En_Kujiya.o"
endseg

beginseg
    name "ovl_En_Geg"
    compress
    include "build/baserom/ovl_En_Geg.o"
endseg

beginseg
    name "ovl_Obj_Kinoko"
    compress
    include "build/baserom/ovl_Obj_Kinoko.o"
endseg

beginseg
    name "ovl_Obj_Yasi"
    compress
    include "build/baserom/ovl_Obj_Yasi.o"
endseg

beginseg
    name "ovl_En_Tanron1"
    compress
    include "build/baserom/ovl_En_Tanron1.o"
endseg

beginseg
    name "ovl_En_Tanron2"
    compress
    include "build/baserom/ovl_En_Tanron2.o"
endseg

beginseg
    name "ovl_En_Tanron3"
    compress
    include "build/baserom/ovl_En_Tanron3.o"
endseg

beginseg
    name "ovl_Obj_Chan"
    compress
    include "build/baserom/ovl_Obj_Chan.o"
endseg

beginseg
    name "ovl_En_Zos"
    compress
    include "build/baserom/ovl_En_Zos.o"
endseg

beginseg
    name "ovl_En_S_Goro"
    compress
    include "build/baserom/ovl_En_S_Goro.o"
endseg

beginseg
    name "ovl_En_Nb"
    compress
    include "build/baserom/ovl_En_Nb.o"
endseg

beginseg
    name "ovl_En_Ja"
    compress
    include "build/baserom/ovl_En_Ja.o"
endseg

beginseg
    name "ovl_Bg_F40_Block"
    compress
    include "build/baserom/ovl_Bg_F40_Block.o"
endseg

beginseg
    name "ovl_Bg_F40_Switch"
    compress
    include "build/baserom/ovl_Bg_F40_Switch.o"
endseg

beginseg
    name "ovl_En_Po_Composer"
    compress
    include "build/baserom/ovl_En_Po_Composer.o"
endseg

beginseg
    name "ovl_En_Guruguru"
    compress
    include "build/baserom/ovl_En_Guruguru.o"
endseg

beginseg
    name "ovl_Oceff_Wipe5"
    compress
    include "build/baserom/ovl_Oceff_Wipe5.o"
endseg

beginseg
    name "ovl_En_Stone_heishi"
    compress
    include "build/baserom/ovl_En_Stone_heishi.o"
endseg

beginseg
    name "ovl_Oceff_Wipe6"
    compress
    include "build/baserom/ovl_Oceff_Wipe6.o"
endseg

beginseg
    name "ovl_En_Scopenuts"
    compress
    include "build/baserom/ovl_En_Scopenuts.o"
endseg

beginseg
    name "ovl_En_Scopecrow"
    compress
    include "build/baserom/ovl_En_Scopecrow.o"
endseg

beginseg
    name "ovl_Oceff_Wipe7"
    compress
    include "build/baserom/ovl_Oceff_Wipe7.o"
endseg

beginseg
    name "ovl_Eff_Kamejima_Wave"
    compress
    include "build/baserom/ovl_Eff_Kamejima_Wave.o"
endseg

beginseg
    name "ovl_En_Hg"
    compress
    include "build/baserom/ovl_En_Hg.o"
endseg

beginseg
    name "ovl_En_Hgo"
    compress
    include "build/baserom/ovl_En_Hgo.o"
endseg

beginseg
    name "ovl_En_Zov"
    compress
    include "build/baserom/ovl_En_Zov.o"
endseg

beginseg
    name "ovl_En_Ah"
    compress
    include "build/baserom/ovl_En_Ah.o"
endseg

beginseg
    name "ovl_Obj_Hgdoor"
    compress
    include "build/baserom/ovl_Obj_Hgdoor.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Bombwall"
    compress
    include "build/baserom/ovl_Bg_Ikana_Bombwall.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Ray"
    compress
    include "build/baserom/ovl_Bg_Ikana_Ray.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Shutter"
    compress
    include "build/baserom/ovl_Bg_Ikana_Shutter.o"
endseg

beginseg
    name "ovl_Bg_Haka_Bombwall"
    compress
    include "build/baserom/ovl_Bg_Haka_Bombwall.o"
endseg

beginseg
    name "ovl_Bg_Haka_Tomb"
    compress
    include "build/baserom/ovl_Bg_Haka_Tomb.o"
endseg

beginseg
    name "ovl_En_Sc_Ruppe"
    compress
    include "build/baserom/ovl_En_Sc_Ruppe.o"
endseg

beginseg
    name "ovl_Bg_Iknv_Doukutu"
    compress
    include "build/baserom/ovl_Bg_Iknv_Doukutu.o"
endseg

beginseg
    name "ovl_Bg_Iknv_Obj"
    compress
    include "build/baserom/ovl_Bg_Iknv_Obj.o"
endseg

beginseg
    name "ovl_En_Pamera"
    compress
    include "build/baserom/ovl_En_Pamera.o"
endseg

beginseg
    name "ovl_Obj_HsStump"
    compress
    include "build/baserom/ovl_Obj_HsStump.o"
endseg

beginseg
    name "ovl_En_Hidden_Nuts"
    compress
    include "build/baserom/ovl_En_Hidden_Nuts.o"
endseg

beginseg
    name "ovl_En_Zow"
    compress
    include "build/baserom/ovl_En_Zow.o"
endseg

beginseg
    name "ovl_En_Talk"
    compress
    include "build/baserom/ovl_En_Talk.o"
endseg

beginseg
    name "ovl_En_Al"
    compress
    include "build/baserom/ovl_En_Al.o"
endseg

beginseg
    name "ovl_En_Tab"
    compress
    include "build/baserom/ovl_En_Tab.o"
endseg

beginseg
    name "ovl_En_Nimotsu"
    compress
    include "build/baserom/ovl_En_Nimotsu.o"
endseg

beginseg
    name "ovl_En_Hit_Tag"
    compress
    include "build/baserom/ovl_En_Hit_Tag.o"
endseg

beginseg
    name "ovl_En_Ruppecrow"
    compress
    include "build/baserom/ovl_En_Ruppecrow.o"
endseg

beginseg
    name "ovl_En_Tanron4"
    compress
    include "build/baserom/ovl_En_Tanron4.o"
endseg

beginseg
    name "ovl_En_Tanron5"
    compress
    include "build/baserom/ovl_En_Tanron5.o"
endseg

beginseg
    name "ovl_En_Tanron6"
    compress
    include "build/baserom/ovl_En_Tanron6.o"
endseg

beginseg
    name "ovl_En_Daiku2"
    compress
    include "build/baserom/ovl_En_Daiku2.o"
endseg

beginseg
    name "ovl_En_Muto"
    compress
    include "build/baserom/ovl_En_Muto.o"
endseg

beginseg
    name "ovl_En_Baisen"
    compress
    include "build/baserom/ovl_En_Baisen.o"
endseg

beginseg
    name "ovl_En_Heishi"
    compress
    include "build/baserom/ovl_En_Heishi.o"
endseg

beginseg
    name "ovl_En_Demo_heishi"
    compress
    include "build/baserom/ovl_En_Demo_heishi.o"
endseg

beginseg
    name "ovl_En_Dt"
    compress
    include "build/baserom/ovl_En_Dt.o"
endseg

beginseg
    name "ovl_En_Cha"
    compress
    include "build/baserom/ovl_En_Cha.o"
endseg

beginseg
    name "ovl_Obj_Dinner"
    compress
    include "build/baserom/ovl_Obj_Dinner.o"
endseg

beginseg
    name "ovl_Eff_Lastday"
    compress
    include "build/baserom/ovl_Eff_Lastday.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Dharma"
    compress
    include "build/baserom/ovl_Bg_Ikana_Dharma.o"
endseg

beginseg
    name "ovl_En_Akindonuts"
    compress
    include "build/baserom/ovl_En_Akindonuts.o"
endseg

beginseg
    name "ovl_Eff_Stk"
    compress
    include "build/baserom/ovl_Eff_Stk.o"
endseg

beginseg
    name "ovl_En_Ig"
    compress
    include "build/baserom/ovl_En_Ig.o"
endseg

beginseg
    name "ovl_En_Rg"
    compress
    include "build/baserom/ovl_En_Rg.o"
endseg

beginseg
    name "ovl_En_Osk"
    compress
    include "build/baserom/ovl_En_Osk.o"
endseg

beginseg
    name "ovl_En_Sth2"
    compress
    include "build/baserom/ovl_En_Sth2.o"
endseg

beginseg
    name "ovl_En_Yb"
    compress
    include "build/baserom/ovl_En_Yb.o"
endseg

beginseg
    name "ovl_En_Rz"
    compress
    include "build/baserom/ovl_En_Rz.o"
endseg

beginseg
    name "ovl_En_Scopecoin"
    compress
    include "build/baserom/ovl_En_Scopecoin.o"
endseg

beginseg
    name "ovl_En_Bjt"
    compress
    include "build/baserom/ovl_En_Bjt.o"
endseg

beginseg
    name "ovl_En_Bomjima"
    compress
    include "build/baserom/ovl_En_Bomjima.o"
endseg

beginseg
    name "ovl_En_Bomjimb"
    compress
    include "build/baserom/ovl_En_Bomjimb.o"
endseg

beginseg
    name "ovl_En_Bombers"
    compress
    include "build/baserom/ovl_En_Bombers.o"
endseg

beginseg
    name "ovl_En_Bombers2"
    compress
    include "build/baserom/ovl_En_Bombers2.o"
endseg

beginseg
    name "ovl_En_Bombal"
    compress
    include "build/baserom/ovl_En_Bombal.o"
endseg

beginseg
    name "ovl_Obj_Moon_Stone"
    compress
    include "build/baserom/ovl_Obj_Moon_Stone.o"
endseg

beginseg
    name "ovl_Obj_Mu_Pict"
    compress
    include "build/baserom/ovl_Obj_Mu_Pict.o"
endseg

beginseg
    name "ovl_Bg_Ikninside"
    compress
    include "build/baserom/ovl_Bg_Ikninside.o"
endseg

beginseg
    name "ovl_Eff_Zoraband"
    compress
    include "build/baserom/ovl_Eff_Zoraband.o"
endseg

beginseg
    name "ovl_Obj_Kepn_Koya"
    compress
    include "build/baserom/ovl_Obj_Kepn_Koya.o"
endseg

beginseg
    name "ovl_Obj_Usiyane"
    compress
    include "build/baserom/ovl_Obj_Usiyane.o"
endseg

beginseg
    name "ovl_En_Nnh"
    compress
    include "build/baserom/ovl_En_Nnh.o"
endseg

beginseg
    name "ovl_Obj_Kzsaku"
    compress
    include "build/baserom/ovl_Obj_Kzsaku.o"
endseg

beginseg
    name "ovl_Obj_Milk_Bin"
    compress
    include "build/baserom/ovl_Obj_Milk_Bin.o"
endseg

beginseg
    name "ovl_En_Kitan"
    compress
    include "build/baserom/ovl_En_Kitan.o"
endseg

beginseg
    name "ovl_Bg_Astr_Bombwall"
    compress
    include "build/baserom/ovl_Bg_Astr_Bombwall.o"
endseg

beginseg
    name "ovl_Bg_Iknin_Susceil"
    compress
    include "build/baserom/ovl_Bg_Iknin_Susceil.o"
endseg

beginseg
    name "ovl_En_Bsb"
    compress
    include "build/baserom/ovl_En_Bsb.o"
endseg

beginseg
    name "ovl_En_Recepgirl"
    compress
    include "build/baserom/ovl_En_Recepgirl.o"
endseg

beginseg
    name "ovl_En_Thiefbird"
    compress
    include "build/baserom/ovl_En_Thiefbird.o"
endseg

beginseg
    name "ovl_En_Jgame_Tsn"
    compress
    include "build/baserom/ovl_En_Jgame_Tsn.o"
endseg

beginseg
    name "ovl_Obj_Jgame_Light"
    compress
    include "build/baserom/ovl_Obj_Jgame_Light.o"
endseg

beginseg
    name "ovl_Obj_Yado"
    compress
    include "build/baserom/ovl_Obj_Yado.o"
endseg

beginseg
    name "ovl_Demo_Syoten"
    compress
    include "build/baserom/ovl_Demo_Syoten.o"
endseg

beginseg
    name "ovl_Demo_Moonend"
    compress
    include "build/baserom/ovl_Demo_Moonend.o"
endseg

beginseg
    name "ovl_Bg_Lbfshot"
    compress
    include "build/baserom/ovl_Bg_Lbfshot.o"
endseg

beginseg
    name "ovl_Bg_Last_Bwall"
    compress
    include "build/baserom/ovl_Bg_Last_Bwall.o"
endseg

beginseg
    name "ovl_En_And"
    compress
    include "build/baserom/ovl_En_And.o"
endseg

beginseg
    name "ovl_En_Invadepoh_Demo"
    compress
    include "build/baserom/ovl_En_Invadepoh_Demo.o"
endseg

beginseg
    name "ovl_Obj_Danpeilift"
    compress
    include "build/baserom/ovl_Obj_Danpeilift.o"
endseg

beginseg
    name "ovl_En_Fall2"
    compress
    include "build/baserom/ovl_En_Fall2.o"
endseg

beginseg
    name "ovl_Dm_Al"
    compress
    include "build/baserom/ovl_Dm_Al.o"
endseg

beginseg
    name "ovl_Dm_An"
    compress
    include "build/baserom/ovl_Dm_An.o"
endseg

beginseg
    name "ovl_Dm_Ah"
    compress
    include "build/baserom/ovl_Dm_Ah.o"
endseg

beginseg
    name "ovl_Dm_Nb"
    compress
    include "build/baserom/ovl_Dm_Nb.o"
endseg

beginseg
    name "ovl_En_Drs"
    compress
    include "build/baserom/ovl_En_Drs.o"
endseg

beginseg
    name "ovl_En_Ending_Hero"
    compress
    include "build/baserom/ovl_En_Ending_Hero.o"
endseg

beginseg
    name "ovl_Dm_Bal"
    compress
    include "build/baserom/ovl_Dm_Bal.o"
endseg

beginseg
    name "ovl_En_Paper"
    compress
    include "build/baserom/ovl_En_Paper.o"
endseg

beginseg
    name "ovl_En_Hint_Skb"
    compress
    include "build/baserom/ovl_En_Hint_Skb.o"
endseg

beginseg
    name "ovl_Dm_Tag"
    compress
    include "build/baserom/ovl_Dm_Tag.o"
endseg

beginseg
    name "ovl_En_Bh"
    compress
    include "build/baserom/ovl_En_Bh.o"
endseg

beginseg
    name "ovl_En_Ending_Hero2"
    compress
    include "build/baserom/ovl_En_Ending_Hero2.o"
endseg

beginseg
    name "ovl_En_Ending_Hero3"
    compress
    include "build/baserom/ovl_En_Ending_Hero3.o"
endseg

beginseg
    name "ovl_En_Ending_Hero4"
    compress
    include "build/baserom/ovl_En_Ending_Hero4.o"
endseg

beginseg
    name "ovl_En_Ending_Hero5"
    compress
    include "build/baserom/ovl_En_Ending_Hero5.o"
endseg

beginseg
    name "ovl_En_Ending_Hero6"
    compress
    include "build/baserom/ovl_En_Ending_Hero6.o"
endseg

beginseg
    name "ovl_Dm_Gm"
    compress
    include "build/baserom/ovl_Dm_Gm.o"
endseg

beginseg
    name "ovl_Obj_Swprize"
    compress
    include "build/baserom/ovl_Obj_Swprize.o"
endseg

beginseg
    name "ovl_En_Invisible_Ruppe"
    compress
    include "build/baserom/ovl_En_Invisible_Ruppe.o"
endseg

beginseg
    name "ovl_Obj_Ending"
    compress
    include "build/baserom/ovl_Obj_Ending.o"
endseg

beginseg
    name "ovl_En_Rsn"
    compress
    include "build/baserom/ovl_En_Rsn.o"
endseg

beginseg
    name "gameplay_keep"
    compress
    romalign 0x1000
    include "build/baserom/gameplay_keep.o"
endseg

beginseg
    name "gameplay_field_keep"
    compress
    romalign 0x1000
    include "build/baserom/gameplay_field_keep.o"
endseg

beginseg
    name "gameplay_dangeon_keep"
    compress
    romalign 0x1000
    include "build/baserom/gameplay_dangeon_keep.o"
endseg

beginseg
    name "gameplay_object_exchange_static"
    compress
    romalign 0x1000
    include "build/baserom/gameplay_object_exchange_static.o"
endseg

beginseg
    name "object_link_boy"
    compress
    romalign 0x1000
    include "build/baserom/object_link_boy.o"
endseg

beginseg
    name "object_link_child"
    compress
    romalign 0x1000
    include "build/baserom/object_link_child.o"
endseg

beginseg
    name "object_link_goron"
    compress
    romalign 0x1000
    include "build/baserom/object_link_goron.o"
endseg

beginseg
    name "object_link_zora"
    compress
    romalign 0x1000
    include "build/baserom/object_link_zora.o"
endseg

beginseg
    name "object_link_nuts"
    compress
    romalign 0x1000
    include "build/baserom/object_link_nuts.o"
endseg

beginseg
    name "object_mask_ki_tan"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_ki_tan.o"
endseg

beginseg
    name "object_mask_rabit"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_rabit.o"
endseg

beginseg
    name "object_mask_skj"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_skj.o"
endseg

beginseg
    name "object_mask_truth"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_truth.o"
endseg

beginseg
    name "object_mask_gibudo"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_gibudo.o"
endseg

beginseg
    name "object_mask_json"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_json.o"
endseg

beginseg
    name "object_mask_kerfay"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_kerfay.o"
endseg

beginseg
    name "object_mask_bigelf"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_bigelf.o"
endseg

beginseg
    name "object_mask_kyojin"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_kyojin.o"
endseg

beginseg
    name "object_mask_romerny"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_romerny.o"
endseg

beginseg
    name "object_mask_posthat"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_posthat.o"
endseg

beginseg
    name "object_mask_zacho"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_zacho.o"
endseg

beginseg
    name "object_mask_stone"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_stone.o"
endseg

beginseg
    name "object_mask_bree"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_bree.o"
endseg

beginseg
    name "object_mask_gero"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_gero.o"
endseg

beginseg
    name "object_mask_yofukasi"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_yofukasi.o"
endseg

beginseg
    name "object_mask_meoto"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_meoto.o"
endseg

beginseg
    name "object_mask_dancer"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_dancer.o"
endseg

beginseg
    name "object_mask_bakuretu"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_bakuretu.o"
endseg

beginseg
    name "object_mask_bu_san"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_bu_san.o"
endseg

beginseg
    name "object_mask_goron"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_goron.o"
endseg

beginseg
    name "object_mask_zora"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_zora.o"
endseg

beginseg
    name "object_mask_nuts"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_nuts.o"
endseg

beginseg
    name "object_mask_boy"
    compress
    romalign 0x1000
    include "build/baserom/object_mask_boy.o"
endseg

beginseg
    name "object_box"
    compress
    romalign 0x1000
    include "build/baserom/object_box.o"
endseg

beginseg
    name "object_okuta"
    compress
    romalign 0x1000
    include "build/baserom/object_okuta.o"
endseg

beginseg
    name "object_wallmaster"
    compress
    romalign 0x1000
    include "build/baserom/object_wallmaster.o"
endseg

beginseg
    name "object_dy_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_dy_obj.o"
endseg

beginseg
    name "object_firefly"
    compress
    romalign 0x1000
    include "build/baserom/object_firefly.o"
endseg

beginseg
    name "object_dodongo"
    compress
    romalign 0x1000
    include "build/baserom/object_dodongo.o"
endseg

beginseg
    name "object_niw"
    compress
    romalign 0x1000
    include "build/baserom/object_niw.o"
endseg

beginseg
    name "object_tite"
    compress
    romalign 0x1000
    include "build/baserom/object_tite.o"
endseg

beginseg
    name "object_ph"
    compress
    romalign 0x1000
    include "build/baserom/object_ph.o"
endseg

beginseg
    name "object_dinofos"
    compress
    romalign 0x1000
    include "build/baserom/object_dinofos.o"
endseg

beginseg
    name "object_zl1"
    compress
    romalign 0x1000
    include "build/baserom/object_zl1.o"
endseg

beginseg
    name "object_bubble"
    compress
    romalign 0x1000
    include "build/baserom/object_bubble.o"
endseg

beginseg
    name "object_test3"
    compress
    romalign 0x1000
    include "build/baserom/object_test3.o"
endseg

beginseg
    name "object_famos"
    compress
    romalign 0x1000
    include "build/baserom/object_famos.o"
endseg

beginseg
    name "object_st"
    compress
    romalign 0x1000
    include "build/baserom/object_st.o"
endseg

beginseg
    name "object_thiefbird"
    compress
    romalign 0x1000
    include "build/baserom/object_thiefbird.o"
endseg

beginseg
    name "object_bombf"
    compress
    romalign 0x1000
    include "build/baserom/object_bombf.o"
endseg

beginseg
    name "object_am"
    compress
    romalign 0x1000
    include "build/baserom/object_am.o"
endseg

beginseg
    name "object_dekubaba"
    compress
    romalign 0x1000
    include "build/baserom/object_dekubaba.o"
endseg

beginseg
    name "object_warp1"
    compress
    romalign 0x1000
    include "build/baserom/object_warp1.o"
endseg

beginseg
    name "object_b_heart"
    compress
    romalign 0x1000
    include "build/baserom/object_b_heart.o"
endseg

beginseg
    name "object_dekunuts"
    compress
    romalign 0x1000
    include "build/baserom/object_dekunuts.o"
endseg

beginseg
    name "object_bb"
    compress
    romalign 0x1000
    include "build/baserom/object_bb.o"
endseg

beginseg
    name "object_death"
    compress
    romalign 0x1000
    include "build/baserom/object_death.o"
endseg

beginseg
    name "object_hata"
    compress
    romalign 0x1000
    include "build/baserom/object_hata.o"
endseg

beginseg
    name "object_wood02"
    compress
    romalign 0x1000
    include "build/baserom/object_wood02.o"
endseg

beginseg
    name "object_trap"
    compress
    romalign 0x1000
    include "build/baserom/object_trap.o"
endseg

beginseg
    name "object_vm"
    compress
    romalign 0x1000
    include "build/baserom/object_vm.o"
endseg

beginseg
    name "object_efc_star_field"
    compress
    romalign 0x1000
    include "build/baserom/object_efc_star_field.o"
endseg

beginseg
    name "object_rd"
    compress
    romalign 0x1000
    include "build/baserom/object_rd.o"
endseg

beginseg
    name "object_yukimura_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_yukimura_obj.o"
endseg

beginseg
    name "object_horse_link_child"
    compress
    romalign 0x1000
    include "build/baserom/object_horse_link_child.o"
endseg

beginseg
    name "object_syokudai"
    compress
    romalign 0x1000
    include "build/baserom/object_syokudai.o"
endseg

beginseg
    name "object_efc_tw"
    compress
    romalign 0x1000
    include "build/baserom/object_efc_tw.o"
endseg

beginseg
    name "object_gi_key"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_key.o"
endseg

beginseg
    name "object_mir_ray"
    compress
    romalign 0x1000
    include "build/baserom/object_mir_ray.o"
endseg

beginseg
    name "object_ctower_rot"
    compress
    romalign 0x1000
    include "build/baserom/object_ctower_rot.o"
endseg

beginseg
    name "object_bdoor"
    compress
    romalign 0x1000
    include "build/baserom/object_bdoor.o"
endseg

beginseg
    name "object_sb"
    compress
    romalign 0x1000
    include "build/baserom/object_sb.o"
endseg

beginseg
    name "object_gi_melody"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_melody.o"
endseg

beginseg
    name "object_gi_heart"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_heart.o"
endseg

beginseg
    name "object_gi_compass"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_compass.o"
endseg

beginseg
    name "object_gi_bosskey"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bosskey.o"
endseg

beginseg
    name "object_gi_nuts"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_nuts.o"
endseg

beginseg
    name "object_gi_hearts"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_hearts.o"
endseg

beginseg
    name "object_gi_arrowcase"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_arrowcase.o"
endseg

beginseg
    name "object_gi_bombpouch"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bombpouch.o"
endseg

beginseg
    name "object_in"
    compress
    romalign 0x1000
    include "build/baserom/object_in.o"
endseg

beginseg
    name "object_os_anime"
    compress
    romalign 0x1000
    include "build/baserom/object_os_anime.o"
endseg

beginseg
    name "object_gi_bottle"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bottle.o"
endseg

beginseg
    name "object_gi_stick"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_stick.o"
endseg

beginseg
    name "object_gi_map"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_map.o"
endseg

beginseg
    name "object_oF1d_map"
    compress
    romalign 0x1000
    include "build/baserom/object_oF1d_map.o"
endseg

beginseg
    name "object_ru2"
    compress
    romalign 0x1000
    include "build/baserom/object_ru2.o"
endseg

beginseg
    name "object_gi_magicpot"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_magicpot.o"
endseg

beginseg
    name "object_gi_bomb_1"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bomb_1.o"
endseg

beginseg
    name "object_ma2"
    compress
    romalign 0x1000
    include "build/baserom/object_ma2.o"
endseg

beginseg
    name "object_gi_purse"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_purse.o"
endseg

beginseg
    name "object_rr"
    compress
    romalign 0x1000
    include "build/baserom/object_rr.o"
endseg

beginseg
    name "object_gi_arrow"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_arrow.o"
endseg

beginseg
    name "object_gi_bomb_2"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bomb_2.o"
endseg

beginseg
    name "object_gi_shield_2"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_shield_2.o"
endseg

beginseg
    name "object_gi_hookshot"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_hookshot.o"
endseg

beginseg
    name "object_gi_ocarina"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_ocarina.o"
endseg

beginseg
    name "object_gi_milk"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_milk.o"
endseg

beginseg
    name "object_ma1"
    compress
    romalign 0x1000
    include "build/baserom/object_ma1.o"
endseg

beginseg
    name "object_ny"
    compress
    romalign 0x1000
    include "build/baserom/object_ny.o"
endseg

beginseg
    name "object_fr"
    compress
    romalign 0x1000
    include "build/baserom/object_fr.o"
endseg

beginseg
    name "object_gi_bow"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bow.o"
endseg

beginseg
    name "object_gi_glasses"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_glasses.o"
endseg

beginseg
    name "object_gi_liquid"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_liquid.o"
endseg

beginseg
    name "object_ani"
    compress
    romalign 0x1000
    include "build/baserom/object_ani.o"
endseg

beginseg
    name "object_gi_shield_3"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_shield_3.o"
endseg

beginseg
    name "object_gi_bean"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bean.o"
endseg

beginseg
    name "object_gi_fish"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_fish.o"
endseg

beginseg
    name "object_gi_longsword"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_longsword.o"
endseg

beginseg
    name "object_zo"
    compress
    romalign 0x1000
    include "build/baserom/object_zo.o"
endseg

beginseg
    name "object_umajump"
    compress
    romalign 0x1000
    include "build/baserom/object_umajump.o"
endseg

beginseg
    name "object_mastergolon"
    compress
    romalign 0x1000
    include "build/baserom/object_mastergolon.o"
endseg

beginseg
    name "object_masterzoora"
    compress
    romalign 0x1000
    include "build/baserom/object_masterzoora.o"
endseg

beginseg
    name "object_aob"
    compress
    romalign 0x1000
    include "build/baserom/object_aob.o"
endseg

beginseg
    name "object_ik"
    compress
    romalign 0x1000
    include "build/baserom/object_ik.o"
endseg

beginseg
    name "object_ahg"
    compress
    romalign 0x1000
    include "build/baserom/object_ahg.o"
endseg

beginseg
    name "object_cne"
    compress
    romalign 0x1000
    include "build/baserom/object_cne.o"
endseg

beginseg
    name "object_bji"
    compress
    romalign 0x1000
    include "build/baserom/object_bji.o"
endseg

beginseg
    name "object_bba"
    compress
    romalign 0x1000
    include "build/baserom/object_bba.o"
endseg

beginseg
    name "object_an1"
    compress
    romalign 0x1000
    include "build/baserom/object_an1.o"
endseg

beginseg
    name "object_boj"
    compress
    romalign 0x1000
    include "build/baserom/object_boj.o"
endseg

beginseg
    name "object_fz"
    compress
    romalign 0x1000
    include "build/baserom/object_fz.o"
endseg

beginseg
    name "object_bob"
    compress
    romalign 0x1000
    include "build/baserom/object_bob.o"
endseg

beginseg
    name "object_ge1"
    compress
    romalign 0x1000
    include "build/baserom/object_ge1.o"
endseg

beginseg
    name "object_yabusame_point"
    compress
    romalign 0x1000
    include "build/baserom/object_yabusame_point.o"
endseg

beginseg
    name "object_d_hsblock"
    compress
    romalign 0x1000
    include "build/baserom/object_d_hsblock.o"
endseg

beginseg
    name "object_d_lift"
    compress
    romalign 0x1000
    include "build/baserom/object_d_lift.o"
endseg

beginseg
    name "object_mamenoki"
    compress
    romalign 0x1000
    include "build/baserom/object_mamenoki.o"
endseg

beginseg
    name "object_goroiwa"
    compress
    romalign 0x1000
    include "build/baserom/object_goroiwa.o"
endseg

beginseg
    name "object_toryo"
    compress
    romalign 0x1000
    include "build/baserom/object_toryo.o"
endseg

beginseg
    name "object_daiku"
    compress
    romalign 0x1000
    include "build/baserom/object_daiku.o"
endseg

beginseg
    name "object_nwc"
    compress
    romalign 0x1000
    include "build/baserom/object_nwc.o"
endseg

beginseg
    name "object_gm"
    compress
    romalign 0x1000
    include "build/baserom/object_gm.o"
endseg

beginseg
    name "object_ms"
    compress
    romalign 0x1000
    include "build/baserom/object_ms.o"
endseg

beginseg
    name "object_hs"
    compress
    romalign 0x1000
    include "build/baserom/object_hs.o"
endseg

beginseg
    name "object_lightswitch"
    compress
    romalign 0x1000
    include "build/baserom/object_lightswitch.o"
endseg

beginseg
    name "object_kusa"
    compress
    romalign 0x1000
    include "build/baserom/object_kusa.o"
endseg

beginseg
    name "object_tsubo"
    compress
    romalign 0x1000
    include "build/baserom/object_tsubo.o"
endseg

beginseg
    name "object_kanban"
    compress
    romalign 0x1000
    include "build/baserom/object_kanban.o"
endseg

beginseg
    name "object_owl"
    compress
    romalign 0x1000
    include "build/baserom/object_owl.o"
endseg

beginseg
    name "object_mk"
    compress
    romalign 0x1000
    include "build/baserom/object_mk.o"
endseg

beginseg
    name "object_fu"
    compress
    romalign 0x1000
    include "build/baserom/object_fu.o"
endseg

beginseg
    name "object_gi_ki_tan_mask"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_ki_tan_mask.o"
endseg

beginseg
    name "object_gi_mask18"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask18.o"
endseg

beginseg
    name "object_gi_rabit_mask"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_rabit_mask.o"
endseg

beginseg
    name "object_gi_truth_mask"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_truth_mask.o"
endseg

beginseg
    name "object_stream"
    compress
    romalign 0x1000
    include "build/baserom/object_stream.o"
endseg

beginseg
    name "object_mm"
    compress
    romalign 0x1000
    include "build/baserom/object_mm.o"
endseg

beginseg
    name "object_js"
    compress
    romalign 0x1000
    include "build/baserom/object_js.o"
endseg

beginseg
    name "object_cs"
    compress
    romalign 0x1000
    include "build/baserom/object_cs.o"
endseg

beginseg
    name "object_gi_soldout"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_soldout.o"
endseg

beginseg
    name "object_mag"
    compress
    romalign 0x1000
    include "build/baserom/object_mag.o"
endseg

beginseg
    name "object_gi_golonmask"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_golonmask.o"
endseg

beginseg
    name "object_gi_zoramask"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_zoramask.o"
endseg

beginseg
    name "object_ka"
    compress
    romalign 0x1000
    include "build/baserom/object_ka.o"
endseg

beginseg
    name "object_zg"
    compress
    romalign 0x1000
    include "build/baserom/object_zg.o"
endseg

beginseg
    name "object_gi_m_arrow"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_m_arrow.o"
endseg

beginseg
    name "object_ds2"
    compress
    romalign 0x1000
    include "build/baserom/object_ds2.o"
endseg

beginseg
    name "object_fish"
    compress
    romalign 0x1000
    include "build/baserom/object_fish.o"
endseg

beginseg
    name "object_gi_sutaru"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_sutaru.o"
endseg

beginseg
    name "object_ssh"
    compress
    romalign 0x1000
    include "build/baserom/object_ssh.o"
endseg

beginseg
    name "object_bigslime"
    compress
    romalign 0x1000
    include "build/baserom/object_bigslime.o"
endseg

beginseg
    name "object_bg"
    compress
    romalign 0x1000
    include "build/baserom/object_bg.o"
endseg

beginseg
    name "object_bombiwa"
    compress
    romalign 0x1000
    include "build/baserom/object_bombiwa.o"
endseg

beginseg
    name "object_hintnuts"
    compress
    romalign 0x1000
    include "build/baserom/object_hintnuts.o"
endseg

beginseg
    name "object_rs"
    compress
    romalign 0x1000
    include "build/baserom/object_rs.o"
endseg

beginseg
    name "object_gla"
    compress
    romalign 0x1000
    include "build/baserom/object_gla.o"
endseg

beginseg
    name "object_geldb"
    compress
    romalign 0x1000
    include "build/baserom/object_geldb.o"
endseg

beginseg
    name "object_dog"
    compress
    romalign 0x1000
    include "build/baserom/object_dog.o"
endseg

beginseg
    name "object_kibako2"
    compress
    romalign 0x1000
    include "build/baserom/object_kibako2.o"
endseg

beginseg
    name "object_dns"
    compress
    romalign 0x1000
    include "build/baserom/object_dns.o"
endseg

beginseg
    name "object_dnk"
    compress
    romalign 0x1000
    include "build/baserom/object_dnk.o"
endseg

beginseg
    name "object_gi_insect"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_insect.o"
endseg

beginseg
    name "object_gi_ghost"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_ghost.o"
endseg

beginseg
    name "object_gi_soul"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_soul.o"
endseg

beginseg
    name "object_f40_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_f40_obj.o"
endseg

beginseg
    name "object_gi_rupy"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_rupy.o"
endseg

beginseg
    name "object_po_composer"
    compress
    romalign 0x1000
    include "build/baserom/object_po_composer.o"
endseg

beginseg
    name "object_mu"
    compress
    romalign 0x1000
    include "build/baserom/object_mu.o"
endseg

beginseg
    name "object_wf"
    compress
    romalign 0x1000
    include "build/baserom/object_wf.o"
endseg

beginseg
    name "object_skb"
    compress
    romalign 0x1000
    include "build/baserom/object_skb.o"
endseg

beginseg
    name "object_gs"
    compress
    romalign 0x1000
    include "build/baserom/object_gs.o"
endseg

beginseg
    name "object_ps"
    compress
    romalign 0x1000
    include "build/baserom/object_ps.o"
endseg

beginseg
    name "object_omoya_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_omoya_obj.o"
endseg

beginseg
    name "object_crow"
    compress
    romalign 0x1000
    include "build/baserom/object_crow.o"
endseg

beginseg
    name "object_cow"
    compress
    romalign 0x1000
    include "build/baserom/object_cow.o"
endseg

beginseg
    name "object_gi_sword_1"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_sword_1.o"
endseg

beginseg
    name "object_zl4"
    compress
    romalign 0x1000
    include "build/baserom/object_zl4.o"
endseg

beginseg
    name "object_grasshopper"
    compress
    romalign 0x1000
    include "build/baserom/object_grasshopper.o"
endseg

beginseg
    name "object_boyo"
    compress
    romalign 0x1000
    include "build/baserom/object_boyo.o"
endseg

beginseg
    name "object_fwall"
    compress
    romalign 0x1000
    include "build/baserom/object_fwall.o"
endseg

beginseg
    name "object_jso"
    compress
    romalign 0x1000
    include "build/baserom/object_jso.o"
endseg

beginseg
    name "object_knight"
    compress
    romalign 0x1000
    include "build/baserom/object_knight.o"
endseg

beginseg
    name "object_icicle"
    compress
    romalign 0x1000
    include "build/baserom/object_icicle.o"
endseg

beginseg
    name "object_spdweb"
    compress
    romalign 0x1000
    include "build/baserom/object_spdweb.o"
endseg

beginseg
    name "object_boss01"
    compress
    romalign 0x1000
    include "build/baserom/object_boss01.o"
endseg

beginseg
    name "object_boss02"
    compress
    romalign 0x1000
    include "build/baserom/object_boss02.o"
endseg

beginseg
    name "object_boss03"
    compress
    romalign 0x1000
    include "build/baserom/object_boss03.o"
endseg

beginseg
    name "object_boss04"
    compress
    romalign 0x1000
    include "build/baserom/object_boss04.o"
endseg

beginseg
    name "object_boss05"
    compress
    romalign 0x1000
    include "build/baserom/object_boss05.o"
endseg

beginseg
    name "object_boss07"
    compress
    romalign 0x1000
    include "build/baserom/object_boss07.o"
endseg

beginseg
    name "object_raf"
    compress
    romalign 0x1000
    include "build/baserom/object_raf.o"
endseg

beginseg
    name "object_funen"
    compress
    romalign 0x1000
    include "build/baserom/object_funen.o"
endseg

beginseg
    name "object_raillift"
    compress
    romalign 0x1000
    include "build/baserom/object_raillift.o"
endseg

beginseg
    name "object_numa_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_numa_obj.o"
endseg

beginseg
    name "object_flowerpot"
    compress
    romalign 0x1000
    include "build/baserom/object_flowerpot.o"
endseg

beginseg
    name "object_spinyroll"
    compress
    romalign 0x1000
    include "build/baserom/object_spinyroll.o"
endseg

beginseg
    name "object_ice_block"
    compress
    romalign 0x1000
    include "build/baserom/object_ice_block.o"
endseg

beginseg
    name "object_keikoku_demo"
    compress
    romalign 0x1000
    include "build/baserom/object_keikoku_demo.o"
endseg

beginseg
    name "object_slime"
    compress
    romalign 0x1000
    include "build/baserom/object_slime.o"
endseg

beginseg
    name "object_pr"
    compress
    romalign 0x1000
    include "build/baserom/object_pr.o"
endseg

beginseg
    name "object_f52_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_f52_obj.o"
endseg

beginseg
    name "object_f53_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_f53_obj.o"
endseg

beginseg
    name "object_kibako"
    compress
    romalign 0x1000
    include "build/baserom/object_kibako.o"
endseg

beginseg
    name "object_sek"
    compress
    romalign 0x1000
    include "build/baserom/object_sek.o"
endseg

beginseg
    name "object_gmo"
    compress
    romalign 0x1000
    include "build/baserom/object_gmo.o"
endseg

beginseg
    name "object_bat"
    compress
    romalign 0x1000
    include "build/baserom/object_bat.o"
endseg

beginseg
    name "object_sekihil"
    compress
    romalign 0x1000
    include "build/baserom/object_sekihil.o"
endseg

beginseg
    name "object_sekihig"
    compress
    romalign 0x1000
    include "build/baserom/object_sekihig.o"
endseg

beginseg
    name "object_sekihin"
    compress
    romalign 0x1000
    include "build/baserom/object_sekihin.o"
endseg

beginseg
    name "object_sekihiz"
    compress
    romalign 0x1000
    include "build/baserom/object_sekihiz.o"
endseg

beginseg
    name "object_wiz"
    compress
    romalign 0x1000
    include "build/baserom/object_wiz.o"
endseg

beginseg
    name "object_ladder"
    compress
    romalign 0x1000
    include "build/baserom/object_ladder.o"
endseg

beginseg
    name "object_mkk"
    compress
    romalign 0x1000
    include "build/baserom/object_mkk.o"
endseg

beginseg
    name "object_keikoku_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_keikoku_obj.o"
endseg

beginseg
    name "object_sichitai_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_sichitai_obj.o"
endseg

beginseg
    name "object_dekucity_ana_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_dekucity_ana_obj.o"
endseg

beginseg
    name "object_rat"
    compress
    romalign 0x1000
    include "build/baserom/object_rat.o"
endseg

beginseg
    name "object_water_effect"
    compress
    romalign 0x1000
    include "build/baserom/object_water_effect.o"
endseg

beginseg
    name "object_dblue_object"
    compress
    romalign 0x1000
    include "build/baserom/object_dblue_object.o"
endseg

beginseg
    name "object_bal"
    compress
    romalign 0x1000
    include "build/baserom/object_bal.o"
endseg

beginseg
    name "object_warp_uzu"
    compress
    romalign 0x1000
    include "build/baserom/object_warp_uzu.o"
endseg

beginseg
    name "object_driftice"
    compress
    romalign 0x1000
    include "build/baserom/object_driftice.o"
endseg

beginseg
    name "object_fall"
    compress
    romalign 0x1000
    include "build/baserom/object_fall.o"
endseg

beginseg
    name "object_hanareyama_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_hanareyama_obj.o"
endseg

beginseg
    name "object_crace_object"
    compress
    romalign 0x1000
    include "build/baserom/object_crace_object.o"
endseg

beginseg
    name "object_dnq"
    compress
    romalign 0x1000
    include "build/baserom/object_dnq.o"
endseg

beginseg
    name "object_obj_tokeidai"
    compress
    romalign 0x1000
    include "build/baserom/object_obj_tokeidai.o"
endseg

beginseg
    name "object_eg"
    compress
    romalign 0x1000
    include "build/baserom/object_eg.o"
endseg

beginseg
    name "object_tru"
    compress
    romalign 0x1000
    include "build/baserom/object_tru.o"
endseg

beginseg
    name "object_trt"
    compress
    romalign 0x1000
    include "build/baserom/object_trt.o"
endseg

beginseg
    name "object_hakugin_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_hakugin_obj.o"
endseg

beginseg
    name "object_horse_game_check"
    compress
    romalign 0x1000
    include "build/baserom/object_horse_game_check.o"
endseg

beginseg
    name "object_stk"
    compress
    romalign 0x1000
    include "build/baserom/object_stk.o"
endseg

beginseg
    name "object_mnk"
    compress
    romalign 0x1000
    include "build/baserom/object_mnk.o"
endseg

beginseg
    name "object_gi_bottle_red"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bottle_red.o"
endseg

beginseg
    name "object_tokei_tobira"
    compress
    romalign 0x1000
    include "build/baserom/object_tokei_tobira.o"
endseg

beginseg
    name "object_az"
    compress
    romalign 0x1000
    include "build/baserom/object_az.o"
endseg

beginseg
    name "object_twig"
    compress
    romalign 0x1000
    include "build/baserom/object_twig.o"
endseg

beginseg
    name "object_dekucity_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_dekucity_obj.o"
endseg

beginseg
    name "object_po_fusen"
    compress
    romalign 0x1000
    include "build/baserom/object_po_fusen.o"
endseg

beginseg
    name "object_racetsubo"
    compress
    romalign 0x1000
    include "build/baserom/object_racetsubo.o"
endseg

beginseg
    name "object_ha"
    compress
    romalign 0x1000
    include "build/baserom/object_ha.o"
endseg

beginseg
    name "object_bigokuta"
    compress
    romalign 0x1000
    include "build/baserom/object_bigokuta.o"
endseg

beginseg
    name "object_open_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_open_obj.o"
endseg

beginseg
    name "object_fu_kaiten"
    compress
    romalign 0x1000
    include "build/baserom/object_fu_kaiten.o"
endseg

beginseg
    name "object_fu_mato"
    compress
    romalign 0x1000
    include "build/baserom/object_fu_mato.o"
endseg

beginseg
    name "object_mtoride"
    compress
    romalign 0x1000
    include "build/baserom/object_mtoride.o"
endseg

beginseg
    name "object_osn"
    compress
    romalign 0x1000
    include "build/baserom/object_osn.o"
endseg

beginseg
    name "object_tokei_step"
    compress
    romalign 0x1000
    include "build/baserom/object_tokei_step.o"
endseg

beginseg
    name "object_lotus"
    compress
    romalign 0x1000
    include "build/baserom/object_lotus.o"
endseg

beginseg
    name "object_tl"
    compress
    romalign 0x1000
    include "build/baserom/object_tl.o"
endseg

beginseg
    name "object_dkjail_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_dkjail_obj.o"
endseg

beginseg
    name "object_visiblock"
    compress
    romalign 0x1000
    include "build/baserom/object_visiblock.o"
endseg

beginseg
    name "object_tsn"
    compress
    romalign 0x1000
    include "build/baserom/object_tsn.o"
endseg

beginseg
    name "object_ds2n"
    compress
    romalign 0x1000
    include "build/baserom/object_ds2n.o"
endseg

beginseg
    name "object_fsn"
    compress
    romalign 0x1000
    include "build/baserom/object_fsn.o"
endseg

beginseg
    name "object_shn"
    compress
    romalign 0x1000
    include "build/baserom/object_shn.o"
endseg

beginseg
    name "object_bigicicle"
    compress
    romalign 0x1000
    include "build/baserom/object_bigicicle.o"
endseg

beginseg
    name "object_gi_bottle_15"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bottle_15.o"
endseg

beginseg
    name "object_tk"
    compress
    romalign 0x1000
    include "build/baserom/object_tk.o"
endseg

beginseg
    name "object_market_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_market_obj.o"
endseg

beginseg
    name "object_gi_reserve00"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_reserve00.o"
endseg

beginseg
    name "object_gi_reserve01"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_reserve01.o"
endseg

beginseg
    name "object_lightblock"
    compress
    romalign 0x1000
    include "build/baserom/object_lightblock.o"
endseg

beginseg
    name "object_takaraya_objects"
    compress
    romalign 0x1000
    include "build/baserom/object_takaraya_objects.o"
endseg

beginseg
    name "object_wdhand"
    compress
    romalign 0x1000
    include "build/baserom/object_wdhand.o"
endseg

beginseg
    name "object_sdn"
    compress
    romalign 0x1000
    include "build/baserom/object_sdn.o"
endseg

beginseg
    name "object_snowwd"
    compress
    romalign 0x1000
    include "build/baserom/object_snowwd.o"
endseg

beginseg
    name "object_giant"
    compress
    romalign 0x1000
    include "build/baserom/object_giant.o"
endseg

beginseg
    name "object_comb"
    compress
    romalign 0x1000
    include "build/baserom/object_comb.o"
endseg

beginseg
    name "object_hana"
    compress
    romalign 0x1000
    include "build/baserom/object_hana.o"
endseg

beginseg
    name "object_boss_hakugin"
    compress
    romalign 0x1000
    include "build/baserom/object_boss_hakugin.o"
endseg

beginseg
    name "object_meganeana_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_meganeana_obj.o"
endseg

beginseg
    name "object_gi_nutsmask"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_nutsmask.o"
endseg

beginseg
    name "object_stk2"
    compress
    romalign 0x1000
    include "build/baserom/object_stk2.o"
endseg

beginseg
    name "object_spot11_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_spot11_obj.o"
endseg

beginseg
    name "object_danpei_object"
    compress
    romalign 0x1000
    include "build/baserom/object_danpei_object.o"
endseg

beginseg
    name "object_dhouse"
    compress
    romalign 0x1000
    include "build/baserom/object_dhouse.o"
endseg

beginseg
    name "object_hakaisi"
    compress
    romalign 0x1000
    include "build/baserom/object_hakaisi.o"
endseg

beginseg
    name "object_po"
    compress
    romalign 0x1000
    include "build/baserom/object_po.o"
endseg

beginseg
    name "object_snowman"
    compress
    romalign 0x1000
    include "build/baserom/object_snowman.o"
endseg

beginseg
    name "object_po_sisters"
    compress
    romalign 0x1000
    include "build/baserom/object_po_sisters.o"
endseg

beginseg
    name "object_pp"
    compress
    romalign 0x1000
    include "build/baserom/object_pp.o"
endseg

beginseg
    name "object_goronswitch"
    compress
    romalign 0x1000
    include "build/baserom/object_goronswitch.o"
endseg

beginseg
    name "object_delf"
    compress
    romalign 0x1000
    include "build/baserom/object_delf.o"
endseg

beginseg
    name "object_botihasira"
    compress
    romalign 0x1000
    include "build/baserom/object_botihasira.o"
endseg

beginseg
    name "object_gi_bigbomb"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bigbomb.o"
endseg

beginseg
    name "object_pst"
    compress
    romalign 0x1000
    include "build/baserom/object_pst.o"
endseg

beginseg
    name "object_bsmask"
    compress
    romalign 0x1000
    include "build/baserom/object_bsmask.o"
endseg

beginseg
    name "object_spidertent"
    compress
    romalign 0x1000
    include "build/baserom/object_spidertent.o"
endseg

beginseg
    name "object_zoraegg"
    compress
    romalign 0x1000
    include "build/baserom/object_zoraegg.o"
endseg

beginseg
    name "object_kbt"
    compress
    romalign 0x1000
    include "build/baserom/object_kbt.o"
endseg

beginseg
    name "object_gg"
    compress
    romalign 0x1000
    include "build/baserom/object_gg.o"
endseg

beginseg
    name "object_maruta"
    compress
    romalign 0x1000
    include "build/baserom/object_maruta.o"
endseg

beginseg
    name "object_ghaka"
    compress
    romalign 0x1000
    include "build/baserom/object_ghaka.o"
endseg

beginseg
    name "object_oyu"
    compress
    romalign 0x1000
    include "build/baserom/object_oyu.o"
endseg

beginseg
    name "object_dnp"
    compress
    romalign 0x1000
    include "build/baserom/object_dnp.o"
endseg

beginseg
    name "object_dai"
    compress
    romalign 0x1000
    include "build/baserom/object_dai.o"
endseg

beginseg
    name "object_kgy"
    compress
    romalign 0x1000
    include "build/baserom/object_kgy.o"
endseg

beginseg
    name "object_fb"
    compress
    romalign 0x1000
    include "build/baserom/object_fb.o"
endseg

beginseg
    name "object_taisou"
    compress
    romalign 0x1000
    include "build/baserom/object_taisou.o"
endseg

beginseg
    name "object_gk"
    compress
    romalign 0x1000
    include "build/baserom/object_gk.o"
endseg

beginseg
    name "object_haka_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_haka_obj.o"
endseg

beginseg
    name "object_dnt"
    compress
    romalign 0x1000
    include "build/baserom/object_dnt.o"
endseg

beginseg
    name "object_yukiyama"
    compress
    romalign 0x1000
    include "build/baserom/object_yukiyama.o"
endseg

beginseg
    name "object_icefloe"
    compress
    romalign 0x1000
    include "build/baserom/object_icefloe.o"
endseg

beginseg
    name "object_gi_gold_dust"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_gold_dust.o"
endseg

beginseg
    name "object_gi_bottle_16"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bottle_16.o"
endseg

beginseg
    name "object_gi_bottle_22"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bottle_22.o"
endseg

beginseg
    name "object_bee"
    compress
    romalign 0x1000
    include "build/baserom/object_bee.o"
endseg

beginseg
    name "object_ot"
    compress
    romalign 0x1000
    include "build/baserom/object_ot.o"
endseg

beginseg
    name "object_utubo"
    compress
    romalign 0x1000
    include "build/baserom/object_utubo.o"
endseg

beginseg
    name "object_dora"
    compress
    romalign 0x1000
    include "build/baserom/object_dora.o"
endseg

beginseg
    name "object_gi_loach"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_loach.o"
endseg

beginseg
    name "object_gi_seahorse"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_seahorse.o"
endseg

beginseg
    name "object_bigpo"
    compress
    romalign 0x1000
    include "build/baserom/object_bigpo.o"
endseg

beginseg
    name "object_hariko"
    compress
    romalign 0x1000
    include "build/baserom/object_hariko.o"
endseg

beginseg
    name "object_dno"
    compress
    romalign 0x1000
    include "build/baserom/object_dno.o"
endseg

beginseg
    name "object_sinkai_kabe"
    compress
    romalign 0x1000
    include "build/baserom/object_sinkai_kabe.o"
endseg

beginseg
    name "object_kin2_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_kin2_obj.o"
endseg

beginseg
    name "object_ishi"
    compress
    romalign 0x1000
    include "build/baserom/object_ishi.o"
endseg

beginseg
    name "object_hakugin_demo"
    compress
    romalign 0x1000
    include "build/baserom/object_hakugin_demo.o"
endseg

beginseg
    name "object_jg"
    compress
    romalign 0x1000
    include "build/baserom/object_jg.o"
endseg

beginseg
    name "object_gi_sword_2"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_sword_2.o"
endseg

beginseg
    name "object_gi_sword_3"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_sword_3.o"
endseg

beginseg
    name "object_gi_sword_4"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_sword_4.o"
endseg

beginseg
    name "object_um"
    compress
    romalign 0x1000
    include "build/baserom/object_um.o"
endseg

beginseg
    name "object_rb"
    compress
    romalign 0x1000
    include "build/baserom/object_rb.o"
endseg

beginseg
    name "object_mbar_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_mbar_obj.o"
endseg

beginseg
    name "object_ikana_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_ikana_obj.o"
endseg

beginseg
    name "object_kz"
    compress
    romalign 0x1000
    include "build/baserom/object_kz.o"
endseg

beginseg
    name "object_tokei_turret"
    compress
    romalign 0x1000
    include "build/baserom/object_tokei_turret.o"
endseg

beginseg
    name "object_zog"
    compress
    romalign 0x1000
    include "build/baserom/object_zog.o"
endseg

beginseg
    name "object_rotlift"
    compress
    romalign 0x1000
    include "build/baserom/object_rotlift.o"
endseg

beginseg
    name "object_posthouse_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_posthouse_obj.o"
endseg

beginseg
    name "object_gi_mask09"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask09.o"
endseg

beginseg
    name "object_gi_mask14"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask14.o"
endseg

beginseg
    name "object_gi_mask15"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask15.o"
endseg

beginseg
    name "object_inibs_object"
    compress
    romalign 0x1000
    include "build/baserom/object_inibs_object.o"
endseg

beginseg
    name "object_tree"
    compress
    romalign 0x1000
    include "build/baserom/object_tree.o"
endseg

beginseg
    name "object_kaizoku_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_kaizoku_obj.o"
endseg

beginseg
    name "object_gi_reserve_b_00"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_reserve_b_00.o"
endseg

beginseg
    name "object_gi_reserve_c_00"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_reserve_c_00.o"
endseg

beginseg
    name "object_zob"
    compress
    romalign 0x1000
    include "build/baserom/object_zob.o"
endseg

beginseg
    name "object_milkbar"
    compress
    romalign 0x1000
    include "build/baserom/object_milkbar.o"
endseg

beginseg
    name "object_dmask"
    compress
    romalign 0x1000
    include "build/baserom/object_dmask.o"
endseg

beginseg
    name "object_gi_reserve_c_01"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_reserve_c_01.o"
endseg

beginseg
    name "object_zod"
    compress
    romalign 0x1000
    include "build/baserom/object_zod.o"
endseg

beginseg
    name "object_kumo30"
    compress
    romalign 0x1000
    include "build/baserom/object_kumo30.o"
endseg

beginseg
    name "object_obj_yasi"
    compress
    romalign 0x1000
    include "build/baserom/object_obj_yasi.o"
endseg

beginseg
    name "object_tanron1"
    compress
    romalign 0x1000
    include "build/baserom/object_tanron1.o"
endseg

beginseg
    name "object_tanron2"
    compress
    romalign 0x1000
    include "build/baserom/object_tanron2.o"
endseg

beginseg
    name "object_tanron3"
    compress
    romalign 0x1000
    include "build/baserom/object_tanron3.o"
endseg

beginseg
    name "object_gi_magicmushroom"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_magicmushroom.o"
endseg

beginseg
    name "object_obj_chan"
    compress
    romalign 0x1000
    include "build/baserom/object_obj_chan.o"
endseg

beginseg
    name "object_gi_mask10"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask10.o"
endseg

beginseg
    name "object_zos"
    compress
    romalign 0x1000
    include "build/baserom/object_zos.o"
endseg

beginseg
    name "object_an2"
    compress
    romalign 0x1000
    include "build/baserom/object_an2.o"
endseg

beginseg
    name "object_an3"
    compress
    romalign 0x1000
    include "build/baserom/object_an3.o"
endseg

beginseg
    name "object_f40_switch"
    compress
    romalign 0x1000
    include "build/baserom/object_f40_switch.o"
endseg

beginseg
    name "object_lodmoon"
    compress
    romalign 0x1000
    include "build/baserom/object_lodmoon.o"
endseg

beginseg
    name "object_tro"
    compress
    romalign 0x1000
    include "build/baserom/object_tro.o"
endseg

beginseg
    name "object_gi_mask12"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask12.o"
endseg

beginseg
    name "object_gi_mask23"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask23.o"
endseg

beginseg
    name "object_gi_bottle_21"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bottle_21.o"
endseg

beginseg
    name "object_gi_camera"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_camera.o"
endseg

beginseg
    name "object_kamejima"
    compress
    romalign 0x1000
    include "build/baserom/object_kamejima.o"
endseg

beginseg
    name "object_nb"
    compress
    romalign 0x1000
    include "build/baserom/object_nb.o"
endseg

beginseg
    name "object_harfgibud"
    compress
    romalign 0x1000
    include "build/baserom/object_harfgibud.o"
endseg

beginseg
    name "object_zov"
    compress
    romalign 0x1000
    include "build/baserom/object_zov.o"
endseg

beginseg
    name "object_ah"
    compress
    romalign 0x1000
    include "build/baserom/object_ah.o"
endseg

beginseg
    name "object_hgdoor"
    compress
    romalign 0x1000
    include "build/baserom/object_hgdoor.o"
endseg

beginseg
    name "object_dor01"
    compress
    romalign 0x1000
    include "build/baserom/object_dor01.o"
endseg

beginseg
    name "object_dor02"
    compress
    romalign 0x1000
    include "build/baserom/object_dor02.o"
endseg

beginseg
    name "object_dor03"
    compress
    romalign 0x1000
    include "build/baserom/object_dor03.o"
endseg

beginseg
    name "object_dor04"
    compress
    romalign 0x1000
    include "build/baserom/object_dor04.o"
endseg

beginseg
    name "object_last_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_last_obj.o"
endseg

beginseg
    name "object_redead_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_redead_obj.o"
endseg

beginseg
    name "object_ikninside_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_ikninside_obj.o"
endseg

beginseg
    name "object_iknv_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_iknv_obj.o"
endseg

beginseg
    name "object_pamera"
    compress
    romalign 0x1000
    include "build/baserom/object_pamera.o"
endseg

beginseg
    name "object_hsstump"
    compress
    romalign 0x1000
    include "build/baserom/object_hsstump.o"
endseg

beginseg
    name "object_zm"
    compress
    romalign 0x1000
    include "build/baserom/object_zm.o"
endseg

beginseg
    name "object_al"
    compress
    romalign 0x1000
    include "build/baserom/object_al.o"
endseg

beginseg
    name "object_tab"
    compress
    romalign 0x1000
    include "build/baserom/object_tab.o"
endseg

beginseg
    name "object_secom_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_secom_obj.o"
endseg

beginseg
    name "object_dt"
    compress
    romalign 0x1000
    include "build/baserom/object_dt.o"
endseg

beginseg
    name "object_gi_mask03"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask03.o"
endseg

beginseg
    name "object_cha"
    compress
    romalign 0x1000
    include "build/baserom/object_cha.o"
endseg

beginseg
    name "object_obj_dinner"
    compress
    romalign 0x1000
    include "build/baserom/object_obj_dinner.o"
endseg

beginseg
    name "object_gi_reserve_b_01"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_reserve_b_01.o"
endseg

beginseg
    name "object_lastday"
    compress
    romalign 0x1000
    include "build/baserom/object_lastday.o"
endseg

beginseg
    name "object_bai"
    compress
    romalign 0x1000
    include "build/baserom/object_bai.o"
endseg

beginseg
    name "object_ikn_demo"
    compress
    romalign 0x1000
    include "build/baserom/object_ikn_demo.o"
endseg

beginseg
    name "object_gi_fieldmap"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_fieldmap.o"
endseg

beginseg
    name "object_big_fwall"
    compress
    romalign 0x1000
    include "build/baserom/object_big_fwall.o"
endseg

beginseg
    name "object_hunsui"
    compress
    romalign 0x1000
    include "build/baserom/object_hunsui.o"
endseg

beginseg
    name "object_uch"
    compress
    romalign 0x1000
    include "build/baserom/object_uch.o"
endseg

beginseg
    name "object_tanron4"
    compress
    romalign 0x1000
    include "build/baserom/object_tanron4.o"
endseg

beginseg
    name "object_tanron5"
    compress
    romalign 0x1000
    include "build/baserom/object_tanron5.o"
endseg

beginseg
    name "object_in2"
    compress
    romalign 0x1000
    include "build/baserom/object_in2.o"
endseg

beginseg
    name "object_yb"
    compress
    romalign 0x1000
    include "build/baserom/object_yb.o"
endseg

beginseg
    name "object_rz"
    compress
    romalign 0x1000
    include "build/baserom/object_rz.o"
endseg

beginseg
    name "object_bjt"
    compress
    romalign 0x1000
    include "build/baserom/object_bjt.o"
endseg

beginseg
    name "object_taru"
    compress
    romalign 0x1000
    include "build/baserom/object_taru.o"
endseg

beginseg
    name "object_moonston"
    compress
    romalign 0x1000
    include "build/baserom/object_moonston.o"
endseg

beginseg
    name "object_gi_schedule"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_schedule.o"
endseg

beginseg
    name "object_gi_stonemask"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_stonemask.o"
endseg

beginseg
    name "object_zoraband"
    compress
    romalign 0x1000
    include "build/baserom/object_zoraband.o"
endseg

beginseg
    name "object_kepn_koya"
    compress
    romalign 0x1000
    include "build/baserom/object_kepn_koya.o"
endseg

beginseg
    name "object_obj_usiyane"
    compress
    romalign 0x1000
    include "build/baserom/object_obj_usiyane.o"
endseg

beginseg
    name "object_gi_mask05"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask05.o"
endseg

beginseg
    name "object_gi_mask11"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask11.o"
endseg

beginseg
    name "object_gi_mask20"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask20.o"
endseg

beginseg
    name "object_nnh"
    compress
    romalign 0x1000
    include "build/baserom/object_nnh.o"
endseg

beginseg
    name "object_kzsaku"
    compress
    romalign 0x1000
    include "build/baserom/object_kzsaku.o"
endseg

beginseg
    name "object_obj_milk_bin"
    compress
    romalign 0x1000
    include "build/baserom/object_obj_milk_bin.o"
endseg

beginseg
    name "object_random_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_random_obj.o"
endseg

beginseg
    name "object_kujiya"
    compress
    romalign 0x1000
    include "build/baserom/object_kujiya.o"
endseg

beginseg
    name "object_kitan"
    compress
    romalign 0x1000
    include "build/baserom/object_kitan.o"
endseg

beginseg
    name "object_gi_mask06"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask06.o"
endseg

beginseg
    name "object_gi_mask16"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask16.o"
endseg

beginseg
    name "object_astr_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_astr_obj.o"
endseg

beginseg
    name "object_bsb"
    compress
    romalign 0x1000
    include "build/baserom/object_bsb.o"
endseg

beginseg
    name "object_fall2"
    compress
    romalign 0x1000
    include "build/baserom/object_fall2.o"
endseg

beginseg
    name "object_sth"
    compress
    romalign 0x1000
    include "build/baserom/object_sth.o"
endseg

beginseg
    name "object_gi_mssa"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mssa.o"
endseg

beginseg
    name "object_smtower"
    compress
    romalign 0x1000
    include "build/baserom/object_smtower.o"
endseg

beginseg
    name "object_gi_mask21"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask21.o"
endseg

beginseg
    name "object_yado_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_yado_obj.o"
endseg

beginseg
    name "object_syoten"
    compress
    romalign 0x1000
    include "build/baserom/object_syoten.o"
endseg

beginseg
    name "object_moonend"
    compress
    romalign 0x1000
    include "build/baserom/object_moonend.o"
endseg

beginseg
    name "object_ob"
    compress
    romalign 0x1000
    include "build/baserom/object_ob.o"
endseg

beginseg
    name "object_gi_bottle_04"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_bottle_04.o"
endseg

beginseg
    name "object_and"
    compress
    romalign 0x1000
    include "build/baserom/object_and.o"
endseg

beginseg
    name "object_obj_danpeilift"
    compress
    romalign 0x1000
    include "build/baserom/object_obj_danpeilift.o"
endseg

beginseg
    name "object_drs"
    compress
    romalign 0x1000
    include "build/baserom/object_drs.o"
endseg

beginseg
    name "object_msmo"
    compress
    romalign 0x1000
    include "build/baserom/object_msmo.o"
endseg

beginseg
    name "object_an4"
    compress
    romalign 0x1000
    include "build/baserom/object_an4.o"
endseg

beginseg
    name "object_wdor01"
    compress
    romalign 0x1000
    include "build/baserom/object_wdor01.o"
endseg

beginseg
    name "object_wdor02"
    compress
    romalign 0x1000
    include "build/baserom/object_wdor02.o"
endseg

beginseg
    name "object_wdor03"
    compress
    romalign 0x1000
    include "build/baserom/object_wdor03.o"
endseg

beginseg
    name "object_wdor04"
    compress
    romalign 0x1000
    include "build/baserom/object_wdor04.o"
endseg

beginseg
    name "object_wdor05"
    compress
    romalign 0x1000
    include "build/baserom/object_wdor05.o"
endseg

beginseg
    name "object_stk3"
    compress
    romalign 0x1000
    include "build/baserom/object_stk3.o"
endseg

beginseg
    name "object_kinsta1_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_kinsta1_obj.o"
endseg

beginseg
    name "object_kinsta2_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_kinsta2_obj.o"
endseg

beginseg
    name "object_bh"
    compress
    romalign 0x1000
    include "build/baserom/object_bh.o"
endseg

beginseg
    name "object_gi_mask17"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask17.o"
endseg

beginseg
    name "object_gi_mask22"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask22.o"
endseg

beginseg
    name "object_lbfshot"
    compress
    romalign 0x1000
    include "build/baserom/object_lbfshot.o"
endseg

beginseg
    name "object_fusen"
    compress
    romalign 0x1000
    include "build/baserom/object_fusen.o"
endseg

beginseg
    name "object_ending_obj"
    compress
    romalign 0x1000
    include "build/baserom/object_ending_obj.o"
endseg

beginseg
    name "object_gi_mask13"
    compress
    romalign 0x1000
    include "build/baserom/object_gi_mask13.o"
endseg

beginseg
    name "scene_texture_01"
    compress
    romalign 0x1000
    include "build/baserom/scene_texture_01.o"
endseg

beginseg
    name "scene_texture_02"
    compress
    romalign 0x1000
    include "build/baserom/scene_texture_02.o"
endseg

beginseg
    name "scene_texture_03"
    compress
    romalign 0x1000
    include "build/baserom/scene_texture_03.o"
endseg

beginseg
    name "scene_texture_04"
    compress
    romalign 0x1000
    include "build/baserom/scene_texture_04.o"
endseg

beginseg
    name "scene_texture_05"
    compress
    romalign 0x1000
    include "build/baserom/scene_texture_05.o"
endseg

beginseg
    name "scene_texture_06"
    compress
    romalign 0x1000
    include "build/baserom/scene_texture_06.o"
endseg

beginseg
    name "scene_texture_07"
    compress
    romalign 0x1000
    include "build/baserom/scene_texture_07.o"
endseg

beginseg
    name "scene_texture_08"
    compress
    romalign 0x1000
    include "build/baserom/scene_texture_08.o"
endseg

beginseg
    name "nintendo_rogo_static"
    compress
    romalign 0x1000
    include "build/baserom/nintendo_rogo_static.o"
endseg

beginseg
    name "title_static"
    compress
    romalign 0x1000
    include "build/baserom/title_static.o"
endseg

beginseg
    name "memerrmsg"
    compress
    romalign 0x1000
    include "build/baserom/memerrmsg.o"
endseg

beginseg
    name "locerrmsg"
    compress
    romalign 0x1000
    include "build/baserom/locerrmsg.o"
endseg

beginseg
    name "parameter_static"
    compress
    romalign 0x1000
    include "build/baserom/parameter_static.o"
endseg

beginseg
    name "week_static"
    romalign 0x1000
    include "build/baserom/week_static.o"
endseg

beginseg
    name "daytelop_static"
    compress
    romalign 0x1000
    include "build/baserom/daytelop_static.o"
endseg

beginseg
    name "ger_daytelop_static"
    compress
    romalign 0x1000
    include "build/baserom/ger_daytelop_static.o"
endseg

beginseg
    name "fra_daytelop_static"
    compress
    romalign 0x1000
    include "build/baserom/fra_daytelop_static.o"
endseg

beginseg
    name "esp_daytelop_static"
    compress
    romalign 0x1000
    include "build/baserom/esp_daytelop_static.o"
endseg

beginseg
    name "d2_fine_static"
    compress
    romalign 0x1000
    include "build/baserom/d2_fine_static.o"
endseg

beginseg
    name "d2_cloud_static"
    compress
    romalign 0x1000
    include "build/baserom/d2_cloud_static.o"
endseg

beginseg
    name "d2_fine_pal_static"
    compress
    romalign 0x1000
    include "build/baserom/d2_fine_pal_static.o"
endseg

beginseg
    name "elf_message_field"
    compress
    romalign 0x1000
    include "build/baserom/elf_message_field.o"
endseg

beginseg
    name "elf_message_ydan"
    compress
    romalign 0x1000
    include "build/baserom/elf_message_ydan.o"
endseg

beginseg
    name "Z2_20SICHITAI2"
    compress
    romalign 0x1000
    include "build/baserom/Z2_20SICHITAI2.o"
endseg

beginseg
    name "Z2_20SICHITAI2_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_20SICHITAI2_room_00.o"
endseg

beginseg
    name "Z2_20SICHITAI2_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_20SICHITAI2_room_01.o"
endseg

beginseg
    name "Z2_20SICHITAI2_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_20SICHITAI2_room_02.o"
endseg

beginseg
    name "Z2_WITCH_SHOP"
    compress
    romalign 0x1000
    include "build/baserom/Z2_WITCH_SHOP.o"
endseg

beginseg
    name "Z2_WITCH_SHOP_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_WITCH_SHOP_room_00.o"
endseg

beginseg
    name "Z2_LAST_BS"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_BS.o"
endseg

beginseg
    name "Z2_LAST_BS_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_BS_room_00.o"
endseg

beginseg
    name "Z2_HAKASHITA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKASHITA.o"
endseg

beginseg
    name "Z2_HAKASHITA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKASHITA_room_00.o"
endseg

beginseg
    name "Z2_HAKASHITA_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKASHITA_room_01.o"
endseg

beginseg
    name "Z2_HAKASHITA_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKASHITA_room_02.o"
endseg

beginseg
    name "Z2_HAKASHITA_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKASHITA_room_03.o"
endseg

beginseg
    name "Z2_HAKASHITA_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKASHITA_room_04.o"
endseg

beginseg
    name "Z2_AYASHIISHOP"
    compress
    romalign 0x1000
    include "build/baserom/Z2_AYASHIISHOP.o"
endseg

beginseg
    name "Z2_AYASHIISHOP_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_AYASHIISHOP_room_00.o"
endseg

beginseg
    name "Z2_AYASHIISHOP_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_AYASHIISHOP_room_01.o"
endseg

beginseg
    name "Z2_OMOYA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_OMOYA.o"
endseg

beginseg
    name "Z2_OMOYA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_OMOYA_room_00.o"
endseg

beginseg
    name "Z2_OMOYA_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_OMOYA_room_01.o"
endseg

beginseg
    name "Z2_OMOYA_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_OMOYA_room_02.o"
endseg

beginseg
    name "Z2_BOWLING"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BOWLING.o"
endseg

beginseg
    name "Z2_BOWLING_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BOWLING_room_00.o"
endseg

beginseg
    name "Z2_SONCHONOIE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SONCHONOIE.o"
endseg

beginseg
    name "Z2_SONCHONOIE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SONCHONOIE_room_00.o"
endseg

beginseg
    name "Z2_SONCHONOIE_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SONCHONOIE_room_01.o"
endseg

beginseg
    name "Z2_SONCHONOIE_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SONCHONOIE_room_02.o"
endseg

beginseg
    name "Z2_SONCHONOIE_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SONCHONOIE_room_03.o"
endseg

beginseg
    name "Z2_IKANA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKANA.o"
endseg

beginseg
    name "Z2_IKANA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKANA_room_00.o"
endseg

beginseg
    name "Z2_IKANA_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKANA_room_01.o"
endseg

beginseg
    name "Z2_IKANA_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKANA_room_02.o"
endseg

beginseg
    name "Z2_IKANA_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKANA_room_03.o"
endseg

beginseg
    name "Z2_IKANA_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKANA_room_04.o"
endseg

beginseg
    name "Z2_KAIZOKU"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KAIZOKU.o"
endseg

beginseg
    name "Z2_KAIZOKU_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KAIZOKU_room_00.o"
endseg

beginseg
    name "Z2_MILK_BAR"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MILK_BAR.o"
endseg

beginseg
    name "Z2_MILK_BAR_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MILK_BAR_room_00.o"
endseg

beginseg
    name "Z2_INISIE_N"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N.o"
endseg

beginseg
    name "Z2_INISIE_N_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_00.o"
endseg

beginseg
    name "Z2_INISIE_N_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_01.o"
endseg

beginseg
    name "Z2_INISIE_N_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_02.o"
endseg

beginseg
    name "Z2_INISIE_N_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_03.o"
endseg

beginseg
    name "Z2_INISIE_N_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_04.o"
endseg

beginseg
    name "Z2_INISIE_N_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_05.o"
endseg

beginseg
    name "Z2_INISIE_N_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_06.o"
endseg

beginseg
    name "Z2_INISIE_N_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_07.o"
endseg

beginseg
    name "Z2_INISIE_N_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_08.o"
endseg

beginseg
    name "Z2_INISIE_N_room_09"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_09.o"
endseg

beginseg
    name "Z2_INISIE_N_room_10"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_10.o"
endseg

beginseg
    name "Z2_INISIE_N_room_11"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_N_room_11.o"
endseg

beginseg
    name "Z2_TAKARAYA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TAKARAYA.o"
endseg

beginseg
    name "Z2_TAKARAYA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TAKARAYA_room_00.o"
endseg

beginseg
    name "Z2_INISIE_R"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R.o"
endseg

beginseg
    name "Z2_INISIE_R_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_00.o"
endseg

beginseg
    name "Z2_INISIE_R_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_01.o"
endseg

beginseg
    name "Z2_INISIE_R_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_02.o"
endseg

beginseg
    name "Z2_INISIE_R_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_03.o"
endseg

beginseg
    name "Z2_INISIE_R_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_04.o"
endseg

beginseg
    name "Z2_INISIE_R_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_05.o"
endseg

beginseg
    name "Z2_INISIE_R_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_06.o"
endseg

beginseg
    name "Z2_INISIE_R_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_07.o"
endseg

beginseg
    name "Z2_INISIE_R_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_08.o"
endseg

beginseg
    name "Z2_INISIE_R_room_09"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_09.o"
endseg

beginseg
    name "Z2_INISIE_R_room_10"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_10.o"
endseg

beginseg
    name "Z2_INISIE_R_room_11"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_R_room_11.o"
endseg

beginseg
    name "Z2_OKUJOU"
    compress
    romalign 0x1000
    include "build/baserom/Z2_OKUJOU.o"
endseg

beginseg
    name "Z2_OKUJOU_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_OKUJOU_room_00.o"
endseg

beginseg
    name "Z2_OPENINGDAN"
    compress
    romalign 0x1000
    include "build/baserom/Z2_OPENINGDAN.o"
endseg

beginseg
    name "Z2_OPENINGDAN_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_OPENINGDAN_room_00.o"
endseg

beginseg
    name "Z2_OPENINGDAN_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_OPENINGDAN_room_01.o"
endseg

beginseg
    name "Z2_MITURIN"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN.o"
endseg

beginseg
    name "Z2_MITURIN_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_00.o"
endseg

beginseg
    name "Z2_MITURIN_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_01.o"
endseg

beginseg
    name "Z2_MITURIN_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_02.o"
endseg

beginseg
    name "Z2_MITURIN_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_03.o"
endseg

beginseg
    name "Z2_MITURIN_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_04.o"
endseg

beginseg
    name "Z2_MITURIN_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_05.o"
endseg

beginseg
    name "Z2_MITURIN_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_06.o"
endseg

beginseg
    name "Z2_MITURIN_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_07.o"
endseg

beginseg
    name "Z2_MITURIN_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_08.o"
endseg

beginseg
    name "Z2_MITURIN_room_09"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_09.o"
endseg

beginseg
    name "Z2_MITURIN_room_10"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_10.o"
endseg

beginseg
    name "Z2_MITURIN_room_11"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_11.o"
endseg

beginseg
    name "Z2_MITURIN_room_12"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_room_12.o"
endseg

beginseg
    name "Z2_13HUBUKINOMITI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_13HUBUKINOMITI.o"
endseg

beginseg
    name "Z2_13HUBUKINOMITI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_13HUBUKINOMITI_room_00.o"
endseg

beginseg
    name "Z2_CASTLE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE.o"
endseg

beginseg
    name "Z2_CASTLE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_00.o"
endseg

beginseg
    name "Z2_CASTLE_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_01.o"
endseg

beginseg
    name "Z2_CASTLE_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_02.o"
endseg

beginseg
    name "Z2_CASTLE_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_03.o"
endseg

beginseg
    name "Z2_CASTLE_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_04.o"
endseg

beginseg
    name "Z2_CASTLE_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_05.o"
endseg

beginseg
    name "Z2_CASTLE_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_06.o"
endseg

beginseg
    name "Z2_CASTLE_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_07.o"
endseg

beginseg
    name "Z2_CASTLE_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_08.o"
endseg

beginseg
    name "Z2_CASTLE_room_09"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CASTLE_room_09.o"
endseg

beginseg
    name "Z2_DEKUTES"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DEKUTES.o"
endseg

beginseg
    name "Z2_DEKUTES_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DEKUTES_room_00.o"
endseg

beginseg
    name "Z2_MITURIN_BS"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_BS.o"
endseg

beginseg
    name "Z2_MITURIN_BS_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MITURIN_BS_room_00.o"
endseg

beginseg
    name "Z2_SYATEKI_MIZU"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SYATEKI_MIZU.o"
endseg

beginseg
    name "Z2_SYATEKI_MIZU_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SYATEKI_MIZU_room_00.o"
endseg

beginseg
    name "Z2_HAKUGIN"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_00.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_01.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_02.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_03.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_04.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_05.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_06.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_07.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_08.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_09"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_09.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_10"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_10.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_11"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_11.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_12"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_12.o"
endseg

beginseg
    name "Z2_HAKUGIN_room_13"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_room_13.o"
endseg

beginseg
    name "Z2_ROMANYMAE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_ROMANYMAE.o"
endseg

beginseg
    name "Z2_ROMANYMAE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_ROMANYMAE_room_00.o"
endseg

beginseg
    name "Z2_PIRATE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE.o"
endseg

beginseg
    name "Z2_PIRATE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_00.o"
endseg

beginseg
    name "Z2_PIRATE_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_01.o"
endseg

beginseg
    name "Z2_PIRATE_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_02.o"
endseg

beginseg
    name "Z2_PIRATE_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_03.o"
endseg

beginseg
    name "Z2_PIRATE_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_04.o"
endseg

beginseg
    name "Z2_PIRATE_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_05.o"
endseg

beginseg
    name "Z2_PIRATE_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_06.o"
endseg

beginseg
    name "Z2_PIRATE_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_07.o"
endseg

beginseg
    name "Z2_PIRATE_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_08.o"
endseg

beginseg
    name "Z2_PIRATE_room_09"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_09.o"
endseg

beginseg
    name "Z2_PIRATE_room_10"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_10.o"
endseg

beginseg
    name "Z2_PIRATE_room_11"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_11.o"
endseg

beginseg
    name "Z2_PIRATE_room_12"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_12.o"
endseg

beginseg
    name "Z2_PIRATE_room_13"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_13.o"
endseg

beginseg
    name "Z2_PIRATE_room_14"
    compress
    romalign 0x1000
    include "build/baserom/Z2_PIRATE_room_14.o"
endseg

beginseg
    name "Z2_SYATEKI_MORI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SYATEKI_MORI.o"
endseg

beginseg
    name "Z2_SYATEKI_MORI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SYATEKI_MORI_room_00.o"
endseg

beginseg
    name "Z2_SINKAI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SINKAI.o"
endseg

beginseg
    name "Z2_SINKAI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SINKAI_room_00.o"
endseg

beginseg
    name "Z2_YOUSEI_IZUMI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YOUSEI_IZUMI.o"
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YOUSEI_IZUMI_room_00.o"
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YOUSEI_IZUMI_room_01.o"
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YOUSEI_IZUMI_room_02.o"
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YOUSEI_IZUMI_room_03.o"
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YOUSEI_IZUMI_room_04.o"
endseg

beginseg
    name "Z2_KINSTA1"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINSTA1.o"
endseg

beginseg
    name "Z2_KINSTA1_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINSTA1_room_00.o"
endseg

beginseg
    name "Z2_KINSTA1_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINSTA1_room_01.o"
endseg

beginseg
    name "Z2_KINSTA1_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINSTA1_room_02.o"
endseg

beginseg
    name "Z2_KINSTA1_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINSTA1_room_03.o"
endseg

beginseg
    name "Z2_KINSTA1_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINSTA1_room_04.o"
endseg

beginseg
    name "Z2_KINSTA1_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINSTA1_room_05.o"
endseg

beginseg
    name "Z2_KINDAN2"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINDAN2.o"
endseg

beginseg
    name "Z2_KINDAN2_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINDAN2_room_00.o"
endseg

beginseg
    name "Z2_KINDAN2_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINDAN2_room_01.o"
endseg

beginseg
    name "Z2_KINDAN2_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINDAN2_room_02.o"
endseg

beginseg
    name "Z2_KINDAN2_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINDAN2_room_03.o"
endseg

beginseg
    name "Z2_KINDAN2_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINDAN2_room_04.o"
endseg

beginseg
    name "Z2_KINDAN2_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KINDAN2_room_05.o"
endseg

beginseg
    name "Z2_TENMON_DAI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TENMON_DAI.o"
endseg

beginseg
    name "Z2_TENMON_DAI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TENMON_DAI_room_00.o"
endseg

beginseg
    name "Z2_TENMON_DAI_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TENMON_DAI_room_01.o"
endseg

beginseg
    name "Z2_LAST_DEKU"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_DEKU.o"
endseg

beginseg
    name "Z2_LAST_DEKU_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_DEKU_room_00.o"
endseg

beginseg
    name "Z2_LAST_DEKU_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_DEKU_room_01.o"
endseg

beginseg
    name "Z2_22DEKUCITY"
    compress
    romalign 0x1000
    include "build/baserom/Z2_22DEKUCITY.o"
endseg

beginseg
    name "Z2_22DEKUCITY_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_22DEKUCITY_room_00.o"
endseg

beginseg
    name "Z2_22DEKUCITY_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_22DEKUCITY_room_01.o"
endseg

beginseg
    name "Z2_22DEKUCITY_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_22DEKUCITY_room_02.o"
endseg

beginseg
    name "Z2_KAJIYA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KAJIYA.o"
endseg

beginseg
    name "Z2_KAJIYA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KAJIYA_room_00.o"
endseg

beginseg
    name "Z2_00KEIKOKU"
    compress
    romalign 0x1000
    include "build/baserom/Z2_00KEIKOKU.o"
endseg

beginseg
    name "Z2_00KEIKOKU_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_00KEIKOKU_room_00.o"
endseg

beginseg
    name "Z2_POSTHOUSE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_POSTHOUSE.o"
endseg

beginseg
    name "Z2_POSTHOUSE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_POSTHOUSE_room_00.o"
endseg

beginseg
    name "Z2_LABO"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LABO.o"
endseg

beginseg
    name "Z2_LABO_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LABO_room_00.o"
endseg

beginseg
    name "Z2_DANPEI2TEST"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI2TEST.o"
endseg

beginseg
    name "Z2_DANPEI2TEST_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI2TEST_room_00.o"
endseg

beginseg
    name "Z2_DANPEI2TEST_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI2TEST_room_01.o"
endseg

beginseg
    name "Z2_16GORON_HOUSE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_16GORON_HOUSE.o"
endseg

beginseg
    name "Z2_16GORON_HOUSE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_16GORON_HOUSE_room_00.o"
endseg

beginseg
    name "Z2_16GORON_HOUSE_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_16GORON_HOUSE_room_01.o"
endseg

beginseg
    name "Z2_33ZORACITY"
    compress
    romalign 0x1000
    include "build/baserom/Z2_33ZORACITY.o"
endseg

beginseg
    name "Z2_33ZORACITY_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_33ZORACITY_room_00.o"
endseg

beginseg
    name "Z2_8ITEMSHOP"
    compress
    romalign 0x1000
    include "build/baserom/Z2_8ITEMSHOP.o"
endseg

beginseg
    name "Z2_8ITEMSHOP_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_8ITEMSHOP_room_00.o"
endseg

beginseg
    name "Z2_F01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F01.o"
endseg

beginseg
    name "Z2_F01_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F01_room_00.o"
endseg

beginseg
    name "Z2_INISIE_BS"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_BS.o"
endseg

beginseg
    name "Z2_INISIE_BS_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INISIE_BS_room_00.o"
endseg

beginseg
    name "Z2_30GYOSON"
    compress
    romalign 0x1000
    include "build/baserom/Z2_30GYOSON.o"
endseg

beginseg
    name "Z2_30GYOSON_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_30GYOSON_room_00.o"
endseg

beginseg
    name "Z2_31MISAKI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_31MISAKI.o"
endseg

beginseg
    name "Z2_31MISAKI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_31MISAKI_room_00.o"
endseg

beginseg
    name "Z2_TAKARAKUJI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TAKARAKUJI.o"
endseg

beginseg
    name "Z2_TAKARAKUJI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TAKARAKUJI_room_00.o"
endseg

beginseg
    name "Z2_TORIDE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TORIDE.o"
endseg

beginseg
    name "Z2_TORIDE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TORIDE_room_00.o"
endseg

beginseg
    name "Z2_FISHERMAN"
    compress
    romalign 0x1000
    include "build/baserom/Z2_FISHERMAN.o"
endseg

beginseg
    name "Z2_FISHERMAN_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_FISHERMAN_room_00.o"
endseg

beginseg
    name "Z2_GORONSHOP"
    compress
    romalign 0x1000
    include "build/baserom/Z2_GORONSHOP.o"
endseg

beginseg
    name "Z2_GORONSHOP_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_GORONSHOP_room_00.o"
endseg

beginseg
    name "Z2_DEKU_KING"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DEKU_KING.o"
endseg

beginseg
    name "Z2_DEKU_KING_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DEKU_KING_room_00.o"
endseg

beginseg
    name "Z2_LAST_GORON"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_GORON.o"
endseg

beginseg
    name "Z2_LAST_GORON_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_GORON_room_00.o"
endseg

beginseg
    name "Z2_LAST_GORON_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_GORON_room_01.o"
endseg

beginseg
    name "Z2_24KEMONOMITI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_24KEMONOMITI.o"
endseg

beginseg
    name "Z2_24KEMONOMITI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_24KEMONOMITI_room_00.o"
endseg

beginseg
    name "Z2_F01_B"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F01_B.o"
endseg

beginseg
    name "Z2_F01_B_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F01_B_room_00.o"
endseg

beginseg
    name "Z2_F01C"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F01C.o"
endseg

beginseg
    name "Z2_F01C_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F01C_room_00.o"
endseg

beginseg
    name "Z2_BOTI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BOTI.o"
endseg

beginseg
    name "Z2_BOTI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BOTI_room_00.o"
endseg

beginseg
    name "Z2_BOTI_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BOTI_room_01.o"
endseg

beginseg
    name "Z2_HAKUGIN_BS"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_BS.o"
endseg

beginseg
    name "Z2_HAKUGIN_BS_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_HAKUGIN_BS_room_00.o"
endseg

beginseg
    name "Z2_20SICHITAI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_20SICHITAI.o"
endseg

beginseg
    name "Z2_20SICHITAI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_20SICHITAI_room_00.o"
endseg

beginseg
    name "Z2_20SICHITAI_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_20SICHITAI_room_01.o"
endseg

beginseg
    name "Z2_20SICHITAI_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_20SICHITAI_room_02.o"
endseg

beginseg
    name "Z2_21MITURINMAE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_21MITURINMAE.o"
endseg

beginseg
    name "Z2_21MITURINMAE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_21MITURINMAE_room_00.o"
endseg

beginseg
    name "Z2_LAST_ZORA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_ZORA.o"
endseg

beginseg
    name "Z2_LAST_ZORA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_ZORA_room_00.o"
endseg

beginseg
    name "Z2_11GORONNOSATO2"
    compress
    romalign 0x1000
    include "build/baserom/Z2_11GORONNOSATO2.o"
endseg

beginseg
    name "Z2_11GORONNOSATO2_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_11GORONNOSATO2_room_00.o"
endseg

beginseg
    name "Z2_11GORONNOSATO2_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_11GORONNOSATO2_room_01.o"
endseg

beginseg
    name "Z2_SEA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA.o"
endseg

beginseg
    name "Z2_SEA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_00.o"
endseg

beginseg
    name "Z2_SEA_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_01.o"
endseg

beginseg
    name "Z2_SEA_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_02.o"
endseg

beginseg
    name "Z2_SEA_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_03.o"
endseg

beginseg
    name "Z2_SEA_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_04.o"
endseg

beginseg
    name "Z2_SEA_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_05.o"
endseg

beginseg
    name "Z2_SEA_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_06.o"
endseg

beginseg
    name "Z2_SEA_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_07.o"
endseg

beginseg
    name "Z2_SEA_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_08.o"
endseg

beginseg
    name "Z2_SEA_room_09"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_09.o"
endseg

beginseg
    name "Z2_SEA_room_10"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_10.o"
endseg

beginseg
    name "Z2_SEA_room_11"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_11.o"
endseg

beginseg
    name "Z2_SEA_room_12"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_12.o"
endseg

beginseg
    name "Z2_SEA_room_13"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_13.o"
endseg

beginseg
    name "Z2_SEA_room_14"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_14.o"
endseg

beginseg
    name "Z2_SEA_room_15"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_room_15.o"
endseg

beginseg
    name "Z2_35TAKI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_35TAKI.o"
endseg

beginseg
    name "Z2_35TAKI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_35TAKI_room_00.o"
endseg

beginseg
    name "Z2_REDEAD"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD.o"
endseg

beginseg
    name "Z2_REDEAD_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_00.o"
endseg

beginseg
    name "Z2_REDEAD_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_01.o"
endseg

beginseg
    name "Z2_REDEAD_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_02.o"
endseg

beginseg
    name "Z2_REDEAD_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_03.o"
endseg

beginseg
    name "Z2_REDEAD_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_04.o"
endseg

beginseg
    name "Z2_REDEAD_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_05.o"
endseg

beginseg
    name "Z2_REDEAD_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_06.o"
endseg

beginseg
    name "Z2_REDEAD_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_07.o"
endseg

beginseg
    name "Z2_REDEAD_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_08.o"
endseg

beginseg
    name "Z2_REDEAD_room_09"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_09.o"
endseg

beginseg
    name "Z2_REDEAD_room_10"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_10.o"
endseg

beginseg
    name "Z2_REDEAD_room_11"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_11.o"
endseg

beginseg
    name "Z2_REDEAD_room_12"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_12.o"
endseg

beginseg
    name "Z2_REDEAD_room_13"
    compress
    romalign 0x1000
    include "build/baserom/Z2_REDEAD_room_13.o"
endseg

beginseg
    name "Z2_BANDROOM"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BANDROOM.o"
endseg

beginseg
    name "Z2_BANDROOM_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BANDROOM_room_00.o"
endseg

beginseg
    name "Z2_BANDROOM_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BANDROOM_room_01.o"
endseg

beginseg
    name "Z2_BANDROOM_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BANDROOM_room_02.o"
endseg

beginseg
    name "Z2_BANDROOM_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BANDROOM_room_03.o"
endseg

beginseg
    name "Z2_BANDROOM_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BANDROOM_room_04.o"
endseg

beginseg
    name "Z2_11GORONNOSATO"
    compress
    romalign 0x1000
    include "build/baserom/Z2_11GORONNOSATO.o"
endseg

beginseg
    name "Z2_11GORONNOSATO_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_11GORONNOSATO_room_00.o"
endseg

beginseg
    name "Z2_11GORONNOSATO_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_11GORONNOSATO_room_01.o"
endseg

beginseg
    name "Z2_GORON_HAKA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_GORON_HAKA.o"
endseg

beginseg
    name "Z2_GORON_HAKA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_GORON_HAKA_room_00.o"
endseg

beginseg
    name "Z2_SECOM"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SECOM.o"
endseg

beginseg
    name "Z2_SECOM_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SECOM_room_00.o"
endseg

beginseg
    name "Z2_SECOM_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SECOM_room_01.o"
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_10YUKIYAMANOMURA.o"
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_10YUKIYAMANOMURA_room_00.o"
endseg

beginseg
    name "Z2_TOUGITES"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TOUGITES.o"
endseg

beginseg
    name "Z2_TOUGITES_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TOUGITES_room_00.o"
endseg

beginseg
    name "Z2_DANPEI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI.o"
endseg

beginseg
    name "Z2_DANPEI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI_room_00.o"
endseg

beginseg
    name "Z2_DANPEI_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI_room_01.o"
endseg

beginseg
    name "Z2_DANPEI_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI_room_02.o"
endseg

beginseg
    name "Z2_DANPEI_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI_room_03.o"
endseg

beginseg
    name "Z2_DANPEI_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI_room_04.o"
endseg

beginseg
    name "Z2_DANPEI_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI_room_05.o"
endseg

beginseg
    name "Z2_DANPEI_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI_room_06.o"
endseg

beginseg
    name "Z2_DANPEI_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI_room_07.o"
endseg

beginseg
    name "Z2_DANPEI_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DANPEI_room_08.o"
endseg

beginseg
    name "Z2_IKANAMAE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKANAMAE.o"
endseg

beginseg
    name "Z2_IKANAMAE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKANAMAE_room_00.o"
endseg

beginseg
    name "Z2_DOUJOU"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DOUJOU.o"
endseg

beginseg
    name "Z2_DOUJOU_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_DOUJOU_room_00.o"
endseg

beginseg
    name "Z2_MUSICHOUSE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MUSICHOUSE.o"
endseg

beginseg
    name "Z2_MUSICHOUSE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MUSICHOUSE_room_00.o"
endseg

beginseg
    name "Z2_IKNINSIDE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKNINSIDE.o"
endseg

beginseg
    name "Z2_IKNINSIDE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKNINSIDE_room_00.o"
endseg

beginseg
    name "Z2_IKNINSIDE_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_IKNINSIDE_room_01.o"
endseg

beginseg
    name "Z2_MAP_SHOP"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MAP_SHOP.o"
endseg

beginseg
    name "Z2_MAP_SHOP_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_MAP_SHOP_room_00.o"
endseg

beginseg
    name "Z2_F40"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F40.o"
endseg

beginseg
    name "Z2_F40_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F40_room_00.o"
endseg

beginseg
    name "Z2_F41"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F41.o"
endseg

beginseg
    name "Z2_F41_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_F41_room_00.o"
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA2"
    compress
    romalign 0x1000
    include "build/baserom/Z2_10YUKIYAMANOMURA2.o"
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA2_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_10YUKIYAMANOMURA2_room_00.o"
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA2_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_10YUKIYAMANOMURA2_room_01.o"
endseg

beginseg
    name "Z2_14YUKIDAMANOMITI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_14YUKIDAMANOMITI.o"
endseg

beginseg
    name "Z2_14YUKIDAMANOMITI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_14YUKIDAMANOMITI_room_00.o"
endseg

beginseg
    name "Z2_12HAKUGINMAE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_12HAKUGINMAE.o"
endseg

beginseg
    name "Z2_12HAKUGINMAE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_12HAKUGINMAE_room_00.o"
endseg

beginseg
    name "Z2_17SETUGEN"
    compress
    romalign 0x1000
    include "build/baserom/Z2_17SETUGEN.o"
endseg

beginseg
    name "Z2_17SETUGEN_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_17SETUGEN_room_00.o"
endseg

beginseg
    name "Z2_17SETUGEN2"
    compress
    romalign 0x1000
    include "build/baserom/Z2_17SETUGEN2.o"
endseg

beginseg
    name "Z2_17SETUGEN2_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_17SETUGEN2_room_00.o"
endseg

beginseg
    name "Z2_SEA_BS"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_BS.o"
endseg

beginseg
    name "Z2_SEA_BS_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SEA_BS_room_00.o"
endseg

beginseg
    name "Z2_RANDOM"
    compress
    romalign 0x1000
    include "build/baserom/Z2_RANDOM.o"
endseg

beginseg
    name "Z2_RANDOM_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_RANDOM_room_00.o"
endseg

beginseg
    name "Z2_RANDOM_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_RANDOM_room_01.o"
endseg

beginseg
    name "Z2_RANDOM_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_RANDOM_room_02.o"
endseg

beginseg
    name "Z2_RANDOM_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_RANDOM_room_03.o"
endseg

beginseg
    name "Z2_RANDOM_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_RANDOM_room_04.o"
endseg

beginseg
    name "Z2_RANDOM_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_RANDOM_room_05.o"
endseg

beginseg
    name "Z2_YADOYA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YADOYA.o"
endseg

beginseg
    name "Z2_YADOYA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YADOYA_room_00.o"
endseg

beginseg
    name "Z2_YADOYA_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YADOYA_room_01.o"
endseg

beginseg
    name "Z2_YADOYA_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YADOYA_room_02.o"
endseg

beginseg
    name "Z2_YADOYA_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YADOYA_room_03.o"
endseg

beginseg
    name "Z2_YADOYA_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_YADOYA_room_04.o"
endseg

beginseg
    name "Z2_KONPEKI_ENT"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KONPEKI_ENT.o"
endseg

beginseg
    name "Z2_KONPEKI_ENT_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KONPEKI_ENT_room_00.o"
endseg

beginseg
    name "Z2_INSIDETOWER"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INSIDETOWER.o"
endseg

beginseg
    name "Z2_INSIDETOWER_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INSIDETOWER_room_00.o"
endseg

beginseg
    name "Z2_INSIDETOWER_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_INSIDETOWER_room_01.o"
endseg

beginseg
    name "Z2_26SARUNOMORI"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI.o"
endseg

beginseg
    name "Z2_26SARUNOMORI_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI_room_00.o"
endseg

beginseg
    name "Z2_26SARUNOMORI_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI_room_01.o"
endseg

beginseg
    name "Z2_26SARUNOMORI_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI_room_02.o"
endseg

beginseg
    name "Z2_26SARUNOMORI_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI_room_03.o"
endseg

beginseg
    name "Z2_26SARUNOMORI_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI_room_04.o"
endseg

beginseg
    name "Z2_26SARUNOMORI_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI_room_05.o"
endseg

beginseg
    name "Z2_26SARUNOMORI_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI_room_06.o"
endseg

beginseg
    name "Z2_26SARUNOMORI_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI_room_07.o"
endseg

beginseg
    name "Z2_26SARUNOMORI_room_08"
    compress
    romalign 0x1000
    include "build/baserom/Z2_26SARUNOMORI_room_08.o"
endseg

beginseg
    name "Z2_LOST_WOODS"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LOST_WOODS.o"
endseg

beginseg
    name "Z2_LOST_WOODS_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LOST_WOODS_room_00.o"
endseg

beginseg
    name "Z2_LOST_WOODS_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LOST_WOODS_room_01.o"
endseg

beginseg
    name "Z2_LOST_WOODS_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LOST_WOODS_room_02.o"
endseg

beginseg
    name "Z2_LAST_LINK"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_LINK.o"
endseg

beginseg
    name "Z2_LAST_LINK_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_LINK_room_00.o"
endseg

beginseg
    name "Z2_LAST_LINK_room_01"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_LINK_room_01.o"
endseg

beginseg
    name "Z2_LAST_LINK_room_02"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_LINK_room_02.o"
endseg

beginseg
    name "Z2_LAST_LINK_room_03"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_LINK_room_03.o"
endseg

beginseg
    name "Z2_LAST_LINK_room_04"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_LINK_room_04.o"
endseg

beginseg
    name "Z2_LAST_LINK_room_05"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_LINK_room_05.o"
endseg

beginseg
    name "Z2_LAST_LINK_room_06"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_LINK_room_06.o"
endseg

beginseg
    name "Z2_LAST_LINK_room_07"
    compress
    romalign 0x1000
    include "build/baserom/Z2_LAST_LINK_room_07.o"
endseg

beginseg
    name "Z2_SOUGEN"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SOUGEN.o"
endseg

beginseg
    name "Z2_SOUGEN_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_SOUGEN_room_00.o"
endseg

beginseg
    name "Z2_BOMYA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BOMYA.o"
endseg

beginseg
    name "Z2_BOMYA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BOMYA_room_00.o"
endseg

beginseg
    name "Z2_KYOJINNOMA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KYOJINNOMA.o"
endseg

beginseg
    name "Z2_KYOJINNOMA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KYOJINNOMA_room_00.o"
endseg

beginseg
    name "Z2_KOEPONARACE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KOEPONARACE.o"
endseg

beginseg
    name "Z2_KOEPONARACE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_KOEPONARACE_room_00.o"
endseg

beginseg
    name "Z2_GORONRACE"
    compress
    romalign 0x1000
    include "build/baserom/Z2_GORONRACE.o"
endseg

beginseg
    name "Z2_GORONRACE_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_GORONRACE_room_00.o"
endseg

beginseg
    name "Z2_TOWN"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TOWN.o"
endseg

beginseg
    name "Z2_TOWN_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_TOWN_room_00.o"
endseg

beginseg
    name "Z2_ICHIBA"
    compress
    romalign 0x1000
    include "build/baserom/Z2_ICHIBA.o"
endseg

beginseg
    name "Z2_ICHIBA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_ICHIBA_room_00.o"
endseg

beginseg
    name "Z2_BACKTOWN"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BACKTOWN.o"
endseg

beginseg
    name "Z2_BACKTOWN_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_BACKTOWN_room_00.o"
endseg

beginseg
    name "Z2_CLOCKTOWER"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CLOCKTOWER.o"
endseg

beginseg
    name "Z2_CLOCKTOWER_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_CLOCKTOWER_room_00.o"
endseg

beginseg
    name "Z2_ALLEY"
    compress
    romalign 0x1000
    include "build/baserom/Z2_ALLEY.o"
endseg

beginseg
    name "Z2_ALLEY_room_00"
    compress
    romalign 0x1000
    include "build/baserom/Z2_ALLEY_room_00.o"
endseg

beginseg
    name "SPOT00"
    compress
    romalign 0x1000
    include "build/baserom/SPOT00.o"
endseg

beginseg
    name "SPOT00_room_00"
    compress
    romalign 0x1000
    include "build/baserom/SPOT00_room_00.o"
endseg

beginseg
    name "KAKUSIANA"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA.o"
endseg

beginseg
    name "KAKUSIANA_room_00"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_00.o"
endseg

beginseg
    name "KAKUSIANA_room_01"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_01.o"
endseg

beginseg
    name "KAKUSIANA_room_02"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_02.o"
endseg

beginseg
    name "KAKUSIANA_room_03"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_03.o"
endseg

beginseg
    name "KAKUSIANA_room_04"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_04.o"
endseg

beginseg
    name "KAKUSIANA_room_05"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_05.o"
endseg

beginseg
    name "KAKUSIANA_room_06"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_06.o"
endseg

beginseg
    name "KAKUSIANA_room_07"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_07.o"
endseg

beginseg
    name "KAKUSIANA_room_08"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_08.o"
endseg

beginseg
    name "KAKUSIANA_room_09"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_09.o"
endseg

beginseg
    name "KAKUSIANA_room_10"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_10.o"
endseg

beginseg
    name "KAKUSIANA_room_11"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_11.o"
endseg

beginseg
    name "KAKUSIANA_room_12"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_12.o"
endseg

beginseg
    name "KAKUSIANA_room_13"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_13.o"
endseg

beginseg
    name "KAKUSIANA_room_14"
    compress
    romalign 0x1000
    include "build/baserom/KAKUSIANA_room_14.o"
endseg

beginseg
    name "bump_texture_static"
    compress
    romalign 0x1000
    include "build/baserom/bump_texture_static.o"
endseg

beginseg
    name "02EDB010_02EDB000"
    romalign 0x1000
    include "build/baserom/02EDB010_02EDB000.o"
endseg

beginseg
    name "02EDC010_02EDC000"
    romalign 0x1000
    include "build/baserom/02EDC010_02EDC000.o"
endseg

beginseg
    name "02EDD010_02EDD000"
    romalign 0x1000
    include "build/baserom/02EDD010_02EDD000.o"
endseg

beginseg
    name "02EDE010_02EDE000"
    romalign 0x1000
    include "build/baserom/02EDE010_02EDE000.o"
endseg

beginseg
    name "02EDF010_02EDF000"
    romalign 0x1000
    include "build/baserom/02EDF010_02EDF000.o"
endseg

beginseg
    name "02EE0010_02EE0000"
    romalign 0x1000
    include "build/baserom/02EE0010_02EE0000.o"
endseg

beginseg
    name "02EE1010_02EE1000"
    romalign 0x1000
    include "build/baserom/02EE1010_02EE1000.o"
endseg

beginseg
    name "02EE2010_02EE2000"
    romalign 0x1000
    include "build/baserom/02EE2010_02EE2000.o"
endseg

beginseg
    name "02EE3010_02EE3000"
    romalign 0x1000
    include "build/baserom/02EE3010_02EE3000.o"
endseg

beginseg
    name "02EE4010_02EE4000"
    romalign 0x1000
    include "build/baserom/02EE4010_02EE4000.o"
endseg

beginseg
    name "02EE5010_02EE5000"
    romalign 0x1000
    include "build/baserom/02EE5010_02EE5000.o"
endseg

beginseg
    name "02EE6010_02EE6000"
    romalign 0x1000
    include "build/baserom/02EE6010_02EE6000.o"
endseg

beginseg
    name "02EE7040_02EE7000"
    romalign 0x1000
    include "build/baserom/02EE7040_02EE7000.o"
endseg
