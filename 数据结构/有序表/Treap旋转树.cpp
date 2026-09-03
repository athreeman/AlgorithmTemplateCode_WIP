#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ill = __int128_t;

// Treap树：
// 每个节点存储{key, priority}
// 根据键值key维护搜索二叉树顺序(左<中<右)
// 随后根据优先级priority维护堆结构(大/小根堆)
// priority用随机函数random生成, 保证了Treap的平衡性

const int MAXN = 2e5;
const ll INF = 1e18;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>dist(0, INT_MAX);

int head = 0, cnt = 0;
struct {
    ll key;
    int priority;
    int left, right;
    int size;
    int count;
}node[MAXN + 1];

void clear() {
    for (int i = 0;i <= cnt;i++) {
        node[i] = { 0,0,0,0,0,0 };
    }
    cnt = head = 0;
}

void up(int i) {
    int l = node[i].left, r = node[i].right;
    node[i].size = node[l].size + node[r].size + node[i].count;
}

int rightRotate(int i) {
    int l = node[i].left;
    node[i].left = node[l].right;
    node[l].right = i;
    up(i);
    up(l);
    return l;
}

int leftRotate(int i) {
    int r = node[i].right;
    node[i].right = node[r].left;
    node[r].left = i;
    up(i);
    up(r);
    return r;
}

int add(int i, ll val) {
    if (i == 0) {
        node[++cnt].key = val;
        node[cnt].count = node[cnt].size = 1;
        node[cnt].priority = dist(gen);
        return cnt;
    }
    if (node[i].key == val) {
        node[i].count++;
    }
    else if (node[i].key > val) {
        node[i].left = add(node[i].left, val);
    }
    else {
        node[i].right = add(node[i].right, val);
    }
    up(i);
    if (node[i].left != 0 && node[node[i].left].priority > node[i].priority) {
        return rightRotate(i);
    }
    if (node[i].right != 0 && node[node[i].right].priority > node[i].priority) {
        return leftRotate(i);
    }
    return i;
}

void add(ll val) {
    head = add(head, val);
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
        return max(pre(node[i].right, val), node[i].key);
    }
}

ll pre(ll val) {
    return pre(head, val);
}

ll suf(int i, ll val) {
    if (i == 0) {
        return INF;
    }
    if (node[i].key <= val) {
        return suf(node[i].right, val);
    }
    else {
        return min(suf(node[i].left, val), node[i].key);
    }
}

ll suf(ll val) {
    return suf(head, val);
}

int remove(int i, ll val) {
    if (node[i].key < val) {
        node[i].right = remove(node[i].right, val);
    }
    else if (node[i].key > val) {
        node[i].left = remove(node[i].left, val);
    }
    else {
        if (node[i].count > 1) {
            node[i].count--;
        }
        else {
            if (node[i].left == 0 && node[i].right == 0) {
                return 0;
            }
            else if (node[i].left == 0 && node[i].right != 0) {
                return node[i].right;
            }
            else if (node[i].right == 0 && node[i].left != 0) {
                return node[i].left;
            }
            else {
                if (node[node[i].left].priority >= node[node[i].right].priority) {
                    i = rightRotate(i);
                    node[i].right = remove(node[i].right, val);
                }
                else {
                    i = leftRotate(i);
                    node[i].left = remove(node[i].left, val);
                }
            }
        }
    }
    up(i);
    return i;
}

void remove(ll val) {
    if (::rank(val) != ::rank(val + 1)) {
        head = remove(head, val);
    }
}
