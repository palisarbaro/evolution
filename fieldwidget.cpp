#include "fieldwidget.h"
FieldWidget::FieldWidget(int sqrSize,std::shared_ptr<Water> field,QWidget *parent) : QWidget(parent), field(field),sqr_size(sqrSize)
{
    setFixedSize(sqrSize*field->GetWidth(),sqrSize*field->GetHeight());
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(slotTimer()));
    timer->start(10);
    for(int i=0;i<3;i++){
        field->AddBacteria(rand()%30,rand()%30,100);
    }
}
void FieldWidget::slotTimer(){
    field->Tick(); 
    update(0,0,width(),height());

}
FieldWidget::~FieldWidget()
{
}

void FieldWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    field->UpdateView(1);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,1));
    for(int i=0;i<field->GetWidth();i++){
        for(int j=0;j<field->GetHeight();j++){
            int x = sqr_size*i;
            int y = sqr_size*j;
            painter.setBrush(QBrush(field->View->Get(i,j)));
            painter.drawRect(x,y,sqr_size,sqr_size);
        }
    }
}
