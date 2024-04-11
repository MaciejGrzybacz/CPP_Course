# Vector

## Klasa Fraction:
Bardziej zlozona implementacja klasy Fraction (Ulamek):
1. Klasa powinna posiadac pola `numerator_` (licznik) i `denominator_` (mianownik).
   Najlepiej aby byly to zmienne calkowite.
2. Powinna zawierac jeden konstruktor ustawiajacy licznik (domyslnie na 0) i mianownik (domyslne na 1)
3. Gettery i settery do wartosci licznika i mianownika m.in.: `denominator()` i `setDenominator(...)`.
    - Prosze pamietac, ze gettery, jako metody nic nie zmieniajace powinny byc oznaczone jako metody stale.
    - W mysl zasady aby w razie potrzeby kod modyfikowac w mniejszej ilosci miejsc sugeruje aby
      typem zwracanym getterow bylo `auto`.
4. `operator+` dla ulamka zwracajacy ulamek przez kopie. Metoda stala.
5. `operator*` dla ulamka zwracajacy ulamek przez kopie. Metoda stala.
6. Niepoprawny mianownik (=0) powinien byc zglaszany przez wyjatek `std::invalid_argument`.
   Dotyczy to wszystkich miejsc, gdzie jest ustawiany mianownik.
7. Prosze o automatyczne skracanie ulamkow po operacji `+` i `*`
   Pomocny moze sie okazac algorytm euklidesa, oczywiscie tutaj robimy tylko dla przypadkow dodatnich.
   Zachecam do uzycia `std::gcd(...)`.
____________________________________________________________________________________
## Najczestsze pytania do klasy Fraction:
1. Czy w setterach skracać ułamki?
   Setter swoją nazwą mówi -ustawX, więc powinien to zrobić i nic więcej.
   Trochę dziwne byłoby zachowanie gdy użytkownik ustawia 1/4 na 2/4 i by nagle się mu zrobiło 1/2,
   mimo iż ustawiał tylko licznik na 2.
____________________________________________________________________________________

## Klasa Vector:
Klasy Vector zarzadzająca dynamiczną tablicą na elementy
 *  i rozszerzająca się wg potrzeb z obsługą wyjątków.
 *  **UWAGA: To bardzo wazne zadanie, jeśli ktoś chce być programista C++**
 *  to w srodku nocy powinien umiec takie zadania robic!**
 *  **Nasza implementacja wzorowana C++owym [std::vector](http://www.cplusplus.com/reference/vector/vector/) ale wystepuja różnice**
 *  Nie wolno uzyc w srodku `std::vector`! Zaawansowani moga uzyc uzyc inteligetnych wskaznikow, jesli chca.
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
   - Proszę pamiętać, że należy zdefiniować dwie wersje tego operatora - constową i zwykłą.
9. [Opcjonalnie] Jest utworzone makro `PRINTING_FROM_TESTS_DISABLED`, którego zakomentowanie spowoduje, że w razie błędów testy będą wypisywać cały kontener (wszystkie `Fraction` w ramach `Vector`). Poza tym nic ono nie zmienia.

Informacje o co chodzi w paczce, na co zwrócić uwagę, jak czytać testy znajdują się w materiale [wideo](https://banbye.com/watch/v_StwC1EZk9k1U).

____________________________________________________________________________________
## Uwaga:
Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne,
metody większe niż 1-linijkowe powinny być zadeklarowane w klasie, zdefiniowane
poza klasą, obiekty typów klasowych powinny być w miarę możliwości przekazywane
w argumentach funkcji przez referencję, proszę też stosować słówko "const" w
odpowiednich miejscach. Wszystkie metody, które mogą być stałe proszę aby były

1. Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.
2. Gettery i settery operujace na liczbach, ktore nie rzucaja wyjatku, warto zadeklarowac jako `noexcept`.
3. Co się da na listę inicjalizacyjną konstruktora.
4. Za złe zarządzanie pamięcią (wycieki, pisanie poza pamięcią) powodują odejmowanie punktów
5. Obiekt, z którego przenosimy też powinien się nadawać do użytku!

[Bardziej szczegółowe informacje jak pisać programy w ładnym stylu](https://programowaniec.wordpress.com/2017/11/09/czego-sie-czepiam/) dla zaawansowanych.
____________________________________________________________________________________
## Podpowiedzi:
- polecam uzycie operatora `:?`
- mozna allokowac zero elementor: `new int[0];`
- dla wygody mozna zastosowac idiom: [copy&swap](https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom), podkreslam jednak, ze jest to mniej wydajne
- Nasza implementacja w razie automatycznego zwiekszania rozmiaru ma allokowac pamiec tylko o 1 wieksza!
   - Nie powinno sie tak robic!
- Deklaracje klasy powinny znaleźć się w odpowiednich plikach nagłówkowych, definicje metod i konstruktorów - w plikach źródłowych.

## Ocenianie:
1. Ocenia [Bobot](https://gitlab.com/agh-courses/bobot), na ten moment w następujący sposób:
   1. Kompilacja nadesłanego rozwiązania - bez tego zero punktów. Bobot pracuje na Linuxie, używa kompilatora g++.
   2. Uruchamianie testów - za każdy test, który przejdzie są punkty, ale mogą być odjęte w kolejnych krokach.
   3. Jeśli program się wywala na którymś z testów (to się pojawia często u osób pracujących na Windowsie - ten system pozwala pisać po nie-swojej pamięci, Linux nie pozwala) lub jest timeout - wtedy będzie przyznane tyle punktów ile przechodzi testów **minus dwa za karę**.
   4. Jest odpalane narzędzie [valgrind](https://valgrind.org/), które sprawdza czy umiemy obsługiwać pamięć w praktyce - jeśli nie to **minus punkt**.
   5. Odpalane są też inne narzędzia takie jak [cppcheck](http://cppcheck.net/), czy [fawfinde](https://dwheeler.com/flawfinder/) i inne. One nie odejmują punktów, no ale mają pomóc w pisaniu porządnych programów. Nie olewajmy tego.
   6. Antyplagiat - za wykrycie plagiatu (jest specjalne narzędzie) otrzymuje się 0 punktów. Róbmy więc samemu!
____________________________________________________________________________________
## Najczestsze pytania/błędy/problemy:
1. Może się pojawią...
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
    ├── fraction.h              # file to implement class declaration
    ├── fraction.cpp            # file to implement methods
    ├── vector.h                # another file to implement class declaration
    ├── vector.cpp              # another file to implement methods
    ├── trescPdf.pdf            # documentation in PDF (generated by Doxygen)
    ├── tests                   # here are tests for exercise, inner CMakeLists.txt, GTest library used by tests
    │   ├── CMakeLists.txt      # iner CMake for tests - it is included by outter CMake
    │   ├── lib                 # directory containing GTest library
    │   ├── fractionTests.cpp   # tests v1
    │   └── vectorTests.cpp     # tests v1
    ├── doxyfiles               # here is logo for documentation generated by Doxygen
    │   └── cppLogo.png         # logo
    ├── Doxyfile                # here is prepared file for Doxygen, to generate documentation when we type `doxygen .`
    ├── Dockerfile              # this file contains instructions how to run tests in embedded Ubuntu
    └── README.md               # this file
