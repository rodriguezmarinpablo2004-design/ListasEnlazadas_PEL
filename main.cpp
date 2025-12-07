#include <iostream>
#include <string>
#include <vector>
#include "Usuario.h"
#include "Contacto.h"

using namespace std;

vector<Usuario> usuariosGlobal;

/*-------------------------------------------------------------------------
 *---------------------- Menu Principal de Contactos ----------------------
 ------------------------------------------------------------------------*/
void mostrarMenuContacto(Usuario& usuarioActual) {
    // Variables multi-caso
    int opcion = 0;
    string nombre, telefono, descripcion, usernameBusqueda;
    int edad;

    do {
        cout << "Bienvenido, " << usuarioActual.getUsername() << endl;
        cout << "1. Ver mis contactos" << endl;
        cout << "2. Crear nuevo contacto" << endl;
        cout << "3. Buscar contacto por telefono" << endl;
        cout << "4. Modificar contacto" << endl;
        cout << "5. Eliminar contacto" << endl;
        cout << "6. Importar contactos de otro usuario" << endl;
        cout << "-1. Cerrar Sesion" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Ingrese una opcion valida." << endl;
            cin.clear();
            continue;
        }

        switch (opcion) {
            case 1:
                usuarioActual.verContactos();
                break;
            case 2:
                {
                    cout << "--- Crear Contacto ---" << endl;
                    cout << "Nombre: "; cin.ignore(); getline(cin, nombre);
                    cout << "Telefono (identificador): "; getline(cin, telefono);
                    cout << "Edad: ";
                    if (!(cin >> edad)) {
                        cout << "Ingrese un numero valido." << endl;
                        cin.clear();
                        break;
                    }
                    cin.ignore();
                    cout << "Descripcion: "; getline(cin, descripcion);
                    usuarioActual.crearContacto(nombre, telefono, edad, descripcion);
                }
                break;
            case 3:
                cout << "--- Buscar Contacto ---" << endl;
                cout << "Telefono a buscar: "; cin.ignore(); getline(cin, telefono);
                usuarioActual.buscarContacto(telefono);
                break;
            case 4:
                {
                    cout << "--- Modificar Contacto ---" << endl;
                    cout << "Telefono del contacto a modificar: "; cin.ignore(); getline(cin, telefono);

                    Contacto buscado("", telefono, 0, "");
                    Contacto* encontrado = usuarioActual.getListaContactos().buscarPuntero(buscado);

                    if (encontrado != nullptr) {
                        cout << "Contacto actual: "; encontrado->mostrar(); cout << endl;

                        // Nuevo nombre
                        cout << "Nuevo Nombre (dejar vacio para no modificar): "; getline(cin, nombre);
                        string nuevoNombre = encontrado->getNombre();
                        if (!nombre.empty()) {
                            nuevoNombre = nombre;
                        }

                        // Nueva edad
                        cout << "Nueva Edad (ingrese -1 para no modificar): ";
                        int edadTemp;
                        if (!(cin >> edadTemp)) {
                            cout << "Error: Edad invalida. Debe ser un numero." << endl;
                            cin.clear();
                            break;
                        }
                        cin.ignore();

                        int nuevaEdad;
                        if (edadTemp != -1) {
                            nuevaEdad = edadTemp;
                        } else {
                            // Mantener edad
                            nuevaEdad = encontrado->getEdad();
                        }

                        // Nueva descripcion
                        cout << "Nueva Descripcion (dejar vacio para no modificar): "; getline(cin, descripcion);
                        string nuevaDesc = encontrado->getDescripcion();
                        if (!descripcion.empty()) {
                            nuevaDesc = descripcion;
                        }

                        // Modificacion final
                        usuarioActual.modificarContacto(telefono, nuevoNombre, nuevaEdad, nuevaDesc);
                    } else {
                        cout << "Error: No se encontró el contacto con telefono " << telefono << endl;
                    }
                }
                break;
            case 5:
                cout << "--- Eliminar Contacto ---" << endl;
                cout << "Telefono del contacto a eliminar: "; cin.ignore(); getline(cin, telefono);
                usuarioActual.eliminarContacto(telefono);
                break;
            case 6:
                {
                    cout << "--- Importar Contactos ---" << endl;
                    cout << "Nombre de usuario del que desea importar: "; cin.ignore(); getline(cin, usernameBusqueda);

                    if (usernameBusqueda == usuarioActual.getUsername()) {
                        cout << "Error: No puede importar contactos de si mismo." << endl;
                        break;
                    }

                    Usuario* otroUsuario = nullptr;
                    for (size_t i = 0; i < usuariosGlobal.size(); ++i) {
                        if (usuariosGlobal[i].getUsername() == usernameBusqueda) {
                            otroUsuario = &usuariosGlobal[i];
                            break;
                        }
                    }

                    if (otroUsuario != nullptr) {
                        usuarioActual.importarContactosDe(*otroUsuario);
                    } else {
                        cout << "Error: El usuario " << usernameBusqueda << " no existe." << endl;
                    }
                }
                break;

            case -1:
                cout << "Cerrando sesion." << endl;
                break;

            default:
                cout << "Ingrese una opcion valida" << endl;
                break;
        }
    } while (opcion != -1);
}

// --- Menú Principal ---
void menuPrincipal() {
    int opcion = 0;
    string username, password;

    do {
        cout << "----------  Contactos Tinder  ----------" << endl;
        cout << "1. Iniciar Sesion" << endl;
        cout << "-1. Salir" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Ingrese una opcion valida." << endl;
            cin.clear();
            continue;
        }

        switch (opcion) {
            case 1:
                {
                    cin.ignore();
                    cout << "--- Iniciar Sesion ---" << endl;
                    cout << "Usuario: "; getline(cin, username);
                    cout << "Contrasena: "; getline(cin, password);

                    Usuario* usuarioLogeado = nullptr;
                    for (size_t i = 0; i < usuariosGlobal.size(); ++i) {
                        if (usuariosGlobal[i].getUsername() == username && usuariosGlobal[i].getPassword() == password) {
                            usuarioLogeado = &usuariosGlobal[i];
                            break;
                        }
                    }
                    if (usuarioLogeado != nullptr) {
                        cout << "\nInicio de sesion exitoso." << endl;
                        mostrarMenuContacto(*usuarioLogeado);
                    } else {
                        cout << "\nCredenciales invalidas o usuario no encontrado." << endl;
                    }
                }
                break;
            case -1:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Ingrese una opcion valida." << endl;
                break;
        }
    } while (opcion != -1);
}

void inicializarDatos() {
    usuariosGlobal.push_back(Usuario("pablo", "1234"));
    usuariosGlobal.push_back(Usuario("maria", "5678"));
    usuariosGlobal.push_back(Usuario("martin", "9012"));

    // Carga de contactos
    // (5)
    usuariosGlobal[0].crearContacto("Maria Lopez", "600111222", 30, "Trabajo");
    usuariosGlobal[0].crearContacto("Jose Perez", "600333444", 45, "Amigo");
    usuariosGlobal[0].crearContacto("Hermana", "650555666", 25, "Familiar");
    usuariosGlobal[0].crearContacto("Doctor", "910777888", 50, "Cita");
    usuariosGlobal[0].crearContacto("Vecino", "600999000", 38, "Edificio");

    // (7, tiene duplicados)
    usuariosGlobal[1].crearContacto("Laura Gomez", "610111222", 22, "Universidad");
    usuariosGlobal[1].crearContacto("David Sanz", "610333444", 33, "Colega");
    usuariosGlobal[1].crearContacto("Mama", "650555666", 60, "Familiar");
    usuariosGlobal[1].crearContacto("Electricista", "910777888", 40, "Casa");
    usuariosGlobal[1].crearContacto("Javier", "610999000", 28, "Gym");
    usuariosGlobal[1].crearContacto("Taller", "611111222", 55, "Coche");
    usuariosGlobal[1].crearContacto("Fotografo", "611333444", 30, "Boda");

    // (6)
    usuariosGlobal[2].crearContacto("Elena Ruiz", "620111222", 27, "Amiga");
    usuariosGlobal[2].crearContacto("Profesor", "620333444", 58, "Academico");
    usuariosGlobal[2].crearContacto("Hermano", "620555666", 35, "Familiar");
    usuariosGlobal[2].crearContacto("Tienda", "620777888", 42, "Compras");
    usuariosGlobal[2].crearContacto("Mecanico", "620999000", 50, "Reparacion");
    usuariosGlobal[2].crearContacto("Cliente A", "621111222", 31, "Negocio");

    cout << "Usuarios cargados: pablo(1234), maria(5678), martin(9012)" << endl;
}

int main() {
    inicializarDatos();
    menuPrincipal();
    return 0;
}