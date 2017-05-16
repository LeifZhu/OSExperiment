/*
* @Author: Leif
* @Date:   2017-05-15 19:46:00
* @Last Modified by:   Leif
* @Last Modified time: 2017-05-16 09:44:06
*/

#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define COMMANDNUM 3
#define MAXPATHSIZE 1000
#define MAXENVPSIZE 1000

char ch;
char command[100][100] = {"max","min","average"};
char path[MAXPATHSIZE];
char envp[MAXENVPSIZE][MAXENVPSIZE];
//char *envp[];

char argv[100][100];
int argc;
int foundCommand; //if command was found in command list or not
int successExe;
pid_t forkRet;

void getArg(char *str);
int found(char *str);

void getArg(char *str)
{
	int p = 0;
	while(ch == ' ' || ch == '\t') ch = getchar();
	while(isalnum(ch))
	{
		str[p++] = ch;
		ch = getchar();
	}
}

int found(char *str)
{
	int i = 0;
	while(strcmp(str, command[i]) && i < COMMANDNUM) i++;
	return i < COMMANDNUM; 
	//i < COMMANDNUM means str is found in command list
}





int main()
{
	printf("Welcome to naive shell!\n");
	//"Only max(m,n)/min(m,n)/average(m,n,l) supported.";
	//"Input \"exit\" to exit.";
	//"=================================================";
    char *userName= getenv("USER");
    char *deviceName = "computer";
    getcwd(path, MAXPATHSIZE);
    printf("%s@%s %s:",userName,deviceName,path);
	ch = getchar();
	while(1)
	{
		argc = 0;
		memset(argv,'\0',sizeof(argv));
		if(ch != '\n')
		{
			getArg(argv[argc++]);
			foundCommand = found(argv[0]);
			if(argv[0][0] != '\0' && !foundCommand)
			{
				if(strcmp(argv[0],"exit") == 0) break; //logout naive shell
				printf("-nsh: %s: command not found\n",argv[0]);
			}
			else if(foundCommand)
			{
				while(ch != '\n') getArg(argv[argc++]);
				forkRet = fork();
				if(forkRet == 0) //excute the command in subprocess
				{
                    successExe = execve(path, argv, envp);
					if(successExe < 0)
					{
						printf("-nsh: %s: failed to excute command\n",argv[0]);
						return 0;
					}
					//printf("-nsh: %s: success\n",argv[0]);
				}
				else if(forkRet < 0)
				{
					printf("-nsh: %s: failed to fork subprocess\n",argv[0]);
				}
			}
		}
		printf("%s@%s %s:",userName,deviceName,path);
		ch = getchar();
	}
    return 0;
}
