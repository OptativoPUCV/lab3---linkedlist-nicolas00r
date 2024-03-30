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
    List *lista = (List *)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
  
    return lista;
}

void * firstList(List * list) {
    if(list->head == NULL) return NULL;
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if(list->current == NULL) return NULL;
    else if(list->current->next == NULL) return NULL;
  
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if(list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if(list->current == NULL) return NULL;
    if(list->current->prev == NULL) return NULL;

    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node *newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
    if(list->tail == NULL) list->tail = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    if(list->current == NULL){
      pushFront(list, data);
      return;
    }
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *newNode = createNode(data);
    if(list->tail == list->current){
      list->current->next = newNode;
      newNode->prev = list->current;
      list->tail = newNode;
    } else{
    newNode->next = list->current->next;
    newNode->prev = list->current;
    list->current->next->prev = newNode;
    list->current->next = newNode;
    list->current = newNode;
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
    if(list->current == NULL) return NULL;
   
    if(list->head == list->current){
      if (list->head == NULL) return NULL;

      if(list->head->next == NULL) list->head = NULL;
      else{ 
        list->head = list->head->next;
        list->head->prev = NULL;
      }
    } else if(list->tail == list->current){
      if (list->tail == NULL) return NULL;

      if(list->tail->prev == NULL) list->tail = NULL;
      else{
        list->tail = list->tail->prev;
        list->tail->next = NULL;
      }
    } else{
      list->current->prev->next = list->current->next;
      list->current->next->prev = list->current->prev;
    }
    return list->current->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}