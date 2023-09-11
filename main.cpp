#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "OrderedDictionary.h"
#include "Iterator.h"

bool cresc1(TCheie c1, TCheie c2) {
    if (c1 <= c2) {
        return true;
    } else {
        return false;
    }
}
using namespace std;
int main(){
   testAll();
   testAllExtins();
    std::cout<<"Finished Tests!"<<std::endl;

    DO d{cresc1};

    d.adauga(4,4);
    d.adauga(1,4);
    d.adauga(6,4);
    d.adauga(2,4);
    d.adauga(5,4);
    d.adauga(9,4);
    d.adauga(7,4);
    d.adauga(10,4);
    d.adauga(8,4);
    d.adauga(11,4);
    d.adauga(15,4);
    d.adauga(12,4);
    d.adauga(13,4);
    d.adauga(14,4);
    d.adauga(3,4);

    try {
        Iterator i = d.iterator();
        i.urmator();
        for (; i.valid(); i.avanseazaKPasi(3))
            cout << i.element().first << ' ';
    }
    catch(const string& s){
        cout << '\n' << s << '\n';
    }
}
