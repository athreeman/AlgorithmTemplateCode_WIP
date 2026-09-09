#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e5;

int version[MAXN + 1];
ll a[MAXN + 1];

// https://acm.hdu.edu.cn/showproblem.php?pid=4348

struct tree {
    int left;
    int right;
    ll sum;
    ll addTag;
}node[(MAXN << 2 | 1) + MAXN * 20];
int cnt = 0;

int clone(int i) {
    node[++cnt] = node[i];
    return cnt;
}

int build(int l, int r) {
    int rt = ++cnt;
    node[rt].addTag = 0;
    node[rt].sum = 0;
    node[rt].left = node[rt].right = 0;
    if (l == r) {
        node[rt].sum = a[l];
    }
    else {
        int mid = (l + r) >> 1;
        node[rt].left = build(l, mid);
        node[rt].right = build(mid + 1, r);
        node[rt].sum = node[node[rt].left].sum + node[node[rt].right].sum;
    }
    return rt;
}

int add(int jobl, int jobr, ll tag, int l, int r, int i) {
    int rt = clone(i);
    ll a = max(l, jobl), b = min(jobr, r);
    node[rt].sum += tag * (b - a + 1);
    // 只有当, 节点被完全包裹时, 打上标签信息
    if (jobl <= l && r <= jobr) {
        node[rt].addTag += tag;
    }
    else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            node[rt].left = add(jobl, jobr, tag, l, mid, node[rt].left);
        }
        if (jobr > mid) {
            node[rt].right = add(jobl, jobr, tag, mid + 1, r, node[rt].right);
        }
    }
    return rt;
}

ll query(int jobl, int jobr, ll addHistory, int l, int r, int i) {
    ll a = max(l, jobl), b = min(jobr, r);
    if (jobl <= l && r <= jobr) {
        return node[i].sum + addHistory * (b - a + 1LL);
    }
    else {
        int mid = (l + r) >> 1;
        // 此处的ans, 初始化为0, 在子节点上获取正确的累加和值
        ll ans = 0;
        if (jobl <= mid) {
            ans += query(jobl, jobr, addHistory + node[i].addTag, l, mid, node[i].left);
        }
        if (jobr > mid) {
            ans += query(jobl, jobr, addHistory + node[i].addTag, mid + 1, r, node[i].right);
        }
        return ans;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    int time = 0;
    cnt = 0;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
    }
    version[0] = build(1, n);
    while (m--) {
        char op;
        int l, r, ver;
        ll v;
        cin >> op;
        if (op == 'C') {
            cin >> l >> r >> v;
            version[time + 1] = add(l, r, v, 1, n, version[time]);
            time++;
        }
        else if (op == 'Q') {
            cin >> l >> r;
            cout << query(l, r, 0, 1, n, version[time]) << '\n';
        }
        else if (op == 'H') {
            cin >> l >> r >> ver;
            cout << query(l, r, 0, 1, n, version[ver]) << '\n';
        }
        else {
            cin >> time;
        }
    }
}
