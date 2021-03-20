#include <iostream>
#include <string>
#include <regex>

int main()
{   
    // Patterns
    const std::regex pattern_for_date(R"(\d{4}\.(0[1-9]|1[012])\.(0[1-9]|[12][0-9]|3[01]))");
    const std::regex pattern_for_time(R"((\d|[01][0-9]|[2][0-3]):[0-5][0-9]:[0-5][0-9])");
    
    // Data string
    std::string data = "kjsag;ajlsd 0094.02.10 itjjgr 30:90:00 ated 2021.01.01 asg 17:00:59 y 9001.01.32 aisn 10:40:34 hgffk 20.0.0 hgf 1598.12.30";

    // Block for dates
    std::sregex_iterator date_begin(data.cbegin(), data.cend(), pattern_for_date);
    std::sregex_iterator date_end;
    
    std::cout << "Dates:\n";
    
    std::for_each(date_begin, date_end, [](const std::smatch & m)
        {
            std::cout << m[0] << std::endl;
        });
    
    // Block for times
    std::sregex_iterator time_begin(data.cbegin(), data.cend(), pattern_for_time);
    std::sregex_iterator time_end;
    
    std::cout << "Times:\n";
    
    std::for_each(time_begin, time_end, [](const std::smatch & m)
        {
            std::cout << m[0] << std::endl;
        });

    std::system("pause");

    return EXIT_SUCCESS;
}
