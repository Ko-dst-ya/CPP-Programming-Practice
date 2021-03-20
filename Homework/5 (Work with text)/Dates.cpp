#include <iostream>
#include <string>
#include <regex>

int main()
{   
    const std::regex pattern_for_date(R"(\d{4}\.(0[1-9]|1[012])\.(0[1-9]|[12][0-9]|3[01]))");
    
    std::string data = "kjsag;ajlsd 0094.02.10 itjjgr 30:90:00 ated 2021.01.01 asg 17:00:59 y 9001.01.32 aisn 10:40:34 hgffk 20.0.0 hgf 1598.12.30";

    std::sregex_iterator date_begin(data.cbegin(), data.cend(), pattern_for_date);
    std::sregex_iterator date_end;
    
    std::cout << "Dates:\n";
    
    std::for_each(date_begin, date_end, [](const std::smatch & m)
        {
            std::cout << m[0] << std::endl;
        });

    std::system("pause");

    return EXIT_SUCCESS;
}
