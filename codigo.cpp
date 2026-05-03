#include <iostream>
#include <chrono>

//using namespace chrono;
using namespace std;

# define max 100 

struct nodeList {
    int val;
    nodeList* next;
};
typedef struct nodeList nodo;

void printNList(nodo *l){
    nodo *p = l;
    while (p != nullptr){
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}
void agregarList(nodo **l, int x){
    nodo *q = new nodo;
    q->val = x;
    q->next = NULL;
    
    if (*l == nullptr){
        *l = q;
        return;
    }

    nodo *p = *l;
    while (p->next != nullptr) {
        p = p->next;
    }

    p->next = q;
}

void rellenarListRand(nodo **l, int n){
    for (int i = 0; i < n; i++){
        int valor = rand()%max;
        agregarList(l, valor);
    }
}
void popList(nodo **l){

    // Lista Vacia
    if (*l == nullptr){
        cout << "La lista esta vacia ._." << endl;
        return;
    }

    // Lista con un solo nodo
    nodo *p = *l;
    if (p->next == nullptr){
        delete p;
        *l = nullptr;
        return;
    }

    *l = p->next;
    delete p;
    return;
    //// Lista con 2 o mas nodos
    //while (p->next->next != nullptr){
    //    p = p->next;
    //}
    //delete p->next;
    //p->next = NULL;
    //return;
}
void vaciarList(nodo **l){
    while (*l != NULL){
        popList(l);
    }
}
void InsertionL(nodo **l, int x){
    nodo *q = new nodo;
    q->next = nullptr;
    q->val = x;
    if (*l == nullptr){
        *l = q;
        return;
    }

    nodo *p = *l;
    if (q->val < p->val){
        q->next = p;
        *l = q;
        return; 
    }

    while (p->next != nullptr && p->next->val < x) p = p->next;
    if (p->next == nullptr){
        p->next = q;
    }
    else{
        q->next = p->next;
        p->next = q;
    }

}

int main(){
    cout << "|=======================Empezando programa============================|" << endl;
    cout << "|==== Etapa 1 ====|" << endl;

    nodo *R = nullptr;
    rellenarListRand(&R, 5);
    printNList(R);
    popList(&R);
    printNList(R);
    vaciarList(&R);
    printNList(R);

    cout << "|=====================================================================|" << endl;
    cout << "|==== Etapa 2 ====|" << endl;
    nodo *s = NULL;
    InsertionL(&s, 6);
    printNList(s);
    InsertionL(&s, 4);
    printNList(s);
    InsertionL(&s, 5);
    printNList(s);
    InsertionL(&s, 10);
    printNList(s);
    InsertionL(&s, 11);
    printNList(s);
    InsertionL(&s, 7);
    printNList(s);
    vaciarList(&s);

    cout << "Calculemos el tiempo que tarda en insertar un elemento random" << endl;
    auto inicio = chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++){
        InsertionL(&s, rand()%100000);
    }
    
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    cout << "tiempo Utilizado en seg: " << duracion.count() << endl;

    
    cout << "Calculemos el tiempo que tarda en vaciar la lista" << endl;

    auto inicio1 = chrono::high_resolution_clock::now();
    vaciarList(&s);    
    auto fin1 = chrono::high_resolution_clock::now();

    chrono::duration<double> duracion1 = fin1 - inicio1;
    cout << "tiempo Utilizado en seg: " << duracion1.count() << endl;

    printNList(s);

    
    return 0;
}