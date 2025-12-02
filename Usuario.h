//
// Created by Mahsa on 02/12/2025.
//

#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include "ListaEnlazada.h"
#include "Contacto.h"

using namespace std;

class Usuario {
private:
    string username;
    string password;
    ListaEnlazada<Contacto> misContactos; // Lista enlazada de contactos

public:
    Usuario(string user, string pass) : username(user), password(pass) {}

    // --- GETTERS ---
    string getUsername() const
    {
        return username;
    }

    string getPassword() const
    {
        return password;
    }


    // --- CRUD ---

    // 1. Crear un nuevo contacto
    void crearContacto(string nombre, string telefono, int edad, string desc) {
        Contacto nuevo(nombre, telefono, edad, desc);
        if (misContactos.buscar(nuevo)) {
            cout << "Error: El contacto con telefono " << telefono << " ya existe." << endl;
        } else {
            misContactos.agregar(nuevo);
            cout << "Contacto creado exitosamente." << endl;
        }
    }

    // 2. Modificar información de un contacto existente
    void modificarContacto(string telefono, string nuevoNombre, int nuevaEdad, string nuevaDesc) {
        Contacto buscado("", telefono, 0, "");
        Contacto* encontrado = misContactos.buscar(buscado); // Asumimos que buscar devuelve puntero o nullptr
        if (encontrado) {
            encontrado->setNombre(nuevoNombre);
            encontrado->setEdad(nuevaEdad);
            encontrado->setDescripcion(nuevaDesc);
            cout << "Contacto modificado exitosamente." << endl;
        } else {
            cout << "Error: No se encontró el contacto con telefono " << telefono << endl;
        }
    }

    // 3. Eliminar un contacto de su lista
    void eliminarContacto(string telefono) {
        Contacto aEliminar("", telefono, 0, "");
        if (misContactos.eliminar(aEliminar)) { // Asumimos que eliminar devuelve bool
            cout << "Contacto eliminado exitosamente." << endl;
        } else {
            cout << "Error: No se encontró el contacto con telefono " << telefono << endl;
        }
    }

    // 4. Buscar un contacto
    void buscarContacto(string telefono) {
        Contacto buscado("", telefono, 0, "");
        Contacto* encontrado = misContactos.buscar(buscado);
        if (encontrado) {
            cout << "Contacto encontrado: " << *encontrado << endl;
        } else {
            cout << "No se encontró el contacto con telefono " << telefono << endl;
        }
    }

    // --- Ver contactos ---
    void verContactos() {
        cout << "--- Contactos de " << username << " ---" << endl;
        misContactos.imprimir();
    }

    ListaEnlazada<Contacto>& getListaContactos() {
        return misContactos;
    }
};

#endif //USUARIO_H
