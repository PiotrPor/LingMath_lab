#include <iostream>
#include <vector>
#include <string>

/*
Gramatyka (przed upraszczaniem diagramow skladniowych)
S ::= W;Z
Z ::= W;Z | ε
W ::= PT
T ::= OW | ε
P ::= R | (W)
R ::= LF
F ::= .L | ε
L ::= CM
M ::= L | ε
C ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
O ::= * | : | + | - | ^
*/

//globalne zmienne
bool czy_poprawny; //poniewaz to globalna zmienna, to wszystkie funkcje i main() maja do niej dostep
//abiory symboli pierwszych (dla produkcji, ktore sa na uproszczonym diagramie skladniowym)
const std::vector<char> first_C{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9' };
const std::vector<char> first_O{ '*', ':', '+', '-', '^' };
const std::vector<char> first_P{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9', '(' };
const std::vector<char> first_W{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9', '(' };
const std::vector<char> first_S{ '0','1', '2', '3', '4', '5', '6', '7', '8', '9', '(' };

bool czy_nalezy_do_pierwszych(char znak, std::vector<char> sprawdzany_wektor); //sprawdza czy dany znak nalezy do symboli pierwszych
void parse_C(std::string ss, unsigned int numer_znaku); //odpowiada produkcji "C" z uproszczonego diagramu skladniowego
void parse_O(std::string ss, unsigned int numer_znaku); //...
void parse_P(std::string ss, unsigned int* numer_znaku); //odpowiada produkcji "P" z uproszczonego diagramu skladniowego
void parse_W(std::string ss, unsigned int* numer_znaku);
void parse_S(std::string ss, unsigned int* numer_znaku);
void komunikat_o_zlym_znaku(unsigned int indeks_znaku, std::string ss, std::vector<char> wektor); //gdy znak nie jest symbolem pierwszym
void komunikat_nieten_znak(unsigned int indeks_znaku, char spodziewany, char napotkany); //gdy to inny znak niz sie spodziewano

//-------------------------------
//       MAIN
//-------------------------------

int main()
{
    std::string napis; //do tego 'string' wpisze napis podany przez uzytkownika
    unsigned int indeks_znaku; //potrzebne zmienne
    //unsigned int rozmiar;
    std::cout << "Wpisz dzialania arytmetyczne porozdzielane srednikami (nie pisz spacji):" << std::endl;
    std::getline(std::cin, napis);
    //rozmiar = napis.size();
    indeks_znaku = 0;
    czy_poprawny = true;
    parse_S(napis, &indeks_znaku);
    if (czy_poprawny)
    {
        std::cout << "Ciag zgodny z gramatyka" << std::endl;
    }
    else
    {
        std::cout << "Ciag niezgodny z gramatyka" << std::endl;
    }
    return 0;
}

//-------------------------------
//         FUNKCJE
//-------------------------------

//czy podany znak nalezy do podanego zbioru symboli pierwszych
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

//odpowiada produkcji "C" z uproszczonego diagramu skladniowego
void parse_C(std::string ss, unsigned int numer_znaku)
{
    char znak = ss[numer_znaku];
    if (!czy_poprawny) //nie analizuje ciagu jesli jest niepoprawny 
    { return; }
    if (czy_nalezy_do_pierwszych(znak, first_C)) //czy nalezy do symboli pierwszych produkcji C
    {
        //nic nie robi bo to terminal
    }
    else
    {
        czy_poprawny = false;
        komunikat_o_zlym_znaku(numer_znaku, ss, first_C); //bo nie nalezy do symboli pierwszych
    }
    return;
}

//odpowiada produkcji "O" z uproszczonego diagramu skladniowego
void parse_O(std::string ss, unsigned int numer_znaku)
{
    char znak = ss[numer_znaku];
    if (!czy_poprawny) //nie analizuje ciagu jesli jest niepoprawny 
    { return; }
    if (czy_nalezy_do_pierwszych(znak, first_O)) //czy nalezy do symboli pierwszych produkcji O
    {
        //nic nie robi bo to terminal
    }
    else
    {
        czy_poprawny = false;
        komunikat_o_zlym_znaku(numer_znaku, ss, first_O); //bo nie nalezy do symboli pierwszych
    }
    return;
}

//odpowiada produkcji "P" z uproszczonego diagramu skladniowego
void parse_P(std::string ss, unsigned int* numer_znaku)
{
    char znak = ss[*numer_znaku];
    if (!czy_poprawny) //nie analizuje ciagu jesli jest niepoprawny 
    { return; }
    if (znak == '(') //czy pierwsze co napotka to "(" (potrzebne do wyboru strony alternatywy)
    {
        *numer_znaku += 1;
        parse_W(ss, numer_znaku); //po otwarciu nawiasu jest produkcja "W"
        *numer_znaku += 1;
        znak = ss[*numer_znaku];
        if (znak != ')') //jesli po "W" nie zamknieto nawiasu
        {
            czy_poprawny = false;
            komunikat_nieten_znak(*numer_znaku, ')', znak);
            return;
        }
    }
    else
    {
        parse_C(ss, *numer_znaku); // jesli "P" nie zaczyna sie od nawiasu, to zaczyna sie od pierwszej cyfry liczby
        *numer_znaku += 1;
        while (czy_nalezy_do_pierwszych(ss[*numer_znaku], first_C)) //czy po pierwszej cyfrze sa kolejne cyfry
        {
            parse_C(ss, *numer_znaku);
            *numer_znaku += 1;
        }
        if (ss[*numer_znaku] == '.') //jesli potem jest kropka (od ulamkow dziesietnych)
        {
            *numer_znaku += 1;
            parse_C(ss, *numer_znaku); //po kropce jest cyfra
            *numer_znaku += 1;
            while (czy_nalezy_do_pierwszych(ss[*numer_znaku], first_C)) //po niej moga byc nastepne cyfry
            {
                parse_C(ss, *numer_znaku);
                *numer_znaku += 1;
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

//odpowiada produkcji "W" z uproszczonego diagramu skladniowego
void parse_W(std::string ss, unsigned int* numer_znaku)
{
    char znak = ss[*numer_znaku];
    if (!czy_poprawny) { return; }
    parse_P(ss, numer_znaku);
    *numer_znaku += 1;
    while (czy_nalezy_do_pierwszych(ss[*numer_znaku], first_O))
    {
        parse_O(ss, *numer_znaku);
        *numer_znaku += 1;
        parse_P(ss, numer_znaku);
        *numer_znaku += 1;
    }
    *numer_znaku -= 1;
    return;
}

//odpowiada produkcji "S" z uproszczonego diagramu skladniowego
void parse_S(std::string ss, unsigned int* numer_znaku)
{
    char znak = ss[*numer_znaku];
    if (!czy_poprawny) { return; }
    bool czy_ma_pracowac = true;
    while(czy_ma_pracowac) //w zapetleniu przechodzi przez kolejne "W;"
    {
        parse_W(ss, numer_znaku);
        *numer_znaku += 1;
        znak = ss[*numer_znaku];
        if(znak == ';') //czy po "W" jest srednik
        {
            if (*numer_znaku >= ss.size()-1)
            {
                czy_ma_pracowac = false; //srednik na koncu napisu, wiec mozna skonczyc prace
            }
        }
        else
        {
            czy_poprawny = false; //bo po "W" nie ma srednika
            komunikat_nieten_znak(*numer_znaku, ';', znak);
        }
    }
    return;
}

void komunikat_o_zlym_znaku(unsigned int indeks_znaku, std::string ss, std::vector<char> wektor)
{
    char znak = ss[indeks_znaku];
    unsigned int a;
    std::cout << "Error! Na pozycji " << indeks_znaku << " jest \"" << znak << "\", spoza zbioru: ";
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