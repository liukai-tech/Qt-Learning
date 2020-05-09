#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define WINDOW_HEIGHT   415
#define WINDOW_WIDTH    697

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawFunction();
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resize();
    void resizeEvent(QResizeEvent *event);

private:

    void setCenter(QPoint &p)
    {
        m_centerX = p.x();
        m_centerY = p.y();
    }

    float getCenterX(void)
    {
        return m_centerX;
    }

    float getCenterY(void)
    {
        return m_centerY;
    }

    void tarnslatePos(QPoint &p1)
    {
        float x, y;

        x = p1.x();
        y = p1.y();

        x += (WINDOW_WIDTH/2 - m_centerX);
        y += (WINDOW_HEIGHT/2 - m_centerY);

        p1.setX(x);
        p1.setY(y);
    }

    int getWidth()
    {
        return m_Width;
    }

    int getHeight()
    {
        return m_Height;
    }

private slots:
    void on_btnZoomIn_clicked();

    void on_btnZoomOut_clicked();

    void handleUpdateTimeout();


    void on_btnShowAll_clicked();

private:
    Ui::MainWindow *ui;

    float m_zoomscaleX;//X轴缩放系数
    float m_zoomscaleY;//Y轴缩放系数

    QTimer *m_updateDrawPathTimer;
    QVector<QPoint>m_points;
    QVector<QPoint>m_hgt_bases;

    QPoint m_transCoordinates,m_zoomCoordinates;//当前的坐标,zoom中心点坐标

    bool m_isShowAll;//是否全局

    int m_currPointX;
    int m_currPointY;
    int m_posXmax;
    int m_posXmin;
    int m_posYmax;
    int m_posYmin;
    int m_baseHgt;
    int m_rtHgt;

    float m_centerX;
    float m_centerY;

    int m_Width,m_Height;
};
#endif // MAINWINDOW_H
