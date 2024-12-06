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
#include <cstring>

using namespace std;

struct Node {
    int data;
    Node *next;
};

struct List {
    Node *first;
};

void insertionSort(int *data, const size_t length) {
    for (size_t i = 1; i < length; ++i) {
        size_t k = i;
        while (k > 0 and (*(data + k - 1) < *(data + k))) {
            int temp = *(data + k - 1);
            *(data + k - 1) = *(data + k);
            *(data + k) = temp;
            --k;
        }
    }
}

void insertionSort(const char *data[]) {
    size_t length = 0;
    for (; data[length] != nullptr; ++length);
    for (size_t i = 1; i < length; ++i) {
        size_t k = i;
        while (k > 0 and strcmp(data[k - 1], data[k]) < 0) {
            const char *temp = data[k - 1];
            data[k - 1] = data[k];
            data[k] = temp;
            --k;
        }
    }

}

void insertionSort(List *list) {
    if (list->first == nullptr) { return; }
    Node *sorted = nullptr;

    Node *current = list->first;
    while (current != nullptr) {
        Node *next = current->next;

        if (sorted == nullptr || sorted->data <= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->next != nullptr && temp->next->data > current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    list->first = sorted;
}
//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1].
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli).
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli).

    PRIKLAD:
        low: 4
        middle: 8
        hight: 12
        input:                         (10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10)
        output pred vykonanim funkcie: (20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20)
        output po vykonani funkcie:    (20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, const size_t low, const size_t middle, const size_t high) {
    size_t o_i = low;
    size_t r_i = middle;
    size_t l_i = low;
    while (l_i < middle && r_i < high && o_i < high) {
        if (input[l_i] >= input[r_i]) {
            output[o_i++] = input[l_i++];
        } else {
            output[o_i++] = input[r_i++];
        }
    }
    while (l_i < middle) {
        output[o_i++] = input[l_i++];
    }
    while (r_i < high) {
        output[o_i++] = input[r_i++];
    }
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.
    Vytvorte jedno pomocne pole. Pre alokaciu a dealokaciu pomocneho pola pouzite new[] a delete[].

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete hlavnu cast algoritmu merge sort.
*/
void mergeSortRecursive(int *data, int *temp, const size_t low, const size_t high) {
    if (high - low < 2) {
        return;
    }

    size_t middle = (low + high) / 2;
    mergeSortRecursive(data, temp, low, middle);
    mergeSortRecursive(data, temp, middle, high);

    mergeNeighbours(temp, data, low, middle, high);

    for (size_t i = low; i < high; i++) {
        data[i] = temp[i];
    }
}

void mergeSort(int *data, const size_t length) {
    if (length < 2) {
        return;
    }

    int *temp = new int[length];
    mergeSortRecursive(data, temp, 0, length);
    delete[] temp;
}

int main() {
    return 0;
}