/**
 * @file    template.cpp
 * @name    p138ģ�����
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
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
class Solution {
public:
    int solve(std::vector<vector<std::string>>& old_chart, std::vector<std::vector<std::string>>& new_chart)
    {
        int n = old_chart.size();//����
        int m = (*old_chart.begin()).size();//����
        int i = 0;
        int j = 0;
        int k = 0;
        int sum = 0;
        string* List = new string[500001];//ɢ�б�
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
        //��ɹ�ϣ����
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
                    //�������ֵ
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
/*     ����������Ҫ�ύ�Ĵ���     */
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
