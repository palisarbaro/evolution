#include "water.h"
#include "lib.h"
#include <QDebug>
Water::Water(int width,int height):time(0),width(width),height(height),View(new Matrix<QColor>(width,height)),battle_field(width,height),food_field(width,height)
{
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            View->Set(i,j,Qt::blue);
            food_field.Set(i,j,0);
            if((i+j)%2==0 && j<50){
                food_field.Set(i,j,100);
            }
        }
    }
}

int Water::GetWidth()
{
    return width;
}
int Water::GetHeight(){
    return height;
}
std::shared_ptr<Matrix<QColor>> Water::GetView(){
    return View;
}
void Water::AddBacteria(int x,int y,int energy,Bacteria* parent){
    if(!battle_field.isCoordinatesCorrect(x,y)){
        throw IMPOSSIBLE;
    }
    std::shared_ptr<Bacteria> backt(new Bacteria(this,x,y,energy,parent));

    all_bacteries.push_back(backt);
    alive_bacteries.push_back(backt.get());

    battle_field.Get(x,y).push_back(backt.get());
}
int Water::HowMuchSunEnergy(int depth){
    int energy = 12-depth;
    if(energy<0){
        energy=0;
    }
    return energy;
}
void Water::UpdateView(int display_method){
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            QColor res;
            if(food_field.Get(i,j)!=0){
                res = Qt::yellow;
            }
            else if(!battle_field.Get(i,j ).empty()){
                Bacteria* bact = battle_field.Get(i,j).front();
                if(display_method==0){
                    res = bact->genome->GetColor();
                }
                else if(display_method==1){
                    int val = limit(bact->energy,0,255);
                    res = QColor(val,val,val);
                }
            }
            else{
                int rg = HowMuchSunEnergy(j)*10+50;
                res = QColor(rg,rg,255);
            }
            View->Set(i,j,res);
        }
    }
}

void Water::Battle(){
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            int sum_damage = 0;
            for (auto iter=battle_field.Get(i,j).begin();iter!=battle_field.Get(i,j).end();iter++) {
                sum_damage += (**iter).attack + 0; ////  +5
             }
            for (auto iter=battle_field.Get(i,j).begin();iter!=battle_field.Get(i,j).end();iter++) {
                (**iter).energy-=(sum_damage-(**iter).attack - 0); ////  -5
            }
        }
    }
}
void Water::Eating(){
    for(auto iter=alive_bacteries.begin();iter!=alive_bacteries.end();iter++){
        int x = (**iter).x;
        int y = (**iter).y;
        if(food_field.Get(x,y)!=0){
            if(battle_field.Get(x,y).empty()){
                throw IMPOSSIBLE;
            }
            auto winner = battle_field.Get(x,y).begin();
            for(auto jter=battle_field.Get(x,y).begin();jter!=battle_field.Get(x,y).end();jter++){
                if((**winner).attack<(**jter).attack){
                    winner = jter;
                }
            }
            (**winner).energy+=food_field.Get(x,y);
            food_field.Set(x,y,0);
        }
    }
}

void Water::Tick(){
    all_bacteries.remove_if([](std::shared_ptr<Bacteria> bact){return bact->killed;});
    time++;
    for(auto iter=alive_bacteries.begin();iter!=alive_bacteries.end();iter++){
        (**iter).Tick();
        (**iter).energy-=(**iter).spent_energy;
        if((**iter).energy<=0) (**iter).Kill(true);
    }
    alive_bacteries.remove_if([](Bacteria* bact){return bact->killed;});
    Battle();
    for(auto iter=alive_bacteries.begin();iter!=alive_bacteries.end();iter++){
        if((**iter).energy<=0) (**iter).Kill(true);
    }
    alive_bacteries.remove_if([](Bacteria* bact){return bact->killed;});
    Eating();
    if(true){
        qDebug()<<"fps:"<<1000./(clock()-last_frame);
        last_frame = clock();
        qDebug()<<"all:"<<all_bacteries.size();
        qDebug()<<"alive:"<<alive_bacteries.size();
        int max_life_time = -1;
        int max_energy = -1;
        for(auto iter=alive_bacteries.begin();iter!=alive_bacteries.end();iter++){
            int lt = time-(**iter).birth_time;
            if(max_life_time<lt) max_life_time = lt;
            if(max_energy<(**iter).energy) max_energy=(**iter).energy;
        }
        qDebug()<<"max_life_time:"<<max_life_time;
        qDebug()<<"max_energy:"<<max_energy;
        qDebug()<<"time:"<<time;
    }
}
