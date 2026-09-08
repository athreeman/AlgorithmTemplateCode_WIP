#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 2e5;
const int MAXT = 4e5;
int cnt = 0;
int version[MAXN + 1];
int verSize[MAXN + 1];
struct leftTree {
    ll key;
    int left;
    int right;
    int dist;
    int size;
}node[MAXT + 1];

void cleanNode(int i) {
    node[i].key = 0;
    node[i].left = node[i].right = node[i].dist = 0;
    node[i].size = 1;
}

void clear(int n) {
    for (int i = 0;i <= cnt;i++) {
        cleanNode(i);
    }
    fill(version, version + n + 1, 0);
    fill(verSize, verSize + n + 1, 0);
    node[0].dist = -1;
    node[0].size = 0;
    cnt = 0;
}

int clone(int i) {
    int j = ++cnt;
    node[j] = node[i];
    return j;
}

int create(ll val) {
    int i = ++cnt;
    node[i].key = val;
    node[i].left = node[i].right = node[i].dist = 0;
    node[i].size = 1;
    return i;
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    if (node[i].key > node[j].key) {
        swap(i, j);
    }
    int p = clone(i);
    node[p].right = merge(node[p].right, j);
    if (node[node[p].left].dist < node[node[p].right].dist) {
        swap(node[p].left, node[p].right);
    }
    node[p].dist = node[node[p].right].dist + 1;
    node[p].size = node[node[p].left].size + node[node[p].right].size + 1;
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

// 基于x版本插入v
void treeAdd(int x, ll v, int i) {
    if (version[x] == 0) {
        version[i] = create(v);
        verSize[i] = 1;
    }
    else {
        version[i] = merge(version[x], create(v));
        verSize[i] = verSize[x] + 1;
    }
}

// 基于x和y版本进行合并
void treeMerge(int x, int y, int i) {
    int v1 = version[x];
    int v2 = version[y];
    if (v1 == 0 && v2 == 0) {
        version[i] = 0;
        verSize[i] = 0;
        return;
    }
    if (v1 == 0 || v2 == 0) {
        version[i] = clone(v1 + v2);
        verSize[i] = verSize[x] + verSize[y];
        return;
    }
    version[i] = merge(v1, v2);
    verSize[i] = verSize[x] + verSize[y];
}

// 基于x版本弹出队头
void treePop(int x, int i) {
    if (version[x] != 0) {
        version[i] = pop(version[x]);
        verSize[i] = verSize[x] - 1;
    }
    else {
        version[i] = 0;
        verSize[i] = 0;
    }
}
