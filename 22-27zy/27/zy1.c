 ///
 /// @file    zy1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-21 19:22:44
 ///
 
#include "func.h"
void sig(int signum,siginfo_t *p,void *p1)
{
	printf("before sleep %d is coming\n",signum);
	sleep(3);
	sigset_t pend;
	sigemptyset(&pend);//q清空
	sigpending(&pend);
	if(sigismember(&pend,SIGQUIT))
	{
		printf("SIGQUIT is pend\n");
	}else{
		printf("SIGQUIT is not pend\n");
	}
	printf("after sleep %d is coming\n",signum);
}
int main()
{
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_sigaction = sig;
	act.sa_flags=SA_SIGINFO;
	sigemptyset(&act.sa_mask);//清空集合
	sigaddset(&act.sa_mask,SIGQUIT);
	int ret;
	ret=sigaction(SIGINT,&act,NULL);
	if(-1==ret)
	{
		perror("sigaction");
		return -1;
	}
	sigaction(SIGQUIT,&act,NULL);
	while(1);
	return 0;
}
