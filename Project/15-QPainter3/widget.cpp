#include "widget.h"
#include "ui_widget.h"

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

//当鼠标按下时: 创建一条新线压入vector。并且将当前鼠标位置作为新线的起点。
void Widget::mousePressEvent(QMouseEvent *event){

    QVector<QPoint>line;
    _lines.append(line);

    QVector<QPoint>&last_line = _lines.last();  //注意：引用而不是新建，否则不是同一个内存
    last_line.append(event->pos());

    update();   //注意一定要记得update
}
//如果鼠标正在移动：将这些移动的点都压入最上面也就是最新的线
#include <QDebug>
void Widget::mouseMoveEvent(QMouseEvent *event){
   //  qDebug() << "mouseMoveEvent";
    if(!_lines.size()){  //保证安全
        QVector<QPoint>line;
        _lines.append(line);
    }
    QVector<QPoint>&last_line = _lines.last();
    last_line.append(event->pos());

     update();   //注意一定要记得update
}
//如果鼠标松开，这个点就是新线的终点，只需要把此时的点压入最新线就可以了
void Widget::mouseReleaseEvent(QMouseEvent *event){
    QVector<QPoint>&last_line = _lines.last();
    last_line.append(event->pos());

    update();   //注意一定要记得update
}
//在鼠标事件中记录线的轨迹，在绘画事件中绘制轨迹
void Widget::paintEvent(QPaintEvent *event){
    //创建画笔
//    QPainter painter(this);

    //vector数组中有几条线
//    for(int i = 0; i < _lines.size(); ++i){  //一条条绘制
//        QVector<QPoint>line = _lines.at(i);
//        for(int j = 0; j < line.size(); ++j){
//            QPoint tj = line.at(j);
//            painter.drawPoint(tj);   //不要画点，画线有专门的函数
//        }
//    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//反走样
    painter.setPen(QPen(QColor(0, 255, 0), 3));// 设置画笔颜色、宽度
    for(int i=0; i<_lines.size(); ++i)
    {
        const QVector<QPoint>& line = _lines.at(i);
        for(int j=0; j<line.size()-1; ++j)
        {
            painter.drawLine(line.at(j), line.at(j+1));
        }
    }
}
