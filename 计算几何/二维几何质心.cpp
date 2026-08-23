#include<bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;
const ld eps = 1e-12;

struct point { ld x, y; };
ld cross(point a, point b) { return a.x * b.y - a.y * b.x; }

// 返回多边形质心，顶点按边界顺序排列
point polygonCentroid(const vector<point>& p) {
    int n = p.size();
    if (n < 3) return { 0, 0 };   // 退化情况

    ld A = 0, cx = 0, cy = 0;
    for (int i = 0; i < n; i++) {
        point a = p[i];
        point b = p[(i + 1) % n];
        ld cr = cross(a, b);      // 有向面积的两倍
        A += cr;
        cx += (a.x + b.x) * cr;
        cy += (a.y + b.y) * cr;
    }
    A /= 2;                       // 有向面积
    if (fabs(A) < eps) return { 0, 0 }; // 面积为 0，质心不存在

    return { cx / (6 * A), cy / (6 * A) };
}