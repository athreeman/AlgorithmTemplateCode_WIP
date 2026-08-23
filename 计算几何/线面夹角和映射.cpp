#include<bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-12;

// ---------- 三维基础 ----------
struct point { ld x, y, z; };
point add(point a, point b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
point sub(point a, point b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
point mul(point a, ld k) { return { a.x * k, a.y * k, a.z * k }; }
ld dot(point a, point b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
ld len(point a) { return sqrt(dot(a, a)); }
point cross(point a, point b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// ---------- 线面夹角 ----------
// 直线方向向量 d，平面法向量 n
// 返回线面夹角（弧度），范围 [0, π/2]
ld angleLinePlane(point d, point n) {
    ld ldv = len(d), lnv = len(n);
    if (ldv < eps || lnv < eps) return 0;   // 零向量无定义

    ld sinv = fabs(dot(d, n)) / (ldv * lnv);
    if (sinv > 1) sinv = 1;
    return asin(sinv);
}

// ---------- 平面法向量（由三点确定） ----------
point normalOfPlane(point A, point B, point C) {
    return cross(sub(B, A), sub(C, A));
}

// ---------- 点到平面投影 ----------
// 点 P 到平面（过点 A，法向量 n）的投影点
point projectPointToPlane(point P, point A, point n) {
    point w = sub(P, A);
    ld s = dot(w, n) / dot(n, n);
    return sub(P, mul(n, s));
}

// ---------- 向量到平面投影 ----------
// 将向量 v 投影到法向量为 n 的平面上，得到平面内的分量
point projectVectorToPlane(point v, point n) {
    ld s = dot(v, n) / dot(n, n);
    return sub(v, mul(n, s));
}

// ---------- 直线到平面投影 ----------
// 直线 L: 过点 P0，方向向量 d
// 平面 π: 过点 A，法向量 n
// 投影直线 L' 过点 P0_proj，方向向量 d_proj
// 注意：若 d_proj 接近零向量，说明原直线垂直于平面，投影退化为一个点
void projectLineToPlane(point P0, point d, point A, point n,
    point& P0_proj, point& d_proj) {
    P0_proj = projectPointToPlane(P0, A, n);
    d_proj = projectVectorToPlane(d, n);
}