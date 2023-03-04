#ifndef ULTRA64_OS_H
#define ULTRA64_OS_H

#include "os_ai.h"
#include "os_cache.h"
#include "os_cont.h"
#include "os_convert.h"
#include "os_exception.h"
#include "os_flash.h"
#include "os_host.h"
#include "os_internal_error.h"
#include "os_internal_reg.h"
#include "os_internal_si.h"
#include "os_internal.h"
#include "os_libc.h"
#include "os_message.h"
#include "os_pfs.h"
#include "os_pi.h"
#include "os_reg.h"
#include "os_system.h"
#include "os_thread.h"
#include "os_time.h"
#include "os_tlb.h"
#include "os_voice.h"

// TODO: figure out proper header to put this
s32 __osContChannelReset(OSMesgQueue* mq, s32 channel);

#endif
