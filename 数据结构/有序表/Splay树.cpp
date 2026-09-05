#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;
const ll INF = 1e18;

// splay树中提根操作在每个增, 删, 改, 查操作都有必要执行
// 因为提根操作可以缩短树的高度

// 以下方法内不含提根的只有find方法
// 因为remove依赖连续的find辅助, 一旦提根改变树结构, remove操作非法

int head = 0, cnt = 0;
struct {
    ll key;
    int left;
    int right;
    int father;
    int size;
}node[MAXN + 1];

void clear() {
    for (int i = 0;i <= cnt;i++) {
        node[i] = { 0,0,0,0,0 };
    }
    head = cnt = 0;
}

int create(ll val) {
    node[++cnt].key = val;
    node[cnt].size = 1;
    return cnt;
}

void up(int i) {
    node[i].size = node[node[i].left].size + node[node[i].right].size + 1;
}

int side(int i) {
    return node[node[i].father].left == i ? 1 : 2;
}


// 左旋右旋的同时, 维护争取的父子关系
// 其中节点0不设任何父亲
int leftRotate(int i) {
    int l = node[i].left, r = node[i].right;
    node[i].right = node[r].left;
    node[r].left = i;

    node[r].father = node[i].father;
    node[i].father = r;
    if (node[i].right != 0) {
        // 0号节点不设父亲
        node[node[i].right].father = i;
    }
    return r;
}

int rightRotate(int i) {
    int l = node[i].left, r = node[i].right;
    node[i].left = node[l].right;
    node[l].right = i;

    node[l].father = node[i].father;
    node[i].father = l;
    if (node[i].left != 0) {
        node[node[i].left].father = i;
    }
    return l;
}

// 让i上升一步
void rotate(int i) {
    //  father               grandfather
    int fa = node[i].father, gfa = node[fa].father;
    // 不存在父亲, 根节点不执行操作
    if (fa != 0) {
        int s1 = side(i), s2 = side(fa);
        if (s1 == 1) {
            rightRotate(fa);
        }
        else {
            leftRotate(fa);
        }
        // 存在爷爷, 更新
        if (gfa != 0) {
            if (s2 == 1) {
                node[gfa].left = i;
            }
            else {
                node[gfa].right = i;
            }
        }
        else {// 不存在爷爷, 此时i成为根
            head = i;
        }
        up(fa);
        up(i);
    }
}

// 让i成为goal的儿子
void splay(int i, int goal) {
    int fa = node[i].father, gfa = node[fa].father;
    while (fa != goal) {
        // 若爷爷是目标点, i上升一步即可
        if (gfa != goal) {
            // 一字型
            if (side(i) == side(fa)) {
                rotate(fa);
            }
            else {// 之字型
                rotate(i);
            }
        }
        rotate(i);
        fa = node[i].father;
        gfa = node[fa].father;
    }
    if (goal == 0) {
        // i成为根节点
        head = i;
    }
}

// 查询排名k的节点
int find(int k) {
    int i = head;
    while (i != 0) {
        // 满足
        if (node[node[i].left].size + 1 == k) {
            return i;
        }
        else if (node[node[i].left].size >= k) {
            // 位于左侧
            i = node[i].left;
        }
        else {// 位于右侧
            k -= (node[node[i].left].size + 1);
            i = node[i].right;
        }
    }
    return 0;//不存在
}

int small(ll val) {
    int i = head, last = head;
    int ans = 0;
    while (i != 0) {
        last = i;
        if (node[i].key >= val) {
            i = node[i].left;
        }
        else {
            ans += node[node[i].left].size + 1;
            i = node[i].right;
        }
    }
    splay(last, 0);
    return ans;
}

int rank(ll val) {
    return small(val) + 1;
}

void add(ll val) {
    int i = create(val);
    if (head == 0) {
        head = i;
    }
    else {
        int fa = 0, u = head, side = 0;
        while (u != 0) {
            // 左 <= 中 <= 右
            if (node[u].key <= val) {
                side = 2;
                fa = u;
                u = node[u].right;
            }
            else {
                side = 1;
                fa = u;
                u = node[u].left;
            }
        }
        if (side == 1) {
            node[fa].left = i;
        }
        else {
            node[fa].right = i;
        }
        node[i].father = fa;
        splay(i, 0);
    }
}

void remove(ll val) {
    int kth = ::rank(val);
    if (kth != ::rank(val + 1)) {
        int i = find(kth);
        splay(i, 0);
        if (node[i].left == 0) {
            head = node[i].right;
        }
        else if (node[i].right == 0) {
            head = node[i].left;
        }
        else {
            // i排名kth, kth+1必定在i的右子树
            // 把j提到i的右儿子, 此时j必然不存在左儿子
            // (因为kth是中序遍历的顺序, 所以j作为kth+1名必然不存在左儿子)
            // 把i的左儿子给j, 让j成为头即可
            int j = find(kth + 1);
            splay(j, i);
            node[j].left = node[i].left;
            node[node[j].left].father = j;
            up(j);
            head = j;
        }
        node[head].father = 0;
    }
}

ll index(int x) {
    int i = find(x);
    splay(i, 0);
    return node[i].key;
}

ll pre(ll val) {
    int i = head, last = head;
    ll ans = -INF;
    while (i != 0) {
        last = i;
        if (node[i].key >= val) {
            i = node[i].left;
        }
        else {
            ans = max(ans, node[i].key);
            i = node[i].right;
        }
    }
    splay(last, 0);
    return ans;
}

ll post(ll val) {
    int i = head, last = head;
    ll ans = INF;
    while (i != 0) {
        last = i;
        if (node[i].key <= val) {
            i = node[i].right;
        }
        else {
            ans = min(ans, node[i].key);
            i = node[i].left;
        }
    }
    splay(last, 0);
    return ans;
}
