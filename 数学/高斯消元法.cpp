#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double;
//高斯消元法求解方程组

// 高斯消元法,复杂度O(n^3)
// 1.存在自由元,值!=0矛盾无解
// 2.存在自由元,值==0多解
// 3.不存在自由元,全是主元,唯一解
// 主元只可以依赖自由元，自由元不依赖任何其他元
// 线性，异或，同余方程组都是如此


ll inv[3000001];
//逆元的线性递推
void initial_inv(ll n, ll p) {
    //详见数论NumberTheory....
}
ll gcd(ll a, ll b) {
    //略......
}

//普通线性方程组
class gaussLinear {
private:

    const ld eps = 1e-7;
    ld mat[101][102];

    void gauss(int n) {
        cout << fixed << setprecision(12);
        for (int i = 1;i <= n;i++) {
            int max_idx = i;

            for (int j = 1;j <= n;j++) {
                if (j < i && fabs(mat[j][j]) >= eps) {
                    //主元跳过
                    continue;
                }
                if (fabs(mat[j][i]) > fabs(mat[max_idx][i])) {
                    //获取最大行,线性方程组获取最大值
                    max_idx = j;
                }
            }

            //交换
            swap(mat[max_idx], mat[i]);
            if (fabs(mat[i][i]) >= eps) {//>0
                ld tmp = mat[i][i];

                //当前主元变1,主元所在行也随着变
                for (int j = 1;j <= n + 1;j++) {
                    mat[i][j] /= tmp;
                }

                //当前列,变0
                for (int j = 1;j <= n;j++) {
                    if (i != j) {
                        ld rate = mat[j][i] / mat[i][i];
                        for (int k = i;k <= n + 1;k++) {//处理行
                            mat[j][k] -= mat[i][k] * rate;
                        }
                    }
                }
            }
            else {//自由元,非唯一解
                continue;
            }
        }

        for (int i = 1;i <= n;i++) {
            if (fabs(mat[i][n + 1]) < eps)mat[i][n + 1] = 0;
            cout << mat[i][n + 1] << '\n';
        }
        return;
    }
};

//异或方程组
class gaussXor {
private:

    const static int MAXN = 2e3;
    bitset<1> mat[MAXN + 1][MAXN + 2];

    void gauss(int n) {
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= n;j++) {
                if (j < i && mat[j][j] == 1) {
                    //主元跳过
                    continue;
                }
                if (mat[j][i] == 1) {//发现1,交换
                    swap(mat[j], mat[i]);
                    break;
                }
            }
            if (mat[i][i] == 1) {
                for (int j = 1;j <= n;j++) {
                    if (j != i && mat[j][i] == 1) {
                        for (int k = 1;k <= n + 1;k++) {
                            mat[j][k] ^= mat[i][k];
                        }
                    }
                }
            }
            else {//存在自由元,多解
                continue;
            }
        }
    }

};


//同余方程组
class gaussMod {
    //a ≡ b ≡ c (mod p)
    //-a % mod =( mod - a ) % mod 同余方程组需要该转换
private:
    using ll = long long;
    static Mat[1001][1001];
    const static int mod = 3;
    static int arr[31][31];
    int idx = 0;
    int cnt = 0;
    pair<int, int>dir[4] = { {0,-1},{0,1},{1,0},{-1,0} };

    void gauss(int n) {
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= n;j++) {
                if (j < i && Mat[j][j] != 0) {
                    //主元,跳过
                    continue;
                }
                if (Mat[j][i] != 0) {
                    swap(Mat[i], Mat[j]);
                    break;
                }
            }
            if (Mat[i][i] != 0) {
                //处理
                for (int j = 1;j <= n;j++) {
                    if (j != i && Mat[j][i] != 0) {
                        int g = gcd(Mat[j][i], Mat[i][i]);
                        int a = Mat[i][i] / g;
                        int b = Mat[j][i] / g;
                        if (j < i && Mat[j][j] != 0) {
                            for (int k = 1;k < i;k++) {
                                Mat[j][k] = Mat[j][k] * a % mod;
                            }
                        }
                        for (int k = i;k <= n + 1;k++) {
                            Mat[j][k] = ((Mat[j][k] * a - Mat[i][k] * b) % mod + mod) % mod;
                        }
                    }
                }
            }
        }
    }

};