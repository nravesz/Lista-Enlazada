#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimir_iter_externo(lista_t *lista)
{
    lista_iter_t *iter = lista_iter_crear(lista);

    while (!lista_iter_al_final(iter))
    {
        void* elemento = lista_iter_ver_actual(iter);
        printf("%d\n", *(int*)elemento);

        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

bool multiplicar_por_2(void* dato, void* extra){
	if (*(size_t*)extra%2 == 0){
		*(int*)dato = *(int*)dato*2;
	}
	*(size_t*)extra = *(size_t*)extra + 1; /*No funciona con *(size_t*)extra++. Error: value computed is not used*/
	return true;
}

bool imprimir_hasta_pos_3(void* dato, void* extra){
	if (*(size_t*)extra >= 3){
		return false;
	}
	*(size_t*)extra = *(size_t*)extra + 1;
	printf("%d\n", *(int*)dato);
	return true;
}

void pila_destruir_wrapped(void* pila){
	pila_destruir((pila_t*) pila);
}

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void crear_y_eliminar_lista(){
	printf("PRUEBA 1: Crear y eliminar una lista.\n");
	
	lista_t* lista1 = lista_crear();
	
    print_test("-La lista se creo vacia", lista_esta_vacia(lista1));
    print_test("-La lista tiene 0 elementos", lista_largo(lista1) == 0);
    print_test("-Ver el primer elemento de una lista vacia es NULL", lista_ver_primero(lista1) == NULL);
    print_test("-Ver el ultimo elemento de una lista vacia es NULL", lista_ver_ultimo(lista1) == NULL);
    lista_destruir(lista1, NULL);
    print_test("-La lista fue destruida", true);
    printf("\n");
}

void enlistar_elementos(){
	printf("PRUEBA 2: Enlistar y desenlistar elementos en una lista.\n");
	
	lista_t* lista2 = lista_crear();
	int a = 2;
	int b = 1;
	int c = 3;
	int d = 4;
	
    print_test("-La lista se creo vacia", lista_esta_vacia(lista2));
    print_test("-La lista tiene 0 elementos", lista_largo(lista2) == 0);
    print_test("-Enlisto un elemento en la primera posicion", lista_insertar_primero(lista2, &a));
    print_test("-Enlisto un elemento en la primera posicion", lista_insertar_primero(lista2, &b));
    print_test("-Enlisto un elemento en la ultima posicion", lista_insertar_ultimo(lista2, &c));
    print_test("-Enlisto un elemento en la ultima posicion", lista_insertar_ultimo(lista2, &d));
    print_test("-El primer elemento coincide con el valor", lista_ver_primero(lista2) == &b);
    print_test("-El ultimo elemento coincide con el valor", lista_ver_ultimo(lista2) == &d);
    print_test("-La lista tiene 4 elementos", lista_largo(lista2) == 4);
    
    while(!lista_esta_vacia(lista2)){
		lista_borrar_primero(lista2);
	}
    
    print_test("-Se desenlistaron todos los elementos", lista_esta_vacia(lista2));
    lista_destruir(lista2, NULL);
    print_test("-La lista fue destruida", true);
    printf("\n");
}

void iter_lista_insertar(){
	printf("PRUEBA 3: insertar elementos en distintas posiciones con un iterador\n");
	
	/*Creo una lista de ints*/
	lista_t* lista3 = lista_crear();
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	int z = 0;
	lista_insertar_ultimo(lista3, &a);
	lista_insertar_ultimo(lista3, &b);
	lista_insertar_ultimo(lista3, &c);
	lista_insertar_ultimo(lista3, &d);
	lista_insertar_ultimo(lista3, &e);
	lista_insertar_ultimo(lista3, &f);
	printf("-Inserto 6 elementos del 1 al 6\n");
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista3));
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista3));
	
	/*Creo el iterador*/
	lista_iter_t* iter1 = lista_iter_crear(lista3);
	 
	/*Inserto elementos en distintas posiciones*/
	print_test("-Insertar un 0 al inicio", lista_iter_insertar(iter1, &z));
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista3));
	lista_iter_avanzar(iter1);
	lista_iter_avanzar(iter1);
	lista_iter_avanzar(iter1);

	print_test("-Insertar un 0 en la posicion 4", lista_iter_insertar(iter1, &z));
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista3));
	while(!lista_iter_al_final(iter1)){
		lista_iter_avanzar(iter1);
	}
	print_test("-Insertar un 0 al final", lista_iter_insertar(iter1, &z));
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista3));
	printf("-Estado actual de la lista:\n");
	imprimir_iter_externo(lista3);
	
	/*Destruyo la lista y el iterador*/
	lista_destruir(lista3, NULL);
    print_test("-La lista fue destruida", true);
    lista_iter_destruir(iter1);
    print_test("-El iterador fue destruir", true);
    printf("\n");
}

void iter_lista_borrar(){
	printf("PRUEBA 4: borrar elementos en distintas posiciones de una lista\n");
	/*Creo una lista de ints*/
	lista_t* lista4 = lista_crear();
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	lista_insertar_ultimo(lista4, &a);
	lista_insertar_ultimo(lista4, &b);
	lista_insertar_ultimo(lista4, &c);
	lista_insertar_ultimo(lista4, &d);
	lista_insertar_ultimo(lista4, &e);
	lista_insertar_ultimo(lista4, &f);
	printf("-Inserto 6 elementos del 1 al 6\n");
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista4));
	
	/*Creo el iterador*/
	lista_iter_t* iter2 = lista_iter_crear(lista4);
	
	/*Comienzo a borrar elementos*/
	print_test("-Borro el primer elemento de la lista", lista_iter_borrar(iter2) == &a);
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista4));
	lista_iter_avanzar(iter2);
	lista_iter_avanzar(iter2);
	print_test("-Borro el elemento en la posicion 2 de la lista", lista_iter_borrar(iter2) == &d);
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista4));
	lista_iter_avanzar(iter2);
	print_test("Borro el ultimo elemento de la lista", lista_iter_borrar(iter2) == &f);
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista4));
	printf("-Estado actual de la lista:\n");
	imprimir_iter_externo(lista4);
	
	/*Destruyo la lista y el iterador*/
	lista_destruir(lista4, NULL);
    print_test("-La lista fue destruida", true);
    lista_iter_destruir(iter2);
    print_test("-El iterador fue destruir", true);
    printf("\n");
}

void multiplicar_elementos_lista(){
	printf("PRUEBA 5: multiplico los elementos en las posiciones impares\n");
	/*Creo una lista de ints*/
	lista_t* lista5 = lista_crear();
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	lista_insertar_ultimo(lista5, &a);
	lista_insertar_ultimo(lista5, &b);
	lista_insertar_ultimo(lista5, &c);
	lista_insertar_ultimo(lista5, &d);
	lista_insertar_ultimo(lista5, &e);
	lista_insertar_ultimo(lista5, &f);
	printf("-Inserto 6 elementos del 1 al 6\n");
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista5));
	
	size_t* posicion = 0;
	lista_iterar(lista5, multiplicar_por_2, &posicion);
	printf("-Estado actual de la lista:\n");
	imprimir_iter_externo(lista5);
	
	/*Destruyo la lista*/
	lista_destruir(lista5, NULL);
    print_test("-La lista fue destruida", true);
    printf("\n");
}

void recorrer_lista(){
	printf("PRUEBA 6: imprimo la lista hasta la posicion 3\n");
	/*Creo una lista de ints*/
	lista_t* lista6 = lista_crear();
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	lista_insertar_ultimo(lista6, &a);
	lista_insertar_ultimo(lista6, &b);
	lista_insertar_ultimo(lista6, &c);
	lista_insertar_ultimo(lista6, &d);
	lista_insertar_ultimo(lista6, &e);
	lista_insertar_ultimo(lista6, &f);
	printf("-Inserto 6 elementos del 1 al 6\n");
	printf("-La lista tiene: %zu elementos\n", lista_largo(lista6));
	
	int posicion = 0;
	lista_iterar(lista6, imprimir_hasta_pos_3, &posicion);
	
	/*Destruyo la lista*/
	lista_destruir(lista6, NULL);
    print_test("-La lista fue destruida", true);
    printf("\n");
}

void destruir_lista_de_pilas(){
	printf("PRUEBA 7: Destruir una lista de pilas\n");
	lista_t* lista7 = lista_crear();
	pila_t* pila1 = pila_crear();
	pila_t* pila2 = pila_crear();
	pila_t* pila3 = pila_crear();
	lista_insertar_primero(lista7, pila1);
	lista_insertar_primero(lista7, pila2);
	lista_insertar_primero(lista7, pila3);
	print_test("La lista no esta vacia", !lista_esta_vacia(lista7));
	lista_destruir(lista7, pila_destruir_wrapped);
	print_test("La lista fue destruida", true);
}

void pruebas_lista_alumno(){
	crear_y_eliminar_lista();
	enlistar_elementos();
	iter_lista_insertar();
	iter_lista_borrar();
	multiplicar_elementos_lista();
	recorrer_lista();
	destruir_lista_de_pilas();
}
