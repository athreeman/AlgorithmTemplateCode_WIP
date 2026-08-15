#include<bits/stdc++.h>
using namespace std;
using ll = long long;
//manacher求最长回文子串
//p[i]:表示以i为中心扩展的回文子串的半径
//r:所有已确定点的回文串向右延伸的截止位置的最大位置
//c:回文串截止位置=r的最早中心点
//情况1：当前位置i没有被r包裹,以i为中心扩展
//情况2：当前i被r包住,对称点i2在大回文区域内,p[i]=p[i2]
//情况3：当前i被r包住,对称点i2在大回文区域外,p[i]=r-i
//情况4：当前i被r包住,对称点i2的回文半径撞到边界,从r的位置扩展
class Man {
private:
    static const int MAXN = 2e5;
    static int p[2 * MAXN + 2];
public:
    int manacher(string t) {
        string s = "#";
        for (char ch : t) {
            s += ch;//不能写为 s+=ch+'#
            s += '#';//这样写会把ch和#的ASCII码相加,得到一个字符
        }
        int maxlen = 0;
        //实际回文长度=回文半径-1
        for (int i = 0, r = 0, c = 0, len;i < s.size();i++) {
            len = r > i ? min(p[2 * c - i], r - i) : 1;//若被r包住,获取答案,否则至少len=1
            while (i + len < s.size() && i - len >= 0 && s[i + len] == s[i - len]) {
                //情况2,3不可能执行该while循环
                //情况1,4可能执行该while循环
                len++;
            }
            if (i + len > r) {
                //判断最长回文半径
                r = i + len;
                c = i;
            }
            maxlen = max(maxlen, len);
            p[i] = len;
            int st = (i - len + 1) / 2;//该子串实际映射的开头位置
            int ed = (i + len - 2) / 2;//该子串实际映射的结尾位置
        }
        return maxlen - 1;
    }
};
