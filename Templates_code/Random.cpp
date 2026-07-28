#include<iostream>
#include<random>

int main()
{
    std::random_device rd;//随机数引擎

    std::uniform_int_distribution<int> int_dist(1, 100);//整数均匀分布
    std::uniform_real_distribution<double> real_dist(0.0, 100.0);
    std::cout << int_dist(rd) << '\n';//随机数来源是rd(引擎)
    std::cout << real_dist(rd) << '\n';
}
