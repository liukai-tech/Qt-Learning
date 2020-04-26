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
//    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void drawFunction();

private slots:

    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void handleTimeout();

private:
    Ui::MainWindow *ui;
    QTimer *m_updatePainterTimer;
};
#endif // MAINWINDOW_H
