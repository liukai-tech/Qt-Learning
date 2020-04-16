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

/*
 * 界面布局要点
 * 1.先使用gridlayout布局管理器将数量（label,lineEdit）、单价（label,lineEdit）、总价（label,lineEdit）、计算(pushButton)进行布局，简称Part1；
 * 2.同样使用gridlayout布局管理器将十进制(label,lineEdit,pushButton)、二进制(label,lineEdit,pushButton)、十六进制(label,lineEdit,pushButton)进行布局，简称Part2；
 * 3.加入verticalSpacer，再使用gridlayout布局管理器将Part1,verticalSpacer,Part2进行布局；
 * 4.选中widget，右键选择布局->栅格布局，再调整控件跟随窗体变化时规则即可（注：若此时选择在窗体内布局会出现水平拉伸不会跟随窗体变化而变化）。
 */


void Widget::on_pushButtonCalculate_clicked()
{
    //计算
    uint64_t num = ui->spinBoxNum->value();
    float price = ui->doubleSpinBoxPrice->value();
    float total = num * price;
    ui->doubleSpinBoxTotal->setValue(total);
}

void Widget::on_pushButtonDec_clicked()
{
    //读取十进制数，转换为其他进制
    qulonglong val=ui->spinBoxDec->value();
    ui->spinBoxBin->setValue(val);
    ui->spinBoxHex->setValue(val);
}

void Widget::on_pushButtonBin_clicked()
{
    //读取二进制数，转换为其他进制
    qulonglong val=ui->spinBoxBin->value();
    ui->spinBoxDec->setValue(val);
    ui->spinBoxHex->setValue(val);
}

void Widget::on_pushButtonHex_clicked()
{
    //读取十六进制数，转换为其他进制
    qulonglong val=ui->spinBoxHex->value();
    ui->spinBoxDec->setValue(val);
    ui->spinBoxBin->setValue(val);
}
