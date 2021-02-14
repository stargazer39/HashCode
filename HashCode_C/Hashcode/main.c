#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIZZA 100000
#define MAX_ING 10000

//Structure of a pizza
typedef struct {
    int index;
    int ing_length;
    char ingredients[MAX_ING][20];
}piz;

void sortPizza (piz * orig,piz * sorted_pizza[],int len);
int main()
{
    //New pizza struct
    piz * pizza;
    //Allocate memory to it (MaX_PIZZA * (size of one pizza stucture)
    pizza = malloc(MAX_PIZZA * sizeof(piz));
    if(pizza == NULL){
        printf("Memory allocation faild. (pizzza)");
    }
    //Open the file
    FILE *fptr;
    FILE *fptr2;
    fptr = fopen("c_many_ingredients.in","r");
    fptr2 = fopen("c_many_ingredients.out","w");
    //Check if file is open
    if(fptr == NULL || fptr2 == NULL){
        printf("File couldn't be opened");
        return -1;
    }

    int f_index = 0;
    int f_args[4];
    //int next;
    //char next2[100];
    int ing_amount;
    char temp_ing[20];
    while(!feof(fptr)){
        if(f_index == 0){
                for(int i = 0; i<4; i++){
                    fscanf(fptr,"%d ",&f_args[i]);
                }
            //fscanf(fptr,"%d %d %d %d",&f_args[0],&f_args[1],&f_args[2],&f_args[3]);
        }
        fscanf(fptr,"%d ", &ing_amount);
        for(int i = 0; i < ing_amount; i++){
            fscanf(fptr,"%s ",&pizza[f_index].ingredients[i]);
        }
        pizza[f_index].index = f_index;
        pizza[f_index].ing_length = ing_amount;
        f_index++;
    }
    for(int i = 0; i < 4; i++){
        printf("%d ",f_args[i]);
    }

    //Sort pizza
    piz * sorted_pizza[MAX_PIZZA];
    sortPizza(pizza,sorted_pizza,f_index);

    //Print everything to a file
    for(int i = 0; i<f_index; i++){
        int tmp_length = sorted_pizza[i]->ing_length;
        fprintf(fptr2,"%d ",tmp_length);
        for(int j = 0; j<tmp_length; j++){
            fprintf(fptr2,"%s ",sorted_pizza[i]->ingredients[j]);
        }
        fprintf(fptr2,"\n");
        printf("\n%d",sorted_pizza[i]->ing_length);
    }
    printf("\n%d",f_index);
    getchar();
    return 0;
}
//Pizza sorting by Ingredients.
void sortPizza (piz * orig,piz * sorted_pizza[],int len)
{
    //Get the maximum value
    int max = 0;
    for(int i = 0; i < len; i++){
        if(max < orig[i].ing_length){
            max = orig[i].ing_length;
        }
    }
    printf("\n max : %d\n",max);
    //Decrease value of max and get all structs in order (to a pointer array)
    int i = 0;
    for(int k = max; k >= 0; k--){
        for(int j = 0; j < len; j++){
            if(orig[j].ing_length == k){
                sorted_pizza[i] = &orig[j];
                i++;
                //printf("%d",orig[j].ing_length);
            }
        }
    }
    printf("done");
    //return new_pizza;
}
