#include<bits/stdc++.h>
using namespace std;
using ll = long long;


// 轮廓线dp
// 时间复杂度：O(n * m * 2^m)
// 普通状压：O(n * 2^m * 2^m)
// 轮廓线dp核心是把前后两行的信息压缩到一个位信息里
// 通常的，对于一个位状态s, 当处理第i个位置时, s[0...i - 1]表示当前行新做出的决策, s[i...m]表示上一行的决策
// 处理完成后, 进入i + 1, 第i个位置就是当前行的决策状态
// 普通状压：整行的位信息分开进行更新
// 轮廓线dp：依赖单一格子逐步递推
// https://www.luogu.com.cn/problem/P1879

const int mod = 1e8;

ll getMsk(ll x, int i) { return(x >> i) & 1; }//获取第i位状态
ll revMsk(ll x, int i) { return x ^ (1LL << i); }//第i位取反
ll setMsk(ll x, int i, int v) { return v == 0 ? (x & (~(1LL << i))) : (x | (1LL << i)); }//设置第i位状态

int a[12][12];
int f[12][12][1 << 12];//空间压缩
int dp[13][1 << 12];//空间压缩
int prepare[1 << 12];//辅助数组

int f1(int i, int j, int s, int n, int m) {
    if (i == n) {
        return 1;
    }
    if (j == m) {
        return f1(i + 1, 0, s, n, m);
    }
    if (f[i][j][s] != -1) {
        return f[i][j][s];
    }
    int ans = f1(i, j + 1, setMsk(s, j, 0), n, m) % mod;
    // (矩阵位置可以放)  且  (第一列 或 左边没有放)              且  (上边没有放)
    if (a[i][j] == 1 && (j == 0 || getMsk(s, j - 1) == 0) && getMsk(s, j) == 0) {
        ans = (ans + f1(i, j + 1, setMsk(s, j, 1), n, m)) % mod;
    }
    f[i][j][s] = ans;
    return ans;
}

int dp1(int n, int m) {
    int maxs = 1 << m;
    //prepare初始化为第n行的值，全是1
    fill(prepare, prepare + maxs, 1);

    for (int i = n - 1;i >= 0;i--) {
        //j==m时，直接复用下一行j=0(i+1行,j=0时)的值
        for (int s = 0;s < maxs;s++) {
            dp[m][s] = prepare[s];
        }

        //j[m-1,0]
        for (int j = m - 1;j >= 0;j--) {
            for (int s = 0;s < maxs;s++) {
                dp[j][s] = dp[j + 1][setMsk(s, j, 0)];
                if (a[i][j] == 1 && (j == 0 || getMsk(s, j - 1) == 0) && getMsk(s, j) == 0) {
                    dp[j][s] = (dp[j][s] + dp[j + 1][setMsk(s, j, 1)]) % mod;
                }
            }
        }

        //设置prepare，供上一行(i-1行)依赖
        for (int s = 0;s < maxs;s++) {
            prepare[s] = dp[0][s];
        }
    }

    return dp[0][0];
}

void solve() {
    int n, m;
    cin >> n >> m;
    int maxs = 1 << m;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < m;j++) {
            fill(f[i][j], f[i][j] + maxs, -1);
            cin >> a[i][j];
        }
    }
    // cout << f1(0, 0, 0, n, m) << '\n';
    cout << dp1(n, m) << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
