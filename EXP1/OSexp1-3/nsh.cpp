/*
* @Author: Leif
* @Date:   2017-05-15 19:46:00
* @Last Modified by:   Leif
* @Last Modified time: 2017-05-17 00:53:55
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using std::vector;
using std::string;
#define MAXPATHSIZE 1000

char ch;
vector<string> command = {"max", "min", "average","nsh"};
vector<string> pramList;
const char *argv[100];
char path[MAXPATHSIZE];
int foundCommand; //if command was found in command list or not
int successExe;
pid_t forkRet;

void getArg();
int found(char *str);

void getArg()
{
	string pram;
	while(ch != '\n' && (ch <= 32 || ch >= 127)) ch = getchar();
	while(ch > 32 && ch < 127)
	{
		pram.push_back(ch);
		ch = getchar();
	}
	if(!pram.empty()) pramList.push_back(pram);
}

bool found(string str)
{
	int i = 0;
	while(str != command[i] && i < command.size() ) i++;
	return i <  command.size();
	//i < command.size() means str is found in command list
}





int main()
{
	printf("Welcome to naive shell!\n");
	//"Only max(m,n)/min(m,n)/average(m,n,l) supported.";
	//"Input \"exit\" to exit.";
	//"=================================================";
    char *userName= getenv("USER");
    //char *deviceName = getenv("HOSTNAME");
    getcwd(path, MAXPATHSIZE);
    printf("%s %s>",userName,path);
    ch = getchar();
    while(1)
    {
    	pramList.clear();
    	while(ch != '\n') getArg();
        if(!pramList.empty())
    	{
			if(pramList[0] == "exit") break; //logout naive shell
			else
			{
				foundCommand = found(pramList[0]);
				if(!foundCommand)
				{			
					printf("-nsh: %s: command not found\n",pramList[0].c_str());
				}
				else
				{
					forkRet = fork();
					if(forkRet == 0) //excute the command in subprocess
					{
						const char *file = (string(path)+string("/")+pramList[0]).c_str();
						//printf("%s\n",file);
						for (int i = 0; i < pramList.size(); ++i)
						{
							argv[i] = pramList[i].c_str();
						}
						successExe = execve(file, (char**)argv, NULL);
						printf("-nsh: %s: failed to excute command\n",argv[0]);
						return successExe;
					}
					else if(forkRet < 0)
					{
						printf("-nsh: %s: failed to fork subprocess\n",argv[0]);
					}
					else
					{
						usleep(100000);
						//parent process sleep 0.1s, so that subprocess can print info to screen before prompt show up again
					}
				}
			}
		}
		printf("%s %s>",userName,path);
		ch = getchar();
	}
	return 0;
}
