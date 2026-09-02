#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// AVL: 平衡搜索二叉树
// 每个节点的左右子树高度之差 <= 1

// 有序表:
// 可实现: 增, 删, 改, 查
// 单次时间复杂度O(logn)
// 每个key(键)映射唯一value(值)
// 根据key的序组织, key不能重复(唯一)

// https://www.luogu.com.cn/problem/P3369

const int MAXN = 2e5;
const ll INF = 1e18;
int head = 0;
int cnt = 0;
// 可以使用use表维护可用内存编号, 避免内存浪费
// canUse[0]表示可用节点数量
// int canUse[MAXN + 1];
struct {
    ll key;// 键
    int height;// 树高
    int left;// 左儿子
    int right;// 右儿子
    int cnt;// key词频
    int siz;// 子树大小
}node[MAXN + 1];

void clear() {
    for (int i = 1;i <= cnt;i++) {
        node[i] = { 0,0,0,0,0,0 };
    }
    cnt = 0;
    head = 0;
}

// 汇总信息
void up(int i) {
    int l = node[i].left, r = node[i].right;
    node[i].siz = node[l].siz + node[r].siz + node[i].cnt;
    node[i].height = max(node[l].height, node[r].height) + 1;
}

// 左旋, 父节点向左下沉
// 右孩子的左儿子成为父亲的右孩子
// 父亲成为右孩子的左儿子
int leftRotate(int i) {
    int r = node[i].right;
    node[i].right = node[r].left;
    node[r].left = i;
    up(i);
    up(r);
    return r;
}

// 右旋
int rightRotate(int i) {
    int l = node[i].left;
    node[i].left = node[l].right;
    node[l].right = i;
    up(i);
    up(l);
    return l;
}

// 检查子树是否违规并调整
int maintain(int i) {
    int l = node[i].left, r = node[i].right;
    int lh = node[l].height;
    int rh = node[r].height;
    if (lh - rh > 1) {
        // LL
        if (node[node[l].left].height >= node[node[l].right].height) {
            i = rightRotate(i);
        }
        else {
            // LR
            node[i].left = leftRotate(l);
            i = rightRotate(i);
        }
    }
    else if (rh - lh > 1) {
        // RR
        if (node[node[r].right].height >= node[node[r].left].right) {
            i = leftRotate(i);
        }
        else {
            // RL
            node[i].right = rightRotate(r);
            i = leftRotate(i);
        }
    }
    return i;
}



// 查询 < val的key个数
int small(int i, int val) {
    if (i == 0) {
        return 0;
    }
    if (node[i].key >= val) {
        return small(node[i].left, val);
    }
    else {
        return node[node[i].left].siz + node[i].cnt + small(node[i].right, val);
    }
}

// 查询排名
int rank(int val) {
    return small(head, val) + 1;
}

// 查询子树i上第k小的数
ll index(int i, int k) {
    int l = node[i].left;
    if (node[l].siz >= k) {
        return index(l, k);
    }
    else if (node[l].siz + node[i].cnt < k) {
        return index(node[i].right, k - node[l].siz - node[i].cnt);
    }
    return node[i].key;
}

ll index(int k) {
    return index(head, k);
}


// 查找子树i上val的前驱(< val的最大值)
ll pre(int i, int val) {
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

ll pre(int val) {
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
        return min(node[i].key, suf(node[i].left, val));
    }
}

ll suf(int val) {
    return suf(head, val);
}

// 向子树i添加值val
int add(int i, int val) {
    if (i == 0) {
        node[++cnt].key = val;
        node[cnt].cnt = node[cnt].siz = node[cnt].height = 1;
        return cnt;
    }
    if (node[i].key == val) {
        node[i].cnt++;
    }
    else if (node[i].key > val) {
        node[i].left = add(node[i].left, val);
    }
    else {
        node[i].right = add(node[i].right, val);
    }
    up(i);
    return maintain(i);
}

// 向整颗树添加值val, 返回新的头
void add(int val) {
    head = add(head, val);
}

// 删除子树i上的low节点
int removeLow(int i, int low) {
    if (i == low) {
        return node[i].right;
    }
    else {
        node[i].left = removeLow(node[i].left, low);
        up(i);
        return maintain(i);
    }
}

// 删除子树i上的val
int remove(int i, int val) {
    if (node[i].key < val) {
        node[i].right = remove(node[i].right, val);
    }
    else if (node[i].key > val) {
        node[i].left = remove(node[i].left, val);
    }
    else {
        if (node[i].cnt > 1) {
            node[i].cnt--;
        }
        else {
            if (node[i].left == 0 && node[i].right == 0) {
                return 0;
            }
            else if (node[i].left == 0 && node[i].right != 0) {
                i = node[i].right;
            }
            else if (node[i].left != 0 && node[i].right == 0) {
                i = node[i].left;
            }
            else {
                int low = node[i].right;
                while (node[low].left != 0) {
                    low = node[low].left;
                }
                node[i].right = removeLow(node[i].right, low);
                node[low].left = node[i].left;
                node[low].right = node[i].right;
                i = low;
            }
        }
    }
    up(i);
    return maintain(i);
}

// 单次删除整棵树上的key
void remove(int val) {
    if (::rank(val) != ::rank(val + 1)) {
        head = remove(head, val);
    }
}
