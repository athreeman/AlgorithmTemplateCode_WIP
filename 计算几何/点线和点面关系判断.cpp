#include<bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-12;

// 二维点线判断

struct point { ld x, y; };
point cal(point a, point b) { return { a.x - b.x, a.y - b.y }; }
ld cross(point a, point b) { return a.x * b.y - a.y * b.x; }

// 返回 >0 表示左侧，<0 表示右侧，0 在线上
int sideOfLine(point P, point A, point B) {
    ld d = cross(cal(B, A), cal(P, A));
    if (d > eps) return 1;      // 左侧
    if (d < -eps) return -1;    // 右侧
    return 0;                   // 线上
}



//三维点面判断

struct point3 { ld x, y, z; };
point3 cal3(point3 a, point3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
point3 cross3(point3 a, point3 b) {
    return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}
ld dot3(point3 a, point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

// 返回 >0 表示法向量同侧，<0 表示法向量异侧，0 在平面上
int sideOfPlane(point3 P, point3 A, point3 B, point3 C) {
    point3 n = cross3(cal3(B, A), cal3(C, A));  // 平面法向量
    ld d = dot3(n, cal3(P, A));
    if (d > eps) return 1;      // 法向量同侧
    if (d < -eps) return -1;    // 法向量异侧
    return 0;                   // 平面上
}