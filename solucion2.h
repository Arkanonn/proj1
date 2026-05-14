// c++ code
// en el archivo donde se hara la grulla hay que hacer #include "beta_2.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

# define K 2
int inserciones = 0;
int niveles = 0;
int cantN = 0;
// estructura de los nodos a utilizar
struct nodoDoble{
    string key;
    nodoDoble* up = nullptr; // nodo superior
    nodoDoble* right = nullptr; // nodo a la derecha 
}; 
typedef struct nodoDoble nodo;

void grilla(nodo** R, string referencia){
    // Se abre el diccionario uno
    ifstream dicc1;
    dicc1.open(referencia);
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
            cantN++;
            
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
                cantN++;
                
            }
            p = p->right;
            contador++;
        }
        // El nivel tiene n nodos
        n = (n + K - 1)/K;
        niveles++;
    }

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

// Busca en una grilla
bool Search(nodo* R, string valor){
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
    if (R->right == nullptr) return Search(R->up, valor);
    nodo* p = R;

    while (p->right->right != nullptr && valor > p->right->key) p = p->right;

    if (p->key != valor && p->right == nullptr) return Search(p->up, valor);
    if (p->right != nullptr && p->right->key > valor) return Search(p->up, valor);
    if (p->right != nullptr && p->right->key < valor) return Search(p->right->up, valor);
    if (p->right != nullptr && p->right->key == valor) return true;
    return false;
}

void insertarNodo(nodo **R, string nueva_key){
    //cout << "Insertando nodo.." << endl;
    nodo* q = new nodo;
    q->key = nueva_key;
    // si la lista esta vacia
    if (*R == nullptr){
        *R = q;
        inserciones++;
        cantN++;
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
            cantN++;
            inserciones++;
        }
        return;
    }
    /*
    /// si nueva key es igual a la primera palabra
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
    */
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
        cantN++;
        return;
    }
      
}

// Si el elemento x esta en la lista lo remueve y retorna true
// si no retorna false
// si el x esta en la raiz entonces no se eliminara y retorna false
bool removeL(nodo** R, string valor){
    // si R esta vacio
    if (R == nullptr || *R == nullptr){
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
    
    // si la derecha es mayor que el valor, sube desde p
    if ( p->right->key > valor) {
        return removeL(&(p->up), valor);
    }
    
    // si la derecha es menor al valor, sube desde la derecha
    if (p->right->key < valor) {
        return removeL(&(p->right->up), valor);
    }
    
    // si la derecha es el valor que busco
    if (p->right->key == valor) {
        nodo* aux = p->right;
        removeL(&(p->up), valor);
        p->right = aux->right;
        delete aux;
        cantN--;
        return true;
    }
    return false;   
}