/*
* @Author: Leif
* @Date:   2017-05-15 19:30:40
* @Last Modified by:   Leif
* @Last Modified time: 2017-05-15 19:40:37
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t forkRet;
	printf("My pid is %d\n", getpid());
	forkRet = fork();
	if(forkRet > 0)
	{
		printf("My first son's pid is %d\n", forkRet);
		forkRet = fork();
		if(forkRet > 0)
		{
			printf("My another son's pid is %d\n", forkRet);
		}
		else if(forkRet == 0)
		{
			printf("I'm the second son, my pid is %d\n", getpid());
		}
		else
		{
			printf("the second fork failed!\n");
		}
	}
	else if(forkRet == 0)
	{
		printf("I'm the first son, my pid is %d\n", getpid());
	}
	else
	{
		printf("the first fork failed!\n");
	}
    return 0;
}