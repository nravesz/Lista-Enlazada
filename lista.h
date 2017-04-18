#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista enlazada de punteros genéricos. */


typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;

typedef struct nodo nodo_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al inicio de la lista con el valor dado. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista con el valor dado. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Elimina el primer elemento de la lista. Si la lista tiene elementos, se elimina el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene un
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t* lista);

// Obtiene el valor de la cantidad de elementos de una lista.
// Pre: la lista fue creada.
// Post: se devolvio el valor de la cantidad de elementos de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista y la lista fue destruida.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/* ******************************************************************
 *                    PRIMITIVAS DEl ITERADOR
 * *****************************************************************/


// Crea un iterador. Debe recibir una lista por parametro.
// Pre: la lista fue creada.
// Post: devuelve un iterador cuya posicion actual es el primer elemento de la lista.
lista_iter_t* lista_iter_crear(lista_t *lista);

// Avanza una posicion en la lista. Si el iterador llega al final devuelve falso;
// en caso contrario devuelve verdadero.
// Pre: el iterador fue creado.
// Post: se avanzo un elemento en la lista, en cuanto esta operacion sea valida.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del elemento actual en el que se encuentra el iterador.
// Si la lista se encuentra vacia o el iterador se halla al final, devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvio el elemento actual de la lista, en cuando no se halle vacia o al final.
void* lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero o falso, segun si el iterador se halla o no al final de la lista.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: el iterador fue destruido.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento recibido por parametro en la posicion actual del iterador. En caso de
// ser una operacion valida devuelve verdadero, en el caso contrario falso.
// Pre: el iterador fue creado.
// Post: el elemento fue insertado en la posicion actual del iterador, en caso de ser una operacion
// valida. El iterador se mantiene en esa posicion.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina el elemento en la posicion actual del iterador. Devuelve el valor del
// elemento actual.
// Pre: el iterador fue creado.
// Post: el que era antes el elemento actual fue eliminado. El iterador ahora apunta a la posicion
// siguiente.
void* lista_iter_borrar(lista_iter_t *iter);

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);

#endif
