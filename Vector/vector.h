#ifndef VECTOR_H
#define VECTOR_H


/** @file vector.h
 *  @brief Klasy Vector zarzadzająca dynamiczną tablicą na elementy (bardziej szczegolowa tresc w README.md):
 *  i rozszerzająca się wg potrzeb z obsługą wyjątków.
 *  @note **UWAGA: To bardzo wazne zadanie, jeśli ktoś chce być programista C++
 *  to w srodku nocy powinien umiec takie zadania robic!**
 *  @note Nasza implementacja wzorowana C++owym [std::vector](http://www.cplusplus.com/reference/vector/vector/),
 *  ale wystepuja różnice.
 *  @note Nie wolno uzyc w srodku std::vector! Zaawansowani moga uzyc uzyc inteligetnych wskaznikow, jesli chca.
## Tresc zadania:
1. Proszę aby klasa miała następujące składowe:
    - `Fraction* data_` - dynamiczna tablica na dane.
      **Osobom zaawansowanym sugeruję użyć inteligętnych wskaźników np. `std::unique_ptr<Fraction[]> data_`**
    - `std::size_t size_` - aktualna ilość elementów na tablicy
    - `std::size_t capacity_` - ile elementow pomieści aktualnie zaalokowana tablica.
2. Proszę o zaimplementowanie metod - getterów zwracających powyższe składowe - `size()`, `capacity()`, `data()`.
3. Proszę o zaimplementowanie konstuktora przyjmującego liczbę do wstępnej allokacji (z wartoscia domyslna 0)
4. Proszę o zaimplementowanie destruktora. Musi on koniecznie zwalniać pamięć
   (chyba, że używamy inteligętnych wskaźników, wtedy się zwolni automatycznie i nie musimy go implementować).
5. Proszę o zdefiniowanie konstuktora kopiującego, który będzie wykonywał tzw. "głęboką kopię"
   (czyli allokował nową pamięć i kopiował zawartość).
   **Osoby zaawansowane mogą to rozwiązać przez copy-on-write.**
6. Proszę o zdefiniowanie `operator=` wersji kopiującej głęboko i przenoszącej
7. Proszę zdefiniować metodę dodającą obiekt na koncu tablicy `push_back()`.
   **W razie braku miejsca metoda ta powinna dokonać reallokacji pamięci aby nowy element się zmieścił.**
8. Proszę o zdefiniowanie operatora indeksowania: `operator[](std::size_t index)` zwracający wskazany element tablicy.
   **Dostep po indeksie poza rozmiar tablicy (size) powinny być zgłaszane poprzez wyjątki `std::out_of_range`**
   @note Proszę pamiętać, że należy zdefiniować dwie wersje tego operatora - constową i zwykłą.

____________________________________________________________________________________
## Uwaga (bardziej wiazaca tresc jest w pliku `README.md`):
Wszystkie atrybuty powinny być prywatne. Deklaracje klasy powinny znaleźć się w odpowiednich plikach nagłówkowych, definicje metod i konstruktorów - w plikach źródłowych.
Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne, metody/konstruktory/destruktory większe niż 1-linijkowe powinny być zadeklarowane w klasie, zdefiniowane poza klasą,
Obiekty typów klasowych powinny być przekazywane do funkcji/metod przez referencje (zwykłe lub stałe), metody niemodyfikujące zawartości klasy powinny być oznaczane jako const.
Wszystkie metody, które mogą być stałe proszę aby były.

1. Co się da na listę inicjalizacyjną konstruktora.
@note Za złe zarządzanie pamięcią (wycieki, pisanie poza pamięcią) powodują odejmowanie punktów
@note Obiekt, z którego przenosimy też powinien się nadawać do użytku!

Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.
____________________________________________________________________________________
## Punktacja:
Na maksa przejście wszystkich testów i brak niepoprawnych operacji na pamieci (m.in. wyciekow pamieci)
____________________________________________________________________________________
## Podpowiedzi:
    - polecam uzycie operatora `:?`
    - mozna allokowac zero elementor: `new int[0];`
    - dla wygody mozna zastosowac idiom: [copy&swap](https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom),
      podkreslam jednak, ze jest to mniej wydajne
____________________________________________________________________________________
## Dodatkowe wyjaśnienie:
Nasza implementacja w razie automatycznego zwiekszania rozmiaru ma allokowac pamiec tylko o 1 wieksza!
Ale w implementacjach profesjonalnych nie powinno tak być!
Po prostu ćwiczymy zarządzanie pamięcią, wskaźniki itp.
**/

/// Na potrzeby testów można zakomentować poniższe makro - wtedy testy będą wyświetlać cały Vector of Fraction, ale do tego jest konieczna implementacja
//#define PRINTING_FROM_TESTS_DISABLED

#include <cstddef> // std::size_t
#include <memory>  // std::unique_ptr
#include "fraction.h"


class Vector
{
public:
    Fraction* data_;
    size_t size_;
    size_t capacity_;

    explicit Vector(int initial_capacity = 0);
    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;
    ~Vector();
    [[nodiscard]] Fraction* data() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t capacity() const;
    Vector& operator=(const Vector& other); //deepcopy
    Vector& operator=(Vector&& other) noexcept; //moving values
    void push_back(const Fraction& fraction);
    Fraction& operator[](size_t index) const;

private:
    void reallocate(size_t new_capacity);
};

#endif // VECTOR_H
