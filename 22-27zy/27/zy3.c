 ///
 /// @file    zy3.c
 /// @author  hmd(941115hmd@gmail.com)
 /// @date    2019-01-21 19:51:06
 ///
 
#include "func.h"
void sig(int signum)
{

}
int main()
{
	signal(SIGALRM,sig);
	alarm(5);
	pause();
	return 0;
}
