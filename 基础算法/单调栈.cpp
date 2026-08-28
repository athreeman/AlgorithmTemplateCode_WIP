#include<bits/stdc++.h>
using namespace std;


// 单调栈的应用很广泛：
// 贪心, dp优化, 很多场景都可以应用


// 模板：
// 单调栈求解左侧和右侧第一个严格小于的位置
stack<int>sta;
const int MAXN = 2e5;
int right[MAXN + 1];
int left[MAXN + 1];
int a[MAXN + 1];
void solve(int n) {
    // -1标记不存在
    // 栈必须维护栈顶是最大值
    for (int i = 1;i <= n;i++) {
        // 右侧在弹出时进行维护
        while (sta.size() && a[i] < a[sta.top()]) {
            int t = sta.top();
            ::right[t] = i;
            sta.pop();
        }

        // 左侧在压入时进行维护
        // 若存在相同元素, 和左侧第一个相同位置对齐
        if (sta.size()) {
            if (a[i] == a[sta.top()]) {
                ::left[i] = ::left[sta.top()];
            }
            else {
                ::left[i] = sta.top();
            }
        }
        else {
            ::left[i] = -1;
        }
        sta.push(i);
    }
    while (sta.size()) {
        int t = sta.top();
        ::right[t] = -1;
        sta.pop();
    }
}
