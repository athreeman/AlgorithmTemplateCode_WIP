#include<bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-12;


//二维，点线映射
struct point { ld x, y; };
point add(point a, point b) { return { a.x + b.x, a.y + b.y }; }
point sub(point a, point b) { return { a.x - b.x, a.y - b.y }; }
point mul(point a, ld k) { return { a.x * k, a.y * k }; }
ld dot(point a, point b) { return a.x * b.x + a.y * b.y; }

// 点 P 在直线 AB 上的投影点（A != B）
point projectToLine2D(point P, point A, point B) {
    point v = sub(B, A);
    point w = sub(P, A);
    ld t = dot(w, v) / dot(v, v);
    return add(A, mul(v, t));
}

//三维，点线映射
struct point3 { ld x, y, z; };
point3 add3(point3 a, point3 b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
point3 sub3(point3 a, point3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
point3 mul3(point3 a, ld k) { return { a.x * k, a.y * k, a.z * k }; }
ld dot3(point3 a, point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

// 点 P 在直线 AB 上的投影点（A != B）
point3 projectToLine3D(point3 P, point3 A, point3 B) {
    point3 v = sub3(B, A);
    point3 w = sub3(P, A);
    ld t = dot3(w, v) / dot3(v, v);
    return add3(A, mul3(v, t));
}

//三维，点面映射
point3 cross3(point3 a, point3 b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// 点 P 在平面 ABC 上的投影点（A, B, C 不共线）
point3 projectToPlane3D(point3 P, point3 A, point3 B, point3 C) {
    point3 n = cross3(sub3(B, A), sub3(C, A));   // 法向量
    point3 w = sub3(P, A);
    ld s = dot3(w, n) / dot3(n, n);
    point3 offset = mul3(n, s);
    return sub3(P, offset);    // P - n * s
}