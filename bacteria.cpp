#include "bacteria.h"
#include "lib.h"
Bacteria::Bacteria(Water* water,int x,int y,int energy,const Bacteria* parent):water(water),x(x),y(y),energy(energy),genome(new Genome(this,parent)),parent(parent)
{
    attack = genome->attack;
    birth_time = water->time;
}
void Bacteria::Tick(){
    DoAction();
    if(water->time%25==0){
        killer=0;
    }
    if(energy> genome->max_energy && water->forced_cloning){
        Clone();
    }
    if(water->time%30==0){
        genome->Irradiate(10);
    }
    energy-=attack/5;
}
void Bacteria::TryMove(int dx, int dy){
    water->battle_field.Get(x,y).remove(this);
    int X = x + dx;
    int Y = y + dy;
    try {
        X = loop(X,water->width);
        water->battle_field.Get(X,Y).push_back(this);
        x = X;
        y = Y;
    } catch (int e) {
        if(e==INCORRECT_INDEX){
            water->battle_field.Get(x,y).push_back(this);
        }
        else{
            throw;
        }
    }
    energy -= dx*dx+dy*dy;
}
void Bacteria::Kill(bool in_cycle){
    water->battle_field.Get(x,y).remove(this);
    if(!in_cycle){
        water->alive_bacteries.remove(this);
    }
    killed=true;
    water->food_field.Get(x,y)+=90;
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
    energy-=3;
}

void Bacteria::DoAction()
{
    stop_action = false;
    for(int i=0;i<30;i++){
        COUNT_OF_ACTION = 0;
        Command cmd = genome->code.at(cmd_ptr);
        int last_ptr = cmd_ptr;
        cmd_Move(cmd);
        cmd_Clone(cmd);
        cmd_Photo(cmd);
        cmd_LookForFood(cmd);
        cmd_EatFood(cmd);
        cmd_LookForEnemy(cmd);
        cmd_Suicide(cmd);
        cmd_ConvertAtpToEnergy(cmd);
        cmd_LookForFriend(cmd);
        cmd_Attack(cmd);
        cmd_HowMuchEnergy(cmd);
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
    if(!in_range(cmd.cmd,0,8)){
        return;
    }
    static int counter = 0;
    counter++;
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
    static int counter = 0;
    counter++;
    COUNT_OF_ACTION++;
    stop_action=true;
    Photosynthesis();
    cmd_ptr += cmd.offset[0];
}

void Bacteria::cmd_Clone(Command cmd)
{
    if(cmd.cmd!=10) return;
    static int counter = 0;
    counter++;
    COUNT_OF_ACTION++;
    stop_action=true;
    Clone();
    cmd_ptr += cmd.offset[0];
}

void Bacteria::cmd_LookForFood(Command cmd)
{
    if(!in_range(cmd.cmd,11,35)) return;
    static int counter = 0;
    counter++;
    COUNT_OF_ACTION++;
    int dx,dy;
    TransformToCoordinates(dx,dy,cmd.cmd-11,2);
    int off = -1000;
    try {
        if(water->food_field.Get(x+dx,y+dy)!=0){
            off = 0;
        }
        else{
            off = 1;
        }
    } catch (int e) {
        if(e==INCORRECT_INDEX){
            off = 2;
        }
        else{
            throw;
        }
    }
    cmd_ptr+=cmd.offset[off];
}

void Bacteria::cmd_EatFood(Command cmd)
{
    if(!in_range(cmd.cmd,36,44)) return;
    static int counter = 0;
    counter++;
    COUNT_OF_ACTION++;
    int dx,dy;
    TransformToCoordinates(dx,dy,cmd.cmd-36,1);
    try {
        unsigned int& food = water->food_field.Get(x+dx,y+dy);
        atp+=food;
        food=0;
    } catch (int e) {
        if(e!=INCORRECT_INDEX){
            throw;
        }
    }
    energy-=10;
}
bool isEnemy(QColor me,QColor other){
    int s = 0;
    s+=abs(me.red()-other.red());
    s+=abs(me.blue()-other.blue());
    s+=abs(me.green()-other.green());
    return s>50;
}
void Bacteria::cmd_LookForEnemy(Command cmd)
{
    if(!in_range(cmd.cmd,45,69)) return;
    static int counter = 0;
    counter++;
    COUNT_OF_ACTION++;
    int dx,dy;
    TransformToCoordinates(dx,dy,cmd.cmd-45,2);
    int off = 1;
    try {
        for(auto iter=water->battle_field.Get(x+dx,y+dy).begin();iter!=water->battle_field.Get(x+dx,y+dy).end();iter++){
            if(isEnemy(genome->GetColor(),(**iter).genome->GetColor())){
                off = 0;
                break;
            }
        }
    } catch (int e) {
        if(e==INCORRECT_INDEX){
            off = 2;
        }
        else{
            throw;
        }
    }
    energy-=1;
    cmd_ptr+=cmd.offset[off];
}

void Bacteria::cmd_Suicide(Command cmd)
{
    if(cmd.cmd!=70) return;
    static int counter = 0;
    counter++;
    COUNT_OF_ACTION++;
    stop_action=true;
    water->food_field.Get(x,y)+=2*energy;
    energy=0;
}

void Bacteria::cmd_ConvertAtpToEnergy(Command cmd)
{
    if(cmd.cmd!=71) return;
    static int counter = 0;
    counter++;
    COUNT_OF_ACTION++;
    if(atp>200){
        energy+=200;
        atp-=200;
    }
    else{
        energy+=atp;
        atp=0;
    }
}

void Bacteria::cmd_LookForFriend(Command cmd)
{
    if(!in_range(cmd.cmd,72,96)) return;
    static int counter = 0;
    counter++;
    COUNT_OF_ACTION++;
    int dx,dy;
    TransformToCoordinates(dx,dy,cmd.cmd-72,2);
    int off = 1;
    try {
        for(auto iter=water->battle_field.Get(x+dx,y+dy).begin();iter!=water->battle_field.Get(x+dx,y+dy).end();iter++){
            if(!isEnemy(genome->GetColor(),(**iter).genome->GetColor())){
                off = 0;
                break;
            }
        }
    } catch (int e) {
        if(e==INCORRECT_INDEX){
            off = 2;
        }
        else{
            throw;
        }
    }
    energy-=1;
    cmd_ptr+=cmd.offset[off];
}

void Bacteria::cmd_Attack(Command cmd)
{
    if(!in_range(cmd.cmd,97,104)) return;
    static int counter = 0;
    counter++;
    killer++;
    COUNT_OF_ACTION++;
    int dx,dy;
    TransformToCoordinates(dx,dy,cmd.cmd-97,1);
    try {
        for(auto iter=water->battle_field.Get(x+dx,y+dy).begin();iter!=water->battle_field.Get(x+dx,y+dy).end();iter++){
            (**iter).energy-=attack;
        }
    } catch (int e) {
        if(e!=INCORRECT_INDEX){
            throw;
        }
    }
    energy-=10;
}

void Bacteria::cmd_HowMuchEnergy(Command cmd)
{
    if(!in_range(cmd.cmd,105,125)) return;
    static int counter = 0;
    counter++;
    COUNT_OF_ACTION++;
    int porog = (cmd.cmd-104)*(cmd.cmd-104)*40;
    if(energy<porog){
        cmd_ptr+=cmd.offset[0];
    }
    else{
        cmd_ptr+=cmd.offset[1];
    }
}
