#include "fieldwidget.h"
FieldWidget::FieldWidget(int sqrSize,std::shared_ptr<Universe> field,QWidget *parent) : QWidget(parent), field(field),sqrSize(sqrSize)
{
    setFixedSize(sqrSize*field->GetWidth(),sqrSize*field->GetHeight());
}

FieldWidget::~FieldWidget()
{
}

void FieldWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,1));
    painter.drawEllipse(30,70,30,30);
    for(int i=0;i<field->GetWidth();i++){
        for(int j=0;j<field->GetHeight();j++){
            int x = sqrSize*i;
            int y = sqrSize*j;
            painter.setBrush(QBrush(field->GetView()->Get(i,j)));
            painter.drawRect(x,y,sqrSize,sqrSize);
        }
    }
}
