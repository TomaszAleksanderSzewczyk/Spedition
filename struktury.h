/**@file*/
#pragma once
#include <string>
using namespace std;
/** deklaracja struktury wierzcho³ka*/
struct wierzcholek_t;
/** deklaracja struktury krawêdzi*/
struct krawedz_t;
/**deklaracja struktury wezla listy t*/
template <typename T>
struct wezel_listy_t;

/** Struktura wierzcho³ka*/
struct wierzcholek_t {
	string miasto; ///< zmienna przechowuj¹ca miasto
	int aktualna_najmn_odl_od_bazy; ///< zmienna przechowuje najmniejsz¹ odleg³oœæ od bazy, na starcie ma -1, tzn. ze jeszcze jej nie analizowaliœmy
	wezel_listy_t<krawedz_t*>* pierwszy_wezel_listy_krawedzi; ///<wskaŸnik na pierwszy wêze³ listy krawedzi
	krawedz_t* krawedz_powrotna; ///<krawedz powrotna sluzaca do odtworzenia trasy
};
/**Struktura krawêdzi przechowuj¹ca parametry odleg³oœci*/
struct krawedz_t {
	wierzcholek_t* dokad; ///<wskaŸnik na docelowy wierzcho³ek
	int odleglosc; ///<zmienna przechowuj¹ca odleg³oœæ
};
/** Struktura wêz³a listy(sparametryzowana) */
template <typename T>
struct wezel_listy_t
{
	T element; ///<element wezla listy w zale¿noœci od zmiennej T
	wezel_listy_t<T>* nastepny; ///<wskaŸnik na nastêpny wêze³ 
};



