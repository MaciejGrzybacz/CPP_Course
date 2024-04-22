# MyList<T> and mySort<T>
W zadaniu chodzi o to, aby Państwo zaimplementowali szablon klasy, wraz z odpowiednimi metodami.
Następnie aby Państwo zaimplementowali szablon funkcji.
W tym celu:
1. Prosze utworzyć plik `myList.h` (ważna jest wielkość liter), oraz dokonac nastepujacej implementacji:
   Proszę o zaimplementowanie szablonu klasy `MyList<T>`, reprezentujacej liste jednokierunkowa z głową i iteratorami.
   Punktacja przydzielana za nastepujace metody (jak testy):
    1. Za konstruktor bezargumentowy i metode `size()` zwracajaca ilosc elementow
    2. Za metody `push_front()` i `pop_front()`, ktore odpowiednio dodaja/usuwaja element z poczatku
    3. Metode `front()` zwracajaca element na poczatku,
       oraz aby `pop_front()` zwracala usuniety element.
       - **Standardowo w `std::list` metoda `pop_front()` nic nie zwraca.** Jak myślisz - dlaczego?
    4. Jesli pierwszy wezel (o nazwie `head_`), oraz kazdy nastepny wezel (`head_->next_`)
       sa zaimplementowane przy pomocy `std::unique_ptr<MyList::Node>`
    5. Jesli w razie zawolania `pop_front()` na pustej liscie zostaje wyrzucony wyjatek `std::out_of_range`.
    6. Jesli kopiowanie (konstruktor kopiujacy i operator przypisania) jest niemozliwe (usunięte) dla listy
    7. Jesli mamy zaimplementowane metody iteratora (tutaj jeszcze nie musza w pelni dzialac, chociaz powinny zwracac co nalezy)
    8. Jesli napisany iterator dziala z petla for-zakresowym
    9. Jesli nasz iterator dziala z algorytmami standardowymi na przykladzie `std::count_if`
       - Do tego wymagane jest kilka aliasów typów, szczegóły w internecie lub na wykładzie.
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

______________
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
______________
## Najczęstsze problemy/wątpliwości/Uwaga:
--------
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
7. Czemu to co do tej pory było warningiem kompilacji teraz jest przedstawiane jako error? - jest to z powodu flagi, która traktuje wszystkie warningi jako błędy, takie flagi praktykuje się w firmach.
8. Zrobiłem jak zawsze deklaracje w pliku nagłówkowym, a definicje w pliku źródłowym, a jakby nie znajduje definicji (błędy linkera) - w przypadku szablonów definicje również umieszcza się w pliku nagłówkowym, nie źródłowym.

[Bardziej szczegółowe informacje jak pisać programy w ładnym stylu](https://programowaniec.wordpress.com/2017/11/09/czego-sie-czepiam/) dla zaawansowanych.

____________________________________________________________________________________

Informacje o co chodzi w paczce, na co zwrócić uwagę, jak czytać testy znajdują się w materiale [wideo](https://banbye.com/watch/v_xh2q6xtZduQc).
W opisie filmu jest też częściowy minutowy spis treści.

____________________________________________________________________________________
## Podpowiedzi:
1. (Jak macie pomysł to podrzućcie)

____________________________________________________________________________________
## Ocenianie:
1. Ocenia [Bobot](https://gitlab.com/agh-courses/bobot), na ten moment w następujący sposób:
   1. Kompilacja nadesłanego rozwiązania - bez tego zero punktów. Bobot pracuje na Linuxie, używa kompilatora g++.
   2. Uruchamianie testów - za każdy test, który przejdzie są punkty, ale mogą być odjęte w kolejnych krokach.
   3. Jeśli program się wywala na którymś z testów (to się pojawia często u osób pracujących na Windowsie - ten system pozwala pisać po nie-swojej pamięci, Linux nie pozwala) lub jest timeout - wtedy będzie przyznane tyle punktów ile przechodzi testów **minus dwa za karę**.
   4. Jest odpalane narzędzie [valgrind](https://valgrind.org/), które sprawdza czy umiemy obsługiwać pamięć w praktyce - jeśli nie to **minus punkt**.
   5. Odpalane są też inne narzędzia takie jak [cppcheck](http://cppcheck.net/), czy [fawfinde](https://dwheeler.com/flawfinder/) i inne. One nie odejmują punktów, no ale mają pomóc w pisaniu porządnych programów. Nie olewajmy tego.
   6. Antyplagiat - za wykrycie plagiatu (jest specjalne narzędzie) otrzymuje się 0 punktów. Róbmy więc samemu!
____________________________________________________________________________________
# Pytania po implementacji ćwiczenia:
1. (Jak macie pomysł to podrzućcie)
____________________________________________________________________________________
# Zadania, które warto zrobić (uwaga: nie będzie za to punktów, tylko coś cenniejszego - umiejętności)
1. (Jak macie pomysł to podrzućcie)
____________________________________________________________________________________
# Jak skonfigurować sobie pracę nad paczką:
W formie [wideo](https://banbye.com/watch/v_i79PoGIWrjRC) do poprzedniej paczki (link do projektu inny, reszta analogiczna).

**Alternatywnie poniżej jest to spisane w kolejnej sekcji**
____________________________________________________________________________________
## Grading (section copied from Mateusz Ślażyński, of course he agreed):

* [ ] Make sure, you have a **private** group
  * [how to create a group](https://docs.gitlab.com/ee/user/group/#create-a-group)
* [ ] Fork this project into your private group
  * [how to create a fork](https://docs.gitlab.com/ee/user/project/repository/forking_workflow.html#creating-a-fork)
* [ ] Add @bobot-is-a-bot as the new project's member (role: **maintainer**)
  * [how to add an user](https://docs.gitlab.com/ee/user/project/members/index.html#add-a-user)

## How To Submit Solutions

1. [ ] Clone repository: `git clone` (clone only once the same repository):

    ```bash
    git clone <repository url>
    ```
2. [ ] Solve the exercises
3. [ ] Commit your changes

    ```bash
    git add <path to the changed files>
    git commit -m <commit message>
    ```
4. [ ] Push changes to the gitlab main branch

    ```bash
    git push -u origin main
    ```

The rest will be taken care of automatically. You can check the `GRADE.md` file for your grade / test results. Be aware that it may take some time (up to one hour) till this file. Details can be found in `./logs/` directory where You can check compilation results, tests logs etc.

## Project Structure

    .
    ├── CMakeLists.txt          # CMake configuration file - the file is to open out project in our IDE
    ├── main.cpp                # main file - here we can test out solution manually, but it is not required
    ├── tests                   # here are tests for exercise, inner CMakeLists.txt, GTest library used by tests
    │   ├── CMakeLists.txt      # iner CMake for tests - it is included by outter CMake
    │   ├── lib                 # directory containing GTest library
    │   ├── MyListTests.cpp     # tests for template class
    │   └── MySortTests.cpp     # tests for template function
    ├── doxyfiles               # here is logo for documentation generated by Doxygen
    │   └── cppLogo.png         # logo
    ├── Doxyfile                # here is prepared file for Doxygen, to generate documentation when we type `doxygen .`
    ├── Dockerfile              # this file contains instructions how to run tests in embedded Ubuntu
    └── README.md               # this file
