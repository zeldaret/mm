#ifndef Z_EN_TIME_TAG_H
#define Z_EN_TIME_TAG_H

#include "global.h"

struct EnTimeTag;

typedef void (*EnTimeTagActionFunc)(struct EnTimeTag*, PlayState*);

#define ENTIMETAG_GET_TYPE(thisx) (((thisx)->params & 0xE000) >> 0xD)

#define ENTIMETAG_GET_KICKOUT_TEXT_TYPE(thisx) (((thisx)->params & 0x1FE0) >> 0x5)
#define ENTIMETAG_GET_KICKOUT_EXIT_INDEX(thisx) ((thisx)->params & 0x1F)
#define ENTIMETEG_GET_KICKOUT_HOUR(thisx) ((thisx)->home.rot.x)
#define ENTIMETEG_GET_KICKOUT_MINUTE(thisx) ((thisx)->home.rot.y)

#define ENTIMETAG_GET_SOARING_SWITCHFLAG(thisx) ((thisx)->params & 0x7F)

#define ENTIMETAG_GET_DIARY_TYPE(thisx) ((thisx)->params & 0x7F)
#define ENTIMETAG_GET_DIARY_TIMER(thisx) ((thisx)->home.rot.x)
#define ENTIMETAG_GET_DIARY_SONG(thisx) ((thisx)->home.rot.z)

typedef enum {
    /* 0 */ TIMETAG_KICKOUT_DOOR,
    /* 1 */ TIMETAG_SOARING_ENGRAVING,
    /* 2 */ TIMETAG_ROOFTOP_OATH,
    /* 3 */ TIMETAG_DIARY,
    /* 4 */ TIMETAG_KICKOUT_FINAL_HOURS,
    /* 5 */ TIMETAG_KICKOUT_NO_DOOR
} TimeTagType;

typedef enum {
    /* 0 */ TIMETAG_DIARY_MIKAU,
    /* 1 */ TIMETAG_DIARY_LULU
} DiaryType;

typedef enum {
    /* 0 */ TIMETAG_DIARY_SONG_EVAN_PART1,
    /* 1 */ TIMETAG_DIARY_SONG_EVAN_PART2
} DiarySong;

typedef enum {
    /*  0 */ KICKOUT_TEXT_TYPE_0, // I am closing the shop
    /*  1 */ KICKOUT_TEXT_TYPE_SWAMP_SHOOTING_GALLERY, // time to close shop
    /*  2 */ KICKOUT_TEXT_TYPE_STOCK_POT_INN, // stock pot in locking the door
    /*  3 */ KICKOUT_TEXT_TYPE_HONEY_AND_DARLING, // need some alone time
    /*  4 */ KICKOUT_TEXT_TYPE_LOTTERY, // business is finished
    /*  5 */ KICKOUT_TEXT_TYPE_BARN_DAY, // the lady needs a break
    /*  6 */ KICKOUT_TEXT_TYPE_DEFAULT, // (Many scenes) place is about to close
    /*  7 */ KICKOUT_TEXT_TYPE_BARN_NIGHT, // they came
    /*  8 */ KICKOUT_TEXT_TYPE_TRADING_POST, // we have to close shop
    /*  9 */ KICKOUT_TEXT_TYPE_MILK_BAR, // I have to get ready for business
    /* 10 */ KICKOUT_TEXT_TYPE_CURIOSITY_SHOP_BACK_1, // shop is opening, you need to go
    /* 11 */ KICKOUT_TEXT_TYPE_CURIOSITY_SHOP_BACK_2, // shop is opening, we're in the way
    /* 12 */ KICKOUT_TEXT_TYPE_TOWN_SHOOTING_GALLERY_1, // it's time to close
    /* 13 */ KICKOUT_TEXT_TYPE_TOWN_SHOOTING_GALLERY_2, // quick, it's closing time
    /* 14 */ KICKOUT_TEXT_TYPE_SWORDSMANS_SCHOOL, // need to cut the moon, must leave
    /* 15 */ KICKOUT_TEXT_TYPE_TREASURE_CHEST_SHOP, // already time to close shop
    /* 16 */ KICKOUT_TEXT_TYPE_DOGGY_RACETRACK, // no more for today
} EnTimeTagKickOutTextType;

typedef struct EnTimeTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnTimeTagActionFunc actionFunc;
} EnTimeTag; // size = 0x148

#endif // Z_EN_TIME_TAG_H
