#pragma once

#include<QColor>

#include "bacteria.h"

class Bacteria;
class Genome
{
protected:
    QColor color;
    int attack;
    Bacteria* bacteria;
public:
    Genome(Bacteria* bacteria,const Bacteria* parent=nullptr);
    QColor GetColor();
    friend Bacteria;
};
