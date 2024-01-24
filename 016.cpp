#include<iostream>
using namespace std;
class TreeNode
{
public:
	int leftchild=-1;
	int rightchild=-1;
	string data="";
	TreeNode()
	{
		leftchild = -1;
		rightchild = -1;
		data = "";
	}
};
void ElementIn(TreeNode& Node)
{

	string element;
	//data

	cin >> element;
	Node.data = element;
	//
	getchar();
	char ch = cin.peek();

	//
	if (ch == 45)
	{
		cin >> ch;
		Node.leftchild = -1;
	}
	else
	{
		cin >> Node.leftchild;
	}


	getchar();
	ch = cin.peek();
	if (ch == 45)
	{
		cin >> ch;
		Node.rightchild = -1;
	}
	else
	{
		cin >> Node.rightchild;
	}
}
void CreateTree(TreeNode* T,int &num)
{
	int i = 0;
	cin >> num;
	while (i < num)
	{
		ElementIn(T[i]);
		i++;
	}



}
bool CompareTree(TreeNode* T1, TreeNode* T2, int rootNode1, int rootNode2)
{
	if (rootNode1 == rootNode2 && rootNode1 == -1)
		return true;
	//¿Õ½Úµã
	if ((rootNode1 + 1) * (rootNode2 + 1) == 0)
		return false;
	if (T1[rootNode1].data != T2[rootNode2].data)
		return false;
	int leftpo1 = T1[rootNode1].leftchild;
	int rightpo1 = T1[rootNode1].rightchild;
	int leftpo2 = T2[rootNode2].leftchild;
	int rightpo2 = T2[rootNode2].rightchild;
	bool if_same = (CompareTree(T1, T2, T1[rootNode1].leftchild, T2[rootNode2].leftchild) &&
		CompareTree(T1, T2, T1[rootNode1].rightchild, T2[rootNode2].rightchild)) ||
		(CompareTree(T1, T2, T1[rootNode1].leftchild, T2[rootNode2].rightchild) &&
			CompareTree(T1, T2, T1[rootNode1].rightchild, T2[rootNode2].leftchild));
	return if_same;

}
int FindEntrance(TreeNode* T,int maxlength)
{
	int i = 0;
	int sum = ((0 + maxlength - 1) * maxlength) / 2;
	int realsum = 0;
	while (i < maxlength)
	{
		if (T[i].leftchild != -1)
			realsum += T[i].leftchild;
		if (T[i].rightchild != -1)
			realsum += T[i].rightchild;

		i++;
	}
	return sum - realsum;


}
int depth(TreeNode* T,int node)
{
	if (node == -1)
		return 0;
	int deep = 1+max(depth(T, T[node].leftchild), depth(T, T[node].rightchild));
	return deep;
}
int main()
{
	int num1 = 0;
	int num2 = 0;
	TreeNode* T1=new TreeNode[15000];
	CreateTree(T1,num1);
	TreeNode* T2=new TreeNode[15000];
	CreateTree(T2,num2);
	

	int entrance1 = FindEntrance(T1, num1);
	int entrance2 = FindEntrance(T2, num2);

	if (CompareTree(T1, T2, entrance1, entrance2))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	int deep1=depth(T1, entrance1);
	int deep2=depth(T2, entrance2);
	cout << deep1 <<endl << deep2 << endl;


	return 0;

}



