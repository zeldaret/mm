#include "global.h"

#define DEFINE_SFX(_0, importance, distParam, randParam, flags2, flags1) \
    { importance, flags2,                                                \
      ((((distParam) << SFX_PARAM_01_SHIFT) & SFX_PARAM_01_MASK) |       \
       (((randParam) << SFX_PARAM_67_SHIFT) & SFX_PARAM_67_MASK) | (flags1)) },

SfxParams sEnemyBankParams[] = {
#include "tables/sfx/3_enemybank_table.h"
};

SfxParams sPlayerBankParams[] = {
#include "tables/sfx/0_playerbank_table.h"
};

SfxParams sItemBankParams[] = {
#include "tables/sfx/1_itembank_table.h"
};

SfxParams sEnvBankParams[] = {
#include "tables/sfx/2_environmentbank_table.h"
};

SfxParams sSystemBankParams[] = {
#include "tables/sfx/4_systembank_table.h"
};

SfxParams sOcarinaBankParams[] = {
#include "tables/sfx/5_ocarinabank_table.h"
};

SfxParams sVoiceBankParams[] = {
#include "tables/sfx/6_voicebank_table.h"
};

#undef DEFINE_SFX

SfxParams* gSfxParams[7] = {
    sPlayerBankParams, sItemBankParams,    sEnvBankParams,   sEnemyBankParams,
    sSystemBankParams, sOcarinaBankParams, sVoiceBankParams,
};
