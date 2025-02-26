#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <stdio.h>

#define MAX 50

using namespace std;

struct Nodo {
    int cod;
    string nom;
    int ed;
    Nodo* sgte;
};

typedef Nodo* tlista;

void insertar(tlista&, int, string, int);
void mostrar(tlista);
void ordenar(tlista&);
void mostrarA(tlista);
void mostrarB(tlista);
void mostrarC(tlista);

void insertar(tlista& lista, int cod, string nom, int ed) {
    tlista t;
    tlista q = new Nodo;
    q->cod = cod;
    q->nom = nom;
    q->ed = ed;
    q->sgte = nullptr;

    if (lista == nullptr)
        lista = q;
    else {
        t = lista;
        while (t->sgte != nullptr)
            t = t->sgte;
        t->sgte = q;
    }
}

void mostrar(tlista lista) {
    int i = 1;
    while (lista != nullptr) {
        cout << "Código [" << i << "]: " << lista->cod << " ";
        cout << "Nombre [" << i << "]: " << lista->nom << " ";
        cout << "Edad [" << i << "]: " << lista->ed << endl;
        lista = lista->sgte;
        i++;
    }
}

void ordenar(tlista& lista) {
    if (lista == nullptr) return;
    bool cambiado;
    do {
        cambiado = false;
        tlista q = lista;
        while (q->sgte != nullptr) {
            if (q->ed > q->sgte->ed) {
                swap(q->cod, q->sgte->cod);
                swap(q->nom, q->sgte->nom);
                swap(q->ed, q->sgte->ed);
                cambiado = true;
            }
            q = q->sgte;
        }
    } while (cambiado);
}

int main() {
    tlista lista = nullptr;
    int cod, ed, n, o;
    string nom;
    char r;

    do {
        cout << "1-. Insertar\n";
        cout << "2-. Mostrar\n";
        cout << "3-. Ordenar\n";
        cout << "4-. Salir\n";
        cout << "\nIngrese una opción: ";
        cin >> o;
        cin.ignore();

        switch (o) {
            case 1:
                cout << "Ingrese la cantidad de datos: ";
                cin >> n;
                cin.ignore();
                for (int i = 0; i < n; i++) {
                    cout << "Código [" << i + 1 << "]: ";
                    cin >> cod;
                    cin.ignore();
                    cout << "Nombre [" << i + 1 << "]: ";
                    getline(cin, nom);
                    cout << "Edad [" << i + 1 << "]: ";
                    cin >> ed;
                    cin.ignore();
                    insertar(lista, cod, nom, ed);
                }
                break;

            case 2:
                cout << "\nLos datos son:\n";
                mostrar(lista);
                //cin.ignore();
                break;

            case 3:
                cout << "La lista ordenada es:\n";
                ordenar(lista);
                mostrar(lista);
                //cin.ignore();
                break;

            case 4:
                return 0;
        }

        cout << "¿Desea continuar? (s/n): ";
        cin >> r;
        cin.ignore();
        system("clear");

    } while (r == 's' || r == 'S');

    return 0;
}
