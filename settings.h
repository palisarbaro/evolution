#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QCloseEvent>
#include <QRadioButton>
namespace Ui {
class Form;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
    bool isClosed();
protected:
    Ui::Form *ui;
    bool is_closed;
    void closeEvent(QCloseEvent* e);
signals:
    void color_radio_signal();
    void energy_radio_signal();
    void aggressive_radio_signal();
    void hp_radio_signal();
    void density_radio_signal();

    void food_display_checkbox_signal(int);

    void move_spinbox_signal(int);
    void photo_spinbox_signal(int);
    void clone_spinbox_signal(int);
    void lffood_spinbox_signal(int);
    void eat_food_spinbox_signal(int);
    void lfenemy_spinbox_signal(int);
    void suicide_spinbox_signal(int);
    void convert_atp_spinbox_signal(int);
    void lffriend_spinbox_signal(int);
    void attack_spinbox_signal(int);
    void hme_spinbox_signal(int);
    void heal_spinbox_signal(int);

};

#endif // FORM_H
