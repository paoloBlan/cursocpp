#include <iostream>
#include <cctype>
#include <string>
#include <limits>

using namespace std;

struct nodo {
    int codigo;
    string nombre;
    float nota;
    struct nodo* izq;
    struct nodo* der;
};

typedef struct nodo* ABB;

int leerEntero(const string& mensaje, int min = 1, int max = numeric_limits<int>::max());
float leerNota();
string leerNombre();
void insertar(ABB&, int, string, float);
string convertirMayusculas(const string&);
void recolectar(ABB, nodo* [], int&);
void ordenarNotas(nodo* [], int);
void mostrarMayores(nodo* [], int);
void sumarNotas(ABB, float&, int&);
void buscarNombre(ABB, const string&);

int main() {
    ABB arbol = NULL;
    int opcion;

    do {
        system("cls");
        cout << "  +-----------------------------------+\n"
            << "  |      SISTEMA ESTUDIANTES          |\n"
            << "  +-----------------------------------+\n"
            << "  | 1 - Ingresar estudiantes          |\n"
            << "  | 2 - Notas mayores                 |\n"
            << "  | 3 - Promedios subarboles          |\n"
            << "  | 4 - Buscar por nombre             |\n"
            << "  | 0 - SALIR                         |\n"
            << "  +-----------------------------------+\n"
            << "  |Opcion: ";
        opcion = leerEntero("", 0, 4);
        cout << "  +-----------------------------------+\n";

        system("cls");

        switch (opcion) {
        case 1: {
            int cantidad = leerEntero("Cantidad de estudiantes: ", 1, 100);
            for (int i = 0; i < cantidad; i++) {
                cout << "ESTUDIANTE " << (i + 1) << ":\n";
                int codigo = leerEntero("Codigo: ", 1);
                string nombre = leerNombre();
                float nota = leerNota();
                insertar(arbol, codigo, nombre, nota);
                cout << endl;
            }
            break;
        }

        case 2: {
            if (arbol) {
                nodo* lista[100];
                int total = 0;
                recolectar(arbol, lista, total);
                ordenarNotas(lista, total);
                mostrarMayores(lista, total);
            }
            else {
                cout << "Arbol vacio!\n";
            }
            cin.get();
            break;
        }

        case 3: {
            if (arbol) {
                float sumaIzq = 0, sumaDer = 0;
                int contIzq = 0, contDer = 0;

                if (arbol->izq) sumarNotas(arbol->izq, sumaIzq, contIzq);
                if (arbol->der) sumarNotas(arbol->der, sumaDer, contDer);

                cout << "PROMEDIOS:\n"
                    << "--------------------------------\n"
                    << "Subarbol izquierdo: "
                    << (contIzq > 0 ? to_string(sumaIzq / contIzq) : "Sin datos") << "\n"
                    << "Subarbol derecho:  "
                    << (contDer > 0 ? to_string(sumaDer / contDer) : "Sin datos") << "\n";
            }
            else {
                cout << "Arbol vacio!\n";
            }
            cin.get();
            break;
        }

        case 4: {
            if (arbol) {
                string buscar = leerNombre();
                cout << "\nRESULTADOS:\n"
                    << "--------------------------------\n";
                buscarNombre(arbol, convertirMayusculas(buscar));
            }
            else {
                cout << "Arbol vacio!\n";
            }
            cin.get();
            break;
        }
        }
    } while (opcion != 0);

    return 0;
}

int leerEntero(const string& mensaje, int min, int max) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= min && valor <= max) break;

        if (max == numeric_limits<int>::max()) {
            cout << "Error: Ingrese un valor valido (min: " << min << ")\n";
        } else {
            cout << "Error: Ingrese un valor entre " << min << " y " << max << "\n";
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return valor;
}

float leerNota() {
    float nota;
    while (true) {
        cout << "Nota: ";
        if (cin >> nota && nota >= 0 && nota <= 20) break;
        cout << "Error: Nota debe estar entre 0 y 20\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return nota;
}

string leerNombre() {
    string nombre;
    //cin.ignore();
    while (true) {
        cout << "Nombre: ";
        getline(cin, nombre);
        if (!nombre.empty()) break;
        cout << "Error: El nombre no puede estar vacio\n";
    }
    return nombre;
}

void insertar(ABB& arbol, int codigo, string nombre, float nota) {
    if (!arbol) {
        arbol = new nodo;
        arbol->codigo = codigo;
        arbol->nombre = nombre;
        arbol->nota = nota;
        arbol->izq = arbol->der = nullptr;
    }
    else {
        if (codigo < arbol->codigo) insertar(arbol->izq, codigo, nombre, nota);
        else insertar(arbol->der, codigo, nombre, nota);
    }
}

string convertirMayusculas(const string& cadena) {
    string resultado = cadena;
    for (auto& c : resultado) c = toupper(c);
    return resultado;
}

void recolectar(ABB arbol, nodo* lista[], int& pos) {
    if (arbol) {
        lista[pos++] = arbol;
        recolectar(arbol->izq, lista, pos);
        recolectar(arbol->der, lista, pos);
    }
}

void ordenarNotas(nodo* lista[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (lista[j]->nota < lista[j + 1]->nota) {
                nodo* temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

void mostrarMayores(nodo* lista[], int total) {
    if (total >= 1) {
        cout << "MAYOR NOTA (" << lista[0]->nota << "):\n";
        cout << "CODIGO\tNOMBRE\t\tNOTA\tESTADO\n";
        cout << "--------------------------------\n";
        for (int i = 0; i < total; i++) {
            if (lista[i]->nota == lista[0]->nota) {
                convertirMayusculas(lista[i]->nombre);
                cout << lista[i]->codigo << "\t";
                cout << lista[i]->nombre << "\t\t";
                cout << lista[i]->nota << "\t";
                cout << (lista[i]->nota >= 10.5 ? "APROBADO" : "DESAPROBADO") << endl;
            }
        }
    }

    if (total >= 2) {
        float segunda = lista[0]->nota;
        for (int i = 1; i < total; i++) {
            if (lista[i]->nota < segunda) {
                segunda = lista[i]->nota;
                break;
            }
        }
        cout << "\nSEGUNDA MAYOR (" << segunda << "):\n";
        cout << "CODIGO\tNOMBRE\t\tNOTA\tESTADO\n";
        cout << "--------------------------------\n";
        for (int i = 0; i < total; i++) {
            if (lista[i]->nota == segunda) {
                convertirMayusculas(lista[i]->nombre);
                cout << lista[i]->codigo << "\t";
                cout << lista[i]->nombre << "\t\t";
                cout << lista[i]->nota << "\t";
                cout << (lista[i]->nota >= 10.5 ? "APROBADO" : "DESAPROBADO") << endl;
            }
        }
    }
}

void sumarNotas(ABB arbol, float& suma, int& cont) {
    if (arbol) {
        suma += arbol->nota;
        cont++;
        sumarNotas(arbol->izq, suma, cont);
        sumarNotas(arbol->der, suma, cont);
    }
}

void buscarNombre(ABB arbol, const string& nombreBuscado) {
    if (arbol) {
        string nombreActual = convertirMayusculas(arbol->nombre);
        if (nombreActual.find(nombreBuscado) != string::npos) {
            cout << arbol->codigo << "\t"
                << arbol->nombre << "\t\t"
                << arbol->nota << "\t"
                << (arbol->nota >= 10.5 ? "APROBADO" : "DESAPROBADO") << endl;
        }
        buscarNombre(arbol->izq, nombreBuscado);
        buscarNombre(arbol->der, nombreBuscado);
    }
}