#include<iostream>


using namespace std;


class ArcNode
{
public:
	bool if_Chosen=0;//�Ƿ����
	int num;//Ȩ��
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
	//�����ϵ��ʼ��
	cin >> ArcNum;
	i = 0;
	while (i < ArcNum)
	{
		cin >> row >> col;
		
		Arcs[row - 1][col - 1].num = 0;
		Arcs[col - 1][row - 1].num = 0;
		i++;
	}
	//��ʼ��·��ô����·������Ϊ0 �����Ƿ��޽����� if_Chosen

}
//�õ�������  
int MinusArc(ArcNode** Arcs, int* if_Collected, int n, int& sta, int& des)
{

	//Ѱ�ҳ�����̵�  
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
				//��ʼ�ߴ�����һ�� ���Ҳ����Լ�ָ�Լ� ���Ҷ̵� �����Ҳ��޸�
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
	int num = 0;//�������
	int sum = 0;//�������
	int TreeNum = 1;//����������� 1��ʼ
	int* if_Collected = new int[n];//������ϵ����  0�������� 
	int i = 0;
	while (i < n)
	{
		if_Collected[i] = 0;
		i++;
	}
	//����������ʼ��0
	int sta, des;//������յ�
	while (num < n - 1)//��һ��n-1�� �����ʼ�����˵�
	{
		int length = MinusArc(Arcs,if_Collected, n, sta, des);
		if (if_Collected[sta] == 0 && if_Collected[des] == 0)
		{
			if_Collected[sta] = TreeNum;
			if_Collected[des] = TreeNum;
			TreeNum++;
			//�½�һ��treeNum
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
			//����һ��������� ��des�����Ľڵ�ȫ���ӵ�sta��
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

//����̱� ������ʼ��
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
	//��ʼ��
	CreateRelation(Arcs, NodeNum);
	cout << PathFinding(Arcs, NodeNum);

	

			

	return 0;
}