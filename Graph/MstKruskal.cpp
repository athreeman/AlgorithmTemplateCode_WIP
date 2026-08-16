#include<bits/stdc++.h>
using namespace std;
using ll = long long;

//最小生成树,Kruskal算法
//根据边权从小到大排序
//若连接当前边不会形成环就连接,否则跳过
//达到n-1条边完成
//复杂度取决于边的个数
//点n,边m,时间复杂度O(mlogn)

//模板例题：https://www.luogu.com.cn/problem/P3366

const int MAXN = 5e3;
const int MAXM = 2e5;

array<int, 3> edge[MAXM + 1];

//并查集
int father[MAXN + 1];
int siz[MAXN + 1];
int road[MAXN + 1];

int find(int u) {
    int cnt = -1;
    while (u != father[u]) {
        road[++cnt] = u;
        u = father[u];
    }
    while (cnt >= 0) {
        father[road[cnt]] = u;
        cnt--;
    }
    return u;
}

bool merge(int u, int v) {
    int ru = find(u), rv = find(v);
    if (ru == rv)return false;
    if (siz[ru] <= siz[rv]) {
        father[ru] = rv;
        siz[rv] += siz[ru];
    }
    else {

        father[rv] = ru;
        siz[ru] += siz[rv];
    }
    return true;
}

void initial(int n) {
    //略......
}

bool cmp(array<int, 3>a, array<int, 3>b) {
    return a[2] < b[2];
}