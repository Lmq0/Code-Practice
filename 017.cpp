#include<queue>
#include<stack>
#include<iostream>
using namespace std;


int step = 0;
int maxtime=0;
class TreeNode
{
public:
	int leftchild = -1;
	int rightchild = -1;
	int parent = -1;
	int if_diffusion = 0;
	string data = "";
	TreeNode()
	{
		leftchild = -1;
		rightchild = -1;
		parent = -1;
		data = "";
	}

};
TreeNode* NewTree(int rootnode,int number)
{
	int i = 0;
	
	TreeNode* t=new TreeNode[150000];
	stack<int> a;
	int nownode = rootnode;
	a.push(nownode);
	while (i < number)
	{
		if (!a.empty())
		  nownode = a.top();
		a.pop();

		int left, right;
		cin >> left >> right;
		if (right != -1)
			a.push(right);
		if (left != -1)
			a.push(left);
		

		t[nownode].leftchild = left;
		if (left != -1)
			t[left].parent = nownode;

		t[nownode].rightchild = right;
		if (right != -1)
			t[right].parent = nownode;
		i++;
	}
	return t;
}
//队列方法构造
int depthPro(int rootnode,int beginnode, TreeNode* t)
{
	if (rootnode == beginnode)
		return -10000;
	if (rootnode == -1)
		return 0;


	return depthPro(t[rootnode].rightchild, beginnode, t) > depthPro(t[rootnode].leftchild,beginnode, t) ?
		1 + depthPro(t[rootnode].rightchild, beginnode,t) : 1 + depthPro(t[rootnode].leftchild,beginnode, t);
}
void diffusion(int beginnode,TreeNode* t)
{
	queue<int> a;
	a.push(beginnode);
	t[beginnode].if_diffusion = 1;
	while (!a.empty())
	{
		int size = a.size();
		int i = 0;
		while (i < size)
		{
			int node=a.front();
			a.pop();

			if (t[node].parent != -1 && t[t[node].parent].if_diffusion == 0)
			{
				a.push(t[node].parent);
				t[t[node].parent].if_diffusion = 1;
			}
			if (t[node].leftchild != -1 && t[t[node].leftchild].if_diffusion == 0)
			{
				a.push(t[node].leftchild);
				t[t[node].leftchild].if_diffusion = 1;
			}
			if (t[node].rightchild != -1 && t[t[node].rightchild].if_diffusion == 0)
			{
				a.push(t[node].rightchild);
				t[t[node].rightchild].if_diffusion = 1;
			}

			i++;
		}



		maxtime++;
	}



}
int main()
{
	
	int number, rootnode, beginnode;
	cin >> number;
	if (number == EOF)
		return 0;
	cin>>beginnode;
	TreeNode* t = NewTree(0, number);

	diffusion(beginnode, t);


	cout << maxtime-1 << endl;
	
	return 0;
}