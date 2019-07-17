#include "bacteria.h"
#include "lib.h"

int16_t Bacteria::move_energy = 0;
int16_t Bacteria:: photo_enery = 0;
int16_t Bacteria::clone_energy= 0;
int16_t Bacteria::lffood_energy= 0;
int16_t Bacteria::eat_food_energy= 0;
int16_t Bacteria::lfenemy_energy = 0;
int16_t Bacteria::suicide_energy= 0;
int16_t Bacteria::convert_atp_energy= 0;
int16_t Bacteria::lffriend_energy= 0;
int16_t Bacteria::attack_energy= 0;
int16_t Bacteria::hme_energy= 0;
int16_t Bacteria::heal_energy= 0;

Bacteria::Bacteria(std::weak_ptr<Water> water,uint16_t x,uint16_t y,int32_t energy,int16_t hp,std::weak_ptr<Bacteria> parent)
    :water(water),
    genome(new Genome(parent)),
    x(x),
    y(y),
    energy(energy),
    hp(hp),
    attack(genome->GetAttack()),
    birth_time(water.lock()->GetTime())
{
}
void Bacteria::Tick(){
    if(energy>1000){
        energy/=2;
    }
    DoAction();
    killer = limit(killer-1,0,255);
    if(energy> genome->GetMaxEnergy() && water.lock()->forced_cloning){
        energy = genome->GetMaxEnergy();
        if(genome->GetCloneNearly()){
            Clone(rand()%3-1,rand()%3-1);
        }
        else{
            Clone(0,0);
        }
    }
    if(water.lock()->GetTime()%30==0){
        genome->Irradiate(10);
    }
    energy-=attack/5;
    if(energy<0){
        hp += energy*3;
        energy=0;
    }
    if(hp>MAX_HP) hp = MAX_HP;
}
void Bacteria::TryMove(int8_t dx, int8_t dy){
    water.lock()->GetBattleField().Get(x,y).remove(static_cast<std::shared_ptr<Bacteria>>(self));
    //water.lock()->GetBattleField().Get(x,y).remove_if([this](std::shared_ptr<Bacteria> bact){return bact.get()==this;});
    uint16_t X = x + dx;
    uint16_t Y = y + dy;
    try {
        X = loop(X,water.lock()->GetWidth());
        water.lock()->GetBattleField().Get(X,Y).push_back(static_cast<std::shared_ptr<Bacteria>>(self));
        x = X;
        y = Y;
    } catch (int e) {
        if(e==INCORRECT_INDEX){
            water.lock()->GetBattleField().Get(x,y).push_back(static_cast<std::shared_ptr<Bacteria>>(self));
        }
        else{
            throw;
        }
    }
    energy -= dx*dx+dy*dy;
}
void Bacteria::Kill(){
    water.lock()->GetBattleField().Get(x,y).remove(static_cast<std::shared_ptr<Bacteria>>(self));
    killed=true;
    water.lock()->GetFoodField().Get(x,y)+=energy;
}

void Bacteria::Clone(int8_t dx,int8_t dy){
    water.lock()->AddBacteria(limit(x+dx,0,water.lock()->GetWidth()-1),limit(y+dy,0,water.lock()->GetHeight()-1),energy/2,hp/2,self);
    energy/=2;
    hp/=2;
}

void Bacteria::Photosynthesis(){
    energy+=water.lock()->HowMuchSunEnergy(y)/static_cast<int>(water.lock()->GetBattleField().Get(x,y).size());
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
            energy-=move_energy;
            break;
        case Actions::clone:
            cmd_Clone(cmd);
            energy-=clone_energy;
            break;
        case Actions::photo:
            cmd_Photo(cmd);
            energy-=photo_enery;
            break;
        case Actions::lffood:
            cmd_LookForFood(cmd);
            energy-=lffood_energy;
            break;
        case Actions::eat_food:
            cmd_EatFood(cmd);
            energy-=eat_food_energy;
            break;
        case Actions::lfenemy:
            cmd_LookForEnemy(cmd);
            energy-=lfenemy_energy;
            break;
        case Actions::suicide:
            cmd_Suicide(cmd);
            energy-=suicide_energy;
            break;
        case Actions::convert_atp:
            cmd_ConvertAtpToEnergy(cmd);
            energy-=convert_atp_energy;
            break;
        case Actions::lffriend:
            cmd_LookForFriend(cmd);
            energy-=lffriend_energy;
            break;
        case Actions::attack:
            cmd_Attack(cmd);
            energy-=attack_energy;
            break;
        case Actions::hme:
            cmd_HowMuchEnergy(cmd);
            energy-=hme_energy;
            break;
        case Actions::heal:
            cmd_Heal(cmd);
            energy-=heal_energy;
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
    int8_t dx,dy;
    uint8_t position = cmd.param%25;
    TransformToCoordinates(dx,dy,position,2);
    if(water.lock()->GetTime()-birth_time>10){
        Clone(dx,dy);

    }
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
        if(water.lock()->GetFoodField().Get(x+dx,y+dy)!=0){
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
        uint16_t& food = water.lock()->GetFoodField().Get(x+dx,y+dy);
        energy+=food;
        food=0;
    } catch (int e) {
        if(e!=INCORRECT_INDEX){
            throw;
        }
    }
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
    uint16_t threshold = cmd.param%300;
    TransformToCoordinates(dx,dy,position,2);
    int off = 1;
    try {
        for(auto iter=water.lock()->GetBattleField().Get(x+dx,y+dy).begin();iter!=water.lock()->GetBattleField().Get(x+dx,y+dy).end();iter++){
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
    cmd_ptr+=cmd.offset[off];
}

void Bacteria::cmd_Suicide(Command cmd)
{
    Q_UNUSED(cmd);
    static int counter = 0;
    counter++;
    stop_action=true;
    //water.lock()->GetFoodField().Get(x,y)+=50;
    hp=-1;
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
    uint16_t threshold = cmd.param%300;
    TransformToCoordinates(dx,dy,position,2);
    int off = 1;
    try {
        for(auto iter=water.lock()->GetBattleField().Get(x+dx,y+dy).begin();iter!=water.lock()->GetBattleField().Get(x+dx,y+dy).end();iter++){
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
    cmd_ptr+=cmd.offset[off];
}

void Bacteria::cmd_Attack(Command cmd)
{
    static int counter = 0;
    counter++;
    killer+=5;
    int8_t dx,dy;
    uint8_t position = cmd.param%9;
    TransformToCoordinates(dx,dy,position);
    try {
        for(auto iter=water.lock()->GetBattleField().Get(x+dx,y+dy).begin();iter!=water.lock()->GetBattleField().Get(x+dx,y+dy).end();iter++){
            (**iter).hp-=attack*2;
        }
    } catch (int e) {
        if(e!=INCORRECT_INDEX){
            throw;
        }
    }
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

void Bacteria::cmd_Heal(Command cmd)
{
    static int counter = 0;
    counter++;
    int added = cmd.param%10+5;
    if(energy>added){
        hp+=added;
        energy-=added;
    }
    else{
        hp+=energy;
        energy=0;
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

void Bacteria::SetSelf(std::weak_ptr<Bacteria> bact)
{
    self=bact;
    genome->SetBacteria(bact);
}

int16_t Bacteria::GetHP()
{
    return hp;
}

void Bacteria::IncreaseHP(int16_t added_hp)
{
    hp += added_hp;
}

