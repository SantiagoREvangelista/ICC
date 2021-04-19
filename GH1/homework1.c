#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readBinary.h"

#define N_PRODUCTS 28
#define N_VALUES 4
#define MAX_CHAR 100
#define MAX_CATEG 10


/* defining structure and functions */

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

void print_list_chunk(struct item list_struct[N_PRODUCTS]);

void print_stats(struct item list_struct[N_PRODUCTS], int n_categ);

float calculate_ratio(struct item list_struct[N_PRODUCTS], int category_id);

void calculate_all_ratios(struct item list_struct[N_PRODUCTS], int n_categ, float ratios[MAX_CATEG]);

void print_budget_per_categ(float ratios[MAX_CATEG], int n_categ, float total_solde);

float calculate_excess_after_rising(float old_ratios[MAX_CATEG], float
percent_raise, int for_category[MAX_CATEG], float new_ratios[MAX_CATEG], int n_categ, int n_changed, float total_solde);

void redistribute(float old_ratios[MAX_CATEG], float new_ratios[MAX_CATEG], int
n_categ, float total_solde);




int main() {

  float budget=100;
  float r=0.1;

  char list[N_PRODUCTS][N_VALUES][MAX_CHAR];

  float ratios[MAX_CATEG];
  float new_ratios[MAX_CATEG];

  readBinary("list2.bin",list);

  struct item list_items[N_PRODUCTS];

  int for_category[2]={0,2};

  process_list(list, list_items);

  int g=find_categories(list_items);

  print_list_chunk(list_items);

  print_stats(list_items,g);

  calculate_all_ratios(list_items, g, ratios);

  print_budget_per_categ(ratios, g, budget);

  calculate_excess_after_rising(ratios, r, for_category, new_ratios, g, 2, 100);

  redistribute(ratios, new_ratios, g, budget);

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

  numberCategories=dummyArray[N_PRODUCTS-1]+1;

  if(numberCategories>MAX_CATEG){
    printf("Error: too many categories!");
    return 0;
    }

  else{
    printf("This list contains %d categories !\n", numberCategories);
    }

  return numberCategories;
}



void print_list_chunk(struct item list_struct[N_PRODUCTS]){
  int bottomProduct, topProduct;
  int condition=1;
  while (condition){
    printf("Enter the index of the first item you want to print : ");
    scanf("%d", &bottomProduct);
    printf("Enter the index of the last item you want to print : ");
    scanf("%d", &topProduct);

/* Checking range */

    if(bottomProduct<topProduct && bottomProduct>0 && bottomProduct<N_PRODUCTS){
      condition=0;
    }
    else{
      printf("Invalid Range !");
    }
  }

  printf("This is an extract of the grocery list from item-%d to item-%d\n", bottomProduct, topProduct);
  
  for(int p=bottomProduct; p<=topProduct; p++){
    printf("Item No %d:\n- Category: %d\n- Name: %s\n- Quantity: %d\n- Unitary Price: %f\n---------------\n", p,list_struct[p].category,list_struct[p].name,list_struct[p].quantity,list_struct[p].price);
  }
}



void print_stats(struct item list_struct[N_PRODUCTS], int n_categ){
  float price=0;

  int productsCategories[n_categ];
  /* initializing all values to 0 */
  productsCategories[0]=0;

  for(int h=0; h<N_PRODUCTS; h++){
    /* finding the category for each product and adding them to its respective place in the array productCategories. The loop also sums the price of each product */
    productsCategories[list_struct[h].category] = productsCategories[list_struct[h].category] + list_struct[h].quantity;
    price = price + list_struct[h].price * list_struct[h].quantity;
  }

  printf("Number of articles found in each category :\n");

  for(int j=0; j<n_categ; j++){
    printf("%d articles found in category %d\n", productsCategories[j], j);
  }

  printf("For a total price of : %f\n", price);

}



float calculate_ratio(struct item list_struct[N_PRODUCTS], int category_id){
  float ammountCategory=0;
  float total=0;
  /*calculating total price again for normalization*/
  for(int u=0; u<N_PRODUCTS; u++){
    total=total+list_struct[u].price*list_struct[u].quantity;
  }
  /*summing all the normalized prices from the category*/
  for(int h=0; h<N_PRODUCTS; h++){
    if(list_struct[h].category==category_id){
      ammountCategory=ammountCategory+((list_struct[h].price*list_struct[h].quantity)/total);
    }
  }
  return ammountCategory;
}



void calculate_all_ratios(struct item list_struct[N_PRODUCTS], int n_categ, float ratios[MAX_CATEG]){
  float total=0;
  printf("Checking ratios by category :");

  /*calling the function calculate_ratio for each category and summing all the ratios*/

  for(int z=0; z<n_categ; z++){
    ratios[z]=calculate_ratio(list_struct, z);
    printf(" %f |",ratios[z]);
    total=total+ratios[z];
  }
  /*making sure total is 100%*/
  if(total==1){
    printf(", total = 1\n");
  }
  else{
    printf("ERROR: total is more than 1.0\n");
  }
}



void print_budget_per_categ(float ratios[MAX_CATEG], int n_categ, float total_solde){
  /*dummy variable to print in each pass of the loop*/
  float dummyRatio;
  /*printing solde for each category*/
  for(int r=0; r<n_categ; r++){
    dummyRatio=total_solde*ratios[r];
    printf("Next time you should spend : %f CHF for category %d\n", dummyRatio, r);
  }
}



float calculate_excess_after_rising(float old_ratios[MAX_CATEG], float
percent_raise, int for_category[MAX_CATEG], float new_ratios[MAX_CATEG], int
n_categ, int n_changed, float total_solde){
 /*printablePercent is created only for printing*/ 
  float printablePercent=percent_raise*100;
 /*newTot is the normalization constant for the new ratios*/
  float newTot=1;
  float excess;
 /*turning all values of the arrat new_ratios to assure good functioning of the function. this prevents errors from an input array with initialized values*/
  for(int t=0; t<n_categ; t++){
    new_ratios[t]=0;
  }

  printf("Considering now that the prices of category ");
 /*computing normalization constant for new ratios*/
  for(int y=0; y<n_changed; y++){
    newTot=newTot+(old_ratios[for_category[y]]*percent_raise);
  }

/*computing the values of the array new_ratios at the positions of the changed categories (all the rest stay 0)*/
  for(int e=0; e<n_changed; e++){
    new_ratios[for_category[e]]=old_ratios[for_category[e]]*(1+percent_raise)/newTot;
    printf("%d ",for_category[e]);
  }

  printf("have been raised by %f%%\n", printablePercent);

/*computing the other ratios (notice we ask for new_ratios values to be zero beacause those are the ones untouched from the loop just above)*/
  for(int b=0; b<n_categ; b++){
    if (new_ratios[b]==0){
      new_ratios[b]=old_ratios[b]/newTot;
    } 
  }

/*computing excess*/
  excess=(total_solde*newTot)-total_solde;

  printf("You are exceeding your solde by %f CHF\n",excess);
  return excess;
}



void redistribute(float old_ratios[MAX_CATEG], float new_ratios[MAX_CATEG], int
n_categ, float total_solde){

  /*dummy variable for printing in the loop*/
  float dummyExcess;

  printf("Conserving a total cash-bill of %f\n", total_solde);
  
  /*computing excesses or shorting in the categories*/
  for(int c=0; c<n_categ; c++){
    dummyExcess=(new_ratios[c]-old_ratios[c])*total_solde;
    printf("Because of the raise you should add %f from category %d expenses\n",dummyExcess,c);
  }
}