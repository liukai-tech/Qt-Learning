#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelDrawPath->installEventFilter(this);

    m_zoomscale = 1.0;

    m_Painter = new QPainter(ui->labelDrawPath);
    m_Painter->begin(ui->labelDrawPath);
    m_Painter->translate(290,200); //将点（290,200）设为原点
    m_Painter->setRenderHint(QPainter::Antialiasing, true);//反走样
    m_Painter->end();
//    m_PainterPath = new QPainterPath();
//    m_PainterPath->moveTo(0,0);//移动到原点

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
    static int posx = 0, posy = 0;
    static int basehgt = 10;
    int rthgt = qrand() % 20;

    m_point.append(QPoint(rthgt, basehgt));
    m_lines.append(QPoint(posx, posy));

    posx += 5;
    posy += 5;

    m_Painter->begin(ui->labelDrawPath);

    m_Painter->translate(290,200); //将点（290,200）设为原点
    m_Painter->setRenderHint(QPainter::Antialiasing, true);//反走样
    m_Painter->scale(m_zoomscale, m_zoomscale);

    for(int i=0; i<m_lines.size()-1; ++i)
    {
        QPoint p = m_point.at(i);
        if(p.x() > p.y() + 2){    //red line
            m_Painter->setPen(QPen(QColor(255, 0, 0), 20));// 设置画笔颜色、宽度
        }else if(p.x() < p.y() - 2){  //yellow line
            m_Painter->setPen(QPen(QColor(255, 255, 0), 20));// 设置画笔颜色、宽度
        }else{  //green line
            m_Painter->setPen(QPen(QColor(0, 255, 0), 20));// 设置画笔颜色、宽度
        }
        m_Painter->drawLine(m_lines[i], m_lines[i+1]);
    }

    m_Painter->end();

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
