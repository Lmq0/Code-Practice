#include<iostream>

using namespace std;
const bool Red = false;
const bool Black = true;
template<typename T>
class TreeNode
{
public:
	T data;
	int times;
	bool Color;//1为黑 0为红
	TreeNode* lc = NULL;
	TreeNode* rc = NULL;
	TreeNode* parent = NULL;
	TreeNode()
	{
		lc = NULL;
		rc = NULL;
		parent = NULL;
		Color = Red;
		times = 1;
	}
	~TreeNode()
	{
		;
	}
};
template<typename T>
class RedBlackTree
{
public:
	int NodeNum;
	TreeNode<T>* root;
	RedBlackTree()
	{
		root = NULL;
	}
	~RedBlackTree()
	{
		delete root;
	}

	void right_rotating(TreeNode<T>* Left, TreeNode<T>* Right);
	void left_rotating(TreeNode<T>* Left, TreeNode<T>* Right);

	TreeNode<T>* insert(TreeNode<T>* NowRoot, T newdata);
	void Fix(TreeNode<T>* NowNode);
	TreeNode<T>* Min(TreeNode<T>* NowRoot)
	{
		if (NowRoot == NULL)
		{
			cout << "Errow Empty Tree" << endl;
			return NULL;
		}
		while (NowRoot->lc != NULL)
		{
			NowRoot = NowRoot->lc;
		}
		return NowRoot;
	}
	TreeNode<T>* Max(TreeNode<T>* NowRoot)
	{
		if (NowRoot == NULL)
		{
			cout << "Errow Empty Tree" << endl;
			return NULL;
		}
		while (NowRoot->rc != NULL)
			NowRoot = NowRoot->rc;
		return NowRoot;
	}
	//最大最小值
	TreeNode<T>* Predecessor(T element, TreeNode<T>* NowRoot);
	TreeNode<T>* Successor(T element, TreeNode<T>* NowRoot);
	TreeNode<T>* Find(TreeNode<T>* NowRoot, T Element)
	{
		while (1)
		{
			if (NowRoot == NULL)
			{
				//cout << "NO NODE" << endl;
				return NULL;
			}
			if (NowRoot->data == Element)
			{
				//cout <<NowRoot->data<<"   "<< NowRoot->times << endl;
				return NowRoot;
			}
			else if (NowRoot->data > Element)
				NowRoot = NowRoot->lc;
			else
				NowRoot = NowRoot->rc;
		}

	}
	void Delete(TreeNode<T>* FindNode, T element);
	void InorderTransfer(TreeNode<T>* NowRoot);
	void FrontTransfer(TreeNode<T>* NowRoot);
	bool _Check(TreeNode<T>* root, int BlackNum, int CurBlackNum)
	{
		if (this->root == NULL)
			return true;
		if (root== NULL)
		{
			if (CurBlackNum == BlackNum)
				return true;
			else//黑色节点不相等返回false
				return false;
		}
		if (root->Color == Red && root->parent->Color == Red)//存在两个连续的红节点
			return false;
		if (root->Color == Black)//黑节点就CurBlackNum++
			CurBlackNum++;
		
		return _Check(root->lc, BlackNum, CurBlackNum)
			&& _Check(root->rc, BlackNum, CurBlackNum);//进行左右递归
	}
	bool Check()
	{
		if (root == NULL)
			return true;
		if (root->Color == Red)
			return false;
		int count = 0;//统计出一条路径的黑色节点的个数
		int num = 0;//需要与count比较的其他路径黑色节点个数
		TreeNode<T>* cur = root;
		while (cur)
		{
			if (cur->Color == Black)
				count++;
			cur = cur->lc;
		}
		return _Check(root, count, num);
	}

	
};
template<typename T>
TreeNode<T>* RedBlackTree<T>::insert(TreeNode<T>* NowRoot, T newdata)
{
	if (NowRoot == NULL)
	{
		TreeNode<T>* newNode = new TreeNode<T>();
		newNode->data = newdata;
		newNode->Color = Black;
		root = newNode;
		return root;
	}//初始化根节点
	while (1)
	{
		if (newdata == NowRoot->data)//
		{
			NowRoot->times++;
			return NowRoot;
		}
		//无需插入 频率增加
		else if (newdata > NowRoot->data)
		{
			if (NowRoot->rc != NULL)
			{
				NowRoot = NowRoot->rc;//循环切换到右子树
			}
			else
			{
				TreeNode<T>* newNode = new TreeNode<T>();
				NowRoot->rc = newNode;
				newNode->data = newdata;
				newNode->parent = NowRoot;
				Fix(newNode);
				return newNode;
			}
			//新建节点
		}
		else
		{
			if (NowRoot->lc != NULL)
			{
				NowRoot = NowRoot->lc;
			}
			else
			{
				TreeNode<T>* newNode = new TreeNode<T>();
				NowRoot->lc = newNode;
				newNode->data = newdata;
				newNode->parent = NowRoot;
				Fix(newNode);
				return newNode;

			}
			//新建节点
		}
	}

}
//插入操作
template<typename T>
void RedBlackTree<T>::right_rotating(TreeNode<T>* Left, TreeNode<T>* Right)
{
	TreeNode<T>* B, * D;
	B = Left->rc; D = Right->parent;
	if (D)
	{
		bool if_left = D->lc == Right;
		if (if_left) D->lc = Left;
		else D->rc = Left;
	}
	Left->rc = Right;
	Left->parent = D;

	Right->parent = Left;
	Right->lc = B;
	if (B)
		B->parent = Right;


}
//右旋转
template<typename T>
void RedBlackTree<T>::left_rotating(TreeNode<T>* Left, TreeNode<T>* Right)
{

	// 0
	//   0 
	TreeNode<T>* B, * D;
	B = Right->lc;
	D = Left->parent;
	if (D)
	{
		if (D->lc == Left)
			D->lc = Right;
		else
			D->rc = Right;
	}
	Left->parent = Right;
	Left->rc = B;
	Right->lc = Left;
	Right->parent = D;
	if (B)
		B->parent = Left;



}
//左旋转
template<typename T>
void RedBlackTree<T>::Fix(TreeNode<T>* NowNode)
{

	while (1)
	{
		if ((NowNode->parent == NULL || NowNode->parent->Color == Black))
			return;
		//父节点是黑色 直接插入
		TreeNode<T>* GrandFather = NowNode->parent->parent;
		TreeNode<T>* Father = NowNode->parent;
		TreeNode<T>* Uncle = (GrandFather->lc == NowNode->parent) ? GrandFather->rc : GrandFather->lc;

		if (Uncle != NULL && Uncle->Color == Red)//叔叔红色
		{
			Uncle->Color = Black;
			NowNode->parent->Color = Black;
			if (GrandFather != root)
			{
				GrandFather->Color = Red;
				NowNode = GrandFather;
				continue;
			}
			//如果祖父不是根 变红
		}
		else//叔叔黑色或者没有
		{
			if (GrandFather->lc == Father && Father->lc == NowNode)
			{
				right_rotating(Father, GrandFather);
				if (GrandFather == root)
					root = Father;
				GrandFather->Color = Red;
				Father->Color = Black;
			}
			else if (GrandFather->lc == Father && Father->rc == NowNode)
			{
				left_rotating(Father, NowNode);
				right_rotating(NowNode, GrandFather);
				if (root == GrandFather)
					root = NowNode;
				NowNode->Color = Black;
				GrandFather->Color = Red;
			}
			else if (GrandFather->rc == Father && Father->rc == NowNode)
			{
				left_rotating(GrandFather, Father);
				GrandFather->Color = Red;
				Father->Color = Black;
				if (root == GrandFather)
					root = Father;
			}
			else
			{
				right_rotating(NowNode, Father);
				left_rotating(GrandFather, NowNode);
				NowNode->Color = Black;
				GrandFather->Color = Red;
				if (root == GrandFather)
					root = NowNode;
			}
			break;
		}

	}
}
//输入后调整平衡
template<typename T>
void RedBlackTree<T>::Delete(TreeNode<T>* FindNode, T newdata)
{
	TreeNode<T>* result = Find(FindNode, newdata);
	if (result == NULL)
	{
		cout << "None" << endl;
		return;
	}
	if (result->times > 1)
	{
		result->times--;
		return;
	}
	//若多个就把存在times--
	/****************************/
	if (result->lc != NULL && result->rc != NULL)
	{
		TreeNode<T>* ChangeNode = Min(result->rc);
		result->data = ChangeNode->data;
		result->times = ChangeNode->times;
		result = ChangeNode;
	}
	TreeNode<T>* P = result->parent;
	bool if_left = false;
	if (P != NULL)
	{
		if_left = P->lc == result;
	}

	//非叶子节点
	if (result->lc != NULL && result->rc == NULL)
	{
		if (result == root)
		{
			root = result->lc;
			delete result;
			return;
		}
		//删除单支树树根特判
		result->lc->parent = P;
		if (if_left)
			P->lc = result->lc;
		else P->rc = result->lc;
		result->lc->Color = Black;
		delete result;
		return;
	}
	else if (result->lc == NULL && result->rc != NULL)
	{
		if (result == root)
		{
			root = result->rc;
			delete result;
			return;
		}
		//删除单支树树根特判
		result->rc->parent = P;
		if (if_left)
			P->lc = result->rc;
		else P->rc = result->rc;
		result->rc->Color = Black;
		delete result;
		return;
	}
	//只有一个子节点 该节点必定为黑色节点 子节点为红色
	else if (result->lc == NULL && result->rc == NULL)
	{
		if (result->Color == Red)
		{
			if (if_left)
				P->lc = NULL;
			else
				P->rc = NULL;
			delete result;
			return;

		}
		//下面讨论删除节点为黑而且没有孩子
		if (P == NULL)//树里面只有一个节点而且要删根
		{
			root = NULL;
			delete result;
			return;
		}
		TreeNode<T>* Brother;
		if (if_left) Brother = P->rc;
		else Brother = P->lc;
		//初始化兄弟
		int a = 1;

		while (a)
		{
		
			//出口只有case 4 case 2
			if (Brother->Color == Black &&
				(Brother->lc == NULL || Brother->lc->Color == Black) &&
				(Brother->rc == NULL || Brother->rc->Color == Black))
			{
				Brother->Color = Red;
				a++;
				if (a == 2)
				{
					
					if (if_left)
						P->lc = NULL;
					else P->rc = NULL;
					delete result;
				}
				if (P->Color == Red || P == root)
				{
					P->Color = Black;
					
					return;//调整至合适或者遇到根节点了
				}
				else
				{
					result = P;//继续循环 上浮一层
				}
			}
			//兄弟黑色 且兄弟的孩子要么黑色要么没有
			//变色处理  case2
			//改变分析节点到原来的parent
			//本操作上浮

			else if (Brother->Color == Red)
			{
				if (if_left)				
					left_rotating(P, Brother);
				else right_rotating(Brother, P);
				if (P == root)
					root = Brother;

				P->Color = Red;
				Brother->Color = Black;
			}
			//兄弟为红色  把兄弟转到父亲位置
			//该旋转后不可能结束 case1
			//不改变分析节点

			else if ((Brother->lc != NULL && Brother->lc->Color == Red &&
				(Brother->rc == NULL || Brother->rc->Color == Black) && if_left) ||
				(Brother->rc != NULL && Brother->rc->Color == Red &&
				(Brother->lc == NULL || Brother->lc->Color == Black) && !if_left))
			{
				if (if_left)
					right_rotating(Brother->lc, Brother);
				else left_rotating(Brother, Brother->rc);
				//旋转至直线状态
				Brother->Color = Red;
				Brother->parent->Color = Black;//转上去的BL节点（BR）
			}
			//删除节点在左  兄弟左孩子红或者删除右 兄弟右孩子红case 3
			// 完成后进case 4
			//不改变分析节点  
			else if ((Brother->Color == Black && Brother->rc != NULL && Brother->rc->Color == Red && if_left) ||
				(Brother->Color == Black && Brother->lc != NULL && Brother->lc->Color == Red && !if_left))
			{
				if (if_left)
					left_rotating(P, Brother);
				else right_rotating(Brother, P);
				if (P == root)
					root = Brother;
				//改根
				Brother->Color = P->Color;
				P->Color = Black;
				if (if_left)
				{
					Brother->rc->Color = Black;
					if(a!=2)
					P->lc = NULL;
				}
				else
				{
					Brother->lc->Color = Black;
					if(a!=2)
					P->rc = NULL;
				}
				//节点删除
				if (a != 2)
				delete result;
				return;//出口  case4

			}
			//删左 兄弟红右 完成后结束 case 4
			//
			P = result->parent;
			if_left = P->lc == result;
			if (if_left) Brother = P->rc;
			else Brother = P->lc;
			//重塑

		}

	}
	//为叶子节点的情况
	else
	{
		cout << "Default,Errow" << endl;
	}
}
//删除节点
template<typename T>
void RedBlackTree<T>::InorderTransfer(TreeNode<T>* NowRoot)
{
	if (NowRoot->lc != NULL)
		InorderTransfer(NowRoot->lc);
	cout << " " << NowRoot->data;

	if (NowRoot->Color) cout << "(Black)";
	else cout << "(Red)";

	if (NowRoot->rc != NULL)
		InorderTransfer(NowRoot->rc);
}
//中序遍历 带颜色输出
template<typename T>
void RedBlackTree<T>::FrontTransfer(TreeNode<T>* NowRoot)
{
	cout << " " << NowRoot->data;
	if (NowRoot->Color) cout << "(Black)";
	else cout << "(Red)";
	if (NowRoot->lc != NULL)
		FrontTransfer(NowRoot->lc);
	if (NowRoot->rc != NULL)
		FrontTransfer(NowRoot->rc);
}
//先序输出
template<typename T>
TreeNode<T>* RedBlackTree<T>::Predecessor(T element,TreeNode<T>* NowRoot)
{
	TreeNode<T>* MinOfRightSubTree;
	TreeNode<T>* MaxOfLeftSubTree;
	if (NowRoot == NULL)
	{
		cout << "None" << endl;
		return NULL;
	}
	while (1)
	{
		if (NowRoot->data > element)
		{
			if (NowRoot->lc == NULL)
			{
				cout << "None" << endl;
				return NULL;
			}
			MaxOfLeftSubTree = Max(NowRoot->lc);
			if (MaxOfLeftSubTree->data < element)
				return MaxOfLeftSubTree;
			else
				NowRoot = NowRoot->lc;
				
		}
		else if (NowRoot->data == element)
		{
			if (NowRoot->lc == NULL)
			{
				cout << "None" << endl;
				return NULL;
			}
			else return Max(NowRoot->lc);
		}
		else
		{
			if (NowRoot->rc == NULL)
				return NowRoot;
			MinOfRightSubTree = Min(NowRoot->rc);
			if (MinOfRightSubTree->data >= element)
			{
				return NowRoot;
			}
			else
			{
				NowRoot=NowRoot->rc;
			}
		}
	}
		
}
//前驱
template<typename T>
TreeNode<T>* RedBlackTree<T>::Successor(T element, TreeNode<T>* NowRoot)
{
	TreeNode<T>* MinOfRightSubTree;
	TreeNode<T>* MaxOfLeftSubTree;
	if (NowRoot == NULL)
	{
		cout << "None" << endl;
		return NULL;
	}
	while (1)
	{
		if (NowRoot->data > element)
		{
			if (NowRoot->lc == NULL)
				return NowRoot;
			MaxOfLeftSubTree = Max(NowRoot->lc);
			if (MaxOfLeftSubTree->data <= element)
				return NowRoot;
			else
				NowRoot = NowRoot->lc;

		}
		else if (NowRoot->data == element)
		{
			if (NowRoot->rc == NULL)
			{
				cout << "None" << endl;
				return NULL;
			}
			else return Min(NowRoot->rc);
		}
		else
		{
			if (NowRoot->rc == NULL)
			{
				cout << "None" << endl;
				return NULL;
			}
			MinOfRightSubTree = Min(NowRoot->rc);
			if (MinOfRightSubTree->data > element)
			{
				return MinOfRightSubTree;
			}
			else
			{
				NowRoot = NowRoot->rc;
			}
		}
	}
}
//后驱
int main()
{
	bool ifPrompt = true;//有无提示输出
	/****/
	if (ifPrompt)
	{
		cout << "Please enter the number of your operations:" << endl;
	}
	/****/
	int OperateNum, i;
	int Operation;
	int element;
	//data类型缺省为int 修改那么改模板参数和element即可
	RedBlackTree<int>* RBT = new RedBlackTree<int>();
	TreeNode<int>* NowNode;
	cin >> OperateNum;
	/****/
	if (ifPrompt)
	{
		cout << "/******************************************/" << endl;
		cout << "/* 1: Insert Node                         */" << endl;
		cout << "/* 2: Delete Node (Only Delete One Nodes) */" << endl;
		cout << "/* 3: Input Times of A Node               */" << endl;
		cout << "/* 4: Min Node      5. Max Node           */" << endl;
		cout << "/* 6: Predecessor Node   7: Successor     */" << endl;
		cout << "/* 8: Inorder Transfer   9: FrontTransfer */" << endl;
		cout << "/*10: Check if it is a RedBlack Tree      */" << endl;
		cout << "/******************************************/" << endl;
	}
	/****/
	i = 0;
	while (i < OperateNum)
	{
		

		cin >> Operation;
		switch (Operation)
		{
		case 1://插入
			cin >> element;
			NowNode=RBT->insert(RBT->root, element);
			break;
		case 2://删除
			cin >> element;
			RBT->Delete(RBT->root,element);
			break;
		case 3://寻找次数
			cin >> element;
			NowNode = RBT->Find(RBT->root, element);
			if (NowNode == NULL) cout << "0" << endl;
			else cout << NowNode->times << endl;
			break;
		case 4://最小值
			NowNode = RBT->Min(RBT->root);
			if (NowNode != NULL)
				cout << NowNode->data << endl;
			break;
		case 5://最大值
			NowNode = RBT->Max(RBT->root);
			if (NowNode != NULL)
				cout << NowNode->data << endl;
			break;
		case 6://前驱
			cin >> element;
			NowNode = RBT->Predecessor(element, RBT->root);
			if (NowNode != NULL)
			cout << NowNode->data << endl;
			break;
		case 7://后驱
			cin >> element;
			NowNode = RBT->Successor(element, RBT->root);
			if (NowNode != NULL)
				cout << NowNode->data << endl;
			break;
		case 8://中序带颜色输出
			RBT->InorderTransfer(RBT->root);
			cout << endl;
			break;
		case 9://先序带颜色输出
			RBT->FrontTransfer(RBT->root);
			cout << endl;
			break;
		case 10://验证红黑性质是否满足
			if (RBT->Check())
			cout << "Right,A RedBlack Tree" << endl;
		    else
		 	cout << "Errow,Not A RedBlack Tree" << endl;
			break;
		default://default处理
			break;
		}
		i++;
	}


	return 0;
}
