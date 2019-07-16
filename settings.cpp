#include "settings.h"
#include "ui_form.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}
