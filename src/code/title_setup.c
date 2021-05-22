#include <ultra64.h>
#include <global.h>

void TitleSetup_GameStateResetContext(void) {
    XREG(2) = 0;
    XREG(10) = 0x1A;
    XREG(11) = 0x14;
    XREG(12) = 0xE;
    XREG(13) = 0;
    XREG(31) = 0;
    XREG(41) = 0x50;
    XREG(43) = 0xFFFFFC54;

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
    XREG(87) = 0;
    XREG(88) = 0x56;
    XREG(89) = 0x258;
    XREG(90) = 0x1C2;
    XREG(91) = 0;
    XREG(94) = 0;
    XREG(95) = 0;

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

void TitleSetup_InitImpl(GameState* gameState) {
    func_80185908();
    func_800E9360();
    TitleSetup_GameStateResetContext();

    gameState->running = 0;

setNextGamestate
    :; // This label is probably a leftover of a debug ifdef, it's essential to not have gameState->running reordered!
    SET_NEXT_GAMESTATE(gameState, Title_Init, TitleContext);
}

void TitleSetup_Destroy(GameState* gameState) {
    ;
}

void TitleSetup_Init(GameState* gameState) {
    gameState->destroy = &TitleSetup_Destroy;
    TitleSetup_InitImpl(gameState);
}
