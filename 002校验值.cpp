#include<iostream>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
using namespace std;

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

int Create(Node** joseph, int num)
{
	if (joseph == NULL || num < 1)
	{
		return ERROR;
	}
	//����ͷ���
	Node* head = (Node*)malloc(sizeof(Node));
	if (head == NULL) exit(0);
	head->next = NULL;


	Node* p = head;

	for (size_t i = 1; i <= num; i++)
	{

		Node* node = (Node*)malloc(sizeof(Node));
		if (node == NULL) exit(0);
		node->data = i - 1;
		node->next = head;


		//pָ������β��㣬p->next=node 
		//p = node
		p->next = node;
		p = node;
	}

	p->next = head->next;
	free(head);
	//Լɪ�򻷣�ѭ��������ͷָ��ָ�򻷵�һ�����
	*joseph = p->next;
	return OK;
}
int Length(Node* joseph)
{
	if (joseph == NULL)
	{
		return 0;
	}
	Node* target = joseph;//��ʼtargetָ���һ�����
	int length = 1;
	for (; target->next != joseph; target = target->next)
	{
		length++;
	}
	return length;
}
/*
ģ��Լɪ����ɱ����
ÿ������3���˽�����ɱ��Ȼ�����һ�������¿�ʼ����������3���˽�����ɱ...
�����4�˸�������ɱ
1 2 3 4
����˳��:->3->2->4->1
n Ϊ ������ n������ɱ��Լɪ�� ���� �� ÿ������3������ɱ��
������Խ������ã�Ҳ����ÿ���� ��4���˽�����ɱ��
*/
int ShowKill(Node* joseph, int n)
{
	if (joseph == NULL)
	{
		return ERROR;
	}
	int num = Length(joseph);
	//skipΪɱ��n����Ҫ��Խ������
	int skip = n - 1;
	Node* p = joseph;
	Node* begin = p;//beginָ��ʼ���ĵ�1����
	while (1)
	{
		begin = p;
		//�ҵ���ɱ�˵�ǰһ��λ��
		for (size_t i = 0; i < (skip - 1); i++)
		{
			p = p->next;
		}

		//���ʣ2����ʱ��������ɱ
		if (begin->next->next == begin)
		{
			if (p == begin)
			{
				cout << begin->data << endl;
				free(p->next);
				free(begin);
				begin = NULL;
				p = NULL;
				break;
			}
			else
			{
				cout << begin->next->data << endl;
				free(p);
				free(begin);
				begin = NULL;
				p = NULL;
				break;
			}
        }


		//ѭ���꣬p ָ����ɱǰ��һ����
		//p->next ������ɱ��ʵ���Ͼ��ǽ�p->next����ѭ�������иɵ�
		Node* kill = p->next;

		//��kill�Ƴ����
		p->next = kill->next;
		free(kill);
		kill = NULL;

		//p�ƶ�������3���˵ĵ�1���˵�λ�� 
		p = p->next;

	}

	return OK;
}

int main(int argc, char* argv[])
{
	Node* joseph = NULL;
	int num = 1;
	int word = 0;


	cin >> num >> word;
		if (num == 1)
		{
			cout << 1 << endl;
			return 0;
		}
		if (num == 0)
		{
			return -1;
		}
		if (word == 1)
		{
			cout << num - 1 << endl;
			return 0;
		}
		joseph = NULL;
		Create(&joseph, num);
		ShowKill(joseph, word);

	return 0;
}

