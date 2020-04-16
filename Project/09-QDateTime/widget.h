#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnGetCurrTime_clicked();

    void on_btnSetTime_clicked();

    void on_btnSetDate_clicked();

    void on_btnSetDateTime_clicked();

    void updateLabelTime(void);

    void on_calendarWidget_selectionChanged();

    void on_timer_timeout(); //定时溢出处理槽函数

    void on_btnSetPeriod_clicked();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

private:
    Ui::Widget *ui;
    QTimer m_updateTimer;

    QTimer *m_fTimer; //定时器
    QElapsedTimer m_fTimeCounter;//计时器
};
#endif // WIDGET_H
