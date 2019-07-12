#include"lib.h"
int limit(int x,int min,int max){
    if(x<min && min!=-1){
        x=min;
    }
    if(x>max && max!=-1){
        x=max;
    }
    return x;
}
