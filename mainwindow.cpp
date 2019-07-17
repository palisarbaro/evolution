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
    setGeometry(500,200,40,40);

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
        connect(settings,SIGNAL(food_display_checkbox_signal(int)),this,SLOT(set_food_display(int)));
        settings->show();
        settings->setGeometry(100,200,400,300);
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

void MainWindow::set_food_display(int state)
{
    fw->SetFoodDisplay(state==Qt::Checked);
}
