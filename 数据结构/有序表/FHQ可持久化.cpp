#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5e5;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>dist(1, INT_MAX);

int version[MAXN + 1];
int cnt = 0;
struct {
    ll key;
    int priority;
    int left;
    int right;
    int size;
}node[MAXN * 50 + 1];

void clear() {
    for (int i = 0;i <= cnt;i++) {
        node[i] = { 0,0,0,0,0 };
    }
    cnt = 0;
}

int clone(int i) {
    node[++cnt] = node[i];
    return cnt;
}

int create(int val) {
    node[++cnt].key = val;
    node[cnt].size = 1;
    node[cnt].priority = dist(gen);
    return cnt;
}

void up(int i) {
    node[i].size = node[node[i].left].size + node[node[i].right].size + 1;
}

void split(int l, int r, int i, ll val) {
    if (i == 0) {
        node[l].right = node[r].left = 0;
    }
    else {
        i = clone(i);
        if (node[i].key <= val) {
            node[l].right = i;
            split(i, r, node[i].right, val);
        }
        else {
            node[r].left = i;
            split(l, i, node[i].left, val);
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
        node[l].right = merge(node[l].right, r);
        up(l);
        return l;
    }
    else {
        r = clone(r);
        node[r].left = merge(l, node[r].left);
        up(r);
        return r;
    }
}

int remove(int v, ll val) {
    // 基于v版本, 删除一个val
    int head = version[v];
    split(0, 0, head, val);
    //  <=val                 >val
    int l = node[0].right, r = node[0].left;
    node[0].left = node[0].right = 0;
    split(0, 0, l, val - 1);
    //   <val              =val
    int lm = node[0].right, rm = node[0].left;
    node[0].left = node[0].right = 0;
    int ans = merge(merge(lm, merge(node[rm].left, node[rm].right)), r);
    node[0].left = node[0].right = 0;
    return ans;
}

int add(int v, ll val) {
    int head = version[v];
    split(0, 0, head, val);
    //  <=val                 >val
    int l = node[0].right, r = node[0].left;
    node[0].left = node[0].right = 0;
    int ans = merge(merge(l, create(val)), r);
    return ans;
}

int small(int i, ll val) {
    if (i == 0) {
        return 0;
    }
    if (node[i].key >= val) {
        return small(node[i].left, val);
    }
    else {
        return node[node[i].left].size + 1 + small(node[i].right, val);
    }
}

int rank(int v, ll val) {
    return small(version[v], val) + 1;
}

ll index(int i, int rk) {
    if (i == 0) {
        return 0;
    }
    if (node[node[i].left].size >= rk) {
        return index(node[i].left, rk);
    }
    else if (node[node[i].left].size + 1 < rk) {
        return index(node[i].right, rk - node[node[i].left].size - 1);
    }
    return node[i].key;
}

ll pre(int i, ll val) {
    if (i == 0) {
        return INT_MIN + 1;
    }
    if (node[i].key >= val) {
        return pre(node[i].left, val);
    }
    else {
        return max(node[i].key, pre(node[i].right, val));
    }
}

ll post(int i, ll val) {
    if (i == 0) {
        return INT_MAX;
    }
    if (node[i].key <= val) {
        return post(node[i].right, val);
    }
    else {
        return min(node[i].key, post(node[i].left, val));
    }
}

void solve() {
    int n;
    cin >> n;
    clear();
    for (int i = 1;i <= n;i++) {
        int v, op;
        ll val;
        cin >> v >> op >> val;
        if (op == 1) {
            version[i] = add(v, val);
        }
        else if (op == 2) {
            version[i] = remove(v, val);
        }
        else {
            version[i] = version[v];
            if (op == 3) {
                cout << ::rank(i, val) << '\n';
            }
            else if (op == 4) {
                cout << index(version[i], val) << '\n';
            }
            else if (op == 5) {
                cout << pre(version[i], val) << '\n';
            }
            else {
                cout << post(version[i], val) << '\n';
            }
        }
    }
}
