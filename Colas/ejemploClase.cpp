#include <iostream>

using namespace std;

struct nodo
{
    int nro;
    struct nodo *sgte;
};



struct cola
{
    struct nodo *delante; // apunta al primero
    struct nodo *atras;   // apunta al ultimo
};

void inicializa(struct cola &);
void encola(struct cola &, int);
void verCola(struct cola);
void vaciaCola(struct cola &);
int desencola(struct cola &);

int main()
{
    int opc;
    struct cola q;
    int n;
    inicializa(q);
    do
    {
        cout << endl
             << "******MENU********" << endl;
        cout << "[1] Ingresa Elementos" << endl;
        cout << "[2] Retirar Elementos" << endl;
        cout << "[3] Visualiza cola" << endl;
        cout << "[4] Vaciar Cola" << endl;
        cout << "[5] Salir" << endl;
        cout << "Ingrese Opcion";
        cin >> opc;
        switch (opc)
        {
        case 1:
            cout << "Ingresar Elementos:";
            cin >> n;
            encola(q, n);
            break;
        case 2:
            if (q.delante != NULL)
            {
                n = desencola(q);
                cout << endl
                     << "Desencola elementos" << n << endl;
            }
            else
                cout << endl
                     << "No hay elementos en la cola" << endl;
            break;
        case 3:
            cout << endl
                 << "Elementos de la cola:" << endl;
            verCola(q);
            break;
        case 4:
            vaciaCola(q);
            break;
        }
    } while (opc != 5);
    return 0;
}

// funciones---------------------------
void inicializa(struct cola &q)
{
    q.delante = NULL; // apunta al primer elemento
    q.atras = NULL;   // apunta al ultimo elemento
}

// INGRESA ELEMENTOS EN LA COLA
void encola(struct cola &q, int n)
{
    struct nodo *p;
    p = new (struct nodo);
    p->nro = n;
    p->sgte = NULL;
    if (q.delante == NULL)
        q.delante = p; // ingresa el primer elemento
    else
        (q.atras)->sgte = p; // si no apunta a un nuevo nodo
    q.atras = p;             // la cola apunta al ultimo elemento recientemente ingresado
}

// ELIMINA ELEMENTOS EN LA COLA

int desencola(struct cola &q)
{
    struct nodo *p;
    p = q.delante; // apunta al primer elemento
    int n = p->nro;
    q.delante = (q.delante)->sgte;
    delete (p);

    return n;
}

// BORRA LOS DATOS DE LA COLA
void vaciaCola(struct cola &q)
{
    struct nodo *p, *r;
    p = q.delante; // apunta al primer elemento
    while (p != NULL)
    {
        r = p;
        p = p->sgte;
        delete (r);
    }
    q.delante = NULL;
    q.atras = NULL;
}

void verCola(struct cola q)
{
    struct nodo *p;
    p = q.delante; // apunta al primer elementos
    while (p != NULL)
    {
        cout << p->nro << endl;
        p = p->sgte;
    }
}
