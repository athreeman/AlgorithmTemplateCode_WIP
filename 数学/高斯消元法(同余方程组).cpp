#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 100;
const int MOD = 7;;
// 逆元线性递推，获取逆元表
ll inv[MOD + 1];
ll mat[MAXN + 1][MAXN + 1];
void inv_(int mod) {
    inv[1] = 1;
    for (int i = 2;i < mod;i++) {
        inv[i] = (int)(mod - (ll)inv[mod % i] * ll(mod / i) % mod);
    }
}
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}


// 高斯消元求解同余方程组
// 时间复杂度O(n ^ 3)
// 主元依赖自由元，自由元不依赖任何其他元
// 唯一解：存在 n 个主元（即所有列都是主元列）
// 多解：存在自由元，且所有自由元所在行均为 0 = 0
// 矛盾：存在自由元所在行为 0 = b(b != 0)

// n个变量，n个表达式
// 第n + 1列是值
// 若方程数不足 n，需补全零元；若方程冗余（线性相关），消元后自然产生自由元
// 检查解时，只需要检查实际变量个数n的行[1, n]

// 处理i行i列主元时
// 注意！：若要严格区分唯一解、矛盾、多解，j < i的非主元行也要参与计算
// 若只需判断是否存在唯一解，从第i行开始即可


// ！！！注意！！！
// 所有系数若读入负数，使用以下公式保证gauss消元初始系数都是正数
// -a % mod = (-a % mod + mod) % mod

void gauss(int n, int mod) {
    for (int i = 1;i <= n;i++) {
        // 处理i行i列主元
        // 获取位置i等于1的行
        // ！注意！：若要严格区分唯一解、矛盾、多解，j < i的非主元行也要参与计算
        // 若只需判断是否存在唯一解，从第i行开始即可
        for (int j = 1;j <= n;j++) {
            if (j < i && mat[j][j] != 0) {// 主元行，跳过
                continue;
            }
            if (mat[j][i] != 0) {// 对于同余方程组，只要发现非0值直接交换
                swap(mat[i], mat[j]);
                break;
            }
        }
        if (mat[i][i] != 0) {
            for (int j = 1;j <= n;j++) {
                if (i != j && mat[j][i] != 0) {
                    ll g = gcd(mat[j][i], mat[i][i]);
                    ll a = mat[i][i] / g;
                    ll b = mat[j][i] / g;

                    if (j < i && mat[j][j] != 0) {
                        // ！！注意！！
                        // 若j行存在主元，从j到i - 1列所有系数 * a
                        // 维护正确的主元和自由元的关系
                        for (int k = j;k < i;k++) {
                            mat[j][k] = (mat[j][k] * a) % mod;
                        }
                    }
                    //正常消元
                    for (int k = i;k <= n + 1;k++) {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % mod + mod) % mod;
                    }
                }
            }
        }
    }

    bool sign = false;
    // 判断解
    for (int i = 1;i <= n;i++) {
        if (mat[i][i] != 0) {
            // 主元行，判断是否被自由元影响
            bool flg = false;
            for (int j = i + 1;j <= n;j++) {
                if (mat[i][j] != 0) {
                    flg = true;
                    break;
                }
            }
            if (!flg) {
                // 不被自由元影响，确定唯一解的值
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % mod;
                mat[i][i] = 1;
            }
        }
        else {
            if (mat[i][n + 1] != 0) {
                cout << "矛盾，无解" << '\n';
                return;
            }
            sign = true;
        }
    }
    if (sign) {
        cout << "多解" << '\n';
    }
    else {
        cout << "存在唯一解" << '\n';
    }
}
