#include <iostream>
#include <fstream>
#include <iomanip>

int main()
{
    std::fstream fout("file.txt", std::ios::out | std::ios::trunc);

    for(auto i = 0; i < 10; ++i)
        fout << "Hello" + std::to_string(i) << std::endl;

    std::fstream fin("file.txt", std::ios::in);

    int num;
    std::cin >> num;

    fin.seekp(num * (6 + 2), std::ios::beg);

    std::string s;
    std::getline(fin, s);

    std::cout << s << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}
