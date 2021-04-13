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
#include <atomic>

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

void dots_in_circle_atom(std::uniform_real_distribution < double > & urd, std::size_t N, std::size_t id, std::atomic < int > & counter)
{
    std::mt19937 g(std::chrono::system_clock().now().time_since_epoch().count() + id);

    for(std::size_t i = 0; i < N; ++i)
    {
        auto x = urd(g);
        auto y = urd(g);

        if(x*x + y*y <= 1)
        {
            ++ counter;
        }
    }
}

double par_pi_atom(auto N)
{
    std::atomic < int > counter(0);
    
    std::random_device rd;
    std::mt19937 g(rd());

    static std::uniform_real_distribution < double > urd(0.0, 1.0);

    const std::size_t min_per_thread = 1000;
    const std::size_t max_threads =
            (N + min_per_thread - 1) / min_per_thread;

    const std::size_t hardware_threads =
            std::thread::hardware_concurrency();

    const std::size_t num_threads =
            std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    const std::size_t block_size = N / num_threads;

    std::vector < std::future < void > > futures(num_threads - 1);
    std::vector < std::thread > threads(num_threads - 1);

    Threads_Guard guard(threads);

    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {
        std::packaged_task < decltype(dots_in_circle_atom) > task(dots_in_circle_atom);

        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), std::ref(urd), block_size, i, std::ref(counter));

    }

    dots_in_circle_atom(urd, block_size, num_threads - 1);

    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {
        futures[i].get();
    }

    return 4.0 * counter / N;
}

int main()
{
    auto N = 1e6;
    {
        Timer t;
        std::cout << seq_pi(N) << std::endl;
    }

    {
        Timer t;
        std::cout << par_pi_atom(N) << std::endl;
    }
    
    system("pause");

    return EXIT_SUCCESS;
}
