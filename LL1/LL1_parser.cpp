#include <iostream>

#include <vector>
#include <string>

//globalne zmienne
bool czy_poprawny;
const std::vector<char> first_C{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9' };
const std::vector<char> first_O{ '*', ':', '+', '-', '^' };
const std::vector<char> first_P{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9', ')' };
const std::vector<char> first_W{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9', ')' };
const std::vector<char> first_S{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9', ')' };

bool czy_nalezy_do_pierwszych(char znak, std::vector<char> sprawdzany_wektor);
//void wywolaj_funkcje(char znak);
void parse_C(std::string ss, unsigned int numer_znaku);
void parse_O(std::string ss, unsigned int numer_znaku);
void parse_P(std::string ss, unsigned int* numer_znaku);
void parse_W(std::string ss, unsigned int* numer_znaku);
void parse_S(std::string ss, unsigned int* numer_znaku);
void komunikat_o_zlym_znaku(unsigned int indeks_znaku, std::string ss, std::vector<char> wektor);

int main()
{
    std::string napis;
    unsigned int indeks_znaku, rozmiar;
    std::cout << "Wpisz dzialania arytmetyczne porozdzielane srednikami (nie pisz spacji):" << std::endl;
    std::getline(std::cin, napis);
    rozmiar = napis.size();
    indeks_znaku = 0;
    czy_poprawny = true;
    parse_S(napis, &indeks_znaku);
    if (!czy_poprawny)
    {
        std::cout << "dobry" << std::endl;
    }
    else
    {
        std::cout << "Niedobry" << std::endl;
    }
    return 0;
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

/*void wywolaj_funkcje(char znak)
{
    if (czy_nalezy_do_pierwszych(znak, first_C))
    {
        //parse_C(znak);
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
}*/

void parse_C(std::string ss, unsigned int numer_znaku)
{
    char znak = ss[numer_znaku];
    if (!czy_poprawny) { return; }
    if (czy_nalezy_do_pierwszych(znak, first_C))
    {
        //nic bo to terminal?
    }
    else
    {
        czy_poprawny = false;
    }
    return;
}

void parse_O(std::string ss, unsigned int numer_znaku)
{
    char znak = ss[numer_znaku];
    if (!czy_poprawny) { return; }
    if (czy_nalezy_do_pierwszych(znak, first_O))
    {
        //nic bo to terminal?
    }
    else
    {
        czy_poprawny = false;
    }
    return;
}

void parse_P(std::string ss, unsigned int* numer_znaku)
{
    char znak = ss[*numer_znaku];
    //TODO
    if (znak == '(')
    {
        *numer_znaku += 1;
        parse_W(ss, numer_znaku);
        *numer_znaku += 1;
        znak = ss[*numer_znaku];
        if (znak != ')')
        {
            czy_poprawny = false;
            return;
        }
    }
    else
    {
        while (czy_nalezy_do_pierwszych(ss[*numer_znaku], first_C))
        {
            parse_C(ss, *numer_znaku);
            *numer_znaku += 1;
        }
        if (ss[*numer_znaku] == '.')
        {
            *numer_znaku += 1;
            while (czy_nalezy_do_pierwszych(ss[*numer_znaku], first_C))
            {
                parse_C(ss, *numer_znaku);
                *numer_znaku += 1;
            }
        }
    }
    return;
}

void parse_W(std::string ss, unsigned int* numer_znaku)
{
    char znak = ss[*numer_znaku];
    if (!czy_poprawny) { return; }
    if (czy_nalezy_do_pierwszych(znak, first_P))
    {
        parse_P(ss, numer_znaku);
        while (czy_nalezy_do_pierwszych(znak, first_O))
        {
            parse_O(ss, *numer_znaku);
            *numer_znaku += 1;
            parse_P(ss, numer_znaku);
        }
    }
    else
    {
        czy_poprawny = false;
    }
    return;
}

void parse_S(std::string ss, unsigned int* numer_znaku)
{
    char znak = ss[*numer_znaku];
    if (czy_nalezy_do_pierwszych(znak, first_S))
    {
        parse_W(ss, numer_znaku);
        unsigned int gdzie_srednik = ss.find_first_of(';', *numer_znaku);
        if (gdzie_srednik != std::string::npos)
        {
            *numer_znaku = gdzie_srednik + 1;
            parse_W(ss, numer_znaku);
        }
        else
        {
            czy_poprawny = false;
        }
    }
    else 
    {
        czy_poprawny = false;
    }
    return;
}

void komunikat_o_zlym_znaku(unsigned int indeks_znaku, std::string ss, std::vector<char> wektor)
{
    char znak = ss[indeks_znaku];
    std::cout << "Error! Na pozycji " << indeks_znaku << " jest \"" << znak << "\" zamiast jednego z tych: ";
    unsigned int a;
    for (a = 0; a < wektor.size(); a++)
    {
        std::cout << "\'" << wektor[a] << "\'";
        if (a != wektor.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    return;
}