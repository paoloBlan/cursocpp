#include <iostream>
#include <cctype>
#include <string>
#include <limits>

using namespace std;

struct nodo {
    int codigo;
    string nombre;
    int edad;
    char sexo;
    struct nodo* izq;
    struct nodo* der;
};

typedef struct nodo* ABB;

void inserta(ABB&, int, string, int, char);
void mostrarMenoresEdad(ABB);
void colectarAlumnos(ABB, nodo* [], int&);
void mostrarMujeresEnSubarbol(ABB);
void mostrarMujeresIzquierda(ABB);
void ordenarPorEdad(nodo* [], int);
string convertirMayusculas(const string&);
int leerEnteroPositivo(const string& mensaje, int min = 1, int max = numeric_limits<int>::max());

int main() {
    ABB arbol = NULL;
    int n, opcion;
    do {
        system("cls");
        cout << "  +-----------------------------------+" << endl;
        cout << "  |      MENU PRINCIPAL               |" << endl;
        cout << "  +-----------------------------------+" << endl;
        cout << "  | 1 - Ingresar Elementos            |" << endl;
        cout << "  +-----------------------------------+" << endl;
        cout << "  | 2- Alumnos menos de 18 anios      |" << endl;
        cout << "  | 3- Edad menor y segunda           |" << endl;
        cout << "  | 4- Mujeres lado izquierdo         |" << endl;
        cout << "  +-----------------------------------+" << endl;
        cout << "  | 0 - SALIR                         |" << endl;
        cout << "  +-----------------------------------+" << endl;
        cout << "  |Ingrese su Opcion: ";
        cin >> opcion;
        cout << "  +-----------------------------------+" << endl << endl;

        system("cls");

        switch (opcion) {
        case 1: {
            cout << "Cantidad de alumnos: ";
            int n = leerEnteroPositivo("", 1, 100);


            for (int i = 0; i < n; i++) {
                cout << "Alumno (" << (i + 1) << ")\n";

                int codigo = leerEnteroPositivo("Codigo: ", 1);

                string nombre;
                cout << "Nombre: ";
                getline(cin, nombre);
                while (nombre.empty()) {
                    cout << "Error: Nombre no puede estar vacio: ";
                    getline(cin, nombre);
                }

                int edad = leerEnteroPositivo("Edad: ", 1, 120);


                char sexo;
                while (true) {
                    cout << "Sexo (F/M): ";
                    cin >> sexo;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    sexo = toupper(sexo);
                    if (sexo == 'F' || sexo == 'M') break;
                    cout << "Error: Sexo debe ser F o M.\n";
                }

                inserta(arbol, codigo, nombre, edad, sexo);
                cout << "\n";
            }
            break;
        }

        case 2: {
            if (arbol != NULL) {
                cout << "ALUMNOS MENORES DE 18:\n";
                cout << "CODIGO\tNOMBRE\t\tEDAD\tSEXO\n";
                cout << "--------------------------------\n";
                mostrarMenoresEdad(arbol);
            }
            else cout << "Arbol vacio!\n";
            cin.ignore();
            cin.get();
            break;
        }

        case 3: {
            if (arbol != NULL) {
                nodo* alumnos[100];
                int total = 0;
                colectarAlumnos(arbol, alumnos, total);

                if (total == 0) cout << "No hay alumnos!\n";
                else {
                    ordenarPorEdad(alumnos, total);

                    int menor = alumnos[0]->edad;
                    int segunda = -1;
                    if(total > 1){
                    	segunda = alumnos[1]->edad;
					}
                    

                    cout << "EDAD MENOR (" << menor << "):\n";
                    cout << "CODIGO\tNOMBRE\t\tEDAD\tSEXO\n";
                    cout << "--------------------------------\n";
                    for (int i = 0; i < total; i++) {
                        if (alumnos[i]->edad == menor) {
                            cout << alumnos[i]->codigo << "\t";
                            cout << convertirMayusculas(alumnos[i]->nombre) << "\t\t";
                            cout << alumnos[i]->edad << "\t" << alumnos[i]->sexo << "\n";
                        }
                    }

                    if (segunda != -1) {
                        cout << "\nSEGUNDA EDAD (" << segunda << "):\n";
                        cout << "CODIGO\tNOMBRE\t\tEDAD\tSEXO\n";
                        cout << "--------------------------------\n";
                        for (int i = 0; i < total; i++) {
                            if (alumnos[i]->edad == segunda) {
                                cout << alumnos[i]->codigo << "\t";
                                cout << convertirMayusculas(alumnos[i]->nombre) << "\t\t";
                                cout << alumnos[i]->edad << "\t" << alumnos[i]->sexo << "\n";
                            }
                        }
                    }
                    else cout << "\nNo existe segunda edad menor!\n";
                }
            }
            else cout << "Arbol vacio!\n";
            cin.ignore();
            cin.get();
            break;
        }

        case 4: {
            if (arbol != NULL) mostrarMujeresIzquierda(arbol);
            else cout << "Arbol vacio!\n";
            cin.ignore();
            cin.get();
            break;
        }
        }
    } while (opcion != 0);
    return 0;
}

string convertirMayusculas(const string& cadena) {
    string resultado = cadena;
    for (auto& c : resultado) {
        c = toupper(c);
    }
    return resultado;
}

void ordenarPorEdad(nodo* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j]->edad > arr[j + 1]->edad) {
                nodo* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void inserta(ABB& arbol, int codigo, string nombre, int edad, char sexo) {
    if (arbol == NULL) {
        arbol = new nodo;
        arbol->codigo = codigo;
        arbol->nombre = nombre;
        arbol->edad = edad;
        arbol->sexo = sexo;
        arbol->izq = arbol->der = NULL;
    }
    else {
        if (codigo < arbol->codigo) inserta(arbol->izq, codigo, nombre, edad, sexo);
        else inserta(arbol->der, codigo, nombre, edad, sexo);
    }
}

void mostrarMenoresEdad(ABB arbol) {
    if (arbol != NULL) {
        if (arbol->edad < 18) {
            cout << arbol->codigo << " | "
                << convertirMayusculas(arbol->nombre) << " | "
                << arbol->edad << " | " << arbol->sexo << endl;
        }
        mostrarMenoresEdad(arbol->izq);
        mostrarMenoresEdad(arbol->der);
    }
}

void colectarAlumnos(ABB arbol, nodo* arr[], int& pos) {
    if (arbol == NULL) return;
    arr[pos++] = arbol;
    colectarAlumnos(arbol->izq, arr, pos);
    colectarAlumnos(arbol->der, arr, pos);
}

void mostrarMujeresEnSubarbol(ABB subarbol) {
    if (subarbol != NULL) {
        if (subarbol->sexo == 'F') {
            cout << subarbol->codigo << " | "
                << convertirMayusculas(subarbol->nombre) << " | "
                << subarbol->edad << " | F\n";
        }
        mostrarMujeresEnSubarbol(subarbol->izq);
        mostrarMujeresEnSubarbol(subarbol->der);
    }
}

void mostrarMujeresIzquierda(ABB arbol) {
    if (arbol->izq == NULL) {
        cout << "No existe subarbol izquierdo!\n";
        return;
    }
    cout << "Mujeres en el lado izquierdo:\n";
    mostrarMujeresEnSubarbol(arbol->izq);
    cin.ignore();
    cin.get();
}

int leerEnteroPositivo(const string& mensaje, int min, int max) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor >= min && valor <= max) break;
            cout << "Error: El valor debe estar entre " << min << " y " << max << ".\n";
        }
        else {
            cout << "Error: Entrada no numerica. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cin.ignore();
    return valor;
}