#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getIntersect (char * ar1, char * ar2,int x,int y,int z){
    int intersect = 0;
    printf("%d %s %d %d\n",x,(ar1+0*y),strlen((ar1+0*y)),strcmp((ar1+1*y),(ar2+0*y)));
    for(int i = 0; i < x; i++){
        if(strlen((ar1+0*y)) == 0){
            break;
        }
        for(int j = 0; j < z; j++){
            if(strlen((ar2+j*y)) == 0){
                break;
            }
            printf("\n%s",(ar2+j*y));
            if(strcmp((ar1+i*y),(ar2+j*y)) == 0){
                intersect++;
                break;
            }
        }
    }
    return intersect;
};
typedef struct{
    char ing[5][10];
}piz;
int main()
{
    piz * pizza1 = {{
        "cheese",
        "chicken",
        "basil",
        "peparoni"
    }};
    piz * pizza2 = {{
        "cheese",
        "carrot",
        "chicken",
        "beef",
        "peparoni"
    }};

    //printf("%d\n",sizeof(arr)/sizeof(arr[0]));
    int out = getIntersect((char *)pizza1->ing,(char *)pizza2->ing,5,10,5);
    printf("inter %d\n",out);
    /*int equal;
    int len = 10;
    for(int i = 0; i < len; i++){
        if(strlen(arr[i]) == 0){
            break;
        }
        printf("%s ",arr[i]);
        printf("%d\n",strcmp(arr[i],arr2[i]));
    }
    for(int i = 0; i < sizeof(arr); i++){
        if(strlen(arr[i]) == 0){
            break;
        }
        for(int j = 0; j < sizeof(arr2); j++){
            if(strlen(arr2[j]) == 0){
                break;
            }
            if(strcmp(arr[i],arr2[j]) == 0){
                    equal++;
                //strcpy(equal[i],arr[i]);
                //equal[i] == arr[i];
                break;
            }
        }
    }
    printf("%d\n",equal);*/
    /*for(int i = 0; i < sizeof(equal); i++){
        if(strlen(equal[i]) == 0){
            break;
        }
        printf("%s\n",equal[i]);
    }*/
    printf("ok");
    return 0;
}
