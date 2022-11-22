/*
 * File: z_file_nameset_NES.c (z_file_copy_erase.c)
 * Overlay: ovl_file_choose
 * Description:
 */

#include "z_file_choose.h"
#include "z64rumble.h"

// Vtx Data
#include "overlays/ovl_File_Choose/ovl_file_choose.c"

u8 D_808141F0[] = {
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
    0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
    0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3A, 0x3B, 0x3C, 0x3D, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x40, 0x3F,
    0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// When choosing a file to copy or erase, the 6 main menu buttons are placed at these offsets
s16 sChooseFileYOffsets[] = { -48, -48, -48, -24, -24, 0 };

s16 D_8081424C[3][3] = {
    { 0, -48, -48 },
    { -64, 16, -48 },
    { -64, -64, 32 },
};

s16 sEraseDelayTimer = 15;

s16 D_80814264[] = { -56, -40, -24, 0 };

s16 D_8081426C[] = { 0, 16, 32 };

/**
 * Move buttons into place for the select source screen and fade in the proper labels.
 * Update function for `CM_SETUP_COPY_SOURCE`
 */
void FileSelect_SetupCopySource(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s32 yStep;
    s16 i;

    for (i = 0; i < 5; i++) {
        yStep = ABS_ALT(this->buttonYOffsets[i] - sChooseFileYOffsets[i]) / this->actionTimer;

        if (this->buttonYOffsets[i] >= sChooseFileYOffsets[i]) {
            this->buttonYOffsets[i] -= yStep;
        } else {
            this->buttonYOffsets[i] += yStep;
        }
    }

    this->actionButtonAlpha[FS_BTN_ACTION_COPY] -= 200 / 4;
    this->actionButtonAlpha[FS_BTN_ACTION_ERASE] -= 200 / 4;
    this->optionButtonAlpha -= 200 / 4;
    this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] += 200 / 4;
    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->actionTimer = 4;
        this->actionButtonAlpha[FS_BTN_ACTION_COPY] = this->actionButtonAlpha[FS_BTN_ACTION_ERASE] =
            this->optionButtonAlpha = 0;

        this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] = 200;
        this->titleLabel = this->nextTitleLabel;

        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->buttonIndex = FS_BTN_COPY_QUIT;
        this->configMode++;
    }
}

/**
 * Allow the player to select a file to copy or exit back to the main menu.
 * Update function for `CM_SELECT_COPY_SOURCE`
 */
void FileSelect_SelectCopySource(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    Input* input = CONTROLLER1(&this->state);

    if (((this->buttonIndex == FS_BTN_COPY_QUIT) && CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) ||
        CHECK_BTN_ALL(input->press.button, BTN_B)) {
        this->actionTimer = 4;
        this->buttonIndex = FS_BTN_MAIN_COPY;
        this->nextTitleLabel = FS_TITLE_SELECT_FILE;
        this->configMode = CM_COPY_RETURN_MAIN;
        this->warningLabel = FS_WARNING_NONE;
        play_sound(NA_SE_SY_FSEL_CLOSE);
    } else if (CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) {
        if (!gSaveContext.unk_3F3F) {
            if (SLOT_OCCUPIED(sramCtx, this->buttonIndex)) {
                this->actionTimer = 4;
                this->selectedFileIndex = this->buttonIndex;
                this->configMode = CM_SETUP_COPY_DEST_1;
                this->nextTitleLabel = FS_TITLE_COPY_TO;
                play_sound(NA_SE_SY_FSEL_DECIDE_L);
            } else {
                play_sound(NA_SE_SY_FSEL_ERROR);
            }
        } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, this->buttonIndex)) {
            this->actionTimer = 4;
            this->selectedFileIndex = this->buttonIndex;
            this->configMode = CM_SETUP_COPY_DEST_1;
            this->nextTitleLabel = FS_TITLE_COPY_TO;
            play_sound(NA_SE_SY_FSEL_DECIDE_L);
        } else {
            play_sound(NA_SE_SY_FSEL_ERROR);
        }
    } else {
        if (ABS_ALT(this->stickAdjY) >= 30) {
            play_sound(NA_SE_SY_FSEL_CURSOR);
            if (this->stickAdjY >= 30) {
                this->buttonIndex--;
                if (this->buttonIndex == FS_BTN_COPY_FILE_3) {
                    this->buttonIndex = FS_BTN_COPY_FILE_2;
                }
                if (this->buttonIndex < FS_BTN_COPY_FILE_1) {
                    this->buttonIndex = FS_BTN_COPY_QUIT;
                }
            } else {
                this->buttonIndex++;
                if (this->buttonIndex == FS_BTN_COPY_FILE_3) {
                    this->buttonIndex = FS_BTN_COPY_QUIT;
                }
                if (this->buttonIndex > FS_BTN_COPY_QUIT) {
                    this->buttonIndex = FS_BTN_COPY_FILE_1;
                }
            }
        }
        if (this->buttonIndex != FS_BTN_COPY_QUIT) {
            if (!gSaveContext.unk_3F3F) {
                if (!SLOT_OCCUPIED(sramCtx, this->buttonIndex)) {
                    this->warningLabel = FS_WARNING_FILE_EMPTY;
                    this->warningButtonIndex = this->buttonIndex;
                    this->emptyFileTextAlpha = 255;
                } else {
                    this->warningLabel = FS_WARNING_NONE;
                }
            } else if (!FILE_CHOOSE_SLOT_OCCUPIED(this, this->buttonIndex)) {
                this->warningLabel = FS_WARNING_FILE_EMPTY;
                this->warningButtonIndex = this->buttonIndex;
                this->emptyFileTextAlpha = 255;
            } else {
                this->warningLabel = FS_WARNING_NONE;
            }
        }
    }
}

/**
 * Move the menu buttons into place for the copy destination selection and switch titles.
 * Update function for `CM_SETUP_COPY_DEST_1`
 */
void FileSelect_SetupCopyDest1(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s32 yStep;
    s16 i;

    for (i = 0; i < 3; i++) {
        yStep = ABS_ALT(this->buttonYOffsets[i] - D_8081424C[this->buttonIndex][i]) / this->actionTimer;

        if (D_8081424C[this->buttonIndex][i] >= this->buttonYOffsets[i]) {
            this->buttonYOffsets[i] += yStep;
        } else {
            this->buttonYOffsets[i] -= yStep;
        }
    }

    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->nameBoxAlpha[this->buttonIndex] -= 200 / 4;

    this->actionTimer--;
    if (this->actionTimer == 0) {
        this->buttonYOffsets[this->buttonIndex] = D_8081424C[this->buttonIndex][this->buttonIndex];
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->actionTimer = 4;
        this->configMode++;
    }
}

/**
 * Show the file info of the file selected to copy from.
 * Update function for `CM_SETUP_COPY_DEST_2`
 */
void FileSelect_SetupCopyDest2(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->nameBoxAlpha[this->buttonIndex] -= 200 / 4;
    this->fileInfoAlpha[this->buttonIndex] += 200 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->nameBoxAlpha[this->buttonIndex] = 0;
        this->fileInfoAlpha[this->buttonIndex] = 200;
        this->buttonIndex = FS_BTN_COPY_QUIT;
        this->actionTimer = 4;
        this->configMode = CM_SELECT_COPY_DEST;
    }
}

/**
 * Allow the player to select a slot to copy to or exit to the copy select screen.
 * Update function for `CM_SELECT_COPY_DEST`
 */
void FileSelect_SelectCopyDest(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    Input* input = CONTROLLER1(&this->state);

    if (((this->buttonIndex == FS_BTN_COPY_QUIT) && CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) ||
        CHECK_BTN_ALL(input->press.button, BTN_B)) {
        this->buttonIndex = this->selectedFileIndex;
        this->nextTitleLabel = FS_TITLE_COPY_FROM;
        this->actionTimer = 4;
        this->configMode = CM_EXIT_TO_COPY_SOURCE_1;
        play_sound(NA_SE_SY_FSEL_CLOSE);
    } else if (CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) {
        if (!gSaveContext.unk_3F3F) {
            if (!SLOT_OCCUPIED(sramCtx, this->buttonIndex)) {
                this->fileNum = this->buttonIndex;
                this->nextTitleLabel = FS_TITLE_COPY_CONFIRM;
                this->actionTimer = 4;
                this->configMode = CM_SETUP_COPY_CONFIRM_1;
                play_sound(NA_SE_SY_FSEL_DECIDE_L);
            } else {
                play_sound(NA_SE_SY_FSEL_ERROR);
            }
        } else if (!FILE_CHOOSE_SLOT_OCCUPIED(this, this->buttonIndex)) {
            this->fileNum = this->buttonIndex;
            this->nextTitleLabel = FS_TITLE_COPY_CONFIRM;
            this->actionTimer = 4;
            this->configMode = CM_SETUP_COPY_CONFIRM_1;
            play_sound(NA_SE_SY_FSEL_DECIDE_L);
        } else {
            play_sound(NA_SE_SY_FSEL_ERROR);
        }
    } else {
        if (ABS_ALT(this->stickAdjY) >= 30) {
            play_sound(NA_SE_SY_FSEL_CURSOR);
            if (this->stickAdjY >= 30) {
                this->buttonIndex--;
                if (this->buttonIndex == FS_BTN_COPY_FILE_3) {
                    this->buttonIndex = FS_BTN_COPY_FILE_2;
                }
                if (this->buttonIndex == this->selectedFileIndex) {
                    this->buttonIndex--;
                    if (this->buttonIndex < FS_BTN_COPY_FILE_1) {
                        this->buttonIndex = FS_BTN_COPY_QUIT;
                    }
                    if (this->buttonIndex == FS_BTN_COPY_FILE_3) {
                        this->buttonIndex = FS_BTN_COPY_FILE_2;
                    }
                } else if (this->buttonIndex < FS_BTN_COPY_FILE_1) {
                    this->buttonIndex = FS_BTN_COPY_QUIT;
                }
            } else {
                this->buttonIndex++;
                if (this->buttonIndex > FS_BTN_COPY_QUIT) {
                    this->buttonIndex = FS_BTN_COPY_FILE_1;
                }
                if (this->buttonIndex == this->selectedFileIndex) {
                    this->buttonIndex++;
                }
                if (this->buttonIndex == FS_BTN_COPY_FILE_3) {
                    this->buttonIndex = FS_BTN_COPY_QUIT;
                }
            }
        }
        if (this->buttonIndex != FS_BTN_COPY_QUIT) {
            if (!gSaveContext.unk_3F3F) {
                if (SLOT_OCCUPIED(sramCtx, this->buttonIndex)) {
                    this->warningLabel = FS_WARNING_FILE_IN_USE;
                    this->warningButtonIndex = this->buttonIndex;
                    this->emptyFileTextAlpha = 255;
                } else {
                    this->warningLabel = FS_WARNING_NONE;
                }
            } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, this->buttonIndex)) {
                this->warningLabel = FS_WARNING_FILE_IN_USE;
                this->warningButtonIndex = this->buttonIndex;
                this->emptyFileTextAlpha = 255;
            } else {
                this->warningLabel = FS_WARNING_NONE;
            }
        }
    }
}

/**
 * Fade out file info, bring back the name box, and get ready to return to copy source screen.
 * Update function for `CM_EXIT_TO_COPY_SOURCE_1`
 */
void FileSelect_ExitToCopySource1(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->fileInfoAlpha[this->buttonIndex] -= 200 / 4;
    this->nameBoxAlpha[this->buttonIndex] += 200 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->nextTitleLabel = FS_TITLE_COPY_FROM;
        this->nameBoxAlpha[this->buttonIndex] = 200;
        this->fileInfoAlpha[this->buttonIndex] = 0;
        this->actionTimer = 4;
        this->configMode++;
    }
}

/**
 * Move the buttons back into place and return to copy source select.
 * Update function for `CM_EXIT_TO_COPY_SOURCE_2`
 */
void FileSelect_ExitToCopySource2(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s16 i;
    s32 yStep;

    for (i = 0; i < 3; i++) {
        yStep = ABS_ALT(this->buttonYOffsets[i] - sChooseFileYOffsets[i]) / this->actionTimer;

        if (this->buttonYOffsets[i] >= sChooseFileYOffsets[i]) {
            this->buttonYOffsets[i] -= yStep;
        } else {
            this->buttonYOffsets[i] += yStep;
        }
    }

    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->buttonIndex = 3;
        this->configMode = CM_SELECT_COPY_SOURCE;
    }
}

/**
 * Rearrange buttons on the screen to prepare for copy confirmation.
 * Update function for `CM_SETUP_COPY_CONFIRM_1`
 */
void FileSelect_SetupCopyConfirm1(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s16 i;
    s32 yStep;

    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;

    for (i = 0; i < 3; i++) {
        if ((i != this->fileNum) && (i != this->selectedFileIndex)) {
            this->fileButtonAlpha[i] -= 200 / 4;

            if (!gSaveContext.unk_3F3F) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->connectorAlpha[i] -= 255 / 4;
                    this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                }
            } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                this->connectorAlpha[i] -= 255 / 4;
                this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
            }
        } else if (i == this->fileNum) {
            yStep = ABS_ALT(this->buttonYOffsets[i] - D_80814264[i]) / this->actionTimer;
            this->buttonYOffsets[i] += yStep;

            if (this->buttonYOffsets[i] >= D_80814264[i]) {
                this->buttonYOffsets[i] = D_80814264[i];
            }
        }
    }

    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->actionTimer = 4;
        this->configMode++;
    }
}

/**
 * Fade in the 'Yes' button before allowing the player to decide.
 * Update function for `CM_SETUP_COPY_CONFIRM_2`
 */
void FileSelect_SetupCopyConfirm2(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->confirmButtonAlpha[FS_BTN_CONFIRM_YES] += 200 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->configMode = CM_COPY_CONFIRM;
        this->buttonIndex = FS_BTN_CONFIRM_QUIT;
    }
}

/**
 * Allow the player to confirm the copy, or quit back to the destination select.
 * If yes is selected, the actual copy occurs in this function before moving on to the animation.
 * Update function for `CM_COPY_CONFIRM`
 */
void FileSelect_CopyConfirm(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    Input* input = CONTROLLER1(&this->state);
    u16 dayTime;

    if (((this->buttonIndex != FS_BTN_CONFIRM_YES) && CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) ||
        CHECK_BTN_ALL(input->press.button, BTN_B)) {
        this->actionTimer = 4;
        this->nextTitleLabel = FS_TITLE_COPY_TO;
        this->configMode = CM_RETURN_TO_COPY_DEST;
        play_sound(NA_SE_SY_FSEL_CLOSE);
    } else if (CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) {
        dayTime = gSaveContext.save.time;
        gSaveContext.save.time = dayTime;
        this->nameAlpha[this->fileNum] = 0;
        this->fileInfoAlpha[this->fileNum] = this->nameAlpha[this->fileNum];
        this->nextTitleLabel = FS_TITLE_COPY_COMPLETE;
        this->actionTimer = 4;
        func_80146628(this, sramCtx);
        if (!gSaveContext.unk_3F3F) {
            this->configMode = CM_COPY_ANIM_1;
        } else {
            func_80147008(sramCtx, D_801C67C8[this->fileNum * 2], D_801C6818[this->fileNum * 2]);
            func_80147020(sramCtx);
            this->configMode = CM_UNK_D;
        }
        Rumble_Request(300.0f, 180, 20, 100);
        play_sound(NA_SE_SY_FSEL_DECIDE_L);
    } else if (ABS_ALT(this->stickAdjY) >= 30) {
        play_sound(NA_SE_SY_FSEL_CURSOR);
        this->buttonIndex ^= 1;
    }
}

void func_808054A4(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    u16 i;

    func_80147068(sramCtx);

    if (sramCtx->status == 0) {
        this->configMode = CM_COPY_ANIM_1;

        for (i = 0; i < 6; i++) {
            this->newf[this->fileNum][i] = gSaveContext.save.playerData.newf[i];
        }

        this->deaths[this->fileNum] = gSaveContext.save.playerData.deaths;

        for (i = 0; i < 8; i++) {
            this->playerName[this->fileNum][i] = gSaveContext.save.playerData.playerName[i];
        }

        this->healthCapacity[this->fileNum] = gSaveContext.save.playerData.healthCapacity;
        this->health[this->fileNum] = gSaveContext.save.playerData.health;
        this->defenseHearts[this->fileNum] = gSaveContext.save.inventory.defenseHearts;
    }
}

/**
 * Move buttons back in place and return to copy destination select.
 * Update function for `CM_RETURN_TO_COPY_DEST`
 */
void FileSelect_ReturnToCopyDest(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s16 i;
    s32 yStep;

    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->confirmButtonAlpha[FS_BTN_CONFIRM_YES] -= 200 / 4;

    for (i = 0; i < 3; i++) {
        if ((i != this->fileNum) && (i != this->selectedFileIndex)) {
            this->fileButtonAlpha[i] += 200 / 4;

            if (!gSaveContext.unk_3F3F) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                    this->connectorAlpha[i] += 255 / 4;
                }
            } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                this->connectorAlpha[i] += 255 / 4;
            }
        }

        yStep = ABS_ALT(this->buttonYOffsets[i] - D_8081424C[this->selectedFileIndex][i]) / this->actionTimer;

        if (D_8081424C[this->selectedFileIndex][i] >= this->buttonYOffsets[i]) {
            this->buttonYOffsets[i] += yStep;
        } else {
            this->buttonYOffsets[i] -= yStep;
        }
    }

    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->actionTimer = 4;
        this->buttonIndex = FS_BTN_COPY_QUIT;
        this->configMode = CM_SELECT_COPY_DEST;
    }
}

/**
 * Hide title
 * Update function for `CM_COPY_ANIM_1`
 */
void FileSelect_CopyAnim1(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->titleAlpha[0] -= 255 / 4;
    this->confirmButtonAlpha[FS_BTN_CONFIRM_YES] -= 200 / 4;
    this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] -= 200 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->titleAlpha[0] = 0;
        this->actionTimer = 4;
        this->configMode++;
    }
}

/**
 * Move a copy of the file window down and fade in the file info.
 * Update function for `CM_COPY_ANIM_2`
 */
void FileSelect_CopyAnim2(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s32 yStep;

    this->fileInfoAlpha[this->fileNum] += 200 / 4;
    this->nameAlpha[this->fileNum] += 200 / 4;
    this->titleAlpha[1] += 255 / 4;
    yStep = ABS_ALT(this->fileNamesY[this->fileNum] + 56) / this->actionTimer;
    this->fileNamesY[this->fileNum] -= yStep;

    if (this->fileNamesY[this->fileNum] <= -56) {
        this->fileNamesY[this->fileNum] = -56;
    }

    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->actionTimer = 45;
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->configMode++;
    }
}

/**
 * Play a sound effect to indicate that the copy has completed. Wait for a timer or for
 * the player to press a button before moving on.
 * Update function for `CM_COPY_ANIM_3`
 */
void FileSelect_CopyAnim3(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    Input* input = CONTROLLER1(&this->state);

    if (this->actionTimer == 38) {
        this->connectorAlpha[this->fileNum] = 255;
        play_sound(NA_SE_EV_DIAMOND_SWITCH);
    }

    this->actionTimer--;

    if (this->actionTimer <= 36) {
        if (CHECK_BTN_ANY(input->press.button, BTN_A | BTN_B | BTN_START) || (this->actionTimer == 0)) {
            this->actionTimer = 4;
            this->nextTitleLabel = FS_TITLE_SELECT_FILE;
            play_sound(NA_SE_SY_FSEL_DECIDE_L);
            this->configMode = CM_COPY_ANIM_4;
        }
    }
}

/**
 * Fade out the info boxes for both files and bring in their name boxes. Fade out title.
 * Update function for `CM_COPY_ANIM_4`
 */
void FileSelect_CopyAnim4(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->fileInfoAlpha[this->selectedFileIndex] -= 200 / 4;
    this->fileInfoAlpha[this->fileNum] -= 200 / 4;
    this->nameBoxAlpha[this->selectedFileIndex] += 200 / 4;
    this->nameBoxAlpha[this->fileNum] += 200 / 4;
    this->titleAlpha[0] -= 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->fileNamesY[this->fileNum] = this->buttonYOffsets[3] = 0;
        this->actionTimer = 4;
        this->titleAlpha[0] = 0;
        this->configMode++;
    }
}

/**
 * Restore all buttons and labels back to their original place and go back to the main menu.
 * Update function for `CM_COPY_ANIM_5`
 */
void FileSelect_CopyAnim5(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s16 i;
    s32 yStep;

    for (i = 0; i < 5; i++) {
        yStep = ABS_ALT(this->buttonYOffsets[i]) / this->actionTimer;

        if (this->buttonYOffsets[i] >= 0) {
            this->buttonYOffsets[i] -= yStep;
        } else {
            this->buttonYOffsets[i] += yStep;
        }
    }

    for (i = 0; i < 3; i++) {
        if (i != this->buttonIndex) {
            this->fileButtonAlpha[i] += 200 / 4;

            if (!gSaveContext.unk_3F3F) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                    this->connectorAlpha[i] += 255 / 4;
                }
            } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                this->connectorAlpha[i] += 255 / 4;
            }
        }
    }

    this->actionButtonAlpha[FS_BTN_ACTION_COPY] += 200 / 4;
    this->actionButtonAlpha[FS_BTN_ACTION_ERASE] += 200 / 4;
    this->optionButtonAlpha += 200 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        for (i = 0; i < 3; i++) {
            this->connectorAlpha[i] = 0;
            this->fileButtonAlpha[i] = 200;
            this->nameBoxAlpha[i] = this->nameAlpha[i] = this->connectorAlpha[i];

            if (!gSaveContext.unk_3F3F) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                    this->connectorAlpha[i] = 255;
                }
            } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                this->connectorAlpha[i] = 255;
            }
        }

        this->fileNamesY[this->selectedFileIndex] = 0;
        this->highlightColor[3] = 70;
        this->highlightPulseDir = 1;
        this->highlightTimer = 20;
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->configMode = CM_MAIN_MENU;
    }
}

/**
 * Exit from the copy source screen to the main menu. Return all buttons and labels to their original place.
 * Update function for `CM_COPY_RETURN_MAIN`
 */
void FileSelect_ExitCopyToMain(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s16 i;
    s32 yStep;

    for (i = 0; i < 5; i++) {
        yStep = ABS_ALT(this->buttonYOffsets[i]) / this->actionTimer;

        if (this->buttonYOffsets[i] >= 0) {
            this->buttonYOffsets[i] -= yStep;
        } else {
            this->buttonYOffsets[i] += yStep;
        }
    }

    this->actionButtonAlpha[FS_BTN_ACTION_COPY] += 200 / 4;
    this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] -= 200 / 4;
    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->actionButtonAlpha[FS_BTN_ACTION_COPY] = 200;
        this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] = 0;
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->configMode = CM_MAIN_MENU;
    }

    this->optionButtonAlpha = this->actionButtonAlpha[FS_BTN_ACTION_ERASE] =
        this->actionButtonAlpha[FS_BTN_ACTION_COPY];
}

/**
 * Move buttons into place for the erase select screen and fade in the proper labels.
 * Update function for `CM_SETUP_ERASE_SELECT`
 */
void FileSelect_SetupEraseSelect(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s16 i;
    s32 yStep;

    for (i = 0; i < 5; i++) {
        yStep = ABS_ALT(this->buttonYOffsets[i] - sChooseFileYOffsets[i]) / this->actionTimer;

        if (this->buttonYOffsets[i] >= sChooseFileYOffsets[i]) {
            this->buttonYOffsets[i] -= yStep;
        } else {
            this->buttonYOffsets[i] += yStep;
        }
    }

    this->actionButtonAlpha[FS_BTN_ACTION_COPY] -= 100;
    this->actionButtonAlpha[FS_BTN_ACTION_ERASE] -= 100;
    this->optionButtonAlpha -= 100;
    this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] += 200 / 4;

    if (this->actionButtonAlpha[FS_BTN_ACTION_COPY] <= 0) {
        this->actionButtonAlpha[FS_BTN_ACTION_COPY] = this->actionButtonAlpha[FS_BTN_ACTION_ERASE] =
            this->optionButtonAlpha = 0;
    }

    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->highlightColor[3] = 70;
        this->highlightPulseDir = 1;
        this->highlightTimer = 20;
        this->actionButtonAlpha[FS_BTN_ACTION_COPY] = this->actionButtonAlpha[FS_BTN_ACTION_ERASE] =
            this->optionButtonAlpha = 0;
        this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] = 200;
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->buttonIndex = FS_BTN_ERASE_QUIT;
        this->configMode++;
    }
}

/**
 * Allow the player to select a file to erase or exit back to the main menu.
 * Update function for `CM_ERASE_SELECT`
 */
void FileSelect_EraseSelect(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    Input* input = CONTROLLER1(&this->state);

    if (((this->buttonIndex == FS_BTN_COPY_QUIT) && CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) ||
        CHECK_BTN_ALL(input->press.button, BTN_B)) {
        this->buttonIndex = FS_BTN_MAIN_ERASE;
        this->actionTimer = 4;
        this->nextTitleLabel = FS_TITLE_SELECT_FILE;
        this->configMode = CM_EXIT_ERASE_TO_MAIN;
        this->warningLabel = FS_WARNING_NONE;
        play_sound(NA_SE_SY_FSEL_CLOSE);
    } else if (CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) {

        if (!gSaveContext.unk_3F3F) {
            if (SLOT_OCCUPIED(sramCtx, this->buttonIndex)) {
                this->actionTimer = 4;
                this->selectedFileIndex = this->buttonIndex;
                this->configMode = CM_SETUP_ERASE_CONFIRM_1;
                this->nextTitleLabel = FS_TITLE_ERASE_CONFIRM;
                play_sound(NA_SE_SY_FSEL_DECIDE_L);
            } else {
                play_sound(NA_SE_SY_FSEL_ERROR);
            }
        } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, this->buttonIndex)) {
            this->actionTimer = 4;
            this->selectedFileIndex = this->buttonIndex;
            this->configMode = CM_SETUP_ERASE_CONFIRM_1;
            this->nextTitleLabel = FS_TITLE_ERASE_CONFIRM;
            play_sound(NA_SE_SY_FSEL_DECIDE_L);
        } else {
            play_sound(NA_SE_SY_FSEL_ERROR);
        }
    } else {
        if (ABS_ALT(this->stickAdjY) >= 30) {
            play_sound(NA_SE_SY_FSEL_CURSOR);

            if (this->stickAdjY >= 30) {
                this->buttonIndex--;
                if (this->buttonIndex == FS_BTN_ERASE_FILE_3) {
                    this->buttonIndex = FS_BTN_ERASE_FILE_2;
                }
                if (this->buttonIndex < FS_BTN_ERASE_FILE_1) {
                    this->buttonIndex = FS_BTN_ERASE_QUIT;
                }
            } else {
                this->buttonIndex++;
                if (this->buttonIndex == FS_BTN_ERASE_FILE_3) {
                    this->buttonIndex = FS_BTN_ERASE_QUIT;
                }
                if (this->buttonIndex > FS_BTN_ERASE_QUIT) {
                    this->buttonIndex = FS_BTN_ERASE_FILE_1;
                }
            }
        }

        if (this->buttonIndex != FS_BTN_ERASE_QUIT) {
            if (!gSaveContext.unk_3F3F) {
                if (!SLOT_OCCUPIED(sramCtx, this->buttonIndex)) {
                    this->warningLabel = FS_WARNING_FILE_EMPTY;
                    this->warningButtonIndex = this->buttonIndex;
                    this->emptyFileTextAlpha = 255;
                } else {
                    this->warningLabel = FS_WARNING_NONE;
                }
            } else if (!FILE_CHOOSE_SLOT_OCCUPIED(this, this->buttonIndex)) {
                this->warningLabel = FS_WARNING_FILE_EMPTY;
                this->warningButtonIndex = this->buttonIndex;
                this->emptyFileTextAlpha = 255;
            } else {
                this->warningLabel = FS_WARNING_NONE;
            }
        } else {
            this->warningLabel = FS_WARNING_NONE;
        }
    }
}

/**
 * Update function for `CM_SETUP_ERASE_CONFIRM_1`
 */
void FileSelect_SetupEraseConfirm1(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s16 i;
    s32 yStep;

    for (i = 0; i < 3; i++) {
        if (i != this->buttonIndex) {
            this->fileButtonAlpha[i] -= 200 / 4;

            if (!gSaveContext.unk_3F3F) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->connectorAlpha[i] -= 255 / 4;
                    this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                }
            } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                this->connectorAlpha[i] -= 255 / 4;
                this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
            }
        } else {
            this->nameBoxAlpha[i] -= 200 / 4;
        }
    }
    this->titleAlpha[0] -= 255 / 8;
    this->titleAlpha[1] += 255 / 8;

    yStep = ABS_ALT(this->buttonYOffsets[this->buttonIndex] - D_8081426C[this->buttonIndex]) / this->actionTimer;

    if (this->buttonYOffsets[this->buttonIndex] >= D_8081426C[this->buttonIndex]) {
        this->buttonYOffsets[this->buttonIndex] -= yStep;
    } else {
        this->buttonYOffsets[this->buttonIndex] += yStep;
    }

    this->actionTimer--;

    if (this->actionTimer == 0) {
        for (i = 0; i < 3; i++) {
            if (i != this->buttonIndex) {
                this->fileButtonAlpha[i] = 0;

                if (!gSaveContext.unk_3F3F) {
                    if (SLOT_OCCUPIED(sramCtx, i)) {
                        this->connectorAlpha[i] = 0;
                        this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i] = 0;
                    }
                } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                    this->connectorAlpha[i] = 0;
                    this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i] = 0;
                }
            } else {
                this->nameBoxAlpha[i] = 0;
            }
        }

        this->buttonYOffsets[this->buttonIndex] = D_8081426C[this->buttonIndex];
        this->actionTimer = 4;
        this->configMode++;
    }
}

/**
 * Show the file info of the file selected to erase.
 * Update function for `CM_SETUP_ERASE_CONFIRM_2`
 */
void FileSelect_SetupEraseConfirm2(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->confirmButtonAlpha[FS_BTN_CONFIRM_YES] += 200 / 4;
    this->titleAlpha[0] -= 255 / 8;
    this->titleAlpha[1] += 255 / 8;
    this->fileInfoAlpha[this->buttonIndex] += 200 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->actionTimer = 4;
        this->titleLabel = this->nextTitleLabel;
        this->fileInfoAlpha[this->buttonIndex] = this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->confirmButtonAlpha[FS_BTN_CONFIRM_YES] = 200;
        this->buttonIndex = FS_BTN_CONFIRM_QUIT;
        this->configMode = CM_ERASE_CONFIRM;
    }
}

/**
 * Allow the player to confirm their choice to erase or return back to erase select.
 * Update function for `CM_ERASE_CONFIRM`
 */
void FileSelect_EraseConfirm(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    Input* input = CONTROLLER1(&this->state);

    if (((this->buttonIndex != FS_BTN_CONFIRM_YES) && CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) ||
        CHECK_BTN_ALL(input->press.button, BTN_B)) {
        this->buttonIndex = this->selectedFileIndex;
        this->nextTitleLabel = FS_TITLE_ERASE_FILE;
        this->configMode = CM_EXIT_TO_ERASE_SELECT_1;
        this->actionTimer = 4;
        play_sound(NA_SE_SY_FSEL_CLOSE);
    } else if (CHECK_BTN_ANY(input->press.button, BTN_A | BTN_START)) {
        func_80146580(this, sramCtx, this->selectedFileIndex);
        if (!gSaveContext.unk_3F3F) {
            this->configMode = CM_ERASE_ANIM_1;
        } else {
            func_80147008(sramCtx, D_801C67C8[this->selectedFileIndex * 2], D_801C6818[this->selectedFileIndex * 2]);
            func_80147020(sramCtx);
            this->configMode = CM_UNK_1D;
        }
        this->connectorAlpha[this->selectedFileIndex] = 0;
        play_sound(NA_SE_EV_DIAMOND_SWITCH);
        this->actionTimer = 4;
        this->nextTitleLabel = FS_TITLE_ERASE_COMPLETE;
        Rumble_Request(200.0f, 255, 20, 150);
        sEraseDelayTimer = 15;
    } else if (ABS_ALT(this->stickAdjY) >= 30) {
        play_sound(NA_SE_SY_FSEL_CURSOR);
        this->buttonIndex ^= 1;
    }
}

/**
 * Fade out file info, bring back the name box, and get ready to return to erase select screen.
 * Update function for `CM_EXIT_TO_ERASE_SELECT_1`
 */
void FileSelect_ExitToEraseSelect1(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->fileInfoAlpha[this->buttonIndex] -= 200 / 4;
    this->nameBoxAlpha[this->buttonIndex] += 200 / 4;
    this->confirmButtonAlpha[FS_BTN_CONFIRM_YES] -= 200 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->actionTimer = 4;
        this->fileInfoAlpha[this->buttonIndex] = 0;
        this->configMode++;
    }
}

/**
 * Move the buttons back into place and return to erase select.
 * Update function for `CM_EXIT_TO_ERASE_SELECT_2`
 */
void FileSelect_ExitToEraseSelect2(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s16 i;
    s32 yStep;

    yStep =
        ABS_ALT(this->buttonYOffsets[this->buttonIndex] - sChooseFileYOffsets[this->buttonIndex]) / this->actionTimer;

    if (this->buttonYOffsets[this->buttonIndex] >= sChooseFileYOffsets[this->buttonIndex]) {
        this->buttonYOffsets[this->buttonIndex] -= yStep;
    } else {
        this->buttonYOffsets[this->buttonIndex] += yStep;
    }

    for (i = 0; i < 3; i++) {
        if (i != this->buttonIndex) {
            this->fileButtonAlpha[i] += 200 / 4;

            if (!gSaveContext.unk_3F3F) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                    this->connectorAlpha[i] += 255 / 4;
                }
            } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                this->connectorAlpha[i] += 255 / 4;
            }
        }
    }

    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->buttonYOffsets[this->buttonIndex] = sChooseFileYOffsets[this->buttonIndex];
        this->actionTimer = 4;
        this->buttonIndex = FS_BTN_ERASE_QUIT;
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->configMode = CM_ERASE_SELECT;
    }
}

/**
 * Wait for an initial delay, then start fading out the selected file.
 * The actual file deletion occurs in this function
 * Update function for `CM_ERASE_ANIM_1`
 */
void FileSelect_EraseAnim1(GameState* thisx) {
    static s16 D_80814E80;
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;

    if (sEraseDelayTimer == 0) {
        if (this->actionTimer == 4) {
            D_80814E80 = 1;
        }

        if (this->actionTimer != 0) {
            this->titleAlpha[0] -= 255 / 4;
            this->titleAlpha[1] += 255 / 4;
            this->fileInfoAlpha[this->selectedFileIndex] -= 200 / 4;
            this->confirmButtonAlpha[FS_BTN_CONFIRM_YES] -= 200 / 4;
            this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] -= 200 / 4;
        }

        this->fileNamesY[this->selectedFileIndex] -= D_80814E80;
        D_80814E80 += 2;

        this->actionTimer--;
        if (this->actionTimer == 0) {
            this->configMode = CM_ERASE_ANIM_2;
            this->titleLabel = this->nextTitleLabel;
            this->titleAlpha[0] = 255;
            this->titleAlpha[1] = this->connectorAlpha[this->selectedFileIndex] = 0;

            // probably a fake match, there should be a better chained assignment
            this->confirmButtonAlpha[FS_BTN_CONFIRM_YES] = this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] = 0;
            if (1) {}
            if (0) {}
            this->fileInfoAlpha[this->selectedFileIndex] = this->nameAlpha[this->selectedFileIndex] =
                this->nameBoxAlpha[this->selectedFileIndex] = this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT];

            this->actionTimer = 45;
        }
    } else {
        sEraseDelayTimer--;

        if (sEraseDelayTimer == 0) {
            play_sound(NA_SE_OC_ABYSS);
        }
    }
}

void func_80807390(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    u16 i;

    func_80147068(sramCtx);

    if (sramCtx->status == 0) {
        this->configMode = CM_ERASE_ANIM_1;
        for (i = 0; i < 6; i++) {
            this->newf[this->selectedFileIndex][i] = gSaveContext.save.playerData.newf[i];
        }
    }
}

/**
 * Wait for a delay timer or for the palyer to press a button before returning to the main menu.
 * Update function for `CM_ERASE_ANIM_2`
 */
void FileSelect_EraseAnim2(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    Input* input = CONTROLLER1(&this->state);

    if (CHECK_BTN_ANY(input->press.button, BTN_A | BTN_B | BTN_START) || (--this->actionTimer == 0)) {
        this->buttonYOffsets[3] = 0;
        this->actionTimer = 4;
        this->nextTitleLabel = FS_TITLE_SELECT_FILE;
        this->configMode++;
        play_sound(NA_SE_SY_FSEL_CLOSE);
    }
}

/**
 * Exit from the erase animation to the main menu. Return all buttons and labels to their original place.
 * Update function for `CM_ERASE_ANIM_3`
 */
void FileSelect_EraseAnim3(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s16 i;
    s32 yStep;

    for (i = 0; i < 5; i++) {
        yStep = ABS_ALT(this->buttonYOffsets[i]) / this->actionTimer;

        if (this->buttonYOffsets[i] >= 0) {
            this->buttonYOffsets[i] -= yStep;
        } else {
            this->buttonYOffsets[i] += yStep;
        }
    }

    for (i = 0; i < 3; i++) {
        this->fileButtonAlpha[i] += 200 / 4;

        if (!gSaveContext.unk_3F3F) {
            if (SLOT_OCCUPIED(sramCtx, i)) {
                this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                this->connectorAlpha[i] += 255 / 4;
            }
        } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
            this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
            this->connectorAlpha[i] += 255 / 4;
        }
    }

    if (this->fileButtonAlpha[this->selectedFileIndex] >= 200) {
        this->fileButtonAlpha[this->selectedFileIndex] = 200;
    }

    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->fileNamesY[this->selectedFileIndex] = 0;
        this->highlightColor[3] = 70;
        this->highlightPulseDir = 1;
        this->highlightTimer = 20;
        this->actionButtonAlpha[FS_BTN_ACTION_COPY] = 200;
        this->confirmButtonAlpha[FS_BTN_CONFIRM_YES] = this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] = 0;
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->configMode = CM_MAIN_MENU;
    }

    this->optionButtonAlpha = this->actionButtonAlpha[FS_BTN_ACTION_ERASE] =
        this->actionButtonAlpha[FS_BTN_ACTION_COPY];
}

/**
 * Exit from the erase select screen to the main menu. Return all buttons and labels to their original place.
 * Update function for `CM_EXIT_ERASE_TO_MAIN`
 */
void FileSelect_ExitEraseToMain(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s16 i;
    s32 yStep;

    for (i = 0; i < 5; i++) {
        yStep = ABS_ALT(this->buttonYOffsets[i]) / this->actionTimer;

        if (this->buttonYOffsets[i] >= 0) {
            this->buttonYOffsets[i] -= yStep;
        } else {
            this->buttonYOffsets[i] += yStep;
        }
    }

    this->actionButtonAlpha[FS_BTN_ACTION_COPY] += 200 / 4;
    this->actionButtonAlpha[FS_BTN_ACTION_ERASE] += 200 / 4;
    this->optionButtonAlpha += 200 / 4;
    this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] -= 200 / 2;

    if (this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] <= 0) {
        this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] = 0;
    }

    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->highlightColor[3] = 70;
        this->highlightPulseDir = 1;
        this->highlightTimer = 20;
        this->actionButtonAlpha[FS_BTN_ACTION_COPY] = 200;
        this->confirmButtonAlpha[FS_BTN_CONFIRM_QUIT] = 0;
        this->titleLabel = this->nextTitleLabel;
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->configMode = CM_MAIN_MENU;
    }

    this->optionButtonAlpha = this->actionButtonAlpha[FS_BTN_ACTION_ERASE] =
        this->actionButtonAlpha[FS_BTN_ACTION_COPY];
}
