#include <iostream>
#include <fstream>
#include <iomanip>

int main()
{
    std::fstream fout("file.txt", std::ios::out | std::ios::trunc);

    for(auto i = 0; i < 10; ++i)
        fout << "Hello" + std::to_string(i) << std::endl;
    
    auto size = fout.tellp() / 10; // размер слова с учётом доп символов

    std::fstream fin("file.txt", std::ios::in);

    int num;
    std::cin >> num;

    fin.seekp(num * size, std::ios::beg);

    std::string s;
    std::getline(fin, s);

    std::cout << s << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}
