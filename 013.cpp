#include<iostream>
#include<string>

using namespace std;
class Map
{
public:
	int** map;
	int Col;
	int Row;
	Map(int col,int row)
	{
		Col = col;
		Row = row;
		int i = 0;
		map = (int**)malloc(Row * Col * 4);
		if (!map)exit(0);
		while (i < Row)
		{
			map[i] = (int*)malloc(Col * 4);
			i++;
		}
		
	}

	

};
int  sankland(int hang, int lie, Map& Result)
{
	if (hang > Result.Row - 1 || hang < 0 || lie<0 || lie>Result.Col - 1)
		return 0;
	if (Result.map[hang][lie] == 0)
		return 0;
	else if (Result.map[hang][lie] == 1)
	{
		Result.map[hang][lie] = 0;
		sankland(hang + 1, lie, Result) | sankland(hang - 1, lie, Result) | sankland(hang, lie + 1, Result) | sankland(hang, lie - 1, Result);
		return 1;
	}
	else
	{
		Result.map[hang][lie] = 0;
		return sankland(hang + 1, lie, Result) | sankland(hang - 1, lie, Result) | sankland(hang, lie + 1, Result) | sankland(hang, lie - 1, Result);
	}

}
void Count(int &count,Map &Result,int hang,int lie)
{
	if (Result.map[hang][lie] == 1)
	{
		count++;
		sankland(hang, lie, Result);
	}
	else if (Result.map[hang][lie] == -1)
	{
		if (sankland(hang, lie, Result) == 1)
			count++;
	}
	else
		;

}

int main()
{
	int m, n;//nÐÐmÁÐ
	cin >> n >> m;
	int i = 0;
	int j = 0;
	int count = 0;
	Map Result(m, n);
	while (i < n)
	{
		while (j < m)
		{
			int a = 0;
			cin >> a;
			Result.map[i][j] = a;
			if ((j == 0 || j == m - 1 || i == 0 || i == n - 1) && Result.map[i][j] == 1)
				Result.map[i][j] = -1;
			j++;
		}
		i++;
		j = 0;
	}
	i = 0;
	j = 0;
	while (i < n)
	{
		while (j < m)
		{
			if (Result.map[i][j] != 0)
				Count(count, Result, i, j);
			j++;
		}
		j = 0;
		i++;
	}
	cout << count << endl;

}

