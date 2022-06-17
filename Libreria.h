#ifndef INC_8_1_HERRERAOCAMPOMARTIN_LIBRERIA_H
#define INC_8_1_HERRERAOCAMPOMARTIN_LIBRERIA_H

typedef struct usuario {
    int zona;
    char *nombre;
    char *calle;
    int numero;
    char tipoUsuario;
    float consumo;
    float importe;
    struct usuario *siguiente;
} Usuario;

typedef struct listaUsuarios {
    Usuario *lista;
    int tam;
    int zona;
    struct listaUsuarios *siguienteZona;
} ListaUsuarios;

typedef struct tablaZonas {
    ListaUsuarios *primera;
    int tam;
} TablaZonas;

TablaZonas *crearTablaZonas();
ListaUsuarios *crearListaUsuarios(int zona);
Usuario *crearUsuario(int zona, char *nombre, char *calle, char tipoUsuario, int numero);
void aumentarConsumo(Usuario *usuario, int valor);
void agregarListaZona(TablaZonas *tabla, ListaUsuarios *lista);
void agregarAZona(ListaUsuarios *listaZona, Usuario *nuevo);
void insertarUsuario(TablaZonas *tabla, Usuario *nuevo);
void mostrarTodo(TablaZonas *tabla);
void mostrarUsuariosQueSuperanMinimo(TablaZonas *tabla);
void mostrarConsumoPromedioPorZona(TablaZonas *tabla);
void mostrarMaximoComercialPorZona(TablaZonas *tabla);
void mostrarCantidadUsuariosPorCategoria(TablaZonas *tabla);
void mostrarTotalFacturadoPorZona(TablaZonas *tabla);


#endif //INC_8_1_HERRERAOCAMPOMARTIN_LIBRERIA_H
