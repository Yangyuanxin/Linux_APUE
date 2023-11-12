#include "Inotify.h"

S32 RunInotifyTest(Void)
{
    S32 Len;
    S32 Fd, Wd;  
    S8 Buf[BUF_LEN];
    struct inotify_event *Event;
    printf("Run RunInotifyTest!\n");

    Fd = inotify_init();  
    if (Fd < 0) 
    {  
        perror("inotify_init");  
        return -1;
    }

    Wd = inotify_add_watch(Fd, "/run", IN_ALL_EVENTS);  
    if (Wd < 0)
    {  
        perror("inotify_add_watch");  
        return -2;  
    }

    for(;;) 
    {  
        Len = read(Fd, Buf, BUF_LEN);  
        if (Len < 0) 
        {  
            perror("read");  
            return -3;  
        }  
  
        Event = (struct inotify_event *)Buf;
        printf("Received event: %s\n", Event->name);
        break;
    }

    return 0;
}
