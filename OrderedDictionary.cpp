#include "Iterator.h"
#include "OrderedDictionary.h"
#include <iostream>

#include <exception>
using namespace std;

//θ(cap)
DO::DO(Relatie r, int cap): r{r}, cap{cap} {
    size = 0;
    elems = new Node[cap];

    root = -1;
    firstFree = 0;

    for(int i=0; i<cap-1; i++) {
        elems[i].left = i + 1;
        elems[i].right = i + 1;
    }
    elems[cap-1].left = -1;
    elems[cap-1].right = -1;
}
//θ(1)
int DO::createNode(TCheie c, TValoare v) {
    if(firstFree == -1)
        redim();

    int i=allocate();
    elems[i] = Node{{c, v}, -1, -1};

    return i;
}

//θ(1)
int DO::allocate() {
    int i = firstFree;
    firstFree = elems[firstFree].left;
    return i;
}

//θ(1)
void DO::deallocate(int i) {
    elems[i].left = firstFree;
    firstFree = i;
}

//θ(n)
void DO::redim() {
    Node* newElems = new Node[cap*2];

    for(int i=0; i<cap; i++)
        newElems[i] = elems[i];

    for(int i=cap; i<2*cap-1; i++){
        newElems[i].left = i+1;
        newElems[i].right = i+1;
    }
    elems[2*cap-1].left = -1;
    elems[2*cap-1].right = -1;

    delete[] elems;
    elems = newElems;

    firstFree = cap;
    cap*=2;
}

//O(k)
int DO::min(int p) {
    int k = p;
    while(elems[k].left)
        k = elems[k].left;
    return k;
}

//O(h)
//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
    TValoare oldVal = v;
    bool replaced = false;
    root = adauga_rec(root, c, oldVal, replaced);
    if(replaced)
        return oldVal;
    size += 1;
    return NULL_TVALOARE;
}

//O(h)
int DO::adauga_rec(int p, TCheie c, TValoare& v, bool& replaced) {
    if(p == -1){
        p = createNode(c, v);
    }
    else{
        if(c == elems[p].e.first){
            swap(v, elems[p].e.second);
            replaced = true;
        }
        else if(r(c, elems[p].e.first)){
            elems[p].left = adauga_rec(elems[p].left, c, v, replaced);
        }
        else
            elems[p].right = adauga_rec(elems[p].right, c, v, replaced);
    }
    return p;
}

//O(h)
//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
    return cauta_rec(root, c);
}

//O(h)
TValoare DO::cauta_rec(int p, TCheie c) const {
    if(p == -1)
        return NULL_TVALOARE;
    else if(elems[p].e.first == c)
        return elems[p].e.second;
    else if(r(c, elems[p].e.first))
        return cauta_rec(elems[p].left, c);
    return cauta_rec(elems[p].right, c);
}

//O(h)
//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
    bool deleted = false;
    TValoare oldVal;
    root = sterge_rec(root, c, oldVal, deleted);

    if(!deleted)
        return NULL_TVALOARE;
    size -= 1;
    return oldVal;
}

//O(h)
int DO::sterge_rec(int p, TCheie c, TValoare &v, bool &deleted) {
    if(p == -1)
        return -1;
    if(r(c, elems[p].e.first) && c != elems[p].e.first){
        elems[p].left = sterge_rec(elems[p].left, c, v, deleted);
        return p;
    }
    if (!r(c, elems[p].e.first)) {
        elems[p].right = sterge_rec(elems[p].right, c, v, deleted);
        return p;
    }
    if (elems[p].left != -1 && elems[p].right != -1) {
        int minRight = min(elems[p].right);
        elems[p].e = elems[minRight].e;
        int oldVal = elems[p].e.second;

        elems[p].right = sterge_rec(elems[p].right, elems[p].e.first, v, deleted);
        v = oldVal;
        deleted = true;
        return p;
    }
    else {
        int repl = p;
        if (elems[p].left == -1)
            repl = elems[p].right;
        else
            repl = elems[p].left;


        deleted = true;
        v = elems[p].e.second;

        deallocate(p);
        return repl;
    }
}

//θ(1)
//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
    return size;
}

//θ(1)
//verifica daca dictionarul e vid
bool DO::vid() const {
    return root == -1;
}

//θ(1)
Iterator DO::iterator() const {
    return  Iterator(*this);
}

//θ(1)
DO::~DO() {
    delete[] elems;
}












