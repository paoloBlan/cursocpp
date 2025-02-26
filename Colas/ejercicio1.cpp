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

int tamanioCola = 0;

void inicializa(struct cola &);

void encola(struct cola &, int);

void dividirColas(struct cola , struct cola &, struct cola &);

void verCola(struct cola );
void vaciaCola(struct cola &);

void menu();

void limpiarPantalla();

int valorCentral(struct cola);

int main()
{
    int opc;
    struct cola data;
    struct cola menoresDe;
    struct cola mayoresDe;
    int cantidad;
    int numero;
    inicializa(data);
    inicializa(menoresDe);
    inicializa(mayoresDe);
    char repetir;
    do
    {
        limpiarPantalla();
        menu();
        cout << "tamanio de la cola: " << tamanioCola << endl;

        cout << "Ingrese una opcion: ";
        cin >> opc;
        cin.ignore();
        limpiarPantalla();

        switch (opc)
        {
        case 1:
            cout << "Ingrese un cantidad de numero: ";
            cin >> cantidad;
            tamanioCola += cantidad;

            for (int i = 0; i < cantidad; i++)
            {
                cout << "Ingrese número " << i + 1 << ": ";
                cin >> numero;
                cin.ignore();
                encola(data, numero);
            }
            vaciaCola(menoresDe);
            vaciaCola(mayoresDe);
            dividirColas(data, menoresDe, mayoresDe);
            break;
       
        case 2:
            
            cout << "cola dividida en menores de: " << valorCentral(data) << endl;
            verCola(menoresDe);
            break;
        case 3:
            cout << "cola dividida en  mayores de: " << valorCentral(data) << endl;
            verCola(mayoresDe);
            break;
        case 4:
            cout << "Saliendo...\n";
            return 0;
        default:
            cout << "Opción incorrecta.\n";
        }

        cout << "\n¿Desea realizar otra acción? (s/n): ";
        cin >> repetir;
        cin.ignore();

    } while (repetir == 's' || repetir == 'S');

    cout << "👋 ¡Hasta pronto!\n";
    return 0;
}

void inicializa(struct cola &q)
{
    q.delante = NULL; // apunta al primer elemento
    q.atras = NULL;   // apunta al ultimo elemento
}

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

void menu()
{
    cout << "=============================\n";
    cout << "   📚 MENÚ COLAS   \n";
    cout << "=============================\n";
    cout << "1. Ingresar elemento a la Cola\n";
    cout << "2. cola menores de  \n";
    cout << "3. cola mayores de \n";
    cout << "4. Salir\n";
    cout << "=============================\n";
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void verCola(struct cola q)
{

    struct nodo *p;
    p = q.delante;
    cout << "Elementos en la cola: ";
    while (p != NULL)
    {
        cout << p->nro << " ";
        p = p->sgte;
    }
    cout << endl;
}

void dividirColas(struct cola data, struct cola &menores, struct cola &mayores)
{

    struct nodo *d;
    d = data.delante;
    
    int centro = valorCentral(data);

    while (d != NULL)
    {
       
        if (d->nro < centro)
        {
            encola(menores, d->nro);
        }
        if (d->nro > centro)
        {
            encola(mayores, d->nro);
        }
        d = d->sgte;
    }
}

int valorCentral(cola q)
{

    if (tamanioCola == 0)
    {
        cout << "La cola está vacía." << endl;
        return -1;
    }

    int indiceCentral = (tamanioCola + 1) / 2;

    nodo *aux = q.delante;
    for (int i = 1; i < indiceCentral; i++)
    {
        aux = aux->sgte;
    }
    return aux->nro;
}

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

