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
(8)  V prvych osmich prikladoch mozete pouzit iterativnu alebo rekurzivnu implementaciu. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
     V pripade implementacie rekurziou, moze byt hlavna cast implemetovana v pridanej rekurzivnej funkcii. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <exception>
#include <set>
#include <cassert>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol binarneho vyhladavacieho stromu
struct Node {
    int value;     // hodnota uzla
    Node *smaller; // uzol 'smaller' a jeho nasledovnici maju hodnotu mensiu ako 'value'
    Node *greater; // uzol 'greater' a jeho nasledovnici maju hodnotu vacsiu ako 'value

    explicit Node(int value = 0, Node *smaller = nullptr, Node *greater = nullptr)
            : value(value), smaller(smaller), greater(greater) {
    }
};

// Binarny vyhladavaci strom
struct BinarySearchTree {
    Node *root; // koren stromu

    explicit BinarySearchTree(Node *root = nullptr)
            : root(root) {
    }
};

// Vynimka oznacujuca, ze uzol so zadanou hodnotou v strome neexistuje
class ValueNotExistsException : public std::exception {
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najmensiu hodnotu v strome.
    V pripade neexistencie tejto hodnoty vyhodi vynimku.

    Riesenie (tejto, aj dalsich uloh) musi vyuzivat vlastnosti binarneho vyhladavacieho stromu.
    Napriklad, pri hladani minima treba prejst len cez potrebne uzly. Netreba prehladavat vsetky uzly (okrem specialnych pripadov).

    VSTUPNY PARAMETER:
        [in] tree - strom, v ktorom funkcia hlada minimum

    NAVRATOVA HODNOTA:
        najmensia hodnota v strome

    VYNIMKA:
        ValueNotExistsException - ak je strom prazdny
*/

int min(const BinarySearchTree *tree) {
    if (tree->root == nullptr) {
        throw ValueNotExistsException();
    }

    Node *current = tree->root;
    while (current->smaller != nullptr) {
        current = current->smaller;
    }

    return current->value;
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati hlbku uzla s hodnotou 'value' v strome 'tree'.
    Hlbka korena je 0.
    Ak hladany uzol v strome nie je, tak funkcia vyhodi vynimku.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Hlbka uzla s hodnotou 'value'.

    VYNIMKA:
        ValueNotExistsException - ak sa uzol s hodnotou 'value' v strome nenachdza
*/

unsigned depth(const BinarySearchTree *tree, int value) {
    if (tree->root == nullptr) {
        throw ValueNotExistsException();
    }
    Node *current = tree->root;
    unsigned depth = 0;
    while (current != nullptr) {
        if (current->value == value) {
            return depth;
        }
        if (current->value > value) {
            current = current->smaller;
        } else {
            current = current->greater;
        }
        depth++;
    }
    throw ValueNotExistsException();
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot uzlov, ktore musi prejst pri hladani uzla s hodnotou 'value'.
    Prva hodnota vystupneho zoznamu je hodnota korena, druha hodnota zoznamu je lavy alebo pravy nasledovnik korena, atd.
    Poslednou hodnotou vo vystupnom zozname je hodnota uzla, na ktorom sa hladanie zastavilo.
    Ak 'tree' obsahuje uzol s hodnotou 'value', tak poslednou hodnotou vystupeho zoznamu je 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol s hodnotou 'value'
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Zoznam hodnot uzlov, ktorych hodnoty musela funkcia pri hladani porovnavat.
        Poradie hodnot vo vystupnom zozname musi zodpovedat poradiu prechadzania uzlov stromu.

    PRIKLADY:
        V prikladoch predpokladajme strom:
                  40
                 /  \
               20    50
              /  \    \
            10   30    60

        1. priklad
            value: 30 -> vystup: (40, 20, 30)
        2. priklad
            value: 20 -> vystup: (40, 20)
        3. priklad
            value: 45 -> vystup: (40, 50)
*/

list<int> path(const BinarySearchTree *tree, int value) noexcept {
    list<int> path;
    Node *current = tree->root;
    while (current != nullptr) {
        path.push_back(current->value);
        if (current->value == value) {
            break;
        }
        if (current->value > value) {
            current = current->smaller;
        } else {
            current = current->greater;
        }
    }
    return path;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu.

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho pocet uzlov funkcia zistuje

    NAVRATOVA HODNOTA:
        pocet uzlov stromu
*/
size_t countNode(const Node *node) noexcept {
    if (node == nullptr) {
        return 0;
    }
    return 1 + countNode(node->smaller) + countNode(node->greater);
}

size_t count(const BinarySearchTree *tree) noexcept {
    return countNode(tree->root);
}


//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot vsetkych uzlov v strome 'tree'.
    Zoznam musi byt usporiadany od najmensieho prvku po najvacsi.

    Usporiadanie dosiahnite vhodnou postupnostou prechadzania uzlov stromu!

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho hodnoty funkcia vrati

    NAVRATOVA HODNOTA:
        hodnoty uzlov, v poradi od najmensej po najvacsiu
*/

list<int> result;

void inOrder(const Node *current) {
    if (current) {
        inOrder(current->smaller);
        result.push_back(current->value);
        inOrder(current->greater);
    }
}


list<int> all(const BinarySearchTree *tree) noexcept {
    inOrder(tree->root);
    list<int> temp = result;
    result.clear();
    return temp;
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu 'tree', ktorych hodnota je vacsia ako 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia pocita pocet uzlov splnajich podmienku
        [in] value - hodnota, podla ktorej sa vyberaju uzly

    NAVRATOVA HODNOTA:
        pocet uzlov s hodnotou vacsou ako 'value'
*/
size_t countGreaterNode(const Node *node, int value) noexcept {
    if (node == nullptr) {
        return 0;
    }
    if (node->value > value) {
        return 1 + countGreaterNode(node->smaller, value) + countGreaterNode(node->greater, value);
    } else {
        return countGreaterNode(node->greater, value);
    }
}

size_t countGreater(const BinarySearchTree *tree, int value) noexcept {
    return countGreaterNode(tree->root, value);
}


//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani vsetky uzly stromu a dealokuje ich.

    Na dealokaciu pouzite operator 'delete'!

    VSTUPNY PARAMETER:
        [in, out] tree - strom, ktoreho uzly funkcia odstrani

    VYSTUPNE PODMIENKY:
        vsetky uzly su dealokovane
        'tree->root' je nulovy smernik
*/

void clearNode(Node *node) noexcept {
    if (node) {
        clearNode(node->smaller);
        clearNode(node->greater);
        delete node;
    }
}

void clear(BinarySearchTree *tree) noexcept {
    clearNode(tree->root);
    tree->root = nullptr;
}


//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia hlada hodnotu 'value' vo vektore 'data'.
    Vrati pocet prvkov v 'data', ktore pri hladni porovnala s 'value'.
    Vektor 'data' obsahuje usporiadane hodnoty.
    Casova narocnost algoritmu je O(log(n)), kde n je pocet prvkov vektora.

    PARAMETRE:
        [in] data - hodnoty usporiadane od najmensieho prvku po najvacsi
        [in] value - hodnota hladana v 'data'

    NAVRATOVA HODNOTA:
        Pocet prvkov 'data', ktore funkcia pri hladani porovnala s 'value'.
        (bez ohladu na to, ci 'data' obsahuje hodnotu 'value').

    VSTUPNA PODMIENKA:
        Hodnoty v 'data' su usporiadane od najmensieho prvku po najvacsi.

    PRIKLADY:
        data = (100, 102, 104, 106, 108, 110, 112), value = 106 -> vystup: 1
        data = (100, 102, 104, 106, 108, 110, 112), value = 110 -> vystup: 2
        data = (100, 102, 104, 106, 108, 110, 112), value = 108 -> vystup: 3
        data = (100, 102, 104, 106, 108, 110), value = 104 -> vystup: 1 alebo 3
        data = (100, 102, 104, 106, 108, 110), value = 107 -> vystup: 3
        data = (100), value = 100 -> vystup: 1
        data = (100), value = 200 -> vystup: 1
        data = (), value = 100 -> vystup: 0
*/

unsigned contains(const vector<int> &data, int value) noexcept {
    size_t left = 0;
    size_t right = data.size();
    unsigned comparisons = 0;

    while (left < right) {
        size_t middle = left + (right - left) / 2;
        comparisons++;

        if (data[middle] == value) {
            return comparisons;
        }
        if (data[middle] < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return comparisons;
}


//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati histogram slov v 'data' (zisti, kolko krat sa ktore slovo nachadza v 'data').

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        histogram slov (pre kazde slovo z 'data' obsahuje pocet jeho vyskytov)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Histogram obsahuje iba slova, ktore sa v 'data' nachadzaju

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> 3, "lietadlo" -> 1, "luk" -> 2, "okno" -> 1}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> 1, "" -> 1}

        vstup: data = ()
        vystup: {}
*/

map<string, size_t> histogram(const vector<string> &data) noexcept {
    map<string, size_t> histogram;
    for (const string &word: data) {
        histogram[word]++;
    }
    return histogram;
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati index slov v 'data' (pre kazde slovo mnozinu indexov jeho vyskytu).

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        index slov (pre kazde slovo z 'data' obsahuje indexy, na ktorych sa slovo v 'data' nachadza)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Index obsahuje zoznamy vyskytov len pre slova, ktore sa nachadzaju v 'data'

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> {0, 3, 4}, "lietadlo" -> {1}, "luk" -> {2, 6}, "okno" -> {5}}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> {0}, "" -> {1}}

        vstup: data = ()
        vystup: {}
*/

map<string, set<size_t>> index(const vector<string> &data) noexcept {
    map<string, set<size_t>> index;
    for (size_t i = 0; i < data.size(); i++) {
        index[data[i]].insert(i);
    }
    return index;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

int main() {
    // Test 1: Tree with multiple nodes, value in the middle
    {
        Node n1(10), n2(20), n3(30), n4(40), n5(50);
        n4.smaller = &n2;
        n4.greater = &n5;
        n2.smaller = &n1;
        n2.greater = &n3;
        BinarySearchTree tree(&n4);
        assert(countGreater(&tree, 25) == 3);
    }

    // Test 2: Tree with multiple nodes, value at the root
    {
        Node n1(10), n2(20), n3(30), n4(40), n5(50);
        n4.smaller = &n2;
        n4.greater = &n5;
        n2.smaller = &n1;
        n2.greater = &n3;
        BinarySearchTree tree(&n4);
        assert(countGreater(&tree, 40) == 1);
    }

    // Test 3: Tree with multiple nodes, value at the leaf
    {
        Node n1(10), n2(20), n3(30), n4(40), n5(50);
        n4.smaller = &n2;
        n4.greater = &n5;
        n2.smaller = &n1;
        n2.greater = &n3;
        BinarySearchTree tree(&n4);
        assert(countGreater(&tree, 10) == 4);
    }

    // Test 4: Tree with multiple nodes, value not in the tree
    {
        Node n1(10), n2(20), n3(30), n4(40), n5(50);
        n4.smaller = &n2;
        n4.greater = &n5;
        n2.smaller = &n1;
        n2.greater = &n3;
        BinarySearchTree tree(&n4);
        assert(countGreater(&tree, 35) == 2);
    }

    // Test 5: Tree with a single node
    {
        Node n1(10);
        BinarySearchTree tree(&n1);
        assert(countGreater(&tree, 5) == 1);
    }

    // Test 6: Tree with a single node, value equal to node value
    {
        Node n1(10);
        BinarySearchTree tree(&n1);
        assert(countGreater(&tree, 10) == 0);
    }

    // Test 7: Empty tree
    {
        BinarySearchTree tree(nullptr);
        assert(countGreater(&tree, 10) == 0);
    }

    // Test 8: Tree with duplicate values
    {
        Node n1(10), n2(20), n3(20), n4(30), n5(40);
        n4.smaller = &n2;
        n4.greater = &n5;
        n2.smaller = &n1;
        n2.greater = &n3;
        BinarySearchTree tree(&n4);
        assert(countGreater(&tree, 20) == 2);
    }

    // Test 9: Tree with all values greater than the given value
    {
        Node n1(20), n2(30), n3(40), n4(50), n5(60);
        n4.smaller = &n2;
        n4.greater = &n5;
        n2.smaller = &n1;
        n2.greater = &n3;
        BinarySearchTree tree(&n4);
        assert(countGreater(&tree, 10) == 5);
    }

    // Test 10: Tree with all values less than the given value
    {
        Node n1(10), n2(20), n3(30), n4(40), n5(50);
        n4.smaller = &n2;
        n4.greater = &n5;
        n2.smaller = &n1;
        n2.greater = &n3;
        BinarySearchTree tree(&n4);
        assert(countGreater(&tree, 60) == 0);
    }

    return 0;
}
