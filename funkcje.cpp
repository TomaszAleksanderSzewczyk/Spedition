#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "struktury.h"
#include "funkcje.h"
using namespace std;



template <typename T>
void dodaj_na_poczatek_listy(wezel_listy_t<T>*& pierwszy_wezel_listy, T& element)
{
	wezel_listy_t<T>* nowy_wezel_listy_wierzcholkow = new wezel_listy_t<T>();
	nowy_wezel_listy_wierzcholkow->element = element;
	if (pierwszy_wezel_listy)
		nowy_wezel_listy_wierzcholkow->nastepny = pierwszy_wezel_listy;
	pierwszy_wezel_listy = nowy_wezel_listy_wierzcholkow;
}

template<typename T>
void dodaj_do_listy(wezel_listy_t<T>*& pierwszy_wezel_listy, T& element)
{
	wezel_listy_t<T>* nowy_wezel = new wezel_listy_t<T>();
	nowy_wezel->element = element;
	if (pierwszy_wezel_listy)
	{
		wezel_listy_t<T>* wezel_listy = pierwszy_wezel_listy;
		while (wezel_listy->nastepny)
			wezel_listy = wezel_listy->nastepny;
		wezel_listy->nastepny = nowy_wezel;
	}
	else
		pierwszy_wezel_listy = nowy_wezel;
}


template <typename T>
void usun_pierwszy_wezel_listy(wezel_listy_t<T>*& pierwszy_wezel_listy)
{
	wezel_listy_t<T>* wezel_listy_do_usuniecia = pierwszy_wezel_listy;
	pierwszy_wezel_listy = pierwszy_wezel_listy->nastepny;
	delete wezel_listy_do_usuniecia;
}


template <typename T>
void usun_pierwszy_wezel_listy_i_element(wezel_listy_t<T>*& pierwszy_wezel_listy)
{
	T element = pierwszy_wezel_listy->element;
	usun_pierwszy_wezel_listy(pierwszy_wezel_listy);
	delete element;
}


template <typename T>
void usun_wezel_listy(wezel_listy_t<T>*& pierwszy_wezel_listy, wezel_listy_t<T>* wezel_listy_do_usuniecia)
{
	wezel_listy_t<T>* poprzedni_wezel_listy = nullptr;
	wezel_listy_t<T>* wezel_listy = pierwszy_wezel_listy;
	while (wezel_listy != wezel_listy_do_usuniecia)
	{
		poprzedni_wezel_listy = wezel_listy;
		wezel_listy = wezel_listy->nastepny;
	}
	if (poprzedni_wezel_listy)
	{
		poprzedni_wezel_listy->nastepny = wezel_listy_do_usuniecia->nastepny;
	}
	if (pierwszy_wezel_listy == wezel_listy_do_usuniecia)
	{
		pierwszy_wezel_listy = wezel_listy_do_usuniecia->nastepny;
	}
	delete wezel_listy_do_usuniecia;
}


wierzcholek_t* wybierz_wierzcholek_dla_miasta(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_wierzcholkow, const string& miasto)
{
	wezel_listy_t<wierzcholek_t*>* wezel_listy_wierzcholkow = pierwszy_wezel_listy_wierzcholkow;
	while (wezel_listy_wierzcholkow)
	{
		if (!wezel_listy_wierzcholkow->element->miasto.compare(miasto))
			return wezel_listy_wierzcholkow->element;
		wezel_listy_wierzcholkow = wezel_listy_wierzcholkow->nastepny;
	}
	wierzcholek_t* nowy_wierzcholek = new wierzcholek_t();
	nowy_wierzcholek->aktualna_najmn_odl_od_bazy = -1;
	nowy_wierzcholek->miasto = miasto;
	dodaj_na_poczatek_listy(pierwszy_wezel_listy_wierzcholkow, nowy_wierzcholek);
	return nowy_wierzcholek;
}

void dodaj_krawedz(wierzcholek_t* wierzcholek_miasta_skad, wierzcholek_t* wierzcholek_miasta_dokad, int& odleglosc)
{
	krawedz_t* nowa_krawedz = new krawedz_t();
	nowa_krawedz->dokad = wierzcholek_miasta_dokad;
	nowa_krawedz->odleglosc = odleglosc;
	dodaj_na_poczatek_listy(wierzcholek_miasta_skad->pierwszy_wezel_listy_krawedzi, nowa_krawedz);
}

void wypelnij_liste_wierzcholkow(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_wierzcholkow, const string& miasto1, const string& miasto2, int& odleglosc)
{
	wierzcholek_t* wierzcholek_miasta1 = wybierz_wierzcholek_dla_miasta(pierwszy_wezel_listy_wierzcholkow, miasto1);
	wierzcholek_t* wierzcholek_miasta2 = wybierz_wierzcholek_dla_miasta(pierwszy_wezel_listy_wierzcholkow, miasto2);
	dodaj_krawedz(wierzcholek_miasta1, wierzcholek_miasta2, odleglosc);
	dodaj_krawedz(wierzcholek_miasta2, wierzcholek_miasta1, odleglosc);
}

wezel_listy_t<wierzcholek_t*>* wybierz_wezel_nieanalizowanego_wierzcholka_najblizej_bazy(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_potencjalnych_wierzcholkow)
{
	wezel_listy_t<wierzcholek_t*>* wezel_wierzcholka_najblizej_bazy = pierwszy_wezel_listy_potencjalnych_wierzcholkow;
	wezel_listy_t<wierzcholek_t*>* wezel_wierzcholka = wezel_wierzcholka_najblizej_bazy->nastepny;
	while (wezel_wierzcholka)
	{
		if (wezel_wierzcholka->element->aktualna_najmn_odl_od_bazy < wezel_wierzcholka_najblizej_bazy->element->aktualna_najmn_odl_od_bazy)
			wezel_wierzcholka_najblizej_bazy = wezel_wierzcholka;
		wezel_wierzcholka = wezel_wierzcholka->nastepny;
	}
	return wezel_wierzcholka_najblizej_bazy;
}

void analizuj_krawedzie_wierzcholka(wierzcholek_t* analizowany_wierzcholek, wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_potencjalnych_wierzcholkow)
{
	while (analizowany_wierzcholek->pierwszy_wezel_listy_krawedzi)
	{
		krawedz_t* krawedz = analizowany_wierzcholek->pierwszy_wezel_listy_krawedzi->element;
		wierzcholek_t* dokad = krawedz->dokad;
		int odleglosc_do_celu_przez_analizowany_wierzcholek = analizowany_wierzcholek->aktualna_najmn_odl_od_bazy + krawedz->odleglosc;
		if (dokad->aktualna_najmn_odl_od_bazy == -1)
		{
			dodaj_do_listy(pierwszy_wezel_listy_potencjalnych_wierzcholkow, dokad);
		}
		if (dokad->aktualna_najmn_odl_od_bazy == -1 || dokad->aktualna_najmn_odl_od_bazy > odleglosc_do_celu_przez_analizowany_wierzcholek)
		{
			dokad->aktualna_najmn_odl_od_bazy = odleglosc_do_celu_przez_analizowany_wierzcholek;
			delete dokad->krawedz_powrotna;
			dokad->krawedz_powrotna = new krawedz_t();
			dokad->krawedz_powrotna->odleglosc = krawedz->odleglosc;
			dokad->krawedz_powrotna->dokad = analizowany_wierzcholek;
		}
		usun_pierwszy_wezel_listy_i_element(analizowany_wierzcholek->pierwszy_wezel_listy_krawedzi);
	}
}

void uzupelnij_dane_tras_od_bazy(wierzcholek_t* wierzcholek_bazy)
{
	wezel_listy_t<wierzcholek_t*>* pierwszy_wezel_listy_potencjalnych_wierzcholkow = new wezel_listy_t<wierzcholek_t*>();//PWLPW jest to wezel najblizszy bazie z ktorego mozemy sie rozgladac
	pierwszy_wezel_listy_potencjalnych_wierzcholkow->element = wierzcholek_bazy;//PWLPW staje siê wierzcho³kiem bazy
	while (pierwszy_wezel_listy_potencjalnych_wierzcholkow) {//poki mamy wierzcho³ek z ktorego mozemy siê rozgl¹dac, poki lista niepusta
		wezel_listy_t<wierzcholek_t*>* wezel_wierzcholka_najblizej_bazy = wybierz_wezel_nieanalizowanego_wierzcholka_najblizej_bazy(pierwszy_wezel_listy_potencjalnych_wierzcholkow);
		analizuj_krawedzie_wierzcholka(wezel_wierzcholka_najblizej_bazy->element, pierwszy_wezel_listy_potencjalnych_wierzcholkow);
		usun_wezel_listy(pierwszy_wezel_listy_potencjalnych_wierzcholkow, wezel_wierzcholka_najblizej_bazy);
	}
}

void wyczysc_pamiec(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_wierzcholkow)
{
	while (pierwszy_wezel_listy_wierzcholkow)
	{
		while (pierwszy_wezel_listy_wierzcholkow->element->pierwszy_wezel_listy_krawedzi)
		{
			usun_pierwszy_wezel_listy_i_element(pierwszy_wezel_listy_wierzcholkow->element->pierwszy_wezel_listy_krawedzi);
		}
		delete pierwszy_wezel_listy_wierzcholkow->element->krawedz_powrotna;
		usun_pierwszy_wezel_listy_i_element(pierwszy_wezel_listy_wierzcholkow);
	}
}

void wypisz_trasy_do_pliku(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_wierzcholkow, const string& nazwa_pliku_wyjsciowego)
{
	ofstream plik(nazwa_pliku_wyjsciowego, ofstream::out);
	wezel_listy_t<wierzcholek_t*>* wezel_listy_wierzcholkow = pierwszy_wezel_listy_wierzcholkow;
	while (wezel_listy_wierzcholkow)
	{
		wierzcholek_t* wierzcholek = wezel_listy_wierzcholkow->element;
		string trasa = wierzcholek->miasto + ": " + to_string(wierzcholek->aktualna_najmn_odl_od_bazy);
		while (wierzcholek->krawedz_powrotna)
		{
			trasa = wierzcholek->krawedz_powrotna->dokad->miasto + " -> " + trasa;
			wierzcholek = wierzcholek->krawedz_powrotna->dokad;
		}
		plik << trasa << endl;
		wezel_listy_wierzcholkow = wezel_listy_wierzcholkow->nastepny;
	}
	plik.close();
}


void utworz_trasy_spedycyjne(const string& nazwa_pliku_wejsciowego, const string& nazwa_pliku_wyjsciowego, const string& miasto_bazy)
{
	wezel_listy_t<wierzcholek_t*>* pierwszy_wezel_listy_wierzcholkow = nullptr;
	ifstream plik(nazwa_pliku_wejsciowego);
	string wiersz;
	while (getline(plik, wiersz))
	{
		stringstream wiersz_stream(wiersz);
		string miasto1;
		string miasto2;
		string string_odleglosc;
		getline(wiersz_stream, miasto1, ' ');
		getline(wiersz_stream, miasto2, ' ');
		getline(wiersz_stream, string_odleglosc, ' ');
		int odleglosc = stoi(string_odleglosc);
		wypelnij_liste_wierzcholkow(pierwszy_wezel_listy_wierzcholkow, miasto1, miasto2, odleglosc);
	}
	plik.close();
	wierzcholek_t* wierzcholek_bazy = wybierz_wierzcholek_dla_miasta(pierwszy_wezel_listy_wierzcholkow, miasto_bazy);
	wierzcholek_bazy->aktualna_najmn_odl_od_bazy = 0;
	uzupelnij_dane_tras_od_bazy(wierzcholek_bazy);
	wypisz_trasy_do_pliku(pierwszy_wezel_listy_wierzcholkow, nazwa_pliku_wyjsciowego);
	wyczysc_pamiec(pierwszy_wezel_listy_wierzcholkow);
}