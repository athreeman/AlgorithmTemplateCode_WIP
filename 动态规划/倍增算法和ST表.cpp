#include<bits/stdc++.h>
using namespace std;
using ll = long long;
//倍增表和倍增算法的理解核心：
//1、二进制的可拆分性
//2、二进制数学上天然的必然可组合性
//3、维护信息的可合并性
//4、动态规划的思想

//倍增表维护环状最短路问题
//https://www.luogu.com.cn/problem/P4155
const int MAXN = 2e5;
struct node {
    int idx;
    int st, ed;
}line[2 * MAXN + 1];
int stjump[2 * MAXN + 1][32];
int power = 32;
int ans[MAXN + 1];

//建立倍增表,核心代码
void buildStjump(int n) {
    power = ceil(log2(n));
    int e = n << 1;//line的数量
    for (int i = 1, arrive = 1;i <= e;i++) {//arrive可抵达的line编号
        while (arrive + 1 <= e && line[arrive + 1].st <= line[i].ed) {
            arrive++;//若可达
        }
        stjump[i][0] = arrive;
    }
    for (int p = 1;p <= power;p++) {
        for (int i = 1;i <= e;i++) {
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
        }
    }
}

int jump(int i, int m) {
    int aim = line[i].st + m;
    int cur = i, nxt, ans = 1;
    for (int p = power;p >= 0;p--) {
        nxt = stjump[cur][p];
        if (nxt != 0 && line[nxt].ed < aim) {
            ans += (1 << p);
            cur = nxt;
        }
    }
    return ans + 1;//stjump[cur][0],最后一步
}

bool cmp(node a, node b) {
    return a.st < b.st;
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1;i <= n;i++) {
        cin >> line[i].st >> line[i].ed;
        line[i].idx = i;
        if (line[i].st > line[i].ed) {
            line[i].ed += m;
        }
    }
    sort(line + 1, line + n + 1, cmp);
    for (int i = 1;i <= n;i++) {
        line[i + n] = line[i];
        line[i + n].st += m;
        line[i + n].ed += m;
    }
    buildStjump(n);
    for (int i = 1;i <= n;i++) {
        ans[line[i].idx] = jump(i, m);
    }
    for (int i = 1;i <= n;i++) {
        cout << ans[i] << ' ';
    }
}