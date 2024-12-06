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

using namespace std;

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy prvok do heapu.
    Verzia heap-u je Min-heap (hodnota kazdeho uzla je mensia alebo rovna, ako hodnoty vsetkych jeho nasledovnikov).
    Pouzite algoritmus sift up.

    PARAMETRE:
        [in, out] data - pole, ktoreho prva cast tvori heap, do ktoreho funkcia prida novy prvok
        [in] addIndex - index prvku v 'data', ktory funkcia prida do heap-u (preusporiadanim prvkov)

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole s dlzkou minimalne 'addIndex+1'
        'addIndex' moze mat lubovolnu hodnotu
        Prvky data[0]...data[addIndex-1] (vratane) tvoria heap

    VYSTUPNE PODMIENKY:
        Prvky data[0]...data[addIndex] (vratane) tvoria heap
        Funkcia preusporiadala prvky data[0]...data[addIndex] tak, aby tvorili heap

    PRIKLADY:
        vstup:  data = (1, 2, 10, 7, 4, 2, 5, 0, 3, -1, 11, 12, 1), addIndex = 4
        //              0  1   2   3  4
        vystup: data = (1, 2, 10, 7, 4, 2, 5, 0, 3, -1, 11, 12, 1)

        vstup:  data = (3, 4, 10, 5, 5, 11, 15, 7, 8, 9, 10, 14,  8, 1, 2), addIndex = 12
        vystup: data = (3, 4,  8, 5, 5, 10, 15, 7, 8, 9, 10, 14, 11, 1, 2)

        vstup:  data = (3, 4, 10, 5), addIndex = 0
        vystup: data = (3, 4, 10, 5)
*/

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void siftUp(int data[], const size_t addIndex) {
    size_t child = addIndex;
    while (child > 0) {
        size_t parent = (child - 1) / 2;
        if (data[parent] > data[child]) {
            swap(&data[parent], &data[child]);
            child = parent;
        } else {
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori heap na poli 'data' preusporiadanim prvkov.
    Verzia heap-u je Min-heap.
    Pouzite algoritmus sift up.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia preusporiada, aby bolo heap-om
        [in] length - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole, ak 'length' > 0
        'length' moze mat lubovolnu hodnotu

    VYSTUPNE PODMIENKY:
        'data' je heap-om

    PRIKLAD:
        vstup:  data = (7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6), length = 11
        vystup: data = (1, 2, 2, 2, 2, 5, 3, 7, 4, 8, 6)
*/
void buildHeapSiftUp(int data[], const size_t length) {
    for (size_t i = 1; i < length; i++) {
        siftUp(data, i);
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia opravi cast heap-u (podstrom, ktoreho koren ma index 'topIndex').
    Verzia heap-u je Min-heap.
    Pouzite algoritmus sift down.

    PARAMETRE:
        [in, out] data - pole, v ktorom funkcia opravi cast heapu preusporiadanim prvkov
        [in] topIndex - index korena podstromu (casti heapu), ktory sa ma opravit
        [in] length - pocet prvkov pola

    VSTUPNE PODMIENKY:
        Podstromy prvku s indexom 'topIndex' splnaju podmienky heap (podstromy, ktorych korene su priamy nasledovnici uzla s indexom 'topIndex').
        'data' ukazuje na platne pole
        'topIndex' moze mat lubovolnu hodnotu
        'length' moze mat lubovolnu hodnotu

    VYSTUPNE PODMIENKY:
        Podstrom, ktoreho koren ma index 'topIndex', splna podmienku heap.

    PRIKLADY:
        vstup:  data = (55, 20, 10, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140), topIndex = 0, length = 15
                        (10, 20, 50, 30, 40, 55, 60, 70, 80, 90, 100, 110, 120, 130, 140)
        vystup: data = (10, 20, 50, 30, 40, 55, 60, 70, 80, 90, 100, 110, 120, 130, 140)

        vstup:  data = (100, 8, 2, 1, 0, 5, 6, 7, 4, 2, 3, 11, 12, 13, 14, 15, 16, 17), topIndex = 1, length = 18
        vystup: data = (100, 0, 2, 1, 2, 5, 6, 7, 4, 8, 3, 11, 12, 13, 14, 15, 16, 17)
*/

int minimum(int a, int b){
    if(a<=b){return a;}
    return b;
}
void siftDown(int data[], const size_t topIndex, const size_t length) {
    size_t parent = topIndex;
    while (true) {
        size_t left = parent * 2 + 1;
        size_t right = parent * 2 + 2;
        size_t minIndex = parent;

        if (left < length && data[left] < data[minIndex]) {
            minIndex = left;
        }
        if (right < length && data[right] < data[minIndex]) {
            minIndex = right;
        }
        if (minIndex != parent) {
            swap(&data[parent], &data[minIndex]);
            parent = minIndex;
        } else {
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori heap na poli 'data' preusporiadanim prvkov.
    Verzia heap-u je Min-heap.
    Pouzite algoritmus sift down.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia preusporiada, aby bolo heap-om
        [in] length - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole, ak 'length' > 0
        'length' moze mat lubovolnu hodnotu

    VYSTUPNE PODMIENKY:
        'data' je heap-om

    PRIKLAD:
        vstup:  data = (7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6), length = 11
        vystup: data = (1, 2, 3, 2, 2, 5, 7, 4, 2, 8, 6)
*/
void buildHeapSiftDown(int data[], const size_t length) {
    for (size_t i = length / 2; i > 0; i--) {
        siftDown(data, i, length);
    }
    siftDown(data, 0, length);
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia preusporiada pole 'da   ta' od najvacsieho prvku po najmensi.
    Pouzite algoritmus heap sort.

    PARAMETRE:
        [in,out] data - pole, ktore funkcia usporiada
        [in] length - dlzka pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole, ak 'length' > 0
        'length' moze mat lubovolnu hodnotu

    VYSTUPNE PODMIENKY:
        Pole 'data' je usporiadane

    PRIKLAD:
        vstup:  data = (7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6), length = 11
        vystup: data = (8, 7, 6, 5, 4, 3, 2, 2, 2, 2, 1)
*/
void heapSort(int data[], const size_t length) {
    if (length == 0) return;
    buildHeapSiftDown(data, length);
    for (size_t i = length - 1; i > 0; i--) {
        swap(&data[0], &data[i]);
        siftDown(data, 0, i);
    }
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------
void test1() {
    int data1[] = {1, 2, 10, 7, 4, 2, 5, 0, 3, -1, 11, 12, 1};
    int addIndex1 = 4;
    siftUp(data1, addIndex1);
    cout << "Test 1: ";
    for (int i = 0; i < 13; ++i) {
        cout << data1[i] << " ";
    }
    cout << endl;
    // Expected output: 1 2 10 7 4 2 5 0 3 -1 11 12 1

    int data2[] = {3, 4, 10, 5, 5, 11, 15, 7, 8, 9, 10, 14, 8, 1, 2};
    int addIndex2 = 12;
    siftUp(data2, addIndex2);
    cout << "Test 2: ";
    for (int i = 0; i < 15; ++i) {
        cout << data2[i] << " ";
    }
    cout << endl;
    // Expected output: 3 4 8 5 5 10 15 7 8 9 10 14 11 1 2

    int data3[] = {3, 4, 10, 5};
    int addIndex3 = 0;
    siftUp(data3, addIndex3);
    cout << "Test 3: ";
    for (int i = 0; i < 4; ++i) {
        cout << data3[i] << " ";
    }
    cout << endl;
    // Expected output: 3 4 10 5
}

void test2() {
    int data1[] = {7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6};
    size_t length1 = 11;
    buildHeapSiftUp(data1, length1);
    cout << "Test 2: ";
    for (size_t i = 0; i < length1; ++i) {
        cout << data1[i] << " ";
    }
    cout << endl;
    // Expected output: 1 2 2 2 2 5 3 7 4 8 6
}

void test3() {
    int data1[] = {55, 20, 10, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140};
    size_t topIndex1 = 0;
    size_t length1 = 15;
    siftDown(data1, topIndex1, length1);
    cout << "Test 1: ";
    for (size_t i = 0; i < length1; ++i) {
        cout << data1[i] << " ";
    }
    cout << endl;
    // Expected output: 10 20 50 30 40 55 60 70 80 90 100 110 120 130 140

    int data2[] = {100, 8, 2, 1, 0, 5, 6, 7, 4, 2, 3, 11, 12, 13, 14, 15, 16, 17};
    size_t topIndex2 = 1;
    size_t length2 = 18;
    siftDown(data2, topIndex2, length2);
    cout << "Test 2: ";
    for (size_t i = 0; i < length2; ++i) {
        cout << data2[i] << " ";
    }
    cout << endl;
    // Expected output: 100 0 2 1 2 5 6 7 4 8 3 11 12 13 14 15 16 17
}


int main() {
    int data1[] = {};
    heapSort(data1,0);
    return 0;
}
