#pragma once

#include <QMainWindow>
#include <QVBoxLayout>

#include "fieldwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    Ui::MainWindow *ui;
    QVBoxLayout* mainLayout;
    FieldWidget* fw;
};
