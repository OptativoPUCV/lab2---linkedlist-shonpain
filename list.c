#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* list=(List*) malloc(sizeof(List));
  list->head=NULL;
  list->tail=0;
  list->current=NULL;
     return list;
}

void * firstList(List * list) {
  if(!list->head)return NULL;
  list->current = list->head;
    return (list->head->data);
}

void * nextList(List * list) {
  if(list->current == NULL || list->current->next == NULL)return NULL;
  list->current = list->current->next;
    return (list->current->data);
}

void * lastList(List * list) {
  if (list == NULL || list->tail == NULL)return NULL;
  list->current = list->tail;
  return (list->tail->data); // Retorna ultimo dato
}

void * prevList(List * list) {
  if (list == NULL || list->current == NULL || list->current == list->head) return NULL; // Lista vacía, current no está establecido o current es el primer nodo

  Node* current = list->current;
  Node* temp = list->head;

  // Encontrar el nodo anterior a current
  while (temp->next != current && temp->next != NULL) {
    temp = temp->next;
  }

  if (temp->next == NULL) {
    // No se encontró el nodo anterior a current
    return NULL;
  }

  list->current = temp; // Actualizar current al nodo anterior
  return (temp->data); // Retornar un puntero al dato del nodo anterior

}

void pushFront(List * list, void * data) {
     Node *newNode = createNode(data);
    if (newNode == NULL) {
        // Error al crear el nuevo nodo
        return;
    }

    newNode->next = list->head; // El siguiente del nuevo nodo apunta al antiguo primer nodo

    if (list->head == NULL) {
        // Si la lista estaba vacía, tanto la cabeza como la cola apuntan al nuevo nodo
        list->head = newNode;
        list->tail = newNode;
    } else {
        // Si la lista no estaba vacía, la cabeza ahora apunta al nuevo nodo
        list->head = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
      if (list->current == NULL) {
        // Si current es NULL, no podemos agregar después de él
        return;
    }

    Node *newNode = createNode(data);
    if (newNode == NULL) {
        // Error al crear el nuevo nodo
        return;
    }

    newNode->next = list->current->next; // El siguiente del nuevo nodo apunta al siguiente del nodo actual
    list->current->next = newNode; // El siguiente del nodo actual apunta al nuevo nodo

    if (list->tail == list->current) {
        // Si el nodo actual es el último nodo, actualizamos la cola
        list->tail = newNode;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}