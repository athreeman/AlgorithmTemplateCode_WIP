#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 2e5;

ll a[MAXN + 1];
int version[MAXN + 1];

int cnt = 0;
struct tree {
    int left;
    int right;
    ll sum;
    ll lazyAdd;
}node[(MAXN << 2 | 1) + MAXN * 70];

void up(int i) {
    node[i].sum = node[node[i].left].sum + node[node[i].right].sum;
}


int clone(int i) {
    node[++cnt] = node[i];
    return cnt;
}

int build(int l, int r) {
    int rt = ++cnt;
    node[rt].lazyAdd = 0;
    if (l == r) {
        node[rt].sum = a[l];
    }
    else {
        int mid = (l + r) >> 1;
        node[rt].left = build(l, mid);
        node[rt].right = build(mid + 1, r);
        up(rt);
    }
    return rt;
}

void lazy(int i, int siz, ll jobv) {
    node[i].sum += siz * jobv;
    node[i].lazyAdd += jobv;
}

void down(int i, int lsiz, int rsiz) {
    if (node[i].lazyAdd != 0) {
        node[i].left = clone(node[i].left);
        node[i].right = clone(node[i].right);
        lazy(node[i].left, lsiz, node[i].lazyAdd);
        lazy(node[i].right, rsiz, node[i].lazyAdd);
        node[i].lazyAdd = 0;
    }
}

ll add(int jobl, int jobr, ll jobv, int l, int r, int i) {
    int rt = clone(i);
    if (jobl <= l && r <= jobr) {
        lazy(rt, r - l + 1, jobv);
    }
    else {
        int mid = (l + r) >> 1;
        down(rt, mid - l + 1, r - mid);
        if (jobl <= mid) {
            node[rt].left = add(jobl, jobr, jobv, l, mid, node[rt].left);
        }
        if (jobr > mid) {
            node[rt].right = add(jobl, jobr, jobv, mid + 1, r, node[rt].right);
        }
        up(rt);
    }
    return rt;
}

ll query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return node[i].sum;
    }
    else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        ll ans = 0;
        if (jobl <= mid) {
            ans += query(jobl, jobr, l, mid, node[i].left);
        }
        if (jobr > mid) {
            ans += query(jobl, jobr, mid + 1, r, node[i].right);
        }
        up(i);
        return ans;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
    }
    int time = 0;
    version[0] = build(1, n);
    while (m--) {
        char op;
        cin >> op;
        if (op == 'C') {
            int l, r;
            ll v;
            cin >> l >> r >> v;
            version[time + 1] = add(l, r, v, 1, n, version[time]);
            time++;
        }
        else if (op == 'Q') {
            int l, r;
            cin >> l >> r;
            cout << query(l, r, 1, n, version[time]) << '\n';
        }
        else if (op == 'H') {
            int l, r, ver;
            cin >> l >> r >> ver;
            cout << query(l, r, 1, n, version[ver]) << '\n';
        }
        else {
            cin >> time;
        }
    }
}
