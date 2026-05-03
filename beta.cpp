// c++ code
// Codigo Beta de proyecto de taller version 0.1

#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
using namespace std;

class listaDoble {
private:
    // Creador de la estructura del nodo
    struct nodoDoble {
        string palabra;
        nodoDoble* prev;
        nodoDoble* next;
    }; 
    typedef struct nodoDoble nodo;
    
    // Nodo Raiz
    nodo *R;

    // Contador de nodos 
    int nodoscont;

public:
    // Funciones primarias
    listaDoble();
    listaDoble(string palabra);
    ~listaDoble();

    // Funciones utilizables
    void print();
    string pop_front();
    int size();
    void insert(string palabra);
};

// Constructor de la lista doble que empieza vacia
listaDoble::listaDoble(){
    R = nullptr;
    nodoscont = 0;    
}
// Constructor de la lista doble que empieza con un nodo
listaDoble::listaDoble(string palabra){
    // Creamos el primer nodo de la lista
    nodo *p = new nodo;
    p->palabra = palabra;
    p->prev = nullptr;
    p->next = nullptr;

    // definimos la raiz como ese nodo
    R=p;

    // empezamos el contador en 1
    nodoscont = 1;
}
// Destructor de la lista doble, elimina nodo a nodo
listaDoble::~listaDoble(){
    nodo *p = R;
    cout << "Destruyendo...";
    while (p != nullptr){
        p = R;
        R = R->next;
        delete p;
    }
}
// Retorna la cantidad de nodos en la lista
int listaDoble::size(){
    return nodoscont;
}
// Imprime la palabra contenida en el nodo, llendo de nodo en nodo
void listaDoble::print(){
    cout << "Lista: " << endl;
    if (R == nullptr){
        cout << "Lista Vacia" << endl;
        return;
    }

    nodo *p = R;
    while (p != nullptr){
        cout << p->palabra << "  ";
        p = p->next;
    }
    cout << endl;
}

// Elimina el primer elemento en la lista y redirecciona R al siguiente nodo
// Devuele la palabra del nodo eliminado, si no hay palabra retorna "-1"
string listaDoble::pop_front(){
    // si la lista esta vacia
    if (R == nullptr){
        cout << "No hay elementos a eliminar" << endl;
        return "-1";
    }

    // si hay uno o mas elementos
    nodo *aux;
    aux = R;
    R = R->next;
    string x = aux->palabra;
    delete aux;
    nodoscont--;
    return x;
}

// Inserta la palabra en orden lexicografico respecto del resto;
void listaDoble::insert(string palabra){
    // creamos el nodo y le adjuntamos la palabra
    nodo *nuevo = new nodo;
    nuevo->palabra = palabra;

    // si la lista esta vacia
    if (R == nullptr){
        nuevo->prev = nullptr;
        nuevo->next = nullptr;
        R = nuevo;
        nodoscont++;
        return;
    }

    nodo *p = R;

    // si la lista tiene un nodo y la palabra a insertar es menor a la del nodo
    if (palabra < p->palabra) {
        nuevo->prev = nullptr;
        nuevo->next = p;
        p->prev = nuevo;
        R = nuevo;
        nodoscont++;
        return;
    }
    
    // ver si la palabra esta al medio o al final
    while (p->next != nullptr && palabra > p->next->palabra) p = p->next;

    // si esta al final
    if (p->next == nullptr){
        p->next = nuevo;
        nuevo->prev = p;
        nuevo->next = nullptr;
        nodoscont++;
        return;
    }

    // si esta entre medio
    nuevo->next = p->next;
    p->next->prev = nuevo;
    nuevo->prev = p;
    p->next = nuevo;
    nodoscont++;
    return;
} 
int main(){
    // Prueba de concepto
    cout << "|==============Prueba 1==================|" << endl;
    
    listaDoble lista("Hola");
    lista.print();
    cout << "Largo de la lista: " << lista.size() << endl;

    lista.pop_front();
    lista.print();
    cout << "Largo de la lista: " << lista.size() << endl;

    lista.insert("Hola");
    lista.print();
    cout << "Largo de la lista: " << lista.size() << endl;

    lista.insert("Aloja");
    lista.print();
    cout << "Largo de la lista: " << lista.size() << endl;
    
    lista.insert("Zeta");
    lista.print();
    cout << "Largo de la lista: " << lista.size() << endl;    
    
    lista.insert("Bebelin");
    lista.print();
    cout << "Largo de la lista: " << lista.size() << endl;

    for (int i = 0; i < 4; i++) lista.pop_front();
    lista.print();
    cout << "Largo de la lista: " << lista.size() << endl;

    cout << "|=================Fin 1===============|" << endl;

    // Prueba de lectura e insertado
    cout << "|=================Prueba 2===============|" << endl;

    // seleccionamos el diccionario
    ifstream archivo("D1.txt");
    if (!archivo){
        cout << "No se pudo encontrar el archivo" << endl;
        return 0;
    }

    
    // añadimos las palabras a la lista enlazada y medimos cuanto tarda
    string palabra;

    auto inicio = chrono::high_resolution_clock::now();
    while (getline(archivo, palabra)){
        lista.insert(palabra);
    }
    auto fin = chrono::high_resolution_clock::now();

    archivo.close();
    chrono::duration<double> duracion = fin - inicio;

    // vemos cuanta memoria ocupa
    double RamTotal = sizeof(listaDoble) * lista.size();
    
    // lista.print();
    cout << "Largo de la lista: " << lista.size() << endl;
    cout << "El programa tardo "<< duracion.count() << " segundos en completar la lista con los valores del diccionario." << endl;
    cout << "Y esta ocupando "<< RamTotal/1000000 << " megabytes de memoria ram." << endl;

    cout << "|===============Fin 2=================|" << endl;
    // cout << "|================================|" << endl;
}