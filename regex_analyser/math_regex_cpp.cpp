// math_regex_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string testowany = "25.02";
    std::string testowany2 = "4+20*0.25";
    std::string testowany3 = "(2+0.1)";
    //
    std::string L = "\\-?[0-9]+(\\.[0-9]+)?";
    std::string P = "(\\+|\\-|\\*|\\/)";

    std::string W1 = L;
    std::string W2 = "\\(" + L + P + L + "(" + P + L + ")*\\)";

    std::string wzorzec_bez_nawiasu = "\\-?[0-9]+(\\.[0-9]+)?((\\+|\\-|\\*|\\/)\\-?[0-9]+(\\.[0-9]+)?)*";
    std::string bez_nawiasu_2 = L + "(" + P + L + ")*";
    std::string W_mozliwy_nawias = W1 + "|" + W2;
    //
    std::cout << testowany3 << std::endl;
    std::regex wyrazenie_regularne(W_mozliwy_nawias);
    if (std::regex_match(testowany, wyrazenie_regularne))
    {
        std::cout << "Pasuje";
    }
    else
    {
        std::cout << "Nie pasuje do wzorca";
    }
    return 0;
}
