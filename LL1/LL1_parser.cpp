#include <iostream>

#include <vector>
#include <string>

unsigned int indeks_znaku; //globalna zmienna

const std::vector<char> first_C{'0','1', '2', '3', '4', '5', '6', '7', '8', '9'};
const std::vector<char> first_O{'*', ':', '+', '-', '^'};
const std::vector<char> first_P{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9', ')' };
const std::vector<char> first_W{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9', ')' };
const std::vector<char> first_S{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9', ')' };

bool czy_nalezy_do_pierwszych(char znak, std::vector<char> sprawdzany_wektor);
void wywolaj_funkcje(char znak);
void parse_C(char znak);

int main()
{
    std::string napis;
    unsigned int a, rozmiar;
    std::cout << "Wpisz dzialania arytmetyczne porozdzielane srednikami (nie pisz spacji):" << std::endl;
    std::getline(std::cin, napis);
    rozmiar = napis.size();
    indeks_znaku = 0;
    while (indeks_znaku < rozmiar)
    {
        if (indeks_znaku == 0)
        {
            wywolaj_funkcje(napis[0]);
        }
    }
    return;
}

bool czy_nalezy_do_pierwszych(char znak, std::vector<char> sprawdzany_wektor)
{
    bool werdykt = false;
    unsigned int a;
    for (a = 0; a < sprawdzany_wektor.size(); a++)
    {
        if (znak == sprawdzany_wektor[a])
        {
            werdykt = true;
            break;
        }
    }
    return werdykt;
}

void wywolaj_funkcje(char znak)
{
    if (czy_nalezy_do_pierwszych(znak, first_C))
    {
        parse_C(znak);
    }
    if (czy_nalezy_do_pierwszych(znak, first_O))
    {
        //parse_C(znak);
    }
    if (czy_nalezy_do_pierwszych(znak, first_P))
    {
        //parse_C(znak);
    }
    if (czy_nalezy_do_pierwszych(znak, first_W))
    {
        //parse_C(znak);
    }
    if (czy_nalezy_do_pierwszych(znak, first_S))
    {
        //parse_C(znak);
    }
    return;
}

void parse_C(char znak)
{
    if (czy_nalezy_do_pierwszych(znak, first_C)) //?
    {
        //co tu?
    }
    return;
}