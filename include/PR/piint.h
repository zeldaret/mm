#ifndef PR_PIINT_H
#define PR_PIINT_H

#include "ultratypes.h"
#include "os_pi.h"
#include "libc/stdint.h"

#define LEO_BASE_REG 0x05000000

#define LEO_CMD (LEO_BASE_REG + 0x508)
#define LEO_STATUS (LEO_BASE_REG + 0x508)

#define LEO_BM_CTL (LEO_BASE_REG + 0x510)
#define LEO_BM_STATUS (LEO_BASE_REG + 0x510)

#define LEO_SEQ_CTL (LEO_BASE_REG + 0x518)
#define LEO_SEQ_STATUS (LEO_BASE_REG + 0x518)

#define LEO_C2_BUFF (LEO_BASE_REG + 0x000)      // C2 Sector Buffer
#define LEO_SECTOR_BUFF (LEO_BASE_REG + 0x400)  // Data Sector Buffer
#define LEO_DATA (LEO_BASE_REG + 0x500)         // Data
#define LEO_MISC_REG (LEO_BASE_REG + 0x504)     // Misc Register
#define LEO_CUR_TK (LEO_BASE_REG + 0x50C)       // Current Track
#define LEO_ERR_SECTOR (LEO_BASE_REG + 0x514)   // Sector Error Status
#define LEO_CUR_SECTOR (LEO_BASE_REG + 0x51C)   // Current Sector
#define LEO_HARD_RESET (LEO_BASE_REG + 0x520)   // Hard Reset
#define LEO_C1_S0 (LEO_BASE_REG + 0x524)        // C1
#define LEO_HOST_SECBYTE (LEO_BASE_REG + 0x528) // Sector Size (in bytes)
#define LEO_C1_S2 (LEO_BASE_REG + 0x52C)        // C1
#define LEO_SEC_BYTE (LEO_BASE_REG + 0x530)     // Sectors per Block, Full Size
#define LEO_C1_S4 (LEO_BASE_REG + 0x534)        // C1
#define LEO_C1_S6 (LEO_BASE_REG + 0x538)        // C1
#define LEO_CUR_ADDR (LEO_BASE_REG + 0x53C)     // Current Address?
#define LEO_ID_REG (LEO_BASE_REG + 0x540)       // ID
#define LEO_TEST_REG (LEO_BASE_REG + 0x544)     // Test Read
#define LEO_TEST_PIN_SEL (LEO_BASE_REG + 0x548) // Test Write
#define LEO_RAM_ADDR (LEO_BASE_REG + 0x580)     // Microsequencer RAM

#define LEO_STATUS_PRESENCE_MASK 0xFFFF

#define LEO_STATUS_DATA_REQUEST 0x40000000
#define LEO_STATUS_C2_TRANSFER 0x10000000
#define LEO_STATUS_BUFFER_MANAGER_ERROR 0x08000000
#define LEO_STATUS_BUFFER_MANAGER_INTERRUPT 0x04000000
#define LEO_STATUS_MECHANIC_INTERRUPT 0x02000000
#define LEO_STATUS_DISK_PRESENT 0x01000000
#define LEO_STATUS_BUSY_STATE 0x00800000
#define LEO_STATUS_RESET_STATE 0x00400000
#define LEO_STATUS_MOTOR_NOT_SPINNING 0x00100000
#define LEO_STATUS_HEAD_RETRACTED 0x00080000
#define LEO_STATUS_WRITE_PROTECT_ERROR 0x00040000
#define LEO_STATUS_MECHANIC_ERROR 0x00020000
#define LEO_STATUS_DISK_CHANGE 0x00010000

#define LEO_STATUS_MODE_MASK (LEO_STATUS_MOTOR_NOT_SPINNING | LEO_STATUS_HEAD_RETRACTED)
#define LEO_STATUS_MODE_SLEEP (LEO_STATUS_MOTOR_NOT_SPINNING | LEO_STATUS_HEAD_RETRACTED)
#define LEO_STATUS_MODE_STANDBY (LEO_STATUS_HEAD_RETRACTED)
#define LEO_STATUS_MODE_ACTIVE 0

#define LEO_CUR_TK_INDEX_LOCK 0x60000000

#define LEO_BM_STATUS_RUNNING 0x80000000      // Running
#define LEO_BM_STATUS_ERROR 0x04000000        // Error
#define LEO_BM_STATUS_MICRO 0x02000000        // Micro Status?
#define LEO_BM_STATUS_BLOCK 0x01000000        // Block Transfer
#define LEO_BM_STATUS_C1CORRECTION 0x00800000 // C1 Correction
#define LEO_BM_STATUS_C1DOUBLE 0x00400000     // C1 Double
#define LEO_BM_STATUS_C1SINGLE 0x00200000     // C1 Single
#define LEO_BM_STATUS_C1ERROR 0x00010000      // C1 Error

#define LEO_BM_CTL_START 0x80000000             // Start Buffer Manager
#define LEO_BM_CTL_MODE 0x40000000              // Buffer Manager Mode
#define LEO_BM_CTL_IMASK 0x20000000             // BM Interrupt Mask
#define LEO_BM_CTL_RESET 0x10000000             // Buffer Manager Reset
#define LEO_BM_CTL_DISABLE_OR 0x08000000        // Disable OR Check?
#define LEO_BM_CTL_DISABLE_C1 0x04000000        // Disable C1 Correction
#define LEO_BM_CTL_BLOCK 0x02000000             // Block Transfer
#define LEO_BM_CTL_CLR_MECHANIC_INTR 0x01000000 // Mechanic Interrupt Reset

#define LEO_BM_CTL_CONTROL_MASK 0xFF000000
#define LEO_BM_CTL_SECTOR_MASK 0x00FF0000
#define LEO_BM_CTL_SECTOR_SHIFT 16

extern OSDevMgr __osPiDevMgr;
extern OSPiHandle* __osCurrentHandle[];
extern u32 __osPiAccessQueueEnabled;

extern OSPiHandle __Dom1SpeedParam;
extern OSPiHandle __Dom2SpeedParam;

extern OSMesgQueue __osPiAccessQueue;

void __osDevMgrMain(void* arg);
void __osPiCreateAccessQueue(void);
void __osPiRelAccess(void);
void __osPiGetAccess(void);
s32 __osPiRawStartDma(s32 direction, uintptr_t devAddr, void* dramAddr, size_t size);
s32 __osEPiRawWriteIo(OSPiHandle* handle, uintptr_t devAddr, u32 data);
s32 __osEPiRawReadIo(OSPiHandle* handle, uintptr_t devAddr, u32* data);
s32 __osEPiRawStartDma(OSPiHandle* handle, s32 direction, uintptr_t cartAddr, void* dramAddr, size_t size);
OSMesgQueue* osPiGetCmdQueue(void);

#endif
