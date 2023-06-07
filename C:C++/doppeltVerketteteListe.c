#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

typedef struct ListElement{
    ListElement *previous;
    int content;
    ListElement *next;
} ListElement;


int printList(ListElement*);
int listInsert(ListElement*, int);
int listElementDelete(ListElement*, int);


int main() {
    //erstes Element
    ListElement *list;
    list = malloc(sizeof(ListElement));
    list->previous = NULL;
    list->content = 5;
    list->next = NULL;

    printList(list);
    listInsert(list, 9);
    listInsert(list, 13);
    listInsert(list, 4);
    listInsert(list, 7);
    printList(list);
    listElementDelete(list, 13);
    printList(list);
    return 0;
}




int printList(ListElement *elem){
    if (elem == NULL) {
        printf("Liste kann nicht ausgegeben werden, da sie leer ist!\n");
        return 0;
    }
    int i = 1;
    while (elem != NULL) {
        printf("%d.Element: %d\n", i, elem->content);
        i++;
        elem = elem->next;
    }
    printf("\n");
    return 1;
}

int listInsert(ListElement *elem, int value){
    if (elem == NULL) {
        printf("Leere Liste!\n");
        return 0;
    }
    
    while (elem->next != NULL) {
        elem = elem->next;
    }
    ListElement *nextElement;
    nextElement = malloc(sizeof(ListElement));
    elem->next = nextElement;
    nextElement->previous = elem;
    nextElement->content = value;
    nextElement->next = NULL;
    return 1;
}


int listElementDelete(ListElement *elem, int value){
    //Liste leer
    if (elem == NULL) {
        printf("Element kann nicht gelöscht werden da die Liste leer ist!\n");
        return -1;
    }
    //wenn erstes Element |  && elem != NULL oben abgefangen
    if (elem->content == value) {
        ListElement *newRoot = elem->next;
        free(elem);
        elem = newRoot;
        elem->previous = NULL;
        return 0;
    }
    
    while (elem->next != NULL && elem->next->content != value) {
        elem = elem->next;
    }
    if (elem->next->content == value) {
        //letztes Element
        if (elem->next == NULL) {
            ListElement *previousElem = elem->previous;
            free(elem);
            previousElem->next = NULL;
            return 1;
        }
        elem->previous->next = elem->next;
        elem->next->previous = elem->previous;
        free(elem);
        return 1;
    }
    printf("Element nicht in Liste!\n");
    return -2;
}
