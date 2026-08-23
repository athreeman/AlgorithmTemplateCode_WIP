#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e6;

// 换根dp：解决快速查询以某个节点作为根的某个信息
// 需要维护每个节点的多种信息
// 一般需要两次dfs
// 第一次获取所有节点信息，并获取root节点的答案
// 第二次通过严格位置依赖的转移方程，获得所有节点的答案

ll dp[MAXN + 1];// 以i为根，所有节点抵达i的距离之和
int siz[MAXN + 1];// 子树i的大小
ll sum[MAXN + 1];// i的所有儿子走向i的距离之和
int head[MAXN + 1];
int to[2 * MAXN + 1];
int nxt[2 * MAXN + 1];
int idx = 0;
void addEdge(int u, int v) {
    nxt[++idx] = head[u];
    head[u] = idx;
    to[idx] = v;
}
void dfsDp(int u, int fa, int n) {
    for (int v, edge = head[u];edge > 0;edge = nxt[edge]) {
        v = to[edge];
        if (v != fa) {
            // ！！！核心代码如下：！！！
            // 节点1的儿子2
            // 2的所有子树节点走向1，再退一步(-siz[v])就抵达2
            // 与2反向的1的所有子树节点走向1，再进一步(n-siz[v])就抵达2
            dp[v] = dp[u] - siz[v] + (n - siz[v]);
            dfsDp(v, u, n);
        }
    }
}
void dfs(int u, int fa) {
    siz[u] = 1;
    sum[u] = 0;
    for (int v, edge = head[u];edge > 0;edge = nxt[edge]) {
        v = to[edge];
        if (v != fa) {
            dfs(v, u);
            siz[u] += siz[v];
            sum[u] = sum[v] + siz[v];
        }
    }
}
void solve() {
    // https://www.luogu.com.cn/problem/P3478
    int n;
    cin >> n;
    for (int i = 1;i < n;i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    dp[1] = sum[1];
    dfsDp(1, 0, n);
    int best = 0;
    ll dist = -1e18;
    for (int i = 1;i <= n;i++) {
        if (dp[i] > dist) {
            dist = dp[i];
            best = i;
        }
    }
    cout << best << '\n';
}
