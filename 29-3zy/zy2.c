 ///
 /// @file    zy2.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-02-24 21:32:26
 ///创建一个子线程，子线程申请内存，通过清理函数进行free，子线程停留在read标准输入
 //主线程cancel子线程，子线程能够通过清理函数free对应的malloc的内存
 
#include "func.h"

void cleanup(void *p)
{
	printf("I am cleanup,%ld\n",(long)p);
}

void* thread_func(void *p)
{
	printf("I am child thread\n");
	p=malloc(20);
	pthread_cleanup_push(cleanup,(void*)1);
	pthread_cleanup_push(cleanup,(void*)2);
	sleep(2);
	printf("after sleep,I am child thread\n");
	pthread_exit(NULL);
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);
}
int main()
{
	pthread_t pthid;
	int ret;
	ret=pthread_create(&pthid,NULL,thread_func,NULL);
	if(ret!=0)
	{
		printf("pthread_create ret=%d\n",ret);
		return -1;
	}
//	pthread_cancel(pthid);
	pthread_join(pthid,NULL);
	printf("I am main thread\n");
	return 0;
}
