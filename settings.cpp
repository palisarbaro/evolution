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
    connect(ui->hp_radio,SIGNAL(clicked()),this,SIGNAL(hp_radio_signal()));
    connect(ui->density_radio,SIGNAL(clicked()),this,SIGNAL(density_radio_signal()));

    connect(ui->food_display_checkbox,SIGNAL(stateChanged(int)),this,SIGNAL(food_display_checkbox_signal(int)));

    connect(ui->move_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(move_spinbox_signal(int)));
    connect(ui->move_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(move_spinbox_signal(int)));
    connect(ui->photo_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(photo_spinbox_signal(int)));
    connect(ui->clone_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(clone_spinbox_signal(int)));
    connect(ui->lffood_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(lffood_spinbox_signal(int)));
    connect(ui->eat_food_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(eat_food_spinbox_signal(int)));
    connect(ui->lfenemy_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(lfenemy_spinbox_signal(int)));
    connect(ui->suicide_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(suicide_spinbox_signal(int)));
    connect(ui->atp_to_energy_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(convert_atp_spinbox_signal(int)));
    connect(ui->lffriend_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(lffriend_spinbox_signal(int)));
    connect(ui->attack_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(attack_spinbox_signal(int)));
    connect(ui->hme_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(hme_spinbox_signal(int)));
    connect(ui->heal_spinBox,SIGNAL(valueChanged(int)),this,SIGNAL(heal_spinbox_signal(int)));
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
