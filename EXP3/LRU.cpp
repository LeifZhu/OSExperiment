/*
* @Author: Leif
* @Email: leifzhu@foxmail.com
* @Date:   2017-05-22 20:38:39
* @Last Modified by:   Leif
* @Last Modified time: 2017-05-22 22:16:53
*/
#include <iostream>
#include <vector>
using namespace std;

struct Task
{
	int pid;
	Task* next;
	Task()
	{
		pid = -1;
		next = NULL;
	}
};

Task* precursor[1000];
void LRUSimulate(vector<int> const &taskList, int pageNum)
{
	// I use linklist to optimize the action of putting a task
	// to the end of queue to O(1) time.
	Task *head = new Task;
	Task *last = head;
	for(int i = 0; i < pageNum; i++)
	{
		last->next = new Task;
		last = last->next;
	}
	Task *tail = last;
	int frequency = 0;
	vector<int> eliminateList;

	memset(precursor,0,sizeof(precursor));

	for(int i = 0; i < taskList.size(); i++)
	{
		if(precursor[taskList[i]] == NULL)
		{
			cout<<"replace page"<<head->next->pid<<" with page"<<taskList[i]<<endl;
			//if I use printf(), Bus error occures, Why?
			frequency++;
			precursor[head->next->pid] = NULL;//the front element pop out
			head->next->pid = taskList[i];
			precursor[taskList[i]] = head;
		}
		Task *pre = precursor[taskList[i]];
		Task *cur =  precursor[taskList[i]]->next;
		tail->next = cur;
		precursor[cur->pid] = tail;
		tail = cur;
		pre->next = cur->next;
		precursor[cur->next->pid] = pre; 
		cur->next = NULL;
	}
	cout<<"frequency:"<<frequency<<endl;
	cout<<"rate:"<<frequency/(float)taskList.size()<<endl;

	Task *cur = head;
	while(cur != NULL)
	{
		Task *tmp = cur;
		cur = cur->next;
		delete tmp;
	}
}

int main()
{
	vector<int> taskList{4,3,2,1,4,3,5,4,3,2,1,5};
	LRUSimulate(taskList,3);
	return 0;
}