//
// Created by Mahsa on 02/12/2025.
//

#ifndef CONTACTO_H
#define CONTACTO_H

#include <iostream>
#include <string>

using namespace std;

class Contacto {
private:
    string nombre;
    string telefono; // Usamos string porque el telefono puede tener simbolos (+) o ceros a la izquierda
    int edad;
    string descripcion;

public:
    // Constructor por defecto (necesario para crear arrays o nodos vacíos temporalmente)
    Contacto() : nombre(""), telefono(""), edad(0), descripcion("") {}

    // Constructor Parametrizado
    // Modificado esto para incluir validación de edad desde el inicio
    Contacto(string n, string t, int e, string d) : nombre(n), telefono(t), descripcion(d) {
        if (e < 0) {
            cout << "Advertencia: Se intento crear un contacto con edad negativa (" << e << "). Se ajusta a 0." << endl;
            edad = 0;
        } else {
            edad = e;
        }
    }

    // --- GETTERS ---
    std::string getNombre() const
    {
        return nombre;
    }

    std::string getTelefono() const
    {
        return telefono;
    }

    int getEdad() const
    {
        return edad;
    }

    std::string getDescripcion() const
    {
        return descripcion;
    }

    // --- SETTERS ---
    void setNombre(const std::string& n)
    {
        nombre = n;
    }

    void setTelefono(const std::string& t)
    {
        telefono = t;
    }

    void setEdad(int e)
    {
        if (e >= 0) {
            edad = e; // Validación básica: no permitir edades negativas
        } else {
            cout << "Error: No se puede asignar una edad negativa." << endl;
        }
    }

    void setDescripcion(const std::string& d)
    {
        descripcion = d;
    }

    // Esto es lo que permite que lista.buscar(contacto) funcione.
    // Comparamos por TELEFONO porque es el identificador único (dos 'Juan' pueden existir, dos números iguales no).
    bool operator==(const Contacto& otro) const
    {
        return this->telefono == otro.telefono;
    }

    // Metodo original para mostrar datos
    void mostrar() const {
        cout << "[" << nombre
             << " | Telefono: " << telefono
             << " | " << edad << " años"
             << " | Descripcion: " << descripcion << "]";
    }

    // Sobrecarga del operador << para que la ListaEnlazada pueda imprimir directamente
    // sin tener que llamar a .mostrar() dentro de la plantilla.
    friend ostream& operator<<(ostream& os, const Contacto& c) {
        os << "[" << c.nombre << " | Tel: " << c.telefono << "]";
        return os;
    }
};

#endif //CONTACTO_H