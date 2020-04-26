#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void drawFunction();

private slots:
    void on_btnZoomIn_clicked();

    void on_btnZoomOut_clicked();

    void handleUpdateTimeout();

private:
    Ui::MainWindow *ui;
    QTimer *m_updateDrawPathTimer;
    QVector<QPoint>m_lines;
    QVector<QPoint>m_point;
    QPainter *m_Painter;
//    QPainterPath *m_PainterPath;
};
#endif // MAINWINDOW_H
