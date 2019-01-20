 ///
 /// @file    zy1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-20 21:14:13
 ///
 
#include "func.h"
#define N 10000000
int main()
{
	int shmid;
	shmid = shmget(1234,4096,IPC_CREAT|0600);
	if(-1 == shmid)
	{
		perror("shmget");
		return -1;
	}
	printf("shmid=%d\n",shmid);
	int *p;
	p=(int*)shmat(shmid,NULL,0);
	if((int*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	p[0]=0;
	int i = 0;
	return 0;
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			p[0]=p[0]+1;
		}
		return 0;
	}else{	
		for(i=0;i<N;i++)
		{
			p[0]=p[0]+1;
		}
		wait(NULL);
		printf("p[0]=%d\n",p[0]);
		int ret=shmctl(shmid,IPC_RMID,NULL);//删除共享内存
		if(-1==ret)
		{
			perror("shmctl");
			return -1;
		}
		return 0;
	}
	return 0;

}
