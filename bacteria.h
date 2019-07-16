#pragma once

#include<QDebug>

#include "water.h"
#include "genome.h"
#include "errors.h"
#include <cmath>
class Water;
class Genome;
struct Command{
    int cmd;
    static constexpr int offset_conut = 3;
    int offset[offset_conut];
    static constexpr int command_count = 126;
    int offset_mutate_chance_10000;
    int cmd_mutate_chance_10000;
};
class Bacteria
{
protected:
    Water* water;
    int x,y;
    int energy;
    int attack;
    std::shared_ptr<Genome> genome;
    const Bacteria* parent;
    int birth_time;
    int cmd_ptr = 0;
    int COUNT_OF_ACTION = 0;
    bool stop_action;
    bool killed = false;
    int killer = 0;
    int atp = 0;
public:
    Bacteria(Water* water, int x, int y,int energy,const Bacteria* parent);
    void Tick();
    void TryMove(int dx,int dy);
    void Kill(bool in_cycle=false);
    void Clone();
    void Photosynthesis();
    void DoAction();
    void cmd_Move(Command cmd);
    void cmd_Photo(Command cmd);
    void cmd_Clone(Command cmd);
    void cmd_LookForFood(Command cmd);
    void cmd_EatFood(Command cmd);
    void cmd_LookForEnemy(Command cmd);
    void cmd_Suicide(Command cmd);
    void cmd_ConvertAtpToEnergy(Command cmd);
    void cmd_LookForFriend(Command cmd);
    void cmd_Attack(Command cmd);
    void cmd_HowMuchEnergy(Command cmd);
    friend Water;
    friend Genome;
};

