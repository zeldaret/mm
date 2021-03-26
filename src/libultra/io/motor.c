#include <ultra64.h>
#include <global.h>

s32 __osMotorAccess(OSPfs* pfs, u32 vibrate) {
    s32 i;
    s32 ret;
    u8* buf = (u8*)&osPifBuffers[pfs->channel];

    if (!(pfs->status & 8)) {
        return 5;
    }

    __osSiGetAccess();
    osPifBuffers[pfs->channel].pifstatus = 1;
    buf += pfs->channel;
    for (i = 0; i < BLOCKSIZE; i++) {
        ((__OSContRamReadFormat*)buf)->data[i] = vibrate;
    }

    __osContLastCmd = CONT_CMD_END;
    __osSiRawStartDma(OS_WRITE, &osPifBuffers[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    __osSiRawStartDma(OS_READ, &osPifBuffers[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);

    ret = ((__OSContRamReadFormat*)buf)->rxsize & 0xC0;
    if (!ret) {
        if (!vibrate) {
            if (((__OSContRamReadFormat*)buf)->datacrc != 0) {
                ret = PFS_ERR_CONTRFAIL;
            }
        } else {
            if (((__OSContRamReadFormat*)buf)->datacrc != 0xEB) {
                ret = PFS_ERR_CONTRFAIL;
            }
        }
    }

    __osSiRelAccess();

    return ret;
}
void __osSetupMotorWrite(s32 channel, OSPifRam* buf) {
    u8* bufptr = (u8*)buf;
    __OSContRamReadFormat mempakwr;
    s32 i;

    mempakwr.dummy = 0xFF;
    mempakwr.txsize = 0x23;
    mempakwr.rxsize = 1;
    mempakwr.cmd = 3; // write mempak
    mempakwr.hi = 0x600 >> 3;
    mempakwr.lo = (u8)(__osContAddressCrc(0x600) | (0x600 << 5));

    if (channel != 0) {
        for (i = 0; i < channel; ++i) {
            *bufptr++ = 0;
        }
    }

    *(__OSContRamReadFormat*)bufptr = mempakwr;
    bufptr += sizeof(mempakwr);
    *bufptr = 0xFE;
}

#pragma GLOBAL_ASM("./asm/non_matchings/boot/motor/osMotorInit.asm")
