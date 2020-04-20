#include <QCoreApplication>
#include "sqliteoperator.h"
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //创建并打开SQLite数据库
    SqliteOperator sqlTest;
    sqlTest.openDb();

    // 创建数据表
    sqlTest.createTable();

    // 判断数据表是否存在
    QString str1 = QString("gpsland");
    qDebug() << "isTabelExist：" <<sqlTest.isTableExist(str1);

    // 插入单条数据
    gpslanddb_t gpslanddbTest1 = {1, -2256570.2442, 4413068.4334, 10.1234, 10.1345};
    gpslanddb_t gpslanddbTest2 = {2, -2256570.2455, 4413068.4333, 10.1434, 10.1345};
    sqlTest.singleInsertData(gpslanddbTest1);
    sqlTest.singleInsertData(gpslanddbTest2);

    // 插入多条数据
    QList<gpslanddb_t> list;
    gpslanddb_t gpslanddbTest3 = {3, -2256570.2427, 4413068.4308, 10.1134, 10.1345};
    gpslanddb_t gpslanddbTest4 = {4, -2256570.2438, 4413068.4358, 10.1334, 10.1345};
    list.append(gpslanddbTest3);
    list.append(gpslanddbTest4);
    sqlTest.moreInsertData(list);
    // 查询全部数据
    sqlTest.queryTable();
    qDebug() << endl;

    // 修改数据
    sqlTest.modifyData(2, -2256570.2455, 4413068.4333, 10.1434, 10.1445);
    // 查询全部数据
    sqlTest.queryTable();
    qDebug() << endl;

//    // 删除数据
//    sqlTest.deleteData(2);
//    // 查询全部数据
//    sqlTest.queryTable();
//    qDebug() << endl;

    // 删除数据表
//    QString str2 = QString("gpsland");
//    sqlTest.deleteTable(str2);

    //关闭数据库
    sqlTest.closeDb();


    return a.exec();
}
