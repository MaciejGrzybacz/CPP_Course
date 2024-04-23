# MyString
W zadaniu chodzi o to, żeby Państwo:
- zaimplementowali własny typ do obsługi tekstu, którego część pamięci będzie statycznie (tablica o stałym rozmiarze), a reszta będzie się allokować wg potrzeby,
- zależy mi też aby Państwo byli w stanie zaimplementować własny iterator
- kolejnym aspektem jest aby Państwo przećwiczyli fundamentalną umiejętność programisty - czytanie kodu. Dlatego nie mają Państwo obszernego opisu, tylko kod z testami i muszą sobie Państwo poradzić.
- wreszcie zależy mi też aby Państwo spróbowali maksymalnie dużo zrobić przy użyciu biblioteki standardowej C++ (nie wszystko na piechotę),
dlatego też testy zawierają wskazówki czego można użyć aby daną funkcjonalność dostarczyć bez konieczności implementowania jej samodzielnie.
- \* osoby ambitne mogą spróbować zaimplementować pewne funkcjonalności przy pomocy biblioteki [boost](https://www.boost.org/).
  Oczywiście jakby coś nie działało proszę o priv, abym doinstalował.

## Opis bardziej szczegółowy:
1. Wykorzystanie biblioteki STL i kontenerów podczas implementacji klasy MyString
   - można też użyć typu `std::string` pod spodem, jak i `std::array`, nie trzeba ręcznie zarządzać pamięcią
2. Klasa ta ma zawierać statyczna tablice na tekst do 20 znaków,
   a resztę ma w razie potrzeby pobierać dynamicznie np. przy pomocy typu `std::string`.
3. Funkcjonalności są dopasowane tak, aby użyć kilku kontenerów standardowych,
   poćwiczyć pisanie iteratorów, oraz użyć algorytmów uogólnionych (`<algorithm>`).
4. Treść należy wydedukować w oparciu o plik z testami, nad wieloma testami jest sugestia czego można użyć.
5. Można też użyć biblioteki `boost` (oczywiście wtedy w razie błędów kompilacji na bobotcie proszę o maila z informacją czego Państwo używają).
6. Sygnatury funkcji do zaimplementowania (pobrane przy pomocy `ctags`):

| metoda                | sygnatura                                                           |
|---------------------- |-------------------------------------------------------------------- |
| MyString              | MyString(const char *text)                                          |
| MyString              | MyString(const MyString &text)                                      |
| begin                 | iterator begin()                                                    |
| begin                 | const_iterator begin() const                                        |
| capacity              | auto capacity() const                                               |
| cbegin                | const_iterator cbegin() const                                       |
| cend                  | const_iterator cend() const                                         |
| const_iterator        | explicit const_iterator(const MyString* myString, size_t position)  |
| empty                 | bool empty() const                                                  |
| end                   | iterator end()                                                      |
| end                   | const_iterator end() const                                          |
| getPosition           | auto getPosition() const                                            |
| iterator              | explicit iterator(MyString* myString, size_t position)              |
| operator !=           | bool operator!=(const MyString& rhs) const                          |
| operator !=           | bool operator!=(iterator anotherIt)                                 |
| operator !=           | bool operator!=(const_iterator anotherIt) const                     |
| operator *            | char& operator*()                                                   |
| operator *            | char operator*() const                                              |
| operator +            | iterator operator+(size_t pos)                                      |
| operator +            | const_iterator operator+(size_t pos) const                          |
| operator ++           | iterator& operator++()                                              |
| operator ++           | const_iterator& operator++()                                        |
| operator -            | size_t operator-(iterator anotherIt)                                |
| operator -            | size_t operator-(const_iterator anotherIt) const                    |
| operator --           | iterator& operator--()                                              |
| operator --           | const_iterator& operator--()                                        |
| operator ==           | bool operator==(iterator anotherIt)                                 |
| operator ==           | bool operator==(const_iterator anotherIt) const                     |
| operator []           | char operator[](size_t i) const                                     |
| operator std::string  | explicit operator std::string() const                               |
| push_back             | void push_back(char c)                                              |
| size                  | auto size() const                                                   |
| map<MyString, size_t> | countWordsUsageIgnoringCases() const;                               |
| all_of                | bool all_of(std::function<bool(char)> predicate) const              |
| generateRandomWord    | static MyString generateRandomWord(size_t length)                   |
| getUniqueWords        | std::set<MyString> getUniqueWords() const                           |
| join                  | MyString join(const std::vector<MyString> &texts) const             |
| startsWith            | bool MyString::startsWith(const char *text) const                   |
| toLower               | MyString& toLower()                                                 |
| trim                  | MyString& trim()                                                    |

______________
## Najczęstsze problemy/wątpliwości/Uwaga:
--------
1. Konieczne może się okazać zrobienie dwóch wersji metod begin/end -jedna stała, druga nie.
2. Należy zdefiniować dwie wersje iteratorów - stały `const_iterator` i zwykły `iterator` jako klasy zagnieżdżone.
    1. Informacje [jak zdefiniować własny iterator](https://medium.com/geekculture/iterator-design-pattern-in-c-42caec84bfc)
       lub [2](https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators).
       Najprościej jest dziedziczyć po `std::iterator`, niemniej jednak jest to deprecated.
    2. Powinno się to pojawić na ostatnim wykładzie.
3. Szablony muszą być zdefiniowane w całości w pliku nagłówkowym,
   jednakże proszę aby definicje metod dłuższych niż 1-linijkowe były pod klasą.
4. Iterator nie chce działać z kontenerem standardowym
   - Ponieważ trzeba wskazać jakiego [rodzaju jest ten iterator](https://en.cppreference.com/w/cpp/iterator/iterator_tags).
5. Można użyć `std::sort` lub `std::stable_sort` - tylko trzeba wiedzieć gdzie i jak.
6. Można spróbować użyć `if constexpr` aby zmniejszyć ilość funkcji.
7. Dodałem pliki, ale testy nadal nie przechodzą - trzeba ponownie uruchomić CMake aby wykrył zmiany plików.
8. Dodałem plik `mystring.h` lub `mystring.cpp` i dalej go nie widzi.
   - Proszę się upewnić, że wielkość liter się zgadza (Linux je rozróżnia w przeciwieństwie do Windowsa)
   - Proszę po dodaniu pliku ponownie uruchomić CMake oraz kompilacje - aby wykryło nowe pliki to skompilowania.

[Bardziej szczegółowe informacje jak pisać programy w ładnym stylu](https://programowaniec.wordpress.com/2017/11/09/czego-sie-czepiam/) dla zaawansowanych.

____________________________________________________________________________________

### Informacje o co chodzi w paczce, na co zwrócić uwagę, jak czytać testy znajdują się w materiale [wideo](https://banbye.com/watch/v_HIP0VpziSU92).
**W opisie filmu jest też częściowy spis treści.**
1. O co chodzi w zadaniu
2. Jak to zrobić nie mając pliku z implementacją.
3. Ponowne uruchamienie pliku CMake.
4. Omówienie testów, sugestii i testów iteratorów.
5. Reklama `<algorithm>` i innych algorytmów.
6. Algorytmy tekstowe: `boost::algorithm`
7. Koniec paczek, proszę sobie dopilnować

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
1. Użyć biblioteki boost np. używającego `boost::string::algorithm`, można się zainspirować [artykułem](https://cpp0x.pl/artykuly/Inne-artykuly/Praca-z-tekstem-przy-uzyciu-dostepnych-narzedzi-w-C++/64).
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
    └── zaj6MyString
       ├── CMakeLists.txt         # CMake configuration file - the file is to open out project in our IDE
       ├── Dockerfile             # this file contains instructions how to run tests in embedded Ubuntu
       ├── Doxyfile               # here is prepared file for Doxygen, to generate documentation when we type `doxygen .`
       ├── main.cpp               # main file - here we can test out solution manually, but it is not required, it contains what to do
       ├── mystring.h             # this file should be created and contain declarations
       ├── mystring.cpp           # this file should be created and contain definitions for declared methods
       ├── README.md              # this file
       ├── tests                  # here are tests for exercise, inner CMakeLists.txt, GTest library used by tests
       │   ├── CMakeLists.txt     # iner CMake for tests - it is included by outter CMake
       │   └── myStringTests.cpp  # tests for our class
       └── trescWygenerowan_dlaStudentowa.pdf
