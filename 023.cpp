#include<iostream>
#include<iomanip>
#include<string>
#include<queue>
#include<stack>

using namespace std;
class ArcNode
{
public:
	int des = 0;
	ArcNode* next;

};
class GraphNode
{
public:
	int data;//与数组中编号相同
	ArcNode* fri;
	GraphNode()
	{
		data = 0;
		fri = new ArcNode();
		fri = NULL;
	}
	~GraphNode()
	{
		delete fri;
	}

};
void OriGraph(int n, GraphNode* Graph)
{
	int i = 0;
	while (i <= n)
	{
		Graph[i].data = i;
		i++;
	}

}
void OriArc(int n, GraphNode* Graph)
{
	int i = 0;

	int Node1, Node2;
	while (i < n)
	{

		cin >> Node1 >> Node2;
		ArcNode* arc1 = new ArcNode;
		ArcNode* arc2 = new ArcNode;
		arc1->des = Node2;
		arc1->next = NULL;
		arc2->des = Node1;
		arc2->next = NULL;


		ArcNode* tail1 = Graph[Node1].fri;
		if (tail1 == NULL)
		{
			Graph[Node1].fri = arc1;
		}
		else
		{
			while (tail1->next != NULL)
			{
				tail1 = tail1->next;
			}
			tail1->next = arc1;

		}
		ArcNode* tail2 = Graph[Node2].fri;
		if (tail2 == NULL)
		{
			Graph[Node2].fri = arc2;
		}
		else
		{
			while (tail2->next != NULL)
			{
				tail2 = tail2->next;
			}
			tail2->next = arc2;

		}


		i++;
	}

}

int BFS_six(GraphNode* Graph, int n,int oriNode)
{
	int* if_Collected = new int[n+1];//判断是否遍历过了
	int i = 0;
	int steps = 0;
	int sum = 0;
	GraphNode* NowNode;
	ArcNode* NowArc;
	queue<GraphNode*> Q;
	while (i <=n)
	{
		if_Collected[i] = 0;
		i++;
	}
	//初始化
	Q.push(Graph+oriNode);//首节点进栈
	if_Collected[oriNode] = 1;


	while (!Q.empty())
	{
		int size = Q.size();
		i = 0;
		while (i < size)
		{
			NowNode = Q.front();
			NowArc = NowNode->fri;
			while (NowArc != NULL)
			{
				if (if_Collected[NowArc->des] == 0)
				{
					Q.push(Graph + NowArc->des);
					if_Collected[NowArc->des] = 1;
					sum++;
				}
				NowArc = NowArc->next;
			}
			Q.pop();
			
			i++;
		}
		steps++;
		if (steps == 6)
			break;
	}
	return sum;

}

int main()
{
	int CanReachPersons;
	int arcNum, NodeNum;
	cin >> NodeNum >> arcNum;
	GraphNode* Graph = new GraphNode[NodeNum+1];//注意这里0空置
	OriGraph(NodeNum, Graph);
	OriArc(arcNum, Graph);

	int i = 1;
	while (i <= NodeNum)
	{
		CanReachPersons = BFS_six(Graph, NodeNum, i)+1;
		cout << i << ": ";
		cout << setiosflags(ios::fixed) << setprecision(2);
		cout<<(float)(CanReachPersons*(float)100) / (float)NodeNum<<"%" << endl;
		i++;
	}

	return 0;
}
