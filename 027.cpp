#include<iostream>
#include<queue>
#include<memory.h>
using namespace std;
const int CILING = 2147483647;
//2147483647;

class GrassNode
{
public:
	int* distance;

};
class Node {
public:
	int length;
	int data;
	
	friend bool operator<(Node Node1, Node Node2)
	{
		return Node1.length > Node2.length;
	}
};

class ArcNode
{
public:
	int des = 0;
	int length = 0;
	ArcNode* next;

};
class GraphNode
{
public:
	int data;//与数组中编号加一相同
	ArcNode* fri;
	GrassNode Grass;
	bool if_grass = 0;
	GraphNode()
	{
		data = 0;
		fri = NULL;

	}
	~GraphNode()
	{

	}

};
void InitializeArc(GraphNode* Graph, int ArcNum)
{
	int i = 0;
	int sta, des, len;
	ArcNode* BridgeNode;
	ArcNode* NewNode;
	while (i < ArcNum)
	{
		cin >> sta >> des >> len;
		sta--;
		des--;
		BridgeNode = Graph[sta].fri;
		NewNode = new ArcNode;
		NewNode->length = len;
		NewNode->des = des;
		Graph[sta].fri = NewNode;
		NewNode->next = BridgeNode;

		BridgeNode = Graph[des].fri;
		NewNode = new ArcNode;
		NewNode->length = len;
		NewNode->des = sta;
		Graph[des].fri = NewNode;
		NewNode->next = BridgeNode;
		//串接弧节点


		i++;
	}

}
//*******
int Min(int* Nums, int* Close, int n)
{
	int i = 0;
	int j = CILING;
	int result = -1;
	while (i < n)
	{
		if (Nums[i] < j && Close[i] == 0)
		{
			j = Nums[i];
			result = i;
		}
		i++;
	}


	return result;
}
//*******
void Dijestla(GraphNode* Graph, int NodeNum, int Origin)
{
	int i = 0;
	int n = 0;//判断循环
	priority_queue<Node> P;//装所有的节点
	int* Close = new int[NodeNum];
	int NowNode;//当前节点的序列号
	ArcNode* NowArc;//当前的弧
	Node* Distance = new Node[NodeNum]();

	while (i < NodeNum)
	{
		Close[i] = 0;
		Distance[i].data = i;
		Distance[i].length = CILING / 2;
		if (i == Origin)
			Distance[i].length = 0;
		P.push(Distance[i]);
		i++;
	}
	//初始化距离数组 并将距离数组整合到优先队列里面
	i = 0;
	while (n<NodeNum)
	{
		while (1)
		{
			NowNode = P.top().data;//取出最小距离元素
			P.pop();
			if (Close[NowNode] == 0)
			{
				Close[NowNode] = 1;
				break;
			}
			

		}
		NowArc = Graph[NowNode].fri;
		while (NowArc != NULL)
		{
			if (Distance[NowArc->des].length > NowArc->length + Distance[NowNode].length)
			{
				Distance[NowArc->des].length = Distance[NowNode].length + NowArc->length;
				Node ReNew=Node();
				ReNew.data = NowArc->des;
				ReNew.length = Distance[NowNode].length + NowArc->length;
				P.push(ReNew);

			}
			NowArc = NowArc->next;
			//更新距离
		}
		//更新邻接节点的距离
		n++;
	}
	i = 0;
	Graph[Origin].if_grass = true;
	Graph[Origin].Grass.distance = new int[NodeNum];
	while (i < NodeNum)
	{
		Graph[Origin].Grass.distance[i] = Distance[i].length;
		i++;
	}
}
int MinPath(GraphNode* Graph, int GrassNum, int sta, int des, int* Grasses)
{
	int i = 0;
	int PathLength = CILING;
	int len;
	while (i < GrassNum)
	{
		int grassNumber = Grasses[i];//第几个草丛
		len = Graph[grassNumber].Grass.distance[sta] + Graph[grassNumber].Grass.distance[des];//过该草丛得到的距离
		if (len < PathLength)
			PathLength = len;
		i++;
	}

	return PathLength;
}
int main()
{
	int i = 0;
	int GraphNum, ArcNum;
	cin >> GraphNum >> ArcNum;
	GraphNode* Graph = new GraphNode[GraphNum];
	InitializeArc(Graph, ArcNum);

	int GrassNum, HorseNum;
	cin >> GrassNum >> HorseNum;
	while (i < GrassNum)
	{
		int BeginPosition;
		cin >> BeginPosition;
		BeginPosition--;
		Dijestla(Graph, GraphNum, BeginPosition);
		i++;
	}

	//求每个草点到每个点距离
	i = 0;
	int j = 0;
	int* Grasses = new int[GraphNum];
	while (i < GraphNum)
	{
		if (Graph[i].if_grass)
		{
			Grasses[j] = i;
			j++;
		}
		i++;
	}
	i = 0;
	//建立草丛速查表
	int sta, des;//起点终点
	while (i < HorseNum)
	{
		cin >> sta >> des;
		sta--;
		des--;
		cout << MinPath(Graph, GrassNum, sta, des, Grasses) << endl;
		i++;
	}



	delete[] Grasses;

	return 0;
}