#pragma once

#include<QColor>

#include "bacteria.h"

#include<vector>

class Bacteria;
struct Command;
class Genome
{
protected:
    int max_energy=250;
    QColor color;
    int attack;
    bool clone_nearly;
    Bacteria* bacteria;
    std::vector<Command> code;
public:
    static const int code_length = 64;
    Genome(Bacteria* bacteria,const Bacteria* parent=nullptr);
    QColor init_color();
    QColor mutate_color(QColor color);
    int init_attack();
    int mutate_attack(int attack);
    bool init_clone_nearly();
    bool mutate_clone_nearly(bool clone_nearly);
    void Irradiate(int percent);
    std::vector<Command> init_code();
    std::vector<Command> mutate_code(std::vector<Command> code);
    QColor GetColor();
    int GetAttack();
    bool GetCloneNearly();
    int GetMaxEnergy();
    const std::vector<Command>& GetCode();
};
