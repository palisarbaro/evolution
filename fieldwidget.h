#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QPainter>
#include "universe.h"
class FieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FieldWidget(int sqrSize,std::shared_ptr<Universe> field,QWidget *parent = nullptr);
    ~FieldWidget();
protected:
    std::shared_ptr<Universe> field;
    void paintEvent(QPaintEvent* e);
    int sqrSize;
};

#endif // FIELDWIDGET_H
