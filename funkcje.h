/**@file*/
#pragma once

#include <string>

using namespace std;
/**Funkcja tworzy trasy spedycyjne 
@param nazwa_pliku_wejsciowego
@param nazwa_pliku_wyjsciowego
@param nazwa_miasta_bazy */
void utworz_trasy_spedycyjne(const string& nazwa_pliku_wejsciowego, const string& nazwa_pliku_wyjsciowego, const string& nazwa_miasta_bazy);


/**Funkcja dodaje w zale�no�ci od parametru T na pocz�tek listy
@param pierwszy_wezel_listy
@param element*/
template<typename T>
void dodaj_na_poczatek_listy(wezel_listy_t<T>*& pierwszy_wezel_listy, T& element);

/** Funkcja dodaje do listy
@param pierwszy_wezel_listy
@param element*/
template <typename T>
void dodaj_do_listy(wezel_listy_t<T>*& pierwszy_wezel_listy, T& element);
/**Funkcja usuwa pierwszy wezel listy 
@param pierwszy_wezel_listy*/
template <typename T>
void usun_pierwszy_wezel_listy(wezel_listy_t<T>*& pierwszy_wezel_listy);

/**Funkcja usuwa pierwszy wezel listy 
@param pierwszy_wezel_listy*/
template <typename T>
void usun_pierwszy_wezel_listy_i_element(wezel_listy_t<T>*& pierwszy_wezel_listy);

/**Funkcja usuwa wezel listy
@param pierwszy_wezel_listy
@param wezel_listy_do_usuniecia*/
template <typename T>
void usun_wezel_listy(wezel_listy_t<T>*& pierwszy_wezel_listy, wezel_listy_t<T>* wezel_listy_do_usuniecia);
/**Wypisuje trasy do konsoli
@param pierwszy_wezel_listy_wierzcholkow
@param nazwa_pliku_wyjsciowego*/
void wypisz_trasy_do_pliku(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_wierzcholkow, const string& nazwa_pliku_wyjsciowego);

/** Funkcja czy�ci pami�� 
@param pierwszy_wezel_listy_wierzcholkow*/
void wyczysc_pamiec(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_wierzcholkow);

/**Algorytm znajduj�cy najkr�tsze trasy z wierzcho�ka bazy(Dijkstra)
@param wierzcholek_bazy*/
void uzupelnij_dane_tras_od_bazy(wierzcholek_t* wierzcholek_bazy);
/**Funkcja przejrzy wszystkie kraw�dzie wierzcho�ka najbli�ej bazy,
pousuwa te kraw�dzie jednocze�nie aktualizuj�c odleg�o�ci od bazy wszystkich wierzcho�k�w
do kt�rych prowadzi�y kraw�dzie, kt�re sprawi�yby, �e znaleziona droga by�aby kr�tksza
a nast�pnie usuwa z listy wierzcho�k�w wierzcho�ek najbli�ej bazy, bo zosta� przeanalizowany
@param analizowany_wierzcholek
@param pierwszy_wezel_listy_potencjalnych_wierzcholkow*/
void analizuj_krawedzie_wierzcholka(wierzcholek_t* analizowany_wierzcholek, wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_potencjalnych_wierzcholkow);

/**Funkcja wybiera wierzcho�ek najbli�ej bazy, kt�ry nie by� jeszcze analizowany
@param pierwszy_wezel_listy_potencjalnych_wierzcholkow
@return wezel_listy_wierzcholka*/
wezel_listy_t<wierzcholek_t*>* wybierz_wezel_nieanalizowanego_wierzcholka_najblizej_bazy(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_potencjalnych_wierzcholkow);


/** Funkcja wype�nia list� wierzcho�k�w
@param pierwszy_wezel_listy_wierzcholkow
@param miasto1
@param miasto2
@param odleglosc*/
void wypelnij_liste_wierzcholkow(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_wierzcholkow, const string& miasto1, const string& miasto2, int& odleglosc);
/** Funkcja dodaje kraw�dz do wierzcho�k�w
@param wierzcholek_miasta_skad
@param wierzcholek_miasta_dokad
@param odleglosc */
void dodaj_krawedz(wierzcholek_t* wierzcholek_miasta_skad, wierzcholek_t* wierzcholek_miasta_dokad, int& odleglosc);

/** Jezeli w liscie mamy juz dany wierzcholek to funkcja go zwraca, jezeli nie to doda go do listy i go zwroci
@param pierwszy_wezel_listy_wierzcholkow
@param miasto
@return wierzcholek */
wierzcholek_t* wybierz_wierzcholek_dla_miasta(wezel_listy_t<wierzcholek_t*>*& pierwszy_wezel_listy_wierzcholkow, const string& miasto);