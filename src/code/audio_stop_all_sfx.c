#include "global.h"

const u8 sSfxBankIds[] = {
    BANK_PLAYER, BANK_ITEM, BANK_ENV, BANK_ENEMY, BANK_SYSTEM, BANK_OCARINA, BANK_VOICE,
};

void AudioMgr_StopAllSfxExceptSystem(void) {
    volatile const u8* bankIdPtr;

    for (bankIdPtr = sSfxBankIds; bankIdPtr < (sSfxBankIds + ARRAY_COUNT(sSfxBankIds)); bankIdPtr++) {
        if (*bankIdPtr != BANK_SYSTEM) {
            AudioSfx_StopByBank(*bankIdPtr);
        }
    }
}
