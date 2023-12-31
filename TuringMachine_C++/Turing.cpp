/*
  Zadanie 3 - Maszyna Turinga
  Autor: Piotr Porembinski (253488)
  Poziom trudnosci na ocene 4
*/
#include <iostream>
#include <string>
#include <vector>

//===== ENUMERATORY I STRUKTURY =====
enum Ruch //oznacza, jaki ruch glowicy ma wykonac Maszyna Turinga
{
    R,
    L,
    nic //aby oznaczyc brak ruchu
};

enum Stany //oznacza stany, w ktorych moze byc Maszyna
{
    Qs, //stan poczatkowy
    Q0, //stan, gdy dodano juz pierwsze "1" i w pamieci nie ma "1"
    Q1, //stan, gdy dodano juz pierwsze "1" i w pamieci jest "1"
    Q2, //stan, gdy dodano juz dwa "1" i w pamieci nie ma "1"
    Q3, //stan, gdy dodano juz dwa "1" i w pamieci jest "1"
    pusty
};

const char Alfabet[] = {'0','1','o'}; // "o" oznacza u mnie koniec tasmy
const char nic_nie_pisz = '-'; //do oznaczania, ze nic sie wpisuje natasme

struct Decyzja //aby mozna jednym obiektem opisac dzialanie, ktore podejmie Maszyna po wczytaniu symbolu
{
    Stany nowy_stan; //w jaki stan ma przejsc
    char wpisywany_symbol; //jaki symbol ma wpisac na tasme
    Ruch ruch; //jaki ruch ma wykonac
};

//===== KLASA =====
class MaszynaTuringa //obiekt tej klasy bedzie Maszyna Turinga, ktora bedzie wykonywac ooperacje na tasmie
{
private:
    Stany aktualny_stan; //w jakim stanie jest
    std::vector<Stany> lista_stanow;
public:
    const Stany stan_poczatkowy = Stany::Qs;
    MaszynaTuringa(); //konstruktor bezparametrowy
    std::string dodaj_trzy(std::string liczba); //do podanej liczby binarnej doda 3 i zwroci wynik (liczby jako string'i)
    Decyzja podejmij_decyzje(char ss); //na podstawie tablicy przejsc podejmie decyzje przy wczytaniu danego symbolu
    void wypisz_liste_kolejnych_stanow(); //napisze po kolei liste stanow, w ktorych byla Maszyna
};

//===== FUNKCJA =====
std::string stan_tekstowo(Stany st); //stan (jako wartosc enumeratora) przedstawiony tekstowo
std::string ruch_tekstowo(Ruch r); //ruch (jako wartosc enumeratora) przedstawiony tekstowo
std::string decyzja_jako_tekst(Decyzja DD); //zwraca tekstowy opis decyzji

//================
//===== MAIN =====

int main()
{
    std::string liczba_binarna; //to bedzie liczba binarna podana przez uzytkownika
    std::string zwiekszona_liczba; //to bedzie wynik dodania 3 do podanej liczby binarnej
    MaszynaTuringa MT; //instancja Maszyny Turinga, ktora doda 3 do liczby
    //
    std::cout << "Wpisz \'o\' a potem liczbe binarna: ";
    std::getline(std::cin, liczba_binarna); //pobranie linijki tekstu z wejscia (terminal) do string'a
    //
    std::cout << "Tasma przed: " << liczba_binarna << std::endl;
    zwiekszona_liczba = MT.dodaj_trzy(liczba_binarna); //Maszyna Turinga zwieksza liczbe o 3 i tekstowo wpisuje wynik do string'a
    std::cout << "Tasma po: " << zwiekszona_liczba << std::endl; //wypisanie wyniku
    std::cout << "Maszyna Turinga przeszla przez stany: ";
    MT.wypisz_liste_kolejnych_stanow(); //na koniec napisze, przek ktore stany przechodzila Maszyna
    return 0;
}

//===== KLASA =====

MaszynaTuringa::MaszynaTuringa() //konstruktor bezparametrowy
{
    aktualny_stan = stan_poczatkowy; //Maszyna Turinga zaczyna w stanie poczatkowym
    lista_stanow.empty();
    lista_stanow.push_back(aktualny_stan); //pierwszy stan w ktorym jest Maszyna
}

//jako parametr przyjmuje liczbe binarna (zapisana jako string)
//doda do niej 3
//wynik zwraca jako string
std::string MaszynaTuringa::dodaj_trzy(std::string liczba)
{
    std::string zwiekszona = liczba; //to bedzie wynik dzialania. To tasma dla Maszyny Turinga
    unsigned int x; //potrzebne przy petli
    Decyzja co_zrobi; //tu beda wpisywane decyzje podjete na podstawie tablicy przejsc
    x = liczba.size() - 1;
    while (x >= 0)
    {
        co_zrobi = this->podejmij_decyzje(zwiekszona[x]); //wczytuje symbol z tasmy i podejmuje decyzje
        std::cout << "Napotkano symbol \"" << zwiekszona[x] << "\"\n";
        //w jaki stan ma przejsc
        if (co_zrobi.nowy_stan != Stany::pusty) //jesli nie jest tak, ze nie zmienia stanu
        {
            aktualny_stan = co_zrobi.nowy_stan;
        }
        lista_stanow.push_back(aktualny_stan); //zapisuje w jakim jest stanie po odczytaniu tego (kolejnego) symbolu
        //jaki symbol ma wpisac na tasme
        if (co_zrobi.wpisywany_symbol != nic_nie_pisz) //jesli nie jest tak, ze nic nie wpisuje
        {
            zwiekszona[x] = co_zrobi.wpisywany_symbol;
        }
        //jaki ruch ma wykonac glowica
        if (x == 0) //jesli glowica jest juz na koncu tasmy (ruch od prawej do lewej)
        {
            if (zwiekszona[x] != Alfabet[2]) //jesli to nie symbol konca tasmy
            {
                zwiekszona.insert(0, "o"); //jeszcze bardziej na lewo dopisz symbol konca tasmy
                x++; //tym samym nie jestesmy juz na koncu tasmy
            }
        }
        if (co_zrobi.ruch != Ruch::nic) //jesli nie jest tak, ze nie ma wykonac ruchu
        {
            if (co_zrobi.ruch == Ruch::R) { x++; }
            else { x--; }
        }
        //tekstowe opisanie decyzji, ktora wlasnie zostala podjeta i zrealizowana
        std::cout << "   " << decyzja_jako_tekst(co_zrobi) << std::endl;
        //zakoncz petle jesli glowica nie bedzie juz nic robic i jest na koncu tasmy
        if (co_zrobi.nowy_stan == Stany::pusty &&
            co_zrobi.wpisywany_symbol == nic_nie_pisz && 
            co_zrobi.ruch == Ruch::nic && 
            zwiekszona[x] == Alfabet[2])
        {
            break;
        }
    }
    return zwiekszona; //zwraca tekstowo tasme (wynik dzialania)
}

//przyjmuje wczytany symbol jako parametr
//uwzgledni w decyzji rowniez aktualny stan Maszyny
//jako wynik zwroci podjeta decyzje
Decyzja MaszynaTuringa::podejmij_decyzje(char ss)
{
    Decyzja co_robic;
    switch (aktualny_stan)
    {
        case Stany::Qs: //jesli teraz Maszyna jest w stanie Qs
        {
            if (ss == Alfabet[0]) { co_robic = {Stany::Q0, Alfabet[1], Ruch::L}; } //jesli wczytal "0"
            else if (ss == Alfabet[1]) { co_robic = { Stany::Q1, Alfabet[0], Ruch::L }; } //jesli wczytal "1"
            else { co_robic = { Stany::Q0, Alfabet[1], Ruch::L }; } //jesli wczytal symbol konca tasmy
            break;
        }
        case Stany::Q0: //jesli Maszyna jest w stanie Q0
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::Q2, Alfabet[1], Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::Q3, Alfabet[0], Ruch::L }; }
            else { co_robic = { Stany::Q2, Alfabet[1], Ruch::L }; }
            break;
        }
        case Stany::Q1: //jesli Maszyna jest w stanie Q1
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
        case Stany::Q3:
        {
            if (ss == Alfabet[0]) { co_robic = { Stany::Q2, Alfabet[1], Ruch::L }; }
            else if (ss == Alfabet[1]) { co_robic = { Stany::pusty, Alfabet[0], Ruch::L }; }
            else { co_robic = { Stany::Q2, Alfabet[1], Ruch::nic }; }
            break;
        }
        default:
        {
            co_robic = { Stany::pusty, nic_nie_pisz, Ruch::nic };
            break;
        }
    }
    return co_robic; //zwraca decyzje
}

void MaszynaTuringa::wypisz_liste_kolejnych_stanow() //napisze po kolei liste stanow, w ktorych byla Maszyna
{
    unsigned int x;
    unsigned int ilosc_stanow = lista_stanow.size(); //ile stanow jest na liscie
    for (x = 0; x < ilosc_stanow; x++)
    {
        std::cout << stan_tekstowo(lista_stanow[x]);
        if (x != (ilosc_stanow-1) && ilosc_stanow > 1)
        { std::cout << ", "; }
    }
    std::cout << std::endl;
    return;
}


//===== FUNKCJE =====

std::string stan_tekstowo(Stany st) //zwraca stan (wartosc enumeratora) jako tekst (string)
{
    switch (st)
    {
        case Stany::Qs: {return "Qs"; break; }
        case Stany::Q0: {return "Q0"; break; }
        case Stany::Q1: {return "Q1"; break; }
        case Stany::Q2: {return "Q2"; break; }
        case Stany::Q3: {return "Q3"; break; }
        default: {return "[none]"; }
    }
}

std::string ruch_tekstowo(Ruch r) //zwraca kierunek/rodzaj ruchu (wartosc enumeratora) jako tekst (string)
{
    switch (r)
    {
        case Ruch::L: {return "w lewo"; break; }
        case Ruch::R: {return "w prawo"; break; }
        default: {return "[none]"; }
    }
}

std::string decyzja_jako_tekst(Decyzja DD) //zwraca tesktowy czytelny opis decyzji
{
    std::string opis; //pusty string. Bede do niego dodawal 3 zdania
    if (DD.nowy_stan != Stany::pusty) //najpierw zdanie o nowym stanie. Inne jesli nie ma zmiany stanu
    {
        opis = "Przechodzi do stanu " + stan_tekstowo(DD.nowy_stan) + ". ";
    }
    else
    {
        opis = "Nie zmienia stanu. ";
    }
    //po kropce nastepne zdanie
    if (DD.wpisywany_symbol != nic_nie_pisz)
    {
        opis += "Wpisuje \"";
        opis.append(1, DD.wpisywany_symbol); // "dopisz raz ten 'char' na koniec string'a"
        opis += "\" na tasme. ";
    }
    else
    {
        std::cout << "Nie wpisuje symbolu na tasme. ";
    }
    //po kropce nastepne zdanie
    if (DD.ruch != Ruch::nic) //zdanie rozne zaleznie od tego, czy glowica wykona ruch czy nie
    {
        opis += "Przesuwa glowice " + ruch_tekstowo(DD.ruch) + ".";
    }
    else
    {
        opis += "Glowica nie rusza sie.";
    }
    return opis; //zwraca opis (teraz to juz 3 zdania w jednym wierszu)
}
