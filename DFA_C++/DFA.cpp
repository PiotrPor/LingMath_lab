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
    m1,
    m2,
    m5
};

//Ten enumerator przechowuje mozliwe stany (poprawne), w ktorych moze byc automat
enum MozliweStany
{
    q0, // "do automatu wrzucono 0 PLN"
    q1, // "do automatu wrzucono 1 PLN"
    q2,
    q3,
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
    q15, // "do automatu wrzucono 15 PLN"
    q16,
    q17,
    q18,
    q19  // "do automatu wrzucono 19 PLN"
};

//
// ========  KLASA ========

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
    void zresetuj_automat(); // potrzebne gdy nastapi blad
    MozliweStany daj_aktualny_stan(); // w jakim stanie katualnie jest automat
    bool czy_jest_w_stanie_akceptujacym();
    int ile_pieniedzy_zgromadzone();
};

//
// ========  FUNKCJE ========

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
// ========  KLASA ========

AutomatDeterministyczny::AutomatDeterministyczny() //konstruktor bezparametrowy
{
	stan = stan_poczatkowy;
}

void AutomatDeterministyczny::funkcja_przejscia(Symbole s)
{
	switch (stan)
	{
	case MozliweStany::q0:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q1; }
		if (s == Symbole::m2) { stan = MozliweStany::q2; }
		if (s == Symbole::m5) { stan = MozliweStany::q5; }
		break;
	}
	case MozliweStany::q1:
	{
		if (s == Symbole::m1) { stan = MozliweStany::q2; }
		if (s == Symbole::m2) { stan = MozliweStany::q3; }
		if (s == Symbole::m5) { stan = MozliweStany::q6; }
		break;
	}
	case MozliweStany::q2:
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
	case MozliweStany::q15:
	{
		stan = MozliweStany::q15; //nie zmienia stanu
		break;
	}
	case MozliweStany::q16:
	{
		stan = MozliweStany::q16; //nie zmienia stanu
		break;
	}
	case MozliweStany::q17:
	{
		stan = MozliweStany::q17; //nie zmienia stanu
		break;
	}
	case MozliweStany::q18:
	{
		stan = MozliweStany::q18; //nie zmienia stanu
		break;
	}
	case MozliweStany::q19:
	{
		stan = MozliweStany::q19; //nie zmienia stanu
		break;
	}
	}
	return;
}

void AutomatDeterministyczny::przedstaw_zakonczenie()
{
	switch (stan)
	{
		case MozliweStany::q15:
	    {
		    std::cout << "Automat wydaje bilet." << std::endl;
			break;
		}
		case MozliweStany::q16:
		{
			std::cout << "Automat wydaje bilet i reszte 1 PLN." << std::endl;
			break;
		}
		case MozliweStany::q17:
		{
			std::cout << "Automat wydaje bilet i reszte 2 PLN." << std::endl;
			break;
		}
		case MozliweStany::q18:
		{
			std::cout << "Automat wydaje bilet i reszte 3 PLN." << std::endl;
			break;
		}
		case MozliweStany::q19:
		{
			std::cout << "Automat wydaje bilet i reszte 4 PLN." << std::endl;
			break;
		}
		default:
		{
			break; //nic nie robi, bo przy niepoprawnym zakonczeniu nie trzeba opisywac zakonczenia
		}
	}
	return;
}

void AutomatDeterministyczny::zresetuj_automat()
{
	stan = stan_poczatkowy;
	return;
}

MozliweStany AutomatDeterministyczny::daj_aktualny_stan()
{
	return this->stan;
}

bool AutomatDeterministyczny::czy_jest_w_stanie_akceptujacym()
{
	bool werdykt = false;
	if (stan == MozliweStany::q15)
	{
		werdykt = true;
	}
	else if (stan == MozliweStany::q16)
	{
		werdykt = true;
	}
	else if (stan == MozliweStany::q17)
	{
		werdykt = true;
	}
	else if (stan == MozliweStany::q18)
	{
		werdykt = true;
	}
	else if (stan == MozliweStany::q19)
	{
		werdykt = true;
	}
	return werdykt;
}

int AutomatDeterministyczny::ile_pieniedzy_zgromadzone()
{
	int zgromadzona_suma = 0;
	switch (stan)
	{
	case MozliweStany::q0:
	{
		zgromadzona_suma = 0;
		break;
	}
	case MozliweStany::q1:
	{
		zgromadzona_suma = 1;
		break;
	}
	case MozliweStany::q2:
	{
		zgromadzona_suma = 2;
		break;
	}
	case MozliweStany::q3:
	{
		zgromadzona_suma = 3;
		break;
	}
	case MozliweStany::q4:
	{
		zgromadzona_suma = 4;
		break;
	}
	case MozliweStany::q5:
	{
		zgromadzona_suma = 5;
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
		zgromadzona_suma = 15;
		break;
	}
	case MozliweStany::q16:
	{
		zgromadzona_suma = 16;
		break;
	}
	case MozliweStany::q17:
	{
		zgromadzona_suma = 17;
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
// ========  FUNKCJE ========

bool czy_nalezy_do_alfabetu(char sym)
{
    return (sym == '1' || sym == '2' || sym == '5');
}

Symbole zamien_na_symbol(char sym)
{
    Symbole symbol_alfabetu;
    if (sym == '1')
    {
        symbol_alfabetu = Symbole::m1;
    }
    else if (sym == '2')
    {
        symbol_alfabetu = Symbole::m2;
    }
    else
    {
        symbol_alfabetu = Symbole::m5;
    }
    return symbol_alfabetu;
}

std::string stan_jako_string(MozliweStany s)
{
    std::string tekstowo;
    if (s == MozliweStany::q0) { tekstowo = "q0"; }
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