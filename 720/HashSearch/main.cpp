#include<iostream>
using namespace std;

#define SUCCESS 1
#define YNSUCCESS 0
#define HASHSIZE 12     //����ɢ�б���Ϊ���鳤��
#define NULLKEY -32768

struct HashTable
{
	int *elem;   //��̬��������
	int count;    //��ǰԪ�ظ���
};

int m = 0;    //ɢ�б�� ȫ�ֱ���


bool  Init(HashTable* H)  //��ʼ��
{
	int i;
	m = HASHSIZE;
	H->elem = new int[m];
	for (i = 0; i < m; i++)
	{
		H->elem[i] = NULLKEY;   //��ʼ��Ϊ����
	}
	return true;
}

int HashFun(int Key)  //ɢ�к���
{
	return Key % m;   //����������
}

//�������  ��Key���ȥ
void Insert(HashTable *H, int Key)
{
	int addr = HashFun(Key);  //��ɢ�б��ַ
	while (H->elem[addr] != NULLKEY)   //��Ϊ��ʼ��ֵ   ���Դ����Ѿ��洢
	{
		addr = (addr + 1) % m;

	}
	H->elem[addr] = Key;   //���ȥ

}

//ɢ�б���ҹؼ���
bool SearchHash(HashTable*H, int Key, int *addr)
{
	*addr = HashFun(Key);
	while (H->elem[*addr] != Key)   
	{
		//��ͻ���Ƚ�� �ؼ���
		*addr = (*addr + 1) % m;
		if (H->elem[*addr] == NULLKEY || *addr == HashFun(Key))
		{
			return YNSUCCESS;
		}
	}
	cout << "���\n";
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


	delete hash;    //������


}