/*
* @Author: Leif
* @Email: leifzhu@foxmail.com
* @Date:   2017-05-22 20:43:14
* @Last Modified by:   Leif
* @Last Modified time: 2017-06-25 16:11:48
*/
#include <iostream>
#include <vector>
#define MAXPID 1000
using namespace std;

bool inMemory[MAXPID];
void FIFOSimulate(vector<int> const &pageList, int pageNum)
{
	/*****申请一个循环队列，并初始化********/
	int *cycleQueue = new int[pageNum];int front = 0;
	memset(cycleQueue, -1, pageNum*sizeof(int));
	memset(inMemory,0,sizeof(inMemory));
	int frequency = 0;
	for(int i = 0; i < pageList.size(); i++)
	{
		cout<<"call page"<<pageList[i]<<":"<<endl;
		if(!inMemory[pageList[i]])//如果页面不在内存中，需要替换页面
		{
			cout<<"replace page"<<cycleQueue[front]<<" with page"<<pageList[i]<<endl;
			frequency++;
			if(cycleQueue[front] >=0 ) inMemory[cycleQueue[front]] = false;
			inMemory[pageList[i]] = true;
			cycleQueue[front] = pageList[i];
			front = (front + 1) % pageNum;
		}
		else //如果在内存中找到了请求的页面
		{
			cout<<"found in memory"<<endl;
		}
		cout<<"pages in memory: "; //打印在内存中的页面
		for(int i = 0; i < pageNum; i++)
		{
			cout<<cycleQueue[(front+i)%pageNum]<<' ';
		}
		cout<<endl<<endl;
	}
	cout<<"frequency:"<<frequency<<endl; //打印缺页数
	cout<<"rate:"<<frequency/(float)pageList.size()<<endl; //打印缺页率
	delete [] cycleQueue;
}

int main()
{
	vector<int> pageList{1,2,3,4,1,2,5,1,2,3,4,5};
	FIFOSimulate(pageList,3);
	return 0;
}