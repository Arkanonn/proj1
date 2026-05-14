// c++ code
// en el archivo donde se hara la grulla hay que hacer #include "beta_2.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

# define K 4
int inserciones = 0;
int niveles = 0;
// estructura de los nodos a utilizar
struct nodoDoble{
    string key;
    nodoDoble* up = nullptr; // nodo superior
    nodoDoble* right = nullptr; // nodo a la derecha 
}; 
typedef struct nodoDoble nodo;

void grilla(nodo** R){
    // Se abre el diccionario uno
    ifstream dicc1;
    dicc1.open("prueba.txt");
    long count = 0;
    
    if (dicc1.is_open()){
        // Se inserta cada palabra a un nodo del primer nivel
        string linea;
        nodo* s = nullptr;
        while (getline(dicc1, linea)){
            nodo* q = new nodo;
            q->key = linea;
            if (*R == nullptr)
                *R =  q;
            else
                s->right = q;
            s = q;
            count++;
            
        }
        niveles++;
    }
    dicc1.close();
    
    // Seguimos para i niveles
    long n = count;
    
    while(n > K){
        int contador = 0;

        nodo* p = *R;

        nodo* s = nullptr;
        while(p != nullptr){
            if (contador % K == 0){
                nodo* q = new nodo;
                q->key = p->key;
                if (s == nullptr)
                    *R = q;
                else
                    s->right = q;
                q->up = p;
                s = q;
                
            }
            p = p->right;
            contador++;
        }
        // El nivel tiene n nodos
        n = (n + K - 1)/K;
        niveles++;
    }

}

// Agrega un elemento al final de la lista
void push_back(nodo** R, string dato){
    // crea el nodo y le asigna sus respectivos valores
    nodo* nuevo = new nodo;
    nuevo->key = dato;
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
    if (R == nullptr) return;
    printLista(R->up);
    nodo *p = R;
    int cont = 0;
    while (p != nullptr) {
        cout << p->key << " -> ";
        p = p->right;
        cont++;
    }
    cout << endl;
    //cout << "y tiene: " << cont << " nodos.";
    //cout << endl;
}

// buscara el "dato" en la lista R 
// Solo funcionara bien si el dato a buscar es mayor al primer elemento de la lista
bool Search(nodo *R, string dato){
    if (dato < R->key){
        return false;
    }
    nodo *p = R;
    while (p != nullptr && p->key != dato) p = p->right;
    
    if (p == nullptr) return false;
    
    return true;
}

// Busca en una grilla
bool superSearch(nodo* R, string valor){
    // si la lista esta vacia
    if (R == nullptr){
        return false;
    }
    // si el valor es menor a la primera palabra
    if (R->key > valor){
        return false;
    }

    // si el valor es igual a la primera palabra return true;
    if (R->key == valor){
        return true;
    }
    
    // si a la derecha del primer nodo es nulo
    if (R->right == nullptr) return superSearch(R->up, valor);
    nodo* p = R;

    while (p->right->right != nullptr && valor > p->right->key) p = p->right;

    if (p->key != valor && p->right == nullptr) return superSearch(p->up, valor);
    if (p->right != nullptr && p->right->key > valor) return superSearch(p->up, valor);
    if (p->right != nullptr && p->right->key < valor) return superSearch(p->right->up, valor);
    if (p->right != nullptr && p->right->key == valor) return true;
    return false;
}

void insertarNodo(nodo **R, string nueva_key){
    cout << "Insertando nodo.." << endl;
    nodo* q = new nodo;
    q->key = nueva_key;
    // si la lista esta vacia
    if (*R == nullptr){
        *R = q;
        inserciones++;
        return;
    }
    
    // si nueva key es menor a la primera palabra
    if ((*R)->key > nueva_key){
        nodo* p = *R;
        for (int i=1;i<=niveles;i++){
            if (i == 1){
                q->right = p;
                *R = q;
            }
            else{
                nodo* r = new nodo;
                r->key = nueva_key;
                r->right = p;
                q->up = r;
                q = q->up;
            }
            p = p->up;
            inserciones++;
        }
        return;
    }
    
    // si nueva key es igual a la primera palabra
    if ((*R)->key == nueva_key){
        cout << "if es igual" << endl;
        nodo *r = *R;
        while (r->up != nullptr)
            r = r->up;
        q->right = r->right;
        r->right = q;
        inserciones++;
        return;
    }

    nodo* p = *R;
    while (true){
        // Recorre hacia la derecha
        while ((p->right) != nullptr && (p->right)->key < nueva_key)   
            p = p->right;

        // Si puede recorre hacia arriba
        if (p->up != nullptr)
            p = p->up;
        
        // Else: No se puede subir más
        else break;
    }
    
    // Insertando nodo
    if (p->key <= nueva_key){
        q->right = p->right;
        p->right = q;
        inserciones++;
        return;
    }
    
}
    return false;   
}

// Si el elemento x esta en la lista lo remueve y retorna true
// si no retorna false
// si el x esta en la raiz entonces no se eliminara y retorna false
bool removeL(nodo** R, string valor){
    // si R esta vacio
    if (*R == nullptr){
        return false;
    }

    // si el valor a eliminar es menor al primero
    if (valor < (*R)->key){
        return false;
    }

    // si el valor es igual a la primera palabra return false;
    if ((*R)->key == valor){
        return false;
    }

    // si a la derecha del primer nodo es nulo
    if ((*R)->right == nullptr) {
        return removeL(&((*R)->up), valor);
    }
    nodo* p = *R;
    
    // deja p en el nodo menor al nodo del valor si es que esta o no
    while (p->right->right != nullptr && valor > p->right->key) p = p->right;

    // si puntero derecho es nulo sube
    if (p->key != valor && p->right == nullptr) {
        return removeL(&(p->up), valor);
    }
    
    // si el valor del puntero derecho es mayor al valor sube arriba del menor
    if ( p->right->key > valor) {
        return removeL(&(p->up), valor);
    }
    
    if (p->right->key < valor) {
        return removeL(&(p->right->up), valor);
    }
    
    
    if (p->right->key == valor) {
        nodo* aux = p->right;
        removeL(&(p->up), valor);
        p->right = aux->right;
        delete aux;
        return true;
    }
    return false;   
}
