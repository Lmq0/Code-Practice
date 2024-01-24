#include<iostream>
#include<queue>
#include<set>

using namespace std;

int* Solution(int DataLength, int DataNum, int* Data1,int* Data2)
{
	multiset<int>S;
	multiset<int>::iterator it;
	priority_queue<int, vector<int>, greater<int>> Heap;
	int i = 0;
	int j = 1;

	while (i < DataLength)
	{
		//Heap.push(Data1[i] + Data2[0]);
		S.insert(Data1[i] + Data2[0]);
		i++;
	}
	//�Ƚ�1��2�з���  ����������n����һ�еĺ͵ڶ��е���Сֵ֮��
	i = 0;
	while (i < DataLength)
	{
		while (j < DataLength)
		{
			
			if (Data1[i] + Data2[j] < *S.rbegin())
			{
				int a = *S.rbegin();
				it=S.find(a);
				S.erase(it);
				S.insert(Data1[i] + Data2[j]);
				j++;
			}
			else break;//��֦
			
		}
		if (j == 1)break;//��֦
		j = 1;

		i++;
	}
	//���ڶ������ǵ�һ�еڶ��еĺ͵�ǰn����С


	int* Result = new int[DataLength];
	i = 0;
	while (i < DataLength)
	{
		Result[i] = *S.begin();
		S.erase(S.begin());
		i++;
	}
	return Result;

}
int* _Solution(int DataLength, int DataNum, int** Data)
{
	int* bridgelist,*conclusion;
	conclusion = Solution(DataLength, DataNum, Data[0], Data[1]);
	int j = 2;
	while (j < DataNum)
	{
		bridgelist = conclusion;
		conclusion = Solution(DataLength, DataNum, conclusion, Data[j]);
		delete[] bridgelist;
		j++;
	}
	return conclusion;

}
void QuickSort(int* Data, int Sta, int Des)
{

	int i = Sta;
	int j = Des;
	if (Sta >= Des) return;
	int base = Data[Sta];
	while (Sta < Des)
	{
		while (Sta < Des && Data[Des] >= base)
			Des--;
		Data[Sta] = Data[Des];
		while (Sta < Des && Data[Sta] <= base)
			Sta++;
		Data[Des] = Data[Sta];
	}
	Data[Sta] = base;
	QuickSort(Data, i, Sta - 1);
	QuickSort(Data, Sta + 1, j);

}
int main()
{
	int TestNum,DataNum,DataLength;
	cin >> TestNum;
	while (TestNum)
	{
		cin >> DataNum >> DataLength;
		int j = 0; int i = 0;
		int** Data = new int* [DataNum];
		while (j < DataNum)
		{
			Data[j] = new int[DataLength];
			j++;
		}
		j = 0;
		i = 0;
		while (i < DataNum)
		{
			while(j<DataLength)
			{
				cin >> Data[i][j];
				j++;
			}
			QuickSort(Data[i], 0, DataLength - 1);
			j = 0;
			i++;
		}
		//¼��������� �������������
		int* Result = _Solution(DataLength, DataNum, Data);
		//�������
		j = 0;
		while (j<DataLength)
		{
			cout << Result[j] << " ";
			j++;
		}
		cout << endl;
		//���
		j = 0;
		while (j < DataNum)
		{
			delete[]Data[j];
			j++;
		}
		delete[]Data;
		delete[]Result;
		TestNum--;
	}
	return 0;
}