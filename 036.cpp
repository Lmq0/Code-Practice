
/*
#include<iostream>

using namespace std;


void FastSort(string* Data, int Sta,int Des)
{
	
	int i = Sta;
	int j = Des;
	if (Sta == Des)
		return;
	while (i < j)
	{
		if (Data[i] >= Data[j])
			j--;
		else
		{
			swap(Data[i], Data[j]);
			i++;
		}
	}
	//��ʱi=j
	FastSort(Data,Sta, i);
	FastSort(Data, i + 1, Des);

}
string ToAstring(string* Data, int Num)
{
	string result="";
	int i = 0;
	while (i < Num)
	{
		result += Data[i];
		i++;
	}

	return result;
}
int main()
{
	int i = 0;
	int DataNum;
	cin >> DataNum;
	string* Data = new string[DataNum];
	while (i < DataNum)
	{
		cin >> Data[i];
		i++;
	}
	FastSort(Data, 0, DataNum - 1);
	cout << ToAstring(Data, DataNum) << endl;
	//������



	return 0;
}
*/
/**
 * @file    template.cpp
 * @name    ģ�����
 * @date    2022-11-22
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
class Solution {
public:
	bool Compare(string as, string bs)//a�Ƿ�������b
	{
		if (as == bs)return true;

		int i = 0;
		int length = min(as.size(), bs.size());
		while (i<length)
		{
			if (as[i] > bs[i])
				return true;
			else if (as[i] < bs[i])
				return false;
			else
			{
				i++;
			}

		}
		//��ʱabǰ�沿����ȫһ�� ��һ����һЩ     
		if (as.size() < bs.size())
			return Compare(as, bs.substr(i));
		else return Compare(as.substr(i), bs);

	}
	void FastSort(std::vector<int> &Data, int Sta, int Des)
	{
		int base = Data[Sta];

		int i = Sta;
		int j = Des;
		if (i >= j)
			return;
		while (i < j)
		{
			while (i < j && Compare(to_string(base), to_string(Data[j])))
			{
				j--;
			}
			Data[i] = Data[j];
			while (i < j && Compare(to_string(Data[i]), to_string(base)))
			{
				i++;
			}
			Data[j] = Data[i];


		}
		//��ʱi=j
		Data[i] = base;
		FastSort(Data, Sta, i - 1);
		FastSort(Data, i + 1, Des);

	}
	string ToAstring(std::vector<int> Data)
	{
		int Num = Data.size();
		string result = "";
		int i = 0;
		while (i < Num)
		{
			result += std::to_string(Data[i]);
			i++;
		}

		return result;
	}
	std::string largestNumber(std::vector<int>& nums)
    {
		FastSort(nums, 0, nums.size() - 1);
		return ToAstring(nums);
	}
};
/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/

int main() 
{
	int n;
	Solution s1;
	cout << s1.Compare("966386", "9663") << endl;
	std::cin >> n;
	std::vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		std::cin >> nums[i];
	}
	Solution s;
	std::cout << s.largestNumber(nums) << std::endl;
	return 0;
}