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
	//创建头结点
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


		//p指向链表尾结点，p->next=node 
		//p = node
		p->next = node;
		p = node;
	}

	p->next = head->next;
	free(head);
	//约瑟夫环，循环链表中头指针指向环第一个结点
	*joseph = p->next;
	return OK;
}
int Length(Node* joseph)
{
	if (joseph == NULL)
	{
		return 0;
	}
	Node* target = joseph;//开始target指向第一个结点
	int length = 1;
	for (; target->next != joseph; target = target->next)
	{
		length++;
	}
	return length;
}
/*
模拟约瑟夫自杀问题
每数到第3个人进行自杀，然后从下一个人重新开始数，数到第3个人进行自杀...
如果是4人个进行自杀
1 2 3 4
死亡顺序:->3->2->4->1
n 为 数到第 n个人自杀，约瑟夫 问题 是 每数到第3个人自杀。
这里可以进行设置，也可以每数到 第4个人进行自杀。
*/
int ShowKill(Node* joseph, int n)
{
	if (joseph == NULL)
	{
		return ERROR;
	}
	int num = Length(joseph);
	//skip为杀第n个人要跨越的人数
	int skip = n - 1;
	Node* p = joseph;
	Node* begin = p;//begin指向开始数的第1个人
	while (1)
	{
		begin = p;
		//找到自杀人的前一个位置
		for (size_t i = 0; i < (skip - 1); i++)
		{
			p = p->next;
		}

		//最后剩2个人时，依次自杀
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


		//循环完，p 指向自杀前面一个人
		//p->next 进行自杀，实质上就是将p->next结点从循环链表中干掉
		Node* kill = p->next;

		//将kill移除结点
		p->next = kill->next;
		free(kill);
		kill = NULL;

		//p移动到后面3个人的第1个人的位置 
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

