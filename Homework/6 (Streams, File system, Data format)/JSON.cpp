#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include <locale>
#include <ostream>
#include <iostream>
#include <vector>


#include "json.hpp"

using nlohmann::json;

struct Person
{
    Person()= default;

    Person(std::string n):
            name(n), weight(0), height(0), eyesight("UNK")
    {};

    Person(std::string n, double w):
            name(n), weight(w), height(0), eyesight("UNK")
    {};

    Person(std::string n, double w, double h):
            name(n), weight(w), height(h), eyesight("UNK")
    {};

    Person(std::string n, double w, double h, std::string es):
            name(n), weight(w), height(h), eyesight(es)
    {};

    ~Person()= default;

    friend std::ostream & operator<<(std::ostream & stream, const Person & per)
    {
        stream << "Name:    " << per.name << "\nWeight: " <<  per.weight
                << "\nHeight:  " << per.height << "\nEyesight: " << per.eyesight;
        return stream;
    }

    friend std::istream & operator>>(std::istream & stream, Person & per)
    {
        std::cout << "Name: ";
        stream >> per.name;

        std::cout << "Weight: ";
        stream >> per.weight;

        std::cout << "Height: ";
        stream >> per.height;

        std::cout << "Eyesight: ";
        stream >> per.eyesight;

        return stream;
    }

    std::string name;
    double weight{};
    double height{};
    std::string eyesight;
};

int main(int argc, char ** argv)
{
    system("chcp 65001");

    auto path = std::filesystem::current_path();
    std::filesystem::create_directory(path / "directory");

    Person a ("Alex", 75, 180, "Bad");
    Person b ("Bob", 66, 173, "Excellent");
    Person c ("Clarie", 60, 160, "Not bad");
//    Person a;
//    Person b;
//    Person c;

    std::vector < Person > persons {a, b, c};

//    std::for_each(std::begin(persons), std::end(persons),
//                  [](auto per)
//                  {
//                    std::cin >> per;
//                    std::cout << std::endl;
//                  });

    json j;

    std::string s;

    for(auto p: persons)
    {
        j = {
                {"Name", p.name},
                {"Weight", p.weight},
                {"Height", p.height},
                {"Eyesight", p.eyesight}
        };

        s = p.name + ".txt";
        std::ofstream fout((path / "directory" / s).string());
        fout << std::setw(4) << j;
    }
    
    system("pause");

    return EXIT_SUCCESS;
}
