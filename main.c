#include <stdio.h>
#include "Libreria.h"

int main() {

    TablaZonas *tabla = crearTablaZonas();

    Usuario *usuario1 = crearUsuario(1, "Usuario 1", "Av Cabildo", 'P', 123);
    Usuario *usuario2 = crearUsuario(2, "Usuario 2", "Av Santa Fe", 'P', 234);
    Usuario *usuario3 = crearUsuario(1, "Usuario 3", "Jorge Newbery", 'C', 345);
    Usuario *usuario4 = crearUsuario(3, "Usuario 4", "Santos Dumont", 'C', 456);
    Usuario *usuario5 = crearUsuario(3, "Usuario 5", "Av Cabildo", 'P', 567);

    aumentarConsumo(usuario1, 90);
    aumentarConsumo(usuario2, 20);
    aumentarConsumo(usuario3, 4);
    aumentarConsumo(usuario4, 100);
    aumentarConsumo(usuario5, 7);
    //Los usuarios que superan el mínimo son el 1, 2 y 4

    insertarUsuario(tabla, usuario1);
    insertarUsuario(tabla, usuario2);
    insertarUsuario(tabla, usuario3);
    insertarUsuario(tabla, usuario4);
    insertarUsuario(tabla, usuario5);

    mostrarTodo(tabla);

    printf("- Consignas pedidas: -\n");
    mostrarUsuariosQueSuperanMinimo(tabla);
    mostrarConsumoPromedioPorZona(tabla);
    mostrarMaximoComercialPorZona(tabla);
    mostrarCantidadUsuariosPorCategoria(tabla);
    mostrarTotalFacturadoPorZona(tabla);


    return 0;
}
