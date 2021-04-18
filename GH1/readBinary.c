#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_PRODUCTS 28
#define N_VALUES 4
#define MAX_CHAR 100

void readBinary(char filename[], char list[N_PRODUCTS][N_VALUES][MAX_CHAR]){

    FILE* inputB;
    if ((inputB = fopen(filename,"rb")) == NULL){ // Name of the binary_file to be read
        printf("Error opening binary file\n");
    }
    for (int i=0; i < N_PRODUCTS; i++){
        fread(&list[i], MAX_CHAR , N_VALUES, inputB);
    }
    fclose(inputB);
}
