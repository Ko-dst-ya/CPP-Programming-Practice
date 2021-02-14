#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

int main()
{
    std::vector < int > vec;    

    for (auto i = 0; i <= 31; ++i)
    {
        vec.push_back(i);	
    }

	double coef = vec.capacity();	// Коэффициент расширения
	
	std::cout << "Size      = " << vec.size() << std::endl;
	std::cout << "Capacity  = " << vec.capacity() << std::endl;

    std::cout << "\nAfter adding one element:" << std::endl;

	vec.push_back(31);
	
	std::cout << "Size      = " << vec.size() << std::endl;
	std::cout << "Capacity  = " << vec.capacity() << std::endl;
	
	coef = (double)vec.capacity() / coef;
	std::cout << "\nCoefficient of expansion is " << coef << std::endl; // Коэффициент расширения равен 2 на MinGW

    std::cout << "\nUsing the reserve() member function\n" << std::endl;

    std::vector < int > vec_2;
	vec_2.reserve(5);
	
	std::cout << "Size      = " << vec_2.size() << std::endl;
	std::cout << "Capacity  = " << vec_2.capacity() << std::endl; 
    // На MinGW ёмкость равна запрошенному месту

    // Предельный случай большого запроса памяти 
    try
    {
        vec.reserve(1e10); //Начинает выскакивать на 10^10
    }
    catch(std::exception & oor)
    {
        std::cerr << "\nLimiting case\n" <<  oor.what() << std::endl;
    }

    system("pause");

    return EXIT_SUCCESS;
}
