#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMdiArea>
#include <QCloseEvent>
#include "fieldwidget.h"
#include "settings.h"
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
    FieldWidget* fw;
    Settings* settings = nullptr;
    void closeEvent(QCloseEvent* e);
public slots:
    void open_settings();
    void close_settings();
    void set_display_method_color();
    void set_display_method_energy();
    void set_display_method_aggressive();
    void set_food_display(int state);

};
