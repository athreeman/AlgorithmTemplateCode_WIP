#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e3;
const int MAXM = 3e3;
const int INF = 1e9;

int idx = 0;
int head[MAXN + 1];
int nxt[2 * MAXM + 1];
int to[2 * MAXM + 1];
int weight[2 * MAXM + 1];

void addEdge(int u, int v, int w) {
    nxt[++idx] = head[u];
    head[u] = idx;
    to[idx] = v;
    weight[idx] = w;
}

int roundCnt[MAXN + 1];
int dist[MAXN + 1];
bool vis[MAXN + 1];

int SPFA(int start, int n) {
    queue<int>q;
    q.push(start);
    vis[start] = true;
    roundCnt[start] = 1;
    dist[start] = 0;
    while (q.size()) {
        int cur = q.front();
        vis[cur] = false;
        q.pop();
        for (int edge = head[cur];edge > 0;edge = nxt[edge]) {
            int son = to[edge];
            int w = weight[edge];
            if (dist[cur] + w < dist[son]) {
                dist[son] = dist[cur] + w;
                if (!vis[son]) {
                    //只有当不在队列里时,视为一轮松弛操作
                    if (++roundCnt[son] >= n) {
                        //判断负环
                        return -1;
                    }
                    vis[son] = true;
                    q.push(son);
                }
            }
        }
    }
    return 1;//成功得到结果
}

void solve() {
    int n, m;
    cin >> n >> m;
    idx=0;
    fill(head, head + n + 1, 0);
    fill(vis, vis + n + 1, false);
    fill(dist, dist + n + 1, INF);
    fill(roundCnt, roundCnt + n + 1, 0);
    for (int i = 1;i <= m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w >= 0) {
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        else {
            addEdge(u, v, w);
        }
    }
    if (SPFA(1, n) != -1)cout << "NO" << '\n';
    else cout << "YES" << '\n';

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
