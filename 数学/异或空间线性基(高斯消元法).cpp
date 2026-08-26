#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 2e5;
const int bit = 60;


// ！！注意！！
// 由于高斯消元需要拷贝原始数组，需要设置较大内存
ll basis[MAXN + 1];
ll a[MAXN + 1];
bool zero = false;
int len;// 线性基的大小

// 基：可以表示原空间所有元素的一组极小线性无关组(不唯一)
// 普通消元法或高斯消元法

// 高斯消元求解线性基是高斯消元求解方程组的阉割版本
// 1、不需要给自由元留位置 2、不需要主元和自由元的依赖关系
// 时间复杂度O(nlogV), V是最大值

// 若线性基大小 = m，则原始异或和共有2 ^ m - 1种
// 最大异或和：从高位开始贪心，异或和可以变大则异或，否则不异或
// 第k小异或和，拆解k的二进制位，求异或和

void gauss(int n) {
    len = 1;
    for (int i = bit;i >= 0;i--) {
        for (int j = len;j <= n;j++) {
            if (basis[j] & (1LL << i)) {
                swap(basis[j], basis[len]);
                break;
            }
        }
        if (basis[len] & (1LL << i)) {
            for (int j = 1;j <= n;j++) {
                if (j != len && (basis[j] & (1LL << i))) {
                    basis[j] ^= basis[len];
                }
            }
            len++;
        }
    }
    len--;
    zero = len != n;
}

void buildBasis(ll* arr, int n) {
    zero = false;
    for (int i = 1;i <= n;i++) {
        basis[i] = arr[i];
    }
    gauss(n);
}

// 第k小非空异或和
ll GetXorKth(ll k) {
    if (k == 1 && zero) {
        return 0;
    }
    if (zero) {
        k = k - 1;
    }
    if (k >= (1LL << len)) {
        return -1;
    }
    ll ans = 0;
    for (int i = len, j = 0;i >= 1;i--, j++) {
        if ((k & (1LL << j))) {
            ans ^= basis[i];
        }
    }
    return ans;
}

// 最大异或和
ll GetXorMax() {
    ll res = 0;
    for (int i = 1;i <= len;i++) {
        res = max(res, res ^ basis[i]);
    }
    return res;
}
