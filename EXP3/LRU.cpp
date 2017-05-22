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

Task* precusor[1000];
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

	memset(precusor,0,sizeof(precusor));

	for(int i = 0; i < taskList.size(); i++)
	{
		if(precusor[taskList[i]] == NULL)
		{
			cout<<"replace page"<<head->next->pid<<" with page"<<taskList[i]<<endl;
			//if I use printf, Bus error occured, Why?
			frequency++;
			precusor[head->next->pid] = NULL;//the front element pop out
			head->next->pid = taskList[i];
			precusor[taskList[i]] = head;
		}
		Task *pre = precusor[taskList[i]];
		Task *cur =  precusor[taskList[i]]->next;
		tail->next = cur;
		precusor[cur->pid] = tail;
		tail = cur;
		pre->next = cur->next;
		precusor[cur->next->pid] = pre; 
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