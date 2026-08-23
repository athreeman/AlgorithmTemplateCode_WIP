#include<bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;
const ld eps = 1e-12;


struct point { ld x, y; };
struct Circle {
    point O;
    ld R;
};

// 三点确定一个圆
// 返回圆，若三点共线则返回一个特殊值（例如半径 -1）
Circle circleFrom3Points(point A, point B, point C) {
    ld ax = A.x, ay = A.y;
    ld bx = B.x, by = B.y;
    ld cx = C.x, cy = C.y;

    ld d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
    if (fabs(d) < 1e-12) return { {0,0}, -1 };   // 三点共线，返回半径 -1 表示失败

    ld ux = ((ax * ax + ay * ay) * (by - cy) +
        (bx * bx + by * by) * (cy - ay) +
        (cx * cx + cy * cy) * (ay - by)) / d;
    ld uy = ((ax * ax + ay * ay) * (cx - bx) +
        (bx * bx + by * by) * (ax - cx) +
        (cx * cx + cy * cy) * (bx - ax)) / d;

    ld R = hypot(ax - ux, ay - uy);
    return { {ux, uy}, R };
}

// 过点P和圆G的切点

// 需要用到的其他计算函数
point add(point a, point b) { return { a.x + b.x, a.y + b.y }; }
point sub(point a, point b) { return { a.x - b.x, a.y - b.y }; }
point mul(point a, ld k) { return { a.x * k, a.y * k }; }
ld dot(point a, point b) { return a.x * b.x + a.y * b.y; }
ld len(point a) { return sqrt(dot(a, a)); }
ld dist(point a, point b) { return len(sub(a, b)); }

// 向量逆时针旋转 theta(弧度)
// theta = 角度 * (PI / 180.0)
// PT = acos(-1.0)
point rotate(point v, ld theta) {
    ld c = cos(theta), s = sin(theta);
    return { v.x * c - v.y * s, v.x * s + v.y * c };
}

// 求过点 P 到圆 (C, r) 的切点
// 返回值：切点个数（0/1/2），切点存储在 t 数组
int tangentPoints(point P, point C, ld r, point t[2]) {
    ld d = dist(P, C);

    if (d < r - eps) return 0;          // 点在圆内，无切线
    if (fabs(d - r) < eps) {            // 点在圆上，切点就是自己
        t[0] = P;
        return 1;
    }

    point v = sub(P, C);                // C -> P
    v = mul(v, 1.0 / d);                // 单位化

    ld theta = acos(r / d);             // 旋转角
    point v1 = rotate(v, theta);
    point v2 = rotate(v, -theta);

    t[0] = add(C, mul(v1, r));          // 切点 1
    t[1] = add(C, mul(v2, r));          // 切点 2
    return 2;
}