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
void komunikat_nieten_znak(unsigned int indeks_znaku, char spodziewany, char napotkany);

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
    if (czy_poprawny)
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
    std::cout << "Parse C" << std::endl;
    std::cout << "C: znak " << numer_znaku << std::endl;
    if (czy_nalezy_do_pierwszych(znak, first_C))
    {
        //nic bo to terminal?
    }
    else
    {
        czy_poprawny = false;
        komunikat_o_zlym_znaku(numer_znaku, ss, first_C);
    }
    return;
}

void parse_O(std::string ss, unsigned int numer_znaku)
{
    char znak = ss[numer_znaku];
    if (!czy_poprawny) { return; }
    std::cout << "Parse O" << std::endl;
    std::cout << "O: znak " << numer_znaku << std::endl;
    if (czy_nalezy_do_pierwszych(znak, first_O))
    {
        //nic bo to terminal?
    }
    else
    {
        czy_poprawny = false;
        komunikat_o_zlym_znaku(numer_znaku, ss, first_O);
    }
    return;
}

void parse_P(std::string ss, unsigned int* numer_znaku)
{
    char znak = ss[*numer_znaku];
    std::cout << "Parse P" << std::endl;
    std::cout << "P: znak " << *numer_znaku << std::endl;
    if (znak == '(')
    {
        *numer_znaku += 1;
        std::cout << "P: znak " << *numer_znaku << std::endl;
        parse_W(ss, numer_znaku);
        std::cout << "P: znak " << *numer_znaku <<" po parse_W w nawiasie"<< std::endl;
        *numer_znaku += 1;
        std::cout << "P: znak " << *numer_znaku << " (sprawdzi czy to nawias zamykajacy)"<<std::endl;
        znak = ss[*numer_znaku];
        if (znak != ')')
        {
            czy_poprawny = false;
            komunikat_nieten_znak(*numer_znaku, ')', znak);
            return;
        }
    }
    else
    {
        parse_C(ss, *numer_znaku);
        *numer_znaku += 1;
        std::cout << "P: znak " << *numer_znaku << " po pierwszej cyfrze"<<std::endl;
        while (czy_nalezy_do_pierwszych(ss[*numer_znaku], first_C))
        {
            parse_C(ss, *numer_znaku);
            *numer_znaku += 1;
            std::cout << "P: znak " << *numer_znaku << std::endl;
        }
        if (ss[*numer_znaku] == '.')
        {
            *numer_znaku += 1;
            std::cout << "P: znak " << *numer_znaku <<" po kropce"<< std::endl;
            parse_C(ss, *numer_znaku);
            *numer_znaku += 1;
            std::cout << "P: znak " << *numer_znaku << " po cyfrze po kropce"<<std::endl;
            while (czy_nalezy_do_pierwszych(ss[*numer_znaku], first_C))
            {
                parse_C(ss, *numer_znaku);
                *numer_znaku += 1;
                std::cout << "P: znak " << *numer_znaku << std::endl;
            }
            *numer_znaku -= 1;
        }
        else
        {
            *numer_znaku -= 1;
        }
    }
    return;
}

void parse_W(std::string ss, unsigned int* numer_znaku)
{
    char znak = ss[*numer_znaku];
    if (!czy_poprawny) { return; }
    std::cout << "Parse W" << std::endl;
    std::cout << "W: znak " << *numer_znaku << std::endl;
    parse_P(ss, numer_znaku);
    *numer_znaku += 1;
    std::cout << "W: znak " << *numer_znaku << std::endl;
    std::cout << "  sprawdzi czy " << *numer_znaku << " to operator\n";
    while (czy_nalezy_do_pierwszych(ss[*numer_znaku], first_O))
    {
        std::cout << "  to byl operator" << std::endl;
        parse_O(ss, *numer_znaku);
        *numer_znaku += 1;
        std::cout << "W: znak " << *numer_znaku << " po parse_O"<<std::endl;
        parse_P(ss, numer_znaku);
        *numer_znaku += 1;
        std::cout << "W: znak " << *numer_znaku << " po prarse_P"<<std::endl;
    }
    *numer_znaku -= 1;
    return;
}

void parse_S(std::string ss, unsigned int* numer_znaku)
{
    char znak = ss[*numer_znaku];
    if (!czy_poprawny) { return; }
    bool czy_ma_pracowac = true;
    std::cout << "Parse S" << std::endl;
    std::cout << "S: znak " << *numer_znaku << std::endl;
    while(czy_ma_pracowac)
    {
        std::cout << "S: znak " << *numer_znaku <<" przed uruchomieniem parse_W" << std::endl;
        parse_W(ss, numer_znaku);
        *numer_znaku += 1;
        std::cout << "S: znak " << *numer_znaku <<" po parse_W" << std::endl;
        //unsigned int gdzie_srednik = ss.find_first_of(';', *numer_znaku);
        //if (gdzie_srednik != std::string::npos)
        znak = ss[*numer_znaku];
        std::cout << "  S sprawdzi czy to \";\"" << std::endl;
        if(znak == ';')
        {
            if (*numer_znaku >= ss.size()-1)
            {
                czy_ma_pracowac = false;
            }
            else
            {
                //  //*numer_znaku = gdzie_srednik + 1;
                //parse_W(ss, numer_znaku);
                //std::cout << "S: znak " << *numer_znaku << std::endl;
            }
        }
        else
        {
            czy_poprawny = false;
            komunikat_nieten_znak(*numer_znaku, ';', znak);
        }
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

void komunikat_nieten_znak(unsigned int indeks_znaku, char spodziewany, char napotkany)
{
    std::cout << "Error! Na pozycji "<<indeks_znaku<<" jest \"" << napotkany << "\" zamiast \"" << spodziewany << "\"" << std::endl;
    return;
}