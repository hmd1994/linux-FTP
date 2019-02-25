 ///
 /// @file    zy1.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-02-24 21:07:57
 //创建一个子线程，传入数值1，在子线程中能够获取并打印，子线程退出，返回数值2
 //主线程通过pthread_join获取等子线程结束并获取子线程的退出值并打印
 
#include "func.h"

void* thread_func(void *p)
{
	printf("I am child thread,i=%ld\n",(long)p);
	pthread_exit((void*)2);
}

int main()
{
	pthread_t pthid;
	int ret;
	ret=pthread_create(&pthid,NULL,thread_func,(void*)1);
	if(ret!=0)
	{
		printf("pthread_creat ret=%d\n",ret);
		return -1;
	}
	int i;
	ret=pthread_join(pthid,(void**)&i);
	if(ret!=0)
	{
		printf("pthread_join ret=%d\n",ret);
		return -1;
	}
	printf("I am main thread,i=%d\n",i);
	return 0;
}
