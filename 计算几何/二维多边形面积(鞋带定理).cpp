#include<bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;

// 二维
struct point {
    ld x, y;
};
ld cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

// 三角形面积：已知三边（海伦公式）
ld triangleAreaBySides(ld a, ld b, ld c) {
    ld p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// 三角形面积：已知顶点坐标
ld triangleAreaByPoints(point A, point B, point C) {
    return fabs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2.0;
}

// 多边形面积：鞋带公式，顶点按顺序(逆时针或顺时针，凸凹均可)
ld polygonArea(const vector<point>& p) {
    int n = p.size();
    if (n < 3) return 0;
    ld area = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return fabs(area) / 2.0;
}


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
