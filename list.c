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
  if (list == NULL || list->current == NULL || list->current == list->head) return NULL; // Lista vacía, no hay current o current es el primer nodo

  Node* current = list->current;
  Node* temp = list->head;

  while (temp->next != current && temp->next != NULL) {
    temp = temp->next;
  }

  if (temp->next == NULL) {
    return NULL;
  }

  list->current = temp; 
  return (temp->data); 

}

void pushFront(List * list, void * data) {
  Node *nuevoNodo = createNode(data);
  if (nuevoNodo == NULL)return;

  nuevoNodo->next = list->head; 
  if (list->head == NULL) {
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  } 
  else{
    list->head = nuevoNodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (list->current == NULL)return;
  Node *nuevoNodo = createNode(data);
  if (nuevoNodo == NULL)return;
  
  nuevoNodo->next = list->current->next; 
  nuevoNodo->prev = list->current;       

  if (list->current->next != NULL) {
    list->current->next->prev = nuevoNodo;
  }

  list->current->next = nuevoNodo;
  if (list->tail == list->current) {
    list->tail = nuevoNodo;
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
  Node *n = list->current;
  if (list->current == NULL)return NULL; // No hay nodo actual para eliminar
  else{
    if (n->prev !=NULL){
      n->prev->next = n -> next;
    }
    else{
      list->head = n->next;
    }
    if(n->next != NULL){
      n->next->prev = n->prev;
    }
    else{
      list->tail = n->prev;
    }
  }
  void *data = n->data;
  free(n);
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}