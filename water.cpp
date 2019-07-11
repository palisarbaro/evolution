#include "water.h"
#include <QDebug>
Water::Water(int width,int height):width(width),height(height),View(new Matrix<QColor>(width,height)),battle_field(width,height)
{
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            View->Set(i,j,Qt::blue);
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
    std::shared_ptr<Bacteria> backt(new Bacteria(this,x,y,energy,parent));

    all_bacteries.push_back(backt);
    alive_bacteries.push_back(backt);

    battle_field.Get(x,y).push_back(backt.get());
}
int Water::HowMuchSunEnergy(int depth){
    int energy = 12-depth;
    if(energy<0){
        energy=0;
    }
    return energy;
}
void Water::UpdateView(){
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            QColor res;
            if(!battle_field.Get(i,j ).empty()){
                res = battle_field.Get(i,j).back()->genome->GetColor();
            }
            else{
                res = Qt::blue;
            }
            View->Set(i,j,res);
        }
    }

}
void Water::Tick(){
    for(auto iter=alive_bacteries.begin();iter!=alive_bacteries.end();iter++){
        (**iter).Tick();
        (**iter).energy-=(**iter).spent_energy;
        if((**iter).energy<=0) (**iter).Kill();
    }

}
