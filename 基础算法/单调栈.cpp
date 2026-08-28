#include<bits/stdc++.h>
using namespace std;

// 单调栈求解右侧第一个小的位置
// 单调栈的应用很广泛：
// 贪心, dp优化, 很多场景都可以应用
stack<int>sta;
const int MAXN = 2e5;
int right[MAXN + 1];
int a[MAXN + 1];
void solve(int n) {
    // 栈必须维护栈顶是最大值
    for (int i = 1;i <= n;i++) {
        while (sta.size() && a[i] < a[sta.top()]) {
            ::right[sta.top()] = i;
            sta.pop();
        }
        sta.push(i);
    }
    // 标记不存在
    while (sta.size()) {
        ::right[sta.top()] = -1;
        sta.pop();
    }
}
