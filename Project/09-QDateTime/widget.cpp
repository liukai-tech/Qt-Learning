#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,  m_updateTimer(this)
{
    ui->setupUi(this);

    QFont SimSunFont("SimSun", 16);
    ui->labelCurrDateTime->setFont(SimSunFont);
    ui->labelCurrDateTime->setStyleSheet("color:blue;");

    m_updateTimer.setTimerType(Qt::PreciseTimer);/* 使用高精度软件定时器刷新当前时间 */
    connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(updateLabelTime()));
    m_updateTimer.start(100);

    m_fTimer=new QTimer(this);
    m_fTimer->stop();
    m_fTimer->setInterval (1000);//设置定时周期，单位：毫秒
    connect(m_fTimer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnGetCurrTime_clicked()
{
    //获取当前日期时间，为三个专用编辑器设置日期时间数据，并转换为字符串
    QDateTime curDateTime=QDateTime::currentDateTime();
    ui->timeEdit->setTime(curDateTime.time());
    ui->lineEditTime->setText (curDateTime.toString ("hh:mm:ss"));
    ui->dateEdit->setDate(curDateTime.date());
    ui->lineEditDate->setText(curDateTime.toString("yyyy-MM-dd"));
    ui->dateTimeEdit->setDateTime(curDateTime);
    ui->lineEditDateTime->setText(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}

void Widget::on_btnSetTime_clicked()
{
    //字符串转换为QTime
    QString str = ui->lineEditTime->text();
    str = str.trimmed();
    if (!str.isEmpty())
    {
        QDateTime time = QDateTime::fromString(str,"hh:mm:ss");
        ui->timeEdit->setDateTime(time);
    }
}

void Widget::on_btnSetDate_clicked()
{
    //字符串转换为QDate
    QString str = ui->lineEditDate->text();
    str = str.trimmed();
    if (!str.isEmpty())
    {
        QDateTime date = QDateTime::fromString(str,"yyyy-MM-dd");
        ui->dateEdit->setDateTime(date);
    }
}

void Widget::on_btnSetDateTime_clicked()
{
    //字符串转换为QDateTime
    QString str=ui->lineEditDateTime->text();
    str=str.trimmed();
    if (!str.isEmpty())
    {
        QDateTime datetime=QDateTime::fromString(str,"yyyy-MM-dd hh:mm:ss");
        ui->dateTimeEdit->setDateTime(datetime);
    }
}

void Widget::updateLabelTime(void)
{
    ui->labelCurrDateTime->setText(QDateTime::currentDateTime().toString(Qt::DefaultLocaleLongDate));
}

void Widget::on_calendarWidget_selectionChanged()
{
    //在日历上选择日期
    QDate dt=ui->calendarWidget->selectedDate();
    QString str=dt.toString("yyyy年 M 月 d 日");
    ui->lineEditSelectedDateTime->setText(str);
}

void Widget::on_timer_timeout()
{
    //定时器中断响
    QTime curTime=QTime::currentTime(); //获取当前时间
    ui->lcdNumberHour->display(curTime.hour()); //显示小时
    ui->lcdNumberMin->display(curTime.minute()); //显示分钟
    ui->lcdNumberSec->display(curTime.second()); //显示秒
    int va=ui->progressBar->value();
    va++;
    if (va>100)
        va=0;
    ui->progressBar->setValue(va);
}

void Widget::on_btnSetPeriod_clicked()
{
    uint64_t period = ui->spinBoxPeriod->value();
    if(period > 0)
    {
        m_fTimer->setInterval(period);
    }
}

void Widget::on_btnStart_clicked()
{
    m_fTimer->start() ;//定时器开始工作
    m_fTimeCounter.start() ; //计时器开始工作
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->btnSetPeriod->setEnabled(false);
}

void Widget::on_btnStop_clicked()
{
    m_fTimer->stop() ; //定时器停止
    int tmMsec = m_fTimeCounter.elapsed() ;//毫秒数
    int ms = tmMsec%1000;
    int sec = tmMsec/1000;
    QString str=QString::asprintf ("流逝时间：%d 秒，%03d 毫秒", sec, ms);
    ui->labelElapsTime->setText(str);
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->btnSetPeriod->setEnabled(true);
}
