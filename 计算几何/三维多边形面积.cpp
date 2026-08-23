#include<bits/stdc++.h>
using namespace std;
using ld = long double;


// 三维：
struct point3 {
    ld x, y, z;
};
point3 cross(point3 a, point3 b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
point3 add(point3 a, point3 b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}
ld dot(point3 a, point3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
ld len(point3 a) {
    return sqrt(dot(a, a));
}
// 三维多边形面积，p 为顶点（按顺序排列，且共面）
ld polygonArea3D(vector<point3> p) {
    int n = p.size();
    if (n < 3) return 0;

    point3 N = { 0, 0, 0 };   // 面积法向量累加
    for (int i = 0; i < n; i++) {
        point3 a = p[i];
        point3 b = p[(i + 1) % n];
        N = add(N, cross(a, b));
    }
    return len(N) / 2.0;
}


// 三维空间顶点排序：
// 三维共面点排序（按逆时针顺序，基于凸包）
// 前提：输入点必须共面，且构成凸多边形（或求凸包后按凸包顶点返回）
// 输出：排序好的三维点（逆时针），可直接用于 polygonArea3D
vector<point3> sortPoints3D(vector<point3> p) {
    int n = p.size();
    if (n <= 3) return p;  // 三角形直接返回

    // 1. 计算多边形所在平面的法向量（Newell 法）
    point3 N = { 0, 0, 0 };
    for (int i = 0; i < n; i++) {
        point3 a = p[i];
        point3 b = p[(i + 1) % n];
        N = add(N, cross(a, b));
    }

    // 2. 选择投影平面：忽略法向量中绝对值最大的分量
    int dropAxis;
    if (fabs(N.x) >= fabs(N.y) && fabs(N.x) >= fabs(N.z)) dropAxis = 0;      // 忽略 x
    else if (fabs(N.y) >= fabs(N.z)) dropAxis = 1;                           // 忽略 y
    else dropAxis = 2;                                                       // 忽略 z

    // 3. 投影到二维
    vector<pair<ld, ld>> pts2D(n);
    for (int i = 0; i < n; i++) {
        if (dropAxis == 0) pts2D[i] = { p[i].y, p[i].z };
        else if (dropAxis == 1) pts2D[i] = { p[i].x, p[i].z };
        else pts2D[i] = { p[i].x, p[i].y };
    }

    // 4. 在二维上求凸包（Andrew 算法），返回点的索引
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        if (pts2D[i].first != pts2D[j].first) return pts2D[i].first < pts2D[j].first;
        return pts2D[i].second < pts2D[j].second;
        });

    vector<int> hullIdx;
    // 下凸包
    for (int i : idx) {
        while (hullIdx.size() >= 2) {
            int m = hullIdx.size();
            auto v1 = make_pair(pts2D[hullIdx[m - 1]].first - pts2D[hullIdx[m - 2]].first,
                pts2D[hullIdx[m - 1]].second - pts2D[hullIdx[m - 2]].second);
            auto v2 = make_pair(pts2D[i].first - pts2D[hullIdx[m - 2]].first,
                pts2D[i].second - pts2D[hullIdx[m - 2]].second);
            ld cr = v1.first * v2.second - v1.second * v2.first; // 二维叉乘
            if (cr <= 0) hullIdx.pop_back();
            else break;
        }
        hullIdx.push_back(i);
    }
    // 上凸包
    int lowerSize = hullIdx.size();
    for (int i = n - 2; i >= 0; i--) {
        int idxVal = idx[i];
        while ((int)hullIdx.size() > lowerSize) {
            int m = hullIdx.size();
            auto v1 = make_pair(pts2D[hullIdx[m - 1]].first - pts2D[hullIdx[m - 2]].first,
                pts2D[hullIdx[m - 1]].second - pts2D[hullIdx[m - 2]].second);
            auto v2 = make_pair(pts2D[idxVal].first - pts2D[hullIdx[m - 2]].first,
                pts2D[idxVal].second - pts2D[hullIdx[m - 2]].second);
            ld cr = v1.first * v2.second - v1.second * v2.first;
            if (cr <= 0) hullIdx.pop_back();
            else break;
        }
        hullIdx.push_back(idxVal);
    }
    hullIdx.pop_back(); // 去掉重复起点

    // 5. 按凸包索引返回三维点
    vector<point3> result;
    for (int i : hullIdx) result.push_back(p[i]);
    return result;
}