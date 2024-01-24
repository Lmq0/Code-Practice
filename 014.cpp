#include <iostream>
#include <string.h>
#define MINAL   -2147483648
using namespace std;


class Stack
{
public:
    //���캯������ʼ����ջ��
    //|stackTop|ָ��ǰ��ջ�Ķ���Ԫ�أ�
    //|maxStackItemIndex|�洢��ǰ��ջ�����Ԫ�ص�index
    Stack() 
    {
        stackTop = -1;
        maxStackItemIndex = -1;
        SIZE = 11000;
        stackItem = (int*)malloc(sizeof(int) * 110000);
        link2NextMaxItem = (int*)malloc(sizeof(int) * 11000);//Ĭ�ϴ�СΪ11000
    }
    //�жϵ�ǰ��ջ�Ƿ�Ϊ��
    bool isEmpty() {
        return stackTop == -1;
    }
    //�жϵ�ǰ��ջ�Ƿ���
    bool isFull() {
        return stackTop == SIZE - 1;
    }
    //���ջ��pushԪ�أ�
    void push(int x) {
        if (this->isFull()) {                //���ȼ���ջ�ռ��Ƿ���
            cout << "Full" << endl;
        }
        else {
            stackItem[++stackTop] = x;
            if (x > maxValue()) {
                link2NextMaxItem[stackTop] = maxStackItemIndex;
                maxStackItemIndex = stackTop;
            }
            else
                link2NextMaxItem[stackTop] = -1;
        }
    }
    int pop(bool &empty_or_not) {
        int ret=0;//�������ô���
        if (this->isEmpty()) {
            cout << "Empty" << endl;
            empty_or_not = true;
        }
        else {
            ret = stackItem[stackTop];
            if (stackTop == maxStackItemIndex)
            {
                maxStackItemIndex = link2NextMaxItem[stackTop];
            }
            --stackTop;
        }
    
        return ret;
    }
    //ȡ����ջ�е�ǰ�����ֵ
    int maxValue() {
        if (maxStackItemIndex >= 0)
            return stackItem[maxStackItemIndex];
        else {
            return MINAL;
        }
    }
    void printItems() {
        for (int i = 0; i <= stackTop; ++i) {
            cout << stackItem[i] << " ";
        }
    }
    void reversePrintItems() {
        for (int i = stackTop; i >= 0; --i) {
            cout << stackItem[i] << " ";
        }
    }
private:
    int* stackItem;
    int stackTop;
    int* link2NextMaxItem;
    int maxStackItemIndex;
    int SIZE;
};

class Queue
{
public:

    bool if_empty()
    {
        return stackA.isEmpty()&&stackB.isEmpty();
    }
    int maxValue(int x, int y) {
        if (x > y)
            return x;
        else
            return y;
    }
    void ChangeSize2(int newsize)
    {
        Size = newsize;
    }
    //���ض��������ֵ
    int max() {
        return maxValue(stackA.maxValue(), stackB.maxValue());
    }
    void printQueue() {
        stackA.reversePrintItems();
        stackB.printItems();
        cout << endl;
    }
    //�ڶ���ĩβ����Ԫ��
    void insertQueue(int x) {
        if (Size == NowSize)
        {
            cout << "Queue is Full" << endl;
            return;
        }
        stackB.push(x);
        NowSize++;
       
    }
    //ɾ�������ض���Ԫ��,
    //���stackA���ǿգ����Ƚ�stackB�е�����Ԫ��pop��stackA�У�
    //����stackB���Ȳ����Ԫ�ؾͻ�pop��stackA�еĶ���
    int deQueue(bool& empty_or_not) {
        int result = 0;
        if (!NowSize)
        {
            cout << "Queue is Empty" << endl;
            empty_or_not = true;
            return result;
        }
        else
        {
            if (stackA.isEmpty()) {
                while (!stackB.isEmpty())
                    stackA.push(stackB.pop(empty_or_not));
            }
            result = stackA.pop(empty_or_not);
            NowSize--;
        }
        return result;
    }
    ;
private:
    Stack stackA;    //�����в���
    Stack stackB;    //����в���
    int Size = 0;
    int NowSize = 0;
 
};

int main()
{
    int SIZE = 0;
    cin >> SIZE;
 
    Queue Q;
    Q.ChangeSize2(SIZE);
    while (true)
    {
        char order[25];
        cin >> order;
        if (!strcmp(order, "dequeue"))
        {
            bool empty_or_not = false;
            int result = Q.deQueue(empty_or_not);
            if (!empty_or_not)
                cout << result << endl;

        }
        else if (!strcmp(order, "enqueue"))
        {
            int newelement = 0;
            cin >> newelement;
            Q.insertQueue(newelement);
        }
        else if (!strcmp(order, "max"))
        {
        
            if (!Q.if_empty())
            {
                int result = Q.max();
                cout << result << endl;
            }
            else
                cout << "Queue is Empty" << endl;

        }
        else if (!strcmp(order, "quit"))
        {
            Q.printQueue();
            break;
        }
        else continue;
    }



    return 0;
}