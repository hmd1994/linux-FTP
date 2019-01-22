#include "func.h"
#define SHM_KEY (key_t)1234
typedef struct shmmsg{
	int flag;
	char buf[4092];
}shm_buf;
int shmid;
int semid;
//创建共享内存
int shm()
{
	shmid = shmget((key_t)1234,4096,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmid");
		return -1;
	}
	return shmid;
}
int shmatt(int shmid)
{
	char *p;
	p=(char*)shmat(shmid,NULL,0);
	if((char*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	return 1;
}
void seminit()
{
	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	}arg;
	arg.val=1;
	semid = semget((key_t)4321,1,IPC_CREAT|0600);//打开或者创建信号量
	if(-1 == semid)
	{
		perror("semget");
		return;
	}
	int ret = semctl(semid,0,SETVAL,arg);
	if(-1==ret)
	{
		perror("semctl");
		exit(-1);
	}

}
void ctrl()
{
	//删除共享内存
	int ret=shmctl(shmid,IPC_RMID,NULL);
	if(-1==ret)
	{
		perror("shmctl");
		exit(-1);
	}
	ret=semctl(semid,0,IPC_RMID);
	if(-1==ret)
	{
		perror("semctl");
		exit(-1);
	}
	return;
}

void sig(int signum,siginfo_t *p1,void *p2)
{
	ctrl();
	exit(0);
}


//管道的读端
int main(int argc,char *argv[])
{
	//创建共享内存
	int shmid=shm();
	char message_buf[3072];
	time_t timep;
	char username_buf[40]="用户A";

	//信号量的处理
	struct sigaction sig_act;
	bzero(&sig_act,sizeof(struct sigaction));
	sig_act.sa_sigaction=sig;
	sig_act.sa_flags=SA_SIGINFO;
	int ret=sigaction(SIGINT,&sig_act,NULL);
	if(-1==ret)
	{
		perror("sigaction");
		return -1;
	}
	seminit();

	//判断传参是否正确
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}

	//设置管道的读写端
	int fdr,fdw;
	fdr=open(argv[1],O_RDONLY);//必须O_RDONLY
	if(-1==fdr)
	{
		perror("open");
		return -1;
	}
	fdw=open(argv[2],O_WRONLY);//必须O_WRONLY
	if(-1==fdw)
	{
		perror("open");
		return -1;
	}
	
	printf("I am A\n");
	char buf[128]={0};
	fd_set rdset;

	//信号量锁
	struct sembuf sopp,sopv;
	sopp.sem_num = 0;
	sopp.sem_op= -1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num = 0;
	sopv.sem_op= 1;
	sopv.sem_flg=SEM_UNDO;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(fdr,&rdset);
		ret=select(fdr+1,&rdset,NULL,NULL,NULL);//传入传出参数
		if(ret>0)
		{
			if(FD_ISSET(fdr,&rdset))//如果管道可读
			{
				memset(buf,0,sizeof(buf));
				memset(message_buf,0,sizeof(message_buf));
				ret=read(fdr,buf,sizeof(buf));//如果管道内没有数据，read会阻塞
				if(0==ret)
				{
					printf("byebye\n");
					ctrl();
					close(fdr);
					close(fdw);
					break;
				}
				timep = time(NULL);
				sprintf(message_buf,"%*s%s%*s%s:%s",45," ",ctime(&timep),48," ",username_buf,buf);
				//printf("%s\n",buf);
				char *p;
				p=(char*)shmat(shmid,NULL,0);
				if((char*)-1==p)
				{
					perror("shmat");
					return -1;
				}
				shm_buf message;
				bzero(&message,sizeof(message));
				semop(semid,&sopp,1);//加锁
				strcpy(message.buf,buf);
				message.flag=1;
				memcpy(p,&message,sizeof(message));
				semop(semid,&sopv,1);//解锁
			}
			if(FD_ISSET(0,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));//读取标准输入,写到2号管道
				if(ret>0)
				{
					write(fdw,buf,strlen(buf)-1);
					char *p;
					p=(char*)shmat(shmid,NULL,0);
					if((char*)-1==p)
					{
						perror("shmat");
						return -1;
					}
					shm_buf message;
					bzero(&message,sizeof(message));
					semop(semid,&sopp,1);
					strcpy(message.buf,buf);
					message.flag=1;
					memcpy(p,&message,sizeof(message));
					semop(semid,&sopv,1);
				}else{
					printf("byebye\n");
					close(fdr);
					close(fdw);
					break;
				}
			}
		}
	}
	return 0;
}
