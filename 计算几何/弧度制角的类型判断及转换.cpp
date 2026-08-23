#include<bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-12;
const ld PI = acos(-1.0);
const ld HALF_PI = PI / 2;
const ld DEG_TO_RAD = PI / 180.0;
const ld RAD_TO_DEG = 180.0 / PI;

// 角度制转弧度制
ld degToRad(ld deg) {
    return deg * DEG_TO_RAD;
}

// 弧度制转角度制
ld radToDeg(ld rad) {
    return rad * RAD_TO_DEG;
}

// 根据弧度判断角类型
// 返回 0=零角, 1=锐角, 2=直角, 3=钝角, 4=平角, -1=超出[0,π]
int angleTypeByRad(ld rad) {
    rad = fabs(rad);
    if (rad < eps) return 0;
    if (fabs(rad - HALF_PI) < eps) return 2;
    if (rad < HALF_PI) return 1;
    if (fabs(rad - PI) < eps) return 4;
    if (rad < PI) return 3;
    return -1;
}

// 根据角度制直接判断角类型（可选）
int angleTypeByDeg(ld deg) {
    return angleTypeByRad(degToRad(deg));
}