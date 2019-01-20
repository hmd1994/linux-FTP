 ///
 /// @file    zy4.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-19 21:59:41
 ///实现一个守护进程，让其后台执行，每隔三秒向/tmp/file文件写一句话
 
#include "func.h"
int main()
{
	char buf[30]="i have sleep 3 second";
	int fd;
	fd=open("/tmp/file",O_RDWR|O_CREAT);
	char message_buf[30];
	int count =1;
	time_t timep;
	if(!fork())
	{
		setsid();
		chdir("/");
		umask(0);
		int i;
		for(i=0;i<3;i++)
		{
			close(i);
		}
		while(1)
		{
			sleep(3);
			timep=time(0);
			bzero(message_buf,128);
			sprintf(message_buf,"%d%s  %s",count++,buf,ctime(&timep));
			if(write(fd,message_buf,strlen(message_buf))<0)
			{
				perror("write");
			}
		}
	}else{
		exit(0);
	}
}
