#include <iostream>


using namespace std;

struct nodo
{
    int nro;
    struct nodo *sgte;
};

typedef nodo *ptrPila;

void imprimir(ptrPila);
void eliminaPila(ptrPila &);
void push(ptrPila &, int);
int pop(ptrPila &);

int main()
{
    ptrPila p = NULL;
    int opc, n;
    do
    {
        system("cls");
        cout << "1 Apilar" << endl;
        cout << "2 Desapilar" << endl;
        cout << "3 Ver pila" << endl;
        cout << "4 Eliminar Pila" << endl;
        cout << "5 Salir" << endl;
        cout << "Ingrese una opcion";
        cin >> opc;
        switch (opc)
        {
        case 1:
            cout << "Apilar Valor";
            cin >> n;
            push(p, n);
            break;

        case 2:
            if (p != NULL)
            {
                cout << "Valor Eliminado";
                n = pop(p);
                cout << n << endl;
            }
            else
                cout << "Pila vacia" << endl;
            cin.ignore();
            break;
        case 3:
            cout << "Contenido de la pila" << endl;
            imprimir(p);
            cin.ignore();
            break;
        case 4:
            eliminaPila(p);
            cout << "Pila destruida" << endl;
            cin.ignore();
            break;
        }
    } while (opc != 5);
    return 0;
}
// Función para insertar elementos en la pila
void push(ptrPila &p, int n)
{
    ptrPila q = new (struct nodo);
    q->nro = n;
    q->sgte = p;
    p = q;
}
// Función para eliminar elementos en la pila
int pop(ptrPila &p)
{
    int n = p->nro;

    ptrPila q = p;
    p = p->sgte;
    delete (q);
    return n;
}
// Función para eliminar la pila
void eliminaPila(ptrPila &p)
{
    ptrPila q;
    while (p != NULL)
    {
        q = p;
        p = p->sgte;
        delete (q);
    }
}
// Función para visualizar elementos en la pila
void imprimir(ptrPila p)
{
    while (p != NULL)
    {
        cout << p->nro << endl;
        p = p->sgte;
    }
    cout << endl;
}
