#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>



using namespace std;
typedef struct {
	char data[101];
	char name[101];
}Student,*persons;



int insert(persons& classroom, char* newdata, char* newname, int position,int &length)
{
	if (position <= 0 || position > length + 1)
		return -1;
	classroom=(persons)realloc(classroom, sizeof(Student) * (length + 1));
	if (classroom == NULL)
	{
		return -1;
	}
	length++;
	int a = length;
	while (a-2 >= position-1)
	{
		
		strcpy(classroom[a - 1].data, classroom[a - 2].data);
		strcpy(classroom[a - 1].name, classroom[a - 2].name);
		a--;
	}
	//ÒÆ¶¯
	
	strcpy(classroom[position - 1].name, newname);
	strcpy(classroom[position - 1].data, newdata);
	
	return 0;
}
void check_name(persons classroom, char* check_name, int length)
{
	int a = 0;
	while (a < length)
	{
		if (strcmp(check_name, classroom[a].name) == 0)
		{
			cout <<a+1 <<" " << classroom[a].data << " " << classroom[a].name << endl;
			break;
		}
		a++;
	}
	if (a == length)cout << -1 << endl;
}
void check_no(persons classroom, char* check_no, int length)
{
	int a = 0;
	while (a < length)
	{
		if (strcmp(check_no, classroom[a].data)==0)
		{
			cout<<a+1<<" " << classroom[a].data << " " << classroom[a].name << endl;
			break;
		}
		a++;
	}
	if (a == length)cout << -1 << endl;
}
int remove(persons& classroom, int position, int& length)
{
	if (position <= 0 || position > length)
	{
		return -1;
	}
	int a = position - 1;
	while (a < length - 1)
	{
		strcpy(classroom[a].data, classroom[a + 1].data);
		strcpy(classroom[a].name, classroom[a + 1].name);
		a++;
	}

	classroom = (persons)realloc(classroom, sizeof(Student) * (length - 1));
	length--;
	return 0;


}


int main()
{
	int number = 0;
	cin >> number;
	if (number == 0)
	{
		return 0;
	}
	int a = 0;
	persons classroom = (persons)malloc(sizeof(Student) * number);
	if (classroom == NULL)
	{
		exit(0);
	}
	while (a < number)
	{
		if (classroom + a == NULL)
			exit(0);
		cin >> classroom[a].data;
	    cin >> classroom[a].name;
		if (cin.good() == 0)
		{
			cin.clear();
			continue;
		}
		a++;
	}
	a = 0;
	
	while (1)
	{
		char action[15];
		cin >> action;

		if (strcmp(action, "end") == 0)
		{
			cout << number << endl;
			break;
		}
		else if (strcmp(action, "insert") == 0)
		{
			int position;
			char newdata[101];
			char newname[101];
			cin >> position >> newdata;
			if (cin.good() == 0)
			{
				cin.clear();
				continue;
			}
			cin >> newname;
			int result = insert(classroom, newdata, newname, position, number);
			cout << result << endl;
		}
		else if (strcmp(action, "check") == 0)
		{
			char actiontwo[15];
			cin >> actiontwo;
			if (strcmp(actiontwo, "name") == 0)
			{
				char for_check[15];
				cin >> for_check;
				check_name(classroom,for_check,number);
			}
			else if (strcmp(actiontwo, "no") == 0)
			{
				char for_check[101];
				cin >> for_check;
				if (cin.good() == 0)
				{
					cin.clear();
					continue;
				}
				check_no(classroom, for_check, number);
			}
			else
			{
				continue;
			}
		}
		else if (strcmp(action, "remove") == 0)
		{
			int remove_element;
			cin >> remove_element;
			if (cin.good() == 0)
			{
				cin.clear();
				continue;
			}
			int result=remove(classroom, remove_element, number);
			cout << result<<endl;
		}
		else
			continue;

	}

	return 0;
}