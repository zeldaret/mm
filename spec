/*
 * ROM spec file
 */

beginseg
    name "makerom"
    address 0x8007F000
    include "build/asm/makerom/rom_header.o"
    include "build/asm/makerom/ipl3.o"
    include "build/asm/makerom/entry.o"
endseg

beginseg
    name "boot"
    address 0x80080060
    include "build/src/boot/boot_main.o"
    include "build/data/boot/rspboot.data.o"
    include "build/src/boot/idle.o"
    include "build/src/boot/viconfig.o"
    include "build/data/boot/viconfig.data.o"
    include "build/src/boot/z_std_dma.o"
    include "build/src/boot/yaz0.o"
    include "build/src/boot/irqmgr.o"
    include "build/src/boot/CIC6105.o"
    include "build/src/boot/syncprintf.o"
    include "build/src/boot/fault.o"
    include "build/src/boot/fault_drawer.o"
    include "build/src/boot/O2/rcp_utils.o"
    include "build/src/boot/O2/loadfragment.o"
    include "build/src/boot/O2/loadfragment2.o"
    include "build/src/boot/O2/padutils.o"
    include "build/src/boot/O2/stackcheck.o"
    include "build/src/boot/O2/gfxprint.o"
    include "build/data/boot/gfxprint.data.o"
    include "build/src/boot/O2/mtxuty-cvt.o"
    include "build/src/boot/O2/debug.o"
    include "build/src/boot/O2/system_heap.o"
    include "build/src/boot/O2/padsetup.o"
    include "build/src/boot/O2/math64.o"
    include "build/asm/boot/fp.text.o"
    include "build/data/boot/fp.data.o"
    include "build/src/boot/O2/system_malloc.o"
    include "build/src/boot/O2/rand.o"
    include "build/src/boot/O2/__osMalloc.o"
    include "build/src/libultra/rmon/sprintf.o"
    include "build/src/boot/O2/printutils.o"
    include "build/src/boot/O2/sleep.o"
    include "build/asm/boot/setcause.text.o"
    include "build/src/libultra/os/sendmesg.o"
    include "build/src/libultra/io/pfsfreeblocks.o"
    include "build/src/libultra/os/viextend.o"
    include "build/src/libultra/os/stopthread.o"
    include "build/src/libultra/os/recvmesg.o"
    include "build/asm/boot/setintmask.text.o"
    include "build/data/boot/setintmask.rodata.o"
    include "build/asm/boot/getintmask.text.o"
    include "build/src/libultra/voice/voicesetword.o"
    include "build/src/libultra/io/osViModeNtscHpf1.o"
    include "build/src/libultra/io/osViModePalLan1.o"
    include "build/asm/boot/guScale.text.o"
    include "build/src/libultra/gu/sinf.o"
    include "build/src/libultra/gu/sins.o"
    include "build/src/libultra/io/sptask.o"
    include "build/src/libultra/libc/ll.o"
    include "build/asm/boot/exceptasm.text.o"
    include "build/data/boot/exceptasm.data.o"
    include "build/data/boot/exceptasm.rodata.o"
    include "build/src/libultra/os/thread.o"
    include "build/src/libultra/os/destroythread.o"
    include "build/src/libultra/voice/voicecheckresult.o"
    include "build/asm/boot/bzero.text.o"
    include "build/src/libultra/io/motor.o"
    include "build/src/libultra/io/siacs.o"
    include "build/src/libultra/io/controller.o"
    include "build/src/libultra/os/createthread.o"
    include "build/src/libultra/io/contreaddata.o"
    include "build/src/libultra/voice/voicegetreaddata.o"
    include "build/src/libultra/os/virtualtophysical.o"
    include "build/asm/boot/getsr.text.o"
    include "build/asm/boot/setsr.text.o"
    include "build/asm/boot/writebackdcache.text.o"
    include "build/src/libultra/os/initialize.o"
    include "build/src/libultra/os/threadsave.o"
    pad_text
    pad_text
    pad_text
    pad_text
    pad_text
    pad_text
    include "build/src/libultra/io/vigetnextframebuf.o"
    include "build/src/libultra/gu/perspective.o"
    include "build/src/libultra/io/sprawdma.o"
    include "build/src/libultra/io/sirawdma.o"
    include "build/src/libultra/io/epilinkhandle.o"
    include "build/src/libultra/io/viblack.o"
    include "build/src/libultra/io/sirawread.o"
    include "build/src/libultra/os/getthreadid.o"
    include "build/src/libultra/io/sptaskyield.o"
    include "build/src/libultra/io/pfsreadwritefile.o"
    include "build/src/libultra/io/pfsgetstatus.o"
    pad_text
    include "build/asm/boot/guMtxIdentF.text.o"
    include "build/src/libultra/io/visetmode.o"
    include "build/asm/boot/getconfig.text.o"
    include "build/asm/boot/setconfig.text.o"
    include "build/src/libultra/gu/lookat.o"
    include "build/src/libultra/io/pfsallocatefile.o"
    include "build/src/libultra/os/stoptimer.o"
    include "build/asm/boot/probetlb.text.o"
    include "build/src/libultra/io/pimgr.o"
    include "build/data/boot/pimgr.data.o"
    include "build/src/libultra/io/piacs.o"
    pad_text
    include "build/src/libultra/io/devmgr.o"
    include "build/src/libultra/io/pirawdma.o"
    include "build/src/libultra/io/contpfs.o"
    include "build/asm/boot/getcount.text.o"
    pad_text
    include "build/asm/boot/guMtxL2F.text.o"
    include "build/src/libultra/os/getmemsize.o"
    include "build/src/libultra/io/pfssearchfile.o"
    include "build/src/libultra/os/seteventmesg.o"
    include "build/src/libultra/gu/sqrtf.o"
    include "build/src/libultra/os/afterprenmi.o"
    include "build/src/libultra/io/contquery.o"
    include "build/src/libultra/gu/lookathil.o"
    include "build/src/libultra/rmon/xprintf.o"
    include "build/src/libultra/voice/voicecleardictionary.o"
    include "build/asm/boot/unmaptlball.text.o"
    include "build/src/libultra/io/epidma.o"
    include "build/src/libultra/voice/voicecontread2.o"
    include "build/src/libultra/voice/voicecrc.o"
    include "build/src/libultra/libc/string.o"
    include "build/src/libultra/os/createmesgqueue.o"
    include "build/asm/boot/invalicache.text.o"
    include "build/asm/boot/invaldcache.text.o"
    include "build/src/libultra/os/timerintr.o"
    include "build/src/libultra/voice/voicecontread36.o"
    include "build/src/libultra/io/sp.o"
    include "build/src/libultra/io/si.o"
    include "build/asm/boot/guMtxIdent.text.o"
    include "build/src/libultra/os/jammesg.o"
    include "build/src/libultra/os/setthreadpri.o"
    include "build/src/libultra/os/getthreadpri.o"
    include "build/src/libultra/io/epirawread.o"
    include "build/src/libultra/io/viswapbuf.o"
    include "build/src/libultra/gu/position.o"
    include "build/src/libultra/io/epirawdma.o"
    include "build/src/libultra/io/sptaskyielded.o"
    include "build/asm/boot/bcmp.text.o"
    include "build/src/libultra/os/gettime.o"
    include "build/src/libultra/gu/rotate.o"
    include "build/src/libultra/os/setglobalintmask.o"
    include "build/src/libultra/voice/voiceinit.o"
    include "build/src/libultra/io/contchannelreset.o"
    include "build/src/libultra/voice/voicesetadconverter.o"
    include "build/src/libultra/io/aisetfreq.o"
    include "build/src/libultra/io/contramread.o"
    include "build/src/libultra/voice/voicecontwrite20.o"
    include "build/src/libultra/io/crc.o"
    include "build/src/libultra/os/getactivequeue.o"
    include "build/asm/boot/normalize.text.o"
    include "build/asm/boot/setcompare.text.o"
    include "build/asm/boot/getcompare.text.o"
    include "build/src/libultra/io/dpgetstat.o"
    include "build/src/libultra/io/dpsetstat.o"
    include "build/asm/boot/bcopy.text.o"
    include "build/src/libultra/os/resetglobalintmask.o"
    include "build/src/libultra/io/pfsdeletefile.o"
    include "build/src/libultra/gu/ortho.o"
    include "build/asm/boot/interrupt.text.o"
    include "build/src/libultra/io/osViModeNtscLan1.o"
    include "build/src/libultra/io/osViModeMpalLan1.o"
    include "build/src/libultra/io/vi.o"
    include "build/src/libultra/io/viswapcontext.o"
    include "build/src/libultra/io/pigetcmdq.o"
    include "build/src/libultra/gu/cosf.o"
    include "build/src/libultra/io/epiread.o"
    include "build/src/libultra/io/visetspecial.o"
    include "build/src/libultra/gu/coss.o"
    include "build/src/libultra/os/settime.o"
    include "build/src/libultra/voice/voicestopread.o"
    include "build/src/libultra/gu/visetevent.o"
    include "build/src/libultra/io/pfsisplug.o"
    include "build/src/libultra/voice/voicegetstatus.o"
    include "build/src/libultra/io/cartrominit.o"
    include "build/src/libultra/gu/guS2DInitBg.o"
    include "build/data/boot/guS2DInitBg.data.o"
    include "build/src/libultra/io/pfsselectbank.o"
    include "build/src/libultra/io/contsetch.o"
    include "build/asm/boot/setfpccsr.text.o"
    include "build/asm/boot/getfpccsr.text.o"
    include "build/src/libultra/io/pfsfilestate.o"
    include "build/src/libultra/io/pfsinitpak.o"
    include "build/src/libultra/io/pfschecker.o"
    include "build/src/libultra/io/aigetlen.o"
    include "build/src/libultra/io/epiwrite.o"
    include "build/asm/boot/maptlbrdb.text.o"
    include "build/src/libultra/os/yieldthread.o"
    pad_text
    include "build/asm/boot/guTranslate.text.o"
    include "build/asm/boot/getcause.text.o"
    include "build/src/libultra/io/contramwrite.o"
    include "build/src/libultra/io/epirawwrite.o"
    include "build/src/libultra/os/settimer.o"
    include "build/data/boot/__libm_qnan_f.rodata.o"
    include "build/src/libultra/rmon/xldtob.o"
    include "build/src/libultra/libc/ldiv.o"
    include "build/src/libultra/rmon/xlitob.o"
    include "build/src/libultra/io/sirawwrite.o"
    include "build/src/libultra/io/spgetstat.o"
    include "build/src/libultra/io/spsetstat.o"
    pad_text
    include "build/src/libultra/io/vimgr.o"
    include "build/src/libultra/io/vigetcurrcontext.o"
    include "build/asm/boot/writebackdcacheall.text.o"
    include "build/src/libultra/os/getcurrfaultthread.o"
    include "build/src/libultra/voice/voicemaskdictionary.o"
    pad_text
    include "build/asm/boot/guMtxF2L.text.o"
    include "build/src/libultra/os/startthread.o"
    include "build/src/libultra/io/visetyscale.o"
    include "build/src/libultra/io/visetxscale.o"
    include "build/src/libultra/libc/llcvt.o"
    include "build/src/libultra/voice/voicecheckword.o"
    include "build/src/libultra/voice/voicecontrolgain.o"
    include "build/src/libultra/voice/voicestartreaddata.o"
    include "build/src/libultra/io/vigetcurrframebuf.o"
    include "build/src/libultra/io/spsetpc.o"
    include "build/src/libultra/voice/voicecontwrite4.o"
    include "build/src/libultra/os/gethwinterrupt.o"
    include "build/src/libultra/os/sethwinterrupt.o"
    include "build/asm/boot/getwatchlo.text.o"
    include "build/asm/boot/setwatchlo.text.o"
    include "build/src/boot/O2/fmodf.o"
    include "build/src/boot/O2/__osMemset.o"
    include "build/src/boot/O2/__osStrcmp.o"
    include "build/src/boot/O2/__osStrcpy.o"
    include "build/src/boot/O2/__osMemcpy.o"
    include "build/src/boot/build.o"
endseg

beginseg
    name "dmadata"
    include "build/asm/dmadata/dmadata.o"
endseg

beginseg
    name "Audiobank"
    address 0x10 # fake address to avoid map lookup inaccuracies
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
    include "build/assets/misc/link_animetion/link_animetion.o"
    number 7
endseg

beginseg
    name "icon_item_static_syms"
    romalign 0x1000
    include "build/assets/archives/icon_item_static/icon_item_static_yar.symbols.o"
    number 8
endseg

beginseg
    name "icon_item_24_static_syms"
    romalign 0x1000
    include "build/assets/archives/icon_item_24_static/icon_item_24_static_yar.symbols.o"
    number 9
endseg

beginseg
    name "icon_item_field_static"
    compress
    romalign 0x1000
    include "build/assets/interface/icon_item_field_static/icon_item_field_static.o"
    number 12
endseg

beginseg
    name "icon_item_dungeon_static"
    compress
    romalign 0x1000
    include "build/assets/interface/icon_item_dungeon_static/icon_item_dungeon_static.o"
    number 12
endseg

beginseg
    name "icon_item_gameover_static"
    compress
    romalign 0x1000
    include "build/assets/interface/icon_item_gameover_static/icon_item_gameover_static.o"
    number 12
endseg

beginseg
    name "icon_item_jpn_static"
    compress
    romalign 0x1000
    include "build/assets/interface/icon_item_jpn_static/icon_item_jpn_static.o"
    number 13
endseg

beginseg
    name "icon_item_vtx_static"
    compress
    romalign 0x1000
    include "build/assets/interface/icon_item_vtx_static/icon_item_vtx_static.o"
    number 11
endseg

beginseg
    name "map_i_static"
    include "build/assets/archives/map_i_static/map_i_static.yar.o"
endseg

beginseg
    name "map_grand_static"
    include "build/assets/archives/map_grand_static/map_grand_static.yar.o"
endseg

beginseg
    name "item_name_static"
    include "build/assets/archives/item_name_static/item_name_static.yar.o"
endseg

beginseg
    name "map_name_static"
    include "build/assets/archives/map_name_static/map_name_static.yar.o"
endseg

beginseg
    name "icon_item_static_yar"
    include "build/assets/archives/icon_item_static/icon_item_static_yar.yar.o"
    number 8
endseg

beginseg
    name "icon_item_24_static_yar"
    include "build/assets/archives/icon_item_24_static/icon_item_24_static_yar.yar.o"
    number 9
endseg

beginseg
    name "schedule_dma_static_syms"
    include "build/assets/archives/schedule_dma_static/schedule_dma_static_yar.symbols.o"
    number 7
endseg

beginseg
    name "schedule_dma_static_yar"
    increment 0x1000
    include "build/assets/archives/schedule_dma_static/schedule_dma_static_yar.yar.o"
    number 7
endseg

beginseg
    name "schedule_static"
    compress
    include "build/assets/interface/schedule_static/schedule_static.o"
    number 8
endseg

beginseg
    name "story_static"
    compress
    romalign 0x1000
    include "build/assets/misc/story_static/story_static.o"
    number 7
endseg

beginseg
    name "do_action_static"
    romalign 0x1000
    include "build/assets/interface/do_action_static/do_action_static.o"
    number 9
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
    after "dmadata"
    include "build/data/code/aspMain.data.o"
    include "build/data/code/gspS2DEX2.fifo.data.o"
    include "build/data/code/njpgdspMain.data.o"
    include "build/src/code/z_en_a_keep.o"
    include "build/src/code/z_en_item00.o"
    include "build/src/code/z_eff_blure.o"
    include "build/src/code/z_eff_shield_particle.o"
    include "build/src/code/z_eff_spark.o"
    include "build/src/code/z_eff_ss_dead.o"
    include "build/src/code/z_eff_tire_mark.o"
    include "build/src/code/z_effect.o"
    include "build/src/code/z_effect_soft_sprite.o"
    include "build/src/code/z_effect_soft_sprite_old_init.o"
    include "build/src/code/z_effect_soft_sprite_dlftbls.o"
    include "build/src/code/flg_set.o"
    include "build/src/code/z_DLF.o"
    include "build/src/code/z_actor.o"
    include "build/src/code/z_actor_dlftbls.o"
    include "build/src/code/z_bgcheck.o"
    include "build/src/code/z_bg_collect.o"
    include "build/src/code/z_bg_item.o"
    include "build/src/code/z_camera.o"
    include "build/src/code/z_collision_btltbls.o"
    pad_text
    include "build/src/code/z_collision_check.o"
    include "build/src/code/code_800E8EA0.o"
    include "build/src/code/z_common_data.o"
    include "build/src/code/z_debug.o"
    include "build/src/code/z_debug_display.o"
    include "build/src/code/z_debug_mode.o"
    include "build/src/code/z_demo.o"
    include "build/src/code/z_draw.o"
    include "build/src/code/z_eff_footmark.o"
    include "build/src/code/z_sound_source.o"
    include "build/src/code/z_elf_message.o"
    include "build/src/code/z_en_hy_code.o"
    include "build/src/code/z_face_reaction.o"
    include "build/src/code/z_env_flags.o"
    include "build/src/code/z_eventmgr.o"
    include "build/src/code/z_fcurve_data.o"
    include "build/src/code/z_fcurve_data_skelanime.o"
    include "build/src/code/z_fireobj.o"
    include "build/src/code/z_game_dlftbls.o"
    include "build/src/code/z_horse.o"
    include "build/src/code/z_jpeg.o"
    include "build/src/code/z_kaleido_setup.o"
    include "build/src/code/z_kanfont.o"
    include "build/src/code/z_kankyo.o"
    include "build/src/code/z_lib.o"
    include "build/src/code/z_lifemeter.o"
    include "build/src/code/z_lights.o"
    include "build/src/code/z_malloc.o"
    include "build/src/code/z_map_disp.o"
    include "build/data/code/z_map_disp.data.o"
    include "build/data/code/z_map_disp.bss.o"
    include "build/src/code/z_map_data.o"
    include "build/src/code/z_map_exp.o"
    include "build/src/code/z_msgevent.o"
    include "build/data/code/z_msgevent.data.o"
    include "build/src/code/z_nmi_buff.o"
    include "build/src/code/code_8010C1B0.o"
    include "build/src/code/z_olib.o"
    pad_text
    include "build/src/code/z_parameter.o"
    include "build/src/code/z_path.o"
    include "build/src/code/z_pause.o"
    include "build/src/code/z_player_lib.o"
    include "build/src/code/z_prenmi.o"
    include "build/src/code/z_quake.o"
    include "build/src/code/z_rcp.o"
    pad_text
    include "build/src/code/z_room.o"
    include "build/src/code/code_8012EC80.o"
    pad_text
    include "build/data/code/code_801C2410.data.o"
    include "build/src/code/z_scene.o"
    include "build/src/code/object_table.o"
    include "build/src/code/z_scene_proc.o"
    include "build/src/code/z_scene_table.o"
    include "build/src/code/z_schedule.o"
    include "build/src/code/z_skelanime.o"
    include "build/src/code/z_skin.o"
    include "build/src/code/z_skin_awb.o"
    include "build/src/code/z_skin_matrix.o"
    include "build/src/code/z_snap.o"
    include "build/src/code/z_sub_s.o"
    include "build/data/code/code_801DE890.rodata.o"
    include "build/src/code/z_rumble.o"
    include "build/src/code/z_view.o"
    include "build/src/code/z_vimode.o"
    include "build/src/code/z_viscvg.o"
    include "build/src/code/code_80140E80.o"
    include "build/src/code/z_vismono.o"
    include "build/src/code/z_viszbuf.o"
    include "build/src/code/z_vr_box.o"
    include "build/src/code/z_vr_box_draw.o"
    include "build/src/code/z_sram_NES.o"
    include "build/src/code/z_message.o"
    include "build/src/code/z_message_nes.o"
    include "build/src/code/z_message_staff.o"
    include "build/src/code/z_player_call.o"
    include "build/src/code/z_shrink_window.o"
    include "build/src/code/cutscene_camera.o"
    include "build/data/code/cutscene_camera.bss.o"
    include "build/src/code/z_kaleido_manager.o"
    include "build/src/code/z_kaleido_scope_call.o"
    include "build/src/code/z_fbdemo_dlftbls.o"
    include "build/src/code/z_fbdemo.o"
    include "build/src/code/z_fbdemo_fade.o"
    include "build/src/code/z_fbdemo_circle.o"
    include "build/src/code/z_overlay.o"
    include "build/src/code/z_play.o"
    include "build/src/code/z_play_hireso.o"
    include "build/src/code/PreRender.o"
    include "build/src/code/TwoHeadGfxArena.o"
    include "build/src/code/TwoHeadArena.o"
    include "build/src/code/audio_stop_all_sfx.o"
    include "build/src/code/audio_thread_manager.o"
    include "build/src/code/title_setup.o"
    include "build/src/code/game.o"
    include "build/src/code/gamealloc.o"
    include "build/src/code/graph.o"
    include "build/src/code/graphalloc.o"
    include "build/src/code/listalloc.o"
    include "build/src/code/main.o"
    include "build/src/code/padmgr.o"
    include "build/src/code/sched.o"
    include "build/src/code/speed_meter.o"
    include "build/src/code/su_mtx.o"
    include "build/src/code/sys_cfb.o"
    include "build/src/code/sys_cmpdma.o"
    include "build/src/code/sys_initial_check.o"
    include "build/src/code/sys_math.o"
    include "build/src/code/sys_math3d.o"
    include "build/data/code/sys_math3d.bss.o"
    include "build/data/code/code_801D15B0.data.o"
    include "build/src/code/sys_math_atan.o"
    include "build/src/code/sys_matrix.o"
    include "build/src/code/sys_ucode.o"
    include "build/src/code/sys_rumble.o"
    include "build/data/code/code_801D1E80.data.o"
    include "build/src/code/code_80183070.o"
    include "build/src/code/c_keyframe.o"
    include "build/src/code/sys_slowly.o"
    include "build/src/code/sys_flashrom.o"
    include "build/asm/code/code_80185F90.text.o" // handwritten
    include "build/src/libultra/flash/osFlash.o"
    pad_text
    pad_text
    pad_text
    include "build/src/audio/lib/data.o"
    include "build/src/audio/lib/synthesis.o"
    include "build/src/audio/lib/heap.o"
    include "build/data/code/audio_heap.bss.o"
    include "build/src/audio/lib/load.o"
    include "build/src/audio/lib/thread.o"
    include "build/src/audio/lib/dcache.o"
    include "build/src/audio/lib/aisetnextbuf.o"
    include "build/src/audio/lib/playback.o"
    include "build/src/audio/lib/effects.o"
    include "build/src/audio/lib/seqplayer.o"
    include "build/data/code/audio_dramStack.data.o"
    include "build/asm/code/code_8019AE40.text.o" // handwritten
    pad_text
    include "build/asm/code/code_8019AEC0.text.o" // handwritten
    include "build/src/audio/code_8019AF00.o"
    include "build/src/audio/voice_external.o"
    include "build/data/code/voice_external.data.o"
    include "build/src/audio/voice_internal.o"
    include "build/data/code/voice_internal.data.o"
    include "build/data/code/voice_internal.bss.o"
    pad_text
    include "build/src/audio/sfx_params.o"
    include "build/src/audio/sfx.o"
    include "build/src/audio/sequence.o"
    include "build/data/code/sequence.bss.o"
    include "build/src/audio/session_config.o"
    include "build/src/code/jpegutils.o"
    include "build/src/code/jpegdecoder.o"
    include_data_with_rodata "build/src/code/z_game_over.o"
    include "build/src/code/z_construct.o"
    include "build/data/code/audio_tables.rodata.o"
    include "build/data/code/aspMain.rodata.o"
    include "build/data/code/gspF3DZEX2.NoN.PosLight.fifo.rodata.o"
    include "build/data/code/gspS2DEX2.fifo.rodata.o"
    include "build/data/code/njpgdspMain.rodata.o"
endseg

beginseg
    name "buffers"
    flags NOLOAD
    include "build/src/buffers/gfxyield.o"
    include "build/src/buffers/gfxstack.o"
    include "build/src/buffers/gfxpools.o"
    include "build/data/code/buffers.bss.o"
endseg

beginseg
    name "ovl_title"
    compress
    address 0x80800000
    include "build/src/overlays/gamestates/ovl_title/z_title.o"
    include "build/src/overlays/gamestates/ovl_title/ovl_title_reloc.o"
endseg

beginseg
    name "ovl_select"
    compress
    include "build/src/overlays/gamestates/ovl_select/z_select.o"
    include "build/src/overlays/gamestates/ovl_select/ovl_select_reloc.o"
endseg

beginseg
    name "ovl_opening"
    compress
    include "build/src/overlays/gamestates/ovl_opening/z_opening.o"
    include "build/src/overlays/gamestates/ovl_opening/ovl_opening_reloc.o"
endseg

beginseg
    name "ovl_file_choose"
    compress
    include "build/src/overlays/gamestates/ovl_file_choose/z_file_nameset_data.o"
    include "build/src/overlays/gamestates/ovl_file_choose/z_file_copy_erase.o"
    include "build/src/overlays/gamestates/ovl_file_choose/z_file_nameset_NES.o"
    include "build/src/overlays/gamestates/ovl_file_choose/z_file_choose_NES.o"
    #ifdef NON_MATCHING
        include "build/src/overlays/gamestates/ovl_file_choose/ovl_file_choose_reloc.o"
    #else 
        include "build/data/ovl_file_choose/ovl_file_choose.reloc.o"
    #endif
endseg

beginseg
    name "ovl_daytelop"
    compress
    include "build/src/overlays/gamestates/ovl_daytelop/z_daytelop.o"
    include "build/src/overlays/gamestates/ovl_daytelop/ovl_daytelop_reloc.o"
endseg

beginseg
    name "ovl_kaleido_scope"
    compress
    include "build/src/overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_collect.o"
    include "build/src/overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_debug.o"
    include "build/src/overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_item.o"
    include "build/src/overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_map.o"
    include "build/src/overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_mask.o"
    include "build/src/overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_prompt.o"
    include "build/src/overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope_NES.o"
    include "build/src/overlays/kaleido_scope/ovl_kaleido_scope/ovl_kaleido_scope_reloc.o"
endseg

beginseg
    name "ovl_player_actor"
    compress
    include "build/src/overlays/actors/ovl_player_actor/z_player.o"
    include "build/src/overlays/actors/ovl_player_actor/ovl_player_actor_reloc.o"
endseg

beginseg
    name "ovl_En_Test"
    compress
    include "build/src/overlays/actors/ovl_En_Test/z_en_test.o"
    include "build/src/overlays/actors/ovl_En_Test/ovl_En_Test_reloc.o"
endseg

beginseg
    name "ovl_En_GirlA"
    compress
    include "build/src/overlays/actors/ovl_En_GirlA/z_en_girla.o"
    include "build/src/overlays/actors/ovl_En_GirlA/ovl_En_GirlA_reloc.o"
endseg

beginseg
    name "ovl_En_Part"
    compress
    include "build/src/overlays/actors/ovl_En_Part/z_en_part.o"
    include "build/src/overlays/actors/ovl_En_Part/ovl_En_Part_reloc.o"
endseg

beginseg
    name "ovl_En_Light"
    compress
    include "build/src/overlays/actors/ovl_En_Light/z_en_light.o"
    include "build/src/overlays/actors/ovl_En_Light/ovl_En_Light_reloc.o"
endseg

beginseg
    name "ovl_En_Door"
    compress
    include "build/src/overlays/actors/ovl_En_Door/z_en_door.o"
    include "build/src/overlays/actors/ovl_En_Door/ovl_En_Door_reloc.o"
endseg

beginseg
    name "ovl_En_Box"
    compress
    include "build/src/overlays/actors/ovl_En_Box/z_en_box.o"
    include "build/src/overlays/actors/ovl_En_Box/ovl_En_Box_reloc.o"
endseg

beginseg
    name "ovl_En_Pametfrog"
    compress
    include "build/src/overlays/actors/ovl_En_Pametfrog/z_en_pametfrog.o"
    include "build/src/overlays/actors/ovl_En_Pametfrog/ovl_En_Pametfrog_reloc.o"
endseg

beginseg
    name "ovl_En_Okuta"
    compress
    include "build/src/overlays/actors/ovl_En_Okuta/z_en_okuta.o"
    include "build/data/ovl_En_Okuta/ovl_En_Okuta.data.o"
    include "build/data/ovl_En_Okuta/ovl_En_Okuta.reloc.o"
endseg

beginseg
    name "ovl_En_Bom"
    compress
    include "build/src/overlays/actors/ovl_En_Bom/z_en_bom.o"
    include "build/src/overlays/actors/ovl_En_Bom/ovl_En_Bom_reloc.o"
endseg

beginseg
    name "ovl_En_Wallmas"
    compress
    include "build/src/overlays/actors/ovl_En_Wallmas/z_en_wallmas.o"
    include "build/src/overlays/actors/ovl_En_Wallmas/ovl_En_Wallmas_reloc.o"
endseg

beginseg
    name "ovl_En_Dodongo"
    compress
    include "build/src/overlays/actors/ovl_En_Dodongo/z_en_dodongo.o"
    include "build/src/overlays/actors/ovl_En_Dodongo/ovl_En_Dodongo_reloc.o"
endseg

beginseg
    name "ovl_En_Firefly"
    compress
    include "build/src/overlays/actors/ovl_En_Firefly/z_en_firefly.o"
    include "build/src/overlays/actors/ovl_En_Firefly/ovl_En_Firefly_reloc.o"
endseg

beginseg
    name "ovl_En_Horse"
    compress
    include "build/src/overlays/actors/ovl_En_Horse/z_en_horse.o"
    include "build/src/overlays/actors/ovl_En_Horse/ovl_En_Horse_reloc.o"
endseg

beginseg
    name "ovl_En_Arrow"
    compress
    include "build/src/overlays/actors/ovl_En_Arrow/z_en_arrow.o"
    include "build/src/overlays/actors/ovl_En_Arrow/ovl_En_Arrow_reloc.o"
endseg

beginseg
    name "ovl_En_Elf"
    compress
    include "build/src/overlays/actors/ovl_En_Elf/z_en_elf.o"
    include "build/src/overlays/actors/ovl_En_Elf/ovl_En_Elf_reloc.o"
endseg

beginseg
    name "ovl_En_Niw"
    compress
    include "build/src/overlays/actors/ovl_En_Niw/z_en_niw.o"
    include "build/src/overlays/actors/ovl_En_Niw/ovl_En_Niw_reloc.o"
endseg

beginseg
    name "ovl_En_Tite"
    compress
    include "build/src/overlays/actors/ovl_En_Tite/z_en_tite.o"
    include "build/src/overlays/actors/ovl_En_Tite/ovl_En_Tite_reloc.o"
endseg

beginseg
    name "ovl_En_Peehat"
    compress
    include "build/src/overlays/actors/ovl_En_Peehat/z_en_peehat.o"
    include "build/src/overlays/actors/ovl_En_Peehat/ovl_En_Peehat_reloc.o"
endseg

beginseg
    name "ovl_En_Holl"
    compress
    include "build/src/overlays/actors/ovl_En_Holl/z_en_holl.o"
    include "build/src/overlays/actors/ovl_En_Holl/ovl_En_Holl_reloc.o"
endseg

beginseg
    name "ovl_En_Dinofos"
    compress
    include "build/src/overlays/actors/ovl_En_Dinofos/z_en_dinofos.o"
    include "build/src/overlays/actors/ovl_En_Dinofos/ovl_En_Dinofos_reloc.o"
endseg

beginseg
    name "ovl_En_Hata"
    compress
    include "build/src/overlays/actors/ovl_En_Hata/z_en_hata.o"
    include "build/src/overlays/actors/ovl_En_Hata/ovl_En_Hata_reloc.o"
endseg

beginseg
    name "ovl_En_Zl1"
    compress
    include "build/src/overlays/actors/ovl_En_Zl1/z_en_zl1.o"
    include "build/src/overlays/actors/ovl_En_Zl1/ovl_En_Zl1_reloc.o"
endseg

beginseg
    name "ovl_En_Viewer"
    compress
    include "build/src/overlays/actors/ovl_En_Viewer/z_en_viewer.o"
    include "build/src/overlays/actors/ovl_En_Viewer/ovl_En_Viewer_reloc.o"
endseg

beginseg
    name "ovl_En_Bubble"
    compress
    include "build/src/overlays/actors/ovl_En_Bubble/z_en_bubble.o"
    include "build/src/overlays/actors/ovl_En_Bubble/ovl_En_Bubble_reloc.o"
endseg

beginseg
    name "ovl_Door_Shutter"
    compress
    include "build/src/overlays/actors/ovl_Door_Shutter/z_door_shutter.o"
    include "build/src/overlays/actors/ovl_Door_Shutter/ovl_Door_Shutter_reloc.o"
endseg

beginseg
    name "ovl_En_Boom"
    compress
    include "build/src/overlays/actors/ovl_En_Boom/z_en_boom.o"
    include "build/src/overlays/actors/ovl_En_Boom/ovl_En_Boom_reloc.o"
endseg

beginseg
    name "ovl_En_Torch2"
    compress
    include "build/src/overlays/actors/ovl_En_Torch2/z_en_torch2.o"
    include "build/src/overlays/actors/ovl_En_Torch2/ovl_En_Torch2_reloc.o"
endseg

beginseg
    name "ovl_En_Minifrog"
    compress
    include "build/src/overlays/actors/ovl_En_Minifrog/z_en_minifrog.o"
    include "build/src/overlays/actors/ovl_En_Minifrog/ovl_En_Minifrog_reloc.o"
endseg

beginseg
    name "ovl_En_St"
    compress
    include "build/src/overlays/actors/ovl_En_St/z_en_st.o"
    include "build/src/overlays/actors/ovl_En_St/ovl_En_St_reloc.o"
endseg

beginseg
    name "ovl_Obj_Wturn"
    compress
    include "build/src/overlays/actors/ovl_Obj_Wturn/z_obj_wturn.o"
    include "build/src/overlays/actors/ovl_Obj_Wturn/ovl_Obj_Wturn_reloc.o"
endseg

beginseg
    name "ovl_En_River_Sound"
    compress
    include "build/src/overlays/actors/ovl_En_River_Sound/z_en_river_sound.o"
    include "build/src/overlays/actors/ovl_En_River_Sound/ovl_En_River_Sound_reloc.o"
endseg

beginseg
    name "ovl_En_Ossan"
    compress
    include "build/src/overlays/actors/ovl_En_Ossan/z_en_ossan.o"
    include "build/src/overlays/actors/ovl_En_Ossan/ovl_En_Ossan_reloc.o"
endseg

beginseg
    name "ovl_En_Famos"
    compress
    include "build/src/overlays/actors/ovl_En_Famos/z_en_famos.o"
    include "build/src/overlays/actors/ovl_En_Famos/ovl_En_Famos_reloc.o"
endseg

beginseg
    name "ovl_En_Bombf"
    compress
    include "build/src/overlays/actors/ovl_En_Bombf/z_en_bombf.o"
    include "build/src/overlays/actors/ovl_En_Bombf/ovl_En_Bombf_reloc.o"
endseg

beginseg
    name "ovl_En_Am"
    compress
    include "build/src/overlays/actors/ovl_En_Am/z_en_am.o"
    include "build/src/overlays/actors/ovl_En_Am/ovl_En_Am_reloc.o"
endseg

beginseg
    name "ovl_En_Dekubaba"
    compress
    include "build/src/overlays/actors/ovl_En_Dekubaba/z_en_dekubaba.o"
    include "build/src/overlays/actors/ovl_En_Dekubaba/ovl_En_Dekubaba_reloc.o"
endseg

beginseg
    name "ovl_En_M_Fire1"
    compress
    include "build/src/overlays/actors/ovl_En_M_Fire1/z_en_m_fire1.o"
    include "build/src/overlays/actors/ovl_En_M_Fire1/ovl_En_M_Fire1_reloc.o"
endseg

beginseg
    name "ovl_En_M_Thunder"
    compress
    include "build/src/overlays/actors/ovl_En_M_Thunder/z_en_m_thunder.o"
    include "build/src/overlays/actors/ovl_En_M_Thunder/ovl_En_M_Thunder_reloc.o"
endseg

beginseg
    name "ovl_Bg_Breakwall"
    compress
    include "build/src/overlays/actors/ovl_Bg_Breakwall/z_bg_breakwall.o"
    include "build/src/overlays/actors/ovl_Bg_Breakwall/ovl_Bg_Breakwall_reloc.o"
endseg

beginseg
    name "ovl_Door_Warp1"
    compress
    include "build/src/overlays/actors/ovl_Door_Warp1/z_door_warp1.o"
    include "build/src/overlays/actors/ovl_Door_Warp1/ovl_Door_Warp1_reloc.o"
endseg

beginseg
    name "ovl_Obj_Syokudai"
    compress
    include "build/src/overlays/actors/ovl_Obj_Syokudai/z_obj_syokudai.o"
    include "build/src/overlays/actors/ovl_Obj_Syokudai/ovl_Obj_Syokudai_reloc.o"
endseg

beginseg
    name "ovl_Item_B_Heart"
    compress
    include "build/src/overlays/actors/ovl_Item_B_Heart/z_item_b_heart.o"
    include "build/src/overlays/actors/ovl_Item_B_Heart/ovl_Item_B_Heart_reloc.o"
endseg

beginseg
    name "ovl_En_Dekunuts"
    compress
    include "build/src/overlays/actors/ovl_En_Dekunuts/z_en_dekunuts.o"
    include "build/src/overlays/actors/ovl_En_Dekunuts/ovl_En_Dekunuts_reloc.o"
endseg

beginseg
    name "ovl_En_Bbfall"
    compress
    include "build/src/overlays/actors/ovl_En_Bbfall/z_en_bbfall.o"
    include "build/src/overlays/actors/ovl_En_Bbfall/ovl_En_Bbfall_reloc.o"
endseg

beginseg
    name "ovl_Arms_Hook"
    compress
    include "build/src/overlays/actors/ovl_Arms_Hook/z_arms_hook.o"
    include "build/src/overlays/actors/ovl_Arms_Hook/ovl_Arms_Hook_reloc.o"
endseg

beginseg
    name "ovl_En_Bb"
    compress
    include "build/src/overlays/actors/ovl_En_Bb/z_en_bb.o"
    include "build/src/overlays/actors/ovl_En_Bb/ovl_En_Bb_reloc.o"
endseg

beginseg
    name "ovl_Bg_Keikoku_Spr"
    compress
    include "build/src/overlays/actors/ovl_Bg_Keikoku_Spr/z_bg_keikoku_spr.o"
    include "build/src/overlays/actors/ovl_Bg_Keikoku_Spr/ovl_Bg_Keikoku_Spr_reloc.o"
endseg

beginseg
    name "ovl_En_Wood02"
    compress
    include "build/src/overlays/actors/ovl_En_Wood02/z_en_wood02.o"
    include "build/src/overlays/actors/ovl_En_Wood02/ovl_En_Wood02_reloc.o"
endseg

beginseg
    name "ovl_En_Death"
    compress
    include "build/src/overlays/actors/ovl_En_Death/z_en_death.o"
    include "build/data/ovl_En_Death/ovl_En_Death.data.o"
    include "build/data/ovl_En_Death/ovl_En_Death.reloc.o"
endseg

beginseg
    name "ovl_En_Minideath"
    compress
    include "build/src/overlays/actors/ovl_En_Minideath/z_en_minideath.o"
    include "build/data/ovl_En_Minideath/ovl_En_Minideath.data.o"
    include "build/data/ovl_En_Minideath/ovl_En_Minideath.bss.o"
    include "build/data/ovl_En_Minideath/ovl_En_Minideath.reloc.o"
endseg

beginseg
    name "ovl_En_Vm"
    compress
    include "build/src/overlays/actors/ovl_En_Vm/z_en_vm.o"
    include "build/src/overlays/actors/ovl_En_Vm/ovl_En_Vm_reloc.o"
endseg

beginseg
    name "ovl_Demo_Effect"
    compress
    include "build/src/overlays/actors/ovl_Demo_Effect/z_demo_effect.o"
    include "build/src/overlays/actors/ovl_Demo_Effect/ovl_Demo_Effect_reloc.o"
endseg

beginseg
    name "ovl_Demo_Kankyo"
    compress
    include "build/src/overlays/actors/ovl_Demo_Kankyo/z_demo_kankyo.o"
    include "build/src/overlays/actors/ovl_Demo_Kankyo/ovl_Demo_Kankyo_reloc.o"
endseg

beginseg
    name "ovl_En_Floormas"
    compress
    include "build/src/overlays/actors/ovl_En_Floormas/z_en_floormas.o"
    include "build/src/overlays/actors/ovl_En_Floormas/ovl_En_Floormas_reloc.o"
endseg

beginseg
    name "ovl_En_Rd"
    compress
    include "build/src/overlays/actors/ovl_En_Rd/z_en_rd.o"
    include "build/src/overlays/actors/ovl_En_Rd/ovl_En_Rd_reloc.o"
endseg

beginseg
    name "ovl_Bg_F40_Flift"
    compress
    include "build/src/overlays/actors/ovl_Bg_F40_Flift/z_bg_f40_flift.o"
    include "build/src/overlays/actors/ovl_Bg_F40_Flift/ovl_Bg_F40_Flift_reloc.o"
endseg

beginseg
    name "ovl_Obj_Mure"
    compress
    include "build/src/overlays/actors/ovl_Obj_Mure/z_obj_mure.o"
    include "build/src/overlays/actors/ovl_Obj_Mure/ovl_Obj_Mure_reloc.o"
endseg

beginseg
    name "ovl_En_Sw"
    compress
    include "build/src/overlays/actors/ovl_En_Sw/z_en_sw.o"
    include "build/src/overlays/actors/ovl_En_Sw/ovl_En_Sw_reloc.o"
endseg

beginseg
    name "ovl_Object_Kankyo"
    compress
    include "build/src/overlays/actors/ovl_Object_Kankyo/z_object_kankyo.o"
    include "build/src/overlays/actors/ovl_Object_Kankyo/ovl_Object_Kankyo_reloc.o"
endseg

beginseg
    name "ovl_En_Horse_Link_Child"
    compress
    include "build/src/overlays/actors/ovl_En_Horse_Link_Child/z_en_horse_link_child.o"
    include "build/src/overlays/actors/ovl_En_Horse_Link_Child/ovl_En_Horse_Link_Child_reloc.o"
endseg

beginseg
    name "ovl_Door_Ana"
    compress
    include "build/src/overlays/actors/ovl_Door_Ana/z_door_ana.o"
    include "build/src/overlays/actors/ovl_Door_Ana/ovl_Door_Ana_reloc.o"
endseg

beginseg
    name "ovl_En_Encount1"
    compress
    include "build/src/overlays/actors/ovl_En_Encount1/z_en_encount1.o"
    include "build/src/overlays/actors/ovl_En_Encount1/ovl_En_Encount1_reloc.o"
endseg

beginseg
    name "ovl_Demo_Tre_Lgt"
    compress
    include "build/src/overlays/actors/ovl_Demo_Tre_Lgt/z_demo_tre_lgt.o"
    include "build/src/overlays/actors/ovl_Demo_Tre_Lgt/ovl_Demo_Tre_Lgt_reloc.o"
endseg

beginseg
    name "ovl_En_Encount2"
    compress
    include "build/src/overlays/actors/ovl_En_Encount2/z_en_encount2.o"
    include "build/src/overlays/actors/ovl_En_Encount2/ovl_En_Encount2_reloc.o"
endseg

beginseg
    name "ovl_En_Fire_Rock"
    compress
    include "build/src/overlays/actors/ovl_En_Fire_Rock/z_en_fire_rock.o"
    include "build/src/overlays/actors/ovl_En_Fire_Rock/ovl_En_Fire_Rock_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ctower_Rot"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ctower_Rot/z_bg_ctower_rot.o"
    include "build/src/overlays/actors/ovl_Bg_Ctower_Rot/ovl_Bg_Ctower_Rot_reloc.o"
endseg

beginseg
    name "ovl_Mir_Ray"
    compress
    include "build/src/overlays/actors/ovl_Mir_Ray/z_mir_ray.o"
    include "build/src/overlays/actors/ovl_Mir_Ray/ovl_Mir_Ray_reloc.o"
endseg

beginseg
    name "ovl_En_Sb"
    compress
    include "build/src/overlays/actors/ovl_En_Sb/z_en_sb.o"
    include "build/src/overlays/actors/ovl_En_Sb/ovl_En_Sb_reloc.o"
endseg

beginseg
    name "ovl_En_Bigslime"
    compress
    include "build/src/overlays/actors/ovl_En_Bigslime/z_en_bigslime.o"
    include "build/src/overlays/actors/ovl_En_Bigslime/ovl_En_Bigslime_reloc.o"
endseg

beginseg
    name "ovl_En_Karebaba"
    compress
    include "build/src/overlays/actors/ovl_En_Karebaba/z_en_karebaba.o"
    include "build/src/overlays/actors/ovl_En_Karebaba/ovl_En_Karebaba_reloc.o"
endseg

beginseg
    name "ovl_En_In"
    compress
    include "build/src/overlays/actors/ovl_En_In/z_en_in.o"
    include "build/src/overlays/actors/ovl_En_In/ovl_En_In_reloc.o"
endseg

beginseg
    name "ovl_En_Bom_Chu"
    compress
    include "build/src/overlays/actors/ovl_En_Bom_Chu/z_en_bom_chu.o"
    include "build/src/overlays/actors/ovl_En_Bom_Chu/ovl_En_Bom_Chu_reloc.o"
endseg

beginseg
    name "ovl_En_Horse_Game_Check"
    compress
    include "build/src/overlays/actors/ovl_En_Horse_Game_Check/z_en_horse_game_check.o"
    include "build/src/overlays/actors/ovl_En_Horse_Game_Check/ovl_En_Horse_Game_Check_reloc.o"
endseg

beginseg
    name "ovl_En_Rr"
    compress
    include "build/src/overlays/actors/ovl_En_Rr/z_en_rr.o"
    include "build/src/overlays/actors/ovl_En_Rr/ovl_En_Rr_reloc.o"
endseg

beginseg
    name "ovl_En_Fr"
    compress
    include "build/src/overlays/actors/ovl_En_Fr/z_en_fr.o"
    include "build/src/overlays/actors/ovl_En_Fr/ovl_En_Fr_reloc.o"
endseg

beginseg
    name "ovl_En_Fishing"
    compress
    include "build/src/overlays/actors/ovl_En_Fishing/z_en_fishing.o"
    include "build/src/overlays/actors/ovl_En_Fishing/ovl_En_Fishing_reloc.o"
endseg

beginseg
    name "ovl_Obj_Oshihiki"
    compress
    include "build/src/overlays/actors/ovl_Obj_Oshihiki/z_obj_oshihiki.o"
    include "build/src/overlays/actors/ovl_Obj_Oshihiki/ovl_Obj_Oshihiki_reloc.o"
endseg

beginseg
    name "ovl_Eff_Dust"
    compress
    include "build/src/overlays/actors/ovl_Eff_Dust/z_eff_dust.o"
    include "build/src/overlays/actors/ovl_Eff_Dust/ovl_Eff_Dust_reloc.o"
endseg

beginseg
    name "ovl_Bg_Umajump"
    compress
    include "build/src/overlays/actors/ovl_Bg_Umajump/z_bg_umajump.o"
    include "build/src/overlays/actors/ovl_Bg_Umajump/ovl_Bg_Umajump_reloc.o"
endseg

beginseg
    name "ovl_En_Insect"
    compress
    include "build/src/overlays/actors/ovl_En_Insect/z_en_insect.o"
    include "build/src/overlays/actors/ovl_En_Insect/ovl_En_Insect_reloc.o"
endseg

beginseg
    name "ovl_En_Butte"
    compress
    include "build/src/overlays/actors/ovl_En_Butte/z_en_butte.o"
    include "build/src/overlays/actors/ovl_En_Butte/ovl_En_Butte_reloc.o"
endseg

beginseg
    name "ovl_En_Fish"
    compress
    include "build/src/overlays/actors/ovl_En_Fish/z_en_fish.o"
    include "build/src/overlays/actors/ovl_En_Fish/ovl_En_Fish_reloc.o"
endseg

beginseg
    name "ovl_Item_Etcetera"
    compress
    include "build/src/overlays/actors/ovl_Item_Etcetera/z_item_etcetera.o"
    include "build/src/overlays/actors/ovl_Item_Etcetera/ovl_Item_Etcetera_reloc.o"
endseg

beginseg
    name "ovl_Arrow_Fire"
    compress
    include "build/src/overlays/actors/ovl_Arrow_Fire/z_arrow_fire.o"
    include "build/src/overlays/actors/ovl_Arrow_Fire/ovl_Arrow_Fire_reloc.o"
endseg

beginseg
    name "ovl_Arrow_Ice"
    compress
    include "build/src/overlays/actors/ovl_Arrow_Ice/z_arrow_ice.o"
    include "build/src/overlays/actors/ovl_Arrow_Ice/ovl_Arrow_Ice_reloc.o"
endseg

beginseg
    name "ovl_Arrow_Light"
    compress
    include "build/src/overlays/actors/ovl_Arrow_Light/z_arrow_light.o"
    include "build/src/overlays/actors/ovl_Arrow_Light/ovl_Arrow_Light_reloc.o"
endseg

beginseg
    name "ovl_Obj_Kibako"
    compress
    include "build/src/overlays/actors/ovl_Obj_Kibako/z_obj_kibako.o"
    include "build/src/overlays/actors/ovl_Obj_Kibako/ovl_Obj_Kibako_reloc.o"
endseg

beginseg
    name "ovl_Obj_Tsubo"
    compress
    include "build/src/overlays/actors/ovl_Obj_Tsubo/z_obj_tsubo.o"
    include "build/src/overlays/actors/ovl_Obj_Tsubo/ovl_Obj_Tsubo_reloc.o"
endseg

beginseg
    name "ovl_En_Ik"
    compress
    include "build/src/overlays/actors/ovl_En_Ik/z_en_ik.o"
    include "build/src/overlays/actors/ovl_En_Ik/ovl_En_Ik_reloc.o"
endseg

beginseg
    name "ovl_Demo_Shd"
    compress
    include "build/src/overlays/actors/ovl_Demo_Shd/z_demo_shd.o"
    include "build/src/overlays/actors/ovl_Demo_Shd/ovl_Demo_Shd_reloc.o"
endseg

beginseg
    name "ovl_En_Dns"
    compress
    include "build/src/overlays/actors/ovl_En_Dns/z_en_dns.o"
    include "build/src/overlays/actors/ovl_En_Dns/ovl_En_Dns_reloc.o"
endseg

beginseg
    name "ovl_Elf_Msg"
    compress
    include "build/src/overlays/actors/ovl_Elf_Msg/z_elf_msg.o"
    include "build/src/overlays/actors/ovl_Elf_Msg/ovl_Elf_Msg_reloc.o"
endseg

beginseg
    name "ovl_En_Honotrap"
    compress
    include "build/src/overlays/actors/ovl_En_Honotrap/z_en_honotrap.o"
    include "build/data/ovl_En_Honotrap/ovl_En_Honotrap.data.o"
    include "build/data/ovl_En_Honotrap/ovl_En_Honotrap.reloc.o"
endseg

beginseg
    name "ovl_En_Tubo_Trap"
    compress
    include "build/src/overlays/actors/ovl_En_Tubo_Trap/z_en_tubo_trap.o"
    include "build/src/overlays/actors/ovl_En_Tubo_Trap/ovl_En_Tubo_Trap_reloc.o"
endseg

beginseg
    name "ovl_Obj_Ice_Poly"
    compress
    include "build/src/overlays/actors/ovl_Obj_Ice_Poly/z_obj_ice_poly.o"
    include "build/src/overlays/actors/ovl_Obj_Ice_Poly/ovl_Obj_Ice_Poly_reloc.o"
endseg

beginseg
    name "ovl_En_Fz"
    compress
    include "build/src/overlays/actors/ovl_En_Fz/z_en_fz.o"
    include "build/src/overlays/actors/ovl_En_Fz/ovl_En_Fz_reloc.o"
endseg

beginseg
    name "ovl_En_Kusa"
    compress
    include "build/src/overlays/actors/ovl_En_Kusa/z_en_kusa.o"
    include "build/src/overlays/actors/ovl_En_Kusa/ovl_En_Kusa_reloc.o"
endseg

beginseg
    name "ovl_Obj_Bean"
    compress
    include "build/src/overlays/actors/ovl_Obj_Bean/z_obj_bean.o"
    include "build/src/overlays/actors/ovl_Obj_Bean/ovl_Obj_Bean_reloc.o"
endseg

beginseg
    name "ovl_Obj_Bombiwa"
    compress
    include "build/src/overlays/actors/ovl_Obj_Bombiwa/z_obj_bombiwa.o"
    include "build/src/overlays/actors/ovl_Obj_Bombiwa/ovl_Obj_Bombiwa_reloc.o"
endseg

beginseg
    name "ovl_Obj_Switch"
    compress
    include "build/src/overlays/actors/ovl_Obj_Switch/z_obj_switch.o"
    include "build/src/overlays/actors/ovl_Obj_Switch/ovl_Obj_Switch_reloc.o"
endseg

beginseg
    name "ovl_Obj_Lift"
    compress
    include "build/src/overlays/actors/ovl_Obj_Lift/z_obj_lift.o"
    include "build/src/overlays/actors/ovl_Obj_Lift/ovl_Obj_Lift_reloc.o"
endseg

beginseg
    name "ovl_Obj_Hsblock"
    compress
    include "build/src/overlays/actors/ovl_Obj_Hsblock/z_obj_hsblock.o"
    include "build/src/overlays/actors/ovl_Obj_Hsblock/ovl_Obj_Hsblock_reloc.o"
endseg

beginseg
    name "ovl_En_Okarina_Tag"
    compress
    include "build/src/overlays/actors/ovl_En_Okarina_Tag/z_en_okarina_tag.o"
    include "build/src/overlays/actors/ovl_En_Okarina_Tag/ovl_En_Okarina_Tag_reloc.o"
endseg

beginseg
    name "ovl_En_Goroiwa"
    compress
    include "build/src/overlays/actors/ovl_En_Goroiwa/z_en_goroiwa.o"
    include "build/src/overlays/actors/ovl_En_Goroiwa/ovl_En_Goroiwa_reloc.o"
endseg

beginseg
    name "ovl_En_Daiku"
    compress
    include "build/src/overlays/actors/ovl_En_Daiku/z_en_daiku.o"
    include "build/src/overlays/actors/ovl_En_Daiku/ovl_En_Daiku_reloc.o"
endseg

beginseg
    name "ovl_En_Nwc"
    compress
    include "build/src/overlays/actors/ovl_En_Nwc/z_en_nwc.o"
    include "build/src/overlays/actors/ovl_En_Nwc/ovl_En_Nwc_reloc.o"
endseg

beginseg
    name "ovl_Item_Inbox"
    compress
    include "build/src/overlays/actors/ovl_Item_Inbox/z_item_inbox.o"
    include "build/src/overlays/actors/ovl_Item_Inbox/ovl_Item_Inbox_reloc.o"
endseg

beginseg
    name "ovl_En_Ge1"
    compress
    include "build/src/overlays/actors/ovl_En_Ge1/z_en_ge1.o"
    include "build/src/overlays/actors/ovl_En_Ge1/ovl_En_Ge1_reloc.o"
endseg

beginseg
    name "ovl_Obj_Blockstop"
    compress
    include "build/src/overlays/actors/ovl_Obj_Blockstop/z_obj_blockstop.o"
    include "build/src/overlays/actors/ovl_Obj_Blockstop/ovl_Obj_Blockstop_reloc.o"
endseg

beginseg
    name "ovl_En_Sda"
    compress
    include "build/src/overlays/actors/ovl_En_Sda/z_en_sda.o"
    include "build/src/overlays/actors/ovl_En_Sda/ovl_En_Sda_reloc.o"
endseg

beginseg
    name "ovl_En_Clear_Tag"
    compress
    include "build/src/overlays/actors/ovl_En_Clear_Tag/z_en_clear_tag.o"
    include "build/src/overlays/actors/ovl_En_Clear_Tag/ovl_En_Clear_Tag_reloc.o"
endseg

beginseg
    name "ovl_En_Gm"
    compress
    include "build/src/overlays/actors/ovl_En_Gm/z_en_gm.o"
    include "build/src/overlays/actors/ovl_En_Gm/ovl_En_Gm_reloc.o"
endseg

beginseg
    name "ovl_En_Ms"
    compress
    include "build/src/overlays/actors/ovl_En_Ms/z_en_ms.o"
    include "build/src/overlays/actors/ovl_En_Ms/ovl_En_Ms_reloc.o"
endseg

beginseg
    name "ovl_En_Hs"
    compress
    include "build/src/overlays/actors/ovl_En_Hs/z_en_hs.o"
    include "build/src/overlays/actors/ovl_En_Hs/ovl_En_Hs_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ingate"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ingate/z_bg_ingate.o"
    include "build/src/overlays/actors/ovl_Bg_Ingate/ovl_Bg_Ingate_reloc.o"
endseg

beginseg
    name "ovl_En_Kanban"
    compress
    include "build/src/overlays/actors/ovl_En_Kanban/z_en_kanban.o"
    include "build/src/overlays/actors/ovl_En_Kanban/ovl_En_Kanban_reloc.o"
endseg

beginseg
    name "ovl_En_Attack_Niw"
    compress
    include "build/src/overlays/actors/ovl_En_Attack_Niw/z_en_attack_niw.o"
    include "build/src/overlays/actors/ovl_En_Attack_Niw/ovl_En_Attack_Niw_reloc.o"
endseg

beginseg
    name "ovl_En_Mk"
    compress
    include "build/src/overlays/actors/ovl_En_Mk/z_en_mk.o"
    include "build/src/overlays/actors/ovl_En_Mk/ovl_En_Mk_reloc.o"
endseg

beginseg
    name "ovl_En_Owl"
    compress
    include "build/src/overlays/actors/ovl_En_Owl/z_en_owl.o"
    include "build/src/overlays/actors/ovl_En_Owl/ovl_En_Owl_reloc.o"
endseg

beginseg
    name "ovl_En_Ishi"
    compress
    include "build/src/overlays/actors/ovl_En_Ishi/z_en_ishi.o"
    include "build/src/overlays/actors/ovl_En_Ishi/ovl_En_Ishi_reloc.o"
endseg

beginseg
    name "ovl_Obj_Hana"
    compress
    include "build/src/overlays/actors/ovl_Obj_Hana/z_obj_hana.o"
    include "build/src/overlays/actors/ovl_Obj_Hana/ovl_Obj_Hana_reloc.o"
endseg

beginseg
    name "ovl_Obj_Lightswitch"
    compress
    include "build/src/overlays/actors/ovl_Obj_Lightswitch/z_obj_lightswitch.o"
    include "build/src/overlays/actors/ovl_Obj_Lightswitch/ovl_Obj_Lightswitch_reloc.o"
endseg

beginseg
    name "ovl_Obj_Mure2"
    compress
    include "build/src/overlays/actors/ovl_Obj_Mure2/z_obj_mure2.o"
    include "build/data/ovl_Obj_Mure2/ovl_Obj_Mure2.data.o"
    include "build/data/ovl_Obj_Mure2/ovl_Obj_Mure2.reloc.o"
endseg

beginseg
    name "ovl_En_Fu"
    compress
    include "build/src/overlays/actors/ovl_En_Fu/z_en_fu.o"
    include "build/src/overlays/actors/ovl_En_Fu/ovl_En_Fu_reloc.o"
endseg

beginseg
    name "ovl_En_Stream"
    compress
    include "build/src/overlays/actors/ovl_En_Stream/z_en_stream.o"
    include "build/src/overlays/actors/ovl_En_Stream/ovl_En_Stream_reloc.o"
endseg

beginseg
    name "ovl_En_Mm"
    compress
    include "build/src/overlays/actors/ovl_En_Mm/z_en_mm.o"
    include "build/src/overlays/actors/ovl_En_Mm/ovl_En_Mm_reloc.o"
endseg

beginseg
    name "ovl_En_Weather_Tag"
    compress
    include "build/src/overlays/actors/ovl_En_Weather_Tag/z_en_weather_tag.o"
    include "build/src/overlays/actors/ovl_En_Weather_Tag/ovl_En_Weather_Tag_reloc.o"
endseg

beginseg
    name "ovl_En_Ani"
    compress
    include "build/src/overlays/actors/ovl_En_Ani/z_en_ani.o"
    include "build/src/overlays/actors/ovl_En_Ani/ovl_En_Ani_reloc.o"
endseg

beginseg
    name "ovl_En_Js"
    compress
    include "build/src/overlays/actors/ovl_En_Js/z_en_js.o"
    include "build/src/overlays/actors/ovl_En_Js/ovl_En_Js_reloc.o"
endseg

beginseg
    name "ovl_En_Okarina_Effect"
    compress
    include "build/src/overlays/actors/ovl_En_Okarina_Effect/z_en_okarina_effect.o"
    include "build/src/overlays/actors/ovl_En_Okarina_Effect/ovl_En_Okarina_Effect_reloc.o"
endseg

beginseg
    name "ovl_En_Mag"
    compress
    include "build/src/overlays/actors/ovl_En_Mag/z_en_mag.o"
    include "build/src/overlays/actors/ovl_En_Mag/ovl_En_Mag_reloc.o"
endseg

beginseg
    name "ovl_Elf_Msg2"
    compress
    include "build/src/overlays/actors/ovl_Elf_Msg2/z_elf_msg2.o"
    include "build/src/overlays/actors/ovl_Elf_Msg2/ovl_Elf_Msg2_reloc.o"
endseg

beginseg
    name "ovl_Bg_F40_Swlift"
    compress
    include "build/src/overlays/actors/ovl_Bg_F40_Swlift/z_bg_f40_swlift.o"
    include "build/src/overlays/actors/ovl_Bg_F40_Swlift/ovl_Bg_F40_Swlift_reloc.o"
endseg

beginseg
    name "ovl_En_Kakasi"
    compress
    include "build/src/overlays/actors/ovl_En_Kakasi/z_en_kakasi.o"
    include "build/src/overlays/actors/ovl_En_Kakasi/ovl_En_Kakasi_reloc.o"
endseg

beginseg
    name "ovl_Obj_Makeoshihiki"
    compress
    include "build/src/overlays/actors/ovl_Obj_Makeoshihiki/z_obj_makeoshihiki.o"
    include "build/src/overlays/actors/ovl_Obj_Makeoshihiki/ovl_Obj_Makeoshihiki_reloc.o"
endseg

beginseg
    name "ovl_Oceff_Spot"
    compress
    include "build/src/overlays/actors/ovl_Oceff_Spot/z_oceff_spot.o"
    include "build/src/overlays/actors/ovl_Oceff_Spot/ovl_Oceff_Spot_reloc.o"
endseg

beginseg
    name "ovl_En_Torch"
    compress
    include "build/src/overlays/actors/ovl_En_Torch/z_en_torch.o"
    include "build/src/overlays/actors/ovl_En_Torch/ovl_En_Torch_reloc.o"
endseg

beginseg
    name "ovl_Shot_Sun"
    compress
    include "build/src/overlays/actors/ovl_Shot_Sun/z_shot_sun.o"
    include "build/src/overlays/actors/ovl_Shot_Sun/ovl_Shot_Sun_reloc.o"
endseg

beginseg
    name "ovl_Obj_Roomtimer"
    compress
    include "build/src/overlays/actors/ovl_Obj_Roomtimer/z_obj_roomtimer.o"
    include "build/src/overlays/actors/ovl_Obj_Roomtimer/ovl_Obj_Roomtimer_reloc.o"
endseg

beginseg
    name "ovl_En_Ssh"
    compress
    include "build/src/overlays/actors/ovl_En_Ssh/z_en_ssh.o"
    include "build/src/overlays/actors/ovl_En_Ssh/ovl_En_Ssh_reloc.o"
endseg

beginseg
    name "ovl_Oceff_Wipe"
    compress
    include "build/src/overlays/actors/ovl_Oceff_Wipe/z_oceff_wipe.o"
    include "build/src/overlays/actors/ovl_Oceff_Wipe/ovl_Oceff_Wipe_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dust"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Dust/z_eff_ss_dust.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Dust/ovl_Effect_Ss_Dust_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Kirakira"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Kirakira/z_eff_ss_kirakira.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Kirakira/ovl_Effect_Ss_Kirakira_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Bomb2"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Bomb2/z_eff_ss_bomb2.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Bomb2/ovl_Effect_Ss_Bomb2_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Blast"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Blast/z_eff_ss_blast.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Blast/ovl_Effect_Ss_Blast_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_G_Spk"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_G_Spk/z_eff_ss_g_spk.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_G_Spk/ovl_Effect_Ss_G_Spk_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_D_Fire"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_D_Fire/z_eff_ss_d_fire.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_D_Fire/ovl_Effect_Ss_D_Fire_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Bubble"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Bubble/z_eff_ss_bubble.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Bubble/ovl_Effect_Ss_Bubble_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_G_Ripple"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_G_Ripple/z_eff_ss_g_ripple.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_G_Ripple/ovl_Effect_Ss_G_Ripple_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_G_Splash"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_G_Splash/z_eff_ss_g_splash.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_G_Splash/ovl_Effect_Ss_G_Splash_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_G_Fire"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_G_Fire/z_eff_ss_g_fire.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_G_Fire/ovl_Effect_Ss_G_Fire_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Lightning"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Lightning/z_eff_ss_lightning.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Lightning/ovl_Effect_Ss_Lightning_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dt_Bubble"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Dt_Bubble/z_eff_ss_dt_bubble.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Dt_Bubble/ovl_Effect_Ss_Dt_Bubble_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Hahen"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Hahen/z_eff_ss_hahen.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Hahen/ovl_Effect_Ss_Hahen_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Stick"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Stick/z_eff_ss_stick.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Stick/ovl_Effect_Ss_Stick_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Sibuki"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Sibuki/z_eff_ss_sibuki.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Sibuki/ovl_Effect_Ss_Sibuki_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Stone1"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Stone1/z_eff_ss_stone1.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Stone1/ovl_Effect_Ss_Stone1_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Hitmark"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Hitmark/z_eff_ss_hitmark.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Hitmark/ovl_Effect_Ss_Hitmark_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Fhg_Flash"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Fhg_Flash/z_eff_ss_fhg_flash.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Fhg_Flash/ovl_Effect_Ss_Fhg_Flash_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_K_Fire"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_K_Fire/z_eff_ss_k_fire.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_K_Fire/ovl_Effect_Ss_K_Fire_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Solder_Srch_Ball"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Solder_Srch_Ball/z_eff_ss_solder_srch_ball.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Solder_Srch_Ball/ovl_Effect_Ss_Solder_Srch_Ball_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Kakera"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Kakera/z_eff_ss_kakera.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Kakera/ovl_Effect_Ss_Kakera_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Ice_Piece"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Ice_Piece/z_eff_ss_ice_piece.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Ice_Piece/ovl_Effect_Ss_Ice_Piece_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_En_Ice"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_En_Ice/z_eff_ss_en_ice.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_En_Ice/ovl_Effect_Ss_En_Ice_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Fire_Tail"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Fire_Tail/z_eff_ss_fire_tail.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Fire_Tail/ovl_Effect_Ss_Fire_Tail_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_En_Fire"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_En_Fire/z_eff_ss_en_fire.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_En_Fire/ovl_Effect_Ss_En_Fire_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Extra"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Extra/z_eff_ss_extra.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Extra/ovl_Effect_Ss_Extra_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dead_Db"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Dead_Db/z_eff_ss_dead_db.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Dead_Db/ovl_Effect_Ss_Dead_Db_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dead_Dd"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Dead_Dd/z_eff_ss_dead_dd.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Dead_Dd/ovl_Effect_Ss_Dead_Dd_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Dead_Ds"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Dead_Ds/z_eff_ss_dead_ds.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Dead_Ds/ovl_Effect_Ss_Dead_Ds_reloc.o"
endseg

beginseg
    name "ovl_Oceff_Storm"
    compress
    include "build/src/overlays/actors/ovl_Oceff_Storm/z_oceff_storm.o"
    include "build/src/overlays/actors/ovl_Oceff_Storm/ovl_Oceff_Storm_reloc.o"
endseg

beginseg
    name "ovl_Obj_Demo"
    compress
    include "build/src/overlays/actors/ovl_Obj_Demo/z_obj_demo.o"
    include "build/src/overlays/actors/ovl_Obj_Demo/ovl_Obj_Demo_reloc.o"
endseg

beginseg
    name "ovl_En_Minislime"
    compress
    include "build/src/overlays/actors/ovl_En_Minislime/z_en_minislime.o"
    include "build/src/overlays/actors/ovl_En_Minislime/ovl_En_Minislime_reloc.o"
endseg

beginseg
    name "ovl_En_Nutsball"
    compress
    include "build/src/overlays/actors/ovl_En_Nutsball/z_en_nutsball.o"
    include "build/src/overlays/actors/ovl_En_Nutsball/ovl_En_Nutsball_reloc.o"
endseg

beginseg
    name "ovl_Oceff_Wipe2"
    compress
    include "build/src/overlays/actors/ovl_Oceff_Wipe2/z_oceff_wipe2.o"
    include "build/src/overlays/actors/ovl_Oceff_Wipe2/ovl_Oceff_Wipe2_reloc.o"
endseg

beginseg
    name "ovl_Oceff_Wipe3"
    compress
    include "build/src/overlays/actors/ovl_Oceff_Wipe3/z_oceff_wipe3.o"
    include "build/src/overlays/actors/ovl_Oceff_Wipe3/ovl_Oceff_Wipe3_reloc.o"
endseg

beginseg
    name "ovl_En_Dg"
    compress
    include "build/src/overlays/actors/ovl_En_Dg/z_en_dg.o"
    include "build/src/overlays/actors/ovl_En_Dg/ovl_En_Dg_reloc.o"
endseg

beginseg
    name "ovl_En_Si"
    compress
    include "build/src/overlays/actors/ovl_En_Si/z_en_si.o"
    include "build/src/overlays/actors/ovl_En_Si/ovl_En_Si_reloc.o"
endseg

beginseg
    name "ovl_Obj_Comb"
    compress
    include "build/src/overlays/actors/ovl_Obj_Comb/z_obj_comb.o"
    include "build/src/overlays/actors/ovl_Obj_Comb/ovl_Obj_Comb_reloc.o"
endseg

beginseg
    name "ovl_Obj_Kibako2"
    compress
    include "build/src/overlays/actors/ovl_Obj_Kibako2/z_obj_kibako2.o"
    include "build/src/overlays/actors/ovl_Obj_Kibako2/ovl_Obj_Kibako2_reloc.o"
endseg

beginseg
    name "ovl_En_Hs2"
    compress
    include "build/src/overlays/actors/ovl_En_Hs2/z_en_hs2.o"
    include "build/src/overlays/actors/ovl_En_Hs2/ovl_En_Hs2_reloc.o"
endseg

beginseg
    name "ovl_Obj_Mure3"
    compress
    include "build/src/overlays/actors/ovl_Obj_Mure3/z_obj_mure3.o"
    include "build/src/overlays/actors/ovl_Obj_Mure3/ovl_Obj_Mure3_reloc.o"
endseg

beginseg
    name "ovl_En_Tg"
    compress
    include "build/src/overlays/actors/ovl_En_Tg/z_en_tg.o"
    include "build/src/overlays/actors/ovl_En_Tg/ovl_En_Tg_reloc.o"
endseg

beginseg
    name "ovl_En_Wf"
    compress
    include "build/src/overlays/actors/ovl_En_Wf/z_en_wf.o"
    include "build/src/overlays/actors/ovl_En_Wf/ovl_En_Wf_reloc.o"
endseg

beginseg
    name "ovl_En_Skb"
    compress
    include "build/src/overlays/actors/ovl_En_Skb/z_en_skb.o"
    include "build/src/overlays/actors/ovl_En_Skb/ovl_En_Skb_reloc.o"
endseg

beginseg
    name "ovl_En_Gs"
    compress
    include "build/src/overlays/actors/ovl_En_Gs/z_en_gs.o"
    include "build/src/overlays/actors/ovl_En_Gs/ovl_En_Gs_reloc.o"
endseg

beginseg
    name "ovl_Obj_Sound"
    compress
    include "build/src/overlays/actors/ovl_Obj_Sound/z_obj_sound.o"
    include "build/data/ovl_Obj_Sound/ovl_Obj_Sound.data.o"
    include "build/data/ovl_Obj_Sound/ovl_Obj_Sound.reloc.o"
endseg

beginseg
    name "ovl_En_Crow"
    compress
    include "build/src/overlays/actors/ovl_En_Crow/z_en_crow.o"
    include "build/src/overlays/actors/ovl_En_Crow/ovl_En_Crow_reloc.o"
endseg

beginseg
    name "ovl_En_Cow"
    compress
    include "build/src/overlays/actors/ovl_En_Cow/z_en_cow.o"
    include "build/src/overlays/actors/ovl_En_Cow/ovl_En_Cow_reloc.o"
endseg

beginseg
    name "ovl_Oceff_Wipe4"
    compress
    include "build/src/overlays/actors/ovl_Oceff_Wipe4/z_oceff_wipe4.o"
    include "build/src/overlays/actors/ovl_Oceff_Wipe4/ovl_Oceff_Wipe4_reloc.o"
endseg

beginseg
    name "ovl_En_Zo"
    compress
    include "build/src/overlays/actors/ovl_En_Zo/z_en_zo.o"
    include "build/src/overlays/actors/ovl_En_Zo/ovl_En_Zo_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Ice_Smoke"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Ice_Smoke/z_eff_ss_ice_smoke.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Ice_Smoke/ovl_Effect_Ss_Ice_Smoke_reloc.o"
endseg

beginseg
    name "ovl_Obj_Makekinsuta"
    compress
    include "build/src/overlays/actors/ovl_Obj_Makekinsuta/z_obj_makekinsuta.o"
    include "build/src/overlays/actors/ovl_Obj_Makekinsuta/ovl_Obj_Makekinsuta_reloc.o"
endseg

beginseg
    name "ovl_En_Ge3"
    compress
    include "build/src/overlays/actors/ovl_En_Ge3/z_en_ge3.o"
    include "build/src/overlays/actors/ovl_En_Ge3/ovl_En_Ge3_reloc.o"
endseg

beginseg
    name "ovl_Obj_Hamishi"
    compress
    include "build/src/overlays/actors/ovl_Obj_Hamishi/z_obj_hamishi.o"
    include "build/src/overlays/actors/ovl_Obj_Hamishi/ovl_Obj_Hamishi_reloc.o"
endseg

beginseg
    name "ovl_En_Zl4"
    compress
    include "build/src/overlays/actors/ovl_En_Zl4/z_en_zl4.o"
    include "build/data/ovl_En_Zl4/ovl_En_Zl4.data.o"
    include "build/data/ovl_En_Zl4/ovl_En_Zl4.reloc.o"
endseg

beginseg
    name "ovl_En_Mm2"
    compress
    include "build/src/overlays/actors/ovl_En_Mm2/z_en_mm2.o"
    include "build/src/overlays/actors/ovl_En_Mm2/ovl_En_Mm2_reloc.o"
endseg

beginseg
    name "ovl_Door_Spiral"
    compress
    include "build/src/overlays/actors/ovl_Door_Spiral/z_door_spiral.o"
    include "build/data/ovl_Door_Spiral/ovl_Door_Spiral.data.o"
    include "build/data/ovl_Door_Spiral/ovl_Door_Spiral.reloc.o"
endseg

beginseg
    name "ovl_Obj_Pzlblock"
    compress
    include "build/src/overlays/actors/ovl_Obj_Pzlblock/z_obj_pzlblock.o"
    include "build/src/overlays/actors/ovl_Obj_Pzlblock/ovl_Obj_Pzlblock_reloc.o"
endseg

beginseg
    name "ovl_Obj_Toge"
    compress
    include "build/src/overlays/actors/ovl_Obj_Toge/z_obj_toge.o"
    include "build/src/overlays/actors/ovl_Obj_Toge/ovl_Obj_Toge_reloc.o"
endseg

beginseg
    name "ovl_Obj_Armos"
    compress
    include "build/src/overlays/actors/ovl_Obj_Armos/z_obj_armos.o"
    include "build/src/overlays/actors/ovl_Obj_Armos/ovl_Obj_Armos_reloc.o"
endseg

beginseg
    name "ovl_Obj_Boyo"
    compress
    include "build/src/overlays/actors/ovl_Obj_Boyo/z_obj_boyo.o"
    include "build/data/ovl_Obj_Boyo/ovl_Obj_Boyo.data.o"
    include "build/data/ovl_Obj_Boyo/ovl_Obj_Boyo.reloc.o"
endseg

beginseg
    name "ovl_En_Grasshopper"
    compress
    include "build/src/overlays/actors/ovl_En_Grasshopper/z_en_grasshopper.o"
    include "build/src/overlays/actors/ovl_En_Grasshopper/ovl_En_Grasshopper_reloc.o"
endseg

beginseg
    name "ovl_Obj_Grass"
    compress
    include "build/src/overlays/actors/ovl_Obj_Grass/z_obj_grass.o"
    include "build/src/overlays/actors/ovl_Obj_Grass/ovl_Obj_Grass_reloc.o"
endseg

beginseg
    name "ovl_Obj_Grass_Carry"
    compress
    include "build/src/overlays/actors/ovl_Obj_Grass_Carry/z_obj_grass_carry.o"
    include "build/src/overlays/actors/ovl_Obj_Grass_Carry/ovl_Obj_Grass_Carry_reloc.o"
endseg

beginseg
    name "ovl_Obj_Grass_Unit"
    compress
    include "build/src/overlays/actors/ovl_Obj_Grass_Unit/z_obj_grass_unit.o"
    include "build/data/ovl_Obj_Grass_Unit/ovl_Obj_Grass_Unit.data.o"
    include "build/data/ovl_Obj_Grass_Unit/ovl_Obj_Grass_Unit.reloc.o"
endseg

beginseg
    name "ovl_Bg_Fire_Wall"
    compress
    include "build/src/overlays/actors/ovl_Bg_Fire_Wall/z_bg_fire_wall.o"
    include "build/src/overlays/actors/ovl_Bg_Fire_Wall/ovl_Bg_Fire_Wall_reloc.o"
endseg

beginseg
    name "ovl_En_Bu"
    compress
    include "build/src/overlays/actors/ovl_En_Bu/z_en_bu.o"
    include "build/src/overlays/actors/ovl_En_Bu/ovl_En_Bu_reloc.o"
endseg

beginseg
    name "ovl_En_Encount3"
    compress
    include "build/src/overlays/actors/ovl_En_Encount3/z_en_encount3.o"
    include "build/src/overlays/actors/ovl_En_Encount3/ovl_En_Encount3_reloc.o"
endseg

beginseg
    name "ovl_En_Jso"
    compress
    include "build/src/overlays/actors/ovl_En_Jso/z_en_jso.o"
    include "build/data/ovl_En_Jso/ovl_En_Jso.data.o"
    include "build/data/ovl_En_Jso/ovl_En_Jso.reloc.o"
endseg

beginseg
    name "ovl_Obj_Chikuwa"
    compress
    include "build/src/overlays/actors/ovl_Obj_Chikuwa/z_obj_chikuwa.o"
    include "build/src/overlays/actors/ovl_Obj_Chikuwa/ovl_Obj_Chikuwa_reloc.o"
endseg

beginseg
    name "ovl_En_Knight"
    compress
    include "build/src/overlays/actors/ovl_En_Knight/z_en_knight.o"
    include "build/data/ovl_En_Knight/ovl_En_Knight.data.o"
    include "build/data/ovl_En_Knight/ovl_En_Knight.bss.o"
    include "build/data/ovl_En_Knight/ovl_En_Knight.reloc.o"
endseg

beginseg
    name "ovl_En_Warp_tag"
    compress
    include "build/src/overlays/actors/ovl_En_Warp_tag/z_en_warp_tag.o"
    include "build/src/overlays/actors/ovl_En_Warp_tag/ovl_En_Warp_tag_reloc.o"
endseg

beginseg
    name "ovl_En_Aob_01"
    compress
    include "build/src/overlays/actors/ovl_En_Aob_01/z_en_aob_01.o"
    include "build/src/overlays/actors/ovl_En_Aob_01/ovl_En_Aob_01_reloc.o"
endseg

beginseg
    name "ovl_En_Boj_01"
    compress
    include "build/src/overlays/actors/ovl_En_Boj_01/z_en_boj_01.o"
    include "build/src/overlays/actors/ovl_En_Boj_01/ovl_En_Boj_01_reloc.o"
endseg

beginseg
    name "ovl_En_Boj_02"
    compress
    include "build/src/overlays/actors/ovl_En_Boj_02/z_en_boj_02.o"
    include "build/src/overlays/actors/ovl_En_Boj_02/ovl_En_Boj_02_reloc.o"
endseg

beginseg
    name "ovl_En_Boj_03"
    compress
    include "build/src/overlays/actors/ovl_En_Boj_03/z_en_boj_03.o"
    include "build/src/overlays/actors/ovl_En_Boj_03/ovl_En_Boj_03_reloc.o"
endseg

beginseg
    name "ovl_En_Encount4"
    compress
    include "build/src/overlays/actors/ovl_En_Encount4/z_en_encount4.o"
    include "build/src/overlays/actors/ovl_En_Encount4/ovl_En_Encount4_reloc.o"
endseg

beginseg
    name "ovl_En_Bom_Bowl_Man"
    compress
    include "build/src/overlays/actors/ovl_En_Bom_Bowl_Man/z_en_bom_bowl_man.o"
    include "build/src/overlays/actors/ovl_En_Bom_Bowl_Man/ovl_En_Bom_Bowl_Man_reloc.o"
endseg

beginseg
    name "ovl_En_Syateki_Man"
    compress
    include "build/src/overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.o"
    include "build/src/overlays/actors/ovl_En_Syateki_Man/ovl_En_Syateki_Man_reloc.o"
endseg

beginseg
    name "ovl_Bg_Icicle"
    compress
    include "build/src/overlays/actors/ovl_Bg_Icicle/z_bg_icicle.o"
    include "build/src/overlays/actors/ovl_Bg_Icicle/ovl_Bg_Icicle_reloc.o"
endseg

beginseg
    name "ovl_En_Syateki_Crow"
    compress
    include "build/src/overlays/actors/ovl_En_Syateki_Crow/z_en_syateki_crow.o"
    include "build/src/overlays/actors/ovl_En_Syateki_Crow/ovl_En_Syateki_Crow_reloc.o"
endseg

beginseg
    name "ovl_En_Boj_04"
    compress
    include "build/src/overlays/actors/ovl_En_Boj_04/z_en_boj_04.o"
    include "build/src/overlays/actors/ovl_En_Boj_04/ovl_En_Boj_04_reloc.o"
endseg

beginseg
    name "ovl_En_Cne_01"
    compress
    include "build/src/overlays/actors/ovl_En_Cne_01/z_en_cne_01.o"
    include "build/src/overlays/actors/ovl_En_Cne_01/ovl_En_Cne_01_reloc.o"
endseg

beginseg
    name "ovl_En_Bba_01"
    compress
    include "build/src/overlays/actors/ovl_En_Bba_01/z_en_bba_01.o"
    include "build/src/overlays/actors/ovl_En_Bba_01/ovl_En_Bba_01_reloc.o"
endseg

beginseg
    name "ovl_En_Bji_01"
    compress
    include "build/src/overlays/actors/ovl_En_Bji_01/z_en_bji_01.o"
    include "build/src/overlays/actors/ovl_En_Bji_01/ovl_En_Bji_01_reloc.o"
endseg

beginseg
    name "ovl_Bg_Spdweb"
    compress
    include "build/src/overlays/actors/ovl_Bg_Spdweb/z_bg_spdweb.o"
    include "build/src/overlays/actors/ovl_Bg_Spdweb/ovl_Bg_Spdweb_reloc.o"
endseg

beginseg
    name "ovl_En_Mt_tag"
    compress
    include "build/src/overlays/actors/ovl_En_Mt_tag/z_en_mt_tag.o"
    include "build/src/overlays/actors/ovl_En_Mt_tag/ovl_En_Mt_tag_reloc.o"
endseg

beginseg
    name "ovl_Boss_01"
    compress
    include "build/src/overlays/actors/ovl_Boss_01/z_boss_01.o"
    include "build/data/ovl_Boss_01/ovl_Boss_01.data.o"
    include "build/data/ovl_Boss_01/ovl_Boss_01.bss.o"
    include "build/data/ovl_Boss_01/ovl_Boss_01.reloc.o"
endseg

beginseg
    name "ovl_Boss_02"
    compress
    include "build/src/overlays/actors/ovl_Boss_02/z_boss_02.o"
    include "build/src/overlays/actors/ovl_Boss_02/ovl_Boss_02_reloc.o"
endseg

beginseg
    name "ovl_Boss_03"
    compress
    include "build/src/overlays/actors/ovl_Boss_03/z_boss_03.o"
    include "build/src/overlays/actors/ovl_Boss_03/ovl_Boss_03_reloc.o"
endseg

beginseg
    name "ovl_Boss_04"
    compress
    include "build/src/overlays/actors/ovl_Boss_04/z_boss_04.o"
    include "build/src/overlays/actors/ovl_Boss_04/ovl_Boss_04_reloc.o"
endseg

beginseg
    name "ovl_Boss_05"
    compress
    include "build/src/overlays/actors/ovl_Boss_05/z_boss_05.o"
    include "build/data/ovl_Boss_05/ovl_Boss_05.data.o"
    include "build/data/ovl_Boss_05/ovl_Boss_05.bss.o"
    include "build/data/ovl_Boss_05/ovl_Boss_05.reloc.o"
endseg

beginseg
    name "ovl_Boss_06"
    compress
    include "build/src/overlays/actors/ovl_Boss_06/z_boss_06.o"
#ifdef NON_MATCHING
    include "build/src/overlays/actors/ovl_Boss_06/ovl_Boss_06_reloc.o"
#else
    include "build/data/ovl_Boss_06/ovl_Boss_06.reloc.o"
#endif
endseg

beginseg
    name "ovl_Boss_07"
    compress
    include "build/src/overlays/actors/ovl_Boss_07/z_boss_07.o"
    include "build/data/ovl_Boss_07/ovl_Boss_07.data.o"
    include "build/data/ovl_Boss_07/ovl_Boss_07.bss.o"
    include "build/data/ovl_Boss_07/ovl_Boss_07.reloc.o"
endseg

beginseg
    name "ovl_Bg_Dy_Yoseizo"
    compress
    include "build/src/overlays/actors/ovl_Bg_Dy_Yoseizo/z_bg_dy_yoseizo.o"
    include "build/src/overlays/actors/ovl_Bg_Dy_Yoseizo/ovl_Bg_Dy_Yoseizo_reloc.o"
endseg

beginseg
    name "ovl_En_Boj_05"
    compress
    include "build/src/overlays/actors/ovl_En_Boj_05/z_en_boj_05.o"
    include "build/src/overlays/actors/ovl_En_Boj_05/ovl_En_Boj_05_reloc.o"
endseg

beginseg
    name "ovl_En_Sob1"
    compress
    include "build/src/overlays/actors/ovl_En_Sob1/z_en_sob1.o"
    include "build/src/overlays/actors/ovl_En_Sob1/ovl_En_Sob1_reloc.o"
endseg

beginseg
    name "ovl_En_Go"
    compress
    include "build/src/overlays/actors/ovl_En_Go/z_en_go.o"
    include "build/src/overlays/actors/ovl_En_Go/ovl_En_Go_reloc.o"
endseg

beginseg
    name "ovl_En_Raf"
    compress
    include "build/src/overlays/actors/ovl_En_Raf/z_en_raf.o"
    include "build/src/overlays/actors/ovl_En_Raf/ovl_En_Raf_reloc.o"
endseg

beginseg
    name "ovl_Obj_Funen"
    compress
    include "build/src/overlays/actors/ovl_Obj_Funen/z_obj_funen.o"
    include "build/src/overlays/actors/ovl_Obj_Funen/ovl_Obj_Funen_reloc.o"
endseg

beginseg
    name "ovl_Obj_Raillift"
    compress
    include "build/src/overlays/actors/ovl_Obj_Raillift/z_obj_raillift.o"
    include "build/src/overlays/actors/ovl_Obj_Raillift/ovl_Obj_Raillift_reloc.o"
endseg

beginseg
    name "ovl_Bg_Numa_Hana"
    compress
    include "build/src/overlays/actors/ovl_Bg_Numa_Hana/z_bg_numa_hana.o"
    include "build/src/overlays/actors/ovl_Bg_Numa_Hana/ovl_Bg_Numa_Hana_reloc.o"
endseg

beginseg
    name "ovl_Obj_Flowerpot"
    compress
    include "build/src/overlays/actors/ovl_Obj_Flowerpot/z_obj_flowerpot.o"
    include "build/src/overlays/actors/ovl_Obj_Flowerpot/ovl_Obj_Flowerpot_reloc.o"
endseg

beginseg
    name "ovl_Obj_Spinyroll"
    compress
    include "build/src/overlays/actors/ovl_Obj_Spinyroll/z_obj_spinyroll.o"
    include "build/src/overlays/actors/ovl_Obj_Spinyroll/ovl_Obj_Spinyroll_reloc.o"
endseg

beginseg
    name "ovl_Dm_Hina"
    compress
    include "build/src/overlays/actors/ovl_Dm_Hina/z_dm_hina.o"
    include "build/src/overlays/actors/ovl_Dm_Hina/ovl_Dm_Hina_reloc.o"
endseg

beginseg
    name "ovl_En_Syateki_Wf"
    compress
    include "build/src/overlays/actors/ovl_En_Syateki_Wf/z_en_syateki_wf.o"
    include "build/src/overlays/actors/ovl_En_Syateki_Wf/ovl_En_Syateki_Wf_reloc.o"
endseg

beginseg
    name "ovl_Obj_Skateblock"
    compress
    include "build/src/overlays/actors/ovl_Obj_Skateblock/z_obj_skateblock.o"
    include "build/src/overlays/actors/ovl_Obj_Skateblock/ovl_Obj_Skateblock_reloc.o"
endseg

beginseg
    name "ovl_Effect_En_Ice_Block"
    compress
    include "build/src/overlays/effects/ovl_Effect_En_Ice_Block/z_eff_en_ice_block.o"
    include "build/src/overlays/effects/ovl_Effect_En_Ice_Block/ovl_Effect_En_Ice_Block_reloc.o"
endseg

beginseg
    name "ovl_Obj_Iceblock"
    compress
    include "build/src/overlays/actors/ovl_Obj_Iceblock/z_obj_iceblock.o"
    include "build/src/overlays/actors/ovl_Obj_Iceblock/ovl_Obj_Iceblock_reloc.o"
endseg

beginseg
    name "ovl_En_Bigpamet"
    compress
    include "build/src/overlays/actors/ovl_En_Bigpamet/z_en_bigpamet.o"
    include "build/src/overlays/actors/ovl_En_Bigpamet/ovl_En_Bigpamet_reloc.o"
endseg

beginseg
    name "ovl_Bg_Dblue_Movebg"
    compress
    include "build/src/overlays/actors/ovl_Bg_Dblue_Movebg/z_bg_dblue_movebg.o"
    include "build/src/overlays/actors/ovl_Bg_Dblue_Movebg/ovl_Bg_Dblue_Movebg_reloc.o"
endseg

beginseg
    name "ovl_En_Syateki_Dekunuts"
    compress
    include "build/src/overlays/actors/ovl_En_Syateki_Dekunuts/z_en_syateki_dekunuts.o"
    include "build/src/overlays/actors/ovl_En_Syateki_Dekunuts/ovl_En_Syateki_Dekunuts_reloc.o"
endseg

beginseg
    name "ovl_Elf_Msg3"
    compress
    include "build/src/overlays/actors/ovl_Elf_Msg3/z_elf_msg3.o"
    include "build/src/overlays/actors/ovl_Elf_Msg3/ovl_Elf_Msg3_reloc.o"
endseg

beginseg
    name "ovl_En_Fg"
    compress
    include "build/src/overlays/actors/ovl_En_Fg/z_en_fg.o"
    include "build/src/overlays/actors/ovl_En_Fg/ovl_En_Fg_reloc.o"
endseg

beginseg
    name "ovl_Dm_Ravine"
    compress
    include "build/src/overlays/actors/ovl_Dm_Ravine/z_dm_ravine.o"
    include "build/src/overlays/actors/ovl_Dm_Ravine/ovl_Dm_Ravine_reloc.o"
endseg

beginseg
    name "ovl_Dm_Sa"
    compress
    include "build/src/overlays/actors/ovl_Dm_Sa/z_dm_sa.o"
    include "build/src/overlays/actors/ovl_Dm_Sa/ovl_Dm_Sa_reloc.o"
endseg

beginseg
    name "ovl_En_Slime"
    compress
    include "build/src/overlays/actors/ovl_En_Slime/z_en_slime.o"
    include "build/src/overlays/actors/ovl_En_Slime/ovl_En_Slime_reloc.o"
endseg

beginseg
    name "ovl_En_Pr"
    compress
    include "build/src/overlays/actors/ovl_En_Pr/z_en_pr.o"
    include "build/src/overlays/actors/ovl_En_Pr/ovl_En_Pr_reloc.o"
endseg

beginseg
    name "ovl_Obj_Toudai"
    compress
    include "build/src/overlays/actors/ovl_Obj_Toudai/z_obj_toudai.o"
    include "build/src/overlays/actors/ovl_Obj_Toudai/ovl_Obj_Toudai_reloc.o"
endseg

beginseg
    name "ovl_Obj_Entotu"
    compress
    include "build/src/overlays/actors/ovl_Obj_Entotu/z_obj_entotu.o"
    include "build/src/overlays/actors/ovl_Obj_Entotu/ovl_Obj_Entotu_reloc.o"
endseg

beginseg
    name "ovl_Obj_Bell"
    compress
    include "build/src/overlays/actors/ovl_Obj_Bell/z_obj_bell.o"
    include "build/src/overlays/actors/ovl_Obj_Bell/ovl_Obj_Bell_reloc.o"
endseg

beginseg
    name "ovl_En_Syateki_Okuta"
    compress
    include "build/src/overlays/actors/ovl_En_Syateki_Okuta/z_en_syateki_okuta.o"
    include "build/src/overlays/actors/ovl_En_Syateki_Okuta/ovl_En_Syateki_Okuta_reloc.o"
endseg

beginseg
    name "ovl_Obj_Shutter"
    compress
    include "build/src/overlays/actors/ovl_Obj_Shutter/z_obj_shutter.o"
    include "build/src/overlays/actors/ovl_Obj_Shutter/ovl_Obj_Shutter_reloc.o"
endseg

beginseg
    name "ovl_Dm_Zl"
    compress
    include "build/src/overlays/actors/ovl_Dm_Zl/z_dm_zl.o"
    include "build/src/overlays/actors/ovl_Dm_Zl/ovl_Dm_Zl_reloc.o"
endseg

beginseg
    name "ovl_En_Ru"
    compress
    include "build/src/overlays/actors/ovl_En_Ru/z_en_ru.o"
    include "build/src/overlays/actors/ovl_En_Ru/ovl_En_Ru_reloc.o"
endseg

beginseg
    name "ovl_En_Elfgrp"
    compress
    include "build/src/overlays/actors/ovl_En_Elfgrp/z_en_elfgrp.o"
    include "build/src/overlays/actors/ovl_En_Elfgrp/ovl_En_Elfgrp_reloc.o"
endseg

beginseg
    name "ovl_Dm_Tsg"
    compress
    include "build/src/overlays/actors/ovl_Dm_Tsg/z_dm_tsg.o"
    include "build/data/ovl_Dm_Tsg/ovl_Dm_Tsg.data.o"
    include "build/data/ovl_Dm_Tsg/ovl_Dm_Tsg.reloc.o"
endseg

beginseg
    name "ovl_En_Baguo"
    compress
    include "build/src/overlays/actors/ovl_En_Baguo/z_en_baguo.o"
    include "build/src/overlays/actors/ovl_En_Baguo/ovl_En_Baguo_reloc.o"
endseg

beginseg
    name "ovl_Obj_Vspinyroll"
    compress
    include "build/src/overlays/actors/ovl_Obj_Vspinyroll/z_obj_vspinyroll.o"
    include "build/src/overlays/actors/ovl_Obj_Vspinyroll/ovl_Obj_Vspinyroll_reloc.o"
endseg

beginseg
    name "ovl_Obj_Smork"
    compress
    include "build/src/overlays/actors/ovl_Obj_Smork/z_obj_smork.o"
    include "build/src/overlays/actors/ovl_Obj_Smork/ovl_Obj_Smork_reloc.o"
endseg

beginseg
    name "ovl_En_Test2"
    compress
    include "build/src/overlays/actors/ovl_En_Test2/z_en_test2.o"
    include "build/src/overlays/actors/ovl_En_Test2/ovl_En_Test2_reloc.o"
endseg

beginseg
    name "ovl_En_Test3"
    compress
    include "build/src/overlays/actors/ovl_En_Test3/z_en_test3.o"
    include "build/src/overlays/actors/ovl_En_Test3/ovl_En_Test3_reloc.o"
endseg

beginseg
    name "ovl_En_Test4"
    compress
    include "build/src/overlays/actors/ovl_En_Test4/z_en_test4.o"
    include "build/src/overlays/actors/ovl_En_Test4/ovl_En_Test4_reloc.o"
endseg

beginseg
    name "ovl_En_Bat"
    compress
    include "build/src/overlays/actors/ovl_En_Bat/z_en_bat.o"
    include "build/src/overlays/actors/ovl_En_Bat/ovl_En_Bat_reloc.o"
endseg

beginseg
    name "ovl_En_Sekihi"
    compress
    include "build/src/overlays/actors/ovl_En_Sekihi/z_en_sekihi.o"
    include "build/src/overlays/actors/ovl_En_Sekihi/ovl_En_Sekihi_reloc.o"
endseg

beginseg
    name "ovl_En_Wiz"
    compress
    include "build/src/overlays/actors/ovl_En_Wiz/z_en_wiz.o"
    include "build/src/overlays/actors/ovl_En_Wiz/ovl_En_Wiz_reloc.o"
endseg

beginseg
    name "ovl_En_Wiz_Brock"
    compress
    include "build/src/overlays/actors/ovl_En_Wiz_Brock/z_en_wiz_brock.o"
    include "build/src/overlays/actors/ovl_En_Wiz_Brock/ovl_En_Wiz_Brock_reloc.o"
endseg

beginseg
    name "ovl_En_Wiz_Fire"
    compress
    include "build/src/overlays/actors/ovl_En_Wiz_Fire/z_en_wiz_fire.o"
    include "build/src/overlays/actors/ovl_En_Wiz_Fire/ovl_En_Wiz_Fire_reloc.o"
endseg

beginseg
    name "ovl_Eff_Change"
    compress
    include "build/src/overlays/actors/ovl_Eff_Change/z_eff_change.o"
    include "build/src/overlays/actors/ovl_Eff_Change/ovl_Eff_Change_reloc.o"
endseg

beginseg
    name "ovl_Dm_Statue"
    compress
    include "build/src/overlays/actors/ovl_Dm_Statue/z_dm_statue.o"
    include "build/src/overlays/actors/ovl_Dm_Statue/ovl_Dm_Statue_reloc.o"
endseg

beginseg
    name "ovl_Obj_Fireshield"
    compress
    include "build/src/overlays/actors/ovl_Obj_Fireshield/z_obj_fireshield.o"
    include "build/src/overlays/actors/ovl_Obj_Fireshield/ovl_Obj_Fireshield_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ladder"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ladder/z_bg_ladder.o"
    include "build/src/overlays/actors/ovl_Bg_Ladder/ovl_Bg_Ladder_reloc.o"
endseg

beginseg
    name "ovl_En_Mkk"
    compress
    include "build/src/overlays/actors/ovl_En_Mkk/z_en_mkk.o"
    include "build/src/overlays/actors/ovl_En_Mkk/ovl_En_Mkk_reloc.o"
endseg

beginseg
    name "ovl_Demo_Getitem"
    compress
    include "build/src/overlays/actors/ovl_Demo_Getitem/z_demo_getitem.o"
    include "build/src/overlays/actors/ovl_Demo_Getitem/ovl_Demo_Getitem_reloc.o"
endseg

beginseg
    name "ovl_En_Dnb"
    compress
    include "build/src/overlays/actors/ovl_En_Dnb/z_en_dnb.o"
    include "build/src/overlays/actors/ovl_En_Dnb/ovl_En_Dnb_reloc.o"
endseg

beginseg
    name "ovl_En_Dnh"
    compress
    include "build/src/overlays/actors/ovl_En_Dnh/z_en_dnh.o"
    include "build/src/overlays/actors/ovl_En_Dnh/ovl_En_Dnh_reloc.o"
endseg

beginseg
    name "ovl_En_Dnk"
    compress
    include "build/src/overlays/actors/ovl_En_Dnk/z_en_dnk.o"
    include "build/src/overlays/actors/ovl_En_Dnk/ovl_En_Dnk_reloc.o"
endseg

beginseg
    name "ovl_En_Dnq"
    compress
    include "build/src/overlays/actors/ovl_En_Dnq/z_en_dnq.o"
    include "build/src/overlays/actors/ovl_En_Dnq/ovl_En_Dnq_reloc.o"
endseg

beginseg
    name "ovl_Bg_Keikoku_Saku"
    compress
    include "build/src/overlays/actors/ovl_Bg_Keikoku_Saku/z_bg_keikoku_saku.o"
    include "build/src/overlays/actors/ovl_Bg_Keikoku_Saku/ovl_Bg_Keikoku_Saku_reloc.o"
endseg

beginseg
    name "ovl_Obj_Hugebombiwa"
    compress
    include "build/src/overlays/actors/ovl_Obj_Hugebombiwa/z_obj_hugebombiwa.o"
    include "build/src/overlays/actors/ovl_Obj_Hugebombiwa/ovl_Obj_Hugebombiwa_reloc.o"
endseg

beginseg
    name "ovl_En_Firefly2"
    compress
    include "build/src/overlays/actors/ovl_En_Firefly2/z_en_firefly2.o"
    include "build/src/overlays/actors/ovl_En_Firefly2/ovl_En_Firefly2_reloc.o"
endseg

beginseg
    name "ovl_En_Rat"
    compress
    include "build/src/overlays/actors/ovl_En_Rat/z_en_rat.o"
    include "build/src/overlays/actors/ovl_En_Rat/ovl_En_Rat_reloc.o"
endseg

beginseg
    name "ovl_En_Water_Effect"
    compress
    include "build/src/overlays/actors/ovl_En_Water_Effect/z_en_water_effect.o"
    include "build/src/overlays/actors/ovl_En_Water_Effect/ovl_En_Water_Effect_reloc.o"
endseg

beginseg
    name "ovl_En_Kusa2"
    compress
    include "build/src/overlays/actors/ovl_En_Kusa2/z_en_kusa2.o"
    include "build/src/overlays/actors/ovl_En_Kusa2/ovl_En_Kusa2_reloc.o"
endseg

beginseg
    name "ovl_Bg_Spout_Fire"
    compress
    include "build/src/overlays/actors/ovl_Bg_Spout_Fire/z_bg_spout_fire.o"
    include "build/src/overlays/actors/ovl_Bg_Spout_Fire/ovl_Bg_Spout_Fire_reloc.o"
endseg

beginseg
    name "ovl_En_Dy_Extra"
    compress
    include "build/src/overlays/actors/ovl_En_Dy_Extra/z_en_dy_extra.o"
    include "build/src/overlays/actors/ovl_En_Dy_Extra/ovl_En_Dy_Extra_reloc.o"
endseg

beginseg
    name "ovl_En_Bal"
    compress
    include "build/src/overlays/actors/ovl_En_Bal/z_en_bal.o"
    include "build/src/overlays/actors/ovl_En_Bal/ovl_En_Bal_reloc.o"
endseg

beginseg
    name "ovl_En_Ginko_Man"
    compress
    include "build/src/overlays/actors/ovl_En_Ginko_Man/z_en_ginko_man.o"
    include "build/src/overlays/actors/ovl_En_Ginko_Man/ovl_En_Ginko_Man_reloc.o"
endseg

beginseg
    name "ovl_En_Warp_Uzu"
    compress
    include "build/src/overlays/actors/ovl_En_Warp_Uzu/z_en_warp_uzu.o"
    include "build/src/overlays/actors/ovl_En_Warp_Uzu/ovl_En_Warp_Uzu_reloc.o"
endseg

beginseg
    name "ovl_Obj_Driftice"
    compress
    include "build/src/overlays/actors/ovl_Obj_Driftice/z_obj_driftice.o"
    include "build/src/overlays/actors/ovl_Obj_Driftice/ovl_Obj_Driftice_reloc.o"
endseg

beginseg
    name "ovl_En_Look_Nuts"
    compress
    include "build/src/overlays/actors/ovl_En_Look_Nuts/z_en_look_nuts.o"
    include "build/src/overlays/actors/ovl_En_Look_Nuts/ovl_En_Look_Nuts_reloc.o"
endseg

beginseg
    name "ovl_En_Mushi2"
    compress
    include "build/src/overlays/actors/ovl_En_Mushi2/z_en_mushi2.o"
    include "build/src/overlays/actors/ovl_En_Mushi2/ovl_En_Mushi2_reloc.o"
endseg

beginseg
    name "ovl_En_Fall"
    compress
    include "build/src/overlays/actors/ovl_En_Fall/z_en_fall.o"
    include "build/src/overlays/actors/ovl_En_Fall/ovl_En_Fall_reloc.o"
endseg

beginseg
    name "ovl_En_Mm3"
    compress
    include "build/src/overlays/actors/ovl_En_Mm3/z_en_mm3.o"
    include "build/src/overlays/actors/ovl_En_Mm3/ovl_En_Mm3_reloc.o"
endseg

beginseg
    name "ovl_Bg_Crace_Movebg"
    compress
    include "build/src/overlays/actors/ovl_Bg_Crace_Movebg/z_bg_crace_movebg.o"
    include "build/src/overlays/actors/ovl_Bg_Crace_Movebg/ovl_Bg_Crace_Movebg_reloc.o"
endseg

beginseg
    name "ovl_En_Dno"
    compress
    include "build/src/overlays/actors/ovl_En_Dno/z_en_dno.o"
    include "build/src/overlays/actors/ovl_En_Dno/ovl_En_Dno_reloc.o"
endseg

beginseg
    name "ovl_En_Pr2"
    compress
    include "build/src/overlays/actors/ovl_En_Pr2/z_en_pr2.o"
    include "build/src/overlays/actors/ovl_En_Pr2/ovl_En_Pr2_reloc.o"
endseg

beginseg
    name "ovl_En_Prz"
    compress
    include "build/src/overlays/actors/ovl_En_Prz/z_en_prz.o"
    include "build/src/overlays/actors/ovl_En_Prz/ovl_En_Prz_reloc.o"
endseg

beginseg
    name "ovl_En_Jso2"
    compress
    include "build/src/overlays/actors/ovl_En_Jso2/z_en_jso2.o"
    include "build/data/ovl_En_Jso2/ovl_En_Jso2.data.o"
    include "build/data/ovl_En_Jso2/ovl_En_Jso2.reloc.o"
endseg

beginseg
    name "ovl_Obj_Etcetera"
    compress
    include "build/src/overlays/actors/ovl_Obj_Etcetera/z_obj_etcetera.o"
    include "build/src/overlays/actors/ovl_Obj_Etcetera/ovl_Obj_Etcetera_reloc.o"
endseg

beginseg
    name "ovl_En_Egol"
    compress
    include "build/src/overlays/actors/ovl_En_Egol/z_en_egol.o"
    include "build/src/overlays/actors/ovl_En_Egol/ovl_En_Egol_reloc.o"
endseg

beginseg
    name "ovl_Obj_Mine"
    compress
    include "build/src/overlays/actors/ovl_Obj_Mine/z_obj_mine.o"
    include "build/data/ovl_Obj_Mine/ovl_Obj_Mine.data.o"
    include "build/data/ovl_Obj_Mine/ovl_Obj_Mine.bss.o"
    include "build/data/ovl_Obj_Mine/ovl_Obj_Mine.reloc.o"
endseg

beginseg
    name "ovl_Obj_Purify"
    compress
    include "build/src/overlays/actors/ovl_Obj_Purify/z_obj_purify.o"
    include "build/src/overlays/actors/ovl_Obj_Purify/ovl_Obj_Purify_reloc.o"
endseg

beginseg
    name "ovl_En_Tru"
    compress
    include "build/src/overlays/actors/ovl_En_Tru/z_en_tru.o"
    include "build/src/overlays/actors/ovl_En_Tru/ovl_En_Tru_reloc.o"
endseg

beginseg
    name "ovl_En_Trt"
    compress
    include "build/src/overlays/actors/ovl_En_Trt/z_en_trt.o"
    include "build/src/overlays/actors/ovl_En_Trt/ovl_En_Trt_reloc.o"
endseg

beginseg
    name "ovl_En_Test5"
    compress
    include "build/src/overlays/actors/ovl_En_Test5/z_en_test5.o"
    include "build/src/overlays/actors/ovl_En_Test5/ovl_En_Test5_reloc.o"
endseg

beginseg
    name "ovl_En_Test6"
    compress
    include "build/src/overlays/actors/ovl_En_Test6/z_en_test6.o"
    include "build/src/overlays/actors/ovl_En_Test6/ovl_En_Test6_reloc.o"
endseg

beginseg
    name "ovl_En_Az"
    compress
    include "build/src/overlays/actors/ovl_En_Az/z_en_az.o"
    include "build/src/overlays/actors/ovl_En_Az/ovl_En_Az_reloc.o"
endseg

beginseg
    name "ovl_En_Estone"
    compress
    include "build/src/overlays/actors/ovl_En_Estone/z_en_estone.o"
    include "build/src/overlays/actors/ovl_En_Estone/ovl_En_Estone_reloc.o"
endseg

beginseg
    name "ovl_Bg_Hakugin_Post"
    compress
    include "build/src/overlays/actors/ovl_Bg_Hakugin_Post/z_bg_hakugin_post.o"
    include "build/src/overlays/actors/ovl_Bg_Hakugin_Post/ovl_Bg_Hakugin_Post_reloc.o"
endseg

beginseg
    name "ovl_Dm_Opstage"
    compress
    include "build/src/overlays/actors/ovl_Dm_Opstage/z_dm_opstage.o"
    include "build/src/overlays/actors/ovl_Dm_Opstage/ovl_Dm_Opstage_reloc.o"
endseg

beginseg
    name "ovl_Dm_Stk"
    compress
    include "build/src/overlays/actors/ovl_Dm_Stk/z_dm_stk.o"
    include "build/src/overlays/actors/ovl_Dm_Stk/ovl_Dm_Stk_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char00"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char00/z_dm_char00.o"
    include "build/src/overlays/actors/ovl_Dm_Char00/ovl_Dm_Char00_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char01"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char01/z_dm_char01.o"
    include "build/src/overlays/actors/ovl_Dm_Char01/ovl_Dm_Char01_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char02"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char02/z_dm_char02.o"
    include "build/src/overlays/actors/ovl_Dm_Char02/ovl_Dm_Char02_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char03"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char03/z_dm_char03.o"
    include "build/src/overlays/actors/ovl_Dm_Char03/ovl_Dm_Char03_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char04"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char04/z_dm_char04.o"
    include "build/src/overlays/actors/ovl_Dm_Char04/ovl_Dm_Char04_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char05"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char05/z_dm_char05.o"
    include "build/src/overlays/actors/ovl_Dm_Char05/ovl_Dm_Char05_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char06"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char06/z_dm_char06.o"
    include "build/src/overlays/actors/ovl_Dm_Char06/ovl_Dm_Char06_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char07"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char07/z_dm_char07.o"
    include "build/src/overlays/actors/ovl_Dm_Char07/ovl_Dm_Char07_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char08"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char08/z_dm_char08.o"
    include "build/src/overlays/actors/ovl_Dm_Char08/ovl_Dm_Char08_reloc.o"
endseg

beginseg
    name "ovl_Dm_Char09"
    compress
    include "build/src/overlays/actors/ovl_Dm_Char09/z_dm_char09.o"
    include "build/src/overlays/actors/ovl_Dm_Char09/ovl_Dm_Char09_reloc.o"
endseg

beginseg
    name "ovl_Obj_Tokeidai"
    compress
    include "build/src/overlays/actors/ovl_Obj_Tokeidai/z_obj_tokeidai.o"
    include "build/src/overlays/actors/ovl_Obj_Tokeidai/ovl_Obj_Tokeidai_reloc.o"
endseg

beginseg
    name "ovl_En_Mnk"
    compress
    include "build/src/overlays/actors/ovl_En_Mnk/z_en_mnk.o"
    include "build/src/overlays/actors/ovl_En_Mnk/ovl_En_Mnk_reloc.o"
endseg

beginseg
    name "ovl_En_Egblock"
    compress
    include "build/src/overlays/actors/ovl_En_Egblock/z_en_egblock.o"
    include "build/src/overlays/actors/ovl_En_Egblock/ovl_En_Egblock_reloc.o"
endseg

beginseg
    name "ovl_En_Guard_Nuts"
    compress
    include "build/src/overlays/actors/ovl_En_Guard_Nuts/z_en_guard_nuts.o"
    include "build/src/overlays/actors/ovl_En_Guard_Nuts/ovl_En_Guard_Nuts_reloc.o"
endseg

beginseg
    name "ovl_Bg_Hakugin_Bombwall"
    compress
    include "build/src/overlays/actors/ovl_Bg_Hakugin_Bombwall/z_bg_hakugin_bombwall.o"
    include "build/src/overlays/actors/ovl_Bg_Hakugin_Bombwall/ovl_Bg_Hakugin_Bombwall_reloc.o"
endseg

beginseg
    name "ovl_Obj_Tokei_Tobira"
    compress
    include "build/src/overlays/actors/ovl_Obj_Tokei_Tobira/z_obj_tokei_tobira.o"
    include "build/src/overlays/actors/ovl_Obj_Tokei_Tobira/ovl_Obj_Tokei_Tobira_reloc.o"
endseg

beginseg
    name "ovl_Bg_Hakugin_Elvpole"
    compress
    include "build/src/overlays/actors/ovl_Bg_Hakugin_Elvpole/z_bg_hakugin_elvpole.o"
    include "build/src/overlays/actors/ovl_Bg_Hakugin_Elvpole/ovl_Bg_Hakugin_Elvpole_reloc.o"
endseg

beginseg
    name "ovl_En_Ma4"
    compress
    include "build/src/overlays/actors/ovl_En_Ma4/z_en_ma4.o"
    include "build/src/overlays/actors/ovl_En_Ma4/ovl_En_Ma4_reloc.o"
endseg

beginseg
    name "ovl_En_Twig"
    compress
    include "build/src/overlays/actors/ovl_En_Twig/z_en_twig.o"
    include "build/src/overlays/actors/ovl_En_Twig/ovl_En_Twig_reloc.o"
endseg

beginseg
    name "ovl_En_Po_Fusen"
    compress
    include "build/src/overlays/actors/ovl_En_Po_Fusen/z_en_po_fusen.o"
    include "build/src/overlays/actors/ovl_En_Po_Fusen/ovl_En_Po_Fusen_reloc.o"
endseg

beginseg
    name "ovl_En_Door_Etc"
    compress
    include "build/src/overlays/actors/ovl_En_Door_Etc/z_en_door_etc.o"
    include "build/src/overlays/actors/ovl_En_Door_Etc/ovl_En_Door_Etc_reloc.o"
endseg

beginseg
    name "ovl_En_Bigokuta"
    compress
    include "build/src/overlays/actors/ovl_En_Bigokuta/z_en_bigokuta.o"
    include "build/src/overlays/actors/ovl_En_Bigokuta/ovl_En_Bigokuta_reloc.o"
endseg

beginseg
    name "ovl_Bg_Icefloe"
    compress
    include "build/src/overlays/actors/ovl_Bg_Icefloe/z_bg_icefloe.o"
    include "build/src/overlays/actors/ovl_Bg_Icefloe/ovl_Bg_Icefloe_reloc.o"
endseg

beginseg
    name "ovl_fbdemo_triforce"
    compress
    include "build/src/overlays/fbdemos/ovl_fbdemo_triforce/z_fbdemo_triforce.o"
    include "build/src/overlays/fbdemos/ovl_fbdemo_triforce/ovl_fbdemo_triforce_reloc.o"
endseg

beginseg
    name "ovl_fbdemo_wipe1"
    compress
    include "build/src/overlays/fbdemos/ovl_fbdemo_wipe1/z_fbdemo_wipe1.o"
    include "build/src/overlays/fbdemos/ovl_fbdemo_wipe1/ovl_fbdemo_wipe1_reloc.o"
endseg

beginseg
    name "ovl_fbdemo_wipe3"
    compress
    include "build/src/overlays/fbdemos/ovl_fbdemo_wipe3/z_fbdemo_wipe3.o"
    include "build/src/overlays/fbdemos/ovl_fbdemo_wipe3/ovl_fbdemo_wipe3_reloc.o"
endseg

beginseg
    name "ovl_fbdemo_wipe4"
    compress
    include "build/src/overlays/fbdemos/ovl_fbdemo_wipe4/z_fbdemo_wipe4.o"
    include "build/data/ovl_fbdemo_wipe4/ovl_fbdemo_wipe4.data.o"
    include "build/data/ovl_fbdemo_wipe4/ovl_fbdemo_wipe4.reloc.o"
endseg

beginseg
    name "ovl_fbdemo_wipe5"
    compress
    include "build/src/overlays/fbdemos/ovl_fbdemo_wipe5/z_fbdemo_wipe5.o"
    include "build/src/overlays/fbdemos/ovl_fbdemo_wipe5/ovl_fbdemo_wipe5_reloc.o"
endseg

beginseg
    name "ovl_Effect_Ss_Sbn"
    compress
    include "build/src/overlays/effects/ovl_Effect_Ss_Sbn/z_eff_ss_sbn.o"
    include "build/src/overlays/effects/ovl_Effect_Ss_Sbn/ovl_Effect_Ss_Sbn_reloc.o"
endseg

beginseg
    name "ovl_Obj_Ocarinalift"
    compress
    include "build/src/overlays/actors/ovl_Obj_Ocarinalift/z_obj_ocarinalift.o"
    include "build/src/overlays/actors/ovl_Obj_Ocarinalift/ovl_Obj_Ocarinalift_reloc.o"
endseg

beginseg
    name "ovl_En_Time_Tag"
    compress
    include "build/src/overlays/actors/ovl_En_Time_Tag/z_en_time_tag.o"
    include "build/src/overlays/actors/ovl_En_Time_Tag/ovl_En_Time_Tag_reloc.o"
endseg

beginseg
    name "ovl_Bg_Open_Shutter"
    compress
    include "build/src/overlays/actors/ovl_Bg_Open_Shutter/z_bg_open_shutter.o"
    include "build/src/overlays/actors/ovl_Bg_Open_Shutter/ovl_Bg_Open_Shutter_reloc.o"
endseg

beginseg
    name "ovl_Bg_Open_Spot"
    compress
    include "build/src/overlays/actors/ovl_Bg_Open_Spot/z_bg_open_spot.o"
    include "build/src/overlays/actors/ovl_Bg_Open_Spot/ovl_Bg_Open_Spot_reloc.o"
endseg

beginseg
    name "ovl_Bg_Fu_Kaiten"
    compress
    include "build/src/overlays/actors/ovl_Bg_Fu_Kaiten/z_bg_fu_kaiten.o"
    include "build/src/overlays/actors/ovl_Bg_Fu_Kaiten/ovl_Bg_Fu_Kaiten_reloc.o"
endseg

beginseg
    name "ovl_Obj_Aqua"
    compress
    include "build/src/overlays/actors/ovl_Obj_Aqua/z_obj_aqua.o"
    include "build/src/overlays/actors/ovl_Obj_Aqua/ovl_Obj_Aqua_reloc.o"
endseg

beginseg
    name "ovl_En_Elforg"
    compress
    include "build/src/overlays/actors/ovl_En_Elforg/z_en_elforg.o"
    include "build/src/overlays/actors/ovl_En_Elforg/ovl_En_Elforg_reloc.o"
endseg

beginseg
    name "ovl_En_Elfbub"
    compress
    include "build/src/overlays/actors/ovl_En_Elfbub/z_en_elfbub.o"
    include "build/src/overlays/actors/ovl_En_Elfbub/ovl_En_Elfbub_reloc.o"
endseg

beginseg
    name "ovl_En_Fu_Mato"
    compress
    include "build/src/overlays/actors/ovl_En_Fu_Mato/z_en_fu_mato.o"
    include "build/src/overlays/actors/ovl_En_Fu_Mato/ovl_En_Fu_Mato_reloc.o"
endseg

beginseg
    name "ovl_En_Fu_Kago"
    compress
    include "build/src/overlays/actors/ovl_En_Fu_Kago/z_en_fu_kago.o"
    include "build/src/overlays/actors/ovl_En_Fu_Kago/ovl_En_Fu_Kago_reloc.o"
endseg

beginseg
    name "ovl_En_Osn"
    compress
    include "build/src/overlays/actors/ovl_En_Osn/z_en_osn.o"
    include "build/src/overlays/actors/ovl_En_Osn/ovl_En_Osn_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ctower_Gear"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ctower_Gear/z_bg_ctower_gear.o"
    include "build/src/overlays/actors/ovl_Bg_Ctower_Gear/ovl_Bg_Ctower_Gear_reloc.o"
endseg

beginseg
    name "ovl_En_Trt2"
    compress
    include "build/src/overlays/actors/ovl_En_Trt2/z_en_trt2.o"
    include "build/src/overlays/actors/ovl_En_Trt2/ovl_En_Trt2_reloc.o"
endseg

beginseg
    name "ovl_Obj_Tokei_Step"
    compress
    include "build/src/overlays/actors/ovl_Obj_Tokei_Step/z_obj_tokei_step.o"
    include "build/src/overlays/actors/ovl_Obj_Tokei_Step/ovl_Obj_Tokei_Step_reloc.o"
endseg

beginseg
    name "ovl_Bg_Lotus"
    compress
    include "build/src/overlays/actors/ovl_Bg_Lotus/z_bg_lotus.o"
    include "build/src/overlays/actors/ovl_Bg_Lotus/ovl_Bg_Lotus_reloc.o"
endseg

beginseg
    name "ovl_En_Kame"
    compress
    include "build/src/overlays/actors/ovl_En_Kame/z_en_kame.o"
    include "build/src/overlays/actors/ovl_En_Kame/ovl_En_Kame_reloc.o"
endseg

beginseg
    name "ovl_Obj_Takaraya_Wall"
    compress
    include "build/src/overlays/actors/ovl_Obj_Takaraya_Wall/z_obj_takaraya_wall.o"
    include "build/data/ovl_Obj_Takaraya_Wall/ovl_Obj_Takaraya_Wall.data.o"
    include "build/data/ovl_Obj_Takaraya_Wall/ovl_Obj_Takaraya_Wall.bss.o"
    include "build/data/ovl_Obj_Takaraya_Wall/ovl_Obj_Takaraya_Wall.reloc.o"
endseg

beginseg
    name "ovl_Bg_Fu_Mizu"
    compress
    include "build/src/overlays/actors/ovl_Bg_Fu_Mizu/z_bg_fu_mizu.o"
    include "build/src/overlays/actors/ovl_Bg_Fu_Mizu/ovl_Bg_Fu_Mizu_reloc.o"
endseg

beginseg
    name "ovl_En_Sellnuts"
    compress
    include "build/src/overlays/actors/ovl_En_Sellnuts/z_en_sellnuts.o"
    include "build/src/overlays/actors/ovl_En_Sellnuts/ovl_En_Sellnuts_reloc.o"
endseg

beginseg
    name "ovl_Bg_Dkjail_Ivy"
    compress
    include "build/src/overlays/actors/ovl_Bg_Dkjail_Ivy/z_bg_dkjail_ivy.o"
    include "build/src/overlays/actors/ovl_Bg_Dkjail_Ivy/ovl_Bg_Dkjail_Ivy_reloc.o"
endseg

beginseg
    name "ovl_Obj_Visiblock"
    compress
    include "build/src/overlays/actors/ovl_Obj_Visiblock/z_obj_visiblock.o"
    include "build/src/overlays/actors/ovl_Obj_Visiblock/ovl_Obj_Visiblock_reloc.o"
endseg

beginseg
    name "ovl_En_Takaraya"
    compress
    include "build/src/overlays/actors/ovl_En_Takaraya/z_en_takaraya.o"
    include "build/data/ovl_En_Takaraya/ovl_En_Takaraya.data.o"
    include "build/data/ovl_En_Takaraya/ovl_En_Takaraya.reloc.o"
endseg

beginseg
    name "ovl_En_Tsn"
    compress
    include "build/src/overlays/actors/ovl_En_Tsn/z_en_tsn.o"
    include "build/src/overlays/actors/ovl_En_Tsn/ovl_En_Tsn_reloc.o"
endseg

beginseg
    name "ovl_En_Ds2n"
    compress
    include "build/src/overlays/actors/ovl_En_Ds2n/z_en_ds2n.o"
    include "build/src/overlays/actors/ovl_En_Ds2n/ovl_En_Ds2n_reloc.o"
endseg

beginseg
    name "ovl_En_Fsn"
    compress
    include "build/src/overlays/actors/ovl_En_Fsn/z_en_fsn.o"
    include "build/src/overlays/actors/ovl_En_Fsn/ovl_En_Fsn_reloc.o"
endseg

beginseg
    name "ovl_En_Shn"
    compress
    include "build/src/overlays/actors/ovl_En_Shn/z_en_shn.o"
    include "build/src/overlays/actors/ovl_En_Shn/ovl_En_Shn_reloc.o"
endseg

beginseg
    name "ovl_En_Stop_heishi"
    compress
    include "build/src/overlays/actors/ovl_En_Stop_heishi/z_en_stop_heishi.o"
    include "build/src/overlays/actors/ovl_En_Stop_heishi/ovl_En_Stop_heishi_reloc.o"
endseg

beginseg
    name "ovl_Obj_Bigicicle"
    compress
    include "build/src/overlays/actors/ovl_Obj_Bigicicle/z_obj_bigicicle.o"
    include "build/src/overlays/actors/ovl_Obj_Bigicicle/ovl_Obj_Bigicicle_reloc.o"
endseg

beginseg
    name "ovl_En_Lift_Nuts"
    compress
    include "build/src/overlays/actors/ovl_En_Lift_Nuts/z_en_lift_nuts.o"
    include "build/src/overlays/actors/ovl_En_Lift_Nuts/ovl_En_Lift_Nuts_reloc.o"
endseg

beginseg
    name "ovl_En_Tk"
    compress
    include "build/src/overlays/actors/ovl_En_Tk/z_en_tk.o"
    include "build/src/overlays/actors/ovl_En_Tk/ovl_En_Tk_reloc.o"
endseg

beginseg
    name "ovl_Bg_Market_Step"
    compress
    include "build/src/overlays/actors/ovl_Bg_Market_Step/z_bg_market_step.o"
    include "build/src/overlays/actors/ovl_Bg_Market_Step/ovl_Bg_Market_Step_reloc.o"
endseg

beginseg
    name "ovl_Obj_Lupygamelift"
    compress
    include "build/src/overlays/actors/ovl_Obj_Lupygamelift/z_obj_lupygamelift.o"
    include "build/src/overlays/actors/ovl_Obj_Lupygamelift/ovl_Obj_Lupygamelift_reloc.o"
endseg

beginseg
    name "ovl_En_Test7"
    compress
    include "build/src/overlays/actors/ovl_En_Test7/z_en_test7.o"
    include "build/src/overlays/actors/ovl_En_Test7/ovl_En_Test7_reloc.o"
endseg

beginseg
    name "ovl_Obj_Lightblock"
    compress
    include "build/src/overlays/actors/ovl_Obj_Lightblock/z_obj_lightblock.o"
    include "build/src/overlays/actors/ovl_Obj_Lightblock/ovl_Obj_Lightblock_reloc.o"
endseg

beginseg
    name "ovl_Mir_Ray2"
    compress
    include "build/src/overlays/actors/ovl_Mir_Ray2/z_mir_ray2.o"
    include "build/src/overlays/actors/ovl_Mir_Ray2/ovl_Mir_Ray2_reloc.o"
endseg

beginseg
    name "ovl_En_Wdhand"
    compress
    include "build/src/overlays/actors/ovl_En_Wdhand/z_en_wdhand.o"
    include "build/data/ovl_En_Wdhand/ovl_En_Wdhand.data.o"
    include "build/data/ovl_En_Wdhand/ovl_En_Wdhand.reloc.o"
endseg

beginseg
    name "ovl_En_Gamelupy"
    compress
    include "build/src/overlays/actors/ovl_En_Gamelupy/z_en_gamelupy.o"
    include "build/src/overlays/actors/ovl_En_Gamelupy/ovl_En_Gamelupy_reloc.o"
endseg

beginseg
    name "ovl_Bg_Danpei_Movebg"
    compress
    include "build/src/overlays/actors/ovl_Bg_Danpei_Movebg/z_bg_danpei_movebg.o"
    include "build/data/ovl_Bg_Danpei_Movebg/ovl_Bg_Danpei_Movebg.data.o"
    include "build/data/ovl_Bg_Danpei_Movebg/ovl_Bg_Danpei_Movebg.reloc.o"
endseg

beginseg
    name "ovl_En_Snowwd"
    compress
    include "build/src/overlays/actors/ovl_En_Snowwd/z_en_snowwd.o"
    include "build/src/overlays/actors/ovl_En_Snowwd/ovl_En_Snowwd_reloc.o"
endseg

beginseg
    name "ovl_En_Pm"
    compress
    include "build/src/overlays/actors/ovl_En_Pm/z_en_pm.o"
    include "build/src/overlays/actors/ovl_En_Pm/ovl_En_Pm_reloc.o"
endseg

beginseg
    name "ovl_En_Gakufu"
    compress
    include "build/src/overlays/actors/ovl_En_Gakufu/z_en_gakufu.o"
    include "build/src/overlays/actors/ovl_En_Gakufu/ovl_En_Gakufu_reloc.o"
endseg

beginseg
    name "ovl_Elf_Msg4"
    compress
    include "build/src/overlays/actors/ovl_Elf_Msg4/z_elf_msg4.o"
    include "build/src/overlays/actors/ovl_Elf_Msg4/ovl_Elf_Msg4_reloc.o"
endseg

beginseg
    name "ovl_Elf_Msg5"
    compress
    include "build/src/overlays/actors/ovl_Elf_Msg5/z_elf_msg5.o"
    include "build/src/overlays/actors/ovl_Elf_Msg5/ovl_Elf_Msg5_reloc.o"
endseg

beginseg
    name "ovl_En_Col_Man"
    compress
    include "build/src/overlays/actors/ovl_En_Col_Man/z_en_col_man.o"
    include "build/src/overlays/actors/ovl_En_Col_Man/ovl_En_Col_Man_reloc.o"
endseg

beginseg
    name "ovl_En_Talk_Gibud"
    compress
    include "build/src/overlays/actors/ovl_En_Talk_Gibud/z_en_talk_gibud.o"
    include "build/src/overlays/actors/ovl_En_Talk_Gibud/ovl_En_Talk_Gibud_reloc.o"
endseg

beginseg
    name "ovl_En_Giant"
    compress
    include "build/src/overlays/actors/ovl_En_Giant/z_en_giant.o"
    include "build/src/overlays/actors/ovl_En_Giant/ovl_En_Giant_reloc.o"
endseg

beginseg
    name "ovl_Obj_Snowball"
    compress
    include "build/src/overlays/actors/ovl_Obj_Snowball/z_obj_snowball.o"
    include "build/src/overlays/actors/ovl_Obj_Snowball/ovl_Obj_Snowball_reloc.o"
endseg

beginseg
    name "ovl_Boss_Hakugin"
    compress
    include "build/src/overlays/actors/ovl_Boss_Hakugin/z_boss_hakugin.o"
    include "build/data/ovl_Boss_Hakugin/ovl_Boss_Hakugin.data.o"
    include "build/data/ovl_Boss_Hakugin/ovl_Boss_Hakugin.reloc.o"
endseg

beginseg
    name "ovl_En_Gb2"
    compress
    include "build/src/overlays/actors/ovl_En_Gb2/z_en_gb2.o"
    include "build/src/overlays/actors/ovl_En_Gb2/ovl_En_Gb2_reloc.o"
endseg

beginseg
    name "ovl_En_Onpuman"
    compress
    include "build/src/overlays/actors/ovl_En_Onpuman/z_en_onpuman.o"
    include "build/src/overlays/actors/ovl_En_Onpuman/ovl_En_Onpuman_reloc.o"
endseg

beginseg
    name "ovl_Bg_Tobira01"
    compress
    include "build/src/overlays/actors/ovl_Bg_Tobira01/z_bg_tobira01.o"
    include "build/src/overlays/actors/ovl_Bg_Tobira01/ovl_Bg_Tobira01_reloc.o"
endseg

beginseg
    name "ovl_En_Tag_Obj"
    compress
    include "build/src/overlays/actors/ovl_En_Tag_Obj/z_en_tag_obj.o"
    include "build/src/overlays/actors/ovl_En_Tag_Obj/ovl_En_Tag_Obj_reloc.o"
endseg

beginseg
    name "ovl_Obj_Dhouse"
    compress
    include "build/src/overlays/actors/ovl_Obj_Dhouse/z_obj_dhouse.o"
    include "build/src/overlays/actors/ovl_Obj_Dhouse/ovl_Obj_Dhouse_reloc.o"
endseg

beginseg
    name "ovl_Obj_Hakaisi"
    compress
    include "build/src/overlays/actors/ovl_Obj_Hakaisi/z_obj_hakaisi.o"
    include "build/src/overlays/actors/ovl_Obj_Hakaisi/ovl_Obj_Hakaisi_reloc.o"
endseg

beginseg
    name "ovl_Bg_Hakugin_Switch"
    compress
    include "build/src/overlays/actors/ovl_Bg_Hakugin_Switch/z_bg_hakugin_switch.o"
    include "build/src/overlays/actors/ovl_Bg_Hakugin_Switch/ovl_Bg_Hakugin_Switch_reloc.o"
endseg

beginseg
    name "ovl_En_Snowman"
    compress
    include "build/src/overlays/actors/ovl_En_Snowman/z_en_snowman.o"
    include "build/src/overlays/actors/ovl_En_Snowman/ovl_En_Snowman_reloc.o"
endseg

beginseg
    name "ovl_TG_Sw"
    compress
    include "build/src/overlays/actors/ovl_TG_Sw/z_tg_sw.o"
    include "build/src/overlays/actors/ovl_TG_Sw/ovl_TG_Sw_reloc.o"
endseg

beginseg
    name "ovl_En_Po_Sisters"
    compress
    include "build/src/overlays/actors/ovl_En_Po_Sisters/z_en_po_sisters.o"
    include "build/src/overlays/actors/ovl_En_Po_Sisters/ovl_En_Po_Sisters_reloc.o"
endseg

beginseg
    name "ovl_En_Pp"
    compress
    include "build/src/overlays/actors/ovl_En_Pp/z_en_pp.o"
    include "build/src/overlays/actors/ovl_En_Pp/ovl_En_Pp_reloc.o"
endseg

beginseg
    name "ovl_En_Hakurock"
    compress
    include "build/src/overlays/actors/ovl_En_Hakurock/z_en_hakurock.o"
    include "build/src/overlays/actors/ovl_En_Hakurock/ovl_En_Hakurock_reloc.o"
endseg

beginseg
    name "ovl_En_Hanabi"
    compress
    include "build/src/overlays/actors/ovl_En_Hanabi/z_en_hanabi.o"
    include "build/src/overlays/actors/ovl_En_Hanabi/ovl_En_Hanabi_reloc.o"
endseg

beginseg
    name "ovl_Obj_Dowsing"
    compress
    include "build/src/overlays/actors/ovl_Obj_Dowsing/z_obj_dowsing.o"
    include "build/src/overlays/actors/ovl_Obj_Dowsing/ovl_Obj_Dowsing_reloc.o"
endseg

beginseg
    name "ovl_Obj_Wind"
    compress
    include "build/src/overlays/actors/ovl_Obj_Wind/z_obj_wind.o"
    include "build/src/overlays/actors/ovl_Obj_Wind/ovl_Obj_Wind_reloc.o"
endseg

beginseg
    name "ovl_En_Racedog"
    compress
    include "build/src/overlays/actors/ovl_En_Racedog/z_en_racedog.o"
    include "build/src/overlays/actors/ovl_En_Racedog/ovl_En_Racedog_reloc.o"
endseg

beginseg
    name "ovl_En_Kendo_Js"
    compress
    include "build/src/overlays/actors/ovl_En_Kendo_Js/z_en_kendo_js.o"
    include "build/src/overlays/actors/ovl_En_Kendo_Js/ovl_En_Kendo_Js_reloc.o"
endseg

beginseg
    name "ovl_Bg_Botihasira"
    compress
    include "build/src/overlays/actors/ovl_Bg_Botihasira/z_bg_botihasira.o"
    include "build/src/overlays/actors/ovl_Bg_Botihasira/ovl_Bg_Botihasira_reloc.o"
endseg

beginseg
    name "ovl_En_Fish2"
    compress
    include "build/src/overlays/actors/ovl_En_Fish2/z_en_fish2.o"
    include "build/src/overlays/actors/ovl_En_Fish2/ovl_En_Fish2_reloc.o"
endseg

beginseg
    name "ovl_En_Pst"
    compress
    include "build/src/overlays/actors/ovl_En_Pst/z_en_pst.o"
    include "build/src/overlays/actors/ovl_En_Pst/ovl_En_Pst_reloc.o"
endseg

beginseg
    name "ovl_En_Poh"
    compress
    include "build/src/overlays/actors/ovl_En_Poh/z_en_poh.o"
    include "build/src/overlays/actors/ovl_En_Poh/ovl_En_Poh_reloc.o"
endseg

beginseg
    name "ovl_Obj_Spidertent"
    compress
    include "build/src/overlays/actors/ovl_Obj_Spidertent/z_obj_spidertent.o"
    include "build/src/overlays/actors/ovl_Obj_Spidertent/ovl_Obj_Spidertent_reloc.o"
endseg

beginseg
    name "ovl_En_Zoraegg"
    compress
    include "build/src/overlays/actors/ovl_En_Zoraegg/z_en_zoraegg.o"
    include "build/src/overlays/actors/ovl_En_Zoraegg/ovl_En_Zoraegg_reloc.o"
endseg

beginseg
    name "ovl_En_Kbt"
    compress
    include "build/src/overlays/actors/ovl_En_Kbt/z_en_kbt.o"
    include "build/src/overlays/actors/ovl_En_Kbt/ovl_En_Kbt_reloc.o"
endseg

beginseg
    name "ovl_En_Gg"
    compress
    include "build/src/overlays/actors/ovl_En_Gg/z_en_gg.o"
    include "build/src/overlays/actors/ovl_En_Gg/ovl_En_Gg_reloc.o"
endseg

beginseg
    name "ovl_En_Maruta"
    compress
    include "build/src/overlays/actors/ovl_En_Maruta/z_en_maruta.o"
    include "build/src/overlays/actors/ovl_En_Maruta/ovl_En_Maruta_reloc.o"
endseg

beginseg
    name "ovl_Obj_Snowball2"
    compress
    include "build/src/overlays/actors/ovl_Obj_Snowball2/z_obj_snowball2.o"
    include "build/src/overlays/actors/ovl_Obj_Snowball2/ovl_Obj_Snowball2_reloc.o"
endseg

beginseg
    name "ovl_En_Gg2"
    compress
    include "build/src/overlays/actors/ovl_En_Gg2/z_en_gg2.o"
    include "build/src/overlays/actors/ovl_En_Gg2/ovl_En_Gg2_reloc.o"
endseg

beginseg
    name "ovl_Obj_Ghaka"
    compress
    include "build/src/overlays/actors/ovl_Obj_Ghaka/z_obj_ghaka.o"
    include "build/src/overlays/actors/ovl_Obj_Ghaka/ovl_Obj_Ghaka_reloc.o"
endseg

beginseg
    name "ovl_En_Dnp"
    compress
    include "build/src/overlays/actors/ovl_En_Dnp/z_en_dnp.o"
    include "build/src/overlays/actors/ovl_En_Dnp/ovl_En_Dnp_reloc.o"
endseg

beginseg
    name "ovl_En_Dai"
    compress
    include "build/src/overlays/actors/ovl_En_Dai/z_en_dai.o"
    include "build/src/overlays/actors/ovl_En_Dai/ovl_En_Dai_reloc.o"
endseg

beginseg
    name "ovl_Bg_Goron_Oyu"
    compress
    include "build/src/overlays/actors/ovl_Bg_Goron_Oyu/z_bg_goron_oyu.o"
    include "build/src/overlays/actors/ovl_Bg_Goron_Oyu/ovl_Bg_Goron_Oyu_reloc.o"
endseg

beginseg
    name "ovl_En_Kgy"
    compress
    include "build/src/overlays/actors/ovl_En_Kgy/z_en_kgy.o"
    include "build/src/overlays/actors/ovl_En_Kgy/ovl_En_Kgy_reloc.o"
endseg

beginseg
    name "ovl_En_Invadepoh"
    compress
    include "build/src/overlays/actors/ovl_En_Invadepoh/z_en_invadepoh.o"
    include "build/data/ovl_En_Invadepoh/ovl_En_Invadepoh.data.o"
    include "build/data/ovl_En_Invadepoh/ovl_En_Invadepoh.bss.o"
    include "build/data/ovl_En_Invadepoh/ovl_En_Invadepoh.reloc.o"
endseg

beginseg
    name "ovl_En_Gk"
    compress
    include "build/src/overlays/actors/ovl_En_Gk/z_en_gk.o"
    include "build/src/overlays/actors/ovl_En_Gk/ovl_En_Gk_reloc.o"
endseg

beginseg
    name "ovl_En_An"
    compress
    include "build/src/overlays/actors/ovl_En_An/z_en_an.o"
    include "build/data/ovl_En_An/ovl_En_An.data.o"
    include "build/data/ovl_En_An/ovl_En_An.reloc.o"
endseg

beginseg
    name "ovl_En_Bee"
    compress
    include "build/src/overlays/actors/ovl_En_Bee/z_en_bee.o"
    include "build/src/overlays/actors/ovl_En_Bee/ovl_En_Bee_reloc.o"
endseg

beginseg
    name "ovl_En_Ot"
    compress
    include "build/src/overlays/actors/ovl_En_Ot/z_en_ot.o"
    include "build/src/overlays/actors/ovl_En_Ot/ovl_En_Ot_reloc.o"
endseg

beginseg
    name "ovl_En_Dragon"
    compress
    include "build/src/overlays/actors/ovl_En_Dragon/z_en_dragon.o"
    include "build/src/overlays/actors/ovl_En_Dragon/ovl_En_Dragon_reloc.o"
endseg

beginseg
    name "ovl_Obj_Dora"
    compress
    include "build/src/overlays/actors/ovl_Obj_Dora/z_obj_dora.o"
    include "build/src/overlays/actors/ovl_Obj_Dora/ovl_Obj_Dora_reloc.o"
endseg

beginseg
    name "ovl_En_Bigpo"
    compress
    include "build/src/overlays/actors/ovl_En_Bigpo/z_en_bigpo.o"
    include "build/src/overlays/actors/ovl_En_Bigpo/ovl_En_Bigpo_reloc.o"
endseg

beginseg
    name "ovl_Obj_Kendo_Kanban"
    compress
    include "build/src/overlays/actors/ovl_Obj_Kendo_Kanban/z_obj_kendo_kanban.o"
    include "build/src/overlays/actors/ovl_Obj_Kendo_Kanban/ovl_Obj_Kendo_Kanban_reloc.o"
endseg

beginseg
    name "ovl_Obj_Hariko"
    compress
    include "build/src/overlays/actors/ovl_Obj_Hariko/z_obj_hariko.o"
    include "build/src/overlays/actors/ovl_Obj_Hariko/ovl_Obj_Hariko_reloc.o"
endseg

beginseg
    name "ovl_En_Sth"
    compress
    include "build/src/overlays/actors/ovl_En_Sth/z_en_sth.o"
    include "build/src/overlays/actors/ovl_En_Sth/ovl_En_Sth_reloc.o"
endseg

beginseg
    name "ovl_Bg_Sinkai_Kabe"
    compress
    include "build/src/overlays/actors/ovl_Bg_Sinkai_Kabe/z_bg_sinkai_kabe.o"
    include "build/src/overlays/actors/ovl_Bg_Sinkai_Kabe/ovl_Bg_Sinkai_Kabe_reloc.o"
endseg

beginseg
    name "ovl_Bg_Haka_Curtain"
    compress
    include "build/src/overlays/actors/ovl_Bg_Haka_Curtain/z_bg_haka_curtain.o"
    include "build/src/overlays/actors/ovl_Bg_Haka_Curtain/ovl_Bg_Haka_Curtain_reloc.o"
endseg

beginseg
    name "ovl_Bg_Kin2_Bombwall"
    compress
    include "build/src/overlays/actors/ovl_Bg_Kin2_Bombwall/z_bg_kin2_bombwall.o"
    include "build/src/overlays/actors/ovl_Bg_Kin2_Bombwall/ovl_Bg_Kin2_Bombwall_reloc.o"
endseg

beginseg
    name "ovl_Bg_Kin2_Fence"
    compress
    include "build/src/overlays/actors/ovl_Bg_Kin2_Fence/z_bg_kin2_fence.o"
    include "build/src/overlays/actors/ovl_Bg_Kin2_Fence/ovl_Bg_Kin2_Fence_reloc.o"
endseg

beginseg
    name "ovl_Bg_Kin2_Picture"
    compress
    include "build/src/overlays/actors/ovl_Bg_Kin2_Picture/z_bg_kin2_picture.o"
    include "build/src/overlays/actors/ovl_Bg_Kin2_Picture/ovl_Bg_Kin2_Picture_reloc.o"
endseg

beginseg
    name "ovl_Bg_Kin2_Shelf"
    compress
    include "build/src/overlays/actors/ovl_Bg_Kin2_Shelf/z_bg_kin2_shelf.o"
    include "build/src/overlays/actors/ovl_Bg_Kin2_Shelf/ovl_Bg_Kin2_Shelf_reloc.o"
endseg

beginseg
    name "ovl_En_Rail_Skb"
    compress
    include "build/src/overlays/actors/ovl_En_Rail_Skb/z_en_rail_skb.o"
    include "build/src/overlays/actors/ovl_En_Rail_Skb/ovl_En_Rail_Skb_reloc.o"
endseg

beginseg
    name "ovl_En_Jg"
    compress
    include "build/src/overlays/actors/ovl_En_Jg/z_en_jg.o"
    include "build/src/overlays/actors/ovl_En_Jg/ovl_En_Jg_reloc.o"
endseg

beginseg
    name "ovl_En_Tru_Mt"
    compress
    include "build/src/overlays/actors/ovl_En_Tru_Mt/z_en_tru_mt.o"
    include "build/src/overlays/actors/ovl_En_Tru_Mt/ovl_En_Tru_Mt_reloc.o"
endseg

beginseg
    name "ovl_Obj_Um"
    compress
    include "build/src/overlays/actors/ovl_Obj_Um/z_obj_um.o"
    include "build/src/overlays/actors/ovl_Obj_Um/ovl_Obj_Um_reloc.o"
endseg

beginseg
    name "ovl_En_Neo_Reeba"
    compress
    include "build/src/overlays/actors/ovl_En_Neo_Reeba/z_en_neo_reeba.o"
    include "build/src/overlays/actors/ovl_En_Neo_Reeba/ovl_En_Neo_Reeba_reloc.o"
endseg

beginseg
    name "ovl_Bg_Mbar_Chair"
    compress
    include "build/src/overlays/actors/ovl_Bg_Mbar_Chair/z_bg_mbar_chair.o"
    include "build/src/overlays/actors/ovl_Bg_Mbar_Chair/ovl_Bg_Mbar_Chair_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Block"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ikana_Block/z_bg_ikana_block.o"
    include "build/src/overlays/actors/ovl_Bg_Ikana_Block/ovl_Bg_Ikana_Block_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Mirror"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ikana_Mirror/z_bg_ikana_mirror.o"
    include "build/src/overlays/actors/ovl_Bg_Ikana_Mirror/ovl_Bg_Ikana_Mirror_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Rotaryroom"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ikana_Rotaryroom/z_bg_ikana_rotaryroom.o"
    include "build/src/overlays/actors/ovl_Bg_Ikana_Rotaryroom/ovl_Bg_Ikana_Rotaryroom_reloc.o"
endseg

beginseg
    name "ovl_Bg_Dblue_Balance"
    compress
    include "build/src/overlays/actors/ovl_Bg_Dblue_Balance/z_bg_dblue_balance.o"
    include "build/src/overlays/actors/ovl_Bg_Dblue_Balance/ovl_Bg_Dblue_Balance_reloc.o"
endseg

beginseg
    name "ovl_Bg_Dblue_Waterfall"
    compress
    include "build/src/overlays/actors/ovl_Bg_Dblue_Waterfall/z_bg_dblue_waterfall.o"
    include "build/src/overlays/actors/ovl_Bg_Dblue_Waterfall/ovl_Bg_Dblue_Waterfall_reloc.o"
endseg

beginseg
    name "ovl_En_Kaizoku"
    compress
    include "build/src/overlays/actors/ovl_En_Kaizoku/z_en_kaizoku.o"
    include "build/src/overlays/actors/ovl_En_Kaizoku/ovl_En_Kaizoku_reloc.o"
endseg

beginseg
    name "ovl_En_Ge2"
    compress
    include "build/src/overlays/actors/ovl_En_Ge2/z_en_ge2.o"
    include "build/src/overlays/actors/ovl_En_Ge2/ovl_En_Ge2_reloc.o"
endseg

beginseg
    name "ovl_En_Ma_Yts"
    compress
    include "build/src/overlays/actors/ovl_En_Ma_Yts/z_en_ma_yts.o"
    include "build/src/overlays/actors/ovl_En_Ma_Yts/ovl_En_Ma_Yts_reloc.o"
endseg

beginseg
    name "ovl_En_Ma_Yto"
    compress
    include "build/src/overlays/actors/ovl_En_Ma_Yto/z_en_ma_yto.o"
    include "build/src/overlays/actors/ovl_En_Ma_Yto/ovl_En_Ma_Yto_reloc.o"
endseg

beginseg
    name "ovl_Obj_Tokei_Turret"
    compress
    include "build/src/overlays/actors/ovl_Obj_Tokei_Turret/z_obj_tokei_turret.o"
    include "build/src/overlays/actors/ovl_Obj_Tokei_Turret/ovl_Obj_Tokei_Turret_reloc.o"
endseg

beginseg
    name "ovl_Bg_Dblue_Elevator"
    compress
    include "build/src/overlays/actors/ovl_Bg_Dblue_Elevator/z_bg_dblue_elevator.o"
    include "build/data/ovl_Bg_Dblue_Elevator/ovl_Bg_Dblue_Elevator.data.o"
    include "build/data/ovl_Bg_Dblue_Elevator/ovl_Bg_Dblue_Elevator.reloc.o"
endseg

beginseg
    name "ovl_Obj_Warpstone"
    compress
    include "build/src/overlays/actors/ovl_Obj_Warpstone/z_obj_warpstone.o"
    include "build/src/overlays/actors/ovl_Obj_Warpstone/ovl_Obj_Warpstone_reloc.o"
endseg

beginseg
    name "ovl_En_Zog"
    compress
    include "build/src/overlays/actors/ovl_En_Zog/z_en_zog.o"
    include "build/src/overlays/actors/ovl_En_Zog/ovl_En_Zog_reloc.o"
endseg

beginseg
    name "ovl_Obj_Rotlift"
    compress
    include "build/src/overlays/actors/ovl_Obj_Rotlift/z_obj_rotlift.o"
    include "build/src/overlays/actors/ovl_Obj_Rotlift/ovl_Obj_Rotlift_reloc.o"
endseg

beginseg
    name "ovl_Obj_Jg_Gakki"
    compress
    include "build/src/overlays/actors/ovl_Obj_Jg_Gakki/z_obj_jg_gakki.o"
    include "build/src/overlays/actors/ovl_Obj_Jg_Gakki/ovl_Obj_Jg_Gakki_reloc.o"
endseg

beginseg
    name "ovl_Bg_Inibs_Movebg"
    compress
    include "build/src/overlays/actors/ovl_Bg_Inibs_Movebg/z_bg_inibs_movebg.o"
    include "build/src/overlays/actors/ovl_Bg_Inibs_Movebg/ovl_Bg_Inibs_Movebg_reloc.o"
endseg

beginseg
    name "ovl_En_Zot"
    compress
    include "build/src/overlays/actors/ovl_En_Zot/z_en_zot.o"
    include "build/src/overlays/actors/ovl_En_Zot/ovl_En_Zot_reloc.o"
endseg

beginseg
    name "ovl_Obj_Tree"
    compress
    include "build/src/overlays/actors/ovl_Obj_Tree/z_obj_tree.o"
    include "build/src/overlays/actors/ovl_Obj_Tree/ovl_Obj_Tree_reloc.o"
endseg

beginseg
    name "ovl_Obj_Y2lift"
    compress
    include "build/src/overlays/actors/ovl_Obj_Y2lift/z_obj_y2lift.o"
    include "build/src/overlays/actors/ovl_Obj_Y2lift/ovl_Obj_Y2lift_reloc.o"
endseg

beginseg
    name "ovl_Obj_Y2shutter"
    compress
    include "build/src/overlays/actors/ovl_Obj_Y2shutter/z_obj_y2shutter.o"
    include "build/src/overlays/actors/ovl_Obj_Y2shutter/ovl_Obj_Y2shutter_reloc.o"
endseg

beginseg
    name "ovl_Obj_Boat"
    compress
    include "build/src/overlays/actors/ovl_Obj_Boat/z_obj_boat.o"
    include "build/src/overlays/actors/ovl_Obj_Boat/ovl_Obj_Boat_reloc.o"
endseg

beginseg
    name "ovl_Obj_Taru"
    compress
    include "build/src/overlays/actors/ovl_Obj_Taru/z_obj_taru.o"
    include "build/src/overlays/actors/ovl_Obj_Taru/ovl_Obj_Taru_reloc.o"
endseg

beginseg
    name "ovl_Obj_Hunsui"
    compress
    include "build/src/overlays/actors/ovl_Obj_Hunsui/z_obj_hunsui.o"
    include "build/src/overlays/actors/ovl_Obj_Hunsui/ovl_Obj_Hunsui_reloc.o"
endseg

beginseg
    name "ovl_En_Jc_Mato"
    compress
    include "build/src/overlays/actors/ovl_En_Jc_Mato/z_en_jc_mato.o"
    include "build/src/overlays/actors/ovl_En_Jc_Mato/ovl_En_Jc_Mato_reloc.o"
endseg

beginseg
    name "ovl_Mir_Ray3"
    compress
    include "build/src/overlays/actors/ovl_Mir_Ray3/z_mir_ray3.o"
    include "build/src/overlays/actors/ovl_Mir_Ray3/ovl_Mir_Ray3_reloc.o"
endseg

beginseg
    name "ovl_En_Zob"
    compress
    include "build/src/overlays/actors/ovl_En_Zob/z_en_zob.o"
    include "build/src/overlays/actors/ovl_En_Zob/ovl_En_Zob_reloc.o"
endseg

beginseg
    name "ovl_Elf_Msg6"
    compress
    include "build/src/overlays/actors/ovl_Elf_Msg6/z_elf_msg6.o"
    include "build/src/overlays/actors/ovl_Elf_Msg6/ovl_Elf_Msg6_reloc.o"
endseg

beginseg
    name "ovl_Obj_Nozoki"
    compress
    include "build/src/overlays/actors/ovl_Obj_Nozoki/z_obj_nozoki.o"
    include "build/src/overlays/actors/ovl_Obj_Nozoki/ovl_Obj_Nozoki_reloc.o"
endseg

beginseg
    name "ovl_En_Toto"
    compress
    include "build/src/overlays/actors/ovl_En_Toto/z_en_toto.o"
    include "build/src/overlays/actors/ovl_En_Toto/ovl_En_Toto_reloc.o"
endseg

beginseg
    name "ovl_En_Railgibud"
    compress
    include "build/src/overlays/actors/ovl_En_Railgibud/z_en_railgibud.o"
    include "build/src/overlays/actors/ovl_En_Railgibud/ovl_En_Railgibud_reloc.o"
endseg

beginseg
    name "ovl_En_Baba"
    compress
    include "build/src/overlays/actors/ovl_En_Baba/z_en_baba.o"
    include "build/src/overlays/actors/ovl_En_Baba/ovl_En_Baba_reloc.o"
endseg

beginseg
    name "ovl_En_Suttari"
    compress
    include "build/src/overlays/actors/ovl_En_Suttari/z_en_suttari.o"
    include "build/src/overlays/actors/ovl_En_Suttari/ovl_En_Suttari_reloc.o"
endseg

beginseg
    name "ovl_En_Zod"
    compress
    include "build/src/overlays/actors/ovl_En_Zod/z_en_zod.o"
    include "build/src/overlays/actors/ovl_En_Zod/ovl_En_Zod_reloc.o"
endseg

beginseg
    name "ovl_En_Kujiya"
    compress
    include "build/src/overlays/actors/ovl_En_Kujiya/z_en_kujiya.o"
    include "build/src/overlays/actors/ovl_En_Kujiya/ovl_En_Kujiya_reloc.o"
endseg

beginseg
    name "ovl_En_Geg"
    compress
    include "build/src/overlays/actors/ovl_En_Geg/z_en_geg.o"
    include "build/src/overlays/actors/ovl_En_Geg/ovl_En_Geg_reloc.o"
endseg

beginseg
    name "ovl_Obj_Kinoko"
    compress
    include "build/src/overlays/actors/ovl_Obj_Kinoko/z_obj_kinoko.o"
    include "build/src/overlays/actors/ovl_Obj_Kinoko/ovl_Obj_Kinoko_reloc.o"
endseg

beginseg
    name "ovl_Obj_Yasi"
    compress
    include "build/src/overlays/actors/ovl_Obj_Yasi/z_obj_yasi.o"
    include "build/src/overlays/actors/ovl_Obj_Yasi/ovl_Obj_Yasi_reloc.o"
endseg

beginseg
    name "ovl_En_Tanron1"
    compress
    include "build/src/overlays/actors/ovl_En_Tanron1/z_en_tanron1.o"
    include "build/src/overlays/actors/ovl_En_Tanron1/ovl_En_Tanron1_reloc.o"
endseg

beginseg
    name "ovl_En_Tanron2"
    compress
    include "build/src/overlays/actors/ovl_En_Tanron2/z_en_tanron2.o"
    include "build/src/overlays/actors/ovl_En_Tanron2/ovl_En_Tanron2_reloc.o"
endseg

beginseg
    name "ovl_En_Tanron3"
    compress
    include "build/src/overlays/actors/ovl_En_Tanron3/z_en_tanron3.o"
    include "build/src/overlays/actors/ovl_En_Tanron3/ovl_En_Tanron3_reloc.o"
endseg

beginseg
    name "ovl_Obj_Chan"
    compress
    include "build/src/overlays/actors/ovl_Obj_Chan/z_obj_chan.o"
    include "build/src/overlays/actors/ovl_Obj_Chan/ovl_Obj_Chan_reloc.o"
endseg

beginseg
    name "ovl_En_Zos"
    compress
    include "build/src/overlays/actors/ovl_En_Zos/z_en_zos.o"
    include "build/src/overlays/actors/ovl_En_Zos/ovl_En_Zos_reloc.o"
endseg

beginseg
    name "ovl_En_S_Goro"
    compress
    include "build/src/overlays/actors/ovl_En_S_Goro/z_en_s_goro.o"
    include "build/src/overlays/actors/ovl_En_S_Goro/ovl_En_S_Goro_reloc.o"
endseg

beginseg
    name "ovl_En_Nb"
    compress
    include "build/src/overlays/actors/ovl_En_Nb/z_en_nb.o"
    include "build/src/overlays/actors/ovl_En_Nb/ovl_En_Nb_reloc.o"
endseg

beginseg
    name "ovl_En_Ja"
    compress
    include "build/src/overlays/actors/ovl_En_Ja/z_en_ja.o"
    include "build/src/overlays/actors/ovl_En_Ja/ovl_En_Ja_reloc.o"
endseg

beginseg
    name "ovl_Bg_F40_Block"
    compress
    include "build/src/overlays/actors/ovl_Bg_F40_Block/z_bg_f40_block.o"
    include "build/src/overlays/actors/ovl_Bg_F40_Block/ovl_Bg_F40_Block_reloc.o"
endseg

beginseg
    name "ovl_Bg_F40_Switch"
    compress
    include "build/src/overlays/actors/ovl_Bg_F40_Switch/z_bg_f40_switch.o"
    include "build/src/overlays/actors/ovl_Bg_F40_Switch/ovl_Bg_F40_Switch_reloc.o"
endseg

beginseg
    name "ovl_En_Po_Composer"
    compress
    include "build/src/overlays/actors/ovl_En_Po_Composer/z_en_po_composer.o"
    include "build/data/ovl_En_Po_Composer/ovl_En_Po_Composer.data.o"
    include "build/data/ovl_En_Po_Composer/ovl_En_Po_Composer.reloc.o"
endseg

beginseg
    name "ovl_En_Guruguru"
    compress
    include "build/src/overlays/actors/ovl_En_Guruguru/z_en_guruguru.o"
    include "build/src/overlays/actors/ovl_En_Guruguru/ovl_En_Guruguru_reloc.o"
endseg

beginseg
    name "ovl_Oceff_Wipe5"
    compress
    include "build/src/overlays/actors/ovl_Oceff_Wipe5/z_oceff_wipe5.o"
    include "build/src/overlays/actors/ovl_Oceff_Wipe5/ovl_Oceff_Wipe5_reloc.o"
endseg

beginseg
    name "ovl_En_Stone_heishi"
    compress
    include "build/src/overlays/actors/ovl_En_Stone_heishi/z_en_stone_heishi.o"
    include "build/src/overlays/actors/ovl_En_Stone_heishi/ovl_En_Stone_heishi_reloc.o"
endseg

beginseg
    name "ovl_Oceff_Wipe6"
    compress
    include "build/src/overlays/actors/ovl_Oceff_Wipe6/z_oceff_wipe6.o"
    include "build/src/overlays/actors/ovl_Oceff_Wipe6/ovl_Oceff_Wipe6_reloc.o"
endseg

beginseg
    name "ovl_En_Scopenuts"
    compress
    include "build/src/overlays/actors/ovl_En_Scopenuts/z_en_scopenuts.o"
    include "build/src/overlays/actors/ovl_En_Scopenuts/ovl_En_Scopenuts_reloc.o"
endseg

beginseg
    name "ovl_En_Scopecrow"
    compress
    include "build/src/overlays/actors/ovl_En_Scopecrow/z_en_scopecrow.o"
    include "build/src/overlays/actors/ovl_En_Scopecrow/ovl_En_Scopecrow_reloc.o"
endseg

beginseg
    name "ovl_Oceff_Wipe7"
    compress
    include "build/src/overlays/actors/ovl_Oceff_Wipe7/z_oceff_wipe7.o"
    include "build/src/overlays/actors/ovl_Oceff_Wipe7/ovl_Oceff_Wipe7_reloc.o"
endseg

beginseg
    name "ovl_Eff_Kamejima_Wave"
    compress
    include "build/src/overlays/actors/ovl_Eff_Kamejima_Wave/z_eff_kamejima_wave.o"
    include "build/src/overlays/actors/ovl_Eff_Kamejima_Wave/ovl_Eff_Kamejima_Wave_reloc.o"
endseg

beginseg
    name "ovl_En_Hg"
    compress
    include "build/src/overlays/actors/ovl_En_Hg/z_en_hg.o"
    include "build/src/overlays/actors/ovl_En_Hg/ovl_En_Hg_reloc.o"
endseg

beginseg
    name "ovl_En_Hgo"
    compress
    include "build/src/overlays/actors/ovl_En_Hgo/z_en_hgo.o"
    include "build/src/overlays/actors/ovl_En_Hgo/ovl_En_Hgo_reloc.o"
endseg

beginseg
    name "ovl_En_Zov"
    compress
    include "build/src/overlays/actors/ovl_En_Zov/z_en_zov.o"
    include "build/src/overlays/actors/ovl_En_Zov/ovl_En_Zov_reloc.o"
endseg

beginseg
    name "ovl_En_Ah"
    compress
    include "build/src/overlays/actors/ovl_En_Ah/z_en_ah.o"
    include "build/src/overlays/actors/ovl_En_Ah/ovl_En_Ah_reloc.o"
endseg

beginseg
    name "ovl_Obj_Hgdoor"
    compress
    include "build/src/overlays/actors/ovl_Obj_Hgdoor/z_obj_hgdoor.o"
    include "build/src/overlays/actors/ovl_Obj_Hgdoor/ovl_Obj_Hgdoor_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Bombwall"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ikana_Bombwall/z_bg_ikana_bombwall.o"
    include "build/src/overlays/actors/ovl_Bg_Ikana_Bombwall/ovl_Bg_Ikana_Bombwall_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Ray"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ikana_Ray/z_bg_ikana_ray.o"
    include "build/src/overlays/actors/ovl_Bg_Ikana_Ray/ovl_Bg_Ikana_Ray_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Shutter"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ikana_Shutter/z_bg_ikana_shutter.o"
    include "build/src/overlays/actors/ovl_Bg_Ikana_Shutter/ovl_Bg_Ikana_Shutter_reloc.o"
endseg

beginseg
    name "ovl_Bg_Haka_Bombwall"
    compress
    include "build/src/overlays/actors/ovl_Bg_Haka_Bombwall/z_bg_haka_bombwall.o"
    include "build/src/overlays/actors/ovl_Bg_Haka_Bombwall/ovl_Bg_Haka_Bombwall_reloc.o"
endseg

beginseg
    name "ovl_Bg_Haka_Tomb"
    compress
    include "build/src/overlays/actors/ovl_Bg_Haka_Tomb/z_bg_haka_tomb.o"
    include "build/src/overlays/actors/ovl_Bg_Haka_Tomb/ovl_Bg_Haka_Tomb_reloc.o"
endseg

beginseg
    name "ovl_En_Sc_Ruppe"
    compress
    include "build/src/overlays/actors/ovl_En_Sc_Ruppe/z_en_sc_ruppe.o"
    include "build/src/overlays/actors//ovl_En_Sc_Ruppe/ovl_En_Sc_Ruppe_reloc.o"
endseg

beginseg
    name "ovl_Bg_Iknv_Doukutu"
    compress
    include "build/src/overlays/actors/ovl_Bg_Iknv_Doukutu/z_bg_iknv_doukutu.o"
    include "build/src/overlays/actors/ovl_Bg_Iknv_Doukutu/ovl_Bg_Iknv_Doukutu_reloc.o"
endseg

beginseg
    name "ovl_Bg_Iknv_Obj"
    compress
    include "build/src/overlays/actors/ovl_Bg_Iknv_Obj/z_bg_iknv_obj.o"
    include "build/src/overlays/actors/ovl_Bg_Iknv_Obj/ovl_Bg_Iknv_Obj_reloc.o"
endseg

beginseg
    name "ovl_En_Pamera"
    compress
    include "build/src/overlays/actors/ovl_En_Pamera/z_en_pamera.o"
    include "build/src/overlays/actors/ovl_En_Pamera/ovl_En_Pamera_reloc.o"
endseg

beginseg
    name "ovl_Obj_HsStump"
    compress
    include "build/src/overlays/actors/ovl_Obj_HsStump/z_obj_hsstump.o"
    include "build/src/overlays/actors/ovl_Obj_HsStump/ovl_Obj_HsStump_reloc.o"
endseg

beginseg
    name "ovl_En_Hidden_Nuts"
    compress
    include "build/src/overlays/actors/ovl_En_Hidden_Nuts/z_en_hidden_nuts.o"
    include "build/src/overlays/actors/ovl_En_Hidden_Nuts/ovl_En_Hidden_Nuts_reloc.o"
endseg

beginseg
    name "ovl_En_Zow"
    compress
    include "build/src/overlays/actors/ovl_En_Zow/z_en_zow.o"
    include "build/src/overlays/actors/ovl_En_Zow/ovl_En_Zow_reloc.o"
endseg

beginseg
    name "ovl_En_Talk"
    compress
    include "build/src/overlays/actors/ovl_En_Talk/z_en_talk.o"
    include "build/src/overlays/actors/ovl_En_Talk/ovl_En_Talk_reloc.o"
endseg

beginseg
    name "ovl_En_Al"
    compress
    include "build/src/overlays/actors/ovl_En_Al/z_en_al.o"
    include "build/src/overlays/actors/ovl_En_Al/ovl_En_Al_reloc.o"
endseg

beginseg
    name "ovl_En_Tab"
    compress
    include "build/src/overlays/actors/ovl_En_Tab/z_en_tab.o"
    include "build/src/overlays/actors/ovl_En_Tab/ovl_En_Tab_reloc.o"
endseg

beginseg
    name "ovl_En_Nimotsu"
    compress
    include "build/src/overlays/actors/ovl_En_Nimotsu/z_en_nimotsu.o"
    include "build/src/overlays/actors/ovl_En_Nimotsu/ovl_En_Nimotsu_reloc.o"
endseg

beginseg
    name "ovl_En_Hit_Tag"
    compress
    include "build/src/overlays/actors/ovl_En_Hit_Tag/z_en_hit_tag.o"
    include "build/src/overlays/actors/ovl_En_Hit_Tag/ovl_En_Hit_Tag_reloc.o"
endseg

beginseg
    name "ovl_En_Ruppecrow"
    compress
    include "build/src/overlays/actors/ovl_En_Ruppecrow/z_en_ruppecrow.o"
    include "build/src/overlays/actors/ovl_En_Ruppecrow/ovl_En_Ruppecrow_reloc.o"
endseg

beginseg
    name "ovl_En_Tanron4"
    compress
    include "build/src/overlays/actors/ovl_En_Tanron4/z_en_tanron4.o"
    include "build/src/overlays/actors/ovl_En_Tanron4/ovl_En_Tanron4_reloc.o"
endseg

beginseg
    name "ovl_En_Tanron5"
    compress
    include "build/src/overlays/actors/ovl_En_Tanron5/z_en_tanron5.o"
    include "build/src/overlays/actors/ovl_En_Tanron5/ovl_En_Tanron5_reloc.o"
endseg

beginseg
    name "ovl_En_Tanron6"
    compress
    include "build/src/overlays/actors/ovl_En_Tanron6/z_en_tanron6.o"
    include "build/src/overlays/actors/ovl_En_Tanron6/ovl_En_Tanron6_reloc.o"
endseg

beginseg
    name "ovl_En_Daiku2"
    compress
    include "build/src/overlays/actors/ovl_En_Daiku2/z_en_daiku2.o"
    include "build/src/overlays/actors/ovl_En_Daiku2/ovl_En_Daiku2_reloc.o"
endseg

beginseg
    name "ovl_En_Muto"
    compress
    include "build/src/overlays/actors/ovl_En_Muto/z_en_muto.o"
    include "build/src/overlays/actors/ovl_En_Muto/ovl_En_Muto_reloc.o"
endseg

beginseg
    name "ovl_En_Baisen"
    compress
    include "build/src/overlays/actors/ovl_En_Baisen/z_en_baisen.o"
    include "build/src/overlays/actors/ovl_En_Baisen/ovl_En_Baisen_reloc.o"
endseg

beginseg
    name "ovl_En_Heishi"
    compress
    include "build/src/overlays/actors/ovl_En_Heishi/z_en_heishi.o"
    include "build/src/overlays/actors/ovl_En_Heishi/ovl_En_Heishi_reloc.o"
endseg

beginseg
    name "ovl_En_Demo_heishi"
    compress
    include "build/src/overlays/actors/ovl_En_Demo_heishi/z_en_demo_heishi.o"
    include "build/src/overlays/actors/ovl_En_Demo_heishi/ovl_En_Demo_heishi_reloc.o"
endseg

beginseg
    name "ovl_En_Dt"
    compress
    include "build/src/overlays/actors/ovl_En_Dt/z_en_dt.o"
    include "build/data/ovl_En_Dt/ovl_En_Dt.data.o"
    include "build/data/ovl_En_Dt/ovl_En_Dt.reloc.o"
endseg

beginseg
    name "ovl_En_Cha"
    compress
    include "build/src/overlays/actors/ovl_En_Cha/z_en_cha.o"
    include "build/src/overlays/actors/ovl_En_Cha/ovl_En_Cha_reloc.o"
endseg

beginseg
    name "ovl_Obj_Dinner"
    compress
    include "build/src/overlays/actors/ovl_Obj_Dinner/z_obj_dinner.o"
    include "build/src/overlays/actors/ovl_Obj_Dinner/ovl_Obj_Dinner_reloc.o"
endseg

beginseg
    name "ovl_Eff_Lastday"
    compress
    include "build/src/overlays/actors/ovl_Eff_Lastday/z_eff_lastday.o"
    include "build/src/overlays/actors/ovl_Eff_Lastday/ovl_Eff_Lastday_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ikana_Dharma"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ikana_Dharma/z_bg_ikana_dharma.o"
    include "build/src/overlays/actors/ovl_Bg_Ikana_Dharma/ovl_Bg_Ikana_Dharma_reloc.o"
endseg

beginseg
    name "ovl_En_Akindonuts"
    compress
    include "build/src/overlays/actors/ovl_En_Akindonuts/z_en_akindonuts.o"
    include "build/src/overlays/actors/ovl_En_Akindonuts/ovl_En_Akindonuts_reloc.o"
endseg

beginseg
    name "ovl_Eff_Stk"
    compress
    include "build/src/overlays/actors/ovl_Eff_Stk/z_eff_stk.o"
    include "build/src/overlays/actors/ovl_Eff_Stk/ovl_Eff_Stk_reloc.o"
endseg

beginseg
    name "ovl_En_Ig"
    compress
    include "build/src/overlays/actors/ovl_En_Ig/z_en_ig.o"
    include "build/src/overlays/actors/ovl_En_Ig/ovl_En_Ig_reloc.o"
endseg

beginseg
    name "ovl_En_Rg"
    compress
    include "build/src/overlays/actors/ovl_En_Rg/z_en_rg.o"
    include "build/src/overlays/actors/ovl_En_Rg/ovl_En_Rg_reloc.o"
endseg

beginseg
    name "ovl_En_Osk"
    compress
    include "build/src/overlays/actors/ovl_En_Osk/z_en_osk.o"
    include "build/src/overlays/actors/ovl_En_Osk/ovl_En_Osk_reloc.o"
endseg

beginseg
    name "ovl_En_Sth2"
    compress
    include "build/src/overlays/actors/ovl_En_Sth2/z_en_sth2.o"
    include "build/src/overlays/actors/ovl_En_Sth2/ovl_En_Sth2_reloc.o"
endseg

beginseg
    name "ovl_En_Yb"
    compress
    include "build/src/overlays/actors/ovl_En_Yb/z_en_yb.o"
    include "build/src/overlays/actors/ovl_En_Yb/ovl_En_Yb_reloc.o"
endseg

beginseg
    name "ovl_En_Rz"
    compress
    include "build/src/overlays/actors/ovl_En_Rz/z_en_rz.o"
    include "build/src/overlays/actors/ovl_En_Rz/ovl_En_Rz_reloc.o"
endseg

beginseg
    name "ovl_En_Scopecoin"
    compress
    include "build/src/overlays/actors/ovl_En_Scopecoin/z_en_scopecoin.o"
    include "build/src/overlays/actors/ovl_En_Scopecoin/ovl_En_Scopecoin_reloc.o"
endseg

beginseg
    name "ovl_En_Bjt"
    compress
    include "build/src/overlays/actors/ovl_En_Bjt/z_en_bjt.o"
    include "build/src/overlays/actors/ovl_En_Bjt/ovl_En_Bjt_reloc.o"
endseg

beginseg
    name "ovl_En_Bomjima"
    compress
    include "build/src/overlays/actors/ovl_En_Bomjima/z_en_bomjima.o"
    include "build/src/overlays/actors/ovl_En_Bomjima/ovl_En_Bomjima_reloc.o"
endseg

beginseg
    name "ovl_En_Bomjimb"
    compress
    include "build/src/overlays/actors/ovl_En_Bomjimb/z_en_bomjimb.o"
    include "build/src/overlays/actors/ovl_En_Bomjimb/ovl_En_Bomjimb_reloc.o"
endseg

beginseg
    name "ovl_En_Bombers"
    compress
    include "build/src/overlays/actors/ovl_En_Bombers/z_en_bombers.o"
    include "build/src/overlays/actors/ovl_En_Bombers/ovl_En_Bombers_reloc.o"
endseg

beginseg
    name "ovl_En_Bombers2"
    compress
    include "build/src/overlays/actors/ovl_En_Bombers2/z_en_bombers2.o"
    include "build/src/overlays/actors/ovl_En_Bombers2/ovl_En_Bombers2_reloc.o"
endseg

beginseg
    name "ovl_En_Bombal"
    compress
    include "build/src/overlays/actors/ovl_En_Bombal/z_en_bombal.o"
    include "build/src/overlays/actors/ovl_En_Bombal/ovl_En_Bombal_reloc.o"
endseg

beginseg
    name "ovl_Obj_Moon_Stone"
    compress
    include "build/src/overlays/actors/ovl_Obj_Moon_Stone/z_obj_moon_stone.o"
    include "build/src/overlays/actors/ovl_Obj_Moon_Stone/ovl_Obj_Moon_Stone_reloc.o"
endseg

beginseg
    name "ovl_Obj_Mu_Pict"
    compress
    include "build/src/overlays/actors/ovl_Obj_Mu_Pict/z_obj_mu_pict.o"
    include "build/src/overlays/actors/ovl_Obj_Mu_Pict/ovl_Obj_Mu_Pict_reloc.o"
endseg

beginseg
    name "ovl_Bg_Ikninside"
    compress
    include "build/src/overlays/actors/ovl_Bg_Ikninside/z_bg_ikninside.o"
    include "build/src/overlays/actors/ovl_Bg_Ikninside/ovl_Bg_Ikninside_reloc.o"
endseg

beginseg
    name "ovl_Eff_Zoraband"
    compress
    include "build/src/overlays/actors/ovl_Eff_Zoraband/z_eff_zoraband.o"
    include "build/src/overlays/actors/ovl_Eff_Zoraband/ovl_Eff_Zoraband_reloc.o"
endseg

beginseg
    name "ovl_Obj_Kepn_Koya"
    compress
    include "build/src/overlays/actors/ovl_Obj_Kepn_Koya/z_obj_kepn_koya.o"
    include "build/src/overlays/actors/ovl_Obj_Kepn_Koya/ovl_Obj_Kepn_Koya_reloc.o"
endseg

beginseg
    name "ovl_Obj_Usiyane"
    compress
    include "build/src/overlays/actors/ovl_Obj_Usiyane/z_obj_usiyane.o"
    include "build/src/overlays/actors/ovl_Obj_Usiyane/ovl_Obj_Usiyane_reloc.o"
endseg

beginseg
    name "ovl_En_Nnh"
    compress
    include "build/src/overlays/actors/ovl_En_Nnh/z_en_nnh.o"
    include "build/src/overlays/actors/ovl_En_Nnh/ovl_En_Nnh_reloc.o"
endseg

beginseg
    name "ovl_Obj_Kzsaku"
    compress
    include "build/src/overlays/actors/ovl_Obj_Kzsaku/z_obj_kzsaku.o"
    include "build/src/overlays/actors/ovl_Obj_Kzsaku/ovl_Obj_Kzsaku_reloc.o"
endseg

beginseg
    name "ovl_Obj_Milk_Bin"
    compress
    include "build/src/overlays/actors/ovl_Obj_Milk_Bin/z_obj_milk_bin.o"
    include "build/src/overlays/actors/ovl_Obj_Milk_Bin/ovl_Obj_Milk_Bin_reloc.o"
endseg

beginseg
    name "ovl_En_Kitan"
    compress
    include "build/src/overlays/actors/ovl_En_Kitan/z_en_kitan.o"
    include "build/data/ovl_En_Kitan/ovl_En_Kitan.data.o"
    include "build/data/ovl_En_Kitan/ovl_En_Kitan.reloc.o"
endseg

beginseg
    name "ovl_Bg_Astr_Bombwall"
    compress
    include "build/src/overlays/actors/ovl_Bg_Astr_Bombwall/z_bg_astr_bombwall.o"
    include "build/src/overlays/actors/ovl_Bg_Astr_Bombwall/ovl_Bg_Astr_Bombwall_reloc.o"
endseg

beginseg
    name "ovl_Bg_Iknin_Susceil"
    compress
    include "build/src/overlays/actors/ovl_Bg_Iknin_Susceil/z_bg_iknin_susceil.o"
    include "build/src/overlays/actors/ovl_Bg_Iknin_Susceil/ovl_Bg_Iknin_Susceil_reloc.o"
endseg

beginseg
    name "ovl_En_Bsb"
    compress
    include "build/src/overlays/actors/ovl_En_Bsb/z_en_bsb.o"
    include "build/data/ovl_En_Bsb/ovl_En_Bsb.data.o"
    include "build/data/ovl_En_Bsb/ovl_En_Bsb.reloc.o"
endseg

beginseg
    name "ovl_En_Recepgirl"
    compress
    include "build/src/overlays/actors/ovl_En_Recepgirl/z_en_recepgirl.o"
    include "build/src/overlays/actors/ovl_En_Recepgirl/ovl_En_Recepgirl_reloc.o"
endseg

beginseg
    name "ovl_En_Thiefbird"
    compress
    include "build/src/overlays/actors/ovl_En_Thiefbird/z_en_thiefbird.o"
    include "build/src/overlays/actors/ovl_En_Thiefbird/ovl_En_Thiefbird_reloc.o"
endseg

beginseg
    name "ovl_En_Jgame_Tsn"
    compress
    include "build/src/overlays/actors/ovl_En_Jgame_Tsn/z_en_jgame_tsn.o"
    include "build/src/overlays/actors/ovl_En_Jgame_Tsn/ovl_En_Jgame_Tsn_reloc.o"
endseg

beginseg
    name "ovl_Obj_Jgame_Light"
    compress
    include "build/src/overlays/actors/ovl_Obj_Jgame_Light/z_obj_jgame_light.o"
    include "build/src/overlays/actors/ovl_Obj_Jgame_Light/ovl_Obj_Jgame_Light_reloc.o"
endseg

beginseg
    name "ovl_Obj_Yado"
    compress
    include "build/src/overlays/actors/ovl_Obj_Yado/z_obj_yado.o"
    include "build/src/overlays/actors/ovl_Obj_Yado/ovl_Obj_Yado_reloc.o"
endseg

beginseg
    name "ovl_Demo_Syoten"
    compress
    include "build/src/overlays/actors/ovl_Demo_Syoten/z_demo_syoten.o"
    include "build/src/overlays/actors/ovl_Demo_Syoten/ovl_Demo_Syoten_reloc.o"
endseg

beginseg
    name "ovl_Demo_Moonend"
    compress
    include "build/src/overlays/actors/ovl_Demo_Moonend/z_demo_moonend.o"
    include "build/src/overlays/actors/ovl_Demo_Moonend/ovl_Demo_Moonend_reloc.o"
endseg

beginseg
    name "ovl_Bg_Lbfshot"
    compress
    include "build/src/overlays/actors/ovl_Bg_Lbfshot/z_bg_lbfshot.o"
    include "build/src/overlays/actors/ovl_Bg_Lbfshot/ovl_Bg_Lbfshot_reloc.o"
endseg

beginseg
    name "ovl_Bg_Last_Bwall"
    compress
    include "build/src/overlays/actors/ovl_Bg_Last_Bwall/z_bg_last_bwall.o"
    include "build/src/overlays/actors/ovl_Bg_Last_Bwall/ovl_Bg_Last_Bwall_reloc.o"
endseg

beginseg
    name "ovl_En_And"
    compress
    include "build/src/overlays/actors/ovl_En_And/z_en_and.o"
    include "build/src/overlays/actors/ovl_En_And/ovl_En_And_reloc.o"
endseg

beginseg
    name "ovl_En_Invadepoh_Demo"
    compress
    include "build/src/overlays/actors/ovl_En_Invadepoh_Demo/z_en_invadepoh_demo.o"
    include "build/src/overlays/actors/ovl_En_Invadepoh_Demo/ovl_En_Invadepoh_Demo_reloc.o"
endseg

beginseg
    name "ovl_Obj_Danpeilift"
    compress
    include "build/src/overlays/actors/ovl_Obj_Danpeilift/z_obj_danpeilift.o"
    include "build/src/overlays/actors/ovl_Obj_Danpeilift/ovl_Obj_Danpeilift_reloc.o"
endseg

beginseg
    name "ovl_En_Fall2"
    compress
    include "build/src/overlays/actors/ovl_En_Fall2/z_en_fall2.o"
    include "build/src/overlays/actors/ovl_En_Fall2/ovl_En_Fall2_reloc.o"
endseg

beginseg
    name "ovl_Dm_Al"
    compress
    include "build/src/overlays/actors/ovl_Dm_Al/z_dm_al.o"
    include "build/src/overlays/actors/ovl_Dm_Al/ovl_Dm_Al_reloc.o"
endseg

beginseg
    name "ovl_Dm_An"
    compress
    include "build/src/overlays/actors/ovl_Dm_An/z_dm_an.o"
    include "build/src/overlays/actors/ovl_Dm_An/ovl_Dm_An_reloc.o"
endseg

beginseg
    name "ovl_Dm_Ah"
    compress
    include "build/src/overlays/actors/ovl_Dm_Ah/z_dm_ah.o"
    include "build/src/overlays/actors/ovl_Dm_Ah/ovl_Dm_Ah_reloc.o"
endseg

beginseg
    name "ovl_Dm_Nb"
    compress
    include "build/src/overlays/actors/ovl_Dm_Nb/z_dm_nb.o"
    include "build/src/overlays/actors/ovl_Dm_Nb/ovl_Dm_Nb_reloc.o"
endseg

beginseg
    name "ovl_En_Drs"
    compress
    include "build/src/overlays/actors/ovl_En_Drs/z_en_drs.o"
    include "build/src/overlays/actors/ovl_En_Drs/ovl_En_Drs_reloc.o"
endseg

beginseg
    name "ovl_En_Ending_Hero"
    compress
    include "build/src/overlays/actors/ovl_En_Ending_Hero/z_en_ending_hero.o"
    include "build/src/overlays/actors/ovl_En_Ending_Hero/ovl_En_Ending_Hero_reloc.o"
endseg

beginseg
    name "ovl_Dm_Bal"
    compress
    include "build/src/overlays/actors/ovl_Dm_Bal/z_dm_bal.o"
    include "build/src/overlays/actors/ovl_Dm_Bal/ovl_Dm_Bal_reloc.o"
endseg

beginseg
    name "ovl_En_Paper"
    compress
    include "build/src/overlays/actors/ovl_En_Paper/z_en_paper.o"
    include "build/src/overlays/actors/ovl_En_Paper/ovl_En_Paper_reloc.o"
endseg

beginseg
    name "ovl_En_Hint_Skb"
    compress
    include "build/src/overlays/actors/ovl_En_Hint_Skb/z_en_hint_skb.o"
    include "build/src/overlays/actors/ovl_En_Hint_Skb/ovl_En_Hint_Skb_reloc.o"
endseg

beginseg
    name "ovl_Dm_Tag"
    compress
    include "build/src/overlays/actors/ovl_Dm_Tag/z_dm_tag.o"
    include "build/src/overlays/actors/ovl_Dm_Tag/ovl_Dm_Tag_reloc.o"
endseg

beginseg
    name "ovl_En_Bh"
    compress
    include "build/src/overlays/actors/ovl_En_Bh/z_en_bh.o"
    include "build/src/overlays/actors/ovl_En_Bh/ovl_En_Bh_reloc.o"
endseg

beginseg
    name "ovl_En_Ending_Hero2"
    compress
    include "build/src/overlays/actors/ovl_En_Ending_Hero2/z_en_ending_hero2.o"
    include "build/src/overlays/actors/ovl_En_Ending_Hero2/ovl_En_Ending_Hero2_reloc.o"
endseg

beginseg
    name "ovl_En_Ending_Hero3"
    compress
    include "build/src/overlays/actors/ovl_En_Ending_Hero3/z_en_ending_hero3.o"
    include "build/src/overlays/actors/ovl_En_Ending_Hero3/ovl_En_Ending_Hero3_reloc.o"
endseg

beginseg
    name "ovl_En_Ending_Hero4"
    compress
    include "build/src/overlays/actors/ovl_En_Ending_Hero4/z_en_ending_hero4.o"
    include "build/src/overlays/actors/ovl_En_Ending_Hero4/ovl_En_Ending_Hero4_reloc.o"
endseg

beginseg
    name "ovl_En_Ending_Hero5"
    compress
    include "build/src/overlays/actors/ovl_En_Ending_Hero5/z_en_ending_hero5.o"
    include "build/src/overlays/actors/ovl_En_Ending_Hero5/ovl_En_Ending_Hero5_reloc.o"
endseg

beginseg
    name "ovl_En_Ending_Hero6"
    compress
    include "build/src/overlays/actors/ovl_En_Ending_Hero6/z_en_ending_hero6.o"
    include "build/src/overlays/actors/ovl_En_Ending_Hero6/ovl_En_Ending_Hero6_reloc.o"
endseg

beginseg
    name "ovl_Dm_Gm"
    compress
    include "build/src/overlays/actors/ovl_Dm_Gm/z_dm_gm.o"
    include "build/src/overlays/actors/ovl_Dm_Gm/ovl_Dm_Gm_reloc.o"
endseg

beginseg
    name "ovl_Obj_Swprize"
    compress
    include "build/src/overlays/actors/ovl_Obj_Swprize/z_obj_swprize.o"
    include "build/src/overlays/actors/ovl_Obj_Swprize/ovl_Obj_Swprize_reloc.o"
endseg

beginseg
    name "ovl_En_Invisible_Ruppe"
    compress
    include "build/src/overlays/actors/ovl_En_Invisible_Ruppe/z_en_invisible_ruppe.o"
    include "build/src/overlays/actors/ovl_En_Invisible_Ruppe/ovl_En_Invisible_Ruppe_reloc.o"
endseg

beginseg
    name "ovl_Obj_Ending"
    compress
    include "build/src/overlays/actors/ovl_Obj_Ending/z_obj_ending.o"
    include "build/src/overlays/actors/ovl_Obj_Ending/ovl_Obj_Ending_reloc.o"
endseg

beginseg
    name "ovl_En_Rsn"
    compress
    include "build/src/overlays/actors/ovl_En_Rsn/z_en_rsn.o"
    include "build/src/overlays/actors/ovl_En_Rsn/ovl_En_Rsn_reloc.o"
endseg

beginseg
    name "gameplay_keep"
    compress
    romalign 0x1000
    number 4
    include "build/assets/objects/gameplay_keep/gameplay_keep.o"
endseg

beginseg
    name "gameplay_field_keep"
    compress
    romalign 0x1000
    number 5
    include "build/assets/objects/gameplay_field_keep/gameplay_field_keep.o"
endseg

beginseg
    name "gameplay_dangeon_keep"
    compress
    romalign 0x1000
    number 5
    include "build/assets/objects/gameplay_dangeon_keep/gameplay_dangeon_keep.o"
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
    number 6
    include "build/assets/objects/object_link_boy/object_link_boy.o"
endseg

beginseg
    name "object_link_child"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_link_child/object_link_child.o"
endseg

beginseg
    name "object_link_goron"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_link_goron/object_link_goron.o"
endseg

beginseg
    name "object_link_zora"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_link_zora/object_link_zora.o"
endseg

beginseg
    name "object_link_nuts"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_link_nuts/object_link_nuts.o"
endseg

beginseg
    name "object_mask_ki_tan"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_ki_tan/object_mask_ki_tan.o"
endseg

beginseg
    name "object_mask_rabit"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_rabit/object_mask_rabit.o"
endseg

beginseg
    name "object_mask_skj"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_skj/object_mask_skj.o"
endseg

beginseg
    name "object_mask_truth"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_truth/object_mask_truth.o"
endseg

beginseg
    name "object_mask_gibudo"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_gibudo/object_mask_gibudo.o"
endseg

beginseg
    name "object_mask_json"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_json/object_mask_json.o"
endseg

beginseg
    name "object_mask_kerfay"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_kerfay/object_mask_kerfay.o"
endseg

beginseg
    name "object_mask_bigelf"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_bigelf/object_mask_bigelf.o"
endseg

beginseg
    name "object_mask_kyojin"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_kyojin/object_mask_kyojin.o"
endseg

beginseg
    name "object_mask_romerny"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_romerny/object_mask_romerny.o"
endseg

beginseg
    name "object_mask_posthat"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_posthat/object_mask_posthat.o"
endseg

beginseg
    name "object_mask_zacho"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_zacho/object_mask_zacho.o"
endseg

beginseg
    name "object_mask_stone"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_stone/object_mask_stone.o"
endseg

beginseg
    name "object_mask_bree"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_bree/object_mask_bree.o"
endseg

beginseg
    name "object_mask_gero"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_gero/object_mask_gero.o"
endseg

beginseg
    name "object_mask_yofukasi"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_yofukasi/object_mask_yofukasi.o"
endseg

beginseg
    name "object_mask_meoto"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_meoto/object_mask_meoto.o"
endseg

beginseg
    name "object_mask_dancer"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_dancer/object_mask_dancer.o"
endseg

beginseg
    name "object_mask_bakuretu"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_bakuretu/object_mask_bakuretu.o"
endseg

beginseg
    name "object_mask_bu_san"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_bu_san/object_mask_bu_san.o"
endseg

beginseg
    name "object_mask_goron"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_goron/object_mask_goron.o"
endseg

beginseg
    name "object_mask_zora"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_zora/object_mask_zora.o"
endseg

beginseg
    name "object_mask_nuts"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_nuts/object_mask_nuts.o"
endseg

beginseg
    name "object_mask_boy"
    compress
    romalign 0x1000
    number 10
    include "build/assets/objects/object_mask_boy/object_mask_boy.o"
endseg

beginseg
    name "object_box"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_box/object_box.o"
endseg

beginseg
    name "object_okuta"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_okuta/object_okuta.o"
endseg

beginseg
    name "object_wallmaster"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wallmaster/object_wallmaster.o"
endseg

beginseg
    name "object_dy_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dy_obj/object_dy_obj.o"
endseg

beginseg
    name "object_firefly"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_firefly/object_firefly.o"
endseg

beginseg
    name "object_dodongo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dodongo/object_dodongo.o"
endseg

beginseg
    name "object_niw"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_niw/object_niw.o"
endseg

beginseg
    name "object_tite"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tite/object_tite.o"
endseg

beginseg
    name "object_ph"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ph/object_ph.o"
endseg

beginseg
    name "object_dinofos"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dinofos/object_dinofos.o"
endseg

beginseg
    name "object_zl1"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zl1/object_zl1.o"
endseg

beginseg
    name "object_bubble"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bubble/object_bubble.o"
endseg

beginseg
    name "object_test3"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_test3/object_test3.o"
endseg

beginseg
    name "object_famos"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_famos/object_famos.o"
endseg

beginseg
    name "object_st"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_st/object_st.o"
endseg

beginseg
    name "object_thiefbird"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_thiefbird/object_thiefbird.o"
endseg

beginseg
    name "object_bombf"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bombf/object_bombf.o"
endseg

beginseg
    name "object_am"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_am/object_am.o"
endseg

beginseg
    name "object_dekubaba"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dekubaba/object_dekubaba.o"
endseg

beginseg
    name "object_warp1"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_warp1/object_warp1.o"
endseg

beginseg
    name "object_b_heart"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_b_heart/object_b_heart.o"
endseg

beginseg
    name "object_dekunuts"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dekunuts/object_dekunuts.o"
endseg

beginseg
    name "object_bb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bb/object_bb.o"
endseg

beginseg
    name "object_death"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_death/object_death.o"
endseg

beginseg
    name "object_hata"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hata/object_hata.o"
endseg

beginseg
    name "object_wood02"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wood02/object_wood02.o"
endseg

beginseg
    name "object_trap"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_trap/object_trap.o"
endseg

beginseg
    name "object_vm"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_vm/object_vm.o"
endseg

beginseg
    name "object_efc_star_field"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_efc_star_field/object_efc_star_field.o"
endseg

beginseg
    name "object_rd"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_rd/object_rd.o"
endseg

beginseg
    name "object_yukimura_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_yukimura_obj/object_yukimura_obj.o"
endseg

beginseg
    name "object_horse_link_child"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_horse_link_child/object_horse_link_child.o"
endseg

beginseg
    name "object_syokudai"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_syokudai/object_syokudai.o"
endseg

beginseg
    name "object_efc_tw"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_efc_tw/object_efc_tw.o"
endseg

beginseg
    name "object_gi_key"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_key/object_gi_key.o"
endseg

beginseg
    name "object_mir_ray"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mir_ray/object_mir_ray.o"
endseg

beginseg
    name "object_ctower_rot"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ctower_rot/object_ctower_rot.o"
endseg

beginseg
    name "object_bdoor"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bdoor/object_bdoor.o"
endseg

beginseg
    name "object_sb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sb/object_sb.o"
endseg

beginseg
    name "object_gi_melody"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_melody/object_gi_melody.o"
endseg

beginseg
    name "object_gi_heart"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_heart/object_gi_heart.o"
endseg

beginseg
    name "object_gi_compass"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_compass/object_gi_compass.o"
endseg

beginseg
    name "object_gi_bosskey"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bosskey/object_gi_bosskey.o"
endseg

beginseg
    name "object_gi_nuts"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_nuts/object_gi_nuts.o"
endseg

beginseg
    name "object_gi_hearts"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_hearts/object_gi_hearts.o"
endseg

beginseg
    name "object_gi_arrowcase"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_arrowcase/object_gi_arrowcase.o"
endseg

beginseg
    name "object_gi_bombpouch"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bombpouch/object_gi_bombpouch.o"
endseg

beginseg
    name "object_in"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_in/object_in.o"
endseg

beginseg
    name "object_os_anime"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_os_anime/object_os_anime.o"
endseg

beginseg
    name "object_gi_bottle"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bottle/object_gi_bottle.o"
endseg

beginseg
    name "object_gi_stick"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_stick/object_gi_stick.o"
endseg

beginseg
    name "object_gi_map"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_map/object_gi_map.o"
endseg

beginseg
    name "object_oF1d_map"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_oF1d_map/object_oF1d_map.o"
endseg

beginseg
    name "object_ru2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ru2/object_ru2.o"
endseg

beginseg
    name "object_gi_magicpot"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_magicpot/object_gi_magicpot.o"
endseg

beginseg
    name "object_gi_bomb_1"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bomb_1/object_gi_bomb_1.o"
endseg

beginseg
    name "object_ma2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ma2/object_ma2.o"
endseg

beginseg
    name "object_gi_purse"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_purse/object_gi_purse.o"
endseg

beginseg
    name "object_rr"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_rr/object_rr.o"
endseg

beginseg
    name "object_gi_arrow"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_arrow/object_gi_arrow.o"
endseg

beginseg
    name "object_gi_bomb_2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bomb_2/object_gi_bomb_2.o"
endseg

beginseg
    name "object_gi_shield_2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_shield_2/object_gi_shield_2.o"
endseg

beginseg
    name "object_gi_hookshot"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_hookshot/object_gi_hookshot.o"
endseg

beginseg
    name "object_gi_ocarina"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_ocarina/object_gi_ocarina.o"
endseg

beginseg
    name "object_gi_milk"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_milk/object_gi_milk.o"
endseg

beginseg
    name "object_ma1"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ma1/object_ma1.o"
endseg

beginseg
    name "object_ny"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ny/object_ny.o"
endseg

beginseg
    name "object_fr"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fr/object_fr.o"
endseg

beginseg
    name "object_gi_bow"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bow/object_gi_bow.o"
endseg

beginseg
    name "object_gi_glasses"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_glasses/object_gi_glasses.o"
endseg

beginseg
    name "object_gi_liquid"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_liquid/object_gi_liquid.o"
endseg

beginseg
    name "object_ani"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ani/object_ani.o"
endseg

beginseg
    name "object_gi_shield_3"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_shield_3/object_gi_shield_3.o"
endseg

beginseg
    name "object_gi_bean"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bean/object_gi_bean.o"
endseg

beginseg
    name "object_gi_fish"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_fish/object_gi_fish.o"
endseg

beginseg
    name "object_gi_longsword"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_longsword/object_gi_longsword.o"
endseg

beginseg
    name "object_zo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zo/object_zo.o"
endseg

beginseg
    name "object_umajump"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_umajump/object_umajump.o"
endseg

beginseg
    name "object_mastergolon"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mastergolon/object_mastergolon.o"
endseg

beginseg
    name "object_masterzoora"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_masterzoora/object_masterzoora.o"
endseg

beginseg
    name "object_aob"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_aob/object_aob.o"
endseg

beginseg
    name "object_ik"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ik/object_ik.o"
endseg

beginseg
    name "object_ahg"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ahg/object_ahg.o"
endseg

beginseg
    name "object_cne"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_cne/object_cne.o"
endseg

beginseg
    name "object_bji"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bji/object_bji.o"
endseg

beginseg
    name "object_bba"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bba/object_bba.o"
endseg

beginseg
    name "object_an1"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_an1/object_an1.o"
endseg

beginseg
    name "object_boj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_boj/object_boj.o"
endseg

beginseg
    name "object_fz"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fz/object_fz.o"
endseg

beginseg
    name "object_bob"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bob/object_bob.o"
endseg

beginseg
    name "object_ge1"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ge1/object_ge1.o"
endseg

beginseg
    name "object_yabusame_point"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_yabusame_point/object_yabusame_point.o"
endseg

beginseg
    name "object_d_hsblock"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_d_hsblock/object_d_hsblock.o"
endseg

beginseg
    name "object_d_lift"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_d_lift/object_d_lift.o"
endseg

beginseg
    name "object_mamenoki"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mamenoki/object_mamenoki.o"
endseg

beginseg
    name "object_goroiwa"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_goroiwa/object_goroiwa.o"
endseg

beginseg
    name "object_toryo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_toryo/object_toryo.o"
endseg

beginseg
    name "object_daiku"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_daiku/object_daiku.o"
endseg

beginseg
    name "object_nwc"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_nwc/object_nwc.o"
endseg

beginseg
    name "object_gm"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gm/object_gm.o"
endseg

beginseg
    name "object_ms"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ms/object_ms.o"
endseg

beginseg
    name "object_hs"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hs/object_hs.o"
endseg

beginseg
    name "object_lightswitch"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_lightswitch/object_lightswitch.o"
endseg

beginseg
    name "object_kusa"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kusa/object_kusa.o"
endseg

beginseg
    name "object_tsubo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tsubo/object_tsubo.o"
endseg

beginseg
    name "object_kanban"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kanban/object_kanban.o"
endseg

beginseg
    name "object_owl"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_owl/object_owl.o"
endseg

beginseg
    name "object_mk"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mk/object_mk.o"
endseg

beginseg
    name "object_fu"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fu/object_fu.o"
endseg

beginseg
    name "object_gi_ki_tan_mask"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_ki_tan_mask/object_gi_ki_tan_mask.o"
endseg

beginseg
    name "object_gi_mask18"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask18/object_gi_mask18.o"
endseg

beginseg
    name "object_gi_rabit_mask"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_rabit_mask/object_gi_rabit_mask.o"
endseg

beginseg
    name "object_gi_truth_mask"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_truth_mask/object_gi_truth_mask.o"
endseg

beginseg
    name "object_stream"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_stream/object_stream.o"
endseg

beginseg
    name "object_mm"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mm/object_mm.o"
endseg

beginseg
    name "object_js"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_js/object_js.o"
endseg

beginseg
    name "object_cs"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_cs/object_cs.o"
endseg

beginseg
    name "object_gi_soldout"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_soldout/object_gi_soldout.o"
endseg

beginseg
    name "object_mag"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mag/object_mag.o"
endseg

beginseg
    name "object_gi_golonmask"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_golonmask/object_gi_golonmask.o"
endseg

beginseg
    name "object_gi_zoramask"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_zoramask/object_gi_zoramask.o"
endseg

beginseg
    name "object_ka"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ka/object_ka.o"
endseg

beginseg
    name "object_zg"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zg/object_zg.o"
endseg

beginseg
    name "object_gi_m_arrow"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_m_arrow/object_gi_m_arrow.o"
endseg

beginseg
    name "object_ds2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ds2/object_ds2.o"
endseg

beginseg
    name "object_fish"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fish/object_fish.o"
endseg

beginseg
    name "object_gi_sutaru"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_sutaru/object_gi_sutaru.o"
endseg

beginseg
    name "object_ssh"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ssh/object_ssh.o"
endseg

beginseg
    name "object_bigslime"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bigslime/object_bigslime.o"
endseg

beginseg
    name "object_bg"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bg/object_bg.o"
endseg

beginseg
    name "object_bombiwa"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bombiwa/object_bombiwa.o"
endseg

beginseg
    name "object_hintnuts"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hintnuts/object_hintnuts.o"
endseg

beginseg
    name "object_rs"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_rs/object_rs.o"
endseg

beginseg
    name "object_gla"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gla/object_gla.o"
endseg

beginseg
    name "object_geldb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_geldb/object_geldb.o"
endseg

beginseg
    name "object_dog"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dog/object_dog.o"
endseg

beginseg
    name "object_kibako2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kibako2/object_kibako2.o"
endseg

beginseg
    name "object_dns"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dns/object_dns.o"
endseg

beginseg
    name "object_dnk"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dnk/object_dnk.o"
endseg

beginseg
    name "object_gi_insect"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_insect/object_gi_insect.o"
endseg

beginseg
    name "object_gi_ghost"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_ghost/object_gi_ghost.o"
endseg

beginseg
    name "object_gi_soul"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_soul/object_gi_soul.o"
endseg

beginseg
    name "object_f40_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_f40_obj/object_f40_obj.o"
endseg

beginseg
    name "object_gi_rupy"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_rupy/object_gi_rupy.o"
endseg

beginseg
    name "object_po_composer"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_po_composer/object_po_composer.o"
endseg

beginseg
    name "object_mu"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mu/object_mu.o"
endseg

beginseg
    name "object_wf"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wf/object_wf.o"
endseg

beginseg
    name "object_skb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_skb/object_skb.o"
endseg

beginseg
    name "object_gs"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gs/object_gs.o"
endseg

beginseg
    name "object_ps"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ps/object_ps.o"
endseg

beginseg
    name "object_omoya_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_omoya_obj/object_omoya_obj.o"
endseg

beginseg
    name "object_crow"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_crow/object_crow.o"
endseg

beginseg
    name "object_cow"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_cow/object_cow.o"
endseg

beginseg
    name "object_gi_sword_1"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_sword_1/object_gi_sword_1.o"
endseg

beginseg
    name "object_zl4"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zl4/object_zl4.o"
endseg

beginseg
    name "object_grasshopper"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_grasshopper/object_grasshopper.o"
endseg

beginseg
    name "object_boyo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_boyo/object_boyo.o"
endseg

beginseg
    name "object_fwall"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fwall/object_fwall.o"
endseg

beginseg
    name "object_jso"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_jso/object_jso.o"
endseg

beginseg
    name "object_knight"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_knight/object_knight.o"
endseg

beginseg
    name "object_icicle"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_icicle/object_icicle.o"
endseg

beginseg
    name "object_spdweb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_spdweb/object_spdweb.o"
endseg

beginseg
    name "object_boss01"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_boss01/object_boss01.o"
endseg

beginseg
    name "object_boss02"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_boss02/object_boss02.o"
endseg

beginseg
    name "object_boss03"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_boss03/object_boss03.o"
endseg

beginseg
    name "object_boss04"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_boss04/object_boss04.o"
endseg

beginseg
    name "object_boss05"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_boss05/object_boss05.o"
endseg

beginseg
    name "object_boss07"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_boss07/object_boss07.o"
endseg

beginseg
    name "object_raf"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_raf/object_raf.o"
endseg

beginseg
    name "object_funen"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_funen/object_funen.o"
endseg

beginseg
    name "object_raillift"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_raillift/object_raillift.o"
endseg

beginseg
    name "object_numa_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_numa_obj/object_numa_obj.o"
endseg

beginseg
    name "object_flowerpot"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_flowerpot/object_flowerpot.o"
endseg

beginseg
    name "object_spinyroll"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_spinyroll/object_spinyroll.o"
endseg

beginseg
    name "object_ice_block"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ice_block/object_ice_block.o"
endseg

beginseg
    name "object_keikoku_demo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_keikoku_demo/object_keikoku_demo.o"
endseg

beginseg
    name "object_slime"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_slime/object_slime.o"
endseg

beginseg
    name "object_pr"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_pr/object_pr.o"
endseg

beginseg
    name "object_f52_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_f52_obj/object_f52_obj.o"
endseg

beginseg
    name "object_f53_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_f53_obj/object_f53_obj.o"
endseg

beginseg
    name "object_kibako"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kibako/object_kibako.o"
endseg

beginseg
    name "object_sek"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sek/object_sek.o"
endseg

beginseg
    name "object_gmo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gmo/object_gmo.o"
endseg

beginseg
    name "object_bat"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bat/object_bat.o"
endseg

beginseg
    name "object_sekihil"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sekihil/object_sekihil.o"
endseg

beginseg
    name "object_sekihig"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sekihig/object_sekihig.o"
endseg

beginseg
    name "object_sekihin"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sekihin/object_sekihin.o"
endseg

beginseg
    name "object_sekihiz"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sekihiz/object_sekihiz.o"
endseg

beginseg
    name "object_wiz"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wiz/object_wiz.o"
endseg

beginseg
    name "object_ladder"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ladder/object_ladder.o"
endseg

beginseg
    name "object_mkk"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mkk/object_mkk.o"
endseg

beginseg
    name "object_keikoku_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_keikoku_obj/object_keikoku_obj.o"
endseg

beginseg
    name "object_sichitai_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sichitai_obj/object_sichitai_obj.o"
endseg

beginseg
    name "object_dekucity_ana_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dekucity_ana_obj/object_dekucity_ana_obj.o"
endseg

beginseg
    name "object_rat"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_rat/object_rat.o"
endseg

beginseg
    name "object_water_effect"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_water_effect/object_water_effect.o"
endseg

beginseg
    name "object_dblue_object"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dblue_object/object_dblue_object.o"
endseg

beginseg
    name "object_bal"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bal/object_bal.o"
endseg

beginseg
    name "object_warp_uzu"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_warp_uzu/object_warp_uzu.o"
endseg

beginseg
    name "object_driftice"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_driftice/object_driftice.o"
endseg

beginseg
    name "object_fall"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fall/object_fall.o"
endseg

beginseg
    name "object_hanareyama_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hanareyama_obj/object_hanareyama_obj.o"
endseg

beginseg
    name "object_crace_object"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_crace_object/object_crace_object.o"
endseg

beginseg
    name "object_dno"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dno/object_dno.o"
endseg

beginseg
    name "object_obj_tokeidai"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_obj_tokeidai/object_obj_tokeidai.o"
endseg

beginseg
    name "object_eg"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_eg/object_eg.o"
endseg

beginseg
    name "object_tru"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tru/object_tru.o"
endseg

beginseg
    name "object_trt"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_trt/object_trt.o"
endseg

beginseg
    name "object_hakugin_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hakugin_obj/object_hakugin_obj.o"
endseg

beginseg
    name "object_horse_game_check"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_horse_game_check/object_horse_game_check.o"
endseg

beginseg
    name "object_stk"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_stk/object_stk.o"
endseg

beginseg
    name "object_mnk"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mnk/object_mnk.o"
endseg

beginseg
    name "object_gi_bottle_red"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bottle_red/object_gi_bottle_red.o"
endseg

beginseg
    name "object_tokei_tobira"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tokei_tobira/object_tokei_tobira.o"
endseg

beginseg
    name "object_az"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_az/object_az.o"
endseg

beginseg
    name "object_twig"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_twig/object_twig.o"
endseg

beginseg
    name "object_dekucity_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dekucity_obj/object_dekucity_obj.o"
endseg

beginseg
    name "object_po_fusen"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_po_fusen/object_po_fusen.o"
endseg

beginseg
    name "object_racetsubo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_racetsubo/object_racetsubo.o"
endseg

beginseg
    name "object_ha"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ha/object_ha.o"
endseg

beginseg
    name "object_bigokuta"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bigokuta/object_bigokuta.o"
endseg

beginseg
    name "object_open_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_open_obj/object_open_obj.o"
endseg

beginseg
    name "object_fu_kaiten"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fu_kaiten/object_fu_kaiten.o"
endseg

beginseg
    name "object_fu_mato"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fu_mato/object_fu_mato.o"
endseg

beginseg
    name "object_mtoride"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mtoride/object_mtoride.o"
endseg

beginseg
    name "object_osn"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_osn/object_osn.o"
endseg

beginseg
    name "object_tokei_step"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tokei_step/object_tokei_step.o"
endseg

beginseg
    name "object_lotus"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_lotus/object_lotus.o"
endseg

beginseg
    name "object_tl"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tl/object_tl.o"
endseg

beginseg
    name "object_dkjail_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dkjail_obj/object_dkjail_obj.o"
endseg

beginseg
    name "object_visiblock"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_visiblock/object_visiblock.o"
endseg

beginseg
    name "object_tsn"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tsn/object_tsn.o"
endseg

beginseg
    name "object_ds2n"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ds2n/object_ds2n.o"
endseg

beginseg
    name "object_fsn"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fsn/object_fsn.o"
endseg

beginseg
    name "object_shn"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_shn/object_shn.o"
endseg

beginseg
    name "object_bigicicle"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bigicicle/object_bigicicle.o"
endseg

beginseg
    name "object_gi_bottle_15"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bottle_15/object_gi_bottle_15.o"
endseg

beginseg
    name "object_tk"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tk/object_tk.o"
endseg

beginseg
    name "object_market_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_market_obj/object_market_obj.o"
endseg

beginseg
    name "object_gi_reserve00"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_reserve00/object_gi_reserve00.o"
endseg

beginseg
    name "object_gi_reserve01"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_reserve01/object_gi_reserve01.o"
endseg

beginseg
    name "object_lightblock"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_lightblock/object_lightblock.o"
endseg

beginseg
    name "object_takaraya_objects"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_takaraya_objects/object_takaraya_objects.o"
endseg

beginseg
    name "object_wdhand"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wdhand/object_wdhand.o"
endseg

beginseg
    name "object_sdn"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sdn/object_sdn.o"
endseg

beginseg
    name "object_snowwd"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_snowwd/object_snowwd.o"
endseg

beginseg
    name "object_giant"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_giant/object_giant.o"
endseg

beginseg
    name "object_comb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_comb/object_comb.o"
endseg

beginseg
    name "object_hana"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hana/object_hana.o"
endseg

beginseg
    name "object_boss_hakugin"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_boss_hakugin/object_boss_hakugin.o"
endseg

beginseg
    name "object_meganeana_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_meganeana_obj/object_meganeana_obj.o"
endseg

beginseg
    name "object_gi_nutsmask"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_nutsmask/object_gi_nutsmask.o"
endseg

beginseg
    name "object_stk2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_stk2/object_stk2.o"
endseg

beginseg
    name "object_spot11_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_spot11_obj/object_spot11_obj.o"
endseg

beginseg
    name "object_danpei_object"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_danpei_object/object_danpei_object.o"
endseg

beginseg
    name "object_dhouse"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dhouse/object_dhouse.o"
endseg

beginseg
    name "object_hakaisi"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hakaisi/object_hakaisi.o"
endseg

beginseg
    name "object_po"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_po/object_po.o"
endseg

beginseg
    name "object_snowman"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_snowman/object_snowman.o"
endseg

beginseg
    name "object_po_sisters"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_po_sisters/object_po_sisters.o"
endseg

beginseg
    name "object_pp"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_pp/object_pp.o"
endseg

beginseg
    name "object_goronswitch"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_goronswitch/object_goronswitch.o"
endseg

beginseg
    name "object_delf"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_delf/object_delf.o"
endseg

beginseg
    name "object_botihasira"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_botihasira/object_botihasira.o"
endseg

beginseg
    name "object_gi_bigbomb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bigbomb/object_gi_bigbomb.o"
endseg

beginseg
    name "object_pst"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_pst/object_pst.o"
endseg

beginseg
    name "object_bsmask"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bsmask/object_bsmask.o"
endseg

beginseg
    name "object_spidertent"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_spidertent/object_spidertent.o"
endseg

beginseg
    name "object_zoraegg"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zoraegg/object_zoraegg.o"
endseg

beginseg
    name "object_kbt"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kbt/object_kbt.o"
endseg

beginseg
    name "object_gg"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gg/object_gg.o"
endseg

beginseg
    name "object_maruta"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_maruta/object_maruta.o"
endseg

beginseg
    name "object_ghaka"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ghaka/object_ghaka.o"
endseg

beginseg
    name "object_oyu"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_oyu/object_oyu.o"
endseg

beginseg
    name "object_dnq"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dnq/object_dnq.o"
endseg

beginseg
    name "object_dai"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dai/object_dai.o"
endseg

beginseg
    name "object_kgy"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kgy/object_kgy.o"
endseg

beginseg
    name "object_fb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fb/object_fb.o"
endseg

beginseg
    name "object_taisou"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_taisou/object_taisou.o"
endseg

beginseg
    name "object_gk"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gk/object_gk.o"
endseg

beginseg
    name "object_haka_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_haka_obj/object_haka_obj.o"
endseg

beginseg
    name "object_dnt"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dnt/object_dnt.o"
endseg

beginseg
    name "object_yukiyama"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_yukiyama/object_yukiyama.o"
endseg

beginseg
    name "object_icefloe"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_icefloe/object_icefloe.o"
endseg

beginseg
    name "object_gi_gold_dust"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_gold_dust/object_gi_gold_dust.o"
endseg

beginseg
    name "object_gi_bottle_16"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bottle_16/object_gi_bottle_16.o"
endseg

beginseg
    name "object_gi_bottle_22"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bottle_22/object_gi_bottle_22.o"
endseg

beginseg
    name "object_bee"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bee/object_bee.o"
endseg

beginseg
    name "object_ot"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ot/object_ot.o"
endseg

beginseg
    name "object_utubo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_utubo/object_utubo.o"
endseg

beginseg
    name "object_dora"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dora/object_dora.o"
endseg

beginseg
    name "object_gi_loach"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_loach/object_gi_loach.o"
endseg

beginseg
    name "object_gi_seahorse"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_seahorse/object_gi_seahorse.o"
endseg

beginseg
    name "object_bigpo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bigpo/object_bigpo.o"
endseg

beginseg
    name "object_hariko"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hariko/object_hariko.o"
endseg

beginseg
    name "object_dnj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dnj/object_dnj.o"
endseg

beginseg
    name "object_sinkai_kabe"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sinkai_kabe/object_sinkai_kabe.o"
endseg

beginseg
    name "object_kin2_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kin2_obj/object_kin2_obj.o"
endseg

beginseg
    name "object_ishi"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ishi/object_ishi.o"
endseg

beginseg
    name "object_hakugin_demo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hakugin_demo/object_hakugin_demo.o"
endseg

beginseg
    name "object_jg"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_jg/object_jg.o"
endseg

beginseg
    name "object_gi_sword_2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_sword_2/object_gi_sword_2.o"
endseg

beginseg
    name "object_gi_sword_3"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_sword_3/object_gi_sword_3.o"
endseg

beginseg
    name "object_gi_sword_4"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_sword_4/object_gi_sword_4.o"
endseg

beginseg
    name "object_um"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_um/object_um.o"
endseg

beginseg
    name "object_rb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_rb/object_rb.o"
endseg

beginseg
    name "object_mbar_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_mbar_obj/object_mbar_obj.o"
endseg

beginseg
    name "object_ikana_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ikana_obj/object_ikana_obj.o"
endseg

beginseg
    name "object_kz"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kz/object_kz.o"
endseg

beginseg
    name "object_tokei_turret"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tokei_turret/object_tokei_turret.o"
endseg

beginseg
    name "object_zog"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zog/object_zog.o"
endseg

beginseg
    name "object_rotlift"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_rotlift/object_rotlift.o"
endseg

beginseg
    name "object_posthouse_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_posthouse_obj/object_posthouse_obj.o"
endseg

beginseg
    name "object_gi_mask09"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask09/object_gi_mask09.o"
endseg

beginseg
    name "object_gi_mask14"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask14/object_gi_mask14.o"
endseg

beginseg
    name "object_gi_mask15"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask15/object_gi_mask15.o"
endseg

beginseg
    name "object_inibs_object"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_inibs_object/object_inibs_object.o"
endseg

beginseg
    name "object_tree"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tree/object_tree.o"
endseg

beginseg
    name "object_kaizoku_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kaizoku_obj/object_kaizoku_obj.o"
endseg

beginseg
    name "object_gi_reserve_b_00"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_reserve_b_00/object_gi_reserve_b_00.o"
endseg

beginseg
    name "object_gi_reserve_c_00"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_reserve_c_00/object_gi_reserve_c_00.o"
endseg

beginseg
    name "object_zob"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zob/object_zob.o"
endseg

beginseg
    name "object_milkbar"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_milkbar/object_milkbar.o"
endseg

beginseg
    name "object_dmask"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dmask/object_dmask.o"
endseg

beginseg
    name "object_gi_reserve_c_01"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_reserve_c_01/object_gi_reserve_c_01.o"
endseg

beginseg
    name "object_zod"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zod/object_zod.o"
endseg

beginseg
    name "object_kumo30"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kumo30/object_kumo30.o"
endseg

beginseg
    name "object_obj_yasi"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_obj_yasi/object_obj_yasi.o"
endseg

beginseg
    name "object_tanron1"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tanron1/object_tanron1.o"
endseg

beginseg
    name "object_tanron2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tanron2/object_tanron2.o"
endseg

beginseg
    name "object_tanron3"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tanron3/object_tanron3.o"
endseg

beginseg
    name "object_gi_magicmushroom"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_magicmushroom/object_gi_magicmushroom.o"
endseg

beginseg
    name "object_obj_chan"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_obj_chan/object_obj_chan.o"
endseg

beginseg
    name "object_gi_mask10"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask10/object_gi_mask10.o"
endseg

beginseg
    name "object_zos"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zos/object_zos.o"
endseg

beginseg
    name "object_an2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_an2/object_an2.o"
endseg

beginseg
    name "object_an3"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_an3/object_an3.o"
endseg

beginseg
    name "object_f40_switch"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_f40_switch/object_f40_switch.o"
endseg

beginseg
    name "object_lodmoon"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_lodmoon/object_lodmoon.o"
endseg

beginseg
    name "object_tro"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tro/object_tro.o"
endseg

beginseg
    name "object_gi_mask12"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask12/object_gi_mask12.o"
endseg

beginseg
    name "object_gi_mask23"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask23/object_gi_mask23.o"
endseg

beginseg
    name "object_gi_bottle_21"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bottle_21/object_gi_bottle_21.o"
endseg

beginseg
    name "object_gi_camera"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_camera/object_gi_camera.o"
endseg

beginseg
    name "object_kamejima"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kamejima/object_kamejima.o"
endseg

beginseg
    name "object_nb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_nb/object_nb.o"
endseg

beginseg
    name "object_harfgibud"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_harfgibud/object_harfgibud.o"
endseg

beginseg
    name "object_zov"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zov/object_zov.o"
endseg

beginseg
    name "object_ah"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ah/object_ah.o"
endseg

beginseg
    name "object_hgdoor"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hgdoor/object_hgdoor.o"
endseg

beginseg
    name "object_dor01"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dor01/object_dor01.o"
endseg

beginseg
    name "object_dor02"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dor02/object_dor02.o"
endseg

beginseg
    name "object_dor03"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dor03/object_dor03.o"
endseg

beginseg
    name "object_dor04"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dor04/object_dor04.o"
endseg

beginseg
    name "object_last_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_last_obj/object_last_obj.o"
endseg

beginseg
    name "object_redead_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_redead_obj/object_redead_obj.o"
endseg

beginseg
    name "object_ikninside_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ikninside_obj/object_ikninside_obj.o"
endseg

beginseg
    name "object_iknv_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_iknv_obj/object_iknv_obj.o"
endseg

beginseg
    name "object_pamera"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_pamera/object_pamera.o"
endseg

beginseg
    name "object_hsstump"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hsstump/object_hsstump.o"
endseg

beginseg
    name "object_zm"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zm/object_zm.o"
endseg

beginseg
    name "object_al"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_al/object_al.o"
endseg

beginseg
    name "object_tab"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tab/object_tab.o"
endseg

beginseg
    name "object_secom_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_secom_obj/object_secom_obj.o"
endseg

beginseg
    name "object_dt"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_dt/object_dt.o"
endseg

beginseg
    name "object_gi_mask03"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask03/object_gi_mask03.o"
endseg

beginseg
    name "object_cha"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_cha/object_cha.o"
endseg

beginseg
    name "object_obj_dinner"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_obj_dinner/object_obj_dinner.o"
endseg

beginseg
    name "object_gi_reserve_b_01"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_reserve_b_01/object_gi_reserve_b_01.o"
endseg

beginseg
    name "object_lastday"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_lastday/object_lastday.o"
endseg

beginseg
    name "object_bai"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bai/object_bai.o"
endseg

beginseg
    name "object_ikn_demo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ikn_demo/object_ikn_demo.o"
endseg

beginseg
    name "object_gi_fieldmap"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_fieldmap/object_gi_fieldmap.o"
endseg

beginseg
    name "object_big_fwall"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_big_fwall/object_big_fwall.o"
endseg

beginseg
    name "object_hunsui"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_hunsui/object_hunsui.o"
endseg

beginseg
    name "object_uch"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_uch/object_uch.o"
endseg

beginseg
    name "object_tanron4"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tanron4/object_tanron4.o"
endseg

beginseg
    name "object_tanron5"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_tanron5/object_tanron5.o"
endseg

beginseg
    name "object_in2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_in2/object_in2.o"
endseg

beginseg
    name "object_yb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_yb/object_yb.o"
endseg

beginseg
    name "object_rz"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_rz/object_rz.o"
endseg

beginseg
    name "object_bjt"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bjt/object_bjt.o"
endseg

beginseg
    name "object_taru"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_taru/object_taru.o"
endseg

beginseg
    name "object_moonston"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_moonston/object_moonston.o"
endseg

beginseg
    name "object_gi_schedule"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_schedule/object_gi_schedule.o"
endseg

beginseg
    name "object_gi_stonemask"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_stonemask/object_gi_stonemask.o"
endseg

beginseg
    name "object_zoraband"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_zoraband/object_zoraband.o"
endseg

beginseg
    name "object_kepn_koya"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kepn_koya/object_kepn_koya.o"
endseg

beginseg
    name "object_obj_usiyane"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_obj_usiyane/object_obj_usiyane.o"
endseg

beginseg
    name "object_gi_mask05"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask05/object_gi_mask05.o"
endseg

beginseg
    name "object_gi_mask11"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask11/object_gi_mask11.o"
endseg

beginseg
    name "object_gi_mask20"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask20/object_gi_mask20.o"
endseg

beginseg
    name "object_nnh"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_nnh/object_nnh.o"
endseg

beginseg
    name "object_kzsaku"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kzsaku/object_kzsaku.o"
endseg

beginseg
    name "object_obj_milk_bin"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_obj_milk_bin/object_obj_milk_bin.o"
endseg

beginseg
    name "object_random_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_random_obj/object_random_obj.o"
endseg

beginseg
    name "object_kujiya"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kujiya/object_kujiya.o"
endseg

beginseg
    name "object_kitan"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kitan/object_kitan.o"
endseg

beginseg
    name "object_gi_mask06"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask06/object_gi_mask06.o"
endseg

beginseg
    name "object_gi_mask16"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask16/object_gi_mask16.o"
endseg

beginseg
    name "object_astr_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_astr_obj/object_astr_obj.o"
endseg

beginseg
    name "object_bsb"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bsb/object_bsb.o"
endseg

beginseg
    name "object_fall2"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fall2/object_fall2.o"
endseg

beginseg
    name "object_sth"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_sth/object_sth.o"
endseg

beginseg
    name "object_gi_mssa"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mssa/object_gi_mssa.o"
endseg

beginseg
    name "object_smtower"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_smtower/object_smtower.o"
endseg

beginseg
    name "object_gi_mask21"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask21/object_gi_mask21.o"
endseg

beginseg
    name "object_yado_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_yado_obj/object_yado_obj.o"
endseg

beginseg
    name "object_syoten"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_syoten/object_syoten.o"
endseg

beginseg
    name "object_moonend"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_moonend/object_moonend.o"
endseg

beginseg
    name "object_ob"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ob/object_ob.o"
endseg

beginseg
    name "object_gi_bottle_04"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_bottle_04/object_gi_bottle_04.o"
endseg

beginseg
    name "object_and"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_and/object_and.o"
endseg

beginseg
    name "object_obj_danpeilift"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_obj_danpeilift/object_obj_danpeilift.o"
endseg

beginseg
    name "object_drs"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_drs/object_drs.o"
endseg

beginseg
    name "object_msmo"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_msmo/object_msmo.o"
endseg

beginseg
    name "object_an4"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_an4/object_an4.o"
endseg

beginseg
    name "object_wdor01"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wdor01/object_wdor01.o"
endseg

beginseg
    name "object_wdor02"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wdor02/object_wdor02.o"
endseg

beginseg
    name "object_wdor03"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wdor03/object_wdor03.o"
endseg

beginseg
    name "object_wdor04"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wdor04/object_wdor04.o"
endseg

beginseg
    name "object_wdor05"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_wdor05/object_wdor05.o"
endseg

beginseg
    name "object_stk3"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_stk3/object_stk3.o"
endseg

beginseg
    name "object_kinsta1_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kinsta1_obj/object_kinsta1_obj.o"
endseg

beginseg
    name "object_kinsta2_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_kinsta2_obj/object_kinsta2_obj.o"
endseg

beginseg
    name "object_bh"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_bh/object_bh.o"
endseg

beginseg
    name "object_gi_mask17"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask17/object_gi_mask17.o"
endseg

beginseg
    name "object_gi_mask22"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask22/object_gi_mask22.o"
endseg

beginseg
    name "object_lbfshot"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_lbfshot/object_lbfshot.o"
endseg

beginseg
    name "object_fusen"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_fusen/object_fusen.o"
endseg

beginseg
    name "object_ending_obj"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_ending_obj/object_ending_obj.o"
endseg

beginseg
    name "object_gi_mask13"
    compress
    romalign 0x1000
    number 6
    include "build/assets/objects/object_gi_mask13/object_gi_mask13.o"
endseg

beginseg
    name "scene_texture_01"
    compress
    romalign 0x1000
    number 6
    include "build/assets/misc/scene_texture_01/scene_texture_01.o"
endseg

beginseg
    name "scene_texture_02"
    compress
    romalign 0x1000
    number 6
    include "build/assets/misc/scene_texture_02/scene_texture_02.o"
endseg

beginseg
    name "scene_texture_03"
    compress
    romalign 0x1000
    number 6
    include "build/assets/misc/scene_texture_03/scene_texture_03.o"
endseg

beginseg
    name "scene_texture_04"
    compress
    romalign 0x1000
    number 6
    include "build/assets/misc/scene_texture_04/scene_texture_04.o"
endseg

beginseg
    name "scene_texture_05"
    compress
    romalign 0x1000
    number 6
    include "build/assets/misc/scene_texture_05/scene_texture_05.o"
endseg

beginseg
    name "scene_texture_06"
    compress
    romalign 0x1000
    number 6
    include "build/assets/misc/scene_texture_06/scene_texture_06.o"
endseg

beginseg
    name "scene_texture_07"
    compress
    romalign 0x1000
    number 6
    include "build/assets/misc/scene_texture_07/scene_texture_07.o"
endseg

beginseg
    name "scene_texture_08"
    compress
    romalign 0x1000
    number 6
    include "build/assets/misc/scene_texture_08/scene_texture_08.o"
endseg

beginseg
    name "nintendo_rogo_static"
    compress
    romalign 0x1000
    include "build/assets/misc/nintendo_rogo_static/nintendo_rogo_static.o"
    number 1
endseg

beginseg
    name "title_static"
    compress
    romalign 0x1000
    include "build/assets/misc/title_static/title_static.o"
    number 1
endseg

beginseg
    name "memerrmsg"
    compress
    romalign 0x1000
    include "build/assets/misc/memerrmsg/memerrmsg.o"
    number 1
endseg

beginseg
    name "locerrmsg"
    compress
    romalign 0x1000
    include "build/assets/misc/locerrmsg/locerrmsg.o"
    number 1
endseg

beginseg
    name "parameter_static"
    compress
    romalign 0x1000
    include "build/assets/interface/parameter_static/parameter_static.o"
    number 2
endseg

beginseg
    name "week_static"
    romalign 0x1000
    include "build/assets/interface/week_static/week_static.o"
    number 9
endseg

beginseg
    name "daytelop_static"
    compress
    romalign 0x1000
    include "build/assets/misc/daytelop_static/daytelop_static.o"
    number 9
endseg

beginseg
    name "ger_daytelop_static"
    compress
    romalign 0x1000
    include "build/assets/misc/ger_daytelop_static/ger_daytelop_static.o"
    number 9
endseg

beginseg
    name "fra_daytelop_static"
    compress
    romalign 0x1000
    include "build/assets/misc/fra_daytelop_static/fra_daytelop_static.o"
    number 9
endseg

beginseg
    name "esp_daytelop_static"
    compress
    romalign 0x1000
    include "build/assets/misc/esp_daytelop_static/esp_daytelop_static.o"
    number 9
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
    include "build/assets/scenes/Z2_20SICHITAI2/Z2_20SICHITAI2.o"
    number 2
endseg

beginseg
    name "Z2_20SICHITAI2_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_20SICHITAI2/Z2_20SICHITAI2_room_00.o"
    number 3
endseg

beginseg
    name "Z2_20SICHITAI2_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_20SICHITAI2/Z2_20SICHITAI2_room_01.o"
    number 3
endseg

beginseg
    name "Z2_20SICHITAI2_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_20SICHITAI2/Z2_20SICHITAI2_room_02.o"
    number 3
endseg

beginseg
    name "Z2_WITCH_SHOP"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_WITCH_SHOP/Z2_WITCH_SHOP.o"
    number 2
endseg

beginseg
    name "Z2_WITCH_SHOP_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_WITCH_SHOP/Z2_WITCH_SHOP_room_00.o"
    number 3
endseg

beginseg
    name "Z2_LAST_BS"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_BS/Z2_LAST_BS.o"
    number 2
endseg

beginseg
    name "Z2_LAST_BS_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_BS/Z2_LAST_BS_room_00.o"
    number 3
endseg

beginseg
    name "Z2_HAKASHITA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKASHITA/Z2_HAKASHITA.o"
    number 2
endseg

beginseg
    name "Z2_HAKASHITA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKASHITA/Z2_HAKASHITA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_HAKASHITA_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKASHITA/Z2_HAKASHITA_room_01.o"
    number 3
endseg

beginseg
    name "Z2_HAKASHITA_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKASHITA/Z2_HAKASHITA_room_02.o"
    number 3
endseg

beginseg
    name "Z2_HAKASHITA_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKASHITA/Z2_HAKASHITA_room_03.o"
    number 3
endseg

beginseg
    name "Z2_HAKASHITA_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKASHITA/Z2_HAKASHITA_room_04.o"
    number 3
endseg

beginseg
    name "Z2_AYASHIISHOP"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_AYASHIISHOP/Z2_AYASHIISHOP.o"
    number 2
endseg

beginseg
    name "Z2_AYASHIISHOP_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_AYASHIISHOP/Z2_AYASHIISHOP_room_00.o"
    number 3
endseg

beginseg
    name "Z2_AYASHIISHOP_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_AYASHIISHOP/Z2_AYASHIISHOP_room_01.o"
    number 3
endseg

beginseg
    name "Z2_OMOYA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_OMOYA/Z2_OMOYA.o"
    number 2
endseg

beginseg
    name "Z2_OMOYA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_OMOYA/Z2_OMOYA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_OMOYA_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_OMOYA/Z2_OMOYA_room_01.o"
    number 3
endseg

beginseg
    name "Z2_OMOYA_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_OMOYA/Z2_OMOYA_room_02.o"
    number 3
endseg

beginseg
    name "Z2_BOWLING"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BOWLING/Z2_BOWLING.o"
    number 2
endseg

beginseg
    name "Z2_BOWLING_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BOWLING/Z2_BOWLING_room_00.o"
    number 3
endseg

beginseg
    name "Z2_SONCHONOIE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SONCHONOIE/Z2_SONCHONOIE.o"
    number 2
endseg

beginseg
    name "Z2_SONCHONOIE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SONCHONOIE/Z2_SONCHONOIE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_SONCHONOIE_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SONCHONOIE/Z2_SONCHONOIE_room_01.o"
    number 3
endseg

beginseg
    name "Z2_SONCHONOIE_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SONCHONOIE/Z2_SONCHONOIE_room_02.o"
    number 3
endseg

beginseg
    name "Z2_SONCHONOIE_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SONCHONOIE/Z2_SONCHONOIE_room_03.o"
    number 3
endseg

beginseg
    name "Z2_IKANA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKANA/Z2_IKANA.o"
    number 2
endseg

beginseg
    name "Z2_IKANA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKANA/Z2_IKANA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_IKANA_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKANA/Z2_IKANA_room_01.o"
    number 3
endseg

beginseg
    name "Z2_IKANA_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKANA/Z2_IKANA_room_02.o"
    number 3
endseg

beginseg
    name "Z2_IKANA_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKANA/Z2_IKANA_room_03.o"
    number 3
endseg

beginseg
    name "Z2_IKANA_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKANA/Z2_IKANA_room_04.o"
    number 3
endseg

beginseg
    name "Z2_KAIZOKU"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KAIZOKU/Z2_KAIZOKU.o"
    number 2
endseg

beginseg
    name "Z2_KAIZOKU_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KAIZOKU/Z2_KAIZOKU_room_00.o"
    number 3
endseg

beginseg
    name "Z2_MILK_BAR"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MILK_BAR/Z2_MILK_BAR.o"
    number 2
endseg

beginseg
    name "Z2_MILK_BAR_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MILK_BAR/Z2_MILK_BAR_room_00.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N.o"
    number 2
endseg

beginseg
    name "Z2_INISIE_N_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_00.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_01.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_02.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_03.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_04.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_05.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_06.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_07.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_08.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_09"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_09.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_10"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_10.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_N_room_11"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_N/Z2_INISIE_N_room_11.o"
    number 3
endseg

beginseg
    name "Z2_TAKARAYA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TAKARAYA/Z2_TAKARAYA.o"
    number 2
endseg

beginseg
    name "Z2_TAKARAYA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TAKARAYA/Z2_TAKARAYA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R.o"
    number 2
endseg

beginseg
    name "Z2_INISIE_R_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_00.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_01.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_02.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_03.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_04.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_05.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_06.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_07.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_08.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_09"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_09.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_10"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_10.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_R_room_11"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_R/Z2_INISIE_R_room_11.o"
    number 3
endseg

beginseg
    name "Z2_OKUJOU"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_OKUJOU/Z2_OKUJOU.o"
    number 2
endseg

beginseg
    name "Z2_OKUJOU_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_OKUJOU/Z2_OKUJOU_room_00.o"
    number 3
endseg

beginseg
    name "Z2_OPENINGDAN"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_OPENINGDAN/Z2_OPENINGDAN.o"
    number 2
endseg

beginseg
    name "Z2_OPENINGDAN_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_OPENINGDAN/Z2_OPENINGDAN_room_00.o"
    number 3
endseg

beginseg
    name "Z2_OPENINGDAN_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_OPENINGDAN/Z2_OPENINGDAN_room_01.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN.o"
    number 2
endseg

beginseg
    name "Z2_MITURIN_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_00.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_01.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_02.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_03.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_04.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_05.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_06.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_07.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_08.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_09"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_09.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_10"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_10.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_11"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_11.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_room_12"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN/Z2_MITURIN_room_12.o"
    number 3
endseg

beginseg
    name "Z2_13HUBUKINOMITI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_13HUBUKINOMITI/Z2_13HUBUKINOMITI.o"
    number 2
endseg

beginseg
    name "Z2_13HUBUKINOMITI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_13HUBUKINOMITI/Z2_13HUBUKINOMITI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE.o"
    number 2
endseg

beginseg
    name "Z2_CASTLE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_01.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_02.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_03.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_04.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_05.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_06.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_07.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_08.o"
    number 3
endseg

beginseg
    name "Z2_CASTLE_room_09"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CASTLE/Z2_CASTLE_room_09.o"
    number 3
endseg

beginseg
    name "Z2_DEKUTES"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DEKUTES/Z2_DEKUTES.o"
    number 2
endseg

beginseg
    name "Z2_DEKUTES_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DEKUTES/Z2_DEKUTES_room_00.o"
    number 3
endseg

beginseg
    name "Z2_MITURIN_BS"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN_BS/Z2_MITURIN_BS.o"
    number 2
endseg

beginseg
    name "Z2_MITURIN_BS_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MITURIN_BS/Z2_MITURIN_BS_room_00.o"
    number 3
endseg

beginseg
    name "Z2_SYATEKI_MIZU"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SYATEKI_MIZU/Z2_SYATEKI_MIZU.o"
    number 2
endseg

beginseg
    name "Z2_SYATEKI_MIZU_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SYATEKI_MIZU/Z2_SYATEKI_MIZU_room_00.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN.o"
    number 2
endseg

beginseg
    name "Z2_HAKUGIN_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_00.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_01.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_02.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_03.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_04.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_05.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_06.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_07.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_08.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_09"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_09.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_10"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_10.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_11"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_11.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_12"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_12.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_room_13"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN/Z2_HAKUGIN_room_13.o"
    number 3
endseg

beginseg
    name "Z2_ROMANYMAE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_ROMANYMAE/Z2_ROMANYMAE.o"
    number 2
endseg

beginseg
    name "Z2_ROMANYMAE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_ROMANYMAE/Z2_ROMANYMAE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE.o"
    number 2
endseg

beginseg
    name "Z2_PIRATE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_01.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_02.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_03.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_04.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_05.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_06.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_07.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_08.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_09"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_09.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_10"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_10.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_11"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_11.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_12"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_12.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_13"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_13.o"
    number 3
endseg

beginseg
    name "Z2_PIRATE_room_14"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_PIRATE/Z2_PIRATE_room_14.o"
    number 3
endseg

beginseg
    name "Z2_SYATEKI_MORI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SYATEKI_MORI/Z2_SYATEKI_MORI.o"
    number 2
endseg

beginseg
    name "Z2_SYATEKI_MORI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SYATEKI_MORI/Z2_SYATEKI_MORI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_SINKAI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SINKAI/Z2_SINKAI.o"
    number 2
endseg

beginseg
    name "Z2_SINKAI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SINKAI/Z2_SINKAI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_YOUSEI_IZUMI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YOUSEI_IZUMI/Z2_YOUSEI_IZUMI.o"
    number 2
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YOUSEI_IZUMI/Z2_YOUSEI_IZUMI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YOUSEI_IZUMI/Z2_YOUSEI_IZUMI_room_01.o"
    number 3
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YOUSEI_IZUMI/Z2_YOUSEI_IZUMI_room_02.o"
    number 3
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YOUSEI_IZUMI/Z2_YOUSEI_IZUMI_room_03.o"
    number 3
endseg

beginseg
    name "Z2_YOUSEI_IZUMI_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YOUSEI_IZUMI/Z2_YOUSEI_IZUMI_room_04.o"
    number 3
endseg

beginseg
    name "Z2_KINSTA1"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINSTA1/Z2_KINSTA1.o"
    number 2
endseg

beginseg
    name "Z2_KINSTA1_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINSTA1/Z2_KINSTA1_room_00.o"
    number 3
endseg

beginseg
    name "Z2_KINSTA1_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINSTA1/Z2_KINSTA1_room_01.o"
    number 3
endseg

beginseg
    name "Z2_KINSTA1_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINSTA1/Z2_KINSTA1_room_02.o"
    number 3
endseg

beginseg
    name "Z2_KINSTA1_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINSTA1/Z2_KINSTA1_room_03.o"
    number 3
endseg

beginseg
    name "Z2_KINSTA1_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINSTA1/Z2_KINSTA1_room_04.o"
    number 3
endseg

beginseg
    name "Z2_KINSTA1_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINSTA1/Z2_KINSTA1_room_05.o"
    number 3
endseg

beginseg
    name "Z2_KINDAN2"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINDAN2/Z2_KINDAN2.o"
    number 2
endseg

beginseg
    name "Z2_KINDAN2_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINDAN2/Z2_KINDAN2_room_00.o"
    number 3
endseg

beginseg
    name "Z2_KINDAN2_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINDAN2/Z2_KINDAN2_room_01.o"
    number 3
endseg

beginseg
    name "Z2_KINDAN2_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINDAN2/Z2_KINDAN2_room_02.o"
    number 3
endseg

beginseg
    name "Z2_KINDAN2_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINDAN2/Z2_KINDAN2_room_03.o"
    number 3
endseg

beginseg
    name "Z2_KINDAN2_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINDAN2/Z2_KINDAN2_room_04.o"
    number 3
endseg

beginseg
    name "Z2_KINDAN2_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KINDAN2/Z2_KINDAN2_room_05.o"
    number 3
endseg

beginseg
    name "Z2_TENMON_DAI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TENMON_DAI/Z2_TENMON_DAI.o"
    number 2
endseg

beginseg
    name "Z2_TENMON_DAI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TENMON_DAI/Z2_TENMON_DAI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_TENMON_DAI_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TENMON_DAI/Z2_TENMON_DAI_room_01.o"
    number 3
endseg

beginseg
    name "Z2_LAST_DEKU"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_DEKU/Z2_LAST_DEKU.o"
    number 2
endseg

beginseg
    name "Z2_LAST_DEKU_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_DEKU/Z2_LAST_DEKU_room_00.o"
    number 3
endseg

beginseg
    name "Z2_LAST_DEKU_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_DEKU/Z2_LAST_DEKU_room_01.o"
    number 3
endseg

beginseg
    name "Z2_22DEKUCITY"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_22DEKUCITY/Z2_22DEKUCITY.o"
    number 2
endseg

beginseg
    name "Z2_22DEKUCITY_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_22DEKUCITY/Z2_22DEKUCITY_room_00.o"
    number 3
endseg

beginseg
    name "Z2_22DEKUCITY_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_22DEKUCITY/Z2_22DEKUCITY_room_01.o"
    number 3
endseg

beginseg
    name "Z2_22DEKUCITY_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_22DEKUCITY/Z2_22DEKUCITY_room_02.o"
    number 3
endseg

beginseg
    name "Z2_KAJIYA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KAJIYA/Z2_KAJIYA.o"
    number 2
endseg

beginseg
    name "Z2_KAJIYA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KAJIYA/Z2_KAJIYA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_00KEIKOKU"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_00KEIKOKU/Z2_00KEIKOKU.o"
    number 2
endseg

beginseg
    name "Z2_00KEIKOKU_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_00KEIKOKU/Z2_00KEIKOKU_room_00.o"
    number 3
endseg

beginseg
    name "Z2_POSTHOUSE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_POSTHOUSE/Z2_POSTHOUSE.o"
    number 2
endseg

beginseg
    name "Z2_POSTHOUSE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_POSTHOUSE/Z2_POSTHOUSE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_LABO"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LABO/Z2_LABO.o"
    number 2
endseg

beginseg
    name "Z2_LABO_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LABO/Z2_LABO_room_00.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI2TEST"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI2TEST/Z2_DANPEI2TEST.o"
    number 2
endseg

beginseg
    name "Z2_DANPEI2TEST_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI2TEST/Z2_DANPEI2TEST_room_00.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI2TEST_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI2TEST/Z2_DANPEI2TEST_room_01.o"
    number 3
endseg

beginseg
    name "Z2_16GORON_HOUSE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_16GORON_HOUSE/Z2_16GORON_HOUSE.o"
    number 2
endseg

beginseg
    name "Z2_16GORON_HOUSE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_16GORON_HOUSE/Z2_16GORON_HOUSE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_16GORON_HOUSE_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_16GORON_HOUSE/Z2_16GORON_HOUSE_room_01.o"
    number 3
endseg

beginseg
    name "Z2_33ZORACITY"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_33ZORACITY/Z2_33ZORACITY.o"
    number 2
endseg

beginseg
    name "Z2_33ZORACITY_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_33ZORACITY/Z2_33ZORACITY_room_00.o"
    number 3
endseg

beginseg
    name "Z2_8ITEMSHOP"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_8ITEMSHOP/Z2_8ITEMSHOP.o"
    number 2
endseg

beginseg
    name "Z2_8ITEMSHOP_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_8ITEMSHOP/Z2_8ITEMSHOP_room_00.o"
    number 3
endseg

beginseg
    name "Z2_F01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F01/Z2_F01.o"
    number 2
endseg

beginseg
    name "Z2_F01_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F01/Z2_F01_room_00.o"
    number 3
endseg

beginseg
    name "Z2_INISIE_BS"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_BS/Z2_INISIE_BS.o"
    number 2
endseg

beginseg
    name "Z2_INISIE_BS_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INISIE_BS/Z2_INISIE_BS_room_00.o"
    number 3
endseg

beginseg
    name "Z2_30GYOSON"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_30GYOSON/Z2_30GYOSON.o"
    number 2
endseg

beginseg
    name "Z2_30GYOSON_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_30GYOSON/Z2_30GYOSON_room_00.o"
    number 3
endseg

beginseg
    name "Z2_31MISAKI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_31MISAKI/Z2_31MISAKI.o"
    number 2
endseg

beginseg
    name "Z2_31MISAKI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_31MISAKI/Z2_31MISAKI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_TAKARAKUJI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TAKARAKUJI/Z2_TAKARAKUJI.o"
    number 2
endseg

beginseg
    name "Z2_TAKARAKUJI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TAKARAKUJI/Z2_TAKARAKUJI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_TORIDE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TORIDE/Z2_TORIDE.o"
    number 2
endseg

beginseg
    name "Z2_TORIDE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TORIDE/Z2_TORIDE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_FISHERMAN"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_FISHERMAN/Z2_FISHERMAN.o"
    number 2
endseg

beginseg
    name "Z2_FISHERMAN_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_FISHERMAN/Z2_FISHERMAN_room_00.o"
    number 3
endseg

beginseg
    name "Z2_GORONSHOP"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_GORONSHOP/Z2_GORONSHOP.o"
    number 2
endseg

beginseg
    name "Z2_GORONSHOP_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_GORONSHOP/Z2_GORONSHOP_room_00.o"
    number 3
endseg

beginseg
    name "Z2_DEKU_KING"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DEKU_KING/Z2_DEKU_KING.o"
    number 2
endseg

beginseg
    name "Z2_DEKU_KING_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DEKU_KING/Z2_DEKU_KING_room_00.o"
    number 3
endseg

beginseg
    name "Z2_LAST_GORON"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_GORON/Z2_LAST_GORON.o"
    number 2
endseg

beginseg
    name "Z2_LAST_GORON_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_GORON/Z2_LAST_GORON_room_00.o"
    number 3
endseg

beginseg
    name "Z2_LAST_GORON_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_GORON/Z2_LAST_GORON_room_01.o"
    number 3
endseg

beginseg
    name "Z2_24KEMONOMITI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_24KEMONOMITI/Z2_24KEMONOMITI.o"
    number 2
endseg

beginseg
    name "Z2_24KEMONOMITI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_24KEMONOMITI/Z2_24KEMONOMITI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_F01_B"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F01_B/Z2_F01_B.o"
    number 2
endseg

beginseg
    name "Z2_F01_B_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F01_B/Z2_F01_B_room_00.o"
    number 3
endseg

beginseg
    name "Z2_F01C"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F01C/Z2_F01C.o"
    number 2
endseg

beginseg
    name "Z2_F01C_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F01C/Z2_F01C_room_00.o"
    number 3
endseg

beginseg
    name "Z2_BOTI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BOTI/Z2_BOTI.o"
    number 2
endseg

beginseg
    name "Z2_BOTI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BOTI/Z2_BOTI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_BOTI_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BOTI/Z2_BOTI_room_01.o"
    number 3
endseg

beginseg
    name "Z2_HAKUGIN_BS"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN_BS/Z2_HAKUGIN_BS.o"
    number 2
endseg

beginseg
    name "Z2_HAKUGIN_BS_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_HAKUGIN_BS/Z2_HAKUGIN_BS_room_00.o"
    number 3
endseg

beginseg
    name "Z2_20SICHITAI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_20SICHITAI/Z2_20SICHITAI.o"
    number 2
endseg

beginseg
    name "Z2_20SICHITAI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_20SICHITAI/Z2_20SICHITAI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_20SICHITAI_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_20SICHITAI/Z2_20SICHITAI_room_01.o"
    number 3
endseg

beginseg
    name "Z2_20SICHITAI_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_20SICHITAI/Z2_20SICHITAI_room_02.o"
    number 3
endseg

beginseg
    name "Z2_21MITURINMAE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_21MITURINMAE/Z2_21MITURINMAE.o"
    number 2
endseg

beginseg
    name "Z2_21MITURINMAE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_21MITURINMAE/Z2_21MITURINMAE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_LAST_ZORA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_ZORA/Z2_LAST_ZORA.o"
    number 2
endseg

beginseg
    name "Z2_LAST_ZORA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_ZORA/Z2_LAST_ZORA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_11GORONNOSATO2"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_11GORONNOSATO2/Z2_11GORONNOSATO2.o"
    number 2
endseg

beginseg
    name "Z2_11GORONNOSATO2_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_11GORONNOSATO2/Z2_11GORONNOSATO2_room_00.o"
    number 3
endseg

beginseg
    name "Z2_11GORONNOSATO2_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_11GORONNOSATO2/Z2_11GORONNOSATO2_room_01.o"
    number 3
endseg

beginseg
    name "Z2_SEA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA.o"
    number 2
endseg

beginseg
    name "Z2_SEA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_01.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_02.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_03.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_04.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_05.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_06.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_07.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_08.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_09"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_09.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_10"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_10.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_11"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_11.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_12"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_12.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_13"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_13.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_14"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_14.o"
    number 3
endseg

beginseg
    name "Z2_SEA_room_15"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA/Z2_SEA_room_15.o"
    number 3
endseg

beginseg
    name "Z2_35TAKI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_35TAKI/Z2_35TAKI.o"
    number 2
endseg

beginseg
    name "Z2_35TAKI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_35TAKI/Z2_35TAKI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD.o"
    number 2
endseg

beginseg
    name "Z2_REDEAD_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_00.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_01.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_02.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_03.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_04.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_05.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_06.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_07.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_08.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_09"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_09.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_10"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_10.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_11"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_11.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_12"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_12.o"
    number 3
endseg

beginseg
    name "Z2_REDEAD_room_13"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_REDEAD/Z2_REDEAD_room_13.o"
    number 3
endseg

beginseg
    name "Z2_BANDROOM"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BANDROOM/Z2_BANDROOM.o"
    number 2
endseg

beginseg
    name "Z2_BANDROOM_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BANDROOM/Z2_BANDROOM_room_00.o"
    number 3
endseg

beginseg
    name "Z2_BANDROOM_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BANDROOM/Z2_BANDROOM_room_01.o"
    number 3
endseg

beginseg
    name "Z2_BANDROOM_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BANDROOM/Z2_BANDROOM_room_02.o"
    number 3
endseg

beginseg
    name "Z2_BANDROOM_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BANDROOM/Z2_BANDROOM_room_03.o"
    number 3
endseg

beginseg
    name "Z2_BANDROOM_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BANDROOM/Z2_BANDROOM_room_04.o"
    number 3
endseg

beginseg
    name "Z2_11GORONNOSATO"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_11GORONNOSATO/Z2_11GORONNOSATO.o"
    number 2
endseg

beginseg
    name "Z2_11GORONNOSATO_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_11GORONNOSATO/Z2_11GORONNOSATO_room_00.o"
    number 3
endseg

beginseg
    name "Z2_11GORONNOSATO_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_11GORONNOSATO/Z2_11GORONNOSATO_room_01.o"
    number 3
endseg

beginseg
    name "Z2_GORON_HAKA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_GORON_HAKA/Z2_GORON_HAKA.o"
    number 2
endseg

beginseg
    name "Z2_GORON_HAKA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_GORON_HAKA/Z2_GORON_HAKA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_SECOM"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SECOM/Z2_SECOM.o"
    number 2
endseg

beginseg
    name "Z2_SECOM_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SECOM/Z2_SECOM_room_00.o"
    number 3
endseg

beginseg
    name "Z2_SECOM_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SECOM/Z2_SECOM_room_01.o"
    number 3
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_10YUKIYAMANOMURA/Z2_10YUKIYAMANOMURA.o"
    number 2
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_10YUKIYAMANOMURA/Z2_10YUKIYAMANOMURA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_TOUGITES"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TOUGITES/Z2_TOUGITES.o"
    number 2
endseg

beginseg
    name "Z2_TOUGITES_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TOUGITES/Z2_TOUGITES_room_00.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI.o"
    number 2
endseg

beginseg
    name "Z2_DANPEI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI_room_01.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI_room_02.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI_room_03.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI_room_04.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI_room_05.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI_room_06.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI_room_07.o"
    number 3
endseg

beginseg
    name "Z2_DANPEI_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DANPEI/Z2_DANPEI_room_08.o"
    number 3
endseg

beginseg
    name "Z2_IKANAMAE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKANAMAE/Z2_IKANAMAE.o"
    number 2
endseg

beginseg
    name "Z2_IKANAMAE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKANAMAE/Z2_IKANAMAE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_DOUJOU"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DOUJOU/Z2_DOUJOU.o"
    number 2
endseg

beginseg
    name "Z2_DOUJOU_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_DOUJOU/Z2_DOUJOU_room_00.o"
    number 3
endseg

beginseg
    name "Z2_MUSICHOUSE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MUSICHOUSE/Z2_MUSICHOUSE.o"
    number 2
endseg

beginseg
    name "Z2_MUSICHOUSE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MUSICHOUSE/Z2_MUSICHOUSE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_IKNINSIDE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKNINSIDE/Z2_IKNINSIDE.o"
    number 2
endseg

beginseg
    name "Z2_IKNINSIDE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKNINSIDE/Z2_IKNINSIDE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_IKNINSIDE_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_IKNINSIDE/Z2_IKNINSIDE_room_01.o"
    number 3
endseg

beginseg
    name "Z2_MAP_SHOP"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MAP_SHOP/Z2_MAP_SHOP.o"
    number 2
endseg

beginseg
    name "Z2_MAP_SHOP_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_MAP_SHOP/Z2_MAP_SHOP_room_00.o"
    number 3
endseg

beginseg
    name "Z2_F40"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F40/Z2_F40.o"
    number 2
endseg

beginseg
    name "Z2_F40_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F40/Z2_F40_room_00.o"
    number 3
endseg

beginseg
    name "Z2_F41"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F41/Z2_F41.o"
    number 2
endseg

beginseg
    name "Z2_F41_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_F41/Z2_F41_room_00.o"
    number 3
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA2"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_10YUKIYAMANOMURA2/Z2_10YUKIYAMANOMURA2.o"
    number 2
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA2_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_10YUKIYAMANOMURA2/Z2_10YUKIYAMANOMURA2_room_00.o"
    number 3
endseg

beginseg
    name "Z2_10YUKIYAMANOMURA2_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_10YUKIYAMANOMURA2/Z2_10YUKIYAMANOMURA2_room_01.o"
    number 3
endseg

beginseg
    name "Z2_14YUKIDAMANOMITI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_14YUKIDAMANOMITI/Z2_14YUKIDAMANOMITI.o"
    number 2
endseg

beginseg
    name "Z2_14YUKIDAMANOMITI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_14YUKIDAMANOMITI/Z2_14YUKIDAMANOMITI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_12HAKUGINMAE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_12HAKUGINMAE/Z2_12HAKUGINMAE.o"
    number 2
endseg

beginseg
    name "Z2_12HAKUGINMAE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_12HAKUGINMAE/Z2_12HAKUGINMAE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_17SETUGEN"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_17SETUGEN/Z2_17SETUGEN.o"
    number 2
endseg

beginseg
    name "Z2_17SETUGEN_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_17SETUGEN/Z2_17SETUGEN_room_00.o"
    number 3
endseg

beginseg
    name "Z2_17SETUGEN2"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_17SETUGEN2/Z2_17SETUGEN2.o"
    number 2
endseg

beginseg
    name "Z2_17SETUGEN2_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_17SETUGEN2/Z2_17SETUGEN2_room_00.o"
    number 3
endseg

beginseg
    name "Z2_SEA_BS"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA_BS/Z2_SEA_BS.o"
    number 2
endseg

beginseg
    name "Z2_SEA_BS_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SEA_BS/Z2_SEA_BS_room_00.o"
    number 3
endseg

beginseg
    name "Z2_RANDOM"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_RANDOM/Z2_RANDOM.o"
    number 2
endseg

beginseg
    name "Z2_RANDOM_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_RANDOM/Z2_RANDOM_room_00.o"
    number 3
endseg

beginseg
    name "Z2_RANDOM_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_RANDOM/Z2_RANDOM_room_01.o"
    number 3
endseg

beginseg
    name "Z2_RANDOM_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_RANDOM/Z2_RANDOM_room_02.o"
    number 3
endseg

beginseg
    name "Z2_RANDOM_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_RANDOM/Z2_RANDOM_room_03.o"
    number 3
endseg

beginseg
    name "Z2_RANDOM_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_RANDOM/Z2_RANDOM_room_04.o"
    number 3
endseg

beginseg
    name "Z2_RANDOM_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_RANDOM/Z2_RANDOM_room_05.o"
    number 3
endseg

beginseg
    name "Z2_YADOYA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YADOYA/Z2_YADOYA.o"
    number 2
endseg

beginseg
    name "Z2_YADOYA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YADOYA/Z2_YADOYA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_YADOYA_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YADOYA/Z2_YADOYA_room_01.o"
    number 3
endseg

beginseg
    name "Z2_YADOYA_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YADOYA/Z2_YADOYA_room_02.o"
    number 3
endseg

beginseg
    name "Z2_YADOYA_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YADOYA/Z2_YADOYA_room_03.o"
    number 3
endseg

beginseg
    name "Z2_YADOYA_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_YADOYA/Z2_YADOYA_room_04.o"
    number 3
endseg

beginseg
    name "Z2_KONPEKI_ENT"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KONPEKI_ENT/Z2_KONPEKI_ENT.o"
    number 2
endseg

beginseg
    name "Z2_KONPEKI_ENT_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KONPEKI_ENT/Z2_KONPEKI_ENT_room_00.o"
    number 3
endseg

beginseg
    name "Z2_INSIDETOWER"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INSIDETOWER/Z2_INSIDETOWER.o"
    number 2
endseg

beginseg
    name "Z2_INSIDETOWER_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INSIDETOWER/Z2_INSIDETOWER_room_00.o"
    number 3
endseg

beginseg
    name "Z2_INSIDETOWER_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_INSIDETOWER/Z2_INSIDETOWER_room_01.o"
    number 3
endseg

beginseg
    name "Z2_26SARUNOMORI"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI.o"
    number 2
endseg

beginseg
    name "Z2_26SARUNOMORI_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI_room_00.o"
    number 3
endseg

beginseg
    name "Z2_26SARUNOMORI_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI_room_01.o"
    number 3
endseg

beginseg
    name "Z2_26SARUNOMORI_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI_room_02.o"
    number 3
endseg

beginseg
    name "Z2_26SARUNOMORI_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI_room_03.o"
    number 3
endseg

beginseg
    name "Z2_26SARUNOMORI_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI_room_04.o"
    number 3
endseg

beginseg
    name "Z2_26SARUNOMORI_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI_room_05.o"
    number 3
endseg

beginseg
    name "Z2_26SARUNOMORI_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI_room_06.o"
    number 3
endseg

beginseg
    name "Z2_26SARUNOMORI_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI_room_07.o"
    number 3
endseg

beginseg
    name "Z2_26SARUNOMORI_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_26SARUNOMORI/Z2_26SARUNOMORI_room_08.o"
    number 3
endseg

beginseg
    name "Z2_LOST_WOODS"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LOST_WOODS/Z2_LOST_WOODS.o"
    number 2
endseg

beginseg
    name "Z2_LOST_WOODS_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LOST_WOODS/Z2_LOST_WOODS_room_00.o"
    number 3
endseg

beginseg
    name "Z2_LOST_WOODS_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LOST_WOODS/Z2_LOST_WOODS_room_01.o"
    number 3
endseg

beginseg
    name "Z2_LOST_WOODS_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LOST_WOODS/Z2_LOST_WOODS_room_02.o"
    number 3
endseg

beginseg
    name "Z2_LAST_LINK"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_LINK/Z2_LAST_LINK.o"
    number 2
endseg

beginseg
    name "Z2_LAST_LINK_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_LINK/Z2_LAST_LINK_room_00.o"
    number 3
endseg

beginseg
    name "Z2_LAST_LINK_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_LINK/Z2_LAST_LINK_room_01.o"
    number 3
endseg

beginseg
    name "Z2_LAST_LINK_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_LINK/Z2_LAST_LINK_room_02.o"
    number 3
endseg

beginseg
    name "Z2_LAST_LINK_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_LINK/Z2_LAST_LINK_room_03.o"
    number 3
endseg

beginseg
    name "Z2_LAST_LINK_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_LINK/Z2_LAST_LINK_room_04.o"
    number 3
endseg

beginseg
    name "Z2_LAST_LINK_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_LINK/Z2_LAST_LINK_room_05.o"
    number 3
endseg

beginseg
    name "Z2_LAST_LINK_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_LINK/Z2_LAST_LINK_room_06.o"
    number 3
endseg

beginseg
    name "Z2_LAST_LINK_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_LAST_LINK/Z2_LAST_LINK_room_07.o"
    number 3
endseg

beginseg
    name "Z2_SOUGEN"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SOUGEN/Z2_SOUGEN.o"
    number 2
endseg

beginseg
    name "Z2_SOUGEN_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_SOUGEN/Z2_SOUGEN_room_00.o"
    number 3
endseg

beginseg
    name "Z2_BOMYA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BOMYA/Z2_BOMYA.o"
    number 2
endseg

beginseg
    name "Z2_BOMYA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BOMYA/Z2_BOMYA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_KYOJINNOMA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KYOJINNOMA/Z2_KYOJINNOMA.o"
    number 2
endseg

beginseg
    name "Z2_KYOJINNOMA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KYOJINNOMA/Z2_KYOJINNOMA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_KOEPONARACE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KOEPONARACE/Z2_KOEPONARACE.o"
    number 2
endseg

beginseg
    name "Z2_KOEPONARACE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_KOEPONARACE/Z2_KOEPONARACE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_GORONRACE"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_GORONRACE/Z2_GORONRACE.o"
    number 2
endseg

beginseg
    name "Z2_GORONRACE_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_GORONRACE/Z2_GORONRACE_room_00.o"
    number 3
endseg

beginseg
    name "Z2_TOWN"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TOWN/Z2_TOWN.o"
    number 2
endseg

beginseg
    name "Z2_TOWN_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_TOWN/Z2_TOWN_room_00.o"
    number 3
endseg

beginseg
    name "Z2_ICHIBA"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_ICHIBA/Z2_ICHIBA.o"
    number 2
endseg

beginseg
    name "Z2_ICHIBA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_ICHIBA/Z2_ICHIBA_room_00.o"
    number 3
endseg

beginseg
    name "Z2_BACKTOWN"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BACKTOWN/Z2_BACKTOWN.o"
    number 2
endseg

beginseg
    name "Z2_BACKTOWN_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_BACKTOWN/Z2_BACKTOWN_room_00.o"
    number 3
endseg

beginseg
    name "Z2_CLOCKTOWER"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CLOCKTOWER/Z2_CLOCKTOWER.o"
    number 2
endseg

beginseg
    name "Z2_CLOCKTOWER_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_CLOCKTOWER/Z2_CLOCKTOWER_room_00.o"
    number 3
endseg

beginseg
    name "Z2_ALLEY"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_ALLEY/Z2_ALLEY.o"
    number 2
endseg

beginseg
    name "Z2_ALLEY_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/Z2_ALLEY/Z2_ALLEY_room_00.o"
    number 3
endseg

beginseg
    name "SPOT00"
    compress
    romalign 0x1000
    include "build/assets/scenes/SPOT00/SPOT00.o"
    number 2
endseg

beginseg
    name "SPOT00_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/SPOT00/SPOT00_room_00.o"
    number 3
endseg

beginseg
    name "KAKUSIANA"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA.o"
    number 2
endseg

beginseg
    name "KAKUSIANA_room_00"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_00.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_01"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_01.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_02"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_02.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_03"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_03.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_04"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_04.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_05"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_05.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_06"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_06.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_07"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_07.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_08"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_08.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_09"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_09.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_10"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_10.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_11"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_11.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_12"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_12.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_13"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_13.o"
    number 3
endseg

beginseg
    name "KAKUSIANA_room_14"
    compress
    romalign 0x1000
    include "build/assets/scenes/KAKUSIANA/KAKUSIANA_room_14.o"
    number 3
endseg

beginseg
    name "bump_texture_static"
    compress
    romalign 0x1000
    include "build/baserom/bump_texture_static.o"
endseg

beginseg
    name "anime_model_1_static"
    romalign 0x1000
    include "build/baserom/anime_model_1_static.o"
endseg

beginseg
    name "anime_model_2_static"
    romalign 0x1000
    include "build/baserom/anime_model_2_static.o"
endseg

beginseg
    name "anime_model_3_static"
    romalign 0x1000
    include "build/baserom/anime_model_3_static.o"
endseg

beginseg
    name "anime_model_4_static"
    romalign 0x1000
    include "build/baserom/anime_model_4_static.o"
endseg

beginseg
    name "anime_model_5_static"
    romalign 0x1000
    include "build/baserom/anime_model_5_static.o"
endseg

beginseg
    name "anime_model_6_static"
    romalign 0x1000
    include "build/baserom/anime_model_6_static.o"
endseg

beginseg
    name "anime_texture_1_static"
    romalign 0x1000
    include "build/baserom/anime_texture_1_static.o"
endseg

beginseg
    name "anime_texture_2_static"
    romalign 0x1000
    include "build/baserom/anime_texture_2_static.o"
endseg

beginseg
    name "anime_texture_3_static"
    romalign 0x1000
    include "build/baserom/anime_texture_3_static.o"
endseg

beginseg
    name "anime_texture_4_static"
    romalign 0x1000
    include "build/baserom/anime_texture_4_static.o"
endseg

beginseg
    name "anime_texture_5_static"
    romalign 0x1000
    include "build/baserom/anime_texture_5_static.o"
endseg

beginseg
    name "anime_texture_6_static"
    romalign 0x1000
    include "build/baserom/anime_texture_6_static.o"
endseg

beginseg
    name "softsprite_matrix_static"
    romalign 0x1000
    include "build/baserom/softsprite_matrix_static.o"
endseg
