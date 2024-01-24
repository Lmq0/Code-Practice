#include<iostream>
using namespace std;
const int THEMAXSIZE = 1000;


struct Stack {
	char* base;
	char* top;
	//��int��ʾ�Ƿ��г���1��0û�У�
};
bool EmptyStack(Stack& S)
{
	char * p = S.base;
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
bool Push(Stack& S,char element)
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
void clear(char* p, int num=25)
{
	int i = 0;
	while (i < num)
	{
		*(p+i) = NULL;
		i++;
	}
}


int main()
{
	char InputOrder[25];
	cin >> InputOrder;
	char OutputOrder[25];
	while (cin >> OutputOrder)
	{
		Stack station;
		CreateStack(station);
		int i = 0;//�������ִ�е����ٲ���
		int a = 0;//��¼��վ֮ǰ�ĵ�һ��Ԫ��
		while (OutputOrder[i] != '\0')
		{
			if (OutputOrder[i] == InputOrder[a])
			{
				i++;
				a++;//��һ����δ��վԪ�ؾ�����һ��Ҫ�����Ԫ�أ�
			}
			else
			{
				char element = NULL;
				Seek(station, element);
				if (element != NULL && element == OutputOrder[i])
				{
					Pop(station, element);
					i++;
				}
				else
				{
					Push(station, InputOrder[a]);
					a++;
					if (InputOrder[a] == '\0')
					{
						cout << "no" << endl;
						break;
					}
				}

			}
		}
		if (OutputOrder[i] == '\0')
			cout << "yes" << endl;
		clear(OutputOrder);

	}


	return 0;
}