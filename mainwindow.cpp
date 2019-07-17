#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :   QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->open_settings,SIGNAL(triggered()),this,SLOT(open_settings()));
    connect(ui->close_settings,SIGNAL(triggered()),this,SLOT(close_settings()));
    std::shared_ptr<Water> field(new Water(300,50));
    field->SetSelf(field);
    fw = new FieldWidget(6,field,this);
    setCentralWidget(fw);
    setFixedSize(fw->width(),fw->height());
    open_settings();
    setGeometry(30,40,40,40);

   // setLayout(mainLayout);
  //  mainLayout->addWidget(fw);


}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    close_settings();
    e->accept();
}

void MainWindow::open_settings()
{
    if(settings==nullptr || settings->isClosed()){
        settings = new Settings();
        connect(settings,SIGNAL(energy_radio_signal()),this,SLOT(set_display_method_energy()));
        connect(settings,SIGNAL(color_radio_signal()),this,SLOT(set_display_method_color()));
        connect(settings,SIGNAL(aggressive_radio_signal()),this,SLOT(set_display_method_aggressive()));
        connect(settings,SIGNAL(hp_radio_signal()),this,SLOT(set_display_method_hp()));
        connect(settings,SIGNAL(density_radio_signal()),this,SLOT(set_display_method_density()));
        connect(settings,SIGNAL(food_display_checkbox_signal(int)),this,SLOT(set_food_display(int)));

        connect(settings,SIGNAL(move_spinbox_signal(int)),this,SLOT(change_move_energy(int)));
        connect(settings,SIGNAL(photo_spinbox_signal(int)),this,SLOT(change_photo_energy(int)));
        connect(settings,SIGNAL(clone_spinbox_signal(int)),this,SLOT(change_clone_energy(int)));
        connect(settings,SIGNAL(lffood_spinbox_signal(int)),this,SLOT(change_lffood_energy(int)));
        connect(settings,SIGNAL(eat_food_spinbox_signal(int)),this,SLOT(change_eat_food_energy(int)));
        connect(settings,SIGNAL(lfenemy_spinbox_signal(int)),this,SLOT(change_lfenemy_energy(int)));
        connect(settings,SIGNAL(suicide_spinbox_signal(int)),this,SLOT(change_suicide_energy(int)));
        connect(settings,SIGNAL(convert_atp_spinbox_signal(int)),this,SLOT(change_convert_atp_energy(int)));
        connect(settings,SIGNAL(lffriend_spinbox_signal(int)),this,SLOT(change_lffriend_energy(int)));
        connect(settings,SIGNAL(attack_spinbox_signal(int)),this,SLOT(change_attack_energy(int)));
        connect(settings,SIGNAL(hme_spinbox_signal(int)),this,SLOT(change_hme_energy(int)));
        connect(settings,SIGNAL(heal_spinbox_signal(int)),this,SLOT(change_heal_energy(int)));
        settings->show();
        settings->setGeometry(300,400,600,500);
    }
}

void MainWindow::close_settings()
{
    if(!settings->isClosed()){
        settings->close();
    }

}

void MainWindow::set_display_method_color()
{
    fw->display_method=0;
}
void MainWindow::set_display_method_energy()
{
    fw->display_method=1;
}
void MainWindow::set_display_method_aggressive()
{
    fw->display_method=2;
}

void MainWindow::set_display_method_hp()
{
    fw->display_method=3;
}

void MainWindow::set_display_method_density()
{
    fw->display_method=4;
}

void MainWindow::set_food_display(int state)
{
    fw->SetFoodDisplay(state==Qt::Checked);
}

void MainWindow::change_move_energy(int energy)
{
    Bacteria::move_energy=energy;
}

void MainWindow::change_photo_energy(int energy)
{
    Bacteria::photo_enery=energy;
}

void MainWindow::change_clone_energy(int energy)
{
    Bacteria::clone_energy=energy;
}

void MainWindow::change_lffood_energy(int energy)
{
    Bacteria::lffood_energy=energy;
}

void MainWindow::change_eat_food_energy(int energy)
{
    Bacteria::eat_food_energy=energy;
}

void MainWindow::change_lfenemy_energy(int energy)
{
    Bacteria::lfenemy_energy=energy;
}

void MainWindow::change_suicide_energy(int energy)
{
    Bacteria::suicide_energy=energy;
}

void MainWindow::change_convert_atp_energy(int energy)
{
    Bacteria::convert_atp_energy=energy;
}

void MainWindow::change_lffriend_energy(int energy)
{
    Bacteria::lffriend_energy=energy;
}

void MainWindow::change_attack_energy(int energy)
{
    Bacteria::attack_energy=energy;
}

void MainWindow::change_hme_energy(int energy)
{
    Bacteria::hme_energy=energy;
}

void MainWindow::change_heal_energy(int energy)
{
    Bacteria::heal_energy=energy;
}


