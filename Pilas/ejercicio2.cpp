#include <iostream>

using namespace std;

struct nodo
{
    string nombre;
    int edad;
    struct nodo *sgte;
};

typedef nodo *ptrPila;

void push(ptrPila &, string, int);
void buscarElementoCentral(ptrPila);

int buscarEnPila(ptrPila, string);

void imprimir(ptrPila);
void menu();
void limpiarPantalla();

int main()
{
    ptrPila p = NULL;
    ptrPila mayores = NULL;
    char repetir;
    int opc;
    int cantidad;
    string nombre;
    int posicion;
    int edad;

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
            cout << "ingrese cantidad de personas: ";
            cin >> cantidad;

            for (int i = 0; i < cantidad; i++)
            {
                cout << "Nombre [" << i + 1 << "]: ";
                cin >> nombre;
                cout << "Edad [" << i + 1 << "]: ";
                cin >> edad;
                if (edad >= 18)
                {
                    push(mayores, nombre, edad);
                }
                push(p, nombre, edad);
            }

            break;

        case 2:
            buscarElementoCentral(p);
            break;

        case 3:
            imprimir(mayores);
            break;
        case 4:
            cout << "ingrese nombre a buscar: ";
            cin >> nombre;
            posicion = buscarEnPila(p, nombre);
            if (posicion != -1)
            {
                cout << "El nombre se encuentra en la posición: " << posicion + 1 << endl;
            }
            else
            {
                cout << "elemento no encontrado\n";
            }
            break;
        case 5:
            cout << "Saliendo del programa...\n";
            return 0;
        default:
            cout << "Opción invalida.\n";
            break;
     
        }
        cout << "\n¿Desea realizar otra acción? (s/n): ";
        cin >> repetir;
        cin.ignore();
    } while (repetir == 's' || repetir == 'S');

    return 0;
}

void push(ptrPila &p, string nombre, int edad)
{
    ptrPila q = new nodo;
    q->nombre = nombre;
    q->edad = edad;
    q->sgte = p;
    p = q;
}

void menu()
{
    cout << "=============================\n";
    cout << "   📚 MENÚ PILAS   \n";
    cout << "=============================\n";
    cout << "1. insertar personas\n";
    cout << "2. elemento central\n";
    cout << "3. mayores de edad\n";
    cout << "4. buscar elemento pila\n";
    cout << "5. Salir\n";
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
        cout << "Nombre: " << p->nombre << "----- edad: " << p->edad << endl;
        p = p->sgte;
    }
    cout << endl;
}

void buscarElementoCentral(ptrPila p)
{

    int contador = 1;
    ptrPila pAux = p;
    while (pAux != NULL)
    {
        contador++;
        pAux = pAux->sgte;
    }
    if (contador % 2 == 0 || contador == 1)
    {
        cout << "ingrese mas elementos a la pila" << endl;
        return;
    }
    int posicionCentral = (contador + 1) / 2;
    pAux = p;
    for (int i = 0; i < posicionCentral; i++)
    {
        pAux = pAux->sgte;
    }
    cout << "El elemento central es: Nombre: " << pAux->nombre << "----- edad: " << pAux->edad << endl;
}

int buscarEnPila(ptrPila p, string nombre)
{
    int contador = 1;
    while (p != NULL)
    {
        if (p->nombre == nombre)
        {
            return contador++;
        }
        p = p->sgte;
        contador++;
    }
    return -1;
}
