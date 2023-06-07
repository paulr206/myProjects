#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

typedef struct ListElement{
    int content;
    ListElement *next;
} ListElement;

void printList(ListElement*);
int addElement(ListElement*, int);
int deleteElement(ListElement*, int);



int main() {
    ListElement *erstesElement;
    erstesElement = malloc(sizeof(ListElement));
    erstesElement->content = 5;
    erstesElement->next = NULL;
    
    
    addElement(erstesElement, 8);
    addElement(erstesElement, 64);
    addElement(erstesElement, 10);
    printList(erstesElement);
    deleteElement(erstesElement, 10);
    printList(erstesElement)
    ;    return 0;
}


void printList(ListElement *elem){
    int zaehler = 1;
    while (elem != NULL) {
        printf("%d.Element: %d\n", zaehler, elem->content);
        zaehler++;
        elem = elem->next;
    }
    printf("\n");
}

int addElement(ListElement *elem, int value){
    while (elem->next != NULL) {
        elem = elem->next;
    }
    ListElement *nextElement;
    nextElement = (ListElement*) malloc(sizeof(ListElement));
    nextElement->content = value;
    nextElement->next = NULL;
    elem->next = nextElement;
    return 1;
}

int deleteElement(ListElement *elem, int value){
    //wenn direkt erstes Element die Zahl ist
    if (elem->content == value) {
        ListElement newRoot = *elem->next;
        free(elem);
        *elem = newRoot;
        return 1; //root gelöscht
    }
    
    while (elem->next->content != value && elem->next != NULL) {
        elem = elem->next;
    }
    if (elem->next->content == value) {
        if (elem->next->next == NULL) {
            free(elem->next->next);
            elem->next = NULL;
            return 3; //letzes Element gelöscht
        }
        
        //merken bekommt Speicheradresse des zu löschenden Elements
        ListElement *merken1 = elem->next;
        elem->next = elem->next->next;
        free(merken1);
        return 2; //mittendrin gelöscht
    }
    
    
    
    else printf("\nKein Element gefunden!\n");
    return 0; //nichts gefunden
}
