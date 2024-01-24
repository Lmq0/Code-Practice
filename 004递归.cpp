#include<iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	int t = 2;
	int returning = m % t;
	while (t < n)
	{
		t++;
		returning = (returning + m) % t;

	}
	cout << returning << endl;
	return 0;
}