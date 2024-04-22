#include <iostream>

/**
  @mainpage Laboratorium 5 - Szablony klas i szablony funkcji

  Tresc zadan dla Panstwa (aktualniejsza jest w `README.md`)
  --------
Zadanie 0: absolutnie obowiazkowe, chociaz bez punktow
1. Pierwsza rzecza jest poprawa bledow kompilacji,
   czyli wpisanie poprawnych Panstwa danych w pliku: @ref main.cpp
2. Oddanne zadanie musi sie bezwzglednie kompilowac na systemie Linux:
   - Jesli sie nie skompiluje to jest to 0 punktow za zadanie!
   - Oczywiscie w razie problemow z kompilacja prosze się zgłaszać/pisać.
   - Dobrze, jesli nie byloby warningow kompilacji, ale za to nie obnizam punktow.
   - Aby się upewnić, że się kompiluje można skorzystać z [narzędzia Bobot](https://gitlab.com/agh-courses/bobot)
3. Oddane zadanie nie powinno crashować na żadnym teście,
   jeśli crashuje proszę zrobic implementacje -fake, ktora nie dopusci do crasha nawet jesli test bedzie failowal,
   ale za to testy nie beda sie crashowaly.
   W przypadku crasha biorę pod uwagę tylko tyle testów, ile przejdzie do czasu crasha!
4. Mam program antyplagiatowy, dlatego prosze pracowac samodzielnie!
   - Osoby ktore udostepniaja swoje rozwiazania rowniez beda mialy kare!
   - Na ukaranie prowadzący ma czas 2 tygodnie po terminie oddania,
      czyli nawet jak ktoś otrzyma punkty wcześniej ma pewność, że za oszustwa/łatwowierność dosięgnie go
      niewidzialna ręka sprawiedliwości.
5. Zadanie z zalozenia bedzie sprawdzane automatycznie, przez testy jednostkowe dostepne w pliku: `shapesTests.cpp`,
6. *Dobrze jakby nie bylo warningow kompilacji (flagi: `-Wall -Wextra -pedantic -Werror`, a dla hardcorów jeszcze:  `-Weffc++`)
7. Punkty beda odejmowane za wycieki pamieci (jest podpiety `valgrind`)
8. Niewykluczone jest sprawdzanie reczne - zaleznie od prowadzacego dana grupe.
________________________________
Zadanie implementacyjne:
------------------------
W zadaniu chodzi o to, aby Państwo zaimplementowali szablon klasy, wraz z odpowiednimi metodami.
Następnie aby Państwo zaimplementowali szablon funkcji.
1. Prosze utworzyć plik `myList.h` (ważna jest wielkość liter), oraz dokonac nastepujacej implementacji:
   Proszę o zaimplementowanie szablonu klasy `MyList<T>`, reprezentujacej liste jednokierunkowa z glowa i iteratorami.
   Punktacja przydzielana za nastepujace metody (jak testy):
    1. Za konstruktor bezargumentowy i metode `size()` zwracajaca ilosc elementow
    2. Za metody `push_front` i `pop_front`, ktore odpowiednio dodaja/usuwaja element z poczatku
    3. Metode `front()` zwracajaca element na poczatku,
       oraz aby `pop_front()` zwracala usuniety element.
       @note Standardowo w `std::list` metoda `pop_front()` nic nie zwraca.
       Jak myślisz - dlaczego?
    4. Jesli pierwszy wezel (o nazwie head), oraz kazdy nastepny wezel (`head_->next_`)
       sa zaimplementowane przy pomocy `std::unique_ptr<MyList::Node>`
    5. Jesli w razie zawolania `pop_front` na pustej liscie zostaje
       wyrzucony wyjatek `std::out_of_range`
    6. Jesli kopiowanie (konstruktor kopiujacy i operator przypisania) jest niemozliwe (usunięte) dla listy
    7. Jesli mamy zaimplementowane metody iteratora
       (tutaj jeszcze nie musza w pelni dzialac, chociaz powinny zwracac co nalezy)
    8. Jesli napisany iterator dziala z petla for-zakresowym
    9. Jesli nasz iterator dziala z algorytmami standardowymi na przykladzie `std::count_if`
       @note Do tego wymagane jest kilka aliasów typów, szczegóły w internecie lub na wykładzie.
   10. Jesli mamy metode `remove(T element)`, ktora usuwa wszystkie elementy z listy o danej wartosci
   11. Jesli lista ma operator wypisywania na strumien (forma wydruku dowolna, byleby byly wszystkie elementy)
2. Następnie prosze o utworzenie pliku `mySorting.h` (wielkość liter ma znaczenie).
   W nim prosze o zaimplementowanie szablonu funkcji globalnej `void mySort(???)`:
   Punktacja (analogicznie jak testy):
    1. Sortowanie statycznej tablicy dziala
    2. Dziala z kontenerami standardowymi (na przykladzie `std::vector`)
    3. Dziala z nasza lista - specjalizacja
    4. Specjalizacja sortowania dla tablicy `char[][]`
       jesli dziala dla tablicy slów skladajacych sie wylacznie z DUZYCH LITER
    5. Jw. ale powinno dzialac z pominieciem wielkosci liter.
3. Tym razem kod ma się kompilować z flagami:
   `-Wall -Wextra -pedantic -Werror` a dla hardcorów jeszcze:  `-Weffc++`
_____________________
Aby odblokować odpowiednie testy należy po dokonaniu implementacji wstawić odpowiednie makra w pliku `myList.h`:
```
#define IMPLEMENTED_constructorOfEmptyList
#define IMPLEMENTED_pushingAndPopingElementsFront
#define IMPLEMENTED_nodesStoredAsUniquePtrs
#define IMPLEMENTED_popFromWhenEmptyList
#define IMPLEMENTED_copyingDisabled
#define IMPLEMENTED_removingElements
#define IMPLEMENTED_iteratorOperations
#define IMPLEMENTED_iteratorWithRangedForLoop
#define IMPLEMENTED_iteratorWithStlAlgorithm
#define IMPLEMENTED_ostreamOperator
```
_____________________
Najczęstsze problemy/wątpliwości/Uwaga:
---------------------
1. Konieczne może się okazać zrobienie dwóch wersji metod begin/end -jedna stała, druga nie.
2. Należy zdefiniować dwie wersje iteratorów - stały `const_iterator` i zwykły `iterator` jako klasy zagnieżdżone.
    1. Informacje [jak zdefiniować własny iterator](https://medium.com/geekculture/iterator-design-pattern-in-c-42caec84bfc)
       lub [2](https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators).
       Najprościej jest dziedziczyć po `std::iterator`, niemniej jednak jest to deprecated.
3. Szablony muszą być zdefiniowane w całości w pliku nagłówkowym,
   jednakże proszę aby definicje metod dłuższych niż 1-linijkowe były pod klasą.
4. Można użyć `std::sort` lub `std::stable_sort` - tylko trzeba wiedzieć gdzie i jak.
5. Można spróbować użyć `if constexpr` aby zmniejszyć ilość funkcji.
6. Dodałem pliki, ale testy nadal nie przechodzą - trzeba ponownie uruchomić CMake aby wykrył zmiany plików, oraz **zrobić pełną rekompilacje**.
**/

/// @todo Uzupelnij swoje dane:
constexpr const char* const FIRSTNAME = "Maciej";
constexpr const char* const SURNAME   = "Grzybacz";
constexpr const char* const MAIL    = "mgrzybacz@student.agh.edu.pl";
constexpr const char* const BOOK_ID = "416027";
constexpr const char* const TEACHER_MAIL = "bazior[at]agh.edu.pl"; // change if not correct


void validateStudentsInfo();


int main()
{
    std::cout << "Hello " << FIRSTNAME << " " << SURNAME << "!" << '\n'
              << "make Your teacher: " << TEACHER_MAIL << " proud of you!" << std::endl;
              
    validateStudentsInfo();
}


constexpr inline size_t compileTimeStrlen(const char* text) noexcept
{
    return (*text ? 1+compileTimeStrlen(text+1) : 0);
}

constexpr inline size_t compileTimeCountFirstDigits(const char* text) noexcept
{
    return (*text && ('0'<=*text && *text<='9') ? 1+compileTimeCountFirstDigits(text+1) : 0);
}

constexpr inline bool compileTimeIsDigit(const char* text) noexcept
{
    return compileTimeStrlen(text) == compileTimeCountFirstDigits(text);
}

constexpr inline bool compileTimeContains(const char* text, char letter) noexcept
{
    if ('\n' == *text)
        return false;

    return *text == letter ? 1 : compileTimeContains(text+1, letter);
}

void validateStudentsInfo()
{
    static_assert(compileTimeStrlen(FIRSTNAME) > 2, "You must input your first name!");
    static_assert(compileTimeStrlen(SURNAME) > 2, "You must input your surname!");

    static_assert(compileTimeStrlen(BOOK_ID) > 1, "You must input your student book id!");
    static_assert(compileTimeIsDigit(BOOK_ID), "You student book id should consist only digits, shouldn't it?!");

    static_assert(compileTimeStrlen(MAIL) > 3, "You must input your mail (preferred AGH mail)!");
    static_assert(compileTimeContains(MAIL, '@'), "Invalid mail! It should contain '@'!");
    static_assert(compileTimeContains(MAIL, '.'), "Invalid mail! It should contain '.'!");
}
