#include <iostream>
#include <chrono>
#include "solucion2.h"
using namespace std;

int main(){
    cout << "=========================" << endl;
    
    nodo* raiz = nullptr;
    grilla(&raiz);
    cout << "IMPRIMIENDO..." << endl;
    printLista(raiz);
    
    cout << "=========================" << endl;
    insert(&raiz, "abaco");
    printLista(raiz);
}