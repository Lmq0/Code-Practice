#include<iostream>
#include<stack>

using namespace std;
class RelationNode
{
public:
	int relation = 0;//弧另一端
	RelationNode* next;
};
class ClassNode
{
public:
	int time;//修读时间
	int IntNum = 0;
	int ProitryTime = 0;
	int LastTime = INT16_MAX;
	RelationNode* FirstChild;
	RelationNode* FirstFather;
	
	ClassNode()
	{
		time = 0;
		FirstChild = NULL;
		FirstFather = NULL;
	}
	
};
void InitializeNode(ClassNode* Class ,int n)
{
	int i = 0; 
	int j = 0;

	while (i < n)
	{
		cin >> Class[i].time;
		cin >> Class[i].IntNum;
		j = 0;
		while(j<Class[i].IntNum)
		{
			RelationNode* NewRelation = new RelationNode;
			cin >> NewRelation->relation;
			NewRelation->relation--;
			NewRelation->next = Class[i].FirstFather;
			Class[i].FirstFather = NewRelation;
			j++;
			RelationNode* NextRelation = new RelationNode;
			NextRelation->next = Class[NewRelation->relation].FirstChild;
			Class[NewRelation->relation].FirstChild = NextRelation;
			NextRelation->relation = i;



		}


		i++;
	}


}
int FindNoInNode(ClassNode* Class, int n)
{
	int i = 0;
	while (i < n)
	{
		if (Class[i].IntNum == 0)
		{
			return i;
		}
		i++;
	}
	return -1;
}
void Deletenode(ClassNode* Class, int Deleted)
{
	Class[Deleted].IntNum = -1;
	RelationNode* relation = Class[Deleted].FirstChild;
	while (relation != NULL)
	{
		Class[relation->relation].IntNum--;
		relation = relation->next;
	}

}
void FindOrder(stack<int>& S, int Num,ClassNode* Class)
{
	int i = 0;
	
	while (1)
	{
		int node = FindNoInNode(Class, Num);
		if (node == -1)
		{
			break;
		}
		Deletenode(Class, node);
		S.push(node);
		RelationNode* Relations = Class[node].FirstChild;
		while (Relations!=NULL)
		{
			Class[Relations->relation].ProitryTime=
				max(Class[node].ProitryTime+Class[node].time, Class[Relations->relation].ProitryTime);
			//更新值
			Relations = Relations->next;
		}
		i++;
	}
	

}
void GetLastTime(stack<int>& S, int Num, ClassNode* Class)//反拓扑排序遍历
{
	int NowNode,n;
	NowNode = S.top();
	n = 0;
	int Maxium = Class[NowNode].ProitryTime+Class[NowNode].time;//最大时间
	while (n < Num)
	{
		Class[n].LastTime = Maxium;
		n++;
	}


	while (!S.empty())
	{
		NowNode = S.top();
		S.pop();
		RelationNode* Relation = Class[NowNode].FirstFather;
		while(Relation!=NULL)
		{
			Class[Relation->relation].LastTime =
				min(Class[Relation->relation].LastTime, Class[NowNode].LastTime - Class[NowNode].time);
			Relation = Relation->next;
		}



	}


}
void Display(ClassNode* Class, int Num,int type=1)
{
	int i = 0;
	while (i < Num)
	{
		if (type == 1)
		{
			//cout << "时间" << Class[i].time;
			cout << Class[i].ProitryTime + Class[i].time<<" "<< (Class[i].ProitryTime + Class[i].time==Class[i].LastTime)<<endl;
			
		}
		else if (type == 2)
		{
			cout << i << ":*******" << endl;
			cout << Class[i].time << " " << Class[i].ProitryTime+Class[i].time<<" " <<Class[i].IntNum<< endl;
			cout << "后继:" << endl;
			RelationNode* p = Class[i].FirstChild;
			while (p != NULL)
			{
				cout << p->relation << " ";
				p = p->next;
			}
			cout << endl;
			cout << "前驱:" << endl;
			p = Class[i].FirstFather;
			while (p != NULL)
			{
				cout << p->relation << " ";
				p = p->next;
			}
			cout << endl;
		}
		i++;
	}
}
int main()
{
	int i = 0;
	int ClassNum;
	cin >> ClassNum;
	ClassNode* Class = new ClassNode[ClassNum];//记录课节点
	InitializeNode(Class, ClassNum);

	stack<int>S;
	FindOrder(S, ClassNum, Class);

	GetLastTime(S, ClassNum, Class);
	Display(Class, ClassNum, 1);
	 
	return 0;
}