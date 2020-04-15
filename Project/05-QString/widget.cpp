#include "widget.h"
#include "ui_widget.h"
#include <stdlib.h>

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


void Widget::on_pushButtonCalculate_clicked()
{
    QString str = ui->lineEditNum->text() ;//读取数量n
    //int num = str.toInt();
    qulonglong num = str.toULongLong();
    str = ui->lineEditPrice->text(); //读取"单价"
    float price = str.toFloat();
    float total = num*price;
    str = QString("%1").arg(total, 0, 'f', 2, QChar('0'));
    ui->lineEditTotal->setText(str);
}

void Widget::on_pushButtonDec_clicked()
{
    //读取十进制数，转换为其他进制
    QString str = ui->lineEditDec->text();
    //int val = str.toInt();
    qulonglong val = str.toULongLong();//缺省为十进制
    // str=QString::number(val, 16);//转换为十六进制的字符串
    str = str.setNum (val, 16); //十六进制
    str = str.toUpper();
    ui->lineEditHex->setText(str);
    str = str.setNum (val, 2) ; //二进制
    // str=QString::number(val,2);
    ui->lineEditBin->setText(str);
}

void Widget::on_pushButtonBin_clicked()
{
    //读取二进制数，转换为其他进制的数
    QString str = ui->lineEditBin->text() ; //读取二进制字符串
    bool ok;
    //int val = str.toInt(&ok, 2);
    qulonglong val = str.toULongLong(&ok, 2) ; //以二进制数读入
    str = QString::number(val, 10) ;//数字显示为十进制字符串
    ui->lineEditDec->setText(str);
    str = str.setNum (val, 16) ; //显示为十六进制
    str = str.toUpper();
    ui->lineEditHex->setText(str);
}

void Widget::on_pushButtonHex_clicked()
{
    //读取十六进制数，转换为其他进制的数
    QString str = ui->lineEditHex->text() ; //读取十六进制字符串
    bool ok;
    //int val = str.toInt(&ok, 16);
    qulonglong val = str.toULongLong(&ok, 16) ; //以十六进制数读入
    str = QString::number(val, 10) ;//数字显示为十进制字符串
    ui->lineEditDec->setText(str);
    str = str.setNum (val, 2) ; //显示为二进制
    str = str.toUpper();
    ui->lineEditBin->setText(str);
}
