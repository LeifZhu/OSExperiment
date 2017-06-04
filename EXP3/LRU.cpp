/*
* @Author: Leif
* @Email: leifzhu@foxmail.com
* @Date:   2017-05-22 20:38:39
* @Last Modified by:   Leif
* @Last Modified time: 2017-05-26 12:21:58
*/
#include <iostream>
#include <vector>
using namespace std;

struct Node
{
	int pid;
	int address; //for completed simulation
	Node* next;
	Node()
	{
		pid = -1;
		next = NULL;
		address = -1;
	}
};

void place(int pid, int address){} //for completed simulation

Node* precursor[1000];
void LRUSimulate(vector<int> const &taskList, int pageNum)
{
	// I use linklist to optimize the action of putting a task
	// to the end of queue to O(1) time.
	Node *head = new Node;
	Node *last = head;
	for(int i = 0; i < pageNum; i++)
	{
		last->next = new Node;
		last = last->next;
		last->address = i;
	}
	Node *tail = last;
	int frequency = 0;

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
			place(taskList[i], head->next->address);
		}
		Node *pre = precursor[taskList[i]];
		Node *cur =  precursor[taskList[i]]->next;
		tail->next = cur;
		precursor[cur->pid] = tail;
		tail = cur;
		pre->next = cur->next;
		precursor[cur->next->pid] = pre; 
		cur->next = NULL;
	}
	cout<<"frequency:"<<frequency<<endl;
	cout<<"rate:"<<frequency/(float)taskList.size()<<endl;

	Node *cur = head;
	while(cur != NULL)
	{
		Node *tmp = cur;
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