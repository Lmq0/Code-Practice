#include<iostream>


using namespace std;


class ArcNode
{
public:
	bool if_Chosen=0;//是否相关
	int num;//权重
	ArcNode()
	{
		if_Chosen = 0;
		num = 1;
	}
	ArcNode(int num)
	{
		this->num = num;
	}
	~ArcNode()
	{
		;
	}
};
void CreateRelation(ArcNode** Arcs, int n)
{
	int i = 0;
	int j = 0;
	int row, col;
	int ArcNum = 0;
	while (i < n)
	{
	
		while (j < n)
		{
			cin >> Arcs[i][j].num;
			j++;
		}
		i++;
		j = 0;
	}
	//距离关系初始化
	cin >> ArcNum;
	i = 0;
	while (i < ArcNum)
	{
		cin >> row >> col;
		
		Arcs[row - 1][col - 1].num = 0;
		Arcs[col - 1][row - 1].num = 0;
		i++;
	}
	//初始有路那么设置路径长度为0 无需是否修建变量 if_Chosen

}
//得到弧矩阵  
int MinusArc(ArcNode** Arcs, int* if_Collected, int n, int& sta, int& des)
{

	//寻找长度最短的  
	int i = 0;
	int j = 0;
	int length = 1000;
	while (i < n)
	{
		while (j < n)
		{

			if (Arcs[i][j].num < length && i != j
				&& ((if_Collected[i]!=if_Collected[j])||(if_Collected[i]==0&&if_Collected[j]==0)))
			{
				//起始边从属不一样 而且不能自己指自己 并且短的 仅查找不修改
				sta = i;
				des = j;
				length = Arcs[i][j].num;
				
			}
			j++;
		}
		j = 0;
		i++;
	}
	return length;
}
int PathFinding(ArcNode** Arcs,int n)
{
	int num = 0;//计算边数
	int sum = 0;//计算距离
	int TreeNum = 1;//从属子树编号 1开始
	int* if_Collected = new int[n];//从属关系向量  0代表自由 
	int i = 0;
	while (i < n)
	{
		if_Collected[i] = 0;
		i++;
	}
	//从属向量初始化0
	int sta, des;//弧起点终点
	while (num < n - 1)//弧一共n-1条 不算最开始建立了的
	{
		int length = MinusArc(Arcs,if_Collected, n, sta, des);
		if (if_Collected[sta] == 0 && if_Collected[des] == 0)
		{
			if_Collected[sta] = TreeNum;
			if_Collected[des] = TreeNum;
			TreeNum++;
			//新建一个treeNum
		}
		else if (if_Collected[sta] == 0 && if_Collected[des] != 0)
		{
			if_Collected[sta] = if_Collected[des];
		}
		else if (if_Collected[sta] != 0 && if_Collected[des] == 0)
		{
			if_Collected[des] = if_Collected[sta];
		}
		else
		{
			//遍历一遍从属向量 把des从属的节点全部接到sta上
			int a = 0;
			int belong = if_Collected[des];
			while (a < n)
			{
				
				if (if_Collected[a] == belong)
				{
					if_Collected[a] = if_Collected[sta];
				}
				a++;
			}
		}
		sum += length;
		num ++;
	}
	
	return sum;

}

//找最短边 用于起始边
int main()
{
	int NodeNum;
	cin >> NodeNum;
	ArcNode** Arcs = new ArcNode*[NodeNum];
	int i = 0;
	while (i < NodeNum)
	{
		Arcs[i] = new ArcNode[NodeNum]();
		i++;
	}
	//初始化
	CreateRelation(Arcs, NodeNum);
	cout << PathFinding(Arcs, NodeNum);

	

			

	return 0;
}