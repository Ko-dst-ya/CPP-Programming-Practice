#include <chrono>
#include <execution>
#include <thread>
#include <future>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
#include <random>
#include <algorithm>

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

class Threads_Guard
{
public:

    explicit Threads_Guard(std::vector < std::thread > & threads) :
            m_threads(threads)
    {}

    Threads_Guard(Threads_Guard const &) = delete;

    Threads_Guard& operator=(Threads_Guard const &) = delete;

    ~Threads_Guard() noexcept
    {
        try
        {
            for (std::size_t i = 0; i < m_threads.size(); ++i)
            {
                if (m_threads[i].joinable())
                {
                    m_threads[i].join();
                }
            }
        }
        catch (...)
        {
            // std::abort();
        }
    }

private:

    std::vector < std::thread > & m_threads;
};

double seq_pi(std::size_t N)
{
    std::random_device rd;
    std::mt19937 g(rd());

    static std::uniform_real_distribution < double > urd(0.0, 1.0);

    auto count = 0;

    for(std::size_t i = 0; i < N; ++i)
    {
        auto x = urd(g);
        auto y = urd(g);

        if(x*x + y*y <= 1)
        {
            ++ count;
        }
    }

    return 4.0 * count / N;
}

int main()
{
    auto N = 1e6;
    {
        Timer t;
        std::cout << seq_pi(N) << std::endl;
    }

    system("pause");

    return EXIT_SUCCESS;
}
