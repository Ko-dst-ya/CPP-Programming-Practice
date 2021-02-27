#include <iostream>
#include <chrono>
#include <array>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

class Timer
{
public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;

    Timer() : m_begin(clock_t::now()) {}

    ~Timer()
    {
        auto end = clock_t::now();

        std::cout << "micro : " << std::chrono::duration_cast <std::chrono::microseconds> (end - m_begin).count() << std::endl;
    }

private:
    time_point_t m_begin;
};

int main()
{
    for(auto i = 4; i < 7; ++i)
    {
        const double N = pow(10.0, (double)i);
        std::vector < int > vec;
        std::set < int > set;

        std::cout << "N is " << N << std::endl;

        std::cout << "Set: ";
        {
            Timer timer_for_set;

            for (auto k = 0; k < N; ++k)
            {
                set.insert(k);
            }
        }

        vec.reserve(N);

        std::cout << "\nVector: ";

        {
            Timer timer_for_vector;

            for (auto j = 0; j < N; ++j)
            {
                vec.push_back(N - j);
            }

            std::sort(std::begin(vec), std::end(vec));
        }

        std::cout << std::endl;
    }

    system("pause");

    return EXIT_SUCCESS;
}
