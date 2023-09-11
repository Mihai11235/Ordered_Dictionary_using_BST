#include "Iterator.h"
#include "OrderedDictionary.h"

using namespace std;

//O(h)
Iterator::Iterator(const DO& d) : dict(d){
    curent = dict.root;
    prim();
}

//O(h)
void Iterator::prim(){
    while(!s.empty())
        s.pop();
    curent = dict.root;
    while(curent != -1){
        s.push(curent);
        curent = dict.elems[curent].left;
    }
    if(!s.empty()){
        curent = s.top();
    }
}

//O(h)
void Iterator::urmator(){
    curent = s.top(); s.pop();

    if(dict.elems[curent].right){
        curent = dict.elems[curent].right;
        while(curent != -1){
            s.push(curent);
            curent = dict.elems[curent].left;
        }
    }
    if(!s.empty())
        curent = s.top();
    else
        curent = -1;
}

//θ(1)
bool Iterator::valid() const{
    return curent != -1;
}

//θ(1)
TElem Iterator::element() const{
    return dict.elems[curent].e;
}

//O(k*h)
void Iterator::avanseazaKPasi(int k) {
    if(k<0)
        throw string("k invalid!");

    for(int i=0; i<k; i++){
        if(curent == -1)
            throw string("Iteratorul a devenit invalid!");
        urmator();
    }
}


