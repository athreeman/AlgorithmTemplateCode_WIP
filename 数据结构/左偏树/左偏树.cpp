#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 2e5;

// 左偏树：一种可并堆结构
// 堆的合并时间复杂度O(logn)
// 左偏树依赖dist值维护平衡性
// dist[i]: 从i出发到达空节点经过的最少节点数
// 左偏树的每个节点满足左儿子的dist >= 右儿子的dist
// 节点dist = 右儿子dist + 1

struct tree {
    ll val;
    int left, right;
    int dist;
    int father;// 辅助进行remove删除操作
}node[MAXN + 1];

int fa[MAXN + 1];

void prepare(int n) {
    for (int i = 0;i <= n;i++) {
        node[i] = { 0,0,0,0,0 };
        fa[i] = i;
    }
    node[0].dist = -1;
}

int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    // 维护小根堆
    // 让i成为值小的, 若值相等成为下标小的
    if (node[i].val > node[j].val || (node[i].val == node[j].val && i > j)) {
        swap(i, j);
    }
    node[i].right = merge(node[i].right, j);
    node[node[i].right].father = i;
    if (node[node[i].left].dist < node[node[i].right].dist) {
        swap(node[i].left, node[i].right);
    }
    node[i].dist = node[node[i].right].dist + 1;
    fa[node[i].left] = i;
    fa[node[i].right] = i;
    return i;
}

// 返回新树的头节点
int pop(int i) {
    fa[node[i].left] = node[i].left;
    fa[node[i].right] = node[i].right;
    int newHead = merge(node[i].left, node[i].right);
    fa[i] = newHead;
    node[i].left = node[i].right = node[i].dist = node[i].father = 0;
    return newHead;
}

int remove(int i) {
    int head = find(i);
    int f = node[i].father;
    int s = pop(i);
    node[s].father = f;

    if (head != i) {
        fa[s] = head;
        if (node[f].left == i) {
            node[f].left = s;
        }
        else {
            node[f].right = s;
        }
        for (int d = node[s].dist;node[f].dist > d + 1;f = node[f].father, d++) {
            node[f].dist = d + 1;
            if (node[node[f].left].dist < node[node[f].right].dist) {
                swap(node[f].left, node[f].right);
            }
        }
    }
    // 若i就是head, 则 = 0, fa[s] = 0
    // 若i不是head, 则s存在, 更新
    return fa[s];
}

// 把i调整为to
void update(int i, ll to) {
    int h = remove(i);
    node[i].val = to;
    fa[i] = i;
    node[i].dist = 0;
    fa[h] = fa[i] = merge(h, i);
}
