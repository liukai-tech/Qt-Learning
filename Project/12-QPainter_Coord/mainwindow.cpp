#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>

//在label控件内动态绘制轨迹
//参考 https://blog.csdn.net/qq_41399894/article/details/88051337

int count = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelDraw->installEventFilter(this);

    m_updatePainterTimer = new QTimer;

    m_updatePainterTimer->setInterval(2000);

    connect(m_updatePainterTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));

    m_updatePainterTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if(obj ==ui->labelDraw && event->type() == QEvent::Paint)
    {
        drawFunction();
    }

    if(obj ==ui->labelDraw && event->type() == QEvent::Timer)
    {
        handleTimeout();
    }

    return QWidget::eventFilter(obj, event);

}

//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event);
//    ui->labelBtnInfo->setText("Draw Rect.");
//    QPainter painter(ui->labelDraw);
//    painter.setBrush(Qt::red);
//    painter.drawRect(0,0,100,100);
//    painter.setBrush(Qt::yellow);
//    painter.drawRect(-50,-50,100,100);
//}

void MainWindow::drawFunction()
{
    QPainter painter(ui->labelDraw);
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    painter.setPen(QColor(0,0,0));
    // 设置画笔颜色、宽度
//    painter.setPen(QPen(QColor(0, 0, 0), 2));
    // 设置画刷颜色
    QFont font;
    font.setPointSize(15);
    font.setFamily("楷体");
    font.setItalic(true);
    painter.setFont(font);
    //点坐标
    QPoint points[4] = {
            QPoint(150,100),
            QPoint(300,150),
            QPoint(350,250),
            QPoint(100,300)
        };
    QPainterPath path;
    path.addRect(150,150,100,100);
    path.moveTo(100,100);
    path.cubicTo(100,100,150,100,400,400);
    int startAngle = 90*16;
    // 跨越度数
    int spanAngle = 180*16;
    switch (count) {
    case 0:
        ui->labelBtnInfo->setText("1.画矩形");
        painter.drawRect(QRect(0,0,100,100));
        break;
    case 1:
        ui->labelBtnInfo->setText("2.移动X：100px，画两倍圆");
        //将(100,0)作为坐标原点
        painter.translate(100,0);
        //放大两倍
        painter.scale(2,2);
        painter.drawEllipse(QPointF(50, 50), 50, 50);
        break;
    case 2:
        ui->labelBtnInfo->setText("3.旋转画线");
        painter.resetTransform();
        painter.drawLine(200,150,400,150);
        //旋转45°
        painter.rotate(45);
        painter.drawLine(200,150,400,150);
        break;
    case 3:
        ui->labelBtnInfo->setText("4.画圆角矩形");
        painter.drawRoundRect(QRect(150,0,100,100));
        break;
    case 4:
        ui->labelBtnInfo->setText("5.画多边形");
        painter.drawPolygon(points,4);
        break;
    case 5:
        ui->labelBtnInfo->setText("6.画多边线");
        painter.drawPolyline(points,4);
        break;
    case 6:
        ui->labelBtnInfo->setText("7.画弧线");
        painter.drawArc(QRect(150,0,100,100),startAngle,spanAngle);
        break;
    case 7:
        ui->labelBtnInfo->setText("8.画路径");
        painter.drawPath(path);
        break;
    case 8:
        ui->labelBtnInfo->setText("9.画字");
        painter.drawText(QRect(150,150,100,100),Qt::AlignCenter,tr("Hello Qt"));
        break;
    case 9:
        ui->labelBtnInfo->setText("10.画图");
        painter.drawPixmap(150,50,QPixmap(":/Image/tracker"));
        break;
    default:
        break;
    }
    count == 9 ? count = 0:count++;
}
void MainWindow::handleTimeout()
{
    ui->labelDraw->update();
}


void MainWindow::on_btn1_clicked()
{
    ui->labelBtnInfo->setText("Button 1 Clicked.");
}

void MainWindow::on_btn2_clicked()
{
    ui->labelBtnInfo->setText("Button 2 Clicked.");
}

void MainWindow::on_btn3_clicked()
{
    ui->labelBtnInfo->setText("Button 3 Clicked.");
}

void MainWindow::on_btn4_clicked()
{
    ui->labelBtnInfo->setText("Button 4 Clicked.");
}

void MainWindow::on_btn5_clicked()
{
    ui->labelBtnInfo->setText("Button 5 Clicked.");
}

void MainWindow::on_btn6_clicked()
{
    ui->labelBtnInfo->setText("Button 6 Clicked.");
}

void MainWindow::on_btn7_clicked()
{
    ui->labelBtnInfo->setText("Button 7 Clicked.");
}

void MainWindow::on_btn8_clicked()
{
    ui->labelBtnInfo->setText("Button 8 Clicked.");
}
