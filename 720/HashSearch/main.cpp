#include<iostream>
using namespace std;

#define SUCCESS 1
#define YNSUCCESS 0
#define HASHSIZE 12     //定义散列表长度为数组长度
#define NULLKEY -32768

struct HashTable
{
	int *elem;   //动态分配数组
	int count;    //当前元素个数
};

int m = 0;    //散列表表长 全局变量


bool  Init(HashTable* H)  //初始化
{
	int i;
	m = HASHSIZE;
	H->elem = new int[m];
	for (i = 0; i < m; i++)
	{
		H->elem[i] = NULLKEY;   //初始化为无穷
	}
	return true;
}

int HashFun(int Key)  //散列函数
{
	return Key % m;   //除留余数法
}

//插入操作  把Key插进去
void Insert(HashTable *H, int Key)
{
	int addr = HashFun(Key);  //求散列表地址
	while (H->elem[addr] != NULLKEY)   //不为初始化值   所以代表已经存储
	{
		addr = (addr + 1) % m;

	}
	H->elem[addr] = Key;   //存进去

}

//散列表查找关键词
bool SearchHash(HashTable*H, int Key, int *addr)
{
	*addr = HashFun(Key);
	while (H->elem[*addr] != Key)   
	{
		//冲突就先解决 重计算
		*addr = (*addr + 1) % m;
		if (H->elem[*addr] == NULLKEY || *addr == HashFun(Key))
		{
			return YNSUCCESS;
		}
	}
	cout << "输出\n";
	cout << H->elem[*addr] << endl;
	return true;
}


int main()
{
	HashTable* hash = new HashTable;
	Init(hash);
	Insert(hash, 4);
	Insert(hash, 5);
	Insert(hash, 6);

	int *addr = new int;
	int Key = 4;
	SearchHash(hash, Key, addr);


	delete hash;    //别忘记


}