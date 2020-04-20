#include "widget.h"
#include "ui_widget.h"

#include <QTextCodec>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("SQLite");//设置窗口的标题

    //创建并打开SQLite数据库
    SqliteOperator *sqlTest = new SqliteOperator();
    bool isdbOpen = sqlTest->openDb();
    if(!isdbOpen) //如果数据库打开失败，会弹出一个警告窗口
    {
        QMessageBox::warning(this, "警告", "数据库打开失败");
    }
    else
    {
        ui->textEdit->setText("数据库打开成功");
    }

    // 判断数据表是否存在
    QString str1 = QString("gpsland");
    bool isTableExist = sqlTest->isTableExist(str1);
    qDebug() << "isTabelExist：" << isTableExist;
    if(!isTableExist){
        // 不存在数据表，重新创建数据表
        sqlTest->createTable();
    }

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnDelete_clicked()
{
    int id = ui->lineEditId->text().toUInt();//从行编辑框中获取需要删除的ID
    if(id ==  0)
    {
        ui->textEdit->setText("Please enter the ID to be deleted"); //删除的时候需要输入ID
    }
    else
    {
        bool isDeleteData = sqlTest->deleteData(id);
        if(isDeleteData)
        {
            ui->textEdit->setText("删除成功");
        }
        else
        {
            QString a = QString("Cannot find this Id(%1),delete failed").arg(id);
            ui->textEdit->setText(a);
        }
    }
}

void Widget::on_btnInsert_clicked()
{
    qulonglong id = ui->lineEditId->text().toULongLong();
    double posx = ui->lineEditPosX->text().toDouble();
    double posy = ui->lineEditPosY->text().toDouble();
    float height = ui->lineEditHeight->text().toFloat();
    double basehgt = ui->lineEditBaseHgt->text().toDouble();

    gpslanddb_t gpslanddbTest1;
    sqlTest->singleInsertData(gpslanddbTest1);

    QString namestr = ui->lineEditName->text();
    int num = ui->lineEditNumber->text().toInt();
    double score = ui->lineEditScore->text().toDouble();
    if(namestr == NULL || num == 0 || ui->lineEditScore == NULL) //插入信息的时候需要输入完整的信息
    {
        ui->textEdit->setText("请输入完整的信息");
    }
    else
    {
        QString str = QString("insert into student(num, name, score) values('%1', '%2', '%3')").arg(num).arg(namestr).arg(score);
        QSqlQuery query;
        query.exec(str); //执行插入操作
        ui->lineEditName->clear();
        ui->lineEditNumber->clear();
        ui->lineEditScore->clear();
        ui->textEdit->setText("插入成功");
    }
}

void Widget::on_btnUpdate_clicked()
{

}

void Widget::on_btnQuery_clicked()
{

}

void Widget::on_btnQueryAll_clicked()
{

}
