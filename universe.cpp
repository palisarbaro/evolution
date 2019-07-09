#include "universe.h"
#include <QDebug>
Universe::Universe(int width,int height):width(width),height(height),View(new Matrix<QColor>(width,height))
{
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            View->Set(i,j,Qt::red);
        }
    }
}

int Universe::GetWidth()
{
    return width;
}
int Universe::GetHeight(){
    return height;
}
std::shared_ptr<Matrix<QColor>> Universe::GetView(){
    return View;
}
