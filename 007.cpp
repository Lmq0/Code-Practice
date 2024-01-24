#include<iostream> 
using namespace std;
struct LNode
{
	struct LNode* next;

	int dex;//指数
	int cof;//系数


};
typedef LNode *Linklist;


bool CreateNode(Linklist &head,int length)
{
	Linklist p=head;
	if (length == 0)
	{
		return true;
	}
	int NumForCount = 0;
	while (NumForCount < length)
	{
		Linklist q = (Linklist)malloc(sizeof(LNode));
		if (!q)exit(0);
		q->next = NULL;
		if (q==NULL)return false;
	    p->next=q;

		p = p->next;
		cin >> p->cof >> p->dex;

		NumForCount++;

	}

	return true;

}
bool DestoryNode(Linklist& head)
{
	Linklist p = head;
	while (head != NULL)
	{
		Linklist q = head->next;
		free(head);
		head = q;
	}
	return true;
}
Linklist MergNodePlus(Linklist& list1, Linklist& list2, int extradex = 0, int extracof =1)//list 2 会带倍率
{
	Linklist targetlist=(Linklist)malloc(sizeof(LNode));
	Linklist p1, p2,p_target;
	p1 = list1->next;
	p2 = list2->next;
	p_target = targetlist;//指向最后一个节点
	while (p1 != NULL && p2 != NULL)
	{
		Linklist q = (Linklist)malloc(sizeof(LNode));
		if (!q)exit(0);
		q->next = NULL;
		if (q == NULL)
		{
			exit(0);
		}
		if (p1->dex < p2->dex+extradex)
		{
			if (!p_target)exit(0);
			p_target->next = q;
			q->cof = p1->cof;
			q->dex = p1->dex;
			p_target = p_target->next;
			p1 = p1->next;

		}
		else if (p1->dex > p2->dex+ extradex)
		{
			if (!p_target)exit(0);
			p_target->next = q;
			q->cof = p2->cof* extracof;
			q->dex = p2->dex + extradex;
			
			p_target = p_target->next;
			p2 = p2->next;
		}
		else
		{
			if (p1->cof + p2->cof* extracof != 0)
			{
				if (!p_target)exit(0);
				p_target->next = q;
				q->cof = p2->cof * extracof + p1->cof;
				q->dex = p1->dex;

				p_target = p_target->next;
			}
				p2 = p2->next;
				p1 = p1->next;

			
			
		}
	}
	Linklist tail = p1 ? p1 : p2;

	if (tail == p1)
	{
		extradex = 0;
		extracof = 1;
	}
	while (tail)
	{
		Linklist q = (Linklist)malloc(sizeof(LNode));
		if (!q)exit(0);
		q->next = NULL;
		if (q == NULL)exit(0);
		q->cof = tail->cof*extracof;
		q->dex = tail->dex+extradex;
		if (!p_target)exit(0);
		p_target->next = q;
		p_target = p_target->next;
		tail = tail->next;
	}


	return targetlist;

}
Linklist MergNodeMultply(Linklist& list1, Linklist& list2)
{
	Linklist bridgelist = (Linklist)malloc(sizeof(LNode));
	if (!bridgelist)exit(0);
	bridgelist->next = NULL;
	Linklist p1=list1->next;
	
	while (p1 != NULL)
	{
		Linklist A = MergNodePlus(bridgelist, list2, p1->dex, p1->cof);
		DestoryNode(bridgelist);
		bridgelist = A;
		p1 = p1->next;


	}

	return bridgelist;

}



int main()
{
	int num1 = 0;
	cin >> num1;//项数1
	Linklist head1 = (Linklist)malloc(sizeof(LNode));
	if (!head1)exit(0);
	CreateNode(head1, num1);
	

	int num2 = 0;
	cin >> num2;//项数2
	Linklist head2 = (Linklist)malloc(sizeof(LNode));
	if (!head2)exit(0);
	CreateNode(head2, num2);


	int type;
	cin >> type;
	if (type == 0)
	{
		Linklist Plus = MergNodePlus(head1, head2);
		Plus = Plus->next;
		while (Plus)
		{
			cout << Plus->cof << " " << Plus->dex << " ";
			Plus = Plus->next;
		}
		cout << endl;

	}
	else if (type == 1)
	{
		Linklist Multy = MergNodeMultply(head1, head2);
		Multy = Multy->next;
		while (Multy)
		{
			cout << Multy->cof << " " << Multy->dex << " ";
			Multy = Multy->next;
		}
		cout << endl;
	
	}
	else if (type == 2)
	{
		Linklist Plus = MergNodePlus(head1, head2);
		Plus = Plus->next;
		while (Plus)
		{
			cout << Plus->cof << " " << Plus->dex << " ";
			Plus = Plus->next;
		}
		cout << endl;
		Linklist Multy = MergNodeMultply(head1, head2);
		Multy = Multy->next;
		while (Multy)
		{
			cout << Multy->cof << " " << Multy->dex << " ";
			Multy = Multy->next;
		}
		cout << endl;
	
	}


	return 0;
}

