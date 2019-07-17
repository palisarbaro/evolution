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
    uint16_t param;
    static constexpr uint8_t offset_conut = 3;
    int16_t offset[offset_conut];
    uint16_t offset_mutate_chance_10000;
    uint16_t cmd_mutate_chance_10000;
};
enum Actions:uint8_t
{
    move = 0,
    photo = 1,
    clone = 2,
    lffood = 3,
    eat_food = 4,
    lfenemy = 5,
    suicide = 6,
    convert_atp = 7,
    lffriend = 8,
    attack = 9,
    hme = 10,
    count_of_actions = 11
};

class Bacteria
{
protected:
    std::weak_ptr<Water> water;
    std::shared_ptr<Genome> genome;
    std::weak_ptr<Bacteria> self;
    uint16_t x,y;
    int32_t energy;
    int16_t hp=100;
    uint16_t attack;
    uint64_t birth_time;
    int16_t cmd_ptr = 0;
    bool stop_action;
    bool killed = false;
    uint8_t killer = 0;
    uint32_t atp = 0;
public:
    Bacteria(std::weak_ptr<Water> water, uint16_t x, uint16_t y,int32_t energy,std::weak_ptr<Bacteria> parent);
    void Tick();
    void TryMove(int8_t dx,int8_t dy);
    void Kill();
    void Clone(int8_t dx,int8_t dy);
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
    void SetSelf(std::weak_ptr<Bacteria> bact);
    int16_t GetHP();
    void InreaceHP(int16_t added_hp);
};

