#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
// 无算数运算实现加减乘除
// 纯粹的位运算

// 溢出问题需要自行取模运算解决

// 加法：异或运算 + 与运算
// 异或运算：无进位相加
// 与运算：维护进位信息
ll add(ll a, ll b) {//   无进位相加    进位信息
    return b == 0 ? a : add(a ^ b, (a & b) << 1);
}

// 取相反数
// -b = ~b + 1
ll neg(ll b) {
    return add(~b, 1LL);
}

// 减法
// a - b = a + (-b) = a + (~b + 1)
ll minus(ll a, ll b) {
    return add(a, neg(b));
}

// 乘法
// b一定要转为无符号右移
ll multiply(ll a, ll b, ll ans) {
    return b == 0 ? ans : multiply(a << 1, (ull)b >> 1, (b & 1) ? add(ans, a) : ans);
}
ll mul(ll a, ll b) { return multiply(a, b, 0); }

// int:0~30
// long long:0~62
// 31和63是符号位
// 注意:a, b不能是LLONG_MIN(数据类型最小值)
ll divide(ll a, ll b) {
    ll x = a < 0 ? neg(a) : a;
    ll y = b < 0 ? neg(b) : b;
    ll ans = 0;//         此处::是全局命名空间,避免和std冲突
    for (int i = 62;i >= 0;i = ::minus(i, 1)) {
        if ((x >> i) >= y) {
            ans |= (1LL << i);
            x = ::minus(x, y << i);
        }
    }
    return (a < 0) ^ (b < 0) ? neg(ans) : ans;
}

// 出现数据类型最小值的除法
ll div2(ll a, ll b) {
    if (a == LLONG_MIN && b == LLONG_MIN) {
        return 1;
    }
    if (a != LLONG_MIN && b != LLONG_MIN) {
        return divide(a, b);
    }
    if (b == LLONG_MIN) {
        return 0;
    }
    // a是最小, b不是最小
    a = add(a, b > 0 ? b : neg(b));
    ll ans = divide(a, b);
    ll offset = b > 0 ? neg(1) : 1;
    return add(ans, offset);
}
