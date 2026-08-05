#include<bits/stdc++.h>
using namespace std;

//最小生成树,Prim算法
//模板例题：https://www.luogu.com.cn/problem/P3366

class Tmp {
    //未优化,一般时间复杂度
    //点n,边m,O(n+m)+O(mlogm)
private:

    using ll = long long;

    static const int MAXN = 5e3;
    static const int MAXM = 2e5;

    int head[MAXN + 1];
    int nxt[2 * MAXM + 1];
    int to[2 * MAXM + 1];
    ll w[2 * MAXM + 1];
    int idx = 0;

    bool vis[MAXN + 1];

    void addEdge(int u, int v, ll z) {
        nxt[++idx] = head[u];
        head[u] = idx;
        to[idx] = v;
        w[idx] = z;
    }

    void init(int n) {
        fill(head, head + n + 1, 0);
        fill(vis, vis + n + 1, false);
    }

    ll Prim(int n) {
        int cnt = 1;
        ll ans = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>q;
        vis[1] = true;
        for (int edge = head[1];edge > 0;edge = nxt[edge]) {
            int son = to[edge];
            ll val = w[edge];
            q.push({ val,son });
        }
        while (q.size()) {
            auto [val, cur] = q.top();
            q.pop();
            if (!vis[cur]) {
                ans += val;
                cnt++;
                vis[cur] = true;
                for (int edge = head[cur];edge > 0;edge = nxt[edge]) {
                    int son = to[edge];
                    ll val = w[edge];
                    q.push({ val,son });
                }
            }
        }
        if (cnt < n)ans = -1;
        return ans;
    }

public:
    void solve() {
        int n, m;
        cin >> n >> m;
        init(n);
        for (int i = 1;i <= m;i++) {
            int u, v, z;
            cin >> u >> v >> z;
            addEdge(u, v, z);
            addEdge(v, u, z);
        }
        ll ans = Prim(n);
        if (ans == -1) {
            cout << "orz" << '\n';
        }
        else {
            cout << ans << '\n';
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    return 0;
}
