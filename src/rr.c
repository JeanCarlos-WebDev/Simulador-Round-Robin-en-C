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

int rr_tick(ColaRR *cola, int tick) {
    if (cola->size == 0){
        printf("Cola vacía.\n");
        return 0;
    }
    // El primero
    Nodo *actual = cola->ultimo->siguiente;
    
    actual->rafagas--;
    printf("Tick %d: ejecutando %s (PID %d) — rafagas restantes: %d\n", 
        tick, actual->nombre, actual->pid, actual->rafagas);
    if (actual->rafagas == 0){
        // se guarda la información antes de liberar actual de memoria
        Nodo *siguiente = actual->siguiente;
        int pid = actual->pid;
        char nombre[50];
        strcpy(nombre, actual->nombre);
        if (cola->size == 1){
            cola->ultimo = NULL;
        } else {
            cola->ultimo->siguiente = siguiente;
        }
        cola->size--;
        free(actual);        
        printf("-> %s (PID %d) terminó.\n", nombre, pid);
    } else {
        cola->ultimo = cola->ultimo->siguiente;
    } 
    return 1;
}

void rr_liberar(ColaRR *cola) {
    if (cola->size == 0) return;

    Nodo *actual = cola->ultimo->siguiente; 
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

    // El primero
    Nodo *actual = cola->ultimo->siguiente;
    
    for (int i = 0; i < cola->size; i++) {
        printf("PID %d [%s] Rafagas=%d\n", actual->pid, actual->nombre, actual->rafagas);
        actual = actual->siguiente;
    }
}
