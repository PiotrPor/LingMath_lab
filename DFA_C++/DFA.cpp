/*
  Zadanie 1 - Automat deterministyczny
  Autor: Piotr Porembinski (253488)
  Poziom: ocena dobra
*/

#include <iostream>
#include <string>
#include <vector>

// ========  ENUMERATORY ========

//Ten enumerator sluzy za alfabet. Ma w sobie 3 mozliwe symbole wejsciowe
enum Symbole
{
    m1, //symbolizuje znak "1" na wejsciu, ktory symbolizuje monete 1 PLN
    m2, //symbolizuje znak "2" na wejsciu, ktory symbolizuje monete 2 PLN
    m5  //symbolizuje znak "5" na wejsciu, ktory symbolizuje monete 5 PLN
};

//Ten enumerator przechowuje mozliwe stany (poprawne), w ktorych moze byc automat
enum MozliweStany
{
    q0, //symoblizuje, ze do automatu wrzucono 0 PLN
    q1, //symoblizuje, ze do automatu wrzucono 1 PLN
    q2, // ... 2 PLN
    q3, //... itd.
    q4,
    q5,
    q6,
    q7,
    q8,
    q9,
    q10,
    q11,
    q12,
    q13,
    q14,
    q15, //symbolizuje, ze do automatu wrzucono 15 PLN
    q16,
    q17,
    q18,
    q19  //symbolizuje, ze do automatu wrzucono 19 PLN
};

//
// ========  KLASA (jej deklaracja) ========

//obiekt tej klasy bedzie automatem deterministycznym
class AutomatDeterministyczny
{
private:
    MozliweStany stan; //w jakim stanie jest automat
public:
    const MozliweStany stan_poczatkowy = MozliweStany::q0; // stan poczatkowy automatu
    AutomatDeterministyczny(); //konstruktor bezparametrowy
    void funkcja_przejscia(Symbole s); //po otrzymaniu symbolu automat zmienia stan
    void przedstaw_zakonczenie(); // napisze "bardziej ludzki" opis sytuacji na koniec pracy automatu
    MozliweStany daj_aktualny_stan(); // w jakim stanie katualnie jest automat
    bool czy_jest_w_stanie_akceptujacym();
    int ile_pieniedzy_zgromadzone();
};

//
// ========  FUNKCJE (ich deklaracje) ========

bool czy_nalezy_do_alfabetu(char sym); //czy wczytany symbol nalezy do alfabetu ("1", "2" i "5")
Symbole zamien_na_symbol(char sym); //symbol (jako 'char') zmieniony na symbol jako wartosc z enumeratora
std::string stan_jako_string(MozliweStany s); //tekstowe oznaczenie stanu, w jakim teraz jest automat

/*
* 
    ================
    ====  MAIN  ====
*/

int main()
{
    //najpierw tworze zmienne potrzebne w programie
	AutomatDeterministyczny DFA; //nasz automat (stworzony kontruktorem bezparametrowym)
    char wczytany_znak; //znak wpisany na klawiaturze
    Symbole symbol_na_wejscie; //symbol z alfabetu, podawany do automatu
    std::string nazwa_stanu; //tekstowe nazwanie, w jakim stanie jest automat
    std::vector<std::string> lista_kolejnych_stanow; //przez jakie stany przechodzi automat w czasie pracy programu
    unsigned int x; //zmienna potrzebna w petli pozniej

    /*
	  w ramach ponizszej petli automat bedzie przyjmowal symbole i dzialal
	  petla bedzie przerwana przez blad lub stan akceptujacy automatu
	*/
    while (!DFA.czy_jest_w_stanie_akceptujacym())
    {
        std::cin >> wczytany_znak; //wczytaj z klawiatury jeden znak (uzytkownik podaje jakby symbol wejsciowy)
        if (czy_nalezy_do_alfabetu(wczytany_znak)) //czy mozna powiedziec, ze nalezy do alfabetu
        {
            symbol_na_wejscie = zamien_na_symbol(wczytany_znak); //zamiana z 'char' na odpowiadajacy mu symbol z alfabetu
            DFA.funkcja_przejscia(symbol_na_wejscie); //automat dostaje symbol i na podstawie tablicy przejsc zmienia stan
            nazwa_stanu = stan_jako_string(DFA.daj_aktualny_stan()); //tesktowa nazwa stanu automatu, potrzebne do komunikatow w konsoli
            std::cout << "Teraz jest w stanie " << nazwa_stanu; //komunikat do konsoli
            lista_kolejnych_stanow.push_back(nazwa_stanu); //stan trafia na liste stanow, w ktorych byl automat
            std::cout << " i ma juz w sobie " << DFA.ile_pieniedzy_zgromadzone() << " PLN" << std::endl; //ciag dalszy komunikatu
        }
        else //jesli wczytany symbol nie nalezy do automatu
        {
            std::cout << "Error: \""<< wczytany_znak <<"\" to symbol spoza alfabetu" << std::endl; //komunikat o bledzie
            break; //przerwanie petli bez wprowadzania automatu w stan akceptujacy
        }
    }
    //
    if (DFA.czy_jest_w_stanie_akceptujacym()) //czy po zakonczeniu analizy ciagu automat jest w stanie akceptujacym
    {
        DFA.przedstaw_zakonczenie(); //napisze jaki jest efekt pracy (wyda bilet, ale czy takze reszte?)
        std::cout << "Automat przeszedl przez stany: " << stan_jako_string(DFA.stan_poczatkowy); //wypisze przez jakie stany przeszedl automat
        for (x = 0; x < lista_kolejnych_stanow.size(); x++) //petla potrzebna przy wypisywaniu stanow
        {
            std::cout << " -> " << lista_kolejnych_stanow[x];
        }
        std::cout << std::endl; //koniec wypisywania stanow
    }
    return 0;
}

//
// ========  KLASA (definicje jej metod) ========

AutomatDeterministyczny::AutomatDeterministyczny() //konstruktor bezparametrowy
{
	stan = stan_poczatkowy; //na poczatku automat jest w stanie akceptujacym
}

void AutomatDeterministyczny::funkcja_przejscia(Symbole s) //dziala jak przechodzenie po tablicy przejsc
{
	switch (stan) //podejmie decyzje na podstawie aktualnego stanu automatu
	{
	case MozliweStany::q0: //jest automat jest teraz w stanie q0
	{
		if (s == Symbole::m1) { stan = MozliweStany::q1; } //przechodzi w stan q1
		if (s == Symbole::m2) { stan = MozliweStany::q2; } //przechodzi w stan q2
		if (s == Symbole::m5) { stan = MozliweStany::q5; } //przechodzi w stan q5
		break;
	}
	case MozliweStany::q1: //jesli jest teraz w stanie q1
	{
		if (s == Symbole::m1) { stan = MozliweStany::q2; } //przechodzi w stan...
		if (s == Symbole::m2) { stan = MozliweStany::q3; }
		if (s == Symbole::m5) { stan = MozliweStany::q6; }
		break;
	}
	case MozliweStany::q2: //jesli jest teraz w stanie... itd
	{
		if (s == Symbole::m1) { stan = MozliweStany::q3; }
		if (s == Symbole::m2) { stan = MozliweStany::q4; }
		if (s == Symbole::m5) { stan = MozliweStany::q7; }
		break;
	}
	case MozliweStany::q3:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q4; }
		if (s == Symbole::m2) { stan = MozliweStany::q5; }
		if (s == Symbole::m5) { stan = MozliweStany::q8; }
		break;
	}
	case MozliweStany::q4:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q5; }
		if (s == Symbole::m2) { stan = MozliweStany::q6; }
		if (s == Symbole::m5) { stan = MozliweStany::q9; }
		break;
	}
	case MozliweStany::q5:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q6; }
		if (s == Symbole::m2) { stan = MozliweStany::q7; }
		if (s == Symbole::m5) { stan = MozliweStany::q10; }
		break;
	}
	case MozliweStany::q6:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q7; }
		if (s == Symbole::m2) { stan = MozliweStany::q8; }
		if (s == Symbole::m5) { stan = MozliweStany::q11; }
		break;
	}
	case MozliweStany::q7:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q8; }
		if (s == Symbole::m2) { stan = MozliweStany::q9; }
		if (s == Symbole::m5) { stan = MozliweStany::q12; }
		break;
	}
	case MozliweStany::q8:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q9; }
		if (s == Symbole::m2) { stan = MozliweStany::q10; }
		if (s == Symbole::m5) { stan = MozliweStany::q13; }
		break;
	}
	case MozliweStany::q9:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q10; }
		if (s == Symbole::m2) { stan = MozliweStany::q11; }
		if (s == Symbole::m5) { stan = MozliweStany::q14; }
		break;
	}
	case MozliweStany::q10:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q11; }
		if (s == Symbole::m2) { stan = MozliweStany::q12; }
		if (s == Symbole::m5) { stan = MozliweStany::q15; }
		break;
	}
	case MozliweStany::q11:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q12; }
		if (s == Symbole::m2) { stan = MozliweStany::q13; }
		if (s == Symbole::m5) { stan = MozliweStany::q16; }
		break;
	}
	case MozliweStany::q12:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q13; }
		if (s == Symbole::m2) { stan = MozliweStany::q14; }
		if (s == Symbole::m5) { stan = MozliweStany::q17; }
		break;
	}
	case MozliweStany::q13:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q14; }
		if (s == Symbole::m2) { stan = MozliweStany::q15; }
		if (s == Symbole::m5) { stan = MozliweStany::q18; }
		break;
	}
	case MozliweStany::q14:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q15; }
		if (s == Symbole::m2) { stan = MozliweStany::q16; }
		if (s == Symbole::m5) { stan = MozliweStany::q19; }
		break;
	}
	case MozliweStany::q15: //jesli jest w stanie q15 (jeden ze stanow akceptujacych)
	{
		stan = MozliweStany::q15; //nie zmienia stanu
		break;
	}
	case MozliweStany::q16: //jesli jest w stanie q16 (jeden ze stanow akceptujacych)
	{
		stan = MozliweStany::q16; //nie zmienia stanu
		break;
	}
	case MozliweStany::q17: //stan q17 to tez stan akceptujacy
	{
		stan = MozliweStany::q17; //nie zmienia stanu
		break;
	}
	case MozliweStany::q18: //to tez stan akceptujacy
	{
		stan = MozliweStany::q18; //nie zmienia stanu
		break;
	}
	case MozliweStany::q19: // q19 to ostatni ze stanow akceptujacych
	{
		stan = MozliweStany::q19; //nie zmienia stanu
		break;
	}
	}
	return;
}

void AutomatDeterministyczny::przedstaw_zakonczenie() //opisuje tekstowo rezultat po zakonczeniu analizy ciagu przez automat
{
	switch (stan)
	{
		case MozliweStany::q15: //jesli stan akceptujacy, w ktorym zakonczyl, to q15 (wrzucono do niego 15 PLN)
	    {
		    std::cout << "Automat wydaje bilet." << std::endl;
			break;
		}
		case MozliweStany::q16: //jesli stan akceptujacy, w ktorym zakonczyl, to q16 (wrzucono do niego 16 PLN)
		{
			std::cout << "Automat wydaje bilet i reszte 1 PLN." << std::endl;
			break;
		}
		case MozliweStany::q17: //zakonczyl w stanie q17
		{
			std::cout << "Automat wydaje bilet i reszte 2 PLN." << std::endl;
			break;
		}
		case MozliweStany::q18: //zakonczyl w stanie q17
		{
			std::cout << "Automat wydaje bilet i reszte 3 PLN." << std::endl;
			break;
		}
		case MozliweStany::q19: //zakonczyl w stanie q17
		{
			std::cout << "Automat wydaje bilet i reszte 4 PLN." << std::endl;
			break;
		}
		default:
		{
			//nic nie robi, bo przy niepoprawnym zakonczeniu nie bedzie opisywane zakonczenie
			// "main()" juz zajmie sie wypisaniem bledu
			break;
		}
	}
	return;
}

MozliweStany AutomatDeterministyczny::daj_aktualny_stan() //zwraca, w jakim stanie jest automat (metoda "getter")
{
	return this->stan;
}

bool AutomatDeterministyczny::czy_jest_w_stanie_akceptujacym() //zwraca TRUE jesli automat jest w stanie akceptujacym, inaczej zwraca FALSE
{
	bool werdykt = false;
	if (stan == MozliweStany::q15) //jest w stanie q15 (jeden ze stanow akceptujacych)
	{
		werdykt = true;
	}
	else if (stan == MozliweStany::q16) //jest w stanie q15
	{
		werdykt = true;
	}
	else if (stan == MozliweStany::q17) //jest w stanie q15
	{
		werdykt = true;
	}
	else if (stan == MozliweStany::q18) //jest w stanie q15
	{
		werdykt = true;
	}
	else if (stan == MozliweStany::q19) //jest w stanie q15
	{
		werdykt = true;
	}
	return werdykt;
}

int AutomatDeterministyczny::ile_pieniedzy_zgromadzone() //ile pieniedzy wrzucono juz do automatu (zwraca liczbe)
{
	int zgromadzona_suma = 0;
	switch (stan)
	{
	case MozliweStany::q0:
	{
		zgromadzona_suma = 0; //stan q0 oznacza, ze w automacie jest teraz 0 PLN
		break;
	}
	case MozliweStany::q1:
	{
		zgromadzona_suma = 1; //stan q1 oznacza, ze w automacie jest teraz 1 PLN
		break;
	}
	case MozliweStany::q2:
	{
		zgromadzona_suma = 2; //stan q2 oznacza, ze w automacie jest teraz 2 PLN
		break;
	}
	case MozliweStany::q3:
	{
		zgromadzona_suma = 3; //to oznacza, ze jest 3 PLN
		break;
	}
	case MozliweStany::q4:
	{
		zgromadzona_suma = 4; //to oznacza, ze 4 PLN
		break;
	}
	case MozliweStany::q5:
	{
		zgromadzona_suma = 5; //... itd.
		break;
	}
	case MozliweStany::q6:
	{
		zgromadzona_suma = 6;
		break;
	}
	case MozliweStany::q7:
	{
		zgromadzona_suma = 7;
		break;
	}
	case MozliweStany::q8:
	{
		zgromadzona_suma = 8;
		break;
	}
	case MozliweStany::q9:
	{
		zgromadzona_suma = 9;
		break;
	}
	case MozliweStany::q10:
	{
		zgromadzona_suma = 10;
		break;
	}
	case MozliweStany::q11:
	{
		zgromadzona_suma = 11;
		break;
	}
	case MozliweStany::q12:
	{
		zgromadzona_suma = 12;
		break;
	}
	case MozliweStany::q13:
	{
		zgromadzona_suma = 13;
		break;
	}
	case MozliweStany::q14:
	{
		zgromadzona_suma = 14;
		break;
	}
	case MozliweStany::q15:
	{
		zgromadzona_suma = 15; //w automacie jest juz 15 PLN
		break;
	}
	case MozliweStany::q16:
	{
		zgromadzona_suma = 16; //w automacie jest juz 16 PLN
		break;
	}
	case MozliweStany::q17:
	{
		zgromadzona_suma = 17; //... itd.
		break;
	}
	case MozliweStany::q18:
	{
		zgromadzona_suma = 18;
		break;
	}
	case MozliweStany::q19:
	{
		zgromadzona_suma = 19;
		break;
	}
	}
	return zgromadzona_suma;
}

//
// ========  FUNKCJE (ich definicje) ========

bool czy_nalezy_do_alfabetu(char sym) //czy podany znak drukowalny nalezy do alfabetu
{
	return (sym == '1' || sym == '2' || sym == '5'); //zwraca wynik operacji logicznej OR
}

Symbole zamien_na_symbol(char sym) //symbol alfabetu jako 'char' bedzie zmieniony w odpowiednia wartosc enumeratora
{
    Symbole symbol_alfabetu;
    if (sym == '1')
    {
        symbol_alfabetu = Symbole::m1; //"1" symoblizowane przez wartosc "m1" z enumeratora
    }
    else if (sym == '2')
    {
        symbol_alfabetu = Symbole::m2; //"2" symoblizowane przez wartosc "m2" z enumeratora
    }
    else
    {
        symbol_alfabetu = Symbole::m5; //"5" symoblizowane przez wartosc "m5" z enumeratora
    }
    return symbol_alfabetu;
}

std::string stan_jako_string(MozliweStany s) //zwraca oznaczenie stanu jako tekst a nie wartosc enumeratora
{
    std::string tekstowo;
    if (s == MozliweStany::q0) { tekstowo = "q0"; } //na przyklad stan oznaczany jako "q0" powoduje zwracanie tekstu "q0"
    else if (s == MozliweStany::q1) { tekstowo = "q1"; }
    else if (s == MozliweStany::q2) { tekstowo = "q2"; }
    else if (s == MozliweStany::q3) { tekstowo = "q3"; }
    else if (s == MozliweStany::q4) { tekstowo = "q4"; }
    else if (s == MozliweStany::q5) { tekstowo = "q5"; }
    else if (s == MozliweStany::q6) { tekstowo = "q6"; }
    else if (s == MozliweStany::q7) { tekstowo = "q7"; }
    else if (s == MozliweStany::q8) { tekstowo = "q8"; }
    else if (s == MozliweStany::q9) { tekstowo = "q9"; }
    else if (s == MozliweStany::q10) { tekstowo = "q10"; }
    else if (s == MozliweStany::q11) { tekstowo = "q11"; }
    else if (s == MozliweStany::q12) { tekstowo = "q12"; }
    else if (s == MozliweStany::q13) { tekstowo = "q13"; }
    else if (s == MozliweStany::q14) { tekstowo = "q14"; }
    else if (s == MozliweStany::q15) { tekstowo = "q15"; }
    else if (s == MozliweStany::q16) { tekstowo = "q16"; }
    else if (s == MozliweStany::q17) { tekstowo = "q17"; }
    else if (s == MozliweStany::q18) { tekstowo = "q18"; }
    else { tekstowo = "q19"; }
    return tekstowo;
}