#include <iostream>
#include <vector>
using namespace std;




class FreeTableManage
{
	struct FreeSection
	{
		int firstBlockIndex;
		int sectionSize;
		FreeSection(int firstBlockIndex, int sectionSize)
		{
			this->firstBlockIndex = firstBlockIndex;
			this->sectionSize = sectionSize;
		}
	};

	int diskSize;
	vector<FreeSection> freeTable;

public:

	FreeTableManage(int diskSize);
	~FreeTableManage();
	int allocate(int fileSize);
	void recycle(int firstBlockIndex, int fileSize);
};


FreeTableManage::FreeTableManage(int diskSize)
{
	this->diskSize = diskSize;
	freeTable.push_back(FreeSection(0,diskSize));
}

FreeTableManage::~FreeTableManage(){}

int FreeTableManage::allocate(int fileSize)
{
	for(int i = 0; i < freeTable.size(); i++)
	{
		if(freeTable[i].sectionSize >= fileSize)
		{
			freeTable[i].sectionSize -= fileSize;
			int firstBlockIndex = freeTable[i].firstBlockIndex;
			if(freeTable[i].sectionSize == 0)
			{
				freeTable.erase(freeTable.begin()+i);
			}
			return firstBlockIndex;
		}
	}
	return -1;
}

void FreeTableManage::recycle(int firstBlockIndex, int fileSize)
{
	int left = 0, right = freeTable.size();
	int mid = (left + right) / 2;
	while(right - left > 1)
	{
		if(freeTable[mid].firstBlockIndex > firstBlockIndex)
		{
			right = mid;
		}
		else
		{
			left = mid;
		}
		mid = (left + right)/2;
	}
	/*回收文件所在的的空闲区，在表中插入一条记录*/
}


