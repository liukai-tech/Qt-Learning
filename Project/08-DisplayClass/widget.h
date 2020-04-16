#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onColorSlidervalueChanged(int value);

    void on_horizontalSliderH_valueChanged(int value);

    void on_horizontalScrollBarH_valueChanged(int value);

    void on_verticalSliderV_valueChanged(int value);

    void on_verticalScrollBarV_valueChanged(int value);

    void on_dialInput_valueChanged(int value);

    void on_radioBtnDec_clicked();

    void on_radioBtnBin_clicked();

    void on_radioBtnOct_clicked();

    void on_radioBtnHex_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
