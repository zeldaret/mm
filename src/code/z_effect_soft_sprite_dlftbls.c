#include "global.h"
#include "initvars.h"

#define EFFECT_SS_OVERLAY(name)                                                                \
    {                                                                                          \
        SEGMENT_ROM_START(ovl_##name), SEGMENT_ROM_END(ovl_##name), SEGMENT_START(ovl_##name), \
            SEGMENT_END(ovl_##name), NULL, &name##_InitVars, 1,                                \
    }

#define EFFECT_SS_OVERLAY_INTERNAL(name) \
    { 0, 0, NULL, NULL, NULL, &name##_InitVars, 1 }

#define EFFECT_SS_OVERLAY_UNSET \
    { 0 }

EffectSsOverlay gParticleOverlayTable[] = {
    EFFECT_SS_OVERLAY(Effect_Ss_Dust),
    EFFECT_SS_OVERLAY(Effect_Ss_Kirakira),
    EFFECT_SS_OVERLAY_UNSET,
    EFFECT_SS_OVERLAY(Effect_Ss_Bomb2),
    EFFECT_SS_OVERLAY(Effect_Ss_Blast),
    EFFECT_SS_OVERLAY(Effect_Ss_G_Spk),
    EFFECT_SS_OVERLAY(Effect_Ss_D_Fire),
    EFFECT_SS_OVERLAY(Effect_Ss_Bubble),
    EFFECT_SS_OVERLAY_UNSET,
    EFFECT_SS_OVERLAY(Effect_Ss_G_Ripple),
    EFFECT_SS_OVERLAY(Effect_Ss_G_Splash),
    EFFECT_SS_OVERLAY_UNSET,
    EFFECT_SS_OVERLAY(Effect_Ss_G_Fire),
    EFFECT_SS_OVERLAY(Effect_Ss_Lightning),
    EFFECT_SS_OVERLAY(Effect_Ss_Dt_Bubble),
    EFFECT_SS_OVERLAY(Effect_Ss_Hahen),
    EFFECT_SS_OVERLAY(Effect_Ss_Stick),
    EFFECT_SS_OVERLAY(Effect_Ss_Sibuki),
    EFFECT_SS_OVERLAY_UNSET,
    EFFECT_SS_OVERLAY_UNSET,
    EFFECT_SS_OVERLAY(Effect_Ss_Stone1),
    EFFECT_SS_OVERLAY(Effect_Ss_Hitmark),
    EFFECT_SS_OVERLAY(Effect_Ss_Fhg_Flash),
    EFFECT_SS_OVERLAY(Effect_Ss_K_Fire),
    EFFECT_SS_OVERLAY(Effect_Ss_Solder_Srch_Ball),
    EFFECT_SS_OVERLAY(Effect_Ss_Kakera),
    EFFECT_SS_OVERLAY(Effect_Ss_Ice_Piece),
    EFFECT_SS_OVERLAY(Effect_Ss_En_Ice),
    EFFECT_SS_OVERLAY(Effect_Ss_Fire_Tail),
    EFFECT_SS_OVERLAY(Effect_Ss_En_Fire),
    EFFECT_SS_OVERLAY(Effect_Ss_Extra),
    EFFECT_SS_OVERLAY_UNSET,
    EFFECT_SS_OVERLAY(Effect_Ss_Dead_Db),
    EFFECT_SS_OVERLAY(Effect_Ss_Dead_Dd),
    EFFECT_SS_OVERLAY(Effect_Ss_Dead_Ds),
    EFFECT_SS_OVERLAY_UNSET,
    EFFECT_SS_OVERLAY(Effect_Ss_Ice_Smoke),
    EFFECT_SS_OVERLAY(Effect_En_Ice_Block),
    EFFECT_SS_OVERLAY(Effect_Ss_Sbn),
};
