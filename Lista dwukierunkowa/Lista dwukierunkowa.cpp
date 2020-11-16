//ALGO 2 IS1 212A LAB01
//Filip Rysz
//rf44482@zut.edu.pl

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;


struct bobo
{
	double a;
	char b;
	int c;
	double wypisz_a()
	{
		return a;
	}
	char wypisz_b()
	{
		return b;
	}
	int wypisz_c()
	{
		return c;
	}
};
// miało być data, ale jest już T* data, żebym się nie pogubił!!!

// globalne wyswietlanie, nie wiem co probowalem tym osiagnac
void print(struct bobo danewejsciowe)
{
	cout << "a: " << danewejsciowe.a << " | " << "b: " << danewejsciowe.b << " | " << "c: " << danewejsciowe.c << endl;
}

template <class T>
struct wartosc
{
	T* danewejsciowe;
	wartosc* nastepna;    // wskaźnik na następny element
	wartosc* poprzednia;   // wskaźnik na poprzedni element
	wartosc();
};

template <class T>
wartosc<T>::wartosc<T>()
{
	nastepna = poprzednia = 0;
}

//metody
template <class T>
struct lista
{
	wartosc<T>* poczatek;
	wartosc<T>* koniec;
	void dodaj_koniec(T* data);
	void dodaj_poczatek(T* data);
	void usun_pierwszy();
	void usun_ostatni();
	void wyswietl();
	T* wyswietl_indeks(int d);
	void podmiana(T* data, int d);
	wartosc<T>* wyszukanie(T* data);
	bool usuwanie_po_wyszukaniu(T* data);
	bool dodawanie_z_wymuszeniem(T* data);
	void wyczysc_liste();
	int porownanie(T* data, T* data2);
	int porownanie_char(T* data, T* data2);
	double porownanie_double(T* data, T* data2);
	int porownanie_int(T* data, T* data2);
	lista();
};

template <class T>
lista<T>::lista()
{
	poczatek = koniec = 0;
}

// problem ze zmiennymi rozwiazany ^^ struct bobo u góry
template <class T>
void lista<T>::dodaj_koniec(T* data)
{
	cout << "Rozpoczynam funkcje dodawania na koncu listy: " << endl;
	wartosc<T>* nowa = new wartosc<T>;
	nowa->danewejsciowe = data;
	if (koniec == 0)
	{
		poczatek = nowa;
		koniec = poczatek;
	}
	else
	{
		wartosc<T>* temp = koniec; //koniec listy
		koniec = nowa;
		koniec->poprzednia = temp;
		temp->nastepna = nowa;
	}
}

// problem ze zmiennymi rozwiazany ^^ struct bobo u góry
template <class T>
void lista<T>::dodaj_poczatek(T* data)
{
	cout << "Rozpoczynam funkcje dodawania na poczatku listy: " << endl;
	wartosc<T>* nowa = new wartosc<T>;
	nowa->danewejsciowe = data;

	if (poczatek == 0)
	{
		poczatek = nowa;
		koniec = poczatek;
	}
	else
	{
		wartosc<T>* temp = poczatek; //poczatek listy
		poczatek = nowa;
		poczatek->nastepna = temp;
		temp->poprzednia = nowa;
	}

}

// naprawic przy = 0
template <class T>
T* lista<T>::wyswietl_indeks(int d)
{
	if (poczatek)
	{
		cout << "Rozpoczynam funkcje wyszukiwania po indeksie: " << endl;
		if (d == 0)
		{
			wartosc<T>* temp = poczatek;
			cout << temp->danewejsciowe->wypisz_a() << " | " << temp->danewejsciowe->wypisz_b() << " | " << temp->danewejsciowe->wypisz_c() << endl;
			return poczatek->danewejsciowe;
		}
		else if (d >= 1)
		{
			wartosc<T>* temp = poczatek->nastepna;
			for (int i = 1; i != d + 1; i++)
			{
				if (i != d)
				{
					if (temp->nastepna == 0)
					{
						cout << "Nie znaleziono indeksu" << endl;
						return NULL;
					}
					temp = temp->nastepna;
				}
				else
				{
					cout << temp->danewejsciowe->wypisz_a() << " | " << temp->danewejsciowe->wypisz_b() << " | " << temp->danewejsciowe->wypisz_c() << endl;
					return temp->danewejsciowe;
				}

			}
		}
	}
	else
		cout << "lista jest pusta!!!!" << endl;
}

// petla z usun koniec
template <class T>
void lista<T>::wyczysc_liste()
{
	if (poczatek)
	{
		cout << "Rozpoczynam funkcje czyszczenia listy: " << endl;
		wartosc<T>* temp = poczatek;
		while (temp->nastepna != NULL)
		{
			poczatek = temp->nastepna;
			if (poczatek)
				poczatek->poprzednia = 0;
		}
	}
	else
		cout << "Lista jest pusta" << endl;
}

template <class T>
void lista<T>::usun_pierwszy()
{
	if (poczatek)
	{
		cout << "Rozpoczynam funkcje usuwania pierwszego elementu: " << endl;
		wartosc<T>* temp = poczatek;
		poczatek = temp->nastepna;
		if (poczatek)
			poczatek->poprzednia = 0;
		delete temp;
	}
	else
		cout << "lista jest pusta!!!!!" << endl;
}

template <class T>
void lista<T>::usun_ostatni()
{
	if (koniec)
	{
		cout << "Rozpoczynam funkcje usuwania ostatniego elementu: " << endl;
		wartosc<T>* temp = koniec;
		koniec = temp->poprzednia;
		if (koniec)
			koniec->nastepna = 0;
		delete temp;
	}
	else
		cout << "lista jest pusta!!!!" << endl;
}

template <class T>
void lista<T>::wyswietl()
{
	wartosc<T>* temp = poczatek;
	while (temp != NULL)
	{
		cout << temp->danewejsciowe->wypisz_a() << " | " << temp->danewejsciowe->wypisz_b() << " | " << temp->danewejsciowe->wypisz_c() << endl;
		temp = temp->nastepna;
	}
}

template <class T>
void lista<T>::podmiana(T* data, int d)
{
	if (poczatek)
	{
		cout << "Rozpoczynam funkcje podmiany: " << endl;
		wartosc<T>* nowa = new wartosc<T>;
		if (d == 0)
		{
			poczatek->danewejsciowe = data;
			if (poczatek->nastepna == 0)
				koniec = poczatek;
			//cout << temp->a << " " << temp->b << " " << temp->c << endl;
		}
		else if (d >= 1)
		{
			wartosc<T>* temp = poczatek->nastepna;
			for (int i = 1; i != d + 1; i++)
			{
				if (i != d)
				{
					if (temp->nastepna == 0)
					{
						cout << "Nie znaleziono indeksu" << endl;
						break;
					}
					temp = temp->nastepna;
				}
				else
				{
					temp->danewejsciowe = data;
				}
			}
		}
	}
	else
		cout << "lista jest pusta lub indeks jest poza zakresem!!!!" << endl;
}

template <class T>
int lista<T>::porownanie(T* data, T* data2)
{
	int diff = data->wypisz_c() - data2->wypisz_c();
	if (diff != 0)
		return diff;
	int diff2 = data->wypisz_b() - data2->wypisz_b();
	if (diff2 != 0)
		return diff2;
	return data->wypisz_a() - data2->wypisz_a();
}

template <class T>
int lista<T>::porownanie_char(T* data, T* data2)
{
	int diff = data->wypisz_b() - data2->wypisz_b();
	return diff;
}

template <class T>
double lista<T>::porownanie_double(T* data, T* data2)
{
	int diff = data->wypisz_a() - data2->wypisz_a();
	return diff;
}

template <class T>
int lista<T>::porownanie_int(T* data, T* data2)
{
	int diff = data->wypisz_c() - data2->wypisz_c();
	return diff;
}

template <class T>
wartosc<T>* lista<T>::wyszukanie(T* data)
{
	if (poczatek)
	{
		cout << "Rozpoczynam funkcje wyszukania: " << endl;
		wartosc<T>* nowa = new wartosc<T>;
		nowa->danewejsciowe = data;
		wartosc<T>* temp = poczatek;
		while (temp)
		{
			if (porownanie(data, temp->danewejsciowe) == 0)
				return temp;
			temp = temp->nastepna;
		}
		return NULL;
	}
	else
	{
		cout << "lista jest pusta!!!!!" << endl;
		return NULL;
	}
}

template <class T>
bool lista<T>::usuwanie_po_wyszukaniu(T* data)
{
	if (poczatek)
	{
		cout << "Rozpoczynam funkcje usuwania po wyszukaniu: " << endl;
		wartosc<T>* temp = poczatek;
		while (temp)
		{
			if (porownanie(data, temp->danewejsciowe) == 0)
			{
				if (poczatek != koniec)
				{
					if (temp->poprzednia)
					{
						temp->poprzednia->nastepna = temp->nastepna;
					}
					if (temp->nastepna)
					{
						temp->nastepna->poprzednia = temp->poprzednia;
					}
					if (poczatek == temp)
					{
						poczatek = temp->nastepna;
					}
				}
				else
				{
					poczatek = koniec = 0;
				}
				delete temp;
				return true;
			}
			temp = temp->nastepna;
		}
		cout << "Nie znaleziono elementu" << endl;
		return false;
	}
	else
	{
		cout << "lista jest pusta!!!!!" << endl;
		return false;
	}
}

template <class T>
bool lista<T>::dodawanie_z_wymuszeniem(T* data)
{
	cout << "Rozpoczynam funkcje dodawania z wymuszeniem: " << endl;
	wartosc<T>* nowa = new wartosc<T>;
	nowa->danewejsciowe = data;
	if (poczatek)
	{
		wartosc<T>* temp = poczatek;
		wartosc<T>* temp2 = poczatek;
		double min = DBL_MAX;
		int min2 = INT_MAX;
		int min3 = CHAR_MAX;
		double temp3 = 0;
		bool byl_rowny = false;
		bool byl_rowny2 = false;
		while (temp)
		{
			double nowy_double = porownanie_double(data, temp->danewejsciowe);
			if (nowy_double == 0)
			{
				byl_rowny = true;
				int nowy_int = porownanie_int(data, temp->danewejsciowe);
				if (nowy_int == 0) {
					byl_rowny2 = true;
					int nowy_char = porownanie_char(data, temp->danewejsciowe);
					if (abs(nowy_char) < min3)
					{
						min3 = abs(nowy_char);
						temp3 = nowy_char;
						temp2 = temp;
					}
				}
				else if (abs(nowy_int) < min2 && byl_rowny2 == false)
				{
					min2 = abs(nowy_int);
					temp3 = nowy_int;
					temp2 = temp;
				}
			}
			else if (abs(nowy_double) < min && byl_rowny == false)
			{
				min = abs(nowy_double);
				temp3 = nowy_double;
				temp2 = temp;
			}
			temp = temp->nastepna;
		}
		if (temp3 > 0)
		{
			nowa->nastepna = temp2->nastepna;
			nowa->poprzednia = temp2;
			if (temp2->nastepna)
				temp2->nastepna->poprzednia = nowa;
			else
				koniec = nowa;
			temp2->nastepna = nowa;
		}
		else if (temp3 < 0)
		{
			nowa->nastepna = temp2;
			nowa->poprzednia = temp2->poprzednia;
			if (temp2->poprzednia)
				temp2->poprzednia->nastepna = nowa;
			else
				poczatek = nowa;
			temp2->poprzednia = nowa;
		}
	}
	else
	{
		cout << "Lista jest pusta wiec dodaje na poczatku: " << endl;
		poczatek = nowa;
		koniec = poczatek;
	}
	return true;
}

int main()
{
	lista<struct bobo>* baza = new lista<struct bobo>; //tworzenie listy
	clock_t start, koniec;
	double czas_wykonania;
	start = clock();
	struct bobo danewejsciowe;
	danewejsciowe.a = 42.1;
	danewejsciowe.b = 'c';
	danewejsciowe.c = 40;

	baza->dodaj_poczatek(&danewejsciowe);
	baza->wyswietl();
	struct bobo danewejsciowe2;
	danewejsciowe2.a = 56.1;
	danewejsciowe2.b = 'g';
	danewejsciowe2.c = 31;

	baza->dodaj_koniec(&danewejsciowe2);

	struct bobo danewejsciowe3;
	danewejsciowe3.a = 39.6;
	danewejsciowe3.b = 'h';
	danewejsciowe3.c = 71;

	baza->dodaj_poczatek(&danewejsciowe3);
	baza->wyswietl();
	koniec = clock();
	czas_wykonania = (double)(koniec - start) / CLOCKS_PER_SEC;
	cout << "Czas wykonania: " << czas_wykonania << endl;

	struct bobo danewejsciowe4;
	danewejsciowe4.a = 39.6;
	danewejsciowe4.b = 'g';
	danewejsciowe4.c = 71;

	cout << baza->dodawanie_z_wymuszeniem(&danewejsciowe4) << endl;
	baza->wyswietl();

	/*baza->wyswietl_indeks(2);
	struct bobo danewejsciowe5;
	danewejsciowe5.a = 56.1;
	danewejsciowe5.b = 'g';
	danewejsciowe5.c = 31;

	baza->usuwanie_po_wyszukaniu(&danewejsciowe5);
	baza->wyswietl();*/

	system("pause");
}
