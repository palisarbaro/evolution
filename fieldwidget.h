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
    explicit FieldWidget(int sqr_size,std::shared_ptr<Water> field,QWidget *parent = nullptr);
    ~FieldWidget();
protected:
    std::shared_ptr<Water> field;
    void paintEvent(QPaintEvent* e);
    int sqr_size;
    QTimer* timer;
private slots:
    void slotTimer();
};
