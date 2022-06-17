#include "Libreria.h"
#include <stdio.h>
#include <stdlib.h>
#define __PRECIO_POR_KW_PARTICULAR__ 10
#define __PRECIO_POR_KW_COMERCIAL__ 15
#define __MINIMO_PARTICULAR__ 10
#define __MINIMO_COMERCIAL__ 25

TablaZonas *crearTablaZonas(){
    TablaZonas *tabla = (TablaZonas*) malloc(sizeof (TablaZonas));

    if(tabla == NULL){
        printf("No hay memoria libre.");
        exit(-1);
    }

    tabla->tam = 0;
    tabla->primera = 0;

    return tabla;
}

ListaUsuarios *crearListaUsuarios(int zona) {
    ListaUsuarios *lista = (ListaUsuarios*) malloc(sizeof (ListaUsuarios));

    if(lista == NULL){
        printf("No hay memoria libre.");
        exit(-1);
    }

    lista->tam = 0;
    lista->zona = zona;
    lista->lista = NULL;
    lista->siguienteZona = NULL;

    return lista;
}

void agregarListaZona(TablaZonas *tabla, ListaUsuarios *lista){
    ListaUsuarios *aux = tabla->primera;

    if(aux == NULL){
        tabla->primera = lista;
        return;
    }

    for (; aux->siguienteZona != NULL; aux = aux->siguienteZona){}

    aux->siguienteZona = lista;
}


Usuario *crearUsuario(int zona, char *nombre, char *calle, char tipoUsuario, int numero) {
    if(zona <= 0){
        printf("El número de zona debería ser mayor a 0.\n");
        return NULL;
    }

    Usuario *nuevo = (Usuario*) malloc(sizeof (Usuario));

    if(nuevo == NULL){
        printf("No hay memoria libre.");
        exit(-1);
    }

    nuevo->zona = zona;
    nuevo->nombre = nombre;
    nuevo->calle = calle;
    nuevo->tipoUsuario = tipoUsuario;
    nuevo->numero = numero;
    nuevo->siguiente = NULL;

    return nuevo;
}

void aumentarConsumo(Usuario *usuario, int valor) {
    usuario->consumo += valor;

    if(usuario->tipoUsuario == 'P'){

        if(usuario->consumo < __MINIMO_PARTICULAR__){
            usuario->importe = __MINIMO_PARTICULAR__ * __PRECIO_POR_KW_PARTICULAR__;
            return; // Si el consumo es menor al mínimo, se cobra el mínimo.
        }
        usuario->importe = (float) usuario->consumo * __PRECIO_POR_KW_PARTICULAR__;

    }else{

        if(usuario->consumo < __MINIMO_COMERCIAL__){
            usuario->importe = __MINIMO_COMERCIAL__ * __PRECIO_POR_KW_COMERCIAL__;
            return; // Si el consumo es menor al mínimo, se cobra el mínimo.
        }
        usuario->importe = (float) usuario->consumo * __PRECIO_POR_KW_COMERCIAL__;

    }
}

void agregarAZona(ListaUsuarios *listaZona, Usuario *nuevo){
    Usuario *aux = listaZona->lista;

    if(aux == NULL){
        listaZona->lista = nuevo;
        return;
    }

    for (; aux->siguiente != NULL; aux = aux->siguiente){}

    aux->siguiente = nuevo;
}

void insertarUsuario(TablaZonas *tabla, Usuario *nuevo) {
    ListaUsuarios *aux = tabla->primera;

    for (; aux != NULL; aux = aux->siguienteZona){
        if(aux->zona == nuevo->zona){
            agregarAZona(aux, nuevo);
            return;
        }
    }

    //Si llega hasta aca es porque no encontró la zona, por lo que la tengo que crear.
    ListaUsuarios *lista = crearListaUsuarios(nuevo->zona);

    agregarAZona(lista, nuevo);
    agregarListaZona(tabla, lista);
}

void mostrarTodo(TablaZonas *tabla) {
    ListaUsuarios *aux = tabla->primera;

    printf("- Todos los datos -\n");

    if(aux == NULL){
        printf("La tabla esta vacía.\n");
        return;
    }

    for (; aux != NULL; aux = aux->siguienteZona){
        printf("\n-- Zona %d:\n", aux->zona);
        Usuario *usuActual = aux->lista;

        if(usuActual == NULL){
            printf("Zona sin usuarios.\n");
        }else{
            for (; usuActual != NULL; usuActual = usuActual->siguiente){
                printf("* Nombre: %s - Calle: %s - Tipo usuario: %c - Consumo: %.2f kW - Importe: $%.2f - Numero cliente: %d\n",
                       usuActual->nombre,
                       usuActual->calle,
                       usuActual->tipoUsuario,
                       usuActual->consumo,
                       usuActual->importe,
                       usuActual->numero);
            }
        }

    }

    printf("\n\n");
}

void mostrarUsuariosQueSuperanMinimo(TablaZonas *tabla) {
    ListaUsuarios *aux = tabla->primera;

    printf("\n- Usuarios que superan el mínimo por zona -\n");

    if(aux == NULL){
        printf("La tabla esta vacía.\n");
        return;
    }

    for (; aux != NULL; aux = aux->siguienteZona){
        printf("-- Zona %d:\n", aux->zona);
        Usuario *usuActual = aux->lista;

        if(usuActual == NULL){
            printf("Zona sin usuarios.\n");
        }else{
            for (; usuActual != NULL; usuActual = usuActual->siguiente){
                if((usuActual->tipoUsuario == 'C' && usuActual->consumo > __MINIMO_COMERCIAL__)
                || (usuActual->tipoUsuario == 'P' && usuActual->consumo > __MINIMO_PARTICULAR__)){
                    printf("* Nombre: %s - Calle: %s - Tipo usuario: %c - Consumo: %.2f kW - Importe: $%.2f - Numero cliente: %d\n",
                           usuActual->nombre,
                           usuActual->calle,
                           usuActual->tipoUsuario,
                           usuActual->consumo,
                           usuActual->importe,
                           usuActual->numero);
                }
            }
        }

    }
}

void mostrarConsumoPromedioPorZona(TablaZonas *tabla) {
    ListaUsuarios *aux = tabla->primera;

    printf("\n- Consumo promedio de los usuarios particulares por zona -\n");

    if(aux == NULL){
        printf("La tabla esta vacía.\n");
        return;
    }

    for (; aux != NULL; aux = aux->siguienteZona){
        printf("-- Zona %d:\n", aux->zona);
        Usuario *usuActual = aux->lista;
        float suma = 0;
        int cont = 0;

        if(usuActual == NULL){
            printf("Zona sin usuarios.\n");
        }else{
            for (; usuActual != NULL; usuActual = usuActual->siguiente){
                if(usuActual->tipoUsuario == 'P'){
                    suma += usuActual->consumo;
                    cont++;
                }
            }

            printf("Promedio consumo de los usuarios particulares: %.2f\n", suma/cont);
        }

    }
}

void mostrarMaximoComercialPorZona(TablaZonas *tabla) {
    ListaUsuarios *aux = tabla->primera;

    printf("\n- Usuario comercial con más consumo por zona -\n");

    if(aux == NULL){
        printf("La tabla esta vacía.\n");
        return;
    }

    for (; aux != NULL; aux = aux->siguienteZona){
        printf("-- Zona %d:\n", aux->zona);
        Usuario *usuActual = aux->lista;
        Usuario *mayor = NULL;

        if(usuActual == NULL){
            printf("Zona sin usuarios.\n");
        }else{

            for (; usuActual != NULL; usuActual = usuActual->siguiente){
                if(usuActual->tipoUsuario == 'C'){
                    if(mayor == NULL){
                        mayor = usuActual;
                    }else if(usuActual->consumo > mayor->consumo){
                        mayor = usuActual;
                    }
                }
            }

            if(mayor == NULL){
                printf("No hay usuarios comerciales en esta zona.\n");
            }else {
                printf("El usuario comercial que más consumió esta en la dirección %s. El nombre es %s.\n", mayor->calle, mayor->nombre);
            }

        }

    }

}

void mostrarCantidadUsuariosPorCategoria(TablaZonas *tabla) {
    ListaUsuarios *aux = tabla->primera;

    printf("\n- Cantidad de usuarios por categoria en cada zona -\n");

    if(aux == NULL){
        printf("La tabla esta vacía.\n");
        return;
    }

    for (; aux != NULL; aux = aux->siguienteZona){
        printf("-- Zona %d:\n", aux->zona);
        Usuario *usuActual = aux->lista;
        int contParticulares = 0, contComerciales = 0;

        if(usuActual == NULL){
            printf("Zona sin usuarios.\n");
        }else{
            for (; usuActual != NULL; usuActual = usuActual->siguiente){
                if(usuActual->tipoUsuario == 'C'){
                    contComerciales++;
                }else {
                    contParticulares++;
                }
            }

            printf("Usuarios comerciales: %d\n", contComerciales);
            printf("Usuarios particulares: %d\n", contParticulares);

        }

    }

}

void mostrarTotalFacturadoPorZona(TablaZonas *tabla) {
    ListaUsuarios *aux = tabla->primera;

    printf("\n- Total facturado por zona -\n");

    if(aux == NULL){
        printf("La tabla esta vacía.\n");
        return;
    }

    for (; aux != NULL; aux = aux->siguienteZona){
        printf("-- Zona %d:\n", aux->zona);
        Usuario *usuActual = aux->lista;
        float suma = 0;

        if(usuActual == NULL){
            printf("Zona sin usuarios.\n");
        }else{
            for (; usuActual != NULL; usuActual = usuActual->siguiente){
                suma += usuActual->importe;
            }

            printf("El total facturado en la zona es de %.2f.\n", suma);

        }

    }
}





