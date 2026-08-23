#include<bits/stdc++.h>
using namespace std;
using ld = long double;

// 点乘：就是向量 a 在向量 b 上的 有符号投影长度 * b的长度
// 性质：同向最大，垂直为0，反向取反
// 功能：

// 1、判断角度类型(= 0垂直, > 0锐角, < 0钝角)

// 2、判断方向关系

// 3、A!=B，给定第三点P, 判断关系
// 过A做线(二维)或平面(三维)，依次为边界，判断P在哪
// dot(B - A, P - A) = 0, P在过A垂直AB的线或平面上
// dot(B - A, P - A) > 0, P在AB方向的半平面上或半空间内
// dot(B - A, P - A) < 0, P在BA方向的半平面上或半空间内

// 4、求投影点：给定点P, 求P在AB上的投影点，t是比例系数
// ld t = dot(P - A, B - A) / dot(B - A, B - A)
// 投影点 = A + t * (B - A)
// t=0投影点是A，t=1投影点是B，t<0在BA方向上A的延长线上，t>1在AB方向上B的延长线上

// 5、求向量 a 长度：sqrt(dot(a, a))

// 6、求两向量 a，b的夹角：(C是夹角)
// cosC = dot(a, b) / (| a | *| b | )
// ld C = acos(dot(a, b) / (| a | *| b | ))

// 7、三维判断面的朝向：dot(面的法向量, 视线方向) < 0, 正面朝向摄像机(即朝向你的眼睛)
// 视线方向：从眼睛指向面

struct point { ld x, y; };
// 三维 = x1 * x2 + y1 * y2 + z1 * z2
ld dot(point a, point b) { return a.x * b.x + a.y * b.y; }

// 叉乘：
// 二维：结果是一个数，等于 向量a 和 向量b 围成的平行四边形面积（带正负号）
//      正负号表示 b 在 a 的逆时针(+) / 顺时针(-)方向，0 表示共线
// 三维：结果是一个向量，垂直于 向量a 和 向量b 所在平面，长度等于平行四边形面积
//      方向用右手定则：四指从 向量a 转向 向量b，拇指方向就是结果方向
// 性质：a×b = -b×a；平行/共线为 0

// 功能（二维叉乘）：

// 1、判断顺逆时针方向
//    cross(a, b) > 0, b 在 a 的逆时针方向
//    cross(a, b) < 0, b 在 a 的顺时针方向
//    cross(a, b) == 0, a 和 b 共线

// 2、判断点在线段哪一侧
//    cross(B - A, P - A) > 0, P 在 AB 左侧（逆时针方向）
//    cross(B - A, P - A) < 0, P 在 AB 右侧（顺时针方向）
//    cross(B - A, P - A) == 0, P 在直线 AB 上

// 3、判断两线段是否相交(跨立实验)
//    线段 AB 和 CD 相交的条件：
//    cross(B - A, C - A) 和 cross(B - A, D - A) 异号 且
//    cross(D - C, A - C) 和 cross(D - C, B - C) 异号
//    （注意边界情况需额外处理，如端点在线段上，会误判不相交）

// 4、求三角形面积(三角形ABC)
// S = | cross(B - A, C - A) / 2 |

// 5、求多边形面积（鞋带公式）
//    area = 0;
//    枚举多边形端点
//    for (int i = 0; i < n; i++)
//        area += cross(p[i], p[(i+1)%n]);
//    area = fabs(area) / 2;

// 6、极角排序（按角度排序）
//    极角：一个向量和正 x 轴之间的夹角，逆时针方向算
//    比较两个向量 v1, v2 的角度：
//    cross(v1, v2) > 0 ，v2 > v1
//    cross(v1, v2) < 0 ，v1 > v2
//    cross(v1, v2) = 0 , 共线，方向未知
//    dot(v1, v2) > 0 同向相等 , < 0 反向180°

// 7、凸包（Andrew 算法）：凸包就是能框住所有点的最小凸多边形
//    凸包的构建方向从最左侧点逆时针旋转
//    下凸包：从 左->右 扫描，形成凸包的下半部分（从最左边的点出发，经过下面的边界，到最右边的点）
//    上凸包：从 右->左 扫描，形成凸包的上半部分（从最右边的点出发，经过上面的边界，回到最左边的点）
//    cross(st[top] - st[top - 1], p[i] - st[top - 1]) > 0，逆时针左转
//    cross(st[top] - st[top - 1], p[i] - st[top - 1]) < 0，顺时针右转
//    cross(st[top] - st[top - 1], p[i] - st[top - 1]) = 0，三点贡献

point cal(point a, point b) {
    return { a.x - b.x,
             a.y - b.y };
}

ld cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}
bool cmp(point a, point b) {}
void Andrew() {
    // 如果点数 n < 3，所有点都是凸包
    const int n = 10;
    point st[2 * n];
    point p[n];
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

// 功能（三维叉乘）：

// 1、求平面法向量
//    n = cross(B - A, C - A)，垂直于三角形 ABC 所在平面
//    方向由右手定则确定

// 2、判断点在平面哪一侧
//    dot(cross(B - A, C - A), P - A) > 0, P 在平面一侧（法向量指向侧）
//    dot(cross(B - A, C - A), P - A) < 0, P 在平面另一侧
//    dot(cross(B - A, C - A), P - A) == 0, P 在平面上

// 3、求三维三角形面积
//    S = |cross(B - A, C - A)| / 2

// 4、结合点乘判断面朝向
//    法向量 n = cross(B - A, C - A)，视线方向 eye -> 面
//    dot(n, eyeDir) < 0 正面朝向摄像机（见点乘第7条）

struct pointt {
    ld x, y, z;
};
pointt Cross(pointt a, pointt b) {
    return { a.y * b.z - a.z * b.y,
             a.z * b.x - a.x * b.z,
             a.x * b.y - a.y * b.x };
}