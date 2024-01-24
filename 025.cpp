#include<iostream>
using namespace std;


class ArcNode
{
public:
	int des;
	ArcNode* next;
	ArcNode()
	{
		
		next = NULL;
	}

};
class GraphNode 
{
public:
	int data;
	int In_Num = 0;
	int Out_Num = 0;
	ArcNode* In;
	ArcNode* Out;
	GraphNode()
	{
		data = 0;
	
		In = NULL;
		Out = NULL;
	}
	~GraphNode()
	{
		delete In;
		delete Out;
	}

};

void InitializeGraph(GraphNode* Graph,int n)
{ 
	int i = 0;
	int above, below;
	ArcNode* BridgeNode;
	ArcNode* NewNode;
	while (i < n)
	{
		cin >> above >> below;
		above--;
		below--;

		BridgeNode = Graph[above].Out;
		NewNode = new ArcNode();
		NewNode->des = below;//指向below
		NewNode->next = BridgeNode;
		Graph[above].Out = NewNode;
		//接above节点的邻接表
		BridgeNode = Graph[below].In;
		NewNode = new ArcNode();
		NewNode->des = above;
		NewNode->next = BridgeNode;
		Graph[below].In = NewNode;

		Graph[below].In_Num++;
		Graph[above].Out_Num++;
		i++;

	}

	
}
int Find_No_In_Node(GraphNode* Graph, int n)
{
	int i = 0;
	int Node = -1;
	while (i < n)
	{
		if (Graph[i].In_Num == 0)
		{
			if (Node == -1)
				Node = i;
			else return -1;
		}


		i++;
	}

	return Node;
}
void DeletNode(GraphNode* Graph,int n,int Node)
{
	int i = 0;
	while (i < n)
	{
		if (i == Node)
		{
			Graph[i].In_Num = -1;
		}
		else
		{
			ArcNode* NowArc = Graph[i].In;
			while (NowArc != NULL)
			{
				if (NowArc->des == Node)
				{
					Graph[i].In_Num--;
					
				}
				NowArc = NowArc->next;
			}
		}

		i++;
	}


}
bool Order(GraphNode* Graph, int n, int* VerticalOrder)
{
	int i = 0;
	while (i < n)
	{
		int NowNode = Find_No_In_Node(Graph, n);
		if (NowNode == -1)
			return false;
		DeletNode(Graph, n, NowNode);
		VerticalOrder[i] = NowNode;
		i++;
	}
	return true;
}
void DestoryGraph(GraphNode* Graph, int n)
{
	int i = 0;
	while (i < n)
	{
		
		i++;
	}

}
int main()
{
	int i = 0;
	int j = 0;
	int RowConditionNum, ColConditionNum,Size;
	cin >> Size >> RowConditionNum >> ColConditionNum;

	GraphNode* Graph = new GraphNode[Size]();
	while (i < Size)
	{
		Graph[i].data = i + 1;
		i++;
	}
	i = 0;
	int** Result = new int* [Size];
	while (i < Size)
	{
		Result[i] = new int[Size];
		i++;
	}
	i = 0;
	while (i < Size)
	{
		while (j < Size)
		{
			Result[i][j] = 0;
			j++;
		}
		i++;
		j = 0;
	}
	//结果矩阵先全部赋值0
	i = 0;
	j = 0;
	//初始化计数器
	// 
	//先解决上下问题
	InitializeGraph(Graph, RowConditionNum);
	int* VerticalOrder = new int[Size];
	bool B1=Order(Graph, Size, VerticalOrder);//得到的verticalorder从上到下 从0-n
	i = 0;
	delete[] Graph;//简单删掉  其实内部还有挺多要释放的不过水了。。
	Graph = new GraphNode[Size]();

	InitializeGraph(Graph, ColConditionNum);
	int* HorizontalOrder = new int[Size];
	bool B2=Order(Graph, Size, HorizontalOrder);//得到的horizental从左到右从小到大
	i = 0;
	j = 0;

	if (B1 && B2)
	{
		while (i < Size)
		{
			int nownode = VerticalOrder[i];

			while (j < Size)
			{
				if (HorizontalOrder[j] == nownode)
				{
					cout << nownode + 1 << " ";

				}
				else cout << "0 ";
				j++;

			}
			cout << endl;
			j = 0;
			i++;
		}
	}
	else
	{
		cout << "-1" << endl;
	}



	delete[]Graph;
	delete[]HorizontalOrder;
	delete[]VerticalOrder;
	delete[]Result;

	return 0;
}