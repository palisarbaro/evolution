#include "water.h"
#include "lib.h"
#include <QDebug>
Water::Water(uint16_t width,uint16_t height)
    :time(0),
    width(width),
    height(height),
    View(new Matrix<QColor>(width,height)),
    battle_field(width,height),
    food_field(width,height)
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

uint16_t Water::GetWidth()
{
    return width;
}
uint16_t Water::GetHeight(){
    return height;
}
std::shared_ptr<Matrix<QColor>> Water::GetView(){
    return View;
}

uint64_t Water::GetTime()
{
    return time;
}

Matrix<uint16_t> &Water::GetFoodField()
{
    return food_field;
}

Matrix<std::list<std::shared_ptr<Bacteria >> > &Water::GetBattleField()
{
    return battle_field;
}

std::list<std::shared_ptr<Bacteria>> &Water::GetAliveBacteries()
{
    return alive_bacteries;
}

void Water::SetSelf(std::weak_ptr<Water> i)
{
    self = i;
}
void Water::AddBacteria(uint16_t x,uint16_t y,int32_t energy,std::weak_ptr<Bacteria> parent){
    if(!battle_field.isCoordinatesCorrect(x,y)){
        throw IMPOSSIBLE;
    }
    std::shared_ptr<Bacteria> backt(new Bacteria(self,x,y,energy,parent));
    backt->SetSelf(backt);
    all_bacteries.push_back(backt);
    alive_bacteries.push_back(backt);
    battle_field.Get(x,y).push_back(backt);
}
int32_t Water::HowMuchSunEnergy(uint16_t depth){
    int max = 40+sin(2*3.14*time/800.)*15;
    int energy = max-depth;
    if(energy<0){
        energy=0;
    }
    return energy;
}
void Water::UpdateView(uint8_t display_method){
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            QColor res;
            if(!battle_field.Get(i,j ).empty()){
                std::shared_ptr<Bacteria> bact = battle_field.Get(i,j).front();
                if(display_method==0){
                    res = bact->GetGenome()->GetColor();
                }
                else if(display_method==1){
                    int val = limit(bact->GetEnergy(),0,255);
                    res = QColor(val,val,val);
                }
                else if(display_method==2){
                    int val = limit(bact->GetKiller(),0,255);
                    res = QColor(val,0,0);
                }
            }
            else if(food_field.Get(i,j)!=0 && food_display){
                res = Qt::yellow;
            }
            else{
                int rg = HowMuchSunEnergy(j)*255/75;
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
                sum_damage += (**iter).GetAttack(); ////  +5
             }
            for (auto iter=battle_field.Get(i,j).begin();iter!=battle_field.Get(i,j).end();iter++) {
                (**iter).IncreaseEnergy(-sum_damage + (**iter).GetAttack()); ////  -5
            }
        }
    }
}
void Water::Eating(){
    for(auto iter=alive_bacteries.begin();iter!=alive_bacteries.end();iter++){
        uint16_t x,y;
        (**iter).GetCoords(x,y);
        if(food_field.Get(x,y)!=0){
            if(battle_field.Get(x,y).empty()){
                throw IMPOSSIBLE;
            }
            auto winner = battle_field.Get(x,y).begin();
            for(auto jter=battle_field.Get(x,y).begin();jter!=battle_field.Get(x,y).end();jter++){
                if((**winner).GetAttack()<(**jter).GetAttack()){
                    winner = jter;
                }
            }
            (**winner).IncreaseEnergy(food_field.Get(x,y));
            food_field.Set(x,y,0);
        }
    }
}

void Water::Tick(){
    if(time%500==499) forced_cloning=false;
    all_bacteries.remove_if([](std::shared_ptr<Bacteria> bact){return bact->GetKilled();});
    time++;
    for(auto iter=alive_bacteries.begin();iter!=alive_bacteries.end();iter++){
        (**iter).Tick();
        if((**iter).GetEnergy()<=0) (**iter).Kill();
    }
    alive_bacteries.remove_if([](std::shared_ptr<Bacteria> bact){return bact->GetKilled();});
    Battle();
    for(auto iter=alive_bacteries.begin();iter!=alive_bacteries.end();iter++){
        if((**iter).GetEnergy()<=0) (**iter).Kill();
    }
    alive_bacteries.remove_if([](std::shared_ptr<Bacteria> bact){return bact->GetKilled();});
    //Eating();
    if(true){
        qDebug()<<"fps:"<<1000./(clock()-last_frame);
        last_frame = clock();
        qDebug()<<"all:"<<all_bacteries.size();
        qDebug()<<"alive:"<<alive_bacteries.size();
        int max_life_time = -1;
        int max_energy = -1;
        int max_attack = -1;
        for(auto iter=alive_bacteries.begin();iter!=alive_bacteries.end();iter++){
            int lt = time-(**iter).GetBirthTime();
            if(max_life_time<lt) max_life_time = lt;
            if(max_energy<(**iter).GetEnergy()) max_energy=(**iter).GetEnergy();
            if(max_attack<(**iter).GetAttack()) max_attack=(**iter).GetAttack();
        }
        qDebug()<<"max_life_time:"<<max_life_time;
        qDebug()<<"max_energy:"<<max_energy;
        qDebug()<<"max_attack:"<<max_attack;
        qDebug()<<"time:"<<time;
    }
}
