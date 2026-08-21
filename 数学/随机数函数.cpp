#include<bits/stdc++.h>
using namespace std;
int main()
{
    random_device rd;//获取真随机数种子
    
    //性能即生成速度(cpu时间)和内存占用
    //质量即接近真随机数的程度,越高其生成数据周期越长,规律性越弱

    //直接使用rd()种子生成的数据是真随机,质量最好,但是性能相对一般
    uniform_int_distribution<int> dist(1, 100);
    cout << dist(rd) << '\n';

    //使用伪随机数引擎接受来自rd()的种子,从而生成伪随机种子,伪随机但性能提升显著
    //根据真随机种子,生成伪随机种子
    mt19937 gen(rd());//质量高,性能优秀,周期律约1e6001

    //mt19937_64 生成64位数值的优化选择,周期律约1e6001
    //minstd_rand 性能速度极佳,质量差,周期律约2^31-2
    //ranlux48 质量极高,性能低,周期律约1e576


    uniform_int_distribution<int> int_dist(1, 100);//整数均匀分布
    uniform_real_distribution<double> real_dist(0.0, 100.0);
    cout << int_dist(gen) << '\n';//随机数来源是gen(种子)
    cout << real_dist(gen) << '\n';
}
