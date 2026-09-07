#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 替罪羊树:
// 平衡因子Alpha, 最优取0.7
// 当左或右子树节点数 > n * Alpha时
// 进行整颗子树的重构
// 若存在多个违规子树, 选择最高的节点子树

const int MAXN = 2e5;
const double Alpha = 0.7;// 平衡因子
const ll INF = 1e18;
int head = 0, cnt = 0;
int collect[MAXN + 1];// 中序遍历收集节点
// 最高的不平衡点  top的父亲  top和父亲的关系
int top, father, side;
struct {
    ll key;// 键值
    int count;// 当前key, 词频
    int left;// 左儿子
    int right;// 右儿子
    int diff;// 维护子树上不同key的个数(即节点数), different
    int size;// 收集的元素个数(词频和) 
}node[MAXN + 1];

int create(ll val) {
    node[++cnt].key = val;
    node[cnt].count = 1;
    node[cnt].left = node[cnt].right = 0;
    node[cnt].diff = 1;
    node[cnt].size = 1;
    return cnt;
}

void up(int i) {
    int l = node[i].left, r = node[i].right;
    node[i].size = node[l].size + node[r].size + node[i].count;
    // 由于替罪羊树的懒删除机制, 此处diff需要判断节点i是否存在词频
    node[i].diff = node[l].diff + node[r].diff + (node[i].count > 0 ? 1 : 0);
}

// 中序遍历
// 左 -> 中 -> 右
void inorder(int i) {
    if (i != 0) {
        inorder(node[i].left);
        if (node[i].count > 0) {
            collect[++collect[0]] = i;
        }
        inorder(node[i].right);
    }
}

int build(int l, int r) {
    if (l > r) {
        return 0;
    }
    int mid = (l + r) >> 1;
    int h = collect[mid];
    node[h].left = build(l, mid - 1);
    node[h].right = build(mid + 1, r);
    up(h);
    return h;
}

// 二分重构
void rebuild() {
    if (top != 0) {
        collect[0] = 0;
        inorder(top);
        if (collect[0] > 0) {
            if (father == 0) {
                head = build(1, collect[0]);
            }
            else if (side == 1) {
                node[father].left = build(1, collect[0]);
            }
            else {
                node[father].right = build(1, collect[0]);
            }
        }
    }
}

bool isBalance(int i) {
    return Alpha * node[i].diff >= max(node[node[i].left].diff, node[node[i].right].diff);
}

// 当前节点  父亲  父子关系  key值
void add(int i, int fa, int s, ll val) {
    if (i == 0) {
        if (fa == 0) {
            head = create(val);
        }
        else if (s == 1) {
            node[fa].left = create(val);
        }
        else {
            node[fa].right = create(val);
        }
    }
    else {
        if (node[i].key == val) {
            node[i].count++;
        }
        else if (node[i].key > val) {
            add(node[i].left, i, 1, val);
        }
        else {
            add(node[i].right, i, 2, val);
        }
    }
    up(i);
    if (!isBalance(i)) {
        top = i;
        father = fa;
        side = s;
    }
}

void add(ll val) {
    top = father = side = 0;
    add(head, 0, 0, val);
    rebuild();
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

void remove(int i, int fa, int s, ll val) {
    if (node[i].key == val) {
        node[i].count--;
    }
    else if (node[i].key > val) {
        remove(node[i].left, i, 1, val);
    }
    else {
        remove(node[i].right, i, 2, val);
    }
    up(i);
    if (!isBalance(i)) {
        top = i;
        father = fa;
        side = s;
    }
}

void remove(ll val) {
    if (::rank(val) != ::rank(val + 1)) {
        top = father = side = 0;
        remove(head, 0, 0, val);
        rebuild();
    }
}

ll index(int i, ll x) {
    if (node[node[i].left].size >= x) {
        return index(node[i].left, x);
    }
    else if (node[node[i].left].size + node[i].count < x) {
        return index(node[i].right, x - node[node[i].left].size - node[i].count);
    }
    return node[i].key;
}

ll index(ll x) {
    return index(head, x);
}

ll pre(ll val) {
    int kth = ::rank(val);
    if (kth == 1) {
        return -INF;
    }
    return index(kth - 1);
}

ll suf(ll val) {
    int kth = ::rank(val + 1);
    if (kth == node[head].size + 1) {
        return INF;
    }
    return index(kth);
}

void clear() {
    for (int i = 0;i <= cnt;i++) {
        node[i] = { 0,0,0,0,0,0 };
    }
    cnt = 0;
    head = 0;
}
