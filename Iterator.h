#pragma once

#include "OrderedDictionary.h"
#include <stack>
#include <string>

using std::string;
using std::stack;

class Iterator{
    friend class DO;
private:
    //constructorul primeste o referinta catre Container
    //iteratorul va referi primul element din container
    Iterator(const DO& dictionar);

    //contine o referinta catre containerul pe care il itereaza
    const DO& dict;

    /* aici e reprezentarea specifica a iteratorului */
    int curent;
    stack<int> s;


public:

    //reseteaza pozitia iteratorului la inceputul containerului
    void prim();

    //muta iteratorul in container
    // arunca exceptie daca iteratorul nu e valid
    void urmator();

    void avanseazaKPasi(int k);

    //verifica daca iteratorul e valid (indica un element al containerului)
    bool valid() const;

    //returneaza valoarea elementului din container referit de iterator
    //arunca exceptie daca iteratorul nu e valid
    TElem element() const;
};

