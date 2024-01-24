#include<iostream>
#include<string>
#include<queue>
using namespace std;
class ObjectNode
{
public:
	int num=0;//权
	int data=0;//ascll值
	ObjectNode* left;
	ObjectNode* right;
	ObjectNode* parent;
	//二叉树结构
	ObjectNode* next;
	//链表的结构
	ObjectNode()
	{
		left = NULL;
		right = NULL;
		next = NULL;
	}
	ObjectNode(ObjectNode* P)
	{
		left = NULL;
		right = NULL;
		next = P;
	}
	ObjectNode(ObjectNode* p1,ObjectNode* p2)
	{
		left = p1;
		right =p2;
		next = NULL;
	}
	ObjectNode(ObjectNode* p1, ObjectNode* p2,ObjectNode* p3)
	{
		left = p1;
		right = p2;
		parent = p3;
		next = NULL;
	}
};
void NewObjectLinklist(ObjectNode* &root,int ascll[])
{
	//数组初始化万用链表
	ObjectNode* Node = root;
	int i = 0;
	while (i < 128)
	{
		if (ascll[i] != 0)
		{
			ObjectNode* NewNode = new ObjectNode;
			NewNode->data = i;
			NewNode->num = ascll[i];
			while (Node->next != NULL&&Node->next->num < NewNode->num)
			{
				Node = Node->next;
			}
			NewNode->next = Node->next;
			Node->next = NewNode;
		
	    }
		Node = root;
		i++;
	}

}
//链表方式初始化
void DisplayLinklist(ObjectNode* root)
{
	while (root != NULL)
	{
		cout << "num:" << root->num << "  data:" << root->data << endl;
		root = root->next;
	}
}
//链表方式输出
void Linklist_OrderInsert(ObjectNode*& root,ObjectNode*& NewNode,int num,int data)
{
	ObjectNode* Node = root;
	NewNode->data = data;
	NewNode->num = num;
	while (Node->next != NULL && Node->next->num < NewNode->num)
	{
		Node = Node->next;
	}
	NewNode->next = Node->next;
	Node->next = NewNode;
}
ObjectNode* NewObjectBinaryTree(ObjectNode* &OriRoot)
{
	ObjectNode* Bridge;

	Bridge = OriRoot->next;
	delete OriRoot;
	OriRoot = Bridge;//去掉头节点

	while (OriRoot != NULL&&OriRoot->next!=NULL)
	{
		ObjectNode* NewNode = new ObjectNode(OriRoot,OriRoot->next);
		OriRoot->parent = NewNode;
		OriRoot->next->parent = NewNode;//父节点初始化
		int sum_num = OriRoot->num + OriRoot->next->num;
		Linklist_OrderInsert(OriRoot,NewNode,sum_num, -1);//中间节点都是-1
		OriRoot = OriRoot->next->next;
	}

	return Bridge;
}
//链表转 链表-二叉树 结构 返回值是链表起点（去掉了头节点）执行完后OriRoot指向树根
void DisplayBinaryTree(ObjectNode* root)
{
	ObjectNode* Node = new ObjectNode;
	queue<ObjectNode*> Q;
	Q.push(root);
	while (!Q.empty())
	{
		int length = Q.size();
		int i = 0;
		while (i < length)
		{
			Node = Q.front();
			Q.pop();
			cout << "  Data: " << Node->data << "  Num: " << Node->num;
			if (Node->left != NULL)
				Q.push(Node->left);
			if (Node->right != NULL)
				Q.push(Node->right);
			i++;
		}
		cout << endl;
	}

}
void Coding(int ascll[], ObjectNode* LinkRoot)
{
	ObjectNode* LastNode = LinkRoot;
	int result = 0;//二进制的值
	int dex = 0;//指数
	while (LinkRoot->next != NULL)
	{
		if (LinkRoot->data != -1)
		{
			ObjectNode* NowNode = LinkRoot;
			while (NowNode->parent != NULL)
			{

				LastNode = NowNode;
				NowNode = NowNode->parent;

				if (LastNode=NowNode->left)//向左为0
					dex++;
				else
				{
					result += (int)pow(2, dex);
					dex++;
				}
			}
		}
		ascll[LinkRoot->data] = result;
		dex = 0;
		result = 0;
		LinkRoot = LinkRoot->next;
	}



}
//树方式输出
int main()
{
	int num = 0;//不同字符个数
	int ascll[128]={0};//初始0个
	string target;//存储的串
	cin >> target;
	int length = target.length();
	int i = 0;
	while (i < length)
	{
		if (ascll[target[i]] == 0)
			num++;
		ascll[target[i]]++;
		i++;
	}
	ObjectNode* root = new ObjectNode;
	NewObjectLinklist(root, ascll);
	//DisplayLinklist(root->next);
	NewObjectBinaryTree(root);
	DisplayBinaryTree(root);


}