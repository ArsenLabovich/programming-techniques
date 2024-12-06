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
#include <list>
#include <vector>
#include <numeric>
#include <algorithm>
#include <initializer_list>

using namespace std;

double average(const initializer_list<int> &data) {
    if (data.size() == 0) {throw std::invalid_argument("inicializacny zoznam je prazdny");}
    return std::accumulate(data.begin(), data.end(), 0)/ data.size();
}


list<int>::const_iterator findValue(const list<int> &data, int value) noexcept {
    auto it = std::find(data.begin(), data.end(), value);{return it != data.end() ? it: data.cend();}
}

bool isInRange200to400(const int element) noexcept {
    return element >= 200 && element <= 400;
}

list<int>::const_iterator findInRange200to400(const list<int> &data) noexcept {
    auto it = std::find_if(data.begin(), data.end(), isInRange200to400);
    return it != data.end() ? it : data.cend();
}

void replace200to400by5(list<int> &data) noexcept {
    std::replace_if(data.begin(), data.end(), isInRange200to400, 5);
}

int increment(int element) noexcept {
    return element + 1;
}

void incrementAll(list<int> &data) noexcept {
    std::transform(data.begin(), data.end(), data.begin(), increment);
}

int incrementPointsIfItHelps(int points) noexcept {
    switch (points) {
        case 91 :
            return 92;
        case 82:
            return 83;
        case 73:
            return 74;
        case 64:
            return 65;
        case 55:
            return 56;
        default:
            return points;
    }
}
void helpAfterExam1(list<int> &points) noexcept {
    std::transform(points.begin(), points.end(), points.begin(), incrementPointsIfItHelps);
}

void helpAfterExam2(list<int> &points) noexcept {
    for (int &point : points) {point = incrementPointsIfItHelps(point);}
}
list<int> add(const list<int> &data1, const list<int> &data2) noexcept {
    list<int> output;
    std::transform(data1.begin(), data1.end(), data2.begin(), std::back_inserter(output), std::plus<int>());
    return output;
}

void sort1(vector<int> &data) noexcept {
    std::sort(data.begin(), data.end(), std::greater<int>());
}
void sort2(vector<int> &data) noexcept {
    std::sort(data.rbegin(), data.rend());
}
int main() {

    return 0;
}
