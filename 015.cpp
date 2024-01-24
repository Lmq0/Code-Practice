#include<iostream>
#include<string.h>
using namespace std;
int type = 0;
int num = 0;
class TreeNode
{
public:
	TreeNode* leftchild;
	TreeNode* rightchild;
	TreeNode* parent;
	string element;
	TreeNode()
	{
	
		leftchild = NULL;
		rightchild = NULL;
		parent = NULL;
		element ="";
	}
	TreeNode(string data)
	{
		leftchild = NULL;
		rightchild = NULL;
		parent = NULL;
		element = data;
	}
	TreeNode(bool left_or_right, TreeNode* son,string data)
	{
		leftchild = NULL;
		rightchild = NULL;
		parent = NULL;
		left_or_right ? leftchild = son : rightchild = son;
		element = data;
	}
	TreeNode(TreeNode* p,string data)
	{
		parent = p;
		leftchild = NULL;
		rightchild = NULL;
		element = data;
	}
	TreeNode(TreeNode* p, bool left_or_right, TreeNode* son, string data)
	{
		leftchild = NULL;
		rightchild = NULL;
		parent = p;
		left_or_right ? leftchild = son : rightchild = son;
		element = data;
	}
};
class Stack
{
public:
	TreeNode** base;
	TreeNode** top=base;
	const int Maxsize=100;
	Stack()
	{
		base = (TreeNode**)malloc(sizeof(TreeNode*) * Maxsize);
		top = base;
	}
	bool Push(TreeNode* element)
	{
		if (top == base + Maxsize)
			return false;
		;
		*top = element;
		top++;
		return true;
	}
	bool Pop(TreeNode* &element)
	{
		element = NULL;
		if (top == base)
			return false;
		top--;
		element = *top;
		*top = NULL;
		return true;
	}
	bool if_empty()
	{
		if (top == base)
			return true;
		return false;
	}
	
};
bool GetOrder()
{
	string order;
	cin >> order;
	if (order == "push")
		return false;
	else if (order == "pop")
		return true;
	else
		exit(0);
	return true;
}
void CreateTree(Stack& S,TreeNode* root)
{
	int poptime = 0;
	TreeNode* Last = NULL;
	while (!S.if_empty()||poptime<num)
	{
		string data = "";
		bool operation = GetOrder();
		if (!operation)
		{
			//push操作
			cin >> data;
			if (type==1)
			{
				
				TreeNode* NewNode = new TreeNode(root,data);
				S.Push(NewNode);
				root->leftchild = NewNode;
				Last = root;
				root = NewNode;
			}
			else
			{
				TreeNode* NewNode = new TreeNode(Last, data);
				S.Push(NewNode);
				Last->rightchild = NewNode;
				Last = root;
				root = NewNode;
				type = 1;
			}
		}
		else
		{
			//pop操作
			if (type == 1)
			{
				if (S.top - 1 != S.base)
					root = *(S.top - 2);
				else
					root = NULL;
				S.Pop(Last);//退栈 回退
				type = 2;
			}
			else
			{
				if (S.top - 1 != S.base)
					root = *(S.top - 2);
				else
					root = NULL;
				S.Pop(Last);
			}
			poptime++;
		}
	}
}
void Print(TreeNode* root)
{
	if (root->leftchild != NULL)
		Print(root->leftchild);
	if (root->rightchild != NULL)
		Print(root->rightchild);
	cout << root->element;
}
int main()
{
	

	cin >> num;
	int i = 0;


	TreeNode* root=new TreeNode;

	Stack S;
	S.Push(root);
	type = 1;//左行


	string data = "";
	bool operation = GetOrder();//获取命令
	if (!operation) cin >> data;
		//如果为push就cin data
	root->element = data;
	root->leftchild = NULL;
	root->rightchild = NULL;
	root->parent = NULL;
	CreateTree(S, root);


	if (root != NULL)
		Print(root);



	return 0;
}