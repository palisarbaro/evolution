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
    void set_display_method_hp();
    void set_display_method_density();
    void set_food_display(int state);

    void change_move_energy(int energy);
    void change_photo_energy(int energy);
    void change_clone_energy(int energy);
    void change_lffood_energy(int energy);
    void change_eat_food_energy(int energy);
    void change_lfenemy_energy(int energy);
    void change_suicide_energy(int energy);
    void change_convert_atp_energy(int energy);
    void change_lffriend_energy(int energy);
    void change_attack_energy(int energy);
    void change_hme_energy(int energy);
    void change_heal_energy(int energy);


};
