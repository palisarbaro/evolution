#pragma once

#include<QColor>

#include "bacteria.h"

class Bacteria;
class Genome
{
protected:
    QColor color;
    int attack;
    bool clone_nearly;
    Bacteria* bacteria;
public:
    Genome(Bacteria* bacteria,const Bacteria* parent=nullptr);
    QColor init_color();
    QColor mutate_color(QColor color);
    int init_attack();
    int mutate_attack(int attack);
    bool init_clone_nearly();
    bool mutate_clone_nearly(bool clone_nearly);
    QColor GetColor();
    friend Bacteria;
};
