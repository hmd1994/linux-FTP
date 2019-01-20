 ///
 /// @file    zy3.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-19 21:39:03
 ///通过fork创建进程，能够产生僵尸进程
 
#include "func.h"

int main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		exit(10);
	}
	else
	{
		sleep(20);
	}
}
