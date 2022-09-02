/****************************************************************************
  Copyright(C)    2022, morixinguan@vip.qq.com
  File name :     SystemVMsg.c
  Author :        Yangyuanxin
  Version:        1.0
  Description:    System-V共享内存相关接口及测试程序实现
  Other:
  Mode History:
          <author>        <time>      <version>   <desc>
          Yangyuanxin    2022-9-2      V1.0.0.0
****************************************************************************/
#include "SystemVShareMem.h"

S32 SystemVShareMemOpen(SystemVShareMemKey_t Key, S32 MemSize)
{
	S32 Fd = -1;
	
	Fd = shmget(Key, MemSize, IPC_CREAT | 0600);
	if(Fd < 0)
	{
		printf("shmget fail!\n");
		return -1;
	}
	
	return Fd;
}

S32 SystemVShareMemClose(S32 Fd)
{
	return shmctl(Fd, IPC_RMID, 0);
}


#ifdef TEST_OPEN

S32 SystemVShareMemTest(Void)
{
    return 0;
}
#endif

