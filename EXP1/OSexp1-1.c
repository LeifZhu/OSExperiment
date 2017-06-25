/*
* @Author: Leif
* @Date:   2017-05-15 18:43:23
* @Last Modified by:   Leif
* @Last Modified time: 2017-06-24 20:21:05
*/
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t forkRet;
	printf("Father:My pid is %d\n", getpid());
	forkRet = fork();
	//forkRet is 0 in subprocess, subprocess's pid instead in father process;
	//subprocess and parent process parted ways here; 
	if(forkRet < 0)
	{
		printf("fork failed!\n");
	}
	else if(forkRet > 0) //parent process
	{
		printf("Father:My son's pid is %d\n",forkRet);
	}
	else //subprocess
	{
		printf("Son:My pid is %d\n", getpid());
		forkRet = fork();
		if(forkRet < 0)
		{
			printf("fork failed\n");
		}
		else if(forkRet > 0)
		{
			printf("Son:my son's pid is %d\n",forkRet);
		}
		else //sub-subprocess
		{
			printf("Grandson:My pid is %d\n", getpid());
		}
	}
    return 0;
}