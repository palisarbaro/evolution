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
    uint64_t time;
    uint16_t width,height;
    std::shared_ptr<Matrix<QColor>> View;
    std::list<std::shared_ptr<Bacteria>> all_bacteries;
    std::list<Bacteria*> alive_bacteries;
    Matrix<std::list<Bacteria*>> battle_field;
    Matrix<uint16_t> food_field;
    clock_t last_frame;
public:
    Water(uint16_t width,uint16_t height);
    uint16_t GetHeight();
    uint16_t GetWidth();
    void AddBacteria(uint16_t x,uint16_t y,int32_t energy,Bacteria* parent=nullptr);
    void UpdateView(uint8_t display_method);
    void Tick();
    void Battle();
    void Eating();
    int32_t HowMuchSunEnergy(uint16_t depth);
    bool forced_cloning = true;

    uint64_t GetTime();
    std::shared_ptr<Matrix<QColor>> GetView();
    Matrix<uint16_t>& GetFoodField();
    Matrix<std::list<Bacteria*>>& GetBattleField();
    std::list<Bacteria*>& GetAliveBacteries();
};
