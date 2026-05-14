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
    
    removeL(&raiz, "arbol");
    printLista(raiz);

    cout << "=========================" << endl;
    string palabra = "Izquierda";
    if (removeL(&raiz, palabra)) cout << "Se elimino: " << palabra << endl;
    else cout << "No se elimino: " << palabra << endl; 
    printLista(raiz);
}