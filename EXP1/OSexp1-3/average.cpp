#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;
int strType(char* str)//this is a automata for recognizing prameters
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

int main(int argc, char *argv[])
{
	 if(argc != 4)
	 {
	 	cout<<"usage: average num1 num2 num3"<<endl;
	 }
	 else
	 {
	 	int flag1 = strType(argv[1]), flag2 = strType(argv[2]), flag3 = strType(argv[3]);
	 	if(flag1 == 0 || flag2 == 0 || flag3 == 0) //at least one prameter isn't a number
	 	{
	 		cout<<"all prameters should be integers or float numbers"<<endl;
	 	}
	 	else
	 	{
	 		cout<<(atof(argv[1]) + atof(argv[2]) + atof(argv[3]))/3<<endl;
	 	}
	 }
	 return 0;
}