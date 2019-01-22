 ///
 /// @file    a1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-22 09:37:17
 ///
 
#include "func.h"
typedef struct shmmsg{
	int flag;
	char buf[4092];
}shm_buf;


int main()
{
		int shmid;
		shmid=shmget((key_t)1234,4096,IPC_CREAT|0600);
		if(-1==shmid)
		{
			perror("shmget");
			return -1;
		}
		shm_buf *buf;
		buf=(shm_buf *)shmat(shmid,NULL,0);
		struct sembuf sopp,sopv;
		sopp.sem_num=0;
		sopp.sem_op=-1;
		sopp.sem_flg=SEM_UNDO;
		sopv.sem_num=0;
		sopv.sem_op=1;
		sopv.sem_flg=SEM_UNDO;
	while(1)
	{
		if((shm_buf*)-1==buf)
		{
			perror("shmat");
			return -1;
		}
		while(buf->flag)
		{
			printf("%s\n",buf->buf);
			buf->flag=0;
			break;
		}
	}
	return 0;
}
