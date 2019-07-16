#include "bacteria.h"
#include "lib.h"
Bacteria::Bacteria(Water* water,uint16_t x,uint16_t y,int32_t energy,const Bacteria* parent)
    :water(water),
    genome(new Genome(this,parent)),
    x(x),
    y(y),
    energy(energy),
    attack(genome->GetAttack()),
    parent(parent),
    birth_time(water->GetTime())
{
}
void Bacteria::Tick(){
    DoAction();
    if(water->GetTime()%25==0){
        killer=0;
    }
    if(energy> genome->GetMaxEnergy() && water->forced_cloning){
        Clone();
    }
    if(water->GetTime()%30==0){
        genome->Irradiate(10);
    }
    energy-=attack/5;
}
void Bacteria::TryMove(int8_t dx, int8_t dy){
    water->GetBattleField().Get(x,y).remove(this);
    uint16_t X = x + dx;
    uint16_t Y = y + dy;
    try {
        X = loop(X,water->GetWidth());
        water->GetBattleField().Get(X,Y).push_back(this);
        x = X;
        y = Y;
    } catch (int e) {
        if(e==INCORRECT_INDEX){
            water->GetBattleField().Get(x,y).push_back(this);
        }
        else{
            throw;
        }
    }
    energy -= dx*dx+dy*dy;
}
void Bacteria::Kill(bool in_cycle){
    water->GetBattleField().Get(x,y).remove(this);
    if(!in_cycle){
        water->GetAliveBacteries().remove(this);
    }
    killed=true;
    water->GetFoodField().Get(x,y)+=0;
}

void Bacteria::Clone(){
    int dx = 0;
    int dy = 0;
    if(genome->GetCloneNearly()){
        dx = rand()%3-1;
        dy = rand()%3-1;
    }
    water->AddBacteria(limit(x+dx,0,water->GetWidth()-1),limit(y+dy,0,water->GetHeight()-1),energy/2,this);
    energy/=2;
}

void Bacteria::Photosynthesis(){
    energy+=water->HowMuchSunEnergy(y)/static_cast<int>(water->GetBattleField().Get(x,y).size());
    energy-=3;
}

void Bacteria::DoAction()
{
    stop_action = false;
    for(int i=0;i<30;i++){
        Command cmd = genome->GetCode().at(cmd_ptr);
        int last_ptr = cmd_ptr;
        switch (cmd.cmd) {
        case Actions::move:
            cmd_Move(cmd);
            break;
        case Actions::clone:
            cmd_Clone(cmd);
            break;
        case Actions::photo:
            cmd_Photo(cmd);
            break;
        case Actions::lffood:
            cmd_LookForFood(cmd);
            break;
        case Actions::eat_food:
            cmd_EatFood(cmd);
            break;
        case Actions::lfenemy:
            cmd_LookForEnemy(cmd);
            break;
        case Actions::suicide:
            cmd_Suicide(cmd);
            break;
        case Actions::convert_atp:
            cmd_ConvertAtpToEnergy(cmd);
            break;
        case Actions::lffriend:
            cmd_LookForFriend(cmd);
            break;
        case Actions::attack:
            cmd_Attack(cmd);
            break;
        case Actions::hme:
            cmd_HowMuchEnergy(cmd);
            break;
        default:
            throw IMPOSSIBLE;
            break;
        }
        if(last_ptr==cmd_ptr) {
            cmd_ptr++;
        }
        cmd_ptr = loop(cmd_ptr,genome->code_length-1);
        if(stop_action) break;
    }
}

void TransformToCoordinates(int8_t &x,int8_t &y, uint8_t d,uint8_t size=1){
    x = d%(2*size+1)-size;
    y = d/(2*size+1)-size;
}
void Bacteria::cmd_Move(Command cmd)
{ 
    static int counter = 0;
    counter++;
    stop_action=true;
    int8_t dx,dy;
    uint8_t position = cmd.param%9;
    TransformToCoordinates(dx,dy,position);
    TryMove(dx,dy);
    cmd_ptr += cmd.offset[0];
}

void Bacteria::cmd_Photo(Command cmd)
{    
    static int counter = 0;
    counter++;
    stop_action=true;
    Photosynthesis();
    cmd_ptr += cmd.offset[0];
}

void Bacteria::cmd_Clone(Command cmd)
{
    static int counter = 0;
    counter++;
    stop_action=true;
    Clone();
    cmd_ptr += cmd.offset[0];
}

void Bacteria::cmd_LookForFood(Command cmd)
{
    static int counter = 0;
    counter++;
    int8_t dx,dy;
    uint8_t position = cmd.param%25;
    TransformToCoordinates(dx,dy,position,2);
    int off = -1000;
    try {
        if(water->GetFoodField().Get(x+dx,y+dy)!=0){
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
    static int counter = 0;
    counter++;
    int8_t dx,dy;
    uint8_t position = cmd.param%9;
    TransformToCoordinates(dx,dy,position);
    try {
        uint16_t& food = water->GetFoodField().Get(x+dx,y+dy);
        atp+=food;
        food=0;
    } catch (int e) {
        if(e!=INCORRECT_INDEX){
            throw;
        }
    }
    energy-=10;
}
bool isEnemy(QColor me,QColor other,uint16_t threshold){
    int s = 0;
    s+=abs(me.red()-other.red());
    s+=abs(me.blue()-other.blue());
    s+=abs(me.green()-other.green());
    return s>threshold;
}
void Bacteria::cmd_LookForEnemy(Command cmd)
{
    static int counter = 0;
    counter++;
    int8_t dx,dy;
    uint8_t position = cmd.param%25;
    uint16_t threshold = cmd.param;
    TransformToCoordinates(dx,dy,position,2);
    int off = 1;
    try {
        for(auto iter=water->GetBattleField().Get(x+dx,y+dy).begin();iter!=water->GetBattleField().Get(x+dx,y+dy).end();iter++){
            if(isEnemy(genome->GetColor(),(**iter).genome->GetColor(),threshold)){
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
    static int counter = 0;
    counter++;
    stop_action=true;
    water->GetFoodField().Get(x,y)+=3;
    energy=0;
}

void Bacteria::cmd_ConvertAtpToEnergy(Command cmd)
{
    static int counter = 0;
    counter++;
    if(atp>cmd.param){
        energy+=cmd.param;
        atp-=cmd.param;
    }
    else{
        energy+=atp;
        atp=0;
    }
}

void Bacteria::cmd_LookForFriend(Command cmd)
{
    static int counter = 0;
    counter++;
    int8_t dx,dy;
    uint8_t position = cmd.param%25;
    uint16_t threshold = cmd.param;
    TransformToCoordinates(dx,dy,position,2);
    int off = 1;
    try {
        for(auto iter=water->GetBattleField().Get(x+dx,y+dy).begin();iter!=water->GetBattleField().Get(x+dx,y+dy).end();iter++){
            if(!isEnemy(genome->GetColor(),(**iter).genome->GetColor(),threshold)){
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
    static int counter = 0;
    counter++;
    killer++;
    int8_t dx,dy;
    uint8_t position = cmd.param%9;
    TransformToCoordinates(dx,dy,position);
    try {
        for(auto iter=water->GetBattleField().Get(x+dx,y+dy).begin();iter!=water->GetBattleField().Get(x+dx,y+dy).end();iter++){
            (**iter).energy-=attack*2;
        }
    } catch (int e) {
        if(e!=INCORRECT_INDEX){
            throw;
        }
    }
    energy-=attack;
}

void Bacteria::cmd_HowMuchEnergy(Command cmd)
{
    static int counter = 0;
    counter++;
    int threshold = cmd.param;
    if(energy<threshold){
        cmd_ptr+=cmd.offset[0];
    }
    else{
        cmd_ptr+=cmd.offset[1];
    }
}

std::shared_ptr<Genome> Bacteria::GetGenome() const
{
    return genome;
}

void Bacteria::GetCoords(uint16_t &X, uint16_t &Y)
{
    X=x;
    Y=y;
}

int32_t Bacteria::GetEnergy()
{
    return energy;
}

uint64_t Bacteria::GetBirthTime()
{
    return birth_time;
}

uint16_t Bacteria::GetAttack()
{
    return attack;
}

void Bacteria::IncreaseEnergy(int32_t added_energy)
{
    energy+=added_energy;
}

uint8_t Bacteria::GetKiller()
{
    return killer;
}

bool Bacteria::GetKilled()
{
    return killed;
}
