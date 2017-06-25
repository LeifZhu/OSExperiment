/*
* @Author: Leif
* @Date:   2017-05-15 19:30:40
* @Last Modified by:   Leif
* @Last Modified time: 2017-06-24 20:26:32
*/
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t forkRet;
	printf("My pid is %d\n", getpid());
	forkRet = fork();
	if(forkRet > 0)// parent process
	{
		printf("My first son's pid is %d\n", forkRet);
		forkRet = fork();
		if(forkRet > 0)	// parent process
		{
			printf("My second son's pid is %d\n", forkRet);
		}
		else if(forkRet == 0) // the second subprocess
		{
			printf("I'm the second son, my pid is %d\n", getpid());
		}
		else
		{
			printf("the second fork failed!\n");
		}
	}
	else if(forkRet == 0) // the first subprocess
	{
		printf("I'm the first son, my pid is %d\n", getpid());
	}
	else
	{
		printf("the first fork failed!\n");
	}
    return 0;
}