#include "Usuario.h"

int main() {
    // 1. Carga Inicial (Simulación de Base de Datos)
    Usuario user1("Pablo", "1234");
    Usuario user2("Maria", "abcd");

    // Llenamos User 1 (5 contactos)
    user1.crearContacto("Ana", "600111222", 25, "Amiga");
    user1.crearContacto("Luis", "600333444", 30, "Trabajo");
    user1.crearContacto("Pepe", "600555666", 22, "Gym");
    user1.crearContacto("Sara", "600777888", 28, "Uni");
    user1.crearContacto("Javi", "600999000", 24, "Vecino");

    // Llenamos User 2 (Algunos repetidos para probar TU filtro)
    user2.crearContacto("Ana", "600111222", 25, "Amiga de Pablo"); // REPETIDO
    user2.crearContacto("Carlos", "700111222", 40, "Jefe");         // NUEVO
    user2.crearContacto("Luis", "600333444", 30, "Compañero");      // REPETIDO

    cout << "\n--- ESTADO INICIAL ---" << endl;
    user1.verContactos();
    user2.verContactos();

    // 2. Probar lógica de Importación y Filtrado
    // Pablo importa los contactos de Maria
    user1.importarContactosDe(user2);

    cout << "\n--- DESPUES DE IMPORTAR ---" << endl;
    user1.verContactos();
    // Debería tener 5 originales + 1 nuevo (Carlos).
    // Ana y Luis no deberían duplicarse.

    return 0;
}