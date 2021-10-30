#include "global.h"

SaveContext gSaveContext;

void SaveContext_Init(void) {
    bzero(&gSaveContext, sizeof(gSaveContext));
    gSaveContext.playerForm = 0;
    gSaveContext.seqIndex = 0xFF;
    gSaveContext.nightSeqIndex = 0xFF;
    gSaveContext.unk_3F46 = 0;
    gSaveContext.nextCutsceneIndex = 0xFFEF;
    gSaveContext.cutsceneTrigger = 0;
    gSaveContext.unk_3F4D = 0;
    gSaveContext.nextDayTime = 0xFFFF;
    gSaveContext.environmentTime = 0;
    gSaveContext.dogIsLost = true;
    gSaveContext.nextTransition = 0xFF;
    gSaveContext.unk_3F26 = 50;
    gSaveContext.language = 1;
    gSaveContext.audioSetting = 0;
    gSaveContext.zTargetSetting = 0;
}
