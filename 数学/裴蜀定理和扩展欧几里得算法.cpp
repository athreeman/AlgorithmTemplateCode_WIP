#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 裴蜀定理:
// 如果a, b是不全为0的整数, 则一定存在整数x, y, 使得ax + by = gcd(a, b)
// 注意：其中的x, y只要满足整数即可
// a和b的最大公约数 = ax 和 by, 随意给定的整数x, y, 能取得的最小正数差值
// 推论：
// 1、若a, b是不全为0的整数, a, b互质, 当且仅当存在整数x, y, 使得ax + by = 1
// 2、若a, b是不全为0的整数, 并且ax + by = c有解, 那么c一定是gcd(a, b)的整数倍(0倍也算)
// 3、a和b两项的裴蜀定理, 可以推广到多项的情况
// 例, ax + by + cz = g * k, 其中g = gcd(a, b, c), k >= 0, 一定存在x, y, z的解


// 扩展欧几里得算法:
// 给定ax + by = c, c是gcd(a, b)的倍数
// g = gcd(a, b)
// exgcd求解x, y的一组特解x0, y0
// 该特解x0, y0是ax + by = gcd(a, b)时的解
// 当前公式ax + by的解：(xx, yy) = (x0 * (c / d), y0 * (c / d))
// 通解：x = x0 + (b / d) * n, y = y0 - (a / d) * n
// 其中x的最小非负解minx = x0 * (c / d) % (b / d)
// 时间复杂度O((logmin(a, b)) ^ 3)
// 注意：传入的a, b不能出现负数
ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    else {
        ll g = exgcd(b, a % b, x, y);
        ll tmp = y;
        y = x - y * (a / b);
        x = tmp;
        return g;
    }
}
