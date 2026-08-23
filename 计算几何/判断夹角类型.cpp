#include<bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-12;

//二维给定向量求夹角
struct point { ld x, y; };
ld dot(point a, point b) { return a.x * b.x + a.y * b.y; }
ld len(point a) { return sqrt(dot(a, a)); }


// 返回值：1 = 锐角，0 = 直角， - 1 = 钝角， - 2 = 存在零向量无法判断
int angleType(point a, point b) {
    ld la = len(a), lb = len(b);
    if (la < eps || lb < eps) return -2;   // 零向量无定义

    ld d = dot(a, b);
    if (d > eps) return 1;      // 锐角
    if (d < -eps) return -1;    // 钝角
    return 0;                   // 直角
}

// 三维
struct point3 { ld x, y, z; };
ld dot3(point3 a, point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
ld len3(point3 a) { return sqrt(dot3(a, a)); }

// 返回值：1 = 锐角，0 = 直角， - 1 = 钝角， - 2 = 存在零向量无法判断
int angleType3D(point3 a, point3 b) {
    ld la = len3(a), lb = len3(b);
    if (la < eps || lb < eps) return -2;

    ld d = dot3(a, b);
    if (d > eps) return 1;
    if (d < -eps) return -1;
    return 0;
}