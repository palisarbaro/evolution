#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QPainter>
#include "water.h"
class FieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FieldWidget(int sqrSize,std::shared_ptr<Water> field,QWidget *parent = nullptr);
    ~FieldWidget();
protected:
    std::shared_ptr<Water> field;
    void paintEvent(QPaintEvent* e);
    int sqrSize;
};

#endif // FIELDWIDGET_H
