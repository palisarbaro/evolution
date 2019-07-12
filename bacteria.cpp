#include "bacteria.h"
#include "lib.h"
Bacteria::Bacteria(Water* water,int x,int y,int energy,const Bacteria* parent):water(water),x(x),y(y),energy(energy),genome(new Genome(this,parent)),parent(parent)
{
    attack = genome->attack;
}
void Bacteria::Tick(){
    spent_energy = 0;
    if(rand()%2==1){
        TryMove(1,0);
    }
    else{
        TryMove(-1,0);
    }
    if(energy>100){
        Clone();
    }
    spent_energy = 1;
}
void Bacteria::TryMove(int dx, int dy){
    water->battle_field.Get(x,y).remove(this);
    x+=dx;
    y+=dy;
    try {
        water->battle_field.Get(x,y).push_back(this);
    } catch (int e) {
        if(e==INCORRECT_INDEX){
            x-=dx;
            y-=dy;
            water->battle_field.Get(x,y).push_back(this);
        }
        else{
            throw;
        }
    }
}
void Bacteria::Kill(){
    water->battle_field.Get(x,y).remove(this);
    water->alive_bacteries.remove(std::shared_ptr<Bacteria>(this));
    water->food_field.Get(x,y)+=10;
}

void Bacteria::Clone(){
    int dx = 0;
    int dy = 0;
    if(genome->clone_nearly){
        dx = rand()%3-1;
        dy = rand()%3-1;
    }
    water->AddBacteria(limit(x+dx,0,water->width-1),limit(y+dy,0,water->height-1),energy/2,this);
    energy/=2;
}
