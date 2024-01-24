#include<iostream>
#include<string>
#include<queue>
using namespace std;
class ObjectNode
{
public:
	int num=0;//Ȩ
	int data=0;//ascllֵ
	ObjectNode* left;
	ObjectNode* right;
	ObjectNode* parent;
	//�������ṹ
	ObjectNode* next;
	//����Ľṹ
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
	//�����ʼ����������
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
//����ʽ��ʼ��
void DisplayLinklist(ObjectNode* root)
{
	while (root != NULL)
	{
		cout << "num:" << root->num << "  data:" << root->data << endl;
		root = root->next;
	}
}
//����ʽ���
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
	OriRoot = Bridge;//ȥ��ͷ�ڵ�

	while (OriRoot != NULL&&OriRoot->next!=NULL)
	{
		ObjectNode* NewNode = new ObjectNode(OriRoot,OriRoot->next);
		OriRoot->parent = NewNode;
		OriRoot->next->parent = NewNode;//���ڵ��ʼ��
		int sum_num = OriRoot->num + OriRoot->next->num;
		Linklist_OrderInsert(OriRoot,NewNode,sum_num, -1);//�м�ڵ㶼��-1
		OriRoot = OriRoot->next->next;
	}

	return Bridge;
}
//����ת ����-������ �ṹ ����ֵ��������㣨ȥ����ͷ�ڵ㣩ִ�����OriRootָ������
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
	int result = 0;//�����Ƶ�ֵ
	int dex = 0;//ָ��
	while (LinkRoot->next != NULL)
	{
		if (LinkRoot->data != -1)
		{
			ObjectNode* NowNode = LinkRoot;
			while (NowNode->parent != NULL)
			{

				LastNode = NowNode;
				NowNode = NowNode->parent;

				if (LastNode=NowNode->left)//����Ϊ0
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
//����ʽ���
int main()
{
	int num = 0;//��ͬ�ַ�����
	int ascll[128]={0};//��ʼ0��
	string target;//�洢�Ĵ�
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