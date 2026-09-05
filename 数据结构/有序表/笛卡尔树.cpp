#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ill = __int128_t;

// 笛卡尔树:
// 笛卡尔树的核心在于:
// 1、根据每个元素i的特征值a[i]天然维护该特征值的单调顺序
// 2、中序遍历的结果就是元素i插入的顺序

// 特征: 
// 每个节点存储value
// 节点编号就是key
// 节点编号按照搜索二叉树 左<根<右 组织
// value满足每颗子树的头节点是最大/最小值
// 整棵树维护广义上的(大/小根)堆结构

// 建树过程依赖单调栈:
// 按照key的值升序遍历, 若压入栈, 则作为压住的元素(即旧的栈顶)的右儿子
// 若弹出节点, 记录最后弹出的节点编号, 作为新入栈节点的左儿子

const int MAXN = 1e7;
ll a[MAXN + 1];
int head = 0;
struct {
    ll value;
    int left, right;
}node[MAXN + 1];

void link(int i, int fa, int side) {
    // i连接到fa的side侧
    if (side == 1) {
        node[fa].left = i;
    }
    else {
        node[fa].right = i;
    }
}

void clear(int n) {
    head = 0;
    for (int i = 1;i <= n;i++) {
        node[i] = { 0,0,0 };
    }
}

void build(int n) {
    clear(n);
    stack<pair<int, ll>>sta;
    for (int i = 1;i <= n;i++) {
        node[i].value = a[i];
        if (!sta.size()) {
            head = i;
            sta.push({ i,a[i] });
        }
        else {
            if (sta.top().second < a[i]) {
                link(i, sta.top().first, 2);
            }
            else {
                int last = 0;// 最后出栈的节点
                while (sta.size() && sta.top().second > a[i]) {
                    last = sta.top().first;
                    sta.pop();
                }
                if (sta.size()) {
                    link(i, sta.top().first, 2);
                }
                else {
                    head = i;
                }
                link(last, i, 1);
            }
            sta.push({ i,a[i] });
        }
    }
}
