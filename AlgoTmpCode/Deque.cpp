#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int a[500000];

void randomArray(int n, int* arr) {
    random_device rd;
    uniform_int_distribution<int>dist(-100, 100);
    for (int i = 1;i <= n;i++) {
        arr[i] = dist(rd);
    }
}

void solve() {
    int n = 1000;
    randomArray(n, a);
    deque<int>q;//单调队列维护区间最大值
    int len = 2;
    for (int l = 1, r = 1;r <= n;r++) {
        if (r - l + 1 > len) {
            l++;
        }
        //维护左侧合法下标
        while (q.size() && q.front() < l) {
            q.pop_front();
        }
        //维护右侧最大候选值
        while (q.size() && a[q.back()] < a[r]) {
            q.pop_back();
        }
        q.push_back(r);
        //输出区间最大值
        //加上如下限定,区间长度严格=len,否则<=len
        if (r - l + 1 == len) {
            cout << l << "---" << r << ' ' << a[q.front()] << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}