#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
const int MAXN = 2e6;
const ld Alpha = 0.7;
const ll INF = 1e18;

int top, father, side;
int collects[MAXN + 1];
int ci = 0;

int head = 0, cnt = 0;
struct tree {
    ll key;
    int aliveSiz;
    int left;
    int right;
    bool alive;
}node[MAXN + 1];

void clear() {
    for (int i = 0;i <= cnt;i++) {
        node[i] = { 0,0,0,0,0 };
    }
    head = cnt = 0;
}

int create(ll val) {
    node[++cnt].key = val;
    node[cnt].aliveSiz = 1;
    node[cnt].alive = true;
    node[cnt].left = node[cnt].right = 0;
    return cnt;
}


void up(int i) {
    node[i].aliveSiz = node[node[i].left].aliveSiz + node[node[i].right].aliveSiz + (node[i].alive ? 1 : 0);
}

int build(int l, int r) {
    if (l > r) {
        return 0;
    }
    int mid = (l + r) >> 1;
    int p = collects[mid];
    node[p].left = build(l, mid - 1);
    node[p].right = build(mid + 1, r);
    up(p);
    return p;
}

void inorder(int i) {
    if (i != 0 && node[i].aliveSiz > 0) {
        inorder(node[i].left);
        if (node[i].alive) {
            collects[++ci] = i;
        }
        inorder(node[i].right);
    }
}

void rebuild() {
    if (top != 0) {
        ci = 0;
        inorder(top);
        int u = build(1, ci);
        if (side == 1) {
            node[father].left = u;
        }
        else if (side == 2) {
            node[father].right = u;
        }
        else {
            head = u;
        }
        top = father = side = 0;
    }
}

bool isBalance(int i) {
    return node[i].aliveSiz * Alpha >= max(node[node[i].left].aliveSiz, node[node[i].right].aliveSiz);
}

int add(int i, int f, int s, ll val) {
    if (i == 0 || node[i].aliveSiz == 0) {
        return create(val);
    }
    if (node[i].key >= val) {
        node[i].left = add(node[i].left, i, 1, val);
    }
    else {
        node[i].right = add(node[i].right, i, 2, val);
    }
    up(i);
    if (!isBalance(i)) {
        top = i;
        father = f;
        side = s;
    }
    return i;
}

void add(ll val) {
    top = father = side = 0;
    head = add(head, 0, 0, val);
    rebuild();
}

int samll(int i, ll val) {
    if (i == 0 || node[i].aliveSiz == 0) {
        return 0;
    }
    if (node[i].key >= val) {
        return samll(node[i].left, val);
    }
    else {
        return node[node[i].left].aliveSiz + (node[i].alive ? 1 : 0) + samll(node[i].right, val);
    }
}

int rank(ll val) {
    return samll(head, val) + 1;
}


ll index(int i, int rank) {
    int cur = node[i].alive ? 1 : 0;
    if (node[node[i].left].aliveSiz >= rank) {
        return index(node[i].left, rank);
    }
    else if (node[node[i].left].aliveSiz + cur < rank) {
        return index(node[i].right, rank - node[node[i].left].aliveSiz - cur);
    }
    return node[i].key;
}

ll index(int rank) {
    return index(head, rank);
}

int remove(int i, int f, int s, int rank) {
    if (i == 0 || node[i].aliveSiz == 0) {
        return 0;
    }
    int lsiz = node[node[i].left].aliveSiz;
    int cur = node[i].alive ? 1 : 0;
    if (rank <= lsiz) {
        node[i].left = remove(node[i].left, i, 1, rank);
    }
    else if (node[i].alive && rank == lsiz + cur) {
        node[i].alive = false;
    }
    else {
        node[i].right = remove(node[i].right, i, 2, rank - lsiz - cur);
    }
    up(i);
    if (!isBalance(i)) {
        top = i;
        father = f;
        side = s;
    }
    return i;
}

void remove(ll val) {
    int k1 = ::rank(val);
    int k2 = ::rank(val + 1);
    if (k1 != k2) {
        top = father = side = 0;
        head = remove(head, 0, 0, k1);
        rebuild();
    }
}

ll post(ll val) {
    int kth = ::rank(val + 1);
    if (kth == node[head].aliveSiz + 1) {
        return INF;
    }
    else {
        return index(kth);
    }
}


ll pre(ll val) {
    int kth = ::rank(val);
    if (kth == 1) {
        return -INF;
    }
    else {
        return index(kth - 1);
    }
}

