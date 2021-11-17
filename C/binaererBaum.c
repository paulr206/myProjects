#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum Geschlecht {m, w};

typedef struct {
    int tag, monat, jahr;
} Datum;

typedef struct{
    char name[50];
    enum Geschlecht geschlecht;
    Datum geburtsdatum;
} Person;

typedef struct Knoten{
    Person *inhalt;
    struct Knoten *vater;
    struct Knoten *mutter;
} Knoten;



Knoten* createStammbaum(Person*);
void printStammbaum(Knoten*);
void findKind(Knoten*, Person*, Knoten**);
void addPerson(Person*, Person*, Knoten*);


int main() {
    Person karl = {"Karl I.", m, {19,3,1745}};
    Knoten *stammbaum = createStammbaum(&karl);
    
    
    Person otto = {"Otto", m, {19,3,1715}};
    Person maria = {"Maria", w, {19,3,1719}};
    Person anna = {"Anna", w, {19,3,1746}};
    Person sophie = {"Sophie", w, {19,3,1718}};
    
    addPerson(&otto, &karl, stammbaum);
    addPerson(&maria, &karl, stammbaum);
    addPerson(&anna, &otto, stammbaum);
    addPerson(&sophie, &anna, stammbaum);
    
    
    
    printStammbaum(stammbaum);
    
    
    return 0;
}



Knoten* createStammbaum(Person *person) {
    Knoten *elem = (Knoten*) malloc(sizeof(Knoten));
    elem->inhalt = person;
    elem->vater = NULL;
    elem->mutter = NULL;
    return elem;
}


void printStammbaum(Knoten *baum) {
    if (baum == NULL) {
        // nichts machen
        return;
    }
    else {
        if (baum->inhalt != NULL) {
            printf("%s\n", baum->inhalt->name);
        }
    printStammbaum(baum->vater);
    printStammbaum(baum->mutter);
    }
}

void findKind(Knoten *baum, Person *kind, Knoten **gefundenerKnoten) {
    if (baum == NULL) {
        return;
    }
    if (baum->inhalt != NULL && strcmp(baum->inhalt->name, kind->name) == 0/*baum->inhalt == kind*/) {
        *gefundenerKnoten = baum;
        return;
    }
    else {
        findKind(baum->vater, kind, gefundenerKnoten);
        findKind(baum->mutter, kind, gefundenerKnoten);
    }
}



void addPerson(Person *elternTeil, Person *kind, Knoten *baum) {
    
    // wenn "kind" der Wurzelknoten ist
    if (baum->inhalt->geburtsdatum.jahr == kind->geburtsdatum.jahr) {
        if (elternTeil->geschlecht == m) {
            baum->vater = (Knoten*) malloc(sizeof(Knoten));
            baum->vater->inhalt = elternTeil;
            baum->vater->mutter = NULL;
            baum->vater->vater = NULL;
        }
        else {
            baum->mutter = (Knoten*) malloc(sizeof(Knoten));
            baum->mutter->inhalt = elternTeil;
            baum->mutter->mutter = NULL;
            baum->mutter->vater = NULL;
        }
    }
    else {
    // ansonten finde den Knoten "kind"
        Knoten *tempKnoten;
        tempKnoten = NULL;
        findKind(baum, kind, &tempKnoten);
        if(tempKnoten != NULL){
            baum = tempKnoten;
            if (elternTeil->geschlecht == m) {
                baum->vater = (Knoten*) malloc(sizeof(Knoten));
                baum->vater->inhalt = (Person*) malloc(sizeof(Person));
                baum->vater->inhalt = elternTeil;
                baum->vater->mutter = NULL;
                baum->vater->vater = NULL;
            }
            else {
                baum->mutter = (Knoten*) malloc(sizeof(Knoten));
                baum->mutter->inhalt = elternTeil;
                baum->mutter->mutter = NULL;
                baum->mutter->vater = NULL;
            }
        }
        else {
           printf("***** FEHLER *****\n<%s> not found!\n******************\n\n", kind->name);
        }
    }
}
