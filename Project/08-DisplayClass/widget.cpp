#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //this->setLayout(ui->gridLayout);
    QObject::connect(ui->horizontalSliderRed, SIGNAL(valueChanged(int)), this, SLOT(onColorSlidervalueChanged(int)));
    QObject::connect(ui->horizontalSliderGreen, SIGNAL(valueChanged(int)), this, SLOT(onColorSlidervalueChanged(int)));
    QObject::connect(ui->horizontalSliderBlue, SIGNAL(valueChanged(int)), this, SLOT(onColorSlidervalueChanged(int)));
    QObject::connect(ui->horizontalSliderAlpha, SIGNAL(valueChanged(int)), this, SLOT(onColorSlidervalueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

/*
 * 布局存在拉伸窗口控件不跟随变化，待解决。——2020/04/16 Caesar
 */

void Widget::onColorSlidervalueChanged(int value)
{
    //拖动Red、Green、Blue颜色滑动条时设置textEdit的底色
    Q_UNUSED(value);
    QColor color;
    int R = ui->horizontalSliderRed->value();
    int G = ui->horizontalSliderGreen->value();
    int B = ui->horizontalSliderBlue->value();
    int alpha = ui->horizontalSliderAlpha->value();
    color.setRgb (R, G, B, alpha) ; //使用 QColor 的 setRgb ()函数获得颜色
    QPalette pal=ui->textEditColor->palette();
    pal.setColor (QPalette::Base, color) ; //设置底色
    ui->textEditColor->setPalette (pal);
}

void Widget::on_horizontalSliderH_valueChanged(int value)
{
    ui->horizontalScrollBarH->setValue(value);
    ui->progressBarH->setValue(value);

}

void Widget::on_horizontalScrollBarH_valueChanged(int value)
{
    ui->horizontalSliderH->setValue(value);
    ui->progressBarH->setValue(value);
}

void Widget::on_verticalSliderV_valueChanged(int value)
{
    ui->verticalScrollBarV->setValue(value);
    ui->progressBarV->setValue(value);
}

void Widget::on_verticalScrollBarV_valueChanged(int value)
{
    ui->verticalSliderV->setValue(value);
    ui->progressBarV->setValue(value);
}

void Widget::on_dialInput_valueChanged(int value)
{
    //设置LCD的显示值等手Dial的值
    ui->lcdNumber->display(value);
}

void Widget::on_radioBtnDec_clicked()
{
    //设置LCD显示位数+十进制数
    ui->lcdNumber->setDigitCount(5) ; //设置位数
    ui->lcdNumber->setDecMode();
    ui->radioBtnBin->setChecked(false);
    ui->radioBtnOct->setChecked(false);
    ui->radioBtnHex->setChecked(false);
}

void Widget::on_radioBtnBin_clicked()
{
    //设置LCD显示位数+二进制数
    ui->lcdNumber->setDigitCount(17) ; //设置位数
    ui->lcdNumber->setBinMode();
    ui->radioBtnDec->setChecked(false);
    ui->radioBtnOct->setChecked(false);
    ui->radioBtnHex->setChecked(false);
}

void Widget::on_radioBtnOct_clicked()
{
    //设置LCD显示位数+八进制数
    ui->lcdNumber->setDigitCount(6) ; //设置位数
    ui->lcdNumber->setOctMode();
    ui->radioBtnDec->setChecked(false);
    ui->radioBtnBin->setChecked(false);
    ui->radioBtnHex->setChecked(false);
}

void Widget::on_radioBtnHex_clicked()
{
    //设置LCD显示位数+十六进制数
    ui->lcdNumber->setDigitCount(5) ; //设置位数
    ui->lcdNumber->setHexMode();
    ui->radioBtnDec->setChecked(false);
    ui->radioBtnBin->setChecked(false);
    ui->radioBtnOct->setChecked(false);
}
