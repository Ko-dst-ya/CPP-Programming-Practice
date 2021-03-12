#include <iostream>
#include <string>
#include <regex>

bool is_email_valid(const std::string& email)
{
    // define a regular expression
    const std::regex pattern
            ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    // try to match the string with the regular expression
    return std::regex_match(email, pattern);
}

int main()
{
    std::string email1 = "text.example@randomcom";
    std::string email2 = "text.example@random.com";

    std::vector < std::string > emails = {email1, email2};

    std::for_each(std::begin(emails), std::end(emails),
                  [](auto x){std::cout << x << " : " << (is_email_valid(x) ?

                  "valid" : "invalid") << std::endl;});
    
    std::system("pause");
    
    return EXIT_SUCCESS;
}
