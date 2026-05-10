#include <iostream>
#include <fstream>
#include <chrono>
#include "beta_2.h"

int main(){
    nodo* principal = nullptr;

    ifstream archivo("D1.txt");

    if (!archivo) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    string linea;
    auto inicio = chrono::high_resolution_clock::now();
    while(getline(archivo, linea)){
        push_back(&principal, linea);
    }
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;
    cout << endl;
    printLista(principal);
    cout << "El proceso de insertar todo duro: " << duracion.count() << " segundos" <<  endl;

    archivo.close();
    return 0;
}