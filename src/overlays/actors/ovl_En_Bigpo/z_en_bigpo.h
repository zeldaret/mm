#ifndef Z_EN_BIGPO_H
#define Z_EN_BIGPO_H

#include "global.h"

struct EnBigpo;

typedef void (*EnBigPoActionFunc)(struct EnBigpo*, GlobalContext*);

typedef struct EnBigpoFireEffect {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ LightNode* light;
    /* 0x10 */ LightInfo info; // size 0xE
} EnBigpoFireEffect; // size = 0x20

#define ENBIGPO_LIMBCOUNT 10


// idleTimer gets reused:
// * after dampe reveals a fire, 8 minutes of frames before it goes away again
// * used by flames and regular bigpo to count frames during the appearance cutscene
// * when idle flying around, frames until next attack
// * when spinning in/out of reality, counts frames from start
// * in burning death, counts frames from death start
// * after scoop spawned, idle timer used to count down to actor disapear

typedef struct EnBigpo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[ENBIGPO_LIMBCOUNT];
    /* 0x1C4 */ Vec3s morphTable[ENBIGPO_LIMBCOUNT];
    /* 0x200 */ EnBigPoActionFunc actionFunc;
    /* 0x204 */ u8 unkBool204; // need to know what func_801A2E54 does to know what this is
    /* 0x206 */ s16 idleTimer; // frame counter
    /* 0x208 */ s16 unk208; // facing rotY?
    /* 0x20A */ s16 rotVelocity;
    /* 0x20C */ s16 unk20C; // is this counting the number of frames the player is ztargeting them?
    /* 0x20E */ s16 cutsceneSubCamId;
    /* 0x210 */ s16 switchFlags;
    /* 0x212 */ s16 hoverHeightCycleTimer; // sin wave up and down bobbing
    /* 0x214 */ f32 fireRadius; // distance from center during conjunction cutscene
    /* 0x218 */ f32 savedHeight; // actual height while flying moves as part of bobbing
    /* 0x21C */ f32 drawDmgEffAlpha;
    /* 0x220 */ f32 drawDmgEffScale;
    /* 0x224 */ Vec3f limbPos[9];
    /* 0x290 */ Color_RGBA8 mainColor;
    /* 0x294 */ Color_RGBA8 lanternColor;
    /* 0x298 */ UNK_TYPE1 pad298[0x14];
    /* 0x2AC */ ColliderCylinder collider;
    /* 0x2F8 */ MtxF drawMtxF;
    // the three fires that merge to become big po
    //   also the fires dampe digs up under his house
    /* 0x338 */ EnBigpoFireEffect fires[3];
} EnBigpo; // size = 0x398

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

#define GET_BIGPO_SWITCHFLAGS(thisx) ((u8)(thisx->params >> 0x8)) 

#endif // Z_EN_BIGPO_H
