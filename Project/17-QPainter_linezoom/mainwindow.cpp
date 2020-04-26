#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <qdebug.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_zoomCoordinates.setX(WINDOW_WIDTH/2);
    m_zoomCoordinates.setY(WINDOW_HEIGHT/2);
    m_zoomscale = 1.0;

    ui->labelDrawPath->installEventFilter(this);

    m_updateDrawPathTimer = new QTimer;
    m_updateDrawPathTimer->setInterval(1000);
    connect(m_updateDrawPathTimer, SIGNAL(timeout()), this, SLOT(handleUpdateTimeout()));
    m_updateDrawPathTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if((obj ==ui->labelDrawPath) && (event->type() == QEvent::Paint))
    {
        drawFunction();
    }

    if((obj ==ui->labelDrawPath) && (event->type() == QEvent::Timer))
    {
        handleUpdateTimeout();
    }

    return QWidget::eventFilter(obj, event);

}

void MainWindow::drawFunction()
{
    static int posx = WINDOW_WIDTH/2, posy = WINDOW_HEIGHT/2;
    static int basehgt = 10;
    int rthgt = qrand() % 20;

    m_hgt_bases.append(QPoint(rthgt, basehgt));
    m_points.append(QPoint(posx, posy));

    int quad = qrand() % 4;
    switch(quad){
    case 0:
        posx += qrand() % 50;
        posy += qrand() % 50;
        break;
    case 1:
        posx += qrand() % 50;
        posy -= qrand() % 50;
        break;
    case 2:
        posx -= qrand() % 50;
        posy += qrand() % 50;
        break;
    case 3:
        posx -= qrand() % 50;
        posy -= qrand() % 50;
        break;
    default:
        break;
    }

    m_currentCoordinates.setX(posx);
    m_currentCoordinates.setY(posy);

    QPainter painter(ui->labelDrawPath);
    //设置坐标系
    painter.translate(m_currentCoordinates);
    qDebug() << m_currentCoordinates;
    //反锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.scale(m_zoomscale, m_zoomscale);

    for(int i=0; i<m_points.size()-1; ++i)
    {
        QPoint p = m_hgt_bases.at(i);
        if(p.x() > p.y() + 2){    //red line
            painter.setPen(QPen(QColor(255, 0, 0), 20));// 设置画笔颜色、宽度
        }else if(p.x() < p.y() - 2){  //yellow line
           painter.setPen(QPen(QColor(255, 255, 0), 20));// 设置画笔颜色、宽度
        }else{  //green line
            painter.setPen(QPen(QColor(0, 255, 0), 20));// 设置画笔颜色、宽度
        }
        painter.drawLine(m_points[i], m_points[i+1]);
    }

}

void MainWindow::handleUpdateTimeout()
{
    ui->labelDrawPath->update();
}

void MainWindow::on_btnZoomIn_clicked()
{
    if(m_zoomscale < 4.0){
        m_zoomscale += 0.1;
    }
    ui->labelDrawPath->update();
}

void MainWindow::on_btnZoomOut_clicked()
{
    if(m_zoomscale > 0.1){
        m_zoomscale -= 0.1;
    }
    ui->labelDrawPath->update();
}
