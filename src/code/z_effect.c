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
        sizeof(EffectBlure),
        (eff_init_func)EffectBlure_Init1,
        (eff_destroy_func)EffectBlure_Destroy,
        (eff_update_func)EffectBlure_Update,
        (eff_draw_func)EffectBlure_Draw,
    },
    {
        sizeof(EffectBlure),
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
    return sEffTable.globalCtx;
}

void* Effect_GetParams(s32 index) {
    if (index == TOTAL_EFFECT_COUNT) {
        return NULL;
    }

    if (index < SPARK_COUNT) {
        if (sEffTable.sparks[index].base.active == 1) {
            return &sEffTable.sparks[index].params;
        } else {
            return NULL;
        }
    }

    index -= SPARK_COUNT;
    if (index < BLURE_COUNT) {
        if (sEffTable.blures[index].base.active == 1) {
            return &sEffTable.blures[index].params;
        } else {
            return NULL;
        }
    }

    index -= BLURE_COUNT;
    if (index < SHIELD_PARTICLE_COUNT) {
        if (sEffTable.shieldParticles[index].base.active == 1) {
            return &sEffTable.shieldParticles[index].params;
        } else {
            return NULL;
        }
    }

    index -= SHIELD_PARTICLE_COUNT;
    if (index < TIRE_MARK_COUNT) {
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

void Effect_Init(GlobalContext* globalCtx) {
    s32 i;

    for (i = 0; i < SPARK_COUNT; i++) {
        Effect_InitCommon(&sEffTable.sparks[i].base);
    }

    for (i = 0; i < BLURE_COUNT; i++) {
        Effect_InitCommon(&sEffTable.blures[i].base);
    }

    //! @bug This is probably supposed to loop over shieldParticles, not blures again
    for (i = 0; i < SHIELD_PARTICLE_COUNT; i++) {
        Effect_InitCommon(&sEffTable.blures[i].base);
    }

    for (i = 0; i < TIRE_MARK_COUNT; i++) {
        Effect_InitCommon(&sEffTable.tireMarks[i].base);
    }

    sEffTable.globalCtx = globalCtx;
}

void Effect_Add(GlobalContext* globalCtx, s32* index, s32 type, u8 param_4, u8 param_5, void* initParams) {
    u32 slotFound;
    s32 i;
    void* params;
    EffCommon* common;

    params = NULL;
    *index = TOTAL_EFFECT_COUNT;
    common = NULL;

    if (FrameAdvance_IsEnabled(globalCtx) != true) {
        slotFound = 0;
        switch (type) {
            case 0:
                for (i = 0; i < SPARK_COUNT; i++) {
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
                for (i = 0; i < BLURE_COUNT; i++) {
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
                for (i = 0; i < SHIELD_PARTICLE_COUNT; i++) {
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
                for (i = 0; i < TIRE_MARK_COUNT; i++) {
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

void Effect_DrawAll(GraphicsContext* gfxCtx) {
    s32 i;

    for (i = 0; i < SPARK_COUNT; i++) {
        if (1) {} // necessary to match
        if (sEffTable.sparks[i].base.active) {
            sEffInfoTable[0].draw(&sEffTable.sparks[i].params, gfxCtx);
        }
    }

    for (i = 0; i < BLURE_COUNT; i++) {
        if (1) {
            if (gfxCtx) {}
        } // necessary to match
        if (sEffTable.blures[i].base.active) {
            sEffInfoTable[1].draw(&sEffTable.blures[i].params, gfxCtx);
        }
    }

    for (i = 0; i < SHIELD_PARTICLE_COUNT; i++) {
        if (1) {} // necessary to match
        if (sEffTable.shieldParticles[i].base.active) {
            sEffInfoTable[3].draw(&sEffTable.shieldParticles[i].params, gfxCtx);
        }
    }

    if (1) {} // necessary to match
    for (i = 0; i < TIRE_MARK_COUNT; i++) {
        if (sEffTable.tireMarks[i].base.active) {
            sEffInfoTable[4].draw(&sEffTable.tireMarks[i].params, gfxCtx);
        }
    }
}

void Effect_UpdateAll(GlobalContext* globalCtx) {
    s32 i;

    for (i = 0; i < SPARK_COUNT; i++) {
        if (1) {} // necessary to match
        if (sEffTable.sparks[i].base.active) {
            if (sEffInfoTable[0].update(&sEffTable.sparks[i].params) == 1) {
                Effect_Destroy(globalCtx, i);
            }
        }
    }

    for (i = 0; i < BLURE_COUNT; i++) {
        if (1) {} // necessary to match
        if (sEffTable.blures[i].base.active) {
            if (sEffInfoTable[1].update(&sEffTable.blures[i].params) == 1) {
                Effect_Destroy(globalCtx, i + 3);
            }
        }
    }

    for (i = 0; i < SHIELD_PARTICLE_COUNT; i++) {
        if (1) {} // necessary to match
        if (sEffTable.shieldParticles[i].base.active) {
            if (sEffInfoTable[3].update(&sEffTable.shieldParticles[i].params) == 1) {
                Effect_Destroy(globalCtx, i + 28);
            }
        }
    }

    for (i = 0; i < TIRE_MARK_COUNT; i++) {
        if (1) {} // necessary to match
        if (sEffTable.tireMarks[i].base.active) {
            if (sEffInfoTable[4].update(&sEffTable.tireMarks[i].params) == 1) {
                Effect_Destroy(globalCtx, i + 31);
            }
        }
    }
}

void Effect_Destroy(GlobalContext* globalCtx, s32 index) {
    if (index == TOTAL_EFFECT_COUNT) {
        return;
    }

    if (index < SPARK_COUNT) {
        sEffTable.sparks[index].base.active = 0;
        sEffInfoTable[0].destroy(&sEffTable.sparks[index].params);
        return;
    }

    index -= SPARK_COUNT;
    if (index < BLURE_COUNT) {
        sEffTable.blures[index].base.active = 0;
        sEffInfoTable[1].destroy(&sEffTable.blures[index].params);
        return;
    }

    index -= BLURE_COUNT;
    if (index < SHIELD_PARTICLE_COUNT) {
        sEffTable.shieldParticles[index].base.active = 0;
        sEffInfoTable[3].destroy(&sEffTable.shieldParticles[index].params);
        return;
    }

    index -= SHIELD_PARTICLE_COUNT;
    if (index < TIRE_MARK_COUNT) {
        sEffTable.tireMarks[index].base.active = 0;
        sEffInfoTable[4].destroy(&sEffTable.tireMarks[index].params);
        return;
    }
}

void Effect_DestroyAll(GlobalContext* globalCtx) {
    s32 i;

    for (i = 0; i < SPARK_COUNT; i++) {
        sEffTable.sparks[i].base.active = 0;
        sEffInfoTable[0].destroy(&sEffTable.sparks[i].params);
    }

    for (i = 0; i < BLURE_COUNT; i++) {
        sEffTable.blures[i].base.active = 0;
        sEffInfoTable[1].destroy(&sEffTable.blures[i].params);
    }

    for (i = 0; i < SHIELD_PARTICLE_COUNT; i++) {
        sEffTable.shieldParticles[i].base.active = 0;
        sEffInfoTable[3].destroy(&sEffTable.shieldParticles[i].params);
    }

    for (i = 0; i < TIRE_MARK_COUNT; i++) {
        sEffTable.tireMarks[i].base.active = 0;
        sEffInfoTable[4].destroy(&sEffTable.tireMarks[i].params);
    }
}
