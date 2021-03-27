#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
#include <random>
#include <algorithm>

int main()
{
    std::random_device rd;
    std::mt19937 g(rd());

    static std::uniform_real_distribution < double > urd(0.0, 1.0);
    auto N = 1e6;

    auto count = 0;

   for(auto i = 0; i < N; ++i)
   {
        auto x = urd(g);
        auto y = urd(g);

        if(x*x + y*y <= 1)
        {
            ++ count;
        }
   }

   auto pi = 4.0 * count / N;

    std::cout << pi << std::endl;
    
    std::vector < std::pair <double, double> > v(N);
    
    std::generate(std::begin(v), std::end(v), [&g](){return std::make_pair <double, double> (urd(g), urd(g));});

    int count_1 = std::count_if(std::execution::par, std::begin(v), std::end(v),
                  [](auto x){return (x.first)*(x.first) + (x.second)*(x.second) <= 1;});
    
    auto pi_1 = 4.0 * count_1 / N;
    
    std::cout << pi_1 << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}
