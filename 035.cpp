#include<iostream>

using namespace std;

int ans = 0;

void Merge(int*List,int l, int m, int r)
{
	int i = l;
	int j = m + 1;
	int k = l;

	int* tmp = new int[r+1];

	while (i <= m && j <= r)
	{
		if (List[i] > List[j])
		{
			tmp[k++] = List[j++];
			ans += m - i + 1;
		}
		else
		{
			tmp[k++] = List[i++];
		}
	}
	while (i <= m) tmp[k++] = List[i++];
	while (j <= r) tmp[k++] = List[j++];

	for (int i = l; i <= r; i++)
		List[i] = tmp[i];

	delete[]tmp;
}
void Merge_sort(int* List,int l, int r)
{
	if (l < r)
	{
		int m = (l + r) >> 1;
		Merge_sort(List,l, m);
		Merge_sort(List,m + 1, r);
		Merge(List,l, m, r);
	}
}
int main()
{
	int Num;
	int* List;
	int i = 0;

	while (1)
	{
		i = 0;
		cin >> Num;
		if (Num == 0) break;
		List = new int[Num];
		while (i < Num)
		{
			cin >> List[i];
			i++;
		}
		Merge_sort(List, 0, Num - 1);
		cout << ans << endl;
		ans = 0;
		delete[]List;
	}

	return 0;
}