 ///
 /// @file    zy4.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-19 21:59:41
 ///通过fork创建子进程，然后父进程通过wait回收，同时拿到子进程的返回值
 
#include "func.h"
int main()
{
	printf("parent is %d\n",getpid());
	pid_t iRet=fork();
	if(iRet<0)
	{
		printf("error\n");
	}else if(iRet==0)
	{
		printf("child id = %d,ppid = %d\n",getpid(),getppid());
		exit(10);
	}else
	{
		printf("parent child id=%d\n",iRet);
		wait(NULL);
		sleep(20);
	}
}
