#ifndef SHAPE_H
#define SHAPE_H

/** @file stage.h
@brief Implementacja klasy czysto abstrakcyjnej `Shape`, majacej funkcje opisane nizej.
   Zadanie ma na celu "ugryzienie" polimorfizmu dynamicznego, w tym również o kompozycje klas w formie drzewa.
1. Klasa `Shape` powinna mieć metodę `bool isIn(int x, int y) const = 0;`, ktora zwraca informacje czy dany punkt jest wewnatrz figury czy nie
2. Proszę zaimplementować klasę `Rectangle` dziedziczącą po `Shape` i implementującą powyższą metodę.
   1. Implementacja klasy powinna być dokonana w nowo-utworzonych plikach: `rectangle.h` i `rectangle.cpp`
   2. Konstruktor powinien przyjmować położenia współrzędnych dwóch: dolnegolewego i gornegoprawego `(xFrom, yFrom, xTo, yTo)`
   3. Odpowiada to prostokątowi o bokach równoległych do osi wykresu
3. Proszę zaimplementować klasę `Circle` dziedziczącą po `Shape` i implementującą jej metodę.
   1. Implementacja klasy powinna być dokonana w nowo-utworzonych plikach: `circle.h` i `circle.cpp`
   2. Konstruktor powinien przyjmować wspolrzedne srodka, oraz promien `(int xCenter, int yCenter, int radius)`
4. Proszę zaimplementować klasę-kompozyt `ShapeComposite` dziedziczącą po `Shape` i implementującą jej metodę.
   Klasa ta w konstruktorze powinna przyjąć:
    1. dwie instancje `shared_ptr<Shape>`
    2. operacje na zbiorach `enum class ShapeOperation`: `INTERSECTION`, `SUM`, `DIFFERENCE`
    3. w oparciu o to bedzie mozna cala hierarchie figur polaczyc w jedno drzewo,
       dla ktorego bedzie mozna zapytac czy dany punkt jest w hierarchii, czy nie (metoda `isIn`).
5. Opcjonalnie mozna sobie zaimplementowac klase `Stage` rysujaca na konsole.
________________________
Przyklad obrazka jaki można osiągnąć komponując dwa kształty przy pomocy operacji na zbiorach:
```
     21:            *******
     20:          ***********
     19:         *************
     18:        ***************
     17:       *****************
     16:      *******************
     15:      *******************
     14:     *********************
     13:     *********************
     12:     ***      ***      ***
     11:     ***      ***      ***
     10:     ***      ***      ***
      9:     ***      ***      ***
      8:     ***      ***      ***
      7:     ***      ***      ***
      6:     ***      ************
      5:     ***      ************
      4:     ***      ************
      3:     ***      ************
      2:     ***      ************
      1:     *********************
```

____________________________________________________________________________________

Informacje o co chodzi w paczce, na co zwrócić uwagę, jak czytać testy znajdują się w materiale [wideo](https://banbye.com/watch/v_Bvp_U7USzEVC).
____________________________________________________________________________________
## Uwaga:
Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne,
metody większe niż 1-linijkowe powinny być zadeklarowane w klasie, zdefiniowane
poza klasą, obiekty typów klasowych powinny być w miarę możliwości przekazywane
w argumentach funkcji przez referencję, proszę też stosować słówko "const" w
odpowiednich miejscach.
@note Co się da na listę inicjalizacyjną konstruktora.

Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.

## Punktacja:
Na maksa przejście wszystkich testów i niepoprawnych operacji na pamieci (m.in. wyciekow pamieci)
____________________________________________________________________________________
## Podpowiedzi:
1. Warto sobie stworzyć pomocniczą strukturę Point do trzymania współrzędnych.
2. Proszę pamiętać o dodawaniu klas w przestrzeni nazw Shapes
3. Klasa Shape powinna mieć zdefiniowaną prze nas jedną specjalną metodę poza `isIn`, każda klasa bazowa w polimorfiźmie powinna.
4. Pamiętajcie o słówku kluczowym `override` przy metodzie `isIn`.
____________________________________________________________________________________
## Najczęstsze błędy/pytania/problemy:
1. Zaimplementowałem metodę klasy w pliku źródłowym dodałem `using namespace Shapes`, a linker sygnalizuje, że niezdefiniowałem Shapes::Klasa::metoda.
   1. `using namespace` nie dodanie do danej przestrzeni nazw czegokolwiek, to jedynie powoduje dostęp do składowych tej przestrzeni nazw tak jakby jej nie było.
      Dlatego nie ma wyjścia - trzeba zdefiniować metodę w taki sposób `... Shapes::Klasa::metoda(...) {...}`
2. Dodałem plik z implementacją danej klasy, a testy uparcie twierdzą, że nie.
   1. To wynika z faktu, że "aktywowanie" odpowiedniej części kodu odbywa się na etapie kompilacji - tam jest wykrywane czy plik istnieje czy nie.
      Aby skompilowały się testy musi się zmienić coś w pliku testów lub w pliku includowanym.
      **Konkretnie: po dodaniu pliku przebuduj cały projekt!**
3. Jak zaimplementowac `isIn` dla kola?
   1. Matematyka - czy odległość punktu od środka koła jest nie większa niż promień.
4. Napisałem klasę `Rectangle`, która dziedziczy po `Shape`, a kompilator sygnalizuje jakby nie było dziedziczenia.
   1. Domyślnie dziedziczenie w C++ jest prywatne, należy więc pamiętać o słówku `public`.
   2. Czy zdefiniowano klasę w odpowiedniej przestrzeni nazw?
5. Po co jest struktura `Shapes::Point`?
   1. Można jej użyć aby trzymać współrzędne X i Y.
**/

namespace Shapes
{
struct Point
{
    int x_, y_;
};

class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default;
    [[nodiscard]] virtual bool isIn(int x, int y) const = 0;
protected:
};

enum class ShapeOperation {
    INTERSECTION,
    SUM,
    DIFFERENCE
};

} // namespace Shapes

#endif // SHAPE_H
