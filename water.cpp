#include "water.h"
#include <QDebug>
Water::Water(int width,int height):width(width),height(height),View(new Matrix<QColor>(width,height))
{
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            View->Set(i,j,Qt::blue);
        }
    }
}

int Water::GetWidth()
{
    return width;
}
int Water::GetHeight(){
    return height;
}
std::shared_ptr<Matrix<QColor>> Water::GetView(){
    return View;
}
