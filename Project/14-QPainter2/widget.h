#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Paint();

protected:
    void paintEvent(QPaintEvent *){
            QPainter painter(this);
            painter.drawImage(0,0,image);
        }

private:
    Ui::Widget *ui;
    QImage image;
};
#endif // WIDGET_H
