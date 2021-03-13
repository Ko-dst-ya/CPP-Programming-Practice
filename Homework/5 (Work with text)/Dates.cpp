#include <iostream>
#include <string>
#include <regex>

int main()
{   
    //https://stackoverflow.com/questions/15491894/regex-to-validate-date-format-dd-mm-yyyy
    const std::regex pattern
            (R"(^(?:(?:31(\/|-|\.)(?:0?[13578]|1[02]))\1|(?:(?:29|30)(\/|-|\.)(?:0?[13-9]|1[0-2])\2))(?:(?:1[6-9]|[2-9]\d)?\d{2})$|^(?:29(\/|-|\.)0?2\3(?:(?:(?:1[6-9]|[2-9]\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\d|2[0-8])(\/|-|\.)(?:(?:0?[1-9])|(?:1[0-2]))\4(?:(?:1[6-9]|[2-9]\d)?\d{2})$)");

    std::string adf = "JLDJfd sdaj 29-0,-11 12/03/2011 354jj 3512 fdg 02/12/3544 34jg 54/34/2434";
    std::string data = "01/02/2011";

    std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
    std::sregex_iterator end;

    std::for_each(begin, end, [](const std::smatch & m)
        {
            std::cout << m[0] << std::endl;
        });

    std::system("pause");

    return EXIT_SUCCESS;
}
