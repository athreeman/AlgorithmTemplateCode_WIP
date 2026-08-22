#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int a[500000];

void prove() {
    int n = 1000;
    // randomArray(n, a);
    deque<int>q;//单调队列维护区间最大值
    int len = 2;
    for (int l = 1, r = 1;r <= n;r++) {
        if (r - l + 1 > len) {
            l++;
        }

        //维护右侧最大候选值
        //注意：某些题目可能因为维护信息的原因，必须先放入新端点r，否则会出错
        while (q.size() && a[q.back()] < a[r]) {
            q.pop_back();
        }
        q.push_back(r);//新节点入队

        //维护左侧合法下标
        while (q.size() && q.front() < l) {
            q.pop_front();
        }


        //输出区间最大值
        //加上如下限定,区间长度严格=len,否则<=len
        if (r - l + 1 == len) {
            cout << l << "---" << r << ' ' << a[q.front()] << '\n';
        }
    }
}
