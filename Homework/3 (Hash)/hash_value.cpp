#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <set>
#include <boost/container_hash/hash.hpp>

std::set < std::string > make_random_words(std::size_t N, std::size_t length) // length = 10 - good enough
{
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast < std::size_t > (
                                         std::chrono::system_clock::now().time_since_epoch().count()));

    std::set < std::string > words;

    for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
        for (auto & c : s)
            c = letter(e);

    return words;
}

int main(int argc, char ** argv)
{
    const int H = 100000;       // size of hash table
    const size_t length = 10;   // length of random words

    for (auto i = 10; i < H; i+=100)
    {
        std::set < int > hashes;
        std::set < std::string > words = make_random_words(i, length);
        int collisions = 0;

        for (auto j = 0; j < i; ++j)
        {
            auto iterator_and_bool = hashes.insert(boost::hash_value(rand() % H));

            if (!iterator_and_bool.second)
            {
                ++collisions;
            }
        }

        for (std::string word : words)
        {
            auto iterator_and_bool = hashes.insert(boost::hash_value(word));

            if (!iterator_and_bool.second)
            {
                ++collisions;
            }
        }

        std::cout << "(" << i << "," << collisions << ")," << std::endl; // format of output if for python
    }

    system("pause");

    return EXIT_SUCCESS;
}
