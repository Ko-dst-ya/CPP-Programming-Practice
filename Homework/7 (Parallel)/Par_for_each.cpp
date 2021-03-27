#include <iostream>
#include <vector>
#include <cmath>
#include<chrono>
#include <algorithm>
#include <thread>
#include <future>
#include <numeric>
#include <functional>

template < typename Iterator, typename T >
void parallel_for_each(Iterator first, Iterator last, T init)
{
    const std::size_t length = std::distance(first, last);

    const std::size_t max_size = 25;

    if (length <= max_size)
    {
        std::for_each(first, last, init);
    }
    else
    {
        Iterator middle = first;
        std::advance(middle, length / 2);

        std::future < void > first_half_result =
                std::async(parallel_for_each < Iterator, T >, first, middle, init);

        parallel_for_each(middle, last, init);
        first_half_result.get();
    }
}


int main(int argc, char** argv)
{
    std::vector < int > v(1e6);

    std::iota(v.begin(), v.end(), 1);

    parallel_for_each(std::begin(v), std::end(v), [](auto x) {sin(x); });

    system("pause");

    return EXIT_SUCCESS;
}
