#include <iostream>
#include <chrono>
#include "solucion2.h"
using namespace std;

int main(){
    cout << "=========================" << endl;
    
    nodo* raiz = nullptr;
    grilla(&raiz, "prueba.txt");
    cout << "IMPRIMIENDO..." << endl;
    printLista(raiz);
    
    cout << "=========================" << endl;
    insertarNodo(&raiz, "A");
    printLista(raiz);
    cout << raiz->key << endl;
}