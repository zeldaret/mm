#include "global.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"
#include "overlays/gamestates/ovl_file_choose/z_file_choose.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
#include "overlays/gamestates/ovl_select/z_select.h"
#include "overlays/gamestates/ovl_title/z_title.h"
#include "z_title_setup.h"

#define GAMESTATE_OVERLAY(name, init, destroy, size)                                                 \
    {                                                                                                \
        NULL, SEGMENT_ROM_START(ovl_##name), SEGMENT_ROM_END(ovl_##name), SEGMENT_START(ovl_##name), \
            SEGMENT_END(ovl_##name), 0, init, destroy, 0, 0, 0, size                                 \
    }
#define GAMESTATE_OVERLAY_INTERNAL(init, destroy, size) \
    { NULL, 0, 0, NULL, NULL, 0, init, destroy, 0, 0, 0, size }

GameStateOverlay gGameStateOverlayTable[] = {
    GAMESTATE_OVERLAY_INTERNAL(Setup_Init, Setup_Destroy, sizeof(SetupState)),
    GAMESTATE_OVERLAY(select, MapSelect_Init, MapSelect_Destroy, sizeof(MapSelectState)),
    GAMESTATE_OVERLAY(title, ConsoleLogo_Init, ConsoleLogo_Destroy, sizeof(ConsoleLogoState)),
    GAMESTATE_OVERLAY_INTERNAL(Play_Init, Play_Destroy, sizeof(PlayState)),
    GAMESTATE_OVERLAY(opening, TitleSetup_Init, TitleSetup_Destroy, sizeof(TitleSetupState)),
    GAMESTATE_OVERLAY(file_choose, FileSelect_Init, FileSelect_Destroy, sizeof(FileSelectState)),
    GAMESTATE_OVERLAY(daytelop, DayTelop_Init, DayTelop_Destroy, sizeof(DayTelopState)),
};

s32 gGraphNumGameStates = ARRAY_COUNT(gGameStateOverlayTable);
