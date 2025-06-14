# Shapes drawing
W zadaniu chodzi o to aby użyć polimorfizmu w C++ w poprawny sposób, pamiętając o koniecznych elementach.
Przy okazji prostej implementacji powstaje ciekawa kompozycja umożliwiająca rysowanie złożonych kształtów jak przykładowo:
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

## Klasa abstrakcyjna Shape:
Implementacja klasy czysto abstrakcyjnej `Shape`, majacej funkcje opisane niżej.   
Zadanie ma na celu "ugryzienie" polimorfizmu dynamicznego, w tym również o kompozycje klas w formie drzewa.   
Wraz z implementacją kolejnych klas powinny się aktywować kolejne testy 
(aktywacja następuje, gdy dany plik istnieje, nie ma makr preprocesora do zakomentowania).
1. Klasa `Shape` powinna mieć metodę `virtual bool isIn(int x, int y) const = 0;`, ktora zwraca informacje czy dany punkt jest wewnatrz figury czy nie
2. Proszę zaimplementować klasę `Rectangle` dziedziczącą po `Shape` i implementującą powyższą metodę.
   1. Implementacja klasy powinna być dokonana w nowo-utworzonych plikach: `rectangle.h` i `rectangle.cpp` (zwróć uwagę na wielkość liter w nazwie)
   2. Konstruktor powinien przyjmować położenia współrzędnych dwóch: dolnegolewego i gornegoprawego `(xFrom, yFrom, xTo, yTo)`
   3. Odpowiada to prostokątowi o bokach równoległych do osi wykresu
3. Proszę zaimplementować klasę `Circle` dziedziczącą po `Shape` i implementującą jej metodę.
   1. Implementacja klasy powinna być dokonana w nowo-utworzonych plikach: `circle.h` i `circle.cpp` (zwróć uwagę na wielkość liter w nazwie)
   2. Konstruktor powinien przyjmować wspolrzedne środka, oraz promien `(int xCenter, int yCenter, int radius)`
4. Proszę zaimplementować klasę-kompozyt `ShapeComposite` dziedziczącą po `Shape` i implementującą jej metodę.
   Klasa ta w konstruktorze powinna przyjąć:
    1. dwie instancje `std::shared_ptr<Shape>`
    2. operacje na zbiorach `enum class ShapeOperation`: `INTERSECTION`, `SUM`, `DIFFERENCE`
    3. w oparciu o to bedzie mozna cala hierarchie figur polaczyc w jedno drzewo,
       dla ktorego bedzie mozna zapytac czy dany punkt jest w hierarchii, czy nie (metoda `isIn`).
    4. Proszę zwrócić uwagę na konstruktor aby istniał przyjmujący argumenty, jakich wymagają testy.
    5. **UWAGA: Linux rozróżnia wielkość liter w przeciwieństwie do Windowsa. 
       Proszę ustawić nazwę klasy dokładnie na: `shapecomposite.h`.**
5. \*Opcjonalnie mozna sobie zaimplementowac klase `Stage` rysujaca na konsole.
____________________________________________________________________________________

Informacje o co chodzi w paczce, na co zwrócić uwagę, jak czytać testy znajdują się w materiale [wideo](https://banbye.com/watch/v_Bvp_U7USzEVC).
____________________________________________________________________________________
## Uwaga:
Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne,
metody większe niż 1-linijkowe powinny być zadeklarowane w klasie, zdefiniowane
poza klasą, obiekty typów klasowych powinny być w miarę możliwości przekazywane
w argumentach funkcji przez referencję, proszę też stosować słówko `const` w
odpowiednich miejscach. Wszystkie metody, które mogą być stałe proszę aby były.

1. Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.
2. Gettery i settery operujace na liczbach, ktore nie rzucaja wyjatku, warto zadeklarowac jako `noexcept`.
3. Co się da na listę inicjalizacyjną konstruktora.
4. Za złe zarządzanie pamięcią (wycieki, pisanie poza pamięcią) powodują odejmowanie punktów

[Bardziej szczegółowe informacje jak pisać programy w ładnym stylu](https://programowaniec.wordpress.com/2017/11/09/czego-sie-czepiam/) dla zaawansowanych.

____________________________________________________________________________________
## Podpowiedzi:
1. Warto sobie stworzyć pomocniczą strukturę Point do trzymania współrzędnych.
2. Proszę pamiętać o dodawaniu klas w przestrzeni nazw Shapes
3. Klasa Shape powinna mieć zdefiniowaną przez nas jedną specjalną metodę poza `isIn`, każda klasa bazowa w polimorfiźmie powinna.
4. Pamiętajcie o słówku kluczowym `override` przy metodzie `isIn` - to jest dobra praktyka.

____________________________________________________________________________________
## Poruszane w paczce zagadnienia:
1. Pomimorfizm dynamiczny:
   1. Klasa czysto abstrakcyjna
   2. Użycie polimorfizmu
   3. Agregacja obiektów polimorficznych (jako wskaźniki)
2. Typy wyliczeniowe (`enum class`).
3. Inteligentne wskaźniki: `std::shared_ptr<T>`
4. Przestrzenie nazw.

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
## Najczęstsze błędy/pytania/problemy:
1. Zaimplementowałem metodę klasy w pliku źródłowym dodałem `using namespace Shapes`, a linker sygnalizuje, że niezdefiniowałem `Shapes::Klasa::metoda`.
   1. `using namespace` nie dodanie do danej przestrzeni nazw czegokolwiek, to jedynie powoduje dostęp do składowych tej przestrzeni nazw tak jakby jej nie było.
      Dlatego nie ma wyjścia - trzeba zdefiniować metodę w taki sposób `... Shapes::Klasa::metoda(...) {...}`
2. Dodałem plik z implementacją danej klasy, a testy uparcie twierdzą, że nie.
   1. To wynika z faktu, że "aktywowanie" odpowiedniej części kodu odbywa się na etapie kompilacji - tam jest wykrywane czy plik istnieje czy nie.
      Aby skompilowały się testy musi się zmienić coś w pliku testów lub w pliku includowanym.
      **Konkretnie: po dodaniu pliku przeładuj konfiguracje CMake'a, oraz przebuduj cały projekt!**
3. Jak zaimplementowac `isIn` dla kola?
   1. Matematyka - czy odległość punktu od środka koła jest nie większa niż promień.
4. Napisałem klasę `Rectangle`, która dziedziczy po `Shape`, a kompilator sygnalizuje jakby nie było dziedziczenia.
   1. Domyślnie dziedziczenie w C++ jest prywatne, należy więc pamiętać o słówku `public`.
   2. Czy zdefiniowano klasę w odpowiedniej przestrzeni nazw?
5. Po co jest struktura `Shapes::Point`?
   1. Można jej użyć aby trzymać współrzędne X i Y, ale nie jest to konieczne.
____________________________________________________________________________________
# Pytania po implementacji ćwiczenia:
1. Co tak właściwie daje słówko `override`?
____________________________________________________________________________________
# Zadania, które warto zrobić (uwaga: nie będzie za to punktów, tylko coś cenniejszego - umiejętności)
1. Warto sobie napisać funkcjonalność, która narysuje to co narysowaliśmy, 
   można do tego celu użyć [dowolnej biblioteki do rysowania grafiki](https://stackoverflow.com/questions/1610210/c-graphic-drawing-library).

____________________________________________________________________________________
## Podpięte narzędzia:
1. `cppcheck` - narzędzie do statycznej analizy kodu, które analizuje kod i szyka potencjalnych błędów (statyczny analizator może się pomylić)
2. `flawfinder` - narzędzie do statycznej analizy kodu pod względem podatności kodu pod względem bezpieczeństwa
3. `perf` (`perf stats` i `perf record`), narzędzie do zaawansowanego monitorowanania wykonywania programu, można zarówno podejrzeć szczegóły wykonania (`perf stats`), jak i prześledzić ile czasu program spędził w danej funkcji (`perf record`). W oparciu o wynik tej drugiej komendy można prześledzić w sposób interaktywny w [programie hotspot](https://github.com/KDAB/hotspot), natomiast można też wygenerować grafikę w oparciu o [brendangregg/Flamegraph](https://github.com/brendangregg/Flamegraph.git).
4. `cpplint` - narzędzie do statycznej analizy kodu, autorstwa firmy Google, które znajduje różne rzeczy do poprawy (również aspekty związane ze stylem programowania)
5. `clang-tidy` - narzędzie do analizy kodu bazujące na kompilatorze, służy jako backend w wielu środowiskach programistycznych znajdując błędy na bieżąco. Narzędzie to raczej się nie myli (ma pod spodem kompilator), chociaż może być bardziej restrykcyjne niż aktualnie używany kompilator.
6. Wykrywanie tabów w plikach - zła praktyka aby umieszczać znaki tabulacji w plikach źródłowych z C++. A także narzędzie do wykrywania tzw. trailing whitespaces - czyli białych znaków na końcu linii. Robię to jako skrypty bashowe.
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
    ├── shape.h                 # file to implement abstract class
    ├── tests                   # here are tests for exercise, inner CMakeLists.txt, GTest library used by tests
    │   ├── CMakeLists.txt      # iner CMake for tests - it is included by outter CMake
    │   ├── lib                 # directory containing GTest library
    │   └── shapesTests.cpp     # tests v1
    ├── doxyfiles               # here is logo for documentation generated by Doxygen
    │   └── cppLogo.png         # logo
    ├── Doxyfile                # here is prepared file for Doxygen, to generate documentation when we type `doxygen .`
    ├── Dockerfile              # this file contains instructions how to run tests in embedded Ubuntu
    └── README.md               # this file
