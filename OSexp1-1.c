/*
* @Author: Leif
* @Date:   2017-05-15 18:43:23
* @Last Modified by:   Leif
* @Last Modified time: 2017-05-16 09:09:27
*/
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t forkRet;
	printf("Father:My pid is %d\n", getpid());
	forkRet = fork();
	//forkRet is 0 in son process, son process's pid instead in father process;
	//son process and father process parted ways from here; 
	if(forkRet < 0)
	{
		printf("fork failed!\n");
	}
	else if(forkRet > 0)
	{
		printf("Father:My son's pid is %d\n",forkRet);
	}
	else
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
		else
		{
			printf("Grandson:My pid is %d\n", getpid());
		}
	}
    return 0;
}