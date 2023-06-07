#include <stdio.h>
#include <stdlib.h>

int binarySearch(int[], int, int, int);

int main() {

    int arr[] = {7, 8, 14, 17, 19, 23, 45, 47, 56, 58, 61, 73, 75, 79,
    81, 88, 92, 95, 101, 110, 123, 125, 134, 135, 156, 167, 177, 178,
    179, 234, 237, 888};
        
    int ergebnis;
    ergebnis = binarySearch(arr, 125, 0, 31);
    
    if (ergebnis != -1) {
        printf("Die Zahl ist an Stelle %d des Arrays\n", ergebnis);
    }
    else
        printf("\nDie Zahl ist nicht im Array!\n");
    


    return 0;
}

int binarySearch(int arr[], int key, int links, int rechts){
    int mitte = links + (rechts - links +1) / 2;
    printf("Mitte: %d\n", mitte);
    
    if (rechts < links){
        return -1;
    }
    else if (arr[mitte] == key) {
        return mitte;
    }
    else if (arr[mitte] > key) {
        return binarySearch(arr, key, links, mitte-1);
    }
    else{
        return binarySearch(arr, key, mitte+1, rechts);
    }
}
