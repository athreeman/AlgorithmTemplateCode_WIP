#include<bits/stdc++.h>
using namespace std;

class Mat_pos {
    //矩阵快速幂
private:
    using ll = long long;
    const static int mod = 1e9 + 7;

    //例题1数据：
    const static int MAXN = 1000;
    ll f[MAXN + 1] = { 0,1,2,5 };
    vector<vector<ll>>arr = { {5,2,1} };
    vector<vector<ll>>mat = { {2,1,0},
                            {0,0,1},
                            {1,0,0} };


    //例题2数据：
    const static int MAXM = 1e5;
    const static int f01 = 3;
    vector<vector<ll>>arr02 = { {1,1,0,1,0,0} };
    vector<vector<ll>>mat02 = { {1,1,0,1,0,0},
                           {1,0,1,1,0,0},
                           {1,0,0,1,0,0},
                           {0,0,0,1,1,0},
                           {0,0,0,1,0,1},
                           {0,0,0,1,0,0} };
    //矩阵快速幂
    //解决固定关系,严格应用于方阵
    //复杂度O(log2n*k的3次幂)

    //矩阵相乘
    //二维矩阵
    vector<vector<ll>> multiply(vector<vector<ll>>a, vector<vector<ll>>b) {
        int n = a.size();//前行
        int m = b[0].size();//后列
        int k = a[0].size();//前列
        vector<vector<ll>>ans(n, vector<ll>(m));
        for (int i = 0;i < n;i++) {
            for (int j = 0;j < m;j++) {
                for (int c = 0;c < k;c++) {
                    ans[i][j] = (ans[i][j] + (a[i][c] * b[c][j]) % mod) % mod;
                }
            }
        }
        return ans;
    }

    //矩阵快速幂
    vector<vector<ll>> Pow_Mat(vector<vector<ll>>m, ll p) {
        int n = m.size();//行
        vector<vector<ll>>ans(n, vector<ll>(n));
        for (int i = 0;i < n;i++) {
            ans[i][i] = 1;
        }
        while (p) {
            if (p & 1) {
                ans = multiply(ans, m);
            }
            m = multiply(m, m);
            p >>= 1;
        }
        return ans;
    }

    //f(n,h)h=0,1
    //表示2*n的矩阵+边角1格的方案数
    //一型即水平或竖直两格,二型即L状三格
    int f1(int n, int h) {
        if (n == 0) {
            return h == 0 ? 1 : 0;
        }
        if (n == 1) {
            return 1;
        }
        if (h == 1) {
            //边角分别放二型,一型
            return f1(n - 1, 0) + f1(n - 1, 1);
        }
        else {
            //边角分别放竖直一型,两个水平一型,一个二型
            return f1(n - 1, 0) + f1(n - 2, 0) + 2 * f1(n - 2, 1);
        }
    }

    ll num = 0;
    void f2(int n, string s, int cntA) {
        if (cntA >= 2)return;
        if (n == 0) {
            int A = 0;
            for (int i = 0;i < s.size();i++) {
                if (i + 2 < s.size()) {
                    if (s[i] == 'L' && s[i + 1] == 'L' && s[i + 2] == 'L') {
                        return;
                    }
                }
                if (s[i] == 'A')A++;
            }
            if (A < 2) {
                num++;
            }
            return;
        }
        f2(n - 1, s + 'A', cntA + 1);
        f2(n - 1, s + 'L', 0);
        f2(n - 1, s + 'P', 0);
    }

public:

    //斐波那契数列快速幂:(1维2阶)
    //int a[][]={{1,1},{1,0}};
    //{f[n],f[n-1]}={{f[1],f[0]}}*Pow_Mat(a,n-1);

    ll Mat_pow_1_k(int n) {
        //解决1维k阶
        //例题：https://leetcode.cn/problems/domino-and-tromino-tiling/description/
        //暴力打表找规律,函数f1(n,0)
        //f[i]=2*f[i-1]+f[i-3]
        //{f[i+1],f[i],f[i-1]}={f[i],f[i-1],f[i-2]}*{{2,0,1},{1,0,0},{0,1,0}};

        vector<vector<ll>>ans;
        if (n <= 3) {
            return f[n];
        }
        else {
            ans = multiply(arr, Pow_Mat(mat, ll(n - 3)));
        }
        return ans[0][0];
    }

    ll Mat_pow_k_1(int n) {
        //解决k维1阶
        //例题：https://leetcode.cn/problems/student-attendance-record-ii/description/
        if (n <= 1) {
            return f01;
        }
        else {
            vector<vector<ll>>ans;
            ans = multiply(arr, Pow_Mat(mat, n - 1));
            ll res = 0;
            for (int i = 0;i < 6;i++) {
                res = (res + ans[0][i]) % mod;
            }
            return res;
        }
    }
};
