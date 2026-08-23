#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// 二维
struct point { ld x, y; };

// 直线 AB 的法向量（不唯一，任取一个）
point normal2D(point A, point B) {
    point v = {B.x - A.x, B.y - A.y};
    return {-v.y, v.x};   // 或 {v.y, -v.x}
}


// 三维
struct point3 { ld x, y, z; };

point3 cross(point3 a, point3 b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

point3 cal(point3 a, point3 b) {   // a - b
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

// 平面 ABC 的法向量（A,B,C 不共线）
point3 normal3D(point3 A, point3 B, point3 C) {
    return cross(cal(B, A), cal(C, A));
}