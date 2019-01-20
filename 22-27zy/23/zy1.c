 ///
 /// @file    zy1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-19 15:19:55
 ///通过fork创建子进程，让父子进程打印pid，都处于while(1),用ps进程查看
 //查看完毕用kill命令杀
 
#include "func.h"
int main()
{
	pid_t pid;
	pid=fork();
	if(0==pid)
	{
		printf("I am child,mypid=%d,myppid=%d\n",getpid(),getppid());
		while(1);
	}else{
		printf("I am parent ,pid=%d,mypid=%d\n",pid,getpid());
		while(1);
		return 0;
	}
}
