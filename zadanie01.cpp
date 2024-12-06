/*
Meno a priezvisko: Arsen Labovich

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (s vypracovanymi rieseniami).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Bod v rovine
struct Point {
    int x; // x-ova suradnica
    int y; // y-ova suradnica
};

// Usecka v rovine
struct Line {
    Point start; // zaciatocny bod
    Point end;   // koncovy bod
};

// Student
struct Student {
    char *name; // meno studenta
    int year;  // rocnik studia
};

// Uspesnost vykonania funkcie
enum class Result {
    SUCCESS, // funkcia vykonana uspesne
    FAILURE  // chyba pri vykonavani funkcie
};

// Matematicka funkcia
enum class Operation {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
};

// Vstup pre matematicky vypocet funkcie s dvoma parametrami
struct CalculationInput {
    int operand1; // prvy parameter
    int operand2; // druhy parameter
    Operation operation; // funkcia
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytlaci obsah pola na standardny vystup.
    V implementacii musi byt pouzity 'std::cout'.

    Format tlace:
    - prvky pola (cisla) su oddelene jednou medzerou
    - pred prvym prvkom je gulata otvaracia zatvorka (medzi zatvorkou a cislom nesmie byt medzera)
    - za poslednym prvkom je gulata zatvaracia zatvorka (medzi cislom a zatvorkou nesmie byt medzera)

    PARAMETRE:
        [in] data - pole cisiel
        [in] length - dlzka pola 'data'

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        prazdne pole: ()
        jednoprvkove pole: (10)
        10 prvkove pole: (8 -5 100000 2 1 2 4 5 -20 345)
*/


//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zo standardneho vstupu nacita dve cele cisla (typu 'int') a vrati ich sucet.
    V implementacii musi byt pouzity 'std::cin' a formatovany vstup.

    NAVRATOVA HODNOTA:
        sucet cisiel nacitanych zo standardneho vstupu

    VSTUPNE PODMIENKY:
        Textovy vstup zadany na standardny vstup programu obsahuje dve cele cisla, ktore mozno reprezetovat typom 'int'.
        Nemusite osetrovat moznost chybnych udajov zadanych na standardny vstup.

    PRIKLADY:
        Ak je na standardny vstup zadany text "10 20\n" (bez uvodzoviek), tak funkcia vrati 30.
        Ak je na standardny vstup zadany text " 10 \n 20 \n" (bez uvodzoviek), tak funkcia vrati 30.
*/
int sumOfTwoNumbersFromConsole() {
    int num1, num2;
    std::cout << "enter first number: ";
    std::cin >> num1 ;
    std::cout << "enter second number: ";
    std::cin >> num2;
    return num1+num2;
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati 'true' ak 'text' obsahuje velke pismeno, inak vrati 'false'.

    PARAMETER:
        [in] text - textovy retazec ukonceny '\0'

    NAVRATOVA HODNOTA:
        'true' - ak 'text' obsahuje aspon jedno velke pismeno
        'false' - ak 'text' neobsahuje ani jedno velke pismeno (plati aj pre prazdny retazec)

    POZNAMKA:
        Pri implementacii pouzite funkciu 'std::isupper'.
*/
bool containsUpperCase(const char *text) {
    for (size_t i = 0; i < strlen(text); i++) {
        if (std::isupper(*(text + i))) {
            return true;
        }
    }
    return false; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati 'true' ak 'data' obsahuje stupajucu postupnost, inak vrati 'false'.

    PARAMETRE:
        [in] data - pole hodnot
        [in] length - pocet prvkov pola 'data'

    NAVRATOVA HODNOTA:
        'true' - ak 'data' obsahuje stupajucu postupnost hodnot, alebo pocet prvkov pola je mensi ako 2
        'false' - v opacnom pripade

    PRIKLADY:
        data = (10, 11, 15, 20) => vysledok je 'true'
        data = (10, 15, 15, 20) => vysledok je 'false'
        data = (10, 11, 15, 12) => vysledok je 'false'
        data = (10)             => vysledok je 'true'
        data = ()               => vysledok je 'true'
*/
bool isAscending(const int *data, std::size_t length) {
    for (size_t i = 1; i < length; i++) {
        if (data[i] <= data[i - 1]) {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia posunie hodnoty pola 'data' o 1 miesto vyssie. Hodnotu posledneho prvku presunie na zaciatok.

    PARAMETRE:
        [in,out] data - pole hodnot, ktore bude preusporiadane
        [in] length - pocet prvkov pola 'data'

    PRIKLADY:
        (10, 20, 30, 40, 50) => (50, 10, 20, 30, 40)
        (10) => (10)
        () => ()
*/
void shiftUp(int *data, std::size_t length) {
    int temp;
    for (size_t i = 1; i < length; i++) {
        temp = data[i];
        data[i] = data[0];
        data[0] = temp;
    }
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia preusporiada pole 'data' tak, ze jeho prvky budu v opacnom poradi.

    PARAMETRE:
        [in, out] data - pole hodnot, ktore bude preusporiadane
        [in] lenght - pocet prvkov pola 'data'

    PRIKLADY:
        (10, 20, 30, 40, 50) => (50, 40, 30, 20, 10)
        (10, 2, 30, 4) => (4, 30, 2, 10)
        (10) => (10)
        () => ()
*/
void reverse(int *data, std::size_t length) {
    int temparr[length];
    for (size_t i = 0; i < length; i++) {
        temparr[i] = data[length - i - 1];
    }
    for (size_t i = 0; i < length; i++) {
        data[i] = temparr[i];
    }
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati dlzku usecky 'line'

    PARAMETER:
        [in] line - usecka

    NAVRATOVA HODNOTA:
        dlzka usecky 'line'

    PRIKLAD:
        line:
            start:
                x=10
                y=20
            end:
                x=100
                y = 50
        return 94.868329805
*/
double length(const Line *line) {
    int dx = line->start.x - line->end.x;
    int dy = line->start.y - line->end.y;
    return sqrt(pow(dx, 2) + pow(dy, 2));
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Implementujte rovnaku funkcionalitu ako v predchadzajucom priklade. Rozdielny je len typ parametra funkcie.
*/
double length(const Line &line) {
    int dx = line.start.x - line.end.x;
    int dy = line.start.y - line.end.y;
    return sqrt(pow(dx, 2) + pow(dy, 2));
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori noveho studenta s menom 'name' a rocnikom studia 'year'.
    Vrati smernik na vytvoreneho studenta.
    Pre alokaciu pamate pouzite operatory 'new' a 'new[]'.

    PARAMETRE:
        [in] name - meno studenta
        [in] year - rocnik v ktorom student studuje

    NAVRATOVA HODNOTA:
        vytvoreny student

    VSTUPNE PODMIENKY:
        'name' je textovy retazec ukonceny '\0'
*/
Student *createStudent(const char *name, int year) {
    Student *student = new Student;
    student->name = new char[strlen(name)+1];
    strcpy(student->name, name);
    student->year = year;
    return student;
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vypocita celociselny matematicky vypocet zadany parametrom 'input'.
    Vysledok ulozi do 'output'.

    PARAMETRE:
        [in] input - vstupne udaje pre matematicky vypocet
        [out] output - vystupna hodnota vypoctu (v pripade moznosti vypoctu)

    NAVRATOVA HODNOTA:
        Result::SUCCESS - ak je mozne vypocitat vyslednu hodnotu
        Result::FAILURE - ak nie je mozne vypocitat vyslednu hodnotu (v pripade delenia nulou)

    VYSTUPNE PODMIENKY:
        - Vysledok vypoctu je celociselny.
        - Ak je mozne vykonat vypocet, tak sa vysledok ulozi do 'output' a funkcia vrati 'Result::SUCCESS',
          inak (v pripade delenia nulou) sa hodnota 'output' nemeni a funkcia vrati 'Result::FAILURE'.
*/
Result calculate(int *output, const CalculationInput *input) {
    if (input->operation == Operation::DIVIDE && input->operand2 == 0) {
        return Result::FAILURE;
    }
    if (input->operation == Operation::PLUS) {
        *output = input->operand1 + input->operand2;
    }
    if (input->operation == Operation::MINUS) {
        *output = input->operand1 - input->operand2;
    }
    if (input->operation == Operation::MULTIPLY) {
        *output = input->operand1 * input->operand2;
    }
    if (input->operation == Operation::DIVIDE) {
        *output = input->operand1 / input->operand2;
    }
    return Result::SUCCESS;
}

int main() {
    return 0;
}
