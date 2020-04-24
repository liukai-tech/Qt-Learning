#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>

//参考：https://blog.csdn.net/liang19890820/article/details/51154216

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    /* 绘制文本 */

//    Q_UNUSED(event);

//    QPainter painter(this);
//    // 设置画笔颜色
//    painter.setPen(QColor(0, 160, 230));

//    // 设置字体：微软雅黑、点大小50、斜体
//    QFont font;
//    font.setFamily("Microsoft YaHei");
//    font.setPointSize(50);
//    font.setItalic(true);
//    painter.setFont(font);

//    // 绘制文本
//    painter.drawText(rect(), Qt::AlignCenter, "Qt");

    /* 绘制直线 */

//    Q_UNUSED(event);

//    QPainter painter(this);
//    // 反走样
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    // 设置画笔颜色
//    painter.setPen(QColor(0, 160, 230));
//    // 绘制直线
//    painter.drawLine(QPointF(0, height()), QPointF(width() / 2, height() / 2));

    /* 绘制矩形 */
//    Q_UNUSED(event);

//    QPainter painter(this);

//    // 反走样
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    // 设置画笔颜色、宽度
//    painter.setPen(QPen(QColor(0, 160, 230), 2));
//    // 设置画刷颜色
//    painter.setBrush(QColor(125, 255, 200));
//    painter.drawRect(50, 50, 160, 100);

    /* 绘制弧线 */
//    Q_UNUSED(event);

//    // 矩形
//    QRectF rect(90.0, 90.0, 80.0, 90.0);
//    // 起始角度
//    int startAngle = 30 * 16;
//    // 跨越度数
//    int spanAngle = 120 * 16;

//    QPainter painter(this);

//    // 反走样
//    painter.setRenderHint(QPainter::Antialiasing, true);

//    // 设置画笔颜色、宽度
//    painter.setPen(QPen(QColor(0, 160, 230), 2));

//    // 绘制弧线
//    painter.drawArc(rect, startAngle, spanAngle);

    /* 绘制椭圆和圆 */
//    Q_UNUSED(event);

//    QPainter painter(this);

//    // 反走样
//    painter.setRenderHint(QPainter::Antialiasing, true);

//    // 设置画笔颜色、宽度
//    painter.setPen(QPen(QColor(0, 160, 230), 2));

//    // 绘制椭圆
//    painter.drawEllipse(QPointF(120, 60), 50, 20);

//    // 设置画刷颜色
//    painter.setBrush(QColor(255, 160, 90));

//    // 绘制圆
//    painter.drawEllipse(QPointF(120, 140), 40, 40);


    /* 绘制多边形 */
//    Q_UNUSED(event);

//    QPainter painter(this);

//    // 反走样
//    painter.setRenderHint(QPainter::Antialiasing, true);

//    // 设置画笔颜色
//    painter.setPen(QColor(0, 160, 230));

//    // 各个点的坐标
//    static const QPointF points[4] = {QPointF(30, 40), QPointF(60, 150), QPointF(150, 160), QPointF(220, 100)};

//    // 绘制多边形
//    painter.drawPolygon(points, 4);

    /* 绘制图标 */

    Q_UNUSED(event);

    QPainter painter(this);

    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制图标
    painter.drawPixmap(rect(), QPixmap(":/Image/linux"));
}
