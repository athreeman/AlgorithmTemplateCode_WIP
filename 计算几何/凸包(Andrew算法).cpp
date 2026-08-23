#include<bits/stdc++.h>
using namespace std;
using ld = long double;

// 7、凸包（Andrew 算法）：凸包就是能框住所有点的最小凸多边形
//    凸包的构建方向从最左侧点逆时针旋转
//    下凸包：从 左->右 扫描，形成凸包的下半部分（从最左边的点出发，经过下面的边界，到最右边的点）
//    上凸包：从 右->左 扫描，形成凸包的上半部分（从最右边的点出发，经过上面的边界，回到最左边的点）
//    cross(st[top] - st[top - 1], p[i] - st[top - 1]) > 0，逆时针左转
//    cross(st[top] - st[top - 1], p[i] - st[top - 1]) < 0，顺时针右转
//    cross(st[top] - st[top - 1], p[i] - st[top - 1]) = 0，三点贡献


struct point {//二维
    ld x, y;
};
ld dot(point a, point b) {
    // 三维 = x1 * x2 + y1 * y2 + z1 * z2
    return a.x * b.x + a.y * b.y;
}

point cal(point a, point b) {
    return { a.x - b.x,
             a.y - b.y };
}

ld cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}
bool cmp(point a, point b) {
    if (a.x == b.x)return a.y < b.y;
    return a.x < b.x;
}
void Andrew(point* st, point* p) {
    // 如果点数 n < 3，所有点都是凸包
    const int n = 10;
    // point st[2 * n]; st的大小需要开2倍
    sort(p + 1, p + n + 1, cmp);//x递增, y递增排序
    // 下凸包
    int top = 0;
    for (int i = 1; i <= n; i++) {
        while (top >= 2 && cross(cal(st[top], st[top - 1]), cal(p[i], st[top - 1])) <= 0) {
            top--;  // 弹出栈顶
        }
        st[++top] = p[i];  // 当前点入栈
    }
    // 上凸包：从 n-1 到 1 反向遍历（跳过最右边点，它已在下凸包中）
    int tmp = top;  // 记录下凸包大小
    for (int i = n - 1; i >= 1; i--) {
        while (top > tmp && cross(cal(st[top], st[top - 1]), cal(p[i], st[top - 1])) <= 0) {
            top--;
        }
        st[++top] = p[i];
    }
    top--;//弹出多余p[1]，维护逆时针顺序，此时st就是凸包顶点
}