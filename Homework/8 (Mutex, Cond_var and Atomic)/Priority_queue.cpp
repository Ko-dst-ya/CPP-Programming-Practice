#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

template <  typename T
            typename Container = std::vector < T >,
            typename Compare = std::less < typename Container::value_type >
> class Threadsafe_Priority_Queue
{
public:

    Threadsafe_Priority_Queue() = default;

    Threadsafe_Priority_Queue(const Threadsafe_Priority_Queue & other)
    {
        std::lock_guard < std::mutex > lock(other.m_mutex);
        m_pqueue = other.m_pqueue;
    }

    Threadsafe_Priority_Queue & operator=(const Threadsafe_Priority_Queue & other)
    {
        std::scoped_lock lock(m_mutex, other.m_mutex);
        m_pqueue = other.m_pqueue;
    }

public:

    void push(T value)
    {
        std::lock_guard < std::mutex > lock(m_mutex);
        m_pqueue.push(value);
        m_condition_variable.notify_one();
    }

    void wait_and_pop(T & value)
    {
        std::unique_lock < std::mutex > lock(m_mutex);

        m_condition_variable.wait(lock, [this] {return !m_pqueue.empty(); });
        value = m_pqueue.top();
        m_pqueue.pop();
    }

    std::shared_ptr < T > wait_and_pop()
    {
        std::unique_lock < std::mutex > lock(m_mutex);

        m_condition_variable.wait(lock, [this] {return !m_pqueue.empty(); });
        auto result = std::make_shared < T > (m_pqueue.top());
        m_pqueue.pop();

        return result;
    }

    bool try_pop(T & value)
    {
        std::lock_guard < std::mutex > lock(m_mutex);

        if (m_pqueue.empty())
        {
            return false;
        }

        value = m_pqueue.top();
        m_pqueue.pop();

        return true;
    }

    std::shared_ptr < T > try_pop()
    {
        std::lock_guard < std::mutex > lock(m_mutex);

        if (m_pqueue.empty())
        {
            return std::shared_ptr < T > ();
        }

        auto result = std::make_shared < T > (m_pqueue.top());
        m_pqueue.pop();

        return result;
    }

    bool empty() const
    {
        std::lock_guard < std::mutex > lock(m_mutex);
        return m_pqueue.empty();
    }

private:

    std::priority_queue < T >		m_pqueue;
    std::condition_variable m_condition_variable;

private:

    mutable std::mutex m_mutex;
};

int main(int argc, char ** argv)
{
    Threadsafe_Priority_Queue < int > pqueue;

    pqueue.push(42);

    auto ptr = pqueue.wait_and_pop();

    int value;

    bool result = pqueue.try_pop(value);

    system("pause");

    return EXIT_SUCCESS;
}
