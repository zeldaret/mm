#ifndef BGM_H
#define BGM_H

#define NA_BGM_STOP 0x100000FF

#define NA_BGM_GENERAL_SFX 0x0       // General Sound Effects
#define NA_BGM_NATURE_AMBIENCE 0x01
#define NA_BGM_FIELD 0x02                // Termina Field
#define NA_BGM_CHASE 0x03                //	Forest Chase
#define NA_BGM_STALKID 0x04              //	Majora's Theme
#define NA_BGM_CLOCK_TOWER 0x05          //	The Clock Tower
#define NA_BGM_RUIN_DUNGEON_FRONT 0x06   //	Stone Tower Temple
#define NA_BGM_RUIN_DUNGEON_REVERSE 0x07 //	Stone Tower Temple Inverted
#define NA_BGM_FAILURE_0 0x08            //	Missed Event 1
#define NA_BGM_FAILURE_1 0x09            //	Title
#define NA_BGM_OMENYA 0x0A               //	Mask Salesman
#define NA_BGM_DEMO_CURE 0x0B            //	Song of Healing
#define NA_BGM_DAMP_AREA 0x0C            //	Southern Swamp
#define NA_BGM_UFO 0x0D                  //	Ghost Attack
#define NA_BGM_JUNGLE_CREWS 0x0E         //	Mini Game
#define NA_BGM_SHARP 0x0F                //	Sharp's Curse
#define NA_BGM_SEA_AREA 0x10             //	Great Bay Coast
#define NA_BGM_IKANA_AREA 0x11           //	Ikana Valley
#define NA_BGM_DEKU_KING 0x12            //	Court of the Deku King
#define NA_BGM_SNOW_AREA 0x13            //	Mountain Village
#define NA_BGM_PIRATE_AREA 0x14          //	Pirates' Fortress
#define NA_BGM_DUMMY_21 0x15             //	Clock Town Day 1		This song's filename is dummied out in MM3D
#define NA_BGM_DUMMY_22 0x16             //	Clock Town Day 2		This song's filename is dummied out in MM3D
#define NA_BGM_DUMMY_23 0x17             //	Clock Town Day 3		This song's filename is dummied out in MM3D
#define NA_BGM_FILE_SELECT 0x18          //  This song has no track name, as it's a duplicate of the Fairy's Fountain
#define NA_BGM_EVENT_CLEAR 0x19          //	Event Clear
#define NA_BGM_ENEMY 0x1A                //	Battle
#define NA_BGM_BOSS 0x1B               //	Boss Battle
#define NA_BGM_JUNGLE_DUNGEON 0x1C       //	Woodfall Temple
#define NA_BGM_MARKET 0x1D               //	Clock Town Day 1		Duplicate of #15. Interesting filename in MM3D.	✘
#define NA_BGM_OPENING 0x1E              //	Forest Ambush
#define NA_BGM_LINK_HOUSE 0x1F           //	House
#define NA_BGM_GAME_OVER 0x20            //	Game Over
#define NA_BGM_BOSS_CLEAR 0x21           //	Boss Clear
#define NA_BGM_ITEM_GET 0x22             //	Item Catch
#define NA_BGM_GATE_OPEN 0x23            //	Clock Town Day 2	Duplicate of #16. In MM3D, it shares its filename with the Door of Time song from OoT
#define NA_BGM_HEART_GET 0x24            //	Complete a Heart Piece
#define NA_BGM_MINI_GAME_2 0x25          //	Playing Minigame
#define NA_BGM_GORON_RACE 0x26           //	Goron Race
#define NA_BGM_ORGEL_HOUSE 0x27          //	Music Box House
#define NA_BGM_GODESS 0x28               //	Fairy's Fountain		In MM3D, it shares its filename with the Door of Time song from OoT
#define NA_BGM_HIME 0x29                 //	Zelda's Lullaby
#define NA_BGM_SISTER_DANCER 0x2A        //	Rosa Sisters' Dance
#define NA_BGM_OPEN_TRE_BOX 0x2B         //	Open Chest
#define NA_BGM_DRUGSTORE 0x2C            //	Marine Research Laboratory
#define NA_BGM_KYOJIN_ROOM 0x2D          //	The Four Giants
#define NA_BGM_FUSHA 0x2E                //	Guru-Guru's Song
#define NA_BGM_ROMANI_RANCH 0x2F               //	Romani Ranch "RONRON"
#define NA_BGM_GORON 0x30                //	Goron Village
#define NA_BGM_MEETING 0x31              //	Mayor Dotour
#define NA_BGM_OCA_EPONA 0x32            //	Ocarina Epona's Song
#define NA_BGM_OCA_SUN 0x33              //	Ocarina Sun's Song
#define NA_BGM_OCA_TIME_NORMAL 0x34      //	Ocarina Song of Time
#define NA_BGM_OCA_STORM 0x35            //	Ocarina Song of Storms
#define NA_BGM_ZORA 0x36                 //	Zora Hall
#define NA_BGM_MASK_GET 0x37             //	A New Mask
#define NA_BGM_MINI_BOSS 0x38          //	Mini Boss "MIDDLE_BOSS"
#define NA_BGM_S_ITEM_GET 0x39           //	Small Item Catch
#define NA_BGM_TENMONDAI 0x3A            //	Astral Observatory
#define NA_BGM_NORMAL_DUNGEON 0x3B       //	Clock Town Cavern
#define NA_BGM_MILK_BAR 0x3C             //	Milk Bar Latte
#define NA_BGM_APPEAR 0x3D               //	Meet Zelda (OoT)
#define NA_BGM_MAYOIMORI 0x3E            //	Woods of Mystery
#define NA_BGM_GORON_GOAL 0x3F           //	Goron Race Goal
#define NA_BGM_HORSE 0x40                //	Gorman Race
#define NA_BGM_HORSE_GOAL 0x41           //	Race Finish
#define NA_BGM_INGO 0x42                 //	Gorman Bros.
#define NA_BGM_KOTAKE_KOUME 0x43         //	Kotake's Potion Shop
#define NA_BGM_SHOP 0x44                 //	Store
#define NA_BGM_OWL 0x45                  //	Gaebora's Theme
#define NA_BGM_MINI_GAME 0x46            //	Target Practice
#define NA_BGM_OCA_BIGWING 0x47          //	Ocarina Song of Soaring
#define NA_BGM_OCA_CURE 0x48             //	Ocarina Song of Healing
#define NA_BGM_TIME_SPEED 0x49           //	Inverted Song of Time
#define NA_BGM_TIME_JUMP 0x4A            //	Song of Double Time
#define NA_BGM_DEMO_AWAKING 0x4B         //	Sonata of Awakening
#define NA_BGM_DEMO_LULLABY 0x4C         //	Goron Lullaby
#define NA_BGM_DEMO_TIDE 0x4D            //	New Wave Bossa Nova
#define NA_BGM_DEMO_SHELL 0x4E           //	Elegy of Emptiness
#define NA_BGM_DEMO_PLEDGE 0x4F          //	Oath to Order
#define NA_BGM_EXERCISE_HALL 0x50        //	Sword Training
#define NA_BGM_DEMO_LULLABY_HALF 0x51    //	Ocarina Goron Lullaby Intro
#define NA_BGM_OCA_YOUSEI 0x52           //	New Song
#define NA_BGM_FACEMASK 0x53             //	Bremen March
#define NA_BGM_QUARTET 0x54              //	Ballad of the Wind Fish
#define NA_BGM_WING_WARP 0x55            //	Song of Soaring
#define NA_BGM_MILK_BAR_DUMMY 0x56       //	Milk Bar Latte		Duplicate.
#define NA_BGM_FINAL_HOURS 0x57           //	Final Hours "TIME_LIMIT"
#define NA_BGM_MIKAU_LIFF 0x58           //	Mikau's Tale
#define NA_BGM_MIKAU_FIN 0x59            //	A single guitar chord.
#define NA_BGM_FROG_SONG 0x5A            //	Don Gero's Song
#define NA_BGM_OCA_AWAKING 0x5B          //	Ocarina Sonata of Awakening
#define NA_BGM_OCA_LULLABY 0x5C          //	Ocarina Goron Lullaby
#define NA_BGM_OCA_TIDE 0x5D             //	Ocarina New Wave Bossa Nova
#define NA_BGM_OCA_SHELL 0x5E            //	Ocarina Elegy of Emptiness
#define NA_BGM_OCA_PLEDGE 0x5F           //	Ocarina Oath to Order
#define NA_BGM_LAST_DUNGEON 0x60         //
#define NA_BGM_OCA_LULLABY_HALF 0x61     //
#define NA_BGM_OCA_SESSION 0x62          //	Bass and Guitar Session
#define NA_BGM_DEMO_SESSION 0x63         //	Piano Solo
#define NA_BGM_ALLPART_SESSION 0x64      //	The Indigo-Go's Rehearsal
#define NA_BGM_SILVER_DUNGEON 0x65       //	Snowhead Temple
#define NA_BGM_DEEPBLUE_DUNGEON 0x66     //	Great Bay Temple
#define NA_BGM_DEMO_TIDE_SAX 0x67        //
#define NA_BGM_DEMO_TIDE_VOCAL 0x68      //
#define NA_BGM_MUJURA_1 0x69             //	Majora's Wrath
#define NA_BGM_MUJURA_2 0x6A             //	Majora's Incarnation
#define NA_BGM_MUJURA_3 0x6B             //	Majora's Mask Battle
#define NA_BGM_BASS_PLAY 0x6C            //	Bass Practice
#define NA_BGM_DRUMS_PLAY 0x6D           //	Drums Practice
#define NA_BGM_PIANO_PLAY 0x6E           //	Piano Practice
#define NA_BGM_IKANA_CASTLE 0x6F         //	Ikana Castle
#define NA_BGM_GATHERING 0x70            //	Calling the Four Giants
#define NA_BGM_CAMARO_DANCE 0x71         //	Kamaro's Dance
#define NA_BGM_DONKEY_CART 0x72          //	Cremia's Carriage
#define NA_BGM_QUIZ 0x73                 //	Keaton
#define NA_BGM_END_DEMO 0x74             //	The End/Credits I
#define NA_BGM_OPENING_LOOP 0x75         //	Forest Ambush (?)		Duplicate.
#define NA_BGM_TITLE 0x76                //	Title Screen
#define NA_BGM_DUNGEON_APPEAR 0x77       //	Surfacing of Woodfall
#define NA_BGM_PURIFICATION_0 0x78       //	Woodfall Clear
#define NA_BGM_PURIFICATION_1 0x79       //	Snowhead Clear
#define NA_BGM_INTO_THE_MOON 0x7B        //	To the Moon
#define NA_BGM_GOODBYE_GIANT 0x7C        //
#define NA_BGM_CHAT 0x7D                 //	Tatl and Tael
#define NA_BGM_MOON_VANISH 0x7E          //	Moon's Destruction
#define NA_BGM_STAFFROLL2 0x7F           //	The End/Credits II
#define NA_BGM_DISABLED 0xFFFF

#endif
