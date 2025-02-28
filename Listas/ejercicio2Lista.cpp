/*
    Se tiene artículos cada uno con los siguientes atributos: código, descripción, precio de compra y cantidad. 
    Ordene estos artículos según el monto total de inversión (precio de compra * cantidad). 
    Luego, clasifíquelos en tres grupos: 
    grupo A, con aquellos artículos que tengan el 70 por ciento de la inversión total; 
    grupo B, con aquellos artículos que concentren el 25 por ciento de la inversión total; y 
    grupo C, con aquellos artículos que representen el 5 por ciento restante. Use listas doblemente enlazadas.

*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <stdio.h>
#include <iomanip>
using namespace std;

struct Nodo
{
    string codigo;
    string descripcion;
    float precioCompra;
    int cantidad;

    Nodo *sgte;
};

typedef Nodo* tProducto;
typedef Nodo* tGrupoA;
typedef Nodo* tGrupoB;
typedef Nodo* tGrupoC;


float totalInversion = 0.0;
float iGrupoA = 0.0;
float iGrupoB = 0.0;
float iGrupoC = 0.0;

void insertar(tProducto &, string, string, float, int);

float calcularInversion(float, int);

void OrdenarPorTotalInversion(tProducto &);

void clasificarProducto(tProducto, tGrupoA &, tGrupoB &, tGrupoC &);

void mostrarMenu();
void limpiarPantalla();

void mostrarProductos(tProducto,float);

int main()
{

    tProducto producto = nullptr;
    tGrupoA grupoA = nullptr;
    tGrupoB grupoB = nullptr;
    tGrupoC grupoC = nullptr;
    int opcion;
    char repetir;

    insertar(producto, "P001", "Laptop", 999.99, 10.0);
    insertar(producto, "P002", "Smartphone", 499.49, 20.0);
    insertar(producto, "P003", "Monitor", 199.99, 15.0);
    insertar(producto, "P004", "Teclado", 49.99, 50.0);
    insertar(producto, "P005", "Mouse", 19.99, 100.0);
    insertar(producto, "P006", "Impresora", 150.75, 5.0);
    insertar(producto, "P007", "Escritorio", 250.00, 8.0);
    insertar(producto, "P008", "Silla", 85.50, 30.0);
    insertar(producto, "P009", "Lámpara", 22.99, 25.0);
    insertar(producto, "P010", "USB", 9.99, 200.0);
    insertar(producto, "P011", "Cable HDMI", 12.50, 100.0);
    insertar(producto, "P012", "Audífonos", 29.99, 40.0);
    insertar(producto, "P013", "Proyector", 499.99, 3.0);
    insertar(producto, "P014", "Tablet", 350.00, 12.0);
    insertar(producto, "P015", "Cámara", 299.99, 6.0);
    insertar(producto, "P016", "Router", 75.00, 10.0);
    insertar(producto, "P017", "Disco Duro", 89.99, 20.0);
    insertar(producto, "P018", "Memoria RAM", 45.99, 15.0);
    insertar(producto, "P019", "Tarjeta Gráfica", 750.00, 2.0);
    insertar(producto, "P020", "Batería Externa", 39.99, 50.0);

    OrdenarPorTotalInversion(producto);

    iGrupoA = totalInversion * 0.70;
    iGrupoB = totalInversion * 0.25;
    iGrupoC = totalInversion * 0.05;
    clasificarProducto(producto, grupoA, grupoB, grupoC);

    //clasificarProducto(producto, grupoA, grupoB, grupoC);

    do
    {
        limpiarPantalla();
        mostrarMenu();
        cout << "\nIngrese una opción: ";
        cin >> opcion;
        cin.ignore();
        limpiarPantalla();
        switch (opcion)
        {
        case 1:
            mostrarProductos(producto,totalInversion);
            break;
        case 2:
            mostrarProductos(grupoA,iGrupoA);
           
            break;
        case 3:
            mostrarProductos(grupoB,iGrupoB);
            break;
        case 4:
             mostrarProductos(grupoC,iGrupoC);
            break;
        case 5:
            cout << "Saliendo del programa...\n";
            return 0;
        default:
            cout << "Opción inválida.\n";
        }
        cout << "\n¿Desea realizar otra acción? (s/n): ";
        cin >> repetir;
        cin.ignore();

    } while (repetir == 's' || repetir == 'S');
    
    
    
}

void insertar(tProducto &lista, string codigo, string descripcion, float precioCompra, int cantidad)
{
    tProducto pro;
    tProducto q = new Nodo;
    q->codigo = codigo;
    q->descripcion = descripcion;
    q->cantidad = cantidad;
    q->precioCompra = precioCompra;
    q->sgte = nullptr;
    
    if (lista == nullptr)
    {
        lista = q;
        
    }else {
        pro = lista;
        while (pro->sgte!= nullptr){
            pro = pro->sgte;
        }
        pro->sgte = q;
    }
    
}

float calcularInversion(float precioCompra, int cantidad)
{
    return precioCompra * cantidad;
}

void OrdenarPorTotalInversion(tProducto &producto)
{
    totalInversion = 0.0;
    if (!producto)
        return;
    bool cambiado;
    do
    {

        cambiado = false;
        tProducto p = producto;
        totalInversion += calcularInversion(p->precioCompra, p->cantidad);
        while (p->sgte != nullptr)
        {
           
            if (calcularInversion(p->precioCompra, p->cantidad) > calcularInversion(p->sgte->precioCompra, p->sgte->cantidad))
            {
                swap(p->codigo, p->sgte->codigo);
                swap(p->descripcion, p->sgte->descripcion);
                swap(p->precioCompra, p->sgte->precioCompra);
                swap(p->cantidad, p->sgte->cantidad);
                cambiado = true;
            }
            p = p->sgte;
        }

    } while (cambiado);
}

void mostrarProductos(tProducto producto, float totalInversionBygrupo)

{
    cout << "\n═════════════════════════════════════════════════════════════════════════════════════════════════════\n";
    cout << "║ " << left << setw(12) << "Código"
         << "║ " << setw(35) << "Descripción"
         << "║ " << setw(20) << "Precio Unitario"
         << "║ " << setw(15) << "Cantidad"
         << "║ " << setw(15) << "Inversión"
         << "║\n";
    cout << "═════════════════════════════════════════════════════════════════════════════════════════════════════\n";

    while (producto != nullptr)
    {
        cout << "║ " << left << setw(12) << producto->codigo
             << "║ " << setw(35) << producto->descripcion
             << "║ $" << setw(19) << fixed << setprecision(2) << producto->precioCompra
             << "║ " << setw(14) << producto->cantidad
             << "║ $" << setw(14) << fixed << setprecision(2)
             << calcularInversion(producto->precioCompra, producto->cantidad)
             << "║\n";

        cout << "-----------------------------------------------------------------------------------------------------\n";

        producto = producto->sgte;
    }
    cout
        << "║ " << setw(88) << "total inversión: "
        << "║ $" << setw(14) << totalInversionBygrupo << "║\n";

    cout << "-----------------------------------------------------------------------------------------------------\n";

    cout << "═════════════════════════════════════════════════════════════════════════════════════════════════════\n";
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarMenu()
{
    cout << "=============================\n";
    cout << "   📚 MENÚ PRODUCTOS   \n";
    cout << "=============================\n";
    cout << "1. Orden por monto de inversion\n";
    cout << "2. Grupo A\n";
    cout << "3. Grupo B\n";
    cout << "4. Grupo C\n";
    cout << "5. Salir\n";
    cout << "=============================\n";
}

void clasificarProducto(tProducto producto, tGrupoA &grupoA, tGrupoB &grupoB, tGrupoC &grupoC)
{

    if (!producto)
        return;

    grupoA = nullptr;
    grupoB = nullptr;
    grupoC = nullptr;

    while (producto!= nullptr) 
    {
       if (calcularInversion(producto->precioCompra, producto->cantidad) <= iGrupoC) {
            insertar(grupoC, producto->codigo, producto->descripcion, producto->precioCompra, producto->cantidad);
             producto = producto->sgte;
            continue;
       }
       if (calcularInversion(producto->precioCompra, producto->cantidad) <= iGrupoB) {
            insertar(grupoB, producto->codigo, producto->descripcion, producto->precioCompra, producto->cantidad);
             producto = producto->sgte;
            continue;
       }

       if (calcularInversion(producto->precioCompra, producto->cantidad) <= iGrupoA) {
            insertar(grupoA, producto->codigo, producto->descripcion, producto->precioCompra, producto->cantidad);
             producto = producto->sgte;
            continue;
       }
       producto = producto->sgte;
    }


    
}
