/**
 * @name    template.cpp
 * @brief   p142ģ�����
 * @date    2022-12-02
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
class FreqStack {
public:
    map<int, stack<int>> ToEle;
    map<int, stack<int>>::iterator E;
    map<int, int>ToFre;
    map<int, int>::iterator F;

    FreqStack() 
    {
       
    }

    void push(int val) 
    {
        F = ToFre.find(val);
        if (F != ToFre.end())
        {
            //fָ��ǰval��Ӧ�Ľڵ�
            F->second++;

        }
        else ToFre[val] = 1;
        /****************/
        int times = ToFre[val];
        E = ToEle.find(times);
        if (E != ToEle.end())
        {
            E->second.push(val);
        }
        else
        {
            stack<int>* s=new stack<int>;
            s->push(val);
            ToEle[times] = *s;
        }
     
    }

    int pop() 
    {
        E = ToEle.begin();
        int maxTime = 0;
        while (E != ToEle.end())
        {
            if (E->first > maxTime)
            {
                maxTime = E->first;
            }
            E++;
        }
        int delEle = ToEle[maxTime].top();
        ToEle[maxTime].pop();
        if (ToEle[maxTime].empty())ToEle.erase(maxTime);
        /**************************************/
        ToFre[delEle]--;
        if (ToFre[delEle] == 0)ToFre.erase(delEle);


        return delEle;
    }
};
/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/

int main() {
    int n;
    std::cin >> n;
    FreqStack fs;
    while (n--) {
        std::string order;
        std::cin >> order;
        if (order == "push") {
            int val;
            std::cin >> val;
            fs.push(val);
        }
        else if (order == "pop") {
            std::cout << fs.pop() << std::endl;
        }
    }
    return 0;
}
