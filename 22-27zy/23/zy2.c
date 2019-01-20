 ///
 /// @file    zy2.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-19 21:32:04
 ///得到孤儿进程
 
#include "func.h"
int main()
{
	pid_t pid= fork();
	if(pid == 0)
	{
		while(1);
	}
	else
	{
		exit(10);
	}
}
