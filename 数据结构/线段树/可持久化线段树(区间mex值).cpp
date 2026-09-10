#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 2e5;

// lateLeft表示
// 所管辖的区间内, 所有出现的元素的最晚出现位置的最左位置
// 核心判断: 某个节点左儿子的lateLeft >= L, 意味着要查询范围的mex值在右侧
// 线段树的节点, 维护的是所管辖的值域区间, 值出现的位置的情况 

int n, m;
int a[MAXN + 5];
int version[MAXN + 5];

int cnt = 0;
struct tree {
    int left;
    int right;
    int lateLeft;
}node[(MAXN << 2 | 1) + MAXN * 60];

int clone(int i) {
    cnt++;
    node[cnt] = node[i];
    return cnt;
}

void up(int i) {
    node[i].lateLeft = min(node[node[i].left].lateLeft, node[node[i].right].lateLeft);
}

int build(int l, int r) {
    int rt = ++cnt;
    node[rt].left = node[rt].right = node[rt].lateLeft = 0;
    if (l != r) {
        int mid = (l + r) >> 1;
        node[rt].left = build(l, mid);
        node[rt].right = build(mid + 1, r);
        up(rt);
    }
    return rt;
}

int update(int jobi, int jobv, int l, int r, int i) {
    int rt = clone(i);
    if (l == r) {
        node[rt].lateLeft = jobv;
    }
    else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            node[rt].left = update(jobi, jobv, l, mid, node[rt].left);
        }
        else {
            node[rt].right = update(jobi, jobv, mid + 1, r, node[rt].right);
        }
        up(rt);
    }
    return rt;
}

int query(int L, int l, int r, int i) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    if (node[node[i].left].lateLeft >= L) {
        return query(L, mid + 1, r, node[i].right);
    }
    else {
        return query(L, l, mid, node[i].left);
    }
}

void prepare() {
    cnt = 0;
    version[0] = build(1, n);
    for (int v, i = 1;i <= n;i++) {
        // [0, n - 1] a[i] > n
        // 映射[1, n] a[i] + 1 > n + 1
        v = a[i] + 1;
        if (v > n + 1) {
            version[i] = version[i - 1];
        }
        else {
            version[i] = update(v, i, 1, n + 1, version[i - 1]);
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
    }
    prepare();
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, 1, n + 1, version[r]) - 1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
