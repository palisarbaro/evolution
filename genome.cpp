#include "genome.h"
#include "lib.h"
QColor Genome::GetColor(){
    return color;
}

uint16_t Genome::GetAttack()
{
    return attack;
}

bool Genome::GetCloneNearly()
{
    return clone_nearly;
}

uint16_t Genome::GetMaxEnergy()
{
    return max_energy;
}

const std::vector<Command> &Genome::GetCode()
{
    return code;
}

void Genome::SetBacteria(std::weak_ptr<Bacteria> bact)
{
    bacteria=bact;
}

int mutate_color_component(int c){
    return mutate(c,0,255,5);
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
uint16_t Genome::init_attack(){
    return rand()%10;
}
uint16_t Genome::mutate_attack(uint16_t attack){
    return mutate(attack,10,-1,2);
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

void Genome::Irradiate(uint8_t percent)
{
    int full_change_1000 = percent/10;
    if(rand()%100<percent){
        color = mutate_color(color);
    }
    if(rand()%100<percent){
        attack = mutate_attack(attack);
    }
    if(rand()%100<percent){
        clone_nearly = mutate_clone_nearly(clone_nearly);
    }
    if(rand()%100<percent){
        code = mutate_code(code);
    }
    /////
    if(rand()%1000<full_change_1000){
        attack = init_attack();
    }
    for(auto iter = code.begin();iter!=code.end();iter++){
        if(rand()%1000<full_change_1000){
            (*iter).cmd_mutate_chance_10000 = rand()%10000;
        }
        if(rand()%1000<full_change_1000){
            (*iter).offset_mutate_chance_10000 = rand()%10000;
        }
    }




}
Command mutate_command(Command cmd){
    if(rand()%10000<cmd.cmd_mutate_chance_10000){
        cmd.cmd = rand()%Actions::count_of_actions;
    }
    if(rand()%10000<cmd.cmd_mutate_chance_10000){
        cmd.param = mutate(cmd.param,0,UINT16_MAX,3);
    }
    cmd.cmd_mutate_chance_10000=mutate(cmd.cmd_mutate_chance_10000,0,10000,10);
    for(int i=0;i<Command::offset_conut;i++){
        if(rand()%10000<cmd.offset_mutate_chance_10000){
            cmd.offset[i] = rand()%Genome::code_length;
        }
    }
    cmd.offset_mutate_chance_10000=mutate(cmd.offset_mutate_chance_10000,0,10000,10);

    return cmd;
}
std::vector<Command> Genome::init_code(){
    for(int i=0;i<code_length;i++){
        Command cmd;
        cmd.cmd_mutate_chance_10000 = rand()%10000;
        cmd.offset_mutate_chance_10000 = rand()%10000;
        cmd.cmd = rand()%Actions::count_of_actions;
        if(rand()%5==0) cmd.cmd = Actions::clone;
        if(rand()%5==0) cmd.cmd = Actions::photo;
        cmd.param = rand()%UINT16_MAX;
        for(int i=0;i<Command::offset_conut;i++){
            cmd.offset[i]=limit(rand()%64,0,code_length-1);
        }
        code.push_back(cmd);
    }
    return code;
}
std::vector<Command> Genome::mutate_code(std::vector<Command> code){
    for(unsigned int i=0;i<code_length;i++){
        code.at(i) = mutate_command(code.at(i));
    }
    return code;
}
Genome::Genome(std::weak_ptr<Bacteria> parent)
{
    if(!parent.expired()){
        color = mutate_color(parent.lock()->GetGenome()->color);
        attack = mutate_attack(parent.lock()->GetGenome()->attack);
        clone_nearly = mutate_clone_nearly(parent.lock()->GetGenome()->clone_nearly);
        code = mutate_code(parent.lock()->GetGenome()->code);
    }
    else{
        color = init_color();
        attack = init_attack();
        clone_nearly = init_clone_nearly();
        code = init_code();
    }
}
