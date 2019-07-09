#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>

namespace Ui {
class FieldWidget;
}

class FieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FieldWidget(QWidget *parent = nullptr);
    ~FieldWidget();

private:
    Ui::FieldWidget *ui;
};

#endif // FIELDWIDGET_H
