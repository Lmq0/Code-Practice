#include<iostream>
#include<string>

using namespace std;
const int THEMAXSIZE = 150;


struct Stack {
	char* base;
	char* top;
	//用int表示是否有车，1有0没有；
};
bool EmptyStack(Stack& S)
{
	char* p = S.base;
	while (p < S.top)
	{
		*p = NULL;
		p++;
	}
	S.top = S.base;
	return true;
}
Stack CreateStack(Stack& S)
{
	S.base = (char*)malloc(sizeof(int) * THEMAXSIZE);
	S.top = S.base;
	int i = 0;
	while (i < THEMAXSIZE)
	{
		S.base[i] = NULL;
		i++;
	}


	return S;
}
bool Push(Stack& S, char element)
{
	if (S.top - S.base >= THEMAXSIZE)
		return false;
	*S.top = element;
	S.top++;
	return true;
}
bool Pop(Stack& S, char& element)
{
	if (S.top == S.base)
		return false;
	element = *(S.top - 1);
	*(S.top - 1) = NULL;
	S.top--;
	return true;
}
bool Seek(Stack& S, char& element)
{
	if (S.top == S.base)
	{
		element = NULL;
		return false;
	}
	element = *(S.top - 1);
	return true;
}
void clear(char* p, int num = 25)
{
	int i = 0;
	while (i < num)
	{
		*(p + i) = NULL;
		i++;
	}
}
char Calculate(char number1, char signal, char number2)
{
	char result;
	int bridge=0;
	int num1, num2;
	if (number1 == 'V')
		num1 = 1;
	else
		num1 = 0;

	if (number2 == 'V')
		num2 = 1;
	else
		num2 = 0;

	if (signal == '&')
	{
		bridge = num1+num2-1;
		if (bridge == -1)
			bridge = 0;
	}
	else
	{
		bridge = num1+num2;
		if (bridge == 2)
			bridge = 1;
	}
	
	if (bridge == 1)
		result = 'V';
	else
		result = 'F';
	return result;

}
void Add(char* p)
{
	
	while (*p != '\0')
	{
		p++;
	}
	*p = '#';

}
int change(char A)
{
	int left;
	if (A == '#')
		left = 0;
	else if (A == '(')
		left = 1;
	else if (A == '|')
		left = 2;
	else if (A == '&')
		left = 3;
	else if (A == '!')
		left = 4;
	else if (A == ')')
		left = 1;
	else
		left = -1;
	return left;
}
int Compare(char A, char B)
{
	if (A == '(' && B == ')' || A == '#' && B == '#'||A=='!'&&B=='!')
		return 0;
	if (B == '(')
		return -1;
	int left=0;
	int right=0;
	left = change(A);
	right = change(B);
	if (left >= right)
		return 1;
	else
		return -1;
}
//左边大返回1
//栈null为空
int main()
{
	char ch[110];
	
	
	int k = 1;
	while (cin.getline(ch,100))
	{
		
		int i = 0;//标记入栈了多少个元素
		Stack SNumber, SWord;
		CreateStack(SNumber);
		CreateStack(SWord);
		Add(ch);
		Push(SWord, '#');
		bool if_stop = false;


		while (SWord.top!=SWord.base)
		{
		
			switch (ch[i])
			{
			case'V':Push(SNumber, 'V');
				i++;
				break;
			case'F':Push(SNumber, 'F');
				i++;
				break;
			case' ':i++;
				break;
			default:
				char element;
				
				switch (Compare(*(SWord.top-1),ch[i]))
				{
				case 0:
					Pop(SWord, element);
					i++;
					break;
				case 1://源栈顶的大
					char signal;
					Pop(SWord, signal);
					char result;
					if (signal == '!')
					{
						char p1;
						Pop(SNumber, p1);
						if (p1 == 'V')
							result = 'F';
						else
							result = 'V';
						Push(SNumber, result);
					}
					else
					{
						char p1;
						Pop(SNumber, p1);
						char p2; 
						Pop(SNumber, p2);
						result = Calculate(p1, signal, p2);
						Push(SNumber, result);
					}
					break;
				case -1:
					Push(SWord, ch[i]);
					i++;
					break;
				default:
					break;
				}
				break;


			}

		}
		cout <<"Expression "<< k <<": "<< * (SNumber.top - 1) << endl;
		k++;
	}

	return 0;
}