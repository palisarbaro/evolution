#pragma once
#include<QColor>

#include<iostream>
#include <memory>
#include<vector>
#include<list>

#include"matrix.h"
#include"bacteria.h"
#include"fieldwidget.h"

class Bacteria;
class FieldWidget;
class Water
{
protected:
    int width,height;
    std::shared_ptr<Matrix<QColor>> View;
    std::vector<std::shared_ptr<Bacteria>> all_bacteries;
    std::list<std::shared_ptr<Bacteria>> alive_bacteries;
    Matrix<std::list<Bacteria*>> battle_field;
public:
    Water(int width,int height);
    int GetHeight();
    int GetWidth();
    void AddBacteria(int x,int y,int energy,Bacteria* parent=nullptr);
    void UpdateView();
    void Tick();
    int HowMuchSunEnergy(int depth);
    std::shared_ptr<Matrix<QColor>> GetView();
    friend Bacteria;
    friend FieldWidget;
};
