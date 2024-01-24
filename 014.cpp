#include <iostream>
#include <string.h>
#define MINAL   -2147483648
using namespace std;


class Stack
{
public:
    //构造函数，初始化堆栈：
    //|stackTop|指向当前堆栈的顶部元素，
    //|maxStackItemIndex|存储当前堆栈中最大元素的index
    Stack() 
    {
        stackTop = -1;
        maxStackItemIndex = -1;
        SIZE = 11000;
        stackItem = (int*)malloc(sizeof(int) * 110000);
        link2NextMaxItem = (int*)malloc(sizeof(int) * 11000);//默认大小为11000
    }
    //判断当前堆栈是否为空
    bool isEmpty() {
        return stackTop == -1;
    }
    //判断当前堆栈是否满
    bool isFull() {
        return stackTop == SIZE - 1;
    }
    //向堆栈中push元素，
    void push(int x) {
        if (this->isFull()) {                //首先检测堆栈空间是否满
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
        int ret=0;//如果空那么输出
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
    //取出堆栈中当前的最大值
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
    //返回队列中最大值
    int max() {
        return maxValue(stackA.maxValue(), stackB.maxValue());
    }
    void printQueue() {
        stackA.reversePrintItems();
        stackB.printItems();
        cout << endl;
    }
    //在队列末尾插入元素
    void insertQueue(int x) {
        if (Size == NowSize)
        {
            cout << "Queue is Full" << endl;
            return;
        }
        stackB.push(x);
        NowSize++;
       
    }
    //删除并返回队首元素,
    //如果stackA中是空，则先将stackB中的所有元素pop到stackA中，
    //这样stackB中先插入的元素就会pop到stackA中的顶部
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
    Stack stackA;    //出队列操作
    Stack stackB;    //入队列操作
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