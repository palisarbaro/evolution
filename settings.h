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
    void food_display_checkbox_signal(int);
};

#endif // FORM_H
