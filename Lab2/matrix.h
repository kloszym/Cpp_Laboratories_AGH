#ifndef MATRIX_H
#define MATRIX_H

/** @file matrix.h
@brief Przeciążanie operatorów na przykładzie Macierzy (bardziej szczegolowa tresc w README.md):
1. Zaimplementuj klasę TwoDimensionMatrix odzwierciedlajaca macierz 2*2, zawierającą:
    - tablice typu `MatrixElement` (alias na typ `int`, zdefiniowany w pliku `matrixElement.h`), 
    - `size_` - liczbę bez znaku o wartości wynoszacej 2
    - konstruktory:
        - bezargumentowy - zerujący wszystkie elementy macierzy
        - kopiujący - kopiujacy wszystkie elementy macierzy
        - przyjmujący jako argument tablicę `const MatrixElement matrix[size_][size_]` i kopiujący z niej wartości
    - funkcja składowa do dostępu do elementów (`get()`) zwracająca odpowiedni element przyjmując dwa argumenty: `row` i `column`
    - funkcja zwracająca `size_` o nazwie (`size()`), proponuję aby była `static constexpr`
    - po zaimplementowaniu usun makro `UNIMPLEMENTED_CONSTRUCTORS`
2. Uzupełnij klasy o następujące operacje zdefiniowane poprzez przeciążenie operatorów:
    - operator przypisania kopiujący (głęboko): `operator=()`
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_ASIGNMENT_OPERATOR`
    - operatory wypisywania do strumienia (jako funkcja zewnętrzna) - format i separator elementow dowolny,
      byleby wszystkie elementy były w strumieniu
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_OSTREAM_OPERATOR`
    - operatory wczytywania ze strumienia (jako funkcja zewnętrzna) - dla macierzy:
      ```
      { a, b }
      { c, d }
      ```
      wczytuje sie w nastepujący sposób:
      ```
        a b
        c d
      ```
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_ISTREAM_OPERATOR`
    - operatory arytmetyczne (stosujące odpowiednie operacje na macierzach):
        - `TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2); // jako funkcja globalna`
        - `TwoDimensionMatrix& operator*=(MatrixElement number); // metoda klasy`
        - Zadany operator logiczny (metoda klasy) - to jest przykład gdzie **nie** należy przeciążać operatorów:
          `TwoDimensionMatrix operator&&(const TwoDimensionMatrix& matrix) const;`  
          Wykonująca na każdym z elementów `&&`, czyli:
          ```
          { 0, 0 }      { 0, 6 }      { 0, 0 }
          {-3, 9 }  &&  { 0, -9 }  =  { 0, 1 }
          ```
           - po zaimplementowaniu usun makro `UNIMPLEMENTED_ARITHMETIC_OPERATORS`
    - operator tablicowy dostający się po indeksie do pierwszego z wymiarów tablicy (metoda klasy), 
        **proszę pamiętać, że mają być dwie wersje: z i bez const**
          `MatrixElement* operator[](size_t i);`
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_SUBSCRIPT_OPERATOR`
       - Od C++23 istnieje możliwość zdefiniowania tego operatora przyjmującego dwa argumenty,
        ze względu na fakt, że nie wszyscy Państwo mają kompilatory zgodne z tym standardem to testy oczekują wersji jedno-argumentowej.
        Kto może zachęcam aby spróbował zaimplementować ten operator:
        `MatrixElement& operator[](size_t row, size_t column);`
          - po zaimplementowaniu mozna sobie sprobowac usunac makro `UNIMPLEMENTED_SUBSCRIPT_OPERATOR_CPP23` (wraz z `UNIMPLEMENTED_SUBSCRIPT_OPERATOR`)
       - Osoby zaawansowane mogą spróbować użyć funckjonalności C++23, tzw. "Deducting this",
         niestety kompilator na bobotcie tego nie obsłuży, stąd lepiej tego nie wysyłać.
    - operator konwersji do `size_t`, zwracający to co `size()` (metoda klasy),
       - po zaimplementowaniu usun makro `UNIMPLEMENTED_CONVERSION_OPERATOR`
Deklaracja klasy i funkcji globalnych powinna się znaleźć w pliku "matrix.h", natomiast definicje funkcji zewnętrznych i metod klas w pliku źródłowym "matrix.cpp"
____________________________________________________________________________________
## Uwaga (bardziej wiazaca tresc jest w pliku `README.md`):
Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne,
metody większe niż 1-linijkowe powinny być zadeklarowane w klasie, zdefiniowane
poza klasą, obiekty typów klasowych powinny być w miarę możliwości przekazywane
w argumentach funkcji przez referencję, proszę też stosować słówko "const" w
odpowiednich miejscach.

Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.
____________________________________________________________________________________
## Punktacja:
Na maksa przejście wszystkich testów i niepoprawnych operacji na pamieci (m.in. wyciekow pamieci)
____________________________________________________________________________________
## Najczestsze pytania/błędy/problemy:
1. Jak ma działać `&&` dla macierzy?
   - Wykonująca na każdym z elementów `&&`, czyli:

    ```
    { 0, 0 }      { 0, 6 }      { 0, 0 }
    {-3, 9 }  &&  { 0, -9 }  =  { 0, 1 }
    ```
2. Jak ma działać operator tablicowy []?
    Operator ten przyjmuje tylko jeden argument (poza this), a chcemy odnieść się w następujący sposób:
    `matrix[row][column]`, dlatego ten operator musi zwrócić `matrix[row]` typu `MatrixElement*`.
3. Mam operator indeksowania `[]`, a kompilator jakby go nie widzi.
    To najczęstrzy błąd w tym zadaniu - muszą być dwie wersje - jedna zwykła, a druga stała (przydomek `const`)
____________________________________________________________________________________
# Pytania po implementacji ćwiczenia:
@note A. Jaka jest różnica między przeciążaniem operatorów jako metoda klasy vs jako funkcja?
@note B. Których operatorów nie da się przeciążać?
@note C. Wymień operatory mające różną ilość argumentów?
@note D. Jakie konsekwencje będzie miało przeciążanie operatorów logicznych? (chodzi o lazy-evaluation)
**/

#include <iosfwd>

#include "matrixElement.h"


#define UNIMPLEMENTED_SUBSCRIPT_OPERATOR_CPP23 // bobot does not have nevest compiler

class TwoDimensionMatrix
{
    constexpr static size_t size_ = 2;

public:

    TwoDimensionMatrix();

    TwoDimensionMatrix(const TwoDimensionMatrix &matrix);

    TwoDimensionMatrix(const MatrixElement[size_][size_]);

    MatrixElement get(int column, int row) const{return matrix_[column][row];};
    static constexpr size_t size(){return size_;}


    TwoDimensionMatrix operator=(const TwoDimensionMatrix&);

    friend std::ostream &operator<<(std::ostream &os, const TwoDimensionMatrix &m){return os << '{' << m.matrix_[0][0] << ", " << m.matrix_[1][0] << "}\n" << '{' << m.matrix_[0][1] << ", " << m.matrix_[1][1] << "}\n";}
    friend std::istream &operator>>(std::istream &is, TwoDimensionMatrix &m){return is >> m.matrix_[0][0] >> m.matrix_[0][1] >> m.matrix_[1][0] >> m.matrix_[1][1];}

    TwoDimensionMatrix& operator*=(MatrixElement);
    TwoDimensionMatrix operator&&(const TwoDimensionMatrix&) const;

    MatrixElement* operator[](int);
    const MatrixElement* operator[](int) const;

    operator size_t() const;

private: // methods:

private: // fields:
    MatrixElement matrix_[size_][size_]{};
};

TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2);

#endif // MATRIX_H
