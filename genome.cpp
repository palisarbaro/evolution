#include "genome.h"
QColor Genome::GetColor(){
    return color;
}

int mutate_color_component(int c){
    c += rand()%5-2;
    if(c<0) {
        c = 0;
    }
    if(c>255){
        c = 255;
    }
    return c;
}
Genome::Genome(Bacteria* bacteira,const Bacteria* parent): bacteria(bacteira)
{
    if(parent!=nullptr){
        int r = mutate_color_component(parent->genome->color.red());
        int g = mutate_color_component(parent->genome->color.green());
        int b = mutate_color_component(parent->genome->color.blue());
        color = QColor(r,g,b);
    }
    else{
        color = QColor(rand()%256,rand()%256,rand()%256);
    }
}
