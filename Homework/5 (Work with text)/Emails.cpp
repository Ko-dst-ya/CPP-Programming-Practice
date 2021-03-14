#include <iostream>
#include <string>
#include <regex>

bool is_email_valid(const std::string& email)
{
    // define a regular expression
    const std::regex pattern
            (R"(((\w+)(\.|_))?(\w*)@(\w+)(\.(\w+))+)");

    // try to match the string with the regular expression
    return std::regex_match(email, pattern);
}

int main()
{
    const std::regex pattern
            (R"(\w+\.|_?\w*@([\w+\.]*\w++))");
    
    std::string data = "abc_dj@madj.jd 1234.asd  hkdhkshga def@laocom 346j ratr 5678_df@mail.ru  roguorug 435 hij@phystech.edu ajsd@mail.ru.gmail.com";

    std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
    std::sregex_iterator end;

   std::for_each(begin, end, [](const std::smatch & m)
    {
        for (std::size_t i = 0; i < m.size(); ++i)
        {
            std::cout << (is_email_valid(m[0]) ? "valid" : "invalid") << " | " <<  m[i] << " | " ;
        }
        std::cout << std::endl;
    });
    
    std::system("pause");
    
    return EXIT_SUCCESS;
}
