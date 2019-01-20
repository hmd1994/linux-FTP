 ///
 /// @file    zy1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-20 20:30:57
 ///
 
#include "func.h"
int main()
{
	int fds[2];
	pipe(fds);
	if(!fork())
	{//子进程
		close(fds[0]);//关闭读端
		char j[10]="hello";
		write(fds[1]/*写端*/,&j/*写入内容*/,strlen(j));
		return 0;
	}else{//父进程	
		close(fds[1]);//关闭读端
		char j[10]="hello";
		read(fds[1]/*写端*/,&j/*写入内容*/,strlen(j));
		printf("i am parent %s\n",j);
		wait(NULL);
		return 0;
	}
}
