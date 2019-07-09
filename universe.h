#ifndef FIELD_H
#define FIELD_H
#include"matrix.h"
#include<iostream>
#include <memory>
#include<QColor>
class Universe
{
protected:
    int width,height;
    std::shared_ptr<Matrix<QColor>> View;
public:
    Universe(int width,int height);
    int GetHeight();
    int GetWidth();
    std::shared_ptr<Matrix<QColor>> GetView();

};

#endif // FIELD_H
