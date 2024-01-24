#include<iostream>
#include<algorithm>
#include<set>

using namespace std;

int Double_Sort(int *Sum,int Num,int FindNum)
{
	int front = 0;
	int back = Num-1;
	int NowNode;
	if (FindNum >= Sum[Num - 1])
		return Num - 1;
	if (FindNum < Sum[0])
		return -1;
	while (true)
	{
		NowNode = (front + back)/2;
	
		if (Sum[NowNode] > FindNum)
			back = NowNode;
		else if (Sum[NowNode] < FindNum)
			front = NowNode;
		else return NowNode;
		if (back - front == 1)
			return front;
	}

	return -1;

}
int main()
{
	int Num, QuesNum;
	cin >> Num >> QuesNum;
	set<int> S;
	set<int>::iterator it;
	int i=0;
	int* data = new int[Num+1];
	int* Sum = new int[Num];//前缀和数组 第n项为前n项和
	int* Ques = new int[QuesNum];
	int p = 0;
	while (i < Num)
	{
		cin >> data[i];
		i++;
	}
	sort(data, data + Num);

	/*
	while (i < Num)
	{
		int element;
		cin >> element;
		S.insert(element);
		i++;
	}
	*/
	//完成初始化操作
	//it = S.begin();//设置为头部
	i = 0;
	
	while (i < QuesNum)
	{
		cin >> Ques[i];
		i++;
	}
	//初始化问题数组
	i = 0;
	/*
	while (i < Num)
	{
		p += *it;
		Sum[i] = p;
		i++;
		it++;
		if (it == S.end())
		{
			break;
		}
	}
	//初始化前缀和数组
	*/
	while (i < Num)
	{
		p += data[i];
		Sum[i] = p;
		i++;
	}
	i = 0;
	while (i < QuesNum)
	{
		cout << Double_Sort(Sum, Num, Ques[i])+1<<" ";
		i++;
	}
	cout << endl;


}