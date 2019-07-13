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

int loop(int x, int max)
{
    x = x%max;
    if(x<0) x+=max;
    return x;
}
