// c++ code
// en el archivo donde se hara la grulla hay que hacer #include "beta_2.h"
#include <iostream>
#include <string>
using namespace std;

// estructura de los nodos a utilizar
struct nodoDoble{
    string palabra;
    nodoDoble* up; // nodo superior
    nodoDoble* right; // nodo a la derecha
}; 
typedef struct nodoDoble nodo;

// Agrega un elemento al final de la lista
void push_back(nodo** R, string dato){
    // crea el nodo y le asigna sus respectivos valores
    nodo* nuevo = new nodo;
    nuevo->palabra = dato;
    nuevo->up = nullptr;
    nuevo->right = nullptr;
    
    // si la lista esta vacia el nuevo nodo sera la raiz
    if (*R == nullptr){
        *R = nuevo;
        return;
    } 
    
    // recorre hasta el final nodo final
    nodo *p = *R;
    while (p->right != nullptr) p = p->right;

    // inserta el nuevo nodo a su derecha
    p->right = nuevo;    
}

// imprime la lista completa
void printLista(nodo *R){
    nodo *p = R;
    int cont = 0;
    while (p != nullptr) {
        cout << p->palabra << "  ";
        p = p->right;
        cont++;
    }
    cout << endl;
    cout << "y tiene: " << cont << " nodos.";
    cout << endl;
}

// buscara el "dato" en la lista R 
// Solo funcionara bien si el dato a buscar es mayor al primer elemento de la lista
bool Search(nodo *R, string dato){
    if (dato < R->palabra){
        return false;
    }
    nodo *p = R;
    while (p != nullptr && p->palabra != dato) p = p->right;
    
    if (p == nullptr) return false;
    
    return true;
}
