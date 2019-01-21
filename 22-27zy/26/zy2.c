 ///
 /// @file    zy2.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-21 15:19:19
 ///
 
#include "func.h"
void sig(int signum)
{
	printf("%d is coming\n",signum);
	exit(1);
}
int main()
{
	if(signal(SIGINT,sig)==SIG_ERR)
	{
		perror("signal");
		return -1;
	}
	sleep(5);
	return 0;
}
