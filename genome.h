#pragma once

#include<QColor>

#include "bacteria.h"

#include<vector>

class Bacteria;
struct Command;
class Genome
{
protected:
    uint16_t max_energy=250;
    QColor color;
    uint16_t attack;
    bool clone_nearly;
    Bacteria* bacteria;
    std::vector<Command> code;
public:
    static constexpr uint16_t code_length = 64;
    Genome(Bacteria* bacteria,const Bacteria* parent=nullptr);
    QColor init_color();
    QColor mutate_color(QColor color);
    uint16_t init_attack();
    uint16_t mutate_attack(uint16_t attack);
    bool init_clone_nearly();
    bool mutate_clone_nearly(bool clone_nearly);
    void Irradiate(uint8_t percent);
    std::vector<Command> init_code();
    std::vector<Command> mutate_code(std::vector<Command> code);
    QColor GetColor();
    uint16_t GetAttack();
    bool GetCloneNearly();
    uint16_t GetMaxEnergy();
    const std::vector<Command>& GetCode();
};
