#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void UpdatePlot(void);
    void Refresh(void);
    void UpdateDisp(void);
    void DrawTrk(QPainter &c,int level);

private:
    Ui::MainWindow *ui;

    QPixmap Buff;
    Graph *GraphT;

    int Flush;

    int Drag,Xn,Yn;

    QColor CColor[4];    // {background,grid,text,line}
};
#endif // MAINWINDOW_H
