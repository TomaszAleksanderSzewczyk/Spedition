/**@file*/
#pragma once
#include <string>
using namespace std;
/** deklaracja struktury wierzcho�ka*/
struct wierzcholek_t;
/** deklaracja struktury kraw�dzi*/
struct krawedz_t;
/**deklaracja struktury wezla listy t*/
template <typename T>
struct wezel_listy_t;

/** Struktura wierzcho�ka*/
struct wierzcholek_t {
	string miasto; ///< zmienna przechowuj�ca miasto
	int aktualna_najmn_odl_od_bazy; ///< zmienna przechowuje najmniejsz� odleg�o�� od bazy, na starcie ma -1, tzn. ze jeszcze jej nie analizowali�my
	wezel_listy_t<krawedz_t*>* pierwszy_wezel_listy_krawedzi; ///<wska�nik na pierwszy w�ze� listy krawedzi
	krawedz_t* krawedz_powrotna; ///<krawedz powrotna sluzaca do odtworzenia trasy
};
/**Struktura kraw�dzi przechowuj�ca parametry odleg�o�ci*/
struct krawedz_t {
	wierzcholek_t* dokad; ///<wska�nik na docelowy wierzcho�ek
	int odleglosc; ///<zmienna przechowuj�ca odleg�o��
};
/** Struktura w�z�a listy(sparametryzowana) */
template <typename T>
struct wezel_listy_t
{
	T element; ///<element wezla listy w zale�no�ci od zmiennej T
	wezel_listy_t<T>* nastepny; ///<wska�nik na nast�pny w�ze� 
};



