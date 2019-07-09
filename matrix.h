#ifndef MATRIX_H
#define MATRIX_H
#include"errors.h"
template<class T>
class Matrix
{
    int width,height;
    T** matrix;
public:
    Matrix(int width,int height):width(width),height(height)
    {
        matrix = new T*[width];
        for(int i=0;i<width;i++){
            matrix[i]=new T[height];
        }
    }
    void Set(int x,int y,T val,bool looped=false){
        loopOrThrow(x,y,looped);
        matrix[x][y] = val;
    }
    T Get(int x,int y, bool looped=false){
        loopOrThrow(x,y,looped);
        return matrix[x][y];
    }
    ~Matrix(){
        for(int i=0;i<width;i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
private:
    bool isCoordinatesCorrect(int x, int y) {
        if(x < 0 || x >= width) return false;
        if(y < 0 || y >= height) return false;
        return true;
    }

    void lp(int& v,int max){ //обобщение loopX и loopY
        v = v%max;
        if(v<0) v = max+v;
    }
    void loopX(int &x){
        lp(x,width);
    }
    void loopY(int &y){
        lp(y,height);
    }
    void loopOrThrow(int &x,int &y,bool looped){
        if(looped){
            loopX(x);
            loopY(y);
        }
        if(!isCoordinatesCorrect(x,y)){
            if(looped) throw IMPOSSIBLE;
            throw INCORRECT_INDEX;
        }
    }
};

#endif // MATRIX_H
