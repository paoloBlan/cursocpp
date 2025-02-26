#include <iostream>
#include <string>
#include <iomanip> // Para alinear texto

using namespace std;

struct Nodo {
    string spanish;
    string english;
    Nodo* sgte;
};

using tDiccionario = Nodo*;

void insertar(tDiccionario& diccionario, const string& spanish, const string& english);
void mostrar(tDiccionario diccionario);
void buscarEnglishToSpanish(tDiccionario diccionario, const string& english);
void buscarSpanishToEnglish(tDiccionario diccionario, const string& spanish);
void mostrarDespuesPalabra(tDiccionario diccionario, const string& palabra);
void mostrarMenu();
void limpiarPantalla();

int main() {
    tDiccionario diccionario = nullptr;
    int opcion;
    string spanish, english;
    char repetir;

    // Insertar datos en el diccionario
    insertar(diccionario, "hola", "hello");
    insertar(diccionario, "adios", "goodbye");
    insertar(diccionario, "manzana", "apple");
    insertar(diccionario, "perro", "dog");
    insertar(diccionario, "gato", "cat");
    insertar(diccionario, "luna", "moon");
    insertar(diccionario, "sol", "sun");
    insertar(diccionario, "nube", "cloud");
    insertar(diccionario, "arbol", "tree");
    insertar(diccionario, "hoja", "leaf");
    insertar(diccionario, "ventana", "window");
    insertar(diccionario, "casa", "house");
    insertar(diccionario, "piso", "floor");
    insertar(diccionario, "puerta", "door");
    insertar(diccionario, "ventilador", "air conditioner");
    insertar(diccionario, "lavadora", "washing machine");
    insertar(diccionario, "television", "television");
    insertar(diccionario, "computadora", "computer");
    insertar(diccionario, "celular", "cellphone");
    insertar(diccionario, "internet", "internet");

    do {
        limpiarPantalla();
        mostrarMenu();

        cout << "\nIngrese una opción: ";
        cin >> opcion;
        cin.ignore();

        limpiarPantalla();

        switch (opcion) {
            case 1:
                cout << "📖 Diccionario Completo:\n";
                cout << "========================\n";
                mostrar(diccionario);
                break;

            case 2:
                mostrar(diccionario);
                cout << "\n🔍 Traducir al Castellano\n";
                cout << "-----------------------------\n";
                cout << "Ingrese la palabra en inglés: ";
                cin >> english;
                cin.ignore();
                buscarEnglishToSpanish(diccionario, english);
                break;

            case 3:
                mostrar(diccionario);
                cout << "\n🔍 Traducir al Inglés\n";
                cout << "-----------------------------\n";
                cout << "Ingrese la palabra en castellano: ";
                cin >> spanish;
                cin.ignore();
                buscarSpanishToEnglish(diccionario, spanish);
                break;

            case 4:
                mostrar(diccionario);
                cout << "\n📂 Mostrar Después de una Palabra\n";
                cout << "-----------------------------------\n";
                cout << "Ingrese la palabra en castellano: ";
                cin >> spanish;
                cin.ignore();
                mostrarDespuesPalabra(diccionario, spanish);
                break;

            case 5:
                cout << "👋 ¡Gracias por usar el diccionario!\n";
                return 0;

            default:
                cout << "❌ Opción no válida. Intente de nuevo.\n";
        }

        cout << "\n¿Desea realizar otra acción? (s/n): ";
        cin >> repetir;
        cin.ignore();

    } while (repetir == 's' || repetir == 'S');

    cout << "👋 ¡Hasta pronto!\n";
    return 0;
}


void mostrarMenu() {
    cout << "=============================\n";
    cout << "   📚 MENÚ DEL DICCIONARIO   \n";
    cout << "=============================\n";
    cout << "1. Mostrar Diccionario\n";
    cout << "2. Traducir al Castellano\n";
    cout << "3. Traducir al Inglés\n";
    cout << "4. Mostrar Después de una Palabra\n";
    cout << "5. Salir\n";
    cout << "=============================\n";
}


void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void insertar(tDiccionario& diccionario, const string& spanish, const string& english) {
    Nodo* nuevo = new Nodo{spanish, english, nullptr};
    if (!diccionario) {
        diccionario = nuevo;
        return;
    }
    Nodo* actual = diccionario;
    while (actual->sgte) {
        actual = actual->sgte;
    }
    actual->sgte = nuevo;
}

void mostrar(tDiccionario diccionario) {
    Nodo* actual = diccionario;
    cout << left << setw(15) << "Español" << " | " << "Inglés" << endl;
    cout << "-----------------------------" << endl;
    while (actual) {
        cout << left << setw(15) << actual->spanish << " | " << actual->english << endl;
        actual = actual->sgte;
    }
}

void buscarEnglishToSpanish(tDiccionario diccionario, const string& english) {
    Nodo* actual = diccionario;
    while (actual) {
        if (actual->english == english) {
            cout << "La traducción de '" << english << "' es '" << actual->spanish << "'." << endl;
            return;
        }
        actual = actual->sgte;
    }
    cout << "No se encontró la traducción para '" << english << "'." << endl;
}

void buscarSpanishToEnglish(tDiccionario diccionario, const string& spanish) {
    Nodo* actual = diccionario;
    while (actual) {
        if (actual->spanish == spanish) {
            cout << "La traducción de '" << spanish << "' es '" << actual->english << "'." << endl;
            return;
        }
        actual = actual->sgte;
    }
    cout << "No se encontró la traducción para '" << spanish << "'." << endl;
}

void mostrarDespuesPalabra(tDiccionario diccionario, const string& palabra) {
    Nodo* actual = diccionario;
    bool encontrado = false;

    while (actual) {
        if (actual->spanish == palabra) {
            encontrado = true;
        }
        if (encontrado) {
            cout << actual->spanish << " - " << actual->english << endl;
        }
        actual = actual->sgte;
    }

    if (!encontrado) {
        cout << "Palabra '" << palabra << "' no encontrada en la lista." << endl;
    }
}
