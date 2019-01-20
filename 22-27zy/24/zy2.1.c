 ///
 /// @file    zy2.1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-20 20:38:18
 ///
 
#include "func.h"
int main()
{
	int shmid;//存放创建共享内存返回值
	shmid = shmget((key_t)1234/*创建的共享内存的ID*/,4096/*大小（一般4k的整数倍）*/,IPC_CREAT|0600);
	if(-1==shmid )
	{
		perror("shmget");
		return -1;
	}
	char *p;//定义地址
	printf("shmid = %d\n",shmid);
	p=(char*)shmat(shmid,NULL,0);//链接共享内存
	if((char*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	printf("p=%p,%s\n",p,p);//输出p的地址
	strcpy(p,"hello");//将信息写入共享内
	while(1);
	return 0;

}
