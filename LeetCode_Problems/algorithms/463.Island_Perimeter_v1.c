#include <stdio.h>
#include <stdlib.h>

int islandPerimeter(int** grid, int gridRowSize, int gridColSize) {
    if(gridRowSize < 1 || gridColSize < 1) return 0;
    int i,j;
    int count = 0;
    for(i = 0; i < gridRowSize; i++) {
        for(j = 0 ; j < gridColSize; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    for(i = 1; i < gridRowSize - 1; i++){
        for(j = 1; j < gridColSize - 1; j++) {
            printf("grid[%d][%d] = %d\n", i, j, grid[i][j]);
            if(grid[i][j]) {
                printf("grid[%d][%d] = %d\n", i-1, j, grid[i-1][j]);
                printf("grid[%d][%d] = %d\n", i+1, j, grid[i+1][j]);
                printf("grid[%d][%d] = %d\n", i, j-1, grid[i][j-1]);
                printf("grid[%d][%d] = %d\n", i, j+1, grid[i][j+1]);
                if(!grid[i-1][j]) count++;
                if(!grid[i+1][j]) count++;
                if(!grid[i][j-1]) count++;
                if(!grid[i][j+1]) count++;
            }
        }
        printf("one: i=%d,count = %d\n", i, count);
    }
    printf("one end: i=%d,count = %d\n", i, count);
    for(j = 1; j < gridColSize - 1; j++) {
        if(grid[0][j]){
            count++;
            if(!grid[0][j-1]) count++;
            if(!grid[0][j+1]) count++;
            if(gridRowSize > 1) {
                if(!grid[1][j]) count++;
            }else count++;
        }
    }
    for(j = 1; j < gridColSize - 1; j++) {
        if(grid[gridRowSize - 1][j]){
            if(gridRowSize > 1) {
                count++;
                if(!grid[gridRowSize - 1][j-1]) count++;
                if(!grid[gridRowSize - 1][j+1]) count++;
                if(!grid[gridRowSize - 2][j]) count++;
            }
        }
    }
    for(i = 1; i < gridRowSize - 1; i++) {
        if(grid[i][0]){
            count++;
            if(!grid[i-1][0]) count++;
            if(!grid[i+1][0]) count++;
            if(gridColSize > 1) {
                if(!grid[i][1]) count++;
            }else count++;
        }
    }
    for(i = 1; i < gridRowSize - 1; i++) {
        if(grid[i][gridColSize - 1]){
            if(gridColSize > 1) {
                count++;
                if(!grid[i-1][gridColSize-1]) count++;
                if(!grid[i+1][gridColSize-1]) count++;
                if(!grid[i][gridColSize-2]) count++;
            }
        }
    }
    if(grid[0][0]) {
        count+=2;
        if(!grid[0][1] || !grid[1][0]) count++;
    }
    if(grid[0][gridColSize-1]){
        count+=2;
        if(!grid[0][gridColSize-2] || !grid[1][gridColSize-1]) count++;
    }
    if(grid[gridRowSize-1][0]){
        count+=2;
        if(!grid[gridRowSize-2][0] || !grid[gridRowSize-1][1]) count++;
    }
    if(grid[gridRowSize-1][gridColSize-1]) {
        count+=2;
        if(!grid[gridRowSize-1][gridColSize-2] || !grid[gridRowSize-2][gridColSize-1]) count++;
    }
    return (count < 4 && count > 0)? 4 : count;
}

int main(void) {
    int ** test;
    test = (int**)malloc(4 * sizeof(int*));
    test[0] = (int*)malloc(4 * sizeof(int));
    test[1] = (int*)malloc(4 * sizeof(int));
//    test[2] = (int*)malloc(4 * sizeof(int));
//    test[3] = (int*)malloc(4 * sizeof(int));
    test[0][0] = 0;
    test[0][1] = 1;
    test[0][2] = 0;
    test[0][3] = 0;
    test[1][0] = 1;
    test[1][1] = 1;
    test[1][2] = 1;
    test[1][3] = 0;
//    test[2][0] = 0;
//    test[2][1] = 1;
//    test[2][2] = 0;
//    test[2][3] = 0;
//    test[3][0] = 1;
//    test[3][1] = 1;
//    test[3][2] = 0;
//    test[3][3] = 0;
    int rt = 0 ;
    rt = islandPerimeter(test, 2, 4);
    printf("rt = %d\n", rt);
}
