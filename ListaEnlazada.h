//
// Created by pablo on 02/12/2025.
//

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
#include <iostream>
#include <stdexcept>
template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;

    // Constructor del nodo
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

// Clase ListaEnlazada (Templatizada)
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza; // Puntero al primer elemento
    int tamano;      // Contador de elementos para acceso rápido al tamaño

public:
    // Constructor
    ListaEnlazada() : cabeza(nullptr), tamano(0) {}

    // Destructor
    ~ListaEnlazada() {
        limpiarMemoria();
    }


    // Agregar (al final de la lista)
    void agregar(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);

        // Si la lista está vacía, el nuevo nodo es la cabeza
        if (estaVacia()) {
            cabeza = nuevoNodo;
        } else {
            // Recorremos hasta el último nodo
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        tamano++;
    }

    // Eliminar (la primera ocurrencia del valor)
    void eliminar(T valor) {
        if (estaVacia()) return;

        // el valor está en la cabeza
        if (cabeza->dato == valor) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            tamano--;
            return;
        }

        // Buscamos el nodo previo al que queremos eliminar
        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->dato != valor) {
            actual = actual->siguiente;
        }

        // Si encontramos el nodo
        if (actual->siguiente != nullptr) {
            Nodo<T>* aEliminar = actual->siguiente;
            actual->siguiente = aEliminar->siguiente; // Saltamos el nodo
            delete aEliminar; // Liberamos memoria
            tamano--;
        }
    }

    // Buscar
    T buscar(T valor) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == valor) {
                return actual->dato;
            }
            actual = actual->siguiente;
        }

        // En lugar de devolver un dato falso, lanzamos una excepción con el mensaje
        throw std::runtime_error("Error: El elemento no existe en la lista.");
    }

    // Obtener Tamaño
    int obtenerTamano() const {
        return tamano;
    }

    // Esta Vacía
    bool estaVacia() const {
        return cabeza == nullptr;
    }

    // Acceder por Índice
    T obtenerPorIndice(int indice) const {
        if (indice < 0 || indice >= tamano) {
            throw std::out_of_range("Índice fuera de rango");
        }

        Nodo<T>* actual = cabeza;
        for (int i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }

    // Metodo auxiliar para imprimir la lista
    void imprimir() const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            std::cout << actual->dato << " -> ";
            actual = actual->siguiente;
        }
        std::cout << "nullptr" << std::endl;
    }

private:
    // Metodo privado para liberar toda la memoria
    void limpiarMemoria() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual; // Elimina el nodo actual
            actual = siguiente; // Avanza al siguiente
        }
        cabeza = nullptr;
        tamano = 0;
    }
};
#endif //LISTAENLAZADA_H
