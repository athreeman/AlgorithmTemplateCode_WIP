#include<bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;
const ld eps = 1e-12;


struct point {
    ld x, y, z;
};

point add(point a, point b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

point mul(point a, ld k) {
    return { a.x * k, a.y * k, a.z * k };
}

point cross(point a, point b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

ld dot(point a, point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 三角形面片
struct Triangle {
    point a, b, c;
};

// 三维多面体质心
// 所有三角形面片，顶点顺序一致（从外部看逆时针）
point polyhedronCentroid(const vector<Triangle>& tris) {
    point C = { 0, 0, 0 };
    ld V = 0;

    for (auto [a, b, c] : tris) {
        ld vol = dot(a, cross(b, c)) / 6.0;   // 有向体积
        V += vol;

        // 四面体质心 = (0 + a + b + c) / 4
        point ci = mul(add(add(a, b), c), 1.0 / 4.0);
        C = add(C, mul(ci, vol));
    }

    if (fabs(V) < 1e-12) return { 0, 0, 0 };   // 退化
    return mul(C, 1.0 / V);
}