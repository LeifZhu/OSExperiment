/*
* @Author: Leif
* @Date:   2017-05-15 19:46:00
* @Last Modified by:   Leif
* @Last Modified time: 2017-05-16 19:50:27
*/

#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define COMMANDNUM 4
#define MAXPATHSIZE 1000
#define MAXENVPSIZE 1000

char ch;
char command[100][100] = {"max","min","average","OSexp1-1"};
char path[MAXPATHSIZE];
char envp[MAXENVPSIZE][MAXENVPSIZE];

char *argv[100];
int argc;
int foundCommand; //if command was found in command list or not
int successExe;
pid_t forkRet;

char* getArg();
int found(char *str);

char* getArg()
{
    char str[1000];
    int p = 0;
    memset(str, '\0', sizeof(str));
	while(ch == ' ' || ch == '\t') ch = getchar();
	while(ch > 32 && ch < 127)
	{
		str[p++] = ch;
		ch = getchar();
	}
    char* result = (char*)malloc(p+1);
    int i = 0;
    while(i<p) result[i] = str[i];
    result[p] = '\0';
    return result;
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
    char *deviceName = getenv("HOSTNAME");
    getcwd(path, MAXPATHSIZE);
    printf("%s@%s %s:",userName,deviceName,path);
    ch = getchar();
    while(1)
    {
    	argc = 0;
    	memset(argv,0,sizeof(argv));
    	while(ch != '\n') argv[argc++] = getArg();
        if(argv[0] != NULL)
    	{
			if(strcmp(argv[0],"exit") == 0) break; //logout naive shell
			else
			{
				foundCommand = found(argv[0]);
				if(!foundCommand)
				{			
					printf("-nsh: %s: command not found\n",argv[0]);
				}
				else
				{
					forkRet = fork();
					if(forkRet == 0) //excute the command in subprocess
					{
						char file[MAXPATHSIZE];
						strcpy(file,path);
                        strcat(file,"/");
						strcat(file, argv[0]);
						printf("%s\n",file);
                        successExe = execve(file, argv, NULL);
						if(successExe < 0)
						{
							printf("-nsh: %s: failed to excute command\n",argv[0]);
							return successExe;
						}
					}
					else if(forkRet < 0)
					{
						printf("-nsh: %s: failed to fork subprocess\n",argv[0]);
					}
				}
			}
		}
		printf("%s@%s %s:",userName,deviceName,path);
		ch = getchar();
	}
	return 0;
}
