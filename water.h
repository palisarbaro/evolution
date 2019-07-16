#pragma once
#include<QColor>

#include<iostream>
#include <memory>
#include<vector>
#include<list>

#include"matrix.h"
#include"bacteria.h"
#include"fieldwidget.h"
#include<ctime>
class Bacteria;
class FieldWidget;
class Water
{
protected:
    int time;
    int width,height;
    std::shared_ptr<Matrix<QColor>> View;
    std::list<std::shared_ptr<Bacteria>> all_bacteries;
    std::list<Bacteria*> alive_bacteries;
    Matrix<std::list<Bacteria*>> battle_field;
    Matrix<unsigned int> food_field;
    clock_t last_frame;
public:
    Water(int width,int height);
    int GetHeight();
    int GetWidth();
    void AddBacteria(int x,int y,int energy,Bacteria* parent=nullptr);
    void UpdateView(int display_method);
    void Tick();
    void Battle();
    void Eating();
    int HowMuchSunEnergy(int depth);
    std::shared_ptr<Matrix<QColor>> GetView();
    bool forced_cloning = true;
    friend Bacteria;
    friend FieldWidget;
};
