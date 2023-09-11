#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);


class DO {
    friend class Iterator;
private:
    class Node{
    public:
        TElem e;
        int left;
        int right;

        Node() = default;
        Node(TElem e, int left, int right):e{e},left{left},right{right}{};
    };

    Relatie r;
    int cap;
    int size;
    Node* elems;
    int root;
    int firstFree;


    void redim();
    int createNode(TCheie c, TValoare v);
    int allocate();
    void deallocate(int i);

    int adauga_rec(int p, TCheie c, TValoare& v, bool& replaced);
    TValoare cauta_rec(int p, TCheie c) const;
    int sterge_rec(int p, TCheie c, TValoare& v, bool& deleted);
    int min(int p);
public:

    // constructorul implicit al dictionarului
    DO(Relatie r, int cap = 200000);


    // adauga o pereche (cheie, valoare) in dictionar
    //daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
    // daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
    TValoare adauga(TCheie c, TValoare v);

    //cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
    TValoare cauta(TCheie c) const;


    //sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
    TValoare sterge(TCheie c);

    //returneaza numarul de perechi (cheie, valoare) din dictionar
    int dim() const;

    //verifica daca dictionarul e vid
    bool vid() const;

    // se returneaza iterator pe dictionar
    // iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
    Iterator iterator() const;


    // destructorul dictionarului
    ~DO();

};
