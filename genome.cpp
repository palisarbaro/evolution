#include "genome.h"
#include "lib.h"
QColor Genome::GetColor(){
    return color;
}
int mutate_color_component(int c){
    c += rand()%5-2;
    c = limit(c,0,255);
    return c;
}
QColor Genome::init_color(){
    return QColor(rand()%256,rand()%256,rand()%256);
}
QColor Genome::mutate_color(QColor color){
    int r = mutate_color_component(color.red());
    int g = mutate_color_component(color.green());
    int b = mutate_color_component(color.blue());
    return QColor(r,g,b);
}
int Genome::init_attack(){
    return rand()%10;
}
int Genome::mutate_attack(int attack){
    return limit(attack+rand()%5-2,0,-1);
}
bool Genome::init_clone_nearly(){
    return rand()%2;
}
bool Genome::mutate_clone_nearly(bool clone_nearly){
    if(rand()%5==0){
        return !clone_nearly;
    }
    return clone_nearly;
}
Genome::Genome(Bacteria* bacteira,const Bacteria* parent): bacteria(bacteira)
{
    if(parent!=nullptr){
        color = mutate_color(parent->genome->color);
        attack = mutate_attack(parent->genome->attack);
        clone_nearly = mutate_clone_nearly(parent->genome->clone_nearly);
    }
    else{
        color = init_color();
        attack = init_attack();
        clone_nearly = init_clone_nearly();
    }
}
