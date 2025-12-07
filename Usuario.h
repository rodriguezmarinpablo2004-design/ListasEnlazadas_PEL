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
    Usuario(): username(""), password("") {}
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

    void changeUsername (string nuevoUsername) {
        username = nuevoUsername;
    }

    void changePassword (string nuevaPassword) {
        password = nuevaPassword;
    }

    // --- FUNCIONES AUXILIARES ---
    // Verifica si un teléfono ya existe en la lista para mantener la integridad
    bool esDuplicado(string telefono) {
        Contacto temporal("", telefono, 0, "");
        return misContactos.existe(temporal);
    }

    // --- CRUD ---

    // 1. Crear un nuevo contacto
    void crearContacto(string nombre, string telefono, int edad, string desc) {
        // Validación A: Datos lógicos (Tu responsabilidad)
        if (edad < 0) {
            cout << "Error: Edad invalida (negativa)." << endl;
            return;
        }

        // Validación B: Detección de duplicados (Tu responsabilidad)
        if (esDuplicado(telefono)) {
            cout << "Error: El contacto con telefono " << telefono << " ya existe." << endl;
        } else {
            // Si pasa las validaciones, creamos y agregamos
            Contacto nuevo(nombre, telefono, edad, desc);
            misContactos.agregar(nuevo);
            cout << "Contacto creado exitosamente." << endl;
        }
    }

    // 2. Modificar información de un contacto existente
    void modificarContacto(string telefono, string nuevoNombre, int nuevaEdad, string nuevaDesc) {
        Contacto buscado("", telefono, 0, "");

        // Usamos buscarPuntero para obtener el objeto real en memoria
        Contacto* encontrado = misContactos.buscarPuntero(buscado);

        if (encontrado != nullptr) {
            encontrado->setNombre(nuevoNombre);
            encontrado->setEdad(nuevaEdad); // El setter interno también valida negativos
            encontrado->setDescripcion(nuevaDesc);
            cout << "Contacto modificado exitosamente." << endl;
        } else {
            cout << "Error: No se encontró el contacto con telefono " << telefono << endl;
        }
    }

    // 3. Eliminar un contacto de su lista
    void eliminarContacto(string telefono) {
        Contacto aEliminar("", telefono, 0, "");

        // Utilizamos el eliminar que devuelve bool para confirmar la acción
        if (misContactos.eliminar(aEliminar)) {
            cout << "Contacto eliminado exitosamente." << endl;
        } else {
            cout << "Error: No se encontró el contacto con telefono " << telefono << endl;
        }
    }

    // 4. Buscar un contacto
    void buscarContacto(string telefono) {
        Contacto buscado("", telefono, 0, "");

        // Usamos buscarPuntero para verificar existencia y mostrar
        Contacto* encontrado = misContactos.buscarPuntero(buscado);

        if (encontrado != nullptr) {
            // Gracias a la sobrecarga de << en Contacto.h, podemos imprimir punteros dereferenciados
            cout << "Contacto encontrado: " << *encontrado << endl;
            encontrado->mostrar(); // Muestra detalles completos
            cout << endl;
        } else {
            cout << "No se encontró el contacto con telefono " << telefono << endl;
        }
    }

    // --- FUNCIONALIDADES AVANZADAS  ---

    // Importar contactos de otro usuario con FILTRADO DE DUPLICADOS
    void importarContactosDe(Usuario& otroUsuario) {
        cout << "\n--- Iniciando Importacion de contactos de " << otroUsuario.getUsername() << " a " << this->username << " ---" << endl;

        ListaEnlazada<Contacto>& listaExterna = otroUsuario.getListaContactos();
        int cantidadImportar = listaExterna.obtenerTamano();
        int importados = 0;
        int omitidos = 0;

        for (int i = 0; i < cantidadImportar; i++) {
            Contacto c = listaExterna.obtenerPorIndice(i);

            // Lógica de filtrado: Solo importamos si NO existe ya en mi lista
            if (!misContactos.existe(c)) {
                misContactos.agregar(c);
                importados++;
            } else {
                omitidos++; // Se ignora para evitar duplicados
            }
        }

        cout << "Resumen Importacion:" << endl;
        cout << " -> Nuevos contactos agregados: " << importados << endl;
        cout << " -> Contactos omitidos (ya existian): " << omitidos << endl;
        cout << "--------------------------------------------------\n" << endl;
    }

    // --- Ver contactos ---
    void verContactos() {
        cout << "--- Contactos de " << username << " (" << misContactos.obtenerTamano() << ") ---" << endl;
        misContactos.imprimir();
    }

    // Necesario para que otros usuarios puedan acceder a la lista al importar
    ListaEnlazada<Contacto>& getListaContactos() {
        return misContactos;
    }
};

#endif //USUARIO_H