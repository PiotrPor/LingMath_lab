/*
  Zadanie 2 - Automat Niedeterministyczny
  Autor: Piotr Porembinski (253488)
  Poziom: na ocene 4
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//===== ENUMERATORY =====

enum Stany //stany w jakich moze byc automat
{
    Qs, //stan startowy
    Q01, //stan gdy wykryto "0" raz
    Q11, //stan gdy wykryto "1" raz
    Q21, //...
    Q31, //...
    Qa1, //stan gdy wykryto "a" raz
    Qb1, //...
    Qc1,
    Q02, //stan gdy wykryto "0" dwa razy
    Q12, //stan gdy wykryto "1" dwa razy
    Q22,
    Q32,
    Qa2,
    Qb2,
    Qc2,
    Q03, //stan gdy wykryto "0" trzy razy
    Q13, //stan gdy wykryto "1" trzy razy
    Q23, //...
    Q33,
    Qa3,
    Qb3,
    Qc3,
    X //to nie stan automatu, pseudo-stan potrzebny do oznaczenia koncowki ucietej galezi
};

enum Alfabet //alfabet nad ktorym zdefiniowano automat
{
    s0, //oznacza "0"
    s1, // "1"
    s2, // "2"
    s3, // "3"
    sA, // "a"
    sB, // "b"
    sC, // "c"
};

std::string stan_tekstowo(Stany ss); //zapisze dany stan (wartosc enumeratora) jako tekst
std::string symbol_tekstowo(Alfabet ss); //zapisze symbol alfabetu (warrtosc enumeratora) jako tekst
bool czy_nalezy_do_alfabetu(char cs); //czy dany drukowalny znak nalezy do alfabetu
Alfabet wczytaj_symbol(char cs); //zmienia drukowalny znak na symbol alfabetu (wartosc enumeratora)
std::string lowercase_string(std::string str); //w string'u sprawia ze litery sa male ("A" -> "a")

//===== KLASA =====
class AutomatNiedeterministyczny //klasa symuluje funkcjonowanie Skonczonego Automatu Niedeterministycznego (NFA)
{
private:
    std::vector<Stany> aktualne_stany; //NFA moze byc w wiecej niz 1 stanie jednoczesnie (dlatego ma tablice o zmiennym rozmiarze)
    std::vector<std::vector<Stany>> drzewo_przejsc; //tu zapisane jest drzewo przejsc jako tablica 2D (wiersze to galezie)
    void zakoncz_galaz(int indeks); //funkcja do oznaczania w drzewie przejsc zakonczenia/uciecia galezi
    Stany nastepny_stan_wedlug_tablicy(Stany stan_teraz, Alfabet sym); //z tablicy przejsc odczyta jaki ma byc nastepny stan
public:
    const Stany stan_poczatkowy = Stany::Qs; //stan  poczatkowy automatu
    AutomatNiedeterministyczny(); //konstruktor bezparametrowy
    void wykonaj_przejscie(Alfabet wczytany); //wykonaj przejscie na podstawie wczytanego symbolu alfabetu
    void przedstaw_drzewo(); //przedstawi drzewo przejsc powstale podczas pracy automatu
    void wylistuj_aktualny_stan(); //wypisze, w jakich stanach jest teraz NFA
};

//===========================
//===== MAIN =====

int main()
{
    std::ifstream plik;
    std::string ciag; //to beda kolejne wyrazy odczytane z pliku
    unsigned int x; //zmienna pomocnicza
    char znak; //zmienna pomocnicza
    bool nie_ma_bledu = true; //do oznaczenia bledu jesli wczyta sie symbol spoza alfabetu

    plik.open("plik_wejsciowy.txt"); //otwiera plik do odczytu
    if (plik.is_open()) //bedzie wykonywal czynnosci jesli poprawnie otwarto plik
    {
        while (std::getline(plik, ciag, '#') && nie_ma_bledu) //czytaj z pliku wyrazy (ciagi rozdzielone znakiem '#')
        {
            ciag = lowercase_string(ciag); //zmien duze litery na male
            std::cout << "  Wyraz: " << ciag << std::endl;
            AutomatNiedeterministyczny NFA; //stworz od nowa NFA
            for (x = 0; x < ciag.size(); x++) //petla by wczytywac wyraz znak po znaku
            {
                znak = ciag[x];
                if (czy_nalezy_do_alfabetu(znak))
                {
                    NFA.wykonaj_przejscie(wczytaj_symbol(znak));
                }
                else
                {
                    std::cout << "   Wczytany znak \"" << znak << "\" nie nalezy do alfabetu" << std::endl;
                    nie_ma_bledu = false;
                    break;
                }
            }
            std::cout << "Koniec analizy wyrazu" << std::endl;
            NFA.przedstaw_drzewo();
            std::cout << "Stany automatu na koniec: ";
            NFA.wylistuj_aktualny_stan();
            std::cout << "\n\n====\n====\n";
        }
    }
    plik.close();
    return 0;
}

//===== FUNKCJE =====

std::string stan_tekstowo(Stany ss)
{
    switch (ss)
    {
        case Stany::Qs: { return "Qs"; }
        case Stany::Q01: { return "Q01"; }
        case Stany::Q11: { return "Q11"; }
        case Stany::Q21: { return "Q21"; }
        case Stany::Q31: { return "Q31"; }
        case Stany::Qa1: { return "Qa1"; }
        case Stany::Qb1: { return "Qb1"; }
        case Stany::Qc1: { return "Qc1"; }
        case Stany::Q02: { return "Q02"; }
        case Stany::Q12: { return "Q12"; }
        case Stany::Q22: { return "Q22"; }
        case Stany::Q32: { return "Q32"; }
        case Stany::Qa2: { return "Qa2"; }
        case Stany::Qb2: { return "Qb2"; }
        case Stany::Qc2: { return "Qc2"; }
        case Stany::Q03: { return "Q03"; }
        case Stany::Q13: { return "Q13"; }
        case Stany::Q23: { return "Q23"; }
        case Stany::Q33: { return "Q33"; }
        case Stany::Qa3: { return "Qa3"; }
        case Stany::Qb3: { return "Qb3"; }
        case Stany::Qc3: { return "Qc3"; }
        default: { return "X"; }
    }
}

std::string symbol_tekstowo(Alfabet ss)
{
    switch (ss)
    {
        case Alfabet::s0: { return "0"; }
        case Alfabet::s1: { return "1"; }
        case Alfabet::s2: { return "2"; }
        case Alfabet::s3: { return "3"; }
        case Alfabet::sA: { return "a"; }
        case Alfabet::sB: { return "b"; }
        case Alfabet::sC: { return "c"; }
        default: { return "X"; }
    }
}

bool czy_nalezy_do_alfabetu(char cs)
{
    bool czy_nalezy;
    if (cs == '0' || cs == '1' || cs == '2' || cs == '3') { czy_nalezy = true; }
    else if (cs == 'a' || cs == 'b' || cs == 'c') { czy_nalezy = true; }
    else { czy_nalezy = false; }
    return czy_nalezy;
}

Alfabet wczytaj_symbol(char cs)
{
    Alfabet drukowalny_jako_symbol;
    switch (cs)
    {
        case '0': { drukowalny_jako_symbol = Alfabet::s0; break; }
        case '1': { drukowalny_jako_symbol = Alfabet::s1; break; }
        case '2': { drukowalny_jako_symbol = Alfabet::s2; break; }
        case '3': { drukowalny_jako_symbol = Alfabet::s3; break; }
        case 'a': { drukowalny_jako_symbol = Alfabet::sA; break; }
        case 'b': { drukowalny_jako_symbol = Alfabet::sB; break; }
        case 'c': { drukowalny_jako_symbol = Alfabet::sC; break; }
    }
    return drukowalny_jako_symbol;
}

std::string lowercase_string(std::string str)
{
    std::string with_lowercase;
    unsigned int x;
    char letter_or_not;
    for (x = 0; x < str.length(); x++)
    {
        letter_or_not = str[x];
        if (std::isalpha(letter_or_not) && !std::isdigit(letter_or_not))
        {
            letter_or_not = (char)std::tolower((int)letter_or_not);
        }
        with_lowercase.push_back(letter_or_not);
    }
    return with_lowercase;
}

//===== KLASA =====

void AutomatNiedeterministyczny::zakoncz_galaz(int indeks)
{
    drzewo_przejsc[indeks].push_back(Stany::X);
    return;
}

Stany AutomatNiedeterministyczny::nastepny_stan_wedlug_tablicy(Stany stan_teraz, Alfabet sym)
{
    Stany nowy_stan;
    switch (stan_teraz)
    {
        case Stany::Qs:
        {
            switch (sym)
            {
            case s0: { nowy_stan = Stany::Q01; break; }
            case s1: { nowy_stan = Stany::Q11; break; }
            case s2: { nowy_stan = Stany::Q21; break; }
            case s3: { nowy_stan = Stany::Q31; break; }
            case sA: { nowy_stan = Stany::Qa1; break; }
            case sB: { nowy_stan = Stany::Qb1; break; }
            case sC: { nowy_stan = Stany::Qc1; break; }
            }
            break;
        }
        case Stany::Q01:
        {
            if (sym == Alfabet::s0) { nowy_stan = Stany::Q02; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Q11:
        {
            if (sym == Alfabet::s1) { nowy_stan = Stany::Q12; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Q21:
        {
            if (sym == Alfabet::s2) { nowy_stan = Stany::Q22; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Q31:
        {
            if (sym == Alfabet::s3) { nowy_stan = Stany::Q32; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Qa1:
        {
            if (sym == Alfabet::sA) { nowy_stan = Stany::Qa2; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Qb1:
        {
            if (sym == Alfabet::sB) { nowy_stan = Stany::Qb2; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Qc1:
        {
            if (sym == Alfabet::sC) { nowy_stan = Stany::Qc2; }
            else { nowy_stan = Stany::X; }
            break;
        }
        //-----------------------------------
        case Stany::Q02:
        {
            if (sym == Alfabet::s0) { nowy_stan = Stany::Q03; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Q12:
        {
            if (sym == Alfabet::s1) { nowy_stan = Stany::Q13; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Q22:
        {
            if (sym == Alfabet::s2) { nowy_stan = Stany::Q23; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Q32:
        {
            if (sym == Alfabet::s3) { nowy_stan = Stany::Q33; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Qa2:
        {
            if (sym == Alfabet::sA) { nowy_stan = Stany::Qa3; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Qb2:
        {
            if (sym == Alfabet::sB) { nowy_stan = Stany::Qb3; }
            else { nowy_stan = Stany::X; }
            break;
        }
        case Stany::Qc2:
        {
            if (sym == Alfabet::sC) { nowy_stan = Stany::Qc3; }
            else { nowy_stan = Stany::X; }
            break;
        }
        //stany gdzie juz wczytano 3 identyczne symbole jeden po drugim
        case Stany::Q03: { nowy_stan = Stany::Q03; break; }
        case Stany::Q13: { nowy_stan = Stany::Q13; break; }
        case Stany::Q23: { nowy_stan = Stany::Q23; break; }
        case Stany::Q33: { nowy_stan = Stany::Q33; break; }
        case Stany::Qa3: { nowy_stan = Stany::Qa3; break; }
        case Stany::Qb3: { nowy_stan = Stany::Qb3; break; }
        case Stany::Qc3: { nowy_stan = Stany::Qc3; break; }
        default: { nowy_stan = Stany::X; }
    }
    return nowy_stan;
}

AutomatNiedeterministyczny::AutomatNiedeterministyczny()
{
    aktualne_stany.clear();
    aktualne_stany.push_back(stan_poczatkowy);
    std::vector<Stany> punkt_startu = { Stany::Qs };
    drzewo_przejsc.push_back(punkt_startu);
}

void AutomatNiedeterministyczny::wykonaj_przejscie(Alfabet wczytany)
{
    unsigned int x, rozmiar;
    Stany nowy_stan, stan_na_koncu_galezi;
    rozmiar = drzewo_przejsc.size();
    for (x = 0; x < rozmiar; x++)
    {
        stan_na_koncu_galezi = drzewo_przejsc[x].back();
        if (stan_na_koncu_galezi != Stany::X)
        {
            nowy_stan = nastepny_stan_wedlug_tablicy(stan_na_koncu_galezi, wczytany);
            drzewo_przejsc[x].push_back(nowy_stan);
        }
    }
    if (drzewo_przejsc.back().at(0) == Stany::Qs)
    {
        std::vector<Stany> nastepna_galaz;
        nastepna_galaz.push_back(Stany::Qs);
        drzewo_przejsc.push_back(nastepna_galaz);
    }
    rozmiar = drzewo_przejsc.size();
    std::vector<Stany> nowe_aktualne_stany;
    for (x = 0; x < rozmiar; x++)
    {
        if (drzewo_przejsc[x].back() != Stany::X)
        {
            nowe_aktualne_stany.push_back(drzewo_przejsc[x].back());
        }
    }
    aktualne_stany = nowe_aktualne_stany;
    return;
}

void AutomatNiedeterministyczny::przedstaw_drzewo()
{
    unsigned int a, b;
    for (a = 0; a < drzewo_przejsc.size(); a++)
    {
        for (b = 0; b < drzewo_przejsc[a].size(); b++)
        {
            if (b > 0) 
            { std::cout << " -> "; }
            std::cout << stan_tekstowo(drzewo_przejsc[a][b]);
        }
        if (a < (drzewo_przejsc.size() - 1))
        {
            std::cout << std::endl << "|";
        }
        std::cout << std::endl;
    }
    return;
}

void AutomatNiedeterministyczny::wylistuj_aktualny_stan()
{
    unsigned int x;
    for (x = 0; x < aktualne_stany.size(); x++)
    {
        if (x > 0) 
        {
            std::cout << ", ";
        }
        std::cout << stan_tekstowo(aktualne_stany[x]);
    }
    std::cout << std::endl;
    return;
}
