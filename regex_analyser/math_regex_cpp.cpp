#include <iostream>
#include <string>
#include <regex>

/*
  GRAMATYKA
Y ::= S{;S}
S ::= WPW{PW}
W ::= L | (LPL{PL})
L ::= C{C}D | -C{C}D
D ::= .C{C} | ?
C ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
P ::= + | - | * | /
*/

/*
(\\-?[0-9]+(\\.[0-9]+)?|\\(\\-?[0-9]+(\\.[0-9]+)?([\\+\\-\\*\\/]\\-?[0-9]+(\\.[0-9]+)?)+\\))([\\+\\-\\*\\/](\\-?[0-9]+(\\.[0-9]+)?|\\(\\-?[0-9]+(\\.[0-9]+)?([\\+\\-\\*\\/]\\-?[0-9]+(\\.[0-9]+)?)+\\)))+(\\;(\\-?[0-9]+(\\.[0-9]+)?|\\(\\-?[0-9]+(\\.[0-9]+)?([\\+\\-\\*\\/]\\-?[0-9]+(\\.[0-9]+)?)+\\))([\\+\\-\\*\\/](\\-?[0-9]+(\\.[0-9]+)?|\\(\\-?[0-9]+(\\.[0-9]+)?([\\+\\-\\*\\/]\\-?[0-9]+(\\.[0-9]+)?)+\\)))+)*
*/

int main()
{
    std::string testowany; //tutaj uzytkownik wpisze dzialanie/a
    //moje wyrazenie regularne
    std::string regex_tekst = "(\\-?[0-9]+(\\.[0-9]+)?|\\(\\-?[0-9]+(\\.[0-9]+)?([\\+\\-\\*\\/]\\-?[0-9]+(\\.[0-9]+)?)+\\))([\\+\\-\\*\\/](\\-?[0-9]+(\\.[0-9]+)?|\\(\\-?[0-9]+(\\.[0-9]+)?([\\+\\-\\*\\/]\\-?[0-9]+(\\.[0-9]+)?)+\\)))+(\\;(\\-?[0-9]+(\\.[0-9]+)?|\\(\\-?[0-9]+(\\.[0-9]+)?([\\+\\-\\*\\/]\\-?[0-9]+(\\.[0-9]+)?)+\\))([\\+\\-\\*\\/](\\-?[0-9]+(\\.[0-9]+)?|\\(\\-?[0-9]+(\\.[0-9]+)?([\\+\\-\\*\\/]\\-?[0-9]+(\\.[0-9]+)?)+\\)))+)*";

    std::cout << "Wpisz dzialania na liczbach (jesli kilka to rozdziel je srednikami, bez odstepow):" << std::endl;
    std::getline(std::cin, testowany); //to co wpisze uzytkownik jest zapisane do string'a

    std::cout << "\nCzy \""<< testowany <<"\" pasuje do wzorca?" << std::endl; //wypisze to co podal uzytkownik
    std::regex wyrazenie_regularne(regex_tekst); //tekstowo zapisane wyrazenie regularne bedzie teraz rozumiane przez program
    if (std::regex_match(testowany, wyrazenie_regularne)) //czy podany string pasuje do wyrazenia regularnego
    {
        std::cout << "Pasuje" << std::endl;
    }
    else
    {
        std::cout << "Nie pasuje" << std::endl;
    }
    std::cout << "\n---\nwyrazenie regularne:\n" << regex_tekst << "\n----\n"; //wupisze wyrazenie regularne
    return 0;
}
