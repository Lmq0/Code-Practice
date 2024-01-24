




#include<iostream>
#include<cmath>

using namespace std;

int Min_Prime_Number(int a)
{
	if (a == 1) return 2;//特殊情况
	int ciling = min(int(sqrt(a)+1),a);
	int Remainder;
	int i = 2;
	while (i < ciling)
	{
		Remainder = a % i;
		if (Remainder == 0)
		{
			a++;
			ciling = min(int(sqrt(a) + 1), a);
			i = 2;
			continue;
		}
		i++;
	}

	return a;
}
int main()
{
	int BasNum, RfNum;
	cin >> BasNum >> RfNum;
	RfNum = Min_Prime_Number(RfNum);
	//质数修正
	string* List = new string[RfNum];//散列表
	string element;
	int i = 0;
	int j = 0;
	long long int sum = 0;//位置总和

	while (i < BasNum)
	{
		cin >> element;
		int size = element.length();

		while (j < size)
		{
			sum *= 37;
			sum += element[j];
			sum %= RfNum;
			j++;
		}
		//计算完总和
		if (List[sum] == "")
		{
			List[sum] = element;
			cout << sum << " ";
		}
		else
		{
			int SafariTimes = 1;
			while (SafariTimes<=RfNum/2)
			{
				if (List[(sum + (int)pow(SafariTimes, 2)) % RfNum] == "")
				{
					List[(sum + (int)pow(SafariTimes, 2)) % RfNum] = element;
					cout << (sum + (int)pow(SafariTimes, 2)) % RfNum <<" ";
					break;
				}
				if (List[(sum - (int)pow(SafariTimes, 2)+RfNum*SafariTimes) % RfNum] == "")
				{
					List[(sum - (int)pow(SafariTimes, 2)+RfNum * SafariTimes) % RfNum] = element;
					cout << (sum - (int)pow(SafariTimes, 2) + RfNum * SafariTimes) % RfNum << " ";
					break;
				}
				SafariTimes++;
			}
			if (SafariTimes > RfNum / 2)
				cout << "- ";

		}
	
		i++;
		j = 0;
		sum = 0;
		
	}
	cout << endl;
	delete[] List;

	return 0;
}