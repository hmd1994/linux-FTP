 ///
 /// @file    zy2.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-21 15:19:19
 ///
 
#include "func.h"
void sig(int signo,siginfo_t *p,void *p1)
{
	printf("before sleep %d is coming\n",signo);
	sleep(3);
	printf("after sleep %d is coming\n",signo);
}
int main()
{
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_sigaction = sig;
	act.sa_flags=SA_SIGINFO|SA_NODEFER;
	int ret;
	ret=sigaction(SIGINT,&act,NULL);
	if(-1==ret)
	{
		perror("sigaction");
		return -1;
	}
	sigaction(SIGQUIT,&act,NULL);
	while(1);
	exit(0);
}
