#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


private slots:
    void on_btnZoomIn_clicked();

    void on_btnZoomOut_clicked();

    void handleUpdateTimeout();

private:
    Ui::MainWindow *ui;

    float m_zoomscale;//缩放系数

    QTimer *m_updateDrawPathTimer;
    QVector<QPoint>m_points;
    QVector<QPoint>m_hgt_bases;

    QPoint m_currentCoordinates,m_zoomCoordinates;//当前的坐标,zoom中心点坐标
};
#endif // MAINWINDOW_H
