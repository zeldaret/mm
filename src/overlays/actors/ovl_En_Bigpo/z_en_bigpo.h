#ifndef Z_EN_BIGPO_H
#define Z_EN_BIGPO_H

#include "global.h"

struct EnBigpo;

typedef void (*EnBigPoActionFunc)(struct EnBigpo*, GlobalContext*);

typedef struct EnBigpoFireParticle {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ LightNode* light;
    /* 0x10 */ LightInfo info; // size 0xE
} EnBigpoFireParticle; // size = 0x20

typedef struct EnBigpo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTbl[0xA];
    /* 0x1C4 */ Vec3s transitionDrawTbl[0xA];
    /* 0x200 */ EnBigPoActionFunc actionFunc;
    /* 0x204 */ u8 unk204;
    // idleTimer gets reused:
    // * when idle flying around, frames until next attack
    // * when spinning back into reality, counts frames from start
    // * in death one, counts frames from death start
    // * after scoop spawned, idle timer used to count down to actor disapear
    /* 0x206 */ s16 idleTimer; // idle frames beteween attacks
    /* 0x208 */ s16 unk208;
    /* 0x20A */ s16 rotVelocity;
    /* 0x20C */ s16 unk20C; // incremented 
    /* 0x20E */ s16 unk20E;
    /* 0x210 */ s16 switchFlags;
    /* 0x212 */ s16 unk212; // seems to affect pos.y of idle flying poh
    /* 0x214 */ f32 unk214; // speed?
    /* 0x218 */ f32 unk218; // re-appear height
    /* 0x21C */ f32 unk21C; // reduced alpha?
    /* 0x220 */ f32 unk220; // created from unk21C
    /* 0x224 */ Vec3f limbPos[0x9];
    /* 0x290 */ Color_RGBA8 mainColor;
    /* 0x294 */ Color_RGBA8 unk294; // only used by one draw function
    /* 0x298 */ u8 pad298[0x14];
    /* 0x2AC */ ColliderCylinder collider;
    /* 0x2F8 */ MtxF drawMtxF;
    /* 0x338 */ EnBigpoFireParticle fires[3];
} EnBigpo; // size = 0x398

// todo make params macro for switch flags

// well ver is regular, dampe basement ver is summoned
// on spawn, 3/possible fires are turned into chosenfire
enum EnBigpoType {
  /* 0 */ ENBIGPO_REGULAR,
  /* 1 */ ENBIGPO_SUMMONED,
  /* 2 */ ENBIGPO_POSSIBLEFIRE,
  /* 3 */ ENBIGPO_CHOSENFIRE,
  /* 4 */ ENBIGPO_REVEALEDFIRE,
  /* 5 */ ENBIGPO_UNK5,
};

#define FIRSTENEMY ((Actor*)globalCtx->actorCtx.actorList[ACTORCAT_ENEMY].first)

#endif // Z_EN_BIGPO_H
