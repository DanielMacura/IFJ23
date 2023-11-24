/**
 * @file DLL.c
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Implementation of doubly linked list used for storing tokens
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "DLL.h"
#include <stdio.h>


DLL *createDLL() {
    DLL *newDLL = malloc(sizeof(DLL));
    newDLL->firstElement = NULL;
    newDLL->activeElement = NULL;
    newDLL->lastElement = NULL;
    return newDLL;
}


void DLL_push(DLL *dll, token *t) {
    DLLElementPtr new_element = malloc(sizeof(*new_element));
    new_element->data = *t;
    new_element->previousElement = dll->lastElement;
    new_element->nextElement = NULL;
    if (dll->lastElement != NULL) {
        dll->lastElement->nextElement = new_element;
    }
    else {
        dll->firstElement = new_element;
    }
    dll->lastElement = new_element;
    dll->activeElement = dll->lastElement;
}


token *DLL_get_active(DLL *dll) {
    if (dll->activeElement != NULL) {
        return &dll->activeElement->data;
    }
    return NULL;
}


void DLL_move_active_left(DLL *dll) {
    if (dll->activeElement == NULL) {
        return;
    }
    if(dll->activeElement->previousElement != NULL){
        dll->activeElement = dll->activeElement->previousElement;\
    }
}


void DLL_move_active_right(DLL *dll) {
    if (dll->activeElement == NULL) {
        dll->activeElement = dll->firstElement;
        return;
    }
    if(dll->activeElement->nextElement != NULL){
        dll->activeElement = dll->activeElement->nextElement;
    }
}


void DLL_free(DLL *dll) {
    DLLElementPtr current = dll->firstElement;
    DLLElementPtr next;
    while (current != NULL) {
        next = current->nextElement;
        if (current->data.VAL.string!= NULL /*&& current->data.ID !=TOKEN_ID_KEYWORD*/) { //keywords are not allocated      TODO: fix me probably
            free(current->data.VAL.string);
        }
        free(current);
        current = next;
    }
    free(dll);
}