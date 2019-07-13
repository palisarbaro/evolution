#pragma once

#include<QDebug>

#include "water.h"
#include "genome.h"
#include "errors.h"

class Water;
class Genome;
class Bacteria
{
protected:
    Water* water;
    int x,y;
    int energy;
    int spent_energy;
    int attack;
    std::shared_ptr<Genome> genome;
    const Bacteria* parent;
public:
    Bacteria(Water* water, int x, int y,int energy,const Bacteria* parent);
    void Tick();
    void TryMove(int dx,int dy);
    void Kill();
    void Clone();
    void Photosynthesis();
    friend Water;
    friend Genome;
};

