#include<iostream>
using namespace std;
int main()
{
	int length, step;
	cin >> length >> step;
	int num = 0;
	int* store = (int*)malloc((1+length) * sizeof(int));
	if (store==NULL)
		exit(0);
	while (num < length)
	{
		
		cin >> store[num];
		num++;
	}
	if (step > 0)
		step = step % length;
	else
	{
		step *= -1;
		step = step % length;
		step *= -1;
	}

	if (step > 0)
	{
		int head = length-step;//读取的位置记录


		while (head < length)
		{
			cout << store[head] << " ";
			head++;
		}
		head = 0;
		while (head < length-step)
		{
			cout << store[head] << " ";
			head++;
		}
		cout << endl;
	
	}
	else if (step == 0)
	{
		int head=0;
		while (head < length)
		{
			cout << store[head]<<" ";
			head++;
		}
		cout << endl;
	}
	else
	{
		int head = step*( - 1);
		while (head < length)
		{
			cout << store[head] << " ";
			head++;
		}
		head = 0;
		while (head<step*(-1))
		{
			cout << store[head] << " ";
			head++;
		}
		cout << endl;
	}
	return 0;

}
