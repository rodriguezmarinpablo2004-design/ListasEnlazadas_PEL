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
    Contacto(string n, string t, int e, string d) : nombre(n), telefono(t), edad(e), descripcion(d) {}

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

    void mostrar() const {
        cout << "[" << nombre
             << " | Telefono: " << telefono
             << " | " << edad << " años"
             << " | Descripcion: " << descripcion << "]";
    }

};

#endif //CONTACTO_H
