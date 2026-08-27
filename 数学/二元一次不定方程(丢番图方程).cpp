#include<bits/stdc++.h>
using namespace std;

// 给定a, b不全为0
// d = gcd(a, b)

// ax + by = d
// 存在特解(x0, y0)
// 存在无穷解：x = x0 + (b / d) * n
//            y = y0 - (a / d) * n
// n为任意整数

// ax + by = c(c = d * k, k为任意整数)
// 存在特解(x0, y0)
// x1 = x0 * (c / d), y1 = y0 * (c / d)
// 存在无穷解：x = x1 + (b / d) * n
//            y = y1 - (a / d) * n
// n为任意整数
