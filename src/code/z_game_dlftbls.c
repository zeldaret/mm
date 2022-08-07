#include "global.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"
#include "overlays/gamestates/ovl_file_choose/z_file_choose.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
#include "overlays/gamestates/ovl_select/z_select.h"
#include "overlays/gamestates/ovl_title/z_title.h"

#define GAMESTATE_OVERLAY(name, init, destroy, size)                                                 \
    {                                                                                                \
        NULL, SEGMENT_ROM_START(ovl_##name), SEGMENT_ROM_END(ovl_##name), SEGMENT_START(ovl_##name), \
            SEGMENT_END(ovl_##name), 0, init, destroy, 0, 0, 0, size                                 \
    }
#define GAMESTATE_OVERLAY_INTERNAL(init, destroy, size) \
    { NULL, 0, 0, NULL, NULL, 0, init, destroy, 0, 0, 0, size }

GameStateOverlay gGameStateOverlayTable[] = {
    GAMESTATE_OVERLAY_INTERNAL(TitleSetup_Init, TitleSetup_Destroy, sizeof(GameState)),
    GAMESTATE_OVERLAY(select, MapSelect_Init, MapSelect_Destroy, sizeof(MapSelectState)),
    GAMESTATE_OVERLAY(title, Title_Init, Title_Destroy, sizeof(TitleContext)),
    GAMESTATE_OVERLAY_INTERNAL(Play_Init, Play_Fini, sizeof(PlayState)),
    GAMESTATE_OVERLAY(opening, Opening_Init, Opening_Destroy, sizeof(OpeningContext)),
    GAMESTATE_OVERLAY(file_choose, FileChoose_Init, FileChoose_Destroy, sizeof(FileChooseContext)),
    GAMESTATE_OVERLAY(daytelop, Daytelop_Init, Daytelop_Destroy, sizeof(DaytelopContext)),
};

s32 graphNumGameStates = ARRAY_COUNT(gGameStateOverlayTable);
