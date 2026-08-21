#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// AC自动机(优化版)：统计目标串在查询串中的出现次数
// tree(直通表)：Trie转移表，直接存节点遇到字符后应跳到的节点，已融合fail，避免回跳
// fail：指向当前路径最长合法后缀对应的前缀节点，类似KMP的next
// (维护拥有和当前截止字符路径的合法后缀相同的前缀节点(且长度最长), 类似kmp的next数组)
// 统计：遍历查询串，对到达节点累加计数
// 汇总：按fail反向建图，自底向上累加计数到根节点

// AC自动机可以实现除收集词频以外的功能,可根据题目定制
// 例:alert(bool报警发现目标信息,该信息可延fail传递
// 其核心是根据目标串建立tree直通表,然后再构建fail表

// 调用顺序：insert -> setFail -> buildTree/查询
// 复杂度：O(S+T+L)
// S=查询串长，T=目标串总长，L=tree节点数
// 模板例题：https ://www.luogu.com.cn/problem/P5357

const int MAXN = 2e5;
const int MAXS = 2e6;

int ed[MAXN + 1];//每个目标字符的结尾位置
int fail[MAXS + 1];//fail指针
int times[MAXS + 1];//词频
int tree[MAXS + 1][26];//tree直通表
int head[MAXS + 1];//建图
int nxt[MAXS + 1];
int to[MAXS + 1];
int idx = 0;
int cnt = 0;

void addEdge(int u, int v) {//建图
    nxt[++idx] = head[u];
    head[u] = idx;
    to[idx] = v;
}
void insert(int i, string s) {//前缀树tree插入字符串
    int cur = 0;
    for (char ch : s) {
        int path = ch - 'a';
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
        }
        cur = tree[cur][path];
    }
    ed[i] = cur;
}
void setFail() {//设置fail指针和tree直通表
    queue<int>q;
    fail[0] = 0;
    for (int path = 0;path <= 25;path++) {
        if (tree[0][path] > 0) {
            fail[tree[0][path]] = 0;
            q.push(tree[0][path]);
        }
    }
    while (q.size()) {
        int cur = q.front();
        q.pop();
        for (int path = 0;path <= 25;path++) {
            if (tree[cur][path] == 0) {
                tree[cur][path] = tree[fail[cur]][path];
            }
            else {
                fail[tree[cur][path]] = tree[fail[cur]][path];
                q.push(tree[cur][path]);
            }
        }
    }
}
void buildTree(int n) {//建立fail反向图
    for (int i = 1;i <= n;i++) {
        addEdge(fail[i], i);
    }
}
void Get(string s) {//读入大文章,获取初始单点词频
    int cur = 0;
    for (char ch : s) {
        int path = ch - 'a';
        cur = tree[cur][path];
        times[cur]++;
    }
}
void f(int cur) {//递归统计真实词频
    for (int edge = head[cur];edge > 0;edge = nxt[edge]) {
        f(to[edge]);
        times[cur] += times[to[edge]];
    }
}
