 ///
 /// @file    zy1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-21 19:22:44
 ///
 
#include "func.h"
int main()
{
	sigset_t mask;
	sigemptyset(&mask);//清空阻塞信号集合
	sigaddset(&mask,SIGINT);
	int ret;
	ret=sigprocmask(SIG_BLOCK,&mask,NULL);
	if(-1==ret)
	{
		perror("sigprocmask");
		return -1;
	}
	sleep(5);
	sigset_t pend;
	sigemptyset(&pend);
	sigpending(&pend);
	if(sigismember(&pend,SIGINT))
	{
		printf("SIGINT is pending\n");
	}else{
		printf("SIGINT is not pending\n");
	}
	ret = sigprocmask(SIG_UNBLOCK,&mask,NULL);
	if(-1==ret)
	{
		perror("sigprocmask1");
		return -1;
	}
	return 0;
}
