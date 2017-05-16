/*
* @Author: Leif
* @Email: leifzhu@foxmail.com
* @Date:   2017-05-16 23:19:07
* @Last Modified by:   Leif
* @Last Modified time: 2017-05-16 23:27:08
*/
#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;
int strType(char* str)//this is a automatain fact
{
	int flag = 0; // 0:not a number 1:int 2:float
	int i;
	if(isnumber(str[0])) flag = 1;
	if(flag == 1)
	{
		for(i = 1; str[i]!=0; i++)
		{
			if(isnumber(str[i])) continue;
			else if(str[i] ==  '.')
			{
				flag = 2;
				i++;
				break;
			}
			else
			{
				flag = 0; 
				break;
			}
		}
	}
	if(flag == 2)
	{
		for(;str[i] != '\0'; i++)
		{
			if(!isnumber(str[i]))
			{
				flag = 0; break;
			}
		}
	}
	return flag;
}

int main(int argc, char *argv[])//even the tow numbers are different type, we can compare them
{
	 if(argc != 3)
	 {
	 	cout<<"usage: min num1 num2"<<endl;
	 }
	 else
	 {
	 	int flag1 = strType(argv[1]), flag2 = strType(argv[2]);
	 	//cout<<flag1<<flag2<<endl;
	 	if(flag1 == 0 || flag2 == 0) //at least one prameters isn't a number
	 	{
	 		cout<<"all prameters should be integers or float numbers"<<endl;
	 	}
	 	else if(flag1 == 2 || flag2 ==2) //at least one float number
	 	{
	 		cout<<min(atof(argv[1]), atof(argv[2]))<<endl;
	 	}
	 	else //both integers
	 	{
	 		cout<<min(atoi(argv[1]), atoi(argv[2]))<<endl;
	 	}
	 }
	 return 0;
}