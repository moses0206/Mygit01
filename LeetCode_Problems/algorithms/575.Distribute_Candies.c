#include <stdio.h>
#include <stdlib.h>

int distributeCandies(int* candies, int candiesSize) {
    int arr[200001] = {0};
    int i, count = 0;
    for(i = 0; i < candiesSize; ++i){
        if(!arr[(candies[i] + 100000)]){
            arr[(candies[i] + 100000)] = 1;
            count++;
        }
    }
    return candiesSize/2 > count ? count : candiesSize/2;
}

void main(void) {
    int test[] = {1, 2, 3, 2 ,1 ,3 ,5, 2, 7, 9, 1, 2, 2, 3, 8, 1};
    printf("candies type = %d\n", distributeCandies(test, 16));
}
