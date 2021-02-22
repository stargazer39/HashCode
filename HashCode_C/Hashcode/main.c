#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIZZA 100000
#define MAX_ING 10000
#define MAX_ING_X4 40000
//Structure of a pizza
typedef struct {
    int index;
    int ing_length;
    int active;
    char ingredients[MAX_ING][20];
}piz;

void sortPizza (piz * orig,piz * sorted_pizza[],int len);
int getIntersect (char * ar1, char * ar2,int x,int y);
int getNextUniquePizza(piz * sortPizza[],char * uni_ing,int len,int last);
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
    fptr = fopen("a_example.in","r");
    fptr2 = fopen("ex0.sorted.out","w");
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

    char uni_ing[MAX_ING_X4][20];
    int last = -1;
    int index = 0;
    int j_now = 0;
    for(int i = 0; i<2; i++){
        int output;
        if(j_now == 0){
            output = getNextUniquePizza(sorted_pizza,sorted_pizza[0]->ingredients,f_index,last);
            last = 0;
            printf("\n---------");
        }else{
            output = getNextUniquePizza(sorted_pizza,uni_ing,f_index,output);
            printf("\n---------");
        }
        for(int k = 0; k<MAX_ING; k++){
            if(strlen(sorted_pizza[output]->ingredients[k]) == 0){
                break;
            }
            printf("%s ",sorted_pizza[output]->ingredients[k]);
            strcpy(uni_ing[j_now],sorted_pizza[output]->ingredients[k]);
            j_now++;
        }
        printf("\nlol %d\n",output);
    }
    //Print everything to a file
    for(int i = 0; i<f_index; i++){
        int tmp_length = sorted_pizza[i]->ing_length;
        fprintf(fptr2,"%d ",tmp_length);
        for(int j = 0; j<tmp_length; j++){
            fprintf(fptr2,"%s ",sorted_pizza[i]->ingredients[j]);
        }
        fprintf(fptr2,"\n");
        //printf("\n%d",sorted_pizza[i]->ing_length);
    }
    printf("\n%d\n",f_index);

    //printf("inter %d\n",getIntersect((char *)pizza[0].ingredients,(char *)sorted_pizza[0]->ingredients,MAX_ING,20));
    fclose(fptr2);
    fclose(fptr);
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
int getNextUniquePizza(piz * sortPizza[],char * uni_ing,int len,int last){
    int tmp_inter;
    int index = NULL;
    if(sortPizza[0]->active != -1){
        sortPizza[0]->active = -1;
        //printf("getNextUniquePizza return 0 %d\n",sortPizza[0]->active);
        return 0;
    }else{
        for(int i = 0; i<len; i++){
            if(sortPizza[i]->active == -1){
                //printf("getNextUniquePizza sortPizza[i]->active == -1 1 %d\n",i);
                continue;
            }
            for(int j = 0; j<len;j++){
                if(sortPizza[j]->active == -1){
                    //printf("getNextUniquePizza sortPizza[j]->active == -1 2 %d\n",j);
                    continue;
                }
                int inter = getIntersect((char *)sortPizza[0]->ingredients,(char *)uni_ing,MAX_ING,20);
                //printf("getNextUniquePizza getIntersect %d\n",inter);
                if(j == 0){
                    tmp_inter = inter;
                    index = j;
                    printf("getNextUniquePizza if(j == 0) %d\n",j);
                    continue;
                }
                if(inter == 0){
                    sortPizza[j]->active = -1;
                    //printf("getNextUniquePizza sortPizza[j]->active = -1; %d\n",j);
                    return j;
                }
                if(tmp_inter > inter){
                    tmp_inter = inter;
                    index = j;
                }
            }
        }
        if(last == index){
            for(int k = 0; k < len; k++){
                if(sortPizza[k]->active != -1){
                    return k;
                }
            }
        }
        //printf("getNextUniquePizza return index; %d\n",index);
        return index;
    }
    //printf("\ndebug %d",sortPizza[0]->ing_length);
    return -1;
}
int getIntersect (char * ar1, char * ar2,int x,int y){
    int intersect = 0;
    //printf("debug %d %s %d %d\n",x,(ar1+0*y),strlen((ar1+0*y)),strcmp((ar1+1*y),(ar2+0*y)));
    for(int i = 0; i < x; i++){
        if(strlen((ar1+0*y)) == 0){
            break;
        }
        for(int j = 0; j < x; j++){
            if(strlen((ar2+j*y)) == 0){
                break;
            }
            if(strcmp((ar1+i*y),(ar2+j*y)) == 0){
                intersect++;
                break;
            }
        }
    }
    return intersect;
};
