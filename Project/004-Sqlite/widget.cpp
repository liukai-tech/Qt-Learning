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
        QMessageBox::warning(this, "warning", "Database open failed.");
    }
    else
    {
        ui->textEdit->setText("Database open success.");
    }

    // 判断数据表是否存在
    QString str1 = QString("gpsland");
    bool isTableExist = sqlTest->isTableExist(str1);
//    qDebug() << "isTabelExist：" << isTableExist;
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
        ui->textEdit->setText("Please enter the ID to be deleted."); //删除的时候需要输入ID
    }
    else
    {
        bool isDeleteData = sqlTest->deleteData(id);
        if(isDeleteData)
        {
            ui->textEdit->setText("Delete Success.");
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
    float basehgt = ui->lineEditBaseHgt->text().toFloat();
    if((ui->lineEditId->text() == NULL)
            || (ui->lineEditPosX->text() == NULL)
            || (ui->lineEditPosY->text() == NULL)
            || (ui->lineEditHeight->text() == NULL)
            || (ui->lineEditBaseHgt->text() == NULL))
    {
        ui->textEdit->setText("Please enter valid data.");
    }
    else
    {
        gpslanddb_t gpslanddbTest1;
        gpslanddbTest1.id = id;
        gpslanddbTest1.posx = posx;
        gpslanddbTest1.posy = posy;
        gpslanddbTest1.height = height;
        gpslanddbTest1.basehgt = basehgt;
        bool isInsert = sqlTest->singleInsertData(gpslanddbTest1);
        if(isInsert)
        {
            ui->textEdit->setText("Insert Success.");
        }
        else
        {
            ui->textEdit->setText("Insert Failed.");
        }
    }
}

void Widget::on_btnUpdate_clicked()
{
    qulonglong id = ui->lineEditId->text().toULongLong();
    double posx = ui->lineEditPosX->text().toDouble();
    double posy = ui->lineEditPosY->text().toDouble();
    float height = ui->lineEditHeight->text().toFloat();
    float basehgt = ui->lineEditBaseHgt->text().toFloat();
    if((id == 0)
        ||(ui->lineEditId->text() == NULL)
        || (ui->lineEditPosX->text() == NULL)
        || (ui->lineEditPosY->text() == NULL)
        || (ui->lineEditHeight->text() == NULL)
        || (ui->lineEditBaseHgt->text() == NULL))
    {
        ui->textEdit->setText("Please enter valid data.");
    }
    else
    {
        bool isUpdate = sqlTest->modifyData(id, posx, posy, height, basehgt);
        if(isUpdate)
        {
            ui->textEdit->setText("Update Success.");
        }
        else
        {
            ui->textEdit->setText("Update Failed.");
        }
    }
}

void Widget::on_btnQuery_clicked()
{
    qulonglong searchid = ui->lineEditId->text().toULongLong();

    if(searchid == 0)
    {
        ui->textEdit->setText("Please enter query id.");
    }
    else
    {
        //从数据库中查询是否有这么一个id
        QString str = QString("select *from gpsland where id = '%1'").arg(searchid);
        QSqlQuery query;
        query.exec(str);

        qulonglong id = 0;
        double posx;
        double posy;
        float height;
        float basehgt;

        while (query.next())
        {
            id = query.value(0).toULongLong();
            posx = query.value(1).toDouble();
            posy =  query.value(2).toDouble();
            height = query.value(3).toFloat();
            basehgt =  query.value(4).toFloat();
        }

        if(id == 0)
        {
            QString a = QString("Cannot find this id(%1),please enter again.").arg(searchid);
            ui->textEdit->setText(a);
            ui->lineEditId->clear();
            ui->lineEditPosX->clear();
            ui->lineEditPosY->clear();
            ui->lineEditHeight->clear();
            ui->lineEditBaseHgt->clear();
        }
        else
        {
            QString idstr = QString("%1").arg(id);
            QString posxstr = QString("%1").arg(posx, 0, 'f', 4, QChar('0'));
            QString posystr = QString("%1").arg(posy, 0, 'f', 4, QChar('0'));
            QString heightstr = QString("%1").arg(height, 0, 'f', 4, QChar('0'));
            QString basehgtstr = QString("%1").arg(basehgt, 0, 'f', 4, QChar('0'));

            ui->lineEditId->setText(idstr);
            ui->lineEditPosX->setText(posxstr);
            ui->lineEditPosY->setText(posystr);
            ui->lineEditHeight->setText(heightstr);
            ui->lineEditBaseHgt->setText(basehgtstr);
            ui->textEdit->setText("Query Success.");
        }
    }
}

void Widget::on_btnQueryAll_clicked()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM gpsland");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
        ui->textEdit->setText("Error: Fail to query table");
    }
    else
    {
        ui->textEdit->clear();
        while(sqlQuery.next())
        {
            qulonglong id = sqlQuery.value(0).toULongLong();
            double posx = sqlQuery.value(1).toDouble();
            double posy = sqlQuery.value(2).toDouble();
            float height = sqlQuery.value(3).toFloat();
            float basehgt = sqlQuery.value(4).toFloat();

            QString str = QString("id:%1    posx:%2    posy:%3    height:%4    basehgt:%5")
                      .arg(id)
                      .arg(posx, 0, 'f', 4, QChar('0'))
                      .arg(posy, 0, 'f', 4, QChar('0'))
                      .arg(height, 0, 'f', 4, QChar('0'))
                      .arg(basehgt, 0, 'f', 4, QChar('0'));
            ui->textEdit->append(str);
        }
    }
}
