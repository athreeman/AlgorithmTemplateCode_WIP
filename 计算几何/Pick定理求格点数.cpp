#include<bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;

// 给定线段(x1, y1), (x2, y2)
// 线段上过的格点数 = gcd(| x1 - x2 | , | y1 - y2 | )
// (包括端点)

// 多边形面积：S
// 边上格点数：B
// 内部格点数：I
// S = I + B / 2 - 1

// 其中求面积可以用鞋带定理

struct pointll {
    ll x, y;
};
ll crossLL(pointll a, pointll b) {
    return a.x * b.y - a.y * b.x;
}

// S = I + B / 2 - 1
// pick定理获取边界格点数
// 边界格点数 B：每条边贡献 gcd(|dx|, |dy|) 个点（只算起点不算终点）
// 注意：此处用整数二倍运算，避免精度问题
ll boundaryPoints(const vector<pointll>& p) {
    int n = p.size();
    ll B = 0;
    for (int i = 0; i < n; i++) {
        pointll a = p[i], b = p[(i + 1) % n];
        ll dx = llabs(a.x - b.x);
        ll dy = llabs(a.y - b.y);
        B += std::gcd(dx, dy);
    }
    return B;
}
