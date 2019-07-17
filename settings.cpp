#include "settings.h"
#include "ui_form.h"
#include<QDebug>
Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    is_closed = false;
    connect(ui->energy_radio,SIGNAL(clicked()),this,SIGNAL(energy_radio_signal()));
    connect(ui->color_radio,SIGNAL(clicked()),this,SIGNAL(color_radio_signal()));
    connect(ui->aggressive_radio,SIGNAL(clicked()),this,SIGNAL(aggressive_radio_signal()));
    connect(ui->food_display_checkbox,SIGNAL(stateChanged(int)),this,SIGNAL(food_display_checkbox_signal(int)));
}

Settings::~Settings()
{
    delete ui;
}

bool Settings::isClosed()
{
    return is_closed;
}

void Settings::closeEvent(QCloseEvent *e)
{
    is_closed=true;
    e->accept();
}
