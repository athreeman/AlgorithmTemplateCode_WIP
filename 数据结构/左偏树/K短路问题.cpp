#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int MAXN = 5e3;
const int MAXM = 2e5;
const int MAXT = 2e6;

int headGo[MAXM + 1];
int nxtGo[MAXM + 1];
int toGo[MAXM + 1];
int idxGo = 0;

int headBack[MAXM + 1];
int nxtBack[MAXM + 1];
int toBack[MAXM + 1];
int idxBack = 0;

int path[MAXN + 1];

ld weight[MAXM + 1];

bool vis[MAXN + 1];
ld dist[MAXN + 1];

struct {
    int left;
    int right;
    int dist;
    ld addVal;
    int to;
}node[MAXT + 1];

int cnt = 0;
int top[MAXM + 1];

int create(ld addVal, int to) {
    cnt++;
    node[cnt].addVal = addVal;
    node[cnt].to = to;
    node[cnt].left = node[cnt].right = node[cnt].dist = 0;
    return cnt;
}

int clone(int i) {
    cnt++;
    node[cnt] = node[i];
    return cnt;
}

void addEdgeGo(int u, int v, ld w) {
    nxtGo[++idxGo] = headGo[u];
    headGo[u] = idxGo;
    toGo[idxGo] = v;
    weight[idxGo] = w;
}

void addEdgeBack(int u, int v, ld w) {
    nxtBack[++idxBack] = headBack[u];
    headBack[u] = idxBack;
    toBack[idxBack] = v;
    weight[idxBack] = w;
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    if (node[i].addVal > node[j].addVal) {
        swap(i, j);
    }
    int p = clone(i);
    node[p].right = merge(node[p].right, j);
    if (node[node[p].left].dist < node[node[p].right].dist) {
        swap(node[p].left, node[p].right);
    }
    node[p].dist = node[node[p].right].dist + 1;
    return p;
}

int pop(int i) {
    if (node[i].left == 0 && node[i].right == 0) {
        return 0;
    }
    if (node[i].left == 0 || node[i].right == 0) {
        return clone(node[i].left + node[i].right);
    }
    return merge(node[i].left, node[i].right);
}

// 反图上跑最短路算法
void Djk(int n) {
    priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<pair<ld, int>>>q;
    fill(vis, vis + n + 1, false);
    fill(dist, dist + n + 1, 1e18);
    dist[n] = 0;
    q.push({ 0,n });
    while (q.size()) {
        auto [w, u] = q.top();
        q.pop();
        if (!vis[u]) {
            vis[u] = true;
            for (int edge = headBack[u];edge > 0;edge = nxtBack[edge]) {
                int v = toBack[edge];
                if (dist[v] > dist[u] + weight[edge]) {
                    dist[v] = dist[u] + weight[edge];
                    path[v] = edge;
                    q.push({ dist[v],v });
                }
            }
        }
    }
}


void mergeRoad(int n) {
    priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<pair<ld, int>>>q;
    for (int i = 1;i <= n;i++) {
        q.push({ dist[i],i });
    }
    while (q.size()) {
        auto [w, u] = q.top();
        q.pop();
        for (int edge = headGo[u];edge > 0;edge = nxtGo[edge]) {
            int v = toGo[edge];
            if (edge != path[u]) {
                // 非树边
                if (top[u] == 0) {
                    top[u] = create(dist[v] + weight[edge] - dist[u], v);
                }
                else {
                    top[u] = merge(top[u], create(dist[v] + weight[edge] - dist[u], v));
                }
            }
        }
        if (path[u] != 0) {
            // 存在父亲
            int v = toGo[path[u]];
            top[u] = merge(top[u], top[v]);
        }
    }
}

struct heapNode {
    ld addVal;
    int to;
    int heapRoot;
};

int compute(int n, ld money) {
    auto cmp = [](heapNode a, heapNode b) { return a.addVal > b.addVal; };
    priority_queue<heapNode, vector<heapNode>, decltype(cmp)>q(cmp);

    int ans = 0;
    if (money >= dist[1]) {
        ans++;
        money -= dist[1];
    }
    else {
        return ans;
    }

    q.push({ node[top[1]].addVal,node[top[1]].to,top[1] });
    while (q.size()) {
        auto [addVal, to, heapRoot] = q.top();
        q.pop();

        if (dist[1] + addVal <= money) {
            money -= (dist[1] + addVal);
            ans++;
        }
        else {
            return ans;
        }

        // 替换影响, 方式: 直接选择左右孩子, 不要弹出堆顶, 否则MLE
        // 左偏树满足: 每个节点的孩子的key值都小于父亲
        int ls = node[heapRoot].left;
        int rs = node[heapRoot].right;
        if (ls != 0) {
            ld newAddVal = addVal - node[heapRoot].addVal + node[ls].addVal;
            q.push({ newAddVal,node[ls].to,ls });
        }

        if (rs != 0) {
            ld newAddVal = addVal - node[heapRoot].addVal + node[rs].addVal;
            q.push({ newAddVal,node[rs].to,rs });
        }

        // 弹出堆顶, 拷贝, 会导致!!!MLE!!!
        // int newHead = pop(heapRoot);
        // if (newHead != 0) {
        //     ld newAddVal = addVal - node[heapRoot].addVal + node[newHead].addVal;
        //     q.push({ newAddVal,node[newHead].to,newHead });
        // }

        // 新增影响

        int newHead = top[to];
        if (newHead != 0) {
            ld newAddVal = addVal + node[newHead].addVal;
            q.push({ newAddVal,node[newHead].to,newHead });
        }

    }
    return ans;
}

void solve() {

    // https://www.luogu.com.cn/problem/P2483

    // 核心: djk算法生成的最短路树
    // 对于非树边, 一定是连接两个树上节点的边
    // 对于边(u, v), 若选择这条边额外耗费的代价是dist[v] + weight(u, v) - dist[u]
    // 使用可持久化左偏树, 逐点逐级递推

    int n, m;
    ld money;
    cnt = idxGo = idxBack = 0;
    cin >> n >> m >> money;
    node[0].dist = -1;
    fill(top, top + n + 1, 0);
    fill(path, path + n + 1, 0);
    fill(headGo, headGo + n + 1, 0);
    fill(headBack, headBack + n + 1, 0);
    for (int i = 1;i <= m;i++) {
        int u, v;
        ld w;
        cin >> u >> v >> w;
        // 抵达终点即截止, 因此不应有任何边的连接
        // 避免额外计算
        if (u != n) {
            addEdgeGo(u, v, w);
            addEdgeBack(v, u, w);
        }
    }
    Djk(n);
    mergeRoad(n);
    cout << compute(n, money) << '\n';
}
