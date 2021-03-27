typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long int s64;
typedef unsigned long long int u64;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;
typedef float f32;
typedef double f64;
typedef long int Mtx_t[4][4];
typedef union {
    Mtx_t m;
    long long int forc_structure_alignment;
} Mtx;
typedef float MtxF_t[4][4];
typedef union {
    MtxF_t mf;
    struct {
        float xx, xy, xz, xw,
              yx, yy, yz, yw,
              zx, zy, zz, zw,
              wx, wy, wz, ww;
    };
} MtxF;
typedef struct {
 short ob[3];
 unsigned short flag;
 short tc[2];
 unsigned char cn[4];
} Vtx_t;
typedef struct {
 short ob[3];
 unsigned short flag;
 short tc[2];
 signed char n[3];
 unsigned char a;
} Vtx_tn;
typedef union {
    Vtx_t v;
    Vtx_tn n;
    long long int force_structure_alignment;
} Vtx;
typedef struct {
  void *SourceImagePointer;
  void *TlutPointer;
  short Stride;
  short SubImageWidth;
  short SubImageHeight;
  char SourceImageType;
  char SourceImageBitSize;
  short SourceImageOffsetS;
  short SourceImageOffsetT;
  char dummy[4];
} uSprite_t;
typedef union {
  uSprite_t s;
  long long int force_structure_allignment[3];
} uSprite;
typedef struct {
 unsigned char flag;
 unsigned char v[3];
} Tri;
typedef struct {
 short vscale[4];
 short vtrans[4];
} Vp_t;
typedef union {
    Vp_t vp;
    long long int force_structure_alignment;
} Vp;
typedef struct {
  unsigned char col[3];
  char pad1;
  unsigned char colc[3];
  char pad2;
  signed char dir[3];
  char pad3;
} Light_t;
typedef struct {
  unsigned char col[3];
  char pad1;
  unsigned char colc[3];
  char pad2;
} Ambient_t;
typedef struct {
  int x1,y1,x2,y2;
} Hilite_t;
typedef union {
    Light_t l;
    long long int force_structure_alignment[2];
} Light;
typedef union {
    Ambient_t l;
    long long int force_structure_alignment[1];
} Ambient;
typedef struct {
    Ambient a;
    Light l[7];
} Lightsn;
typedef struct {
    Ambient a;
    Light l[1];
} Lights0;
typedef struct {
    Ambient a;
    Light l[1];
} Lights1;
typedef struct {
    Ambient a;
    Light l[2];
} Lights2;
typedef struct {
    Ambient a;
    Light l[3];
} Lights3;
typedef struct {
    Ambient a;
    Light l[4];
} Lights4;
typedef struct {
    Ambient a;
    Light l[5];
} Lights5;
typedef struct {
    Ambient a;
    Light l[6];
} Lights6;
typedef struct {
    Ambient a;
    Light l[7];
} Lights7;
typedef struct {
    Light l[2];
} LookAt;
typedef union {
    Hilite_t h;
    long int force_structure_alignment[4];
} Hilite;
typedef struct {
 int cmd:8;
 unsigned int par:8;
 unsigned int len:16;
 unsigned int addr;
} Gdma;
typedef struct {
  int cmd:8;
  int pad:24;
  Tri tri;
} Gtri;
typedef struct {
  int cmd:8;
  int pad1:24;
  int pad2:24;
  unsigned char param:8;
} Gpopmtx;
typedef struct {
  int cmd:8;
  int pad0:8;
  int mw_index:8;
  int number:8;
  int pad1:8;
  int base:24;
} Gsegment;
typedef struct {
  int cmd:8;
  int pad0:8;
  int sft:8;
  int len:8;
  unsigned int data:32;
} GsetothermodeL;
typedef struct {
  int cmd:8;
  int pad0:8;
  int sft:8;
  int len:8;
  unsigned int data:32;
} GsetothermodeH;
typedef struct {
  unsigned char cmd;
  unsigned char lodscale;
  unsigned char tile;
  unsigned char on;
  unsigned short s;
  unsigned short t;
} Gtexture;
typedef struct {
  int cmd:8;
  int pad:24;
  Tri line;
} Gline3D;
typedef struct {
  int cmd:8;
  int pad1:24;
  short int pad2;
  short int scale;
} Gperspnorm;
typedef struct {
                int cmd:8;
                unsigned int fmt:3;
                unsigned int siz:2;
                unsigned int pad:7;
                unsigned int wd:12;
                unsigned int dram;
} Gsetimg;
typedef struct {
  int cmd:8;
  unsigned int muxs0:24;
  unsigned int muxs1:32;
} Gsetcombine;
typedef struct {
  int cmd:8;
  unsigned char pad;
  unsigned char prim_min_level;
  unsigned char prim_level;
  unsigned long color;
} Gsetcolor;
typedef struct {
  int cmd:8;
  int x0:10;
  int x0frac:2;
  int y0:10;
  int y0frac:2;
  unsigned int pad:8;
  int x1:10;
  int x1frac:2;
  int y1:10;
  int y1frac:2;
} Gfillrect;
typedef struct {
  int cmd:8;
  unsigned int fmt:3;
  unsigned int siz:2;
  unsigned int pad0:1;
  unsigned int line:9;
  unsigned int tmem:9;
  unsigned int pad1:5;
  unsigned int tile:3;
  unsigned int palette:4;
  unsigned int ct:1;
  unsigned int mt:1;
  unsigned int maskt:4;
  unsigned int shiftt:4;
  unsigned int cs:1;
  unsigned int ms:1;
  unsigned int masks:4;
  unsigned int shifts:4;
} Gsettile;
typedef struct {
  int cmd:8;
  unsigned int sl:12;
  unsigned int tl:12;
  int pad:5;
  unsigned int tile:3;
  unsigned int sh:12;
  unsigned int th:12;
} Gloadtile;
typedef Gloadtile Gloadblock;
typedef Gloadtile Gsettilesize;
typedef Gloadtile Gloadtlut;
typedef struct {
  unsigned int cmd:8;
  unsigned int xl:12;
  unsigned int yl:12;
  unsigned int pad1:5;
  unsigned int tile:3;
  unsigned int xh:12;
  unsigned int yh:12;
  unsigned int s:16;
  unsigned int t:16;
  unsigned int dsdx:16;
  unsigned int dtdy:16;
} Gtexrect;
typedef struct {
    unsigned long w0;
    unsigned long w1;
    unsigned long w2;
    unsigned long w3;
} TexRect;
typedef struct {
 unsigned int w0;
 unsigned int w1;
} Gwords;
typedef union {
 Gwords words;
 Gdma dma;
 Gtri tri;
 Gline3D line;
 Gpopmtx popmtx;
 Gsegment segment;
 GsetothermodeH setothermodeH;
 GsetothermodeL setothermodeL;
 Gtexture texture;
 Gperspnorm perspnorm;
 Gsetimg setimg;
 Gsetcombine setcombine;
 Gsetcolor setcolor;
 Gfillrect fillrect;
 Gsettile settile;
 Gloadtile loadtile;
 Gsettilesize settilesize;
 Gloadtlut loadtlut;
        long long int force_structure_alignment;
} Gfx;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int gain : 16;
    unsigned int addr;
} Aadpcm;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int gain : 16;
    unsigned int addr;
} Apolef;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int pad1 : 16;
    unsigned int addr;
} Aenvelope;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int dmem : 16;
    unsigned int pad2 : 16;
    unsigned int count : 16;
} Aclearbuff;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int pad2 : 16;
    unsigned int inL : 16;
    unsigned int inR : 16;
} Ainterleave;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int pad1 : 24;
    unsigned int addr;
} Aloadbuff;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int pad1 : 16;
    unsigned int addr;
} Aenvmixer;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int gain : 16;
    unsigned int dmemi : 16;
    unsigned int dmemo : 16;
} Amixer;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int dmem2 : 16;
    unsigned int addr;
} Apan;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int pitch : 16;
    unsigned int addr;
} Aresample;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int pad1 : 16;
    unsigned int addr;
} Areverb;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int pad1 : 24;
    unsigned int addr;
} Asavebuff;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int pad1 : 24;
    unsigned int pad2 : 2;
    unsigned int number : 4;
    unsigned int base : 24;
} Asegment;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int dmemin : 16;
    unsigned int dmemout : 16;
    unsigned int count : 16;
} Asetbuff;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int flags : 8;
    unsigned int vol : 16;
    unsigned int voltgt : 16;
    unsigned int volrate : 16;
} Asetvol;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int dmemin : 16;
    unsigned int dmemout : 16;
    unsigned int count : 16;
} Admemmove;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int count : 16;
    unsigned int addr;
} Aloadadpcm;
typedef struct
{
    unsigned int cmd : 8;
    unsigned int pad1 : 8;
    unsigned int pad2 : 16;
    unsigned int addr;
} Asetloop;
typedef struct
{
    unsigned int w0;
    unsigned int w1;
} Awords;
typedef union {
    Awords words;
    Aadpcm adpcm;
    Apolef polef;
    Aclearbuff clearbuff;
    Aenvelope envelope;
    Ainterleave interleave;
    Aloadbuff loadbuff;
    Aenvmixer envmixer;
    Aresample resample;
    Areverb reverb;
    Asavebuff savebuff;
    Asegment segment;
    Asetbuff setbuff;
    Asetvol setvol;
    Admemmove dmemmove;
    Aloadadpcm loadadpcm;
    Amixer mixer;
    Asetloop setloop;
    long long int force_union_align;
} Acmd;
typedef short ADPCM_STATE[16];
typedef short POLEF_STATE[4];
typedef short RESAMPLE_STATE[16];
typedef short ENVMIX_STATE[40];
typedef s32 OSPri;
typedef s32 OSId;
typedef union {
              struct {
                  f32 f_odd;
                  f32 f_even;
    } f;
              f64 d;
} __OSfp;
typedef struct {
              u64 at;
              u64 v0;
               u64 v1;
               u64 a0;
               u64 a1;
               u64 a2;
               u64 a3;
               u64 t0;
               u64 t1;
               u64 t2;
               u64 t3;
               u64 t4;
               u64 t5;
               u64 t6;
               u64 t7;
               u64 s0;
               u64 s1;
               u64 s2;
               u64 s3;
               u64 s4;
               u64 s5;
               u64 s6;
               u64 s7;
               u64 t8;
               u64 t9;
               u64 gp;
               u64 sp;
               u64 s8;
               u64 ra;
               u64 lo;
               u64 hi;
               u32 sr;
               u32 pc;
                u32 cause;
                u32 badvaddr;
                u32 rcp;
                u32 fpcsr;
                __OSfp fp0;
                __OSfp fp2;
                __OSfp fp4;
                __OSfp fp6;
                __OSfp fp8;
                __OSfp fp10;
                __OSfp fp12;
                __OSfp fp14;
                __OSfp fp16;
                __OSfp fp18;
                __OSfp fp20;
                __OSfp fp22;
                __OSfp fp24;
                __OSfp fp26;
                __OSfp fp28;
                __OSfp fp30;
} __OSThreadContext;
typedef struct OSThread_s {
              struct OSThread_s* next;
              OSPri priority;
              struct OSThread_s** queue;
              struct OSThread_s* tlnext;
               u16 state;
               u16 flags;
               OSId id;
               int fp;
               __OSThreadContext context;
} OSThread;
typedef u32 OSEvent;
typedef u32 OSIntMask;
typedef u32 OSPageMask;
typedef void* OSMesg;
typedef struct {
              OSThread* mtqueue;
              OSThread* fullqueue;
              s32 validCount;
              s32 first;
               s32 msgCount;
               OSMesg* msg;
} OSMesgQueue;
typedef struct {
              u32 errStatus;
              void* dramAddr;
              void* C2Addr;
              u32 sectorSize;
               u32 C1ErrNum;
               u32 C1ErrSector[4];
} __OSBlockInfo;
typedef struct {
              u32 cmdType;
              u16 transferMode;
              u16 blockNum;
              s32 sectorNum;
              u32 devAddr;
               u32 bmCtlShadow;
               u32 seqCtlShadow;
               __OSBlockInfo block[2];
} __OSTranxInfo;
typedef struct OSPiHandle_s {
              struct OSPiHandle_s* next;
              u8 type;
              u8 latency;
              u8 pageSize;
              u8 relDuration;
              u8 pulse;
              u8 domain;
              u32 baseAddress;
               u32 speed;
               __OSTranxInfo transferInfo;
} OSPiHandle;
typedef struct {
              u8 type;
              u32 address;
} OSPiInfo;
typedef struct {
              u16 type;
              u8 pri;
              u8 status;
              OSMesgQueue* retQueue;
} OSIoMesgHdr;
typedef struct {
              OSIoMesgHdr hdr;
              void* dramAddr;
              u32 devAddr;
               u32 size;
               OSPiHandle* piHandle;
} OSIoMesg;
typedef struct {
              s32 active;
              OSThread* thread;
              OSMesgQueue* cmdQueue;
              OSMesgQueue* evtQueue;
               OSMesgQueue* acsQueue;
               s32 (*dma)(void);
               s32 (*unk18)(void);
} OSDevMgr;
typedef struct {
              u32 ctrl;
              u32 width;
              u32 burst;
              u32 vSync;
               u32 hSync;
               u32 leap;
               u32 hStart;
               u32 xScale;
               u32 vCurrent;
} OSViCommonRegs;
typedef struct {
              u32 origin;
              u32 yScale;
              u32 vStart;
              u32 vBurst;
               u32 vIntr;
} OSViFieldRegs;
typedef struct {
              u8 type;
              OSViCommonRegs comRegs;
               OSViFieldRegs fldRegs[2];
} OSViMode;
typedef u64 OSTime;
typedef struct OSTimer_s {
              struct OSTimer_s* next;
              struct OSTimer_s* prev;
              OSTime interval;
               OSTime value;
               OSMesgQueue* mq;
               OSMesg msg;
} OSTimer;
typedef struct {
              u16 type;
              u8 status;
              u8 errno;
} OSContStatus;
typedef struct {
              u16 button;
              s8 stick_x;
              s8 stick_y;
              u8 errno;
} OSContPad;
typedef struct {
              void* address;
              u8 databuffer[32];
               u8 addressCrc;
               u8 dataCrc;
               u8 errno;
} OSContRamIo;
typedef struct {
              int status;
              OSMesgQueue* queue;
              int channel;
              u8 id[32];
               u8 label[32];
               int version;
               int dir_size;
               int inode_table;
               int minode_table;
               int dir_table;
               int inode_start_page;
               u8 banks;
               u8 activebank;
} OSPfs;
typedef struct {
              u32 file_size;
              u16 company_code;
              u16 game_code;
              unsigned char ext_name[4];
              unsigned char game_name[16];
} OSPfsState;
typedef struct {
              u16* histo_base;
              u32 histo_size;
              u32* text_start;
              u32* text_end;
} OSProf;
typedef struct {
              u32 type;
              u32 flags;
              u64* ucode_boot;
              u32 ucode_boot_size;
               u64* ucode;
               u32 ucode_size;
               u64* ucode_data;
               u32 ucode_data_size;
               u64* dram_stack;
               u32 dram_stack_size;
               u64* output_buff;
               u64* output_buff_size;
               u64* data_ptr;
               u32 data_size;
               u64* yield_data_ptr;
               u32 yield_data_size;
} OSTask_t;
typedef union {
              OSTask_t t;
              long long force_structure_alignment;
} OSTask;
typedef u32 OSYieldResult;
typedef struct {
              short type;
              unsigned char misc[30];
} OSScMsg;
typedef struct OSScTask_s {
              struct OSScTask_s* next;
              u32 state;
              u32 flags;
              void* framebuffer;
               OSTask list;
               OSMesgQueue* msgQ;
               OSMesg msg;
} OSScTask;
typedef struct OSScClient_s {
              struct OSScClient_s* next;
              OSMesgQueue* msgQ;
} OSScClient;
typedef struct {
              OSScMsg retraceMsg;
               OSScMsg prenmiMsg;
               OSMesgQueue interruptQ;
               OSMesg intBuf[8];
               OSMesgQueue cmdQ;
               OSMesg cmdMsgBuf[8];
               OSThread thread;
                OSScClient* clientList;
                OSScTask* audioListHead;
                OSScTask* gfxListHead;
                OSScTask* audioListTail;
                OSScTask* gfxListTail;
                OSScTask* curRSPTask;
                OSScTask* curRDPTask;
                u32 frameCount;
                s32 doAudio;
} OSSched;
typedef struct {
               u32 ramarray[15];
               u32 pifstatus;
} OSPifRam;
typedef struct {
              u8 dummy;
              u8 txsize;
              u8 rxsize;
              u8 cmd;
              u16 button;
              s8 stick_x;
              s8 stick_y;
} __OSContReadFormat;
typedef struct {
              u8 dummy;
              u8 txsize;
              u8 rxsize;
              u8 cmd;
              u8 typeh;
              u8 typel;
              u8 status;
              u8 dummy1;
} __OSContRequesFormat;
typedef struct {
               u8 dummy;
               u8 txsize;
               u8 rxsize;
               u8 cmd;
               u16 address;
               u8 data[32];
               u8 datacrc;
} __OSContRamReadFormat;
typedef struct {
               u16 company_code;
               u16 game_code;
               u8 start_page;
               u8 status;
               u16 data_sum;
               unsigned char ext_name[4];
               unsigned char game_name[16];
               s32 reserved;
} __OSDir;
typedef struct {
              u8 inode_page[256];
} __OSInode;
typedef char *va_list;
typedef void (*OSErrorHandler)( );
typedef struct {
              u32 magic;
              u32 len;
              u32* base;
              s32 startCount;
               s32 writeOffset;
} OSLog;
typedef struct {
              u32 magic;
              u32 timeStamp;
              u16 argCount;
              u16 eventID;
} OSLogItem;
typedef struct {
              u32 magic;
              u32 version;
} OSLogFileHdr;
typedef struct {
              OSMesgQueue* messageQueue;
              OSMesg message;
} __OSEventState;
typedef struct {
              OSThread* next;
              OSPri priority;
} __OSThreadTail;
typedef struct {
              f32 factor;
              u16 offset;
              u32 scale;
} __OSViScale;
typedef struct {
              u16 state;
              u16 retraceCount;
              void* framep;
              OSViMode* modep;
              u32 control;
               OSMesgQueue* msgq;
               OSMesg msg;
               __OSViScale x;
               __OSViScale y;
} __OSViContext;
typedef struct {
              unsigned char* base;
              int fmt;
              int siz;
              int xsize;
               int ysize;
               int lsize;
               int addr;
               int w;
               int h;
               int s;
               int t;
} Image;
typedef struct {
              float col[3];
              float pos[3];
               float a1;
               float a2;
} PositionalLight;
typedef union {
              struct {
                  unsigned int hi;
                  unsigned int lo;
    } word;
              double d;
} du;
typedef union {
              unsigned int i;
              float f;
} fu;
typedef float Matrix[4][4];
typedef struct {
              int quot;
              int rem;
} div_t;
typedef struct {
              long quot;
              long rem;
} ldiv_t;
typedef struct {
              long long quot;
              long long rem;
} lldiv_t;
typedef unsigned int size_t;
typedef int ssize_t;
typedef long wchar_t;
typedef double ldouble;
typedef struct {
              union {
                  long long ll;
                  ldouble ld;
    } v;
              unsigned char* s;
              int n0;
               int nz0;
               int n1;
               int nz1;
               int n2;
               int nz2;
               int prec;
               int width;
               size_t nchar;
               unsigned int flags;
               unsigned char qual;
} _Pft;
typedef struct {
              u8 red;
              u8 green;
              u8 blue;
              u8 alpha;
} ColorRGBA8;
typedef struct {
              u8 red;
              u8 green;
              u8 blue;
} RGB;
typedef struct {
              u8 red;
              u8 green;
              u8 blue;
              u8 alpha;
} RGBA8;
typedef struct {
    u32 cont: 1;
    u32 type: 4;
    u32 offset: 11;
    s32 value: 16;
} InitChainEntry;
typedef enum {
              ICHAINTYPE_U8,
              ICHAINTYPE_S8,
              ICHAINTYPE_U16,
              ICHAINTYPE_S16,
              ICHAINTYPE_U32,
              ICHAINTYPE_S32,
              ICHAINTYPE_F32,
              ICHAINTYPE_F32_DIV1000,
              ICHAINTYPE_VEC3F,
              ICHAINTYPE_VEC3F_DIV1000,
              ICHAINTYPE_VEC3S
} InitChainType;
typedef struct {
               f32 x;
               f32 y;
} Vec2f;
typedef struct {
               f32 x;
               f32 y;
               f32 z;
} Vec3f;
typedef struct {
               u16 x;
               u16 y;
               u16 z;
} Vec3us;
typedef struct {
               s16 x;
               s16 y;
               s16 z;
} Vec3s;
typedef struct {
               s32 x;
               s32 y;
               s32 z;
} Vec3i;
typedef struct {
               Vec3s center;
               s16 radius;
} Sphere16;
typedef struct {
               Vec3f center;
               f32 radius;
} Spheref;
typedef struct {
               Vec3f normal;
               f32 originDist;
} Plane;
typedef struct {
               Vec3f vtx[3];
               Plane plane;
} TriNorm;
typedef struct {
               s16 radius;
               s16 height;
               s16 yShift;
               Vec3s pos;
} Cylinder16;
typedef struct {
               f32 radius;
               f32 height;
               f32 yShift;
               Vec3f pos;
} Cylinderf;
typedef struct {
               Vec3f point;
               Vec3f dir;
} InfiniteLine;
typedef struct {
               Vec3f a;
               Vec3f b;
} LineSegment;
typedef struct {
               f32 r;
               s16 pitch;
               s16 yaw;
} VecSph;
typedef struct {
               u32 vromAddr;
               void* dramAddr;
               u32 size;
               char* filename;
               s32 line;
               s32 unk14;
               OSMesgQueue* notifyQueue;
               OSMesg notifyMsg;
} DmaRequest;
typedef struct {
               u32 vromStart;
               u32 vromEnd;
               u32 romStart;
               u32 romEnd;
} DmaEntry;
struct GlobalContext;
struct Actor;
typedef struct SkelAnime SkelAnime;
typedef struct {
                Vec3s translation;
                u8 firstChildIndex;
                u8 nextLimbIndex;
                Gfx* displayLists[1];
} SkelLimbEntry;
typedef struct {
                SkelLimbEntry* limbs[1];
} Skeleton;
typedef struct {
                Skeleton* skeletonSeg;
                u8 limbCount;
                char unk05[3];
                u8 dListCount;
} SkeletonHeader;
typedef s16 AnimationRotationValue;
typedef struct {
                u16 x;
                u16 y;
                u16 z;
} AnimationRotationIndex;
typedef struct {
                s16 frameCount;
                s16 unk02;
} GenericAnimationHeader;
typedef struct {
                GenericAnimationHeader genericHeader;
                u32 rotationValueSeg;
                u32 rotationIndexSeg;
                u16 limit;
} AnimationHeader;
typedef enum {
    ANIMATION_LINKANIMETION,
    ANIMATION_TYPE1,
    ANIMATION_TYPE2,
    ANIMATION_TYPE3,
    ANIMATION_TYPE4,
    ANIMATION_TYPE5
} AnimationType;
typedef struct {
                DmaRequest req;
                OSMesgQueue msgQueue;
                OSMesg msg;
} AnimationEntryType0;
typedef struct {
                u8 unk00;
                u8 vecCount;
                Vec3s* dst;
                Vec3s* src;
} AnimationEntryType1;
typedef struct {
                u8 unk00;
                u8 limbCount;
                Vec3s* unk04;
                Vec3s* unk08;
                f32 unk0C;
} AnimationEntryType2;
typedef struct {
                u8 unk00;
                u8 vecCount;
                Vec3s* dst;
                Vec3s* src;
                u8* index;
} AnimationEntryType3;
typedef struct {
                u8 unk00;
                u8 vecCount;
                char unk02[0x2];
                Vec3s* dst;
                Vec3s* src;
                u8* index;
} AnimationEntryType4;
typedef struct {
                struct Actor* actor;
                SkelAnime* skelAnime;
                f32 unk08;
} AnimationEntryType5;
typedef struct {
                u8 raw[0x3C];
} AnimationEntryRaw;
typedef union {
    AnimationEntryRaw raw;
    AnimationEntryType0 type0;
    AnimationEntryType1 type1;
    AnimationEntryType2 type2;
    AnimationEntryType3 type3;
    AnimationEntryType4 type4;
    AnimationEntryType5 type5;
} AnimationEntryType;
typedef struct {
                u8 type;
                u8 unk01;
                AnimationEntryType types;
} AnimationEntry;
typedef struct AnimationContext {
                s16 animationCount;
                char unk02[2];
                AnimationEntry entries[50];
} AnimationContext;
typedef struct {
                GenericAnimationHeader genericHeader;
                u32 animationSegAddress;
} LinkAnimetionEntry;
struct SkelAnime {
               u8 limbCount;
               u8 mode;
               u8 dListCount;
               s8 unk03;
               Skeleton* skeleton;
    union {
        AnimationHeader* animCurrentSeg;
        LinkAnimetionEntry* linkAnimetionSeg;
        GenericAnimationHeader* genericSeg;
    };
               f32 initialFrame;
               f32 animFrameCount;
               f32 totalFrames;
               f32 animCurrentFrame;
               f32 animPlaybackSpeed;
               Vec3s* limbDrawTbl;
               Vec3s* transitionDrawTbl;
               f32 transCurrentFrame;
               f32 transitionStep;
               s32 (*animUpdate)();
               s8 initFlags;
               u8 flags;
               s16 prevFrameRot;
               Vec3s prevFramePos;
               Vec3s unk3E;
};
typedef s32 (*OverrideLimbDraw)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                struct Actor* actor);
typedef void (*PostLimbDraw)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot,
                             struct Actor* actor);
typedef s32 (*OverrideLimbDraw2)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 struct Actor* actor, Gfx** gfx);
typedef void (*PostLimbDraw2)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot,
                              struct Actor* actor, Gfx** gfx);
typedef s32 (*OverrideLimbDrawSV)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                  struct Actor* actor);
typedef void (*PostLimbDrawSV)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList1, Gfx** dList2, Vec3s* rot,
                               struct Actor* actor);
typedef void (*UnkActorDraw)(struct GlobalContext* globalCtx, s32 limbIndex, struct Actor* actor);
typedef void (*AnimationEntryCallback)(struct GlobalContext*, AnimationEntryType*);
extern u32 link_animetion_segment;
typedef struct {
                 u16 unk00;
                 s16 unk02;
                 s16 unk04;
                 s16 unk06;
                 f32 unk08;
} TransformData;
typedef struct {
                 u8* refIndex;
                 TransformData* transformData;
                 s16* copyValues;
                 s16 unk0C;
                 s16 unk10;
} TransformUpdateIndex;
typedef struct {
                 u8 firstChildIdx;
                 u8 nextLimbIdx;
                 Gfx* dList[2];
} SkelCurveLimb;
typedef struct {
                 SkelCurveLimb** limbs;
                 u8 limbCount;
} SkelCurveLimbList;
typedef struct {
                 Vec3s scale;
                 Vec3s rot;
                 Vec3s pos;
} LimbTransform;
typedef struct {
                 u8 limbCount;
                 SkelCurveLimb** limbList;
                 TransformUpdateIndex* transUpdIdx;
                 f32 unk0C;
                 f32 animFinalFrame;
                 f32 animSpeed;
                 f32 animCurFrame;
                 LimbTransform* transforms;
} SkelAnimeCurve;
typedef s32 (*OverrideCurveLimbDraw)(struct GlobalContext* globalCtx, SkelAnimeCurve* skelCuve, s32 limbIndex,
                                     struct Actor* actor);
typedef void (*PostCurveLimbDraw)(struct GlobalContext* globalCtx, SkelAnimeCurve* skelCuve, s32 limbIndex,
                                  struct Actor* actor);
struct Actor;
typedef struct {
               struct Actor* actor;
               struct Actor* at;
               struct Actor* ac;
               struct Actor* oc;
               u8 atFlags;
               u8 acFlags;
               u8 ocFlags1;
               u8 ocFlags2;
               u8 colType;
               u8 shape;
} Collider;
typedef struct {
               u8 colType;
               u8 atFlags;
               u8 acFlags;
               u8 ocFlags1;
               u8 ocFlags2;
               u8 shape;
} ColliderInit;
typedef struct {
               u8 colType;
               u8 atFlags;
               u8 acFlags;
               u8 ocFlags1;
               u8 shape;
} ColliderInitType1;
typedef struct {
               struct Actor* actor;
               u8 atFlags;
               u8 acFlags;
               u8 ocFlags1;
               u8 shape;
} ColliderInitToActor;
typedef struct {
               u32 dmgFlags;
               u8 effect;
               u8 damage;
} ColliderTouch;
typedef struct {
               u32 dmgFlags;
               u8 effect;
               u8 damage;
} ColliderTouchInit;
typedef struct {
               u32 dmgFlags;
               u8 effect;
               u8 defense;
               Vec3s hitPos;
} ColliderBump;
typedef struct {
               u32 dmgFlags;
               u8 effect;
               u8 defense;
} ColliderBumpInit;
typedef struct ColliderInfo {
               ColliderTouch toucher;
               ColliderBump bumper;
               u8 elemType;
               u8 toucherFlags;
               u8 bumperFlags;
               u8 ocElemFlags;
               Collider* atHit;
               Collider* acHit;
               struct ColliderInfo* atHitInfo;
               struct ColliderInfo* acHitInfo;
} ColliderInfo;
typedef struct {
               u8 elemType;
               ColliderTouchInit toucher;
               ColliderBumpInit bumper;
               u8 toucherFlags;
               u8 bumperFlags;
               u8 ocElemFlags;
} ColliderInfoInit;
typedef struct {
               Sphere16 modelSphere;
               Sphere16 worldSphere;
               f32 scale;
               u8 limb;
} ColliderJntSphElementDim;
typedef struct {
               u8 limb;
               Sphere16 modelSphere;
               s16 scale;
} ColliderJntSphElementDimInit;
typedef struct {
               ColliderInfo info;
               ColliderJntSphElementDim dim;
} ColliderJntSphElement;
typedef struct {
               ColliderInfoInit info;
               ColliderJntSphElementDimInit dim;
} ColliderJntSphElementInit;
typedef struct {
               Collider base;
               s32 count;
               ColliderJntSphElement* elements;
} ColliderJntSph;
typedef struct {
              ColliderInit base;
              s32 count;
              ColliderJntSphElementInit* elements;
} ColliderJntSphInit;
typedef struct {
               ColliderInitType1 base;
               s32 count;
               ColliderJntSphElementInit* elements;
} ColliderJntSphInitType1;
typedef struct {
               ColliderInitToActor base;
               s32 count;
               ColliderJntSphElementInit* elements;
} ColliderJntSphInitToActor;
typedef struct {
               Collider base;
               ColliderInfo info;
               Cylinder16 dim;
} ColliderCylinder;
typedef struct {
               ColliderInit base;
               ColliderInfoInit info;
               Cylinder16 dim;
} ColliderCylinderInit;
typedef struct {
               ColliderInitType1 base;
               ColliderInfoInit info;
               Cylinder16 dim;
} ColliderCylinderInitType1;
typedef struct {
               ColliderInitToActor base;
               ColliderInfoInit info;
               Cylinder16 dim;
} ColliderCylinderInitToActor;
typedef struct {
               Vec3f vtx[3];
} ColliderTrisElementDimInit;
typedef struct {
               ColliderInfo info;
               TriNorm dim;
} ColliderTrisElement;
typedef struct {
               ColliderInfoInit info;
               ColliderTrisElementDimInit dim;
} ColliderTrisElementInit;
typedef struct {
               Collider base;
               s32 count;
               ColliderTrisElement* elements;
} ColliderTris;
typedef struct {
              ColliderInit base;
              s32 count;
              ColliderTrisElementInit* elements;
} ColliderTrisInit;
typedef struct {
               ColliderInitType1 base;
               s32 count;
               ColliderTrisElementInit* elements;
} ColliderTrisInitType1;
typedef struct {
               Vec3f quad[4];
               Vec3s dcMid;
               Vec3s baMid;
               f32 acDist;
} ColliderQuadDim;
typedef struct {
               Vec3f quad[4];
} ColliderQuadDimInit;
typedef struct {
               Collider base;
               ColliderInfo info;
               ColliderQuadDim dim;
} ColliderQuad;
typedef struct {
               ColliderInit base;
               ColliderInfoInit info;
               ColliderQuadDimInit dim;
} ColliderQuadInit;
typedef struct {
               ColliderInitType1 base;
               ColliderInfoInit info;
               ColliderQuadDimInit dim;
} ColliderQuadInitType1;
typedef struct {
               Collider base;
               ColliderInfo info;
               ColliderJntSphElementDim dim;
} ColliderSphere;
typedef struct {
               ColliderInit base;
               ColliderInfoInit info;
               ColliderJntSphElementDimInit dim;
} ColliderSphereInit;
typedef struct {
               LineSegment line;
               u16 ocFlags;
} OcLine;
typedef struct {
                s16 colATCount;
                u16 sacFlags;
                Collider* colAT[50];
                s32 colACCount;
                Collider* colAC[60];
                s32 colOCCount;
                Collider* colOC[50];
                s32 colLineCount;
                OcLine* colLine[3];
} CollisionCheckContext;
typedef struct {
            u8 blood;
            u8 effect;
} HitInfo;
typedef enum {
            BLOOD_NONE,
            BLOOD_BLUE,
            BLOOD_GREEN,
            BLOOD_WATER,
            BLOOD_RED,
            BLOOD_RED2
} ColChkBloodType;
typedef enum {
            HIT_WHITE,
            HIT_DUST,
            HIT_RED,
            HIT_SOLID,
            HIT_WOOD,
            HIT_NONE
} ColChkHitType;
typedef enum {
            MASSTYPE_IMMOVABLE,
            MASSTYPE_HEAVY,
            MASSTYPE_NORMAL
} ColChkMassType;
typedef enum {
             COLTYPE_HIT0,
             COLTYPE_HIT1,
             COLTYPE_HIT2,
             COLTYPE_HIT3,
             COLTYPE_HIT4,
             COLTYPE_HIT5,
             COLTYPE_HIT6,
             COLTYPE_HIT7,
             COLTYPE_HIT8,
             COLTYPE_METAL,
             COLTYPE_NONE,
             COLTYPE_WOOD,
             COLTYPE_HARD,
             COLTYPE_TREE
} ColliderType;
typedef enum {
            COLSHAPE_JNTSPH,
            COLSHAPE_CYLINDER,
            COLSHAPE_TRIS,
            COLSHAPE_QUAD,
            COLSHAPE_SPHERE,
            COLSHAPE_MAX
} ColliderShape;
typedef enum {
            ELEMTYPE_UNK0,
            ELEMTYPE_UNK1,
            ELEMTYPE_UNK2,
            ELEMTYPE_UNK3,
            ELEMTYPE_UNK4,
            ELEMTYPE_UNK5,
            ELEMTYPE_UNK6,
            ELEMTYPE_UNK7
} ElementType;
struct Actor;
struct GlobalContext;
struct LightMapper;
struct BgPolygon;
typedef void(*ActorFunc)(struct Actor* this, struct GlobalContext* ctxt);
typedef struct {
               Vec3f pos;
               Vec3s rot;
} PosRot;
typedef struct {
               u8 attack[32];
} DamageTable;
typedef struct {
               u8 health;
               s16 cylRadius;
               s16 cylHeight;
               u8 mass;
} CollisionCheckInfoInit;
typedef struct {
               u8 health;
               s16 cylRadius;
               s16 cylHeight;
               s16 cylYShift;
               u8 mass;
} CollisionCheckInfoInit2;
typedef struct {
               DamageTable* damageTable;
               Vec3f displacement;
               s16 cylRadius;
               s16 cylHeight;
               s16 cylYShift;
               u8 mass;
               u8 health;
               u8 damage;
               u8 damageEffect;
               u8 atHitEffect;
               u8 acHitEffect;
} CollisionCheckInfo;
typedef struct {
               s32 unk0;
               s32 unk4;
               f32 unk8;
               f32 unkC;
               f32 unk10;
               f32 unk14;
               f32 unk18;
               f32 unk1C;
               f32 unk20;
               f32 unk24;
               f32 unk28;
               f32 unk2C;
               s16 unk30;
               s16 unk32;
               s16 unk34;
               s16 unk36;
               s16 unk38;
               s16 unk3A;
} ActorEnTest20C;
typedef struct {
               s16 id;
               u8 type;
               u32 flags;
               s16 objectId;
               u32 instanceSize;
               ActorFunc init;
               ActorFunc destroy;
               ActorFunc update;
               ActorFunc draw;
} ActorInit;
typedef enum {
    ALLOCTYPE_NORMAL,
    ALLOCTYPE_ABSOLUTE,
    ALLOCTYPE_PERMANENT
} AllocType;
typedef struct {
               u32 vromStart;
               u32 vromEnd;
               void* vramStart;
               void* vramEnd;
               void* loadedRamAddr;
               ActorInit* initInfo;
               char* name;
               u16 allocType;
               s8 nbLoaded;
               s8 pad1F[0x1];
} ActorOverlay;
typedef void(*ActorShadowFunc)(struct Actor* actor, struct LightMapper* mapper, struct GlobalContext* ctxt);
typedef struct {
               Vec3s rot;
               s16 face;
               f32 yOffset;
               ActorShadowFunc shadowDraw;
               f32 shadowScale;
               u8 shadowAlpha;
               u8 feetFloorFlags;
               Vec3f feetPos[2];
} ActorShape;
typedef struct Actor {
                s16 id;
                u8 category;
                s8 room;
                u32 flags;
                PosRot home;
                s16 params;
                s8 objBankIndex;
                s8 targetMode;
                u16 unk20;
                PosRot world;
                s8 cutscene;
                s8 unk39;
                PosRot focus;
                u16 sfx;
                f32 targetArrowOffset;
                Vec3f scale;
                Vec3f velocity;
                f32 speedXZ;
                f32 gravity;
                f32 minVelocityY;
                struct BgPolygon* wallPoly;
                struct BgPolygon* floorPoly;
                u8 wallBgId;
                u8 floorBgId;
                s16 wallYaw;
                f32 floorHeight;
                f32 yDistToWater;
                u16 bgCheckFlags;
                s16 yawTowardsPlayer;
                f32 xyzDistToPlayerSq;
                f32 xzDistToPlayer;
                f32 yDistToPlayer;
                CollisionCheckInfo colChkInfo;
                ActorShape shape;
                Vec3f projectedPos;
                f32 projectedW;
                f32 uncullZoneForward;
                f32 uncullZoneScale;
                f32 uncullZoneDownward;
                Vec3f prevPos;
                u8 isTargeted;
                u8 targetPriority;
                u16 textId;
                u16 freezeTimer;
                u16 colorFilterParams;
                u8 colorFilterTimer;
                u8 isDrawn;
                u8 dropFlag;
                u8 hintId;
                struct Actor* parent;
                struct Actor* child;
                struct Actor* prev;
                struct Actor* next;
                ActorFunc init;
                ActorFunc destroy;
                ActorFunc update;
                ActorFunc draw;
                ActorOverlay* overlayEntry;
} Actor;
typedef enum {
            FOOT_LEFT,
            FOOT_RIGHT
} ActorFootIndex;
typedef struct {
                Actor actor;
                s32 bgId;
                f32 unk148;
                f32 unk14C;
                s16 unk150;
                u16 unk152;
                u32 unk154;
                u8 unk_158;
                s16 pad15A;
} DynaPolyActor;
typedef struct {
                Actor base;
                s8 pad144[0x3];
                s8 itemActionParam;
                s8 pad148[0x2];
                s8 heldItemActionParam;
                u8 unk14B;
                s8 pad14C[0x5];
                u8 unk151;
                s8 unk152;
                u8 unk153;
                s8 pad154[0x1F8];
                Actor* heldActor;
                s8 pad350[0x18];
                Vec3f unk368;
                s8 pad374[0x20];
                u8 unk394;
                s8 pad395[0x37];
                s16 unk3CC;
                s8 unk3CE;
                s8 pad3CF[0x361];
                Actor* unk730;
                s8 pad734[0x338];
                u32 stateFlags1;
                u32 unkA70;
                u32 unkA74;
                s8 padA78[0x8];
                Actor* unkA80;
                s8 padA84[0x4];
                Actor* unkA88;
                f32 unkA8C;
                s8 padA90[0x44];
                s16 unkAD4;
                s8 padAD6[0x8];
                u8 unkADE;
                s8 padADF[0x4];
                s8 unkAE3;
                s8 padAE4[0x44];
                s16 unkB28;
                s8 padB2A[0x72];
                Vec3f unkB9C;
                s8 padBA8[0x1D0];
} ActorPlayer;
typedef struct {
                Actor base;
                ActorFunc update;
                s16 collectibleFlagId;
                s16 unk14A;
                s16 unk14C;
                s16 unk14E;
                s16 unk150;
                s16 unk152;
                f32 unk154;
                ColliderCylinder collision;
                s8 pad1A4[0x4];
} ActorEnItem00;
typedef struct {
                Actor base;
                ActorFunc update;
                ColliderCylinder collision;
                s8 pad194[0x14];
} ActorEnAObj;
typedef enum {
               ACTORCAT_SWITCH,
               ACTORCAT_BG,
               ACTORCAT_PLAYER,
               ACTORCAT_EXPLOSIVES,
               ACTORCAT_NPC,
               ACTORCAT_ENEMY,
               ACTORCAT_PROP,
               ACTORCAT_ITEMACTION,
               ACTORCAT_MISC,
               ACTORCAT_BOSS,
               ACTORCAT_DOOR,
               ACTORCAT_CHEST
} ActorType;
typedef struct {
               AnimationHeader* animation;
               f32 playSpeed;
               f32 startFrame;
               f32 frameCount;
               u8 mode;
               f32 morphFrames;
} ActorAnimationEntry;
typedef enum {
                ACTOR_PLAYER,
                ACTOR_EN_TEST,
                ACTOR_EN_GIRLA,
                ACTOR_EN_PART,
                ACTOR_EN_LIGHT,
                ACTOR_EN_DOOR,
                ACTOR_EN_BOX,
                ACTOR_EN_PAMETFROG,
                ACTOR_EN_OKUTA,
                ACTOR_EN_BOM,
                ACTOR_EN_WALLMAS,
                ACTOR_EN_DODONGO,
                ACTOR_EN_FIREFLY,
                ACTOR_EN_HORSE,
                ACTOR_EN_ITEM00,
                ACTOR_EN_ARROW,
                ACTOR_EN_ELF,
                ACTOR_EN_NIW,
                ACTOR_EN_TITE,
                ACTOR_UNSET_13,
                ACTOR_EN_PEEHAT,
                ACTOR_EN_BUTTE,
                ACTOR_EN_INSECT,
                ACTOR_EN_FISH,
                ACTOR_EN_HOLL,
                ACTOR_EN_DINOFOS,
                ACTOR_EN_HATA,
                ACTOR_EN_ZL1,
                ACTOR_EN_VIEWER,
                ACTOR_EN_BUBBLE,
                ACTOR_DOOR_SHUTTER,
                ACTOR_UNSET_1F,
                ACTOR_EN_BOOM,
                ACTOR_EN_TORCH2,
                ACTOR_EN_MINIFROG,
                ACTOR_UNSET_23,
                ACTOR_EN_ST,
                ACTOR_UNSET_25,
                ACTOR_EN_A_OBJ,
                ACTOR_OBJ_WTURN,
                ACTOR_EN_RIVER_SOUND,
                ACTOR_UNSET_29,
                ACTOR_EN_OSSAN,
                ACTOR_UNSET_2B,
                ACTOR_UNSET_2C,
                ACTOR_EN_FAMOS,
                ACTOR_UNSET_2E,
                ACTOR_EN_BOMBF,
                ACTOR_UNSET_30,
                ACTOR_UNSET_31,
                ACTOR_EN_AM,
                ACTOR_EN_DEKUBABA,
                ACTOR_EN_M_FIRE1,
                ACTOR_EN_M_THUNDER,
                ACTOR_BG_BREAKWALL,
                ACTOR_UNSET_37,
                ACTOR_DOOR_WARP1,
                ACTOR_OBJ_SYOKUDAI,
                ACTOR_ITEM_B_HEART,
                ACTOR_EN_DEKUNUTS,
                ACTOR_EN_BBFALL,
                ACTOR_ARMS_HOOK,
                ACTOR_EN_BB,
                ACTOR_BG_KEIKOKU_SPR,
                ACTOR_UNSET_40,
                ACTOR_EN_WOOD02,
                ACTOR_UNSET_42,
                ACTOR_EN_DEATH,
                ACTOR_EN_MINIDEATH,
                ACTOR_UNSET_45,
                ACTOR_UNSET_46,
                ACTOR_EN_VM,
                ACTOR_DEMO_EFFECT,
                ACTOR_DEMO_KANKYO,
                ACTOR_EN_FLOORMAS,
                ACTOR_UNSET_4B,
                ACTOR_EN_RD,
                ACTOR_BG_F40_FLIFT,
                ACTOR_UNSET_4E,
                ACTOR_OBJ_MURE,
                ACTOR_EN_SW,
                ACTOR_OBJECT_KANKYO,
                ACTOR_UNSET_52,
                ACTOR_UNSET_53,
                ACTOR_EN_HORSE_LINK_CHILD,
                ACTOR_DOOR_ANA,
                ACTOR_UNSET_56,
                ACTOR_UNSET_57,
                ACTOR_UNSET_58,
                ACTOR_UNSET_59,
                ACTOR_UNSET_5A,
                ACTOR_EN_ENCOUNT1,
                ACTOR_DEMO_TRE_LGT,
                ACTOR_UNSET_5D,
                ACTOR_UNSET_5E,
                ACTOR_EN_ENCOUNT2,
                ACTOR_EN_FIRE_ROCK,
                ACTOR_BG_CTOWER_ROT,
                ACTOR_MIR_RAY,
                ACTOR_UNSET_63,
                ACTOR_EN_SB,
                ACTOR_EN_BIGSLIME,
                ACTOR_EN_KAREBABA,
                ACTOR_EN_IN,
                ACTOR_UNSET_68,
                ACTOR_EN_RU,
                ACTOR_EN_BOM_CHU,
                ACTOR_EN_HORSE_GAME_CHECK,
                ACTOR_EN_RR,
                ACTOR_UNSET_6D,
                ACTOR_UNSET_6E,
                ACTOR_UNSET_6F,
                ACTOR_UNSET_70,
                ACTOR_UNSET_71,
                ACTOR_UNSET_72,
                ACTOR_EN_FR,
                ACTOR_UNSET_74,
                ACTOR_UNSET_75,
                ACTOR_UNSET_76,
                ACTOR_UNSET_77,
                ACTOR_UNSET_78,
                ACTOR_UNSET_79,
                ACTOR_OBJ_OSHIHIKI,
                ACTOR_EFF_DUST,
                ACTOR_BG_UMAJUMP,
                ACTOR_ARROW_FIRE,
                ACTOR_ARROW_ICE,
                ACTOR_ARROW_LIGHT,
                ACTOR_ITEM_ETCETERA,
                ACTOR_OBJ_KIBAKO,
                ACTOR_OBJ_TSUBO,
                ACTOR_UNSET_83,
                ACTOR_EN_IK,
                ACTOR_UNSET_85,
                ACTOR_UNSET_86,
                ACTOR_UNSET_87,
                ACTOR_UNSET_88,
                ACTOR_DEMO_SHD,
                ACTOR_EN_DNS,
                ACTOR_ELF_MSG,
                ACTOR_EN_HONOTRAP,
                ACTOR_EN_TUBO_TRAP,
                ACTOR_OBJ_ICE_POLY,
                ACTOR_EN_FZ,
                ACTOR_EN_KUSA,
                ACTOR_OBJ_BEAN,
                ACTOR_OBJ_BOMBIWA,
                ACTOR_OBJ_SWITCH,
                ACTOR_UNSET_94,
                ACTOR_OBJ_LIFT,
                ACTOR_OBJ_HSBLOCK,
                ACTOR_EN_OKARINA_TAG,
                ACTOR_UNSET_98,
                ACTOR_EN_GOROIWA,
                ACTOR_UNSET_9A,
                ACTOR_UNSET_9B,
                ACTOR_EN_DAIKU,
                ACTOR_EN_NWC,
                ACTOR_ITEM_INBOX,
                ACTOR_EN_GE1,
                ACTOR_OBJ_BLOCKSTOP,
                ACTOR_EN_SDA,
                ACTOR_EN_CLEAR_TAG,
                ACTOR_UNSET_A3,
                ACTOR_EN_GM,
                ACTOR_EN_MS,
                ACTOR_EN_HS,
                ACTOR_BG_INGATE,
                ACTOR_EN_KANBAN,
                ACTOR_UNSET_A9,
                ACTOR_EN_ATTACK_NIW,
                ACTOR_UNSET_AB,
                ACTOR_UNSET_AC,
                ACTOR_UNSET_AD,
                ACTOR_EN_MK,
                ACTOR_EN_OWL,
                ACTOR_EN_ISHI,
                ACTOR_OBJ_HANA,
                ACTOR_OBJ_LIGHTSWITCH,
                ACTOR_OBJ_MURE2,
                ACTOR_UNSET_B4,
                ACTOR_EN_FU,
                ACTOR_UNSET_B6,
                ACTOR_UNSET_B7,
                ACTOR_EN_STREAM,
                ACTOR_EN_MM,
                ACTOR_UNSET_BA,
                ACTOR_UNSET_BB,
                ACTOR_EN_WEATHER_TAG,
                ACTOR_EN_ANI,
                ACTOR_UNSET_BE,
                ACTOR_EN_JS,
                ACTOR_UNSET_C0,
                ACTOR_UNSET_C1,
                ACTOR_UNSET_C2,
                ACTOR_UNSET_C3,
                ACTOR_EN_OKARINA_EFFECT,
                ACTOR_EN_MAG,
                ACTOR_ELF_MSG2,
                ACTOR_BG_F40_SWLIFT,
                ACTOR_UNSET_C8,
                ACTOR_UNSET_C9,
                ACTOR_EN_KAKASI,
                ACTOR_OBJ_MAKEOSHIHIKI,
                ACTOR_OCEFF_SPOT,
                ACTOR_UNSET_CD,
                ACTOR_EN_TORCH,
                ACTOR_UNSET_CF,
                ACTOR_SHOT_SUN,
                ACTOR_UNSET_D1,
                ACTOR_UNSET_D2,
                ACTOR_OBJ_ROOMTIMER,
                ACTOR_EN_SSH,
                ACTOR_UNSET_D5,
                ACTOR_OCEFF_WIPE,
                ACTOR_OCEFF_STORM,
                ACTOR_OBJ_DEMO,
                ACTOR_EN_MINISLIME,
                ACTOR_EN_NUTSBALL,
                ACTOR_UNSET_DB,
                ACTOR_UNSET_DC,
                ACTOR_UNSET_DD,
                ACTOR_UNSET_DE,
                ACTOR_OCEFF_WIPE2,
                ACTOR_OCEFF_WIPE3,
                ACTOR_UNSET_E1,
                ACTOR_EN_DG,
                ACTOR_EN_SI,
                ACTOR_OBJ_COMB,
                ACTOR_OBJ_KIBAKO2,
                ACTOR_UNSET_E6,
                ACTOR_EN_HS2,
                ACTOR_OBJ_MURE3,
                ACTOR_EN_TG,
                ACTOR_UNSET_EA,
                ACTOR_UNSET_EB,
                ACTOR_EN_WF,
                ACTOR_EN_SKB,
                ACTOR_UNSET_EE,
                ACTOR_EN_GS,
                ACTOR_OBJ_SOUND,
                ACTOR_EN_CROW,
                ACTOR_UNSET_F2,
                ACTOR_EN_COW,
                ACTOR_UNSET_F4,
                ACTOR_UNSET_F5,
                ACTOR_OCEFF_WIPE4,
                ACTOR_UNSET_F7,
                ACTOR_EN_ZO,
                ACTOR_OBJ_MAKEKINSUTA,
                ACTOR_EN_GE3,
                ACTOR_UNSET_FB,
                ACTOR_OBJ_HAMISHI,
                ACTOR_EN_ZL4,
                ACTOR_EN_MM2,
                ACTOR_UNSET_FF,
                ACTOR_DOOR_SPIRAL,
                ACTOR_UNSET_101,
                ACTOR_OBJ_PZLBLOCK,
                ACTOR_OBJ_TOGE,
                ACTOR_UNSET_104,
                ACTOR_OBJ_ARMOS,
                ACTOR_OBJ_BOYO,
                ACTOR_UNSET_107,
                ACTOR_UNSET_108,
                ACTOR_EN_GRASSHOPPER,
                ACTOR_UNSET_10A,
                ACTOR_OBJ_GRASS,
                ACTOR_OBJ_GRASS_CARRY,
                ACTOR_OBJ_GRASS_UNIT,
                ACTOR_UNSET_10E,
                ACTOR_UNSET_10F,
                ACTOR_BG_FIRE_WALL,
                ACTOR_EN_BU,
                ACTOR_EN_ENCOUNT3,
                ACTOR_EN_JSO,
                ACTOR_OBJ_CHIKUWA,
                ACTOR_EN_KNIGHT,
                ACTOR_EN_WARP_TAG,
                ACTOR_EN_AOB_01,
                ACTOR_EN_BOJ_01,
                ACTOR_EN_BOJ_02,
                ACTOR_EN_BOJ_03,
                ACTOR_EN_ENCOUNT4,
                ACTOR_EN_BOM_BOWL_MAN,
                ACTOR_EN_SYATEKI_MAN,
                ACTOR_UNSET_11E,
                ACTOR_BG_ICICLE,
                ACTOR_EN_SYATEKI_CROW,
                ACTOR_EN_BOJ_04,
                ACTOR_EN_CNE_01,
                ACTOR_EN_BBA_01,
                ACTOR_EN_BJI_01,
                ACTOR_BG_SPDWEB,
                ACTOR_UNSET_126,
                ACTOR_UNSET_127,
                ACTOR_EN_MT_TAG,
                ACTOR_BOSS_01,
                ACTOR_BOSS_02,
                ACTOR_BOSS_03,
                ACTOR_BOSS_04,
                ACTOR_BOSS_05,
                ACTOR_BOSS_06,
                ACTOR_BOSS_07,
                ACTOR_BG_DY_YOSEIZO,
                ACTOR_UNSET_131,
                ACTOR_EN_BOJ_05,
                ACTOR_UNSET_133,
                ACTOR_UNSET_134,
                ACTOR_EN_SOB1,
                ACTOR_UNSET_136,
                ACTOR_UNSET_137,
                ACTOR_EN_GO,
                ACTOR_UNSET_139,
                ACTOR_EN_RAF,
                ACTOR_OBJ_FUNEN,
                ACTOR_OBJ_RAILLIFT,
                ACTOR_BG_NUMA_HANA,
                ACTOR_OBJ_FLOWERPOT,
                ACTOR_OBJ_SPINYROLL,
                ACTOR_DM_HINA,
                ACTOR_EN_SYATEKI_WF,
                ACTOR_OBJ_SKATEBLOCK,
                ACTOR_OBJ_ICEBLOCK,
                ACTOR_EN_BIGPAMET,
                ACTOR_EN_SYATEKI_DEKUNUTS,
                ACTOR_ELF_MSG3,
                ACTOR_EN_FG,
                ACTOR_DM_RAVINE,
                ACTOR_DM_SA,
                ACTOR_EN_SLIME,
                ACTOR_EN_PR,
                ACTOR_OBJ_TOUDAI,
                ACTOR_OBJ_ENTOTU,
                ACTOR_OBJ_BELL,
                ACTOR_EN_SYATEKI_OKUTA,
                ACTOR_UNSET_150,
                ACTOR_OBJ_SHUTTER,
                ACTOR_DM_ZL,
                ACTOR_EN_ELFGRP,
                ACTOR_DM_TSG,
                ACTOR_EN_BAGUO,
                ACTOR_OBJ_VSPINYROLL,
                ACTOR_OBJ_SMORK,
                ACTOR_EN_TEST2,
                ACTOR_EN_TEST3,
                ACTOR_EN_TEST4,
                ACTOR_EN_BAT,
                ACTOR_EN_SEKIHI,
                ACTOR_EN_WIZ,
                ACTOR_EN_WIZ_BROCK,
                ACTOR_EN_WIZ_FIRE,
                ACTOR_EFF_CHANGE,
                ACTOR_DM_STATUE,
                ACTOR_OBJ_FIRESHIELD,
                ACTOR_BG_LADDER,
                ACTOR_EN_MKK,
                ACTOR_DEMO_GETITEM,
                ACTOR_UNSET_166,
                ACTOR_EN_DNB,
                ACTOR_EN_DNH,
                ACTOR_EN_DNK,
                ACTOR_EN_DNQ,
                ACTOR_UNSET_16B,
                ACTOR_BG_KEIKOKU_SAKU,
                ACTOR_OBJ_HUGEBOMBIWA,
                ACTOR_EN_FIREFLY2,
                ACTOR_EN_RAT,
                ACTOR_EN_WATER_EFFECT,
                ACTOR_EN_KUSA2,
                ACTOR_BG_SPOUT_FIRE,
                ACTOR_UNSET_173,
                ACTOR_BG_DBLUE_MOVEBG,
                ACTOR_EN_DY_EXTRA,
                ACTOR_EN_BAL,
                ACTOR_EN_GINKO_MAN,
                ACTOR_EN_WARP_UZU,
                ACTOR_OBJ_DRIFTICE,
                ACTOR_EN_LOOK_NUTS,
                ACTOR_EN_MUSHI2,
                ACTOR_EN_FALL,
                ACTOR_EN_MM3,
                ACTOR_BG_CRACE_MOVEBG,
                ACTOR_EN_DNO,
                ACTOR_EN_PR2,
                ACTOR_EN_PRZ,
                ACTOR_EN_JSO2,
                ACTOR_OBJ_ETCETERA,
                ACTOR_EN_EGOL,
                ACTOR_OBJ_MINE,
                ACTOR_OBJ_PURIFY,
                ACTOR_EN_TRU,
                ACTOR_EN_TRT,
                ACTOR_UNSET_189,
                ACTOR_UNSET_18A,
                ACTOR_EN_TEST5,
                ACTOR_EN_TEST6,
                ACTOR_EN_AZ,
                ACTOR_EN_ESTONE,
                ACTOR_BG_HAKUGIN_POST,
                ACTOR_DM_OPSTAGE,
                ACTOR_DM_STK,
                ACTOR_DM_CHAR00,
                ACTOR_DM_CHAR01,
                ACTOR_DM_CHAR02,
                ACTOR_DM_CHAR03,
                ACTOR_DM_CHAR04,
                ACTOR_DM_CHAR05,
                ACTOR_DM_CHAR06,
                ACTOR_DM_CHAR07,
                ACTOR_DM_CHAR08,
                ACTOR_DM_CHAR09,
                ACTOR_OBJ_TOKEIDAI,
                ACTOR_UNSET_19D,
                ACTOR_EN_MNK,
                ACTOR_EN_EGBLOCK,
                ACTOR_EN_GUARD_NUTS,
                ACTOR_BG_HAKUGIN_BOMBWALL,
                ACTOR_OBJ_TOKEI_TOBIRA,
                ACTOR_BG_HAKUGIN_ELVPOLE,
                ACTOR_EN_MA4,
                ACTOR_EN_TWIG,
                ACTOR_EN_PO_FUSEN,
                ACTOR_EN_DOOR_ETC,
                ACTOR_EN_BIGOKUTA,
                ACTOR_BG_ICEFLOE,
                ACTOR_OBJ_OCARINALIFT,
                ACTOR_EN_TIME_TAG,
                ACTOR_BG_OPEN_SHUTTER,
                ACTOR_BG_OPEN_SPOT,
                ACTOR_BG_FU_KAITEN,
                ACTOR_OBJ_AQUA,
                ACTOR_EN_ELFORG,
                ACTOR_EN_ELFBUB,
                ACTOR_UNSET_1B2,
                ACTOR_EN_FU_MATO,
                ACTOR_EN_FU_KAGO,
                ACTOR_EN_OSN,
                ACTOR_BG_CTOWER_GEAR,
                ACTOR_EN_TRT2,
                ACTOR_OBJ_TOKEI_STEP,
                ACTOR_BG_LOTUS,
                ACTOR_EN_KAME,
                ACTOR_OBJ_TAKARAYA_WALL,
                ACTOR_BG_FU_MIZU,
                ACTOR_EN_SELLNUTS,
                ACTOR_BG_DKJAIL_IVY,
                ACTOR_UNSET_1BF,
                ACTOR_OBJ_VISIBLOCK,
                ACTOR_EN_TAKARAYA,
                ACTOR_EN_TSN,
                ACTOR_EN_DS2N,
                ACTOR_EN_FSN,
                ACTOR_EN_SHN,
                ACTOR_UNSET_1C6,
                ACTOR_EN_STOP_HEISHI,
                ACTOR_OBJ_BIGICICLE,
                ACTOR_EN_LIFT_NUTS,
                ACTOR_EN_TK,
                ACTOR_UNSET_1CB,
                ACTOR_BG_MARKET_STEP,
                ACTOR_OBJ_LUPYGAMELIFT,
                ACTOR_EN_TEST7,
                ACTOR_OBJ_LIGHTBLOCK,
                ACTOR_MIR_RAY2,
                ACTOR_EN_WDHAND,
                ACTOR_EN_GAMELUPY,
                ACTOR_BG_DANPEI_MOVEBG,
                ACTOR_EN_SNOWWD,
                ACTOR_EN_PM,
                ACTOR_EN_GAKUFU,
                ACTOR_ELF_MSG4,
                ACTOR_ELF_MSG5,
                ACTOR_EN_COL_MAN,
                ACTOR_EN_TALK_GIBUD,
                ACTOR_EN_GIANT,
                ACTOR_OBJ_SNOWBALL,
                ACTOR_BOSS_HAKUGIN,
                ACTOR_EN_GB2,
                ACTOR_EN_ONPUMAN,
                ACTOR_BG_TOBIRA01,
                ACTOR_EN_TAG_OBJ,
                ACTOR_OBJ_DHOUSE,
                ACTOR_OBJ_HAKAISI,
                ACTOR_BG_HAKUGIN_SWITCH,
                ACTOR_UNSET_1E5,
                ACTOR_EN_SNOWMAN,
                ACTOR_TG_SW,
                ACTOR_EN_PO_SISTERS,
                ACTOR_EN_PP,
                ACTOR_EN_HAKUROCK,
                ACTOR_EN_HANABI,
                ACTOR_OBJ_DOWSING,
                ACTOR_OBJ_WIND,
                ACTOR_EN_RACEDOG,
                ACTOR_EN_KENDO_JS,
                ACTOR_BG_BOTIHASIRA,
                ACTOR_EN_FISH2,
                ACTOR_EN_PST,
                ACTOR_EN_POH,
                ACTOR_OBJ_SPIDERTENT,
                ACTOR_EN_ZORAEGG,
                ACTOR_EN_KBT,
                ACTOR_EN_GG,
                ACTOR_EN_MARUTA,
                ACTOR_OBJ_SNOWBALL2,
                ACTOR_EN_GG2,
                ACTOR_OBJ_GHAKA,
                ACTOR_EN_DNP,
                ACTOR_EN_DAI,
                ACTOR_BG_GORON_OYU,
                ACTOR_EN_KGY,
                ACTOR_EN_INVADEPOH,
                ACTOR_EN_GK,
                ACTOR_EN_AN,
                ACTOR_UNSET_203,
                ACTOR_EN_BEE,
                ACTOR_EN_OT,
                ACTOR_EN_DRAGON,
                ACTOR_OBJ_DORA,
                ACTOR_EN_BIGPO,
                ACTOR_OBJ_KENDO_KANBAN,
                ACTOR_OBJ_HARIKO,
                ACTOR_EN_STH,
                ACTOR_BG_SINKAI_KABE,
                ACTOR_BG_HAKA_CURTAIN,
                ACTOR_BG_KIN2_BOMBWALL,
                ACTOR_BG_KIN2_FENCE,
                ACTOR_BG_KIN2_PICTURE,
                ACTOR_BG_KIN2_SHELF,
                ACTOR_EN_RAIL_SKB,
                ACTOR_EN_JG,
                ACTOR_EN_TRU_MT,
                ACTOR_OBJ_UM,
                ACTOR_EN_NEO_REEBA,
                ACTOR_BG_MBAR_CHAIR,
                ACTOR_BG_IKANA_BLOCK,
                ACTOR_BG_IKANA_MIRROR,
                ACTOR_BG_IKANA_ROTARYROOM,
                ACTOR_BG_DBLUE_BALANCE,
                ACTOR_BG_DBLUE_WATERFALL,
                ACTOR_EN_KAIZOKU,
                ACTOR_EN_GE2,
                ACTOR_EN_MA_YTS,
                ACTOR_EN_MA_YTO,
                ACTOR_OBJ_TOKEI_TURRET,
                ACTOR_BG_DBLUE_ELEVATOR,
                ACTOR_OBJ_WARPSTONE,
                ACTOR_EN_ZOG,
                ACTOR_OBJ_ROTLIFT,
                ACTOR_OBJ_JG_GAKKI,
                ACTOR_BG_INIBS_MOVEBG,
                ACTOR_EN_ZOT,
                ACTOR_OBJ_TREE,
                ACTOR_OBJ_Y2LIFT,
                ACTOR_OBJ_Y2SHUTTER,
                ACTOR_OBJ_BOAT,
                ACTOR_OBJ_TARU,
                ACTOR_OBJ_HUNSUI,
                ACTOR_EN_JC_MATO,
                ACTOR_MIR_RAY3,
                ACTOR_EN_ZOB,
                ACTOR_ELF_MSG6,
                ACTOR_OBJ_NOZOKI,
                ACTOR_EN_TOTO,
                ACTOR_EN_RAILGIBUD,
                ACTOR_EN_BABA,
                ACTOR_EN_SUTTARI,
                ACTOR_EN_ZOD,
                ACTOR_EN_KUJIYA,
                ACTOR_EN_GEG,
                ACTOR_OBJ_KINOKO,
                ACTOR_OBJ_YASI,
                ACTOR_EN_TANRON1,
                ACTOR_EN_TANRON2,
                ACTOR_EN_TANRON3,
                ACTOR_OBJ_CHAN,
                ACTOR_EN_ZOS,
                ACTOR_EN_S_GORO,
                ACTOR_EN_NB,
                ACTOR_EN_JA,
                ACTOR_BG_F40_BLOCK,
                ACTOR_BG_F40_SWITCH,
                ACTOR_EN_PO_COMPOSER,
                ACTOR_EN_GURUGURU,
                ACTOR_OCEFF_WIPE5,
                ACTOR_EN_STONE_HEISHI,
                ACTOR_OCEFF_WIPE6,
                ACTOR_EN_SCOPENUTS,
                ACTOR_EN_SCOPECROW,
                ACTOR_OCEFF_WIPE7,
                ACTOR_EFF_KAMEJIMA_WAVE,
                ACTOR_EN_HG,
                ACTOR_EN_HGO,
                ACTOR_EN_ZOV,
                ACTOR_EN_AH,
                ACTOR_OBJ_HGDOOR,
                ACTOR_BG_IKANA_BOMBWALL,
                ACTOR_BG_IKANA_RAY,
                ACTOR_BG_IKANA_SHUTTER,
                ACTOR_BG_HAKA_BOMBWALL,
                ACTOR_BG_HAKA_TOMB,
                ACTOR_EN_SC_RUPPE,
                ACTOR_BG_IKNV_DOUKUTU,
                ACTOR_BG_IKNV_OBJ,
                ACTOR_EN_PAMERA,
                ACTOR_OBJ_HSSTUMP,
                ACTOR_EN_HIDDEN_NUTS,
                ACTOR_EN_ZOW,
                ACTOR_EN_TALK,
                ACTOR_EN_AL,
                ACTOR_EN_TAB,
                ACTOR_EN_NIMOTSU,
                ACTOR_EN_HIT_TAG,
                ACTOR_EN_RUPPECROW,
                ACTOR_EN_TANRON4,
                ACTOR_EN_TANRON5,
                ACTOR_EN_TANRON6,
                ACTOR_EN_DAIKU2,
                ACTOR_EN_MUTO,
                ACTOR_EN_BAISEN,
                ACTOR_EN_HEISHI,
                ACTOR_EN_DEMO_HEISHI,
                ACTOR_EN_DT,
                ACTOR_EN_CHA,
                ACTOR_OBJ_DINNER,
                ACTOR_EFF_LASTDAY,
                ACTOR_BG_IKANA_DHARMA,
                ACTOR_EN_AKINDONUTS,
                ACTOR_EFF_STK,
                ACTOR_EN_IG,
                ACTOR_EN_RG,
                ACTOR_EN_OSK,
                ACTOR_EN_STH2,
                ACTOR_EN_YB,
                ACTOR_EN_RZ,
                ACTOR_EN_SCOPECOIN,
                ACTOR_EN_BJT,
                ACTOR_EN_BOMJIMA,
                ACTOR_EN_BOMJIMB,
                ACTOR_EN_BOMBERS,
                ACTOR_EN_BOMBERS2,
                ACTOR_EN_BOMBAL,
                ACTOR_OBJ_MOON_STONE,
                ACTOR_OBJ_MU_PICT,
                ACTOR_BG_IKNINSIDE,
                ACTOR_EFF_ZORABAND,
                ACTOR_OBJ_KEPN_KOYA,
                ACTOR_OBJ_USIYANE,
                ACTOR_EN_NNH,
                ACTOR_OBJ_KZSAKU,
                ACTOR_OBJ_MILK_BIN,
                ACTOR_EN_KITAN,
                ACTOR_BG_ASTR_BOMBWALL,
                ACTOR_BG_IKNIN_SUSCEIL,
                ACTOR_EN_BSB,
                ACTOR_EN_RECEPGIRL,
                ACTOR_EN_THIEFBIRD,
                ACTOR_EN_JGAME_TSN,
                ACTOR_OBJ_JGAME_LIGHT,
                ACTOR_OBJ_YADO,
                ACTOR_DEMO_SYOTEN,
                ACTOR_DEMO_MOONEND,
                ACTOR_BG_LBFSHOT,
                ACTOR_BG_LAST_BWALL,
                ACTOR_EN_AND,
                ACTOR_EN_INVADEPOH_DEMO,
                ACTOR_OBJ_DANPEILIFT,
                ACTOR_EN_FALL2,
                ACTOR_DM_AL,
                ACTOR_DM_AN,
                ACTOR_DM_AH,
                ACTOR_DM_NB,
                ACTOR_EN_DRS,
                ACTOR_EN_ENDING_HERO,
                ACTOR_DM_BAL,
                ACTOR_EN_PAPER,
                ACTOR_EN_HINT_SKB,
                ACTOR_DM_TAG,
                ACTOR_EN_BH,
                ACTOR_EN_ENDING_HERO2,
                ACTOR_EN_ENDING_HERO3,
                ACTOR_EN_ENDING_HERO4,
                ACTOR_EN_ENDING_HERO5,
                ACTOR_EN_ENDING_HERO6,
                ACTOR_DM_GM,
                ACTOR_OBJ_SWPRIZE,
                ACTOR_EN_INVISIBLE_RUPPE,
                ACTOR_OBJ_ENDING,
                ACTOR_EN_RSN,
                ACTOR_ID_MAX
} ActorID;
typedef struct {
               u16 unk0;
               u16 startFrame;
               u16 endFrame;
               s8 pad6[0x2A];
} CsCmdActorAction;
typedef struct {
              u16 base;
              u16 startFrame;
              u16 endFrame;
} CsCmdBase;
typedef struct {
              u16 unk0;
              u16 startFrame;
              u16 endFrame;
              u8 hour;
              u8 minute;
} CsCmdDayTime;
typedef struct {
              u16 setting;
              u16 startFrame;
              u16 endFrame;
} CsCmdEnvLighting;
typedef struct {
              u16 sequence;
              u16 startFrame;
              u16 endFrame;
} CsCmdMusicChange;
typedef struct {
              u16 type;
              u16 startFrame;
              u16 endFrame;
} CsCmdMusicFade;
typedef struct {
              u16 base;
              u16 startFrame;
              u16 endFrame;
              u16 type;
              u16 textId1;
              u16 textId2;
} CsCmdTextbox;
typedef struct {
              u16 unk0;
              u16 startFrame;
              u16 endFrame;
              u8 unk6;
              u8 unk7;
              u8 unk8;
              s8 pad9[0x3];
} CsCmdUnk190;
typedef struct {
              s32 unk0;
              s32 unk4;
} CsCmdUnk5A;
typedef struct {
              u16 unk0;
              u16 startFrame;
              u16 endFrame;
              u8 unk6;
              u8 unk7;
              u8 unk8;
              s8 pad9[0x3];
} CsCmdUnk9B;
typedef struct {
              u8 type;
              u16 params[6];
} LightInfo;
typedef struct z_Light_t {
              LightInfo* info;
              struct z_Light_t* prev;
              struct z_Light_t* next;
} z_Light;
typedef struct {
              z_Light* lightsHead;
              u8 ambientRed;
              u8 ambientGreen;
              u8 ambientBlue;
              u8 unk7;
              u8 unk8;
              u8 unk9;
              s16 unkA;
              s16 unkC;
} LightingContext;
typedef struct {
                s32 numOccupied;
                s32 nextFree;
                z_Light lights[32];
} LightsList;
typedef struct {
              s8 dirX;
              s8 dirY;
              s8 dirZ;
              u8 red;
              u8 green;
              u8 blue;
              u16 pad[3];
} LightInfoDirectionalParams;
typedef struct {
              s16 posX;
              s16 posY;
              s16 posZ;
              u8 red;
              u8 green;
              u8 blue;
              u8 unk9;
              s16 radius;
} LightInfoPositionalParams;
typedef struct {
               u8 enablePosLights;
               u8 numLights;
               s8 pad2[6];
               Lights7 lights;
} LightMapper;
typedef struct {
              u8 type;
              LightInfoDirectionalParams params;
} LightInfoDirectional;
typedef struct {
              u8 type;
              LightInfoPositionalParams params;
} LightInfoPositional;
struct GraphicsContext;
struct GlobalContext;
typedef void(*eff_destroy_func)(void* params);
typedef void(*eff_draw_func)(void* params, struct GraphicsContext* gCtxt);
typedef void(*eff_init_func)(void* params, void* init);
typedef s32(*eff_update_func)(void* params);
typedef struct {
              u8 active;
              u8 unk1;
              u8 unk2;
              s8 pad3[0x1];
} EffCommon;
typedef struct {
               Vec3f velocity;
               Vec3f position;
               Vec3s unk18;
               Vec3s unk1E;
} EffSparkParticle;
typedef struct {
                Vec3s position;
                s32 numParticles;
                EffSparkParticle particles[32];
                f32 velocity;
                f32 gravity;
                u32 particleFactor1;
                u32 particleFactor2;
                ColorRGBA8 colorStart[4];
                ColorRGBA8 colorEnd[4];
                s32 age;
                s32 duration;
} EffSparkParams;
typedef struct {
                EffCommon base;
                EffSparkParams params;
} EffSpark;
typedef struct {
               s8 pad0[0x18];
} EffBlureParticle;
typedef struct {
                s8 pad0[0x184];
                ColorRGBA8 unk184;
                ColorRGBA8 unk188;
                ColorRGBA8 unk18C;
                ColorRGBA8 unk190;
                s8 pad194[0xC];
} EffBlureInit1;
typedef struct {
               s8 pad0[0x8];
               ColorRGBA8 unk8;
               ColorRGBA8 unkC;
               ColorRGBA8 unk10;
               ColorRGBA8 unk14;
               s8 pad18[0xC];
} EffBlureInit2;
typedef struct {
                EffBlureParticle particles[16];
                s8 pad180[0x4];
                f32 unk184;
                u16 unk188;
                s8 pad18A[0x4];
                ColorRGBA8 unk18E;
                ColorRGBA8 unk192;
                ColorRGBA8 unk196;
                ColorRGBA8 unk19A;
                u8 unk19E;
                u8 unk19F;
                u8 unk1A0;
                u8 unk1A1;
                s8 pad1A2[0xA];
} EffBlureParams;
typedef struct {
                EffCommon base;
                EffBlureParams params;
} EffBlure;
typedef struct {
               f32 startSpeed;
               f32 endXChange;
               f32 endX;
               f32 startXChange;
               f32 startX;
               s16 rotationY;
               s16 rotationZ;
} EffShieldParticleParticle;
typedef struct {
               u8 numParticles;
               Vec3s position;
               ColorRGBA8 primColorStart;
               ColorRGBA8 envColorStart;
               ColorRGBA8 primColorMid;
               ColorRGBA8 envColorMid;
               ColorRGBA8 primColorEnd;
               ColorRGBA8 envColorEnd;
               f32 acceleration;
               f32 maxInitialSpeed;
               f32 lengthCutoff;
               u8 duration;
               LightInfoPositionalParams lightParams;
               s32 hasLight;
} EffShieldParticleInit;
typedef struct {
                EffShieldParticleParticle particles[16];
                u8 numParticles;
                s8 pad181[0x1];
                Vec3s position;
                ColorRGBA8 primColorStart;
                ColorRGBA8 envColorStart;
                ColorRGBA8 primColorMid;
                ColorRGBA8 envColorMid;
                ColorRGBA8 primColorEnd;
                ColorRGBA8 envColorEnd;
                f32 acceleration;
                s8 pad1A4[0x4];
                f32 maxInitialSpeed;
                f32 lengthCutoff;
                u8 duration;
                u8 age;
                LightInfo lightInfo;
                z_Light* light;
                s32 hasLight;
} EffShieldParticleParams;
typedef struct {
                EffCommon base;
                EffShieldParticleParams params;
} EffShieldParticle;
typedef struct {
               s16 active;
               Vec3s position1;
               Vec3s position2;
               s16 life;
               s8 pad10[0x4];
               s32 unk14;
} EffTireMarkParticle;
typedef struct {
              s16 unk0;
              s16 maxLife;
              ColorRGBA8 color;
} EffTireMarkInit;
typedef struct {
                EffTireMarkParticle particles[64];
                s16 unk600;
                s16 numParticles;
                s16 maxLife;
                ColorRGBA8 color;
                s8 pad60A[0x2];
} EffTireMarkParams;
typedef struct {
                EffCommon base;
                EffTireMarkParams params;
} EffTireMark;
typedef struct {
               u32 paramsSize;
               eff_init_func init;
               eff_destroy_func destroy;
               eff_update_func update;
               eff_draw_func draw;
} EffInfo;
typedef struct {
                 struct GlobalContext* ctxt;
                 EffSpark sparks[3];
                 EffBlure blures[25];
                 EffShieldParticle shieldParticles[3];
                 EffTireMark tireMarks[15];
} EffTables;
typedef struct {
               Vec3f position;
               Vec3f velocity;
               Vec3f acceleration;
               ColorRGBA8 color1;
               ColorRGBA8 color2;
               s16 scale;
               s16 scaleChangePerFrame;
               s16 life;
               u16 flags;
               u8 type;
} EffectDustInit;
typedef struct LoadedParticleEntry LoadedParticleEntry;
typedef void(*effect_func)(struct GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle);
typedef void(*effect_init_func)(struct GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle, void* init);
struct LoadedParticleEntry {
               Vec3f position;
               Vec3f velocity;
               Vec3f acceleration;
               effect_func update;
               effect_func draw;
               Vec3f unk2C;
               u32 displayList;
               s32 unk3C;
               s16 regs[13];
               u16 flags;
               s16 life;
               u8 priority;
               u8 type;
};
typedef struct {
              LoadedParticleEntry* data_table;
              s32 searchIndex;
              s32 size;
} EffectTableInfo;
typedef struct {
              s32 unk0;
              effect_init_func init;
} ParticleOverlayInfo;
typedef struct {
               u32 vromStart;
               u32 vromEnd;
               void* vramStart;
               void* vramEnd;
               void* loadedRamAddr;
               ParticleOverlayInfo* overlayInfo;
               u32 unk18;
} ParticleOverlay;
typedef enum EffectSSType {
    EFFECT_SS2_TYPE_DUST = 0x0,
    EFFECT_SS2_TYPE_SPARKLE = 0x1,
    EFFECT_SS2_TYPE_DELETED_2 = 0x2,
    EFFECT_SS2_TYPE_BOMB2 = 0x3,
    EFFECT_SS2_TYPE_BLAST = 0x4,
    EFFECT_SS2_TYPE_G_SPARK = 0x5,
    EFFECT_SS2_TYPE_DODONGO_FIRE = 0x6,
    EFFECT_SS2_TYPE_BUBBLE = 0x7,
    EFFECT_SS2_TYPE_DELETED_8 = 0x8,
    EFFECT_SS2_TYPE_G_RIPPLE = 0x9,
    EFFECT_SS2_TYPE_G_SPLASH = 0xA,
    EFFECT_SS2_TYPE_DELETED_B = 0xB,
    EFFECT_SS2_TYPE_G_FIRE = 0xC,
    EFFECT_SS2_TYPE_LIGHTNING = 0xD,
    EFFECT_SS2_TYPE_BIG_OCTO_BUBBLE = 0xE,
    EFFECT_SS2_TYPE_FRAGMENT = 0xF,
    EFFECT_SS2_TYPE_STICK = 0x10,
    EFFECT_SS2_TYPE_SPLASH = 0x11,
    EFFECT_SS2_TYPE_DELETED_12 = 0x12,
    EFFECT_SS2_TYPE_DELETED_13 = 0x13,
    EFFECT_SS2_TYPE_STONE1 = 0x14,
    EFFECT_SS2_TYPE_HIT_MARK = 0x15,
    EFFECT_SS2_TYPE_PHANTOM_GANON_FLASH = 0x16,
    EFFECT_SS2_TYPE_KAKARIKO_FIRE = 0x17,
    EFFECT_SS2_TYPE_SOLDIER_SEARCH_BALL = 0x18,
    EFFECT_SS2_TYPE_SHARD = 0x19,
    EFFECT_SS2_TYPE_ICE_PIECE = 0x1A,
    EFFECT_SS2_TYPE_ENEMY_ICE = 0x1B,
    EFFECT_SS2_TYPE_FIRE_TAIL = 0x1C,
    EFFECT_SS2_TYPE_ENEMY_FIRE = 0x1D,
    EFFECT_SS2_TYPE_EXTRA = 0x1E,
    EFFECT_SS2_TYPE_DELETED_1F = 0x1F,
    EFFECT_SS2_TYPE_DEAD_DEKU_BABA = 0x20,
    EFFECT_SS2_TYPE_DEAD_DODONGO = 0x21,
    EFFECT_SS2_TYPE_DEAD_DEKU_SCRUB = 0x22,
    EFFECT_SS2_TYPE_DELETED_23 = 0x23,
    EFFECT_SS2_TYPE_ICE_SMOKE = 0x24,
    EFFECT_SS2_TYPE_ICE_BLOCK = 0x25,
    EFFECT_SS2_TYPE_SBN = 0x26,
    EFFECT_SS2_TYPE_LAST_LABEL = 0x27
} EffectSSType;
typedef enum {
                OBJECT_UNSET_0,
                GAMEPLAY_KEEP,
                GAMEPLAY_FIELD_KEEP,
                GAMEPLAY_DANGEON_KEEP,
                OBJECT_NB,
                OBJECT_OKUTA,
                OBJECT_CROW,
                OBJECT_AH,
                OBJECT_DY_OBJ,
                OBJECT_WALLMASTER,
                OBJECT_DODONGO,
                OBJECT_FIREFLY,
                OBJECT_BOX,
                OBJECT_AL,
                OBJECT_BUBBLE,
                OBJECT_NIW,
                OBJECT_LINK_BOY,
                OBJECT_LINK_CHILD,
                OBJECT_TITE,
                OBJECT_TAB,
                OBJECT_PH,
                OBJECT_AND,
                OBJECT_MSMO,
                OBJECT_DINOFOS,
                OBJECT_DRS,
                OBJECT_ZL1,
                OBJECT_AN4,
                OBJECT_UNSET_1B,
                OBJECT_TEST3,
                OBJECT_FAMOS,
                OBJECT_UNSET_1E,
                OBJECT_UNSET_1F,
                OBJECT_ST,
                OBJECT_UNSET_21,
                OBJECT_THIEFBIRD,
                OBJECT_UNSET_23,
                OBJECT_UNSET_24,
                OBJECT_UNSET_25,
                OBJECT_UNSET_26,
                OBJECT_UNSET_27,
                OBJECT_UNSET_28,
                OBJECT_UNSET_29,
                OBJECT_BOMBF,
                OBJECT_UNSET_2B,
                OBJECT_UNSET_2C,
                OBJECT_UNSET_2D,
                OBJECT_UNSET_2E,
                OBJECT_UNSET_2F,
                OBJECT_AM,
                OBJECT_DEKUBABA,
                OBJECT_UNSET_32,
                OBJECT_UNSET_33,
                OBJECT_UNSET_34,
                OBJECT_UNSET_35,
                OBJECT_UNSET_36,
                OBJECT_UNSET_37,
                OBJECT_UNSET_38,
                OBJECT_UNSET_39,
                OBJECT_UNSET_3A,
                OBJECT_UNSET_3B,
                OBJECT_UNSET_3C,
                OBJECT_UNSET_3D,
                OBJECT_WARP1,
                OBJECT_B_HEART,
                OBJECT_DEKUNUTS,
                OBJECT_UNSET_41,
                OBJECT_UNSET_42,
                OBJECT_UNSET_43,
                OBJECT_UNSET_44,
                OBJECT_UNSET_45,
                OBJECT_UNSET_46,
                OBJECT_UNSET_47,
                OBJECT_UNSET_48,
                OBJECT_UNSET_49,
                OBJECT_UNSET_4A,
                OBJECT_UNSET_4B,
                OBJECT_UNSET_4C,
                OBJECT_UNSET_4D,
                OBJECT_UNSET_4E,
                OBJECT_UNSET_4F,
                OBJECT_UNSET_50,
                OBJECT_BB,
                OBJECT_DEATH,
                OBJECT_UNSET_53,
                OBJECT_UNSET_54,
                OBJECT_UNSET_55,
                OBJECT_UNSET_56,
                OBJECT_UNSET_57,
                OBJECT_UNSET_58,
                OBJECT_UNSET_59,
                OBJECT_UNSET_5A,
                OBJECT_UNSET_5B,
                OBJECT_F40_OBJ,
                OBJECT_PO_COMPOSER,
                OBJECT_UNSET_5E,
                OBJECT_HATA,
                OBJECT_UNSET_60,
                OBJECT_WOOD02,
                OBJECT_UNSET_62,
                OBJECT_UNSET_63,
                OBJECT_TRAP,
                OBJECT_UNSET_65,
                OBJECT_UNSET_66,
                OBJECT_UNSET_67,
                OBJECT_UNSET_68,
                OBJECT_UNSET_69,
                OBJECT_VM,
                OBJECT_UNSET_6B,
                OBJECT_UNSET_6C,
                OBJECT_UNSET_6D,
                OBJECT_UNSET_6E,
                OBJECT_UNSET_6F,
                OBJECT_EFC_STAR_FIELD,
                OBJECT_UNSET_71,
                OBJECT_UNSET_72,
                OBJECT_UNSET_73,
                OBJECT_UNSET_74,
                OBJECT_RD,
                OBJECT_YUKIMURA_OBJ,
                OBJECT_HEAVY_OBJECT,
                OBJECT_UNSET_78,
                OBJECT_UNSET_79,
                OBJECT_UNSET_7A,
                OBJECT_UNSET_7B,
                OBJECT_UNSET_7C,
                OBJECT_HORSE_LINK_CHILD,
                OBJECT_UNSET_7E,
                OBJECT_UNSET_7F,
                OBJECT_SYOKUDAI,
                OBJECT_UNSET_81,
                OBJECT_UNSET_82,
                OBJECT_UNSET_83,
                OBJECT_EFC_TW,
                OBJECT_UNSET_85,
                OBJECT_GI_KEY,
                OBJECT_MIR_RAY,
                OBJECT_CTOWER_ROT,
                OBJECT_UNSET_89,
                OBJECT_BDOOR,
                OBJECT_UNSET_8B,
                OBJECT_UNSET_8C,
                OBJECT_UNSET_8D,
                OBJECT_SB,
                OBJECT_GI_MELODY,
                OBJECT_GI_HEART,
                OBJECT_GI_COMPASS,
                OBJECT_GI_BOSSKEY,
                OBJECT_UNSET_93,
                OBJECT_GI_NUTS,
                OBJECT_UNSET_95,
                OBJECT_GI_HEARTS,
                OBJECT_GI_ARROWCASE,
                OBJECT_GI_BOMBPOUCH,
                OBJECT_IN,
                OBJECT_UNSET_9A,
                OBJECT_UNSET_9B,
                OBJECT_UNSET_9C,
                OBJECT_OS_ANIME,
                OBJECT_GI_BOTTLE,
                OBJECT_GI_STICK,
                OBJECT_GI_MAP,
                OBJECT_OF1D_MAP,
                OBJECT_RU2,
                OBJECT_UNSET_A3,
                OBJECT_GI_MAGICPOT,
                OBJECT_GI_BOMB_1,
                OBJECT_UNSET_A6,
                OBJECT_MA2,
                OBJECT_GI_PURSE,
                OBJECT_UNSET_A9,
                OBJECT_UNSET_AA,
                OBJECT_RR,
                OBJECT_UNSET_AC,
                OBJECT_UNSET_AD,
                OBJECT_UNSET_AE,
                OBJECT_GI_ARROW,
                OBJECT_GI_BOMB_2,
                OBJECT_UNSET_B1,
                OBJECT_UNSET_B2,
                OBJECT_GI_SHIELD_2,
                OBJECT_GI_HOOKSHOT,
                OBJECT_GI_OCARINA,
                OBJECT_GI_MILK,
                OBJECT_MA1,
                OBJECT_UNSET_B8,
                OBJECT_UNSET_B9,
                OBJECT_UNSET_BA,
                OBJECT_NY,
                OBJECT_FR,
                OBJECT_UNSET_BD,
                OBJECT_UNSET_BE,
                OBJECT_GI_BOW,
                OBJECT_GI_GLASSES,
                OBJECT_GI_LIQUID,
                OBJECT_ANI,
                OBJECT_GI_SHIELD_3,
                OBJECT_UNSET_C4,
                OBJECT_UNSET_C5,
                OBJECT_GI_BEAN,
                OBJECT_GI_FISH,
                OBJECT_UNSET_C8,
                OBJECT_UNSET_C9,
                OBJECT_UNSET_CA,
                OBJECT_GI_LONGSWORD,
                OBJECT_UNSET_CC,
                OBJECT_UNSET_CD,
                OBJECT_UNSET_CE,
                OBJECT_UNSET_CF,
                OBJECT_ZO,
                OBJECT_UNSET_D1,
                OBJECT_UMAJUMP,
                OBJECT_UNSET_D3,
                OBJECT_UNSET_D4,
                OBJECT_MASTERGOLON,
                OBJECT_MASTERZOORA,
                OBJECT_AOB,
                OBJECT_IK,
                OBJECT_AHG,
                OBJECT_CNE,
                OBJECT_UNSET_DB,
                OBJECT_UNSET_DC,
                OBJECT_AN3,
                OBJECT_BJI,
                OBJECT_BBA,
                OBJECT_AN2,
                OBJECT_UNSET_E1,
                OBJECT_AN1,
                OBJECT_BOJ,
                OBJECT_FZ,
                OBJECT_BOB,
                OBJECT_GE1,
                OBJECT_YABUSAME_POINT,
                OBJECT_UNSET_E8,
                OBJECT_UNSET_E9,
                OBJECT_UNSET_EA,
                OBJECT_UNSET_EB,
                OBJECT_D_HSBLOCK,
                OBJECT_D_LIFT,
                OBJECT_MAMENOKI,
                OBJECT_GOROIWA,
                OBJECT_TORYO,
                OBJECT_DAIKU,
                OBJECT_NWC,
                OBJECT_GM,
                OBJECT_MS,
                OBJECT_HS,
                OBJECT_UNSET_F6,
                OBJECT_LIGHTSWITCH,
                OBJECT_KUSA,
                OBJECT_TSUBO,
                OBJECT_UNSET_FA,
                OBJECT_UNSET_FB,
                OBJECT_KANBAN,
                OBJECT_OWL,
                OBJECT_MK,
                OBJECT_FU,
                OBJECT_GI_KI_TAN_MASK,
                OBJECT_UNSET_101,
                OBJECT_GI_MASK18,
                OBJECT_GI_RABIT_MASK,
                OBJECT_GI_TRUTH_MASK,
                OBJECT_UNSET_105,
                OBJECT_STREAM,
                OBJECT_MM,
                OBJECT_UNSET_108,
                OBJECT_UNSET_109,
                OBJECT_UNSET_10A,
                OBJECT_UNSET_10B,
                OBJECT_UNSET_10C,
                OBJECT_UNSET_10D,
                OBJECT_UNSET_10E,
                OBJECT_JS,
                OBJECT_CS,
                OBJECT_UNSET_111,
                OBJECT_UNSET_112,
                OBJECT_GI_SOLDOUT,
                OBJECT_UNSET_114,
                OBJECT_MAG,
                OBJECT_UNSET_116,
                OBJECT_UNSET_117,
                OBJECT_UNSET_118,
                OBJECT_GI_GOLONMASK,
                OBJECT_GI_ZORAMASK,
                OBJECT_UNSET_11B,
                OBJECT_UNSET_11C,
                OBJECT_KA,
                OBJECT_UNSET_11E,
                OBJECT_ZG,
                OBJECT_UNSET_120,
                OBJECT_GI_M_ARROW,
                OBJECT_DS2,
                OBJECT_UNSET_123,
                OBJECT_FISH,
                OBJECT_GI_SUTARU,
                OBJECT_UNSET_126,
                OBJECT_SSH,
                OBJECT_BIGSLIME,
                OBJECT_BG,
                OBJECT_BOMBIWA,
                OBJECT_HINTNUTS,
                OBJECT_RS,
                OBJECT_UNSET_12D,
                OBJECT_GLA,
                OBJECT_UNSET_12F,
                OBJECT_GELDB,
                OBJECT_UNSET_131,
                OBJECT_DOG,
                OBJECT_KIBAKO2,
                OBJECT_DNS,
                OBJECT_DNK,
                OBJECT_UNSET_136,
                OBJECT_GI_INSECT,
                OBJECT_UNSET_138,
                OBJECT_GI_GHOST,
                OBJECT_GI_SOUL,
                OBJECT_UNSET_13B,
                OBJECT_UNSET_13C,
                OBJECT_UNSET_13D,
                OBJECT_UNSET_13E,
                OBJECT_GI_RUPY,
                OBJECT_MU,
                OBJECT_WF,
                OBJECT_SKB,
                OBJECT_GS,
                OBJECT_PS,
                OBJECT_OMOYA_OBJ,
                OBJECT_COW,
                OBJECT_UNSET_147,
                OBJECT_GI_SWORD_1,
                OBJECT_UNSET_149,
                OBJECT_UNSET_14A,
                OBJECT_ZL4,
                OBJECT_LINK_GORON,
                OBJECT_LINK_ZORA,
                OBJECT_GRASSHOPPER,
                OBJECT_BOYO,
                OBJECT_UNSET_150,
                OBJECT_UNSET_151,
                OBJECT_UNSET_152,
                OBJECT_FWALL,
                OBJECT_LINK_NUTS,
                OBJECT_JSO,
                OBJECT_KNIGHT,
                OBJECT_ICICLE,
                OBJECT_SPDWEB,
                OBJECT_UNSET_159,
                OBJECT_BOSS01,
                OBJECT_BOSS02,
                OBJECT_BOSS03,
                OBJECT_BOSS04,
                OBJECT_BOSS05,
                OBJECT_BOSS06,
                OBJECT_BOSS07,
                OBJECT_RAF,
                OBJECT_FUNEN,
                OBJECT_RAILLIFT,
                OBJECT_NUMA_OBJ,
                OBJECT_FLOWERPOT,
                OBJECT_SPINYROLL,
                OBJECT_ICE_BLOCK,
                OBJECT_UNSET_168,
                OBJECT_KEIKOKU_DEMO,
                OBJECT_SLIME,
                OBJECT_PR,
                OBJECT_F52_OBJ,
                OBJECT_F53_OBJ,
                OBJECT_UNSET_16E,
                OBJECT_KIBAKO,
                OBJECT_SEK,
                OBJECT_GMO,
                OBJECT_BAT,
                OBJECT_SEKIHIL,
                OBJECT_SEKIHIG,
                OBJECT_SEKIHIN,
                OBJECT_SEKIHIZ,
                OBJECT_UNSET_177,
                OBJECT_WIZ,
                OBJECT_LADDER,
                OBJECT_MKK,
                OBJECT_UNSET_17B,
                OBJECT_UNSET_17C,
                OBJECT_UNSET_17D,
                OBJECT_KEIKOKU_OBJ,
                OBJECT_SICHITAI_OBJ,
                OBJECT_DEKUCITY_ANA_OBJ,
                OBJECT_RAT,
                OBJECT_WATER_EFFECT,
                OBJECT_UNSET_183,
                OBJECT_DBLUE_OBJECT,
                OBJECT_BAL,
                OBJECT_WARP_UZU,
                OBJECT_DRIFTICE,
                OBJECT_FALL,
                OBJECT_HANAREYAMA_OBJ,
                OBJECT_CRACE_OBJECT,
                OBJECT_DNQ,
                OBJECT_OBJECT_UNSET_TOKEIDAI,
                OBJECT_EG,
                OBJECT_TRU,
                OBJECT_TRT,
                OBJECT_HAKUGIN_OBJ,
                OBJECT_HORSE_GAME_CHECK,
                OBJECT_STK,
                OBJECT_UNSET_193,
                OBJECT_UNSET_194,
                OBJECT_MNK,
                OBJECT_GI_BOTTLE_RED,
                OBJECT_TOKEI_TOBIRA,
                OBJECT_AZ,
                OBJECT_TWIG,
                OBJECT_DEKUCITY_OBJ,
                OBJECT_PO_FUSEN,
                OBJECT_RACETSUBO,
                OBJECT_HA,
                OBJECT_BIGOKUTA,
                OBJECT_OPEN_OBJ,
                OBJECT_FU_KAITEN,
                OBJECT_FU_MATO,
                OBJECT_MTORIDE,
                OBJECT_OSN,
                OBJECT_TOKEI_STEP,
                OBJECT_LOTUS,
                OBJECT_TL,
                OBJECT_DKJAIL_OBJ,
                OBJECT_VISIBLOCK,
                OBJECT_TSN,
                OBJECT_DS2N,
                OBJECT_FSN,
                OBJECT_SHN,
                OBJECT_BIGICICLE,
                OBJECT_GI_BOTTLE_15,
                OBJECT_TK,
                OBJECT_MARKET_OBJ,
                OBJECT_GI_RESERVE00,
                OBJECT_GI_RESERVE01,
                OBJECT_LIGHTBLOCK,
                OBJECT_TAKARAYA_OBJECTS,
                OBJECT_WDHAND,
                OBJECT_SDN,
                OBJECT_SNOWWD,
                OBJECT_GIANT,
                OBJECT_COMB,
                OBJECT_HANA,
                OBJECT_BOSS_HAKUGIN,
                OBJECT_MEGANEANA_OBJ,
                OBJECT_GI_NUTSMASK,
                OBJECT_STK2,
                OBJECT_SPOT11_OBJ,
                OBJECT_DANPEI_OBJECT,
                OBJECT_DHOUSE,
                OBJECT_HAKAISI,
                OBJECT_PO,
                OBJECT_SNOWMAN,
                OBJECT_PO_SISTERS,
                OBJECT_PP,
                OBJECT_GORONSWITCH,
                OBJECT_DELF,
                OBJECT_BOTIHASIRA,
                OBJECT_GI_BIGBOMB,
                OBJECT_PST,
                OBJECT_BSMASK,
                OBJECT_SPIDERTENT,
                OBJECT_ZORAEGG,
                OBJECT_KBT,
                OBJECT_GG,
                OBJECT_MARUTA,
                OBJECT_GHAKA,
                OBJECT_OYU,
                OBJECT_DNP,
                OBJECT_DAI,
                OBJECT_KGY,
                OBJECT_FB,
                OBJECT_TAISOU,
                OBJECT_MASK_BU_SAN,
                OBJECT_MASK_KI_TAN,
                OBJECT_MASK_RABIT,
                OBJECT_MASK_SKJ,
                OBJECT_MASK_BAKURETU,
                OBJECT_MASK_TRUTH,
                OBJECT_GK,
                OBJECT_HAKA_OBJ,
                OBJECT_MASK_GORON,
                OBJECT_MASK_ZORA,
                OBJECT_MASK_NUTS,
                OBJECT_MASK_BOY,
                OBJECT_DNT,
                OBJECT_YUKIYAMA,
                OBJECT_ICEFLOE,
                OBJECT_GI_GOLD_DUST,
                OBJECT_GI_BOTTLE_16,
                OBJECT_GI_BOTTLE_22,
                OBJECT_BEE,
                OBJECT_OT,
                OBJECT_UTUBO,
                OBJECT_DORA,
                OBJECT_GI_LOACH,
                OBJECT_GI_SEAHORSE,
                OBJECT_BIGPO,
                OBJECT_HARIKO,
                OBJECT_DNO,
                OBJECT_SINKAI_KABE,
                OBJECT_KIN2_OBJ,
                OBJECT_ISHI,
                OBJECT_HAKUGIN_DEMO,
                OBJECT_JG,
                OBJECT_GI_SWORD_2,
                OBJECT_GI_SWORD_3,
                OBJECT_GI_SWORD_4,
                OBJECT_UM,
                OBJECT_MASK_GIBUDO,
                OBJECT_MASK_JSON,
                OBJECT_MASK_KERFAY,
                OBJECT_MASK_BIGELF,
                OBJECT_RB,
                OBJECT_MBAR_OBJ,
                OBJECT_IKANA_OBJ,
                OBJECT_KZ,
                OBJECT_TOKEI_TURRET,
                OBJECT_ZOG,
                OBJECT_ROTLIFT,
                OBJECT_POSTHOUSE_OBJ,
                OBJECT_GI_MASK09,
                OBJECT_GI_MASK14,
                OBJECT_GI_MASK15,
                OBJECT_INIBS_OBJECT,
                OBJECT_TREE,
                OBJECT_KAIZOKU_OBJ,
                OBJECT_GI_RESERVE_B_00,
                OBJECT_GI_RESERVE_C_00,
                OBJECT_ZOB,
                OBJECT_MILKBAR,
                OBJECT_DMASK,
                OBJECT_MASK_KYOJIN,
                OBJECT_GI_RESERVE_C_01,
                OBJECT_ZOD,
                OBJECT_KUMO30,
                OBJECT_OBJECT_UNSET_YASI,
                OBJECT_MASK_ROMERNY,
                OBJECT_TANRON1,
                OBJECT_TANRON2,
                OBJECT_TANRON3,
                OBJECT_GI_MAGICMUSHROOM,
                OBJECT_OBJECT_UNSET_CHAN,
                OBJECT_GI_MASK10,
                OBJECT_ZOS,
                OBJECT_MASK_POSTHAT,
                OBJECT_F40_SWITCH,
                OBJECT_LODMOON,
                OBJECT_TRO,
                OBJECT_GI_MASK12,
                OBJECT_GI_MASK23,
                OBJECT_GI_BOTTLE_21,
                OBJECT_GI_CAMERA,
                OBJECT_KAMEJIMA,
                OBJECT_HARFGIBUD,
                OBJECT_ZOV,
                OBJECT_HGDOOR,
                OBJECT_UNSET_22D,
                OBJECT_UNSET_22E,
                OBJECT_UNSET_22F,
                OBJECT_DOR01,
                OBJECT_DOR02,
                OBJECT_DOR03,
                OBJECT_DOR04,
                OBJECT_LAST_OBJ,
                OBJECT_REDEAD_OBJ,
                OBJECT_IKNINSIDE_OBJ,
                OBJECT_IKNV_OBJ,
                OBJECT_PAMERA,
                OBJECT_HSSTUMP,
                OBJECT_ZM,
                OBJECT_BIG_FWALL,
                OBJECT_SECOM_OBJ,
                OBJECT_HUNSUI,
                OBJECT_UCH,
                OBJECT_TANRON4,
                OBJECT_TANRON5,
                OBJECT_DT,
                OBJECT_GI_MASK03,
                OBJECT_CHA,
                OBJECT_OBJECT_UNSET_DINNER,
                OBJECT_GI_RESERVE_B_01,
                OBJECT_LASTDAY,
                OBJECT_BAI,
                OBJECT_IN2,
                OBJECT_IKN_DEMO,
                OBJECT_YB,
                OBJECT_RZ,
                OBJECT_MASK_ZACHO,
                OBJECT_GI_FIELDMAP,
                OBJECT_MASK_STONE,
                OBJECT_BJT,
                OBJECT_TARU,
                OBJECT_MOONSTON,
                OBJECT_MASK_BREE,
                OBJECT_GI_SCHEDULE,
                OBJECT_GI_STONEMASK,
                OBJECT_ZORABAND,
                OBJECT_KEPN_KOYA,
                OBJECT_OBJECT_UNSET_USIYANE,
                OBJECT_GI_MASK05,
                OBJECT_GI_MASK11,
                OBJECT_GI_MASK20,
                OBJECT_NNH,
                OBJECT_MASK_GERO,
                OBJECT_MASK_YOFUKASI,
                OBJECT_MASK_MEOTO,
                OBJECT_MASK_DANCER,
                OBJECT_KZSAKU,
                OBJECT_OBJECT_UNSET_MILK_BIN,
                OBJECT_RANDOM_OBJ,
                OBJECT_KUJIYA,
                OBJECT_KITAN,
                OBJECT_GI_MASK06,
                OBJECT_GI_MASK16,
                OBJECT_ASTR_OBJ,
                OBJECT_BSB,
                OBJECT_FALL2,
                OBJECT_STH,
                OBJECT_GI_MSSA,
                OBJECT_SMTOWER,
                OBJECT_GI_MASK21,
                OBJECT_YADO_OBJ,
                OBJECT_SYOTEN,
                OBJECT_MOONEND,
                OBJECT_OB,
                OBJECT_GI_BOTTLE_04,
                OBJECT_OBJECT_UNSET_DANPEILIFT,
                OBJECT_WDOR01,
                OBJECT_WDOR02,
                OBJECT_WDOR03,
                OBJECT_STK3,
                OBJECT_KINSTA1_OBJ,
                OBJECT_KINSTA2_OBJ,
                OBJECT_BH,
                OBJECT_WDOR04,
                OBJECT_WDOR05,
                OBJECT_GI_MASK17,
                OBJECT_GI_MASK22,
                OBJECT_LBFSHOT,
                OBJECT_FUSEN,
                OBJECT_ENDING_OBJ,
                OBJECT_GI_MASK13
} ObjectID;
typedef struct {
          u32 vromStart;
          u32 vromEnd;
} RoomFileLocation;
typedef struct {
               u8 code;
               u8 data1;
               u32 data2;
} SCmdBase;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdSpawnList;
typedef struct {
               u8 code;
               u8 num;
               void* segment;
} SCmdActorList;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdCsCameraList;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdColHeader;
typedef struct {
               u8 code;
               u8 num;
               void* segment;
} SCmdRoomList;
typedef struct {
               u8 code;
               u8 data1;
               s8 pad2[2];
               s8 west;
               s8 vertical;
               s8 south;
               u8 clothIntensity;
} SCmdWindSettings;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdEntranceList;
typedef struct {
               u8 code;
               u8 cUpElfMsgNum;
               u32 keepObjectId;
} SCmdSpecialFiles;
typedef struct {
               u8 code;
               u8 gpFlag1;
               u32 gpFlag2;
} SCmdRoomBehavior;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdMesh;
typedef struct {
               u8 code;
               u8 num;
               void* segment;
} SCmdObjectList;
typedef struct {
               u8 code;
               u8 num;
               void* segment;
} SCmdLightList;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdPathList;
typedef struct {
               u8 code;
               u8 num;
               void* segment;
} SCmdTransiActorList;
typedef struct {
               u8 code;
               u8 num;
               void* segment;
} SCmdLightSettingList;
typedef struct {
               u8 code;
               u8 data1;
               s8 pad2[2];
               u8 hour;
               u8 min;
               u8 unk6;
} SCmdTimeSettings;
typedef struct {
               u8 code;
               u8 data1;
               s8 pad2[2];
               u8 skyboxId;
               u8 unk5;
               u8 unk6;
} SCmdSkyboxSettings;
typedef struct {
               u8 code;
               u8 data1;
               s8 pad2[2];
               u8 unk4;
               u8 unk5;
} SCmdSkyboxDisables;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdExitList;
typedef struct {
               u8 code;
               u8 data1;
               u32 data2;
} SCmdEndMarker;
typedef struct {
               u8 code;
               u8 bgmId;
               s8 pad2[4];
               u8 nighttimeSFX;
               u8 musicSeq;
} SCmdSoundSettings;
typedef struct {
               u8 code;
               u8 data1;
               s8 pad2[5];
               u8 echo;
} SCmdEchoSettings;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdCutsceneData;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdAltHeaders;
typedef struct {
               u8 code;
               u8 data1;
               u32 data2;
} SCmdWorldMapVisited;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdTextureAnimations;
typedef struct {
               u8 code;
               u8 num;
               void* segment;
} SCmdCutsceneActorList;
typedef struct {
               u8 code;
               u8 data1;
               void* segment;
} SCmdMinimapSettings;
typedef struct {
               u8 code;
               u8 num;
               void* segment;
} SCmdMinimapChests;
typedef struct {
              u32 opaqueDl;
              u32 translucentDl;
} RoomMeshType0Params;
typedef struct {
              u8 type;
              u8 format;
} RoomMeshType1;
typedef struct {
              s8 pad0[0x10];
} RoomMeshType1Params;
typedef struct {
              s8 pad0[0x10];
} RoomMeshType2Params;
typedef struct {
              u8 type;
              u8 count;
              s8 pad2[0x2];
              RoomMeshType0Params* paramsStart;
              RoomMeshType0Params* paramsEnd;
} RoomMeshType0;
typedef struct {
              u8 type;
              u8 count;
              s8 pad2[0x2];
              RoomMeshType2Params* paramsStart;
              RoomMeshType2Params* paramsEnd;
} RoomMeshType2;
typedef union {
    RoomMeshType0 type0;
    RoomMeshType1 type1;
    RoomMeshType2 type2;
} RoomMesh;
typedef struct {
               s8 num;
               u8 unk1;
               u8 unk2;
               u8 unk3;
               s8 echo;
               u8 unk5;
               u8 enablePosLights;
               s8 pad7[0x1];
               RoomMesh* mesh;
               void* segment;
               s8 pad10[0x4];
} Room;
typedef struct {
               Room currRoom;
               Room prevRoom;
               void* roomMemPages[2];
               u8 activeMemPage;
               s8 unk31;
               s8 pad32[0x2];
               void* activeRoomVram;
               DmaRequest dmaRequest;
               OSMesgQueue loadQueue;
               OSMesg loadMsg[1];
               void* unk74;
               s8 unk78;
               s8 unk79;
               s16 unk7A[3];
} RoomContext;
typedef struct {
              s16 id;
              Vec3s pos;
              Vec3s rot;
              s16 params;
} ActorEntry;
typedef struct {
              u32 data;
              s16 unk4;
              u8 unk6;
              u8 unk7;
} CutsceneEntry;
typedef struct {
              u8 spawn;
              u8 room;
} EntranceEntry;
typedef struct {
              s8 scene;
              s8 unk1;
              u16 unk2;
} EntranceRecord;
typedef struct {
              u32 entranceCount;
              EntranceRecord** entrances;
              char* name;
} SceneEntranceTableEnty;
typedef struct {
               u16 scenes[27];
} SceneIdList;
typedef struct {
               s16 id;
               s8 pad2[0x2];
               void* vramAddr;
               DmaRequest dmaReq;
               OSMesgQueue loadQueue;
               OSMesg loadMsg;
} SceneObject;
typedef struct {
              u32 romStart;
              u32 romEnd;
              u16 unk8;
              s8 padA[0x1];
              u8 sceneConfig;
              s8 padC[0x1];
              u8 unkD;
              s8 padE[0x2];
} SceneTableEntry;
typedef struct {
              s8 xStep;
              s8 yStep;
              u8 width;
              u8 height;
} ScrollingTextureParams;
typedef struct {
                void* objectVramStart;
                void* objectVramEnd;
                u8 objectCount;
                u8 spawnedObjectCount;
                u8 mainKeepIndex;
                u8 keepObjectId;
                SceneObject objects[35];
} SceneContext;
typedef union {
                        SCmdBase base;
                        SCmdSpawnList spawnList;
                        SCmdActorList actorList;
                        SCmdCsCameraList csCameraList;
                        SCmdColHeader colHeader;
                        SCmdRoomList roomList;
                        SCmdWindSettings windSettings;
                        SCmdEntranceList entranceList;
                        SCmdSpecialFiles specialFiles;
                        SCmdRoomBehavior roomBehavior;
                        SCmdMesh mesh;
                        SCmdObjectList objectList;
                        SCmdLightList lightList;
                        SCmdPathList pathList;
                        SCmdTransiActorList transiActorList;
                        SCmdLightSettingList lightSettingList;
                        SCmdTimeSettings timeSettings;
                        SCmdSkyboxSettings skyboxSettings;
                        SCmdSkyboxDisables skyboxDisables;
                        SCmdExitList exitList;
                        SCmdEndMarker endMarker;
                        SCmdSoundSettings soundSettings;
                        SCmdEchoSettings echoSettings;
                        SCmdCutsceneData cutsceneData;
                        SCmdAltHeaders altHeaders;
                        SCmdWorldMapVisited worldMapVisited;
                        SCmdTextureAnimations textureAnimations;
                        SCmdCutsceneActorList cutsceneActorList;
                        SCmdMinimapSettings minimapSettings;
                        SCmdMinimapChests minimapChests;
} SceneCmd;
typedef enum {
               SCENE_20SICHITAI2,
               SCENE_UNSET_1,
               SCENE_UNSET_2,
               SCENE_UNSET_3,
               SCENE_UNSET_4,
               SCENE_UNSET_5,
               SCENE_UNSET_6,
               SCENE_KAKUSIANA,
               SCENE_SPOT00,
               SCENE_UNSET_9,
               SCENE_WITCH_SHOP,
               SCENE_LAST_BS,
               SCENE_HAKASHITA,
               SCENE_AYASHIISHOP,
               SCENE_UNSET_E,
               SCENE_UNSET_F,
               SCENE_OMOYA,
               SCENE_BOWLING,
               SCENE_SONCHONOIE,
               SCENE_IKANA,
               SCENE_KAIZOKU,
               SCENE_MILK_BAR,
               SCENE_INISIE_N,
               SCENE_TAKARAYA,
               SCENE_INISIE_R,
               SCENE_OKUJOU,
               SCENE_OPENINGDAN,
               SCENE_MITURIN,
               SCENE_13HUBUKINOMITI,
               SCENE_CASTLE,
               SCENE_DEKUTES,
               SCENE_MITURIN_BS,
               SCENE_SYATEKI_MIZU,
               SCENE_HAKUGIN,
               SCENE_ROMANYMAE,
               SCENE_PIRATE,
               SCENE_SYATEKI_MORI,
               SCENE_SINKAI,
               SCENE_YOUSEI_IZUMI,
               SCENE_KINSTA1,
               SCENE_KINDAN2,
               SCENE_TENMON_DAI,
               SCENE_LAST_DEKU,
               SCENE_22DEKUCITY,
               SCENE_KAJIYA,
               SCENE_00KEIKOKU,
               SCENE_POSTHOUSE,
               SCENE_LABO,
               SCENE_DANPEI2TEST,
               SCENE_UNSET_31,
               SCENE_16GORON_HOUSE,
               SCENE_33ZORACITY,
               SCENE_8ITEMSHOP,
               SCENE_F01,
               SCENE_INISIE_BS,
               SCENE_30GYOSON,
               SCENE_31MISAKI,
               SCENE_TAKARAKUJI,
               SCENE_UNSET_3A,
               SCENE_TORIDE,
               SCENE_FISHERMAN,
               SCENE_GORONSHOP,
               SCENE_DEKU_KING,
               SCENE_LAST_GORON,
               SCENE_24KEMONOMITI,
               SCENE_F01_B,
               SCENE_F01C,
               SCENE_BOTI,
               SCENE_HAKUGIN_BS,
               SCENE_20SICHITAI,
               SCENE_21MITURINMAE,
               SCENE_LAST_ZORA,
               SCENE_11GORONNOSATO2,
               SCENE_SEA,
               SCENE_35TAKI,
               SCENE_REDEAD,
               SCENE_BANDROOM,
               SCENE_11GORONNOSATO,
               SCENE_GORON_HAKA,
               SCENE_SECOM,
               SCENE_10YUKIYAMANOMURA,
               SCENE_TOUGITES,
               SCENE_DANPEI,
               SCENE_IKANAMAE,
               SCENE_DOUJOU,
               SCENE_MUSICHOUSE,
               SCENE_IKNINSIDE,
               SCENE_MAP_SHOP,
               SCENE_F40,
               SCENE_F41,
               SCENE_10YUKIYAMANOMURA2,
               SCENE_14YUKIDAMANOMITI,
               SCENE_12HAKUGINMAE,
               SCENE_17SETUGEN,
               SCENE_17SETUGEN2,
               SCENE_SEA_BS,
               SCENE_RANDOM,
               SCENE_YADOYA,
               SCENE_KONPEKI_ENT,
               SCENE_INSIDETOWER,
               SCENE_26SARUNOMORI,
               SCENE_LOST_WOODS,
               SCENE_LAST_LINK,
               SCENE_SOUGEN,
               SCENE_BOMYA,
               SCENE_KYOJINNOMA,
               SCENE_KOEPONARACE,
               SCENE_GORONRACE,
               SCENE_TOWN,
               SCENE_ICHIBA,
               SCENE_BACKTOWN,
               SCENE_CLOCKTOWER,
               SCENE_ALLEY
} SceneID;
typedef struct {
              s16 priority;
              s16 length;
              s16 unk4;
              s16 unk6;
              s16 additionalCutscene;
              u8 sound;
              u8 unkB;
              s16 unkC;
              u8 unkE;
              u8 letterboxSize;
} ActorCutscene;
typedef struct {
              s16 polyStartIndex;
              s16 ceilingNodeHead;
              s16 wallNodeHead;
              s16 floorNodeHead;
} ActorMeshPolyLists;
typedef struct {
              s8 segment;
              s16 type;
              void* params;
} AnimatedTexture;
typedef struct {
              u16 floorHead;
              u16 wallHead;
              u16 ceilingHead;
} BgMeshSubdivision;
typedef struct {
              u32 attributes[2];
} BgPolygonAttributes;
typedef struct {
              s16 polyIndex;
              u16 next;
} BgPolygonLinkedListNode;
typedef struct {
              u16 maxNodes;
              u16 reservedNodes;
              BgPolygonLinkedListNode* nodes;
              u8* unk8;
} BgScenePolygonLists;
typedef struct {
              s16 sceneNumber;
              s8 pad2[0x2];
              u32 maxMemory;
} BgSpecialSceneMaxMemory;
typedef struct {
              s16 sceneId;
              s16 maxNodes;
              s16 maxPolygons;
              s16 maxVertices;
} BgSpecialSceneMaxObjects;
typedef struct {
              s16 sceneNumber;
              s16 xSubdivisions;
              s16 ySubdivisions;
              s16 zSubdivisions;
              s32 unk8;
} BgSpecialSceneMeshSubdivision;
typedef struct {
              s16 func;
              s8 pad2[0x6];
} CameraModeParams;
typedef struct {
              u32 validModes;
              s8 pad4[0x4];
              CameraModeParams* modes;
} CameraStateParams;
typedef struct {
               u8 cutsceneCount;
               s8 pad1[0x3];
               u8* segment;
               u8 state;
               s8 pad9[0x3];
               f32 unkC;
               u16 frames;
               u16 unk12;
               s8 pad14[0x14];
               CsCmdActorAction* actorActions[10];
} CutsceneContext;
typedef struct {
               u32 chestFlags;
               u32 switchFlags[2];
               u32 clearedRooms;
               u32 collectibleFlags;
} CycleSceneFlags;
typedef struct {
              u16 cycleLength;
              Gfx** textureDls;
              u8* textureDlOffsets;
} CyclingTextureParams;
typedef struct {
              u32 size;
              Gfx* buf;
              Gfx* p;
              Gfx* d;
} DispBuf;
typedef struct {
              s16 x;
              s16 y;
              s16 z;
              s16 reserved;
              s16 s;
              s16 t;
              s8 r;
              s8 g;
              s8 b;
              s8 a;
} F3DVertexColor;
typedef struct {
              s16 x;
              s16 y;
              s16 z;
              s16 reserved;
              s16 s;
              s16 t;
              s8 normalX;
              s8 normalY;
              s8 normalZ;
              s8 a;
} F3DVertexNormal;
typedef struct {
              f32 size;
              f32 dynamicSizeStep;
              u8 state;
              u8 sizeGrowsCos2;
              u8 unkA;
              u8 flags;
              u8 unkC;
} FireObjInitParams;
typedef struct {
              u8 unk0;
              u8 unk1;
              u8 unk2;
              u8 unk3;
              u8 unk4;
              u8 unk5;
              u8 unk6;
              u8 unk7;
} FireObjLightParams;
typedef struct {
              u8 red;
              u8 green;
              u8 blue;
              u8 alpha;
              u8 lodFrac;
} FlashingTexturePrimColor;
typedef struct {
                 u8 unk0[2][120][128];
                 u8 unk7800[93][128];
} Font;
typedef struct {
                 u8 unk0;
                 u8 unk1;
                 u8 unk2;
                 u8 unk3;
                 u32 unk4;
                 s8 pad8[0xC];
                 s16 data[2784];
} GameInfo;
typedef struct {
              s32 size;
              void* heapStart;
              void* heapAppendStart;
              void* heapAppendEnd;
} GameStateHeap;
typedef struct {
                  u16 headMagic;
                  Gfx unk8[96];
                  Gfx polyXluBuffer[2048];
                  Gfx overlayBuffer[1024];
                  Gfx unk6308[64];
                  Gfx unk6508[64];
                  Gfx polyOpaBuffer[13184];
                  u16 tailMagic;
} GfxPool;
typedef struct {
               s32 unk0;
               s8 pad4[0x40];
} GlobalContext17D98;
typedef struct {
                Gfx* polyOpaBuffer;
                Gfx* polyXluBuffer;
                s8 pad8[0x8];
                Gfx* overlayBuffer;
                s8 pad14[0x24];
                s32 unk38[8];
                OSMesgQueue* unk58;
                OSMesgQueue unk5C;
                s8 pad74[0x12C];
                Gfx* unk1A0;
                DispBuf unk1A4;
                Gfx* unk1B4;
                DispBuf unk1B8;
                s8 pad1C8[0xAC];
                OSViMode* unk274;
                void* zbuffer;
                s8 pad27C[0x1C];
                DispBuf overlay;
                DispBuf polyOpa;
                DispBuf polyXlu;
                s32 displaylistCounter;
                void* framebuffer;
                int pad2D0;
                u32 viConfigFeatures;
                s8 gap2D8[0x3];
                u8 framebufferCounter;
                s8 pad2DC[0x8];
                f32 viConfigXScale;
                f32 viConfigYScale;
                s8 pad2EC[0x4];
} GraphicsContext;
typedef enum IRQ_MSG_TYPE {
    IRQ_VERTICAL_RETRACE_MSG = 0x1,
    IRQ_PRENMI_2_MSG = 0x3,
    IRQ_PRENMI_1_MSG = 0x4
} IRQ_MSG_TYPE;
typedef enum IRQ_TYPE {
    IRQ_VERTICAL_RETRACE = 0x29A,
    IRQ_SP = 0x29B,
    IRQ_DP = 0x29C,
    IRQ_PRENMI_1 = 0x29D,
    IRQ_PRENMI_2 = 0x29F,
    IRQ_PRENMI_3 = 0x2A0,
    IRQ_PRENMI_4 = 0x2A1
} IRQ_TYPE;
typedef struct {
              u32 vromStart;
              u32 vromEnd;
} ObjectFileTableEntry;
typedef struct {
               u32 textSize;
               u32 dataSize;
               u32 rodataSize;
               u32 bssSize;
               u32 nRelocations;
} OverlayRelocationSection;
typedef struct {
               s8 pad0[0x1C];
} PermanentSceneFlags;
typedef struct {
              s16 unk0;
              s16 unk2;
              s16 unk4;
} QuakeRequest14;
typedef struct {
               s16 intPart[16];
               u16 fracPart[16];
} RSPMatrix;
typedef struct {
                s8 pad0[0xC];
                s32 sceneSetupIndex;
                s32 unk10;
                s8 pad14[0x2E];
                s16 unk42;
                s8 pad44[0x43];
                s8 unk87;
                s8 pad88[0x1EE];
                u8 unk276;
                s8 pad277[0x9];
                u16 unk280;
                u16 unk282;
                s8 pad284[0x28];
                u8 cutsceneTrigger;
                s8 pad2AD[0x5];
                u16 environmentTime;
                s8 pad2B4[0x4];
                s16 unk2b8;
                s8 pad2BA[0xA];
                f32 unk2C4;
                CycleSceneFlags cycleSceneFlags[120];
} SaveContextExtra;
typedef struct {
               u8 items[24];
               u8 masks[24];
               u8 quantities[24];
               s8 pad48[0x40];
} SaveContextInventory;
typedef struct {
                 s8 pad0[0x1];
                 u8 unk1;
                 u8 unk2;
                 s8 pad3[0x2];
                 u8 unk5;
                 s8 pad6[0x2C8E];
} SaveContextOwl;
typedef struct {
               u8 zelda[6];
               s8 pad6[0xA];
               s16 maxLife;
               s16 currentLife;
               s8 pad14[0x1];
               s8 currentMagic;
               s8 pad16[0x12];
} SaveContext_struct1;
typedef struct {
               s8 pad0[0x22];
} SaveContext_struct2;
typedef struct {
              s8 letterboxTarget;
              s8 letterboxMagnitude;
              s8 pillarboxTarget;
              s8 pillarboxMagnitude;
} ShrinkWindowContext;
typedef struct {
               s8 pad0[0x4];
               void* savefile;
               s8 pad8[0x4];
               s16 unkC;
               s8 padE[0xA];
               OSTime unk18;
} SramContext;
typedef struct {
               s32 unk0;
               s32 unk4;
               s32 unk8;
               f32 unkC;
               ColorRGBA8 unk10;
} TargetContextEntry;
typedef struct {
              u32 texture;
              s16 unk4;
              s16 unk6;
              u8 unk8;
              u8 unk9;
              u8 fadeOutDelay;
              u8 fadeInDelay;
              s16 alpha;
              s16 color;
} TitleCardContext;
typedef struct {
              s8 unk0;
              s8 pad1[0x1];
              s8 unk2;
              s8 pad3[0x1];
              s16 actorIndex;
              s16 x;
              s16 y;
              s16 z;
              s16 yRot;
              u16 variable;
} TransitionActorInit;
typedef struct {
              s32 topY;
              s32 bottomY;
              s32 leftX;
              s32 rightX;
} Viewport;
typedef struct {
              unsigned int inst1;
              unsigned int inst2;
              unsigned int inst3;
              unsigned int inst4;
} __osExceptionVector;
typedef void*(*fault_address_converter_func)(void* addr, void* arg);
typedef void(*fault_client_func)(void* arg1, void* arg2);
typedef unsigned long(*func)(void);
typedef void(*func_ptr)(void);
typedef void(*actor_init_var_func)(u8*, InitChainEntry*);
typedef void(*light_map_directional_func)(LightMapper* mapper, void* params, Vec3f* pos);
typedef void(*osCreateThread_func)(void*);
typedef void*(*printf_func)(void*, char*, size_t);
typedef struct {
                OSThread unk0;
                s8 argCount;
                s8 unk1B1;
                s8 pad1B2[0x2];
                s8 func;
                s8 pad1B5[0x3];
                s32 arg0;
                s32 arg1;
} s8018571C;
typedef struct {
               int unk0;
               void* unk4;
               int unk8;
               int unkC;
               int unk10;
               OSMesgQueue unk14;
} s80185D40;
typedef struct {
               u32 unk0;
               u8 unk4;
               u8 unk5;
               u8 unk6;
               s8 pad7[0x2];
               u8 unk9;
               s8 padA[0x2];
               u32 unkC;
               u16 unk10;
               u16 unk12;
               u16 unk14;
               s8 pad16[0x2];
               u32 unk18;
               u32 unk1C;
               u32 unk20;
               u32 unk24;
               u32 unk28;
               u32 unk2C;
               u32 unk30;
               u32 unk34;
} s8018CFAC;
typedef struct {
              u8 unk0;
              u8 unk1;
              u8 unk2;
              u8 unk3;
              u8 unk4;
              u8 unk5;
              u8 unk6;
              u8 unk7;
} s801AEC84;
typedef struct {
               s8 pad0[0x14];
} s801FE7C0;
typedef struct {
               Vec3f unk0;
               Vec3f unkC;
               s16 unk18;
               s16 unk1A;
} s80874650;
typedef struct {
               f32 x[4];
               f32 y[4];
               f32 z[4];
               f32 w[4];
} z_Matrix;
typedef struct {
               Vec3f scale;
               Vec3s rotation;
               Vec3f pos;
} ActorMeshParams;
typedef struct {
              u16 attributeIndex;
              u16 vertA;
              u16 vertB;
              u16 vertC;
              Vec3s normal;
              s16 unkE;
} BgPolygon;
typedef struct {
              BgPolygonLinkedListNode* nodes;
              u32 nextFreeNode;
              s32 maxNodes;
} BgPolygonLinkedList;
typedef struct {
              Vec3s pos;
} BgVertex;
typedef struct {
              Vec3s minPos;
              s8 xLength;
              s8 pad7[0x1];
              s8 zLength;
              s8 pad9[0x3];
              u32 properties;
} BgWaterBox;
typedef struct {
              s8 pad0[0x4];
              BgWaterBox* boxes;
} BgWaterboxList;
typedef union {
    F3DVertexColor color;
    F3DVertexNormal normal;
} F3DVertex;
typedef struct {
               u16* fb;
               u16 w;
               u16 h;
               u16 yStart;
               u16 yEnd;
               u16 xStart;
               u16 xEnd;
               u16 foreColor;
               u16 backColor;
               u16 cursorX;
               u16 cursorY;
               u32* font;
               u8 charW;
               u8 charH;
               s8 charWPad;
               s8 charHPad;
               u16 printColors[10];
               u8 escCode;
               u8 osSyncPrintfEnabled;
               func_ptr inputCallback;
} FaultDrawer;
typedef struct {
              u16 cycleLength;
              u16 numKeyFrames;
              FlashingTexturePrimColor* primColors;
              RGBA8* envColors;
              u16* keyFrames;
} FlashingTextureParams;
typedef struct {
               void* loadedRamAddr;
               u32 vromStart;
               u32 vromEnd;
               void* vramStart;
               void* vramEnd;
               s32 unk14;
               func_ptr init;
               func_ptr destroy;
               s32 unk20;
               s32 unk24;
               s32 unk28;
               u32 instanceSize;
} GameStateOverlay;
typedef struct {
               u8 unk0;
               u8 unk1;
               u16 unk2;
               Vec3f unk4;
               Vec3f unk10;
} GlobalContext1F78;
typedef struct {
               OSContPad cur;
               OSContPad prev;
               OSContPad press;
               OSContPad rel;
} Input;
typedef struct {
                 u32 entranceIndex;
                 s8 pad4[0x4];
                 s32 cutscene;
                 u16 time;
                 s8 padE[0x2];
                 u32 isNight;
                 u32 unk14;
                 u32 day;
                 u32 daysElapsed;
                 u8 unk20;
                 s8 pad21[0x2];
                 u8 owlSave;
                 SaveContext_struct1 unk24;
                 SaveContext_struct2 unk4C;
                 s8 pad6E[0x2];
                 SaveContextInventory inv;
                 PermanentSceneFlags sceneFlags[120];
                 s8 padE18[0x60];
                 u32 pictoFlags0;
                 u32 pictoFlags1;
                 s8 padE80[0x78];
                 u8 weekEventReg[100];
                 u32 mapsVisited;
                 s8 padF60[0x8C];
                 u8 lotteryCodes[9];
                 u8 spiderHouseMaskOrder[6];
                 u8 bomberCode[5];
                 s8 pad1000[0xA];
                 u16 checksum;
} SaveContextPerm;
typedef struct {
               Vec3f focalPointChange;
               Vec3f eyeChange;
               s16 rotZ;
               s16 zoom;
               s8 pad1C[0x2];
} ShakeInfo;
typedef struct {
               Vec3f focalPointChange;
               Vec3f eyeChange;
               s16 unk18;
               s16 unk1A;
               f32 unk1C;
               f32 unk20;
} UnkQuakeCalcStruct;
typedef struct {
                u32 magic;
                GraphicsContext* gfxCtx;
                Viewport viewport;
                f32 fovy;
                f32 zNear;
                f32 zFar;
                f32 scale;
                Vec3f eye;
                Vec3f focalPoint;
                Vec3f upDir;
                s8 pad4C[0x4];
                Vp vp;
                Mtx projection;
                Mtx viewing;
                Mtx unkE0;
                Mtx* projectionPtr;
                Mtx* viewingPtr;
                Vec3f quakeRot;
                Vec3f quakeScale;
                f32 quakeSpeed;
                Vec3f currQuakeRot;
                Vec3f currQuakeScale;
                u16 normal;
                s8 pad15E[0x2];
                u32 flags;
                s32 unk164;
} View;
typedef void(*fault_update_input_func)(Input* input);
typedef struct {
               Vec3s min;
               Vec3s max;
               u16 numVertices;
               BgVertex* vertices;
               u16 numPolygons;
               BgPolygon* polygons;
               BgPolygonAttributes* attributes;
               void* cameraData;
               u16 numWaterBoxes;
               BgWaterBox* waterboxes;
} BgMeshHeader;
typedef struct {
                View view;
                s8 pad168[0x84];
                u16 unk1EC;
                u16 unk1EE;
                u8 unk1F0;
                s8 pad1F1[0x3];
                f32 unk1F4;
                s8 pad1F8[0xC];
                u16 unk204;
                s8 pad206[0x6];
                f32 unk20C;
                f32 unk210;
                f32 unk214;
                f32 unk218;
                f32 unk21C;
                f32 unk220;
                s8 pad224[0xAC];
} GlobalContext16D30;
typedef struct {
                View view;
                s8 pad168[0xBE];
                s16 lifeColorChange;
                s16 lifeColorChangeDirection;
                s16 unk22A;
                s16 unk22C;
                s16 unk22E;
                s16 unk230;
                s16 unk232;
                s16 unk234;
                s16 unk236;
                s16 unk238;
                s16 unk23A;
                s16 unk23C;
                s16 unk23E;
                s16 unk240;
                s16 unk242;
                s16 unk244;
                s16 unk246;
                s16 unk248;
                s16 unk24A;
                s16 unk24C;
                s16 unk24E;
                s16 unk250;
                s16 lifeSizeChange;
                s16 lifeSizeChangeDirection;
                s8 pad256[0x1A];
                s16 lifeAlpha;
                s8 pad272[0xD6];
} InterfaceContext;
typedef struct {
               s8 unk0;
               s8 unk1;
               u16 unk2;
               f32 unk4;
               f32 unk8;
               f32 unkC;
               u8 unk10;
               u8 unk11;
               s8 unk12;
               s8 unk13;
               s8 unk14;
               u8 unk15;
               u8 unk16;
               u8 unk17;
               u8 unk18;
               s8 unk19;
               s8 unk1A;
               s8 unk1B;
               s8 unk1C;
               s8 unk1D;
               u8 unk1E;
               u8 unk1F;
               u8 unk20;
               u8 unk21;
               u16 unk22;
               u16 unk24;
               s8 unk26;
               s8 unk27;
               LightInfoDirectional unk28;
               LightInfoDirectional unk36;
               s8 unk44;
               s8 unk45;
               s8 unk46;
               s8 unk47;
               s8 unk48;
               s8 unk49;
               s8 unk4A;
               s8 unk4B;
               s8 unk4C;
               s8 unk4D;
               s8 unk4E;
               s8 unk4F;
               s8 unk50;
               s8 unk51;
               s8 unk52;
               s8 unk53;
               s8 unk54;
               s8 unk55;
               s8 unk56;
               s8 unk57;
               s8 unk58;
               s8 unk59;
               s8 unk5A;
               s8 unk5B;
               s8 unk5C;
               s8 unk5D;
               s8 unk5E;
               s8 unk5F;
               s8 unk60;
               s8 unk61;
               s8 unk62;
               s8 unk63;
               s8 unk64;
               s8 unk65;
               s8 unk66;
               s8 unk67;
               s8 unk68;
               s8 unk69;
               s8 unk6A;
               s8 unk6B;
               s8 unk6C;
               s8 unk6D;
               s8 unk6E;
               s8 unk6F;
               s8 unk70;
               s8 unk71;
               s8 unk72;
               s8 unk73;
               s8 unk74;
               s8 unk75;
               s8 unk76;
               s8 unk77;
               s8 unk78;
               s8 unk79;
               s8 unk7A;
               s8 unk7B;
               s8 unk7C;
               s8 unk7D;
               s8 unk7E;
               s8 unk7F;
               s8 unk80;
               s8 unk81;
               s8 unk82;
               s8 unk83;
               s8 unk84;
               s8 unk85;
               s8 unk86;
               s8 unk87;
               s8 unk88;
               s8 unk89;
               s8 unk8A;
               s8 unk8B;
               Vec3s unk8C;
               Vec3s unk92;
               Vec3s unk98;
               Vec3s unk9E;
               s16 unkA4;
               s16 unkA6;
               s8 unkA8;
               s8 unkA9;
               s8 unkAA;
               s8 unkAB;
               s16 windWest;
               s16 windVertical;
               s16 windSouth;
               s8 unkB2;
               s8 unkB3;
               f32 windClothIntensity;
               u8 environmentSettingsCount;
               s8 unkB9;
               s8 unkBA;
               s8 unkBB;
               void* environmentSettingsList;
               s8 unkC0;
               u8 unkC1;
               u8 unkC2;
               u8 unkC3;
               RGB unkC4;
               s8 unkC7;
               s8 unkC8;
               s8 unkC9;
               RGB unkCA;
               s8 unkCD;
               s8 unkCE;
               s8 unkCF;
               RGB unkD0;
               RGB unkD3;
               s16 unkD6;
               s16 unkD8;
               s8 unkDA;
               s8 unkDB;
               f32 unkDC;
               u8 unkE0;
               s8 unkE1;
               s8 unkE2;
               s8 unkE3;
               s8 unkE4;
               s8 unkE5;
               s8 unkE6;
               s8 unkE7;
               s8 unkE8;
               s8 unkE9;
               s8 unkEA;
               s8 unkEB;
               s8 unkEC;
               s8 unkED;
               s8 unkEE;
               s8 unkEF;
               s8 unkF0;
               s8 unkF1;
               u8 unkF2[0xC];
} KankyoContext;
typedef struct {
                  View view;
                  void* skyboxStaticSegment[2];
                  char unk170[8];
                  void* skyboxPaletteStaticSegment;
                  Gfx* unk17C;
                  Gfx* unk180;
                  Vtx* roomVtx;
                  DmaRequest unk188;
                  DmaRequest unk1A8;
                  DmaRequest unk1C8;
                  OSMesgQueue loadQueue;
                  OSMesg loadMsg;
                  s16 skyboxShouldDraw;
                  f32 rotX;
                  f32 rotY;
                  f32 rotZ;
                  Vec3f eye;
                  s16 angle;
                  u8 primR;
                  u8 primG;
                  u8 primB;
                  u8 envR;
                  u8 envG;
                  u8 envB;
} SkyboxContext;
typedef struct {
                  View view;
                  Font font;
                  s8 padA7E8[0x7708];
                  u8 unk11EF0;
                  s8 pad11EF1[0x13];
                  u16 unk11F04;
                  s8 pad11F06[0x4];
                  u8 unk11F0A;
                  s8 pad11F0B[0x5];
                  s32 unk11F10;
                  s8 pad11F11[0xD];
                  u8 unk11F22;
                  s8 pad11F23[0xFD];
                  u8 unk12020;
                  s8 pad12021[0x23];
                  s16 unk12044;
                  s8 pad12046[0x24];
                  s16 unk1206A;
                  s8 pad1206C[0x6C];
} MessageContext;
typedef struct {
                 SaveContextPerm perm;
                 SaveContextOwl owl;
                 SaveContextExtra extra;
} SaveContext;
typedef struct {
               BgMeshHeader* sceneMesh;
               Vec3f sceneMin;
               Vec3f sceneMax;
               s32 xSubdivisions;
               s32 ySubdivisions;
               s32 zSubdivisions;
               Vec3f subdivisionSize;
               Vec3f inverseSubdivisionSize;
               BgMeshSubdivision* subdivisions;
               BgScenePolygonLists scenePolyLists;
} StaticCollisionContext;
typedef struct ActorBgMbarChair ActorBgMbarChair;
typedef struct ActorEnBji01 ActorEnBji01;
typedef struct ActorEnTest ActorEnTest;
typedef struct ActorListEntry ActorListEntry;
typedef struct DynaCollisionContext DynaCollisionContext;
typedef struct CollisionContext CollisionContext;
typedef struct ArenaNode_t {
              s16 magic;
              s16 isFree;
              u32 size;
              struct ArenaNode_t* next;
              struct ArenaNode_t* prev;
} ArenaNode;
typedef struct {
               ArenaNode* head;
               void* start;
               OSMesgQueue lock;
               u8 unk20;
               u8 isInit;
               u8 flag;
} Arena;
typedef struct ActorEnBom ActorEnBom;
typedef struct ActorEnFirefly ActorEnFirefly;
typedef struct ActorObjBell ActorObjBell;
typedef struct DaytelopContext DaytelopContext;
typedef struct {
               DynaPolyActor* actor;
               BgMeshHeader* header;
               ActorMeshPolyLists polyLists;
               s16 verticesStartIndex;
               s16 waterboxesStartIndex;
               ActorMeshParams prevParams;
               ActorMeshParams currParams;
               Vec3s averagePos;
               s16 radiusFromAveragePos;
               f32 minY;
               f32 maxY;
} ActorMesh;
struct DynaCollisionContext {
                 u8 unk0;
                 s8 pad1[0x3];
                 ActorMesh actorMeshArr[50];
                 u16 flags[50];
                 BgPolygon* polygons;
                 BgVertex* vertices;
                 BgWaterboxList waterboxes;
                 BgPolygonLinkedList polygonList;
                 u32 maxNodes;
                 u32 maxPolygons;
                 u32 maxVertices;
                 u32 maxMemory;
                 u32 unk141C;
};
struct CollisionContext {
                 StaticCollisionContext stat;
                 DynaCollisionContext dyna;
};
typedef struct ActorBgIknvObj ActorBgIknvObj;
typedef struct FaultAddrConvClient FaultAddrConvClient;
struct FaultAddrConvClient {
              FaultAddrConvClient* next;
              fault_address_converter_func callback;
              void* param;
};
typedef struct FaultClient FaultClient;
struct FaultClient {
              FaultClient* next;
              fault_client_func callback;
              void* param0;
              void* param1;
};
typedef struct {
                OSThread thread;
                u8 stack[1536];
                OSMesgQueue queue;
                OSMesg msg[1];
                u8 exitDebugger;
                u8 msgId;
                u8 faultHandlerEnabled;
                u8 faultActive;
                OSThread* faultedThread;
                fault_update_input_func padCallback;
                FaultClient* clients;
                FaultAddrConvClient* addrConvClients;
                s8 pad7E0[0x4];
                Input padInput[4];
                void* fb;
} FaultThreadStruct;
typedef struct FileChooseContext FileChooseContext;
typedef void(*filechoose_update_func)(FileChooseContext* ctxt);
typedef struct FireObj FireObj;
typedef struct FireObjLight FireObjLight;
typedef struct GameAlloc GameAlloc;
typedef struct GameState GameState;
typedef struct OpeningContext OpeningContext;
typedef struct PreNMIContext PreNMIContext;
typedef struct TitleContext TitleContext;
typedef struct GameAllocNode GameAllocNode;
struct GameAllocNode {
              GameAllocNode* next;
              GameAllocNode* prev;
              u32 size;
              s8 padC[0x4];
};
struct GameAlloc {
               GameAllocNode base;
               GameAllocNode* head;
};
typedef void (*GameStateFunc)(struct GameState* gameState);
struct GameState {
               GraphicsContext* gfxCtx;
               GameStateFunc main;
               GameStateFunc destroy;
               GameStateFunc nextGameStateInit;
               u32 nextGameStateSize;
               Input input[4];
               GameStateHeap heap;
               GameAlloc alloc;
               s8 pad98[0x3];
               u8 running;
               u32 frames;
               s8 padA0[0x2];
               u8 framerateDivisor;
               s8 unkA3;
};
struct OpeningContext {
                GameState common;
                s8 padA4[0x4];
                View view;
};
struct PreNMIContext {
               GameState state;
               u32 timer;
               s32 unkA8;
};
struct TitleContext {
                GameState state;
                u8* nintendo_logo_data;
                View view;
                SramContext sram;
                s8 pad230[0x8];
                s16 unk238;
                s16 logoCoverAlpha;
                s16 logoCoverAlphaChangePerFrame;
                s16 logoFullVisibilityDuration;
                s16 frameCounter;
                s16 frameCounterMod0x80;
                u8 switchToNextGameState;
                s8 pad245[0x3];
};
struct DaytelopContext {
                GameState common;
                s8 padA4[0xC];
                View view;
                s8 pad218[0x28];
                s16 transitionCountdown;
                s16 unk242;
                s16 unk244;
                s8 pad246[0x2];
};
struct FileChooseContext {
                  GameState common;
                  s8 padA4[0x14];
                  View view;
                  SramContext sram;
                  s8 pad240[0x12310];
                  Font unk12550;
                  s8 pad1CBD0[0x78B0];
                  s16 unk24480;
                  s8 pad24482[0x2];
                  s16 unk24484;
                  s16 unk24486;
                  s8 pad24488[0x4];
                  s16 unk2448C;
                  s8 pad2448E[0x1A];
                  s16 unk244A8;
                  s8 pad244AA[0x2];
                  s16 unk244AC;
                  s16 unk244AE;
                  s16 unk244B0;
                  s16 unk244B2;
                  s16 unk244B4;
                  s16 unk244B6;
                  s16 unk244B8;
                  s16 unk244BA;
                  s8 pad244BC[0x18];
                  s16 unk244D4;
                  s8 pad244D6[0x4];
                  s16 unk244DA;
                  s8 pad244DC[0xA];
                  s16 unk244E6;
                  s8 pad244E8[0x8];
                  s16 unk244F0;
                  s16 unk244F2;
                  s8 pad244F4[0x6];
                  s16 inputXChangeCooldown;
                  s16 inputYChangeCooldown;
                  s16 inputXDir;
                  s16 inputYDir;
                  s16 inputX;
                  s16 inputY;
                  s8 pad24506[0x2];
                  s16 unk24508;
                  s16 unk2450A;
                  s8 pad2450C[0x1C];
                  s16 unk24528;
                  s8 pad2452A[0x2E];
};
typedef struct AudioThreadStruct AudioThreadStruct;
typedef struct GlobalContext GlobalContext;
typedef s32 (*ColChkResetFunc)(GlobalContext*, Collider*);
typedef void (*ColChkBloodFunc)(GlobalContext*, Collider*, Vec3f*);
typedef void (*ColChkApplyFunc)(GlobalContext*, CollisionCheckContext*, Collider*);
typedef void (*ColChkVsFunc)(GlobalContext*, CollisionCheckContext*, Collider*, Collider*);
typedef s32 (*ColChkLineFunc)(GlobalContext*, CollisionCheckContext*, Collider*, Vec3f*, Vec3f*);
typedef struct {
              GlobalContext* ctxt;
              s32 type;
              s16 countdown;
              s16 state;
} Quake2Context;
typedef void(*cutscene_update_func)(GlobalContext* ctxt, CutsceneContext* cCtxt);
typedef void(*draw_func)(GlobalContext* ctxt, s16 index);
typedef void(*global_context_func)(GlobalContext*);
typedef void(*light_map_positional_func)(LightMapper* mapper, void* params, GlobalContext* ctxt);
typedef void(*room_draw_func)(GlobalContext* ctxt, Room* room, u32 flags);
typedef struct {
               draw_func unk0;
               u32 unk4;
               u32 unk8;
               u32 unkC;
               u32 unk10;
               u32 unk14;
               u32 unk18;
               u32 unk1C;
               u32 unk20;
} s801BB170;
typedef void(*scene_header_func)(GlobalContext* ctxt, SceneCmd* entry);
typedef void(*scene_proc_draw_func)(GlobalContext* ctxt, u32 segment, void* params);
typedef struct Camera Camera;
typedef struct {
               s16 randIdx;
               s16 countdownMax;
               Camera* cam;
               u32 callbackIdx;
               s16 y;
               s16 x;
               s16 zoom;
               s16 rotZ;
               QuakeRequest14 unk14;
               s16 speed;
               s16 unk1C;
               s16 countdown;
               s16 camPtrIdx;
               s8 pad22[0x2];
} QuakeRequest;
typedef s32(*camera_update_func)(Camera* camera);
typedef s16(*quake_callback_func)(QuakeRequest* req, ShakeInfo* shake);
typedef struct OSMesgQueueListNode_t {
              struct OSMesgQueueListNode_t* next;
              OSMesgQueue* queue;
} OSMesgQueueListNode;
typedef struct {
                OSScMsg verticalRetraceMesg;
                OSScMsg prenmiMsg;
                OSScMsg nmiMsg;
                OSMesgQueue irqQueue;
                OSMesg irqBuffer[8];
                OSThread thread;
                OSMesgQueueListNode* callbacks;
                u8 prenmiStage;
                OSTime lastPrenmiTime;
                OSTimer prenmiTimer;
                OSTime lastFrameTime;
} IrqMgr;
typedef struct {
                u8 controllers;
                s8 pad1[0x13];
                OSContStatus statuses[4];
                s32 unk24;
                OSMesg lockMesg[1];
                OSMesg interrupts[8];
                OSMesgQueue siEventCallbackQueue;
                OSMesgQueue lock;
                OSMesgQueue irqmgrCallbackQueue;
                OSMesgQueueListNode irqmgrCallbackQueueNode;
                IrqMgr* irqmgr;
                OSThread thread;
                Input input[4];
                OSContPad controllerState1[4];
                u8 maxNumControllers;
                s8 pad2C9[0x1B3];
                u8 unk47C;
                u8 unk47D;
                u8 hasStopped;
                s8 pad47F[0x1];
} PadmgrThreadStruct;
typedef struct {
                OSMesgQueue unk0;
                s32 unk18[64];
                OSMesgQueue unk118;
                s32 unk130[8];
                OSThread thread;
                s32 unk300;
                s32 unk304;
                s32 unk308;
                s32 unk30C;
                s32 unk310;
                s32 unk314;
                s32 unk318;
                s8 pad31C[0x4];
                s32 unk320;
                s32 unk324;
                s8 pad328[0x7];
                s8 unk32F;
                OSMesgQueueListNode unk330;
} SchedThreadStruct;
struct AudioThreadStruct {
                IrqMgr* irqmgr;
                SchedThreadStruct* sched;
                s8 pad8[0x58];
                s32 unk60;
                OSMesgQueue irqQueue;
                OSMesg irqBuffer[30];
                OSMesgQueue unkF4;
                s32 unk10C;
                OSMesgQueue initDoneCallback;
                OSMesg initDoneCallbackMsgBuffer[1];
                s8 pad12C[0x4];
                OSThread thread;
};
typedef struct StackEntry_t {
               struct StackEntry_t* next;
               struct StackEntry_t* prev;
               u32 head;
               u32 tail;
               u32 initValue;
               s32 minSpace;
               const char* name;
} StackEntry;
typedef struct TargetContext TargetContext;
typedef struct ActorContext ActorContext;
typedef struct s800B948C s800B948C;
struct FireObjLight {
               z_Light* light;
               LightInfoPositional lightInfo;
               u8 unk12;
};
struct ActorListEntry {
              s32 length;
              Actor* first;
              s8 pad8[0x4];
};
struct Camera {
                s8 pad0[0x4];
                Vec3f unk4;
                s8 pad10[0x8];
                f32 unk18;
                s16 unk1C;
                s16 unk1E;
                Vec3f unk20;
                s8 pad2C[0x2];
                s16 unk2E;
                s8 pad30[0x10];
                s16 unk40;
                s16 unk42;
                s8 pad44[0x8];
                s16 unk4C;
                s8 pad4E[0x2];
                Vec3f focalPoint;
                Vec3f eye;
                Vec3f upDir;
                Vec3f unk74;
                f32 unk80;
                f32 unk84;
                f32 unk88;
                GlobalContext* ctxt;
                ActorPlayer* player;
                PosRot unk94;
                Actor* unkA8;
                Vec3f unkAC;
                s8 padB8[0x8];
                f32 unkC0;
                f32 unkC4;
                f32 unkC8;
                f32 unkCC;
                f32 unkD0;
                f32 unkD4;
                s8 padD8[0x4];
                f32 unkDC;
                f32 unkE0;
                s8 padE4[0x18];
                f32 fov;
                f32 unk100;
                s8 pad104[0x30];
                Vec3s unk134;
                s8 pad13A[0x4];
                u16 unk13E;
                s16 unk140;
                s16 state;
                s16 mode;
                s8 pad146[0x2];
                s16 unk148;
                s16 unk14A;
                s16 unk14C;
                s8 pad14E[0x6];
                s16 unk154;
                s8 pad156[0x4];
                s16 unk15A;
                s16 unk15C;
                s16 unk15E;
                s8 pad160[0x4];
                s16 unk164;
                s16 unk166;
                s8 pad168[0x10];
};
typedef struct {
               z_Matrix displayMatrix;
               Actor* actor;
               Vec3f location;
               u8 flags;
               u8 id;
               u8 red;
               u8 blue;
               u8 green;
               s8 pad55[0x1];
               u16 alpha;
               u16 alphaChange;
               u16 size;
               u16 fadeoutDelay;
               u16 age;
} EffFootmark;
struct FireObj {
               Vec3f position;
               f32 size;
               f32 sizeInv;
               f32 xScale;
               f32 yScale;
               f32 dynamicSize;
               f32 dynamicSizeStep;
               u8 state;
               u8 sizeGrowsCos2;
               u8 unk26;
               u8 unk27;
               u8 flags;
               s8 pad29[0x1];
               s16 ignitionDelay;
               ColliderCylinder collision;
               FireObjLight light;
};
struct TargetContext {
               Vec3f unk0;
               Vec3f unkC;
               f32 unk18;
               f32 unk1C;
               f32 unk20;
               f32 unk24;
               f32 unk28;
               f32 unk2C;
               f32 unk30;
               f32 unk34;
               Actor* unk38;
               Actor* unk3C;
               f32 unk40;
               f32 unk44;
               s16 unk48;
               u8 unk4A;
               u8 unk4B;
               s8 unk4C;
               s8 pad4D[0x3];
               TargetContextEntry unk50[3];
               Actor* unk8C;
               Actor* unk90;
               s8 pad94[0x4];
};
struct s800B948C {
               GlobalContext* ctxt;
               Actor* actor;
               u32 updateActorIfSet;
               u32 unkC;
               Actor* unk10;
               ActorPlayer* player;
               u32 runMainIfSet;
};
struct ActorContext {
                s8 pad0[0x2];
                u8 unk2;
                u8 unk3;
                s8 unk4;
                u8 unk5;
                s8 pad6[0x5];
                s8 unkB;
                s16 unkC;
                u8 totalLoadedActors;
                u8 undrawnActorCount;
                ActorListEntry actorList[12];
                Actor* undrawnActors[32];
                TargetContext targetContext;
                u32 switchFlags[4];
                u32 chestFlags;
                u32 clearedRooms;
                u32 clearedRoomsTemp;
                u32 collectibleFlags[4];
                TitleCardContext titleCtxt;
                u8 unk1F4;
                u8 unk1F5;
                s8 pad1F6[0x2];
                f32 unk1F8;
                Vec3f unk1FC;
                s8 pad208[0x48];
                void* unk250;
                s8 pad254[0x14];
                u8 unk268;
                s8 pad269[0x1B];
};
struct GlobalContext {
                  GameState state;
                  s16 sceneNum;
                  u8 sceneConfig;
                  s8 padA7[0x9];
                  SceneCmd* currentSceneVram;
                  s8 padB4[0x4];
                  View view;
                  Camera activeCameras[4];
                  Camera* cameraPtrs[4];
                  s16 activeCamera;
                  s16 unk812;
                  u8 unk814;
                  u8 unk815;
                  s8 pad816[0x2];
                  LightingContext lightCtx;
                  u32 unk828;
                  s8 pad82C[0x4];
                  CollisionContext colCtx;
                  ActorContext actorCtx;
                  CutsceneContext csCtx;
                  CutsceneEntry* cutsceneList;
                  GlobalContext1F78 unk1F78[16];
                  EffFootmark footmarks[100];
                  SramContext sram;
                  s8 pad46D8[0x8];
                  SkyboxContext skyboxCtx;
                  MessageContext msgCtx;
                  s8 pad169E0[0x8];
                  InterfaceContext interfaceCtx;
                  GlobalContext16D30 unk16D30;
                  u16 unk17000;
                  s8 pad17002[0x2];
                  KankyoContext kankyoContext;
                  AnimationContext animationCtx;
                  SceneContext sceneContext;
                  RoomContext roomContext;
                  u8 transitionActorCount;
                  s8 pad18761[0x3];
                  TransitionActorInit* transitionActorList;
                  s8 pad18768[0x48];
                  z_Matrix unk187B0;
                  s8 pad187F0[0xC];
                  z_Matrix unk187FC;
                  s8 pad1883C[0x4];
                  u32 unk18840;
                  u8 unk18844;
                  u8 unk18845;
                  u16 sceneNumActorsToLoad;
                  u8 numRooms;
                  s8 pad18849[0x3];
                  RoomFileLocation* roomList;
                  ActorEntry* linkActorEntry;
                  ActorEntry* setupActorList;
                  void* unk18858;
                  EntranceEntry* setupEntranceList;
                  void* setupExitList;
                  void* setupPathList;
                  void* unk18868;
                  AnimatedTexture* sceneTextureAnimations;
                  s8 pad18870[0x4];
                  u8 unk18874;
                  s8 unk18875;
                  s8 pad18876[0x4];
                  u16 unk1887A;
                  s8 unk1887C;
                  s8 pad1887D[0x2];
                  u8 unk1887F;
                  s8 pad18880[0x4];
                  CollisionCheckContext colCheckCtx;
                  s8 pad18B20[0x28];
                  u8 curSpawn;
                  s8 pad18B49[0x1];
                  u8 unk18B4A;
                  s8 pad18B4B[0x309];
                  SceneTableEntry* currentSceneTableEntry;
                  s8 pad18E58[0x400];
};
typedef struct {
               s32 unk0;
               s32 unk4;
               s32 unk8;
               s32 unkC;
               s32 unk10;
} struct_801C5F44;
typedef struct {
                Actor base;
                ColliderQuad unk144;
                ColliderQuad unk1C4;
                Vec3f unk244;
                f32 unk250;
                f32 unk254;
                ActorFunc update;
                s16 unk25C;
                u16 unk25E;
                u8 unk260;
                s8 pad261[0x3];
} ActorArrowFire;
struct ActorBgMbarChair {
                Actor base;
                s8 pad144[0x18];
};
struct ActorEnBji01 {
                Actor base;
                s8 pad144[0x170];
};
struct ActorEnBom {
                Actor base;
                ColliderCylinder unk144;
                ColliderJntSph unk190;
                ColliderJntSphElement unk1B0[1];
                s16 unk1F0;
                s8 pad1F2[0x6];
                u8 unk1F8;
                u8 unk1F9;
                s8 pad1FA[0x2];
                u8 unk1FC;
                s8 pad1FD[0x3];
                func_ptr unk200;
};
struct ActorEnFirefly {
                Actor base;
                s8 pad144[0x1C];
                f32 unk160;
                s8 pad164[0x24];
                func_ptr updateFunc;
                s8 type;
                u8 unk18D;
                u8 unk18E;
                u8 unk18F;
                s16 unk190;
                s8 pad192[0x152];
                f32 unk2E4;
                f32 unk2E8;
                f32 unk2EC;
                f32 unk2F0;
                s8 pad2F4[0x28];
                ColliderSphere collision;
};
struct ActorEnTest {
                Actor base;
                s8 pad144[0x10];
                f32 unk154;
                s8 pad158[0xB0];
                u8 unk208;
                s8 pad209[0x1];
                u8 unk20A;
                s8 pad20B[0x1];
                ActorEnTest20C unk20C[20];
};
typedef struct {
                Actor base;
                s8 unk144;
                u8 unk145;
                u16 unk146;
                u16 unk148;
                u16 unk14A;
                u8 unk14C;
                s8 pad14D[0x3];
                ActorFunc unk150;
} ActorEnTest4;
struct ActorObjBell {
                Actor base;
                s8 pad144[0x18];
                ColliderSphere unk15C;
                ColliderSphere unk1B4;
                s8 pad20C[0x2];
                s16 unk20E;
                s8 pad210[0x4];
                s16 unk214;
                s8 pad216[0x12];
};
struct ActorBgIknvObj {
                DynaPolyActor bg;
                ColliderCylinder collision;
                u32 displayListAddr;
                ActorFunc updateFunc;
};
typedef struct {
               u32 type;
               u32 setScissor;
               ColorRGBA8 color;
               ColorRGBA8 envColor;
} struct_801F8010;
typedef struct {
               u32 useRgba;
               u32 setScissor;
               ColorRGBA8 primColor;
               ColorRGBA8 envColor;
} struct_801F8020;
typedef struct {
               u32 unk_00;
               u32 setScissor;
               ColorRGBA8 primColor;
               ColorRGBA8 envColor;
               u16* tlut;
               Gfx* monoDl;
} VisMono;
typedef enum {
    MTXMODE_NEW,
    MTXMODE_APPLY
} MatrixMode;
float fabsf(float f);
#pragma intrinsic(fabsf)
float sqrtf(float f);
#pragma intrinsic(sqrtf)
double sqrt(double d);
#pragma intrinsic(sqrt)
void bootproc(void);
void Idle_ClearMemory(void* begin, void* end);
void Idle_InitFramebuffer(u32* ptr, u32 numBytes, u32 value);
void Idle_InitScreen(void);
void Idle_InitMemory(void);
void Idle_InitCodeAndMemory(void);
void Main_ThreadEntry(void* arg);
void func_8008038C(void);
void Idle_ThreadEntry(void* arg);
void ViConfig_UpdateVi(u32 arg0);
void ViConfig_UpdateBlack(void);
s32 DmaMgr_DMARomToRam(u32 src, void* dst, u32 size);
void DmaMgr_DmaCallback0(OSPiHandle* pOParm1, OSIoMesg* pOParm2, s32 OParm3);
DmaEntry* Dmamgr_FindDmaEntry(u32 vromAddr);
u32 Dmamgr_TranslateVromToRom(u32 vromAddr);
s32 Dmamgr_FindDmaIndex(u32 vromAddr);
char* func_800809F4(u32 param_1);
void DmaMgr_ProcessMsg(DmaRequest* request);
void Dmamgr_ThreadEntry(void* arg);
s32 DmaMgr_SendRequestImpl(DmaRequest* request, void* vramStart, u32 vromStart, u32 size, s32 unused, OSMesgQueue* callback, void* callbackMesg);
s32 DmaMgr_SendRequest0(void* vramStart, u32 vromStart, u32 size);
void Dmamgr_Start(void);
void Dmamgr_Stop(void);
void* Yaz0_FirstDMA(void);
void* Yaz0_NextDMA(void* curSrcPos);
s32 Yaz0_DecompressImpl(u8* hdr, u8* dst);
void Yaz0_Decompress(u32 romStart, void* dst, u32 size);
void IrqMgr_AddClient(IrqMgr* irqmgr, OSMesgQueueListNode* param_2, OSMesgQueue* param_3);
void IrqMgr_RemoveClient(IrqMgr* irqmgr, OSMesgQueueListNode* remove);
void IrqMgr_SendMesgForClient(IrqMgr* irqmgr, OSMesg msg);
void IrqMgr_JamMesgForClient(IrqMgr* irqmgr, OSMesg msg);
void IrqMgr_HandlePreNMI(IrqMgr* irqmgr);
void IrqMgr_CheckStack(void);
void IrqMgr_HandlePRENMI450(IrqMgr* irqmgr);
void IrqMgr_HandlePRENMI480(IrqMgr* irqmgr);
void IrqMgr_HandlePRENMI500(IrqMgr* irqmgr);
void IrqMgr_HandleRetrace(IrqMgr* irqmgr);
void IrqMgr_ThreadEntry(IrqMgr* irqmgr);
void IrqMgr_Create(IrqMgr* irqmgr, void* stack, OSPri pri, u8 retraceCount);
void CIC6105_Nop80081820(void);
void CIC6105_Nop80081828(void);
void CIC6105_PrintRomInfo(void);
void CIC6105_AddRomInfoFaultPage(void);
void CIC6105_RemoveRomInfoFaultPage(void);
void func_800818F4(void);
void Fault_Nop80081920(s32 param_1, ...);
void Fault_Log(char* str, ...);
void Fault_Nop80081958(s32 param_1, ...);
void Fault_SleepImpl(u32 duration);
void Fault_AddClient(FaultClient* client, fault_client_func callback, void* param0, void* param1);
void Fault_RemoveClient(FaultClient* client);
void Fault_AddAddrConvClient(FaultAddrConvClient* client, fault_address_converter_func callback, void* param);
void Fault_RemoveAddrConvClient(FaultAddrConvClient* client);
void* Fault_ConvertAddress(void* addr);
void Fault_Sleep(u32 duration);
void Fault_PadCallback(Input* input);
void Fault_UpdatePadImpl(void);
s32 Fault_WaitForInputImpl(void);
void Fault_WaitForInput(void);
void Fault_DrawRec(s32 x, s32 y, s32 w, s32 h, u16 color);
void Fault_FillScreenBlack(void);
void Fault_FillScreenRed(void);
void Fault_DrawCornerRec(u16 color);
void Fault_PrintFReg(s32 idx, f32* value);
void Fault_LogFReg(s32 idx, f32* value);
void Fault_PrintFPCR(u32 value);
void Fault_LogFPCR(u32 value);
void Fault_PrintThreadContext(OSThread* t);
void Fault_LogThreadContext(OSThread* t);
OSThread* Fault_FindFaultedThread(void);
void Fault_Wait5Seconds(void);
void Fault_WaitForButtonCombo(void);
void Fault_DrawMemDumpPage(char* title, u32* addr, u32 param_3);
void Fault_DrawMemDump(u32 pc, u32 sp, u32 unk0, u32 unk1);
void Fault_FindNextStackCall(u32** sp, u32** pc, u32** ra);
void Fault_DrawStackTrace(OSThread* t, u32 flags);
void Fault_LogStackTrace(OSThread* t, u32 flags);
void Fault_ResumeThread(OSThread* t);
void Fault_CommitFB(void);
void Fault_ProcessClients(void);
void Fault_SetOptionsFromController3(void);
void Fault_SetOptions(void);
void Fault_ThreadEntry(void* arg);
void Fault_SetFB(void* fb, u16 w, u16 h);
void Fault_Start(void);
void Fault_HangupFaultClient(char* arg0, char* arg1);
void Fault_AddHungupAndCrashImpl(char* arg0, char* arg1);
void Fault_AddHungupAndCrash(char* filename, u32 line);
void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled);
void FaultDrawer_DrawRecImpl(s32 xstart, s32 ystart, s32 xend, s32 yend, u16 color);
void FaultDrawer_DrawChar(char c);
s32 FaultDrawer_ColorToPrintColor(u16 color);
void FaultDrawer_UpdatePrintColor(void);
void FaultDrawer_SetForeColor(u16 color);
void FaultDrawer_SetBackColor(u16 color);
void FaultDrawer_SetFontColor(u16 color);
void FaultDrawer_SetCharPad(s8 padW, s8 padH);
void FaultDrawer_SetCursor(s32 x, s32 y);
void FaultDrawer_FillScreen(void);
FaultDrawer* FaultDrawer_FormatStringFunc(FaultDrawer* arg, char* str, s32 count);
void FaultDrawer_VPrintf(char* str, char* args);
void FaultDrawer_Printf(char* fmt, ...);
void FaultDrawer_DrawText(s32 x, s32 y, char* fmt, ...);
void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h);
void FaultDrawer_SetInputCallback(func_ptr func);
void FaultDrawer_Init(void);
void func_80084940(void);
void func_80084968(void);
void Load_Relocate(u32 allocatedVRamAddr, OverlayRelocationSection* overlayInfo, u32 vRamStart);
s32 Load_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 allocatedVRamAddr, u32 allocatedBytes);
void* Load_AllocateAndLoad(u32 vRomStart, u32 vRomEnd, u32 vRamStart);
void Load2_Relocate(u32 allocatedVRamAddr, OverlayRelocationSection* overlayInfo, u32 vRamStart);
s32 Load2_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd, u32 allocatedVRamAddr);
void* Load2_AllocateAndLoad(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd);
void PadUtils_Init(Input* input);
void func_80085150(void);
void PadUtils_ResetPressRel(Input* input);
u32 PadUtils_CheckCurExact(Input* input, u16 value);
u32 PadUtils_CheckCur(Input* input, u16 key);
u32 PadUtils_CheckPressed(Input* input, u16 key);
u32 PadUtils_CheckReleased(Input* input, u16 key);
u16 PadUtils_GetCurButton(Input* input);
u16 PadUtils_GetPressButton(Input* input);
s8 PadUtils_GetCurX(Input* input);
s8 PadUtils_GetCurY(Input* input);
void PadUtils_SetRelXY(Input* input, s32 x, s32 y);
s8 PadUtils_GetRelXImpl(Input* input);
s8 PadUtils_GetRelYImpl(Input* input);
s8 PadUtils_GetRelX(Input* input);
s8 PadUtils_GetRelY(Input* input);
void PadUtils_UpdateRelXY(Input* input);
void StackCheck_Init(StackEntry* entry, void* stackTop, void* stackBottom, u32 initValue, s32 minSpace, const char* name);
void StackCheck_Cleanup(StackEntry* entry);
s32 StackCheck_GetState(StackEntry* entry);
u32 StackCheck_CheckAll(void);
u32 StackCheck_Check(StackEntry* entry);
void func_80085A54(s32 param_1, s32 param_2, s32 param_3);
void assert_fail(char* file, u32 lineNum);
void* StartHeap_AllocMin1(u32 size);
void StartHeap_FreeNull(void* pvParm1);
void func_8008633C(u32 param_1, s32 param_2, s32 param_3, void* param_4);
void func_800863AC(u32 param_1, s32 param_2, s32 param_3, void* param_4);
void StartHeap_Init(u32 base, u32 size);
s32 func_80086620(OSMesgQueue* param_1, PadmgrThreadStruct* param_2, OSContStatus* param_3);
f64 func_80086C7C(f64 param_1);
s32 func_80086C88(f32 param_1);
s32 func_80086C98(f64 param_1);
f64 func_80086CB4(f64 param_1);
s32 func_80086CC0(f32 param_1);
s32 func_80086CD0(f64 param_1);
f64 func_80086CEC(f64 param_1);
s32 func_80086CF8(f32 param_1);
s32 func_80086D08(f64 param_1);
s32 func_80086D30(f32 param_1);
s32 func_80086D40(f64 param_1);
f64 func_80086D6C(f64 param_1);
s32 func_80086D8C(f32 param_1);
s32 func_80086DAC(f64 param_1);
void* StartHeap_Alloc(u32 size);
void* StartHeap_AllocR(u32 size);
void* StartHeap_Realloc(void* oldPtr, u32 newSize);
void StartHeap_Free(void* ptr);
void* StartHeap_Calloc(s32 param_1, s32 param_2);
void StartHeap_AnalyzeArena(u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated);
void StartHeap_InitArena(u32 base, u32 size);
u32 rand(void);
void randSetSeed(u32 seed);
f32 randZeroOne(void);
f32 randPlusMinusPoint5(void);
void func_80087090(s32* param_1);
f32 func_800870B8(u32* param_1);
f32 func_80087104(u32* param_1);
void arena_lock_init(Arena* heap);
void arena_lock(Arena* heap);
void arena_unlock(Arena* heap);
ArenaNode* heap_get_tail(Arena* param_1);
void __osMallocInit(Arena* heap, u32 heapBase, u32 heapSize);
void __osMallocAddBlock(Arena* heap, u32 start, u32 size);
void __osMallocCleanup(Arena* heap);
u32 __osMallocIsInitalized(Arena* heap);
void* __osMalloc(Arena* heap, u32 size);
void* __osMallocR(Arena* heap, u32 size);
void __osFree(Arena* heap, void* ptr);
void* __osRealloc(Arena* heap, void* oldPtr, u32 newSize);
void __osAnalyzeArena(Arena* heap, u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated);
s32 __osCheckArena(Arena* heap);
void* proutSprintf(void* s, char* buf, size_t n);
s32 vsprintf(char* dst, char* fmt, va_list args);
s32 sprintf(char* s, char* fmt, ...);
void wait_cycles(OSTime uParm1);
void func_80087A1C(s32);
void func_80087A6C(u32 param_1);
s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags);
void func_80087E00(u32 param_1);
void osStopThread(OSThread* t);
s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flags);
OSIntMask osSetIntMask(OSIntMask im);
f32 __sinf(f32 __x);
s16 sins(u16 x);
OSTask* _VirtualToPhysicalTask(OSTask* intp);
void osSpTaskLoad(OSTask* intp);
void osSpTaskStartGo(OSTask* tp);
long long __ull_rshift(unsigned long long left, unsigned long long right);
unsigned long long __ull_rem(unsigned long long left, unsigned long long right);
unsigned long long __ull_div(unsigned long long left, unsigned long long right);
long long __ll_lshift(long long left, long long right);
long long __ll_rem(long long left, unsigned long long right);
long long __ll_div(long long left, long long right);
long long __ll_mul(long long left, long long right);
void __ull_divremi(unsigned long long* quotient, unsigned long long* remainder, unsigned long long dividend, unsigned short divisor);
long long __ll_mod(long long left, long long right);
long long __ll_rshift(long long left, long long right);
void __osExceptionPreamble(void);
void __osException(void);
void __osEnqueueAndYield(OSThread** param_1);
void __osEnqueueThread(OSThread** param_1, OSThread* param_2);
OSThread* __osPopThread(OSThread** param_1);
void __osDispatchThread(void);
void __osCleanupThread(void);
void __osDequeueThread(OSThread** param_1, OSThread* param_2);
void osDestroyThread(OSThread* puParm1);
void bzero(void* begin, s32 length);
void __osSiCreateAccessQueue(void);
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 osContInit(OSMesgQueue* mq, u8* bitpattern, OSContStatus* data);
void __osContGetInitData(u8* pattern, OSContStatus* data);
void __osPackRequestData(u8 cmd);
void osCreateThread(OSThread* t, OSId id, osCreateThread_func entry, void* arg, void* sp, OSPri p);
s32 osContStartReadData(OSMesgQueue* mq);
void osContGetReadData(OSContPad* data);
void __osPackReadData(void);
u32 osVirtualToPhysical(void* vaddr);
u32 __osGetSR(void);
void __osSetSR(u32 value);
void osWritebackDCache(void* vaddr, s32 nbytes);
void func_8008A660(void);
void osInitialize(void);
void func_8008A9A8(void);
void* osViGetNextFramebuffer(void);
void guPerspectiveF(float mf[4][4], u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
void guPerspective(Mtx* m, u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
s32 __osSpRawStartDma(s32 direction, u32 devAddr, void* dramAddr, u32 size);
s32 __osSiRawStartDma(s32 direction, void* dramAddr);
void osViBlack(u8 active);
s32 __osSiRawReadIo(u32 devAddr, u32* data);
OSId osGetThreadId(OSThread* t);
void osSpTaskYield(void);
s32 __osPfsRWInode(OSPfs* param_1, __OSInode* param_2, u8 param_3, u8 param_4);
s32 osPfsReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, s32 offset, s32 size_in_bytes, u8* data_buffer);
void guMtxIdentF(float mf[4][4]);
void osViSetMode(OSViMode* modep);
void guLookAtF(float mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void guLookAt(Mtx* m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
s32 osStopTimer(OSTimer* t);
u32 __osProbeTLB(void* param_1);
void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt);
void __osPiCreateAccessQueue(void);
void __osPiGetAccess(void);
void __osPiRelAccess(void);
void __osDevMgrMain(void* arg);
s32 osPiRawStartDma(s32 direction, u32 devAddr, void* dramAddr, u32 size);
u32 osGetCount(void);
u32 osGetMemSize(void);
void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg m);
f32 sqrtf(f32 __x);
s32 osAfterPreNMI(void);
s32 osContStartQuery(OSMesgQueue* mq);
void osContGetQuery(OSContStatus* data);
void guLookAtHiliteF(float mf[4][4], void* l, s32* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 twidth, s32 theight);
void guLookAtHilite(Mtx* m, LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 twidth, s32 theight);
s32 _Printf(printf_func pfn, void* arg, char* fmt, va_list ap);
void _Putfld(_Pft* px, va_list* pap, u8 code, u8* ac);
void osUnmapTLBAll(void);
s32 osEPiStartDma(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction);
u8* strchr(u8* __s, s32 __c);
size_t strlen(u8* __s);
void* memcpy(void* __dest, void* __src, size_t __n);
void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msq, s32 count);
void osInvalICache(void* vaddr, s32 nbytes);
void osInvalDCache(void* vaddr, s32 nbytes);
void __osTimerServicesInit(void);
void __osTimerInterrupt(void);
void __osSetTimerIntr(OSTime tim);
OSTime __osInsertTimer(OSTimer* t);
s32 __osSpDeviceBusy(void);
s32 __osSiDeviceBusy(void);
s32 osJamMesg(OSMesgQueue* mq, OSMesg msg, s32 flag);
void osSetThreadPri(OSThread* t, OSPri pri);
OSPri osGetThreadPri(OSThread* t);
void osViSwapBuffer(void* frameBufPtr);
void guPositionF(float mf[4][4], f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
void guPosition(Mtx* m, f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
void func_800900C0(s8 param_1, s8 param_2, s8 param_3, s8 param_4, s32 param_5);
OSYieldResult osSpTaskYielded(OSTask* task);
s32 memcmp(void* __s1, void* __s2, size_t __n);
OSTime osGetTime(void);
void guRotateF(float mf[4][4], f32 a, f32 x, f32 y, f32 z);
void guRotate(Mtx* m, f32 a, f32 x, f32 y, f32 z);
s32 osAiSetFrequency(u32 frequency);
s32 __osContRamRead(OSMesgQueue* mq, s32 channel, u16 address, u8* buffer);
u8 __osContAddressCrc(u16 addr);
u8 __osContDataCrc(u8* data);
OSThread* __osGetActiveQueue(void);
void guNormalize(float* x, float* y, float* z);
void __osSetCompare(u32 value);
u32 osDpGetStatus(void);
void osDpSetStatus(u32 data);
void bcopy(void* __src, void* __dest, size_t __n);
void guOrthoF(float mf[4][4], f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
void guOrtho(Mtx* m, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
OSIntMask __osDisableInt(void);
void __osRestoreInt(OSIntMask im);
void __osViInit(void);
void __osViSwapContext(void);
OSMesgQueue* osPiGetCmdQueue(void);
f32 __cosf(f32 __x);
void osViSetSpecialFeatures(u32 func);
s16 coss(u16 x);
void osSetTime(OSTime ticks);
void osViSetEvent(OSMesgQueue* mq, OSMesg m, u32 retraceCount);
s32 osPfsIsPlug(OSMesgQueue* queue, u8* pattern);
OSPiHandle* osCartRomInit(void);
s32 osContSetCh(u8 ch);
u32 __osSetFpcCsr(u32 value);
u32 __osGetFpcCsr(void);
u32 osAiGetLength(void);
void osMapTLBRdb(void);
void osYieldThread(void);
u32 __osGetCause(void);
s32 __osContRamWrite(OSMesgQueue* mq, s32 channel, u16 address, u8* buffer, s32 force);
s32 osSetTimer(OSTimer* t, OSTime value, OSTime interval, OSMesgQueue* mq, OSMesg msg);
void _Ldtob(_Pft* px, u8 code);
void _Genld(_Pft* px, u8 code, u8* p, s16 nsig, s16 xexp);
ldiv_t ldiv(long numer, long denom);
lldiv_t lldiv(long long numer, long long denom);
void _Litob(_Pft* px, u8 code);
s32 __osSiRawWriteIo(u32 devAddr, u32 data);
u32 __osSpGetStatus(void);
void __osSpSetStatus(u32 value);
void osCreateViManager(OSPri pri);
void viMgrMain(OSDevMgr* iParm1);
__OSViContext* __osViGetCurrentContext(void);
void osWritebackDCacheAll(void);
OSThread* __osGetCurrFaultedThread(void);
void guMtxF2L(float mf[4][4], Mtx* m);
void osStartThread(OSThread* param_1);
void osViSetYScale(f32 value);
void osViSetXScale(f32 value);
long long __d_to_ll(double d);
long long __f_to_ll(float f);
unsigned long long __d_to_ull(double d);
unsigned long long __f_to_ull(float f);
double __ll_to_d(long long l);
float __ll_to_f(long long l);
double __ull_to_d(unsigned long long l);
float __ull_to_f(unsigned long long l);
s32 __osSpSetPc(u32 data);
void func_80096770(s32 param_1, void* param_2, void* param_3);
void __osSetWatchLo(u32 value);
f32 func_80096830(f32 param_1, f32 param_2);
void* func_80096880(void* param_1, u8 param_2, s32 param_3);
s32 func_800968B0(const char* str1, const char* str2);
char* func_800968f0(char* param_1, char* param_2);
void EnAObj_Init(ActorEnAObj* this, GlobalContext* ctxt);
void EnAObj_Destroy(ActorEnAObj* this, GlobalContext* ctxt);
void EnAObj_Update1(ActorEnAObj* this, GlobalContext* ctxt);
void EnAObj_Update2(ActorEnAObj* this, GlobalContext* ctxt);
void EnAObj_Update(ActorEnAObj* this, GlobalContext* ctxt);
void EnAObj_Draw(ActorEnAObj* this, GlobalContext* ctxt);
void EnItem00_UpdateForNewObjectId(ActorEnItem00* this, GlobalContext* ctxt, f32* puParm3, f32* pfParm4);
void EnItem00_Init(ActorEnItem00* this, GlobalContext* ctxt);
void EnItem00_Destroy(ActorEnItem00* this, GlobalContext* ctxt);
void func_800A63A8(ActorEnItem00* this, GlobalContext* ctxt);
void func_800A640C(ActorEnItem00* this);
void EnItem00_Update1(ActorEnItem00* this, GlobalContext* ctxt);
void EnItem00_Update(ActorEnItem00* this, GlobalContext* ctxt);
void EnItem00_Draw(ActorEnItem00* this, GlobalContext* ctxt);
void EnItem00_DrawRupee(ActorEnItem00* this, GlobalContext* ctxt);
void EnItem00_DrawSprite(ActorEnItem00* actor, GlobalContext* ctxt);
void EnItem00_DrawHeartContainer(ActorEnItem00* actor, GlobalContext* ctxt);
void EffectBlure_Initcommon(EffBlureParams* params);
void EffectBlure_Init1(EffBlureParams* params, EffBlureInit1* init);
void EffectBlure_Init2(EffBlureParams* params, EffBlureInit2* init);
void EffectBlure_Destroy(EffBlureParams* params);
s32 EffectBlure_Update(EffBlureParams* params);
void EffectBlure_Draw(EffBlureParams* params, GraphicsContext* gCtxt);
void EffectShieldParticle_Init(EffShieldParticleParams* params, EffShieldParticleInit* init);
void EffectShieldParticle_Destroy(EffShieldParticleParams* params);
s32 EffectShieldParticle_Update(EffShieldParticleParams* params);
void EffectShieldParticle_CalculateColors(EffShieldParticleParams* params, ColorRGBA8* primColor, ColorRGBA8* envColor);
void EffectShieldParticle_Draw(EffShieldParticleParams* params, GraphicsContext* gCtxt);
void EffectSpark_Init(EffSparkParams* params, EffSparkParams* init);
void EffectSpark_Destroy(EffSparkParams* params);
s32 EffectSpark_Update(EffSparkParams* params);
void EffectSpark_Draw(EffSparkParams* params, GraphicsContext* gCtxt);
void func_800AE434(GlobalContext* ctxt, ColorRGBA8* color, s16 sParm3, s16 sParm4);
void func_800AE5A0(GlobalContext* ctxt);
void func_800AE778(GlobalContext* ctxt, ColorRGBA8* color, s16 param_3, s16 param_4);
void func_800AE8EC(GlobalContext* ctxt);
void func_800AE930(CollisionContext* bgCtxt, s32 param_2, float* param_3, f32 param_4, s16 param_5, BgPolygon* param_6, s32 param_7);
void EffectTireMark_InitParticle(EffTireMarkParticle* particle);
void EffectTireMark_Init(EffTireMarkParams* params, EffTireMarkInit* init);
void EffectTireMark_Destroy(EffTireMarkParams* params);
s32 EffectTireMark_Update(EffTireMarkParams* params);
void EffectTireMark_InitVertices(F3DVertexColor* vertices, EffTireMarkParticle* particle, s32 index, s32 alpha);
void EffectTireMark_Draw(EffTireMarkParams* params, GraphicsContext* gCtxt);
GlobalContext* Effect_GetContext(void);
void* Effect_GetParams(s32 index);
void Effect_InitCommon(EffCommon* common);
void Effect_Init(GlobalContext* ctxt);
void Effect_Add(GlobalContext* ctxt, s32* index, s32 type, u8 param_4, u8 param_5, void* initParams);
void Effect_DrawAll(GraphicsContext* gCtxt);
void Effect_UpdateAll(GlobalContext* ctxt);
void Effect_Destroy(GlobalContext* ctxt, s32 index);
void Effect_DestroyAll(GlobalContext* ctxt);
void EffectSS_Init(GlobalContext* ctxt, s32 numEntries);
void EffectSS_Clear(GlobalContext* ctxt);
LoadedParticleEntry* EffectSS_GetTable(void);
void EffectSS_Delete(LoadedParticleEntry* param_1);
void EffectSS_ResetEntry(LoadedParticleEntry* particle);
s32 EffectSS_FindFreeSpace(u32 priority, u32* tableEntry);
void EffectSS_Copy(GlobalContext* ctxt, LoadedParticleEntry* particle);
void EffectSS_UpdateParticle(GlobalContext* ctxt, s32 index);
void EffectSS_UpdateAllParticles(GlobalContext* ctxt);
void EffectSS_DrawParticle(GlobalContext* ctxt, s32 index);
void EffectSS_DrawAllParticles(GlobalContext* ctxt);
s32 func_800B096C(s16 param_1, s16 param_2, s32 param_3);
s16 func_800B09D0(s16 a0, s16 a1, f32 a2);
u8 func_800B0A24(u8 a0, u8 a1, f32 a2);
void func_800B0B10(GlobalContext* ctxt, LoadedParticleEntry* particle, u32 uParm3);
void EffectSS_SpawnDust(GlobalContext* ctxt, u16 flags, Vec3f* position, Vec3f* velocity, Vec3f* acceleration, ColorRGBA8* color1, ColorRGBA8* color2, s16 scale, s16 scaleChangePerFrame, s16 life, u8 type);
void func_800B32D0(GameState* ctxt);
void DLF_LoadGameState(GameStateOverlay* gameState);
void DLF_FreeGameState(GameStateOverlay* gameState);
void Actor_PrintLists(ActorContext* actCtxt);
void Actor_SetDrawParams(ActorShape* actorShape, f32 yOffset, ActorShadowFunc func, f32 scale);
void Actor_PostDraw(Actor* actor, LightMapper* mapper, GlobalContext* ctxt, u32 displayList, ColorRGBA8* color);
void func_800B3FC0(Actor* actor, LightMapper* mapper, GlobalContext* ctxt);
void func_800B4024(Actor* actor, LightMapper* mapper, GlobalContext* ctxt);
void func_800B4088(Actor* actor, LightMapper* mapper, GlobalContext* ctxt);
void func_800B40B8(Actor* actor, LightMapper* mapper, GlobalContext* ctxt);
void func_800B40E0(GlobalContext* ctxt, s32 iParm2, z_Matrix* pzParm3, s32 iParm4, f32 param_5, f32 param_6, f32 param_7);
void func_800B42F8(Actor* actor, LightMapper* mapper, GlobalContext* ctxt);
void func_800B4AEC(GlobalContext* ctxt, Actor* actor, f32 param_3);
void func_800B4B50(Actor* actor, s32 iParm2, GlobalContext* pzParm3);
void func_800B4EDC(GlobalContext* ctxt, Vec3f* pzParm2, Vec3f* pzParm3, f32* pfParm4);
void func_800B4F78(TargetContext* targetContext, u8 type, GlobalContext* ctxt);
void func_800B5040(TargetContext* targetContext, Actor* actor, u8 type, GlobalContext* ctxt);
void Actor_TargetContextInit(TargetContext* targetCtxt, Actor* actor, GlobalContext* ctxt);
void func_800B5208(TargetContext* targetCtxt, GlobalContext* ctxt);
void func_800B5814(TargetContext* targetContext, ActorPlayer* player, Actor* param_3, GlobalContext* ctxt);
u32 Actor_GetSwitchFlag(GlobalContext* ctxt, s32 flag);
void Actor_SetSwitchFlag(GlobalContext* ctxt, s32 flag);
void Actor_UnsetSwitchFlag(GlobalContext* ctxt, s32 flag);
u32 Actor_GetChestFlag(GlobalContext* ctxt, u32 flag);
void Actor_SetChestFlag(GlobalContext* ctxt, u32 flag);
void Actor_SetAllChestFlag(GlobalContext* ctxt, u32 flags);
u32 Actor_GetAllChestFlag(GlobalContext* ctxt);
u32 Actor_GetRoomCleared(GlobalContext* ctxt, u32 roomNumber);
void Actor_SetRoomCleared(GlobalContext* ctxt, u32 roomNumber);
void Actor_UnsetRoomCleared(GlobalContext* ctxt, u32 roomNumber);
u32 Actor_GetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber);
void Actor_SetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber);
void Actor_UnsetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber);
u32 Actor_GetCollectibleFlag(GlobalContext* ctxt, s32 index);
void Actor_SetCollectibleFlag(GlobalContext* ctxt, s32 index);
void Actor_TitleCardContextInit(GlobalContext* ctxt, TitleCardContext* titleCtxt);
void Actor_TitleCardCreate(GlobalContext* ctxt, TitleCardContext* titleCtxt, u32 texture, s16 param_4, s16 param_5, u8 param_6, u8 param_7);
void Actor_TitleCardUpdate(GlobalContext* ctxt, TitleCardContext* titleCtxt);
void Actor_TitleCardDraw(GlobalContext* ctxt, TitleCardContext* titleCtxt);
void func_800B6468(GlobalContext* ctxt);
void func_800B6474(GlobalContext* ctxt);
f32 func_800B64FC(GlobalContext* ctxt, f32 fParm2, Vec3f* pzParm3, u32* puParm4);
void* func_800B6584(GlobalContext* ctxt, s16 sParm2, void* pvParm3, u32 uParm4);
void Actor_MarkForDeath(Actor* actor);
void Actor_InitCurrPosition(Actor* actor);
void Actor_SetHeight(Actor* actor, f32 height);
void Actor_SetRotationFromDrawRotation(Actor* actor);
void Actor_InitDrawRotation(Actor* actor);
void Actor_SetScale(Actor* actor, f32 scale);
void Actor_SetObjectSegment(GlobalContext* ctxt, Actor* actor);
void Actor_InitToDefaultValues(Actor* actor, GlobalContext* ctxt);
void Actor_FiniActor(Actor* actor, GlobalContext* ctxt);
void Actor_SetMovementScale(s32 scale);
void Actor_ApplyMovement(Actor* actor);
void Actor_SetVelocityYRotationAndGravity(Actor* actor);
void Actor_SetVelocityAndMoveYRotationAndGravity(Actor* actor);
void Actor_SetVelocityXYRotation(Actor* actor);
void Actor_SetVelocityAndMoveXYRotation(Actor* actor);
void Actor_SetVelocityXYRotationReverse(Actor* actor);
void Actor_SetVelocityAndMoveXYRotationReverse(Actor* actor);
void func_800B6C04(Actor* actor, f32 fParm2);
s16 Actor_YawBetweenActors(Actor* from, Actor* to);
s16 Actor_YawBetweenActorsTop(Actor* from, Actor* to);
s16 Actor_YawToPoint(Actor* actor, Vec3f* point);
s16 Actor_PitchBetweenActors(Actor* from, Actor* to);
s16 Actor_PitchBetweenActorsTop(Actor* from, Actor* to);
s16 Actor_PitchToPoint(Actor* actor, Vec3f* point);
f32 Actor_DistanceBetweenActors(Actor* actor1, Actor* actor2);
f32 Actor_DistanceToPoint(Actor* actor, Vec3f* point);
f32 Actor_XZDistanceBetweenActors(Actor* actor1, Actor* actor2);
f32 Actor_XZDistanceToPoint(Actor* actor, Vec3f* point);
void Actor_CalcOffsetOrientedToDrawRotation(Actor* actor, Vec3f* offset, Vec3f* point);
f32 Actor_YDistance(Actor* actor1, Actor* actor2);
void func_800B6F20(GlobalContext* ctxt, s32 param_2, f32 param_3, s16 param_4);
float func_800B6FC8(ActorPlayer* player);
u32 func_800B7200(s32 param_1);
u32 func_800B7298(GlobalContext* ctxt, s32 param_2, u8 param_3);
void func_800B72E0(s32 param_1);
void func_800B72F8(DynaPolyActor* dpactor, f32 a1, s16 a2);
s32 Actor_IsLinkFacingActor(Actor* actor, s16 tolerance, GlobalContext* ctxt);
s32 Actor_IsActorFacedByActor(Actor* actor, Actor* other, s16 tolerance);
s32 Actor_IsActorFacingLink(Actor* actor, s16 angle);
s32 Actor_IsActorFacingActor(Actor* actor, Actor* other, s16 tolerance);
s32 Actor_IsActorFacingLinkAndWithinRange(Actor* actor, f32 range, s16 tolerance);
s32 Actor_IsActorFacingActorAndWithinRange(Actor* actor, Actor* other, f32 range, s16 tolerance);
void func_800B75A0(BgPolygon* param_1, Vec3f* param_2, s16* param_3);
void func_800B78B8(GlobalContext* ctxt, Actor* actor, f32 uParm3, f32 uParm4, f32 param_5, u32 param_6);
s32 func_800B7FE0(f32* param_1, f32* param_2, f32* param_3, GraphicsContext* gCtxt);
void func_800B8050(Actor* actor, GlobalContext* ctxt, s32 iParm3);
void* func_800B8214(PosRot* param_1, Actor* param_2);
f32* func_800B8248(PosRot* param_1, ActorPlayer* param_2);
s32 func_800B84D0(Actor* actor, GlobalContext* ctxt);
void func_800B85E0(Actor* actor, GlobalContext* ctxt, f32 uParm3, s32 uParm4);
void func_800B8614(Actor* actor, GlobalContext* ctxt, f32 uParm3);
void func_800B863C(Actor* actor, GlobalContext* ctxt);
u32 func_800B867C(Actor* actor, GlobalContext* ctxt);
s32 func_800B8708(GlobalContext* ctxt);
void func_800B8898(GlobalContext* ctxt, Actor* actor, void* param_3, void* param_4);
u32 Actor_HasParent(Actor* actor, GlobalContext* ctxt);
void Audio_PlayActorSound2(Actor* actor, u16 sfxId);
void func_800B8F98(Actor* actor, u16 sfxId);
void func_800B9010(Actor* actor, s16 uParm2);
void func_800B9098(Actor* actor);
s32 func_800B90AC(GlobalContext* globalCtx, Actor* actor, s32 arg2, s32 arg3, s32 arg4);
void func_800B9120(ActorContext* actCtxt);
void func_800B9334(GlobalContext* ctxt, ActorContext* actCtxt);
Actor* Actor_UpdateActor(s800B948C* params);
void Actor_UpdateAll(GlobalContext* ctxt, ActorContext* actCtxt);
void Actor_DrawActor(GlobalContext* ctxt, Actor* actor);
void func_800B9D1C(Actor* actor);
void Actor_DrawAllSetup(GlobalContext* ctxt);
s32 Actor_RecordUndrawnActor(GlobalContext* ctxt, Actor* actor);
void func_800B9EF4(GlobalContext* ctxt, s32 numActors, Actor** actors);
s32 func_800BA2D8(GlobalContext* ctxt, Actor* actor);
s32 func_800BA2FC(GlobalContext* ctxt, Actor* actor, Vec3f* param_3, f32 param_4);
void Actor_DrawAll(GlobalContext* ctxt, ActorContext* aCtxt);
void func_800BA6FC(GlobalContext* ctxt, ActorContext* aCtxt);
void func_800BA798(GlobalContext* ctxt, ActorContext* aCtxt);
void func_800BA8B8(GlobalContext* ctxt, ActorContext* actCtxt);
void Actor_InsertIntoTypeList(ActorContext* actCtxt, Actor* actor, u8 type);
Actor* Actor_RemoveFromTypeList(GlobalContext* ctxt, ActorContext* actCtxt, Actor* actor);
void Actor_FreeOverlay(ActorOverlay* entry);
Actor* Actor_Spawn(ActorContext* actCtxt, GlobalContext* ctxt, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 sParm10);
ActorInit* Actor_LoadOverlay(ActorContext* actCtxt, s16 index);
Actor* Actor_SpawnWithParentAndCutscene(ActorContext* actCtxt, GlobalContext* ctxt, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 variable, u32 cutscene, s32 param_12, Actor* parent);
void Actor_SpawnWithParent(ActorContext* actCtxt, Actor* parent, GlobalContext* ctxt, s16 index, f32 x, f32 y, f32 z, s16 rotX, s16 rotY, s16 rotZ, s16 variable);
void Actor_SpawnTransitionActors(GlobalContext* ctxt, ActorContext* actCtxt);
void func_800BB2D0(ActorContext* aCtxt, u16* param_2, GlobalContext* ctxt);
Actor* func_800BB498(ActorContext* actCtxt, Actor* actor, GlobalContext* ctxt);
void func_800BBA88(GlobalContext* ctxt, Actor* iParm2);
void func_800BCBF4(Vec3f* uParm1, GlobalContext* ctxt);
void func_800BCC68(Vec3f* param_1, GlobalContext* ctxt);
void func_800BDC5C(SkelAnime* skelAnime, void* animation, s32 param_3);
void func_800BDFB0(void);
void func_800BDFC0(GlobalContext* ctxt, s32 uParm2);
void func_800BE03C(GlobalContext* ctxt, Gfx* dl);
void ActorOverlayTable_FaultPrint(void* arg0, void* arg1);
void* ActorOverlayTable_FaultAddrConv(void* arg0, void* arg1);
void ActorOverlayTable_Init(void);
void ActorOverlayTable_Cleanup(void);
void BgCheck_PolygonLinkedListNodeInit(BgPolygonLinkedListNode* node, s16* polyIndex, u16 next);
void BgCheck_PolygonLinkedListResetHead(u16* head);
void BgCheck_ScenePolygonListsNodeInsert(BgScenePolygonLists* list, u16* head, s16* polyIndex);
void BgCheck_PolygonLinkedListNodeInsert(BgPolygonLinkedList* list, u16* head, s16* polyIndex);
void BgCheck_PolygonLinkedListInit(GlobalContext* ctxt, BgPolygonLinkedList* list);
void BgCheck_PolygonLinkedListAlloc(GlobalContext* ctxt, BgPolygonLinkedList* list, u32 numNodes);
void BgCheck_PolygonLinkedListReset(BgPolygonLinkedList* list);
u16 BgCheck_AllocPolygonLinkedListNode(BgPolygonLinkedList* list);
void BgCheck_CreateVec3fFromVertex(BgVertex* vertex, Vec3f* vector);
void BgCheck_CreateVertexFromVec3f(BgVertex* vertex, Vec3f* vector);
float func_800BFD84(BgPolygon* polygon, f32 param_2, f32 param_3);
s32 func_800BFDEC(BgPolygon* param_1, BgPolygon* param_2, u32* param_3, u32* param_4);
s32 BgCheck_PolygonGetMinY(BgPolygon* polygons, BgVertex* vertices);
void BgCheck_PolygonGetNormal(BgPolygon* polygon, f32* normalX, f32* normalY, f32* normalZ);
void func_800C0094(BgPolygon* param_1, f32 xOffset, f32 yOffset, f32 zOffset, z_Matrix* matrix);
f32 func_800C01B8(BgPolygon* param_1, Vec3f* param_2);
void BgCheck_CreateTriNormFromPolygon(BgPolygon* polygon, BgVertex* vertices, TriNorm* tri);
void func_800C02C0(BgPolygon* poly, s32 index, CollisionContext* bgCtxt, TriNorm* tri);
void BgCheck_PolygonCollidesWithSphere(BgPolygon* polygon, BgVertex* verticies, Vec3f* pos, f32 readius);
void BgCheck_ScenePolygonListsInsertSorted(CollisionContext* bgCtxt, u16* head, BgPolygon* polygons, BgVertex* vertices, s16 index);
void BgCheck_ScenePolygonListsInsert(BgMeshSubdivision* subdivision, CollisionContext* bgCtxt, BgPolygon* polygons, BgVertex* vertices, s16 index);
void BgCheck_GetPolyMinSubdivisions(CollisionContext* bgCtxt, Vec3f* min, s32* xSubdivision, s32* ySubdivision, s32* zSubdivision);
void BgCheck_GetPolyMaxSubdivisions(CollisionContext* bgCtxt, Vec3f* max, s32* xSubdivision, s32* ySubdivision, s32* zSubdivision);
void BgCheck_GetPolyMinMaxSubdivisions(CollisionContext* bgCtxt, BgVertex* vertices, BgPolygon* polygons, s32* minX, s32* minY, s32* minZ, s32* maxX, s32* maxY, s32* maxZ, s16 index);
u32 BgCheck_SplitScenePolygonsIntoSubdivisions(CollisionContext* bgCtxt, GlobalContext* ctxt, BgMeshSubdivision* subdivisions);
s32 BgCheck_GetIsDefaultSpecialScene(GlobalContext* ctxt);
s32 BgCheck_GetSpecialSceneMaxMemory(s32 sceneId, u32* maxMemory);
void BgCheck_CalcSubdivisionSize(f32 min, s32 subdivisions, f32* max, f32* subdivisionSize, f32* inverseSubdivisionSize);
s32 BgCheck_GetSpecialSceneMaxObjects(GlobalContext* ctxt, u32* maxNodes, u32* maxPolygons, u32* maxVertices);
void BgCheck_Init(CollisionContext* bgCtxt, GlobalContext* ctxt, BgMeshHeader* mesh);
void func_800C3C00(CollisionContext* bgCtxt, u32 param_2);
void func_800C3C14(CollisionContext* bgCtxt, u32 param_2);
BgMeshHeader* BgCheck_GetActorMeshHeader(CollisionContext* bgCtxt, s32 index);
s32 func_800C45C4(CollisionContext* bgCtxt, u32 param_2, Vec3f* param_3, Vec3f* param_4, Vec3f* param_5, f32 param_6, s32* param_7, s32* param_8, DynaPolyActor* param_9, f32 param_10, u8 param_11);
s32 func_800C55C4(CollisionContext*, Vec3f*, Vec3f*, Vec3f*, BgPolygon**, u32, u32, u32, u32, u32*);
s32 func_800C576C(CollisionContext*, Vec3f*, Vec3f*, Vec3f*, BgPolygon**, u32, u32, u32, u32, u32*);
void BgCheck_ScenePolygonListsInit(BgScenePolygonLists* param_1);
void BgCheck_ScenePolygonListsAlloc(GlobalContext* ctxt, BgScenePolygonLists* lists, s32 numNodes, u32 numPolygons);
s32 func_800C5B80(u16* param_1);
u16 BgCheck_ScenePolygonListsReserveNode(BgScenePolygonLists* lists);
void BgCheck_ActorMeshParamsInit(ActorMeshParams* params);
void BgCheck_SetActorMeshParams(ActorMeshParams* params, Vec3f* scale, Vec3s* rotation, Vec3f* position);
s32 BgCheck_AreActorMeshParamsEqual(ActorMeshParams* param_1, ActorMeshParams* param_2);
void BgCheck_ActorMeshPolyListsHeadsInit(ActorMeshPolyLists* lists);
void BgCheck_ActorMeshPolyListsInit(ActorMeshPolyLists* lists);
void BgCheck_ActorMeshVerticesIndexInit(s16* index);
void BgCheck_ActorMeshWaterboxesIndexInit(s16* index);
void BgCheck_ActorMeshInit(GlobalContext* ctxt, ActorMesh* mesh);
void BgCheck_ActorMeshInitFromActor(ActorMesh* actorMesh, DynaPolyActor* actor, BgMeshHeader* header);
s32 BgCheck_HasActorMeshChanged(ActorMesh* mesh);
void BgCheck_PolygonsInit(BgPolygon** polygons);
void BgCheck_PolygonsAlloc(GlobalContext* ctxt, BgPolygon* polygons, u32 numPolygons);
void BgCheck_VerticesInit(BgVertex** vertices);
void BgCheck_VerticesListAlloc(GlobalContext* ctxt, BgVertex** vertices, u32 numVertices);
void BgCheck_WaterboxListInit(BgWaterboxList* waterboxList);
void BgCheck_WaterboxListAlloc(GlobalContext* ctxt, BgWaterboxList* waterboxList, u32 numWaterboxes);
void BgCheck_ActorMeshUpdateParams(GlobalContext* ctxt, ActorMesh* mesh);
s32 BgCheck_IsActorMeshIndexValid(s32 index);
void BgCheck_DynaInit(GlobalContext* ctxt, DynaCollisionContext* param_2);
void BgCheck_DynaAlloc(GlobalContext* ctxt, DynaCollisionContext* dyna);
s32 BgCheck_AddActorMesh(GlobalContext* ctxt, DynaCollisionContext* dyna, DynaPolyActor* actor, BgMeshHeader* header);
DynaPolyActor* BgCheck_GetActorOfMesh(CollisionContext* bgCtxt, s32 index);
void func_800C62BC(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index);
void func_800C6314(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index);
void func_800C636C(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index);
void func_800C63C4(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index);
void func_800C641C(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index);
void func_800C6474(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index);
void BgCheck_RemoveActorMesh(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index);
void BgCheck_CalcWaterboxDimensions(Vec3f* minPos, Vec3f* maxXPos, Vec3f* maxZPos, Vec3s* minPosOut, s16* xLength, s16* zLength);
void BgCheck_AddActorMeshToLists(GlobalContext* ctxt, DynaCollisionContext* dyna, s32 index, s32* currVertices, s32* currPolygons, s32* currWaterboxes);
void BgCheck_ResetFlagsIfLoadedActor(GlobalContext* ctxt, DynaCollisionContext* dyna, Actor* actor);
void BgCheck_Update(GlobalContext* ctxt, DynaCollisionContext* dyna);
void func_800C756C(s32 param_1, s32* param_2, s32* param_3, s32* param_4);
void BgCheck_UpdateAllActorMeshes(GlobalContext* ctxt, DynaCollisionContext* dyna);
void BgCheck_RelocateMeshHeaderPointers(BgMeshHeader* header);
void BgCheck_RelocateMeshHeader(BgMeshHeader* meshSegPtr, BgMeshHeader** param_2);
void BgCheck_RelocateAllMeshHeaders(CollisionContext* bgCtxt, GlobalContext* ctxt);
u32 BgCheck_GetPolygonAttributes(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index, s32 attributeIndex);
u32 func_800C9704(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C99AC(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C99D4(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C99FC(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9A24(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9A4C(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9A7C(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9AB0(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9AE4(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9B18(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9B40(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9B68(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9B90(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9BB8(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9BDC(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9C74(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9C9C(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9CC4(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9CEC(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9D8C(CollisionContext* param_1, BgPolygon* param_2, s32 param_3);
u32 func_800C9E18(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9E40(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
u32 func_800C9E88(CollisionContext* bgCtxt, BgPolygon* polygon, s32 index);
void BgCheck2_UpdateActorPosition(CollisionContext* bgCtxt, s32 index, Actor* actor);
void BgCheck2_UpdateActorYRotation(CollisionContext* bgCtxt, s32 index, Actor* actor);
void BgCheck2_AttachToMesh(CollisionContext* bgCtxt, Actor* actor, s32 index);
u32 BgCheck2_UpdateActorAttachedToMesh(CollisionContext* bgCtxt, s32 index, Actor* actor);
void BcCheck3_BgActorInit(DynaPolyActor* actor, s32 param_2);
void BgCheck3_LoadMesh(GlobalContext* ctxt, DynaPolyActor* actor, BgMeshHeader* meshHeader);
void BgCheck3_ResetFlags(DynaPolyActor* actor);
void func_800CAE88(DynaPolyActor* actor);
void func_800CAE9C(DynaPolyActor* actor);
void func_800CAEB0(CollisionContext* bgCtxt, s32 index);
void func_800CAEE0(DynaPolyActor* actor);
void func_800CAEF4(CollisionContext* bgCtxt, s32 index);
void func_800CAF24(DynaPolyActor* actor);
void func_800CAF38(DynaPolyActor* actor);
s32 func_800CAF4C(DynaPolyActor* actor);
s32 func_800CAF70(DynaPolyActor* actor);
s32 func_800CAF94(DynaPolyActor* actor);
s32 func_800CAFB8(DynaPolyActor* actor);
s32 func_800CAFDC(DynaPolyActor* actor);
f32 Camera_fabsf(f32 f);
f32 Camera_LengthVec3f(Vec3f* v);
f32 Camera_Lerpf(f32 b, f32 a, f32 t, f32 minDist);
s16 Camera_Lerps(s16 b, s16 a, f32 t, s16 minDist);
void Camera_LerpVec3f(Vec3f* b, Vec3f* a, f32 tXZ, f32 tY, f32 minDist);
void func_800CB544(Camera* camera);
f32 func_800CB700(Camera* camera);
s32 Camera_ModeNop(Camera* camera);
s32 Camera_ModeNORM1(Camera* camera);
s32 Camera_ModeNORM2(Camera* camera);
s32 Camera_ModeNORM3(Camera* camera);
s32 Camera_ModeNORM4(Camera* camera);
s32 Camera_ModeNORM0(Camera* camera);
s32 Camera_ModePARA1(Camera* camera);
s32 Camera_ModePARA2(Camera* camera);
s32 Camera_ModePARA3(Camera* camera);
s32 Camera_ModePARA4(Camera* camera);
s32 Camera_ModePARA0(Camera* camera);
s32 Camera_ModeJUMP1(Camera* camera);
s32 Camera_ModeJUMP2(Camera* camera);
s32 Camera_ModeJUMP3(Camera* camera);
s32 Camera_ModeJUMP4(Camera* camera);
s32 Camera_ModeJUMP0(Camera* camera);
s32 Camera_ModeBATT1(Camera* camera);
s32 Camera_ModeBATT2(Camera* camera);
s32 Camera_ModeBATT3(Camera* camera);
s32 Camera_ModeBATT4(Camera* camera);
s32 Camera_ModeBATT0(Camera* camera);
s32 Camera_ModeKEEP1(Camera* camera);
s32 Camera_ModeKEEP2(Camera* camera);
s32 Camera_ModeKEEP3(Camera* camera);
s32 Camera_ModeKEEP4(Camera* camera);
s32 Camera_ModeKEEP0(Camera* camera);
s32 Camera_ModeFIXD1(Camera* camera);
s32 Camera_ModeFIXD2(Camera* camera);
s32 Camera_ModeFIXD3(Camera* camera);
s32 Camera_ModeFIXD4(Camera* camera);
s32 Camera_ModeFIXD0(Camera* camera);
s32 Camera_ModeSUBJ1(Camera* camera);
s32 Camera_ModeSUBJ2(Camera* camera);
s32 Camera_ModeSUBJ3(Camera* camera);
s32 Camera_ModeSUBJ4(Camera* camera);
s32 Camera_ModeSUBJ0(Camera* camera);
s32 Camera_ModeDATA0(Camera* camera);
s32 Camera_ModeDATA1(Camera* camera);
s32 Camera_ModeDATA2(Camera* camera);
s32 Camera_ModeDATA3(Camera* camera);
s32 Camera_ModeDATA4(Camera* camera);
s32 Camera_ModeUNIQ1(Camera* camera);
s32 Camera_ModeUNIQ2(Camera* camera);
s32 Camera_ModeUNIQ3(Camera* camera);
s32 Camera_ModeUNIQ4(Camera* camera);
s32 Camera_ModeUNIQ5(Camera* camera);
s32 Camera_ModeUNIQ0(Camera* camera);
s32 Camera_ModeUNIQ6(Camera* camera);
s32 Camera_ModeUNIQ7(Camera* camera);
s32 Camera_ModeUNIQ8(Camera* camera);
s32 Camera_ModeUNIQ9(Camera* camera);
s32 Camera_ModeDEMO1(Camera* camera);
s32 Camera_ModeDEMO2(Camera* camera);
s32 Camera_ModeDEMO3(Camera* camera);
s32 Camera_ModeDEMO4(Camera* camera);
s32 Camera_ModeDEMO5(Camera* camera);
s32 Camera_ModeDEMO6(Camera* camera);
s32 Camera_ModeDEMO7(Camera* camera);
s32 Camera_ModeDEMO8(Camera* camera);
s32 Camera_ModeDEMO9(Camera* camera);
s32 Camera_ModeDEMO0(Camera* camera);
s32 Camera_ModeSPEC0(Camera* camera);
s32 Camera_ModeSPEC1(Camera* camera);
s32 Camera_ModeSPEC2(Camera* camera);
s32 Camera_ModeSPEC3(Camera* camera);
s32 Camera_ModeSPEC4(Camera* camera);
s32 Camera_ModeSPEC5(Camera* camera);
s32 Camera_ModeSPEC6(Camera* camera);
s32 Camera_ModeSPEC7(Camera* camera);
s32 Camera_ModeSPEC8(Camera* camera);
s32 Camera_ModeSPEC9(Camera* camera);
Camera* Camera_Alloc(View* view, CollisionContext* bg, GlobalContext* ctxt);
void Camera_Free(Camera* camera);
void Camera_Init(Camera* camera, View* view, CollisionContext* bg, GlobalContext* ctxt);
void func_800DE0EC(Camera* camera, Actor* actor);
Vec3s* Camera_Update(Vec3s* param_1, Camera* camera);
u32 Camera_SetMode(Camera* camera, s16 mode, s8 param_3);
s32 func_800DFAC8(Camera* camera, s16 param_2);
u32 func_800DFB14(Camera* camera, u32 param_2);
s32 func_800DFC68(Camera* camera);
s16 func_800DFCB4(Camera* camera);
s16 func_800DFCDC(Camera* camera);
s16 Camera_SetFlags(Camera* iParm1, s16 flags);
s16 Camera_ClearFlags(Camera* camera, s16 flags);
void func_800E0348(Camera* camera);
DamageTable* DamageTable_Get(s32 index);
void DamageTable_Clear(DamageTable* damageTable);
f32 CollisionCheck_GetDamageAndEffectOnBumper(Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo, u32* effect);
f32 CollisionCheck_ApplyBumperDefense(f32 damage, ColliderInfo* ac);
s32 CollisionCheck_GetToucherDamage(Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo);
s32 Collider_InitBase(GlobalContext* ctxt, Collider* collider);
s32 Collider_DestroyBase(GlobalContext* ctxt, Collider* collider);
s32 Collider_SetBaseToActor(GlobalContext* ctxt, Collider* collider, ColliderInitToActor* src);
s32 Collider_SetBaseType1(GlobalContext* ctxt, Collider* collider, Actor* actor, ColliderInitType1* src);
s32 Collider_SetBase(GlobalContext* ctxt, Collider* collider, Actor* actor, ColliderInit* src);
void Collider_ResetATBase(GlobalContext* ctxt, Collider* collider);
void Collider_ResetACBase(GlobalContext* ctxt, Collider* collider);
void Collider_ResetOCBase(GlobalContext* ctxt, Collider* collider);
s32 Collider_InitTouch(GlobalContext* ctxt, ColliderTouch* touch);
s32 Collider_DestroyTouch(GlobalContext* ctxt, ColliderTouch* touch);
s32 Collider_SetTouch(GlobalContext* ctxt, ColliderTouch* touch, ColliderTouchInit* src);
void Collider_ResetATInfoUnk(GlobalContext* ctxt, ColliderInfo* info);
s32 Collider_InitBump(GlobalContext* ctxt, ColliderBump* bump);
s32 Collider_DestroyBump(GlobalContext* ctxt, ColliderBump* bump);
s32 Collider_SetBump(GlobalContext* ctxt, ColliderBump* bump, ColliderBumpInit* src);
s32 Collider_InitInfo(GlobalContext* ctxt, ColliderInfo* info);
s32 Collider_DestroyInfo(GlobalContext* ctxt, ColliderInfo* info);
s32 Collider_SetInfo(GlobalContext* ctxt, ColliderInfo* info, ColliderInfoInit* src);
void Collider_ResetATInfo(GlobalContext* ctxt, ColliderInfo* info);
void Collider_ResetACInfo(GlobalContext* ctxt, ColliderInfo* info);
void Collider_ResetOCInfo(GlobalContext* ctxt, ColliderInfo* info);
s32 Collider_InitJntSphElementDim(GlobalContext* ctxt, ColliderJntSphElementDim* dim);
s32 Collider_DestroyJntSphElementDim(GlobalContext* ctxt, ColliderJntSphElementDim* dim);
s32 Collider_SetJntSphElementDim(GlobalContext* ctxt, ColliderJntSphElementDim* dest, ColliderJntSphElementDimInit* src);
s32 Collider_InitJntSphElement(GlobalContext* ctxt, ColliderJntSphElement* element);
s32 Collider_DestroyJntSphElement(GlobalContext* ctxt, ColliderJntSphElement* element);
s32 Collider_SetJntSphElement(GlobalContext* ctxt, ColliderJntSphElement* dest, ColliderJntSphElementInit* src);
s32 Collider_ResetJntSphElementAT(GlobalContext* ctxt, ColliderJntSphElement* collider);
s32 Collider_ResetJntSphElementAC(GlobalContext* ctxt, ColliderJntSphElement* collider);
s32 Collider_ResetJntSphElementOC(GlobalContext* ctxt, ColliderJntSphElement* collider);
s32 Collider_InitJntSph(GlobalContext* ctxt, ColliderJntSph* collider);
s32 Collider_FreeJntSph(GlobalContext* ctxt, ColliderJntSph* collider);
s32 Collider_DestroyJntSph(GlobalContext* ctxt, ColliderJntSph* collider);
s32 Collider_SetJntSphToActor(GlobalContext* ctxt, ColliderJntSph* collider, ColliderJntSphInitToActor* src);
s32 Collider_SetJntSphAllocType1(GlobalContext* ctxt, ColliderJntSph* sphereGroup, Actor* actor, ColliderJntSphInitType1* src);
s32 Collider_SetJntSph(GlobalContext* ctxt, ColliderJntSph* sphereGroup, Actor* actor, ColliderJntSphInit* src, ColliderJntSphElement* elements);
s32 Collider_InitAndSetJntSph(GlobalContext* ctxt, ColliderJntSph* sphereGroup, Actor* actor, ColliderJntSphInit* src, ColliderJntSphElement* elements);
s32 Collider_ResetJntSphAT(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetJntSphAC(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetJntSphOC(GlobalContext* ctxt, Collider* collider);
s32 Collider_InitCylinderDim(GlobalContext* ctxt, Cylinder16* dim);
s32 Collider_DestroyCylinderDim(GlobalContext* ctxt, Cylinder16* dim);
s32 Collider_SetCylinderDim(GlobalContext* ctxt, Cylinder16* dim, Cylinder16* src);
s32 Collider_InitCylinder(GlobalContext* ctxt, ColliderCylinder* collider);
s32 Collider_DestroyCylinder(GlobalContext* ctxt, ColliderCylinder* collider);
s32 Collider_SetCylinderToActor(GlobalContext* ctxt, ColliderCylinder* collider, ColliderCylinderInitToActor* src);
s32 Collider_SetCylinderType1(GlobalContext* ctxt, ColliderCylinder* collider, Actor* actor, ColliderCylinderInitType1* src);
s32 Collider_SetCylinder(GlobalContext* ctxt, ColliderCylinder* collider, Actor* actor, ColliderCylinderInit* src);
s32 Collider_InitAndSetCylinder(GlobalContext* ctxt, ColliderCylinder* collider, Actor* actor, ColliderCylinderInit* src);
s32 Collider_ResetCylinderAT(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetCylinderAC(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetCylinderOC(GlobalContext* ctxt, Collider* collider);
s32 Collider_InitTrisElementDim(GlobalContext* ctxt, TriNorm* dim);
s32 Collider_DestroyTrisElementDim(GlobalContext* ctxt, TriNorm* dim);
s32 Collider_SetTrisElementDim(GlobalContext* ctxt, TriNorm* dim, ColliderTrisElementDimInit* src);
s32 Collider_InitTrisElement(GlobalContext* ctxt, ColliderTrisElement* element);
s32 Collider_DestroyTrisElement(GlobalContext* ctxt, ColliderTrisElement* element);
s32 Collider_SetTrisElement(GlobalContext* ctxt, ColliderTrisElement* element, ColliderTrisElementInit* src);
s32 Collider_ResetTrisElementAT(GlobalContext* ctxt, ColliderTrisElement* element);
s32 Collider_ResetTrisElementAC(GlobalContext* ctxt, ColliderTrisElement* element);
s32 Collider_ResetTrisElementOC(GlobalContext* ctxt, ColliderTrisElement* element);
s32 Collider_InitTris(GlobalContext* ctxt, ColliderTris* tris);
s32 Collider_FreeTris(GlobalContext* ctxt, ColliderTris* tris);
s32 Collider_DestroyTris(GlobalContext* ctxt, ColliderTris* tris);
s32 Collider_SetTrisAllocType1(GlobalContext* ctxt, ColliderTris* tris, Actor* actor, ColliderTrisInitType1* src);
s32 Collider_SetTris(GlobalContext* ctxt, ColliderTris* triGroup, Actor* actor, ColliderTrisInit* src, ColliderTrisElement* tris);
s32 Collider_InitAndSetTris(GlobalContext* ctxt, ColliderTris* tris, Actor* actor, ColliderTrisInit* src, ColliderTrisElement* elements);
s32 Collider_ResetTrisAT(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetTrisAC(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetTrisOC(GlobalContext* ctxt, Collider* collider);
s32 Collider_InitQuadDim(GlobalContext* ctxt, ColliderQuadDim* dim);
s32 Collider_DestroyQuadDim(GlobalContext* ctxt, ColliderQuadDim* dim);
s32 Collider_ResetQuadACDist(GlobalContext* ctxt, ColliderQuadDim* dim);
void Collider_SetQuadMidpoints(ColliderQuadDim* dim);
s32 Collider_SetQuadDim(GlobalContext* ctxt, ColliderQuadDim* dim, ColliderQuadDimInit* init);
s32 Collider_InitQuad(GlobalContext* ctxt, ColliderQuad* collider);
s32 Collider_DestroyQuad(GlobalContext* ctxt, ColliderQuad* collider);
s32 Collider_SetQuadType1(GlobalContext* ctxt, ColliderQuad* collider, Actor* actor, ColliderQuadInitType1* src);
s32 Collider_SetQuad(GlobalContext* ctxt, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src);
s32 Collider_InitAndSetQuad(GlobalContext* ctxt, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src);
s32 Collider_ResetQuadAT(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetQuadAC(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetQuadOC(GlobalContext* ctxt, Collider* collider);
s32 Collider_QuadSetNearestAC(GlobalContext* ctxt, ColliderQuad* quad, Vec3f* hitPos);
s32 Collider_InitSphere(GlobalContext* ctxt, ColliderSphere* collider);
s32 Collider_DestroySphere(GlobalContext* ctxt, ColliderSphere* collider);
s32 Collider_SetSphere(GlobalContext* ctxt, ColliderSphere* collider, Actor* actor, ColliderSphereInit* src);
s32 Collider_InitAndSetSphere(GlobalContext* ctxt, ColliderSphere* collider, Actor* actor, ColliderSphereInit* src);
s32 Collider_ResetSphereAT(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetSphereAC(GlobalContext* ctxt, Collider* collider);
s32 Collider_ResetSphereOC(GlobalContext* ctxt, Collider* collider);
s32 Collider_InitLine(GlobalContext* ctxt, OcLine* line);
s32 Collider_DestroyLine(GlobalContext* ctxt, OcLine* line);
s32 Collider_SetLinePoints(GlobalContext* ctxt, OcLine* line, Vec3f* a, Vec3f* b);
s32 Collider_SetLine(GlobalContext* ctxt, OcLine* line, OcLine* src);
s32 Collider_ResetLineOC(GlobalContext* ctxt, OcLine* line);
void CollisionCheck_InitContext(GlobalContext* ctxt, CollisionCheckContext* colCtxt);
void CollisionCheck_DestroyContext(GlobalContext* ctxt, CollisionCheckContext* colCtxt);
void CollisionCheck_ClearContext(GlobalContext* ctxt, CollisionCheckContext* colCtxt);
void CollisionCheck_EnableSAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt);
void CollisionCheck_DisableSAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt);
s32 CollisionCheck_SetAT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
s32 CollisionCheck_SetAT_SAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider, s32 index);
s32 CollisionCheck_SetAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
s32 CollisionCheck_SetAC_SAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider, s32 index);
s32 CollisionCheck_SetOC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
s32 CollisionCheck_SetOC_SAC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider, s32 index);
s32 CollisionCheck_SetOCLine(GlobalContext* ctxt, CollisionCheckContext* colCtxt, OcLine* line);
s32 CollisionCheck_SkipTouch(ColliderInfo* info);
s32 CollisionCheck_SkipBump(ColliderInfo* info);
s32 CollisionCheck_NoSharedFlags(ColliderInfo* toucher, ColliderInfo* bumper);
void CollisionCheck_NoBlood(GlobalContext* ctxt, Collider* collider, Vec3f* v);
void CollisionCheck_BlueBlood(GlobalContext* ctxt, Collider* collider, Vec3f* v);
void CollisionCheck_GreenBlood(GlobalContext* ctxt, Collider* collider, Vec3f* v);
void CollisionCheck_WaterBurst(GlobalContext* ctxt, Collider* collider, Vec3f* v);
void CollisionCheck_RedBlood(GlobalContext* ctxt, Collider* collider, Vec3f* v);
void CollisionCheck_RedBloodUnused(GlobalContext* ctxt, Collider* collider, Vec3f* v);
void CollisionCheck_HitSolid(GlobalContext* ctxt, ColliderInfo* info, Collider* collider, Vec3f* hitPos);
s32 CollisionCheck_SwordHitAudio(Collider* at, ColliderInfo* acInfo);
void CollisionCheck_HitEffects(GlobalContext* ctxt, Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo, Vec3f* hitPos);
void CollisionCheck_SetBounce(Collider* at, Collider* ac);
s32 CollisionCheck_SetATvsAC(GlobalContext* ctxt, Collider* at, ColliderInfo* atInfo, Vec3f* atPos, Collider* ac, ColliderInfo* acInfo, Vec3f* acPos, Vec3f* hitPos);
void CollisionCheck_TrisAvgPoint(ColliderTrisElement* tri, Vec3f* avg);
void CollisionCheck_QuadAvgPoint(ColliderQuad* quad, Vec3f* avg);
void CollisionCheck_AC_JntSphVsJntSph(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_JntSphVsCyl(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_JntSphVsTris(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_JntSphVsQuad(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_JntSphVsSphere(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_CylVsJntSph(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_CylVsCyl(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_CylVsTris(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_CylVsQuad(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_CylVsSphere(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsJntSph(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsCyl(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsTris(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsQuad(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsSphere(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsJntSph(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsCyl(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsTris(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsQuad(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsSphere(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_SphereVsJntSph(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_SphereVsCylinder(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_SphereVsTris(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_SphereVsQuad(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_SphereVsSphere(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_SetJntSphHitFX(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetCylHitFX(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetTrisHitFX(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetQuadHitFX(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetSphereHitFX(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetHitEffects(GlobalContext* ctxt, CollisionCheckContext* colCtxt);
void CollisionCheck_AC(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* colAT);
void CollisionCheck_AT(GlobalContext* ctxt, CollisionCheckContext* colCtxt);
s32 CollisionCheck_GetMassType(u8 mass);
void CollisionCheck_SetOCvsOC(GlobalContext* ctxt, Collider* left, ColliderInfo* leftInfo, Vec3f* leftPos, Collider* right, ColliderInfo* rightInfo, Vec3f* rightPos, f32 overlap);
void CollisionCheck_OC_JntSphVsJntSph(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_JntSphVsCyl(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_JntSphVsSphere(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_CylVsJntSph(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_CylVsCyl(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_CylVsSphere(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_SphereVsJntSph(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_SphereVsCyl(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_SphereVsSphere(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
s32 CollisionCheck_SkipOC(Collider* collider);
s32 CollisionCheck_Incompatible(Collider* left, Collider* right);
void CollisionCheck_OC(GlobalContext* ctxt, CollisionCheckContext* colCtxt);
void CollisionCheck_InitInfo(CollisionCheckInfo* info);
void CollisionCheck_ResetDamage(CollisionCheckInfo* info);
void CollisionCheck_SetInfoNoDamageTable(CollisionCheckInfo* info, CollisionCheckInfoInit* init);
void CollisionCheck_SetInfo(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit* init);
void CollisionCheck_SetInfo2(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit2* init);
void CollisionCheck_SetInfoGetDamageTable(CollisionCheckInfo* info, s32 index, CollisionCheckInfoInit2* init);
void CollisionCheck_ApplyDamage(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider, ColliderInfo* info);
void CollisionCheck_ApplyDamageJntSph(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageCyl(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageTris(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageQuad(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageSphere(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_Damage(GlobalContext* ctxt, CollisionCheckContext* colCtxt);
s32 CollisionCheck_LineOC_JntSph(GlobalContext* globalCtx, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a, Vec3f* b);
s32 CollisionCheck_LineOC_Cyl(GlobalContext* globalCtx, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a, Vec3f* b);
s32 CollisionCheck_LineOC_Sphere(GlobalContext* globalCtx, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a, Vec3f* b);
s32 CollisionCheck_LineOC(GlobalContext* globalCtx, CollisionCheckContext* colChkCtx, Vec3f* a, Vec3f* b, Actor** exclusions, s32 numExclusions);
s32 CollisionCheck_LineOCCheckAll(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Vec3f* a, Vec3f* b);
s32 CollisionCheck_LineOCCheck(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Vec3f* a, Vec3f* b, Actor** exclusions, s32 numExclusions);
void Collider_UpdateCylinder(Actor* actor, ColliderCylinder* collider);
void Collider_SetCylinderPosition(ColliderCylinder* collider, Vec3s* pos);
void Collider_SetQuadVertices(ColliderQuad* collider, Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* d);
void Collider_SetTrisVertices(ColliderTris* collider, s32 index, Vec3f* a, Vec3f* b, Vec3f* c);
void Collider_SetTrisDim(GlobalContext* ctxt, ColliderTris* collider, s32 index, ColliderTrisElementDimInit* init);
void Collider_UpdateSpheres(s32 limb, ColliderJntSph* collider);
void Collider_UpdateSpheresElement(ColliderJntSph* collider, s32 index, Actor* actor);
void Collider_UpdateSphere(s32 limb, ColliderSphere* collider);
void CollisionCheck_SpawnRedBlood(GlobalContext* ctxt, Vec3f* v);
void CollisionCheck_SpawnWaterDroplets(GlobalContext* ctxt, Vec3f* v);
void CollisionCheck_SpawnShieldParticles(GlobalContext* ctxt, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesMetal(GlobalContext* ctxt, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesMetalSound(GlobalContext* ctxt, Vec3f* v, Vec3f* pos);
void CollisionCheck_SpawnShieldParticlesMetal2(GlobalContext* ctxt, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesWood(GlobalContext* ctxt, Vec3f* v, Vec3f* pos);
s32 CollisionCheck_CylSideVsLineSeg(f32 radius, f32 height, f32 offset, Vec3f* actorPos, Vec3f* itemPos, Vec3f* itemProjPos, Vec3f* out1, Vec3f* out2);
void func_800E8EA0(GlobalContext* ctxt, Actor* actor, u16 param_3);
s32 nop_800E8ED0(s32 param_1);
void nop_800E8EE0(s32 param_1);
s32 nop_800E8EEC(s32 param_1);
void nop_800E8EFC(s32 param_1);
s32 func_800E8F08(Vec3s* param_1, Vec3s* param_2);
s32 func_800E8FA4(Actor* actor, Vec3f* param_2, Vec3s* param_3, Vec3s* param_4);
s32 func_800E9138(GlobalContext* ctxt, Actor* actor, Vec3s* param_3, Vec3s* param_4, f32 param_5);
s32 func_800E9250(GlobalContext* ctxt, Actor* actor, Vec3s* param_3, Vec3s* param_4, Vec3f param_5);
u8 func_800E9360(void);
void DebugDisplay_AddObject(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX, f32 scaleY, f32 scaleZ, u8 red, u8 green, u8 blue, u8 alpha, s16 type, GraphicsContext* gfxCtx);
void DebugDisplay_DrawObjects(GlobalContext* globalCtx);
void func_800E9F78(GraphicsContext* gCtxt);
void Cutscene_Init(GlobalContext* ctxt, CutsceneContext* csCtx);
void func_800EA0D4(GlobalContext* ctxt, CutsceneContext* csCtx);
void func_800EA0EC(GlobalContext* ctxt, CutsceneContext* csCtx);
void Cutscene_StepCutscene1(GlobalContext* ctxt, CutsceneContext* csCtx);
void Cutscene_StepCutscene2(GlobalContext* ctxt, CutsceneContext* csCtx);
void Cutscene_Nop800EA210(GlobalContext* ctxt, CutsceneContext* csCtx);
s32 func_800EA220(GlobalContext* ctxt, CutsceneContext* csCtx, f32 target);
void func_800EA258(GlobalContext* ctxt, CutsceneContext* csCtx);
void func_800EA2B8(GlobalContext* ctxt, CutsceneContext* csCtx);
void func_800EA324(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EABAC(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdEnvLighting* cmd);
void func_800EAC08(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdMusicChange* cmd);
void func_800EAC44(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdMusicChange* cmd);
void func_800EAC94(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdMusicFade* cmd);
void func_800EAD14(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EAD48(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EAD7C(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EADB0(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EAECC(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EAF20(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdUnk190* cmd);
void func_800EAFE0(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdUnk9B* cmd);
void func_800EB1DC(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdDayTime* cmd);
void func_800EB364(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EB4B4(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EB6F8(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EBB68(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EBCD0(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EBD60(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdBase* cmd);
s32 func_800EC678(GlobalContext* ctxt, CsCmdUnk5A* cmd);
void func_800EC924(GlobalContext* ctxt, CutsceneContext* csCtx, CsCmdTextbox* cmd);
void func_800ECD7C(CutsceneContext* csCtx, u8** cutscenePtr, s16 index);
void Cutscene_ProcessCommands(GlobalContext* ctxt, CutsceneContext* csCtx, u8* cutscenePtr, u16* commandReadHead);
void func_800ED980(GlobalContext* ctxt, CutsceneContext* csCtx);
void func_800ED9C4(GlobalContext* ctxt, CutsceneContext* csCtx);
void func_800EDA04(GlobalContext* ctxt, CutsceneContext* csCtx);
void func_800EDA84(GlobalContext* ctxt, CutsceneContext* csCtx);
void func_800EDBE0(GlobalContext* ctxt);
void nop_800EDDB0(GlobalContext* ctxt);
void func_800EDDCC(GlobalContext* ctxt, u32 uParm2);
void func_800EDE34(Actor* actor, GlobalContext* ctxt, s32 param_3);
void func_800EDF78(Actor* actor, GlobalContext* ctxt, s32 iParm3);
void func_800EE0CC(Actor* actor, GlobalContext* ctxt, s32 iParm3);
u32 func_800EE200(GlobalContext* ctxt, u32 uParm2);
u32 func_800EE29C(GlobalContext* ctxt, u32 uParm2);
u32 func_800EE2F4(GlobalContext* ctxt);
void func_800EE320(GlobalContext* ctxt, s16 index);
void func_800EE364(GlobalContext* ctxt, s16 index);
void func_800EE400(GlobalContext* ctxt, s16 index);
void func_800EE5FC(GlobalContext* ctxt, s16 index);
void func_800EE7D8(GlobalContext* ctxt, s16 index);
void func_800EE940(GlobalContext* ctxt, s16 index);
void func_800EEA48(GlobalContext* ctxt, s16 index);
void func_800EEC18(GlobalContext* ctxt, s16 index);
void func_800EED20(GlobalContext* ctxt, s16 index);
void func_800EEE34(GlobalContext* ctxt, s16 index);
void func_800EEF4C(GlobalContext* ctxt, s16 index);
void func_800EF054(GlobalContext* ctxt, s16 index);
void func_800EF0F0(GlobalContext* ctxt, s16 index);
void func_800EF1F4(GlobalContext* ctxt, s16 index);
void func_800EF2AC(GlobalContext* ctxt, s16 index);
void func_800EF364(GlobalContext* ctxt, s16 index);
void func_800EF4D4(GlobalContext* ctxt, s16 index);
void func_800EF65C(GlobalContext* ctxt, s16 index);
void func_800EF780(GlobalContext* ctxt, s16 index);
void func_800EF89C(GlobalContext* ctxt, s16 index);
void func_800EF984(GlobalContext* ctxt, s16 index);
void func_800EFAB8(GlobalContext* ctxt, s16 index);
void func_800EFBFC(GlobalContext* ctxt, s16 index);
void func_800EFD44(GlobalContext* ctxt, s16 index);
void EffFootmark_Init(GlobalContext* ctxt);
void EffFootmark_Add(GlobalContext* ctxt, z_Matrix* displayMatrix, Actor* actor, u8 id, Vec3f* location, u16 size, u8 red, u8 green, u8 blue, u16 alpha, u16 alphaChange, u16 fadeoutDelay);
void EffFootmark_Update(GlobalContext* ctxt);
void EffFootmark_Draw(GlobalContext* ctxt);
void func_800F0390(GlobalContext* ctxt);
void func_800F03C0(GlobalContext* ctxt);
void func_800F048C(GlobalContext* ctxt, Vec3f* param_2, u8 param_3, u16 param_4, u8 param_5);
void func_800F12D0(GlobalContext* ctxt);
void func_800F1304(GlobalContext* ctxt, s16 param_2);
void func_800F1374(s32 param_1, s16 param_2);
s16 func_800F1460(s16 param_1);
ActorCutscene* ActorCutscene_GetCutsceneImpl(s16 index);
void ActorCutscene_Init(GlobalContext* ctxt, ActorCutscene* cutscenes, s32 num);
void func_800F15D8(Camera* camera);
void ActorCutscene_SetIntentToPlay(s16 index);
s16 ActorCutscene_GetCanPlayNext(s16 index);
s16 ActorCutscene_StartAndSetUnkLinkFields(s16 index, Actor* actor);
s16 ActorCutscene_StartAndSetFlag(s16 index, Actor* actor);
s16 ActorCutscene_Start(s16 index, Actor* actor);
s16 ActorCutscene_Stop(s16 index);
ActorCutscene* ActorCutscene_GetCutscene(s16 index);
s16 ActorCutscene_GetAdditionalCutscene(s16 index);
s16 ActorCutscene_GetLength(s16 index);
void ActorCutscene_SetReturnCamera(s16 index);
void FireObj_InitWithParams(GlobalContext* ctxt, FireObj* fire, FireObjInitParams* init);
void FireObj_SetState(FireObj* fire, f32 dynamicSizeStep, u8 newState);
void FireObj_SetPosition(FireObj* fire, Vec3f* pos);
void FireObj_StepSize(FireObj* fire);
void FireObj_UpdateStateTransitions(GlobalContext* ctxt, FireObj* fire);
void FireObj_Draw(GlobalContext* ctxt, FireObj* fire);
void FireObj_InitLight(GlobalContext* ctxt, FireObjLight* light, u8* param_3, Vec3f* pos);
void FireObj_FiniLight(GlobalContext* ctxt, FireObjLight* light);
void FireObj_UpdateLight(GlobalContext* ctxt, FireObjLight* light, FireObj* fire);
void FireObj_Init(GlobalContext* ctxt, FireObj* fire, FireObjInitParams* init, Actor* actor);
void FireObj_Fini(GlobalContext* ctxt, FireObj* fire);
void FireObj_SetState2(FireObj* fire, f32 dynamicSizeStep, u8 newState);
void FireObj_Update(GlobalContext* ctxt, FireObj* fire);
void func_800F40A0(GlobalContext* ctxt, s32 param_2);
void func_800F4A10(GlobalContext* ctxt);
void func_800F4C0C(GlobalContext* ctxt);
void func_800F4E20(GlobalContext* ctxt);
void func_800F4F28(GlobalContext* ctxt);
void Kanfont_Nop800F4F40(GlobalContext* ctxt, s32 param_2, s32 param_3);
void Kanfont_LoadAsciiChar(GlobalContext* ctxt, u8 character, s32 iParm3);
void Kanfont_LoadMessageBoxEnd(Font* font, u16 type);
void Kanfont_LoadOrderedFont(Font* font);
void Kankyo_Init(GlobalContext* ctxt, KankyoContext* kanCtxt);
u32 func_800F5954(u8* param_1, u32 param_2, u32 param_3, u8 param_4, u8 param_5);
void func_800F6B44(GlobalContext* ctxt, KankyoContext* kanCtxt, s32 iParm3, s32 iParm4, s16* param_5);
void func_800F6FF8(GlobalContext* ctxt, KankyoContext* kanCtxt, LightingContext* lCtxt);
void func_800FB320(GlobalContext* ctxt, u8 param_2);
void func_800FBF3C(GlobalContext* ctxt);
void func_800FD538(RGB* param_1, RGB* param_2, f32 param_3, Vec3s* param_4);
void func_800FD59C(GlobalContext* ctxt, RGB* pzParm2, f32 fParm3);
void func_800FD5E0(GlobalContext* ctxt, RGB* pzParm2, f32 fParm3);
void func_800FD654(GlobalContext* ctxt, RGB* pzParm2, f32 fParm3);
void func_800FD78C(GlobalContext* ctxt);
void func_800FD858(GlobalContext* ctxt);
void func_800FD928(s32 param_1);
u32 func_800FE4B8(GlobalContext* ctxt);
void func_800FEAB0(void);
void* Lib_bcopy(void* dst, void* src, size_t n);
s32* Lib_MemSet(s32* buffer, s32 value, u32 size);
f32 Math_Coss(s16 angle);
f32 Math_Sins(s16 angle);
s32 Lib_StepTowardsGet_i(s32 start, s32 value, s32 step);
void Lib_StepTowards_i(s32* start, s32 value, s32 step);
s32 Lib_StepTowardsCheck_i(s32* start, s32 value, s32 step);
s32 Lib_StepTowardsCheckFramerateScaled_s(s16* start, s16 target, s16 step);
s32 Lib_StepTowardsCheck_s(s16* start, s16 target, s16 step);
s32 Lib_StepTowardsCheck_c(s8* start, s8 target, s8 step);
s32 Lib_StepTowardsCheck_f(f32* start, f32 target, f32 step);
s16 Math_Rand_S16Offset(s16 base, s16 range);
s16 Math_Rand_S16OffsetStride(s16 base, s16 stride, s16 range);
void Math_Vec3f_Copy(Vec3f* dest, Vec3f* src);
void Math_Vec3s_Copy(Vec3s* dest, Vec3s* src);
void Math_Vec3s_ToVec3f(Vec3f* dest, Vec3s* src);
void Math_Vec3f_ToVec3s(Vec3s* dest, Vec3f* src);
void Math_Vec3f_Sum(Vec3f* l, Vec3f* r, Vec3f* dest);
void Math_Vec3f_Diff(Vec3f* l, Vec3f* r, Vec3f* dest);
void Math_Vec3s_DiffToVec3f(Vec3f* dest, Vec3s* l, Vec3s* r);
void Math_Vec3f_Scale(Vec3f* vec, f32 scale);
void Math_Vec3f_ScaleAndStore(Vec3f* vec, f32 scale, Vec3f* dest);
void Math_Vec3f_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dest);
void Math_Vec3f_SumScaled(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest);
void Math_Vec3f_ModifyRand(Vec3f* orig, f32 scale, Vec3f* dest);
void Math_Vec3f_DistXYZAndStoreNormalizedDiff(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest);
f32 Math_Vec3f_DistXYZ(Vec3f* a, Vec3f* b);
f32 Math_Vec3f_DistXYZAndStoreDiff(Vec3f* a, Vec3f* b, Vec3f* difference);
f32 Math_Vec3f_DistXZ(Vec3f* a, Vec3f* b);
f32 Math_Vec3f_DistXZAndStore(Vec3f* a, Vec3f* b, f32* xDiff, f32* zDiff);
f32 Math_Vec3f_PushAwayXZ(Vec3f* start, Vec3f* pusher, f32 distanceToApproach);
f32 Math_Vec3f_DiffY(Vec3f* a, Vec3f* b);
s16 Math_Vec3f_Yaw(Vec3f* from, Vec3f* to);
s16 Math_Vec3f_Pitch(Vec3f* from, Vec3f* to);
void Actor_ProcessInitChain(Actor* actor, InitChainEntry* init);
void IChain_Apply_u8(u8* actor, InitChainEntry* init);
void IChain_Apply_s8(u8* actor, InitChainEntry* init);
void IChain_Apply_u16(u8* actor, InitChainEntry* init);
void IChain_Apply_s16(u8* actor, InitChainEntry* init);
void IChain_Apply_u32(u8* actor, InitChainEntry* init);
void IChain_Apply_s32(u8* actor, InitChainEntry* init);
void IChain_Apply_f32(u8* actor, InitChainEntry* init);
void IChain_Apply_f32div1000(u8* actor, InitChainEntry* init);
void IChain_Apply_Vec3f(u8* actor, InitChainEntry* init);
void IChain_Apply_Vec3fdiv1000(u8* actor, InitChainEntry* init);
void IChain_Apply_Vec3s(u8* actor, InitChainEntry* init);
f32 Math_SmoothScaleMaxMinF(f32* a0, f32 a1, f32 a2, f32 a3, f32 a4);
void Math_SmoothScaleMaxF(f32* start, f32 target, f32 scale, f32 maxStep);
void Math_SmoothDownscaleMaxF(f32* start, f32 scale, f32 maxStep);
s32 Math_SmoothScaleMaxMinS(s16* start, s16 target, s16 scale, s16 maxStep, s16 minStep);
void Math_SmoothScaleMaxS(s16* start, s16 target, s16 scale, s16 maxStep);
void Color_RGBA8_Copy(ColorRGBA8* dst, ColorRGBA8* src);
void func_801000A4(u16 param_1);
void func_801000CC(u16 param_1);
void func_801000F4(s32 param_1, u16 param_2);
void Lib_TranslateAndRotateYVec3f(Vec3f* translation, s16 rotation, Vec3f* src, Vec3f* dst);
void Lib_LerpRGB(RGB* a, RGB* b, f32 t, RGB* dst);
f32 Lib_PushAwayVec3f(Vec3f* start, Vec3f* pusher, f32 distanceToApproach);
void Lib_Nop801004FC(void);
void* Lib_PtrSegToVirt(void* ptr);
void* Lib_PtrSegToVirtNull(void* ptr);
void* Lib_PtrSegToK0(void* ptr);
void* Lib_PtrSegToK0Null(void* ptr);
void LifeMeter_Init(GlobalContext* ctxt);
void LifeMeter_UpdateColors(GlobalContext* ctxt);
void LifeMeter_Draw(GlobalContext* ctxt);
void LifeMeter_UpdateSizeAndBeep(GlobalContext* ctxt);
void Lights_InitPositionalLight(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius, u32 type);
void Lights_InitType0PositionalLight(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius);
void Lights_InitType2PositionalLight(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ, u8 red, u8 green, u8 blue, s16 radius);
void Lights_SetPositionalLightColorAndRadius(LightInfoPositional* info, u8 red, u8 green, u8 blue, s16 radius);
void Lights_SetPositionalLightPosition(LightInfoPositional* info, s16 posX, s16 posY, s16 posZ);
void Lights_InitDirectional(LightInfoDirectional* info, s8 dirX, s8 dirY, s8 dirZ, u8 red, u8 green, u8 blue);
void Lights_MapperInit(LightMapper* mapper, u8 red, u8 green, u8 blue);
void Lights_UploadLights(LightMapper* mapper, GraphicsContext* gCtxt);
Light* Lights_MapperGetNextFreeSlot(LightMapper* mapper);
void Lights_MapPositionalWithReference(LightMapper* mapper, LightInfoPositionalParams* params, Vec3f* pos);
void Lights_MapPositional(LightMapper* mapper, LightInfoPositionalParams* params, GlobalContext* ctxt);
void Lights_MapDirectional(LightMapper* mapper, LightInfoDirectionalParams* params, GlobalContext* ctxt);
void Lights_MapLights(LightMapper* mapper, z_Light* lights, Vec3f* refPos, GlobalContext* ctxt);
z_Light* Lights_FindFreeSlot(void);
void Lights_Free(z_Light* light);
void Lights_Init(GlobalContext* ctxt, LightingContext* lCtxt);
void Lights_SetAmbientColor(LightingContext* lCtxt, u8 red, u8 green, u8 blue);
void func_80102544(LightingContext* lCtxt, u8 a1, u8 a2, u8 a3, s16 sp12, s16 sp16);
LightMapper* Lights_CreateMapper(LightingContext* lCtxt, GraphicsContext* gCtxt);
void Lights_ClearHead(GlobalContext* ctxt, LightingContext* lCtxt);
void Lights_RemoveAll(GlobalContext* ctxt, LightingContext* lCtxt);
z_Light* Lights_Insert(GlobalContext* ctxt, LightingContext* lCtxt, LightInfo* info);
void Lights_Remove(GlobalContext* ctxt, LightingContext* lCtxt, z_Light* light);
LightMapper* func_801026E8(GraphicsContext* gCtxt, u8 ambientRed, u8 ambientGreen, u8 ambientBlue, u8 numLights, u8 red, u8 green, u8 blue, s8 dirX, s8 dirY, s8 dirZ);
LightMapper* Lights_MapperAllocateAndInit(GraphicsContext* gCtxt, u8 red, u8 green, u8 blue);
void func_80102880(GlobalContext* ctxt);
void func_80102A64(GlobalContext* ctxt);
void* zelda_malloc(u32 size);
void* zelda_mallocR(u32 size);
void* zelda_realloc(void* oldPtr, u32 newSize);
void zelda_free(void* param_1);
void* zelda_calloc(u32 num, u32 size);
void MainHeap_AnalyzeArena(u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated);
void MainHeap_Init(u32 base, u32 size);
void func_80102EB4(u32 param_1);
void func_80102ED0(u32 param_1);
void func_80104CF4(GlobalContext* ctxt);
void func_8010549C(GlobalContext* ctxt, void* segmentAddress);
void func_8010565C(GlobalContext* ctxt, u8 num, void* segmentAddress);
void func_80105818(GlobalContext* ctxt, u32 uParm2, TransitionActorInit* puParm3);
s32 func_8010A000(GlobalContext* ctxt);
void func_8010A2DC(GlobalContext* ctxt);
void func_8010A33C(GlobalContext* ctxt, s16 param_2);
f32 CamMath_Distance(Vec3f* a, Vec3f* b);
f32 CamMath_DistanceAndDiff(Vec3f* a, Vec3f* b, Vec3f* diff);
f32 CamMath_DistanceXZ(Vec3f* a, Vec3f* b);
f32 func_8010C304(f32 a, f32 b);
f32 func_8010C36C(f32 a, f32 b);
void Interface_ChangeAlpha(u16 param_1);
u32 func_80112E80(GlobalContext* ctxt, u8 param_2);
void func_80115844(GlobalContext* ctxt, s16 param_2);
void func_801159c0(s16 param_1);
void func_8011C808(GlobalContext* ctxt);
void func_80121FC4(GlobalContext* ctxt);
s32 func_801224E0(s32 param_1, s16 param_2, s16 param_3);
void func_80122868(GlobalContext* globalCtx, ActorPlayer* player);
void func_801229A0(GlobalContext* globalCtx, ActorPlayer* player);
void func_8012301C(s32 iParm1, GlobalContext* ctxt);
void func_80123140(GlobalContext* ctxt, ActorPlayer* param_2);
u32 func_80123358(GlobalContext* ctxt, ActorPlayer* player);
u32 func_801233E4(GlobalContext* ctxt);
s32 func_80123590(GlobalContext* ctxt, Actor* actor);
void func_80123DA4(ActorPlayer* player);
u32 func_8012403C(GlobalContext* ctxt);
void func_8012404C(GlobalContext* ctxt);
s32 func_801240C8(ActorPlayer* player);
void func_80126440(GlobalContext* globalCtx, Collider* param_2, s32* param_3, Vec3f* param_4, Vec3f* param_5);
void PreNMI_Stop(PreNMIContext* prenmiCtx);
void PreNMI_Update(PreNMIContext* prenmiCtx);
void PreNMI_Draw(PreNMIContext* prenmiCtx);
void PreNMI_Main(PreNMIContext* prenmiCtx);
void PreNMI_Destroy(PreNMIContext* prenmiCtx);
void PreNMI_Init(PreNMIContext* prenmiCtx);
void Quake_UpdateShakeInfo(QuakeRequest* req, ShakeInfo* shake, f32 y, f32 x);
s16 Quake_Callback1(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback5(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback6(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback3(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback2(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback4(QuakeRequest* req, ShakeInfo* shake);
QuakeRequest* Quake_AddImpl(Camera* cam, u32 callbackIdx);
void Quake_Remove(QuakeRequest* req);
QuakeRequest* Quake_GetRequest(s16 idx);
QuakeRequest* Quake_SetValue(s16 idx, s16 valueType, s16 value);
u32 Quake_SetSpeed(s16 idx, s16 value);
u32 Quake_SetCountdown(s16 idx, s16 value);
s16 Quake_GetCountdown(s16 idx);
u32 Quake_SetQuakeValues(s16 idx, s16 y, s16 x, s16 zoom, s16 rotZ);
u32 Quake_SetUnkValues(s16 idx, s16 arg1);
s16 Quake_Add(Camera* cam, u32 callbackIdx);
u32 Quake_RemoveFromIdx(s16 idx);
s16 Quake_Calc(Camera* camera, UnkQuakeCalcStruct* camData);
void Quake2_Init(GlobalContext* ctxt);
void Quake2_SetCountdown(s16 countdown);
void Quake2_SetType(s16 type);
void Quake2_ClearType(s16 type);
u32 Quake2_GetFloorQuake(ActorPlayer* player);
Gfx* Gfx_SetFog(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_SetFogWithSync(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_SetFog2(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_CallSetupDLImpl(Gfx* gfx, u32 i);
Gfx* Gfx_CallSetupDL(Gfx* gfx, u32 i);
void Gfx_CallSetupDLAtPtr(Gfx** gfxp, u32 i);
Gfx* func_8012BFC4(Gfx* gfx);
Gfx* func_8012BFEC(Gfx* gfx);
Gfx* func_8012C014(Gfx* gfx);
void func_8012C058(GraphicsContext* gCtxt);
void func_8012C080(GraphicsContext* gCtxt);
void func_8012C0A8(GraphicsContext* gCtxt);
void func_8012C0D0(GraphicsContext* gCtxt);
void func_8012C0F8(GraphicsContext* gCtxt);
void func_8012C120(GraphicsContext* gCtxt);
void func_8012C148(GraphicsContext* gCtxt);
void func_8012C170(GraphicsContext* gCtxt);
Gfx* func_8012C198(Gfx* gfx);
void func_8012C1C0(GraphicsContext* gCtxt);
Gfx* func_8012C1EC(Gfx* gfx);
void func_8012C214(GraphicsContext* gCtxt);
void func_8012C240(GraphicsContext* gCtxt);
void func_8012C268(GlobalContext* ctxt);
void func_8012C28C(GraphicsContext* gCtxt);
Gfx* func_8012C2B4(Gfx* gfx);
void func_8012C2DC(GraphicsContext* gCtxt);
Gfx* func_8012C304(Gfx* gfx);
void func_8012C32C(GraphicsContext* gCtxt);
void func_8012C354(GraphicsContext* gCtxt);
void func_8012C37C(GraphicsContext* gCtxt);
Gfx* func_8012C3A4(Gfx* gfx);
Gfx* func_8012C3CC(Gfx* gfx);
void func_8012C3F4(GraphicsContext* gCtxt);
void func_8012C420(GraphicsContext* gCtxt);
void func_8012C448(GraphicsContext* gCtxt);
void func_8012C470(GraphicsContext* gCtxt);
Gfx* func_8012C498(Gfx* gfx);
void func_8012C4C0(GraphicsContext* gCtxt);
void func_8012C4E8(GraphicsContext* gCtxt);
void func_8012C510(GraphicsContext* gCtxt);
void func_8012C538(GraphicsContext* gCtxt);
void func_8012C560(GraphicsContext* gCtxt);
void func_8012C588(GraphicsContext* gCtxt);
void func_8012C5B0(GraphicsContext* gCtxt);
void func_8012C5D8(GraphicsContext* gCtxt);
Gfx* func_8012C600(Gfx* gfx);
void func_8012C628(GraphicsContext* gCtxt);
void func_8012C654(GraphicsContext* gCtxt);
void func_8012C680(Gfx** gfxp);
void func_8012C6AC(GraphicsContext* gCtxt);
void func_8012C6D4(GraphicsContext* gCtxt);
void func_8012C6FC(GraphicsContext* gCtxt);
Gfx* func_8012C724(Gfx* gfx);
Gfx* func_8012C74C(Gfx* gfx);
Gfx* func_8012C774(Gfx* gfx);
Gfx* func_8012C7B8(Gfx* gfx);
Gfx* func_8012C7FC(Gfx* gfx);
Gfx* func_8012C840(Gfx* gfx);
Gfx* func_8012C868(Gfx* gfx);
void func_8012C8AC(GraphicsContext* gCtxt);
void func_8012C8D4(GraphicsContext* gCtxt);
void func_8012C8FC(GraphicsContext* gCtxt);
void func_8012C924(GraphicsContext* gCtxt);
void func_8012C94C(GraphicsContext* gCtxt);
void func_8012C974(GraphicsContext* gCtxt);
void func_8012C9BC(GraphicsContext* gCtxt);
void func_8012C9E4(GraphicsContext* gCtxt);
void func_8012CA0C(Gfx** gfxp);
void func_8012CA38(GraphicsContext* gCtxt);
Gfx* Gfx_BranchTexScroll(Gfx** gfxp, u32 x, u32 y, s32 width, s32 height);
void func_8012CB04(Gfx** gfxp, u32 x, u32 y);
Gfx* func_8012CB28(GraphicsContext* gfxCtx, u32 x, u32 y);
Gfx* Gfx_TexScroll(GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height);
Gfx* Gfx_TwoTexScroll(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2);
Gfx* Gfx_TwoTexScrollEnvColor(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2, s32 r, s32 g, s32 b, s32 a);
Gfx* Gfx_EnvColor(GraphicsContext* gfxCtx, s32 r, s32 g, s32 b, s32 a);
Gfx* Gfx_PrimColor(GraphicsContext* gfxCtx, s32 lodfrac, s32 r, s32 g, s32 b, s32 a);
void func_8012CF0C(GraphicsContext* gCtxt, s32 iParm2, s32 iParm3, u8 r, u8 g, u8 b);
void func_8012D374(GraphicsContext* gCtxt, u8 r, u8 g, u8 b);
void func_8012D40C(f32* param_1, f32* param_2, s16* param_3);
void Room_nop8012D510(GlobalContext* ctxt, Room* room, void* param_3, s8 param_4);
void Room_DrawType3Mesh(GlobalContext* ctxt, Room* room, u32 flags);
void Room_DrawType0Mesh(GlobalContext* ctxt, Room* room, u32 flags);
void Room_DrawType2Mesh(GlobalContext* ctxt, Room* room, u32 flags);
void func_8012DEE8(GlobalContext* ctxt, Room* room, u32 flags);
u32 func_8012E254(s32 param_1, GlobalContext* ctxt);
void func_8012E32C(GlobalContext* ctxt, Room* room, u32 flags);
void Room_DrawType1Mesh(GlobalContext* ctxt, Room* room, u32 flags);
void Room_Init(GlobalContext* ctxt, RoomContext* roomCtxt);
u32 Room_AllocateAndLoad(GlobalContext* ctxt, RoomContext* roomCtxt);
s32 Room_StartRoomTransition(GlobalContext* ctxt, RoomContext* roomCtxt, s32 index);
s32 Room_HandleLoadCallbacks(GlobalContext* ctxt, RoomContext* roomCtxt);
void Room_Draw(GlobalContext* ctxt, Room* room, u32 flags);
void func_8012EBF8(GlobalContext* ctxt, RoomContext* roomCtxt);
u32 func_8012EC80(GlobalContext* ctxt);
void func_8012ED34(s16 param_1);
s32 Scene_LoadObject(SceneContext* sceneCtxt, s16 id);
void Scene_Init(GlobalContext* ctxt, SceneContext* sceneCtxt);
void Scene_ReloadUnloadedObjects(SceneContext* sceneCtxt);
s32 Scene_FindSceneObjectIndex(SceneContext* sceneCtxt, s16 id);
s32 Scene_IsObjectLoaded(SceneContext* sceneCtxt, s32 index);
void Scene_DmaAllObjects(SceneContext* sceneCtxt);
void* func_8012F73C(SceneContext* sceneCtxt, s32 iParm2, s16 id);
void Scene_HeaderCommand00(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand01(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand02(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand03(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand04(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand06(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand07(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand08(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand0A(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand0B(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand0C(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand0D(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand0E(GlobalContext* ctxt, SceneCmd* entry);
void func_8012FEBC(GlobalContext* ctxt, u8* nbTransitionActors);
void Scene_HeaderCommand0F(GlobalContext* ctxt, SceneCmd* entry);
s32 func_8012FF10(GlobalContext* ctxt, s32 fileIndex);
void Scene_HeaderCommand11(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand12(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand10(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand05(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand13(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand09(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand15(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand16(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand18(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand17(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand1B(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand1C(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand1D(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand1E(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand19(GlobalContext* ctxt, SceneCmd* entry);
void Scene_HeaderCommand1A(GlobalContext* ctxt, SceneCmd* entry);
void func_801306A4(GlobalContext* ctxt);
s32 Scene_ProcessHeader(GlobalContext* ctxt, SceneCmd* header);
u32 Scene_CreateEntrance(u32 sceneIndex, u32 spawnIndex, u32 offset);
void func_80130784(u32 spawnIndex);
void SceneProc_DrawCurrentSceneAnimatedTextures(GlobalContext* ctxt);
void SceneProc_DrawSceneConfig0(GlobalContext* ctxt);
Gfx* SceneProc_SetTile1Layer(GlobalContext* ctxt, ScrollingTextureParams* params);
void SceneProc_DrawType0Texture(GlobalContext* ctxt, u32 segment, ScrollingTextureParams* params);
Gfx* SceneProc_SetTile2Layers(GlobalContext* ctxt, ScrollingTextureParams* params);
void SceneProc_DrawType1Texture(GlobalContext* ctxt, u32 segment, ScrollingTextureParams* params);
void SceneProc_DrawFlashingTexture(GlobalContext* ctxt, u32 segment, FlashingTexturePrimColor* primColor, RGBA8* envColor);
void SceneProc_DrawType2Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params);
s32 SceneProc_Lerp(s32 a, s32 b, f32 t);
void SceneProc_DrawType3Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params);
f32 SceneProc_Interpolate(u32 numKeyFrames, f32* keyFrames, f32* values, f32 frame);
u8 SceneProc_InterpolateClamped(u32 numKeyFrames, f32* keyFrames, f32* values, f32 frame);
void SceneProc_DrawType4Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params);
void SceneProc_DrawType5Texture(GlobalContext* ctxt, u32 segment, CyclingTextureParams* params);
void SceneProc_DrawAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, f32 flashingAlpha, u32 step, u32 flags);
void SceneProc_DrawAllSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures);
void SceneProc_DrawOpaqueSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures);
void SceneProc_DrawTranslucentSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures);
void SceneProc_DrawAllSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha);
void SceneProc_DrawOpaqueSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha);
void SceneProc_DrawTranslucentSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha);
void SceneProc_DrawAllAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step);
void SceneProc_DrawOpaqueAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step);
void SceneProc_DrawTranslucentAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step);
void SceneProc_DrawAllAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha, u32 step);
void SceneProc_DrawOpaqueAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha, u32 step);
void SceneProc_DrawTranslucentAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha, u32 step);
void SceneProc_DrawSceneConfig1(GlobalContext* ctxt);
void SceneProc_DrawSceneConfig3(GlobalContext* ctxt);
void SceneProc_DrawSceneConfig4(GlobalContext* ctxt);
void SceneProc_DrawSceneConfig2(GlobalContext* ctxt);
void func_80131DF0(GlobalContext* ctxt, u32 param_2, u32 flags);
void func_80131E58(GlobalContext* ctxt, u32 param_2, u32 flags);
void SceneProc_DrawSceneConfig5(GlobalContext* ctxt);
void SceneProc_DrawSceneConfig7(GlobalContext* ctxt);
void SceneProc_DrawSceneConfig6(GlobalContext* ctxt);
EntranceRecord* SceneTable_LookupEntrance(u32 entrance);
s32 SceneTable_LookupEntranceScene(u32 entrance);
s32 SceneTable_LookupEntranceAbsoluteScene(u32 entrance);
s16 func_801323A0(u32 entrance);
void SkelAnime_LodDrawLimb(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex);
void SkelAnime_LodDraw(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex);
void SkelAnime_LodDrawLimbSV(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor, s32 dListIndex, RSPMatrix** mtx);
void SkelAnime_LodDrawSV(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount, OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor, s32 dListIndex);
void SkelAnime_DrawLimb(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor);
void SkelAnime_Draw(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor);
void SkelAnime_DrawLimbSV(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, RSPMatrix** limbMatricies);
void SkelAnime_DrawSV(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor);
void func_80134148(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor, RSPMatrix** mtx);
void func_801343C0(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor);
void SkelAnime_AnimateFrame(AnimationHeader* animationSeg, s32 currentFrame, s32 limbCount, Vec3s* dst);
s16 SkelAnime_GetTotalFrames(GenericAnimationHeader* animationSeg);
s16 SkelAnime_GetFrameCount(GenericAnimationHeader* animationSeg);
Gfx* SkelAnime_Draw2Limb(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
Gfx* SkelAnime_Draw2(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
Gfx* SkelAnime_DrawLimbSV2(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable, OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, RSPMatrix** mtx, Gfx* gfx);
Gfx* SkelAnime_DrawSV2(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount, OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
s32 func_80134FFC(s32 arg0, s32 arg1, Vec3s* dst);
s16 func_801353D4(GenericAnimationHeader* animationSeg);
s16 SkelAnime_GetTotalFrames2(GenericAnimationHeader* animationSeg);
s16 SkelAnime_GetFrameCount2(GenericAnimationHeader* animationSeg);
void SkelAnime_InterpolateVec3s(s32 limbCount, Vec3s* dst, Vec3s* vec2, Vec3s* vec3, f32 unkf);
void SkelAnime_AnimationCtxReset(AnimationContext* animationCtx);
void func_801358D4(GlobalContext* globalCtx);
void func_801358F4(GlobalContext* globalCtx);
AnimationEntry* SkelAnime_NextEntry(AnimationContext* animationCtx, AnimationType type);
void SkelAnime_LoadLinkAnimetion(GlobalContext* globalCtx, LinkAnimetionEntry* linkAnimetionSeg, s32 frame, s32 limbCount, void* ram);
void SkelAnime_LoadAnimationType1(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src);
void SkelAnime_LoadAnimationType2(GlobalContext* globalCtx, s32 limbCount, Vec3s* arg2, Vec3s* arg3, f32 arg4);
void SkelAnime_LoadAnimationType3(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index);
void SkelAnime_LoadAnimationType4(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index);
void SkelAnime_LoadAnimationType5(GlobalContext* globalCtx, Actor* actor, SkelAnime* skelAnime, f32 arg3);
void SkelAnime_LinkAnimetionLoaded(GlobalContext* globalCtx, AnimationEntryType0* entry);
void SkelAnime_AnimationType1Loaded(GlobalContext* globalCtx, AnimationEntryType1* entry);
void SkelAnime_AnimationType2Loaded(GlobalContext* globalCtx, AnimationEntryType2* entry);
void SkelAnime_AnimationType3Loaded(GlobalContext* globalCtx, AnimationEntryType3* entry);
void SkelAnime_AnimationType4Loaded(GlobalContext* globalCtx, AnimationEntryType4* entry);
void SkelAnime_AnimationType5Loaded(GlobalContext* globalCtx, AnimationEntryType5* entry);
void func_80135EE8(GlobalContext* globalCtx, AnimationContext* animationCtx);
void SkelAnime_InitLinkAnimetion(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg, LinkAnimetionEntry* linkAnimetionEntrySeg, s32 flags, Vec3s* limbDrawTbl, Vec3s* transitionDrawTbl, s32 limbBufCount);
void func_801360A8(SkelAnime* skelAnime);
s32 func_801360E0(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_80136104(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_801361BC(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_80136288(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_8013631C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void SkelAnime_SetTransition(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 transitionRate);
void SkelAnime_ChangeLinkAnim(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 playbackSpeed, f32 frame, f32 frameCount, u8 animationMode, f32 transitionRate);
void SkelAnime_ChangeLinkAnimDefaultStop(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg);
void SkelAnime_ChangeLinkAnimPlaybackStop(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 playbackSpeed);
void SkelAnime_ChangeLinkAnimDefaultRepeat(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg);
void SkelAnime_ChangeLinkAnimPlaybackRepeat(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 playbackSpeed);
void func_8013670C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_8013673C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_8013676C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 frame);
void func_801367B0(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 frame);
void func_801367F4(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 frame);
void func_8013682C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 transitionFrame, LinkAnimetionEntry* linkAnimetionEntrySeg2, f32 frame, f32 transitionRate, Vec3s* limbDrawTbl);
void func_801368CC(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg, f32 transitionFrame, LinkAnimetionEntry* linkAnimetionEntrySeg2, f32 frame, f32 transitionRate, Vec3s* limbDrawTbl);
void SkelAnime_SetModeStop(SkelAnime* skelAnime);
s32 func_80136990(SkelAnime* skelAnime, f32 arg1, f32 updateRate);
s32 func_80136A48(SkelAnime* skelAnime, f32 arg1);
void SkelAnime_Init(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg, AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount);
void SkelAnime_InitSV(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg, AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount);
void SkelAnime_InitSkin(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg, AnimationHeader* animationSeg);
void func_80136C84(SkelAnime* skelAnime);
s32 SkelAnime_FrameUpdateMatrix(SkelAnime* skelAnime);
s32 func_80136CF4(SkelAnime* skelAnime);
s32 func_80136D98(SkelAnime* skelAnime);
void func_80136F04(SkelAnime* skelAnime);
s32 func_8013702C(SkelAnime* skelAnime);
s32 func_801370B0(SkelAnime* skelAnime);
s32 func_8013713C(SkelAnime* skelAnime);
void SkelAnime_ChangeAnimImpl(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame, f32 frameCount, u8 animationType, f32 transitionRate, s8 unk2);
void SkelAnime_ChangeAnim(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame, f32 frameCount, u8 mode, f32 transitionRate);
void SkelAnime_ChangeAnimDefaultStop(SkelAnime* skelAnime, AnimationHeader* animationSeg);
void SkelAnime_ChangeAnimTransitionStop(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate);
void SkelAnime_ChangeAnimPlaybackStop(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed);
void SkelAnime_ChangeAnimDefaultRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg);
void SkelAnime_ChangeAnimTransitionRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate);
void SkelAnime_ChangeAnimPlaybackRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed);
void SkelAnime_AnimSetStop(SkelAnime* skelAnime);
void SkelAnime_AnimReverse(SkelAnime* skelAnime);
void func_80137674(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* index);
void func_801376DC(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* arg3);
void func_80137748(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
s32 func_801378B8(SkelAnime* skelAnime, f32 arg1);
void SkelAnime_Free(SkelAnime* skelAnime, GlobalContext* globalCtx);
void SkelAnime_CopyVec3s(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);
void Matrix_MultiplyByVectorXYZW(z_Matrix* matrix, Vec3f* vector, Vec3f* resultXYZ, f32* resultW);
void Matrix_MultiplyByVectorXYZ(z_Matrix* matrix, Vec3f* vector, Vec3f* result);
void Matrix_Multiply(z_Matrix* l, z_Matrix* r, z_Matrix* dst);
void Matrix_GetIdentity(z_Matrix** puParm1);
void Matrix_MakeIdentity(z_Matrix* matrix);
void Matrix_Copy(z_Matrix* src, z_Matrix* dst);
s32 Matrix_Invert(z_Matrix* matrix, z_Matrix* invert);
void Matrix_MakeScale(z_Matrix* matrix, f32 x, f32 y, f32 z);
void Matrix_MakeRotationZYX(z_Matrix* matrix, s16 xRotation, s16 yRotation, s16 zRotation);
void Matrix_MakeRotationYXZ(z_Matrix* matrix, s16 xRotation, s16 yRotation, s16 zRotation);
void Matrix_MakeTranslation(z_Matrix* matrix, f32 x, f32 y, f32 z);
void Matrix_MakeTranslationRotationZYXScale(z_Matrix* matrix, f32 xScale, f32 yScale, f32 zScale, s16 xRotation, s16 yRotation, s16 zRotation, f32 xTranslation, f32 yTranslation, f32 zTranslation);
void Matrix_MakeTranslationRotationYXZScale(z_Matrix* matrix, f32 xScale, f32 yScale, f32 zScale, s16 xRotation, s16 yRotation, s16 zRotation, f32 xTranslation, f32 yTranslation, f32 zTranslation);
void Matrix_MakeTranslationRotationZYX(z_Matrix* matrix, s16 xRotation, s16 yRotation, s16 zRotation, f32 xTranslation, f32 yTranslation, f32 zTranslation);
void Matrix_ToVec3s(Vec3f* vec3f, Vec3s* vec3s);
void Matrix_ToVec3f(Vec3s* vec3s, Vec3f* vec3f);
void Matrix_ToRSPMatrix(z_Matrix* src, RSPMatrix* dst);
RSPMatrix* Matrix_AppendToPloyOpaDisp(GraphicsContext* gCtxt, z_Matrix* matrix);
void Matrix_MakeRotationAroundUnitVector(z_Matrix* matrix, s16 rotation, f32 x, f32 y, f32 z);
void Matrix_MakeXRotation(z_Matrix* matrix, s16 rotation);
void Matrix_XRotation(z_Matrix* matrix, s16 rotation);
void Matrix_MakeYRotation(z_Matrix* matrix, s16 rotation);
void Matrix_YRotation(z_Matrix* matrix, s16 rotation);
void Matrix_MakeZRotation(z_Matrix* matrix, s16 rotation);
s32 func_8013A240(GlobalContext* ctxt);
void func_8013A41C(s32 flag);
void func_8013A46C(s32 flag);
u32 func_8013A4C4(s32 flag);
s16 func_8013A504(s16 val);
s32 func_8013A530(GlobalContext* ctxt, Actor* actor, s32 flag, Vec3f* pos, Vec3s* rot, f32 distanceMin, f32 distanceMax, s16 angleError);
void func_8013AED4(u16* param_1, u16 param_2, u16 param_3);
Actor* func_ActorCategoryIterateById(GlobalContext* globalCtx, struct Actor* actorListStart, s32 actorCategory, s32 actorId);
void func_8013E1C8(s32 iParm1, s32 iParm2, s32 iParm3, s32* piParm4);
void func_8013ECE0(f32 param_1, u8 param_2, u8 param_3, u8 param_4);
void func_8013ED9C(void);
void func_8013EDD0(void);
void View_ViewportToVp(Vp* dest, Viewport* src);
void View_Init(View* view, GraphicsContext* gCtxt);
void View_SetViewOrientation(View* view, Vec3f* eye, Vec3f* focalPoint, Vec3f* upDir);
void func_8013F050(View* view, Vec3f* eye, Vec3f* focalPoint, Vec3f* upDir);
void View_SetScale(View* view, f32 scale);
void View_GetScale(View* view, f32* scale);
void func_8013F0D0(View* view, f32 fovy, f32 zNear, f32 zFar);
void func_8013F100(View* view, f32* fovy, f32* zNear, f32* zFar);
void func_8013F120(View* view, f32 fovy, f32 zNear, f32 zFar);
void func_8013F15C(View* view, f32* fovy, f32* zNear, f32* zFar);
void View_SetViewport(View* view, Viewport* viewport);
void View_GetViewport(View* view, Viewport* viewport);
void View_WriteScissor(Gfx** gfx, s32 ulx, s32 uly, s32 lrx, s32 lry);
void View_SyncAndWriteScissor(View* view, Gfx** gfx);
void View_SetScissorForLetterbox(View* view);
s32 View_SetQuakeRotation(View* view, f32 x, f32 y, f32 z);
s32 View_SetQuakeScale(View* view, f32 x, f32 y, f32 z);
s32 View_SetQuakeSpeed(View* view, f32 speed);
s32 View_InitCameraQuake(View* view);
s32 View_ClearQuake(View* view);
s32 View_SetQuake(View* view, Vec3f rot, Vec3f scale, f32 speed);
s32 View_StepQuake(View* view, RSPMatrix* matrix);
void View_RenderView(View* view, s32 uParm2);
s32 View_RenderToPerspectiveMatrix(View* view);
s32 View_RenderToOrthographicMatrix(View* view);
s32 func_8013FBC8(View* view);
s32 func_8013FD74(View* view);
s32 func_80140024(View* view);
s32 func_801400CC(View* view, Gfx** gfxp);
void func_80140260(OSViMode* vimode);
void func_80140898(void* arg0);
void func_80140900(void* arg0);
void func_80140CE0(void* arg0);
void func_80140D04(void* arg0);
void func_80140D10(void* arg0, Gfx** gfx, u32 arg2);
void func_80140E80(void* param_1);
void func_801418B0(void* arg0);
void func_80141900(void* arg0);
void VisMono_Draw(void* arg0, Gfx** gfx, u32 arg2);
void func_801420C0(void* arg0);
void func_801420F4(void* arg0);
void func_80142100(void* arg0, Gfx** gfx, u32 arg2);
s32 func_80142440(SkyboxContext* skyboxCtx, Vtx* vtx, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_80143148(SkyboxContext* skyboxCtx, s32 arg1);
void func_801431E8(GameState* state, SkyboxContext* skyboxCtx, s16 skyType);
void func_80143324(GlobalContext* globalCtx, SkyboxContext* skyboxCtx, s16 skyType);
void func_801434E4(GameState* state, SkyboxContext* skyboxCtx, s16 skyType);
void func_80143B0C(GlobalContext* ctxt);
u32 Sram_CalcChecksum(u8* data, u32 length);
void func_801457CC(GameState* ctxt, SramContext* param_2);
void func_80146580(s32 param_1, SramContext* param_2, s32 param_3);
void Sram_Alloc(GameState* ctxt, SramContext* iParm2);
void func_80147020(SramContext* param_1);
void func_80147068(SramContext* param_1);
void func_80147150(SramContext* param_1);
void func_80147198(SramContext* param_1);
void func_80147564(GlobalContext* ctxt);
u32 func_80147624(GlobalContext* ctxt);
u32 func_80147734(GlobalContext* ctxt);
void func_801477B4(GlobalContext* ctxt);
void func_80148B98(GlobalContext* ctxt, u8 bParm2);
void func_80149F74(GlobalContext* globalCtx, u32** ppuParm2);
void func_8014ADBC(GlobalContext* globalCtx, void* puParm2);
void func_80150D08(GlobalContext* ctxt, u32 uParm2);
void func_801518B0(GlobalContext* ctxt, u32 uParm2, Actor* uParm3);
void func_80151938(GlobalContext* ctxt, u16 param_2);
void func_80151A68(GlobalContext* ctxt, u16 param_2);
void func_80151BB4(s32 iParm1, u32 uParm2);
void func_8015680C(GlobalContext* param_1);
void func_801586A4(GlobalContext* ctxt);
void Message_Init(GlobalContext* ctxt);
void func_801588D0(GlobalContext* ctxt, s16 param_2);
void func_8015E7EC(GlobalContext* globalCtx, void* puParm2);
void ShrinkWindow_SetLetterboxTarget(s8 target);
void ShrinkWindow_SetLetterboxMagnitude(s8 magnitude);
s32 ShrinkWindow_GetLetterboxMagnitude(void);
void ShrinkWindow_SetPillarboxTarget(s8 target);
void ShrinkWindow_SetPillarboxMagnitude(u8 magnitude);
void ShrinkWindow_Step(s32 framerateDivisor);
void ShrinkWindow_Draw(GlobalContext* ctxt);
void func_80163804(GlobalContext* ctxt);
void func_801639EC(GlobalContext* ctxt);
void func_80163A38(GlobalContext* ctxt);
void* func_8016482C(void* param_1);
void func_80165438(void* param_1);
void Play_Fini(GlobalContext* ctxt);
void func_80166968(GlobalContext* ctxt, Camera* camera);
void func_80166B30(GlobalContext* param_1);
void func_80167814(GlobalContext* ctxt);
void func_80167DE4(GlobalContext* ctxt);
void func_80168090(GlobalContext* ctxt);
void func_80168DAC(GlobalContext* ctxt);
void Play_Update(GlobalContext* ctxt);
void* Play_LoadScene(GlobalContext* ctxt, ObjectFileTableEntry* entry);
void func_8016927C(GlobalContext* ctxt, s16 sParm2);
s32 func_801694DC(GlobalContext* ctxt);
s32 Play_GetActiveCameraIndex(GlobalContext* ctxt);
void func_80169590(GlobalContext* ctxt, s16 param_2, s16 param_3);
void func_80169600(GlobalContext* ctxt, s16 param_2);
Camera* Play_GetCamera(GlobalContext* ctxt, s16 index);
void func_801699D4(GlobalContext* ctxt, s16 param_2, s16 param_3);
void func_80169D40(GlobalContext* ctxt);
u32 func_8016A01C(GlobalContext* ctxt);
void Play_Init(GlobalContext* ctxt);
void func_8016F5A8(GlobalContext* ctxt, s8* pcParm2, Input* iParm3);
void func_8016FD2C(void* param_1);
void func_80171F4C(s32 param_1);
void func_801727F0(GameStateHeap* heap, void* memoryBlock, u32 size);
s32 func_80172830(GameStateHeap* pzParm1);
void func_801728F0(GameStateHeap* heap, s32 iParm2);
void* GameStateHeap_GetStart(GameStateHeap* heap);
void GameStateHeap_SetStart(GameStateHeap* heap, void* start);
void* GameStateHeap_GetEnd(GameStateHeap* heap);
void* GameStateHeap_Alloc(GameStateHeap* heap, s32 iParm2);
void* GameStateHeap_AllocByte(GameStateHeap* pzParm1);
void* GameStateHeap_AllocFromEndAlignedTo(GameStateHeap* heap, void* ptr);
void* GameStateHeap_AllocFromEnd(GameStateHeap* heap, u32 size);
void* GameStateHeap_AllocFromEndAligned(GameStateHeap* heap, u32 size, u32 allignment);
s32 GameStateHeap_GetFreeSize(GameStateHeap* iParm1);
s32 GameStateHeap_GetHasOverflowed(GameStateHeap* pzParm1);
void GameStateHeap_InitAppend(GameStateHeap* heap);
void GameStateHeap_Init(GameStateHeap* heap, void* memoryBlock, u32 size);
void GameStateHeap_Clear(GameStateHeap* pvParm1);
void func_80172BC0(void);
void func_80172C30(AudioThreadStruct* audio);
void func_80172C68(AudioThreadStruct* audio);
void Audio_ThreadEntry(AudioThreadStruct* audio);
void Audio_WaitForInit(AudioThreadStruct* param_1);
void Audio_Start(AudioThreadStruct* audio, s32* audioThreadStackEnd, OSPri pri, OSId id, SchedThreadStruct* sched, IrqMgr* irq);
void TitleSetup_GameStateResetContext(void);
void TitleSetup_InitImpl(GameState* gameState);
void TitleSetup_Destroy(GameState* gameState);
void TitleSetup_Init(GameState* gameState);
void Game_UpdateFramerateVariables(s32 divisor);
void Game_SetFramerateDivisor(GameState* gameState, s32 divisor);
void GameState_SetFBFilter(Gfx** gfx, u32 arg1);
void Game_Nop80173534(GameState* ctxt);
void GameState_Draw(GameState* ctxt, GraphicsContext* gCtxt);
void Game_ResetSegments(GraphicsContext* gCtxt);
void func_801736DC(GraphicsContext* gCtxt);
void Game_UpdateInput(GameState* ctxt);
void Game_Update(GameState* ctxt);
void Game_IncrementFrameCount(GameState* ctxt);
void Game_InitHeap(GameState* ctxt, u32 size);
void Game_ResizeHeap(GameState* ctxt, u32 size);
void Game_StateInit(GameState* ctxt, GameStateFunc gameStateInit, GraphicsContext* gCtxt);
void Game_StateFini(GameState* ctxt);
GameStateFunc Game_GetNextStateInit(GameState* ctxt);
u32 Game_GetNextStateSize(GameState* ctxt);
u32 Game_GetShouldContinue(GameState* ctxt);
s32 Game_GetHeapFreeSize(GameState* ctxt);
s32 func_80173B48(GameState* ctxt);
GameAlloc* func_80173BF0(GameAlloc* heap);
void* Gamealloc_Alloc(GameAlloc* heap, u32 size);
void Gamealloc_Free(GameAlloc* heap, void* ptr);
void Gamealloc_FreeAll(GameAlloc* heap);
void Gamealloc_Init(GameAlloc* iParm1);
void Graph_DlAlloc(DispBuf* dl, void* memoryBlock, u32 size);
void Graph_InitTHGA(GraphicsContext* gCtxt);
GameStateOverlay* Graph_GetNextGameState(GameState* ctxt);
void* Graph_FaultAddrConvFunc(void* addr);
void Graph_Init(GraphicsContext* gCtxt);
void Graph_Render(GraphicsContext* gCtxt, GameState* ctxt);
void Graph_FrameSetup(GameState* ctxt);
void Graph_RenderFrame(GraphicsContext* gCtxt, GameState* ctxt);
void Graph_DoFrame(GraphicsContext* gCtxt, GameState* ctxt);
void Graph_ThreadEntry(void* arg);
Gfx* Graph_GfxPlusOne(Gfx* gfx);
Gfx* Graph_BranchDlist(Gfx* gfx, Gfx* dst);
void* Graph_DlistAlloc(Gfx** gfx, u32 size);
void main(void* arg);
void Padmgr_SetEventCallback(OSMesg pvParm1);
void Padmgr_CalcStickEdges(Input* input);
void func_80175E68(Input* input, s32 param_2);
void Padmgr_GetInput(Input* input, s32 param_2);
void Padmgr_GetInput2(Input* input, s32 param_2);
void Padmgr_ThreadEntry(PadmgrThreadStruct* padmgr);
void Padmgr_Start(OSMesgQueue* siEventCallbackQueue, IrqMgr* irqmgr, OSId threadId, OSPri threadPri, void* stack);
void Sched_Nop80176364(SchedThreadStruct* sched);
void func_80176370(SchedThreadStruct* sched);
void func_80176394(SchedThreadStruct* sched);
void func_801764F0(SchedThreadStruct* sched);
void func_8017668C(SchedThreadStruct* sched, void* puParm2);
void func_80176B34(SchedThreadStruct* sched);
void func_80176C24(SchedThreadStruct* sched);
void func_80176CF4(SchedThreadStruct* sched);
void func_80176F2C(SchedThreadStruct* sched);
void func_80177018(SchedThreadStruct* sched);
void func_8017703C(SchedThreadStruct* sched);
void func_80177060(SchedThreadStruct* sched);
void func_80177084(SchedThreadStruct* sched);
void Sched_ThreadEntry(SchedThreadStruct* sched);
void func_801773A0(void* arg0);
void func_801773C4(void* arg0);
void SpeedMeter_DrawTimeEntries(void* displayList, GraphicsContext* gCtx);
void SpeedMeter_DrawAllocEntries(void* displayList, GraphicsContext *gCtx, GameState *ctx);
u32* get_framebuffer(s32 index);
s32 func_80178A94(s32 param_1, s32 param_2);
void Check_WriteRGB5A1Pixel(u16* buffer, u32 x, u32 y, u16 value);
void Check_WriteI4Pixel(u16* buffer, u32 x, u32 y, u32 value);
void Check_DrawI4Texture(u16* buffer, u32 x, u32 y, u32 width, u32 height, u8* texture);
void Check_ClearRGB5A1(s16* buffer);
f32 func_80179300(f32 param_1);
f32 func_80179400(s32 param_1);
f32 pow_int(f32 x, s32 pow);
f32 sin_rad(f32 rad);
f32 cos_rad(f32 rad);
f32 randZeroOneScaled(f32 scale);
f32 randPlusMinusPoint5Scaled(f32 scale);
f32 Math3D_Normalize(Vec3f* vec);
void func_80179B34(float fParm1, f32 fParm2, f32 fParm5, f32 fParm6, f32 param_5, f32 param_6, f32 param_7, float* param_8, float* param_9);
void Math3D_ScaleAndAdd(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dst);
void Math3D_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dst);
s32 Math3D_Parallel(Vec3f* a, Vec3f* b);
s32 Math3D_AngleBetweenVectors(Vec3f* a, Vec3f* b, f32* angle);
void func_80179F64(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
s32 Math3D_XZBoundCheck(f32 xMin, f32 xMax, f32 zMin, f32 zMax, f32 x, f32 z);
f32 Math3D_XZLengthSquared(f32 x, f32 z);
f32 Math3D_XZLength(f32 x, f32 z);
f32 Math3D_XZDistanceSquared(f32 x1, f32 x2, f32 z1, f32 z2);
f32 Math3D_XZDistance(f32 x1, f32 x2, f32 z1, f32 z2);
f32 Math3D_LengthSquared(Vec3f* vec);
f32 Math3D_Length(Vec3f* vec);
f32 Math3D_DistanceSquared(Vec3f* a, Vec3f* b);
f32 Math3D_Distance(Vec3f* a, Vec3f* b);
f32 Math3D_DistanceS(Vec3s* s, Vec3f* f);
f32 func_8017A7B8(f32* param_1, f32* param_2, f32 param_3, f32 param_4);
f32 func_8017A7F8(f32* param_1, f32* param_2, f32 param_3, f32 param_4);
f32 func_8017A838(f32* param_1, f32* param_2, f32 param_3, f32 param_4);
void Math3D_CrossProduct(Vec3f* a, Vec3f* b, Vec3f* res);
void Math3D_NormalVector(Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* res);
u32 func_8017A954(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
u32 func_8017AA0C(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
u32 func_8017ABBC(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
void Math3D_UnitNormalVector(Vec3f* a, Vec3f* b, Vec3f* c, f32* normX, f32* normY, f32* normZ, f32* param_7);
f32 Math3D_SignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
f32 Math3D_NormalizedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
f32 Math3D_NormalizedSignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
void Math3D_TriSetCoords(TriNorm* tri, Vec3f* pointA, Vec3f* pointB, Vec3f* pointC);
u32 Math3D_IsPointInSphere(Sphere16* sphere, Vec3f* point);
s32 Math3D_ColSphereLineSeg(Sphere16* sphere, LineSegment* line);
void func_8017DD34(Sphere16* sphere, TriNorm* tri, Vec3f* pfParm3);
s32 Math3D_ColSphereTri(Sphere16* sphere, TriNorm* tri, Vec3f* uParm3);
s32 Math3D_ColCylinderTri(Cylinder16* cylinder, TriNorm* tri, Vec3f* pzParm3);
s32 Math3D_ColSphereSphere(Sphere16* sphere1, Sphere16* sphere2);
s32 Math3D_ColSphereSphereIntersect(Sphere16* sphere1, Sphere16* sphere2, f32* intersectAmount);
s32 Math3D_ColSphereSphereIntersectAndDistance(Sphere16* sphere1, Sphere16* sphere2, f32* intersectAmount, f32* dist);
s32 Math3D_ColSphereCylinderDistance(Sphere16* sphere, Cylinder16* cylinder, f32* dist);
s32 Math3D_ColSphereCylinderDistanceAndAmount(Sphere16* sphere, Cylinder16* cylinder, f32* dist, f32* intersectAmount);
s32 Math3D_ColCylinderCylinderAmount(Cylinder16* cylinder1, Cylinder16* cylinder2, f32* intersectAmount);
s32 Math3D_ColCylinderCylinderAmountAndDistance(Cylinder16* cylinder1, Cylinder16* cylinder2, f32* intersectAmount, f32* dist);
s32 Math3d_ColTriTri(TriNorm* tri1, TriNorm* tri2, Vec3f* uParm3);
s16 atans_first_8th(f32 opposite, f32 adjacent);
s16 atans(f32 opposite, f32 adjacent);
f32 atan(f32 opposite, f32 adjacent);
s16 atans_flip(f32 adjacent, f32 opposite);
s16 atan_flip(f32 adjacent, f32 opposite);
void SysMatrix_StateAlloc(GameState* ctxt);
void SysMatrix_StatePush(void);
void SysMatrix_StatePop(void);
void SysMatrix_CopyCurrentState(z_Matrix* matrix);
void SysMatrix_SetCurrentState(z_Matrix* matrix);
void SysMatrix_InsertMatrix(z_Matrix* matrix, s32 appendToState);
void SysMatrix_InsertTranslation(f32 x, f32 y, f32 z, s32 appendToState);
void SysMatrix_InsertScale(f32 xScale, f32 yScale, f32 zScale, s32 appendToState);
void SysMatrix_InsertXRotation_s(s16 rotation, s32 appendToState);
void SysMatrix_InsertXRotation_f(f32 rotation, s32 appendToState);
void SysMatrix_RotateStateAroundXAxis(f32 rotation);
void SysMatrix_SetStateXRotation(f32 rotation);
void SysMatrix_InsertYRotation_s(s16 rotation, s32 appendToState);
void SysMatrix_InsertYRotation_f(f32 rotation, s32 appendToState);
void SysMatrix_InsertZRotation_s(s16 rotation, s32 appendToState);
void SysMatrix_InsertZRotation_f(f32 rotation, s32 appendToState);
void SysMatrix_InsertRotation(s16 xRotation, s16 yRotation, s16 zRotation, s32 appendToState);
void SysMatrix_RotateAndTranslateState(Vec3f* translation, Vec3s* rotation);
void SysMatrix_SetStateRotationAndTranslation(f32 x, f32 y, f32 z, Vec3s* rotation);
RSPMatrix* SysMatrix_ToRSPMatrix(z_Matrix* src, RSPMatrix* dst);
RSPMatrix* SysMatrix_GetStateAsRSPMatrix(RSPMatrix* matrix);
RSPMatrix* SysMatrix_AppendStateToPolyOpaDisp(GraphicsContext* gCtxt);
void SysMatrix_AppendToPolyOpaDisp(z_Matrix* ctxt, GraphicsContext* gCtxt);
void SysMatrix_MultiplyVector3fByState(Vec3f* src, Vec3f* dst);
void SysMatrix_GetStateTranslation(Vec3f* dst);
void SysMatrix_GetStateTranslationAndScaledX(f32 scale, Vec3f* dst);
void SysMatrix_GetStateTranslationAndScaledY(f32 scale, Vec3f* dst);
void SysMatrix_GetStateTranslationAndScaledZ(f32 scale, Vec3f* dst);
void SysMatrix_MultiplyVector3fXZByCurrentState(Vec3f* src, Vec3f* dst);
void SysMatrix_Copy(z_Matrix* dst, z_Matrix* src);
void SysMatrix_FromRSPMatrix(RSPMatrix* src, z_Matrix* dst);
void SysMatrix_MultiplyVector3fByMatrix(Vec3f* src, Vec3f* dst, z_Matrix* matrix);
void SysMatrix_TransposeXYZ(z_Matrix* matrix);
void SysMatrix_NormalizeXYZ(z_Matrix* matrix);
void func_8018219C(z_Matrix* pfParm1, Vec3s* psParm2, s32 iParm3);
void SysMatrix_InsertRotationAroundUnitVector_f(f32 rotation, Vec3f* vector, s32 appendToState);
void SysMatrix_InsertRotationAroundUnitVector_s(s16 rotation, Vec3f* vector, s32 appendToState);
void func_80183070(void);
void Slowly_Main(s8018571C* iParm1);
void Slowly_ThreadEntry(s8018571C* param_1);
u32 func_80185908(void);
void SysFlashrom_ThreadEntry(s80185D40* param_1);
s32 func_80185F90(u32 param_1);
void func_80199268(s32* param_1);
void func_8019AE40(s32 param_1, s32 param_2, u32 param_3, s32 param_4);
void func_8019AEC0(void* param_1, void* param_2);
void func_8019E014(void);
void play_sound(u16 param_1);
void func_8019F128(u16 param_1);
void func_8019F1C0(Vec3f* pos, u16 sfxId);
void func_8019FAD8(Vec3f* param_1, u16 param_2, f32 param_3);
void func_801A246C(u8 param_1, u8 param_2);
void func_801A3CD8(s8 param_1);
void audio_setBGM(u32 bgmID);
void func_801A72CC(Vec3f* uParm1);
void func_801A7794(u32 param_1, u32 param_2, u32 param_3);
s32 func_801A8A50(s32 param1);
void func_801AA610(GlobalContext* ctxt);
void func_801AA624(GlobalContext* ctxt);
void nop_801AAAA0(GlobalContext* ctxt);
void Title_Init(TitleContext* ctxt);
extern u8 _bootSegmentStart[]; extern u8 _bootSegmentEnd[];
extern u8 _bootSegmentRomStart[]; extern u8 _bootSegmentRomEnd[];
extern u8 _dmadataSegmentStart[]; extern u8 _dmadataSegmentEnd[];
extern u8 _dmadataSegmentRomStart[]; extern u8 _dmadataSegmentRomEnd[];
extern u8 _AudiobankSegmentRomStart[]; extern u8 _AudiobankSegmentRomEnd[];
extern u8 _AudioseqSegmentRomStart[]; extern u8 _AudioseqSegmentRomEnd[];
extern u8 _AudiotableSegmentRomStart[]; extern u8 _AudiotableSegmentRomEnd[];
extern u8 _jpn_font_staticSegmentRomStart[]; extern u8 _jpn_font_staticSegmentRomEnd[];
extern u8 _link_animetionSegmentRomStart[]; extern u8 _link_animetionSegmentRomEnd[];
extern u8 _icon_item_field_staticSegmentRomStart[]; extern u8 _icon_item_field_staticSegmentRomEnd[];
extern u8 _icon_item_dungeon_staticSegmentRomStart[]; extern u8 _icon_item_dungeon_staticSegmentRomEnd[];
extern u8 _icon_item_gameover_staticSegmentRomStart[]; extern u8 _icon_item_gameover_staticSegmentRomEnd[];
extern u8 __013_0x00963540SegmentRomStart[]; extern u8 __013_0x00963540SegmentRomEnd[];
extern u8 __014_0x00967260SegmentRomStart[]; extern u8 __014_0x00967260SegmentRomEnd[];
extern u8 _map_i_staticSegmentRomStart[]; extern u8 _map_i_staticSegmentRomEnd[];
extern u8 _map_grand_staticSegmentRomStart[]; extern u8 _map_grand_staticSegmentRomEnd[];
extern u8 _item_name_staticSegmentRomStart[]; extern u8 _item_name_staticSegmentRomEnd[];
extern u8 _map_name_staticSegmentRomStart[]; extern u8 _map_name_staticSegmentRomEnd[];
extern u8 __019_0x00980f60SegmentRomStart[]; extern u8 __019_0x00980f60SegmentRomEnd[];
extern u8 __020_0x009c6230SegmentRomStart[]; extern u8 __020_0x009c6230SegmentRomEnd[];
extern u8 __022_0x009caaf0SegmentRomStart[]; extern u8 __022_0x009caaf0SegmentRomEnd[];
extern u8 __023_0x009d1500SegmentRomStart[]; extern u8 __023_0x009d1500SegmentRomEnd[];
extern u8 __024_0x009d3760SegmentRomStart[]; extern u8 __024_0x009d3760SegmentRomEnd[];
extern u8 _do_action_staticSegmentRomStart[]; extern u8 _do_action_staticSegmentRomEnd[];
extern u8 _message_staticSegmentRomStart[]; extern u8 _message_staticSegmentRomEnd[];
extern u8 _message_texture_staticSegmentRomStart[]; extern u8 _message_texture_staticSegmentRomEnd[];
extern u8 _nes_font_staticSegmentRomStart[]; extern u8 _nes_font_staticSegmentRomEnd[];
extern u8 _en_message_data_staticSegmentRomStart[]; extern u8 _en_message_data_staticSegmentRomEnd[];
extern u8 _staff_message_data_staticSegmentRomStart[]; extern u8 _staff_message_data_staticSegmentRomEnd[];
extern u8 _codeSegmentStart[]; extern u8 _codeSegmentEnd[];
extern u8 _codeSegmentRomStart[]; extern u8 _codeSegmentRomEnd[];
extern u8 _codeSegmentBssStart[]; extern u8 _codeSegmentBssEnd[];
extern u8 _ovl_titleSegmentStart[]; extern u8 _ovl_titleSegmentEnd[]; extern u8 _ovl_titleSegmentRomStart[]; extern u8 _ovl_titleSegmentRomEnd[];
extern u8 _ovl_selectSegmentStart[]; extern u8 _ovl_selectSegmentEnd[]; extern u8 _ovl_selectSegmentRomStart[]; extern u8 _ovl_selectSegmentRomEnd[];
extern u8 _ovl_openingSegmentStart[]; extern u8 _ovl_openingSegmentEnd[]; extern u8 _ovl_openingSegmentRomStart[]; extern u8 _ovl_openingSegmentRomEnd[];
extern u8 _ovl_file_chooseSegmentStart[]; extern u8 _ovl_file_chooseSegmentEnd[]; extern u8 _ovl_file_chooseSegmentRomStart[]; extern u8 _ovl_file_chooseSegmentRomEnd[];
extern u8 _ovl_daytelopSegmentStart[]; extern u8 _ovl_daytelopSegmentEnd[]; extern u8 _ovl_daytelopSegmentRomStart[]; extern u8 _ovl_daytelopSegmentRomEnd[];
extern u8 _ovl_kaleido_scopeSegmentStart[]; extern u8 _ovl_kaleido_scopeSegmentEnd[]; extern u8 _ovl_kaleido_scopeSegmentRomStart[]; extern u8 _ovl_kaleido_scopeSegmentRomEnd[];
extern u8 _ovl_Player_ActorSegmentStart[]; extern u8 _ovl_Player_ActorSegmentEnd[]; extern u8 _ovl_Player_ActorSegmentRomStart[]; extern u8 _ovl_Player_ActorSegmentRomEnd[];
extern u8 _ovl_En_TestSegmentStart[]; extern u8 _ovl_En_TestSegmentEnd[]; extern u8 _ovl_En_TestSegmentRomStart[]; extern u8 _ovl_En_TestSegmentRomEnd[];
extern u8 _ovl_En_GirlASegmentStart[]; extern u8 _ovl_En_GirlASegmentEnd[]; extern u8 _ovl_En_GirlASegmentRomStart[]; extern u8 _ovl_En_GirlASegmentRomEnd[];
extern u8 _ovl_En_PartSegmentStart[]; extern u8 _ovl_En_PartSegmentEnd[]; extern u8 _ovl_En_PartSegmentRomStart[]; extern u8 _ovl_En_PartSegmentRomEnd[];
extern u8 _ovl_En_LightSegmentStart[]; extern u8 _ovl_En_LightSegmentEnd[]; extern u8 _ovl_En_LightSegmentRomStart[]; extern u8 _ovl_En_LightSegmentRomEnd[];
extern u8 _ovl_En_DoorSegmentStart[]; extern u8 _ovl_En_DoorSegmentEnd[]; extern u8 _ovl_En_DoorSegmentRomStart[]; extern u8 _ovl_En_DoorSegmentRomEnd[];
extern u8 _ovl_En_BoxSegmentStart[]; extern u8 _ovl_En_BoxSegmentEnd[]; extern u8 _ovl_En_BoxSegmentRomStart[]; extern u8 _ovl_En_BoxSegmentRomEnd[];
extern u8 _ovl_En_PametfrogSegmentStart[]; extern u8 _ovl_En_PametfrogSegmentEnd[]; extern u8 _ovl_En_PametfrogSegmentRomStart[]; extern u8 _ovl_En_PametfrogSegmentRomEnd[];
extern u8 _ovl_En_OkutaSegmentStart[]; extern u8 _ovl_En_OkutaSegmentEnd[]; extern u8 _ovl_En_OkutaSegmentRomStart[]; extern u8 _ovl_En_OkutaSegmentRomEnd[];
extern u8 _ovl_En_BomSegmentStart[]; extern u8 _ovl_En_BomSegmentEnd[]; extern u8 _ovl_En_BomSegmentRomStart[]; extern u8 _ovl_En_BomSegmentRomEnd[];
extern u8 _ovl_En_WallmasSegmentStart[]; extern u8 _ovl_En_WallmasSegmentEnd[]; extern u8 _ovl_En_WallmasSegmentRomStart[]; extern u8 _ovl_En_WallmasSegmentRomEnd[];
extern u8 _ovl_En_DodongoSegmentStart[]; extern u8 _ovl_En_DodongoSegmentEnd[]; extern u8 _ovl_En_DodongoSegmentRomStart[]; extern u8 _ovl_En_DodongoSegmentRomEnd[];
extern u8 _ovl_En_FireflySegmentStart[]; extern u8 _ovl_En_FireflySegmentEnd[]; extern u8 _ovl_En_FireflySegmentRomStart[]; extern u8 _ovl_En_FireflySegmentRomEnd[];
extern u8 _ovl_En_HorseSegmentStart[]; extern u8 _ovl_En_HorseSegmentEnd[]; extern u8 _ovl_En_HorseSegmentRomStart[]; extern u8 _ovl_En_HorseSegmentRomEnd[];
extern u8 _ovl_En_ArrowSegmentStart[]; extern u8 _ovl_En_ArrowSegmentEnd[]; extern u8 _ovl_En_ArrowSegmentRomStart[]; extern u8 _ovl_En_ArrowSegmentRomEnd[];
extern u8 _ovl_En_ElfSegmentStart[]; extern u8 _ovl_En_ElfSegmentEnd[]; extern u8 _ovl_En_ElfSegmentRomStart[]; extern u8 _ovl_En_ElfSegmentRomEnd[];
extern u8 _ovl_En_NiwSegmentStart[]; extern u8 _ovl_En_NiwSegmentEnd[]; extern u8 _ovl_En_NiwSegmentRomStart[]; extern u8 _ovl_En_NiwSegmentRomEnd[];
extern u8 _ovl_En_TiteSegmentStart[]; extern u8 _ovl_En_TiteSegmentEnd[]; extern u8 _ovl_En_TiteSegmentRomStart[]; extern u8 _ovl_En_TiteSegmentRomEnd[];
extern u8 _ovl_En_PeehatSegmentStart[]; extern u8 _ovl_En_PeehatSegmentEnd[]; extern u8 _ovl_En_PeehatSegmentRomStart[]; extern u8 _ovl_En_PeehatSegmentRomEnd[];
extern u8 _ovl_En_HollSegmentStart[]; extern u8 _ovl_En_HollSegmentEnd[]; extern u8 _ovl_En_HollSegmentRomStart[]; extern u8 _ovl_En_HollSegmentRomEnd[];
extern u8 _ovl_En_DinofosSegmentStart[]; extern u8 _ovl_En_DinofosSegmentEnd[]; extern u8 _ovl_En_DinofosSegmentRomStart[]; extern u8 _ovl_En_DinofosSegmentRomEnd[];
extern u8 _ovl_En_HataSegmentStart[]; extern u8 _ovl_En_HataSegmentEnd[]; extern u8 _ovl_En_HataSegmentRomStart[]; extern u8 _ovl_En_HataSegmentRomEnd[];
extern u8 _ovl_En_Zl1SegmentStart[]; extern u8 _ovl_En_Zl1SegmentEnd[]; extern u8 _ovl_En_Zl1SegmentRomStart[]; extern u8 _ovl_En_Zl1SegmentRomEnd[];
extern u8 _ovl_En_ViewerSegmentStart[]; extern u8 _ovl_En_ViewerSegmentEnd[]; extern u8 _ovl_En_ViewerSegmentRomStart[]; extern u8 _ovl_En_ViewerSegmentRomEnd[];
extern u8 _ovl_En_BubbleSegmentStart[]; extern u8 _ovl_En_BubbleSegmentEnd[]; extern u8 _ovl_En_BubbleSegmentRomStart[]; extern u8 _ovl_En_BubbleSegmentRomEnd[];
extern u8 _ovl_Door_ShutterSegmentStart[]; extern u8 _ovl_Door_ShutterSegmentEnd[]; extern u8 _ovl_Door_ShutterSegmentRomStart[]; extern u8 _ovl_Door_ShutterSegmentRomEnd[];
extern u8 _ovl_En_BoomSegmentStart[]; extern u8 _ovl_En_BoomSegmentEnd[]; extern u8 _ovl_En_BoomSegmentRomStart[]; extern u8 _ovl_En_BoomSegmentRomEnd[];
extern u8 _ovl_En_Torch2SegmentStart[]; extern u8 _ovl_En_Torch2SegmentEnd[]; extern u8 _ovl_En_Torch2SegmentRomStart[]; extern u8 _ovl_En_Torch2SegmentRomEnd[];
extern u8 _ovl_En_MinifrogSegmentStart[]; extern u8 _ovl_En_MinifrogSegmentEnd[]; extern u8 _ovl_En_MinifrogSegmentRomStart[]; extern u8 _ovl_En_MinifrogSegmentRomEnd[];
extern u8 _ovl_En_StSegmentStart[]; extern u8 _ovl_En_StSegmentEnd[]; extern u8 _ovl_En_StSegmentRomStart[]; extern u8 _ovl_En_StSegmentRomEnd[];
extern u8 _ovl_Obj_WturnSegmentStart[]; extern u8 _ovl_Obj_WturnSegmentEnd[]; extern u8 _ovl_Obj_WturnSegmentRomStart[]; extern u8 _ovl_Obj_WturnSegmentRomEnd[];
extern u8 _ovl_En_River_SoundSegmentStart[]; extern u8 _ovl_En_River_SoundSegmentEnd[]; extern u8 _ovl_En_River_SoundSegmentRomStart[]; extern u8 _ovl_En_River_SoundSegmentRomEnd[];
extern u8 _ovl_En_OssanSegmentStart[]; extern u8 _ovl_En_OssanSegmentEnd[]; extern u8 _ovl_En_OssanSegmentRomStart[]; extern u8 _ovl_En_OssanSegmentRomEnd[];
extern u8 _ovl_En_FamosSegmentStart[]; extern u8 _ovl_En_FamosSegmentEnd[]; extern u8 _ovl_En_FamosSegmentRomStart[]; extern u8 _ovl_En_FamosSegmentRomEnd[];
extern u8 _ovl_En_BombfSegmentStart[]; extern u8 _ovl_En_BombfSegmentEnd[]; extern u8 _ovl_En_BombfSegmentRomStart[]; extern u8 _ovl_En_BombfSegmentRomEnd[];
extern u8 _ovl_En_AmSegmentStart[]; extern u8 _ovl_En_AmSegmentEnd[]; extern u8 _ovl_En_AmSegmentRomStart[]; extern u8 _ovl_En_AmSegmentRomEnd[];
extern u8 _ovl_En_DekubabaSegmentStart[]; extern u8 _ovl_En_DekubabaSegmentEnd[]; extern u8 _ovl_En_DekubabaSegmentRomStart[]; extern u8 _ovl_En_DekubabaSegmentRomEnd[];
extern u8 _ovl_En_M_Fire1SegmentStart[]; extern u8 _ovl_En_M_Fire1SegmentEnd[]; extern u8 _ovl_En_M_Fire1SegmentRomStart[]; extern u8 _ovl_En_M_Fire1SegmentRomEnd[];
extern u8 _ovl_En_M_ThunderSegmentStart[]; extern u8 _ovl_En_M_ThunderSegmentEnd[]; extern u8 _ovl_En_M_ThunderSegmentRomStart[]; extern u8 _ovl_En_M_ThunderSegmentRomEnd[];
extern u8 _ovl_Bg_BreakwallSegmentStart[]; extern u8 _ovl_Bg_BreakwallSegmentEnd[]; extern u8 _ovl_Bg_BreakwallSegmentRomStart[]; extern u8 _ovl_Bg_BreakwallSegmentRomEnd[];
extern u8 _ovl_Door_Warp1SegmentStart[]; extern u8 _ovl_Door_Warp1SegmentEnd[]; extern u8 _ovl_Door_Warp1SegmentRomStart[]; extern u8 _ovl_Door_Warp1SegmentRomEnd[];
extern u8 _ovl_Obj_SyokudaiSegmentStart[]; extern u8 _ovl_Obj_SyokudaiSegmentEnd[]; extern u8 _ovl_Obj_SyokudaiSegmentRomStart[]; extern u8 _ovl_Obj_SyokudaiSegmentRomEnd[];
extern u8 _ovl_Item_B_HeartSegmentStart[]; extern u8 _ovl_Item_B_HeartSegmentEnd[]; extern u8 _ovl_Item_B_HeartSegmentRomStart[]; extern u8 _ovl_Item_B_HeartSegmentRomEnd[];
extern u8 _ovl_En_DekunutsSegmentStart[]; extern u8 _ovl_En_DekunutsSegmentEnd[]; extern u8 _ovl_En_DekunutsSegmentRomStart[]; extern u8 _ovl_En_DekunutsSegmentRomEnd[];
extern u8 _ovl_En_BbfallSegmentStart[]; extern u8 _ovl_En_BbfallSegmentEnd[]; extern u8 _ovl_En_BbfallSegmentRomStart[]; extern u8 _ovl_En_BbfallSegmentRomEnd[];
extern u8 _ovl_Arms_HookSegmentStart[]; extern u8 _ovl_Arms_HookSegmentEnd[]; extern u8 _ovl_Arms_HookSegmentRomStart[]; extern u8 _ovl_Arms_HookSegmentRomEnd[];
extern u8 _ovl_En_BbSegmentStart[]; extern u8 _ovl_En_BbSegmentEnd[]; extern u8 _ovl_En_BbSegmentRomStart[]; extern u8 _ovl_En_BbSegmentRomEnd[];
extern u8 _ovl_Bg_Keikoku_SprSegmentStart[]; extern u8 _ovl_Bg_Keikoku_SprSegmentEnd[]; extern u8 _ovl_Bg_Keikoku_SprSegmentRomStart[]; extern u8 _ovl_Bg_Keikoku_SprSegmentRomEnd[];
extern u8 _ovl_En_Wood02SegmentStart[]; extern u8 _ovl_En_Wood02SegmentEnd[]; extern u8 _ovl_En_Wood02SegmentRomStart[]; extern u8 _ovl_En_Wood02SegmentRomEnd[];
extern u8 _ovl_En_DeathSegmentStart[]; extern u8 _ovl_En_DeathSegmentEnd[]; extern u8 _ovl_En_DeathSegmentRomStart[]; extern u8 _ovl_En_DeathSegmentRomEnd[];
extern u8 _ovl_En_MinideathSegmentStart[]; extern u8 _ovl_En_MinideathSegmentEnd[]; extern u8 _ovl_En_MinideathSegmentRomStart[]; extern u8 _ovl_En_MinideathSegmentRomEnd[];
extern u8 _ovl_En_VmSegmentStart[]; extern u8 _ovl_En_VmSegmentEnd[]; extern u8 _ovl_En_VmSegmentRomStart[]; extern u8 _ovl_En_VmSegmentRomEnd[];
extern u8 _ovl_Demo_EffectSegmentStart[]; extern u8 _ovl_Demo_EffectSegmentEnd[]; extern u8 _ovl_Demo_EffectSegmentRomStart[]; extern u8 _ovl_Demo_EffectSegmentRomEnd[];
extern u8 _ovl_Demo_KankyoSegmentStart[]; extern u8 _ovl_Demo_KankyoSegmentEnd[]; extern u8 _ovl_Demo_KankyoSegmentRomStart[]; extern u8 _ovl_Demo_KankyoSegmentRomEnd[];
extern u8 _ovl_En_FloormasSegmentStart[]; extern u8 _ovl_En_FloormasSegmentEnd[]; extern u8 _ovl_En_FloormasSegmentRomStart[]; extern u8 _ovl_En_FloormasSegmentRomEnd[];
extern u8 _ovl_En_RdSegmentStart[]; extern u8 _ovl_En_RdSegmentEnd[]; extern u8 _ovl_En_RdSegmentRomStart[]; extern u8 _ovl_En_RdSegmentRomEnd[];
extern u8 _ovl_Bg_F40_FliftSegmentStart[]; extern u8 _ovl_Bg_F40_FliftSegmentEnd[]; extern u8 _ovl_Bg_F40_FliftSegmentRomStart[]; extern u8 _ovl_Bg_F40_FliftSegmentRomEnd[];
extern u8 _ovl_Obj_MureSegmentStart[]; extern u8 _ovl_Obj_MureSegmentEnd[]; extern u8 _ovl_Obj_MureSegmentRomStart[]; extern u8 _ovl_Obj_MureSegmentRomEnd[];
extern u8 _ovl_En_SwSegmentStart[]; extern u8 _ovl_En_SwSegmentEnd[]; extern u8 _ovl_En_SwSegmentRomStart[]; extern u8 _ovl_En_SwSegmentRomEnd[];
extern u8 _ovl_Object_KankyoSegmentStart[]; extern u8 _ovl_Object_KankyoSegmentEnd[]; extern u8 _ovl_Object_KankyoSegmentRomStart[]; extern u8 _ovl_Object_KankyoSegmentRomEnd[];
extern u8 _ovl_En_Horse_Link_ChildSegmentStart[]; extern u8 _ovl_En_Horse_Link_ChildSegmentEnd[]; extern u8 _ovl_En_Horse_Link_ChildSegmentRomStart[]; extern u8 _ovl_En_Horse_Link_ChildSegmentRomEnd[];
extern u8 _ovl_Door_AnaSegmentStart[]; extern u8 _ovl_Door_AnaSegmentEnd[]; extern u8 _ovl_Door_AnaSegmentRomStart[]; extern u8 _ovl_Door_AnaSegmentRomEnd[];
extern u8 _ovl_En_Encount1SegmentStart[]; extern u8 _ovl_En_Encount1SegmentEnd[]; extern u8 _ovl_En_Encount1SegmentRomStart[]; extern u8 _ovl_En_Encount1SegmentRomEnd[];
extern u8 _ovl_Demo_Tre_LgtSegmentStart[]; extern u8 _ovl_Demo_Tre_LgtSegmentEnd[]; extern u8 _ovl_Demo_Tre_LgtSegmentRomStart[]; extern u8 _ovl_Demo_Tre_LgtSegmentRomEnd[];
extern u8 _ovl_En_Encount2SegmentStart[]; extern u8 _ovl_En_Encount2SegmentEnd[]; extern u8 _ovl_En_Encount2SegmentRomStart[]; extern u8 _ovl_En_Encount2SegmentRomEnd[];
extern u8 _ovl_En_Fire_RockSegmentStart[]; extern u8 _ovl_En_Fire_RockSegmentEnd[]; extern u8 _ovl_En_Fire_RockSegmentRomStart[]; extern u8 _ovl_En_Fire_RockSegmentRomEnd[];
extern u8 _ovl_Bg_Ctower_RotSegmentStart[]; extern u8 _ovl_Bg_Ctower_RotSegmentEnd[]; extern u8 _ovl_Bg_Ctower_RotSegmentRomStart[]; extern u8 _ovl_Bg_Ctower_RotSegmentRomEnd[];
extern u8 _ovl_Mir_RaySegmentStart[]; extern u8 _ovl_Mir_RaySegmentEnd[]; extern u8 _ovl_Mir_RaySegmentRomStart[]; extern u8 _ovl_Mir_RaySegmentRomEnd[];
extern u8 _ovl_En_SbSegmentStart[]; extern u8 _ovl_En_SbSegmentEnd[]; extern u8 _ovl_En_SbSegmentRomStart[]; extern u8 _ovl_En_SbSegmentRomEnd[];
extern u8 _ovl_En_BigslimeSegmentStart[]; extern u8 _ovl_En_BigslimeSegmentEnd[]; extern u8 _ovl_En_BigslimeSegmentRomStart[]; extern u8 _ovl_En_BigslimeSegmentRomEnd[];
extern u8 _ovl_En_KarebabaSegmentStart[]; extern u8 _ovl_En_KarebabaSegmentEnd[]; extern u8 _ovl_En_KarebabaSegmentRomStart[]; extern u8 _ovl_En_KarebabaSegmentRomEnd[];
extern u8 _ovl_En_InSegmentStart[]; extern u8 _ovl_En_InSegmentEnd[]; extern u8 _ovl_En_InSegmentRomStart[]; extern u8 _ovl_En_InSegmentRomEnd[];
extern u8 _ovl_En_Bom_ChuSegmentStart[]; extern u8 _ovl_En_Bom_ChuSegmentEnd[]; extern u8 _ovl_En_Bom_ChuSegmentRomStart[]; extern u8 _ovl_En_Bom_ChuSegmentRomEnd[];
extern u8 _ovl_En_Horse_Game_CheckSegmentStart[]; extern u8 _ovl_En_Horse_Game_CheckSegmentEnd[]; extern u8 _ovl_En_Horse_Game_CheckSegmentRomStart[]; extern u8 _ovl_En_Horse_Game_CheckSegmentRomEnd[];
extern u8 _ovl_En_RrSegmentStart[]; extern u8 _ovl_En_RrSegmentEnd[]; extern u8 _ovl_En_RrSegmentRomStart[]; extern u8 _ovl_En_RrSegmentRomEnd[];
extern u8 _ovl_En_FrSegmentStart[]; extern u8 _ovl_En_FrSegmentEnd[]; extern u8 _ovl_En_FrSegmentRomStart[]; extern u8 _ovl_En_FrSegmentRomEnd[];
extern u8 _ovl_En_FishingSegmentStart[]; extern u8 _ovl_En_FishingSegmentEnd[]; extern u8 _ovl_En_FishingSegmentRomStart[]; extern u8 _ovl_En_FishingSegmentRomEnd[];
extern u8 _ovl_Obj_OshihikiSegmentStart[]; extern u8 _ovl_Obj_OshihikiSegmentEnd[]; extern u8 _ovl_Obj_OshihikiSegmentRomStart[]; extern u8 _ovl_Obj_OshihikiSegmentRomEnd[];
extern u8 _ovl_Eff_DustSegmentStart[]; extern u8 _ovl_Eff_DustSegmentEnd[]; extern u8 _ovl_Eff_DustSegmentRomStart[]; extern u8 _ovl_Eff_DustSegmentRomEnd[];
extern u8 _ovl_Bg_UmajumpSegmentStart[]; extern u8 _ovl_Bg_UmajumpSegmentEnd[]; extern u8 _ovl_Bg_UmajumpSegmentRomStart[]; extern u8 _ovl_Bg_UmajumpSegmentRomEnd[];
extern u8 _ovl_En_InsectSegmentStart[]; extern u8 _ovl_En_InsectSegmentEnd[]; extern u8 _ovl_En_InsectSegmentRomStart[]; extern u8 _ovl_En_InsectSegmentRomEnd[];
extern u8 _ovl_En_ButteSegmentStart[]; extern u8 _ovl_En_ButteSegmentEnd[]; extern u8 _ovl_En_ButteSegmentRomStart[]; extern u8 _ovl_En_ButteSegmentRomEnd[];
extern u8 _ovl_En_FishSegmentStart[]; extern u8 _ovl_En_FishSegmentEnd[]; extern u8 _ovl_En_FishSegmentRomStart[]; extern u8 _ovl_En_FishSegmentRomEnd[];
extern u8 _ovl_Item_EtceteraSegmentStart[]; extern u8 _ovl_Item_EtceteraSegmentEnd[]; extern u8 _ovl_Item_EtceteraSegmentRomStart[]; extern u8 _ovl_Item_EtceteraSegmentRomEnd[];
extern u8 _ovl_Arrow_FireSegmentStart[]; extern u8 _ovl_Arrow_FireSegmentEnd[]; extern u8 _ovl_Arrow_FireSegmentRomStart[]; extern u8 _ovl_Arrow_FireSegmentRomEnd[];
extern u8 _ovl_Arrow_IceSegmentStart[]; extern u8 _ovl_Arrow_IceSegmentEnd[]; extern u8 _ovl_Arrow_IceSegmentRomStart[]; extern u8 _ovl_Arrow_IceSegmentRomEnd[];
extern u8 _ovl_Arrow_LightSegmentStart[]; extern u8 _ovl_Arrow_LightSegmentEnd[]; extern u8 _ovl_Arrow_LightSegmentRomStart[]; extern u8 _ovl_Arrow_LightSegmentRomEnd[];
extern u8 _ovl_Obj_KibakoSegmentStart[]; extern u8 _ovl_Obj_KibakoSegmentEnd[]; extern u8 _ovl_Obj_KibakoSegmentRomStart[]; extern u8 _ovl_Obj_KibakoSegmentRomEnd[];
extern u8 _ovl_Obj_TsuboSegmentStart[]; extern u8 _ovl_Obj_TsuboSegmentEnd[]; extern u8 _ovl_Obj_TsuboSegmentRomStart[]; extern u8 _ovl_Obj_TsuboSegmentRomEnd[];
extern u8 _ovl_En_IkSegmentStart[]; extern u8 _ovl_En_IkSegmentEnd[]; extern u8 _ovl_En_IkSegmentRomStart[]; extern u8 _ovl_En_IkSegmentRomEnd[];
extern u8 _ovl_Demo_ShdSegmentStart[]; extern u8 _ovl_Demo_ShdSegmentEnd[]; extern u8 _ovl_Demo_ShdSegmentRomStart[]; extern u8 _ovl_Demo_ShdSegmentRomEnd[];
extern u8 _ovl_En_DnsSegmentStart[]; extern u8 _ovl_En_DnsSegmentEnd[]; extern u8 _ovl_En_DnsSegmentRomStart[]; extern u8 _ovl_En_DnsSegmentRomEnd[];
extern u8 _ovl_Elf_MsgSegmentStart[]; extern u8 _ovl_Elf_MsgSegmentEnd[]; extern u8 _ovl_Elf_MsgSegmentRomStart[]; extern u8 _ovl_Elf_MsgSegmentRomEnd[];
extern u8 _ovl_En_HonotrapSegmentStart[]; extern u8 _ovl_En_HonotrapSegmentEnd[]; extern u8 _ovl_En_HonotrapSegmentRomStart[]; extern u8 _ovl_En_HonotrapSegmentRomEnd[];
extern u8 _ovl_En_Tubo_TrapSegmentStart[]; extern u8 _ovl_En_Tubo_TrapSegmentEnd[]; extern u8 _ovl_En_Tubo_TrapSegmentRomStart[]; extern u8 _ovl_En_Tubo_TrapSegmentRomEnd[];
extern u8 _ovl_Obj_Ice_PolySegmentStart[]; extern u8 _ovl_Obj_Ice_PolySegmentEnd[]; extern u8 _ovl_Obj_Ice_PolySegmentRomStart[]; extern u8 _ovl_Obj_Ice_PolySegmentRomEnd[];
extern u8 _ovl_En_FzSegmentStart[]; extern u8 _ovl_En_FzSegmentEnd[]; extern u8 _ovl_En_FzSegmentRomStart[]; extern u8 _ovl_En_FzSegmentRomEnd[];
extern u8 _ovl_En_KusaSegmentStart[]; extern u8 _ovl_En_KusaSegmentEnd[]; extern u8 _ovl_En_KusaSegmentRomStart[]; extern u8 _ovl_En_KusaSegmentRomEnd[];
extern u8 _ovl_Obj_BeanSegmentStart[]; extern u8 _ovl_Obj_BeanSegmentEnd[]; extern u8 _ovl_Obj_BeanSegmentRomStart[]; extern u8 _ovl_Obj_BeanSegmentRomEnd[];
extern u8 _ovl_Obj_BombiwaSegmentStart[]; extern u8 _ovl_Obj_BombiwaSegmentEnd[]; extern u8 _ovl_Obj_BombiwaSegmentRomStart[]; extern u8 _ovl_Obj_BombiwaSegmentRomEnd[];
extern u8 _ovl_Obj_SwitchSegmentStart[]; extern u8 _ovl_Obj_SwitchSegmentEnd[]; extern u8 _ovl_Obj_SwitchSegmentRomStart[]; extern u8 _ovl_Obj_SwitchSegmentRomEnd[];
extern u8 _ovl_Obj_LiftSegmentStart[]; extern u8 _ovl_Obj_LiftSegmentEnd[]; extern u8 _ovl_Obj_LiftSegmentRomStart[]; extern u8 _ovl_Obj_LiftSegmentRomEnd[];
extern u8 _ovl_Obj_HsblockSegmentStart[]; extern u8 _ovl_Obj_HsblockSegmentEnd[]; extern u8 _ovl_Obj_HsblockSegmentRomStart[]; extern u8 _ovl_Obj_HsblockSegmentRomEnd[];
extern u8 _ovl_En_Okarina_TagSegmentStart[]; extern u8 _ovl_En_Okarina_TagSegmentEnd[]; extern u8 _ovl_En_Okarina_TagSegmentRomStart[]; extern u8 _ovl_En_Okarina_TagSegmentRomEnd[];
extern u8 _ovl_En_GoroiwaSegmentStart[]; extern u8 _ovl_En_GoroiwaSegmentEnd[]; extern u8 _ovl_En_GoroiwaSegmentRomStart[]; extern u8 _ovl_En_GoroiwaSegmentRomEnd[];
extern u8 _ovl_En_DaikuSegmentStart[]; extern u8 _ovl_En_DaikuSegmentEnd[]; extern u8 _ovl_En_DaikuSegmentRomStart[]; extern u8 _ovl_En_DaikuSegmentRomEnd[];
extern u8 _ovl_En_NwcSegmentStart[]; extern u8 _ovl_En_NwcSegmentEnd[]; extern u8 _ovl_En_NwcSegmentRomStart[]; extern u8 _ovl_En_NwcSegmentRomEnd[];
extern u8 _ovl_Item_InboxSegmentStart[]; extern u8 _ovl_Item_InboxSegmentEnd[]; extern u8 _ovl_Item_InboxSegmentRomStart[]; extern u8 _ovl_Item_InboxSegmentRomEnd[];
extern u8 _ovl_En_Ge1SegmentStart[]; extern u8 _ovl_En_Ge1SegmentEnd[]; extern u8 _ovl_En_Ge1SegmentRomStart[]; extern u8 _ovl_En_Ge1SegmentRomEnd[];
extern u8 _ovl_Obj_BlockstopSegmentStart[]; extern u8 _ovl_Obj_BlockstopSegmentEnd[]; extern u8 _ovl_Obj_BlockstopSegmentRomStart[]; extern u8 _ovl_Obj_BlockstopSegmentRomEnd[];
extern u8 _ovl_En_SdaSegmentStart[]; extern u8 _ovl_En_SdaSegmentEnd[]; extern u8 _ovl_En_SdaSegmentRomStart[]; extern u8 _ovl_En_SdaSegmentRomEnd[];
extern u8 _ovl_En_Clear_TagSegmentStart[]; extern u8 _ovl_En_Clear_TagSegmentEnd[]; extern u8 _ovl_En_Clear_TagSegmentRomStart[]; extern u8 _ovl_En_Clear_TagSegmentRomEnd[];
extern u8 _ovl_En_GmSegmentStart[]; extern u8 _ovl_En_GmSegmentEnd[]; extern u8 _ovl_En_GmSegmentRomStart[]; extern u8 _ovl_En_GmSegmentRomEnd[];
extern u8 _ovl_En_MsSegmentStart[]; extern u8 _ovl_En_MsSegmentEnd[]; extern u8 _ovl_En_MsSegmentRomStart[]; extern u8 _ovl_En_MsSegmentRomEnd[];
extern u8 _ovl_En_HsSegmentStart[]; extern u8 _ovl_En_HsSegmentEnd[]; extern u8 _ovl_En_HsSegmentRomStart[]; extern u8 _ovl_En_HsSegmentRomEnd[];
extern u8 _ovl_Bg_IngateSegmentStart[]; extern u8 _ovl_Bg_IngateSegmentEnd[]; extern u8 _ovl_Bg_IngateSegmentRomStart[]; extern u8 _ovl_Bg_IngateSegmentRomEnd[];
extern u8 _ovl_En_KanbanSegmentStart[]; extern u8 _ovl_En_KanbanSegmentEnd[]; extern u8 _ovl_En_KanbanSegmentRomStart[]; extern u8 _ovl_En_KanbanSegmentRomEnd[];
extern u8 _ovl_En_Attack_NiwSegmentStart[]; extern u8 _ovl_En_Attack_NiwSegmentEnd[]; extern u8 _ovl_En_Attack_NiwSegmentRomStart[]; extern u8 _ovl_En_Attack_NiwSegmentRomEnd[];
extern u8 _ovl_En_MkSegmentStart[]; extern u8 _ovl_En_MkSegmentEnd[]; extern u8 _ovl_En_MkSegmentRomStart[]; extern u8 _ovl_En_MkSegmentRomEnd[];
extern u8 _ovl_En_OwlSegmentStart[]; extern u8 _ovl_En_OwlSegmentEnd[]; extern u8 _ovl_En_OwlSegmentRomStart[]; extern u8 _ovl_En_OwlSegmentRomEnd[];
extern u8 _ovl_En_IshiSegmentStart[]; extern u8 _ovl_En_IshiSegmentEnd[]; extern u8 _ovl_En_IshiSegmentRomStart[]; extern u8 _ovl_En_IshiSegmentRomEnd[];
extern u8 _ovl_Obj_HanaSegmentStart[]; extern u8 _ovl_Obj_HanaSegmentEnd[]; extern u8 _ovl_Obj_HanaSegmentRomStart[]; extern u8 _ovl_Obj_HanaSegmentRomEnd[];
extern u8 _ovl_Obj_LightswitchSegmentStart[]; extern u8 _ovl_Obj_LightswitchSegmentEnd[]; extern u8 _ovl_Obj_LightswitchSegmentRomStart[]; extern u8 _ovl_Obj_LightswitchSegmentRomEnd[];
extern u8 _ovl_Obj_Mure2SegmentStart[]; extern u8 _ovl_Obj_Mure2SegmentEnd[]; extern u8 _ovl_Obj_Mure2SegmentRomStart[]; extern u8 _ovl_Obj_Mure2SegmentRomEnd[];
extern u8 _ovl_En_FuSegmentStart[]; extern u8 _ovl_En_FuSegmentEnd[]; extern u8 _ovl_En_FuSegmentRomStart[]; extern u8 _ovl_En_FuSegmentRomEnd[];
extern u8 _ovl_En_StreamSegmentStart[]; extern u8 _ovl_En_StreamSegmentEnd[]; extern u8 _ovl_En_StreamSegmentRomStart[]; extern u8 _ovl_En_StreamSegmentRomEnd[];
extern u8 _ovl_En_MmSegmentStart[]; extern u8 _ovl_En_MmSegmentEnd[]; extern u8 _ovl_En_MmSegmentRomStart[]; extern u8 _ovl_En_MmSegmentRomEnd[];
extern u8 _ovl_En_Weather_TagSegmentStart[]; extern u8 _ovl_En_Weather_TagSegmentEnd[]; extern u8 _ovl_En_Weather_TagSegmentRomStart[]; extern u8 _ovl_En_Weather_TagSegmentRomEnd[];
extern u8 _ovl_En_AniSegmentStart[]; extern u8 _ovl_En_AniSegmentEnd[]; extern u8 _ovl_En_AniSegmentRomStart[]; extern u8 _ovl_En_AniSegmentRomEnd[];
extern u8 _ovl_En_JsSegmentStart[]; extern u8 _ovl_En_JsSegmentEnd[]; extern u8 _ovl_En_JsSegmentRomStart[]; extern u8 _ovl_En_JsSegmentRomEnd[];
extern u8 _ovl_En_Okarina_EffectSegmentStart[]; extern u8 _ovl_En_Okarina_EffectSegmentEnd[]; extern u8 _ovl_En_Okarina_EffectSegmentRomStart[]; extern u8 _ovl_En_Okarina_EffectSegmentRomEnd[];
extern u8 _ovl_En_MagSegmentStart[]; extern u8 _ovl_En_MagSegmentEnd[]; extern u8 _ovl_En_MagSegmentRomStart[]; extern u8 _ovl_En_MagSegmentRomEnd[];
extern u8 _ovl_Elf_Msg2SegmentStart[]; extern u8 _ovl_Elf_Msg2SegmentEnd[]; extern u8 _ovl_Elf_Msg2SegmentRomStart[]; extern u8 _ovl_Elf_Msg2SegmentRomEnd[];
extern u8 _ovl_Bg_F40_SwliftSegmentStart[]; extern u8 _ovl_Bg_F40_SwliftSegmentEnd[]; extern u8 _ovl_Bg_F40_SwliftSegmentRomStart[]; extern u8 _ovl_Bg_F40_SwliftSegmentRomEnd[];
extern u8 _ovl_En_KakasiSegmentStart[]; extern u8 _ovl_En_KakasiSegmentEnd[]; extern u8 _ovl_En_KakasiSegmentRomStart[]; extern u8 _ovl_En_KakasiSegmentRomEnd[];
extern u8 _ovl_Obj_MakeoshihikiSegmentStart[]; extern u8 _ovl_Obj_MakeoshihikiSegmentEnd[]; extern u8 _ovl_Obj_MakeoshihikiSegmentRomStart[]; extern u8 _ovl_Obj_MakeoshihikiSegmentRomEnd[];
extern u8 _ovl_Oceff_SpotSegmentStart[]; extern u8 _ovl_Oceff_SpotSegmentEnd[]; extern u8 _ovl_Oceff_SpotSegmentRomStart[]; extern u8 _ovl_Oceff_SpotSegmentRomEnd[];
extern u8 _ovl_En_TorchSegmentStart[]; extern u8 _ovl_En_TorchSegmentEnd[]; extern u8 _ovl_En_TorchSegmentRomStart[]; extern u8 _ovl_En_TorchSegmentRomEnd[];
extern u8 _ovl_Shot_SunSegmentStart[]; extern u8 _ovl_Shot_SunSegmentEnd[]; extern u8 _ovl_Shot_SunSegmentRomStart[]; extern u8 _ovl_Shot_SunSegmentRomEnd[];
extern u8 _ovl_Obj_RoomtimerSegmentStart[]; extern u8 _ovl_Obj_RoomtimerSegmentEnd[]; extern u8 _ovl_Obj_RoomtimerSegmentRomStart[]; extern u8 _ovl_Obj_RoomtimerSegmentRomEnd[];
extern u8 _ovl_En_SshSegmentStart[]; extern u8 _ovl_En_SshSegmentEnd[]; extern u8 _ovl_En_SshSegmentRomStart[]; extern u8 _ovl_En_SshSegmentRomEnd[];
extern u8 _ovl_Oceff_WipeSegmentStart[]; extern u8 _ovl_Oceff_WipeSegmentEnd[]; extern u8 _ovl_Oceff_WipeSegmentRomStart[]; extern u8 _ovl_Oceff_WipeSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_DustSegmentStart[]; extern u8 _ovl_Effect_Ss_DustSegmentEnd[]; extern u8 _ovl_Effect_Ss_DustSegmentRomStart[]; extern u8 _ovl_Effect_Ss_DustSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_KirakiraSegmentStart[]; extern u8 _ovl_Effect_Ss_KirakiraSegmentEnd[]; extern u8 _ovl_Effect_Ss_KirakiraSegmentRomStart[]; extern u8 _ovl_Effect_Ss_KirakiraSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Bomb2SegmentStart[]; extern u8 _ovl_Effect_Ss_Bomb2SegmentEnd[]; extern u8 _ovl_Effect_Ss_Bomb2SegmentRomStart[]; extern u8 _ovl_Effect_Ss_Bomb2SegmentRomEnd[];
extern u8 _ovl_Effect_Ss_BlastSegmentStart[]; extern u8 _ovl_Effect_Ss_BlastSegmentEnd[]; extern u8 _ovl_Effect_Ss_BlastSegmentRomStart[]; extern u8 _ovl_Effect_Ss_BlastSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_G_SpkSegmentStart[]; extern u8 _ovl_Effect_Ss_G_SpkSegmentEnd[]; extern u8 _ovl_Effect_Ss_G_SpkSegmentRomStart[]; extern u8 _ovl_Effect_Ss_G_SpkSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_D_FireSegmentStart[]; extern u8 _ovl_Effect_Ss_D_FireSegmentEnd[]; extern u8 _ovl_Effect_Ss_D_FireSegmentRomStart[]; extern u8 _ovl_Effect_Ss_D_FireSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_BubbleSegmentStart[]; extern u8 _ovl_Effect_Ss_BubbleSegmentEnd[]; extern u8 _ovl_Effect_Ss_BubbleSegmentRomStart[]; extern u8 _ovl_Effect_Ss_BubbleSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_G_RippleSegmentStart[]; extern u8 _ovl_Effect_Ss_G_RippleSegmentEnd[]; extern u8 _ovl_Effect_Ss_G_RippleSegmentRomStart[]; extern u8 _ovl_Effect_Ss_G_RippleSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_G_SplashSegmentStart[]; extern u8 _ovl_Effect_Ss_G_SplashSegmentEnd[]; extern u8 _ovl_Effect_Ss_G_SplashSegmentRomStart[]; extern u8 _ovl_Effect_Ss_G_SplashSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_G_FireSegmentStart[]; extern u8 _ovl_Effect_Ss_G_FireSegmentEnd[]; extern u8 _ovl_Effect_Ss_G_FireSegmentRomStart[]; extern u8 _ovl_Effect_Ss_G_FireSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_LightningSegmentStart[]; extern u8 _ovl_Effect_Ss_LightningSegmentEnd[]; extern u8 _ovl_Effect_Ss_LightningSegmentRomStart[]; extern u8 _ovl_Effect_Ss_LightningSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Dt_BubbleSegmentStart[]; extern u8 _ovl_Effect_Ss_Dt_BubbleSegmentEnd[]; extern u8 _ovl_Effect_Ss_Dt_BubbleSegmentRomStart[]; extern u8 _ovl_Effect_Ss_Dt_BubbleSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_HahenSegmentStart[]; extern u8 _ovl_Effect_Ss_HahenSegmentEnd[]; extern u8 _ovl_Effect_Ss_HahenSegmentRomStart[]; extern u8 _ovl_Effect_Ss_HahenSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_StickSegmentStart[]; extern u8 _ovl_Effect_Ss_StickSegmentEnd[]; extern u8 _ovl_Effect_Ss_StickSegmentRomStart[]; extern u8 _ovl_Effect_Ss_StickSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_SibukiSegmentStart[]; extern u8 _ovl_Effect_Ss_SibukiSegmentEnd[]; extern u8 _ovl_Effect_Ss_SibukiSegmentRomStart[]; extern u8 _ovl_Effect_Ss_SibukiSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Stone1SegmentStart[]; extern u8 _ovl_Effect_Ss_Stone1SegmentEnd[]; extern u8 _ovl_Effect_Ss_Stone1SegmentRomStart[]; extern u8 _ovl_Effect_Ss_Stone1SegmentRomEnd[];
extern u8 _ovl_Effect_Ss_HitmarkSegmentStart[]; extern u8 _ovl_Effect_Ss_HitmarkSegmentEnd[]; extern u8 _ovl_Effect_Ss_HitmarkSegmentRomStart[]; extern u8 _ovl_Effect_Ss_HitmarkSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Fhg_FlashSegmentStart[]; extern u8 _ovl_Effect_Ss_Fhg_FlashSegmentEnd[]; extern u8 _ovl_Effect_Ss_Fhg_FlashSegmentRomStart[]; extern u8 _ovl_Effect_Ss_Fhg_FlashSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_K_FireSegmentStart[]; extern u8 _ovl_Effect_Ss_K_FireSegmentEnd[]; extern u8 _ovl_Effect_Ss_K_FireSegmentRomStart[]; extern u8 _ovl_Effect_Ss_K_FireSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Solder_Srch_BallSegmentStart[]; extern u8 _ovl_Effect_Ss_Solder_Srch_BallSegmentEnd[]; extern u8 _ovl_Effect_Ss_Solder_Srch_BallSegmentRomStart[]; extern u8 _ovl_Effect_Ss_Solder_Srch_BallSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_KakeraSegmentStart[]; extern u8 _ovl_Effect_Ss_KakeraSegmentEnd[]; extern u8 _ovl_Effect_Ss_KakeraSegmentRomStart[]; extern u8 _ovl_Effect_Ss_KakeraSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Ice_PieceSegmentStart[]; extern u8 _ovl_Effect_Ss_Ice_PieceSegmentEnd[]; extern u8 _ovl_Effect_Ss_Ice_PieceSegmentRomStart[]; extern u8 _ovl_Effect_Ss_Ice_PieceSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_En_IceSegmentStart[]; extern u8 _ovl_Effect_Ss_En_IceSegmentEnd[]; extern u8 _ovl_Effect_Ss_En_IceSegmentRomStart[]; extern u8 _ovl_Effect_Ss_En_IceSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Fire_TailSegmentStart[]; extern u8 _ovl_Effect_Ss_Fire_TailSegmentEnd[]; extern u8 _ovl_Effect_Ss_Fire_TailSegmentRomStart[]; extern u8 _ovl_Effect_Ss_Fire_TailSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_En_FireSegmentStart[]; extern u8 _ovl_Effect_Ss_En_FireSegmentEnd[]; extern u8 _ovl_Effect_Ss_En_FireSegmentRomStart[]; extern u8 _ovl_Effect_Ss_En_FireSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_ExtraSegmentStart[]; extern u8 _ovl_Effect_Ss_ExtraSegmentEnd[]; extern u8 _ovl_Effect_Ss_ExtraSegmentRomStart[]; extern u8 _ovl_Effect_Ss_ExtraSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Dead_DbSegmentStart[]; extern u8 _ovl_Effect_Ss_Dead_DbSegmentEnd[]; extern u8 _ovl_Effect_Ss_Dead_DbSegmentRomStart[]; extern u8 _ovl_Effect_Ss_Dead_DbSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Dead_DdSegmentStart[]; extern u8 _ovl_Effect_Ss_Dead_DdSegmentEnd[]; extern u8 _ovl_Effect_Ss_Dead_DdSegmentRomStart[]; extern u8 _ovl_Effect_Ss_Dead_DdSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Dead_DsSegmentStart[]; extern u8 _ovl_Effect_Ss_Dead_DsSegmentEnd[]; extern u8 _ovl_Effect_Ss_Dead_DsSegmentRomStart[]; extern u8 _ovl_Effect_Ss_Dead_DsSegmentRomEnd[];
extern u8 _ovl_Oceff_StormSegmentStart[]; extern u8 _ovl_Oceff_StormSegmentEnd[]; extern u8 _ovl_Oceff_StormSegmentRomStart[]; extern u8 _ovl_Oceff_StormSegmentRomEnd[];
extern u8 _ovl_Obj_DemoSegmentStart[]; extern u8 _ovl_Obj_DemoSegmentEnd[]; extern u8 _ovl_Obj_DemoSegmentRomStart[]; extern u8 _ovl_Obj_DemoSegmentRomEnd[];
extern u8 _ovl_En_MinislimeSegmentStart[]; extern u8 _ovl_En_MinislimeSegmentEnd[]; extern u8 _ovl_En_MinislimeSegmentRomStart[]; extern u8 _ovl_En_MinislimeSegmentRomEnd[];
extern u8 _ovl_En_NutsballSegmentStart[]; extern u8 _ovl_En_NutsballSegmentEnd[]; extern u8 _ovl_En_NutsballSegmentRomStart[]; extern u8 _ovl_En_NutsballSegmentRomEnd[];
extern u8 _ovl_Oceff_Wipe2SegmentStart[]; extern u8 _ovl_Oceff_Wipe2SegmentEnd[]; extern u8 _ovl_Oceff_Wipe2SegmentRomStart[]; extern u8 _ovl_Oceff_Wipe2SegmentRomEnd[];
extern u8 _ovl_Oceff_Wipe3SegmentStart[]; extern u8 _ovl_Oceff_Wipe3SegmentEnd[]; extern u8 _ovl_Oceff_Wipe3SegmentRomStart[]; extern u8 _ovl_Oceff_Wipe3SegmentRomEnd[];
extern u8 _ovl_En_DgSegmentStart[]; extern u8 _ovl_En_DgSegmentEnd[]; extern u8 _ovl_En_DgSegmentRomStart[]; extern u8 _ovl_En_DgSegmentRomEnd[];
extern u8 _ovl_En_SiSegmentStart[]; extern u8 _ovl_En_SiSegmentEnd[]; extern u8 _ovl_En_SiSegmentRomStart[]; extern u8 _ovl_En_SiSegmentRomEnd[];
extern u8 _ovl_Obj_CombSegmentStart[]; extern u8 _ovl_Obj_CombSegmentEnd[]; extern u8 _ovl_Obj_CombSegmentRomStart[]; extern u8 _ovl_Obj_CombSegmentRomEnd[];
extern u8 _ovl_Obj_Kibako2SegmentStart[]; extern u8 _ovl_Obj_Kibako2SegmentEnd[]; extern u8 _ovl_Obj_Kibako2SegmentRomStart[]; extern u8 _ovl_Obj_Kibako2SegmentRomEnd[];
extern u8 _ovl_En_Hs2SegmentStart[]; extern u8 _ovl_En_Hs2SegmentEnd[]; extern u8 _ovl_En_Hs2SegmentRomStart[]; extern u8 _ovl_En_Hs2SegmentRomEnd[];
extern u8 _ovl_Obj_Mure3SegmentStart[]; extern u8 _ovl_Obj_Mure3SegmentEnd[]; extern u8 _ovl_Obj_Mure3SegmentRomStart[]; extern u8 _ovl_Obj_Mure3SegmentRomEnd[];
extern u8 _ovl_En_TgSegmentStart[]; extern u8 _ovl_En_TgSegmentEnd[]; extern u8 _ovl_En_TgSegmentRomStart[]; extern u8 _ovl_En_TgSegmentRomEnd[];
extern u8 _ovl_En_WfSegmentStart[]; extern u8 _ovl_En_WfSegmentEnd[]; extern u8 _ovl_En_WfSegmentRomStart[]; extern u8 _ovl_En_WfSegmentRomEnd[];
extern u8 _ovl_En_SkbSegmentStart[]; extern u8 _ovl_En_SkbSegmentEnd[]; extern u8 _ovl_En_SkbSegmentRomStart[]; extern u8 _ovl_En_SkbSegmentRomEnd[];
extern u8 _ovl_En_GsSegmentStart[]; extern u8 _ovl_En_GsSegmentEnd[]; extern u8 _ovl_En_GsSegmentRomStart[]; extern u8 _ovl_En_GsSegmentRomEnd[];
extern u8 _ovl_Obj_SoundSegmentStart[]; extern u8 _ovl_Obj_SoundSegmentEnd[]; extern u8 _ovl_Obj_SoundSegmentRomStart[]; extern u8 _ovl_Obj_SoundSegmentRomEnd[];
extern u8 _ovl_En_CrowSegmentStart[]; extern u8 _ovl_En_CrowSegmentEnd[]; extern u8 _ovl_En_CrowSegmentRomStart[]; extern u8 _ovl_En_CrowSegmentRomEnd[];
extern u8 _ovl_En_CowSegmentStart[]; extern u8 _ovl_En_CowSegmentEnd[]; extern u8 _ovl_En_CowSegmentRomStart[]; extern u8 _ovl_En_CowSegmentRomEnd[];
extern u8 _ovl_Oceff_Wipe4SegmentStart[]; extern u8 _ovl_Oceff_Wipe4SegmentEnd[]; extern u8 _ovl_Oceff_Wipe4SegmentRomStart[]; extern u8 _ovl_Oceff_Wipe4SegmentRomEnd[];
extern u8 _ovl_En_ZoSegmentStart[]; extern u8 _ovl_En_ZoSegmentEnd[]; extern u8 _ovl_En_ZoSegmentRomStart[]; extern u8 _ovl_En_ZoSegmentRomEnd[];
extern u8 _ovl_Effect_Ss_Ice_SmokeSegmentStart[]; extern u8 _ovl_Effect_Ss_Ice_SmokeSegmentEnd[]; extern u8 _ovl_Effect_Ss_Ice_SmokeSegmentRomStart[]; extern u8 _ovl_Effect_Ss_Ice_SmokeSegmentRomEnd[];
extern u8 _ovl_Obj_MakekinsutaSegmentStart[]; extern u8 _ovl_Obj_MakekinsutaSegmentEnd[]; extern u8 _ovl_Obj_MakekinsutaSegmentRomStart[]; extern u8 _ovl_Obj_MakekinsutaSegmentRomEnd[];
extern u8 _ovl_En_Ge3SegmentStart[]; extern u8 _ovl_En_Ge3SegmentEnd[]; extern u8 _ovl_En_Ge3SegmentRomStart[]; extern u8 _ovl_En_Ge3SegmentRomEnd[];
extern u8 _ovl_Obj_HamishiSegmentStart[]; extern u8 _ovl_Obj_HamishiSegmentEnd[]; extern u8 _ovl_Obj_HamishiSegmentRomStart[]; extern u8 _ovl_Obj_HamishiSegmentRomEnd[];
extern u8 _ovl_En_Zl4SegmentStart[]; extern u8 _ovl_En_Zl4SegmentEnd[]; extern u8 _ovl_En_Zl4SegmentRomStart[]; extern u8 _ovl_En_Zl4SegmentRomEnd[];
extern u8 _ovl_En_Mm2SegmentStart[]; extern u8 _ovl_En_Mm2SegmentEnd[]; extern u8 _ovl_En_Mm2SegmentRomStart[]; extern u8 _ovl_En_Mm2SegmentRomEnd[];
extern u8 _ovl_Door_SpiralSegmentStart[]; extern u8 _ovl_Door_SpiralSegmentEnd[]; extern u8 _ovl_Door_SpiralSegmentRomStart[]; extern u8 _ovl_Door_SpiralSegmentRomEnd[];
extern u8 _ovl_Obj_PzlblockSegmentStart[]; extern u8 _ovl_Obj_PzlblockSegmentEnd[]; extern u8 _ovl_Obj_PzlblockSegmentRomStart[]; extern u8 _ovl_Obj_PzlblockSegmentRomEnd[];
extern u8 _ovl_Obj_TogeSegmentStart[]; extern u8 _ovl_Obj_TogeSegmentEnd[]; extern u8 _ovl_Obj_TogeSegmentRomStart[]; extern u8 _ovl_Obj_TogeSegmentRomEnd[];
extern u8 _ovl_Obj_ArmosSegmentStart[]; extern u8 _ovl_Obj_ArmosSegmentEnd[]; extern u8 _ovl_Obj_ArmosSegmentRomStart[]; extern u8 _ovl_Obj_ArmosSegmentRomEnd[];
extern u8 _ovl_Obj_BoyoSegmentStart[]; extern u8 _ovl_Obj_BoyoSegmentEnd[]; extern u8 _ovl_Obj_BoyoSegmentRomStart[]; extern u8 _ovl_Obj_BoyoSegmentRomEnd[];
extern u8 _ovl_En_GrasshopperSegmentStart[]; extern u8 _ovl_En_GrasshopperSegmentEnd[]; extern u8 _ovl_En_GrasshopperSegmentRomStart[]; extern u8 _ovl_En_GrasshopperSegmentRomEnd[];
extern u8 _ovl_Obj_GrassSegmentStart[]; extern u8 _ovl_Obj_GrassSegmentEnd[]; extern u8 _ovl_Obj_GrassSegmentRomStart[]; extern u8 _ovl_Obj_GrassSegmentRomEnd[];
extern u8 _ovl_Obj_Grass_CarrySegmentStart[]; extern u8 _ovl_Obj_Grass_CarrySegmentEnd[]; extern u8 _ovl_Obj_Grass_CarrySegmentRomStart[]; extern u8 _ovl_Obj_Grass_CarrySegmentRomEnd[];
extern u8 _ovl_Obj_Grass_UnitSegmentStart[]; extern u8 _ovl_Obj_Grass_UnitSegmentEnd[]; extern u8 _ovl_Obj_Grass_UnitSegmentRomStart[]; extern u8 _ovl_Obj_Grass_UnitSegmentRomEnd[];
extern u8 _ovl_Bg_Fire_WallSegmentStart[]; extern u8 _ovl_Bg_Fire_WallSegmentEnd[]; extern u8 _ovl_Bg_Fire_WallSegmentRomStart[]; extern u8 _ovl_Bg_Fire_WallSegmentRomEnd[];
extern u8 _ovl_En_BuSegmentStart[]; extern u8 _ovl_En_BuSegmentEnd[]; extern u8 _ovl_En_BuSegmentRomStart[]; extern u8 _ovl_En_BuSegmentRomEnd[];
extern u8 _ovl_En_Encount3SegmentStart[]; extern u8 _ovl_En_Encount3SegmentEnd[]; extern u8 _ovl_En_Encount3SegmentRomStart[]; extern u8 _ovl_En_Encount3SegmentRomEnd[];
extern u8 _ovl_En_JsoSegmentStart[]; extern u8 _ovl_En_JsoSegmentEnd[]; extern u8 _ovl_En_JsoSegmentRomStart[]; extern u8 _ovl_En_JsoSegmentRomEnd[];
extern u8 _ovl_Obj_ChikuwaSegmentStart[]; extern u8 _ovl_Obj_ChikuwaSegmentEnd[]; extern u8 _ovl_Obj_ChikuwaSegmentRomStart[]; extern u8 _ovl_Obj_ChikuwaSegmentRomEnd[];
extern u8 _ovl_En_KnightSegmentStart[]; extern u8 _ovl_En_KnightSegmentEnd[]; extern u8 _ovl_En_KnightSegmentRomStart[]; extern u8 _ovl_En_KnightSegmentRomEnd[];
extern u8 _ovl_En_Warp_tagSegmentStart[]; extern u8 _ovl_En_Warp_tagSegmentEnd[]; extern u8 _ovl_En_Warp_tagSegmentRomStart[]; extern u8 _ovl_En_Warp_tagSegmentRomEnd[];
extern u8 _ovl_En_Aob_01SegmentStart[]; extern u8 _ovl_En_Aob_01SegmentEnd[]; extern u8 _ovl_En_Aob_01SegmentRomStart[]; extern u8 _ovl_En_Aob_01SegmentRomEnd[];
extern u8 _ovl_En_Boj_01SegmentStart[]; extern u8 _ovl_En_Boj_01SegmentEnd[]; extern u8 _ovl_En_Boj_01SegmentRomStart[]; extern u8 _ovl_En_Boj_01SegmentRomEnd[];
extern u8 _ovl_En_Boj_02SegmentStart[]; extern u8 _ovl_En_Boj_02SegmentEnd[]; extern u8 _ovl_En_Boj_02SegmentRomStart[]; extern u8 _ovl_En_Boj_02SegmentRomEnd[];
extern u8 _ovl_En_Boj_03SegmentStart[]; extern u8 _ovl_En_Boj_03SegmentEnd[]; extern u8 _ovl_En_Boj_03SegmentRomStart[]; extern u8 _ovl_En_Boj_03SegmentRomEnd[];
extern u8 _ovl_En_Encount4SegmentStart[]; extern u8 _ovl_En_Encount4SegmentEnd[]; extern u8 _ovl_En_Encount4SegmentRomStart[]; extern u8 _ovl_En_Encount4SegmentRomEnd[];
extern u8 _ovl_En_Bom_Bowl_ManSegmentStart[]; extern u8 _ovl_En_Bom_Bowl_ManSegmentEnd[]; extern u8 _ovl_En_Bom_Bowl_ManSegmentRomStart[]; extern u8 _ovl_En_Bom_Bowl_ManSegmentRomEnd[];
extern u8 _ovl_En_Syateki_ManSegmentStart[]; extern u8 _ovl_En_Syateki_ManSegmentEnd[]; extern u8 _ovl_En_Syateki_ManSegmentRomStart[]; extern u8 _ovl_En_Syateki_ManSegmentRomEnd[];
extern u8 _ovl_Bg_IcicleSegmentStart[]; extern u8 _ovl_Bg_IcicleSegmentEnd[]; extern u8 _ovl_Bg_IcicleSegmentRomStart[]; extern u8 _ovl_Bg_IcicleSegmentRomEnd[];
extern u8 _ovl_En_Syateki_CrowSegmentStart[]; extern u8 _ovl_En_Syateki_CrowSegmentEnd[]; extern u8 _ovl_En_Syateki_CrowSegmentRomStart[]; extern u8 _ovl_En_Syateki_CrowSegmentRomEnd[];
extern u8 _ovl_En_Boj_04SegmentStart[]; extern u8 _ovl_En_Boj_04SegmentEnd[]; extern u8 _ovl_En_Boj_04SegmentRomStart[]; extern u8 _ovl_En_Boj_04SegmentRomEnd[];
extern u8 _ovl_En_Cne_01SegmentStart[]; extern u8 _ovl_En_Cne_01SegmentEnd[]; extern u8 _ovl_En_Cne_01SegmentRomStart[]; extern u8 _ovl_En_Cne_01SegmentRomEnd[];
extern u8 _ovl_En_Bba_01SegmentStart[]; extern u8 _ovl_En_Bba_01SegmentEnd[]; extern u8 _ovl_En_Bba_01SegmentRomStart[]; extern u8 _ovl_En_Bba_01SegmentRomEnd[];
extern u8 _ovl_En_Bji_01SegmentStart[]; extern u8 _ovl_En_Bji_01SegmentEnd[]; extern u8 _ovl_En_Bji_01SegmentRomStart[]; extern u8 _ovl_En_Bji_01SegmentRomEnd[];
extern u8 _ovl_Bg_SpdwebSegmentStart[]; extern u8 _ovl_Bg_SpdwebSegmentEnd[]; extern u8 _ovl_Bg_SpdwebSegmentRomStart[]; extern u8 _ovl_Bg_SpdwebSegmentRomEnd[];
extern u8 _ovl_En_Mt_tagSegmentStart[]; extern u8 _ovl_En_Mt_tagSegmentEnd[]; extern u8 _ovl_En_Mt_tagSegmentRomStart[]; extern u8 _ovl_En_Mt_tagSegmentRomEnd[];
extern u8 _ovl_Boss_01SegmentStart[]; extern u8 _ovl_Boss_01SegmentEnd[]; extern u8 _ovl_Boss_01SegmentRomStart[]; extern u8 _ovl_Boss_01SegmentRomEnd[];
extern u8 _ovl_Boss_02SegmentStart[]; extern u8 _ovl_Boss_02SegmentEnd[]; extern u8 _ovl_Boss_02SegmentRomStart[]; extern u8 _ovl_Boss_02SegmentRomEnd[];
extern u8 _ovl_Boss_03SegmentStart[]; extern u8 _ovl_Boss_03SegmentEnd[]; extern u8 _ovl_Boss_03SegmentRomStart[]; extern u8 _ovl_Boss_03SegmentRomEnd[];
extern u8 _ovl_Boss_04SegmentStart[]; extern u8 _ovl_Boss_04SegmentEnd[]; extern u8 _ovl_Boss_04SegmentRomStart[]; extern u8 _ovl_Boss_04SegmentRomEnd[];
extern u8 _ovl_Boss_05SegmentStart[]; extern u8 _ovl_Boss_05SegmentEnd[]; extern u8 _ovl_Boss_05SegmentRomStart[]; extern u8 _ovl_Boss_05SegmentRomEnd[];
extern u8 _ovl_Boss_06SegmentStart[]; extern u8 _ovl_Boss_06SegmentEnd[]; extern u8 _ovl_Boss_06SegmentRomStart[]; extern u8 _ovl_Boss_06SegmentRomEnd[];
extern u8 _ovl_Boss_07SegmentStart[]; extern u8 _ovl_Boss_07SegmentEnd[]; extern u8 _ovl_Boss_07SegmentRomStart[]; extern u8 _ovl_Boss_07SegmentRomEnd[];
extern u8 _ovl_Bg_Dy_YoseizoSegmentStart[]; extern u8 _ovl_Bg_Dy_YoseizoSegmentEnd[]; extern u8 _ovl_Bg_Dy_YoseizoSegmentRomStart[]; extern u8 _ovl_Bg_Dy_YoseizoSegmentRomEnd[];
extern u8 _ovl_En_Boj_05SegmentStart[]; extern u8 _ovl_En_Boj_05SegmentEnd[]; extern u8 _ovl_En_Boj_05SegmentRomStart[]; extern u8 _ovl_En_Boj_05SegmentRomEnd[];
extern u8 _ovl_En_Sob1SegmentStart[]; extern u8 _ovl_En_Sob1SegmentEnd[]; extern u8 _ovl_En_Sob1SegmentRomStart[]; extern u8 _ovl_En_Sob1SegmentRomEnd[];
extern u8 _ovl_En_GoSegmentStart[]; extern u8 _ovl_En_GoSegmentEnd[]; extern u8 _ovl_En_GoSegmentRomStart[]; extern u8 _ovl_En_GoSegmentRomEnd[];
extern u8 _ovl_En_RafSegmentStart[]; extern u8 _ovl_En_RafSegmentEnd[]; extern u8 _ovl_En_RafSegmentRomStart[]; extern u8 _ovl_En_RafSegmentRomEnd[];
extern u8 _ovl_Obj_FunenSegmentStart[]; extern u8 _ovl_Obj_FunenSegmentEnd[]; extern u8 _ovl_Obj_FunenSegmentRomStart[]; extern u8 _ovl_Obj_FunenSegmentRomEnd[];
extern u8 _ovl_Obj_RailliftSegmentStart[]; extern u8 _ovl_Obj_RailliftSegmentEnd[]; extern u8 _ovl_Obj_RailliftSegmentRomStart[]; extern u8 _ovl_Obj_RailliftSegmentRomEnd[];
extern u8 _ovl_Bg_Numa_HanaSegmentStart[]; extern u8 _ovl_Bg_Numa_HanaSegmentEnd[]; extern u8 _ovl_Bg_Numa_HanaSegmentRomStart[]; extern u8 _ovl_Bg_Numa_HanaSegmentRomEnd[];
extern u8 _ovl_Obj_FlowerpotSegmentStart[]; extern u8 _ovl_Obj_FlowerpotSegmentEnd[]; extern u8 _ovl_Obj_FlowerpotSegmentRomStart[]; extern u8 _ovl_Obj_FlowerpotSegmentRomEnd[];
extern u8 _ovl_Obj_SpinyrollSegmentStart[]; extern u8 _ovl_Obj_SpinyrollSegmentEnd[]; extern u8 _ovl_Obj_SpinyrollSegmentRomStart[]; extern u8 _ovl_Obj_SpinyrollSegmentRomEnd[];
extern u8 _ovl_Dm_HinaSegmentStart[]; extern u8 _ovl_Dm_HinaSegmentEnd[]; extern u8 _ovl_Dm_HinaSegmentRomStart[]; extern u8 _ovl_Dm_HinaSegmentRomEnd[];
extern u8 _ovl_En_Syateki_WfSegmentStart[]; extern u8 _ovl_En_Syateki_WfSegmentEnd[]; extern u8 _ovl_En_Syateki_WfSegmentRomStart[]; extern u8 _ovl_En_Syateki_WfSegmentRomEnd[];
extern u8 _ovl_Obj_SkateblockSegmentStart[]; extern u8 _ovl_Obj_SkateblockSegmentEnd[]; extern u8 _ovl_Obj_SkateblockSegmentRomStart[]; extern u8 _ovl_Obj_SkateblockSegmentRomEnd[];
extern u8 _ovl_Effect_En_Ice_BlockSegmentStart[]; extern u8 _ovl_Effect_En_Ice_BlockSegmentEnd[]; extern u8 _ovl_Effect_En_Ice_BlockSegmentRomStart[]; extern u8 _ovl_Effect_En_Ice_BlockSegmentRomEnd[];
extern u8 _ovl_Obj_IceblockSegmentStart[]; extern u8 _ovl_Obj_IceblockSegmentEnd[]; extern u8 _ovl_Obj_IceblockSegmentRomStart[]; extern u8 _ovl_Obj_IceblockSegmentRomEnd[];
extern u8 _ovl_En_BigpametSegmentStart[]; extern u8 _ovl_En_BigpametSegmentEnd[]; extern u8 _ovl_En_BigpametSegmentRomStart[]; extern u8 _ovl_En_BigpametSegmentRomEnd[];
extern u8 _ovl_Bg_Dblue_MovebgSegmentStart[]; extern u8 _ovl_Bg_Dblue_MovebgSegmentEnd[]; extern u8 _ovl_Bg_Dblue_MovebgSegmentRomStart[]; extern u8 _ovl_Bg_Dblue_MovebgSegmentRomEnd[];
extern u8 _ovl_En_Syateki_DekunutsSegmentStart[]; extern u8 _ovl_En_Syateki_DekunutsSegmentEnd[]; extern u8 _ovl_En_Syateki_DekunutsSegmentRomStart[]; extern u8 _ovl_En_Syateki_DekunutsSegmentRomEnd[];
extern u8 _ovl_Elf_Msg3SegmentStart[]; extern u8 _ovl_Elf_Msg3SegmentEnd[]; extern u8 _ovl_Elf_Msg3SegmentRomStart[]; extern u8 _ovl_Elf_Msg3SegmentRomEnd[];
extern u8 _ovl_En_FgSegmentStart[]; extern u8 _ovl_En_FgSegmentEnd[]; extern u8 _ovl_En_FgSegmentRomStart[]; extern u8 _ovl_En_FgSegmentRomEnd[];
extern u8 _ovl_Dm_RavineSegmentStart[]; extern u8 _ovl_Dm_RavineSegmentEnd[]; extern u8 _ovl_Dm_RavineSegmentRomStart[]; extern u8 _ovl_Dm_RavineSegmentRomEnd[];
extern u8 _ovl_Dm_SaSegmentStart[]; extern u8 _ovl_Dm_SaSegmentEnd[]; extern u8 _ovl_Dm_SaSegmentRomStart[]; extern u8 _ovl_Dm_SaSegmentRomEnd[];
extern u8 _ovl_En_SlimeSegmentStart[]; extern u8 _ovl_En_SlimeSegmentEnd[]; extern u8 _ovl_En_SlimeSegmentRomStart[]; extern u8 _ovl_En_SlimeSegmentRomEnd[];
extern u8 _ovl_En_PrSegmentStart[]; extern u8 _ovl_En_PrSegmentEnd[]; extern u8 _ovl_En_PrSegmentRomStart[]; extern u8 _ovl_En_PrSegmentRomEnd[];
extern u8 _ovl_Obj_ToudaiSegmentStart[]; extern u8 _ovl_Obj_ToudaiSegmentEnd[]; extern u8 _ovl_Obj_ToudaiSegmentRomStart[]; extern u8 _ovl_Obj_ToudaiSegmentRomEnd[];
extern u8 _ovl_Obj_EntotuSegmentStart[]; extern u8 _ovl_Obj_EntotuSegmentEnd[]; extern u8 _ovl_Obj_EntotuSegmentRomStart[]; extern u8 _ovl_Obj_EntotuSegmentRomEnd[];
extern u8 _ovl_Obj_BellSegmentStart[]; extern u8 _ovl_Obj_BellSegmentEnd[]; extern u8 _ovl_Obj_BellSegmentRomStart[]; extern u8 _ovl_Obj_BellSegmentRomEnd[];
extern u8 _ovl_En_Syateki_OkutaSegmentStart[]; extern u8 _ovl_En_Syateki_OkutaSegmentEnd[]; extern u8 _ovl_En_Syateki_OkutaSegmentRomStart[]; extern u8 _ovl_En_Syateki_OkutaSegmentRomEnd[];
extern u8 _ovl_Obj_ShutterSegmentStart[]; extern u8 _ovl_Obj_ShutterSegmentEnd[]; extern u8 _ovl_Obj_ShutterSegmentRomStart[]; extern u8 _ovl_Obj_ShutterSegmentRomEnd[];
extern u8 _ovl_Dm_ZlSegmentStart[]; extern u8 _ovl_Dm_ZlSegmentEnd[]; extern u8 _ovl_Dm_ZlSegmentRomStart[]; extern u8 _ovl_Dm_ZlSegmentRomEnd[];
extern u8 _ovl_En_RuSegmentStart[]; extern u8 _ovl_En_RuSegmentEnd[]; extern u8 _ovl_En_RuSegmentRomStart[]; extern u8 _ovl_En_RuSegmentRomEnd[];
extern u8 _ovl_En_ElfgrpSegmentStart[]; extern u8 _ovl_En_ElfgrpSegmentEnd[]; extern u8 _ovl_En_ElfgrpSegmentRomStart[]; extern u8 _ovl_En_ElfgrpSegmentRomEnd[];
extern u8 _ovl_Dm_TsgSegmentStart[]; extern u8 _ovl_Dm_TsgSegmentEnd[]; extern u8 _ovl_Dm_TsgSegmentRomStart[]; extern u8 _ovl_Dm_TsgSegmentRomEnd[];
extern u8 _ovl_En_BaguoSegmentStart[]; extern u8 _ovl_En_BaguoSegmentEnd[]; extern u8 _ovl_En_BaguoSegmentRomStart[]; extern u8 _ovl_En_BaguoSegmentRomEnd[];
extern u8 _ovl_Obj_VspinyrollSegmentStart[]; extern u8 _ovl_Obj_VspinyrollSegmentEnd[]; extern u8 _ovl_Obj_VspinyrollSegmentRomStart[]; extern u8 _ovl_Obj_VspinyrollSegmentRomEnd[];
extern u8 _ovl_Obj_SmorkSegmentStart[]; extern u8 _ovl_Obj_SmorkSegmentEnd[]; extern u8 _ovl_Obj_SmorkSegmentRomStart[]; extern u8 _ovl_Obj_SmorkSegmentRomEnd[];
extern u8 _ovl_En_Test2SegmentStart[]; extern u8 _ovl_En_Test2SegmentEnd[]; extern u8 _ovl_En_Test2SegmentRomStart[]; extern u8 _ovl_En_Test2SegmentRomEnd[];
extern u8 _ovl_En_Test3SegmentStart[]; extern u8 _ovl_En_Test3SegmentEnd[]; extern u8 _ovl_En_Test3SegmentRomStart[]; extern u8 _ovl_En_Test3SegmentRomEnd[];
extern u8 _ovl_En_Test4SegmentStart[]; extern u8 _ovl_En_Test4SegmentEnd[]; extern u8 _ovl_En_Test4SegmentRomStart[]; extern u8 _ovl_En_Test4SegmentRomEnd[];
extern u8 _ovl_En_BatSegmentStart[]; extern u8 _ovl_En_BatSegmentEnd[]; extern u8 _ovl_En_BatSegmentRomStart[]; extern u8 _ovl_En_BatSegmentRomEnd[];
extern u8 _ovl_En_SekihiSegmentStart[]; extern u8 _ovl_En_SekihiSegmentEnd[]; extern u8 _ovl_En_SekihiSegmentRomStart[]; extern u8 _ovl_En_SekihiSegmentRomEnd[];
extern u8 _ovl_En_WizSegmentStart[]; extern u8 _ovl_En_WizSegmentEnd[]; extern u8 _ovl_En_WizSegmentRomStart[]; extern u8 _ovl_En_WizSegmentRomEnd[];
extern u8 _ovl_En_Wiz_BrockSegmentStart[]; extern u8 _ovl_En_Wiz_BrockSegmentEnd[]; extern u8 _ovl_En_Wiz_BrockSegmentRomStart[]; extern u8 _ovl_En_Wiz_BrockSegmentRomEnd[];
extern u8 _ovl_En_Wiz_FireSegmentStart[]; extern u8 _ovl_En_Wiz_FireSegmentEnd[]; extern u8 _ovl_En_Wiz_FireSegmentRomStart[]; extern u8 _ovl_En_Wiz_FireSegmentRomEnd[];
extern u8 _ovl_Eff_ChangeSegmentStart[]; extern u8 _ovl_Eff_ChangeSegmentEnd[]; extern u8 _ovl_Eff_ChangeSegmentRomStart[]; extern u8 _ovl_Eff_ChangeSegmentRomEnd[];
extern u8 _ovl_Dm_StatueSegmentStart[]; extern u8 _ovl_Dm_StatueSegmentEnd[]; extern u8 _ovl_Dm_StatueSegmentRomStart[]; extern u8 _ovl_Dm_StatueSegmentRomEnd[];
extern u8 _ovl_Obj_FireshieldSegmentStart[]; extern u8 _ovl_Obj_FireshieldSegmentEnd[]; extern u8 _ovl_Obj_FireshieldSegmentRomStart[]; extern u8 _ovl_Obj_FireshieldSegmentRomEnd[];
extern u8 _ovl_Bg_LadderSegmentStart[]; extern u8 _ovl_Bg_LadderSegmentEnd[]; extern u8 _ovl_Bg_LadderSegmentRomStart[]; extern u8 _ovl_Bg_LadderSegmentRomEnd[];
extern u8 _ovl_En_MkkSegmentStart[]; extern u8 _ovl_En_MkkSegmentEnd[]; extern u8 _ovl_En_MkkSegmentRomStart[]; extern u8 _ovl_En_MkkSegmentRomEnd[];
extern u8 _ovl_Demo_GetitemSegmentStart[]; extern u8 _ovl_Demo_GetitemSegmentEnd[]; extern u8 _ovl_Demo_GetitemSegmentRomStart[]; extern u8 _ovl_Demo_GetitemSegmentRomEnd[];
extern u8 _ovl_En_DnbSegmentStart[]; extern u8 _ovl_En_DnbSegmentEnd[]; extern u8 _ovl_En_DnbSegmentRomStart[]; extern u8 _ovl_En_DnbSegmentRomEnd[];
extern u8 _ovl_En_DnhSegmentStart[]; extern u8 _ovl_En_DnhSegmentEnd[]; extern u8 _ovl_En_DnhSegmentRomStart[]; extern u8 _ovl_En_DnhSegmentRomEnd[];
extern u8 _ovl_En_DnkSegmentStart[]; extern u8 _ovl_En_DnkSegmentEnd[]; extern u8 _ovl_En_DnkSegmentRomStart[]; extern u8 _ovl_En_DnkSegmentRomEnd[];
extern u8 _ovl_En_DnqSegmentStart[]; extern u8 _ovl_En_DnqSegmentEnd[]; extern u8 _ovl_En_DnqSegmentRomStart[]; extern u8 _ovl_En_DnqSegmentRomEnd[];
extern u8 _ovl_Bg_Keikoku_SakuSegmentStart[]; extern u8 _ovl_Bg_Keikoku_SakuSegmentEnd[]; extern u8 _ovl_Bg_Keikoku_SakuSegmentRomStart[]; extern u8 _ovl_Bg_Keikoku_SakuSegmentRomEnd[];
extern u8 _ovl_Obj_HugebombiwaSegmentStart[]; extern u8 _ovl_Obj_HugebombiwaSegmentEnd[]; extern u8 _ovl_Obj_HugebombiwaSegmentRomStart[]; extern u8 _ovl_Obj_HugebombiwaSegmentRomEnd[];
extern u8 _ovl_En_Firefly2SegmentStart[]; extern u8 _ovl_En_Firefly2SegmentEnd[]; extern u8 _ovl_En_Firefly2SegmentRomStart[]; extern u8 _ovl_En_Firefly2SegmentRomEnd[];
extern u8 _ovl_En_RatSegmentStart[]; extern u8 _ovl_En_RatSegmentEnd[]; extern u8 _ovl_En_RatSegmentRomStart[]; extern u8 _ovl_En_RatSegmentRomEnd[];
extern u8 _ovl_En_Water_EffectSegmentStart[]; extern u8 _ovl_En_Water_EffectSegmentEnd[]; extern u8 _ovl_En_Water_EffectSegmentRomStart[]; extern u8 _ovl_En_Water_EffectSegmentRomEnd[];
extern u8 _ovl_En_Kusa2SegmentStart[]; extern u8 _ovl_En_Kusa2SegmentEnd[]; extern u8 _ovl_En_Kusa2SegmentRomStart[]; extern u8 _ovl_En_Kusa2SegmentRomEnd[];
extern u8 _ovl_Bg_Spout_FireSegmentStart[]; extern u8 _ovl_Bg_Spout_FireSegmentEnd[]; extern u8 _ovl_Bg_Spout_FireSegmentRomStart[]; extern u8 _ovl_Bg_Spout_FireSegmentRomEnd[];
extern u8 _ovl_En_Dy_ExtraSegmentStart[]; extern u8 _ovl_En_Dy_ExtraSegmentEnd[]; extern u8 _ovl_En_Dy_ExtraSegmentRomStart[]; extern u8 _ovl_En_Dy_ExtraSegmentRomEnd[];
extern u8 _ovl_En_BalSegmentStart[]; extern u8 _ovl_En_BalSegmentEnd[]; extern u8 _ovl_En_BalSegmentRomStart[]; extern u8 _ovl_En_BalSegmentRomEnd[];
extern u8 _ovl_En_Ginko_ManSegmentStart[]; extern u8 _ovl_En_Ginko_ManSegmentEnd[]; extern u8 _ovl_En_Ginko_ManSegmentRomStart[]; extern u8 _ovl_En_Ginko_ManSegmentRomEnd[];
extern u8 _ovl_En_Warp_UzuSegmentStart[]; extern u8 _ovl_En_Warp_UzuSegmentEnd[]; extern u8 _ovl_En_Warp_UzuSegmentRomStart[]; extern u8 _ovl_En_Warp_UzuSegmentRomEnd[];
extern u8 _ovl_Obj_DrifticeSegmentStart[]; extern u8 _ovl_Obj_DrifticeSegmentEnd[]; extern u8 _ovl_Obj_DrifticeSegmentRomStart[]; extern u8 _ovl_Obj_DrifticeSegmentRomEnd[];
extern u8 _ovl_En_Look_NutsSegmentStart[]; extern u8 _ovl_En_Look_NutsSegmentEnd[]; extern u8 _ovl_En_Look_NutsSegmentRomStart[]; extern u8 _ovl_En_Look_NutsSegmentRomEnd[];
extern u8 _ovl_En_Mushi2SegmentStart[]; extern u8 _ovl_En_Mushi2SegmentEnd[]; extern u8 _ovl_En_Mushi2SegmentRomStart[]; extern u8 _ovl_En_Mushi2SegmentRomEnd[];
extern u8 _ovl_En_FallSegmentStart[]; extern u8 _ovl_En_FallSegmentEnd[]; extern u8 _ovl_En_FallSegmentRomStart[]; extern u8 _ovl_En_FallSegmentRomEnd[];
extern u8 _ovl_En_Mm3SegmentStart[]; extern u8 _ovl_En_Mm3SegmentEnd[]; extern u8 _ovl_En_Mm3SegmentRomStart[]; extern u8 _ovl_En_Mm3SegmentRomEnd[];
extern u8 _ovl_Bg_Crace_MovebgSegmentStart[]; extern u8 _ovl_Bg_Crace_MovebgSegmentEnd[]; extern u8 _ovl_Bg_Crace_MovebgSegmentRomStart[]; extern u8 _ovl_Bg_Crace_MovebgSegmentRomEnd[];
extern u8 _ovl_En_DnoSegmentStart[]; extern u8 _ovl_En_DnoSegmentEnd[]; extern u8 _ovl_En_DnoSegmentRomStart[]; extern u8 _ovl_En_DnoSegmentRomEnd[];
extern u8 _ovl_En_Pr2SegmentStart[]; extern u8 _ovl_En_Pr2SegmentEnd[]; extern u8 _ovl_En_Pr2SegmentRomStart[]; extern u8 _ovl_En_Pr2SegmentRomEnd[];
extern u8 _ovl_En_PrzSegmentStart[]; extern u8 _ovl_En_PrzSegmentEnd[]; extern u8 _ovl_En_PrzSegmentRomStart[]; extern u8 _ovl_En_PrzSegmentRomEnd[];
extern u8 _ovl_En_Jso2SegmentStart[]; extern u8 _ovl_En_Jso2SegmentEnd[]; extern u8 _ovl_En_Jso2SegmentRomStart[]; extern u8 _ovl_En_Jso2SegmentRomEnd[];
extern u8 _ovl_Obj_EtceteraSegmentStart[]; extern u8 _ovl_Obj_EtceteraSegmentEnd[]; extern u8 _ovl_Obj_EtceteraSegmentRomStart[]; extern u8 _ovl_Obj_EtceteraSegmentRomEnd[];
extern u8 _ovl_En_EgolSegmentStart[]; extern u8 _ovl_En_EgolSegmentEnd[]; extern u8 _ovl_En_EgolSegmentRomStart[]; extern u8 _ovl_En_EgolSegmentRomEnd[];
extern u8 _ovl_Obj_MineSegmentStart[]; extern u8 _ovl_Obj_MineSegmentEnd[]; extern u8 _ovl_Obj_MineSegmentRomStart[]; extern u8 _ovl_Obj_MineSegmentRomEnd[];
extern u8 _ovl_Obj_PurifySegmentStart[]; extern u8 _ovl_Obj_PurifySegmentEnd[]; extern u8 _ovl_Obj_PurifySegmentRomStart[]; extern u8 _ovl_Obj_PurifySegmentRomEnd[];
extern u8 _ovl_En_TruSegmentStart[]; extern u8 _ovl_En_TruSegmentEnd[]; extern u8 _ovl_En_TruSegmentRomStart[]; extern u8 _ovl_En_TruSegmentRomEnd[];
extern u8 _ovl_En_TrtSegmentStart[]; extern u8 _ovl_En_TrtSegmentEnd[]; extern u8 _ovl_En_TrtSegmentRomStart[]; extern u8 _ovl_En_TrtSegmentRomEnd[];
extern u8 _ovl_En_Test5SegmentStart[]; extern u8 _ovl_En_Test5SegmentEnd[]; extern u8 _ovl_En_Test5SegmentRomStart[]; extern u8 _ovl_En_Test5SegmentRomEnd[];
extern u8 _ovl_En_Test6SegmentStart[]; extern u8 _ovl_En_Test6SegmentEnd[]; extern u8 _ovl_En_Test6SegmentRomStart[]; extern u8 _ovl_En_Test6SegmentRomEnd[];
extern u8 _ovl_En_AzSegmentStart[]; extern u8 _ovl_En_AzSegmentEnd[]; extern u8 _ovl_En_AzSegmentRomStart[]; extern u8 _ovl_En_AzSegmentRomEnd[];
extern u8 _ovl_En_EstoneSegmentStart[]; extern u8 _ovl_En_EstoneSegmentEnd[]; extern u8 _ovl_En_EstoneSegmentRomStart[]; extern u8 _ovl_En_EstoneSegmentRomEnd[];
extern u8 _ovl_Bg_Hakugin_PostSegmentStart[]; extern u8 _ovl_Bg_Hakugin_PostSegmentEnd[]; extern u8 _ovl_Bg_Hakugin_PostSegmentRomStart[]; extern u8 _ovl_Bg_Hakugin_PostSegmentRomEnd[];
extern u8 _ovl_Dm_OpstageSegmentStart[]; extern u8 _ovl_Dm_OpstageSegmentEnd[]; extern u8 _ovl_Dm_OpstageSegmentRomStart[]; extern u8 _ovl_Dm_OpstageSegmentRomEnd[];
extern u8 _ovl_Dm_StkSegmentStart[]; extern u8 _ovl_Dm_StkSegmentEnd[]; extern u8 _ovl_Dm_StkSegmentRomStart[]; extern u8 _ovl_Dm_StkSegmentRomEnd[];
extern u8 _ovl_Dm_Char00SegmentStart[]; extern u8 _ovl_Dm_Char00SegmentEnd[]; extern u8 _ovl_Dm_Char00SegmentRomStart[]; extern u8 _ovl_Dm_Char00SegmentRomEnd[];
extern u8 _ovl_Dm_Char01SegmentStart[]; extern u8 _ovl_Dm_Char01SegmentEnd[]; extern u8 _ovl_Dm_Char01SegmentRomStart[]; extern u8 _ovl_Dm_Char01SegmentRomEnd[];
extern u8 _ovl_Dm_Char02SegmentStart[]; extern u8 _ovl_Dm_Char02SegmentEnd[]; extern u8 _ovl_Dm_Char02SegmentRomStart[]; extern u8 _ovl_Dm_Char02SegmentRomEnd[];
extern u8 _ovl_Dm_Char03SegmentStart[]; extern u8 _ovl_Dm_Char03SegmentEnd[]; extern u8 _ovl_Dm_Char03SegmentRomStart[]; extern u8 _ovl_Dm_Char03SegmentRomEnd[];
extern u8 _ovl_Dm_Char04SegmentStart[]; extern u8 _ovl_Dm_Char04SegmentEnd[]; extern u8 _ovl_Dm_Char04SegmentRomStart[]; extern u8 _ovl_Dm_Char04SegmentRomEnd[];
extern u8 _ovl_Dm_Char05SegmentStart[]; extern u8 _ovl_Dm_Char05SegmentEnd[]; extern u8 _ovl_Dm_Char05SegmentRomStart[]; extern u8 _ovl_Dm_Char05SegmentRomEnd[];
extern u8 _ovl_Dm_Char06SegmentStart[]; extern u8 _ovl_Dm_Char06SegmentEnd[]; extern u8 _ovl_Dm_Char06SegmentRomStart[]; extern u8 _ovl_Dm_Char06SegmentRomEnd[];
extern u8 _ovl_Dm_Char07SegmentStart[]; extern u8 _ovl_Dm_Char07SegmentEnd[]; extern u8 _ovl_Dm_Char07SegmentRomStart[]; extern u8 _ovl_Dm_Char07SegmentRomEnd[];
extern u8 _ovl_Dm_Char08SegmentStart[]; extern u8 _ovl_Dm_Char08SegmentEnd[]; extern u8 _ovl_Dm_Char08SegmentRomStart[]; extern u8 _ovl_Dm_Char08SegmentRomEnd[];
extern u8 _ovl_Dm_Char09SegmentStart[]; extern u8 _ovl_Dm_Char09SegmentEnd[]; extern u8 _ovl_Dm_Char09SegmentRomStart[]; extern u8 _ovl_Dm_Char09SegmentRomEnd[];
extern u8 _ovl_Obj_TokeidaiSegmentStart[]; extern u8 _ovl_Obj_TokeidaiSegmentEnd[]; extern u8 _ovl_Obj_TokeidaiSegmentRomStart[]; extern u8 _ovl_Obj_TokeidaiSegmentRomEnd[];
extern u8 _ovl_En_MnkSegmentStart[]; extern u8 _ovl_En_MnkSegmentEnd[]; extern u8 _ovl_En_MnkSegmentRomStart[]; extern u8 _ovl_En_MnkSegmentRomEnd[];
extern u8 _ovl_En_EgblockSegmentStart[]; extern u8 _ovl_En_EgblockSegmentEnd[]; extern u8 _ovl_En_EgblockSegmentRomStart[]; extern u8 _ovl_En_EgblockSegmentRomEnd[];
extern u8 _ovl_En_Guard_NutsSegmentStart[]; extern u8 _ovl_En_Guard_NutsSegmentEnd[]; extern u8 _ovl_En_Guard_NutsSegmentRomStart[]; extern u8 _ovl_En_Guard_NutsSegmentRomEnd[];
extern u8 _ovl_Bg_Hakugin_BombwallSegmentStart[]; extern u8 _ovl_Bg_Hakugin_BombwallSegmentEnd[]; extern u8 _ovl_Bg_Hakugin_BombwallSegmentRomStart[]; extern u8 _ovl_Bg_Hakugin_BombwallSegmentRomEnd[];
extern u8 _ovl_Obj_Tokei_TobiraSegmentStart[]; extern u8 _ovl_Obj_Tokei_TobiraSegmentEnd[]; extern u8 _ovl_Obj_Tokei_TobiraSegmentRomStart[]; extern u8 _ovl_Obj_Tokei_TobiraSegmentRomEnd[];
extern u8 _ovl_Bg_Hakugin_ElvpoleSegmentStart[]; extern u8 _ovl_Bg_Hakugin_ElvpoleSegmentEnd[]; extern u8 _ovl_Bg_Hakugin_ElvpoleSegmentRomStart[]; extern u8 _ovl_Bg_Hakugin_ElvpoleSegmentRomEnd[];
extern u8 _ovl_En_Ma4SegmentStart[]; extern u8 _ovl_En_Ma4SegmentEnd[]; extern u8 _ovl_En_Ma4SegmentRomStart[]; extern u8 _ovl_En_Ma4SegmentRomEnd[];
extern u8 _ovl_En_TwigSegmentStart[]; extern u8 _ovl_En_TwigSegmentEnd[]; extern u8 _ovl_En_TwigSegmentRomStart[]; extern u8 _ovl_En_TwigSegmentRomEnd[];
extern u8 _ovl_En_Po_FusenSegmentStart[]; extern u8 _ovl_En_Po_FusenSegmentEnd[]; extern u8 _ovl_En_Po_FusenSegmentRomStart[]; extern u8 _ovl_En_Po_FusenSegmentRomEnd[];
extern u8 _ovl_En_Door_EtcSegmentStart[]; extern u8 _ovl_En_Door_EtcSegmentEnd[]; extern u8 _ovl_En_Door_EtcSegmentRomStart[]; extern u8 _ovl_En_Door_EtcSegmentRomEnd[];
extern u8 _ovl_En_BigokutaSegmentStart[]; extern u8 _ovl_En_BigokutaSegmentEnd[]; extern u8 _ovl_En_BigokutaSegmentRomStart[]; extern u8 _ovl_En_BigokutaSegmentRomEnd[];
extern u8 _ovl_Bg_IcefloeSegmentStart[]; extern u8 _ovl_Bg_IcefloeSegmentEnd[]; extern u8 _ovl_Bg_IcefloeSegmentRomStart[]; extern u8 _ovl_Bg_IcefloeSegmentRomEnd[];
extern u8 __385_0x00cfc450SegmentRomStart[]; extern u8 __385_0x00cfc450SegmentRomEnd[];
extern u8 __386_0x00cfc970SegmentRomStart[]; extern u8 __386_0x00cfc970SegmentRomEnd[];
extern u8 __387_0x00cfd400SegmentRomStart[]; extern u8 __387_0x00cfd400SegmentRomEnd[];
extern u8 __388_0x00cfdf10SegmentRomStart[]; extern u8 __388_0x00cfdf10SegmentRomEnd[];
extern u8 __389_0x00cfe150SegmentRomStart[]; extern u8 __389_0x00cfe150SegmentRomEnd[];
extern u8 _ovl_Effect_Ss_SbnSegmentStart[]; extern u8 _ovl_Effect_Ss_SbnSegmentEnd[]; extern u8 _ovl_Effect_Ss_SbnSegmentRomStart[]; extern u8 _ovl_Effect_Ss_SbnSegmentRomEnd[];
extern u8 _ovl_Obj_OcarinaliftSegmentStart[]; extern u8 _ovl_Obj_OcarinaliftSegmentEnd[]; extern u8 _ovl_Obj_OcarinaliftSegmentRomStart[]; extern u8 _ovl_Obj_OcarinaliftSegmentRomEnd[];
extern u8 _ovl_En_Time_TagSegmentStart[]; extern u8 _ovl_En_Time_TagSegmentEnd[]; extern u8 _ovl_En_Time_TagSegmentRomStart[]; extern u8 _ovl_En_Time_TagSegmentRomEnd[];
extern u8 _ovl_Bg_Open_ShutterSegmentStart[]; extern u8 _ovl_Bg_Open_ShutterSegmentEnd[]; extern u8 _ovl_Bg_Open_ShutterSegmentRomStart[]; extern u8 _ovl_Bg_Open_ShutterSegmentRomEnd[];
extern u8 _ovl_Bg_Open_SpotSegmentStart[]; extern u8 _ovl_Bg_Open_SpotSegmentEnd[]; extern u8 _ovl_Bg_Open_SpotSegmentRomStart[]; extern u8 _ovl_Bg_Open_SpotSegmentRomEnd[];
extern u8 _ovl_Bg_Fu_KaitenSegmentStart[]; extern u8 _ovl_Bg_Fu_KaitenSegmentEnd[]; extern u8 _ovl_Bg_Fu_KaitenSegmentRomStart[]; extern u8 _ovl_Bg_Fu_KaitenSegmentRomEnd[];
extern u8 _ovl_Obj_AquaSegmentStart[]; extern u8 _ovl_Obj_AquaSegmentEnd[]; extern u8 _ovl_Obj_AquaSegmentRomStart[]; extern u8 _ovl_Obj_AquaSegmentRomEnd[];
extern u8 _ovl_En_ElforgSegmentStart[]; extern u8 _ovl_En_ElforgSegmentEnd[]; extern u8 _ovl_En_ElforgSegmentRomStart[]; extern u8 _ovl_En_ElforgSegmentRomEnd[];
extern u8 _ovl_En_ElfbubSegmentStart[]; extern u8 _ovl_En_ElfbubSegmentEnd[]; extern u8 _ovl_En_ElfbubSegmentRomStart[]; extern u8 _ovl_En_ElfbubSegmentRomEnd[];
extern u8 _ovl_En_Fu_MatoSegmentStart[]; extern u8 _ovl_En_Fu_MatoSegmentEnd[]; extern u8 _ovl_En_Fu_MatoSegmentRomStart[]; extern u8 _ovl_En_Fu_MatoSegmentRomEnd[];
extern u8 _ovl_En_Fu_KagoSegmentStart[]; extern u8 _ovl_En_Fu_KagoSegmentEnd[]; extern u8 _ovl_En_Fu_KagoSegmentRomStart[]; extern u8 _ovl_En_Fu_KagoSegmentRomEnd[];
extern u8 _ovl_En_OsnSegmentStart[]; extern u8 _ovl_En_OsnSegmentEnd[]; extern u8 _ovl_En_OsnSegmentRomStart[]; extern u8 _ovl_En_OsnSegmentRomEnd[];
extern u8 _ovl_Bg_Ctower_GearSegmentStart[]; extern u8 _ovl_Bg_Ctower_GearSegmentEnd[]; extern u8 _ovl_Bg_Ctower_GearSegmentRomStart[]; extern u8 _ovl_Bg_Ctower_GearSegmentRomEnd[];
extern u8 _ovl_En_Trt2SegmentStart[]; extern u8 _ovl_En_Trt2SegmentEnd[]; extern u8 _ovl_En_Trt2SegmentRomStart[]; extern u8 _ovl_En_Trt2SegmentRomEnd[];
extern u8 _ovl_Obj_Tokei_StepSegmentStart[]; extern u8 _ovl_Obj_Tokei_StepSegmentEnd[]; extern u8 _ovl_Obj_Tokei_StepSegmentRomStart[]; extern u8 _ovl_Obj_Tokei_StepSegmentRomEnd[];
extern u8 _ovl_Bg_LotusSegmentStart[]; extern u8 _ovl_Bg_LotusSegmentEnd[]; extern u8 _ovl_Bg_LotusSegmentRomStart[]; extern u8 _ovl_Bg_LotusSegmentRomEnd[];
extern u8 _ovl_En_KameSegmentStart[]; extern u8 _ovl_En_KameSegmentEnd[]; extern u8 _ovl_En_KameSegmentRomStart[]; extern u8 _ovl_En_KameSegmentRomEnd[];
extern u8 _ovl_Obj_Takaraya_WallSegmentStart[]; extern u8 _ovl_Obj_Takaraya_WallSegmentEnd[]; extern u8 _ovl_Obj_Takaraya_WallSegmentRomStart[]; extern u8 _ovl_Obj_Takaraya_WallSegmentRomEnd[];
extern u8 _ovl_Bg_Fu_MizuSegmentStart[]; extern u8 _ovl_Bg_Fu_MizuSegmentEnd[]; extern u8 _ovl_Bg_Fu_MizuSegmentRomStart[]; extern u8 _ovl_Bg_Fu_MizuSegmentRomEnd[];
extern u8 _ovl_En_SellnutsSegmentStart[]; extern u8 _ovl_En_SellnutsSegmentEnd[]; extern u8 _ovl_En_SellnutsSegmentRomStart[]; extern u8 _ovl_En_SellnutsSegmentRomEnd[];
extern u8 _ovl_Bg_Dkjail_IvySegmentStart[]; extern u8 _ovl_Bg_Dkjail_IvySegmentEnd[]; extern u8 _ovl_Bg_Dkjail_IvySegmentRomStart[]; extern u8 _ovl_Bg_Dkjail_IvySegmentRomEnd[];
extern u8 _ovl_Obj_VisiblockSegmentStart[]; extern u8 _ovl_Obj_VisiblockSegmentEnd[]; extern u8 _ovl_Obj_VisiblockSegmentRomStart[]; extern u8 _ovl_Obj_VisiblockSegmentRomEnd[];
extern u8 _ovl_En_TakarayaSegmentStart[]; extern u8 _ovl_En_TakarayaSegmentEnd[]; extern u8 _ovl_En_TakarayaSegmentRomStart[]; extern u8 _ovl_En_TakarayaSegmentRomEnd[];
extern u8 _ovl_En_TsnSegmentStart[]; extern u8 _ovl_En_TsnSegmentEnd[]; extern u8 _ovl_En_TsnSegmentRomStart[]; extern u8 _ovl_En_TsnSegmentRomEnd[];
extern u8 _ovl_En_Ds2nSegmentStart[]; extern u8 _ovl_En_Ds2nSegmentEnd[]; extern u8 _ovl_En_Ds2nSegmentRomStart[]; extern u8 _ovl_En_Ds2nSegmentRomEnd[];
extern u8 _ovl_En_FsnSegmentStart[]; extern u8 _ovl_En_FsnSegmentEnd[]; extern u8 _ovl_En_FsnSegmentRomStart[]; extern u8 _ovl_En_FsnSegmentRomEnd[];
extern u8 _ovl_En_ShnSegmentStart[]; extern u8 _ovl_En_ShnSegmentEnd[]; extern u8 _ovl_En_ShnSegmentRomStart[]; extern u8 _ovl_En_ShnSegmentRomEnd[];
extern u8 _ovl_En_Stop_heishiSegmentStart[]; extern u8 _ovl_En_Stop_heishiSegmentEnd[]; extern u8 _ovl_En_Stop_heishiSegmentRomStart[]; extern u8 _ovl_En_Stop_heishiSegmentRomEnd[];
extern u8 _ovl_Obj_BigicicleSegmentStart[]; extern u8 _ovl_Obj_BigicicleSegmentEnd[]; extern u8 _ovl_Obj_BigicicleSegmentRomStart[]; extern u8 _ovl_Obj_BigicicleSegmentRomEnd[];
extern u8 _ovl_En_Lift_NutsSegmentStart[]; extern u8 _ovl_En_Lift_NutsSegmentEnd[]; extern u8 _ovl_En_Lift_NutsSegmentRomStart[]; extern u8 _ovl_En_Lift_NutsSegmentRomEnd[];
extern u8 _ovl_En_TkSegmentStart[]; extern u8 _ovl_En_TkSegmentEnd[]; extern u8 _ovl_En_TkSegmentRomStart[]; extern u8 _ovl_En_TkSegmentRomEnd[];
extern u8 _ovl_Bg_Market_StepSegmentStart[]; extern u8 _ovl_Bg_Market_StepSegmentEnd[]; extern u8 _ovl_Bg_Market_StepSegmentRomStart[]; extern u8 _ovl_Bg_Market_StepSegmentRomEnd[];
extern u8 _ovl_Obj_LupygameliftSegmentStart[]; extern u8 _ovl_Obj_LupygameliftSegmentEnd[]; extern u8 _ovl_Obj_LupygameliftSegmentRomStart[]; extern u8 _ovl_Obj_LupygameliftSegmentRomEnd[];
extern u8 _ovl_En_Test7SegmentStart[]; extern u8 _ovl_En_Test7SegmentEnd[]; extern u8 _ovl_En_Test7SegmentRomStart[]; extern u8 _ovl_En_Test7SegmentRomEnd[];
extern u8 _ovl_Obj_LightblockSegmentStart[]; extern u8 _ovl_Obj_LightblockSegmentEnd[]; extern u8 _ovl_Obj_LightblockSegmentRomStart[]; extern u8 _ovl_Obj_LightblockSegmentRomEnd[];
extern u8 _ovl_Mir_Ray2SegmentStart[]; extern u8 _ovl_Mir_Ray2SegmentEnd[]; extern u8 _ovl_Mir_Ray2SegmentRomStart[]; extern u8 _ovl_Mir_Ray2SegmentRomEnd[];
extern u8 _ovl_En_WdhandSegmentStart[]; extern u8 _ovl_En_WdhandSegmentEnd[]; extern u8 _ovl_En_WdhandSegmentRomStart[]; extern u8 _ovl_En_WdhandSegmentRomEnd[];
extern u8 _ovl_En_GamelupySegmentStart[]; extern u8 _ovl_En_GamelupySegmentEnd[]; extern u8 _ovl_En_GamelupySegmentRomStart[]; extern u8 _ovl_En_GamelupySegmentRomEnd[];
extern u8 _ovl_Bg_Danpei_MovebgSegmentStart[]; extern u8 _ovl_Bg_Danpei_MovebgSegmentEnd[]; extern u8 _ovl_Bg_Danpei_MovebgSegmentRomStart[]; extern u8 _ovl_Bg_Danpei_MovebgSegmentRomEnd[];
extern u8 _ovl_En_SnowwdSegmentStart[]; extern u8 _ovl_En_SnowwdSegmentEnd[]; extern u8 _ovl_En_SnowwdSegmentRomStart[]; extern u8 _ovl_En_SnowwdSegmentRomEnd[];
extern u8 _ovl_En_PmSegmentStart[]; extern u8 _ovl_En_PmSegmentEnd[]; extern u8 _ovl_En_PmSegmentRomStart[]; extern u8 _ovl_En_PmSegmentRomEnd[];
extern u8 _ovl_En_GakufuSegmentStart[]; extern u8 _ovl_En_GakufuSegmentEnd[]; extern u8 _ovl_En_GakufuSegmentRomStart[]; extern u8 _ovl_En_GakufuSegmentRomEnd[];
extern u8 _ovl_Elf_Msg4SegmentStart[]; extern u8 _ovl_Elf_Msg4SegmentEnd[]; extern u8 _ovl_Elf_Msg4SegmentRomStart[]; extern u8 _ovl_Elf_Msg4SegmentRomEnd[];
extern u8 _ovl_Elf_Msg5SegmentStart[]; extern u8 _ovl_Elf_Msg5SegmentEnd[]; extern u8 _ovl_Elf_Msg5SegmentRomStart[]; extern u8 _ovl_Elf_Msg5SegmentRomEnd[];
extern u8 _ovl_En_Col_ManSegmentStart[]; extern u8 _ovl_En_Col_ManSegmentEnd[]; extern u8 _ovl_En_Col_ManSegmentRomStart[]; extern u8 _ovl_En_Col_ManSegmentRomEnd[];
extern u8 _ovl_En_Talk_GibudSegmentStart[]; extern u8 _ovl_En_Talk_GibudSegmentEnd[]; extern u8 _ovl_En_Talk_GibudSegmentRomStart[]; extern u8 _ovl_En_Talk_GibudSegmentRomEnd[];
extern u8 _ovl_En_GiantSegmentStart[]; extern u8 _ovl_En_GiantSegmentEnd[]; extern u8 _ovl_En_GiantSegmentRomStart[]; extern u8 _ovl_En_GiantSegmentRomEnd[];
extern u8 _ovl_Obj_SnowballSegmentStart[]; extern u8 _ovl_Obj_SnowballSegmentEnd[]; extern u8 _ovl_Obj_SnowballSegmentRomStart[]; extern u8 _ovl_Obj_SnowballSegmentRomEnd[];
extern u8 _ovl_Boss_HakuginSegmentStart[]; extern u8 _ovl_Boss_HakuginSegmentEnd[]; extern u8 _ovl_Boss_HakuginSegmentRomStart[]; extern u8 _ovl_Boss_HakuginSegmentRomEnd[];
extern u8 _ovl_En_Gb2SegmentStart[]; extern u8 _ovl_En_Gb2SegmentEnd[]; extern u8 _ovl_En_Gb2SegmentRomStart[]; extern u8 _ovl_En_Gb2SegmentRomEnd[];
extern u8 _ovl_En_OnpumanSegmentStart[]; extern u8 _ovl_En_OnpumanSegmentEnd[]; extern u8 _ovl_En_OnpumanSegmentRomStart[]; extern u8 _ovl_En_OnpumanSegmentRomEnd[];
extern u8 _ovl_Bg_Tobira01SegmentStart[]; extern u8 _ovl_Bg_Tobira01SegmentEnd[]; extern u8 _ovl_Bg_Tobira01SegmentRomStart[]; extern u8 _ovl_Bg_Tobira01SegmentRomEnd[];
extern u8 _ovl_En_Tag_ObjSegmentStart[]; extern u8 _ovl_En_Tag_ObjSegmentEnd[]; extern u8 _ovl_En_Tag_ObjSegmentRomStart[]; extern u8 _ovl_En_Tag_ObjSegmentRomEnd[];
extern u8 _ovl_Obj_DhouseSegmentStart[]; extern u8 _ovl_Obj_DhouseSegmentEnd[]; extern u8 _ovl_Obj_DhouseSegmentRomStart[]; extern u8 _ovl_Obj_DhouseSegmentRomEnd[];
extern u8 _ovl_Obj_HakaisiSegmentStart[]; extern u8 _ovl_Obj_HakaisiSegmentEnd[]; extern u8 _ovl_Obj_HakaisiSegmentRomStart[]; extern u8 _ovl_Obj_HakaisiSegmentRomEnd[];
extern u8 _ovl_Bg_Hakugin_SwitchSegmentStart[]; extern u8 _ovl_Bg_Hakugin_SwitchSegmentEnd[]; extern u8 _ovl_Bg_Hakugin_SwitchSegmentRomStart[]; extern u8 _ovl_Bg_Hakugin_SwitchSegmentRomEnd[];
extern u8 _ovl_En_SnowmanSegmentStart[]; extern u8 _ovl_En_SnowmanSegmentEnd[]; extern u8 _ovl_En_SnowmanSegmentRomStart[]; extern u8 _ovl_En_SnowmanSegmentRomEnd[];
extern u8 _ovl_TG_SwSegmentStart[]; extern u8 _ovl_TG_SwSegmentEnd[]; extern u8 _ovl_TG_SwSegmentRomStart[]; extern u8 _ovl_TG_SwSegmentRomEnd[];
extern u8 _ovl_En_Po_SistersSegmentStart[]; extern u8 _ovl_En_Po_SistersSegmentEnd[]; extern u8 _ovl_En_Po_SistersSegmentRomStart[]; extern u8 _ovl_En_Po_SistersSegmentRomEnd[];
extern u8 _ovl_En_PpSegmentStart[]; extern u8 _ovl_En_PpSegmentEnd[]; extern u8 _ovl_En_PpSegmentRomStart[]; extern u8 _ovl_En_PpSegmentRomEnd[];
extern u8 _ovl_En_HakurockSegmentStart[]; extern u8 _ovl_En_HakurockSegmentEnd[]; extern u8 _ovl_En_HakurockSegmentRomStart[]; extern u8 _ovl_En_HakurockSegmentRomEnd[];
extern u8 _ovl_En_HanabiSegmentStart[]; extern u8 _ovl_En_HanabiSegmentEnd[]; extern u8 _ovl_En_HanabiSegmentRomStart[]; extern u8 _ovl_En_HanabiSegmentRomEnd[];
extern u8 _ovl_Obj_DowsingSegmentStart[]; extern u8 _ovl_Obj_DowsingSegmentEnd[]; extern u8 _ovl_Obj_DowsingSegmentRomStart[]; extern u8 _ovl_Obj_DowsingSegmentRomEnd[];
extern u8 _ovl_Obj_WindSegmentStart[]; extern u8 _ovl_Obj_WindSegmentEnd[]; extern u8 _ovl_Obj_WindSegmentRomStart[]; extern u8 _ovl_Obj_WindSegmentRomEnd[];
extern u8 _ovl_En_RacedogSegmentStart[]; extern u8 _ovl_En_RacedogSegmentEnd[]; extern u8 _ovl_En_RacedogSegmentRomStart[]; extern u8 _ovl_En_RacedogSegmentRomEnd[];
extern u8 _ovl_En_Kendo_JsSegmentStart[]; extern u8 _ovl_En_Kendo_JsSegmentEnd[]; extern u8 _ovl_En_Kendo_JsSegmentRomStart[]; extern u8 _ovl_En_Kendo_JsSegmentRomEnd[];
extern u8 _ovl_Bg_BotihasiraSegmentStart[]; extern u8 _ovl_Bg_BotihasiraSegmentEnd[]; extern u8 _ovl_Bg_BotihasiraSegmentRomStart[]; extern u8 _ovl_Bg_BotihasiraSegmentRomEnd[];
extern u8 _ovl_En_Fish2SegmentStart[]; extern u8 _ovl_En_Fish2SegmentEnd[]; extern u8 _ovl_En_Fish2SegmentRomStart[]; extern u8 _ovl_En_Fish2SegmentRomEnd[];
extern u8 _ovl_En_PstSegmentStart[]; extern u8 _ovl_En_PstSegmentEnd[]; extern u8 _ovl_En_PstSegmentRomStart[]; extern u8 _ovl_En_PstSegmentRomEnd[];
extern u8 _ovl_En_PohSegmentStart[]; extern u8 _ovl_En_PohSegmentEnd[]; extern u8 _ovl_En_PohSegmentRomStart[]; extern u8 _ovl_En_PohSegmentRomEnd[];
extern u8 _ovl_Obj_SpidertentSegmentStart[]; extern u8 _ovl_Obj_SpidertentSegmentEnd[]; extern u8 _ovl_Obj_SpidertentSegmentRomStart[]; extern u8 _ovl_Obj_SpidertentSegmentRomEnd[];
extern u8 _ovl_En_ZoraeggSegmentStart[]; extern u8 _ovl_En_ZoraeggSegmentEnd[]; extern u8 _ovl_En_ZoraeggSegmentRomStart[]; extern u8 _ovl_En_ZoraeggSegmentRomEnd[];
extern u8 _ovl_En_KbtSegmentStart[]; extern u8 _ovl_En_KbtSegmentEnd[]; extern u8 _ovl_En_KbtSegmentRomStart[]; extern u8 _ovl_En_KbtSegmentRomEnd[];
extern u8 _ovl_En_GgSegmentStart[]; extern u8 _ovl_En_GgSegmentEnd[]; extern u8 _ovl_En_GgSegmentRomStart[]; extern u8 _ovl_En_GgSegmentRomEnd[];
extern u8 _ovl_En_MarutaSegmentStart[]; extern u8 _ovl_En_MarutaSegmentEnd[]; extern u8 _ovl_En_MarutaSegmentRomStart[]; extern u8 _ovl_En_MarutaSegmentRomEnd[];
extern u8 _ovl_Obj_Snowball2SegmentStart[]; extern u8 _ovl_Obj_Snowball2SegmentEnd[]; extern u8 _ovl_Obj_Snowball2SegmentRomStart[]; extern u8 _ovl_Obj_Snowball2SegmentRomEnd[];
extern u8 _ovl_En_Gg2SegmentStart[]; extern u8 _ovl_En_Gg2SegmentEnd[]; extern u8 _ovl_En_Gg2SegmentRomStart[]; extern u8 _ovl_En_Gg2SegmentRomEnd[];
extern u8 _ovl_Obj_GhakaSegmentStart[]; extern u8 _ovl_Obj_GhakaSegmentEnd[]; extern u8 _ovl_Obj_GhakaSegmentRomStart[]; extern u8 _ovl_Obj_GhakaSegmentRomEnd[];
extern u8 _ovl_En_DnpSegmentStart[]; extern u8 _ovl_En_DnpSegmentEnd[]; extern u8 _ovl_En_DnpSegmentRomStart[]; extern u8 _ovl_En_DnpSegmentRomEnd[];
extern u8 _ovl_En_DaiSegmentStart[]; extern u8 _ovl_En_DaiSegmentEnd[]; extern u8 _ovl_En_DaiSegmentRomStart[]; extern u8 _ovl_En_DaiSegmentRomEnd[];
extern u8 _ovl_Bg_Goron_OyuSegmentStart[]; extern u8 _ovl_Bg_Goron_OyuSegmentEnd[]; extern u8 _ovl_Bg_Goron_OyuSegmentRomStart[]; extern u8 _ovl_Bg_Goron_OyuSegmentRomEnd[];
extern u8 _ovl_En_KgySegmentStart[]; extern u8 _ovl_En_KgySegmentEnd[]; extern u8 _ovl_En_KgySegmentRomStart[]; extern u8 _ovl_En_KgySegmentRomEnd[];
extern u8 _ovl_En_InvadepohSegmentStart[]; extern u8 _ovl_En_InvadepohSegmentEnd[]; extern u8 _ovl_En_InvadepohSegmentRomStart[]; extern u8 _ovl_En_InvadepohSegmentRomEnd[];
extern u8 _ovl_En_GkSegmentStart[]; extern u8 _ovl_En_GkSegmentEnd[]; extern u8 _ovl_En_GkSegmentRomStart[]; extern u8 _ovl_En_GkSegmentRomEnd[];
extern u8 _ovl_En_AnSegmentStart[]; extern u8 _ovl_En_AnSegmentEnd[]; extern u8 _ovl_En_AnSegmentRomStart[]; extern u8 _ovl_En_AnSegmentRomEnd[];
extern u8 _ovl_En_BeeSegmentStart[]; extern u8 _ovl_En_BeeSegmentEnd[]; extern u8 _ovl_En_BeeSegmentRomStart[]; extern u8 _ovl_En_BeeSegmentRomEnd[];
extern u8 _ovl_En_OtSegmentStart[]; extern u8 _ovl_En_OtSegmentEnd[]; extern u8 _ovl_En_OtSegmentRomStart[]; extern u8 _ovl_En_OtSegmentRomEnd[];
extern u8 _ovl_En_DragonSegmentStart[]; extern u8 _ovl_En_DragonSegmentEnd[]; extern u8 _ovl_En_DragonSegmentRomStart[]; extern u8 _ovl_En_DragonSegmentRomEnd[];
extern u8 _ovl_Obj_DoraSegmentStart[]; extern u8 _ovl_Obj_DoraSegmentEnd[]; extern u8 _ovl_Obj_DoraSegmentRomStart[]; extern u8 _ovl_Obj_DoraSegmentRomEnd[];
extern u8 _ovl_En_BigpoSegmentStart[]; extern u8 _ovl_En_BigpoSegmentEnd[]; extern u8 _ovl_En_BigpoSegmentRomStart[]; extern u8 _ovl_En_BigpoSegmentRomEnd[];
extern u8 _ovl_Obj_Kendo_KanbanSegmentStart[]; extern u8 _ovl_Obj_Kendo_KanbanSegmentEnd[]; extern u8 _ovl_Obj_Kendo_KanbanSegmentRomStart[]; extern u8 _ovl_Obj_Kendo_KanbanSegmentRomEnd[];
extern u8 _ovl_Obj_HarikoSegmentStart[]; extern u8 _ovl_Obj_HarikoSegmentEnd[]; extern u8 _ovl_Obj_HarikoSegmentRomStart[]; extern u8 _ovl_Obj_HarikoSegmentRomEnd[];
extern u8 _ovl_En_SthSegmentStart[]; extern u8 _ovl_En_SthSegmentEnd[]; extern u8 _ovl_En_SthSegmentRomStart[]; extern u8 _ovl_En_SthSegmentRomEnd[];
extern u8 _ovl_Bg_Sinkai_KabeSegmentStart[]; extern u8 _ovl_Bg_Sinkai_KabeSegmentEnd[]; extern u8 _ovl_Bg_Sinkai_KabeSegmentRomStart[]; extern u8 _ovl_Bg_Sinkai_KabeSegmentRomEnd[];
extern u8 _ovl_Bg_Haka_CurtainSegmentStart[]; extern u8 _ovl_Bg_Haka_CurtainSegmentEnd[]; extern u8 _ovl_Bg_Haka_CurtainSegmentRomStart[]; extern u8 _ovl_Bg_Haka_CurtainSegmentRomEnd[];
extern u8 _ovl_Bg_Kin2_BombwallSegmentStart[]; extern u8 _ovl_Bg_Kin2_BombwallSegmentEnd[]; extern u8 _ovl_Bg_Kin2_BombwallSegmentRomStart[]; extern u8 _ovl_Bg_Kin2_BombwallSegmentRomEnd[];
extern u8 _ovl_Bg_Kin2_FenceSegmentStart[]; extern u8 _ovl_Bg_Kin2_FenceSegmentEnd[]; extern u8 _ovl_Bg_Kin2_FenceSegmentRomStart[]; extern u8 _ovl_Bg_Kin2_FenceSegmentRomEnd[];
extern u8 _ovl_Bg_Kin2_PictureSegmentStart[]; extern u8 _ovl_Bg_Kin2_PictureSegmentEnd[]; extern u8 _ovl_Bg_Kin2_PictureSegmentRomStart[]; extern u8 _ovl_Bg_Kin2_PictureSegmentRomEnd[];
extern u8 _ovl_Bg_Kin2_ShelfSegmentStart[]; extern u8 _ovl_Bg_Kin2_ShelfSegmentEnd[]; extern u8 _ovl_Bg_Kin2_ShelfSegmentRomStart[]; extern u8 _ovl_Bg_Kin2_ShelfSegmentRomEnd[];
extern u8 _ovl_En_Rail_SkbSegmentStart[]; extern u8 _ovl_En_Rail_SkbSegmentEnd[]; extern u8 _ovl_En_Rail_SkbSegmentRomStart[]; extern u8 _ovl_En_Rail_SkbSegmentRomEnd[];
extern u8 _ovl_En_JgSegmentStart[]; extern u8 _ovl_En_JgSegmentEnd[]; extern u8 _ovl_En_JgSegmentRomStart[]; extern u8 _ovl_En_JgSegmentRomEnd[];
extern u8 _ovl_En_Tru_MtSegmentStart[]; extern u8 _ovl_En_Tru_MtSegmentEnd[]; extern u8 _ovl_En_Tru_MtSegmentRomStart[]; extern u8 _ovl_En_Tru_MtSegmentRomEnd[];
extern u8 _ovl_Obj_UmSegmentStart[]; extern u8 _ovl_Obj_UmSegmentEnd[]; extern u8 _ovl_Obj_UmSegmentRomStart[]; extern u8 _ovl_Obj_UmSegmentRomEnd[];
extern u8 _ovl_En_Neo_ReebaSegmentStart[]; extern u8 _ovl_En_Neo_ReebaSegmentEnd[]; extern u8 _ovl_En_Neo_ReebaSegmentRomStart[]; extern u8 _ovl_En_Neo_ReebaSegmentRomEnd[];
extern u8 _ovl_Bg_Mbar_ChairSegmentStart[]; extern u8 _ovl_Bg_Mbar_ChairSegmentEnd[]; extern u8 _ovl_Bg_Mbar_ChairSegmentRomStart[]; extern u8 _ovl_Bg_Mbar_ChairSegmentRomEnd[];
extern u8 _ovl_Bg_Ikana_BlockSegmentStart[]; extern u8 _ovl_Bg_Ikana_BlockSegmentEnd[]; extern u8 _ovl_Bg_Ikana_BlockSegmentRomStart[]; extern u8 _ovl_Bg_Ikana_BlockSegmentRomEnd[];
extern u8 _ovl_Bg_Ikana_MirrorSegmentStart[]; extern u8 _ovl_Bg_Ikana_MirrorSegmentEnd[]; extern u8 _ovl_Bg_Ikana_MirrorSegmentRomStart[]; extern u8 _ovl_Bg_Ikana_MirrorSegmentRomEnd[];
extern u8 _ovl_Bg_Ikana_RotaryroomSegmentStart[]; extern u8 _ovl_Bg_Ikana_RotaryroomSegmentEnd[]; extern u8 _ovl_Bg_Ikana_RotaryroomSegmentRomStart[]; extern u8 _ovl_Bg_Ikana_RotaryroomSegmentRomEnd[];
extern u8 _ovl_Bg_Dblue_BalanceSegmentStart[]; extern u8 _ovl_Bg_Dblue_BalanceSegmentEnd[]; extern u8 _ovl_Bg_Dblue_BalanceSegmentRomStart[]; extern u8 _ovl_Bg_Dblue_BalanceSegmentRomEnd[];
extern u8 _ovl_Bg_Dblue_WaterfallSegmentStart[]; extern u8 _ovl_Bg_Dblue_WaterfallSegmentEnd[]; extern u8 _ovl_Bg_Dblue_WaterfallSegmentRomStart[]; extern u8 _ovl_Bg_Dblue_WaterfallSegmentRomEnd[];
extern u8 _ovl_En_KaizokuSegmentStart[]; extern u8 _ovl_En_KaizokuSegmentEnd[]; extern u8 _ovl_En_KaizokuSegmentRomStart[]; extern u8 _ovl_En_KaizokuSegmentRomEnd[];
extern u8 _ovl_En_Ge2SegmentStart[]; extern u8 _ovl_En_Ge2SegmentEnd[]; extern u8 _ovl_En_Ge2SegmentRomStart[]; extern u8 _ovl_En_Ge2SegmentRomEnd[];
extern u8 _ovl_En_Ma_YtsSegmentStart[]; extern u8 _ovl_En_Ma_YtsSegmentEnd[]; extern u8 _ovl_En_Ma_YtsSegmentRomStart[]; extern u8 _ovl_En_Ma_YtsSegmentRomEnd[];
extern u8 _ovl_En_Ma_YtoSegmentStart[]; extern u8 _ovl_En_Ma_YtoSegmentEnd[]; extern u8 _ovl_En_Ma_YtoSegmentRomStart[]; extern u8 _ovl_En_Ma_YtoSegmentRomEnd[];
extern u8 _ovl_Obj_Tokei_TurretSegmentStart[]; extern u8 _ovl_Obj_Tokei_TurretSegmentEnd[]; extern u8 _ovl_Obj_Tokei_TurretSegmentRomStart[]; extern u8 _ovl_Obj_Tokei_TurretSegmentRomEnd[];
extern u8 _ovl_Bg_Dblue_ElevatorSegmentStart[]; extern u8 _ovl_Bg_Dblue_ElevatorSegmentEnd[]; extern u8 _ovl_Bg_Dblue_ElevatorSegmentRomStart[]; extern u8 _ovl_Bg_Dblue_ElevatorSegmentRomEnd[];
extern u8 _ovl_Obj_WarpstoneSegmentStart[]; extern u8 _ovl_Obj_WarpstoneSegmentEnd[]; extern u8 _ovl_Obj_WarpstoneSegmentRomStart[]; extern u8 _ovl_Obj_WarpstoneSegmentRomEnd[];
extern u8 _ovl_En_ZogSegmentStart[]; extern u8 _ovl_En_ZogSegmentEnd[]; extern u8 _ovl_En_ZogSegmentRomStart[]; extern u8 _ovl_En_ZogSegmentRomEnd[];
extern u8 _ovl_Obj_RotliftSegmentStart[]; extern u8 _ovl_Obj_RotliftSegmentEnd[]; extern u8 _ovl_Obj_RotliftSegmentRomStart[]; extern u8 _ovl_Obj_RotliftSegmentRomEnd[];
extern u8 _ovl_Obj_Jg_GakkiSegmentStart[]; extern u8 _ovl_Obj_Jg_GakkiSegmentEnd[]; extern u8 _ovl_Obj_Jg_GakkiSegmentRomStart[]; extern u8 _ovl_Obj_Jg_GakkiSegmentRomEnd[];
extern u8 _ovl_Bg_Inibs_MovebgSegmentStart[]; extern u8 _ovl_Bg_Inibs_MovebgSegmentEnd[]; extern u8 _ovl_Bg_Inibs_MovebgSegmentRomStart[]; extern u8 _ovl_Bg_Inibs_MovebgSegmentRomEnd[];
extern u8 _ovl_En_ZotSegmentStart[]; extern u8 _ovl_En_ZotSegmentEnd[]; extern u8 _ovl_En_ZotSegmentRomStart[]; extern u8 _ovl_En_ZotSegmentRomEnd[];
extern u8 _ovl_Obj_TreeSegmentStart[]; extern u8 _ovl_Obj_TreeSegmentEnd[]; extern u8 _ovl_Obj_TreeSegmentRomStart[]; extern u8 _ovl_Obj_TreeSegmentRomEnd[];
extern u8 _ovl_Obj_Y2liftSegmentStart[]; extern u8 _ovl_Obj_Y2liftSegmentEnd[]; extern u8 _ovl_Obj_Y2liftSegmentRomStart[]; extern u8 _ovl_Obj_Y2liftSegmentRomEnd[];
extern u8 _ovl_Obj_Y2shutterSegmentStart[]; extern u8 _ovl_Obj_Y2shutterSegmentEnd[]; extern u8 _ovl_Obj_Y2shutterSegmentRomStart[]; extern u8 _ovl_Obj_Y2shutterSegmentRomEnd[];
extern u8 _ovl_Obj_BoatSegmentStart[]; extern u8 _ovl_Obj_BoatSegmentEnd[]; extern u8 _ovl_Obj_BoatSegmentRomStart[]; extern u8 _ovl_Obj_BoatSegmentRomEnd[];
extern u8 _ovl_Obj_TaruSegmentStart[]; extern u8 _ovl_Obj_TaruSegmentEnd[]; extern u8 _ovl_Obj_TaruSegmentRomStart[]; extern u8 _ovl_Obj_TaruSegmentRomEnd[];
extern u8 _ovl_Obj_HunsuiSegmentStart[]; extern u8 _ovl_Obj_HunsuiSegmentEnd[]; extern u8 _ovl_Obj_HunsuiSegmentRomStart[]; extern u8 _ovl_Obj_HunsuiSegmentRomEnd[];
extern u8 _ovl_En_Jc_MatoSegmentStart[]; extern u8 _ovl_En_Jc_MatoSegmentEnd[]; extern u8 _ovl_En_Jc_MatoSegmentRomStart[]; extern u8 _ovl_En_Jc_MatoSegmentRomEnd[];
extern u8 _ovl_Mir_Ray3SegmentStart[]; extern u8 _ovl_Mir_Ray3SegmentEnd[]; extern u8 _ovl_Mir_Ray3SegmentRomStart[]; extern u8 _ovl_Mir_Ray3SegmentRomEnd[];
extern u8 _ovl_En_ZobSegmentStart[]; extern u8 _ovl_En_ZobSegmentEnd[]; extern u8 _ovl_En_ZobSegmentRomStart[]; extern u8 _ovl_En_ZobSegmentRomEnd[];
extern u8 _ovl_Elf_Msg6SegmentStart[]; extern u8 _ovl_Elf_Msg6SegmentEnd[]; extern u8 _ovl_Elf_Msg6SegmentRomStart[]; extern u8 _ovl_Elf_Msg6SegmentRomEnd[];
extern u8 _ovl_Obj_NozokiSegmentStart[]; extern u8 _ovl_Obj_NozokiSegmentEnd[]; extern u8 _ovl_Obj_NozokiSegmentRomStart[]; extern u8 _ovl_Obj_NozokiSegmentRomEnd[];
extern u8 _ovl_En_TotoSegmentStart[]; extern u8 _ovl_En_TotoSegmentEnd[]; extern u8 _ovl_En_TotoSegmentRomStart[]; extern u8 _ovl_En_TotoSegmentRomEnd[];
extern u8 _ovl_En_RailgibudSegmentStart[]; extern u8 _ovl_En_RailgibudSegmentEnd[]; extern u8 _ovl_En_RailgibudSegmentRomStart[]; extern u8 _ovl_En_RailgibudSegmentRomEnd[];
extern u8 _ovl_En_BabaSegmentStart[]; extern u8 _ovl_En_BabaSegmentEnd[]; extern u8 _ovl_En_BabaSegmentRomStart[]; extern u8 _ovl_En_BabaSegmentRomEnd[];
extern u8 _ovl_En_SuttariSegmentStart[]; extern u8 _ovl_En_SuttariSegmentEnd[]; extern u8 _ovl_En_SuttariSegmentRomStart[]; extern u8 _ovl_En_SuttariSegmentRomEnd[];
extern u8 _ovl_En_ZodSegmentStart[]; extern u8 _ovl_En_ZodSegmentEnd[]; extern u8 _ovl_En_ZodSegmentRomStart[]; extern u8 _ovl_En_ZodSegmentRomEnd[];
extern u8 _ovl_En_KujiyaSegmentStart[]; extern u8 _ovl_En_KujiyaSegmentEnd[]; extern u8 _ovl_En_KujiyaSegmentRomStart[]; extern u8 _ovl_En_KujiyaSegmentRomEnd[];
extern u8 _ovl_En_GegSegmentStart[]; extern u8 _ovl_En_GegSegmentEnd[]; extern u8 _ovl_En_GegSegmentRomStart[]; extern u8 _ovl_En_GegSegmentRomEnd[];
extern u8 _ovl_Obj_KinokoSegmentStart[]; extern u8 _ovl_Obj_KinokoSegmentEnd[]; extern u8 _ovl_Obj_KinokoSegmentRomStart[]; extern u8 _ovl_Obj_KinokoSegmentRomEnd[];
extern u8 _ovl_Obj_YasiSegmentStart[]; extern u8 _ovl_Obj_YasiSegmentEnd[]; extern u8 _ovl_Obj_YasiSegmentRomStart[]; extern u8 _ovl_Obj_YasiSegmentRomEnd[];
extern u8 _ovl_En_Tanron1SegmentStart[]; extern u8 _ovl_En_Tanron1SegmentEnd[]; extern u8 _ovl_En_Tanron1SegmentRomStart[]; extern u8 _ovl_En_Tanron1SegmentRomEnd[];
extern u8 _ovl_En_Tanron2SegmentStart[]; extern u8 _ovl_En_Tanron2SegmentEnd[]; extern u8 _ovl_En_Tanron2SegmentRomStart[]; extern u8 _ovl_En_Tanron2SegmentRomEnd[];
extern u8 _ovl_En_Tanron3SegmentStart[]; extern u8 _ovl_En_Tanron3SegmentEnd[]; extern u8 _ovl_En_Tanron3SegmentRomStart[]; extern u8 _ovl_En_Tanron3SegmentRomEnd[];
extern u8 _ovl_Obj_ChanSegmentStart[]; extern u8 _ovl_Obj_ChanSegmentEnd[]; extern u8 _ovl_Obj_ChanSegmentRomStart[]; extern u8 _ovl_Obj_ChanSegmentRomEnd[];
extern u8 _ovl_En_ZosSegmentStart[]; extern u8 _ovl_En_ZosSegmentEnd[]; extern u8 _ovl_En_ZosSegmentRomStart[]; extern u8 _ovl_En_ZosSegmentRomEnd[];
extern u8 _ovl_En_S_GoroSegmentStart[]; extern u8 _ovl_En_S_GoroSegmentEnd[]; extern u8 _ovl_En_S_GoroSegmentRomStart[]; extern u8 _ovl_En_S_GoroSegmentRomEnd[];
extern u8 _ovl_En_NbSegmentStart[]; extern u8 _ovl_En_NbSegmentEnd[]; extern u8 _ovl_En_NbSegmentRomStart[]; extern u8 _ovl_En_NbSegmentRomEnd[];
extern u8 _ovl_En_JaSegmentStart[]; extern u8 _ovl_En_JaSegmentEnd[]; extern u8 _ovl_En_JaSegmentRomStart[]; extern u8 _ovl_En_JaSegmentRomEnd[];
extern u8 _ovl_Bg_F40_BlockSegmentStart[]; extern u8 _ovl_Bg_F40_BlockSegmentEnd[]; extern u8 _ovl_Bg_F40_BlockSegmentRomStart[]; extern u8 _ovl_Bg_F40_BlockSegmentRomEnd[];
extern u8 _ovl_Bg_F40_SwitchSegmentStart[]; extern u8 _ovl_Bg_F40_SwitchSegmentEnd[]; extern u8 _ovl_Bg_F40_SwitchSegmentRomStart[]; extern u8 _ovl_Bg_F40_SwitchSegmentRomEnd[];
extern u8 _ovl_En_Po_ComposerSegmentStart[]; extern u8 _ovl_En_Po_ComposerSegmentEnd[]; extern u8 _ovl_En_Po_ComposerSegmentRomStart[]; extern u8 _ovl_En_Po_ComposerSegmentRomEnd[];
extern u8 _ovl_En_GuruguruSegmentStart[]; extern u8 _ovl_En_GuruguruSegmentEnd[]; extern u8 _ovl_En_GuruguruSegmentRomStart[]; extern u8 _ovl_En_GuruguruSegmentRomEnd[];
extern u8 _ovl_Oceff_Wipe5SegmentStart[]; extern u8 _ovl_Oceff_Wipe5SegmentEnd[]; extern u8 _ovl_Oceff_Wipe5SegmentRomStart[]; extern u8 _ovl_Oceff_Wipe5SegmentRomEnd[];
extern u8 _ovl_En_Stone_heishiSegmentStart[]; extern u8 _ovl_En_Stone_heishiSegmentEnd[]; extern u8 _ovl_En_Stone_heishiSegmentRomStart[]; extern u8 _ovl_En_Stone_heishiSegmentRomEnd[];
extern u8 _ovl_Oceff_Wipe6SegmentStart[]; extern u8 _ovl_Oceff_Wipe6SegmentEnd[]; extern u8 _ovl_Oceff_Wipe6SegmentRomStart[]; extern u8 _ovl_Oceff_Wipe6SegmentRomEnd[];
extern u8 _ovl_En_ScopenutsSegmentStart[]; extern u8 _ovl_En_ScopenutsSegmentEnd[]; extern u8 _ovl_En_ScopenutsSegmentRomStart[]; extern u8 _ovl_En_ScopenutsSegmentRomEnd[];
extern u8 _ovl_En_ScopecrowSegmentStart[]; extern u8 _ovl_En_ScopecrowSegmentEnd[]; extern u8 _ovl_En_ScopecrowSegmentRomStart[]; extern u8 _ovl_En_ScopecrowSegmentRomEnd[];
extern u8 _ovl_Oceff_Wipe7SegmentStart[]; extern u8 _ovl_Oceff_Wipe7SegmentEnd[]; extern u8 _ovl_Oceff_Wipe7SegmentRomStart[]; extern u8 _ovl_Oceff_Wipe7SegmentRomEnd[];
extern u8 _ovl_Eff_Kamejima_WaveSegmentStart[]; extern u8 _ovl_Eff_Kamejima_WaveSegmentEnd[]; extern u8 _ovl_Eff_Kamejima_WaveSegmentRomStart[]; extern u8 _ovl_Eff_Kamejima_WaveSegmentRomEnd[];
extern u8 _ovl_En_HgSegmentStart[]; extern u8 _ovl_En_HgSegmentEnd[]; extern u8 _ovl_En_HgSegmentRomStart[]; extern u8 _ovl_En_HgSegmentRomEnd[];
extern u8 _ovl_En_HgoSegmentStart[]; extern u8 _ovl_En_HgoSegmentEnd[]; extern u8 _ovl_En_HgoSegmentRomStart[]; extern u8 _ovl_En_HgoSegmentRomEnd[];
extern u8 _ovl_En_ZovSegmentStart[]; extern u8 _ovl_En_ZovSegmentEnd[]; extern u8 _ovl_En_ZovSegmentRomStart[]; extern u8 _ovl_En_ZovSegmentRomEnd[];
extern u8 _ovl_En_AhSegmentStart[]; extern u8 _ovl_En_AhSegmentEnd[]; extern u8 _ovl_En_AhSegmentRomStart[]; extern u8 _ovl_En_AhSegmentRomEnd[];
extern u8 _ovl_Obj_HgdoorSegmentStart[]; extern u8 _ovl_Obj_HgdoorSegmentEnd[]; extern u8 _ovl_Obj_HgdoorSegmentRomStart[]; extern u8 _ovl_Obj_HgdoorSegmentRomEnd[];
extern u8 _ovl_Bg_Ikana_BombwallSegmentStart[]; extern u8 _ovl_Bg_Ikana_BombwallSegmentEnd[]; extern u8 _ovl_Bg_Ikana_BombwallSegmentRomStart[]; extern u8 _ovl_Bg_Ikana_BombwallSegmentRomEnd[];
extern u8 _ovl_Bg_Ikana_RaySegmentStart[]; extern u8 _ovl_Bg_Ikana_RaySegmentEnd[]; extern u8 _ovl_Bg_Ikana_RaySegmentRomStart[]; extern u8 _ovl_Bg_Ikana_RaySegmentRomEnd[];
extern u8 _ovl_Bg_Ikana_ShutterSegmentStart[]; extern u8 _ovl_Bg_Ikana_ShutterSegmentEnd[]; extern u8 _ovl_Bg_Ikana_ShutterSegmentRomStart[]; extern u8 _ovl_Bg_Ikana_ShutterSegmentRomEnd[];
extern u8 _ovl_Bg_Haka_BombwallSegmentStart[]; extern u8 _ovl_Bg_Haka_BombwallSegmentEnd[]; extern u8 _ovl_Bg_Haka_BombwallSegmentRomStart[]; extern u8 _ovl_Bg_Haka_BombwallSegmentRomEnd[];
extern u8 _ovl_Bg_Haka_TombSegmentStart[]; extern u8 _ovl_Bg_Haka_TombSegmentEnd[]; extern u8 _ovl_Bg_Haka_TombSegmentRomStart[]; extern u8 _ovl_Bg_Haka_TombSegmentRomEnd[];
extern u8 _ovl_En_Sc_RuppeSegmentStart[]; extern u8 _ovl_En_Sc_RuppeSegmentEnd[]; extern u8 _ovl_En_Sc_RuppeSegmentRomStart[]; extern u8 _ovl_En_Sc_RuppeSegmentRomEnd[];
extern u8 _ovl_Bg_Iknv_DoukutuSegmentStart[]; extern u8 _ovl_Bg_Iknv_DoukutuSegmentEnd[]; extern u8 _ovl_Bg_Iknv_DoukutuSegmentRomStart[]; extern u8 _ovl_Bg_Iknv_DoukutuSegmentRomEnd[];
extern u8 _ovl_Bg_Iknv_ObjSegmentStart[]; extern u8 _ovl_Bg_Iknv_ObjSegmentEnd[]; extern u8 _ovl_Bg_Iknv_ObjSegmentRomStart[]; extern u8 _ovl_Bg_Iknv_ObjSegmentRomEnd[];
extern u8 _ovl_En_PameraSegmentStart[]; extern u8 _ovl_En_PameraSegmentEnd[]; extern u8 _ovl_En_PameraSegmentRomStart[]; extern u8 _ovl_En_PameraSegmentRomEnd[];
extern u8 _ovl_Obj_HsStumpSegmentStart[]; extern u8 _ovl_Obj_HsStumpSegmentEnd[]; extern u8 _ovl_Obj_HsStumpSegmentRomStart[]; extern u8 _ovl_Obj_HsStumpSegmentRomEnd[];
extern u8 _ovl_En_Hidden_NutsSegmentStart[]; extern u8 _ovl_En_Hidden_NutsSegmentEnd[]; extern u8 _ovl_En_Hidden_NutsSegmentRomStart[]; extern u8 _ovl_En_Hidden_NutsSegmentRomEnd[];
extern u8 _ovl_En_ZowSegmentStart[]; extern u8 _ovl_En_ZowSegmentEnd[]; extern u8 _ovl_En_ZowSegmentRomStart[]; extern u8 _ovl_En_ZowSegmentRomEnd[];
extern u8 _ovl_En_TalkSegmentStart[]; extern u8 _ovl_En_TalkSegmentEnd[]; extern u8 _ovl_En_TalkSegmentRomStart[]; extern u8 _ovl_En_TalkSegmentRomEnd[];
extern u8 _ovl_En_AlSegmentStart[]; extern u8 _ovl_En_AlSegmentEnd[]; extern u8 _ovl_En_AlSegmentRomStart[]; extern u8 _ovl_En_AlSegmentRomEnd[];
extern u8 _ovl_En_TabSegmentStart[]; extern u8 _ovl_En_TabSegmentEnd[]; extern u8 _ovl_En_TabSegmentRomStart[]; extern u8 _ovl_En_TabSegmentRomEnd[];
extern u8 _ovl_En_NimotsuSegmentStart[]; extern u8 _ovl_En_NimotsuSegmentEnd[]; extern u8 _ovl_En_NimotsuSegmentRomStart[]; extern u8 _ovl_En_NimotsuSegmentRomEnd[];
extern u8 _ovl_En_Hit_TagSegmentStart[]; extern u8 _ovl_En_Hit_TagSegmentEnd[]; extern u8 _ovl_En_Hit_TagSegmentRomStart[]; extern u8 _ovl_En_Hit_TagSegmentRomEnd[];
extern u8 _ovl_En_RuppecrowSegmentStart[]; extern u8 _ovl_En_RuppecrowSegmentEnd[]; extern u8 _ovl_En_RuppecrowSegmentRomStart[]; extern u8 _ovl_En_RuppecrowSegmentRomEnd[];
extern u8 _ovl_En_Tanron4SegmentStart[]; extern u8 _ovl_En_Tanron4SegmentEnd[]; extern u8 _ovl_En_Tanron4SegmentRomStart[]; extern u8 _ovl_En_Tanron4SegmentRomEnd[];
extern u8 _ovl_En_Tanron5SegmentStart[]; extern u8 _ovl_En_Tanron5SegmentEnd[]; extern u8 _ovl_En_Tanron5SegmentRomStart[]; extern u8 _ovl_En_Tanron5SegmentRomEnd[];
extern u8 _ovl_En_Tanron6SegmentStart[]; extern u8 _ovl_En_Tanron6SegmentEnd[]; extern u8 _ovl_En_Tanron6SegmentRomStart[]; extern u8 _ovl_En_Tanron6SegmentRomEnd[];
extern u8 _ovl_En_Daiku2SegmentStart[]; extern u8 _ovl_En_Daiku2SegmentEnd[]; extern u8 _ovl_En_Daiku2SegmentRomStart[]; extern u8 _ovl_En_Daiku2SegmentRomEnd[];
extern u8 _ovl_En_MutoSegmentStart[]; extern u8 _ovl_En_MutoSegmentEnd[]; extern u8 _ovl_En_MutoSegmentRomStart[]; extern u8 _ovl_En_MutoSegmentRomEnd[];
extern u8 _ovl_En_BaisenSegmentStart[]; extern u8 _ovl_En_BaisenSegmentEnd[]; extern u8 _ovl_En_BaisenSegmentRomStart[]; extern u8 _ovl_En_BaisenSegmentRomEnd[];
extern u8 _ovl_En_HeishiSegmentStart[]; extern u8 _ovl_En_HeishiSegmentEnd[]; extern u8 _ovl_En_HeishiSegmentRomStart[]; extern u8 _ovl_En_HeishiSegmentRomEnd[];
extern u8 _ovl_En_Demo_heishiSegmentStart[]; extern u8 _ovl_En_Demo_heishiSegmentEnd[]; extern u8 _ovl_En_Demo_heishiSegmentRomStart[]; extern u8 _ovl_En_Demo_heishiSegmentRomEnd[];
extern u8 _ovl_En_DtSegmentStart[]; extern u8 _ovl_En_DtSegmentEnd[]; extern u8 _ovl_En_DtSegmentRomStart[]; extern u8 _ovl_En_DtSegmentRomEnd[];
extern u8 _ovl_En_ChaSegmentStart[]; extern u8 _ovl_En_ChaSegmentEnd[]; extern u8 _ovl_En_ChaSegmentRomStart[]; extern u8 _ovl_En_ChaSegmentRomEnd[];
extern u8 _ovl_Obj_DinnerSegmentStart[]; extern u8 _ovl_Obj_DinnerSegmentEnd[]; extern u8 _ovl_Obj_DinnerSegmentRomStart[]; extern u8 _ovl_Obj_DinnerSegmentRomEnd[];
extern u8 _ovl_Eff_LastdaySegmentStart[]; extern u8 _ovl_Eff_LastdaySegmentEnd[]; extern u8 _ovl_Eff_LastdaySegmentRomStart[]; extern u8 _ovl_Eff_LastdaySegmentRomEnd[];
extern u8 _ovl_Bg_Ikana_DharmaSegmentStart[]; extern u8 _ovl_Bg_Ikana_DharmaSegmentEnd[]; extern u8 _ovl_Bg_Ikana_DharmaSegmentRomStart[]; extern u8 _ovl_Bg_Ikana_DharmaSegmentRomEnd[];
extern u8 _ovl_En_AkindonutsSegmentStart[]; extern u8 _ovl_En_AkindonutsSegmentEnd[]; extern u8 _ovl_En_AkindonutsSegmentRomStart[]; extern u8 _ovl_En_AkindonutsSegmentRomEnd[];
extern u8 _ovl_Eff_StkSegmentStart[]; extern u8 _ovl_Eff_StkSegmentEnd[]; extern u8 _ovl_Eff_StkSegmentRomStart[]; extern u8 _ovl_Eff_StkSegmentRomEnd[];
extern u8 _ovl_En_IgSegmentStart[]; extern u8 _ovl_En_IgSegmentEnd[]; extern u8 _ovl_En_IgSegmentRomStart[]; extern u8 _ovl_En_IgSegmentRomEnd[];
extern u8 _ovl_En_RgSegmentStart[]; extern u8 _ovl_En_RgSegmentEnd[]; extern u8 _ovl_En_RgSegmentRomStart[]; extern u8 _ovl_En_RgSegmentRomEnd[];
extern u8 _ovl_En_OskSegmentStart[]; extern u8 _ovl_En_OskSegmentEnd[]; extern u8 _ovl_En_OskSegmentRomStart[]; extern u8 _ovl_En_OskSegmentRomEnd[];
extern u8 _ovl_En_Sth2SegmentStart[]; extern u8 _ovl_En_Sth2SegmentEnd[]; extern u8 _ovl_En_Sth2SegmentRomStart[]; extern u8 _ovl_En_Sth2SegmentRomEnd[];
extern u8 _ovl_En_YbSegmentStart[]; extern u8 _ovl_En_YbSegmentEnd[]; extern u8 _ovl_En_YbSegmentRomStart[]; extern u8 _ovl_En_YbSegmentRomEnd[];
extern u8 _ovl_En_RzSegmentStart[]; extern u8 _ovl_En_RzSegmentEnd[]; extern u8 _ovl_En_RzSegmentRomStart[]; extern u8 _ovl_En_RzSegmentRomEnd[];
extern u8 _ovl_En_ScopecoinSegmentStart[]; extern u8 _ovl_En_ScopecoinSegmentEnd[]; extern u8 _ovl_En_ScopecoinSegmentRomStart[]; extern u8 _ovl_En_ScopecoinSegmentRomEnd[];
extern u8 _ovl_En_BjtSegmentStart[]; extern u8 _ovl_En_BjtSegmentEnd[]; extern u8 _ovl_En_BjtSegmentRomStart[]; extern u8 _ovl_En_BjtSegmentRomEnd[];
extern u8 _ovl_En_BomjimaSegmentStart[]; extern u8 _ovl_En_BomjimaSegmentEnd[]; extern u8 _ovl_En_BomjimaSegmentRomStart[]; extern u8 _ovl_En_BomjimaSegmentRomEnd[];
extern u8 _ovl_En_BomjimbSegmentStart[]; extern u8 _ovl_En_BomjimbSegmentEnd[]; extern u8 _ovl_En_BomjimbSegmentRomStart[]; extern u8 _ovl_En_BomjimbSegmentRomEnd[];
extern u8 _ovl_En_BombersSegmentStart[]; extern u8 _ovl_En_BombersSegmentEnd[]; extern u8 _ovl_En_BombersSegmentRomStart[]; extern u8 _ovl_En_BombersSegmentRomEnd[];
extern u8 _ovl_En_Bombers2SegmentStart[]; extern u8 _ovl_En_Bombers2SegmentEnd[]; extern u8 _ovl_En_Bombers2SegmentRomStart[]; extern u8 _ovl_En_Bombers2SegmentRomEnd[];
extern u8 _ovl_En_BombalSegmentStart[]; extern u8 _ovl_En_BombalSegmentEnd[]; extern u8 _ovl_En_BombalSegmentRomStart[]; extern u8 _ovl_En_BombalSegmentRomEnd[];
extern u8 _ovl_Obj_Moon_StoneSegmentStart[]; extern u8 _ovl_Obj_Moon_StoneSegmentEnd[]; extern u8 _ovl_Obj_Moon_StoneSegmentRomStart[]; extern u8 _ovl_Obj_Moon_StoneSegmentRomEnd[];
extern u8 _ovl_Obj_Mu_PictSegmentStart[]; extern u8 _ovl_Obj_Mu_PictSegmentEnd[]; extern u8 _ovl_Obj_Mu_PictSegmentRomStart[]; extern u8 _ovl_Obj_Mu_PictSegmentRomEnd[];
extern u8 _ovl_Bg_IkninsideSegmentStart[]; extern u8 _ovl_Bg_IkninsideSegmentEnd[]; extern u8 _ovl_Bg_IkninsideSegmentRomStart[]; extern u8 _ovl_Bg_IkninsideSegmentRomEnd[];
extern u8 _ovl_Eff_ZorabandSegmentStart[]; extern u8 _ovl_Eff_ZorabandSegmentEnd[]; extern u8 _ovl_Eff_ZorabandSegmentRomStart[]; extern u8 _ovl_Eff_ZorabandSegmentRomEnd[];
extern u8 _ovl_Obj_Kepn_KoyaSegmentStart[]; extern u8 _ovl_Obj_Kepn_KoyaSegmentEnd[]; extern u8 _ovl_Obj_Kepn_KoyaSegmentRomStart[]; extern u8 _ovl_Obj_Kepn_KoyaSegmentRomEnd[];
extern u8 _ovl_Obj_UsiyaneSegmentStart[]; extern u8 _ovl_Obj_UsiyaneSegmentEnd[]; extern u8 _ovl_Obj_UsiyaneSegmentRomStart[]; extern u8 _ovl_Obj_UsiyaneSegmentRomEnd[];
extern u8 _ovl_En_NnhSegmentStart[]; extern u8 _ovl_En_NnhSegmentEnd[]; extern u8 _ovl_En_NnhSegmentRomStart[]; extern u8 _ovl_En_NnhSegmentRomEnd[];
extern u8 _ovl_Obj_KzsakuSegmentStart[]; extern u8 _ovl_Obj_KzsakuSegmentEnd[]; extern u8 _ovl_Obj_KzsakuSegmentRomStart[]; extern u8 _ovl_Obj_KzsakuSegmentRomEnd[];
extern u8 _ovl_Obj_Milk_BinSegmentStart[]; extern u8 _ovl_Obj_Milk_BinSegmentEnd[]; extern u8 _ovl_Obj_Milk_BinSegmentRomStart[]; extern u8 _ovl_Obj_Milk_BinSegmentRomEnd[];
extern u8 _ovl_En_KitanSegmentStart[]; extern u8 _ovl_En_KitanSegmentEnd[]; extern u8 _ovl_En_KitanSegmentRomStart[]; extern u8 _ovl_En_KitanSegmentRomEnd[];
extern u8 _ovl_Bg_Astr_BombwallSegmentStart[]; extern u8 _ovl_Bg_Astr_BombwallSegmentEnd[]; extern u8 _ovl_Bg_Astr_BombwallSegmentRomStart[]; extern u8 _ovl_Bg_Astr_BombwallSegmentRomEnd[];
extern u8 _ovl_Bg_Iknin_SusceilSegmentStart[]; extern u8 _ovl_Bg_Iknin_SusceilSegmentEnd[]; extern u8 _ovl_Bg_Iknin_SusceilSegmentRomStart[]; extern u8 _ovl_Bg_Iknin_SusceilSegmentRomEnd[];
extern u8 _ovl_En_BsbSegmentStart[]; extern u8 _ovl_En_BsbSegmentEnd[]; extern u8 _ovl_En_BsbSegmentRomStart[]; extern u8 _ovl_En_BsbSegmentRomEnd[];
extern u8 _ovl_En_RecepgirlSegmentStart[]; extern u8 _ovl_En_RecepgirlSegmentEnd[]; extern u8 _ovl_En_RecepgirlSegmentRomStart[]; extern u8 _ovl_En_RecepgirlSegmentRomEnd[];
extern u8 _ovl_En_ThiefbirdSegmentStart[]; extern u8 _ovl_En_ThiefbirdSegmentEnd[]; extern u8 _ovl_En_ThiefbirdSegmentRomStart[]; extern u8 _ovl_En_ThiefbirdSegmentRomEnd[];
extern u8 _ovl_En_Jgame_TsnSegmentStart[]; extern u8 _ovl_En_Jgame_TsnSegmentEnd[]; extern u8 _ovl_En_Jgame_TsnSegmentRomStart[]; extern u8 _ovl_En_Jgame_TsnSegmentRomEnd[];
extern u8 _ovl_Obj_Jgame_LightSegmentStart[]; extern u8 _ovl_Obj_Jgame_LightSegmentEnd[]; extern u8 _ovl_Obj_Jgame_LightSegmentRomStart[]; extern u8 _ovl_Obj_Jgame_LightSegmentRomEnd[];
extern u8 _ovl_Obj_YadoSegmentStart[]; extern u8 _ovl_Obj_YadoSegmentEnd[]; extern u8 _ovl_Obj_YadoSegmentRomStart[]; extern u8 _ovl_Obj_YadoSegmentRomEnd[];
extern u8 _ovl_Demo_SyotenSegmentStart[]; extern u8 _ovl_Demo_SyotenSegmentEnd[]; extern u8 _ovl_Demo_SyotenSegmentRomStart[]; extern u8 _ovl_Demo_SyotenSegmentRomEnd[];
extern u8 _ovl_Demo_MoonendSegmentStart[]; extern u8 _ovl_Demo_MoonendSegmentEnd[]; extern u8 _ovl_Demo_MoonendSegmentRomStart[]; extern u8 _ovl_Demo_MoonendSegmentRomEnd[];
extern u8 _ovl_Bg_LbfshotSegmentStart[]; extern u8 _ovl_Bg_LbfshotSegmentEnd[]; extern u8 _ovl_Bg_LbfshotSegmentRomStart[]; extern u8 _ovl_Bg_LbfshotSegmentRomEnd[];
extern u8 _ovl_Bg_Last_BwallSegmentStart[]; extern u8 _ovl_Bg_Last_BwallSegmentEnd[]; extern u8 _ovl_Bg_Last_BwallSegmentRomStart[]; extern u8 _ovl_Bg_Last_BwallSegmentRomEnd[];
extern u8 _ovl_En_AndSegmentStart[]; extern u8 _ovl_En_AndSegmentEnd[]; extern u8 _ovl_En_AndSegmentRomStart[]; extern u8 _ovl_En_AndSegmentRomEnd[];
extern u8 _ovl_En_Invadepoh_DemoSegmentStart[]; extern u8 _ovl_En_Invadepoh_DemoSegmentEnd[]; extern u8 _ovl_En_Invadepoh_DemoSegmentRomStart[]; extern u8 _ovl_En_Invadepoh_DemoSegmentRomEnd[];
extern u8 _ovl_Obj_DanpeiliftSegmentStart[]; extern u8 _ovl_Obj_DanpeiliftSegmentEnd[]; extern u8 _ovl_Obj_DanpeiliftSegmentRomStart[]; extern u8 _ovl_Obj_DanpeiliftSegmentRomEnd[];
extern u8 _ovl_En_Fall2SegmentStart[]; extern u8 _ovl_En_Fall2SegmentEnd[]; extern u8 _ovl_En_Fall2SegmentRomStart[]; extern u8 _ovl_En_Fall2SegmentRomEnd[];
extern u8 _ovl_Dm_AlSegmentStart[]; extern u8 _ovl_Dm_AlSegmentEnd[]; extern u8 _ovl_Dm_AlSegmentRomStart[]; extern u8 _ovl_Dm_AlSegmentRomEnd[];
extern u8 _ovl_Dm_AnSegmentStart[]; extern u8 _ovl_Dm_AnSegmentEnd[]; extern u8 _ovl_Dm_AnSegmentRomStart[]; extern u8 _ovl_Dm_AnSegmentRomEnd[];
extern u8 _ovl_Dm_AhSegmentStart[]; extern u8 _ovl_Dm_AhSegmentEnd[]; extern u8 _ovl_Dm_AhSegmentRomStart[]; extern u8 _ovl_Dm_AhSegmentRomEnd[];
extern u8 _ovl_Dm_NbSegmentStart[]; extern u8 _ovl_Dm_NbSegmentEnd[]; extern u8 _ovl_Dm_NbSegmentRomStart[]; extern u8 _ovl_Dm_NbSegmentRomEnd[];
extern u8 _ovl_En_DrsSegmentStart[]; extern u8 _ovl_En_DrsSegmentEnd[]; extern u8 _ovl_En_DrsSegmentRomStart[]; extern u8 _ovl_En_DrsSegmentRomEnd[];
extern u8 _ovl_En_Ending_HeroSegmentStart[]; extern u8 _ovl_En_Ending_HeroSegmentEnd[]; extern u8 _ovl_En_Ending_HeroSegmentRomStart[]; extern u8 _ovl_En_Ending_HeroSegmentRomEnd[];
extern u8 _ovl_Dm_BalSegmentStart[]; extern u8 _ovl_Dm_BalSegmentEnd[]; extern u8 _ovl_Dm_BalSegmentRomStart[]; extern u8 _ovl_Dm_BalSegmentRomEnd[];
extern u8 _ovl_En_PaperSegmentStart[]; extern u8 _ovl_En_PaperSegmentEnd[]; extern u8 _ovl_En_PaperSegmentRomStart[]; extern u8 _ovl_En_PaperSegmentRomEnd[];
extern u8 _ovl_En_Hint_SkbSegmentStart[]; extern u8 _ovl_En_Hint_SkbSegmentEnd[]; extern u8 _ovl_En_Hint_SkbSegmentRomStart[]; extern u8 _ovl_En_Hint_SkbSegmentRomEnd[];
extern u8 _ovl_Dm_TagSegmentStart[]; extern u8 _ovl_Dm_TagSegmentEnd[]; extern u8 _ovl_Dm_TagSegmentRomStart[]; extern u8 _ovl_Dm_TagSegmentRomEnd[];
extern u8 _ovl_En_BhSegmentStart[]; extern u8 _ovl_En_BhSegmentEnd[]; extern u8 _ovl_En_BhSegmentRomStart[]; extern u8 _ovl_En_BhSegmentRomEnd[];
extern u8 _ovl_En_Ending_Hero2SegmentStart[]; extern u8 _ovl_En_Ending_Hero2SegmentEnd[]; extern u8 _ovl_En_Ending_Hero2SegmentRomStart[]; extern u8 _ovl_En_Ending_Hero2SegmentRomEnd[];
extern u8 _ovl_En_Ending_Hero3SegmentStart[]; extern u8 _ovl_En_Ending_Hero3SegmentEnd[]; extern u8 _ovl_En_Ending_Hero3SegmentRomStart[]; extern u8 _ovl_En_Ending_Hero3SegmentRomEnd[];
extern u8 _ovl_En_Ending_Hero4SegmentStart[]; extern u8 _ovl_En_Ending_Hero4SegmentEnd[]; extern u8 _ovl_En_Ending_Hero4SegmentRomStart[]; extern u8 _ovl_En_Ending_Hero4SegmentRomEnd[];
extern u8 _ovl_En_Ending_Hero5SegmentStart[]; extern u8 _ovl_En_Ending_Hero5SegmentEnd[]; extern u8 _ovl_En_Ending_Hero5SegmentRomStart[]; extern u8 _ovl_En_Ending_Hero5SegmentRomEnd[];
extern u8 _ovl_En_Ending_Hero6SegmentStart[]; extern u8 _ovl_En_Ending_Hero6SegmentEnd[]; extern u8 _ovl_En_Ending_Hero6SegmentRomStart[]; extern u8 _ovl_En_Ending_Hero6SegmentRomEnd[];
extern u8 _ovl_Dm_GmSegmentStart[]; extern u8 _ovl_Dm_GmSegmentEnd[]; extern u8 _ovl_Dm_GmSegmentRomStart[]; extern u8 _ovl_Dm_GmSegmentRomEnd[];
extern u8 _ovl_Obj_SwprizeSegmentStart[]; extern u8 _ovl_Obj_SwprizeSegmentEnd[]; extern u8 _ovl_Obj_SwprizeSegmentRomStart[]; extern u8 _ovl_Obj_SwprizeSegmentRomEnd[];
extern u8 _ovl_En_Invisible_RuppeSegmentStart[]; extern u8 _ovl_En_Invisible_RuppeSegmentEnd[]; extern u8 _ovl_En_Invisible_RuppeSegmentRomStart[]; extern u8 _ovl_En_Invisible_RuppeSegmentRomEnd[];
extern u8 _ovl_Obj_EndingSegmentStart[]; extern u8 _ovl_Obj_EndingSegmentEnd[]; extern u8 _ovl_Obj_EndingSegmentRomStart[]; extern u8 _ovl_Obj_EndingSegmentRomEnd[];
extern u8 _ovl_En_RsnSegmentStart[]; extern u8 _ovl_En_RsnSegmentEnd[]; extern u8 _ovl_En_RsnSegmentRomStart[]; extern u8 _ovl_En_RsnSegmentRomEnd[];
extern u8 _gameplay_keepSegmentRomStart[]; extern u8 _gameplay_keepSegmentRomEnd[];
extern u8 _gameplay_field_keepSegmentRomStart[]; extern u8 _gameplay_field_keepSegmentRomEnd[];
extern u8 _gameplay_dangeon_keepSegmentRomStart[]; extern u8 _gameplay_dangeon_keepSegmentRomEnd[];
extern u8 _object_link_boySegmentRomStart[]; extern u8 _object_link_boySegmentRomEnd[];
extern u8 _object_link_childSegmentRomStart[]; extern u8 _object_link_childSegmentRomEnd[];
extern u8 _object_link_goronSegmentRomStart[]; extern u8 _object_link_goronSegmentRomEnd[];
extern u8 _object_link_zoraSegmentRomStart[]; extern u8 _object_link_zoraSegmentRomEnd[];
extern u8 _object_link_nutsSegmentRomStart[]; extern u8 _object_link_nutsSegmentRomEnd[];
extern u8 _object_mask_ki_tanSegmentRomStart[]; extern u8 _object_mask_ki_tanSegmentRomEnd[];
extern u8 _object_mask_rabitSegmentRomStart[]; extern u8 _object_mask_rabitSegmentRomEnd[];
extern u8 _object_mask_skjSegmentRomStart[]; extern u8 _object_mask_skjSegmentRomEnd[];
extern u8 _object_mask_truthSegmentRomStart[]; extern u8 _object_mask_truthSegmentRomEnd[];
extern u8 _object_mask_gibudoSegmentRomStart[]; extern u8 _object_mask_gibudoSegmentRomEnd[];
extern u8 _object_mask_jsonSegmentRomStart[]; extern u8 _object_mask_jsonSegmentRomEnd[];
extern u8 _object_mask_kerfaySegmentRomStart[]; extern u8 _object_mask_kerfaySegmentRomEnd[];
extern u8 _object_mask_bigelfSegmentRomStart[]; extern u8 _object_mask_bigelfSegmentRomEnd[];
extern u8 _object_mask_kyojinSegmentRomStart[]; extern u8 _object_mask_kyojinSegmentRomEnd[];
extern u8 _object_mask_romernySegmentRomStart[]; extern u8 _object_mask_romernySegmentRomEnd[];
extern u8 _object_mask_posthatSegmentRomStart[]; extern u8 _object_mask_posthatSegmentRomEnd[];
extern u8 _object_mask_zachoSegmentRomStart[]; extern u8 _object_mask_zachoSegmentRomEnd[];
extern u8 _object_mask_stoneSegmentRomStart[]; extern u8 _object_mask_stoneSegmentRomEnd[];
extern u8 _object_mask_breeSegmentRomStart[]; extern u8 _object_mask_breeSegmentRomEnd[];
extern u8 _object_mask_geroSegmentRomStart[]; extern u8 _object_mask_geroSegmentRomEnd[];
extern u8 _object_mask_yofukasiSegmentRomStart[]; extern u8 _object_mask_yofukasiSegmentRomEnd[];
extern u8 _object_mask_meotoSegmentRomStart[]; extern u8 _object_mask_meotoSegmentRomEnd[];
extern u8 _object_mask_dancerSegmentRomStart[]; extern u8 _object_mask_dancerSegmentRomEnd[];
extern u8 _object_mask_bakuretuSegmentRomStart[]; extern u8 _object_mask_bakuretuSegmentRomEnd[];
extern u8 _object_mask_bu_sanSegmentRomStart[]; extern u8 _object_mask_bu_sanSegmentRomEnd[];
extern u8 _object_mask_goronSegmentRomStart[]; extern u8 _object_mask_goronSegmentRomEnd[];
extern u8 _object_mask_zoraSegmentRomStart[]; extern u8 _object_mask_zoraSegmentRomEnd[];
extern u8 _object_mask_nutsSegmentRomStart[]; extern u8 _object_mask_nutsSegmentRomEnd[];
extern u8 _object_mask_boySegmentRomStart[]; extern u8 _object_mask_boySegmentRomEnd[];
extern u8 _object_boxSegmentRomStart[]; extern u8 _object_boxSegmentRomEnd[];
extern u8 _object_okutaSegmentRomStart[]; extern u8 _object_okutaSegmentRomEnd[];
extern u8 _object_wallmasterSegmentRomStart[]; extern u8 _object_wallmasterSegmentRomEnd[];
extern u8 _object_dy_objSegmentRomStart[]; extern u8 _object_dy_objSegmentRomEnd[];
extern u8 _object_fireflySegmentRomStart[]; extern u8 _object_fireflySegmentRomEnd[];
extern u8 _object_dodongoSegmentRomStart[]; extern u8 _object_dodongoSegmentRomEnd[];
extern u8 _object_niwSegmentRomStart[]; extern u8 _object_niwSegmentRomEnd[];
extern u8 _object_titeSegmentRomStart[]; extern u8 _object_titeSegmentRomEnd[];
extern u8 _object_phSegmentRomStart[]; extern u8 _object_phSegmentRomEnd[];
extern u8 _object_dinofosSegmentRomStart[]; extern u8 _object_dinofosSegmentRomEnd[];
extern u8 _object_zl1SegmentRomStart[]; extern u8 _object_zl1SegmentRomEnd[];
extern u8 _object_bubbleSegmentRomStart[]; extern u8 _object_bubbleSegmentRomEnd[];
extern u8 _object_test3SegmentRomStart[]; extern u8 _object_test3SegmentRomEnd[];
extern u8 _object_famosSegmentRomStart[]; extern u8 _object_famosSegmentRomEnd[];
extern u8 _object_stSegmentRomStart[]; extern u8 _object_stSegmentRomEnd[];
extern u8 _object_thiefbirdSegmentRomStart[]; extern u8 _object_thiefbirdSegmentRomEnd[];
extern u8 _object_bombfSegmentRomStart[]; extern u8 _object_bombfSegmentRomEnd[];
extern u8 _object_amSegmentRomStart[]; extern u8 _object_amSegmentRomEnd[];
extern u8 _object_dekubabaSegmentRomStart[]; extern u8 _object_dekubabaSegmentRomEnd[];
extern u8 _object_warp1SegmentRomStart[]; extern u8 _object_warp1SegmentRomEnd[];
extern u8 _object_b_heartSegmentRomStart[]; extern u8 _object_b_heartSegmentRomEnd[];
extern u8 _object_dekunutsSegmentRomStart[]; extern u8 _object_dekunutsSegmentRomEnd[];
extern u8 _object_bbSegmentRomStart[]; extern u8 _object_bbSegmentRomEnd[];
extern u8 _object_deathSegmentRomStart[]; extern u8 _object_deathSegmentRomEnd[];
extern u8 _object_hataSegmentRomStart[]; extern u8 _object_hataSegmentRomEnd[];
extern u8 _object_wood02SegmentRomStart[]; extern u8 _object_wood02SegmentRomEnd[];
extern u8 _object_trapSegmentRomStart[]; extern u8 _object_trapSegmentRomEnd[];
extern u8 _object_vmSegmentRomStart[]; extern u8 _object_vmSegmentRomEnd[];
extern u8 _object_efc_star_fieldSegmentRomStart[]; extern u8 _object_efc_star_fieldSegmentRomEnd[];
extern u8 _object_rdSegmentRomStart[]; extern u8 _object_rdSegmentRomEnd[];
extern u8 _object_yukimura_objSegmentRomStart[]; extern u8 _object_yukimura_objSegmentRomEnd[];
extern u8 _object_horse_link_childSegmentRomStart[]; extern u8 _object_horse_link_childSegmentRomEnd[];
extern u8 _object_syokudaiSegmentRomStart[]; extern u8 _object_syokudaiSegmentRomEnd[];
extern u8 _object_efc_twSegmentRomStart[]; extern u8 _object_efc_twSegmentRomEnd[];
extern u8 _object_gi_keySegmentRomStart[]; extern u8 _object_gi_keySegmentRomEnd[];
extern u8 _object_mir_raySegmentRomStart[]; extern u8 _object_mir_raySegmentRomEnd[];
extern u8 _object_ctower_rotSegmentRomStart[]; extern u8 _object_ctower_rotSegmentRomEnd[];
extern u8 _object_bdoorSegmentRomStart[]; extern u8 _object_bdoorSegmentRomEnd[];
extern u8 _object_sbSegmentRomStart[]; extern u8 _object_sbSegmentRomEnd[];
extern u8 _object_gi_melodySegmentRomStart[]; extern u8 _object_gi_melodySegmentRomEnd[];
extern u8 _object_gi_heartSegmentRomStart[]; extern u8 _object_gi_heartSegmentRomEnd[];
extern u8 _object_gi_compassSegmentRomStart[]; extern u8 _object_gi_compassSegmentRomEnd[];
extern u8 _object_gi_bosskeySegmentRomStart[]; extern u8 _object_gi_bosskeySegmentRomEnd[];
extern u8 _object_gi_nutsSegmentRomStart[]; extern u8 _object_gi_nutsSegmentRomEnd[];
extern u8 _object_gi_heartsSegmentRomStart[]; extern u8 _object_gi_heartsSegmentRomEnd[];
extern u8 _object_gi_arrowcaseSegmentRomStart[]; extern u8 _object_gi_arrowcaseSegmentRomEnd[];
extern u8 _object_gi_bombpouchSegmentRomStart[]; extern u8 _object_gi_bombpouchSegmentRomEnd[];
extern u8 _object_inSegmentRomStart[]; extern u8 _object_inSegmentRomEnd[];
extern u8 _object_os_animeSegmentRomStart[]; extern u8 _object_os_animeSegmentRomEnd[];
extern u8 _object_gi_bottleSegmentRomStart[]; extern u8 _object_gi_bottleSegmentRomEnd[];
extern u8 _object_gi_stickSegmentRomStart[]; extern u8 _object_gi_stickSegmentRomEnd[];
extern u8 _object_gi_mapSegmentRomStart[]; extern u8 _object_gi_mapSegmentRomEnd[];
extern u8 _object_oF1d_mapSegmentRomStart[]; extern u8 _object_oF1d_mapSegmentRomEnd[];
extern u8 _object_ru2SegmentRomStart[]; extern u8 _object_ru2SegmentRomEnd[];
extern u8 _object_gi_magicpotSegmentRomStart[]; extern u8 _object_gi_magicpotSegmentRomEnd[];
extern u8 _object_gi_bomb_1SegmentRomStart[]; extern u8 _object_gi_bomb_1SegmentRomEnd[];
extern u8 _object_ma2SegmentRomStart[]; extern u8 _object_ma2SegmentRomEnd[];
extern u8 _object_gi_purseSegmentRomStart[]; extern u8 _object_gi_purseSegmentRomEnd[];
extern u8 _object_rrSegmentRomStart[]; extern u8 _object_rrSegmentRomEnd[];
extern u8 _object_gi_arrowSegmentRomStart[]; extern u8 _object_gi_arrowSegmentRomEnd[];
extern u8 _object_gi_bomb_2SegmentRomStart[]; extern u8 _object_gi_bomb_2SegmentRomEnd[];
extern u8 _object_gi_shield_2SegmentRomStart[]; extern u8 _object_gi_shield_2SegmentRomEnd[];
extern u8 _object_gi_hookshotSegmentRomStart[]; extern u8 _object_gi_hookshotSegmentRomEnd[];
extern u8 _object_gi_ocarinaSegmentRomStart[]; extern u8 _object_gi_ocarinaSegmentRomEnd[];
extern u8 _object_gi_milkSegmentRomStart[]; extern u8 _object_gi_milkSegmentRomEnd[];
extern u8 _object_ma1SegmentRomStart[]; extern u8 _object_ma1SegmentRomEnd[];
extern u8 _object_nySegmentRomStart[]; extern u8 _object_nySegmentRomEnd[];
extern u8 _object_frSegmentRomStart[]; extern u8 _object_frSegmentRomEnd[];
extern u8 _object_gi_bowSegmentRomStart[]; extern u8 _object_gi_bowSegmentRomEnd[];
extern u8 _object_gi_glassesSegmentRomStart[]; extern u8 _object_gi_glassesSegmentRomEnd[];
extern u8 _object_gi_liquidSegmentRomStart[]; extern u8 _object_gi_liquidSegmentRomEnd[];
extern u8 _object_aniSegmentRomStart[]; extern u8 _object_aniSegmentRomEnd[];
extern u8 _object_gi_shield_3SegmentRomStart[]; extern u8 _object_gi_shield_3SegmentRomEnd[];
extern u8 _object_gi_beanSegmentRomStart[]; extern u8 _object_gi_beanSegmentRomEnd[];
extern u8 _object_gi_fishSegmentRomStart[]; extern u8 _object_gi_fishSegmentRomEnd[];
extern u8 _object_gi_longswordSegmentRomStart[]; extern u8 _object_gi_longswordSegmentRomEnd[];
extern u8 _object_zoSegmentRomStart[]; extern u8 _object_zoSegmentRomEnd[];
extern u8 _object_umajumpSegmentRomStart[]; extern u8 _object_umajumpSegmentRomEnd[];
extern u8 _object_mastergolonSegmentRomStart[]; extern u8 _object_mastergolonSegmentRomEnd[];
extern u8 _object_masterzooraSegmentRomStart[]; extern u8 _object_masterzooraSegmentRomEnd[];
extern u8 _object_aobSegmentRomStart[]; extern u8 _object_aobSegmentRomEnd[];
extern u8 _object_ikSegmentRomStart[]; extern u8 _object_ikSegmentRomEnd[];
extern u8 _object_ahgSegmentRomStart[]; extern u8 _object_ahgSegmentRomEnd[];
extern u8 _object_cneSegmentRomStart[]; extern u8 _object_cneSegmentRomEnd[];
extern u8 _object_bjiSegmentRomStart[]; extern u8 _object_bjiSegmentRomEnd[];
extern u8 _object_bbaSegmentRomStart[]; extern u8 _object_bbaSegmentRomEnd[];
extern u8 _object_an1SegmentRomStart[]; extern u8 _object_an1SegmentRomEnd[];
extern u8 _object_bojSegmentRomStart[]; extern u8 _object_bojSegmentRomEnd[];
extern u8 _object_fzSegmentRomStart[]; extern u8 _object_fzSegmentRomEnd[];
extern u8 _object_bobSegmentRomStart[]; extern u8 _object_bobSegmentRomEnd[];
extern u8 _object_ge1SegmentRomStart[]; extern u8 _object_ge1SegmentRomEnd[];
extern u8 _object_yabusame_pointSegmentRomStart[]; extern u8 _object_yabusame_pointSegmentRomEnd[];
extern u8 _object_d_hsblockSegmentRomStart[]; extern u8 _object_d_hsblockSegmentRomEnd[];
extern u8 _object_d_liftSegmentRomStart[]; extern u8 _object_d_liftSegmentRomEnd[];
extern u8 _object_mamenokiSegmentRomStart[]; extern u8 _object_mamenokiSegmentRomEnd[];
extern u8 _object_goroiwaSegmentRomStart[]; extern u8 _object_goroiwaSegmentRomEnd[];
extern u8 _object_toryoSegmentRomStart[]; extern u8 _object_toryoSegmentRomEnd[];
extern u8 _object_daikuSegmentRomStart[]; extern u8 _object_daikuSegmentRomEnd[];
extern u8 _object_nwcSegmentRomStart[]; extern u8 _object_nwcSegmentRomEnd[];
extern u8 _object_gmSegmentRomStart[]; extern u8 _object_gmSegmentRomEnd[];
extern u8 _object_msSegmentRomStart[]; extern u8 _object_msSegmentRomEnd[];
extern u8 _object_hsSegmentRomStart[]; extern u8 _object_hsSegmentRomEnd[];
extern u8 _object_lightswitchSegmentRomStart[]; extern u8 _object_lightswitchSegmentRomEnd[];
extern u8 _object_kusaSegmentRomStart[]; extern u8 _object_kusaSegmentRomEnd[];
extern u8 _object_tsuboSegmentRomStart[]; extern u8 _object_tsuboSegmentRomEnd[];
extern u8 _object_kanbanSegmentRomStart[]; extern u8 _object_kanbanSegmentRomEnd[];
extern u8 _object_owlSegmentRomStart[]; extern u8 _object_owlSegmentRomEnd[];
extern u8 _object_mkSegmentRomStart[]; extern u8 _object_mkSegmentRomEnd[];
extern u8 _object_fuSegmentRomStart[]; extern u8 _object_fuSegmentRomEnd[];
extern u8 _object_gi_ki_tan_maskSegmentRomStart[]; extern u8 _object_gi_ki_tan_maskSegmentRomEnd[];
extern u8 _object_gi_mask18SegmentRomStart[]; extern u8 _object_gi_mask18SegmentRomEnd[];
extern u8 _object_gi_rabit_maskSegmentRomStart[]; extern u8 _object_gi_rabit_maskSegmentRomEnd[];
extern u8 _object_gi_truth_maskSegmentRomStart[]; extern u8 _object_gi_truth_maskSegmentRomEnd[];
extern u8 _object_streamSegmentRomStart[]; extern u8 _object_streamSegmentRomEnd[];
extern u8 _object_mmSegmentRomStart[]; extern u8 _object_mmSegmentRomEnd[];
extern u8 _object_jsSegmentRomStart[]; extern u8 _object_jsSegmentRomEnd[];
extern u8 _object_csSegmentRomStart[]; extern u8 _object_csSegmentRomEnd[];
extern u8 _object_gi_soldoutSegmentRomStart[]; extern u8 _object_gi_soldoutSegmentRomEnd[];
extern u8 _object_magSegmentRomStart[]; extern u8 _object_magSegmentRomEnd[];
extern u8 _object_gi_golonmaskSegmentRomStart[]; extern u8 _object_gi_golonmaskSegmentRomEnd[];
extern u8 _object_gi_zoramaskSegmentRomStart[]; extern u8 _object_gi_zoramaskSegmentRomEnd[];
extern u8 _object_kaSegmentRomStart[]; extern u8 _object_kaSegmentRomEnd[];
extern u8 _object_zgSegmentRomStart[]; extern u8 _object_zgSegmentRomEnd[];
extern u8 _object_gi_m_arrowSegmentRomStart[]; extern u8 _object_gi_m_arrowSegmentRomEnd[];
extern u8 _object_ds2SegmentRomStart[]; extern u8 _object_ds2SegmentRomEnd[];
extern u8 _object_fishSegmentRomStart[]; extern u8 _object_fishSegmentRomEnd[];
extern u8 _object_gi_sutaruSegmentRomStart[]; extern u8 _object_gi_sutaruSegmentRomEnd[];
extern u8 _object_sshSegmentRomStart[]; extern u8 _object_sshSegmentRomEnd[];
extern u8 _object_bigslimeSegmentRomStart[]; extern u8 _object_bigslimeSegmentRomEnd[];
extern u8 _object_bgSegmentRomStart[]; extern u8 _object_bgSegmentRomEnd[];
extern u8 _object_bombiwaSegmentRomStart[]; extern u8 _object_bombiwaSegmentRomEnd[];
extern u8 _object_hintnutsSegmentRomStart[]; extern u8 _object_hintnutsSegmentRomEnd[];
extern u8 _object_rsSegmentRomStart[]; extern u8 _object_rsSegmentRomEnd[];
extern u8 _object_glaSegmentRomStart[]; extern u8 _object_glaSegmentRomEnd[];
extern u8 _object_geldbSegmentRomStart[]; extern u8 _object_geldbSegmentRomEnd[];
extern u8 _object_dogSegmentRomStart[]; extern u8 _object_dogSegmentRomEnd[];
extern u8 _object_kibako2SegmentRomStart[]; extern u8 _object_kibako2SegmentRomEnd[];
extern u8 _object_dnsSegmentRomStart[]; extern u8 _object_dnsSegmentRomEnd[];
extern u8 _object_dnkSegmentRomStart[]; extern u8 _object_dnkSegmentRomEnd[];
extern u8 _object_gi_insectSegmentRomStart[]; extern u8 _object_gi_insectSegmentRomEnd[];
extern u8 _object_gi_ghostSegmentRomStart[]; extern u8 _object_gi_ghostSegmentRomEnd[];
extern u8 _object_gi_soulSegmentRomStart[]; extern u8 _object_gi_soulSegmentRomEnd[];
extern u8 _object_f40_objSegmentRomStart[]; extern u8 _object_f40_objSegmentRomEnd[];
extern u8 _object_gi_rupySegmentRomStart[]; extern u8 _object_gi_rupySegmentRomEnd[];
extern u8 _object_po_composerSegmentRomStart[]; extern u8 _object_po_composerSegmentRomEnd[];
extern u8 _object_muSegmentRomStart[]; extern u8 _object_muSegmentRomEnd[];
extern u8 _object_wfSegmentRomStart[]; extern u8 _object_wfSegmentRomEnd[];
extern u8 _object_skbSegmentRomStart[]; extern u8 _object_skbSegmentRomEnd[];
extern u8 _object_gsSegmentRomStart[]; extern u8 _object_gsSegmentRomEnd[];
extern u8 _object_psSegmentRomStart[]; extern u8 _object_psSegmentRomEnd[];
extern u8 _object_omoya_objSegmentRomStart[]; extern u8 _object_omoya_objSegmentRomEnd[];
extern u8 _object_crowSegmentRomStart[]; extern u8 _object_crowSegmentRomEnd[];
extern u8 _object_cowSegmentRomStart[]; extern u8 _object_cowSegmentRomEnd[];
extern u8 _object_gi_sword_1SegmentRomStart[]; extern u8 _object_gi_sword_1SegmentRomEnd[];
extern u8 _object_zl4SegmentRomStart[]; extern u8 _object_zl4SegmentRomEnd[];
extern u8 _object_grasshopperSegmentRomStart[]; extern u8 _object_grasshopperSegmentRomEnd[];
extern u8 _object_boyoSegmentRomStart[]; extern u8 _object_boyoSegmentRomEnd[];
extern u8 _object_fwallSegmentRomStart[]; extern u8 _object_fwallSegmentRomEnd[];
extern u8 _object_jsoSegmentRomStart[]; extern u8 _object_jsoSegmentRomEnd[];
extern u8 _object_knightSegmentRomStart[]; extern u8 _object_knightSegmentRomEnd[];
extern u8 _object_icicleSegmentRomStart[]; extern u8 _object_icicleSegmentRomEnd[];
extern u8 _object_spdwebSegmentRomStart[]; extern u8 _object_spdwebSegmentRomEnd[];
extern u8 _object_boss01SegmentRomStart[]; extern u8 _object_boss01SegmentRomEnd[];
extern u8 _object_boss02SegmentRomStart[]; extern u8 _object_boss02SegmentRomEnd[];
extern u8 _object_boss03SegmentRomStart[]; extern u8 _object_boss03SegmentRomEnd[];
extern u8 _object_boss04SegmentRomStart[]; extern u8 _object_boss04SegmentRomEnd[];
extern u8 _object_boss05SegmentRomStart[]; extern u8 _object_boss05SegmentRomEnd[];
extern u8 _object_boss07SegmentRomStart[]; extern u8 _object_boss07SegmentRomEnd[];
extern u8 _object_rafSegmentRomStart[]; extern u8 _object_rafSegmentRomEnd[];
extern u8 _object_funenSegmentRomStart[]; extern u8 _object_funenSegmentRomEnd[];
extern u8 _object_railliftSegmentRomStart[]; extern u8 _object_railliftSegmentRomEnd[];
extern u8 _object_numa_objSegmentRomStart[]; extern u8 _object_numa_objSegmentRomEnd[];
extern u8 _object_flowerpotSegmentRomStart[]; extern u8 _object_flowerpotSegmentRomEnd[];
extern u8 _object_spinyrollSegmentRomStart[]; extern u8 _object_spinyrollSegmentRomEnd[];
extern u8 _object_ice_blockSegmentRomStart[]; extern u8 _object_ice_blockSegmentRomEnd[];
extern u8 _object_keikoku_demoSegmentRomStart[]; extern u8 _object_keikoku_demoSegmentRomEnd[];
extern u8 _object_slimeSegmentRomStart[]; extern u8 _object_slimeSegmentRomEnd[];
extern u8 _object_prSegmentRomStart[]; extern u8 _object_prSegmentRomEnd[];
extern u8 _object_f52_objSegmentRomStart[]; extern u8 _object_f52_objSegmentRomEnd[];
extern u8 _object_f53_objSegmentRomStart[]; extern u8 _object_f53_objSegmentRomEnd[];
extern u8 _object_kibakoSegmentRomStart[]; extern u8 _object_kibakoSegmentRomEnd[];
extern u8 _object_sekSegmentRomStart[]; extern u8 _object_sekSegmentRomEnd[];
extern u8 _object_gmoSegmentRomStart[]; extern u8 _object_gmoSegmentRomEnd[];
extern u8 _object_batSegmentRomStart[]; extern u8 _object_batSegmentRomEnd[];
extern u8 _object_sekihilSegmentRomStart[]; extern u8 _object_sekihilSegmentRomEnd[];
extern u8 _object_sekihigSegmentRomStart[]; extern u8 _object_sekihigSegmentRomEnd[];
extern u8 _object_sekihinSegmentRomStart[]; extern u8 _object_sekihinSegmentRomEnd[];
extern u8 _object_sekihizSegmentRomStart[]; extern u8 _object_sekihizSegmentRomEnd[];
extern u8 _object_wizSegmentRomStart[]; extern u8 _object_wizSegmentRomEnd[];
extern u8 _object_ladderSegmentRomStart[]; extern u8 _object_ladderSegmentRomEnd[];
extern u8 _object_mkkSegmentRomStart[]; extern u8 _object_mkkSegmentRomEnd[];
extern u8 _object_keikoku_objSegmentRomStart[]; extern u8 _object_keikoku_objSegmentRomEnd[];
extern u8 _object_sichitai_objSegmentRomStart[]; extern u8 _object_sichitai_objSegmentRomEnd[];
extern u8 _object_dekucity_ana_objSegmentRomStart[]; extern u8 _object_dekucity_ana_objSegmentRomEnd[];
extern u8 _object_ratSegmentRomStart[]; extern u8 _object_ratSegmentRomEnd[];
extern u8 _object_water_effectSegmentRomStart[]; extern u8 _object_water_effectSegmentRomEnd[];
extern u8 _object_dblue_objectSegmentRomStart[]; extern u8 _object_dblue_objectSegmentRomEnd[];
extern u8 _object_balSegmentRomStart[]; extern u8 _object_balSegmentRomEnd[];
extern u8 _object_warp_uzuSegmentRomStart[]; extern u8 _object_warp_uzuSegmentRomEnd[];
extern u8 _object_drifticeSegmentRomStart[]; extern u8 _object_drifticeSegmentRomEnd[];
extern u8 _object_fallSegmentRomStart[]; extern u8 _object_fallSegmentRomEnd[];
extern u8 _object_hanareyama_objSegmentRomStart[]; extern u8 _object_hanareyama_objSegmentRomEnd[];
extern u8 _object_crace_objectSegmentRomStart[]; extern u8 _object_crace_objectSegmentRomEnd[];
extern u8 _object_dnqSegmentRomStart[]; extern u8 _object_dnqSegmentRomEnd[];
extern u8 _object_obj_tokeidaiSegmentRomStart[]; extern u8 _object_obj_tokeidaiSegmentRomEnd[];
extern u8 _object_egSegmentRomStart[]; extern u8 _object_egSegmentRomEnd[];
extern u8 _object_truSegmentRomStart[]; extern u8 _object_truSegmentRomEnd[];
extern u8 _object_trtSegmentRomStart[]; extern u8 _object_trtSegmentRomEnd[];
extern u8 _object_hakugin_objSegmentRomStart[]; extern u8 _object_hakugin_objSegmentRomEnd[];
extern u8 _object_horse_game_checkSegmentRomStart[]; extern u8 _object_horse_game_checkSegmentRomEnd[];
extern u8 _object_stkSegmentRomStart[]; extern u8 _object_stkSegmentRomEnd[];
extern u8 _object_mnkSegmentRomStart[]; extern u8 _object_mnkSegmentRomEnd[];
extern u8 _object_gi_bottle_redSegmentRomStart[]; extern u8 _object_gi_bottle_redSegmentRomEnd[];
extern u8 _object_tokei_tobiraSegmentRomStart[]; extern u8 _object_tokei_tobiraSegmentRomEnd[];
extern u8 _object_azSegmentRomStart[]; extern u8 _object_azSegmentRomEnd[];
extern u8 _object_twigSegmentRomStart[]; extern u8 _object_twigSegmentRomEnd[];
extern u8 _object_dekucity_objSegmentRomStart[]; extern u8 _object_dekucity_objSegmentRomEnd[];
extern u8 _object_po_fusenSegmentRomStart[]; extern u8 _object_po_fusenSegmentRomEnd[];
extern u8 _object_racetsuboSegmentRomStart[]; extern u8 _object_racetsuboSegmentRomEnd[];
extern u8 _object_haSegmentRomStart[]; extern u8 _object_haSegmentRomEnd[];
extern u8 _object_bigokutaSegmentRomStart[]; extern u8 _object_bigokutaSegmentRomEnd[];
extern u8 _object_open_objSegmentRomStart[]; extern u8 _object_open_objSegmentRomEnd[];
extern u8 _object_fu_kaitenSegmentRomStart[]; extern u8 _object_fu_kaitenSegmentRomEnd[];
extern u8 _object_fu_matoSegmentRomStart[]; extern u8 _object_fu_matoSegmentRomEnd[];
extern u8 _object_mtorideSegmentRomStart[]; extern u8 _object_mtorideSegmentRomEnd[];
extern u8 _object_osnSegmentRomStart[]; extern u8 _object_osnSegmentRomEnd[];
extern u8 _object_tokei_stepSegmentRomStart[]; extern u8 _object_tokei_stepSegmentRomEnd[];
extern u8 _object_lotusSegmentRomStart[]; extern u8 _object_lotusSegmentRomEnd[];
extern u8 _object_tlSegmentRomStart[]; extern u8 _object_tlSegmentRomEnd[];
extern u8 _object_dkjail_objSegmentRomStart[]; extern u8 _object_dkjail_objSegmentRomEnd[];
extern u8 _object_visiblockSegmentRomStart[]; extern u8 _object_visiblockSegmentRomEnd[];
extern u8 _object_tsnSegmentRomStart[]; extern u8 _object_tsnSegmentRomEnd[];
extern u8 _object_ds2nSegmentRomStart[]; extern u8 _object_ds2nSegmentRomEnd[];
extern u8 _object_fsnSegmentRomStart[]; extern u8 _object_fsnSegmentRomEnd[];
extern u8 _object_shnSegmentRomStart[]; extern u8 _object_shnSegmentRomEnd[];
extern u8 _object_bigicicleSegmentRomStart[]; extern u8 _object_bigicicleSegmentRomEnd[];
extern u8 _object_gi_bottle_15SegmentRomStart[]; extern u8 _object_gi_bottle_15SegmentRomEnd[];
extern u8 _object_tkSegmentRomStart[]; extern u8 _object_tkSegmentRomEnd[];
extern u8 _object_market_objSegmentRomStart[]; extern u8 _object_market_objSegmentRomEnd[];
extern u8 _object_gi_reserve00SegmentRomStart[]; extern u8 _object_gi_reserve00SegmentRomEnd[];
extern u8 _object_gi_reserve01SegmentRomStart[]; extern u8 _object_gi_reserve01SegmentRomEnd[];
extern u8 _object_lightblockSegmentRomStart[]; extern u8 _object_lightblockSegmentRomEnd[];
extern u8 _object_takaraya_objectsSegmentRomStart[]; extern u8 _object_takaraya_objectsSegmentRomEnd[];
extern u8 _object_wdhandSegmentRomStart[]; extern u8 _object_wdhandSegmentRomEnd[];
extern u8 _object_sdnSegmentRomStart[]; extern u8 _object_sdnSegmentRomEnd[];
extern u8 _object_snowwdSegmentRomStart[]; extern u8 _object_snowwdSegmentRomEnd[];
extern u8 _object_giantSegmentRomStart[]; extern u8 _object_giantSegmentRomEnd[];
extern u8 _object_combSegmentRomStart[]; extern u8 _object_combSegmentRomEnd[];
extern u8 _object_hanaSegmentRomStart[]; extern u8 _object_hanaSegmentRomEnd[];
extern u8 _object_boss_hakuginSegmentRomStart[]; extern u8 _object_boss_hakuginSegmentRomEnd[];
extern u8 _object_meganeana_objSegmentRomStart[]; extern u8 _object_meganeana_objSegmentRomEnd[];
extern u8 _object_gi_nutsmaskSegmentRomStart[]; extern u8 _object_gi_nutsmaskSegmentRomEnd[];
extern u8 _object_stk2SegmentRomStart[]; extern u8 _object_stk2SegmentRomEnd[];
extern u8 _object_spot11_objSegmentRomStart[]; extern u8 _object_spot11_objSegmentRomEnd[];
extern u8 _object_danpei_objectSegmentRomStart[]; extern u8 _object_danpei_objectSegmentRomEnd[];
extern u8 _object_dhouseSegmentRomStart[]; extern u8 _object_dhouseSegmentRomEnd[];
extern u8 _object_hakaisiSegmentRomStart[]; extern u8 _object_hakaisiSegmentRomEnd[];
extern u8 _object_poSegmentRomStart[]; extern u8 _object_poSegmentRomEnd[];
extern u8 _object_snowmanSegmentRomStart[]; extern u8 _object_snowmanSegmentRomEnd[];
extern u8 _object_po_sistersSegmentRomStart[]; extern u8 _object_po_sistersSegmentRomEnd[];
extern u8 _object_ppSegmentRomStart[]; extern u8 _object_ppSegmentRomEnd[];
extern u8 _object_goronswitchSegmentRomStart[]; extern u8 _object_goronswitchSegmentRomEnd[];
extern u8 _object_delfSegmentRomStart[]; extern u8 _object_delfSegmentRomEnd[];
extern u8 _object_botihasiraSegmentRomStart[]; extern u8 _object_botihasiraSegmentRomEnd[];
extern u8 _object_gi_bigbombSegmentRomStart[]; extern u8 _object_gi_bigbombSegmentRomEnd[];
extern u8 _object_pstSegmentRomStart[]; extern u8 _object_pstSegmentRomEnd[];
extern u8 _object_bsmaskSegmentRomStart[]; extern u8 _object_bsmaskSegmentRomEnd[];
extern u8 _object_spidertentSegmentRomStart[]; extern u8 _object_spidertentSegmentRomEnd[];
extern u8 _object_zoraeggSegmentRomStart[]; extern u8 _object_zoraeggSegmentRomEnd[];
extern u8 _object_kbtSegmentRomStart[]; extern u8 _object_kbtSegmentRomEnd[];
extern u8 _object_ggSegmentRomStart[]; extern u8 _object_ggSegmentRomEnd[];
extern u8 _object_marutaSegmentRomStart[]; extern u8 _object_marutaSegmentRomEnd[];
extern u8 _object_ghakaSegmentRomStart[]; extern u8 _object_ghakaSegmentRomEnd[];
extern u8 _object_oyuSegmentRomStart[]; extern u8 _object_oyuSegmentRomEnd[];
extern u8 _object_dnpSegmentRomStart[]; extern u8 _object_dnpSegmentRomEnd[];
extern u8 _object_daiSegmentRomStart[]; extern u8 _object_daiSegmentRomEnd[];
extern u8 _object_kgySegmentRomStart[]; extern u8 _object_kgySegmentRomEnd[];
extern u8 _object_fbSegmentRomStart[]; extern u8 _object_fbSegmentRomEnd[];
extern u8 _object_taisouSegmentRomStart[]; extern u8 _object_taisouSegmentRomEnd[];
extern u8 _object_gkSegmentRomStart[]; extern u8 _object_gkSegmentRomEnd[];
extern u8 _object_haka_objSegmentRomStart[]; extern u8 _object_haka_objSegmentRomEnd[];
extern u8 _object_dntSegmentRomStart[]; extern u8 _object_dntSegmentRomEnd[];
extern u8 _object_yukiyamaSegmentRomStart[]; extern u8 _object_yukiyamaSegmentRomEnd[];
extern u8 _object_icefloeSegmentRomStart[]; extern u8 _object_icefloeSegmentRomEnd[];
extern u8 _object_gi_gold_dustSegmentRomStart[]; extern u8 _object_gi_gold_dustSegmentRomEnd[];
extern u8 _object_gi_bottle_16SegmentRomStart[]; extern u8 _object_gi_bottle_16SegmentRomEnd[];
extern u8 _object_gi_bottle_22SegmentRomStart[]; extern u8 _object_gi_bottle_22SegmentRomEnd[];
extern u8 _object_beeSegmentRomStart[]; extern u8 _object_beeSegmentRomEnd[];
extern u8 _object_otSegmentRomStart[]; extern u8 _object_otSegmentRomEnd[];
extern u8 _object_utuboSegmentRomStart[]; extern u8 _object_utuboSegmentRomEnd[];
extern u8 _object_doraSegmentRomStart[]; extern u8 _object_doraSegmentRomEnd[];
extern u8 _object_gi_loachSegmentRomStart[]; extern u8 _object_gi_loachSegmentRomEnd[];
extern u8 _object_gi_seahorseSegmentRomStart[]; extern u8 _object_gi_seahorseSegmentRomEnd[];
extern u8 _object_bigpoSegmentRomStart[]; extern u8 _object_bigpoSegmentRomEnd[];
extern u8 _object_harikoSegmentRomStart[]; extern u8 _object_harikoSegmentRomEnd[];
extern u8 _object_dnoSegmentRomStart[]; extern u8 _object_dnoSegmentRomEnd[];
extern u8 _object_sinkai_kabeSegmentRomStart[]; extern u8 _object_sinkai_kabeSegmentRomEnd[];
extern u8 _object_kin2_objSegmentRomStart[]; extern u8 _object_kin2_objSegmentRomEnd[];
extern u8 _object_ishiSegmentRomStart[]; extern u8 _object_ishiSegmentRomEnd[];
extern u8 _object_hakugin_demoSegmentRomStart[]; extern u8 _object_hakugin_demoSegmentRomEnd[];
extern u8 _object_jgSegmentRomStart[]; extern u8 _object_jgSegmentRomEnd[];
extern u8 _object_gi_sword_2SegmentRomStart[]; extern u8 _object_gi_sword_2SegmentRomEnd[];
extern u8 _object_gi_sword_3SegmentRomStart[]; extern u8 _object_gi_sword_3SegmentRomEnd[];
extern u8 _object_gi_sword_4SegmentRomStart[]; extern u8 _object_gi_sword_4SegmentRomEnd[];
extern u8 _object_umSegmentRomStart[]; extern u8 _object_umSegmentRomEnd[];
extern u8 _object_rbSegmentRomStart[]; extern u8 _object_rbSegmentRomEnd[];
extern u8 _object_mbar_objSegmentRomStart[]; extern u8 _object_mbar_objSegmentRomEnd[];
extern u8 _object_ikana_objSegmentRomStart[]; extern u8 _object_ikana_objSegmentRomEnd[];
extern u8 _object_kzSegmentRomStart[]; extern u8 _object_kzSegmentRomEnd[];
extern u8 _object_tokei_turretSegmentRomStart[]; extern u8 _object_tokei_turretSegmentRomEnd[];
extern u8 _object_zogSegmentRomStart[]; extern u8 _object_zogSegmentRomEnd[];
extern u8 _object_rotliftSegmentRomStart[]; extern u8 _object_rotliftSegmentRomEnd[];
extern u8 _object_posthouse_objSegmentRomStart[]; extern u8 _object_posthouse_objSegmentRomEnd[];
extern u8 _object_gi_mask09SegmentRomStart[]; extern u8 _object_gi_mask09SegmentRomEnd[];
extern u8 _object_gi_mask14SegmentRomStart[]; extern u8 _object_gi_mask14SegmentRomEnd[];
extern u8 _object_gi_mask15SegmentRomStart[]; extern u8 _object_gi_mask15SegmentRomEnd[];
extern u8 _object_inibs_objectSegmentRomStart[]; extern u8 _object_inibs_objectSegmentRomEnd[];
extern u8 _object_treeSegmentRomStart[]; extern u8 _object_treeSegmentRomEnd[];
extern u8 _object_kaizoku_objSegmentRomStart[]; extern u8 _object_kaizoku_objSegmentRomEnd[];
extern u8 _object_gi_reserve_b_00SegmentRomStart[]; extern u8 _object_gi_reserve_b_00SegmentRomEnd[];
extern u8 _object_gi_reserve_c_00SegmentRomStart[]; extern u8 _object_gi_reserve_c_00SegmentRomEnd[];
extern u8 _object_zobSegmentRomStart[]; extern u8 _object_zobSegmentRomEnd[];
extern u8 _object_milkbarSegmentRomStart[]; extern u8 _object_milkbarSegmentRomEnd[];
extern u8 _object_dmaskSegmentRomStart[]; extern u8 _object_dmaskSegmentRomEnd[];
extern u8 _object_gi_reserve_c_01SegmentRomStart[]; extern u8 _object_gi_reserve_c_01SegmentRomEnd[];
extern u8 _object_zodSegmentRomStart[]; extern u8 _object_zodSegmentRomEnd[];
extern u8 _object_kumo30SegmentRomStart[]; extern u8 _object_kumo30SegmentRomEnd[];
extern u8 _object_obj_yasiSegmentRomStart[]; extern u8 _object_obj_yasiSegmentRomEnd[];
extern u8 _object_tanron1SegmentRomStart[]; extern u8 _object_tanron1SegmentRomEnd[];
extern u8 _object_tanron2SegmentRomStart[]; extern u8 _object_tanron2SegmentRomEnd[];
extern u8 _object_tanron3SegmentRomStart[]; extern u8 _object_tanron3SegmentRomEnd[];
extern u8 _object_gi_magicmushroomSegmentRomStart[]; extern u8 _object_gi_magicmushroomSegmentRomEnd[];
extern u8 _object_obj_chanSegmentRomStart[]; extern u8 _object_obj_chanSegmentRomEnd[];
extern u8 _object_gi_mask10SegmentRomStart[]; extern u8 _object_gi_mask10SegmentRomEnd[];
extern u8 _object_zosSegmentRomStart[]; extern u8 _object_zosSegmentRomEnd[];
extern u8 _object_an2SegmentRomStart[]; extern u8 _object_an2SegmentRomEnd[];
extern u8 _object_an3SegmentRomStart[]; extern u8 _object_an3SegmentRomEnd[];
extern u8 _object_f40_switchSegmentRomStart[]; extern u8 _object_f40_switchSegmentRomEnd[];
extern u8 _object_lodmoonSegmentRomStart[]; extern u8 _object_lodmoonSegmentRomEnd[];
extern u8 _object_troSegmentRomStart[]; extern u8 _object_troSegmentRomEnd[];
extern u8 _object_gi_mask12SegmentRomStart[]; extern u8 _object_gi_mask12SegmentRomEnd[];
extern u8 _object_gi_mask23SegmentRomStart[]; extern u8 _object_gi_mask23SegmentRomEnd[];
extern u8 _object_gi_bottle_21SegmentRomStart[]; extern u8 _object_gi_bottle_21SegmentRomEnd[];
extern u8 _object_gi_cameraSegmentRomStart[]; extern u8 _object_gi_cameraSegmentRomEnd[];
extern u8 _object_kamejimaSegmentRomStart[]; extern u8 _object_kamejimaSegmentRomEnd[];
extern u8 _object_nbSegmentRomStart[]; extern u8 _object_nbSegmentRomEnd[];
extern u8 _object_harfgibudSegmentRomStart[]; extern u8 _object_harfgibudSegmentRomEnd[];
extern u8 _object_zovSegmentRomStart[]; extern u8 _object_zovSegmentRomEnd[];
extern u8 _object_ahSegmentRomStart[]; extern u8 _object_ahSegmentRomEnd[];
extern u8 _object_hgdoorSegmentRomStart[]; extern u8 _object_hgdoorSegmentRomEnd[];
extern u8 _object_dor01SegmentRomStart[]; extern u8 _object_dor01SegmentRomEnd[];
extern u8 _object_dor02SegmentRomStart[]; extern u8 _object_dor02SegmentRomEnd[];
extern u8 _object_dor03SegmentRomStart[]; extern u8 _object_dor03SegmentRomEnd[];
extern u8 _object_dor04SegmentRomStart[]; extern u8 _object_dor04SegmentRomEnd[];
extern u8 _object_last_objSegmentRomStart[]; extern u8 _object_last_objSegmentRomEnd[];
extern u8 _object_redead_objSegmentRomStart[]; extern u8 _object_redead_objSegmentRomEnd[];
extern u8 _object_ikninside_objSegmentRomStart[]; extern u8 _object_ikninside_objSegmentRomEnd[];
extern u8 _object_iknv_objSegmentRomStart[]; extern u8 _object_iknv_objSegmentRomEnd[];
extern u8 _object_pameraSegmentRomStart[]; extern u8 _object_pameraSegmentRomEnd[];
extern u8 _object_hsstumpSegmentRomStart[]; extern u8 _object_hsstumpSegmentRomEnd[];
extern u8 _object_zmSegmentRomStart[]; extern u8 _object_zmSegmentRomEnd[];
extern u8 _object_alSegmentRomStart[]; extern u8 _object_alSegmentRomEnd[];
extern u8 _object_tabSegmentRomStart[]; extern u8 _object_tabSegmentRomEnd[];
extern u8 _object_secom_objSegmentRomStart[]; extern u8 _object_secom_objSegmentRomEnd[];
extern u8 _object_dtSegmentRomStart[]; extern u8 _object_dtSegmentRomEnd[];
extern u8 _object_gi_mask03SegmentRomStart[]; extern u8 _object_gi_mask03SegmentRomEnd[];
extern u8 _object_chaSegmentRomStart[]; extern u8 _object_chaSegmentRomEnd[];
extern u8 _object_obj_dinnerSegmentRomStart[]; extern u8 _object_obj_dinnerSegmentRomEnd[];
extern u8 _object_gi_reserve_b_01SegmentRomStart[]; extern u8 _object_gi_reserve_b_01SegmentRomEnd[];
extern u8 _object_lastdaySegmentRomStart[]; extern u8 _object_lastdaySegmentRomEnd[];
extern u8 _object_baiSegmentRomStart[]; extern u8 _object_baiSegmentRomEnd[];
extern u8 _object_ikn_demoSegmentRomStart[]; extern u8 _object_ikn_demoSegmentRomEnd[];
extern u8 _object_gi_fieldmapSegmentRomStart[]; extern u8 _object_gi_fieldmapSegmentRomEnd[];
extern u8 _object_big_fwallSegmentRomStart[]; extern u8 _object_big_fwallSegmentRomEnd[];
extern u8 _object_hunsuiSegmentRomStart[]; extern u8 _object_hunsuiSegmentRomEnd[];
extern u8 _object_uchSegmentRomStart[]; extern u8 _object_uchSegmentRomEnd[];
extern u8 _object_tanron4SegmentRomStart[]; extern u8 _object_tanron4SegmentRomEnd[];
extern u8 _object_tanron5SegmentRomStart[]; extern u8 _object_tanron5SegmentRomEnd[];
extern u8 _object_in2SegmentRomStart[]; extern u8 _object_in2SegmentRomEnd[];
extern u8 _object_ybSegmentRomStart[]; extern u8 _object_ybSegmentRomEnd[];
extern u8 _object_rzSegmentRomStart[]; extern u8 _object_rzSegmentRomEnd[];
extern u8 _object_bjtSegmentRomStart[]; extern u8 _object_bjtSegmentRomEnd[];
extern u8 _object_taruSegmentRomStart[]; extern u8 _object_taruSegmentRomEnd[];
extern u8 _object_moonstonSegmentRomStart[]; extern u8 _object_moonstonSegmentRomEnd[];
extern u8 _object_gi_scheduleSegmentRomStart[]; extern u8 _object_gi_scheduleSegmentRomEnd[];
extern u8 _object_gi_stonemaskSegmentRomStart[]; extern u8 _object_gi_stonemaskSegmentRomEnd[];
extern u8 _object_zorabandSegmentRomStart[]; extern u8 _object_zorabandSegmentRomEnd[];
extern u8 _object_kepn_koyaSegmentRomStart[]; extern u8 _object_kepn_koyaSegmentRomEnd[];
extern u8 _object_obj_usiyaneSegmentRomStart[]; extern u8 _object_obj_usiyaneSegmentRomEnd[];
extern u8 _object_gi_mask05SegmentRomStart[]; extern u8 _object_gi_mask05SegmentRomEnd[];
extern u8 _object_gi_mask11SegmentRomStart[]; extern u8 _object_gi_mask11SegmentRomEnd[];
extern u8 _object_gi_mask20SegmentRomStart[]; extern u8 _object_gi_mask20SegmentRomEnd[];
extern u8 _object_nnhSegmentRomStart[]; extern u8 _object_nnhSegmentRomEnd[];
extern u8 _object_kzsakuSegmentRomStart[]; extern u8 _object_kzsakuSegmentRomEnd[];
extern u8 _object_obj_milk_binSegmentRomStart[]; extern u8 _object_obj_milk_binSegmentRomEnd[];
extern u8 _object_random_objSegmentRomStart[]; extern u8 _object_random_objSegmentRomEnd[];
extern u8 _object_kujiyaSegmentRomStart[]; extern u8 _object_kujiyaSegmentRomEnd[];
extern u8 _object_kitanSegmentRomStart[]; extern u8 _object_kitanSegmentRomEnd[];
extern u8 _object_gi_mask06SegmentRomStart[]; extern u8 _object_gi_mask06SegmentRomEnd[];
extern u8 _object_gi_mask16SegmentRomStart[]; extern u8 _object_gi_mask16SegmentRomEnd[];
extern u8 _object_astr_objSegmentRomStart[]; extern u8 _object_astr_objSegmentRomEnd[];
extern u8 _object_bsbSegmentRomStart[]; extern u8 _object_bsbSegmentRomEnd[];
extern u8 _object_fall2SegmentRomStart[]; extern u8 _object_fall2SegmentRomEnd[];
extern u8 _object_sthSegmentRomStart[]; extern u8 _object_sthSegmentRomEnd[];
extern u8 _object_gi_mssaSegmentRomStart[]; extern u8 _object_gi_mssaSegmentRomEnd[];
extern u8 _object_smtowerSegmentRomStart[]; extern u8 _object_smtowerSegmentRomEnd[];
extern u8 _object_gi_mask21SegmentRomStart[]; extern u8 _object_gi_mask21SegmentRomEnd[];
extern u8 _object_yado_objSegmentRomStart[]; extern u8 _object_yado_objSegmentRomEnd[];
extern u8 _object_syotenSegmentRomStart[]; extern u8 _object_syotenSegmentRomEnd[];
extern u8 _object_moonendSegmentRomStart[]; extern u8 _object_moonendSegmentRomEnd[];
extern u8 _object_obSegmentRomStart[]; extern u8 _object_obSegmentRomEnd[];
extern u8 _object_gi_bottle_04SegmentRomStart[]; extern u8 _object_gi_bottle_04SegmentRomEnd[];
extern u8 _object_andSegmentRomStart[]; extern u8 _object_andSegmentRomEnd[];
extern u8 _object_obj_danpeiliftSegmentRomStart[]; extern u8 _object_obj_danpeiliftSegmentRomEnd[];
extern u8 _object_drsSegmentRomStart[]; extern u8 _object_drsSegmentRomEnd[];
extern u8 _object_msmoSegmentRomStart[]; extern u8 _object_msmoSegmentRomEnd[];
extern u8 _object_an4SegmentRomStart[]; extern u8 _object_an4SegmentRomEnd[];
extern u8 _object_wdor01SegmentRomStart[]; extern u8 _object_wdor01SegmentRomEnd[];
extern u8 _object_wdor02SegmentRomStart[]; extern u8 _object_wdor02SegmentRomEnd[];
extern u8 _object_wdor03SegmentRomStart[]; extern u8 _object_wdor03SegmentRomEnd[];
extern u8 _object_wdor04SegmentRomStart[]; extern u8 _object_wdor04SegmentRomEnd[];
extern u8 _object_wdor05SegmentRomStart[]; extern u8 _object_wdor05SegmentRomEnd[];
extern u8 _object_stk3SegmentRomStart[]; extern u8 _object_stk3SegmentRomEnd[];
extern u8 _object_kinsta1_objSegmentRomStart[]; extern u8 _object_kinsta1_objSegmentRomEnd[];
extern u8 _object_kinsta2_objSegmentRomStart[]; extern u8 _object_kinsta2_objSegmentRomEnd[];
extern u8 _object_bhSegmentRomStart[]; extern u8 _object_bhSegmentRomEnd[];
extern u8 _object_gi_mask17SegmentRomStart[]; extern u8 _object_gi_mask17SegmentRomEnd[];
extern u8 _object_gi_mask22SegmentRomStart[]; extern u8 _object_gi_mask22SegmentRomEnd[];
extern u8 _object_lbfshotSegmentRomStart[]; extern u8 _object_lbfshotSegmentRomEnd[];
extern u8 _object_fusenSegmentRomStart[]; extern u8 _object_fusenSegmentRomEnd[];
extern u8 _object_ending_objSegmentRomStart[]; extern u8 _object_ending_objSegmentRomEnd[];
extern u8 _object_gi_mask13SegmentRomStart[]; extern u8 _object_gi_mask13SegmentRomEnd[];
extern u8 __1114_0x01607b40SegmentRomStart[]; extern u8 __1114_0x01607b40SegmentRomEnd[];
extern u8 __1115_0x0160b1d0SegmentRomStart[]; extern u8 __1115_0x0160b1d0SegmentRomEnd[];
extern u8 __1116_0x0160c540SegmentRomStart[]; extern u8 __1116_0x0160c540SegmentRomEnd[];
extern u8 __1117_0x0160ed50SegmentRomStart[]; extern u8 __1117_0x0160ed50SegmentRomEnd[];
extern u8 __1118_0x01611e20SegmentRomStart[]; extern u8 __1118_0x01611e20SegmentRomEnd[];
extern u8 __1119_0x01615e00SegmentRomStart[]; extern u8 __1119_0x01615e00SegmentRomEnd[];
extern u8 __1120_0x01619170SegmentRomStart[]; extern u8 __1120_0x01619170SegmentRomEnd[];
extern u8 __1121_0x01619190SegmentRomStart[]; extern u8 __1121_0x01619190SegmentRomEnd[];
extern u8 _nintendo_rogo_staticSegmentRomStart[]; extern u8 _nintendo_rogo_staticSegmentRomEnd[];
extern u8 _title_staticSegmentRomStart[]; extern u8 _title_staticSegmentRomEnd[];
extern u8 __1124_0x0163f490SegmentRomStart[]; extern u8 __1124_0x0163f490SegmentRomEnd[];
extern u8 __1125_0x0163fc10SegmentRomStart[]; extern u8 __1125_0x0163fc10SegmentRomEnd[];
extern u8 __1126_0x0163ffc0SegmentRomStart[]; extern u8 __1126_0x0163ffc0SegmentRomEnd[];
extern u8 __1127_0x01643d50SegmentRomStart[]; extern u8 __1127_0x01643d50SegmentRomEnd[];
extern u8 __1128_0x01644c80SegmentRomStart[]; extern u8 __1128_0x01644c80SegmentRomEnd[];
extern u8 __1129_0x01646b60SegmentRomStart[]; extern u8 __1129_0x01646b60SegmentRomEnd[];
extern u8 __1130_0x01649020SegmentRomStart[]; extern u8 __1130_0x01649020SegmentRomEnd[];
extern u8 __1131_0x0164ad90SegmentRomStart[]; extern u8 __1131_0x0164ad90SegmentRomEnd[];
extern u8 _vr_fine_staticSegmentRomStart[]; extern u8 _vr_fine_staticSegmentRomEnd[];
extern u8 _vr_cloud_staticSegmentRomStart[]; extern u8 _vr_cloud_staticSegmentRomEnd[];
extern u8 _vr_pal_staticSegmentRomStart[]; extern u8 _vr_pal_staticSegmentRomEnd[];
extern u8 _elf_message_fieldSegmentRomStart[]; extern u8 _elf_message_fieldSegmentRomEnd[];
extern u8 _elf_message_ydanSegmentRomStart[]; extern u8 _elf_message_ydanSegmentRomEnd[];
extern u8 _Z2_20SICHITAI2SegmentRomStart[]; extern u8 _Z2_20SICHITAI2SegmentRomEnd[];
extern u8 _Z2_20SICHITAI2_room_00SegmentRomStart[]; extern u8 _Z2_20SICHITAI2_room_00SegmentRomEnd[];
extern u8 _Z2_20SICHITAI2_room_01SegmentRomStart[]; extern u8 _Z2_20SICHITAI2_room_01SegmentRomEnd[];
extern u8 _Z2_20SICHITAI2_room_02SegmentRomStart[]; extern u8 _Z2_20SICHITAI2_room_02SegmentRomEnd[];
extern u8 _Z2_WITCH_SHOPSegmentRomStart[]; extern u8 _Z2_WITCH_SHOPSegmentRomEnd[];
extern u8 _Z2_WITCH_SHOP_room_00SegmentRomStart[]; extern u8 _Z2_WITCH_SHOP_room_00SegmentRomEnd[];
extern u8 _Z2_LAST_BSSegmentRomStart[]; extern u8 _Z2_LAST_BSSegmentRomEnd[];
extern u8 _Z2_LAST_BS_room_00SegmentRomStart[]; extern u8 _Z2_LAST_BS_room_00SegmentRomEnd[];
extern u8 _Z2_HAKASHITASegmentRomStart[]; extern u8 _Z2_HAKASHITASegmentRomEnd[];
extern u8 _Z2_HAKASHITA_room_00SegmentRomStart[]; extern u8 _Z2_HAKASHITA_room_00SegmentRomEnd[];
extern u8 _Z2_HAKASHITA_room_01SegmentRomStart[]; extern u8 _Z2_HAKASHITA_room_01SegmentRomEnd[];
extern u8 _Z2_HAKASHITA_room_02SegmentRomStart[]; extern u8 _Z2_HAKASHITA_room_02SegmentRomEnd[];
extern u8 _Z2_HAKASHITA_room_03SegmentRomStart[]; extern u8 _Z2_HAKASHITA_room_03SegmentRomEnd[];
extern u8 _Z2_HAKASHITA_room_04SegmentRomStart[]; extern u8 _Z2_HAKASHITA_room_04SegmentRomEnd[];
extern u8 _Z2_AYASHIISHOPSegmentRomStart[]; extern u8 _Z2_AYASHIISHOPSegmentRomEnd[];
extern u8 _Z2_AYASHIISHOP_room_00SegmentRomStart[]; extern u8 _Z2_AYASHIISHOP_room_00SegmentRomEnd[];
extern u8 _Z2_AYASHIISHOP_room_01SegmentRomStart[]; extern u8 _Z2_AYASHIISHOP_room_01SegmentRomEnd[];
extern u8 _Z2_OMOYASegmentRomStart[]; extern u8 _Z2_OMOYASegmentRomEnd[];
extern u8 _Z2_OMOYA_room_00SegmentRomStart[]; extern u8 _Z2_OMOYA_room_00SegmentRomEnd[];
extern u8 _Z2_OMOYA_room_01SegmentRomStart[]; extern u8 _Z2_OMOYA_room_01SegmentRomEnd[];
extern u8 _Z2_OMOYA_room_02SegmentRomStart[]; extern u8 _Z2_OMOYA_room_02SegmentRomEnd[];
extern u8 _Z2_BOWLINGSegmentRomStart[]; extern u8 _Z2_BOWLINGSegmentRomEnd[];
extern u8 _Z2_BOWLING_room_00SegmentRomStart[]; extern u8 _Z2_BOWLING_room_00SegmentRomEnd[];
extern u8 _Z2_SONCHONOIESegmentRomStart[]; extern u8 _Z2_SONCHONOIESegmentRomEnd[];
extern u8 _Z2_SONCHONOIE_room_00SegmentRomStart[]; extern u8 _Z2_SONCHONOIE_room_00SegmentRomEnd[];
extern u8 _Z2_SONCHONOIE_room_01SegmentRomStart[]; extern u8 _Z2_SONCHONOIE_room_01SegmentRomEnd[];
extern u8 _Z2_SONCHONOIE_room_02SegmentRomStart[]; extern u8 _Z2_SONCHONOIE_room_02SegmentRomEnd[];
extern u8 _Z2_SONCHONOIE_room_03SegmentRomStart[]; extern u8 _Z2_SONCHONOIE_room_03SegmentRomEnd[];
extern u8 _Z2_IKANASegmentRomStart[]; extern u8 _Z2_IKANASegmentRomEnd[];
extern u8 _Z2_IKANA_room_00SegmentRomStart[]; extern u8 _Z2_IKANA_room_00SegmentRomEnd[];
extern u8 _Z2_IKANA_room_01SegmentRomStart[]; extern u8 _Z2_IKANA_room_01SegmentRomEnd[];
extern u8 _Z2_IKANA_room_02SegmentRomStart[]; extern u8 _Z2_IKANA_room_02SegmentRomEnd[];
extern u8 _Z2_IKANA_room_03SegmentRomStart[]; extern u8 _Z2_IKANA_room_03SegmentRomEnd[];
extern u8 _Z2_IKANA_room_04SegmentRomStart[]; extern u8 _Z2_IKANA_room_04SegmentRomEnd[];
extern u8 _Z2_KAIZOKUSegmentRomStart[]; extern u8 _Z2_KAIZOKUSegmentRomEnd[];
extern u8 _Z2_KAIZOKU_room_00SegmentRomStart[]; extern u8 _Z2_KAIZOKU_room_00SegmentRomEnd[];
extern u8 _Z2_MILK_BARSegmentRomStart[]; extern u8 _Z2_MILK_BARSegmentRomEnd[];
extern u8 _Z2_MILK_BAR_room_00SegmentRomStart[]; extern u8 _Z2_MILK_BAR_room_00SegmentRomEnd[];
extern u8 _Z2_INISIE_NSegmentRomStart[]; extern u8 _Z2_INISIE_NSegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_00SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_00SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_01SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_01SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_02SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_02SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_03SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_03SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_04SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_04SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_05SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_05SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_06SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_06SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_07SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_07SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_08SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_08SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_09SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_09SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_10SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_10SegmentRomEnd[];
extern u8 _Z2_INISIE_N_room_11SegmentRomStart[]; extern u8 _Z2_INISIE_N_room_11SegmentRomEnd[];
extern u8 _Z2_TAKARAYASegmentRomStart[]; extern u8 _Z2_TAKARAYASegmentRomEnd[];
extern u8 _Z2_TAKARAYA_room_00SegmentRomStart[]; extern u8 _Z2_TAKARAYA_room_00SegmentRomEnd[];
extern u8 _Z2_INISIE_RSegmentRomStart[]; extern u8 _Z2_INISIE_RSegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_00SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_00SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_01SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_01SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_02SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_02SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_03SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_03SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_04SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_04SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_05SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_05SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_06SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_06SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_07SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_07SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_08SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_08SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_09SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_09SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_10SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_10SegmentRomEnd[];
extern u8 _Z2_INISIE_R_room_11SegmentRomStart[]; extern u8 _Z2_INISIE_R_room_11SegmentRomEnd[];
extern u8 _Z2_OKUJOUSegmentRomStart[]; extern u8 _Z2_OKUJOUSegmentRomEnd[];
extern u8 _Z2_OKUJOU_room_00SegmentRomStart[]; extern u8 _Z2_OKUJOU_room_00SegmentRomEnd[];
extern u8 _Z2_OPENINGDANSegmentRomStart[]; extern u8 _Z2_OPENINGDANSegmentRomEnd[];
extern u8 _Z2_OPENINGDAN_room_00SegmentRomStart[]; extern u8 _Z2_OPENINGDAN_room_00SegmentRomEnd[];
extern u8 _Z2_OPENINGDAN_room_01SegmentRomStart[]; extern u8 _Z2_OPENINGDAN_room_01SegmentRomEnd[];
extern u8 _Z2_MITURINSegmentRomStart[]; extern u8 _Z2_MITURINSegmentRomEnd[];
extern u8 _Z2_MITURIN_room_00SegmentRomStart[]; extern u8 _Z2_MITURIN_room_00SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_01SegmentRomStart[]; extern u8 _Z2_MITURIN_room_01SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_02SegmentRomStart[]; extern u8 _Z2_MITURIN_room_02SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_03SegmentRomStart[]; extern u8 _Z2_MITURIN_room_03SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_04SegmentRomStart[]; extern u8 _Z2_MITURIN_room_04SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_05SegmentRomStart[]; extern u8 _Z2_MITURIN_room_05SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_06SegmentRomStart[]; extern u8 _Z2_MITURIN_room_06SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_07SegmentRomStart[]; extern u8 _Z2_MITURIN_room_07SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_08SegmentRomStart[]; extern u8 _Z2_MITURIN_room_08SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_09SegmentRomStart[]; extern u8 _Z2_MITURIN_room_09SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_10SegmentRomStart[]; extern u8 _Z2_MITURIN_room_10SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_11SegmentRomStart[]; extern u8 _Z2_MITURIN_room_11SegmentRomEnd[];
extern u8 _Z2_MITURIN_room_12SegmentRomStart[]; extern u8 _Z2_MITURIN_room_12SegmentRomEnd[];
extern u8 _Z2_13HUBUKINOMITISegmentRomStart[]; extern u8 _Z2_13HUBUKINOMITISegmentRomEnd[];
extern u8 _Z2_13HUBUKINOMITI_room_00SegmentRomStart[]; extern u8 _Z2_13HUBUKINOMITI_room_00SegmentRomEnd[];
extern u8 _Z2_CASTLESegmentRomStart[]; extern u8 _Z2_CASTLESegmentRomEnd[];
extern u8 _Z2_CASTLE_room_00SegmentRomStart[]; extern u8 _Z2_CASTLE_room_00SegmentRomEnd[];
extern u8 _Z2_CASTLE_room_01SegmentRomStart[]; extern u8 _Z2_CASTLE_room_01SegmentRomEnd[];
extern u8 _Z2_CASTLE_room_02SegmentRomStart[]; extern u8 _Z2_CASTLE_room_02SegmentRomEnd[];
extern u8 _Z2_CASTLE_room_03SegmentRomStart[]; extern u8 _Z2_CASTLE_room_03SegmentRomEnd[];
extern u8 _Z2_CASTLE_room_04SegmentRomStart[]; extern u8 _Z2_CASTLE_room_04SegmentRomEnd[];
extern u8 _Z2_CASTLE_room_05SegmentRomStart[]; extern u8 _Z2_CASTLE_room_05SegmentRomEnd[];
extern u8 _Z2_CASTLE_room_06SegmentRomStart[]; extern u8 _Z2_CASTLE_room_06SegmentRomEnd[];
extern u8 _Z2_CASTLE_room_07SegmentRomStart[]; extern u8 _Z2_CASTLE_room_07SegmentRomEnd[];
extern u8 _Z2_CASTLE_room_08SegmentRomStart[]; extern u8 _Z2_CASTLE_room_08SegmentRomEnd[];
extern u8 _Z2_CASTLE_room_09SegmentRomStart[]; extern u8 _Z2_CASTLE_room_09SegmentRomEnd[];
extern u8 _Z2_DEKUTESSegmentRomStart[]; extern u8 _Z2_DEKUTESSegmentRomEnd[];
extern u8 _Z2_DEKUTES_room_00SegmentRomStart[]; extern u8 _Z2_DEKUTES_room_00SegmentRomEnd[];
extern u8 _Z2_MITURIN_BSSegmentRomStart[]; extern u8 _Z2_MITURIN_BSSegmentRomEnd[];
extern u8 _Z2_MITURIN_BS_room_00SegmentRomStart[]; extern u8 _Z2_MITURIN_BS_room_00SegmentRomEnd[];
extern u8 _Z2_SYATEKI_MIZUSegmentRomStart[]; extern u8 _Z2_SYATEKI_MIZUSegmentRomEnd[];
extern u8 _Z2_SYATEKI_MIZU_room_00SegmentRomStart[]; extern u8 _Z2_SYATEKI_MIZU_room_00SegmentRomEnd[];
extern u8 _Z2_HAKUGINSegmentRomStart[]; extern u8 _Z2_HAKUGINSegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_00SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_00SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_01SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_01SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_02SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_02SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_03SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_03SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_04SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_04SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_05SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_05SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_06SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_06SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_07SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_07SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_08SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_08SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_09SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_09SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_10SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_10SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_11SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_11SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_12SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_12SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_room_13SegmentRomStart[]; extern u8 _Z2_HAKUGIN_room_13SegmentRomEnd[];
extern u8 _Z2_ROMANYMAESegmentRomStart[]; extern u8 _Z2_ROMANYMAESegmentRomEnd[];
extern u8 _Z2_ROMANYMAE_room_00SegmentRomStart[]; extern u8 _Z2_ROMANYMAE_room_00SegmentRomEnd[];
extern u8 _Z2_PIRATESegmentRomStart[]; extern u8 _Z2_PIRATESegmentRomEnd[];
extern u8 _Z2_PIRATE_room_00SegmentRomStart[]; extern u8 _Z2_PIRATE_room_00SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_01SegmentRomStart[]; extern u8 _Z2_PIRATE_room_01SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_02SegmentRomStart[]; extern u8 _Z2_PIRATE_room_02SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_03SegmentRomStart[]; extern u8 _Z2_PIRATE_room_03SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_04SegmentRomStart[]; extern u8 _Z2_PIRATE_room_04SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_05SegmentRomStart[]; extern u8 _Z2_PIRATE_room_05SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_06SegmentRomStart[]; extern u8 _Z2_PIRATE_room_06SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_07SegmentRomStart[]; extern u8 _Z2_PIRATE_room_07SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_08SegmentRomStart[]; extern u8 _Z2_PIRATE_room_08SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_09SegmentRomStart[]; extern u8 _Z2_PIRATE_room_09SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_10SegmentRomStart[]; extern u8 _Z2_PIRATE_room_10SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_11SegmentRomStart[]; extern u8 _Z2_PIRATE_room_11SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_12SegmentRomStart[]; extern u8 _Z2_PIRATE_room_12SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_13SegmentRomStart[]; extern u8 _Z2_PIRATE_room_13SegmentRomEnd[];
extern u8 _Z2_PIRATE_room_14SegmentRomStart[]; extern u8 _Z2_PIRATE_room_14SegmentRomEnd[];
extern u8 _Z2_SYATEKI_MORISegmentRomStart[]; extern u8 _Z2_SYATEKI_MORISegmentRomEnd[];
extern u8 _Z2_SYATEKI_MORI_room_00SegmentRomStart[]; extern u8 _Z2_SYATEKI_MORI_room_00SegmentRomEnd[];
extern u8 _Z2_SINKAISegmentRomStart[]; extern u8 _Z2_SINKAISegmentRomEnd[];
extern u8 _Z2_SINKAI_room_00SegmentRomStart[]; extern u8 _Z2_SINKAI_room_00SegmentRomEnd[];
extern u8 _Z2_YOUSEI_IZUMISegmentRomStart[]; extern u8 _Z2_YOUSEI_IZUMISegmentRomEnd[];
extern u8 _Z2_YOUSEI_IZUMI_room_00SegmentRomStart[]; extern u8 _Z2_YOUSEI_IZUMI_room_00SegmentRomEnd[];
extern u8 _Z2_YOUSEI_IZUMI_room_01SegmentRomStart[]; extern u8 _Z2_YOUSEI_IZUMI_room_01SegmentRomEnd[];
extern u8 _Z2_YOUSEI_IZUMI_room_02SegmentRomStart[]; extern u8 _Z2_YOUSEI_IZUMI_room_02SegmentRomEnd[];
extern u8 _Z2_YOUSEI_IZUMI_room_03SegmentRomStart[]; extern u8 _Z2_YOUSEI_IZUMI_room_03SegmentRomEnd[];
extern u8 _Z2_YOUSEI_IZUMI_room_04SegmentRomStart[]; extern u8 _Z2_YOUSEI_IZUMI_room_04SegmentRomEnd[];
extern u8 _Z2_KINSTA1SegmentRomStart[]; extern u8 _Z2_KINSTA1SegmentRomEnd[];
extern u8 _Z2_KINSTA1_room_00SegmentRomStart[]; extern u8 _Z2_KINSTA1_room_00SegmentRomEnd[];
extern u8 _Z2_KINSTA1_room_01SegmentRomStart[]; extern u8 _Z2_KINSTA1_room_01SegmentRomEnd[];
extern u8 _Z2_KINSTA1_room_02SegmentRomStart[]; extern u8 _Z2_KINSTA1_room_02SegmentRomEnd[];
extern u8 _Z2_KINSTA1_room_03SegmentRomStart[]; extern u8 _Z2_KINSTA1_room_03SegmentRomEnd[];
extern u8 _Z2_KINSTA1_room_04SegmentRomStart[]; extern u8 _Z2_KINSTA1_room_04SegmentRomEnd[];
extern u8 _Z2_KINSTA1_room_05SegmentRomStart[]; extern u8 _Z2_KINSTA1_room_05SegmentRomEnd[];
extern u8 _Z2_KINDAN2SegmentRomStart[]; extern u8 _Z2_KINDAN2SegmentRomEnd[];
extern u8 _Z2_KINDAN2_room_00SegmentRomStart[]; extern u8 _Z2_KINDAN2_room_00SegmentRomEnd[];
extern u8 _Z2_KINDAN2_room_01SegmentRomStart[]; extern u8 _Z2_KINDAN2_room_01SegmentRomEnd[];
extern u8 _Z2_KINDAN2_room_02SegmentRomStart[]; extern u8 _Z2_KINDAN2_room_02SegmentRomEnd[];
extern u8 _Z2_KINDAN2_room_03SegmentRomStart[]; extern u8 _Z2_KINDAN2_room_03SegmentRomEnd[];
extern u8 _Z2_KINDAN2_room_04SegmentRomStart[]; extern u8 _Z2_KINDAN2_room_04SegmentRomEnd[];
extern u8 _Z2_KINDAN2_room_05SegmentRomStart[]; extern u8 _Z2_KINDAN2_room_05SegmentRomEnd[];
extern u8 _Z2_TENMON_DAISegmentRomStart[]; extern u8 _Z2_TENMON_DAISegmentRomEnd[];
extern u8 _Z2_TENMON_DAI_room_00SegmentRomStart[]; extern u8 _Z2_TENMON_DAI_room_00SegmentRomEnd[];
extern u8 _Z2_TENMON_DAI_room_01SegmentRomStart[]; extern u8 _Z2_TENMON_DAI_room_01SegmentRomEnd[];
extern u8 _Z2_LAST_DEKUSegmentRomStart[]; extern u8 _Z2_LAST_DEKUSegmentRomEnd[];
extern u8 _Z2_LAST_DEKU_room_00SegmentRomStart[]; extern u8 _Z2_LAST_DEKU_room_00SegmentRomEnd[];
extern u8 _Z2_LAST_DEKU_room_01SegmentRomStart[]; extern u8 _Z2_LAST_DEKU_room_01SegmentRomEnd[];
extern u8 _Z2_22DEKUCITYSegmentRomStart[]; extern u8 _Z2_22DEKUCITYSegmentRomEnd[];
extern u8 _Z2_22DEKUCITY_room_00SegmentRomStart[]; extern u8 _Z2_22DEKUCITY_room_00SegmentRomEnd[];
extern u8 _Z2_22DEKUCITY_room_01SegmentRomStart[]; extern u8 _Z2_22DEKUCITY_room_01SegmentRomEnd[];
extern u8 _Z2_22DEKUCITY_room_02SegmentRomStart[]; extern u8 _Z2_22DEKUCITY_room_02SegmentRomEnd[];
extern u8 _Z2_KAJIYASegmentRomStart[]; extern u8 _Z2_KAJIYASegmentRomEnd[];
extern u8 _Z2_KAJIYA_room_00SegmentRomStart[]; extern u8 _Z2_KAJIYA_room_00SegmentRomEnd[];
extern u8 _Z2_00KEIKOKUSegmentRomStart[]; extern u8 _Z2_00KEIKOKUSegmentRomEnd[];
extern u8 _Z2_00KEIKOKU_room_00SegmentRomStart[]; extern u8 _Z2_00KEIKOKU_room_00SegmentRomEnd[];
extern u8 _Z2_POSTHOUSESegmentRomStart[]; extern u8 _Z2_POSTHOUSESegmentRomEnd[];
extern u8 _Z2_POSTHOUSE_room_00SegmentRomStart[]; extern u8 _Z2_POSTHOUSE_room_00SegmentRomEnd[];
extern u8 _Z2_LABOSegmentRomStart[]; extern u8 _Z2_LABOSegmentRomEnd[];
extern u8 _Z2_LABO_room_00SegmentRomStart[]; extern u8 _Z2_LABO_room_00SegmentRomEnd[];
extern u8 _Z2_DANPEI2TESTSegmentRomStart[]; extern u8 _Z2_DANPEI2TESTSegmentRomEnd[];
extern u8 _Z2_DANPEI2TEST_room_00SegmentRomStart[]; extern u8 _Z2_DANPEI2TEST_room_00SegmentRomEnd[];
extern u8 _Z2_DANPEI2TEST_room_01SegmentRomStart[]; extern u8 _Z2_DANPEI2TEST_room_01SegmentRomEnd[];
extern u8 _Z2_16GORON_HOUSESegmentRomStart[]; extern u8 _Z2_16GORON_HOUSESegmentRomEnd[];
extern u8 _Z2_16GORON_HOUSE_room_00SegmentRomStart[]; extern u8 _Z2_16GORON_HOUSE_room_00SegmentRomEnd[];
extern u8 _Z2_16GORON_HOUSE_room_01SegmentRomStart[]; extern u8 _Z2_16GORON_HOUSE_room_01SegmentRomEnd[];
extern u8 _Z2_33ZORACITYSegmentRomStart[]; extern u8 _Z2_33ZORACITYSegmentRomEnd[];
extern u8 _Z2_33ZORACITY_room_00SegmentRomStart[]; extern u8 _Z2_33ZORACITY_room_00SegmentRomEnd[];
extern u8 _Z2_8ITEMSHOPSegmentRomStart[]; extern u8 _Z2_8ITEMSHOPSegmentRomEnd[];
extern u8 _Z2_8ITEMSHOP_room_00SegmentRomStart[]; extern u8 _Z2_8ITEMSHOP_room_00SegmentRomEnd[];
extern u8 _Z2_F01SegmentRomStart[]; extern u8 _Z2_F01SegmentRomEnd[];
extern u8 _Z2_F01_room_00SegmentRomStart[]; extern u8 _Z2_F01_room_00SegmentRomEnd[];
extern u8 _Z2_INISIE_BSSegmentRomStart[]; extern u8 _Z2_INISIE_BSSegmentRomEnd[];
extern u8 _Z2_INISIE_BS_room_00SegmentRomStart[]; extern u8 _Z2_INISIE_BS_room_00SegmentRomEnd[];
extern u8 _Z2_30GYOSONSegmentRomStart[]; extern u8 _Z2_30GYOSONSegmentRomEnd[];
extern u8 _Z2_30GYOSON_room_00SegmentRomStart[]; extern u8 _Z2_30GYOSON_room_00SegmentRomEnd[];
extern u8 _Z2_31MISAKISegmentRomStart[]; extern u8 _Z2_31MISAKISegmentRomEnd[];
extern u8 _Z2_31MISAKI_room_00SegmentRomStart[]; extern u8 _Z2_31MISAKI_room_00SegmentRomEnd[];
extern u8 _Z2_TAKARAKUJISegmentRomStart[]; extern u8 _Z2_TAKARAKUJISegmentRomEnd[];
extern u8 _Z2_TAKARAKUJI_room_00SegmentRomStart[]; extern u8 _Z2_TAKARAKUJI_room_00SegmentRomEnd[];
extern u8 _Z2_TORIDESegmentRomStart[]; extern u8 _Z2_TORIDESegmentRomEnd[];
extern u8 _Z2_TORIDE_room_00SegmentRomStart[]; extern u8 _Z2_TORIDE_room_00SegmentRomEnd[];
extern u8 _Z2_FISHERMANSegmentRomStart[]; extern u8 _Z2_FISHERMANSegmentRomEnd[];
extern u8 _Z2_FISHERMAN_room_00SegmentRomStart[]; extern u8 _Z2_FISHERMAN_room_00SegmentRomEnd[];
extern u8 _Z2_GORONSHOPSegmentRomStart[]; extern u8 _Z2_GORONSHOPSegmentRomEnd[];
extern u8 _Z2_GORONSHOP_room_00SegmentRomStart[]; extern u8 _Z2_GORONSHOP_room_00SegmentRomEnd[];
extern u8 _Z2_DEKU_KINGSegmentRomStart[]; extern u8 _Z2_DEKU_KINGSegmentRomEnd[];
extern u8 _Z2_DEKU_KING_room_00SegmentRomStart[]; extern u8 _Z2_DEKU_KING_room_00SegmentRomEnd[];
extern u8 _Z2_LAST_GORONSegmentRomStart[]; extern u8 _Z2_LAST_GORONSegmentRomEnd[];
extern u8 _Z2_LAST_GORON_room_00SegmentRomStart[]; extern u8 _Z2_LAST_GORON_room_00SegmentRomEnd[];
extern u8 _Z2_LAST_GORON_room_01SegmentRomStart[]; extern u8 _Z2_LAST_GORON_room_01SegmentRomEnd[];
extern u8 _Z2_24KEMONOMITISegmentRomStart[]; extern u8 _Z2_24KEMONOMITISegmentRomEnd[];
extern u8 _Z2_24KEMONOMITI_room_00SegmentRomStart[]; extern u8 _Z2_24KEMONOMITI_room_00SegmentRomEnd[];
extern u8 _Z2_F01_BSegmentRomStart[]; extern u8 _Z2_F01_BSegmentRomEnd[];
extern u8 _Z2_F01_B_room_00SegmentRomStart[]; extern u8 _Z2_F01_B_room_00SegmentRomEnd[];
extern u8 _Z2_F01CSegmentRomStart[]; extern u8 _Z2_F01CSegmentRomEnd[];
extern u8 _Z2_F01C_room_00SegmentRomStart[]; extern u8 _Z2_F01C_room_00SegmentRomEnd[];
extern u8 _Z2_BOTISegmentRomStart[]; extern u8 _Z2_BOTISegmentRomEnd[];
extern u8 _Z2_BOTI_room_00SegmentRomStart[]; extern u8 _Z2_BOTI_room_00SegmentRomEnd[];
extern u8 _Z2_BOTI_room_01SegmentRomStart[]; extern u8 _Z2_BOTI_room_01SegmentRomEnd[];
extern u8 _Z2_HAKUGIN_BSSegmentRomStart[]; extern u8 _Z2_HAKUGIN_BSSegmentRomEnd[];
extern u8 _Z2_HAKUGIN_BS_room_00SegmentRomStart[]; extern u8 _Z2_HAKUGIN_BS_room_00SegmentRomEnd[];
extern u8 _Z2_20SICHITAISegmentRomStart[]; extern u8 _Z2_20SICHITAISegmentRomEnd[];
extern u8 _Z2_20SICHITAI_room_00SegmentRomStart[]; extern u8 _Z2_20SICHITAI_room_00SegmentRomEnd[];
extern u8 _Z2_20SICHITAI_room_01SegmentRomStart[]; extern u8 _Z2_20SICHITAI_room_01SegmentRomEnd[];
extern u8 _Z2_20SICHITAI_room_02SegmentRomStart[]; extern u8 _Z2_20SICHITAI_room_02SegmentRomEnd[];
extern u8 _Z2_21MITURINMAESegmentRomStart[]; extern u8 _Z2_21MITURINMAESegmentRomEnd[];
extern u8 _Z2_21MITURINMAE_room_00SegmentRomStart[]; extern u8 _Z2_21MITURINMAE_room_00SegmentRomEnd[];
extern u8 _Z2_LAST_ZORASegmentRomStart[]; extern u8 _Z2_LAST_ZORASegmentRomEnd[];
extern u8 _Z2_LAST_ZORA_room_00SegmentRomStart[]; extern u8 _Z2_LAST_ZORA_room_00SegmentRomEnd[];
extern u8 _Z2_11GORONNOSATO2SegmentRomStart[]; extern u8 _Z2_11GORONNOSATO2SegmentRomEnd[];
extern u8 _Z2_11GORONNOSATO2_room_00SegmentRomStart[]; extern u8 _Z2_11GORONNOSATO2_room_00SegmentRomEnd[];
extern u8 _Z2_11GORONNOSATO2_room_01SegmentRomStart[]; extern u8 _Z2_11GORONNOSATO2_room_01SegmentRomEnd[];
extern u8 _Z2_SEASegmentRomStart[]; extern u8 _Z2_SEASegmentRomEnd[];
extern u8 _Z2_SEA_room_00SegmentRomStart[]; extern u8 _Z2_SEA_room_00SegmentRomEnd[];
extern u8 _Z2_SEA_room_01SegmentRomStart[]; extern u8 _Z2_SEA_room_01SegmentRomEnd[];
extern u8 _Z2_SEA_room_02SegmentRomStart[]; extern u8 _Z2_SEA_room_02SegmentRomEnd[];
extern u8 _Z2_SEA_room_03SegmentRomStart[]; extern u8 _Z2_SEA_room_03SegmentRomEnd[];
extern u8 _Z2_SEA_room_04SegmentRomStart[]; extern u8 _Z2_SEA_room_04SegmentRomEnd[];
extern u8 _Z2_SEA_room_05SegmentRomStart[]; extern u8 _Z2_SEA_room_05SegmentRomEnd[];
extern u8 _Z2_SEA_room_06SegmentRomStart[]; extern u8 _Z2_SEA_room_06SegmentRomEnd[];
extern u8 _Z2_SEA_room_07SegmentRomStart[]; extern u8 _Z2_SEA_room_07SegmentRomEnd[];
extern u8 _Z2_SEA_room_08SegmentRomStart[]; extern u8 _Z2_SEA_room_08SegmentRomEnd[];
extern u8 _Z2_SEA_room_09SegmentRomStart[]; extern u8 _Z2_SEA_room_09SegmentRomEnd[];
extern u8 _Z2_SEA_room_10SegmentRomStart[]; extern u8 _Z2_SEA_room_10SegmentRomEnd[];
extern u8 _Z2_SEA_room_11SegmentRomStart[]; extern u8 _Z2_SEA_room_11SegmentRomEnd[];
extern u8 _Z2_SEA_room_12SegmentRomStart[]; extern u8 _Z2_SEA_room_12SegmentRomEnd[];
extern u8 _Z2_SEA_room_13SegmentRomStart[]; extern u8 _Z2_SEA_room_13SegmentRomEnd[];
extern u8 _Z2_SEA_room_14SegmentRomStart[]; extern u8 _Z2_SEA_room_14SegmentRomEnd[];
extern u8 _Z2_SEA_room_15SegmentRomStart[]; extern u8 _Z2_SEA_room_15SegmentRomEnd[];
extern u8 _Z2_35TAKISegmentRomStart[]; extern u8 _Z2_35TAKISegmentRomEnd[];
extern u8 _Z2_35TAKI_room_00SegmentRomStart[]; extern u8 _Z2_35TAKI_room_00SegmentRomEnd[];
extern u8 _Z2_REDEADSegmentRomStart[]; extern u8 _Z2_REDEADSegmentRomEnd[];
extern u8 _Z2_REDEAD_room_00SegmentRomStart[]; extern u8 _Z2_REDEAD_room_00SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_01SegmentRomStart[]; extern u8 _Z2_REDEAD_room_01SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_02SegmentRomStart[]; extern u8 _Z2_REDEAD_room_02SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_03SegmentRomStart[]; extern u8 _Z2_REDEAD_room_03SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_04SegmentRomStart[]; extern u8 _Z2_REDEAD_room_04SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_05SegmentRomStart[]; extern u8 _Z2_REDEAD_room_05SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_06SegmentRomStart[]; extern u8 _Z2_REDEAD_room_06SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_07SegmentRomStart[]; extern u8 _Z2_REDEAD_room_07SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_08SegmentRomStart[]; extern u8 _Z2_REDEAD_room_08SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_09SegmentRomStart[]; extern u8 _Z2_REDEAD_room_09SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_10SegmentRomStart[]; extern u8 _Z2_REDEAD_room_10SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_11SegmentRomStart[]; extern u8 _Z2_REDEAD_room_11SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_12SegmentRomStart[]; extern u8 _Z2_REDEAD_room_12SegmentRomEnd[];
extern u8 _Z2_REDEAD_room_13SegmentRomStart[]; extern u8 _Z2_REDEAD_room_13SegmentRomEnd[];
extern u8 _Z2_BANDROOMSegmentRomStart[]; extern u8 _Z2_BANDROOMSegmentRomEnd[];
extern u8 _Z2_BANDROOM_room_00SegmentRomStart[]; extern u8 _Z2_BANDROOM_room_00SegmentRomEnd[];
extern u8 _Z2_BANDROOM_room_01SegmentRomStart[]; extern u8 _Z2_BANDROOM_room_01SegmentRomEnd[];
extern u8 _Z2_BANDROOM_room_02SegmentRomStart[]; extern u8 _Z2_BANDROOM_room_02SegmentRomEnd[];
extern u8 _Z2_BANDROOM_room_03SegmentRomStart[]; extern u8 _Z2_BANDROOM_room_03SegmentRomEnd[];
extern u8 _Z2_BANDROOM_room_04SegmentRomStart[]; extern u8 _Z2_BANDROOM_room_04SegmentRomEnd[];
extern u8 _Z2_11GORONNOSATOSegmentRomStart[]; extern u8 _Z2_11GORONNOSATOSegmentRomEnd[];
extern u8 _Z2_11GORONNOSATO_room_00SegmentRomStart[]; extern u8 _Z2_11GORONNOSATO_room_00SegmentRomEnd[];
extern u8 _Z2_11GORONNOSATO_room_01SegmentRomStart[]; extern u8 _Z2_11GORONNOSATO_room_01SegmentRomEnd[];
extern u8 _Z2_GORON_HAKASegmentRomStart[]; extern u8 _Z2_GORON_HAKASegmentRomEnd[];
extern u8 _Z2_GORON_HAKA_room_00SegmentRomStart[]; extern u8 _Z2_GORON_HAKA_room_00SegmentRomEnd[];
extern u8 _Z2_SECOMSegmentRomStart[]; extern u8 _Z2_SECOMSegmentRomEnd[];
extern u8 _Z2_SECOM_room_00SegmentRomStart[]; extern u8 _Z2_SECOM_room_00SegmentRomEnd[];
extern u8 _Z2_SECOM_room_01SegmentRomStart[]; extern u8 _Z2_SECOM_room_01SegmentRomEnd[];
extern u8 _Z2_10YUKIYAMANOMURASegmentRomStart[]; extern u8 _Z2_10YUKIYAMANOMURASegmentRomEnd[];
extern u8 _Z2_10YUKIYAMANOMURA_room_00SegmentRomStart[]; extern u8 _Z2_10YUKIYAMANOMURA_room_00SegmentRomEnd[];
extern u8 _Z2_TOUGITESSegmentRomStart[]; extern u8 _Z2_TOUGITESSegmentRomEnd[];
extern u8 _Z2_TOUGITES_room_00SegmentRomStart[]; extern u8 _Z2_TOUGITES_room_00SegmentRomEnd[];
extern u8 _Z2_DANPEISegmentRomStart[]; extern u8 _Z2_DANPEISegmentRomEnd[];
extern u8 _Z2_DANPEI_room_00SegmentRomStart[]; extern u8 _Z2_DANPEI_room_00SegmentRomEnd[];
extern u8 _Z2_DANPEI_room_01SegmentRomStart[]; extern u8 _Z2_DANPEI_room_01SegmentRomEnd[];
extern u8 _Z2_DANPEI_room_02SegmentRomStart[]; extern u8 _Z2_DANPEI_room_02SegmentRomEnd[];
extern u8 _Z2_DANPEI_room_03SegmentRomStart[]; extern u8 _Z2_DANPEI_room_03SegmentRomEnd[];
extern u8 _Z2_DANPEI_room_04SegmentRomStart[]; extern u8 _Z2_DANPEI_room_04SegmentRomEnd[];
extern u8 _Z2_DANPEI_room_05SegmentRomStart[]; extern u8 _Z2_DANPEI_room_05SegmentRomEnd[];
extern u8 _Z2_DANPEI_room_06SegmentRomStart[]; extern u8 _Z2_DANPEI_room_06SegmentRomEnd[];
extern u8 _Z2_DANPEI_room_07SegmentRomStart[]; extern u8 _Z2_DANPEI_room_07SegmentRomEnd[];
extern u8 _Z2_DANPEI_room_08SegmentRomStart[]; extern u8 _Z2_DANPEI_room_08SegmentRomEnd[];
extern u8 _Z2_IKANAMAESegmentRomStart[]; extern u8 _Z2_IKANAMAESegmentRomEnd[];
extern u8 _Z2_IKANAMAE_room_00SegmentRomStart[]; extern u8 _Z2_IKANAMAE_room_00SegmentRomEnd[];
extern u8 _Z2_DOUJOUSegmentRomStart[]; extern u8 _Z2_DOUJOUSegmentRomEnd[];
extern u8 _Z2_DOUJOU_room_00SegmentRomStart[]; extern u8 _Z2_DOUJOU_room_00SegmentRomEnd[];
extern u8 _Z2_MUSICHOUSESegmentRomStart[]; extern u8 _Z2_MUSICHOUSESegmentRomEnd[];
extern u8 _Z2_MUSICHOUSE_room_00SegmentRomStart[]; extern u8 _Z2_MUSICHOUSE_room_00SegmentRomEnd[];
extern u8 _Z2_IKNINSIDESegmentRomStart[]; extern u8 _Z2_IKNINSIDESegmentRomEnd[];
extern u8 _Z2_IKNINSIDE_room_00SegmentRomStart[]; extern u8 _Z2_IKNINSIDE_room_00SegmentRomEnd[];
extern u8 _Z2_IKNINSIDE_room_01SegmentRomStart[]; extern u8 _Z2_IKNINSIDE_room_01SegmentRomEnd[];
extern u8 _Z2_MAP_SHOPSegmentRomStart[]; extern u8 _Z2_MAP_SHOPSegmentRomEnd[];
extern u8 _Z2_MAP_SHOP_room_00SegmentRomStart[]; extern u8 _Z2_MAP_SHOP_room_00SegmentRomEnd[];
extern u8 _Z2_F40SegmentRomStart[]; extern u8 _Z2_F40SegmentRomEnd[];
extern u8 _Z2_F40_room_00SegmentRomStart[]; extern u8 _Z2_F40_room_00SegmentRomEnd[];
extern u8 _Z2_F41SegmentRomStart[]; extern u8 _Z2_F41SegmentRomEnd[];
extern u8 _Z2_F41_room_00SegmentRomStart[]; extern u8 _Z2_F41_room_00SegmentRomEnd[];
extern u8 _Z2_10YUKIYAMANOMURA2SegmentRomStart[]; extern u8 _Z2_10YUKIYAMANOMURA2SegmentRomEnd[];
extern u8 _Z2_10YUKIYAMANOMURA2_room_00SegmentRomStart[]; extern u8 _Z2_10YUKIYAMANOMURA2_room_00SegmentRomEnd[];
extern u8 _Z2_10YUKIYAMANOMURA2_room_01SegmentRomStart[]; extern u8 _Z2_10YUKIYAMANOMURA2_room_01SegmentRomEnd[];
extern u8 _Z2_14YUKIDAMANOMITISegmentRomStart[]; extern u8 _Z2_14YUKIDAMANOMITISegmentRomEnd[];
extern u8 _Z2_14YUKIDAMANOMITI_room_00SegmentRomStart[]; extern u8 _Z2_14YUKIDAMANOMITI_room_00SegmentRomEnd[];
extern u8 _Z2_12HAKUGINMAESegmentRomStart[]; extern u8 _Z2_12HAKUGINMAESegmentRomEnd[];
extern u8 _Z2_12HAKUGINMAE_room_00SegmentRomStart[]; extern u8 _Z2_12HAKUGINMAE_room_00SegmentRomEnd[];
extern u8 _Z2_17SETUGENSegmentRomStart[]; extern u8 _Z2_17SETUGENSegmentRomEnd[];
extern u8 _Z2_17SETUGEN_room_00SegmentRomStart[]; extern u8 _Z2_17SETUGEN_room_00SegmentRomEnd[];
extern u8 __1455_0x01d35b80SegmentRomStart[]; extern u8 __1455_0x01d35b80SegmentRomEnd[];
extern u8 _Z2_17SETUGEN2_room_00SegmentRomStart[]; extern u8 _Z2_17SETUGEN2_room_00SegmentRomEnd[];
extern u8 _Z2_SEA_BSSegmentRomStart[]; extern u8 _Z2_SEA_BSSegmentRomEnd[];
extern u8 _Z2_SEA_BS_room_00SegmentRomStart[]; extern u8 _Z2_SEA_BS_room_00SegmentRomEnd[];
extern u8 _Z2_RANDOMSegmentRomStart[]; extern u8 _Z2_RANDOMSegmentRomEnd[];
extern u8 _Z2_RANDOM_room_00SegmentRomStart[]; extern u8 _Z2_RANDOM_room_00SegmentRomEnd[];
extern u8 _Z2_RANDOM_room_01SegmentRomStart[]; extern u8 _Z2_RANDOM_room_01SegmentRomEnd[];
extern u8 _Z2_RANDOM_room_02SegmentRomStart[]; extern u8 _Z2_RANDOM_room_02SegmentRomEnd[];
extern u8 _Z2_RANDOM_room_03SegmentRomStart[]; extern u8 _Z2_RANDOM_room_03SegmentRomEnd[];
extern u8 _Z2_RANDOM_room_04SegmentRomStart[]; extern u8 _Z2_RANDOM_room_04SegmentRomEnd[];
extern u8 _Z2_RANDOM_room_05SegmentRomStart[]; extern u8 _Z2_RANDOM_room_05SegmentRomEnd[];
extern u8 _Z2_YADOYASegmentRomStart[]; extern u8 _Z2_YADOYASegmentRomEnd[];
extern u8 _Z2_YADOYA_room_00SegmentRomStart[]; extern u8 _Z2_YADOYA_room_00SegmentRomEnd[];
extern u8 _Z2_YADOYA_room_01SegmentRomStart[]; extern u8 _Z2_YADOYA_room_01SegmentRomEnd[];
extern u8 _Z2_YADOYA_room_02SegmentRomStart[]; extern u8 _Z2_YADOYA_room_02SegmentRomEnd[];
extern u8 _Z2_YADOYA_room_03SegmentRomStart[]; extern u8 _Z2_YADOYA_room_03SegmentRomEnd[];
extern u8 _Z2_YADOYA_room_04SegmentRomStart[]; extern u8 _Z2_YADOYA_room_04SegmentRomEnd[];
extern u8 _Z2_KONPEKI_ENTSegmentRomStart[]; extern u8 _Z2_KONPEKI_ENTSegmentRomEnd[];
extern u8 _Z2_KONPEKI_ENT_room_00SegmentRomStart[]; extern u8 _Z2_KONPEKI_ENT_room_00SegmentRomEnd[];
extern u8 _Z2_INSIDETOWERSegmentRomStart[]; extern u8 _Z2_INSIDETOWERSegmentRomEnd[];
extern u8 _Z2_INSIDETOWER_room_00SegmentRomStart[]; extern u8 _Z2_INSIDETOWER_room_00SegmentRomEnd[];
extern u8 _Z2_INSIDETOWER_room_01SegmentRomStart[]; extern u8 _Z2_INSIDETOWER_room_01SegmentRomEnd[];
extern u8 _Z2_26SARUNOMORISegmentRomStart[]; extern u8 _Z2_26SARUNOMORISegmentRomEnd[];
extern u8 _Z2_26SARUNOMORI_room_00SegmentRomStart[]; extern u8 _Z2_26SARUNOMORI_room_00SegmentRomEnd[];
extern u8 _Z2_26SARUNOMORI_room_01SegmentRomStart[]; extern u8 _Z2_26SARUNOMORI_room_01SegmentRomEnd[];
extern u8 _Z2_26SARUNOMORI_room_02SegmentRomStart[]; extern u8 _Z2_26SARUNOMORI_room_02SegmentRomEnd[];
extern u8 _Z2_26SARUNOMORI_room_03SegmentRomStart[]; extern u8 _Z2_26SARUNOMORI_room_03SegmentRomEnd[];
extern u8 _Z2_26SARUNOMORI_room_04SegmentRomStart[]; extern u8 _Z2_26SARUNOMORI_room_04SegmentRomEnd[];
extern u8 _Z2_26SARUNOMORI_room_05SegmentRomStart[]; extern u8 _Z2_26SARUNOMORI_room_05SegmentRomEnd[];
extern u8 _Z2_26SARUNOMORI_room_06SegmentRomStart[]; extern u8 _Z2_26SARUNOMORI_room_06SegmentRomEnd[];
extern u8 _Z2_26SARUNOMORI_room_07SegmentRomStart[]; extern u8 _Z2_26SARUNOMORI_room_07SegmentRomEnd[];
extern u8 _Z2_26SARUNOMORI_room_08SegmentRomStart[]; extern u8 _Z2_26SARUNOMORI_room_08SegmentRomEnd[];
extern u8 _Z2_LOST_WOODSSegmentRomStart[]; extern u8 _Z2_LOST_WOODSSegmentRomEnd[];
extern u8 _Z2_LOST_WOODS_room_00SegmentRomStart[]; extern u8 _Z2_LOST_WOODS_room_00SegmentRomEnd[];
extern u8 _Z2_LOST_WOODS_room_01SegmentRomStart[]; extern u8 _Z2_LOST_WOODS_room_01SegmentRomEnd[];
extern u8 _Z2_LOST_WOODS_room_02SegmentRomStart[]; extern u8 _Z2_LOST_WOODS_room_02SegmentRomEnd[];
extern u8 _Z2_LAST_LINKSegmentRomStart[]; extern u8 _Z2_LAST_LINKSegmentRomEnd[];
extern u8 _Z2_LAST_LINK_room_00SegmentRomStart[]; extern u8 _Z2_LAST_LINK_room_00SegmentRomEnd[];
extern u8 _Z2_LAST_LINK_room_01SegmentRomStart[]; extern u8 _Z2_LAST_LINK_room_01SegmentRomEnd[];
extern u8 _Z2_LAST_LINK_room_02SegmentRomStart[]; extern u8 _Z2_LAST_LINK_room_02SegmentRomEnd[];
extern u8 _Z2_LAST_LINK_room_03SegmentRomStart[]; extern u8 _Z2_LAST_LINK_room_03SegmentRomEnd[];
extern u8 _Z2_LAST_LINK_room_04SegmentRomStart[]; extern u8 _Z2_LAST_LINK_room_04SegmentRomEnd[];
extern u8 _Z2_LAST_LINK_room_05SegmentRomStart[]; extern u8 _Z2_LAST_LINK_room_05SegmentRomEnd[];
extern u8 _Z2_LAST_LINK_room_06SegmentRomStart[]; extern u8 _Z2_LAST_LINK_room_06SegmentRomEnd[];
extern u8 _Z2_LAST_LINK_room_07SegmentRomStart[]; extern u8 _Z2_LAST_LINK_room_07SegmentRomEnd[];
extern u8 _Z2_SOUGENSegmentRomStart[]; extern u8 _Z2_SOUGENSegmentRomEnd[];
extern u8 _Z2_SOUGEN_room_00SegmentRomStart[]; extern u8 _Z2_SOUGEN_room_00SegmentRomEnd[];
extern u8 _Z2_BOMYASegmentRomStart[]; extern u8 _Z2_BOMYASegmentRomEnd[];
extern u8 _Z2_BOMYA_room_00SegmentRomStart[]; extern u8 _Z2_BOMYA_room_00SegmentRomEnd[];
extern u8 _Z2_KYOJINNOMASegmentRomStart[]; extern u8 _Z2_KYOJINNOMASegmentRomEnd[];
extern u8 _Z2_KYOJINNOMA_room_00SegmentRomStart[]; extern u8 _Z2_KYOJINNOMA_room_00SegmentRomEnd[];
extern u8 _Z2_KOEPONARACESegmentRomStart[]; extern u8 _Z2_KOEPONARACESegmentRomEnd[];
extern u8 _Z2_KOEPONARACE_room_00SegmentRomStart[]; extern u8 _Z2_KOEPONARACE_room_00SegmentRomEnd[];
extern u8 _Z2_GORONRACESegmentRomStart[]; extern u8 _Z2_GORONRACESegmentRomEnd[];
extern u8 _Z2_GORONRACE_room_00SegmentRomStart[]; extern u8 _Z2_GORONRACE_room_00SegmentRomEnd[];
extern u8 _Z2_TOWNSegmentRomStart[]; extern u8 _Z2_TOWNSegmentRomEnd[];
extern u8 _Z2_TOWN_room_00SegmentRomStart[]; extern u8 _Z2_TOWN_room_00SegmentRomEnd[];
extern u8 _Z2_ICHIBASegmentRomStart[]; extern u8 _Z2_ICHIBASegmentRomEnd[];
extern u8 _Z2_ICHIBA_room_00SegmentRomStart[]; extern u8 _Z2_ICHIBA_room_00SegmentRomEnd[];
extern u8 _Z2_BACKTOWNSegmentRomStart[]; extern u8 _Z2_BACKTOWNSegmentRomEnd[];
extern u8 _Z2_BACKTOWN_room_00SegmentRomStart[]; extern u8 _Z2_BACKTOWN_room_00SegmentRomEnd[];
extern u8 _Z2_CLOCKTOWERSegmentRomStart[]; extern u8 _Z2_CLOCKTOWERSegmentRomEnd[];
extern u8 _Z2_CLOCKTOWER_room_00SegmentRomStart[]; extern u8 _Z2_CLOCKTOWER_room_00SegmentRomEnd[];
extern u8 _Z2_ALLEYSegmentRomStart[]; extern u8 _Z2_ALLEYSegmentRomEnd[];
extern u8 _Z2_ALLEY_room_00SegmentRomStart[]; extern u8 _Z2_ALLEY_room_00SegmentRomEnd[];
extern u8 _SPOT00SegmentRomStart[]; extern u8 _SPOT00SegmentRomEnd[];
extern u8 _SPOT00_room_00SegmentRomStart[]; extern u8 _SPOT00_room_00SegmentRomEnd[];
extern u8 _KAKUSIANASegmentRomStart[]; extern u8 _KAKUSIANASegmentRomEnd[];
extern u8 _KAKUSIANA_room_00SegmentRomStart[]; extern u8 _KAKUSIANA_room_00SegmentRomEnd[];
extern u8 _KAKUSIANA_room_01SegmentRomStart[]; extern u8 _KAKUSIANA_room_01SegmentRomEnd[];
extern u8 _KAKUSIANA_room_02SegmentRomStart[]; extern u8 _KAKUSIANA_room_02SegmentRomEnd[];
extern u8 _KAKUSIANA_room_03SegmentRomStart[]; extern u8 _KAKUSIANA_room_03SegmentRomEnd[];
extern u8 _KAKUSIANA_room_04SegmentRomStart[]; extern u8 _KAKUSIANA_room_04SegmentRomEnd[];
extern u8 _KAKUSIANA_room_05SegmentRomStart[]; extern u8 _KAKUSIANA_room_05SegmentRomEnd[];
extern u8 _KAKUSIANA_room_06SegmentRomStart[]; extern u8 _KAKUSIANA_room_06SegmentRomEnd[];
extern u8 _KAKUSIANA_room_07SegmentRomStart[]; extern u8 _KAKUSIANA_room_07SegmentRomEnd[];
extern u8 _KAKUSIANA_room_08SegmentRomStart[]; extern u8 _KAKUSIANA_room_08SegmentRomEnd[];
extern u8 _KAKUSIANA_room_09SegmentRomStart[]; extern u8 _KAKUSIANA_room_09SegmentRomEnd[];
extern u8 _KAKUSIANA_room_10SegmentRomStart[]; extern u8 _KAKUSIANA_room_10SegmentRomEnd[];
extern u8 _KAKUSIANA_room_11SegmentRomStart[]; extern u8 _KAKUSIANA_room_11SegmentRomEnd[];
extern u8 _KAKUSIANA_room_12SegmentRomStart[]; extern u8 _KAKUSIANA_room_12SegmentRomEnd[];
extern u8 _KAKUSIANA_room_13SegmentRomStart[]; extern u8 _KAKUSIANA_room_13SegmentRomEnd[];
extern u8 _KAKUSIANA_room_14SegmentRomStart[]; extern u8 _KAKUSIANA_room_14SegmentRomEnd[];
extern u8 _bump_texture_staticSegmentRomStart[]; extern u8 _bump_texture_staticSegmentRomEnd[];
extern s32 D_04029CB0;
extern s32 D_04029CF0;
extern s32 D_0E000048;
extern s32 D_0E000088;
extern s32 D_0E000140;
extern s32 D_0E0001C8;
extern s32 D_0E0002C8;
extern Gfx object_ikana_obj_001100[];
extern AnimatedTexture object_ikana_obj_001228[];
extern Gfx object_fu_kaiten_0005D0[];
extern BgMeshHeader object_fu_kaiten_002D30;
extern void* D_04061FC0[];
extern void* D_04061FE0[];
extern void* D_04062000[];
extern void* D_04062040[];
extern void* D_04062020[];
extern void* D_04062060[];
extern void* D_04062000[];
extern Gfx D_040622C0[];
extern u32 boot_text_start;
extern u32 boot_text_end;
extern u32 boot_data_start;
extern u32 boot_data_end;
extern u32 boot_rodata_start;
extern u32 boot_rodata_end;
extern u32 boot_bss_start;
extern u32 boot_bss_end;
extern u32 code_text_start;
extern u32 code_text_end;
extern u32 code_data_start;
extern u32 code_data_end;
extern u32 code_rodata_start;
extern u32 code_rodata_end;
extern u32 code_bss_start;
extern u32 code_bss_end;
extern s32 osTvType;
extern s32 osRomType;
extern s32 osRomBase;
extern s32 osResetType;
extern s32 osCicId;
extern s32 osVersion;
extern s32 osMemSize;
extern s32 D_8000031C;
extern s32 D_80000500;
extern s32 D_80025D00;
extern s8 D_800969C0;
extern u8 D_80096B20;
extern vu8 gViConfigUseDefault;
extern u8 gViConfigAdditionalScanLines;
extern u32 gViConfigFeatures;
extern f32 gViConfigXScale;
extern f32 gViConfigYScale;
extern OSPiHandle* gCartHandle;
extern s32 sDmaMgrDmaBuffSize;
extern vs32 gIrqMgrResetStatus;
extern volatile OSTime sIrqMgrResetTime;
extern volatile OSTime sIrqMgrRetraceTime;
extern s32 sIrqMgrRetraceCount;
extern char* D_80096B80[18];
extern char* D_80096BC8[6];
extern FaultDrawer* sFaultDrawContext;
extern FaultDrawer sFaultDrawerDefault;
extern s32 D_80096C30;
extern StackEntry* sStackInfoListStart;
extern StackEntry* sStackInfoListEnd;
extern u32 randSeed;
extern OSViMode osViModeNtscHpf1;
extern OSViMode osViModePalLan1;
extern s16 sintable[1024];
extern OSThread* __osThreadTail;
extern OSThread* __osRunQueue;
extern OSThread* __osActiveQueue;
extern OSThread* __osRunningThread;
extern OSThread* __osFaultedThread;
extern u32 __osSiAccessQueueEnabled;
extern s32 D_80097E40;
extern u64 osClockRate;
extern s32 osViClock;
extern s32 __osShutdown;
extern s32 __OSGlobalIntMask;
extern OSDevMgr __osPiDevMgr;
extern OSPiHandle* __osPiTable;
extern void* D_80097E90;
extern s32 __osPiAccessQueueEnabled;
extern OSViMode osViModeNtscHpn1;
extern s32 D_80097F10;
extern char spaces[];
extern char zeroes[];
extern OSTimer* __osTimerList;
extern float D_80097F90;
extern OSViMode osViModeNtscLan1;
extern OSViMode osViModeMpalLan1;
extern __OSViContext D_80098060[2];
extern __OSViContext* __osViCurr;
extern __OSViContext* __osViNext;
extern OSViMode D_800980E0;
extern char ldigs[];
extern char udigs[];
extern OSDevMgr __osViDevMgr;
extern s32 D_8009817C;
extern char bootThreadName[];
extern char idleThreadName[];
extern char irqmgrThreadName[];
extern char mainThreadName[];
extern f32 D_800981B0;
extern char D_800981C0[];
extern char dmamgrString800981C4[];
extern char dmamgrString800981D4[];
extern char dmamgrString800981E4[];
extern char dmamgrString800981F4[];
extern char dmamgrThreadName[];
extern char D_80098210[];
extern char yaz0String80098220[];
extern char yaz0String8009823C[];
extern char D_80098280[];
extern char D_80098290[];
extern char D_800982A4[];
extern char D_800982B0[];
extern char D_800982BC[];
extern char D_800982D0[];
extern char D_800982E8[];
extern char D_80098300[];
extern char D_80098318[];
extern char D_80098330[];
extern char D_80098344[];
extern char D_80098358[];
extern char D_80098370[];
extern char D_80098388[];
extern char D_800983A0[];
extern char D_800983B8[];
extern char D_800983CC[];
extern char D_800983DC[];
extern char D_800983F8[];
extern char D_80098414[];
extern char D_8009842C[];
extern char D_80098448[];
extern char D_80098460[];
extern char D_80098474[];
extern char D_80098488[];
extern char D_80098494[];
extern char D_800984A0[];
extern char D_800984B4[55];
extern char D_800984EC[54];
extern char D_80098524[71];
extern char D_8009856C[74];
extern char D_800985B8[];
extern char D_800985C8[];
extern char D_800985DC[];
extern char D_800985EC[];
extern char D_80098600[];
extern char D_80098610[];
extern char D_80098618[];
extern char D_8009861C[];
extern char D_8009862C[];
extern char D_80098634[];
extern char D_80098648[];
extern char D_80098664[];
extern char D_80098680[];
extern char D_8009869C[];
extern char D_800986B8[];
extern char D_800986D4[];
extern char D_800986F0[];
extern char D_8009870C[];
extern char D_80098728[];
extern char D_80098744[];
extern char D_80098760[];
extern char D_80098780[];
extern char D_80098784[];
extern char D_80098788[];
extern char D_8009878C[];
extern char D_80098790[];
extern char D_80098794[];
extern char D_80098798[];
extern char D_8009879C[];
extern char D_800987A0[];
extern char D_800987A4[];
extern char D_800987B0[];
extern char D_800987B4[];
extern char D_800987CC[];
extern char D_800987EC[];
extern char D_8009880C[];
extern char D_8009882C[];
extern char D_8009884C[];
extern char D_8009886C[];
extern char D_8009888C[];
extern char D_800988AC[];
extern char D_800988CC[];
extern char D_800988EC[];
extern char D_8009890C[];
extern char D_8009892C[];
extern char D_80098930[];
extern char D_80098934[];
extern char D_80098938[];
extern char D_8009893C[];
extern char D_80098940[];
extern char D_80098944[];
extern char D_80098948[];
extern char D_8009894C[];
extern char D_80098950[];
extern char D_80098954[];
extern char D_8009895C[];
extern char D_80098968[];
extern char D_80098970[];
extern char D_80098978[];
extern char D_80098980[];
extern char D_8009898C[];
extern char D_800989A4[];
extern char D_800989B0[];
extern char D_800989BC[];
extern char D_800989CC[];
extern char D_800989D8[];
extern char D_800989F4[];
extern char D_80098A00[];
extern char D_80098A0C[];
extern char D_80098A1C[];
extern char D_80098A20[34];
extern char D_80098A44[];
extern char D_80098A68[];
extern char D_80098A88[53];
extern char D_80098AC0[49];
extern char D_80098AF4[51];
extern char D_80098B28[];
extern char D_80098B4C[];
extern char D_80098B68[];
extern char D_80098B84[];
extern char D_80098BA0[];
extern char D_80098BBC[];
extern char faultThreadName[];
extern char D_80098BE0[];
extern char D_80098BF8[];
extern char D_80098BFC[];
extern char D_80098C04[];
extern char D_80098C08[];
extern char D_80098C10[];
extern char D_80098C28[];
extern char D_80098C2C[];
extern char D_80098C34[];
extern char D_80098C38[];
extern char D_80098C40[];
extern u8 faultDrawFont[8][128];
extern char D_80099050[];
extern char D_80099054[];
extern char D_8009905C[];
extern char D_80099064[];
extern char D_80099070[];
extern char D_80099078[];
extern char D_8009907C[];
extern char D_80099080[];
extern char D_800990B0[];
extern f32 D_800990C0[9];
extern f32 D_800990E4;
extern f32 D_800990E8;
extern f32 D_800990EC;
extern f32 D_800990F0;
extern f32 D_800990F4;
extern f32 D_800990F8;
extern f32 D_800990FC;
extern f32 D_80099100;
extern f32 D_80099104;
extern f32 D_80099108;
extern f32 D_8009910C;
extern u16 D_800991A0[64];
extern du P[5];
extern du rpi;
extern du pihi;
extern du pilo;
extern fu zero;
extern void* __osIntTable;
extern f64 D_800992C0;
extern f64 D_800992F0;
extern f64 D_800992F8;
extern char D_80099300[];
extern char D_80099304[];
extern unsigned int D_8009930C[6];
extern f32 D_80099400;
extern f64 D_80099428;
extern f64 D_80099430;
extern f64 D_80099438;
extern f32 __libm_qnan_f;
extern f64 D_80099460[9];
extern char D_800994A8[];
extern char D_800994AC[];
extern char D_800994B0[];
extern f64 D_800994B8;
extern f64 D_800994C0;
extern f64 D_800994C8;
extern char D_800994D0[];
extern char D_800994DC[];
extern StackEntry sBootThreadInfo;
extern OSThread sIdleThread;
extern u8 sIdleThreadStack[1024];
extern StackEntry sIdleThreadInfo;
extern u8 sBootThreadStack[1024];
extern IrqMgr irqmgrContext;
extern u8 irqmgrStack[1280];
extern StackEntry irqmgrStackEntry;
extern OSThread mainOSThread;
extern u8 mainStack[2304];
extern StackEntry mainStackEntry;
extern OSMesg D_8009B160[50];
extern OSMesgQueue D_8009B228;
extern OSViMode D_8009B240;
extern u8 D_8009B290;
extern StackEntry dmamgrStackEntry;
extern u16 numDmaEntries;
extern OSMesgQueue dmamgrMsq;
extern OSMesg dmamgrMsqMessages[32];
extern OSThread dmamgrOSThread;
extern u8 dmamgrStack[1280];
extern u8 sYaz0DataBuffer[0x400];
extern u8* sYaz0CurDataEnd;
extern u32 sYaz0CurRomStart;
extern u32 sYaz0CurSize;
extern u8* sYaz0MaxPtr;
extern u8* D_8009BE20;
extern s32 D_8009BE30;
extern s32 D_8009BE34;
extern FaultClient romInfoFaultClient;
extern FaultThreadStruct* faultCtxt;
extern f32 D_8009BE54;
extern u32 faultCustomOptions;
extern u32 faultCopyToLog;
extern u8 faultStack[1536];
extern StackEntry faultStackEntry;
extern FaultThreadStruct faultContextStruct;
extern FaultDrawer sFaultDrawerStruct;
extern Arena startHeap;
extern f32 randLast;
extern OSTask tmp_task;
extern OSMesg siAccessBuf[1];
extern OSMesgQueue __osSiAccessQueue;
extern OSPifRam __osContPifRam;
extern u8 __osContLastCmd;
extern u8 __osMaxControllers;
extern OSMesgQueue D_8009CF38;
extern OSMesg D_8009CF50[1];
extern s32 D_8009CF70;
extern OSThread __osThreadSave;
extern OSPiHandle D_8009D130;
extern OSPiHandle D_8009D1A8;
extern OSThread D_8009D220;
extern u8 piManagerStack[4096];
extern OSMesgQueue D_8009E3D0;
extern OSMesg D_8009E3E8[1];
extern OSMesg D_8009E3F0[1];
extern OSMesgQueue __osPiAccessQueue;
extern __OSEventState __osEventStateTab[16];
extern OSTimer D_8009E590;
extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;
extern u32 __osViIntrCount;
extern u32 __osTimerCounter;
extern OSPifRam __osPfsPifRam;
extern OSPiHandle CartRomHandle;
extern OSThread viThread;
extern u8 viThreadStack[4096];
extern OSMesgQueue viEventQueue;
extern OSMesg viEventBuf[5];
extern OSIoMesg viRetraceMsg;
extern OSIoMesg viCounterMsg;
extern u16 vimgrRetrace;
extern DmaEntry dmadata[1568];
extern ActorInit En_A_Obj_InitVars;
extern ColliderCylinderInit enAObjCylinderInit;
extern InitChainEntry enAObjInitVar;
extern u32 enAObjDisplayLists[2];
extern ActorInit En_Item00_InitVars;
extern ColliderCylinderInit enItem00CylinderInit;
extern InitChainEntry enItem00InitVars[1];
extern Vec3f D_801ADF18;
extern Vec3f D_801ADF24;
extern u8 D_801ADF74[272];
extern u8 D_801AE084[272];
extern s32 D_801AE194[32];
extern u8 D_801AE214[32];
extern void* D_801AE260[3];
extern F3DVertex sEffectShieldParticleVertices[4];
extern EffInfo sEffInfoTable[5];
extern EffectTableInfo EffectSS2Info;
extern ParticleOverlay particleOverlayTable[39];
extern void* D_801AE8F0;
extern ColorRGBA8 D_801AEC80;
extern s801AEC84 D_801AEC84[13];
extern f32 actorMovementScale;
extern f32 D_801AECF0;
extern f32 D_801AECF4;
extern ColorRGBA8 actorDefaultHitColor;
extern ActorOverlay gActorOverlayTable[ACTOR_ID_MAX];
extern s32 gMaxActorId;
extern u32 D_801B4620[32];
extern u16 D_801B46A0[16];
extern u8 D_801B46C0[16];
extern s16 bgSpecialSceneParamsDefault[1];
extern BgSpecialSceneMaxMemory bgSpecialSceneMaxMemory[1];
extern BgSpecialSceneMeshSubdivision bgSpecialSceneMeshSubdivisions[3];
extern BgSpecialSceneMaxObjects bgSpecialSceneMaxObjects[1];
extern CameraStateParams cameraStates[91];
extern void* D_801B9CE4;
extern camera_update_func cameraUpdateFuncs[71];
extern s32 D_801B9F10;
extern DamageTable sDamageTablePresets[23];
extern f32 damageMultipliers[16];
extern Collider defaultCollider;
extern ColliderTouch defaultColliderTouch;
extern ColliderBump defaultColliderBump;
extern ColliderInfo defaultColliderInfo;
extern ColliderJntSphElementDim defaultColliderJntSphElementDim;
extern Cylinder16 defaultColliderCylinderDim;
extern TriNorm defaultColliderTrisElementDim;
extern ColliderQuadDim defaultColliderQuadDim;
extern Vec3f defaultLinePoint;
extern ColChkResetFunc sATResetFuncs[COLSHAPE_MAX];
extern ColChkResetFunc sACResetFuncs[COLSHAPE_MAX];
extern ColChkResetFunc sOCResetFuncs[COLSHAPE_MAX];
extern ColChkBloodFunc sBloodFuncs[6];
extern HitInfo sHitInfo[14];
extern ColChkApplyFunc sColChkApplyFuncs[COLSHAPE_MAX];
extern ColChkVsFunc sACVsFuncs[COLSHAPE_MAX][COLSHAPE_MAX];
extern ColChkVsFunc sOCVsFuncs[COLSHAPE_MAX][COLSHAPE_MAX];
extern CollisionCheckInfo defaultColChkInfo;
extern ColChkApplyFunc sApplyDamageFuncs[COLSHAPE_MAX];
extern ColChkLineFunc sOCLineCheckFuncs[COLSHAPE_MAX];
extern EffShieldParticleInit shieldParticleInitMetal;
extern EffShieldParticleInit shieldParticleInitWood;
extern s8 D_801BA550;
extern cutscene_update_func sCsStateHandlers1[5];
extern cutscene_update_func sCsStateHandlers2[5];
extern s801BB170 D_801BB170[118];
extern Gfx D_801BC240[9];
extern Gfx D_801BC288[3];
extern ActorCutscene actorCutscenesGlobalCutscenes[8];
extern s16 actorCutsceneCurrent;
extern s16 actorCutsceneCurrentLength;
extern s16 actorCutsceneEnding;
extern s16 actorCutsceneCurrentCamera;
extern Actor* actorCutsceneCurrentCutsceneActor;
extern GlobalContext* actorCutscenesGlobalCtxt;
extern s16 actorCutsceneReturnCamera;
extern s16 D_801BD8C6;
extern ColliderCylinderInit fireObjCollisionInit;
extern FireObjLightParams D_801BD8FC[2];
extern GameStateOverlay initialGameStateInfo;
extern GameStateOverlay D_801BD940;
extern GameStateOverlay titleGameStateInfo;
extern GameStateOverlay mainGameStateInfo;
extern GameStateOverlay openingGameStateInfo;
extern GameStateOverlay fileChooseGameStateInfo;
extern GameStateOverlay daytelopGameStateInfo;
extern u8 kanfontOrdering[92];
extern actor_init_var_func actorInitVarFuncs[11];
extern light_map_positional_func lightPositionalMapFuncs[3];
extern light_map_directional_func lightDirectionalMapFuncs[3];
extern void* D_801BEC14;
extern void* D_801BF5C0;
extern void* D_801C02F8;
extern void* D_801C0870;
extern void* D_801C095C;
extern void* D_801C0AF4;
extern void* D_801C0AFC;
extern void* D_801C0B04;
extern void* D_801C0B0C;
extern s16 sQuakeRequestCount;
extern quake_callback_func sQuakeCallbacks[7];
extern s16 D_801C0EE4;
extern s16 D_801C0EE8;
extern s16 D_801C0EEC;
extern Gfx sSetupDL[438];
extern Gfx sFillSetupDL[12];
extern Gfx gEmptyDL[1];
extern Vec3f D_801C1D10;
extern room_draw_func roomDrawFuncs[4];
extern u32 gBitFlags[32];
extern void* D_801C1E6C;
extern SceneIdList scenesPerMapArea[11];
extern ObjectFileTableEntry D_801C2650[2];
extern ObjectFileTableEntry D_801C2660[9];
extern scene_header_func sceneHeaderFuncTable[31];
extern s16 D_801C2730[8];
extern ObjectFileTableEntry objectFileTable[643];
extern Gfx gSceneProcDefaultDl[11];
extern global_context_func gSceneProcSceneDrawFuncs[8];
extern scene_proc_draw_func gSceneProcDrawFuncs[6];
extern Gfx D_801C3BF0[4];
extern Gfx D_801C3C10[4];
extern Gfx D_801C3C30[4];
extern Gfx* D_801C3C50[3];
extern Gfx D_801C3C60[2];
extern Gfx D_801C3C70[2];
extern Gfx* D_801C3C80[2];
extern Gfx D_801C3C88[2];
extern SceneTableEntry gSceneTable[113];
extern void* D_801C43BC;
extern void* D_801C442C;
extern void* D_801C4468;
extern void* D_801C457C;
extern void* D_801C4604;
extern void* D_801C46DC;
extern void* D_801C473C;
extern void* D_801C47AC;
extern void* D_801C4808;
extern void* D_801C488C;
extern void* D_801C4910;
extern void* D_801C4AB8;
extern void* D_801C4B34;
extern void* D_801C4B6C;
extern void* D_801C4BE8;
extern void* D_801C4C2C;
extern void* D_801C4CB4;
extern void* D_801C4D3C;
extern void* D_801C4D88;
extern void* D_801C4DC8;
extern void* D_801C4E38;
extern void* D_801C4E84;
extern void* D_801C4EEC;
extern void* D_801C4F28;
extern void* D_801C4F64;
extern void* D_801C4FA0;
extern void* D_801C4FD0;
extern void* D_801C5020;
extern void* D_801C50D0;
extern void* D_801C5118;
extern void* D_801C5174;
extern void* D_801C51E8;
extern void* D_801C5224;
extern void* D_801C52EC;
extern void* D_801C5364;
extern void* D_801C53C4;
extern void* D_801C5410;
extern void* D_801C546C;
extern void* D_801C54F4;
extern void* D_801C56F8;
extern SceneEntranceTableEnty gSceneEntranceTable[110];
extern void* D_801C5C50;
extern void* D_801C5CB0;
extern z_Matrix identityMatrix;
extern s32 D_801C5E30[];
extern u16 D_801C5E48[];
extern s32 D_801C5E88[];
extern s32 D_801C5E9C[];
extern s32 D_801C5EB0[];
extern s16 D_801C5EC4[];
extern struct_801C5F44 D_801C5F44[];
extern SaveContext_struct1 D_801C6898;
extern SaveContext_struct2 D_801C68C0;
extern SaveContextInventory gSaveDefaultInventory;
extern u16 gSaveDefaultChecksum;
extern SaveContext_struct1 D_801C6970;
extern SaveContext_struct2 D_801C6998;
extern SaveContextInventory D_801C69BC;
extern u16 D_801C6A44;
extern void* D_801CFD94;
extern char D_801D039C[];
extern char D_801D06F0[];
extern char D_801D0714[];
extern ActorInit Player_InitVars;
extern void* D_801D0CD8;
extern void* D_801D0D28;
extern s32 D_801D0D50;
extern Input* D_801D0D60;
extern s32 gFramerateDivisor;
extern f32 gFramerateDivisorF;
extern f32 gFramerateDivisorHalf;
extern f32 gFramerateDivisorThird;
extern u32 D_801D1510;
extern u32 D_801D1514[3];
extern s32 gScreenWidth;
extern s32 gScreenHeight;
extern PadmgrThreadStruct* padmgrContext;
extern void* D_801D1540;
extern f32 D_801D1570[13];
extern Vec3f D_801D15B0;
extern s16 atan_first_8th_array[1025];
extern RSPMatrix D_801D1DE0;
extern z_Matrix D_801D1E20;
extern void* D_801D1E60;
extern void* D_801D1E64;
extern void* D_801D4D90;
extern void* D_801D4D98;
extern void* D_801D4DB0;
extern void* D_801D5FE0;
extern void* D_801D6000;
extern void* D_801D6188;
extern void* D_801D618C;
extern void* D_801D84F0;
extern void* D_801D889C;
extern void* D_801D88A0;
extern void* D_801D88A4;
extern void* D_801D8B24;
extern void* D_801DB450;
extern void* D_801DB478[7];
extern void* D_801DB930;
extern s8018CFAC D_801DB958[21];
extern f32 D_801DBDF0;
extern f32 D_801DBE68;
extern f32 D_801DBE6C;
extern f32 D_801DBE70;
extern f32 D_801DBE74;
extern f32 D_801DBE78;
extern f32 D_801DBE7C;
extern f32 D_801DBE80;
extern f32 D_801DBE84;
extern f32 D_801DBE88;
extern f32 D_801DBE8C;
extern f32 D_801DBE90;
extern f32 D_801DBE94;
extern f32 D_801DBE98;
extern f32 D_801DBE9C;
extern f32 D_801DBEA0;
extern f32 D_801DBF10;
extern f32 D_801DBF14;
extern f32 D_801DBF18;
extern f32 D_801DBF1C;
extern f32 D_801DBF20;
extern f32 D_801DC068;
extern f32 D_801DC06C;
extern f32 D_801DC070;
extern f32 D_801DC074;
extern f32 D_801DC080;
extern f32 D_801DC084;
extern f32 D_801DC09C;
extern f32 D_801DC0A0;
extern f32 D_801DC0B0;
extern f32 D_801DC0B4;
extern f32 D_801DC0C0;
extern f32 D_801DC0C4;
extern f32 D_801DC0C8;
extern f32 D_801DC0CC;
extern f32 D_801DC0D0;
extern f32 D_801DC0D4;
extern f32 D_801DC100;
extern f32 D_801DC104;
extern f32 D_801DC108;
extern f32 D_801DC10C;
extern f32 D_801DC110;
extern f32 D_801DC114;
extern char D_801DC120[];
extern char D_801DC134[];
extern char D_801DC148[];
extern char D_801DC15C[];
extern char D_801DC170[];
extern char D_801DC184[];
extern char D_801DC198[];
extern char D_801DC1AC[];
extern char D_801DC1C0[];
extern char D_801DC1D4[];
extern char D_801DC1E8[];
extern char D_801DC1FC[];
extern char D_801DC210[];
extern char D_801DC224[];
extern char D_801DC238[];
extern char D_801DC24C[];
extern char D_801DC260[];
extern char D_801DC274[];
extern char D_801DC288[];
extern char D_801DC29C[];
extern char D_801DC2B0[];
extern char D_801DC2C4[];
extern char D_801DC2D8[];
extern char D_801DC2EC[];
extern char D_801DC300[];
extern char D_801DC314[];
extern char D_801DC328[];
extern char D_801DC33C[];
extern char D_801DC350[];
extern char D_801DC364[];
extern char D_801DC378[];
extern char D_801DC38C[];
extern char D_801DC3A0[];
extern char D_801DC3B4[];
extern char D_801DC3C8[];
extern char D_801DC3DC[];
extern char D_801DC3F0[];
extern char D_801DC404[];
extern char D_801DC418[];
extern char D_801DC42C[];
extern char D_801DC440[];
extern char D_801DC454[];
extern char D_801DC468[];
extern char D_801DC47C[];
extern char D_801DC490[];
extern char D_801DC4A4[];
extern char D_801DC4B8[];
extern char D_801DC4CC[];
extern char D_801DC4E0[];
extern char D_801DC4F4[];
extern char D_801DC508[];
extern char D_801DC51C[];
extern char D_801DC530[];
extern char D_801DC544[];
extern char D_801DC558[];
extern char D_801DC56C[];
extern char D_801DC580[];
extern char D_801DC594[];
extern char D_801DC5A8[];
extern char D_801DC5BC[];
extern char D_801DC5D0[];
extern char D_801DC5E4[];
extern char D_801DC5F8[];
extern char D_801DC60C[];
extern char D_801DC620[];
extern char D_801DC634[];
extern char D_801DC648[];
extern char D_801DC65C[];
extern char D_801DC670[];
extern char D_801DC684[];
extern char D_801DC698[];
extern char D_801DC6AC[];
extern char D_801DC6C0[];
extern char D_801DC6D4[];
extern char D_801DC6E8[];
extern char D_801DC6FC[];
extern char D_801DC710[];
extern char D_801DC724[];
extern char D_801DC738[];
extern char D_801DC74C[];
extern char D_801DC760[];
extern char D_801DC774[];
extern char D_801DC788[];
extern char D_801DC79C[];
extern char D_801DC7B0[];
extern char D_801DC7C4[];
extern char D_801DC7D8[];
extern char D_801DC7EC[];
extern char D_801DC800[];
extern char D_801DC814[];
extern char D_801DC828[];
extern char D_801DC83C[];
extern char D_801DC850[];
extern char D_801DC864[];
extern char D_801DC878[];
extern char D_801DC88C[];
extern char D_801DC8A0[];
extern char D_801DC8B4[];
extern char D_801DC8C8[];
extern char D_801DC8DC[];
extern char D_801DC8F0[];
extern char D_801DC900[];
extern char D_801DC910[];
extern char D_801DC920[];
extern char D_801DC930[];
extern char D_801DC940[];
extern char D_801DC950[];
extern char D_801DC960[];
extern char D_801DC970[];
extern char D_801DC984[];
extern char D_801DC998[];
extern char D_801DC9D0[];
extern char D_801DC9D8[];
extern char D_801DC9F8[];
extern f32 D_801DCA14;
extern f32 D_801DCA18;
extern f32 D_801DCA1C;
extern f32 D_801DCA20;
extern f32 D_801DCA24;
extern f32 D_801DCA28;
extern f32 D_801DCA2C;
extern f32 D_801DCA30;
extern f32 D_801DCA34;
extern f32 D_801DCA38;
extern f32 D_801DCA3C;
extern f32 D_801DCA40;
extern f32 D_801DCA44;
extern f32 D_801DCA48;
extern f32 D_801DCA4C;
extern f32 D_801DCA50;
extern f32 D_801DCA54;
extern f32 D_801DCA6C;
extern f32 D_801DCA70;
extern f32 D_801DCA74;
extern f32 D_801DCA78;
extern f32 D_801DCA7C;
extern f32 D_801DCA80;
extern f32 D_801DCA84;
extern f32 D_801DCA88;
extern f32 D_801DCA8C;
extern f32 D_801DCA90;
extern f32 D_801DCA94;
extern f32 D_801DCA98;
extern f32 D_801DCA9C;
extern f32 D_801DCAA0;
extern f32 D_801DCAA4;
extern f32 D_801DCAA8;
extern f32 D_801DCAAC;
extern f32 D_801DCAB0;
extern f32 D_801DCAB4;
extern f32 D_801DCAB8;
extern f32 D_801DCABC;
extern f32 D_801DCAC0;
extern f32 D_801DCAC4;
extern f32 D_801DCAC8;
extern f32 D_801DCACC;
extern f32 D_801DCAD0;
extern f32 D_801DCAD4;
extern f32 D_801DCAD8;
extern f32 D_801DCADC;
extern f32 D_801DCAE0;
extern f32 D_801DCB68;
extern f32 D_801DCB6C;
extern f32 D_801DCB70;
extern f32 D_801DCB74;
extern f32 D_801DCB78;
extern f32 D_801DCB7C;
extern f32 D_801DCB80;
extern f32 D_801DCB84;
extern f32 D_801DCB88;
extern f32 D_801DCB8C;
extern f32 D_801DCB90;
extern f32 D_801DCB94;
extern f32 D_801DCB98;
extern f32 D_801DCB9C;
extern f32 D_801DCBA0;
extern f32 D_801DCBA4;
extern f32 D_801DCBA8;
extern f32 D_801DCBAC;
extern char D_801DCBB0[];
extern char D_801DCBC4[];
extern char D_801DCBE4[];
extern char D_801DCC00[];
extern char D_801DCC10[];
extern char D_801DCC20[];
extern char D_801DCC64[];
extern char D_801DCC94[];
extern char D_801DCCB8[];
extern char D_801DCCC8[];
extern char D_801DCCE8[];
extern char D_801DCCF8[];
extern char D_801DCD18[];
extern f32 D_801DCD28;
extern f32 D_801DCD2C;
extern f32 D_801DCD30;
extern f32 D_801DCD34;
extern f32 D_801DCD38;
extern f32 D_801DCD3C;
extern f32 D_801DCD40;
extern f32 D_801DCD44;
extern f32 D_801DCD48;
extern f32 D_801DCD4C;
extern f32 D_801DCD50;
extern f32 D_801DCD54;
extern f32 D_801DCD58;
extern f32 D_801DCD5C;
extern f32 D_801DCD60;
extern f32 D_801DCD64;
extern f32 D_801DCD68;
extern f32 D_801DCD6C;
extern f32 D_801DCD70;
extern f32 D_801DCD74;
extern f32 D_801DCD78;
extern f32 D_801DCD7C;
extern f32 D_801DCD80;
extern f32 D_801DCD84;
extern f32 D_801DCD88;
extern f32 D_801DCD8C;
extern f32 D_801DCD90;
extern f32 D_801DCD94;
extern f32 D_801DCD98;
extern f32 D_801DCD9C;
extern f32 D_801DCDA0;
extern f32 D_801DCDA4;
extern f32 D_801DCDB0;
extern f32 D_801DCDB4;
extern f32 D_801DCDC0;
extern f32 D_801DCDC4;
extern f32 D_801DCDC8;
extern f32 D_801DCDCC;
extern f32 D_801DCDD0;
extern f32 D_801DCDD4;
extern f32 D_801DCDD8;
extern f32 D_801DCDE4;
extern f32 D_801DCDE8;
extern f32 D_801DCDEC;
extern f32 D_801DCDF0;
extern f32 D_801DCDF4;
extern f32 D_801DCDF8;
extern f32 D_801DCDFC;
extern f32 D_801DCE00;
extern f32 D_801DCE04;
extern f32 D_801DCE08;
extern f32 D_801DCE0C;
extern f32 D_801DCE10;
extern f32 D_801DCE14;
extern f32 D_801DCE18;
extern f32 D_801DCE1C;
extern f32 D_801DCE20;
extern f32 D_801DCE24;
extern f32 D_801DCE28;
extern f32 D_801DCE2C;
extern f32 D_801DCE30;
extern f32 D_801DCE34;
extern f32 D_801DCE38;
extern f32 D_801DCE3C;
extern f32 D_801DCE40;
extern f32 D_801DCE44;
extern f32 D_801DCE48;
extern f32 D_801DCE4C;
extern f32 D_801DCE50;
extern f32 D_801DCE54;
extern f32 D_801DCE58;
extern f32 D_801DCE5C;
extern f32 D_801DCE60;
extern f32 D_801DCE64;
extern f32 D_801DCE68;
extern f32 D_801DCE6C;
extern f32 D_801DCE70;
extern f32 D_801DCE74;
extern f32 D_801DCE78;
extern f32 D_801DCE7C;
extern f32 D_801DCE80;
extern f32 D_801DCE84;
extern f32 D_801DCE88;
extern f32 D_801DCE8C;
extern f32 D_801DCE90;
extern f32 D_801DCE94;
extern f32 D_801DCE98;
extern f32 D_801DCE9C;
extern f32 D_801DCEA0;
extern f32 D_801DCEA4;
extern f32 D_801DCEA8;
extern f32 D_801DCEAC;
extern f32 D_801DCEB0;
extern f32 D_801DCEB4;
extern f32 D_801DCEB8;
extern f32 D_801DCEBC;
extern f32 D_801DCEC0;
extern f32 D_801DCEC4;
extern f32 D_801DCEC8;
extern f32 D_801DCECC;
extern f32 D_801DCED0;
extern f32 D_801DCED4;
extern f32 D_801DCED8;
extern f32 D_801DCEDC;
extern f32 D_801DCEE0;
extern f32 D_801DCEE4;
extern f32 D_801DCEE8;
extern f32 D_801DCEEC;
extern f32 D_801DCEF0;
extern f32 D_801DCEF4;
extern f32 D_801DCEF8;
extern f32 D_801DCEFC;
extern f32 D_801DCF00;
extern f32 D_801DCF04;
extern f32 D_801DCF08;
extern f32 D_801DCF0C;
extern f32 D_801DCF10;
extern f32 D_801DCF14;
extern f32 D_801DCF18;
extern f32 D_801DCF1C;
extern f32 D_801DCF34;
extern f32 D_801DCF38;
extern f32 D_801DCF3C;
extern f32 D_801DCF40;
extern f32 D_801DCF44;
extern f32 D_801DCF48;
extern f32 D_801DCF4C;
extern f32 D_801DCF50;
extern f32 D_801DCF54;
extern f32 D_801DCF58;
extern f32 D_801DCF5C;
extern f32 D_801DCF60;
extern f32 D_801DCF64;
extern f32 D_801DCF68;
extern f32 D_801DCF6C;
extern f32 D_801DCF70;
extern f32 D_801DCF74;
extern f32 D_801DCF78;
extern f32 D_801DCF7C;
extern f32 D_801DCF80;
extern f32 D_801DCF84;
extern f32 D_801DCF8C;
extern f32 D_801DCF90;
extern f32 D_801DCF98;
extern f32 D_801DCF9C;
extern f32 D_801DCFA0;
extern f32 D_801DCFA4;
extern f32 D_801DCFA8;
extern f32 D_801DCFAC;
extern f32 D_801DCFB0;
extern f32 D_801DCFB8;
extern f32 D_801DCFBC;
extern f32 D_801DCFC0;
extern f32 D_801DCFC4;
extern f32 D_801DCFC8;
extern f32 D_801DCFCC;
extern f32 D_801DCFD0;
extern f32 D_801DCFD4;
extern f32 D_801DD00C;
extern f32 D_801DD010;
extern f32 D_801DD014;
extern f32 D_801DD018;
extern f32 D_801DD01C;
extern f32 D_801DD020;
extern f32 D_801DD024;
extern f32 D_801DD028;
extern f32 D_801DD02C;
extern f32 D_801DD030;
extern f32 D_801DD034;
extern f32 D_801DD038;
extern f32 D_801DD03C;
extern f32 D_801DD040;
extern f32 D_801DD044;
extern f32 D_801DD048;
extern f32 D_801DD04C;
extern f32 D_801DD050;
extern f32 D_801DD054;
extern f32 D_801DD058;
extern f32 D_801DD060;
extern f32 D_801DD064;
extern f32 D_801DD068;
extern f32 D_801DD06C;
extern f32 D_801DD070;
extern f32 D_801DD074;
extern f32 D_801DD078;
extern f32 D_801DD07C;
extern f32 D_801DD080;
extern f32 D_801DD084;
extern f32 D_801DD088;
extern f32 D_801DD08C;
extern f32 D_801DD090;
extern f32 D_801DD094;
extern f32 D_801DD098;
extern f32 D_801DD09C;
extern f32 D_801DD0A0;
extern f32 D_801DD0A4;
extern f32 D_801DD0A8;
extern f32 D_801DD0AC;
extern f32 D_801DD0B0;
extern f32 D_801DD0B4;
extern f32 D_801DD0B8;
extern f32 D_801DD0BC;
extern f32 D_801DD0C0;
extern f32 D_801DD0C4;
extern f32 D_801DD0C8;
extern f32 D_801DD0CC;
extern f32 D_801DD0D0;
extern f32 D_801DD0D4;
extern f32 D_801DD0D8;
extern f32 D_801DD0DC;
extern f32 D_801DD0E0;
extern f32 D_801DD0E4;
extern f32 D_801DD0E8;
extern f32 D_801DD0EC;
extern f32 D_801DD0F0;
extern f32 D_801DD0F4;
extern f32 D_801DD0F8;
extern f32 D_801DD0FC;
extern f32 D_801DD100;
extern f32 D_801DD104;
extern f32 D_801DD108;
extern f32 D_801DD10C;
extern f32 D_801DD110;
extern f32 D_801DD114;
extern f32 D_801DD118;
extern f32 D_801DD11C;
extern f32 D_801DD120;
extern f32 D_801DD124;
extern f32 D_801DD128;
extern f32 D_801DD12C;
extern f32 D_801DD130;
extern f32 D_801DD134;
extern f32 D_801DD138;
extern f32 D_801DD13C;
extern f32 D_801DD140;
extern f32 D_801DD144;
extern f32 D_801DD148;
extern f32 D_801DD14C;
extern f32 D_801DD150;
extern f32 D_801DD154;
extern f32 D_801DD158;
extern f32 D_801DD15C;
extern f32 D_801DD160;
extern f32 D_801DD164;
extern f32 D_801DD168;
extern f32 D_801DD16C;
extern f32 D_801DD170;
extern f32 D_801DD174;
extern f32 D_801DD178;
extern f32 D_801DD1B0;
extern f32 D_801DD1B4;
extern f32 D_801DD1B8;
extern f32 D_801DD1BC;
extern f32 D_801DD1C0;
extern f32 D_801DD1C4;
extern f32 D_801DD1C8;
extern f32 D_801DD1CC;
extern f32 D_801DD1D0;
extern f32 D_801DD1D4;
extern f32 D_801DD1D8;
extern f32 D_801DD1DC;
extern f32 D_801DD1E0;
extern f32 D_801DD1E4;
extern f32 D_801DD1E8;
extern f32 D_801DD1EC;
extern f32 D_801DD1F0;
extern f32 D_801DD1F4;
extern f32 D_801DD1F8;
extern f32 D_801DD1FC;
extern f32 D_801DD200;
extern f32 D_801DD204;
extern f32 D_801DD208;
extern f32 D_801DD20C;
extern f32 D_801DD210;
extern f32 D_801DD214;
extern f32 D_801DD218;
extern f32 D_801DD21C;
extern f32 D_801DD220;
extern f32 D_801DD224;
extern f32 D_801DD228;
extern f32 D_801DD22C;
extern f32 D_801DD230;
extern f32 D_801DD234;
extern f32 D_801DD238;
extern f32 D_801DD23C;
extern f32 D_801DD240;
extern f32 D_801DD244;
extern f32 D_801DD248;
extern f32 D_801DD24C;
extern f32 D_801DD250;
extern f32 D_801DD254;
extern f32 D_801DD258;
extern f32 D_801DD25C;
extern f32 D_801DD260;
extern f32 D_801DD264;
extern f32 D_801DD268;
extern f32 D_801DD26C;
extern f32 D_801DD270;
extern f32 D_801DD274;
extern f32 D_801DD278;
extern f32 D_801DD27C;
extern f32 D_801DD2A0;
extern f32 D_801DD2A4;
extern f32 D_801DD2A8;
extern f32 D_801DD2AC;
extern f32 D_801DD2B0;
extern f32 D_801DD2B4;
extern f32 D_801DD2B8;
extern f32 D_801DD2BC;
extern f32 D_801DD2C0;
extern f32 D_801DD2C4;
extern f32 D_801DD344;
extern f32 D_801DD348;
extern f32 D_801DD34C;
extern f32 D_801DD350;
extern f32 D_801DD354;
extern f32 D_801DD358;
extern f32 D_801DD35C;
extern f32 D_801DD360;
extern f32 D_801DD364;
extern f32 D_801DD368;
extern f32 D_801DD36C;
extern f32 D_801DD370;
extern f32 D_801DD374;
extern f32 D_801DD38C;
extern f32 D_801DD390;
extern f32 D_801DD394;
extern f32 D_801DD398;
extern f32 D_801DD39C;
extern f32 D_801DD3A0;
extern f32 D_801DD3A4;
extern f32 D_801DD3A8;
extern f32 D_801DD3AC;
extern f32 D_801DD3B0;
extern f32 D_801DD3B4;
extern f32 D_801DD3B8;
extern f32 D_801DD3BC;
extern f32 D_801DD3C0;
extern f32 D_801DD3C4;
extern f32 D_801DD3C8;
extern f32 D_801DD3CC;
extern f32 D_801DD3D0;
extern f32 D_801DD3D4;
extern f32 D_801DD3D8;
extern f32 D_801DD3DC;
extern f32 D_801DD3E0;
extern f32 D_801DD3E4;
extern f32 D_801DD3E8;
extern f32 D_801DD3EC;
extern f32 D_801DD3F0;
extern f32 D_801DD3F4;
extern f32 D_801DD3F8;
extern f32 D_801DD3FC;
extern f32 D_801DD400;
extern f32 D_801DD404;
extern f32 D_801DD408;
extern f32 D_801DD40C;
extern f32 D_801DD410;
extern f32 D_801DD414;
extern f32 D_801DD418;
extern f32 D_801DD41C;
extern f32 D_801DD420;
extern f32 D_801DD424;
extern f32 D_801DD43C;
extern f32 D_801DD440;
extern f32 D_801DD444;
extern f32 D_801DD448;
extern f32 D_801DD44C;
extern f32 D_801DD450;
extern f32 D_801DD454;
extern f32 D_801DD458;
extern f32 D_801DD45C;
extern f32 D_801DD460;
extern f32 D_801DD5AC;
extern f32 D_801DD5B0;
extern f32 D_801DD5C0;
extern f32 D_801DD5C4;
extern f32 D_801DD5C8;
extern f32 D_801DD5CC;
extern f32 D_801DD5D0;
extern f32 D_801DD5D4;
extern f32 D_801DD5D8;
extern f32 minCylinderIntersectAmount;
extern f32 D_801DD5E0;
extern f32 D_801DD5E4;
extern f32 D_801DD5E8;
extern f32 D_801DD5EC;
extern f32 D_801DD5F0;
extern f32 D_801DD5F4;
extern f32 D_801DD5F8;
extern f32 D_801DD5FC;
extern char D_801DD600[];
extern char D_801DD604[];
extern f32 D_801DD6FC;
extern f32 D_801DD770;
extern f32 D_801DD774;
extern f32 D_801DD780;
extern f32 D_801DD7B0;
extern f32 D_801DD7C0;
extern f32 D_801DD7D0;
extern f32 D_801DD7D4;
extern f32 D_801DD7E0;
extern f32 D_801DD7E4;
extern f32 D_801DD7E8;
extern f32 D_801DD7EC;
extern f32 D_801DD940;
extern f32 D_801DD944;
extern f32 D_801DD948;
extern f32 D_801DD94C;
extern f32 D_801DD950;
extern f32 D_801DD954;
extern f32 D_801DD958;
extern f32 D_801DD95C;
extern f32 D_801DD960;
extern f32 D_801DD964;
extern f32 D_801DD968;
extern f32 D_801DD96C;
extern f32 D_801DD970;
extern f32 D_801DD974;
extern f32 D_801DD978;
extern f32 D_801DD97C;
extern f32 D_801DD980;
extern f32 D_801DD984;
extern f32 D_801DD988;
extern f32 D_801DD98C;
extern f32 D_801DD990;
extern f32 D_801DD9EC;
extern f32 D_801DD9F0;
extern f32 D_801DD9F4;
extern f32 D_801DD9F8;
extern f32 D_801DD9FC;
extern f32 D_801DDA7C;
extern f32 D_801DDA80;
extern f32 D_801DDA84;
extern f32 D_801DDA90;
extern f32 D_801DDA94;
extern f32 D_801DDA98;
extern f32 D_801DDA9C;
extern f32 D_801DDAA0;
extern f32 D_801DDAB0;
extern f32 D_801DDAB4;
extern f32 D_801DDAB8;
extern f32 D_801DDAC0;
extern f32 D_801DDAC4;
extern f32 D_801DDAC8;
extern f32 D_801DDACC;
extern f32 D_801DDAD0;
extern f32 D_801DDAD4;
extern f32 D_801DDAD8;
extern f32 D_801DDADC;
extern f32 D_801DDAE0;
extern f32 D_801DDAE4;
extern f32 D_801DDAE8;
extern f32 D_801DDAEC;
extern f32 D_801DDAF0;
extern f32 D_801DDAF4;
extern f32 D_801DDAF8;
extern f32 D_801DDAFC;
extern f32 D_801DDBA8;
extern f32 D_801DDBAC;
extern f32 D_801DDBB0;
extern f32 D_801DDBB4;
extern f32 D_801DDBB8;
extern f32 D_801DDBBC;
extern f32 D_801DDBC0;
extern f32 D_801DDBC4;
extern f32 D_801DDBC8;
extern f32 D_801DDBCC;
extern f32 D_801DDCF8;
extern f32 D_801DDCFC;
extern f32 D_801DDD00;
extern f32 D_801DDD04;
extern f32 D_801DDD08;
extern f32 D_801DDD0C;
extern f32 D_801DDD10;
extern f32 D_801DDD14;
extern f32 D_801DDD20;
extern f32 D_801DDD24;
extern f32 D_801DDD28;
extern f32 D_801DDD2C;
extern f32 D_801DDD30;
extern f32 D_801DDD34;
extern f32 D_801DDD38;
extern f32 D_801DDD3C;
extern f32 D_801DDD40;
extern f32 D_801DDD44;
extern f32 D_801DDD48;
extern f32 D_801DDD4C;
extern f32 D_801DDD50;
extern f32 D_801DDD54;
extern f32 D_801DDD58;
extern f32 D_801DDD5C;
extern f32 D_801DDD60;
extern f32 D_801DDD64;
extern f32 D_801DDD68;
extern f32 D_801DDD6C;
extern f32 D_801DDD70;
extern f32 D_801DDD74;
extern f32 D_801DDD78;
extern f32 D_801DDD7C;
extern f32 D_801DDD80;
extern f32 D_801DDD84;
extern f32 D_801DDD88;
extern f32 D_801DDD8C;
extern f32 D_801DDD90;
extern f32 D_801DDD94;
extern f32 D_801DDD98;
extern f32 D_801DDD9C;
extern f32 D_801DDDA0;
extern f32 D_801DDDA4;
extern f32 D_801DDDA8;
extern f32 D_801DDDAC;
extern f32 D_801DDDB0;
extern f32 D_801DDDB4;
extern f32 D_801DDDB8;
extern f32 D_801DDDBC;
extern f32 D_801DDDC0;
extern f32 D_801DDDC4;
extern f32 D_801DDDC8;
extern f32 D_801DDDCC;
extern f32 D_801DDDD0;
extern f32 D_801DDDD4;
extern f32 D_801DDDD8;
extern f32 D_801DDDDC;
extern f32 D_801DDDE0;
extern f32 D_801DDDE4;
extern f32 D_801DDDE8;
extern f32 D_801DDDEC;
extern f32 D_801DDDF0;
extern f32 D_801DDDF4;
extern f32 D_801DDDF8;
extern f32 D_801DDDFC;
extern f32 D_801DDE00;
extern f32 D_801DDE04;
extern f32 D_801DDE90;
extern f32 D_801DDE94;
extern f32 D_801DDE98;
extern f32 D_801DDE9C;
extern f32 D_801DDEA0;
extern f32 D_801DDEA4;
extern f32 D_801DDEA8;
extern f32 D_801DDEAC;
extern f32 D_801DDEB0;
extern f32 D_801DDEB4;
extern f32 D_801DDEB8;
extern f32 D_801DDEBC;
extern f32 D_801DDEC0;
extern f32 D_801DDEC4;
extern f32 D_801DDEC8;
extern f32 D_801DDECC;
extern f32 D_801DDED0;
extern f32 D_801DDED4;
extern f32 D_801DDED8;
extern f32 D_801DDEDC;
extern f32 D_801DDEE0;
extern f32 D_801DDEE4;
extern f32 D_801DDEE8;
extern f32 D_801DDEEC;
extern f32 D_801DDEF0;
extern f32 D_801DDEF4;
extern f32 D_801DDEF8;
extern f32 D_801DDEFC;
extern f32 D_801DDF00;
extern f32 D_801DDF04;
extern f32 D_801DDF08;
extern f32 D_801DDF0C;
extern f32 D_801DDF10;
extern f32 D_801DDF14;
extern f32 D_801DDF18;
extern f32 D_801DDF1C;
extern f32 D_801DDF20;
extern f32 D_801DDF24;
extern f32 D_801DDF28;
extern f32 D_801DDF2C;
extern f32 D_801DDF30;
extern f32 D_801DDF34;
extern f32 D_801DDF38;
extern f32 D_801DDF3C;
extern f32 D_801DDF40;
extern f32 D_801DDF44;
extern f32 D_801DDF48;
extern f32 D_801DDF4C;
extern f32 D_801DDF50;
extern f32 D_801DDF54;
extern f32 D_801DDF58;
extern f32 D_801DDF5C;
extern f32 D_801DDF60;
extern f32 D_801DDF64;
extern f32 D_801DDF68;
extern f32 D_801DDF6C;
extern f32 D_801DDF70;
extern f32 D_801DDF74;
extern f32 D_801DDF78;
extern f32 D_801DDF7C;
extern f32 D_801DDF80;
extern f32 D_801DDF84;
extern f32 D_801DDF88;
extern f32 D_801DDF8C;
extern f32 D_801DDF90;
extern f32 D_801DDF94;
extern char D_801DDFA0[];
extern char D_801DDFAC[];
extern char D_801DDFB8[];
extern f32 D_801DDFC4;
extern f32 D_801DDFC8;
extern f32 D_801DDFCC;
extern f32 D_801DDFD0;
extern f32 D_801DDFD4;
extern f32 D_801DDFD8;
extern f32 D_801DDFDC;
extern f32 D_801DDFE0;
extern f32 D_801DDFE4;
extern char D_801DE020[];
extern char D_801DE030[];
extern char D_801DE03C[];
extern char D_801DE04C[];
extern char D_801DE058[];
extern char D_801DE064[];
extern char D_801DE074[];
extern char D_801DE084[];
extern char D_801DE094[];
extern char D_801DE0A0[];
extern char D_801DE0A8[];
extern char D_801DE0B4[];
extern char D_801DE0C0[];
extern char D_801DE0CC[];
extern char D_801DE0D8[];
extern char D_801DE0E4[];
extern char D_801DE0F0[];
extern char D_801DE0FC[];
extern char D_801DE10C[];
extern char D_801DE118[];
extern char D_801DE12C[];
extern char D_801DE138[];
extern char D_801DE144[];
extern char D_801DE154[];
extern char D_801DE164[];
extern char D_801DE170[];
extern char D_801DE180[];
extern char D_801DE18C[];
extern char D_801DE19C[];
extern char D_801DE1A8[];
extern char D_801DE1B8[];
extern char D_801DE1C4[];
extern char D_801DE1D0[];
extern char D_801DE1E0[];
extern char D_801DE1F0[];
extern char D_801DE200[];
extern char D_801DE20C[];
extern char D_801DE21C[];
extern char D_801DE22C[];
extern char D_801DE234[];
extern char D_801DE244[];
extern char D_801DE258[];
extern char D_801DE268[];
extern char D_801DE278[];
extern char D_801DE280[];
extern char D_801DE290[];
extern char D_801DE29C[];
extern char D_801DE2A8[];
extern char D_801DE2B8[];
extern char D_801DE2C4[];
extern char D_801DE2D4[];
extern char D_801DE2E4[];
extern char D_801DE2F4[];
extern char D_801DE304[];
extern char D_801DE314[];
extern char D_801DE320[];
extern char D_801DE328[];
extern char D_801DE330[];
extern char D_801DE340[];
extern char D_801DE350[];
extern char D_801DE360[];
extern char D_801DE370[];
extern char D_801DE384[];
extern char D_801DE38C[];
extern char D_801DE398[];
extern char D_801DE3A4[];
extern char D_801DE3B0[];
extern char D_801DE3C4[];
extern char D_801DE3D4[];
extern char D_801DE3E0[];
extern char D_801DE3F4[];
extern char D_801DE400[];
extern char D_801DE40C[];
extern char D_801DE418[];
extern char D_801DE424[];
extern char D_801DE434[];
extern char D_801DE444[];
extern char D_801DE450[];
extern char D_801DE458[];
extern char D_801DE460[];
extern char D_801DE478[];
extern char D_801DE48C[];
extern char D_801DE49C[];
extern char D_801DE4AC[];
extern char D_801DE4BC[];
extern char D_801DE4C8[];
extern char D_801DE4D4[];
extern char D_801DE4E0[];
extern char D_801DE4F0[];
extern char D_801DE500[];
extern char D_801DE510[];
extern char D_801DE520[];
extern char D_801DE530[];
extern char D_801DE53C[];
extern char D_801DE548[];
extern char D_801DE558[];
extern char D_801DE568[];
extern char D_801DE578[];
extern char D_801DE580[];
extern char D_801DE58C[];
extern char D_801DE598[];
extern char D_801DE5A8[];
extern f32 D_801DE5C0;
extern f32 D_801DE5D0;
extern f32 D_801DE820;
extern f32 D_801DE824;
extern f32 D_801DE828;
extern f32 D_801DE82C;
extern f32 D_801DE830;
extern f32 D_801DE834;
extern f32 D_801DE838;
extern f32 D_801DE83C;
extern f32 D_801DE840;
extern f32 D_801DE844;
extern f32 D_801DE848;
extern f32 D_801DE84C;
extern f32 D_801DE850;
extern f32 D_801DE854;
extern f32 D_801DE858;
extern f32 D_801DE85C;
extern f32 D_801DE860;
extern f32 D_801DE864;
extern f32 D_801DE868;
extern f32 D_801DE884;
extern f32 D_801DF090;
extern f32 D_801DF094;
extern f32 D_801DF0A0;
extern char D_801DF0B0[];
extern f32 D_801DF120;
extern f32 D_801DF124;
extern f32 D_801DF148;
extern f32 D_801DF3AC;
extern f32 D_801DF3B0;
extern f32 D_801DF3B4;
extern f32 D_801DF3B8;
extern f32 D_801DF3BC;
extern f32 D_801DF3C0;
extern f32 D_801DF3C4;
extern f32 D_801DF3C8;
extern void* D_801DF83C;
extern f32 D_801DF8E0;
extern f32 D_801DF970;
extern f32 D_801DF974;
extern f32 D_801DF978;
extern f32 D_801DF97C;
extern f32 D_801DF980;
extern f32 D_801DF984;
extern f32 D_801DF988;
extern f32 D_801DF98C;
extern f32 D_801DF990;
extern f32 D_801DF994;
extern f32 D_801DF998;
extern f32 D_801DF99C;
extern f32 D_801DF9A0;
extern f32 D_801DF9A4;
extern f32 D_801DF9A8;
extern f32 D_801DF9AC;
extern f32 D_801DF9B0;
extern f32 D_801DF9B4;
extern char D_801DF9C0[];
extern char D_801DF9D0[];
extern f32 D_801DF9E0;
extern f32 D_801DF9E4;
extern f32 D_801DF9E8;
extern f32 D_801DF9EC;
extern f32 D_801DF9F0;
extern f32 D_801DF9F4;
extern f32 D_801DF9F8;
extern char D_801DFA00[];
extern char D_801DFA0C[];
extern f32 D_801DFC3C;
extern f32 D_801DFC40;
extern f32 D_801DFC44;
extern f32 D_801DFC50;
extern f32 D_801DFC54;
extern f32 D_801DFC58;
extern f32 D_801DFC5C;
extern char D_801DFC60[];
extern u8 D_801DFC70[7];
extern char D_801DFC80[];
extern char D_801DFC9C[];
extern char D_801DFCC0[];
extern char D_801DFCCC[];
extern char D_801DFCE0[];
extern char D_801DFCFC[];
extern char D_801DFD10[];
extern char D_801DFD2C[];
extern char D_801DFD40[];
extern char D_801DFD50[];
extern char D_801DFD5C[];
extern char schedThreadName[];
extern char audioThreadName[];
extern char padmgrThreadName[];
extern char graphThreadName[];
extern char D_801DFD90[];
extern char D_801DFD9C[];
extern char D_801DFDA8[];
extern char D_801DFDE0[];
extern char D_801DFDFC[];
extern char D_801DFE18[];
extern char D_801DFE48[];
extern char D_801DFE6C[];
extern char D_801DFE8C[];
extern char D_801DFEF0[];
extern char D_801DFF0C[];
extern char D_801DFF28[];
extern char D_801DFF58[];
extern char D_801DFF7C[];
extern char D_801E0038[];
extern char D_801E0060[];
extern char D_801E0088[];
extern char D_801E0094[];
extern char D_801E00A8[];
extern char D_801E00BC[];
extern char D_801E00E8[];
extern f32 D_801E0120;
extern f32 D_801E0124;
extern f32 D_801E0128;
extern f32 D_801E012C;
extern f32 Math3D_Normalize_min_length;
extern f32 D_801E0134;
extern f32 D_801E0138;
extern f32 D_801E013C;
extern f32 D_801E0140;
extern f32 Math3D_AngleBetweenVectors_min_length;
extern f32 D_801E0148;
extern f32 D_801E014C;
extern f32 Math3D_UnitNormalVector_min_length;
extern f32 Math3D_NormalizedDistanceFromPlane_min_length;
extern f32 D_801E0158;
extern f32 D_801E015C;
extern f32 D_801E0160;
extern f32 D_801E0164;
extern f32 D_801E0168;
extern f32 D_801E016C;
extern f32 D_801E0170;
extern f32 D_801E0174;
extern f32 D_801E0178;
extern f32 D_801E017C;
extern f32 D_801E0180;
extern f32 D_801E0184;
extern f32 D_801E0188;
extern f32 D_801E018C;
extern f32 D_801E0190;
extern f32 D_801E0194;
extern f32 D_801E0198;
extern f32 D_801E019C;
extern f32 D_801E01A0;
extern f32 D_801E01A4;
extern f32 D_801E01A8;
extern f32 D_801E01AC;
extern f32 D_801E01B0;
extern f32 D_801E01B4;
extern f32 D_801E01B8;
extern f32 D_801E01BC;
extern f32 D_801E01C0;
extern f32 D_801E01C4;
extern f32 Math3D_ColSphereSphereIntersectAndDistance_min_intersect;
extern f32 D_801E01CC;
extern f32 D_801E01D0;
extern f32 D_801E01D4;
extern f32 D_801E01E0;
extern f32 D_801E01F0;
extern f32 D_801E01F4;
extern f32 D_801E01F8;
extern f32 D_801E0200;
extern f32 D_801E0204;
extern f32 D_801E0208;
extern f32 D_801E020C;
extern f32 D_801E0210;
extern f32 D_801E0214;
extern f32 D_801E0218;
extern f32 D_801E021C;
extern f32 D_801E0220;
extern f32 D_801E0224;
extern f32 D_801E0228;
extern char D_801E0230[];
extern char D_801E0238[];
extern char D_801E023C[];
extern char D_801E0240[];
extern char D_801E0248[];
extern char D_801E0250[];
extern char D_801E0258[];
extern char D_801E026C[];
extern f32 D_801E02A0;
extern f32 D_801E02B0;
extern f32 D_801E02B4;
extern f32 D_801E02B8;
extern f32 D_801E02D0;
extern char D_801E0300[];
extern char D_801E0330[];
extern char D_801E033C[];
extern char D_801E0348[];
extern char D_801E0354[];
extern f32 D_801E0384;
extern f32 D_801E0388;
extern f32 D_801E038C;
extern f32 D_801E04E0;
extern f32 D_801E04E4;
extern f32 D_801E04E8;
extern f32 D_801E04EC;
extern f32 D_801E04F0;
extern f32 D_801E04F4;
extern f32 D_801E04F8;
extern f32 D_801E04FC;
extern f32 D_801E0500;
extern f32 D_801E0504;
extern f32 D_801E0508;
extern f32 D_801E050C;
extern f32 D_801E0534;
extern f32 D_801E0538;
extern f32 D_801E05B4;
extern f32 D_801E05B8;
extern f32 D_801E05D0;
extern f32 D_801E05D4;
extern f32 D_801E0CEC;
extern f32 D_801E0CF0;
extern f32 D_801E0CF4;
extern f32 D_801E0CF8;
extern f32 D_801E0CFC;
extern f32 D_801E0D20;
extern f32 D_801E0D24;
extern f32 D_801E0D28;
extern f32 D_801E0D2C;
extern f32 D_801E0D30;
extern f32 D_801E0D34;
extern f64 D_801E0D58;
extern f32 D_801E0D60;
extern f32 D_801E0D64;
extern f32 D_801E0D68;
extern f32 D_801E0D8C;
extern f32 D_801E0D90;
extern f32 D_801E0D94;
extern f32 D_801E0D98;
extern f32 D_801E0D9C;
extern f32 D_801E0DBC;
extern f32 D_801E0DC0;
extern f32 D_801E0DC4;
extern f32 D_801E0DC8;
extern f32 D_801E0DCC;
extern f32 D_801E0DD0;
extern f32 D_801E0DD4;
extern f64 D_801E0DD8;
extern f64 D_801E0DE0;
extern f32 D_801E0DE8;
extern f32 D_801E0DEC;
extern f32 D_801E0DF0;
extern f32 D_801E0DF4;
extern f32 D_801E0DF8;
extern f32 D_801E0DFC;
extern f32 D_801E0E00;
extern f32 D_801E0E04;
extern f32 D_801E0E08;
extern f32 D_801E0E0C;
extern f32 D_801E0E10;
extern f32 D_801E0E14;
extern f32 D_801E0E18;
extern f32 D_801E0E1C;
extern f32 D_801E0E20;
extern f32 D_801E0E24;
extern f64 D_801E0EB0;
extern void* D_801E10B0;
extern EffTables sEffTable;
extern f32 D_801ED8C8;
extern f32 D_801ED8CC;
extern f32 D_801ED8D0;
extern Mtx D_801ED8E0;
extern FaultClient D_801ED930;
extern FaultAddrConvClient D_801ED940;
extern char D_801ED950[80];
extern char D_801ED9A0[80];
extern Vec3f D_801ED9F0;
extern Vec3f D_801ED9FC;
extern Vec3f D_801EDA08;
extern Vec3f D_801EDA18;
extern Vec3f D_801EDA24;
extern Vec3f D_801EDA30;
extern z_Matrix D_801EDA40;
extern Vec3f D_801EDA80;
extern Vec3f D_801EDA8C;
extern Vec3f D_801EDA98;
extern char D_801EDAA8[80];
extern char D_801EDAF8[80];
extern Vec3f D_801EDB48;
extern Vec3f D_01EDB54;
extern Vec3f D_01EDB60;
extern Vec3f D_01EDB70;
extern Vec3f D_801EDB7C;
extern Vec3f D_801EDB88;
extern f32 D_801EDB98;
extern f32 D_801EDB9C;
extern f32 D_801EDBA0;
extern Sphere16 D_801EDBA8;
extern TriNorm D_801EDBB0;
extern s16 D_801EDBF0;
extern Vec3f D_801EDE00;
extern Vec3f D_801EDE10;
extern Vec3f D_801EDE20;
extern Vec3f D_801EDE30;
extern TriNorm D_801EDE40;
extern TriNorm D_801EDE78;
extern LineSegment D_801EDEB0;
extern TriNorm D_801EDEC8;
extern TriNorm D_801EDF00;
extern Vec3f D_801EDF38;
extern Vec3f D_801EDF48;
extern TriNorm D_801EDF58;
extern TriNorm D_801EDF90;
extern LineSegment D_801EDFC8;
extern Vec3f D_801EDFE0;
extern Vec3f D_801EDFF0;
extern TriNorm D_801EE000;
extern TriNorm D_801EE038;
extern TriNorm D_801EE070[2];
extern Vec3f D_801EE0D8;
extern TriNorm D_801EE0E8[2];
extern TriNorm D_801EE150;
extern TriNorm D_801EE188;
extern Vec3f D_801EE1C0;
extern Vec3f D_801EE1D0;
extern Vec3f D_801EE1E0;
extern Vec3f D_801EE1F0;
extern EffSparkParams D_801EE200;
extern TriNorm D_801EE6C8;
extern TriNorm D_801EE700;
extern EffSparkParams D_801EE738;
extern EffSparkParams D_801EEC00;
extern EffSparkParams D_801EF0C8;
extern TriNorm D_801EF590;
extern TriNorm D_801EF5C8;
extern TriNorm D_801EF600;
extern TriNorm D_801EF638;
extern SaveContext gSaveContext;
extern GameInfo* gStaticContext;
extern ActorCutscene* actorCutscenes;
extern s16 actorCutsceneCount;
extern u8 actorCutsceneWaiting[16];
extern u8 actorCutsceneNextCutscenes[16];
extern f32 D_801F4E70;
extern LightsList lightsList;
extern Arena mainHeap;
extern s32* gNMIBuffer;
extern QuakeRequest sQuakeRequest[4];
extern Quake2Context sQuake2Context;
extern s32 gSceneProcStep;
extern u32 gSceneProcFlags;
extern f32 gSceneProcFlashingAlpha;
extern s32 D_801F5AB0;
extern s32 D_801F5AB4;
extern ShrinkWindowContext gShrinkWindowContext;
extern ShrinkWindowContext* gShrinkWindowContextPtr;
extern Input D_801F6C18;
extern s32 D_801F6D10;
extern ColorRGBA8 D_801F6D30;
extern u8 D_801F6DFC;
extern s8018571C D_801F6E00;
extern StackEntry slowlyStackEntry;
extern u8 slowlyStack[4096];
extern s8 D_801F7FF0;
extern struct_801F8010 D_801F8010;
extern struct_801F8020 D_801F8020;
extern VisMono sMonoColors;
extern s8 D_801F8048;
extern FaultAddrConvClient grapgFaultAddrConvClient;
extern FaultClient graphFaultClient;
extern Gfx* graphDlEntry;
extern u64 lastRenderFrameTimestamp;
extern OSMesgQueue siEventCallbackQueue;
extern OSMesg siEventCallbackBuffer[1];
extern u32 gRspSegmentPhysAddrs[(16)];
extern SchedThreadStruct schedContext;
extern OSMesgQueueListNode mainIrqmgrCallbackNode;
extern OSMesgQueue mainIrqmgrCallbackQueue;
extern OSMesg mainIrqCallbackBuffer[60];
extern OSThread graphOSThread;
extern u8 graphStack[6144];
extern u8 schedStack[1536];
extern u8 audioStack[2048];
extern u8 padmgrStack[1280];
extern StackEntry graphStackEntry;
extern StackEntry schedStackEntry;
extern StackEntry audioStackEntry;
extern StackEntry padmgrStackEntry;
extern AudioThreadStruct audioContext;
extern PadmgrThreadStruct D_801FB620;
extern volatile OSTime D_801FBAF0;
extern volatile OSTime lastRenderFrameDuration;
extern OSViMode D_801FBB30;
extern u32* gFramebuffers[2];
extern OSViMode* D_801FBB88;
extern u16* gZBufferPtr;
extern u16* sys_cfb_zbufl;
extern u16** sys_cfb_wbufl;
extern u16** sys_cfb_fifol;
extern s16 D_801FBBCC;
extern s16 D_801FBBCE;
extern Vec3f D_801FBBF0;
extern LineSegment Math3D_ColSphereTri_line;
extern Vec3f Math3D_ColSphereTri_point;
extern Vec3f Math3D_NormalVector_temp1;
extern Vec3f Math3D_NormalVector_temp2;
extern f32 D_801FBC8C;
extern f32 D_801FBC90;
extern f32 D_801FBC98;
extern f32 D_801FBCA4;
extern f32 D_801FBCAC;
extern f32 D_801FBCB0;
extern f32 D_801FBCB4;
extern f32 D_801FBCB8;
extern f32 D_801FBCBC;
extern f32 D_801FBCC0;
extern f32 D_801FBCC4;
extern f32 D_801FBCC8;
extern f32 D_801FBCCC;
extern f32 D_801FBCD0;
extern f32 D_801FBCD4;
extern f32 D_801FBCD8;
extern f32 D_801FBCDC;
extern Vec3f Math3D_UnitNormalVector_temp;
extern Vec3f D_801FBD80[2];
extern Vec3f D_801FBD98;
extern Vec3f D_801FBDA4;
extern Vec3f D_801FBDE8;
extern z_Matrix* matrixState;
extern z_Matrix* matrixCurrentState;
extern u8 sys_flashromStack[4096];
extern StackEntry sys_flashromStackEntry;
extern OSThread sys_flashromOSThread;
extern s80185D40 D_801FD008;
extern OSMesg D_801FD034;
extern OSIoMesg D_801FD050;
extern OSMesgQueue D_801FD068;
extern OSPiHandle D_801FD080;
extern s801FE7C0 D_801FE7C0[1];
extern OSMesgQueue D_80202980;
extern OSMesgQueue D_80202AB0;
extern OSMesg D_80202AC8[16];
extern OSMesgQueue D_80202B08;
extern OSMesg D_80202B20[16];
extern OSMesgQueue D_80202B60;
extern OSMesg D_80202B78[64];
extern OSMesgQueue D_80203278;
extern OSMesg D_80203290[1];
extern GfxPool gGfxPools[2];
extern u8 gAudioHeap[1277952];
extern u32 gSystemHeap[1046224];
extern u8 D_80780000[17920];
extern u8 D_80784600[352768];
extern u16 D_807DA800[76800];
extern u32 osVirtualToPhysical(void*);
extern void* osPhysicalToVirtual(u32);
extern GraphicsContext* __gfxCtx;
struct DmSa;
typedef void (*DmSaActionFunc)(struct DmSa*, GlobalContext*);
typedef struct DmSa {
                Actor actor;
                SkelAnime skelAnime;
                char unk194[0x108];
                DmSaActionFunc actionFunc;
                char unk294[0x4C];
                u16 unk2E0;
                char unk2E2[0xE];
                u32 unk2F0;
} DmSa;
extern const ActorInit Dm_Sa_InitVars;
void DmSa_Init(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Update(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80A2EABC(DmSa* this, GlobalContext* globalCtx);
extern SkeletonHeader D_06013328;
extern AnimationHeader D_0600CC94;
extern ActorAnimationEntry D_80A2ED00[];
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2E960.asm")
void DmSa_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmSa* this = ((DmSa*)thisx);
    this->unk2E0 = 0;
    this->unk2F0 = 0xFF;
    this->actor.targetArrowOffset = 3000.0f;
    Actor_SetDrawParams(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013328, 0, 0, 0, 0);
    func_80A2E960(&this->skelAnime, &D_80A2ED00, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80A2EABC;
}
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Destroy.asm")
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EABC.asm")
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Update.asm")
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB10.asm")
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB2C.asm")
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB44.asm")
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB58.asm")
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EBB0.asm")
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Draw.asm")
