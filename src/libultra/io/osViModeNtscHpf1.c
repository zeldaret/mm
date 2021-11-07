#include "global.h"

OSViMode osViModeNtscHpf1 = {
    9, // type
    {
        // comRegs
        0x324E,    // ctrl
        640,       // width
        0x3E52239, // burst
        0x20C,     // vSync
        0xC15,     // hSync
        0xC150C15, // leap
        0x6C02EC,  // hStart
        0x400,     // xScale
        0          // vCurrent
    },
    { // fldRegs
      {
          // [0]
          0x500,     // origin
          0x2000800, // yScale
          0x2301FD,  // vStart
          0xE0204,   // vBurst
          2,         // vIntr
      },
      {
          // [1]
          0xA00,     // origin
          0x2000800, // yScale
          0x2501FF,  // vStart
          0xE0204,   // vBurst
          2          // vIntr
      } },
};
