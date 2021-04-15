#include <iostream>
#include <string>
#include <sstream>
#include "struktury.h"
#include "funkcje.h"
using namespace std;
//main.exe -i wejscie.txt -o wyjscie.txt -s Poznan
int main(int argCount, char* args[]) {
	cout << args[0];
	if (argCount != 7) {
		cout << "B³êdna liczba parametrów";
	}
	else if (strcmp(args[1], "-i") != 0 || strcmp(args[3], "-o") != 0 || strcmp(args[5], "-s") != 0) {
		cout << "B³êdne parametry";
	}
	else {
		string nazwa_pliku_wejsciowego = args[2];
		string nazwa_pliku_wyjsciowego = args[4];
		string miasto_bazy = args[6];
		utworz_trasy_spedycyjne(nazwa_pliku_wejsciowego, nazwa_pliku_wyjsciowego, miasto_bazy);
	}
	return 0;
}