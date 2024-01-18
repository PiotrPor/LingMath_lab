#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string testowany = "25.02";
    std::string testowany2 = "4+20*0.25";
    std::string testowany3 = "(2+0.1)";
    std::string testowany4 = "2.4*(5+4/2)";
    //
    std::string L = "\\-?[0-9]+(\\.[0-9]+)?";
    std::string P = "(\\+|\\-|\\*|\\/)";

    std::string W1 = L;
    std::string W2 = "\\(" + L + "(" + P + L + ")+\\)";
    std::string W = "("+ W1 + "|" + W2 + ")";
    std::string S = W + "(" + P + W + ")+";

    //std::string wzorzec_bez_nawiasu = "\\-?[0-9]+(\\.[0-9]+)?((\\+|\\-|\\*|\\/)\\-?[0-9]+(\\.[0-9]+)?)*";
    //std::string bez_nawiasu_2 = L + "(" + P + L + ")*";
    //
    std::cout << testowany4 << std::endl;
    std::regex wyrazenie_regularne(S);
    if (std::regex_match(testowany4, wyrazenie_regularne))
    {
        std::cout << "Pasuje" << std::endl;
    }
    else
    {
        std::cout << "Nie pasuje do wzorca" << std::endl;
    }
    std::cout << "\n---\n----\n" << S << "\n---\n----\n";
    return 0;
}
