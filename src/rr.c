/*
 * rr.c  —  Implementación del Round Robin Scheduler
 *
 * CI3825 Sistemas de Operación I · Proyecto 0
 * Integrante 1: Cristina Puyosa Carnet: 23-10395
 * Integrante 2: Jean Sifontes  Carnet: 22-10387
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rr.h"

void rr_init(ColaRR *cola) {
    cola->size = 0;
    cola->ultimo = NULL;
}

void rr_encolar(ColaRR *cola, int pid, const char *nombre, int rafagas) {
    
    //Creamos un nuevo nodo con todos los parámetros
    Nodo *nuevo = malloc(sizeof(Nodo));
    strcpy(nuevo->nombre, nombre);
    nuevo->pid = pid;
    nuevo->rafagas = rafagas;
    nuevo->siguiente = NULL;

    
    // Manejamos los punteros
    //  La cola está vacía
    if (cola->size == 0){
        nuevo->siguiente = nuevo;
        cola->ultimo = nuevo;
        (*cola).size += 1;
        return;
    }
     // La cola no está vacía
    nuevo->siguiente = cola->ultimo->siguiente;
    cola->ultimo->siguiente = nuevo;
    cola->ultimo = nuevo;
    (*cola).size += 1;
}

// int rr_tick(ColaRR *cola, int tick) {
//     if (cola != NULL && tick == -1000000){}
//     return 0;
// }

void rr_liberar(ColaRR *cola) {
    if (cola->size == 0) return;

    Nodo *actual = cola->ultimo->siguiente; // Empezamos por el primero (head)
    Nodo *siguiente;

    for (int i = 0; i < cola->size; i++) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    cola->ultimo = NULL;
    cola->size = 0;
}

void rr_imprimir(const ColaRR *cola) {
    if (cola->size == 0) {
        return;
    }

    Nodo *actual = cola->ultimo->siguiente; // El primero
    
    // Usamos el size para evitar confusiones con los punteros
    for (int i = 0; i < cola->size; i++) {
        printf("PID %d [%s] Rafagas=%d\n", actual->pid, actual->nombre, actual->rafagas);
        actual = actual->siguiente;
    }
}
