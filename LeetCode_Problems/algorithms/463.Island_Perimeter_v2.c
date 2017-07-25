#include <stdio.h>
#include <stdlib.h>

int islandPerimeter(int** g, int r, int c) {
    if(r < 1 || c < 1) return 0;
    int i, j, count = 0;
    int **wreath;
    wreath = (int**)calloc(1, (r+2) * sizeof(int*));
    for(i = 0; i < r+2; i++){
    }
    for(i = 0; i < r+2; i++){
        wreath[i] = (int*)calloc(1, (c+2) * sizeof(int));
    }
    for(i = 1; i < r + 1; i++) {
        for(j = 1; j < c + 1; j++) {
            wreath[i][j] = g[i-1][j-1];
        }
    }
    for(i = 1; i < r + 1; i++){
        for(j = 1; j < c + 1; j++) {
            if(wreath[i][j]) {
                if(!wreath[i-1][j]) count++;
                if(!wreath[i+1][j]) count++;
                if(!wreath[i][j-1]) count++;
                if(!wreath[i][j+1]) count++;
            }
        }
    }
    for(i = 0; i < r+2; i++){
        free(wreath[i]);
    }
    free(wreath);
    return count;
}

void main(void) {
    int ** test;
    test = (int**)malloc(4 * sizeof(int*));
    test[0] = (int*)malloc(4 * sizeof(int));
    test[1] = (int*)malloc(4 * sizeof(int));
    test[2] = (int*)malloc(4 * sizeof(int));
    test[3] = (int*)malloc(4 * sizeof(int));
    test[0][0] = 0;
    test[0][1] = 1;
    test[0][2] = 0;
    test[0][3] = 0;
    test[1][0] = 1;
    test[1][1] = 1;
    test[1][2] = 1;
    test[1][3] = 0;
    test[2][0] = 0;
    test[2][1] = 1;
    test[2][2] = 0;
    test[2][3] = 0;
    test[3][0] = 1;
    test[3][1] = 1;
    test[3][2] = 0;
    test[3][3] = 0;
    int rt = 0 ;
    rt = islandPerimeter(test, 4, 4);
    printf("rt = %d\n", rt);
}
