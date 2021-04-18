#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readBinary.h"

#define N_PRODUCTS 28
#define N_VALUES 4
#define MAX_CHAR 100
#define MAX_CATEG 10



struct item
{
  int category;
  int quantity;
  float price;
  char name[MAX_CHAR];
};

void process_list(char list_char[N_PRODUCTS][N_VALUES][MAX_CHAR], struct item
list_struct[N_PRODUCTS]);

int find_categories(struct item list_struct[N_PRODUCTS]);



int main() {


  char list[N_PRODUCTS][N_VALUES][MAX_CHAR];

  readBinary("list2.bin",list);

  struct item list_items[N_PRODUCTS];

  process_list(list, list_items);

  int g=find_categories(list_items);

  return 0;

}



void process_list(char list_char[N_PRODUCTS][N_VALUES][MAX_CHAR], struct item
list_struct[N_PRODUCTS]){
  for(int i=0; i<N_PRODUCTS; i++){
    list_struct[i].category=atoi(list_char[i][0]);
    strcpy(list_struct[i].name, list_char[i][1]);
    list_struct[i].quantity=atoi(list_char[i][2]);
    list_struct[i].price=atof(list_char[i][3]);
  }
}



int find_categories(struct item list_struct[N_PRODUCTS]){
  int numberCategories=1;
  int dummyArray[N_PRODUCTS];
  int temp;

/*creating a dummy array to be able to modify it without affecting original array*/

  for(int i=0; i<N_PRODUCTS; i++){
    dummyArray[i]=list_struct[i].category;
  }

/*sorting dummy array*/

  for(int l=0;l<N_PRODUCTS;l++){
    for(int k=l+1;k<N_PRODUCTS;k++){
      if(dummyArray[l]>dummyArray[k]){
        temp=dummyArray[l];
        dummyArray[l]=dummyArray[k];
        dummyArray[k]=temp;
      }
    }
  }

/*checking for different categories*/

  for(int q=1; q<N_PRODUCTS; q++){
    if(dummyArray[q]!=dummyArray[q-1]){
      numberCategories++;
    }
  }


  if(numberCategories>MAX_CATEG){
    printf("Error: too many categories!");
    return 0;
    }

  else{
    printf("This list contains %d categories !\n", numberCategories);
    }

  return numberCategories;
}