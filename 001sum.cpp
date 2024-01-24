#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	float sum = 0;//求和
	int times = 0;//计算输入的次数
    float fee[12];
	while (times < 12)
	{
		cin >> fee[times];//连续线性 用数组

		times++;
	}
	times = 0;//更换为求加了多少次
	while (times < 12)
	{
		sum += fee[times];
		times++;
	}
	sum /= 12;
	cout << "￥";
	cout << fixed << setprecision(2) << sum<<endl;


	return 0;
}
