/*
  Zadanie 3 - Maszyna Turinga
  Autor: Piotr Porembinski (253488)
  Poziom trudnosci na ocene 4
*/
#include <iostream>
#include <string>

//===== ENUMERATORY I STRUKTURY =====
enum Ruch
{
    R,
    L,
    nic
};

enum Stany
{
    Qs,
    Q1,
    Q2,
    Qe,
    nic
};

const char Alfabet[] = {'0','1','o'};
const char nic_nie_pisz = '-';

struct Decyzja
{
    Stany nowy_stan;
    char wpisywany_symbol;
    Ruch ruch;
};

//===== KLASA =====
class MaszynaTuringa
{
private:
    Stany aktualny_stan;
public:
    const Stany stan_poczatkowy = Stany::Qs;
    MaszynaTuringa();
    std::string dodaj_trzy(std::string liczba);
    Decyzja podejmij_decyzje(char ss);
};

//===== FUNKCJA =====


//================
//===== MAIN =====

int main()
{
    std::string liczba_binarna = "o1001";
    std::string zwiekszona_liczba;
    MaszynaTuringa MT;
    zwiekszona_liczba = MT.dodaj_trzy(liczba_binarna);
    return 0;
}

//===== KLASA =====

MaszynaTuringa::MaszynaTuringa()
{
    aktualny_stan = stan_poczatkowy;
}

std::string MaszynaTuringa::dodaj_trzy(std::string liczba)
{
    std::string zwiekszona = liczba;
    unsigned int dlugosc = liczba.size();
    unsigned int x;
    Decyzja co_zrobi;
    x = dlugosc-1;
    while (x >= 0)
    {
        co_zrobi = this->podejmij_decyzje(zwiekszona[x]);
        if (co_zrobi.nowy_stan != Stany::nic)
        {
            this->aktualny_stan = co_zrobi.nowy_stan;
        }
        //
        if (x > 0)
        {
            if (co_zrobi.wpisywany_symbol != nic_nie_pisz)
            {
                zwiekszona[x] = co_zrobi.wpisywany_symbol;
            }
            if (co_zrobi.ruch == Ruch::R) { x++; }
            else if (co_zrobi.ruch == Ruch::L) { x--; }
            else { x = x; }
        }
        else //jest na koncu, x==0
        {
            //
        }
    }
    return zwiekszona;
}

Decyzja MaszynaTuringa::podejmij_decyzje(char ss)
{
    Decyzja co_robic;
    switch (aktualny_stan)
    {
        case Stany::Qs:
        {
            if (ss == '0') {}
            else if (ss == '1') {}
            else {}
        }
        case Stany::Q1:
        {
            if (ss == '0') {}
            else if (ss == '1') {}
            else {}
        }
        case Stany::Q2:
        {
            if (ss == '0') {}
            else if (ss == '1') {}
            else {}
        }
        case Stany::Qe:
        {
            if (ss == '0') {}
            else if (ss == '1') {}
            else {}
        }
        default:
        {
            co_robic = { Stany::nic, nic_nie_pisz, Ruch::nic };
            break;
        }
    }
    return co_robic;
}


//===== FUNKCJE =====