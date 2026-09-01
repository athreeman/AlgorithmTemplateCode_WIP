#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 记某次操作的环大小n, 被杀节点编号s, 循环k次
// 操作前节点编号记OddPos, 操作后NewPos
// 则存在:OddPos = (NewPos + k - 1) % n + 1
// 最后结束的操作, NewPos = 1

// https://www.luogu.com.cn/problem/P8671

void Cycle() {
    int n, k;
    cin >> n >> k;
    int ans = 1;
    // 最后一个的NewPos = 1
    // 枚举上次操作的环大小c
    for (int c = 2;c <= n;c++) {
        ans = (ans + k - 1) % c + 1;
    }
    cout << ans << '\n';
}
