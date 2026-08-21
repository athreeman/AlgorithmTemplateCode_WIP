#include<bits/stdc++.h>
using namespace std;

//2的幂快速判断
void isPwTwo(int n) {
    //若x>0,x&(~x+1)==x则x是2的幂
    //~x+1=-x
    if (n == 0) {
        cout << 'F' << '\n';
        return;
    }
    if ((n & (-n)) == n) {
        cout << 'T' << '\n';
    }
    else {
        cout << 'F' << '\n';
    }
}

int GetLowBitOne(int a){}
//找到最小的非负整数k,使得a+k的最低位1>=minV
int calCost(int a, int minV) {
    int v = GetLowBitOne(a);
    if (v >= minV) return 0;
    int pow2 = 1 << minV;
    int m = (a + pow2 - 1) >> minV;
    int b = m << minV;
    return b - a;
}

// 用给定位状态status的1位组成的集合(即status位状态的所有子集)
// 循环遍历,该方法的遍历保证严格下降不重复
void s(){
    for (int i = status;i > 0;i = (i - 1) & status) {
        cout << i << ' ';
    }
}

// 加法运算的位本质
// 对于任意整数a, b
// 都满足a + b = a ^ b + 2(a & b)

// 快速提取x最右侧的1(x!=0)
// ll lowBitOne=x&(-x)
