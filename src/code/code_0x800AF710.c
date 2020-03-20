#include <ultra64.h>
#include <global.h>

EffInfo sEffInfoTable[] = {
    {
        sizeof(EffSparkParams),
        (eff_init_func)EffectSpark_Init,
        (eff_destroy_func)EffectSpark_Destroy,
        (eff_update_func)EffectSpark_Update,
        (eff_draw_func)EffectSpark_Draw,
    },
    {
        sizeof(EffBlureParams),
        (eff_init_func)EffectBlure_Init1,
        (eff_destroy_func)EffectBlure_Destroy,
        (eff_update_func)EffectBlure_Update,
        (eff_draw_func)EffectBlure_Draw,
    },
    {
        sizeof(EffBlureParams),
        (eff_init_func)EffectBlure_Init2,
        (eff_destroy_func)EffectBlure_Destroy,
        (eff_update_func)EffectBlure_Update,
        (eff_draw_func)EffectBlure_Draw,
    },
    {
        sizeof(EffShieldParticleParams),
        (eff_init_func)EffectShieldParticle_Init,
        (eff_destroy_func)EffectShieldParticle_Destroy,
        (eff_update_func)EffectShieldParticle_Update,
        (eff_draw_func)EffectShieldParticle_Draw,
    },
    {
        sizeof(EffTireMarkParams),
        (eff_init_func)EffectTireMark_Init,
        (eff_destroy_func)EffectTireMark_Destroy,
        (eff_update_func)EffectTireMark_Update,
        (eff_draw_func)EffectTireMark_Draw,
    },
};

GlobalContext* Effect_GetContext(void) {
    return sEffTable.ctxt;
}

void* Effect_GetParams(s32 index) {
    if (index == 46) {
        return NULL;
    }

    if (index < 3) {
        if (sEffTable.sparks[index].base.active == 1) {
            return &sEffTable.sparks[index].params;
        } else {
            return NULL;
        }
    }

    index -= 3;
    if (index < 25) {
        if (sEffTable.blures[index].base.active == 1) {
            return &sEffTable.blures[index].params;
        } else {
            return NULL;
        }
    }

    index -= 25;
    if (index < 3) {
        if (sEffTable.shieldParticles[index].base.active == 1) {
            return &sEffTable.shieldParticles[index].params;
        } else {
            return NULL;
        }
    }

    index -= 3;
    if (index < 15) {
        if (sEffTable.tireMarks[index].base.active == 1) {
            return &sEffTable.tireMarks[index].params;
        } else {
            return NULL;
        }
    }

    return NULL;
}

void Effect_InitCommon(EffCommon* common) {
    common->active = 0;
    common->unk1 = 0;
    common->unk2 = 0;
}

void Effect_Init(GlobalContext* ctxt) {
    s32 i;

    for (i = 0; i < 3; i++) {
        Effect_InitCommon(&sEffTable.sparks[i].base);
    }

    for (i = 0; i < 25; i++) {
        Effect_InitCommon(&sEffTable.blures[i].base);
    }

    //! @bug This is probably supposed to loop over shieldParticles, not blures again
    for (i = 0; i < 3; i++) {
        Effect_InitCommon(&sEffTable.blures[i].base);
    }

    for (i = 0; i < 15; i++) {
        Effect_InitCommon(&sEffTable.tireMarks[i].base);
    }

    sEffTable.ctxt = ctxt;
}

void Effect_Add(GlobalContext* ctxt, s32* index, s32 type, u8 param_4, u8 param_5, void* initParams) {
    u32 slotFound;
    s32 i;
    void* params;
    EffCommon* common;

    params = NULL;
    *index = 46;
    common = NULL;

    if (func_8016A01C(ctxt) != 1) {
        slotFound = 0;
        switch (type) {
        case 0:
            for (i = 0; i < 3; i++) {
                if (sEffTable.sparks[i].base.active == 0) {
                    slotFound = 1;
                    *index = i;
                    params = &sEffTable.sparks[i].params;
                    common = &sEffTable.sparks[i].base;
                    break;
                }
            }
            break;
        case 1:
        case 2:
            for (i = 0; i < 25; i++) {
                if (sEffTable.blures[i].base.active == 0) {
                    slotFound = 1;
                    *index = i + 3;
                    params = &sEffTable.blures[i].params;
                    common = &sEffTable.blures[i].base;
                    break;
                }
            }
            break;
        case 3:
            for (i = 0; i < 3; i++) {
                if (sEffTable.shieldParticles[i].base.active == 0) {
                    slotFound = 1;
                    *index = i + 28;
                    params = &sEffTable.shieldParticles[i].params;
                    common = &sEffTable.shieldParticles[i].base;
                    break;
                }
            }
            break;
        case 4:
            for (i = 0; i < 15; i++) {
                if (sEffTable.tireMarks[i].base.active == 0) {
                    slotFound = 1;
                    *index = i + 31;
                    params = &sEffTable.tireMarks[i].params;
                    common = &sEffTable.tireMarks[i].base;
                    break;
                }
            }
            break;
        }

        if (slotFound) {
            sEffInfoTable[type].init(params, initParams);
            common->unk2 = param_4;
            common->unk1 = param_5;
            common->active = 1;
        }
    }
}

#ifdef NON_MATCHING
// Contents of s2 and s3 swapped
void Effect_DrawAll(GraphicsContext* gCtxt) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (sEffTable.sparks[i].base.active) {
            sEffInfoTable[0].draw(&sEffTable.sparks[i].params, gCtxt);
        }
    }

    for (i = 0; i < 25; i++) {
        if (sEffTable.blures[i].base.active) {
            sEffInfoTable[1].draw(&sEffTable.blures[i].params, gCtxt);
        }
    }

    for (i = 0; i < 3; i++) {
        if (sEffTable.shieldParticles[i].base.active) {
            sEffInfoTable[3].draw(&sEffTable.shieldParticles[i].params, gCtxt);
        }
    }

    for (i = 0; i < 15; i++) {
        if (sEffTable.tireMarks[i].base.active) {
            sEffInfoTable[4].draw(&sEffTable.tireMarks[i].params, gCtxt);
        }
    }
}
#else
GLOBAL_ASM("./asm/non_matchings/code_0x800AF710/Effect_DrawAll.asm")
#endif

#ifdef NON_MATCHING
// 15 is being placed in s5 instead of at
void Effect_UpdateAll(GlobalContext* ctxt) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (sEffTable.sparks[i].base.active) {
            if (sEffInfoTable[0].update(&sEffTable.sparks[i].params) == 1) {
                Effect_Destroy(ctxt, i);
            }
        }
    }

    for (i = 0; i < 25; i++) {
        if (sEffTable.blures[i].base.active) {
            if (sEffInfoTable[1].update(&sEffTable.blures[i].params) == 1) {
                Effect_Destroy(ctxt, i + 3);
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if (sEffTable.shieldParticles[i].base.active) {
            if (sEffInfoTable[3].update(&sEffTable.shieldParticles[i].params) == 1) {
                Effect_Destroy(ctxt, i + 28);
            }
        }
    }

    for (i = 0; i < 15; i++) {
        if (sEffTable.tireMarks[i].base.active) {
            if (sEffInfoTable[4].update(&sEffTable.tireMarks[i].params) == 1) {
                Effect_Destroy(ctxt, i + 31);
            }
        }
    }
}
#else
GLOBAL_ASM("./asm/non_matchings/code_0x800AF710/Effect_UpdateAll.asm")
#endif

void Effect_Destroy(GlobalContext* ctxt, s32 index) {
    if (index == 46) {
        return;
    }

    if (index < 3) {
        sEffTable.sparks[index].base.active = 0 ;
        sEffInfoTable[0].destroy(&sEffTable.sparks[index].params);
        return;
    }

    index -= 3;
    if (index < 25) {
        sEffTable.blures[index].base.active = 0 ;
        sEffInfoTable[1].destroy(&sEffTable.blures[index].params);
        return;
    }

    index -= 25;
    if (index < 3) {
        sEffTable.shieldParticles[index].base.active = 0 ;
        sEffInfoTable[3].destroy(&sEffTable.shieldParticles[index].params);
        return;
    }

    index -= 3;
    if (index < 15) {
        sEffTable.tireMarks[index].base.active = 0 ;
        sEffInfoTable[4].destroy(&sEffTable.tireMarks[index].params);
        return;
    }
}

void Effect_DestroyAll(GlobalContext* ctxt) {
    s32 i;

    for (i = 0; i < 3; i++) {
        sEffTable.sparks[i].base.active = 0;
        sEffInfoTable[0].destroy(&sEffTable.sparks[i].params);
    }

    for (i = 0; i < 25; i++) {
        sEffTable.blures[i].base.active = 0;
        sEffInfoTable[1].destroy(&sEffTable.blures[i].params);
    }

    for (i = 0; i < 3; i++) {
        sEffTable.shieldParticles[i].base.active = 0;
        sEffInfoTable[3].destroy(&sEffTable.shieldParticles[i].params);
    }

    for (i = 0; i < 15; i++) {
        sEffTable.tireMarks[i].base.active = 0;
        sEffInfoTable[4].destroy(&sEffTable.tireMarks[i].params);
    }
}

