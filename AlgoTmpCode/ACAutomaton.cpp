#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// AC自动机(以下为优化代码), 查询给定字符串中目标字符串的出现频次
// 前缀树tree(直通表)：直接维护节点u遇到字符ch应当前往的节点
// fail指针：维护拥有和当前截止字符路径的合法后缀相同的前缀节点(且长度最长), 类似kmp的next数组
// 优化：通过tree表直接维护fail指针, 避免经典AC自动机的绕路问题
// 词频统计：直接遍历查询字符, 进行单点词频累加
// 最后根据fail指针反向建图, 通过递收集子节点词频至根节点0

// 函数调用顺序 :
// insert->setFail->Get/buildTree(此二者无所谓)->f
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
