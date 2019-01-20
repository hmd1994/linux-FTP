 ///
 /// @file    zy1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-20 21:14:13
 ///两个进程对一个共享内存各加1000万，使用信号量，保证加后的结果为两千万，
 //结束后删除共享内
 
#include "func.h"
#define N 100000000
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

	int sem_id;//信号量
	sem_id = semget(1234,1,IPC_CREAT|0600);
	if(-1==sem_id)
	{
		perror("semget");
		return -1;
	}
	int	ret=semctl(sem_id,0,SETVAL,1);//初始化信号量的值
	if(-1==ret)
	{
		perror("semctl");
		return -1;
	}

	int *p;
	p=(int*)shmat(shmid,NULL,0);
	if((int*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	p[0]=0;
	int i = 0;
	
	struct sembuf sopp,sopv;
	bzero(&sopp,sizeof(sopp));
	bzero(&sopv,sizeof(sopv));
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;

	time_t start,end;
	start=time(NULL);
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			semop(sem_id,&sopp,1);
			p[0]=p[0]+1;
			semop(sem_id,&sopv,1);
		}
		return 0;
	}else{	
		for(i=0;i<N;i++)
		{
			semop(sem_id,&sopp,1);
			p[0]=p[0]+1;
			semop(sem_id,&sopv,1);
		}
		wait(NULL);
		end=time(NULL);
		printf("p[0]=%d,total=%ld\n",p[0],end-start);

		int ret=shmctl(shmid,IPC_RMID,NULL);//删除共享内存
		if(-1==ret)
		{
			perror("shmctl");
			return -1;
		}
		int ret_sem=shmctl(shmid,IPC_RMID,NULL);//删除信号量
		if(-1==ret_sem)
		{
			perror("shmctl");
			return -1;
		}
		return 0;
	}
	return 0;

}
