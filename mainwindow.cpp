#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fieldwidget.h"
MainWindow::MainWindow(QWidget *parent) :   QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainLayout = new QVBoxLayout;
    std::shared_ptr<Water> field(new Water(100,100));
    fw = new FieldWidget(7,field);
   // setLayout(mainLayout);
  //  mainLayout->addWidget(fw);
    setCentralWidget(fw);
}
MainWindow::~MainWindow()
{
    delete ui;
}
