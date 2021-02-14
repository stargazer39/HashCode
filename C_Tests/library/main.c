#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getIntersect (char * ar1, char * ar2,int x,int y){
    int intersect = 0;
    printf("%d %s %d %d\n",x,(ar1+0*x),strlen((ar1+0*x)),strcmp((ar1+1*x),(ar2+0*x)));
    for(int i = 0; i < x; i++){
        if(strlen((ar1+0*x)) == 0){
            break;
        }
        for(int j = 0; j < x; j++){
            if(strlen((ar2+j*x)) == 0){
                break;
            }
            if(strcmp((ar1+i*x),(ar2+j*x)) == 0){
                intersect++;
                break;
            }
        }
    }
    return intersect;
};
int main()
{
    char arr[10][10] = {
        "cheese",
        "chicken",
        "basil",
        "peparoni"
    };
    char arr2[10][10] = {
        "cheese",
        "carrot",
        "chicken",
        "beef"
    };
    //printf("%d\n",sizeof(arr)/sizeof(arr[0]));
    int out = getIntersect((char *)arr,(char *)arr2,10,10);
    printf("inter %d\n",out);
    int equal;
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
    printf("%d\n",equal);
    /*for(int i = 0; i < sizeof(equal); i++){
        if(strlen(equal[i]) == 0){
            break;
        }
        printf("%s\n",equal[i]);
    }*/
    printf("ok");
    return 0;
}
