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
		if(!inMemory[taskList[i]])
		{
			cout<<"replace page"<<cycleQueue[front]<<" with page"<<taskList[i]<<endl;
			frequency++;
			if(cycleQueue[front] >=0 ) inMemory[cycleQueue[front]] = false;
			inMemory[taskList[i]] = true;
			cycleQueue[front] = taskList[i];
			front = (front + 1) % pageNum;
		}
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