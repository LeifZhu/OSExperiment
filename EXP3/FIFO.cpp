/*
* @Author: Leif
* @Email: leifzhu@foxmail.com
* @Date:   2017-05-22 20:43:14
* @Last Modified by:   Leif
* @Last Modified time: 2017-05-23 14:52:30
*/
#include <iostream>
#include <vector>
#define MAXPID 1000
using namespace std;

bool inMemory[MAXPID];
void FIFOSimulate(vector<int> const &taskList, int pageNum)
{
	int *cycleQueue = new int[pageNum];int front = 0;
	memset(cycleQueue, -1, pageNum*sizeof(int));
	memset(inMemory,0,sizeof(inMemory));
	int frequency = 0;
	for(int i = 0; i < taskList.size(); i++)
	{
		cout<<"call page"<<taskList[i]<<":"<<endl;
		if(!inMemory[taskList[i]])
		{
			cout<<"replace page"<<cycleQueue[front]<<" with page"<<taskList[i]<<endl;
			frequency++;
			if(cycleQueue[front] >=0 ) inMemory[cycleQueue[front]] = false;
			inMemory[taskList[i]] = true;
			cycleQueue[front] = taskList[i];
			front = (front + 1) % pageNum;
		}
		else
		{
			cout<<"found in memory"<<endl;
		}
		cout<<"pages in memory: ";
		for(int i = 0; i < pageNum; i++)
		{
			cout<<cycleQueue[(front+i)%pageNum]<<' ';
		}
		cout<<endl<<endl;
	}
	cout<<"frequency:"<<frequency<<endl;
	cout<<"rate:"<<frequency/(float)taskList.size()<<endl;
	delete [] cycleQueue;
}

int main()
{
	vector<int> taskList{1,2,3,4,1,2,5,1,2,3,4,5};
	FIFOSimulate(taskList,3);
	return 0;
}