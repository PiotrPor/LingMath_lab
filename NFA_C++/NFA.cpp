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

//===== TABLICE =====
//alfabet
const char AlfabetTab[7] = {'0', '1', '2', '3', 'a', 'b', 'c'};
//mozliwe stany
const Stany MozliweStany[23] = { Qs,
    Q01, Q11, Q21,  Q31,  Qa1,  Qb1,  Qc1,
    Q02, Q12, Q22,  Q32,  Qa2,  Qb2,  Qc2,
    Q03, Q13, Q23,  Q33,  Qa3,  Qb3,  Qc3,
    X,
};

//tablica przejsc
//jako 2 tablice 2D: jedna to pierwszy wiersz tabeli przejsc, druga to cala reszta
const Stany TablicaPrzejsc_wiersz_1[7][2] = {
    {Qs,Q01},{Qs,Q11},{Qs,Q21},{Qs,Q31},{Qs,Qa1},{Qs,Qb1},{Qs,Qc1},  //wiersz z tablicy dla stanu Qs 
};
const Stany TablicaPrzejsc[21][7] = {
    {Q02,X,X,X,X,X,X},  //wiersz z tablicy dla stanu Q01
    {X,Q12,X,X,X,X,X},  //wiersz z tablicy dla stanu Q11
    {X,X,Q22,X,X,X,X},  //wiersz z tablicy dla stanu Q21
    {X,X,X,Q32,X,X,X},  //...
    {X,X,X,X,Qa2,X,X},
    {X,X,X,X,X,Qb2,X},
    {X,X,X,X,X,X,Qc2},
    {Q03,X,X,X,X,X,X},  //wiersz z tablicy dla stanu Q02
    {X,Q13,X,X,X,X,X},  //wiersz z tablicy dla stanu Q12
    {X,X,Q23,X,X,X,X},  //wiersz z tablicy dla stanu Q22
    {X,X,X,Q33,X,X,X},  //...
    {X,X,X,X,Qa3,X,X},
    {X,X,X,X,X,Qb3,X},
    {X,X,X,X,X,X,Qc3},
    {Q03,Q03,Q03,Q03,Q03,Q03,Q03},  //wiersz z tablicy dla stanu Q03
    {Q13,Q13,Q13,Q13,Q13,Q13,Q13},  //wiersz z tablicy dla stanu Q13
    {Q23,Q23,Q23,Q23,Q23,Q23,Q23},
    {Q33,Q33,Q33,Q33,Q33,Q33,Q33},
    {Qa3,Qa3,Qa3,Qa3,Qa3,Qa3,Qa3},
    {Qb3,Qb3,Qb3,Qb3,Qb3,Qb3,Qb3},
    {Qc3,Qc3,Qc3,Qc3,Qc3,Qc3,Qc3}
};

//===== FUNKCJE =====

std::string stan_tekstowo(Stany ss); //zapisze dany stan (wartosc enumeratora) jako tekst
char symbol_tekstowo(Alfabet ss); //zapisze symbol alfabetu (wartosc enumeratora) jako tekst
int jaki_indeks_symbolu_w_alfabecie(Alfabet ss); //indeks znaku w tablicy 'char' odowiadajacego symbolowi alfabetu
bool czy_nalezy_do_alfabetu(char cs); //czy dany drukowalny znak nalezy do alfabetu
Alfabet wczytaj_symbol(char cs); //zmienia drukowalny znak na symbol alfabetu (wartosc enumeratora)
std::string lowercase_string(std::string str); //w string'u sprawia ze litery sa male ("A" -> "a")
void napisz_tablice_przejsc();

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
    bool czy_potrojenie_nastapilo_wsrod_cyfr(); //czy w badanym wyrazie jest jakas potrojona cyfra (z alfabetu)
    bool czy_potrojenie_nastapilo_wsrod_liter(); //czy w badanym wyrazie jest jakas potrojona litera (z alfabetu)
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
    bool trzy_wsrod_cyfr, trzy_wsrod_liter; //przyda sie przy stwierdzaniu czy w wyrazie jakis znak jest potrojony

    plik.open("plik_wejsciowy.txt"); //otwiera plik do odczytu
    if (plik.is_open()) //bedzie wykonywal czynnosci jesli poprawnie otwarto plik
    {
        std::cout << "  AUTOMAT NIEDETERMINISTYCZNY\nTablica przejsc:" << std::endl;
        napisz_tablice_przejsc();
        std::cout << "\n-----------------\n\n";
        while (std::getline(plik, ciag, '#') && nie_ma_bledu) //czytaj z pliku wyrazy (ciagi rozdzielone znakiem '#')
        {
            ciag = lowercase_string(ciag); //zmien duze litery na male
            std::cout << "  Wyraz: " << ciag << std::endl;
            AutomatNiedeterministyczny NFA; //stworz od nowa NFA
            for (x = 0; x < ciag.size(); x++) //petla by wczytywac wyraz znak po znaku
            {
                znak = ciag[x]; //w zmiennej typu "char" jest jeden znak (cyfra lub litera)
                if (czy_nalezy_do_alfabetu(znak)) //czy wczytany znak nalezy do alfabetu
                {
                    //jesli tak, to automat wykona przejscie na podstawie tego symbolu
                    NFA.wykonaj_przejscie(wczytaj_symbol(znak));
                    std::cout << "Po wczytaniu \"" << znak << "\" automat jest w stanach: ";
                    NFA.wylistuj_aktualny_stan();
                }
                else
                {
                    //jesli nien to wypisz komunikat o bledzie i zakoncz prace nad tym wyrazem
                    std::cout << "   Wczytany znak \"" << znak << "\" nie nalezy do alfabetu" << std::endl;
                    nie_ma_bledu = false;
                    break;
                }
            }
            std::cout << "Koniec analizy wyrazu" << std::endl;
            NFA.przedstaw_drzewo(); //wypisze drzewo przejsc powstale z analizy wyrazu (wiersze to kolejne galezie)
            std::cout << "Stany automatu na koniec: ";
            NFA.wylistuj_aktualny_stan(); //wypisze liste stanow, w ktorych jest na koniec automat
            trzy_wsrod_cyfr = NFA.czy_potrojenie_nastapilo_wsrod_cyfr();
            trzy_wsrod_liter = NFA.czy_potrojenie_nastapilo_wsrod_liter();
            if (trzy_wsrod_cyfr || trzy_wsrod_liter) //jesli w wyrazie bylo potrojenie to napisze o tym
            {
                std::cout << "W wyrazie bylo potrojenie wsrod ";
                if (trzy_wsrod_cyfr) { std::cout << "cyfr"; }
                if (trzy_wsrod_cyfr && trzy_wsrod_liter) { std::cout << " i "; }
                if (trzy_wsrod_liter) { std::cout << "liter"; }
                std::cout << std::endl;
            }
            else
            {
                //o braku potrojenia jakiegos znaku tez napisze
                std::cout << "W wyrazie nie bylo potrojenia zadnego symbolu" << std::endl;
            }
            std::cout << "\n\n====\n====\n"; //widoczna przerwa przed wypisaniem informacji o kolejnym wyrazie z pliku
        }
    }
    plik.close(); //zamyka plik, bo zakonczyl uzywanie go (czytanie z niego)
    return 0;
}

//===== FUNKCJE =====

std::string stan_tekstowo(Stany ss) //nazwe stanu wypisze tekstowo
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

char symbol_tekstowo(Alfabet ss) //stan (wartosc enumeratora) bedzie napisany jako drukowalny znak
{
    switch (ss)
    {
    case Alfabet::s0: { return '0'; }
    case Alfabet::s1: { return '1'; }
    case Alfabet::s2: { return '2'; }
    case Alfabet::s3: { return '3'; }
    case Alfabet::sA: { return 'a'; }
    case Alfabet::sB: { return 'b'; }
    case Alfabet::sC: { return 'c'; }
    default: { return 'X'; }
    }
}

int jaki_indeks_symbolu_w_alfabecie(Alfabet ss)
{
    int a, indeks = -1;
    char drukowalny = symbol_tekstowo(ss);
    for (a = 0; a < 7; a++)
    {
        if (drukowalny == AlfabetTab[a])
        {
            indeks = a;
            break;
        }
    }
    return indeks;
}

bool czy_nalezy_do_alfabetu(char cs) //czy podany znak (zmienna typu "char") nalezy do alfabetu
{
    int a, indeks = -1;
    for (a = 0; a < 7; a++)
    {
        if (cs == AlfabetTab[a])
        {
            indeks = a;
            break;
        }
    }
    if (indeks >= 0) { return true; }
    else { return false; }
}

Alfabet wczytaj_symbol(char cs) //przetlumaczy znak drukowalny na wartosc enumeratora (o ile znak nalezy do alfabetu)
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

std::string lowercase_string(std::string str) //w string'u zmienia duze litery na male
{
    std::string with_lowercase; //nowy string, w nim litery beda male
    unsigned int x;
    char letter_or_not;
    for (x = 0; x < str.length(); x++) //czyta podany string znak po znaku
    {
        letter_or_not = str[x];
        if (std::isalpha(letter_or_not) && !std::isdigit(letter_or_not)) //jesli jest alfanumeryczny i nie jest to cyfra
        {
            letter_or_not = (char)std::tolower((int)letter_or_not); //odpowiednik duzej litery wsrod malych liter
        }
        with_lowercase.push_back(letter_or_not); //dopisz znak do nowego string'a
    }
    return with_lowercase;
}

//===== KLASA =====

void AutomatNiedeterministyczny::zakoncz_galaz(int indeks)
{
    drzewo_przejsc[indeks].push_back(Stany::X); //na koncu galezi dopisuje roboczy stan, ktory potem sluzy do rozpoznania konca galezi
    return;
}

//parametrem wejsciowym jest aktualny stan automatu, oraz wczytany symbol
Stany AutomatNiedeterministyczny::nastepny_stan_wedlug_tablicy(Stany stan_teraz, Alfabet sym)
{
    Stany nowy_stan = Stany::X;
    int indeks_stanu=-1, indeks_symbolu; //aby spojrzec do odpowiedniej komorki tablicy przejsc
    int a;
    indeks_symbolu = jaki_indeks_symbolu_w_alfabecie(sym); //wie na ktora kolumne tablicy trzeba patrzec
    for (a = 0; a < 23; a++)
    {
        if (stan_teraz == MozliweStany[a])
        {
            indeks_stanu = a; //na ktory wiersz trzeba patrzec
            break;
        }
    }
    if (indeks_stanu == 0) //jesli aktualny stan to Qs
    {
        nowy_stan = TablicaPrzejsc_wiersz_1[indeks_symbolu][1]; //zczytuje z tego, co udaje pierwszy wiersz tablicy
    }
    if (indeks_stanu > 0) //jesli stan teraz to inny niz Qs
    {
        nowy_stan = TablicaPrzejsc[indeks_stanu - 1][indeks_symbolu]; //czyta z przeciecia wiersza i kolumny
    }
    return nowy_stan;
}

AutomatNiedeterministyczny::AutomatNiedeterministyczny() //konstruktor bezparametrowy
{
    aktualne_stany.clear();
    aktualne_stany.push_back(stan_poczatkowy); //automat na poczatku jest w stanie poczatkowym
    std::vector<Stany> punkt_startu = { Stany::Qs };
    drzewo_przejsc.push_back(punkt_startu); //drzewo przejsc zaczyna sie od stanu poczatkowego
}

void AutomatNiedeterministyczny::wykonaj_przejscie(Alfabet wczytany) //NFA wczytal symbol i na jego podstawie ma wykonac przejscie
{
    unsigned int x, rozmiar;
    Stany nowy_stan, stan_na_koncu_galezi;
    rozmiar = drzewo_przejsc.size();
    for (x = 0; x < rozmiar; x++) //automat wykona przejscie na kazdej galezi drzewa przejsc
    {
        stan_na_koncu_galezi = drzewo_przejsc[x].back(); //decyzja jest podejmowana na podstawie ostatniego stanu zapisanego na galezi
        if (stan_na_koncu_galezi != Stany::X) //jesli galez nie jest ucieta/zakonczona
        {
            nowy_stan = nastepny_stan_wedlug_tablicy(stan_na_koncu_galezi, wczytany); //jaki ma byc nowy stan (na podstawie tablicy przejsc)
            drzewo_przejsc[x].push_back(nowy_stan); //dopisz nowy stan na koncu galezi (moze to byc tez pseudo-stan oznaczajacy obciecie galezi)
        }
    }
    if (drzewo_przejsc.back().at(0) == Stany::Qs) //jesli ostatnie galaz zaczyna sie od Qs (stanu poczatkowego)
    {
        std::vector<Stany> nastepna_galaz;
        nastepna_galaz.push_back(Stany::Qs);
        drzewo_przejsc.push_back(nastepna_galaz); //doklej na koncu drzewa nowa galaz zaczynajaca sie od stanu poczatkowego 
    }
    rozmiar = drzewo_przejsc.size();
    std::vector<Stany> nowe_aktualne_stany;
    for (x = 0; x < rozmiar; x++) //posprawdza koncowki galezi drzewa, by wiedziec w jakich stanach jest automat
    {
        if (drzewo_przejsc[x].back() != Stany::X)
        {
            nowe_aktualne_stany.push_back(drzewo_przejsc[x].back());
        }
    }
    aktualne_stany = nowe_aktualne_stany; //nowa zaktualizowana lista stanow automatu
    return;
}

//tekstowo przedstaw drzewo przejsc
//kolejne wiersze/linijki to galezie
//kolejne stany z galezi wpisywane sa od lewej do prawej
void AutomatNiedeterministyczny::przedstaw_drzewo()
{
    unsigned int a, b;
    for (a = 0; a < drzewo_przejsc.size(); a++)
    {
        for (b = 0; b < drzewo_przejsc[a].size(); b++)
        {
            if (b > 0)
            {
                std::cout << " -> ";
            } //miedzy kolejnymi stanami jest strzalka (bo NFA przechodzil od stanu do stanu)
            std::cout << stan_tekstowo(drzewo_przejsc[a][b]);
        }
        if (a < (drzewo_przejsc.size() - 1))
        {
            //miedzzy kolejnymi galeziami jest linia laczaca
            //wedlug tabeli przejsc przy kazdym wczytanym symbolu nie tylko przechodzi sie do Q01, Q02, .., Qc1
            //ale tez powstaje nowa galaz zaczynajaca sie od Qs
            std::cout << std::endl << "|";
        }
        std::cout << std::endl;
    }
    return;
}

void AutomatNiedeterministyczny::wylistuj_aktualny_stan() //wypisz tesktowostany z listy stanow w jakich jest automat
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

//na podstawie stanow NFA stwierdzi czy w badanym wyrazie jakas cyfra byla potrojona
bool AutomatNiedeterministyczny::czy_potrojenie_nastapilo_wsrod_cyfr()
{
    bool czy_jest_trojka = false;
    unsigned int x;
    for (x = 0; x < aktualne_stany.size(); x++) //przeszukuje liste aktualnych stanow automatu
    {
        if (aktualne_stany[x] == Stany::Q03 || aktualne_stany[x] == Stany::Q13 ||
            aktualne_stany[x] == Stany::Q23 || aktualne_stany[x] == Stany::Q33)
        {
            czy_jest_trojka = true;
            break;
        }
    }
    return czy_jest_trojka;
}

//na podstawie stanow NFA stwierdzi czy w badanym wyrazie jakas litera byla potrojona
bool AutomatNiedeterministyczny::czy_potrojenie_nastapilo_wsrod_liter()
{
    bool czy_jest_3 = false;
    unsigned int x;
    for (x = 0; x < aktualne_stany.size(); x++) //przeszukuje liste aktualnych stanow automatu
    {
        if (aktualne_stany[x] == Stany::Qa3 || aktualne_stany[x] == Stany::Qb3 || aktualne_stany[x] == Stany::Qc3)
        {
            czy_jest_3 = true;
            break;
        }
    }
    return czy_jest_3;
}

//kolumna z wynikiem przejscia ma szerokosc 8
//kolumna z aktualnym stanem ma szerokosc 4
void napisz_tablice_przejsc()
{
    int a, b, c;
    std::string oznaczenie_stanu;
    //naglowek (tytuly kolumn)
    std::cout << "    |";
    for (a = 0; a < 7; a++)
    { std::cout << "    " << AlfabetTab[a] << "   |"; }
    std::cout << std::endl;
    //pierwszy wiersz
    std::cout << "Qs  |";
    for (a = 0; a < 7; a++)
    {
        std::cout << " " << stan_tekstowo(TablicaPrzejsc_wiersz_1[a][0]);
        std::cout << "," << stan_tekstowo(TablicaPrzejsc_wiersz_1[a][1]) << " |";
    }
    std::cout << std::endl;
    //nastepne wiersze tablicy
    for (a = 1; a < 23; a++)
    {
        std::cout << stan_tekstowo(MozliweStany[a]);
        if (MozliweStany[a] == Stany::X) { std::cout << "  "; } //by byla rowna szerokosc kolumny
        std::cout << " |";
        for (b = 0; b < 7; b++)
        {
            oznaczenie_stanu = stan_tekstowo(TablicaPrzejsc[a - 1][b]);
            std::cout << "   " << oznaczenie_stanu;
            for (c = 3 + oznaczenie_stanu.length(); c <= 7; c++) // "X" i "Qa2" maja rozna dlugosc
            { std::cout << " "; }
            std::cout << "|";
        }
        std::cout << std::endl;
    }
    return;
}