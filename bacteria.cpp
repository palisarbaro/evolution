#include "bacteria.h"
#include "lib.h"
Bacteria::Bacteria(Water* water,int x,int y,int energy,const Bacteria* parent):water(water),x(x),y(y),energy(energy),genome(new Genome(this,parent)),parent(parent)
{
    attack = genome->attack;
    birth_time = water->time;
}
void Bacteria::Tick(){
    spent_energy = 0;
    DoAction();
    if(energy> genome->max_energy){
        Clone();
    }
    genome->Irradiate(10);
    spent_energy+=attack/5;
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
    spent_energy = dx*dx+dy*dy;
}
void Bacteria::Kill(bool in_cycle){
    water->battle_field.Get(x,y).remove(this);
    if(!in_cycle){
        water->alive_bacteries.remove(this);
    }
    killed=true;
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

void Bacteria::Photosynthesis(){
    energy+=water->HowMuchSunEnergy(y)/water->battle_field.Get(x,y).size();
    spent_energy+=3;
}

void Bacteria::DoAction()
{
    stop_action = false;
    for(int i=0;i<10;i++){
        COUNT_OF_ACTION = 0;
        Command cmd = genome->code.at(cmd_ptr);
        int last_ptr = cmd_ptr;
        cmd_Move(cmd);
        cmd_Clone(cmd);
        cmd_Photo(cmd);
        if(last_ptr==cmd_ptr) {
            cmd_ptr++;
        }
        if(COUNT_OF_ACTION>1){
            throw IMPOSSIBLE;
        }
        cmd_ptr = loop(cmd_ptr,genome->code_length-1);
        if(stop_action) break;
    }
}

void TransformToCoordinates(int &x,int &y, int d,int size=1){
    x = d%(2*size+1)-size;
    y = d/(2*size+1)-size;
}

void Bacteria::cmd_Move(Command cmd)
{
    if(cmd.cmd>8){
        return;
    }
    COUNT_OF_ACTION++;
    stop_action=true;
    int dx,dy;
    TransformToCoordinates(dx,dy,cmd.cmd-0);
    TryMove(dx,dy);
    cmd_ptr += cmd.offset[0];
}

void Bacteria::cmd_Photo(Command cmd)
{
    if(cmd.cmd!=9) return;
    COUNT_OF_ACTION++;
    stop_action=true;
    Photosynthesis();
    cmd_ptr += cmd.offset[0];
}

void Bacteria::cmd_Clone(Command cmd)
{
    if(cmd.cmd!=10) return;
    COUNT_OF_ACTION++;
    stop_action=true;
    Clone();
    cmd_ptr += cmd.offset[0];
}
