#pragma once

#include <QWidget>
#include <QPainter>
#include<QTimer>

#include "water.h"

class Water;
class FieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FieldWidget(uint8_t sqr_size,std::shared_ptr<Water> field,QWidget *parent = nullptr);
    uint8_t display_method=0;
    void SetFoodDisplay(bool display);
protected:
    std::shared_ptr<Water> field;
    void paintEvent(QPaintEvent* e);
    uint8_t sqr_size;
    QTimer* timer;
private slots:
    void slotTimer();
};
