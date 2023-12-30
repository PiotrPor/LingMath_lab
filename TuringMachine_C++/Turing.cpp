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
    Q0,
    Q1,
    Q2,
    Q3,
    Qe,
    pusty
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
    //
    std::cout << "Tasma przed: " << liczba_binarna << std::endl;
    zwiekszona_liczba = MT.dodaj_trzy(liczba_binarna);
    std::cout << "Tasma po: " << zwiekszona_liczba << std::endl;
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
        //stan
        if (co_zrobi.nowy_stan != Stany::pusty)
        {
            this->aktualny_stan = co_zrobi.nowy_stan;
        }
        //symbol wpisany na tasme
        if (co_zrobi.wpisywany_symbol != nic_nie_pisz)
        {
            zwiekszona[x] = co_zrobi.wpisywany_symbol;
        }
        //ruch
        if (x == 0)
        {
            if (zwiekszona[x] != Alfabet[2]) //jesli to nie symbol konca tasmy
            {
                zwiekszona.insert(0, "o");
                x++;
            }
        }
        if (co_zrobi.ruch != Ruch::nic)
        {
            if (co_zrobi.ruch == Ruch::R) { x++; }
            else { x--; }
        }
        //zakoncz petle
        if (co_zrobi.nowy_stan == Stany::pusty &&
            co_zrobi.wpisywany_symbol == nic_nie_pisz && 
            co_zrobi.ruch == Ruch::nic && 
            zwiekszona[x] == Alfabet[2])
        {
            break;
        }
    }
    return zwiekszona;
}

/*
    | 0 | 1 | Θ
Qs | Q0, 1, L | Q1, 0, L | Q0, 1, L
Q0 | Q2, 1, L | Q3, 0, L | Q2, 1, L
Q1 | Q3, -, L | Q3, -, L | Q3, 0, L
Q2 | -, -, L | -, -, L | -, -, -
Q3 | Q2, 1, L | -, 0, L | Q2, 1, -
Qe
*/
Decyzja MaszynaTuringa::podejmij_decyzje(char ss)
{
    Decyzja co_robic;
    switch (aktualny_stan)
    {
        case Stany::Qs:
        {
            if (ss == Alfabet[0]) { co_robic = {Stany::Q0, Alfabet[1], Ruch::L}; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::Q1, Alfabet[0], Ruch::L }; }
            else { co_robic = { Stany::Q0, Alfabet[1], Ruch::L }; }
            break;
        }
        case Stany::Q0:
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::Q2, Alfabet[1], Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::Q3, Alfabet[0], Ruch::L }; }
            else { co_robic = { Stany::Q2, Alfabet[1], Ruch::L }; }
            break;
        }
        case Stany::Q1:
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::Q3, nic_nie_pisz, Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::Q3, nic_nie_pisz, Ruch::L }; }
            else { co_robic = { Stany::Q3, Alfabet[0], Ruch::L }; }
            break;
        }
        case Stany::Q2:
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::L }; }
            else { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic }; }
            break;
        }
        case Stany::Q3: //todo
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::Q2, Alfabet[1], Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::pusty, Alfabet[0], Ruch::L }; }
            else { co_robic = { Stany::Q2, Alfabet[1], Ruch::nic }; }
            break;
        }
        case Stany::Qe: //todo
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic }; }
            else { co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic }; }
            break;
        }
        default:
        {
            co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic };
            break;
        }
    }
    return co_robic;
}


//===== FUNKCJE =====