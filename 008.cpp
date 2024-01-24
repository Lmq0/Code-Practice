#define ERROW -1;
#include<iostream> 
#include<cmath>
using namespace std;

struct Numberlist
{
	int* num;
	int length;
};

//创建的初始数值小于100
Numberlist Createlist(int Number = 0)
{
	Numberlist Createdlist;
	int a = 1;
	int creatnumber = Number;
	while (creatnumber / 10 > 0)
	{
		creatnumber = creatnumber / 10;
		a++;
	}
	Createdlist.num = (int*)malloc(a * sizeof(int));
	Createdlist.length = a;
	a = 0;
	while (a < Createdlist.length)
	{
		Createdlist.num[a] = Number-(Number/10)*10;
		Number /= 10;
		a++;
	}

	return Createdlist;
}
void DestoryList(Numberlist& list)
{
	free(list.num);
}
Numberlist ListPlus(Numberlist& list1, Numberlist& list2)//前低位后高位反序存储
{
	Numberlist targetlist;
	targetlist.length = (list1.length >= list2.length) ? list1.length+1 : list2.length+1;//多分配一位 防止进位
	targetlist.num = (int*)malloc(targetlist.length * sizeof(int));
	int a = 0;
	while (a < targetlist.length)
	{
		targetlist.num[a] = 0;
		a++;
	}
	int* p1, * p2;
	p1 = list1.num;
	p2 = list2.num;

	a = 0;
	int if_Plus_Digit = 0;
	while (a < list1.length && a < list2.length)
	{
		targetlist.num[a] = p1[a] + p2[a];
		
		a++;
	}
	while (a < list1.length)
	{
		targetlist.num[a] = p1[a];
	
		a++;
	}
	while (a < list2.length)
	{
		targetlist.num[a] = p2[a];
		
		a++;
	}
	a = 0;
	while (a < targetlist.length)
	{
		targetlist.num[a] += if_Plus_Digit;
		if_Plus_Digit = 0;
		if (targetlist.num[a] >= 10)
		{
			if_Plus_Digit = targetlist.num[a] / 10;
			targetlist.num[a] %= 10;
		}
		a++;
	}
	while (targetlist.num[targetlist.length - 1] == 0)
	{
		targetlist.length--;
	}
	return targetlist;
}
Numberlist ListMultply(Numberlist& list1, Numberlist& list2)
{
	int digital1=1;
	int digital2=1;
	Numberlist targetlist;
	targetlist.length = list1.length >= list2.length ? list1.length*2 : list2.length*2;//多分配一倍 防止进位
	targetlist.num = (int*)malloc(targetlist.length * sizeof(int));
	int a = 0;
	while (a < targetlist.length)
	{
		targetlist.num[a] = 0;
		a++;
	}
	//每一位初始为0
	int For_Digital_Plus = 0;
	//每一位每一位的算
	{
		/*
		while (digital1 < list1.length )
		{

			while (digital2 < list2.length)
			{
				p_target[digital1 + digital2-2] = (p1[digital1-1] * p2[digital2-1])%10+if_Plus+ p_target[digital1 + digital2 - 2];
				if_Plus = 0;
				if (p_target[digital1 + digital2 - 2] >= 10)
				{
					p_target[digital1 + digital2 - 2] %= 10;
					if_Plus = p_target[digital1 + digital2 - 2] / 10;
				}
				//加法进位
				if (p1[digital1 - 1] * p2[digital2 - 1] >= 10)
				{
					if_Plus= (p1[digital1 - 1] * p2[digital2 - 1]) / 10;
				}
				//进位
				digital2++;
				if (digital2 == list2.length&&if_Plus!=0)
				{
					p_target[digital1 + digital2 - 2] += if_Plus;
					if (p_target[digital1 + digital2 - 2] >= 10)
					{

					}
				}
			}
		}
		*/
	}
	while (digital1 <= list1.length)
	{
		while (digital2 <= list2.length)
		{
			targetlist.num[digital1 + digital2 - 2] += list1.num[digital1 - 1] * list2.num[digital2 - 1];
			digital2++;
		}
		digital1++;
		digital2 = 1;
	}
	int CountDigital = 1;
	while (CountDigital <= targetlist.length)
	{
		targetlist.num[CountDigital - 1] += For_Digital_Plus;
		For_Digital_Plus = 0;
		if (targetlist.num[CountDigital - 1] >= 10)
		{

			For_Digital_Plus = targetlist.num[CountDigital - 1] / 10;
			targetlist.num[CountDigital - 1] %= 10;
			
		}

		CountDigital++;
		
	}
	a = targetlist.length;
	while (targetlist.num[a - 1] == 0)
	{
		targetlist.length--;
		a--;
	}

	return targetlist;
}
Numberlist ListPow(Numberlist& list, int PowNumber)
{
	Numberlist targetlist;
	targetlist.length =1;//题目不超过15
	targetlist.num = (int*)malloc(targetlist.length * sizeof(int));
	targetlist.num[0] = 1;//初始化为1
	int times = 0;
	while (times < PowNumber)
	{
		Numberlist bridglist = ListMultply(targetlist, list);
		DestoryList(targetlist);
		targetlist = bridglist;
		times++;
	}
	return targetlist;
}
Numberlist UltimateArithmatic(Numberlist& list, int MaxRange)
{
	Numberlist targetlist;
	targetlist = Createlist();
	int a = MaxRange;
	Numberlist Arithmaticlist1 = Createlist();//记录次方后的式子
	Numberlist Arithmaticlist2 = Createlist(1);//每一个的系数
	Numberlist bridgelist;

	while (a > 0)
	{
		Arithmaticlist1=ListPow(list, a);
		Arithmaticlist2.num[0] = a;
		bridgelist = ListMultply(Arithmaticlist1, Arithmaticlist2);
		DestoryList(Arithmaticlist1);
		Arithmaticlist1 = bridgelist;//乘完常数做完平方了

		bridgelist = ListPlus(Arithmaticlist1, targetlist);
		DestoryList(targetlist);
		targetlist = bridgelist;

		a--;
	}
	return targetlist;

}


void ListPutOut(Numberlist display)
{
	int a = display.length;
	while (display.num[a - 1] == 0)
	{

		a--;
	}
	//去除首位的0
	while (a > 0)
	{
		cout << display.num[a-1];
		a--;
	}
}
int main()
{
	int MaxRang;
	int BasicNum;//小写的是list形式的数
	while (cin>>MaxRang >> BasicNum)
	{
		Numberlist basicnum;
		if (BasicNum == 0)
		{
			cout << 0 << endl;
			continue;
		}
		basicnum = Createlist(BasicNum);
		{
			/*
			ListPutOut(basicnum);
			cout << endl;

			cout<< "Sum" << endl;
			Numberlist result1 = ListPlus(basicnum, basicnum);
			ListPutOut(result1);
			cout << endl;

			cout << "Multy" << endl;
			Numberlist result2 = ListMultply(basicnum, basicnum);
			ListPutOut(result2);
			cout << endl;

			cout << "Pow" << endl;
			Numberlist result3 = ListPow(basicnum,MaxRang);
			ListPutOut(result3);
			cout << endl;

			*/
		}

		Numberlist result4 = UltimateArithmatic(basicnum, MaxRang);
		ListPutOut(result4);
		cout << endl;

	}




	return 0;
}