#include<bits/stdc++.h>
using namespace std;
using ld = long double;

// 二维
struct point { ld x, y; };
ld cross(point a, point b) { return a.x * b.y - a.y * b.x; }
ld dot(point a, point b) { return a.x * b.x + a.y * b.y; }
// 点 P 到直线 AB 的距离（A, B 是直线上两点，A != B）
ld pointLineDist(point P, point A, point B) {
    point v = { B.x - A.x, B.y - A.y };   // 方向向量
    point w = { P.x - A.x, P.y - A.y };   // AP 向量
    return fabs(cross(w, v)) / sqrt(dot(v, v));
}



// 三维
struct point3 { ld x, y, z; };
point3 sub(point3 a, point3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
point3 cross(point3 a, point3 b) {     // 三维叉乘
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
ld dot(point3 a, point3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
ld len(point3 a) { return sqrt(dot(a, a)); }
// 点 P 到三维直线 AB 的距离，A != B
ld pointLineDist3D(point3 P, point3 A, point3 B) {
    point3 v = sub(B, A);   // 方向向量 B - A
    point3 w = sub(P, A);   // P - A
    point3 c = cross(w, v); // 平行四边形面积向量
    return len(c) / len(v);
}