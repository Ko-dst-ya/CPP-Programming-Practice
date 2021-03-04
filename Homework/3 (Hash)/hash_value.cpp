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

std::vector < int > make_random_positive_numbers(int ceil, std::size_t amount)
{
    std::uniform_int_distribution <> uid(0, ceil);
    std::default_random_engine dre(static_cast < std::size_t > (
                                           std::chrono::system_clock::now().time_since_epoch().count()));

    std::vector < int > numbers;
    numbers.reserve(amount);

    for (auto i = 0; i < amount; ++i)
        numbers.push_back(uid(dre));

    return numbers;
}

std::size_t hash_value(int number, const std::string & word)
{
    std::size_t seed = 0;

    boost::hash_combine(seed, number);
    boost::hash_combine(seed, word);

    return seed;
}

int main(int argc, char ** argv)
{
    const int H = 100000;       // size of hash table
    const size_t length = 10;   // length of random words
    
    std::set < std::string > words = make_random_words(H, length);      // create set of random words
    std::vector < int > numbers = make_random_positive_numbers(H, H);   // create vector of random numbers

    for (auto i = 10; i < H; i += 100)
    {
        std::set < int > hashes;
        int collisions = 0;
        auto it_word = words.begin();

        for (auto j = 0; j < i; ++j)
        {
            if(!hashes.insert(hash_value(numbers[j], *it_word)).second)
            {
                ++collisions;
            }

            ++it_word;
        }
        std::cout << "(" << i << "," << collisions << ")," << std::endl; // format of output if for python
    }

    system("pause");

    return EXIT_SUCCESS;
}
