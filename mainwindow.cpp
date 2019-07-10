#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fieldwidget.h"
MainWindow::MainWindow(QWidget *parent) :   QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainLayout = new QVBoxLayout;
    std::shared_ptr<Water> field(new Water(30,10));
    fw = new FieldWidget(10,field);
   // setLayout(mainLayout);
  //  mainLayout->addWidget(fw);
    setCentralWidget(fw);
}
MainWindow::~MainWindow()
{
    delete ui;
}
