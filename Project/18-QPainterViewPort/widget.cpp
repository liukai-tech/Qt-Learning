#include "widget.h"
#include "ui_widget.h"
#include <QPaintEvent>
#include <QPainter>

//参考 https://blog.csdn.net/qq_41453285/article/details/100056268

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int W=width(); //取窗体的宽
    int H=height();//去窗体的高
    int side=qMin(W,H); //取长和宽的最小值

    //先绘制一个矩形
    QRect rect((W-side)/2,(H-side)/2,side,side);
    painter.drawRect(rect);

    painter.setViewport(rect); //设置此次QPainter的区域，为一个正方形
    painter.setWindow(-100,-100,200,200);//设置窗口大小，原点在中心，边长为200
    painter.setRenderHint(QPainter::Antialiasing);

    //设置画笔
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    //线性渐变
    QLinearGradient linearGrad(0,0,100,0); //从左到右
    linearGrad.setColorAt(0,Qt::yellow); //起点颜色
    linearGrad.setColorAt(1,Qt::green); //终点颜色
    linearGrad.setSpread(QGradient::PadSpread); //展布模式
    painter.setBrush(linearGrad);

    //设置复合模式
    painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
    //painter.setCompositionMode(QPainter::CompositionMode_Difference);
    //painter.setCompositionMode(QPainter::CompositionMode_Exclusion);

    //每个椭圆的圆心在X轴的(50,0)，半径为50
    for(int i=0;i<36;i++)
    {
        painter.drawEllipse(QPoint(50,0),50,50);//画椭圆
        painter.rotate(10); //画一次，旋转10度
    }
}
