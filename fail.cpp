//c++ code 
// beta code university project version 1.0.0
#include <iostream>
#include <chrono>
using namespace std;

const int RANGO = 100000;
const int LARGO = 10;

class listE {
private:
    struct nodeList {
        int val;
        nodeList* next;        
    };
    typedef struct nodeList nodo;
    
    nodo *R;
    int cantNodos;
public:
    // Funciones por defecto
    listE();
    listE(int valor);
    ~listE();

    // Funciones adicionales
    //void push_back(int valor);  por fines practicos este se vera desactivado
    //void sort();
    void print();
    int size();
    void insert(int valor);
    int pop(bool b);
    int linealSearch(int elemento);
    void rellenar(int valor);
    void vaciar();
};

// Crea una lista enlazada vacia
listE::listE(){
    cout << "CREANDO LISTA ENLAZADA VACIA" << endl;
    R = NULL;
    cantNodos = 0;
}
// Crea una lista enlazada con un nodo cuyo valor es el parametro
listE::listE(int valor){
    nodo *p = new nodo;
    p->val = valor;
    p->next = NULL;
    R = p;
    cantNodos = 1;
    
}
// DESTRUCTOR Elimina la lista enlazada nodo a nodo
listE::~listE(){
    nodo *p;
    cout << "Destruyendo..." << endl;
    while(R != nullptr){
        p = R;
        //cout << "eliminando nodo con valor " << p->val << endl;
        R = R->next;
        delete p;
    }
}
// Imprime la lista enlazada
void listE::print(){
    if (R == nullptr){
        cout << "Lista vacia ._." << endl;
        return;
    }
    nodo *p = R;
    while (p != nullptr) {
    //for (int i = 0; i < cantNodos; i++) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}
/*
// agrega un elemento al final de la lista
void listE::push_back(int valor){
    nodo *q = new nodo;
    q->val = valor;
    q->next = NULL;
    
    // si la lista esta vacia
    if (R == nullptr){
        R = q;
        cantNodos++;
        return;
    }
    
    // si no
    nodo *p = R;
    while (p->next != nullptr) p = p->next;
    p->next = q;
    cantNodos++; 
    
}
*/

// devuelve el tamaño de la lista enlazada
int listE::size(){
    return cantNodos;
}

// agrega el elemento a la lista en la prosicion que le corresponde
void listE::insert(int valor){
    nodo *q = new nodo;
    q->next = nullptr;
    q->val = valor;
    if (R == nullptr){
        R = q;
        cantNodos++;
        return;
    }

    nodo *p = R;
    if (q->val < p->val){
        q->next = p;
        R = q;
        cantNodos++;
        return; 
    }

    while (p->next != nullptr && p->next->val < valor) p = p->next;
    if (p->next == nullptr){
        p->next = q;
        cantNodos++;
    }
    else{
        q->next = p->next;
        p->next = q;
        cantNodos++;
    }
}

// elimina el ultimo elemento de la lista (0) o el primero(1) y devuelve el valor eliminado
int listE::pop(bool b){
    // Lista Vacia
    if (R == nullptr){
        cout << "La lista esta vacia ._." << endl;
        return -1;
    }

    // Lista con un solo nodo
    nodo *p = R;
    int valor;
    if (p->next == nullptr){
        valor = p->val;
        delete p;
        R = nullptr;
        cantNodos--;
        return valor;
    }

    if (b){
        valor = p->val;
        R = p->next;
        delete p;
        cantNodos--;
        return valor;
    }
    
    else{
        while (p->next->next != nullptr){
            p = p->next;
        }
        valor = p->next->val;
        delete p->next;
        p->next = NULL;
        cantNodos--;
        return valor;
    }
}

// Busca el elemento de forma lineal y devuelve su posicion, en caso de no encontrarlo retorna -1
int listE::linealSearch(int elemento){
    nodo *p = R;
    for (int i = 0; i < cantNodos; i++){
        if (p->val == elemento) return i;
        p = p->next; 
    }
    return -1;
}
void listE::rellenar(int valor){
    for (int i = 0; i < valor; i++){
        int numero = rand()%RANGO;
        insert(numero);
    }
}
void listE::vaciar(){
    while(R!=nullptr){
        pop(1);
    }
}

int main(){
    cout << "============================================" << endl;

    listE Lista(100);
    Lista.print();
    cout << "Largo de la lista: " << Lista.size() << endl;

    //Lista.push_back(12);
    //Lista.print();
    //cout << "Largo de la lista: " << Lista.size() << endl;
    
    Lista.insert(130);
    Lista.insert(120);
    Lista.insert(11);
    Lista.insert(10);
    Lista.insert(4);
    Lista.print();
    cout << "Largo de la lista: " << Lista.size() << endl;

    cout << "============================================" << endl;
    
    cout << "Valor de la lista eliminado: " << Lista.pop(1) << endl;
    Lista.print();
    cout << "Largo de la lista: " << Lista.size() << endl;

    cout << "============================================" << endl;
    cout << "Vaciar y llenar" << endl;
    
    Lista.vaciar();
    cout << "Largo de la lista: " << Lista.size() << endl;
    Lista.rellenar(LARGO);
    cout << "Largo de la lista: " << Lista.size() << endl;

    cout << "============================================" << endl;

    int numero = -1;

    auto inicio = chrono::high_resolution_clock::now();

    cout << "Buscando el valor " << numero << ", su posicion es: " << Lista.linealSearch(numero) << endl;

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    cout << endl << "El LinealSearch tarda: " << duracion.count() << endl;

    cout << "============================================" << endl;
    
}
