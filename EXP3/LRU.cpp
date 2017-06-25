/*
* @Author: Leif
* @Email: leifzhu@foxmail.com
* @Date:   2017-05-22 20:38:39
* @Last Modified by:   Leif
* @Last Modified time: 2017-06-25 15:03:00
*/
#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int pid;
    int address;
    Node* next;
    Node()
    {
        pid = -1;
        next = NULL;
        address = -1;
    }
};

void place(int pid, int address){}
void visit(int address){}
//最大pid是1000，precursor数组又两个功能，precursor[pid] == NULL
//表示pid对应的页面不在内存中,否则precursor[pid]代表前驱
Node* precursor[1000];
//requestSequence是页面请求序列，pageNum是为程序其分配的物理页面
void LRUSimulate(vector<int> const &requestSequence, int pageNum) 
{
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

    for(int i = 0; i < requestSequence.size(); i++)
    {
        cout<<"call page"<<requestSequence[i]<<":"<<endl;
        //如果请求的页面不在内存中，就需要将链表最前面的记录节点中的页面替换成请求的页面
        if(precursor[requestSequence[i]] == NULL)
        {
            cout<<"replace page"<<head->next->pid
            <<" with page"<<requestSequence[i]<<endl;
            frequency++;
            precursor[head->next->pid] = NULL;
            head->next->pid = requestSequence[i];
            precursor[requestSequence[i]] = head;
            place(requestSequence[i], head->next->address);
        }
        else //如果在内存中找到了请求的页面
        {
            cout<<"found in memory"<<endl;
        }
        //将当前请求的页面对应的记录节点放到链表尾部，因为它最近刚刚被使用
        Node *pre = precursor[requestSequence[i]];
        Node *cur =  precursor[requestSequence[i]]->next;
        tail->next = cur;
        precursor[cur->pid] = tail;
        tail = cur;
        pre->next = cur->next;
        precursor[cur->next->pid] = pre; 
        cur->next = NULL;
        visit(tail->address);
        cout<<"pages in memory: "; //打印在内存中的页面
        for(Node *temp = head->next; temp != NULL; temp = temp->next)
        {
            cout<<temp->pid<<' ';
        }
        cout<<endl<<endl;
    }
    //显示缺页次数和缺页率
    cout<<"frequency:"<<frequency<<endl;
    cout<<"rate:"<<frequency/(float)requestSequence.size()<<endl;

    //释放内存
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
    vector<int> requestSequence{4,3,2,1,4,3,5,4,3,2,1,5};
    LRUSimulate(requestSequence,3);
    return 0;
}