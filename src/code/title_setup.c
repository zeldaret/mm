#include "z_title_setup.h"
#include "overlays/gamestates/ovl_title/z_title.h"

void Setup_SetRegs(void) {
    XREG(2) = 0;
    XREG(10) = 0x1A;
    XREG(11) = 0x14;
    XREG(12) = 0xE;
    XREG(13) = 0;
    XREG(31) = 0;
    R_MAGIC_CONSUME_TIMER_GIANTS_MASK = 80;
    XREG(43) = 0xFC54;

    XREG(44) = 0xD7;
    XREG(45) = 0xDA;
    XREG(68) = 0x61;
    XREG(69) = 0x93;
    XREG(70) = 0x28;
    XREG(73) = 0x1E;
    XREG(74) = 0x42;
    XREG(75) = 0x1E;
    XREG(76) = 0x1C;
    XREG(77) = 0x3C;
    XREG(78) = 0x2F;
    XREG(79) = 0x62;
    R_PAUSE_OWLWARP_ALPHA = 0;
    XREG(88) = 0x56;
    XREG(89) = 0x258;
    XREG(90) = 0x1C2;
    R_STORY_FILL_SCREEN_ALPHA = 0;
    R_REVERSE_FLOOR_INDEX = 0;
    R_MINIMAP_DISABLED = false;

    YREG(32) = 0x50;
    YREG(33) = 0x3C;
    YREG(34) = 0xDC;
    YREG(35) = 0x3C;
    YREG(36) = 0x50;
    YREG(37) = 0xA0;
    YREG(38) = 0xDC;
    YREG(39) = 0xA0;
    YREG(40) = 0x8E;
    YREG(41) = 0x6C;
    YREG(42) = 0xCC;
    YREG(43) = 0xB1;
}

void Setup_InitImpl(SetupState* this) {
    func_80185908();
    SaveContext_Init();
    Setup_SetRegs();

    STOP_GAMESTATE(&this->state);
    SET_NEXT_GAMESTATE(&this->state, ConsoleLogo_Init, sizeof(ConsoleLogoState));
}

void Setup_Destroy(GameState* thisx) {
}

void Setup_Init(GameState* thisx) {
    SetupState* this = (SetupState*)thisx;

    this->state.destroy = Setup_Destroy;
    Setup_InitImpl(this);
}
