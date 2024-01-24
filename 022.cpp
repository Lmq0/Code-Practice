#include<iostream>
#include<string>
#include<queue>
#include<stack>

using namespace std;
class ArcNode
{
public:
	int des=0;
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
	while (i < n)
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


		ArcNode* tail1=Graph[Node1].fri;
		if (tail1 == NULL)
		{
			Graph[Node1].fri = arc1;
		}
		else
		{
			while(tail1->next != NULL)
			{
				tail1 = tail1->next;
			}
			tail1->next = arc1;

		}
		ArcNode* tail2=Graph[Node2].fri;
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
void DFS(GraphNode* Graph, int n)
{
	int* if_Collected = new int[n];//判断是否遍历过了
	int i = 0;
	int PopedNodeNum = 0;
	GraphNode* NowNode;
	ArcNode* NowArc;
	stack<GraphNode*> S;
	while (i < n)
	{
		if_Collected[i] = 0;
		i++;
	}
	//初始化
	S.push(Graph);//0进栈
	if_Collected[0] = 1;
	cout << "{0";

	while (!S.empty()||PopedNodeNum!=n)
	{
		if (!S.empty())
		{
			NowNode = S.top();
			NowArc = NowNode->fri;
			while (NowArc != NULL)
			{

				if (if_Collected[NowArc->des] == 0)
				{
					S.push(Graph + NowArc->des);
					cout<<" "<< S.top()->data;
					if_Collected[NowArc->des] = 1;
					break;
				}
				NowArc = NowArc->next;
			}
			if (NowArc == NULL)
			{
				PopedNodeNum++;
				S.pop();
			}
		}
		else
		{
			cout << "}";
			int i = 0;
			while (i < n)
			{
				if (if_Collected[i] == 0)
				{
					S.push(Graph + i);
					if_Collected[i] = 1;
					cout << "{" << Graph[i].data;
					break;
				}
				i++;
			}

		}

	}
	cout << "}" << endl;


	delete[]if_Collected;
}
void BFS(GraphNode* Graph, int n)
{
	int* if_Collected = new int[n];//判断是否遍历过了
	int i = 0;
	int PopedNodeNum = 0;
	GraphNode* NowNode;
	ArcNode* NowArc;
	queue<GraphNode*> Q;
	while (i < n)
	{
		if_Collected[i] = 0;
		i++;
	}
	Q.push(Graph);
	if_Collected[0] = 1;
	cout << "{0";


	while (!Q.empty()||PopedNodeNum!=n)
	{
		if (!Q.empty())
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
						cout <<" "<< Graph[NowArc->des].data;
						if_Collected[NowArc->des] = 1;
					}
					NowArc = NowArc->next;
				}
				Q.pop();
				PopedNodeNum++;
				i++;
			}
		}
		else
		{
			cout << "}";
			int i = 0;
			while (i < n)
			{
				if (if_Collected[i] == 0)
				{
					Q.push(Graph + i);
					if_Collected[i] = 1;
					cout << "{" << Graph[i].data;
					break;
				}
				i++;
			}
		}
	}
	cout << "}" << endl;
	delete[]if_Collected;

}
int main()
{
	int arcNum, NodeNum;
	cin >> NodeNum >> arcNum;
	GraphNode* Graph = new GraphNode[NodeNum];
	OriGraph(NodeNum, Graph);
	OriArc(arcNum, Graph);
	DFS(Graph, NodeNum);
	BFS(Graph, NodeNum);
	return 0;
}