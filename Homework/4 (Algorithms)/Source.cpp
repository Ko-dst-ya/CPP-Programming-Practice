#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>

template < typename T >
void print_vec(std::vector < T > vector)
{
    std::for_each(std::begin(vector),
                  std::end(vector),
                  [](auto x){std::cout << x << ' ';});

    std::cout << std::endl;
}

int main(int argc, char ** argv)
{
// First (Sequence 1 filling)
    std::vector < int > seq1 (10);
    std::iota(std::begin(seq1), std::end(seq1), 1);
    print_vec(seq1);

// Second (Adding some elements)
    std::copy(std::istream_iterator < int > (std::cin),
            std::istream_iterator < int > (),
            std::back_inserter(seq1));

    std::cout << "1st after extra inputting:";
    print_vec(seq1);

    std::cout << "\n";

// Third (Mixing)

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(seq1.begin(), seq1.end(), g);

    std::cout << "After mixing :\n";
    print_vec(seq1);

    std::cout << "\n";

// Fourth (duplicates removing)
    std::sort(std::begin(seq1), std::end(seq1));
    seq1.erase(std::unique(std::begin(seq1), std::end(seq1)), std::end(seq1));

    print_vec(seq1);

    std::cout << "\n";

// Fifth (amount of odd numbers)
    auto amount_of_odds = std::count_if(std::begin(seq1), std::end(seq1), [](auto x){return x % 2;});

    std::cout << "Amount of odd numbers :\n" << amount_of_odds << std::endl;

    // Sixth (find min and max)
    auto [min, max] = std::minmax_element(std::begin(seq1), std::end(seq1));

    std::cout << "min : " << *min << "\nmax : " << *max << std::endl;
    std::cout << "\n";

// Seventh (finding prime number)





// Eighth (replacing numbers with their squares)

    /*
    Possible implementation

    std::for_each(std::begin(seq1),
                  std::end(seq1),
                  [](int & x){x *= x;});
    */

    std::transform(std::begin(seq1), std::end(seq1), std::begin(seq1),
            [](auto x){ return x * x;});

    std::cout << "Squares :\n";
    print_vec(seq1);

    std::cout << "\n";

// Ninth (Sequence 2 creating)
    std::vector <int> seq2 (seq1.size());

    std::default_random_engine dre(std::chrono::system_clock::now().time_since_epoch().count());;
    std::uniform_int_distribution <> uid (0, 10);

    std::generate(std::begin(seq2), std::end(seq2), [&dre, &uid](){return uid(dre);});

    std::cout << "2nd sequence:\n" << std::endl;
    
    print_vec(seq2);

    std::cout << "\n";

// Tenth (sum(sqe2))

    std::cout << "Sum of 2nd sequence:\n" << std::accumulate(std::begin(seq2), std::end(seq2),
                                   decltype(seq2)::value_type(0));
    std::cout << "\n\n";

   /*Possible implementation
    int sum = 0;
    std::for_each(std::begin(seq2), std::end(seq2), [&sum](auto x){ sum += x;});
    std::cout << sum << std::endl;
    std::cout << std::endl;
    */

// Eleventh (replacing some first element)
    std::fill_n(std::begin(seq2), 5, 1); // Replacing the first 5 elements with 1

    std::cout << "2nd after replacing with 1:\n";
    print_vec(seq2);

    std::cout << "\n";
    
    /*
     * Possible implementation
     std::replace_if(std::begin(seq2), std::next(std::begin(seq2) + 4),
                 [](auto x){return x;}, 1);
    */

// Twelfth (Sequence 3 creating)
    std::vector < int > seq3;

    std::cout << "3rd sequence:\n";
    std::transform(std::begin(seq1), std::end(seq1), std::begin(seq2), std::back_inserter(seq3),
                   [](auto a, auto b) { return a - b ;});
    
    print_vec(seq3);

    std::cout << "\n";

// Thirteenth (replacing each element in 3rd sequence with 0)
    std::cout << "3rd after replacing negative to 0-s:\n";

    std::replace_if(std::begin(seq3), std::end(seq3), [](auto x){ return x<0;},0);
    print_vec(seq3);

    std::cout << "\n";

// Fourteenth (Remove zeros)
    std::cout << "3rd after removing 0-s:\n";

    seq3.erase(std::remove_if(std::begin(seq3), std::end(seq3),
                              [](auto x){return x == 0;}),
               std::end(seq3));
    
    print_vec(seq3);

    std::cout << "\n";

// Fifteenth (reverse)
    std::cout << "3rd after reversing:\n";

    std::reverse(std::begin(seq3), std::end(seq3));
    print_vec(seq3);

    std::cout << "\n";

// Sixteenth (top 3)
    std::cout << "Extra shuffling 3rd sequence:\n";
    std::shuffle(seq3.begin(), seq3.end(), g);

    std::cout << "Top 3 elements:\n";
    std::partial_sort(std::begin(seq3),
                      std::next(std::begin(seq3) + 3),
                      std::end(seq3),
                      [](auto x, auto y){return x > y ;});
    print_vec(seq3);

    std::cout << std::endl;

// Seventeenth (Sort 1 and 2)
    std::cout << "1st after sorting:\n";
    std::sort(std::begin(seq1), std::end(seq1));
    print_vec(seq1);
    std::cout << "\n";

    std::cout << "2nd after sorting:\n";
    std::sort(std::begin(seq2), std::end(seq2));
    print_vec(seq2;

    std::cout << "\n";

// Eighteenth (4th seq creating)
    std::vector < int > seq4;

    std::cout << "4th sequence:\n";

    std::merge(std::begin(seq1), std::end(seq1), std::begin(seq2), std::end(seq2), std::back_inserter(seq4));
    print_vec(seq4);

    std::cout << "\n";

// Nineteenth (equal range)
    std::cout << "Eq_range for 1:\n";

    auto it = std::equal_range(std::begin(seq4), std::end(seq4), 1);

    std::cout << *(it.first) << ' ' << *(it.second) << std::endl;

// Twenty (printing all sequences)
    std::vector < std::vector < int > > sequences = {seq1, seq2, seq3, seq4};

    std::cout << "All sequences:\n";

    std::for_each(std::begin(sequences),
                  std::end(sequences),
                  [](auto x)
                  {std::for_each(std::begin(x),
                                 std::end(x),
                                 [](auto y){std::cout << y << ' ';});
                  std::cout << std::endl;
                  });

    system("pause");

    return EXIT_SUCCESS;
}
