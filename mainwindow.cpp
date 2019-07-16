#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fieldwidget.h"
#include "settings.h"
MainWindow::MainWindow(QWidget *parent) :   QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainLayout = new QVBoxLayout;
    std::shared_ptr<Water> field(new Water(200,50));
    field->SetSelf(field);
    fw = new FieldWidget(6,field);
    //Settings* settings = new Settings();

   // setLayout(mainLayout);
  //  mainLayout->addWidget(fw);
    setCentralWidget(fw);
}
MainWindow::~MainWindow()
{
    delete ui;
}
