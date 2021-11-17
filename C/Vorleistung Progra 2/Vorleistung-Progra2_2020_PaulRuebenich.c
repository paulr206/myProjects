#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Vorleistung von Paul Rübenich - Progra2 - 2020

enum EItemPosition {Head, Neck, Armor, RightHand, LeftHand, Foot};
enum Slot {headSlot, neckSlot, armorSlot, rightHandSlot, leftHandSlot, feetSlot};
enum Direction{NORTH, EAST, SOUTH, WEST};

//Strukturen
typedef struct {
    char name[26];
    int position;
    float weight;
    int value;
    int lp_change;
} Item;

typedef struct {
    char name[20];
    int lifepoints;
    int staerke;
    int seitenanzahlWuerfel;
    Item *gegenstand;
} Monster;

typedef struct Room{
    char name[25];
    struct Room *nachbarraum[4];
    int lifepointsAttack;
    Monster *monster;
    Item *schatz;
} Room;

typedef struct{
    char name[26];
    int lifepoints;
    Item *slot[6];
    Item *inventory[10];
    Room *raum;
} Hero;


//Funktionen
int rollDice(int);
void printItem(Item*);
Item createItem(char[], int, float, int, int);
void printHero(Hero*);
Hero createHero(char[], int);
void wearItem(Hero*, Item*);
int addToInventory(Hero*, Item*);
Monster createMonster(char[], int, int, int, Item*);
void printMonster(Monster*);
void monsterAddLoot(Monster*, Item*);
Room createRoom(char[], Room*, Room*, Room*, Room*, int, Monster*, Item*);
void printRoom(Room*);
void setRoomInDirection(Room*, Room*, int);
Room* getRoomInDirection(Room*, int);
void walkInDirection(Hero*, Room*, int);
void setRoom(Hero*, Room*);


Item NOTHING = {"Leer", -1, 0, 0, 0};
Room WALL = {"Wand", NULL, NULL, NULL, NULL, 0};



int main() {
    
    Item holzschwert =  createItem("Holzschwert", LeftHand, 2.5, 3, 0);
    Item eisenschwert = createItem("Eisenschwert", LeftHand, 5.0, 20, 0);
    Hero zelda = createHero("Zelda", 10);
    wearItem(&zelda, &holzschwert);
    wearItem(&zelda, &eisenschwert);
    Item heiltrank = createItem("Heiltrank", 0, 1.0, 10, 5);
    addToInventory(&zelda, &heiltrank);
    
    Monster zombie = createMonster("Zombie", 3, 4, 6, &NOTHING);
    Monster magier = createMonster("Magier", 5, 2, 8, &NOTHING);
    monsterAddLoot(&magier, &heiltrank);
    
    Room eingang = {"Eingang", &WALL, &WALL, &WALL, &WALL, 0, &zombie, &heiltrank};
    Room thronsaal = createRoom("Thronsaal", &WALL, &WALL, &WALL, &WALL, 0, &magier, &NOTHING);
    setRoomInDirection(&eingang, &thronsaal, WEST);
    setRoom(&zelda, &eingang);
    walkInDirection(&zelda, &eingang, WEST);
    
    printHero(&zelda);
    printRoom(&thronsaal);
    
    
    return 0;
}



//Funktionen
int rollDice(int anzahlSeiten){
    srand((unsigned int) time(NULL));
    return rand()%anzahlSeiten;
}

void printItem(Item *gegenstand){
    printf("***** Gegenstand-Info *****\n\n");
    printf("Name: %s\n", gegenstand->name);
    printf("Position: %d\n", gegenstand->position);
    printf("Gewicht: %f\n", gegenstand->weight);
    printf("Wert: %d\n", gegenstand->value);
    printf("Veraenderung: %d\n\n", gegenstand->lp_change);
    printf("***************************\n");
}

Item createItem(char name[], int position, float weight, int value, int lp_change){
    Item gegenstand;
    strcpy(gegenstand.name, name);
    gegenstand.position = position;
    gegenstand.weight = weight;
    gegenstand.value = value;
    gegenstand.lp_change = lp_change;
    return gegenstand;
}

void printHero(Hero *Held){
    printf("***** Helden-Info *****\n");
    printf("Name: %s\n", Held->name);
    printf("Lebenspunkte: %d\n", Held->lifepoints);
    printf("Raum: %s\n", Held->raum->name);
    
    printf("Slots:\n");
    printf("Kopf:    %s\n", Held->slot[headSlot]->name);
    printf("Hals:    %s\n", Held->slot[neckSlot]->name);
    printf("Ruestung:    %s\n", Held->slot[armorSlot]->name);
    printf("Linke Hand:    %s\n", Held->slot[rightHandSlot]->name);
    printf("Rechte Hand:    %s\n", Held->slot[leftHandSlot]->name);
    printf("Fuesse:    %s\n", Held->slot[feetSlot]->name);
    
    printf("Inventar:\n");
    int j = 1;
    for (int i=0; i<10; i++) {
        printf("%d.  Item: %s\n", j, Held->inventory[i]->name);
        j++;
    }
}

Hero createHero(char name[], int lifepoints){
    Hero neuerHeld;
    strcpy(neuerHeld.name, name);
    neuerHeld.lifepoints = lifepoints;
    for (int i=0; i<6; i++) {
        neuerHeld.slot[i] = &NOTHING;
    }
    for (int j=0; j<10; j++) {
        neuerHeld.inventory[j]= &NOTHING;
    }
    return neuerHeld;
}

void wearItem(Hero *held, Item *gegenstand){
    if (held->slot[gegenstand->position]->position == -1) {
        held->slot[gegenstand->position] = gegenstand;
    }
    else if (held->slot[gegenstand->position]->position == gegenstand->position) {
        addToInventory(held, held->slot[gegenstand->position]);
        held->slot[gegenstand->position] = gegenstand;
    }
}

int addToInventory(Hero *held , Item *gegenstand) {
    int freieStelle = 10;
    for (int i=9; i>=0; i--) {
        if (strcmp(held->inventory[i]->name, NOTHING.name) == 0) {
            freieStelle = i;
        }
    }
    if (freieStelle != 10) {
        held->inventory[freieStelle] = gegenstand;
        return 1;
    }
    else
        printf("Inventar ist voll\n");
        return -1;
}

Monster createMonster(char name[], int lifep, int strength, int wuerfel, Item *gegenstand){
    Monster neuesMonster;
    strcpy(neuesMonster.name, name);
    neuesMonster.lifepoints = lifep;
    neuesMonster.staerke = strength;
    neuesMonster.seitenanzahlWuerfel = wuerfel;
    neuesMonster.gegenstand = gegenstand;
    return neuesMonster;
}

void printMonster(Monster *monster){
    printf("***** Monster-Info *****\n");
    printf("Name: %s\n", monster->name);
    printf("Lebenspunkte: %d\n", monster->lifepoints);
    printf("Staerke: %d\n", monster->staerke);
    printf("Wuerfel: %d-seitig\n", monster->seitenanzahlWuerfel);
    printf("Loot: %s\n", monster->gegenstand->name);
}

void monsterAddLoot(Monster *monster, Item *gegenstand){
    monster->gegenstand = gegenstand;
}

Room createRoom(char name[], Room *nachbarN, Room *nachbarO, Room *nachbarS, Room *nachbarW, int lifepAttack, Monster *monster, Item *gegenstand){
    Room neuerRaum;
    strcpy(neuerRaum.name, name);
    neuerRaum.nachbarraum[NORTH] = nachbarN;
    neuerRaum.nachbarraum[EAST] = nachbarO;
    neuerRaum.nachbarraum[SOUTH] = nachbarS;
    neuerRaum.nachbarraum[WEST] = nachbarW;
    neuerRaum.lifepointsAttack = lifepAttack;
    neuerRaum.monster = monster;
    neuerRaum.schatz = gegenstand;
    return neuerRaum;
}

void printRoom(Room *raum){
    printf("****** Raum-Info ******\n");
    printf("Name: %s\n", raum->name);
    for (int i = 0; i<4; i++) {
        printf("Nachbarräume: %s\n", raum->nachbarraum[i]->name);
    }
    printf("Monsters: %s\n", raum->monster->name);
    printf("Gegenstand: %s\n", raum->schatz->name);
}

void setRoomInDirection(Room *room1, Room *room2, int direction){
    int entgegengesetzteRichtung = 0;
    switch (direction) {
        case NORTH:
            entgegengesetzteRichtung = SOUTH;
            break;
        case EAST:
            entgegengesetzteRichtung = WEST;
            break;
        case SOUTH:
            entgegengesetzteRichtung = NORTH;
            break;
        case WEST:
            entgegengesetzteRichtung = EAST;
            break;
        default:
            printf("Ein Fehler mit -direction- ist aufgetreten!\n");
            break;
    }
    room1->nachbarraum[direction] = room2;
    room2->nachbarraum[entgegengesetzteRichtung] = room1;
}

Room* getRoomInDirection(Room *aktuellerRaum, int direction){
    if (aktuellerRaum->nachbarraum[direction]->name != WALL.name) {
        return aktuellerRaum->nachbarraum[direction];
    }
    else return NULL;
}


void walkInDirection(Hero *held, Room *aktuellerRaum, int direction){
    if (getRoomInDirection(aktuellerRaum, direction) != NULL) {
        held->raum = aktuellerRaum->nachbarraum[direction];
    }
}


void setRoom(Hero *held, Room *raum){
    held->raum = raum;
}



