#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string testowany;

    std::string L = "\\-?[0-9]+(\\.[0-9]+)?";
    std::string P = "(\\+|\\-|\\*|\\/)";
    std::string W1 = L;
    std::string W2 = "\\(" + L + "(" + P + L + ")+\\)";
    std::string W = "("+ W1 + "|" + W2 + ")";
    std::string S = W + "(" + P + W + ")+";
    std::string Y = S + "(\\;" + S + ")*";

    std::cout << "Wpisz dzialania na liczbach (jesli kilka to rozdziel je srednikami, bez odstepow):" << std::endl;
    std::getline(std::cin, testowany);

    std::cout << "\nCzy \""<< testowany <<"\" pasuje do wzorca?" << std::endl;
    std::regex wyrazenie_regularne(Y);
    if (std::regex_match(testowany, wyrazenie_regularne))
    {
        std::cout << "Pasuje" << std::endl;
    }
    else
    {
        std::cout << "Nie pasuje" << std::endl;
    }
    std::cout << "\n---\nwyrazenie regularne:\n" << Y << "\n----\n";
    return 0;
}
