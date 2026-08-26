#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 998244353;

// 矩阵快速幂、矩阵乘法
// 往往同时用于动态规划的优化
// 矩阵快速幂时间复杂度：
// 1维k阶，k维1阶：O(logn * k ^ 3)

// 矩阵快速幂解决dp
// 核心在于把i - 1和i的严格位置依赖关系
// 转移到矩阵中去

// 矩阵乘法：前列必须等于后行，(使用引用符号，省去拷贝的耗费)
vector<vector<ll>> multiply(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<ll>>ans(n, vector<ll>(m, 0));
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < m;j++) {
            for (int c = 0;c < k;c++) {
                ans[i][j] += a[i][c] * b[c][j];
            }
        }
    }
    return ans;
}


// 矩阵快速幂：严格用于方阵，即n * n的矩阵(n >= 1)
// 此处不要使用引用符号，直接拷贝过来
vector<vector<ll>> MatPow(vector<vector<ll>> a, ll b) {
    int n = a.size();
    vector<vector<ll>>ans(n, vector<ll>(n, 0));
    for (int i = 0;i < n;i++) {// 主对角线必须为1，其他为0
        ans[i][i] = 1;
    }
    while (b) {
        if (b & 1) {
            ans = multiply(ans, a);
        }
        a = multiply(a, a);
        b >>= 1;
    }
    return ans;
}


// 例题：https://ac.nowcoder.com/acm/contest/139659/F
// 注意！：该题存在取模运算

// 关系映射, 行表示第i个位置, 列表示第i - 1个位置
// 表示在第i - 1个位置处于某种状态时, 第i个位置得到某个状态的方案数
vector<vector<ll>>A = { {1,1,0,1},
                        {1,1,1,0},
                        {0,1,1,1},
                        {1,0,1,1} };

// 初始单位状态
vector<vector<ll>>v0 = { {1},
                         {0},
                         {0},
                         {0} };

void solve() {
    ll n, r;
    cin >> n >> r;
    vector<vector<ll>>ans = multiply(MatPow(A, n), v0);
    cout << ans[r % 4][0] % mod << '\n';
}
