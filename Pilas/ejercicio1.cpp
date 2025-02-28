/*
    1.	Crear un programa que busque un elemento en una pila 
    y reporte la posición en la que se encuentra.
*/
#include <iostream>

using namespace std;

struct nodo
{
    int nro;
    struct nodo *sgte;
};

typedef nodo *ptrPila;

void push(ptrPila &, int);
int buscarEnPila(ptrPila, int);
void imprimir(ptrPila);
void menu();
void limpiarPantalla();

int main()
{
    ptrPila p = NULL;
    char repetir;
    int opc;
    int n;

    do
    {
        limpiarPantalla();
        menu();
        cout << "Ingrese una opcion: ";
        cin >> opc;
        cin.ignore();
        limpiarPantalla();

        switch (opc)
        {
        case 1:
            cout << "Apilar Valor: ";
            cin >> n;
            push(p, n);
            break;

        case 2:
            cout << "Ingrese el valor a buscar: ";
            cin >> n;
            int posicion;
            posicion = buscarEnPila(p, n);
            imprimir(p);
            if (posicion != -1)
                cout << "Elemento encontrado en la posición: " << posicion << endl;
            else
                cout << "Elemento no encontrado en la pila" << endl;
            break;
        }
        cout << "\n¿Desea realizar otra acción? (s/n): ";
        cin >> repetir;
        cin.ignore();
    } while (repetir == 's' || repetir == 'S');

    return 0;
}

void push(ptrPila &p, int n)
{
    ptrPila q = new nodo;
    q->nro = n;
    q->sgte = p;
    p = q;
}

int buscarEnPila(ptrPila p, int valor)
{
    int posicion = 1;
    while (p != NULL)
    {
        if (p->nro == valor)
        {
            return posicion;
        }
        p = p->sgte;
        posicion++;
    }
    return -1;
}

void menu()
{
    cout << "=============================\n";
    cout << "   📚 MENÚ PILAS   \n";
    cout << "=============================\n";
    cout << "1. Apilar\n";
    cout << "2. Buscar elemento\n";
    cout << "3. Salir\n";
    cout << "=============================\n";
}

// Limpiar la pantalla según el sistema operativo
void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void imprimir(ptrPila p)
{
    while (p != NULL)
    {
        cout << p->nro << endl;
        p = p->sgte;
    }
    cout << endl;
}
