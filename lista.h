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

typedef struct iter lista_iter_t;

typedef struct nodo nodo_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

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

void *lista_ver_ultimo(const lista_t* lista);
size_t lista_largo(const lista_t *lista);
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

lista_iter_t *lista_iter_crear(lista_t *lista);
bool lista_iter_avanzar(lista_iter_t *iter);
void *lista_iter_ver_actual(const lista_iter_t *iter);
bool lista_iter_al_final(const lista_iter_t *iter);
void lista_iter_destruir(lista_iter_t *iter);
bool lista_iter_insertar(lista_iter_t *iter, void *dato);
void *lista_iter_borrar(lista_iter_t *iter);

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);

#endif
