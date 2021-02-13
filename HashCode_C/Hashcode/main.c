#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int index;
    int ing_length;
    char ingredients[10000][20];
}piz;
//piz sortPizzas()
int main()
{
    piz *pizza;
    pizza = malloc(100000 * sizeof(piz));

    //Open the file
    FILE *fptr;
    fptr = fopen("b_little_bit_of_everything.in","r");

    //Check if file is open
    if(fptr == NULL){
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
        //(fptr,"%d %s",&next,&next2);
        //fgets(next2,100,fptr);
        //break;
        f_index++;
    }
    //printf("%d",f_args[0]);
    for(int i = 0; i < 4; i++){
        printf("%d ",f_args[i]);
    }
    //printf("\n%d %s\n",next,next2);
    //strcpy(pizza[0].ingredients[0], "lol");
    //strcpy(pizza[0].ingredients[1], "lol2");
    //printf("\n%d %s %s %s %s",pizza[0].ing_length,pizza[0].ingredients[0],pizza[0].ingredients[1],pizza[0].ingredients[2],pizza[0].ingredients[3]);
    for(int i = 0; i<f_index; i++){
        printf("\n%s",pizza[i].ingredients[0]);
    }
    printf("\n%d",f_index);
    getchar();
    return 0;
}
