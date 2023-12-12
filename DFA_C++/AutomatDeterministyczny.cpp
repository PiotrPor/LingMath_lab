#include "AutomatDeterministyczny.h"

#include <iostream>

AutomatDeterministyczny::AutomatDeterministyczny()
{
	stan = stan_poczatkowy;
	czy_koniec = false;
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
			if (!czy_koniec) { czy_koniec = true; }
			break;
		}
		case MozliweStany::q16:
		{
			if (!czy_koniec) { czy_koniec = true; }
			break;
		}
		case MozliweStany::q17:
		{
			if (!czy_koniec) { czy_koniec = true; }
			break;
		}
		case MozliweStany::q18:
		{
			if (!czy_koniec) { czy_koniec = true; }
			break;
		}
		case MozliweStany::q19:
		{
			if (!czy_koniec) { czy_koniec = true; }
			break;
		}
	}
	return;
}

void AutomatDeterministyczny::przedstaw_zakonczenie()
{
	switch (stan)
	{
	    case MozliweStany::q15: { std::cout << "Automat wydaje bilet." << std::endl; break; }
		case MozliweStany::q16: { std::cout << "Automat wydaje bilet i reszte 1 PLN." << std::endl; break; }
		case MozliweStany::q17: { std::cout << "Automat wydaje bilet i reszte 2 PLN." << std::endl; break; }
		case MozliweStany::q18: { std::cout << "Automat wydaje bilet i reszte 3 PLN." << std::endl; break; }
		case MozliweStany::q19: { std::cout << "Automat wydaje bilet i reszte 4 PLN." << std::endl; break; }
	}
	return;
}

bool AutomatDeterministyczny::powiedz_czy_koniec()
{
	return czy_koniec;
}

void AutomatDeterministyczny::wymuszenie_zakonczenia()
{
	czy_koniec = true;
	return;
}

void AutomatDeterministyczny::zresetuj_automat()
{
	stan = stan_poczatkowy;
	czy_koniec = false;
	return;
}

MozliweStany AutomatDeterministyczny::daj_aktualny_stan()
{
	return this->stan;
}

bool AutomatDeterministyczny::czy_jest_w_stanie_akceptujacym()
{
	bool werdykt = false;
	if (stan == MozliweStany::q15) { werdykt = true; }
	else if (stan == MozliweStany::q16) { werdykt = true; }
	else if (stan == MozliweStany::q17) { werdykt = true; }
	else if (stan == MozliweStany::q18) { werdykt = true; }
	else if (stan == MozliweStany::q19) { werdykt = true; }
	return werdykt;
}
