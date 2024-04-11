# Ułamek
## Implementacja prostej klasy - Ułamek
W zadaniu chodzi o to, żeby zaimplementować wg treści podaną klasę `Fraction` wraz z metodami podanymi w treści. Tym sposobem chcemy wejść w świat programowania obiektowego w C++ robiąc pierwszą prostą klasę.

### Utrudnienie - makra preprocesora
Zadanie zawiera testy automatyczne, które testują czy dana metoda jest zaimplementowana poprawnie. Jeśli metody nie ma a byłaby testowana to byłby błąd kompilacji. Tym samym zadanie można by oddać wyłącznie jako wszystko lub jako nic. Dlatego też korzystam z makr preprocesora, które zależnie od tego czy dana funkcjonalność jest zaimplementowana czy nie aktywują (w trakcie kompilacji) odpowiednie części kodu. Czyli Państwo po zaimpelemtowaniu danej metody będą musieli zmazać odpowiednią linijkę `UNIMPLEMENTED_abcFunction`.

### Do zrobienia
Zaimplementuj podaną na zajęciach klasę reprezentującą ulamek:
1. Nazwa klasy `Fraction`.
   1. Następnie usuń makro: `UNIMPLEMENTED_classFraction`
2. Do klasy dodaj pola protected typu całkowitego:
   - `numerator_` (licznik)
   - `denominator_` (mianownik).
   1. Następnie usuń makro `UNIMPLEMENTED_numeratorAndDenominator`
3. Do klasy dodaj konstruktor bezparametrowy (może być też z wartościami domyślnymi),
   który ustawi wartości licznika na `0` i mianownika na `1`.
   1. Następnie usuń makro `UNIMPLEMENTED_defaultConstructor`
4. Do klasy dodaj konstruktor z parametrami (może być modyfikacja powyższego),
   który ustawi licznik i mianownik na podstawie podanych argumentów funkcji,
   - wartością domyślną dla mianownika ma być `1`.
   1. Następnie usuń makro `UNIMPLEMENTED_constructorWhichInitialiseFields`
5. Do klasy dodaj zestaw metod dostępowych/modyfikujących obiekty klasy -tzw. gettery i settery,
   które umożliwią modyfikacje i pobranie wartości licznika i mianownika
   1. Następnie usuń makro `UNIMPLEMENTED_gettersAndSetters`,
6. Do klasy dodaj metodę `print()`, wypisującą atrybuty obiektu na konsolę w formie `"licznik/mianownik\n"`
   1. Następnie usuń makro `UNIMPLEMENTED_printFunction`
7. Do klasy dodaj statyczny atrybut `removedFractions_`
   i metodę statyczną: `removedFractions()` zwracającą ten atrybut
   Skladowa ta powinna byc incrementowana w destruktorze.
   1. Następnie usuń makro `UNIMPLEMENTED_counterOfDestructedFractions`
8. Dodaj do klasy metody `save(std::ostream& os)` i `load(std::istream& is)`,
   zapisujące/odczytujące zawartość obiektu do przekazanego jako parametr strumienia wyjściowego/wejściowego,
   w formacie `"licznik/mianownik"`. Metoda wczytująca może założyć, że format danych będzie poprawny
   (nie trzeba obslugiwac bledow).
   1. Następnie usuń makro `UNIMPLEMENTED_readWrite`.
9. Proszę dodanie stałej odzwierciedlającej nazwę ułamka o nazwie `fractionName_`,
   powinna być `protected`. Do niej proszę dodać metodę stałą:
   `getFractionName()`.
   1. Następnie usuń makro `UNIMPLEMENTED_fractionNameSettableFromConstructor`
10. Do klasy dodaj dwie stałe:
   - stała statyczna odzwierciedlajaca niedopuszczalna wartość mianownika: `invalidDenominatorValue`
   - metodę statyczną zwracającą powyższe: `getInvalidDenominatorValue()`
   - stałą statyczną czasu kompilacji (constexpr) odzwierciedlajaca domyślna wartość mianownika: `defaultDenominatorValue`
   - metodę constexpr `getDefaultDenominatorValue()` zwracającą powyższe.
   1. Następnie usuń makro `UNIMPLEMENTED_fractionConstStaticFields`

Informacje jak czytać testy znajdują się w materiale [wideo](https://banbye.com/watch/v_zrbYPwwctaYy).
____________________________________________________________________________________
Po implementowaniu powyższych poleceń i zmiany wartości poniższych makr powinno przechodzić
coraz więcej testów dostępnych w pliku `fractionTests.cpp`.

## Uwaga:
Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne,
metody większe niż 1-linijkowe powinny być zadeklarowane w klasie, zdefiniowane
poza klasą, obiekty typów klasowych powinny być w miarę możliwości przekazywane
w argumentach funkcji przez referencję, proszę też stosować słówko "const" w
odpowiednich miejscach.

Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.

[Bardziej szczegółowe informacje jak pisać programy w ładnym stylu](https://programowaniec.wordpress.com/2017/11/09/czego-sie-czepiam/) dla zaawansowanych.
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
## Najczestrze pytania/błędy/problemy:
1. Są rozbieżności między treścią `README.md`, a treściami w plikach nagłówkowych!
   - W tym roku przechodzimy na `README.md`, więc ta treść jest wiążąca.
2. Zrobiłem wg treści i się nie kompiluje.
   - Poza samym robieniem wg instrukcji należy pamiętać, że piszemy w C++, nie podaje dokładnych typów zwracanych funkcji,
   a trzeba pamiętać o nich definiując sygnaturę funkcji.
3. Podczas kompilacji pojawia się dziwny błąd z tekstem `removedFractions_` i dużą ilością dziwnych znaków, mimo iż został zdefiniowany w klasie.
   - Zapewne chodzi o błąd linkowania - kod się kompiluje, ale trzeba go jeszcze połączyć w binarkę.
   C++ wymaga aby składowa statyczna (równocześnie nie `const`/`constexpr`) była zdefiniowana poza klasą. Alternatywnie można dołożyć słówko `inline` (to dodał C++17).

____________________________________________________________________________________
# Pytania po implementacji ćwiczenia:
1. Jaka jest różnica między składowymi: `const static` a `static`?
2. Jaka jest różnica między składowymi: `const static` a `constexpr static`?

____________________________________________________________________________________
# Zadania, które warto zrobić (uwaga: nie będzie za to punktów, tylko coś cenniejszego - umiejętności)
1. Warto rozbudować naszą klasę-ułamek o podstawowe operacji na ułamkach takich jak mnożenie, dodawanie, skracanie.
____________________________________________________________________________________
# Jak skonfigurować sobie pracę nad paczką:
W formie [wideo](https://banbye.com/watch/v_i79PoGIWrjRC).

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
    ├── zaj1Fraction                # directory containing exercises
    |   ├── CMakeLists.txt          # CMake configuration file - the file is to open out project in our IDE
    |   ├── main.cpp                # main file - here we can test out solution manually, but it is not required
    |   ├── fraction.h              # file to create class declaration and methods' declaration
    |   ├── fraction.cpp            # file to implement methods
    |   ├── trescPdf.pdf            # documentation in PDF (generated by Doxygen)
    |   ├── tests                   # here are tests for exercise, inner CMakeLists.txt, GTest library used by tests
    │   │   ├── CMakeLists.txt      # iner CMake for tests - it is included by outter CMake
    │   │   ├── fractionTests.cpp   # files with tests for exercise
    │   │   └── lib                 # directory containing GTest library
    |   ├── Doxyfile                # here is prepared file for Doxygen, to generate documentation when we type `doxygen .`
    |   ├── doxyfiles               # here is logo for documentation generated by Doxygen
    |   ├── Dockerfile              # this file contains instructions how to run tests in embedded Ubuntu
    |   └── README.md               # this file
