#include<bits/stdc++.h>
using namespace std;


//计数排序,时间复杂度和空间复杂度O(n)
//对数据的范围有严格要求
class CountSort {
private:
    static const int MAXN = 1e7;
    int cnt[MAXN + 1] = { 0 };
    //unordered_map<int,int>cnt
public:

    void Sort(int* a, int n, int maxval) {
        fill(cnt, cnt + maxval + 1, 0);
        for (int i = 1;i <= n;i++) {
            cnt[a[i]]++;
        }
        int idx = 0;
        for (int i = 0;i <= maxval;i++) {
            for (int j = 1;j <= cnt[i];j++) {
                a[++idx] = i;
            }
        }
    }
};

//基数排序RadixSort
//可以对于不同进制下的非负整数排序
//时间复杂度O(n)
class RadixSort {
private:
    static const int MAXN = 1e7;
    int help[MAXN + 1];//辅助数组
    int bit = 0;
    int GetHeightBit(int* a, int n, int base) {
        //获取最高位
        int maxval = 0;
        int ans = 0;
        for (int i = 1;i <= n;i++) {
            maxval = max(maxval, a[i]);
        }
        while (maxval) {
            maxval /= base;
            ans++;
        }
        return ans;
    }

    void copy(int n, int* a, int* b) {
        //a->b
        for (int i = 1;i <= n;i++) {
            b[i] = a[i];
        }
    }

public:
    void Sort(int* a, int n, int base) {
        //合法下标1~n
        bit = GetHeightBit(a, n, base);//获取在BASE下的最高有效位
        for (int i = 1, offset = 1;i <= bit;i++, offset *= base) {
            //依次处理每一位
            vector<int>cnt(base, 0);//0~base-1
            for (int i = 1;i <= n;i++) {
                cnt[(a[i] / offset) % base]++;
            }
            //base进制意义下的前缀和
            for (int i = 1;i < base;i++) {
                cnt[i] += cnt[i - 1];
            }
            //排序
            for (int i = n;i >= 1;i--) {
                help[cnt[(a[i] / offset) % base]--] = a[i];
            }
            copy(n, help, a);
        }
    }

};
