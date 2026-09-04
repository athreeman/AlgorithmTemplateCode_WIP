#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// FHQTreap
// 核心: 根据key值执行分裂, 根据优先级执行合并操作

const int MAXN = 2e5;
const ll INF = 1e18;
int head = 0, cnt = 0;
struct {
    ll key;
    int priority;
    int left;
    int right;
    int size;// 总元素个数(词频和)
    int count;
}node[MAXN + 1];

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>dist(1, INT_MAX);

void clear() {
    for (int i = 0;i <= cnt;i++) {
        node[i] = { 0,0,0,0,0,0 };
    }
    head = cnt = 0;
}

void up(int i) {
    node[i].size = node[node[i].left].size + node[node[i].right].size + node[i].count;
}

// 若当前 curv <= key, 则左侧子树不需要改变, 向右子树递归
// 反之, 右侧子树不需要改变, 向左子树递归

// key值分裂
void splitByKey(int l, int r, int i, ll key) {
    if (i == 0) {
        node[l].right = node[r].left = 0;
    }
    else {
        if (node[i].key <= key) {
            node[l].right = i;
            splitByKey(i, r, node[i].right, key);
        }
        else {
            node[r].left = i;
            splitByKey(l, i, node[i].left, key);
        }
        up(i);
    }
}

// 排名分裂
// 该排名分裂, 只能解决每个位置的count = 1的情况
// 若存在重复计数, 需要定制
void splitByRank(int l, int r, int i, ll rk) {
    if (i == 0) {
        node[l].right = node[r].left = 0;
    }
    else {
        if (node[node[i].left].size + 1 <= rk) {
            node[l].right = i;
            splitByRank(i, r, node[i].right, rk - node[node[i].left].size - 1);
        }
        else {
            node[r].left = i;
            splitByRank(l, i, node[i].left, rk);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (node[l].priority >= node[r].priority) {
        node[l].right = merge(node[l].right, r);
        up(l);
        return l;
    }
    else {
        node[r].left = merge(l, node[r].left);
        up(r);
        return r;
    }
}

int find(int i, ll val) {
    if (i == 0) {
        return 0;
    }
    if (node[i].key == val) {
        return i;
    }
    else if (node[i].key < val) {
        return find(node[i].right, val);
    }
    else {
        return find(node[i].left, val);
    }
}

void changeCount(int i, ll val, int change) {
    if (node[i].key == val) {
        node[i].count += change;
    }
    else if (node[i].key > val) {
        changeCount(node[i].left, val, change);
    }
    else {
        changeCount(node[i].right, val, change);
    }
    up(i);
}

void add(ll val) {
    if (find(head, val) != 0) {
        changeCount(head, val, 1);
    }
    else {
        splitByKey(0, 0, head, val);
        node[++cnt].key = val;
        node[cnt].count = 1;
        node[cnt].size = 1;
        node[cnt].priority = dist(gen);
        head = merge(merge(node[0].right, cnt), node[0].left);
    }
}

void remove(ll val) {
    int i = find(head, val);
    if (i != 0) {
        if (node[i].count > 1) {
            changeCount(head, val, -1);
        }
        else {
            splitByKey(0, 0, head, val);
            int lm = node[0].right;
            int r = node[0].left;
            splitByKey(0, 0, lm, val - 1);
            int l = node[0].right;
            head = merge(l, r);
        }
    }
}

int small(int i, ll val) {
    if (i == 0) {
        return 0;
    }
    if (node[i].key >= val) {
        return small(node[i].left, val);
    }
    else {
        return node[node[i].left].size + node[i].count + small(node[i].right, val);
    }
}

int rank(ll val) {
    return small(head, val) + 1;
}

ll index(int i, int x) {
    if (node[node[i].left].size >= x) {
        return index(node[i].left, x);
    }
    else if (node[node[i].left].size + node[i].count < x) {
        return index(node[i].right, x - node[node[i].left].size - node[i].count);
    }
    return node[i].key;
}

ll index(int x) {
    return index(head, x);
}

ll pre(int i, ll val) {
    if (i == 0) {
        return -INF;
    }
    if (node[i].key >= val) {
        return pre(node[i].left, val);
    }
    else {
        return max(node[i].key, pre(node[i].right, val));
    }
}

ll pre(ll val) {
    return pre(head, val);
}

ll post(int i, ll val) {
    if (i == 0) {
        return INF;
    }
    if (node[i].key <= val) {
        return post(node[i].right, val);
    }
    else {
        return min(node[i].key, post(node[i].left, val));
    }
}

ll post(ll val) {
    return post(head, val);
}
