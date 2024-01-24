#include<iostream>
#include<stack>
#include<queue>

using namespace std;
class GraphNode
{
public:
	int data;
};
class ArcNode
{
public:
	bool if_visited = 0;
	int relation=0;

};
void Initialize(ArcNode** Arcs)
{
	Arcs[0][2].relation = 1;
	Arcs[2][0].relation = 1;

	Arcs[0][1].relation = 1;
	Arcs[1][0].relation = 1;

	Arcs[0][4].relation = 1;
	Arcs[4][0].relation = 1;

	Arcs[1][4].relation = 1;
	Arcs[4][1].relation = 1;

	Arcs[1][2].relation = 1;
	Arcs[2][1].relation = 1;

	Arcs[4][2].relation = 1;
	Arcs[2][4].relation = 1;

	Arcs[3][2].relation = 1;
	Arcs[2][3].relation = 1;

	Arcs[3][4].relation = 1;
	Arcs[4][3].relation = 1;
	//��ʼ��������

}
void display(stack<GraphNode*>S)
{
	stack<GraphNode*>S2 = S;
	while (!S2.empty())
	{
		cout << S2.top()->data;
		S2.pop();
	}
	cout << endl;
}
void FindWay(ArcNode** Arcs,GraphNode* Graph,int ArcNum)
{
	int ArcNumber = 0;
	stack<GraphNode*>S1;
	stack<int>S2;
	S1.push(Graph);//�׽ڵ�����ջ
	S2.push(-1);//�׽ڵ��������һ���ߵ�·
	while (!S1.empty())
	{
		GraphNode* NowNode = S1.top();
		int LastArc = S2.top();
		int i = LastArc;
		bool if_find = false;
		while (i < 4)
		{
			i++;
			if (Arcs[NowNode->data-1][i].relation == 1&& Arcs[NowNode->data - 1][i].if_visited==false)
			{
				if_find = true;
				break;
			}
		}
		if (if_find)//�ҵ�
		{
			Arcs[NowNode->data - 1][i].if_visited = true;//�ñ߱��߹�
			Arcs[i][NowNode->data - 1].if_visited = true;
			S2.pop();
			S2.push(i);
			S1.push(Graph + i);
			S2.push(-1);
			ArcNumber++;
			if (ArcNumber == ArcNum)
			{
				display(S1);
			
			}
		}
		else
		{
			ArcNumber--;
			S2.pop();
			S1.pop();
			if (!S1.empty())
			{
				Arcs[NowNode->data - 1][S1.top()->data - 1].if_visited = false;
				Arcs[S1.top()->data - 1][NowNode->data - 1].if_visited = false;
			}
			//��ԭ��
		}
	}

}
int main()
{
	int i = 0;
	//�������벿���Һ��Ե���  ֱ�ӹ���oj������Ǹ�ͼ
	GraphNode* Graph = new GraphNode[5];
	while (i < 5)//��data��ֵ
	{
		Graph[i].data = i+1;
		i++;
	}
	i = 0;
	ArcNode** Arcs = new ArcNode*[5];
	while (i < 5)
	{
		Arcs[i] = new ArcNode[5];
		i++;
	}
	//��ʼ��ͼ��
	Initialize(Arcs);
	FindWay(Arcs, Graph, 8);




	
	delete[] Arcs;
	delete[] Graph;
	return 0;
}