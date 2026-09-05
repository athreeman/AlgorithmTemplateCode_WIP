#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ill = __int128_t;

const int MAXN = 2e5;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>dist(1, INT_MAX);

int cnt = 0;
int version[MAXN + 1];
struct {
    ll key;
    ll sum;
    int left;
    int right;
    int size;
    int priority;
    bool isRev;
}node[MAXN * 50 + 1];

void clear() {
    for (int i = 0;i <= cnt;i++) {
        node[i] = { 0,0,0,0,0,0,0 };
    }
    cnt = 0;
}

int clone(int i) {
    node[++cnt] = node[i];
    return cnt;
}

int create(ll val) {
    node[++cnt].key = val;
    node[cnt].sum = val;
    node[cnt].priority = dist(gen);
    node[cnt].size = 1;
    return cnt;
}

void up(int i) {
    node[i].size = node[node[i].left].size + node[node[i].right].size + 1;
    node[i].sum = node[node[i].left].sum + node[node[i].right].sum + node[i].key;
}

void down(int i) {
    if (node[i].isRev) {
        // 若存在, 则拷贝
        if (node[i].left != 0) {
            node[i].left = clone(node[i].left);
            node[node[i].left].isRev ^= 1;
        }
        if (node[i].right != 0) {
            node[i].right = clone(node[i].right);
            node[node[i].right].isRev ^= 1;
        }
        // 对拷贝后的进行懒更新
        swap(node[i].left, node[i].right);
        node[i].isRev = false;
    }
}


void split(int l, int r, int i, int rk) {
    if (i == 0) {
        node[l].right = node[r].left = 0;
    }
    else {
        i = clone(i);
        down(i);
        if (node[node[i].left].size + 1 <= rk) {
            node[l].right = i;
            split(i, r, node[i].right, rk - node[node[i].left].size - 1);
        }
        else {
            node[r].left = i;
            split(l, i, node[i].left, rk);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (node[l].priority >= node[r].priority) {
        l = clone(l);
        down(l);
        node[l].right = merge(node[l].right, r);
        up(l);
        return l;
    }
    else {
        r = clone(r);
        down(r);
        node[r].left = merge(l, node[r].left);
        up(r);
        return r;
    }
}

// 基于版本v, 对区间[jobl, jobr]进行翻转
int reverse(int v, int jobl, int jobr) {
    // 新版本的头
    int head = version[v];

    split(0, 0, head, jobr);
    //   <=jobr               >jobr
    int l = node[0].right, r = node[0].left;
    node[0] = { 0,0,0,0,0,0,0 };

    split(0, 0, l, jobl - 1);
    //   <jobl             [jobl, jobr]
    int lm = node[0].right, rm = node[0].left;
    node[0] = { 0,0,0,0,0,0,0 };

    int ans;
    node[rm].isRev ^= 1;
    lm = merge(lm, rm);
    ans = merge(lm, r);

    return ans;
}

// 基于版本v, 删除第x个元素
int remove(int v, int x) {
    int head = version[v];

    split(0, 0, head, x);
    //  <=x                 >x
    int l = node[0].right, r = node[0].left;
    node[0] = { 0,0,0,0,0,0,0 };

    split(0, 0, l, x - 1);
    //  <x                  =x
    int lm = node[0].right, rm = node[0].left;
    node[0] = { 0,0,0,0,0,0,0 };

    lm = merge(lm, merge(node[rm].left, node[rm].right));
    int ans = merge(lm, r);

    return ans;
}

// 基于版本v, 在第x个元素后, 插入val
int insert(int v, int x, ll val) {
    int head = version[v];

    split(0, 0, head, x);
    //     <=x                 >x
    int l = node[0].right, r = node[0].left;
    node[0] = { 0,0,0,0,0,0,0 };

    l = merge(l, create(val));
    int ans = merge(l, r);

    return ans;
}

// 基于版本v, 查询[l,r]的和
int query(int v, int jobl, int jobr, ll& sum) {
    int head = version[v];

    split(0, 0, head, jobr);
    // <=jobr                 >jobr
    int l = node[0].right, r = node[0].left;
    node[0] = { 0,0,0,0,0,0,0 };

    split(0, 0, l, jobl - 1);
    //   <jobl                [jobl,jobr]
    int lm = node[0].right, rm = node[0].left;
    node[0] = { 0,0,0,0,0,0,0 };

    sum = node[rm].sum;
    lm = merge(lm, rm);
    int ans = merge(lm, r);
    return ans;
}

void solve() {
    int n;
    cin >> n;
    ll lastAns = 0;
    clear();
    for (int i = 1;i <= n;i++) {
        int v, op;
        cin >> v >> op;
        if (op == 1) {
            ll p;ll x;
            cin >> p >> x;
            p ^= lastAns, x ^= lastAns;
            version[i] = insert(v, p, x);
        }
        else if (op == 2) {
            ll p;
            cin >> p;
            p ^= lastAns;
            version[i] = remove(v, p);
        }
        else if (op == 3) {
            ll l, r;
            cin >> l >> r;
            l ^= lastAns, r ^= lastAns;
            version[i] = reverse(v, l, r);
        }
        else {
            ll l, r;
            cin >> l >> r;
            l ^= lastAns, r ^= lastAns;
            ll sum;
            version[i] = query(v, l, r, sum);
            cout << sum << '\n';
            lastAns = sum;
        }
    }
}
