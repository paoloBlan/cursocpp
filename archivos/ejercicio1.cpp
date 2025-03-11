#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <iomanip>
#include <cmath> 

using namespace std;

struct Alumno
{
    char codigo[15];
    char nombre[25];
    char especialidad[35];
    int edad;
    float promedio;
    Alumno * sgte;

};

typedef Alumno* bdAlumno;

void insertar(bdAlumno&, Alumno);
void registrar(bdAlumno&);
void traerBd(bdAlumno&);
void mostrar(bdAlumno);
void mayoresEdad(bdAlumno);
void especialidadIngenieria(bdAlumno);
void ordenarPorNombre(bdAlumno&);
void toUpperCase(char*);
void clrscr();

void clrscr() {
    #ifdef _WIN32
        system("cls");  // Para Windows
    #else
        system("clear"); // Para macOS y Linux
    #endif
}

void registrar(bdAlumno& listaAlumno)
{
    ofstream bdAlumnos;
    Alumno a;
    char dec;
    bdAlumnos.open("bdAlumnos.txt", ios::out | ios::app);
    if (bdAlumnos.fail())
    {
        cout << "ERROR AL ABRIR EL ARCHIVO";
        cin.get();
    }
    else
    {
        do
        {
            clrscr();
            cout << "DATOS A REGISTRAR";
            cout << "\nCodigo:";
            cin.getline(a.codigo, 15);
            toUpperCase(a.codigo);
            cout << "\nNombre:";
            cin.getline(a.nombre, 25);
            toUpperCase(a.nombre);
            cout << "\nEspecialidad:";
            cin.getline(a.especialidad, 35);
            toUpperCase(a.especialidad);
            cout << "\nEdad:";
            cin >> a.edad;
            cout << "\nPromedio:";
            cin >> a.promedio;
            cin.ignore();
            bdAlumnos << left << setw(15) << setfill(' ') << a.codigo
                      << left << setw(25) << setfill(' ') << a.nombre
                      << left << setw(35) << setfill(' ') << a.especialidad
                      << left << setw(3) << a.edad << " "
                      << left << fixed << setprecision(2) << a.promedio << endl;
            insertar(listaAlumno, a);
            cout << "\n¿DESEA REGISTRAR OTRO EMPLEADO?:";
            do
            {
                cin >> dec;
                dec = toupper(dec);
                cin.ignore();
            } while (!isalpha(dec));
        } while (dec != 'N');
        bdAlumnos.close();
    }
}

void traerBd(bdAlumno& listaAlumnos)
{
    Alumno a;
    ifstream bdAlumnos;
    string perosnas;
    bdAlumnos.open("bdAlumnos.txt", ios::in);
    if (bdAlumnos.fail())
    {
        clrscr();
        cout << "OCURRIO UN ERROR AL ABRIR EL ARCHIVO";
        cin.get();
    }
    else
    {        
        while (getline(bdAlumnos, perosnas))
        {
            strncpy(a.codigo, perosnas.c_str(), 15);
            a.codigo[14] = '\0';  
            strncpy(a.nombre, perosnas.c_str() + 15, 25);  
            a.nombre[24] = '\0'; 
            strncpy(a.especialidad, perosnas.c_str() + 40, 35);  
            a.especialidad[34] = '\0';
            a.edad = stoi(perosnas.substr(75,3));
            a.promedio = round(stof(perosnas.substr(78,6)) * 100) / 100.00;
            insertar(listaAlumnos, a);
        }
        bdAlumnos.close();
    }
    cout << "\n Se cargo la base de dato a la lista (write any keys..): ";
    cin.get();
    cin.ignore();
}

int main()
{
    bdAlumno listaAlumno = nullptr;
    traerBd(listaAlumno);
    char dec;
    do
    {
        clrscr();
        cout << "\n[A].- REGISTRAR ALUMNO ";
        cout << "\n[B].- MOSTRAR ALUMNOS ";
        cout << "\n[C].- MOSTRAR ALUMNOS MAYORES DE EDAD";
        cout << "\n[D].- LISTADO ALUMNOS DE INGENIERIA ";
        cout << "\n[E].- ORDENAMIENTO POR NOMBRE METODO BURBUJA";
        cout << "\n[F].- SALIR ";
        do
        {
            do
            {
                cout << "\nINGRESE UNA LETRA: ";
                dec = toupper(cin.get());
                cin.ignore();

            } while (!isalpha(dec));
        } while (dec < 'A' || dec > 'F');

        switch (dec)
        {
            case 'A':
            {
                registrar(listaAlumno);
                break;
            }

            case 'B':
            {
            
                mostrar(listaAlumno);
                cout << "\n write (s/S) to continue: ";
                dec = toupper(cin.get());
                cin.ignore();
                break;
            }

            case 'C':
            {
            
                mayoresEdad(listaAlumno);
                cout << "\n write (s/S) to continue: ";
                dec = toupper(cin.get());
                cin.ignore();
                break;
            }

            case 'D':
            {
            
                especialidadIngenieria(listaAlumno);
                cout << "\n write (s/S) to continue: ";
                dec = toupper(cin.get());
                cin.ignore();
                break;
            }

            case 'E':
            {
            
                ordenarPorNombre(listaAlumno);
                mostrar(listaAlumno);
                cout << "\n write (s/S) to continue: ";
                dec = toupper(cin.get());
                cin.ignore();
                break;
            }
        }
    } while (dec != 'F');
    return 0;
}

void insertar(bdAlumno& listaAlumno, Alumno alum) {
    bdAlumno di;
    bdAlumno q = new Alumno;
    strcpy(q->codigo, alum.codigo);
    strcpy(q->nombre, alum.nombre);
    strcpy(q->especialidad, alum.especialidad);
    q->edad = alum.edad;
    q->promedio = alum.promedio;
    q->sgte = nullptr;
    if (listaAlumno == nullptr) {
        listaAlumno = q;   
    }else
    {
        di = listaAlumno;
        while (di->sgte!= nullptr)
            di = di->sgte;
        di->sgte = q;
    }

}

void mostrar(bdAlumno listaAlumno) {
    cout << "--------------Lista de alumnos---------------------------" << endl;
    while (listaAlumno != nullptr) {
        cout<< "codigo: " << listaAlumno->codigo<< endl;
        cout<< "nombre: " << listaAlumno->nombre<< endl;
        cout<< "especialidad: " << listaAlumno->especialidad<< endl;
        cout<< "edad: " << listaAlumno->edad<< endl;
        cout<< "promedio: " << listaAlumno->promedio<< endl;
        cout<< "\n";
        cout << "------------------------------" << endl;
        listaAlumno = listaAlumno->sgte;    
    }
}

void mayoresEdad(bdAlumno listaAlumno) {
    cout << "--------------Alumnos mayores de edad ---------------------------" << endl;
    while (listaAlumno!= nullptr) {
        if (listaAlumno->edad > 18) {
            cout<< "codigo: " << listaAlumno->codigo<< endl;
            cout<< "nombre: " << listaAlumno->nombre<< endl;
            cout<< "especialidad: " << listaAlumno->especialidad<< endl;
            cout<< "edad: " << listaAlumno->edad<< endl;
            cout<< "promedio: " << listaAlumno->promedio<< endl;
            cout<< "\n";
            cout << "------------------------------" << endl;
        }
        listaAlumno = listaAlumno->sgte;    
    }
}

void especialidadIngenieria(bdAlumno listaAlumno) {
    cout << "--------------Alumnos de la especialidad de Ingenieria ---------------------------" << endl;
    while (listaAlumno!= nullptr) {
        toUpperCase(listaAlumno->especialidad);
        if (strstr(listaAlumno->especialidad, "INGENIERIA") != nullptr) {
            cout<< "codigo: " << listaAlumno->codigo<< endl;
            cout<< "nombre: " << listaAlumno->nombre<< endl;
            cout<< "especialidad: " << listaAlumno->especialidad<< endl;
            cout<< "edad: " << listaAlumno->edad<< endl;
            cout<< "promedio: " << listaAlumno->promedio<< endl;
            cout<< "\n";
            cout << "------------------------------" << endl;
        }
        listaAlumno = listaAlumno->sgte;    
    }
}

void ordenarPorNombre(bdAlumno& lista) {
    if (lista == nullptr) return;
    bool cambiado;
    do {
        cambiado = false;
        bdAlumno q = lista;
        while (q->sgte != nullptr) {
            if (strcmp(q->nombre, q->sgte->nombre) > 0) { // Comparar nombres alfabéticamente
                swap(q->codigo, q->sgte->codigo);
                swap(q->nombre, q->sgte->nombre);
                swap(q->especialidad, q->sgte->especialidad);
                swap(q->edad, q->sgte->edad);
                swap(q->promedio, q->sgte->promedio);
                cambiado = true;
            }
            q = q->sgte;
        }
    } while (cambiado);
}



void toUpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);  
    }
}