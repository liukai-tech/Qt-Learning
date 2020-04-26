#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化矩形的尺寸和放大缩小的系数
    m_rect.setRect(50,50,50,50);
    m_zoom = 1.0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

//绘图
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    QBrush brush;
    QPen pen;

    //设置坐标系
    p.translate(m_currentCoordinates);
    //反锯齿
    p.setRenderHint(QPainter::Antialiasing);
    //设置画笔颜色，边框的颜色
    brush.setColor(Qt::blue);
    //设置填充的风格，不设置默认不填充
    brush.setStyle(Qt::SolidPattern);
    //设置画刷的颜色，矩形填充的颜色
    pen.setColor(Qt::red);
    //将画笔和画刷给QPainter
    p.setPen(pen);
    p.setBrush(brush);
    //画矩形
    p.drawRect(m_rect);

}

//放大缩小函数
void MainWindow::zoomPixmap()
{
    float width,hight;

    width = m_rect.width();
    hight = m_rect.height();
    width = width*m_zoom;
    hight = hight*m_zoom;
    m_rect.setWidth(width);
    m_rect.setHeight(hight);
}

//鼠标按键按下事件
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    //鼠标按下时记录当前按下的坐标
    if(ev->button() == Qt::LeftButton)
    {
        if(ev->x()>m_rect.x() && ev->x()<m_rect.x()+m_rect.width())
        {
            if(ev->y()>m_rect.y() && ev->y()<m_rect.y()+m_rect.height())
            {
                m_lastCoordinates = ev->pos();
            }
        }
    }
}
//鼠标滚轮事件
void MainWindow::wheelEvent(QWheelEvent *ev)
{
    //如果滚轮向上滚动就放大尺寸
    if(ev->delta() > 0)
    {
        m_zoom = 1.1;
    }
    else//如果滚轮向下滚动就缩小尺寸
    {
        m_zoom = 0.9;
    }
    zoomPixmap();
    update();
}
//鼠标移动事件
void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    //当鼠标左键按下且移动
    if(ev->buttons() & Qt::LeftButton){
        //计算当前需要移动的距离，保存本次的坐标
        m_currentCoordinates = m_currentCoordinates - m_lastCoordinates + ev->pos();
        m_lastCoordinates = ev->pos();
        ev->accept();
        this->update();
    }
}
