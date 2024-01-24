#include<iostream>
using namespace std;
int main()
{
	int year[256];
	long long int xiong_bee[256] = { 0 };
	long long int ci_bee[256] = { 0 };
	const int magicbee = 1;
	int row = 0;
	while (1)
	{
		cin >> year[row];
		if (year[row] == -1)
		{
			break;
		}//³ö¿Ú
		int year_for_caculate = 0;
		while (year_for_caculate < year[row])
		{
			long long int bridge = ci_bee[row];
			ci_bee[row] = xiong_bee[row];
			xiong_bee[row] += (bridge + 1);
			year_for_caculate++;
		}
		row++;
	}

	int row_for_output = 0;
	while (row_for_output < row)
	{
		cout << xiong_bee[row_for_output] << " " << ci_bee[row_for_output] + xiong_bee[row_for_output] + 1 << endl;
		row_for_output++;
	}
	return 0;
}