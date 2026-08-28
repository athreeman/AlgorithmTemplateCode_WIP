#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// 给定a, b不全为0
// d = gcd(a, b)

// ax + by = d
// 存在特解(xx, yy)
// 存在无穷解：x = xx + (b / d) * n
//            y = yy - (a / d) * n
// n为任意整数

// ax + by = c(c = d * k, k为任意整数)
// 存在特解(xx, yy)
// x1 = xx * (c / d), y1 = yy * (c / d)
// 存在无穷解：x = x1 + (b / d) * n
//            y = y1 - (a / d) * n
// n为任意整数

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

ll a, b, c, d, x, y;

// 若存在正整数解
// x取 >= 1的最小时, y取最大(>= 1的最大)
// y取 >= 1的最小时, x取最大(>= 1的最大)
// 若不存在
// x取 >= 1最小时, y < 0
// y取 >= 1最小时, x < 0

//模板：https://www.luogu.com.cn/problem/P5656
void solve() {
    cin >> a >> b >> c;
    d = gcd(a, b);
    if (c % d != 0) {
        cout << -1 << '\n';
        return;
    }
    exgcd(a, b, x, y);
    // 解
    x = x * (c / d);
    y = y * (c / d);
    // 增幅
    ll xd = b / d;
    ll yd = a / d;
    if (x <= 0) {
        ll n = (1 - x + xd - 1) / xd;
        x += n * xd;
        y -= n * yd;
    }
    else {
        ll n = (x - 1) / xd;
        x -= n * xd;
        y += n * yd;
    }
    if (y <= 0) {
        cout << x << ' ';
        ll n = (1 - y + yd - 1) / yd;
        y += n * yd;
        cout << y << '\n';
    }
    else {
        cout << ((y - 1) / yd + 1) << ' ';
        cout << x << ' ';
        cout << y - ((y - 1) / yd) * yd << ' ';
        cout << x + ((y - 1) / yd) * xd << ' ';
        cout << y << ' ';
        cout << '\n';
    }
}
