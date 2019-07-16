#include"lib.h"
#include <cstdlib>
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

bool in_range(int x, int min, int max)
{
    return x>=min && x<=max;
}

int mutate(int x,int min,int max,int max_delta){
    return limit(x+rand()%(2*max_delta+1)-max_delta,min,max);
}
