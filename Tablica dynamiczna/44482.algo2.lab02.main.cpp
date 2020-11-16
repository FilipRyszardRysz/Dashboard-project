//ALGO 2 IS1 212A LAB02
//Filip Rysz
//rf44482@zut.edu.pl

#include <iostream>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

template <class T>
class tablica_dynamiczna
{
private:

    int size;
    int max_wielkosc;
    int stale_powiekszenie;
    T* dynamiczny_przydzial;

public:
    tablica_dynamiczna()
    {
        size = 0;
        max_wielkosc = 1;
        stale_powiekszenie = 2;
        dynamiczny_przydzial = new T[max_wielkosc];
    };
    ~tablica_dynamiczna() = default;;
    void dodaj_koniec(T data);
    void czyszczenie();
    void sortowanko();
    void wyswietlanie();
    void wyswietl_indeks(int i);
    void podmiana(T data, int i);
};

template <class T>
void tablica_dynamiczna<T>::dodaj_koniec(T data)
{
    if (size < max_wielkosc)
    {
        dynamiczny_przydzial[size++] = data;
    }
    else if (size == max_wielkosc)
    {
        T* temp = new T[2 * max_wielkosc]; // stare elementy tablicy do nowej tablicy
        for (int i = 0; i < size; i++)
        {
            temp[i] = dynamiczny_przydzial[i];
        }
        temp[size++] = data;
        delete[] dynamiczny_przydzial;
        dynamiczny_przydzial = temp;
        max_wielkosc *= 2;
    }
}

template <class T>
void tablica_dynamiczna<T>::wyswietl_indeks(int i)
{
    if (i < size && i >= 0)
    {
        cout << "Rozpoczynam funkcje wyszukiwania po indeksie: " << dynamiczny_przydzial[i] << endl;
        // return dynamiczny_przydzial[i];
    }
    else
        cout << "lista jest pusta lub indeks jest poza zakresem!!!!" << endl;
}

template <class T>
void tablica_dynamiczna<T>::podmiana(T data, int i)
{
    if (i < size && i >= 0)
    {
        cout << "Rozpoczynam funkcje podmiany: " << endl;
        dynamiczny_przydzial[i] = data;
    }
    else
        cout << "lista jest pusta lub indeks jest poza zakresem!!!!" << endl;
}

template <class T>
void tablica_dynamiczna<T>::czyszczenie()
{
    delete[] dynamiczny_przydzial;
    dynamiczny_przydzial = nullptr;
    size = 0;
}

template <class T>
void tablica_dynamiczna<T>::sortowanko()
{
    bool sortowanie;
    T sor;

    for (int i = 0; i < size; i++)
    {
        sortowanie = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (dynamiczny_przydzial[j] > dynamiczny_przydzial[j + 1])
            {
                sortowanie = true;
                sor = dynamiczny_przydzial[j];
                dynamiczny_przydzial[j] = dynamiczny_przydzial[j + 1];
                dynamiczny_przydzial[j + 1] = sor;
            }
        }
        if (sortowanie == false)
            break;
    }
}

template<class T>
void tablica_dynamiczna<T>::wyswietlanie()
{
    /*cout << "Tablica: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << dynamiczny_przydzial[i] << endl;
    }*/
    cout << "Pojemnosc tablicy: " << max_wielkosc << endl << "Ilosc znakow: " << size << endl;
}

int getRandomInt()
{
    int  i = rand();
    return i;
}

int main()
{
    srand(time(nullptr));
    auto* baza = new tablica_dynamiczna<int>();// stworzenie tablicy
    const int order = 7; // rzad wielkosci rozmiaru dodawanych danych
    const int n = pow(10, order); // rozmiar danych
    // dodawanie do tablicy
    clock_t t1 = clock();
    int so;
    double max_time_per_element = 0.0; // najgorszy zaobserwowany czas operacji dodawania
    for (int i = 0; i < n; i++)
    {
        so = getRandomInt(); // losowe dane
        clock_t t1_element = clock();
        baza->dodaj_koniec(so);
        clock_t t2_element = clock();
        double time_per_element = (t2_element - t1_element); // obliczenie czasu pojedynczej operacji dodawania
        if (time_per_element > max_time_per_element)
        {
            cout << "Nowy najgorszy czas: " << time_per_element << endl;
            max_time_per_element = time_per_element;
        }
    }
    clock_t t2 = clock();
    cout << t2 - t1 << endl;
    baza->wyswietlanie();
    baza->wyswietl_indeks(9999999);
    baza->wyswietl_indeks(9999998);
    baza->wyswietl_indeks(9999997);
    baza->wyswietl_indeks(9999996);
    baza->wyswietl_indeks(9999995);
    baza->czyszczenie();
    delete baza;
    return 0;
}