#ifndef MESSAGE_DATA_FMT_STAFF_H
#define MESSAGE_DATA_FMT_STAFF_H
/*
 * Text control characters
 */

#define MESSAGE_NEWLINE 0x01
#define MESSAGE_END 0x02
#define MESSAGE_BOX_BREAK 0x04
#define MESSAGE_COLOR 0x05
#define MESSAGE_SHIFT 0x06
#define MESSAGE_TEXTID 0x07
#define MESSAGE_QUICKTEXT_ENABLE 0x08
#define MESSAGE_QUICKTEXT_DISABLE 0x09
#define MESSAGE_PERSISTENT 0x0A
#define MESSAGE_EVENT 0x0B
#define MESSAGE_BOX_BREAK_DELAYED 0x0C
#define MESSAGE_AWAIT_BUTTON_PRESS 0x0D
#define MESSAGE_FADE 0x0E
#define MESSAGE_NAME 0x0F
#define MESSAGE_OCARINA 0x10
#define MESSAGE_FADE2 0x11
#define MESSAGE_SFX 0x12
#define MESSAGE_ITEM_ICON 0x13
#define MESSAGE_TEXT_SPEED 0x14
#define MESSAGE_BACKGROUND 0x15
#define MESSAGE_MARATHON_TIME 0x16
#define MESSAGE_RACE_TIME 0x17
#define MESSAGE_POINTS 0x18
#define MESSAGE_TOKENS 0x19
#define MESSAGE_UNSKIPPABLE 0x1A
#define MESSAGE_TWO_CHOICE 0x1B
#define MESSAGE_THREE_CHOICE 0x1C
#define MESSAGE_FISH_INFO 0x1D
#define MESSAGE_HIGHSCORE 0x1E
#define MESSAGE_TIME 0x1F

typedef enum TextColor {
    /* 0 */ TEXT_COLOR_DEFAULT,
    /* 1 */ TEXT_COLOR_RED,
    /* 2 */ TEXT_COLOR_ADJUSTABLE,
    /* 3 */ TEXT_COLOR_BLUE,
    /* 4 */ TEXT_COLOR_LIGHTBLUE,
    /* 5 */ TEXT_COLOR_PURPLE,
    /* 6 */ TEXT_COLOR_YELLOW,
    /* 7 */ TEXT_COLOR_BLACK
} TextColor;

#ifdef MESSAGE_DATA_STATIC
// For use in message_data_static files

// Encoded text consists of an array of bytes. Since it's in a macro it must be wrapped in a varargs macro so that each
// byte is not treated as a separate macro argument to DEFINE_MESSAGE. IDO doesn't support varargs macros, however we
// preprocess the message_data_static files with modern cpp instead. See the makefile rule for assets/text/
#define MSG(...) \
    { __VA_ARGS__ END }

#define ARG1(x) (x),
#define ARG2(x) (((x) >> 8) & 0xFF), (((x) >> 0) & 0xFF),
#define ARGC(x) (0x40 | (TEXT_COLOR_##x)),
#define CTRL_BASE(name) ARG1(MESSAGE_##name)
#define ARGB1(x) ARG1(TEXTBOX_BG_##x)
#define ARGB2(a, b, c, d) \
    (((TEXTBOX_BG_FGCOL_##a) << 4) | ((TEXTBOX_BG_BGCOL_##b) << 0)), (((TEXTBOX_BG_Y_OFFSET_##c) << 4) | ((d) << 0)),

// while a control character, newlines are handled in the charmap conversion
// stage to allow normal newline \n usage in message_data_static files
#define NEWLINE CTRL_BASE(NEWLINE)
#define END CTRL_BASE(END)
#define BOX_BREAK CTRL_BASE(BOX_BREAK)
#define COLOR(color) CTRL_BASE(COLOR) ARGC(color)
#define SHIFT(amount) CTRL_BASE(SHIFT) ARG1(amount)
#define TEXTID(textId) CTRL_BASE(TEXTID) ARG2(textId)
#define QUICKTEXT_ENABLE CTRL_BASE(QUICKTEXT_ENABLE)
#define QUICKTEXT_DISABLE CTRL_BASE(QUICKTEXT_DISABLE)
#define PERSISTENT CTRL_BASE(PERSISTENT)
#define EVENT CTRL_BASE(EVENT)
#define BOX_BREAK_DELAYED(delay) CTRL_BASE(BOX_BREAK_DELAYED) ARG1(delay)
#define AWAIT_BUTTON_PRESS CTRL_BASE(AWAIT_BUTTON_PRESS)
#define FADE(delay) CTRL_BASE(FADE) ARG1(delay)
#define NAME CTRL_BASE(NAME)
#define OCARINA CTRL_BASE(OCARINA)
#define FADE2(delay) CTRL_BASE(FADE2) ARG2(delay)
#define SFX(sfxId) CTRL_BASE(SFX) ARG2(sfxId)
#define ITEM_ICON(itemId) CTRL_BASE(ITEM_ICON) ARG1(itemId)
#define TEXT_SPEED(amount) CTRL_BASE(TEXT_SPEED) ARG1(amount)
#define BACKGROUND(bgIdx, fgColor, bgColor, yOffset, unk) \
    CTRL_BASE(BACKGROUND) ARGB1(bgIdx) ARGB2(fgColor, bgColor, yOffset, unk)
#define MARATHON_TIME CTRL_BASE(MARATHON_TIME)
#define RACE_TIME CTRL_BASE(RACE_TIME)
#define POINTS CTRL_BASE(POINTS)
#define TOKENS CTRL_BASE(TOKENS)
#define UNSKIPPABLE CTRL_BASE(UNSKIPPABLE)
#define TWO_CHOICE CTRL_BASE(TWO_CHOICE)
#define THREE_CHOICE CTRL_BASE(THREE_CHOICE)
#define FISH_INFO CTRL_BASE(FISH_INFO)
#define HIGHSCORE(highscore) CTRL_BASE(HIGHSCORE) ARG1(x)
#define TIME CTRL_BASE(TIME)

#endif

#endif
