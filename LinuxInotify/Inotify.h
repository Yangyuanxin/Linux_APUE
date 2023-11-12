#ifndef __INOTIFY_H
#define __INOTIFY_H

#ifdef __cplusplus
extern "C" {
#endif
#include "SystemConfig.h"

#define EVENT_SIZE  (sizeof(struct inotify_event))  
#define BUF_LEN      (1024 * (EVENT_SIZE + 16))

#ifdef TEST_OPEN
S32 RunInotifyTest(Void);
#endif

#ifdef __cplusplus
}
#endif








#endif //__INOTIFY_H
