#include<bits/stdc++.h>
using namespace std;
using ld = long double;
const int MAXN = 100;
const ld eps = 1e-12;
ld mat[MAXN + 1][MAXN + 1];

// 高斯消元求解线性方程组
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


void gauss(int n) {
    cout << fixed << setprecision(16);
    for (int i = 1;i <= n;i++) {
        // 处理i行i列主元
        int maxpick = i;
        // 获取位置i最大的行
        // 注意！：若要严格区分唯一解、矛盾、多解，j < i的非主元行也要参与计算
        // 若只需判断是否存在唯一解，从第i行开始即可
        for (int j = 1;j <= n;j++) {
            if (j < i && fabsl(mat[j][j]) >= eps) {// 主元行，跳过
                continue;
            }
            if (fabsl(mat[j][i]) > fabsl(mat[maxpick][i])) {
                maxpick = j;
            }
        }
        // 交换最大行
        swap(mat[i], mat[maxpick]);
        // 存在非0最大值, 开始消元
        if (fabsl(mat[i][i]) >= eps) {
            ld tmp = mat[i][i];
            for (int j = i;j <= n + 1;j++) {
                mat[i][j] /= tmp;
            }
            for (int j = 1;j <= n;j++) {
                if (i != j) {
                    ld rate = mat[j][i] / mat[i][i];
                    for (int k = i;k <= n + 1;k++) {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }



    // 判断解的类型
    bool sign = false;
    for (int i = 1;i <= n;i++) {
        if (fabsl(mat[i][i]) < eps) {// 自由元
            if (fabsl(mat[i][n + 1]) >= eps) {
                cout << "矛盾，无解" << '\n';
                return;
            }
            else {
                sign = true;
            }
        }
    }
    if (sign) {
        cout << "多解" << '\n';
        return;
    }
    else {
        cout << "存在唯一解" << '\n';
    }
    for (int i = 1;i <= n;i++) {
        cout << mat[i][n + 1] << ' ';
    }
    cout << '\n';
}
