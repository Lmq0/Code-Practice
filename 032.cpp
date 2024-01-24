/**
 * @file    template.cpp
 * @name    p138模板程序
 * @date    2022-11-20
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
/*     以下是你需要提交的代码     */
/********************************/
class Solution {
public:
    int solve(std::vector<vector<std::string>>& old_chart, std::vector<std::vector<std::string>>& new_chart)
    {
        int n = old_chart.size();//列数
        int m = (*old_chart.begin()).size();//行数
        int i = 0;
        int j = 0;
        int k = 0;
        int sum = 0;
        string* List = new string[500001];//散列表
        int* ListPos = new int[500001];
        while (i < n)
        {
            while (j < m)
            {
                string element = new_chart[i][j];
                while (k < element.length())
                {
                    sum += element[k];
                    sum *= 37;
                    sum %= 400001;
                    k++;
                }
                if (List[sum] == "")
                {
                    ListPos[sum] = i * m + j;
                    List[sum] = element;
                }
                else
                {
                    sum++;
                    while (sum < 5000001)
                    {
                        if (List[sum] == "")
                        {
                            ListPos[sum] = i * m + j;
                            List[sum] = element;
                        }
                        sum++;
                    }
                }
                j++;
                sum = 0;
                k = 0;
            }
            j = 0;
            i++;
        }
        //完成哈希表创建
        i = 0; k = 0; j = 0;
        int times=0;
        sum = 0;
        while (i < n)
        {
            while (j < m)
            {
                string element = old_chart[i][j];
                while(element != new_chart[i][j])
                {
                    k = 0;
                    while (k < element.length())
                    {
                        sum += element[k];
                        sum *= 37;
                        sum %= 400001;
                        k++;
                    }
                    //求出特征值
                    while (List[sum] != element)
                    {
                        sum++;
                    }
                    int position = ListPos[sum];
                    int m_ = position % m;
                    int n_ = position / m;
                    swap(old_chart[i][j], old_chart[n_][m_]);
                    element = old_chart[i][j];
                    sum = 0;
                    times++;
                }
                j++;
            }
            j = 0;
            i++;
        }
        return times;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::string>> old_chart(n, std::vector<std::string>(m));
    std::vector<std::vector<std::string>> new_chart(n, std::vector<std::string>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> old_chart[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> new_chart[i][j];
        }
    }

    Solution s;
    std::cout << s.solve(old_chart, new_chart) << std::endl;
    return true;
}
