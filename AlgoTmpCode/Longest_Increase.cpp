#include<bits/stdc++.h>
using std::cin, std::cout;
const int MAXN = 1e6;
using ll = long long;
//LIS:最长递增子序列(严格递增)

int dp[MAXN + 1];//dp[i]以i结尾的最长递增子序列
int end[MAXN + 1];//长度为i的最大结尾元素递增子序列

int binary_search(int x, int n, int* arr) {
    //查找首个>=x的位置
    //对于最长非严格递增子序列(即可以相等),求首个>x的位置即可
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (arr[mid] >= x) {
            //对于最长非严格递增子序列,>x时r=mid-1
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return l;
}

//获取最长递增子序列的长度
int LIS(int n, int* arr) {
    int R = 1;
    dp[1] = 1;
    end[1] = arr[1];
    for (int i = 2;i <= n;i++) {
        int idx = binary_search(arr[i], R, end);
        if (idx > R) {
            end[++R] = arr[i];
        }
        else {
            end[idx] = arr[i];
        }
        dp[i] = idx;
    }
    return R;
}