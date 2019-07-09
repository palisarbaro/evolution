#include "fieldwidget.h"
#include "ui_fieldwidget.h"

FieldWidget::FieldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FieldWidget)
{
    ui->setupUi(this);
}

FieldWidget::~FieldWidget()
{
    delete ui;
}
