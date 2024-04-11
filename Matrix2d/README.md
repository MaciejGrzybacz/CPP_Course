# Macierz 2x2
## Przeciążanie operatorów na przykładzie Macierzy.
W zadaniu chodzi o to, aby utworzyć wygodny w użyciu typ do operacji na macierzy 2*2, o nazwie `TwoDimensionMatrix`. Polega na tym, że mamy utworzone odpowiednie konstruktory, metody i **przeciążone operatory**.

### Do zrobienia:
1. Zaimplementuj klasę `TwoDimensionMatrix` odzwierciedlajaca macierz 2*2, zawierającą:
    - tablice typu `MatrixElement` (tzn. `int`, alias jest zdefiniowany w pliku `matrixElement.h`), oraz `size_` (=2)
    - konstruktory:
        - bezargumentowy - zerujący wszystkie elementy
        - kopiujący
        - przyjmujący jako argument tablicę `const MatrixElement matrix[size_][size_]` i kopiujący z niej wartości
    - funkcja składowa do dostępu do elementów (`get()`) zwracająca odpowiedni element
    - funkcja zwracająca `size_` o nazwie (`size()`), proponuję aby była `static constexpr`
2. Uzupełnij klasy o następujące operacje zdefiniowane poprzez przeciążenie operatorów:
    - operator przypisania kopiujący (głęboko): `operator=()`
    - operatory wypisywania do strumienia (jako funkcja zewnętrzna) - format dowolny, byleby wszystkie elementy były w strumieniu
    - operatory wczytywania ze strumienia (jako funkcja zewnętrzna) - format dla macierzy:
      ```
      { a, b }
      { c, d }
      ```
      powinno się odbyć:
      ```
        a b
        c d
      ```
    - operatory arytmetyczne (stosujące odpowiednie operacje na macierzach):
        - `TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2); // jako funkcja globalna`
        - `TwoDimensionMatrix& operator*=(MatrixElement number); // metoda klasy`
        - Zadany operator logiczny (metoda klasy) - to jest przykład gdzie **nie** należy przeciążać operatorów:
          `TwoDimensionMatrix operator&&(const TwoDimensionMatrix& matrix) const;`
        - operator tablicowy dostający się po indeksie do pierwszego z wymiarów tablicy (metoda klasy), **proszę pamiętać, że mają być dwie wersje: z i bez const**
          `MatrixElement* operator[](size_t i);`
        - operator konwersji do `size_t`, zwracający to co `size()` (metoda klasy),
3. Deklaracja klasy i funkcji globalnych powinna się znaleźć w pliku "matrix.h", natomiast definicje funkcji zewnętrznych i metod klas w pliku źródłowym `matrix.cpp`

Informacje o co chodzi w paczce, na co zwrócić uwagę, jak czytać testy znajdują się w materiale [wideo](https://banbye.com/watch/v_L15GKhIybbHc).
____________________________________________________________________________________
## Uwaga:
Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne,
metody większe niż 1-linijkowe powinny być zadeklarowane w klasie, zdefiniowane
poza klasą, obiekty typów klasowych powinny być w miarę możliwości przekazywane
w argumentach funkcji przez referencję, proszę też stosować słówko "const" w
odpowiednich miejscach.

Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby były one prywatne.

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
## Najczestsze pytania/błędy/problemy:
1. Jak ma działać `&&` dla macierzy?
   - Wykonująca na każdym z elementów `&&`, czyli:

    ```
    { 0, 0 }      { 0, 6 }      { 0, 0 }
    {-3, 9 }  &&  { 0, -9 }  =  { 0, 1 }
    ```
2. Jak ma działać operator tablicowy []?
   - Operator ten przyjmuje tylko jeden argument (poza this), a chcemy odnieść się w następujący sposób:
    `matrix[row][column]`, dlatego ten operator musi zwrócić matrix[row] typu `MatrixElement*`.
3. Mam operator indeksowania [], a kompilator jakby go nie widzi.
   - To najczęstrzy błąd w tym zadaniu - muszą być dwie wersje - jedna zwykła, a druga stała (przydomek `const`)
4. Nie rozumiem dlaczego mi test nie przechodzi!
   - Testy się __starałem__ robić proste i czytelne o jak najwięcej mówiącej nazwie. Warto wejść do ciała testu i popatrzyć co się tam dzieje.
5. Użycie [chatgpt](chat.openai.com/) czy można?
   - Uczyłem wiele pokoleń studentów, gdy tego nie było, dostawali się na staże, do pracy, nawet nieliczni mi dziękowali mailowo. Bez tego narzędzia są efekty. Zadania to nie tylko ich zrobienie, to też m.in. myślenie programistyczne, umiejętności, umiejętność rozwiązywania problemu, wyszukiwania informacji, przetwarzania tego co się czyta. Sztuczna inteligencja **nie pozwoli** nam na wykształcenie tak wiele, jedynie oszczędzimy czas w danej chwili (ale niekoniecznie w perspektywie całego życia).
6. Gdzie to testować?
   - W pliku `CMakeLists.txt` są tak właściwie dwa projekty - jeden zwykły, gdzie można sobie testować własną klasę ręcznie, a drugi o nazwie `tests`, który testuje testami, jakie używa Bobot.
7. Są rozbieżności między treścią `README.md`, a treściami w plikach nagłówkowych!
  - W tym roku przechodzimy na `README.md`, więc ta treść jest wiążąca.
____________________________________________________________________________________
# Pytania po implementacji ćwiczenia:
1. Jaka jest różnica między przeciążaniem operatorów jako metoda klasy vs jako funkcja?
2. Których operatorów nie da się przeciążać?
3. Wymień operatory mające różną ilość argumentów?
4. Jakie konsekwencje będzie miało przeciążanie operatorów logicznych? (chodzi o lazy-evaluation)

____________________________________________________________________________________
# Zadania, które warto zrobić (uwaga: nie będzie za to punktów, tylko coś cenniejszego - umiejętności)
1. Przeciążenie pozostałych operatorów.
2. Macierz 3*3 - aby przećwiczyć zdobyte umiejętności.
3. Zrobienie zadania zgodnie z powszechnie przyjętymi standardami, [zestawienie mojego autorstwa](https://programowaniec.wordpress.com/2017/11/09/czego-sie-czepiam/) (można się ze mną nie zgodzić w pewnych kwestiach). Bez jakichkolwiek ostrzeżeń i warningów.
4. Poczytanie/zaimplementowanie czegoś co nas zainteresowało.
5. *Mając już skończonym przez nas można porównać z tym z [chatgpt](chat.openai.com/), ale dopiero po zrobieniu swojego.
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
    ├── CMakeLists.txt      # CMake configuration file - the file is to open out project in our IDE
    ├── main.cpp            # main file - here we can test out solution manually, but it is not required
    ├── matrix.h            # file to create class declaration and methods' declaration
    ├── matrix.cpp          # file to implement methods
    ├── matrixElement.h     # file containing type alias
    ├── trescPdf.pdf        # documentation in PDF (generated by Doxygen)
    ├── tests               # here are tests for exercise, inner CMakeLists.txt, GTest library used by tests
    │   ├── CMakeLists.txt  # iner CMake for tests - it is included by outter CMake
    │   ├── matrixTests.cpp # files with tests for exercise
    │   └── lib             # directory containing GTest library
    ├── Doxyfile            # here is prepared file for Doxygen, to generate documentation when we type `doxygen .`
    ├── doxyfiles           # here is logo for documentation generated by Doxygen
    ├── Dockerfile          # this file contains instructions how to run tests in embedded Ubuntu
    └── README.md           # this file
