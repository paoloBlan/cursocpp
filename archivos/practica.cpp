#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <cstring>

using namespace std;

void registrar();
void mostrar();
void modificar();
void clrscr();

void clrscr()
{
    system("clear");
}
void registrar()
{
    char dec, nombre[10], sexo, ced[10];
    float sueldo;
    int edad;
    std::ofstream entrada;
    entrada.open("empleados.txt", std::ios::out | std::ios::app);
    if (entrada.fail())
    {
        std::cout << "ERROR AL ABRIR EL ARCHIVO";
        cin.get();
    }
    else
    {
        do
        {
            clrscr();
            cout << "DATOS A REGISTRAR";
            cout << "\nNOMBRE:";
            cin.getline(nombre, 10);
            cout << "\nCED:";
            cin.getline(ced, 10);
            cout << "\nSEXO (M/F):";
            cin >> sexo;
            cout << "\nEDAD:";
            cin >> edad;
            cout << "\nSUELDO:";
            cin >> sueldo;
            entrada << nombre << " " << ced << " " << sexo << " " << edad << " " << sueldo << endl;
            cout << "\n¿DESEA REGISTRAR OTRO EMPLEADO?:";
            do
            {
                cin >> dec;
                dec = toupper(dec);
                cin.ignore();
            } while (!isalpha(dec));

        } while (dec != 'N');

        entrada.close();
    }

} // FIN DE FUNCION REGISTRAR
void mostrar()
{
    char nombre[10], ced[10], sexo;
    int sueldo, edad;

    std::ifstream salida;

    salida.open("empleados.txt", std::ios::in);
    if (salida.fail())
    {
        clrscr();
        cout << "OCURRIO UN ERROR AL ABRIR EL ARCHIVO";
        cin.get();
    }
    else
    {
        clrscr();
        while (salida >> nombre >> ced >> sexo >> edad >> sueldo)
        {
            std::cout << "\nNOMBRE: " << nombre;
            std::cout << "\nCED: " << ced;
            std::cout << "\nSEXO: " << sexo;
            std::cout << "\nEDAD: " << edad;
            std::cout << "\nSUELDO: $" << sueldo;
            std::cout << "\n---------------------------\n";
        }

        salida.close();
    }
    cout << "\nRbegresar(y/n): ";
    cin.get();
    cin.ignore();
}

void modificar()
{
    char auxced[10], nombre[10], ced[10], sexo;
    int sueldo, edad;

    ofstream temp;
    temp.open("temporal.txt", ios::out);

    ifstream salida;
    salida.open("empleados.txt", ios::in);

    if (temp.fail() || salida.fail())
    {
        clrscr();
        cout << "OCURRIO UN ERROR AL ABRIR EL ARCHIVO";
        cin.get();
    }
    else
    {
        clrscr();
        cout << "INTRODUZCA LA CEDULA:";
        cin.getline(auxced, 10);

        while (salida >> nombre >> ced >> sexo >> edad >> sueldo)
        {
            
            
            if (strcmp(auxced, ced) == 0)
            {
                cout << "INTRODUZCA EL NUEVO SUELDO DEL TRABAJADOR:";
                cin >> sueldo;
              
            }
            temp << nombre << " " << ced << " " << sexo << " " << edad << " " << sueldo << endl;
            
            
        
        }
        temp.close();   // contiene lo datos actualizados
        salida.close(); // Este es el archivo viejo con los datos viejos

        remove("empleados.txt");
        rename("temporal.txt", "empleados.txt");

        cout << "\nRbegresar(y/n): ";
        cin.get();
        cin.ignore();
    }
}

int main()
{
    char dec;
    do
    {
        clrscr();
        cout << "\n[A].- REGISTRAR ";
        cout << "\n[B].- MOSTRAR ";
        cout << "\n[C].- MODIFICAR ";
        cout << "\n[D].- SALIR ";

        do
        {
            do
            {

                cout << "\nINGRESE UNA LETRA: ";
                dec = toupper(cin.get());
                cin.ignore();

            } while (!isalpha(dec));
        } while (dec < 'A' || dec > 'E');
        switch (dec)
        {
        case 'A':
        {
            registrar();
            break;
        }
        case 'B':
        {
            mostrar();
            break;
        }
        case 'C':
        {
            modificar();
            break;
        }
        }
    } while (dec != 'D');

    return 0;
}
