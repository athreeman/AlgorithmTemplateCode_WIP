#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2e5;
const ll INF = 1e18;


// 跳表：
// 核心是维护每个节点的层级指针所覆盖的区间元素个数
// 使用随机函数random
// 模拟二分查找, 期望结构类似于平衡树
// 实现logn的时间复杂度

// https://www.luogu.com.cn/problem/P3369

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>dist(1, 100);
int cnt = 0;
// 最大层限制log2(n)足够
int UpLimit = 20;
struct {
    ll key;// 键值
    int count;// 词频
    int level;// 层数
    int next[21];// 指针(指向下一个)
    int len[21];// 每个指针跨越的元素个数
}node[MAXN + 1];

void build() {
    cnt = 1;
    node[cnt].key = -INF;
    node[cnt].level = UpLimit;
}

void clear() {
    for (int i = 0;i <= cnt;i++) {
        node[i].key = node[i].count = node[i].level = 0;
        fill(node[i].next, node[i].next + UpLimit + 1, 0);
        fill(node[i].len, node[i].len + UpLimit + 1, 0);
    }
    cnt = 0;
}

// 随机层数
int randomLevel() {
    int ans = 1;
    while (ans <= UpLimit && dist(gen) < 50) {
        ans++;
    }
    return min(ans, UpLimit);
}

// 从i号节点h层出发, 找到val所在的空间编号
int find(int i, int h, ll val) {
    // 水平跳跃 -> 竖直跳跃 -> 抵达1层返回
    int* next = node[i].next;// 指针数组
    while (next[h] != 0 && node[next[h]].key < val) {// 该指针指向有效空间, 且该空间的key值 < val
        i = next[h];
        next = node[i].next;
    }
    if (h == 1) {
        if (next[h] != 0 && node[next[h]].key == val) {
            return next[h];
        }
        else {// 不存在val
            return 0;
        }
    }
    // 前往下一层
    return find(i, h - 1, val);
}

void addCount(int i, int h, ll val) {
    // 增加词频
    while (node[i].next[h] != 0 && node[node[i].next[h]].key < val) {
        i = node[i].next[h];
    }
    if (h == 1) {
        // 当前位置是 < val的位置, 下一个是val
        node[node[i].next[h]].count++;
    }
    else {
        addCount(i, h - 1, val);
    }
    node[i].len[h]++;// 指针跨越元素个数 + 1
}

// 实际增加节点
// 返回值：底层指针跨越的元素个数
int addNode(int i, int h, int idx) {
    int rightCnt = 0;
    // 路径累计元素个数
    while (node[i].next[h] != 0 && node[node[i].next[h]].key < node[idx].key) {
        rightCnt += node[i].len[h];// 指针计数
        i = node[i].next[h];
    }
    if (h == 1) {
        node[idx].next[h] = node[i].next[h];
        node[i].next[h] = idx;
        node[idx].len[h] = node[i].len[h];
        node[i].len[h] = node[idx].count;
        return rightCnt;
    }
    else {
        // (i ~ idx) 之间 < node[idx].val的有多少个
        int downCnt = addNode(i, h - 1, idx);
        if (h > node[idx].level) {
            // 该层无法设置节点
            node[i].len[h]++;
        }
        else {
            node[idx].next[h] = node[i].next[h];
            node[i].next[h] = idx;
            node[idx].len[h] = node[i].len[h] + 1 - downCnt - node[idx].count;
            node[i].len[h] = downCnt + node[idx].count;
        }
        return rightCnt + downCnt;
    }
}

void add(ll val) {
    if (find(1, UpLimit, val) != 0) {
        addCount(1, UpLimit, val);
    }
    else {
        node[++cnt].key = val;
        node[cnt].count = 1;
        node[cnt].level = randomLevel();
        addNode(1, UpLimit, cnt);
    }
}

void removeCount(int i, int h, ll val) {
    while (node[i].next[h] != 0 && node[node[i].next[h]].key < val) {
        i = node[i].next[h];
    }
    if (h == 1) {
        node[node[i].next[h]].count--;
    }
    else {
        removeCount(i, h - 1, val);
    }
    node[i].len[h]--;
}

void removeNode(int i, int h, int idx) {
    if (h < 1) {
        return;
    }
    while (node[i].next[h] != 0 && node[node[i].next[h]].key < node[idx].key) {
        i = node[i].next[h];
    }
    if (h > node[idx].level) {
        node[i].len[h]--;
    }
    else {
        node[i].next[h] = node[idx].next[h];
        node[i].len[h] += node[idx].len[h] - 1;
    }
    removeNode(i, h - 1, idx);
}

void remove(ll val) {
    int idx = find(1, UpLimit, val);
    if (idx != 0) {
        if (node[idx].count > 1) {
            removeCount(1, UpLimit, val);
        }
        else {
            removeNode(1, UpLimit, idx);
        }
    }
}

int small(int i, int h, ll val) {
    int rightCnt = 0;
    while (node[i].next[h] != 0 && node[node[i].next[h]].key < val) {
        rightCnt += node[i].len[h];
        i = node[i].next[h];
    }
    if (h == 1) {
        return rightCnt;
    }
    else {
        return rightCnt + small(i, h - 1, val);
    }
}

int rank(ll val) {// 查询排名
    return small(1, UpLimit, val) + 1;
}

ll index(int i, int h, int x) {
    int c = 0;
    while (node[i].next[h] != 0 && c + node[i].len[h] < x) {
        c += node[i].len[h];
        i = node[i].next[h];
    }
    if (h == 1) {
        return node[node[i].next[h]].key;
    }
    else {
        return index(i, h - 1, x - c);
    }
}

ll index(int x) {
    return index(1, UpLimit, x);
}

ll pre(int i, int h, ll val) {
    while (node[i].next[h] != 0 && node[node[i].next[h]].key < val) {
        i = node[i].next[h];
    }
    if (h == 1) {
        return i == 1 ? -INF : node[i].key;
    }
    else {
        return pre(i, h - 1, val);
    }
}

ll pre(ll val) {
    return pre(1, UpLimit, val);
}

ll suf(int i, int h, ll val) {
    while (node[i].next[h] != 0 && node[node[i].next[h]].key < val) {
        i = node[i].next[h];
    }
    if (h == 1) {
        if (node[i].next[h] == 0) {
            return INF;
        }
        if (node[node[i].next[h]].key > val) {
            return node[node[i].next[h]].key;
        }
        i = node[i].next[h];
        if (node[i].next[h] == 0) {
            return INF;
        }
        else {
            return node[node[i].next[h]].key;
        }
    }
    else {
        return suf(i, h - 1, val);
    }
}

ll suf(ll val) {
    return suf(1, UpLimit, val);
}
