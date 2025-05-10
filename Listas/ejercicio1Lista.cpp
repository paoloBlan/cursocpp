/*
    Se tiene una lista enlazada con un traductor electrónico en inglés/ castellano, se requiere hacer lo siguiente:
        o	Ingrese una palabra en castellano y muestre sus significados en inglés
        o	Ingrese una palabra en inglés y muestre sus significados en castellano
        o	Ingrese una palabra y muestre todas las que siguen después de ella.


*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <stdio.h>
#include <iomanip> // Para alinear texto

using namespace std;

struct Nodo {
    string spanish;
    string english;
    Nodo* sgte;
};

typedef Nodo* tDiccionario;


void insertar(tDiccionario& ,string, string);
void mostrar(tDiccionario );
void buscarEnglishToSpanish(tDiccionario,string);
void buscarSpanishToEnglish(tDiccionario, string);
void mostrarDespuesPalabra(tDiccionario, string);
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


void insertar(tDiccionario& diccionario,  string spanish, string english) {
    tDiccionario di;
    tDiccionario q = new Nodo;
    q->spanish = spanish;
    q->english = english;
    q->sgte = nullptr;

    if (diccionario == nullptr) {
        diccionario = q;   
    }else
    {
        di = diccionario;
        while (di->sgte!= nullptr)
            di = di->sgte;
        di->sgte = q;
    }
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

void buscarEnglishToSpanish(tDiccionario diccionario, string english) {
   
    while (diccionario) {
        if (diccionario->english == english) {
            cout << "La traducción de '" << english << "' es '" << diccionario->spanish << "'." << endl;
            return;
        }
        diccionario = diccionario->sgte;
    }
    cout << "No se encontró la traducción para '" << english << "'." << endl;
}

void buscarSpanishToEnglish(tDiccionario diccionario, string spanish) {
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

void mostrarDespuesPalabra(tDiccionario diccionario, string palabra) {
   
    bool encontrado = false;

    while (diccionario) {
        if (diccionario->spanish == palabra) {
            encontrado = true;
        }
        if (encontrado) {
            cout << diccionario->spanish << " - " << diccionario->english << endl;
        }
        diccionario = diccionario->sgte;
    }

    if (!encontrado) {
        cout << "Palabra '" << palabra << "' no encontrada en la lista." << endl;
    }
}
