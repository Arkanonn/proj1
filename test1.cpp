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

    string palabra = "Banco";
    cout << "La palabra: " << palabra << " ";
    if (Search(raiz, palabra)) cout << "fue encontrada" << endl;
    else cout << "no encontrada" << endl;
    
    cout << "=========================" << endl;
}