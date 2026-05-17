/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SharedLibrary.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    动态库加载相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2024-01-01    V1.0.0.0
****************************************************************************/
#include "SharedLibrary.h"
#include <dlfcn.h>

Void *SharedLibOpen(const S8 *Path)
{
    return dlopen(Path, RTLD_LAZY);
}

S32 SharedLibClose(Void *Handle)
{
    return dlclose(Handle);
}

Void *SharedLibSym(Void *Handle, const S8 *Symbol)
{
    return dlsym(Handle, Symbol);
}

S8 *SharedLibError(Void)
{
    return (S8 *)dlerror();
}

#ifdef TEST_OPEN
S32 SharedLibraryTest(Void)
{
    Void *Handle;
    S8 *Error;
    Void (*Func)(Void);

    Handle = SharedLibOpen("libc.so.6");
    if(Null == Handle)
    {
        Error = SharedLibError();
        printf("SharedLibOpen failed: %s\n", Error ? Error : "unknown");
        /* 尝试 macOS 路径 */
        Handle = SharedLibOpen("libSystem.dylib");
        if(Null == Handle)
        {
            Error = SharedLibError();
            printf("SharedLibOpen libSystem.dylib also failed: %s\n", Error ? Error : "unknown");
            printf("SharedLibrary Test Skip (no suitable shared library found)!\n");
            return 0;
        }
    }

    /* 尝试查找一个常见的函数 */
    Func = (Void (*)(Void))SharedLibSym(Handle, "printf");
    if(Null == Func)
    {
        Error = SharedLibError();
        printf("SharedLibSym failed: %s\n", Error ? Error : "unknown");
        SharedLibClose(Handle);
        return -1;
    }

    printf("Successfully loaded shared library and found printf symbol!\n");

    SharedLibClose(Handle);
    printf("SharedLibraryTest Success!\n");
    return 0;
}
#endif
