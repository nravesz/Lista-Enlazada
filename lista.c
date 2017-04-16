#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Definición del struct nodo_t.*/
typedef struct nodo{
	void* dato;
	struct nodo* prox;
}nodo_t;

/* Definición del struct lista_t.*/
typedef struct lista{
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
}lista_t;

/* Definición del struct lista_t.*/
typedef struct iter{
	lista_t* lista;
	nodo_t* act;
	nodo_t* ant;
}lista_iter_t;

nodo_t* crear_nodo(){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL){
		return NULL;
	}
	nodo->dato = NULL;
	nodo->prox = NULL;
	return nodo;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA					   *
 * *****************************************************************/

lista_t *lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if (!lista) return NULL;
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo = crear_nodo();
	nodo->dato = dato;
	if (lista->largo == 0){
		lista->prim = nodo;
		lista->ult = nodo;
	}
	else{
		nodo_t* aux = lista->prim;
		lista->prim = nodo;
		nodo->prox = aux;
	}
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo = crear_nodo();
	nodo->dato = dato;
	if (lista->largo == 0){
		lista->prim = nodo;
		lista->ult = nodo;
	}
	else{
		(lista->ult)->prox = nodo;
		lista->ult = nodo;
	}
	lista->largo++;
	return true;
}

void* lista_borrar_primero(lista_t *lista){
	if (lista->largo == 0) return NULL;
	void* dato = (lista->prim)->dato;
	if (lista->largo == 1){
		free(lista->prim);
		lista->prim = NULL;
		lista->ult = NULL;
	}
	else{
		nodo_t* aux = (lista->prim)->prox;
		free(lista->prim);
		lista->prim = aux;
	}
	lista->largo--;
	return dato;
}

void* lista_ver_primero(const lista_t *lista){
	if (lista->largo == 0){
		return NULL;
	}
	return (lista->prim)->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if (lista->largo == 0){
		return NULL;
	}
	return (lista->ult)->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
	nodo_t* nodo = lista->prim;
	while(nodo){
		nodo_t* aux = nodo->prox;
		if (destruir_dato != NULL){
			destruir_dato(nodo->dato);
		}
		free(nodo);
		nodo = aux;
		lista->largo--;
	}
	free(lista);
}

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
	nodo_t* nodo = lista->prim;
	while(nodo && visitar(nodo->dato, &extra)){
		nodo = nodo->prox;
	}
	return;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA					   *
 * *****************************************************************/

lista_iter_t* lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (!iter){
		return NULL;
	}
	iter->lista = lista;
	iter->act = (iter->lista)->prim;
	iter->ant = NULL;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if (!iter->act){
		return false;
	}
	iter->ant = iter->act;
	iter->act = (iter->act)->prox;
	if (iter->ant){
		(iter->ant)->prox = iter->act;
	}
	return true;
}

void* lista_iter_ver_actual(const lista_iter_t *iter){
	if (!iter->act){
		return NULL;
	}
	void* dato = (iter->act)->dato;
	return dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return iter->act == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	nodo_t* nodo = crear_nodo();
	nodo->dato = dato;
	if (!nodo) return false;
	nodo->prox = iter->act;
	iter->act = nodo;
	if (iter->ant){
		(iter->ant)->prox = nodo;
	}
	else{
		iter->lista->prim = nodo;
	}
	if (!(iter->act)->prox){
		(iter->lista)->ult = nodo;
	}
	(iter->lista)->largo++;
	return true;
}

void* lista_iter_borrar(lista_iter_t *iter){
	if (!iter->act){
		return NULL;
	}
	void* dato = (iter->act)->dato;
	nodo_t* aux = (iter->act)->prox;
	free(iter->act);
	iter->act = aux;
	if (!iter->ant){
		(iter->lista)->prim = iter->act;
	}
	else if (iter->act && !(iter->act)->prox){
		(iter->ant)->prox = iter->act;
		(iter->lista)->ult = iter->act;
	}
	else{
		iter->ant->prox = iter->act;
	}
	(iter->lista)->largo--;
	return dato;
}
