/*
    Se tiene una cola de hombre y mujeres con sus nombres,
     se debe dividir la colar en dos resultantes, 
     una para hombres y otra para mujeres.
*/

#include <iostream>

using namespace std;

struct nodo {
    string nombre;
    int genero; // 0 para mujer, 1 para hombre
    struct nodo *sgte;
};

// Estructura de la cola
struct cola {
    struct nodo *delante;
    struct nodo *atras;
};

// Funciones principales
void inicializa(struct cola &);
void encola(struct cola &,string, int);


void dividirColas(struct cola &, struct cola &, struct cola &);
void verCola(struct cola, string);
void desencola(struct cola &);
void menu();
void limpiarPantalla();

int main() {
    int opc;
    struct cola data, mujeres, hombres;
    inicializa(data);
    inicializa(mujeres);
    inicializa(hombres);
    char repetir;
    int genero;
    string nombre;

    do {
        limpiarPantalla();
        menu();

        cout << "Ingrese una opcion: ";
        cin >> opc;
        cin.ignore();
        limpiarPantalla();

        switch (opc) {
            case 1:
                cout << "Ingrese nombre: ";
                cin >> nombre;
                cout << "Ingrese género (0 = Mujer, 1 = Hombre): ";
                cin >> genero;
                cin.ignore();
                encola(data, nombre, genero);
                dividirColas(data, mujeres, hombres);
                break;

          

            case 2:
                verCola(mujeres, "Cola de Mujeres");
                break;

            case 3:
                verCola(hombres, "Cola de Hombres");
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

// Inicializar la cola
void inicializa(struct cola &q) {
   q.delante = NULL; 
    q.atras = NULL;
}

// Encolar un elemento con nombre y género
void encola(struct cola &q, string nombre, int genero) {
    struct nodo *p;
    p = new (struct nodo);
    p->nombre = nombre;
    p->genero = genero;
    p->sgte = nullptr;

    if (q.delante == NULL) {
        q.delante = p;
    } else {
         (q.atras)->sgte = p;
    }
    q.atras = p;
}

// Dividir la cola en mujeres y hombres
void dividirColas(struct cola &data, struct cola &mujeres, struct cola &hombres)
 {
    
    struct nodo *d;
    d = data.delante;
    struct nodo *aux;

    while (d != NULL) {
        aux = d->sgte;
        if (d->genero == 0) {
            encola(mujeres, d->nombre, d->genero); 
        } 

        if (d->genero == 1) {
            encola(hombres, d->nombre, d->genero);
            
        } 
        delete(d);
        d = aux;
    }
    data.delante = NULL;
    data.atras = NULL;
}

// Mostrar los elementos de la cola con el título dado
void verCola(struct cola q, string titulo) {
    struct nodo *p;
    p = q.delante;
    cout << titulo << ":\n";
    while (p != nullptr) {
        cout << p->nombre << " (" << (p->genero == 0 ? "Mujer" : "Hombre") << ")\n";
        p = p->sgte;
    }
    cout << endl;
}

// Menú principal
void menu() {
    cout << "=============================\n";
    cout << "   📚 MENÚ COLAS   \n";
    cout << "=============================\n";
    cout << "1. Ingresar persona a la Cola\n";
    cout << "2. Ver Cola de Mujeres\n";
    cout << "3. Ver Cola de Hombres\n";
    cout << "4. Salir\n";
    cout << "=============================\n";
}

// Limpiar la pantalla según el sistema operativo
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void desencola(struct cola &q)
{
    struct nodo *p;
    p = q.delante; 
    q.delante = (q.delante)->sgte;
    delete (p);
   
}