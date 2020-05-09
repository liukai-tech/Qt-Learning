#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <qdebug.h>
#include <math.h>
#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize();
    m_transCoordinates.setX(0);
    m_transCoordinates.setY(0);
    m_zoomscaleX = 1.0;
    m_zoomscaleY = 1.0;
    m_isShowAll = false;
    m_posXmax = 0;
    m_posXmin = 0;
    m_posYmax = 0;
    m_posYmin = 0;
    m_rtHgt = 0;
    m_baseHgt = 10;
    m_currPointX = 0;
    m_currPointY = 0;
    srand(time(NULL));/* 设定随机数种子 */

    ui->labelDrawPath->installEventFilter(this);

    setMouseTracking(true);/* mousemoveEvent事件如果mouserTrack为false，那么只有鼠标按下才会执行，而且默认是false，所以需要把窗口事件设置一下 */

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

//获取鼠标坐标
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    ui->labelMousePos->setText(QString("MPos:（%1,%2）").arg(event->pos().x()).arg(event->pos().y()));
}

void MainWindow::resize()
{
    m_Width = ui->labelDrawPath->width();
    m_Height = ui->labelDrawPath->height();
    qDebug() << "m_Width:" << m_Width << "m_Height:" << m_Height;
}


void MainWindow::drawFunction()
{
    QTime timenow = QTime();
    qDebug() << timenow.currentTime().toString("HH:mm:ss.zzz") << "update";

    m_rtHgt = qrand() % 20;

    m_hgt_bases.append(QPoint(m_rtHgt, m_baseHgt));
    m_points.append(QPoint(m_currPointX, m_currPointY));

    int quad = qrand() % 4;
    switch(quad){
    case 0:
        m_currPointX += qrand() % 20;
        m_currPointY += qrand() % 20;
        break;
    case 1:
        m_currPointX += qrand() % 20;
        m_currPointY -= qrand() % 20;
        break;
    case 2:
        m_currPointX -= qrand() % 20;
        m_currPointY += qrand() % 20;
        break;
    case 3:
        m_currPointX -= qrand() % 20;
        m_currPointY -= qrand() % 20;
        break;
    default:
        break;
    }

    if(m_currPointX >= m_posXmax){
        m_posXmax = m_currPointX;
    }

    if(m_currPointX <= m_posXmin){
        m_posXmin = m_currPointX;
    }

    if(m_currPointY >= m_posYmax){
        m_posYmax = m_currPointY;
    }

    if(m_currPointY <= m_posYmin){
        m_posYmin = m_currPointY;
    }

    qDebug() << "posXmin:" << m_posXmin << "posXmax:" << m_posXmax << "posYmin:" << m_posYmin << "posYmax:" << m_posYmax ;

    if(m_isShowAll){
        float fabsX = fabs(m_posXmax - m_posXmin);
        if(fabsX > getWidth()){
            m_zoomscaleX = getWidth()/fabsX;
        }

        float fabsY = fabs(m_posYmax - m_posYmin);
        if(fabsY > getHeight()){
            m_zoomscaleY = getHeight()/fabsX;
        }
        m_transCoordinates.setX((m_posXmax - m_posXmin)/2 + m_posXmin);
        m_transCoordinates.setY((m_posYmax - m_posYmin)/2 + m_posYmin);
        qDebug() << "[Show All]" << "scalex:" << m_zoomscaleX << "scaley:" << m_zoomscaleY ;

    }else{
        if((fabs(m_posXmax - m_posXmin) > WINDOW_WIDTH) || (fabs(m_posYmax - m_posYmin) > WINDOW_HEIGHT) ){
            m_currPointX += ((m_posXmax - m_posXmin)/2 - getCenterX());
            m_currPointY += ((m_posYmax - m_posYmin)/2 - getCenterY());
        }else{
            m_currPointX += (WINDOW_WIDTH/2 - getCenterX());
            m_currPointY += (WINDOW_HEIGHT/2 - getCenterY());
        }
        m_transCoordinates.setX(m_currPointX);
        m_transCoordinates.setY(m_currPointY);
    }

    setCenter(m_transCoordinates);//设置中心点

    QPainter painter(ui->labelDrawPath);

    if((fabs(m_posXmax - m_posXmin) > WINDOW_WIDTH) || (fabs(m_posYmax - m_posYmin) > WINDOW_HEIGHT) ){
        painter.setWindow(-fabs(m_posXmax - m_posXmin)/2,fabs(m_posYmax - m_posYmin)/2,fabs(m_posXmax - m_posXmin),fabs(m_posYmax - m_posYmin));
        painter.setViewport(-fabs(m_posXmax - m_posXmin)/2,fabs(m_posYmax - m_posYmin)/2,fabs(m_posXmax - m_posXmin),fabs(m_posYmax - m_posYmin));
    }else{
        painter.setWindow(-WINDOW_WIDTH/2,WINDOW_HEIGHT/2,WINDOW_WIDTH,WINDOW_HEIGHT);
        painter.setViewport(-WINDOW_WIDTH/2,WINDOW_HEIGHT/2,WINDOW_WIDTH,WINDOW_HEIGHT);
    }

//    painter.setWindow(-WINDOW_WIDTH/2,WINDOW_HEIGHT/2,WINDOW_WIDTH,WINDOW_HEIGHT);
//    painter.setViewport(-WINDOW_WIDTH/2,WINDOW_HEIGHT/2,WINDOW_WIDTH,WINDOW_HEIGHT);
    //设置坐标系
    painter.translate( m_transCoordinates);
    qDebug() << "trans:" << m_transCoordinates;
    qDebug() << "window" << painter.window();
    qDebug() << "viewport" << painter.viewport();
    //反锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.scale(m_zoomscaleX, m_zoomscaleY);

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
        tarnslatePos(m_points[i]);
        tarnslatePos(m_points[i+1]);
        painter.drawLine(m_points[i], m_points[i+1]);
    }

    QRect rect(m_points.last().x(), m_points.last().y(), 64, 64);
    // 绘制图标
    painter.drawPixmap(rect, QPixmap(":/Image/navi.png"));

    ui->labelCurrPos->setText(QString("CPos:（%1,%2）").arg(m_points.last().x()).arg(m_points.last().y()));
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    ui->labelDrawPath->resize(ui->centralwidget->size());
    resize();
}

void MainWindow::handleUpdateTimeout()
{
    ui->labelDrawPath->update();
}

void MainWindow::on_btnZoomIn_clicked()
{
    if(m_zoomscaleX < 4.0){
        m_zoomscaleX += 0.01;
    }
    if(m_zoomscaleY < 4.0){
        m_zoomscaleY += 0.01;
    }
    QString str = QString("%1%").arg((m_zoomscaleX * 100), 0, 'd', 0, QChar('0'));
    ui->labelZoomNum->setText(str);
    ui->labelDrawPath->update();
}

void MainWindow::on_btnZoomOut_clicked()
{
    if(m_zoomscaleX > 0.01){
        m_zoomscaleX -= 0.01;
    }
    if(m_zoomscaleY > 0.01){
        m_zoomscaleY -= 0.01;
    }
    QString str = QString("%1%").arg((m_zoomscaleX * 100), 0, 'd', 0, QChar('0'));
    ui->labelZoomNum->setText(str);
    ui->labelDrawPath->update();
}

void MainWindow::on_btnShowAll_clicked()
{
    if(m_isShowAll){
        m_isShowAll = false;
        ui->btnShowAll->setText("Show All");
    }else{
        m_isShowAll = true;
        ui->btnShowAll->setText("Refresh");
    }
    m_zoomscaleX = 1.0;
    m_zoomscaleY = 1.0;
    QString str = QString("%1%").arg((m_zoomscaleX * 100), 0, 'd', 0, QChar('0'));
    ui->labelZoomNum->setText(str);
    ui->labelDrawPath->update();
}
