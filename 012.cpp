#include<iostream>
#include<string>

using namespace std;
const int THEMAXSIZE = 101000;
typedef struct {
	char data;
	int num;
}signal,*sign;




struct Stack {
    sign base;
	sign top;
	//用int表示是否有车，1有0没有；
};

bool EmptyStack(Stack& S)
{
	sign p = S.base;
	while (p < S.top)
	{
		p->data = NULL;
		p->num = -1;
		p++;
	}
	S.top = S.base;
	return true;
}
Stack CreateStack(Stack& S)
{
	S.base = (sign)malloc(sizeof(signal) * THEMAXSIZE);
	S.top = S.base;
	int i = 0;
	while (i < THEMAXSIZE)
	{
		S.base->data = NULL;
		S.base->num = -1;
		i++;
	}


	return S;
}
bool Push(Stack& S, char element,int number)
{
	if (S.top - S.base >= THEMAXSIZE)
		return false;
	S.top->data = element;
	S.top->num = number;
	S.top++;
	return true;
}
bool Pop(Stack& S, char& element)
{
	if (S.top == S.base)
	{
		element = NULL;
		return false;
	}
	element = (S.top - 1)->data;
	(S.top - 1)->data = NULL;
	(S.top - 1)->num = -1;
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
	element = (S.top - 1)->data;
	return true;
}


int main()
{
	int num = 0;

	int begin = -2;
	int end = -2;

	int max_begin = -2;
	int max_end = -2;

	int last_end = -2;
	int last_begin = -2;
	Stack S;
	CreateStack(S);
	int Map[100000];
	int a = 0;
	while (a < 100000)
	{
		Map[a] = -2;
		a++;
	}
	char ch;
	ch = getchar();
	if (ch == '\n'|| ch == EOF)
	{
		cout << "0 0" << endl;
		return 0;
	}


	while (ch != '\n')
	{
		switch (ch)
		{
		case'(':
			Push(S, '(', num);
			break;
		case')':
			char element;
			char trash;
			Seek(S, element);
			if (element == NULL)
				;
			else
			{
			
				end = num;
				begin = (S.top - 1)->num;
				Map[end] = begin;
				


				if (Map[begin-1]!=-2&&begin>0)
				{
					begin= Map[begin - 1];
					Map[end] = begin;
					

				}
			    if ((end - begin) > (max_end - max_begin))
				{
					max_end = end;
					max_begin = begin;
				

				}
			


				
				Pop(S, trash);
			}
			break;
		default:
			break;
		}
		ch = getchar();
		num++;
	}
	if (max_end == -2 && max_begin == -2)
		cout << "0 0" << endl;
	else
		cout << max_end - max_begin + 1 << " " << max_begin << endl;

	return 0;
}