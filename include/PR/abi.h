#ifndef _ABI_H_
#define _ABI_H_

typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int gain : 16;
    /* 0x4 */ unsigned int addr;
} Aadpcm;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int gain : 16;
    /* 0x4 */ unsigned int addr;
} Apolef;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int pad1 : 16;
    /* 0x4 */ unsigned int addr;
} Aenvelope;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int pad1 : 8;
    /* 0x2 */ unsigned int dmem : 16;
    /* 0x4 */ unsigned int pad2 : 16;
    /* 0x6 */ unsigned int count : 16;
} Aclearbuff;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int pad1 : 8;
    /* 0x2 */ unsigned int pad2 : 16;
    /* 0x4 */ unsigned int inL : 16;
    /* 0x6 */ unsigned int inR : 16;
} Ainterleave;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int pad1 : 24;
    /* 0x4 */ unsigned int addr;
} Aloadbuff;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int pad1 : 16;
    /* 0x4 */ unsigned int addr;
} Aenvmixer;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int gain : 16;
    /* 0x4 */ unsigned int dmemi : 16;
    /* 0x6 */ unsigned int dmemo : 16;
} Amixer;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int dmem2 : 16;
    /* 0x4 */ unsigned int addr;
} Apan;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int pitch : 16;
    /* 0x4 */ unsigned int addr;
} Aresample;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int pad1 : 16;
    /* 0x4 */ unsigned int addr;
} Areverb;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int pad1 : 24;
    /* 0x4 */ unsigned int addr;
} Asavebuff;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int pad1 : 24;
    /* 0x4 */ unsigned int pad2 : 2;
    /* 0x4 */ unsigned int number : 4;
    /* 0x4 */ unsigned int base : 24;
} Asegment;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int dmemin : 16;
    /* 0x4 */ unsigned int dmemout : 16;
    /* 0x6 */ unsigned int count : 16;
} Asetbuff;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int flags : 8;
    /* 0x2 */ unsigned int vol : 16;
    /* 0x4 */ unsigned int voltgt : 16;
    /* 0x6 */ unsigned int volrate : 16;
} Asetvol;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int pad1 : 8;
    /* 0x2 */ unsigned int dmemin : 16;
    /* 0x4 */ unsigned int dmemout : 16;
    /* 0x6 */ unsigned int count : 16;
} Admemmove;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int pad1 : 8;
    /* 0x2 */ unsigned int count : 16;
    /* 0x4 */ unsigned int addr;
} Aloadadpcm;


typedef struct {
    /* 0x0 */ unsigned int cmd : 8;
    /* 0x1 */ unsigned int pad1 : 8;
    /* 0x2 */ unsigned int pad2 : 16;
    /* 0x4 */ unsigned int addr;
} Asetloop;


typedef struct {
    /* 0x0 */ unsigned int w0;
    /* 0x4 */ unsigned int w1;
} Awords;


typedef union {
    /* 0x0 */ Awords words;
    /* 0x0 */ Aadpcm adpcm;
    /* 0x0 */ Apolef polef;
    /* 0x0 */ Aclearbuff clearbuff;
    /* 0x0 */ Aenvelope envelope;
    /* 0x0 */ Ainterleave interleave;
    /* 0x0 */ Aloadbuff loadbuff;
    /* 0x0 */ Aenvmixer envmixer;
    /* 0x0 */ Aresample resample;
    /* 0x0 */ Areverb reverb;
    /* 0x0 */ Asavebuff savebuff;
    /* 0x0 */ Asegment segment;
    /* 0x0 */ Asetbuff setbuff;
    /* 0x0 */ Asetvol setvol;
    /* 0x0 */ Admemmove dmemmove;
    /* 0x0 */ Aloadadpcm loadadpcm;
    /* 0x0 */ Amixer mixer;
    /* 0x0 */ Asetloop setloop;
    /* 0x0 */ long long force_union_align;
} Acmd;

typedef short ADPCM_STATE[16];

typedef short POLEF_STATE[4];

typedef short RESAMPLE_STATE[16];

typedef short ENVMIX_STATE[40];

#endif
