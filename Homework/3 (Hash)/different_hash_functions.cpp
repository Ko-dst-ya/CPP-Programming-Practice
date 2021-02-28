#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <set>
#include <boost/container_hash/hash.hpp>

unsigned int RSHash(const char* str, unsigned int length)
{
    unsigned int b    = 378551;
    unsigned int a    = 63689;
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = hash * a + (*str);
        a    = a * b;
    }

    return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
    const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits          =
            (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

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

unsigned int BKDRHash(const char* str, unsigned int length)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
    unsigned int hash = length;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash;
}

int main(int argc, char ** argv)
{
    const int Max_value = 1e6;
    const size_t length = 10;   // length of random words
    std::set < int > hashes;
    
    for (auto i = 10; i <= Max_value; i+=50000)
    {
        std::set < int > hashes;
        std::set < std::string > words = make_random_words(i, length);
        std::size_t collisions = 0;

        for (std::string word : words)
        {
            const char * c = word.c_str();
//            auto iterator_and_bool = hashes.insert(RSHash(c, length));
//            auto iterator_and_bool = hashes.insert(JSHash(c, length));
//            auto iterator_and_bool = hashes.insert(PJWHash(c, length));
//            auto iterator_and_bool = hashes.insert(ELFHash(c, length));
//            auto iterator_and_bool = hashes.insert(BKDRHash(c, length));
//            auto iterator_and_bool = hashes.insert(SDBMHash(c, length));
//            auto iterator_and_bool = hashes.insert(DJBHash(c, length));
//            auto iterator_and_bool = hashes.insert(DEKHash(c, length));
            auto iterator_and_bool = hashes.insert(APHash(c, length));

//            auto iterator_and_bool = hashes.insert(boost::hash_value(word));

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
