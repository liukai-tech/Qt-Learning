#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QWheelEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);
    void zoomPixmap();


private:
    Ui::MainWindow *ui;

    QRect m_rect;
    float m_zoom;//缩放系数
    QPoint m_currentCoordinates,m_lastCoordinates;//当前的坐标,上一次移动的坐标

};
#endif // MAINWINDOW_H
