#include<bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-12;

// ---------- 二维 ----------
struct point {
    ld x, y;
};

point add(point a, point b) { return { a.x + b.x, a.y + b.y }; }
point sub(point a, point b) { return { a.x - b.x, a.y - b.y }; }
point mul(point a, ld k) { return { a.x * k, a.y * k }; }
ld dot(point a, point b) { return a.x * b.x + a.y * b.y; }
ld len(point a) { return sqrt(dot(a, a)); }
ld cross(point a, point b) { return a.x * b.y - a.y * b.x; }

// 二维两直线夹角（方向向量 v1, v2）

ld angleBetweenLines2D(point v1, point v2) {
    ld la = len(v1), lb = len(v2);
    if (la < eps || lb < eps) return 0;   // 零向量无定义
    ld cosv = dot(v1, v2) / (la * lb);
    if (cosv > 1) cosv = 1;
    if (cosv < -1) cosv = -1;
    return acos(cosv);
}

// 二维两直线交点

// 直线1由 A1,B1 确定，直线2由 A2,B2 确定
// 返回 0：正常一个交点（通过 res 返回）
// 返回 1：平行无交点
// 返回 2：共线无穷交点
int intersectLines2D(point A1, point B1, point A2, point B2, point& res) {
    point v1 = sub(B1, A1);
    point v2 = sub(B2, A2);
    ld d = cross(v1, v2);

    if (fabs(d) < eps) {
        // 平行或共线
        if (fabs(cross(sub(A2, A1), v1)) < eps) return 2;   // 共线
        return 1;                                           // 平行无交点
    }

    point w = sub(A2, A1);
    ld t = cross(w, v2) / d;
    res = add(A1, mul(v1, t));
    return 0;
}

// ---------- 三维 ----------
struct point3 {
    ld x, y, z;
};

point3 add3(point3 a, point3 b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
point3 sub3(point3 a, point3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
point3 mul3(point3 a, ld k) { return { a.x * k, a.y * k, a.z * k }; }
ld dot3(point3 a, point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
ld len3(point3 a) { return sqrt(dot3(a, a)); }
point3 cross3(point3 a, point3 b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// 三维两直线夹角（方向向量 v1, v2）

ld angleBetweenLines3D(point3 v1, point3 v2) {
    ld la = len3(v1), lb = len3(v2);
    if (la < eps || lb < eps) return 0;
    ld cosv = dot3(v1, v2) / (la * lb);
    if (cosv > 1) cosv = 1;
    if (cosv < -1) cosv = -1;
    return acos(cosv);
}

// 三维两直线最短距离(公垂线段)及最近点对

// 直线1由 A1,B1 确定，直线2由 A2,B2 确定
// 返回最短距离，最近点通过 p1,p2 返回
ld distanceLines3D(point3 A1, point3 B1, point3 A2, point3 B2, point3& p1, point3& p2) {
    point3 v1 = sub3(B1, A1);
    point3 v2 = sub3(B2, A2);
    point3 w = sub3(A2, A1);

    point3 n = cross3(v1, v2);
    ld nlen = len3(n);

    if (nlen > eps) {
        // 异面直线：公垂线法
        ld s = dot3(cross3(w, v2), n) / (nlen * nlen);
        ld t = dot3(cross3(w, v1), n) / (nlen * nlen);

        p1 = add3(A1, mul3(v1, s));
        p2 = add3(A2, mul3(v2, t));
        return len3(sub3(p1, p2));
    }
    else {
        // 两直线平行：取 A2 到直线1 的投影
        p1 = A2;
        point3 v = v1;
        point3 ap = sub3(A2, A1);
        ld t = dot3(ap, v) / dot3(v, v);
        p2 = add3(A1, mul3(v, t));
        return len3(sub3(p1, p2));
    }
}