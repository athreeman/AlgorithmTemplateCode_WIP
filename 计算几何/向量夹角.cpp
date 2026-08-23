#include<bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-12;

//二维给定向量求夹角
struct point { ld x, y; };
ld dot(point a, point b) { return a.x * b.x + a.y * b.y; }
ld len(point a) { return sqrt(dot(a, a)); }

// 返回向量 a 和 b 的夹角（弧度，范围 [0, π]）
ld angleBetween(point a, point b) {
    ld la = len(a), lb = len(b);
    if (la < eps || lb < eps) return 0;   // 零向量无定义，按需处理

    ld cosv = dot(a, b) / (la * lb);

    // 防止浮点误差导致 cosv 超出 [-1, 1]
    if (cosv > 1) cosv = 1;
    if (cosv < -1) cosv = -1;

    return acos(cosv);
}


// 三维
struct point3 { ld x, y, z; };
ld dot3(point3 a, point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
ld len3(point3 a) { return sqrt(dot3(a, a)); }

// 返回向量 a 和 b 的夹角（弧度，范围 [0, π]）
ld angleBetween3D(point3 a, point3 b) {
    ld la = len3(a), lb = len3(b);
    if (la < eps || lb < eps) return 0;   // 零向量无定义

    ld cosv = dot3(a, b) / (la * lb);

    // 防止浮点误差导致 cosv 超出 [-1, 1]
    if (cosv > 1) cosv = 1;
    if (cosv < -1) cosv = -1;

    return acos(cosv);
}