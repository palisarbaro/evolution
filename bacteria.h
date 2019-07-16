#pragma once

#include<QDebug>

#include "water.h"
#include "genome.h"
#include "errors.h"
#include <cmath>
class Water;
class Genome;
struct Command{
    uint8_t cmd;
    //uint8_t param;
    static constexpr uint8_t offset_conut = 3;
    int16_t offset[offset_conut];
    static constexpr int command_count = 126;
    uint16_t offset_mutate_chance_10000;
    uint16_t cmd_mutate_chance_10000;
};
class Bacteria
{
protected:
    Water* water;
    std::shared_ptr<Genome> genome;
    uint16_t x,y;
    int32_t energy;
    uint16_t attack;
    const Bacteria* parent;
    uint64_t birth_time;
    int16_t cmd_ptr = 0;
    uint8_t COUNT_OF_ACTION = 0;
    bool stop_action;
    bool killed = false;
    uint8_t killer = 0;
    uint32_t atp = 0;
public:
    Bacteria(Water* water, uint16_t x, uint16_t y,int32_t energy,const Bacteria* parent);
    void Tick();
    void TryMove(int8_t dx,int8_t dy);
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

    std::shared_ptr<Genome> GetGenome() const;
    void GetCoords(uint16_t &X,uint16_t &Y);
    int32_t GetEnergy();
    uint64_t GetBirthTime();
    uint16_t GetAttack();
    void IncreaseEnergy(int32_t added_energy);
    uint8_t GetKiller();
    bool GetKilled();
};

