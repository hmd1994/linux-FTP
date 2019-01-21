 ///
 /// @file    zy1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-21 10:21:59
 ///创建消息队列，fork子进程，父进程发消息，子进程接消息并打印，
 //然后父进程收回子进程，然后删除消息队列
 
#include "func.h"
typedef struct{
	long mtype;
	char buf[64];
}MSG;
int main()
{
	int msgid=msgget(1234,IPC_CREAT|0600);
	if(-1==msgid)
	{
		perror("msgget");
	}
	int ret;
	MSG msg;
	bzero(&msg,sizeof(msg));
	if(!fork())
	{
		ret=msgrcv(msgid,&msg,sizeof(msg.buf),1,0);
		if(-1==ret)
		{
			perror("msgrcv");
			return -1;
		}
		printf("ret=%d\n",ret);
		printf("buf=%s\n",msg.buf);
		return 0;
	}else
	{
		msg.mtype=1;
		strcpy(msg.buf,"world");
		ret=msgsnd(msgid,&msg,sizeof(msg.buf),0);
		if(-1==ret)
		{
			perror("msgsnd");
			return -1;
		}
		wait(NULL);
		ret=msgctl(msgid,IPC_RMID,NULL);
		if(-1==ret)
		{
			perror("msgget");
			return -1;
		}
		exit(0);
	}
	return 0;
}
