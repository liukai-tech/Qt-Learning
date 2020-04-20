#include "sqliteoperator.h"

// 构造函数中初始化数据库对象，并建立数据库
SqliteOperator::SqliteOperator()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        m_database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        m_database.setDatabaseName("MyGpsLandDataBase.db");
    }
}


// 打开数据库
bool SqliteOperator::openDb()
{
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        // do something
    }

    return true;
}

// 创建数据表
void SqliteOperator::createTable()
{
    // 用于执行sql语句的对象
    QSqlQuery sqlQuery;
    // 构建创建数据库的sql语句字符串
    QString createSql = QString("CREATE TABLE gpsland (\
                          id INT PRIMARY KEY NOT NULL,\
                          posx REAL NOT NULL,\
                          posy REAL NOT NULL,\
                          height FLOAT NOT NULL,\
                          basehgt FLOAT NOT NULL)");
    sqlQuery.prepare(createSql);
    // 执行sql语句
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

// 判断数据库中某个数据表是否存在
bool SqliteOperator::isTableExist(QString& tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }

    return false;
}

// 查询全部数据
void SqliteOperator::queryTable()
{
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT * FROM gpsland");
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            double posx = sqlQuery.value(1).toDouble();
            double posy = sqlQuery.value(2).toDouble();
            float height = sqlQuery.value(3).toFloat();
            float basehgt = sqlQuery.value(4).toFloat();
            qDebug()<<QString("id:%1    posx:%2    posy:%3    height:%4    basehgt:%5")
                      .arg(id)
                      .arg(posx, 0, 'f', 4, QChar('0'))
                      .arg(posy, 0, 'f', 4, QChar('0'))
                      .arg(height, 0, 'f', 4, QChar('0'))
                      .arg(basehgt, 0, 'f', 4, QChar('0'));
        }
    }
}

// 插入单条数据
void SqliteOperator::singleInsertData(gpslanddb_t &singledb)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO gpsland VALUES(:id,:posx,:posy,:height,:basehgt)");
    sqlQuery.bindValue(":id", singledb.id);
    sqlQuery.bindValue(":posx", singledb.posx);
    sqlQuery.bindValue(":posy", singledb.posy);
    sqlQuery.bindValue(":height", singledb.height);
    sqlQuery.bindValue(":basehgt", singledb.basehgt);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

// 插入多条数据
void SqliteOperator::moreInsertData(QList<gpslanddb_t>& moredb)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO gpsland VALUES(?,?,?,?,?)");
    QVariantList idList, posxList, posyList, heightList, basehgtList;
    for(int i=0; i< moredb.size(); i++)
    {
        idList <<  moredb.at(i).id;
        posxList << moredb.at(i).posx;
        posyList << moredb.at(i).posy;
        heightList << moredb.at(i).height;
        basehgtList << moredb.at(i).basehgt;
    }
    sqlQuery.addBindValue(idList);
    sqlQuery.addBindValue(posxList);
    sqlQuery.addBindValue(posyList);
    sqlQuery.addBindValue(heightList);
    sqlQuery.addBindValue(basehgtList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        qDebug() << sqlQuery.lastError();
    }
}

// 修改数据
void SqliteOperator::modifyData(int id, double posx, double posy, float height, float basehgt)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE gpsland SET posx=?,posy=?,height=?,basehgt=? WHERE id=?");
    sqlQuery.addBindValue(posx);
    sqlQuery.addBindValue(posy);
    sqlQuery.addBindValue(height);
    sqlQuery.addBindValue(basehgt);
    sqlQuery.addBindValue(id);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}

// 删除数据
bool SqliteOperator::deleteData(int id)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DELETE FROM gpsland WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
        return false;
    }
    else
    {
        qDebug()<<"deleted data success!";
        return true;
    }
}

//删除数据表
void SqliteOperator::deleteTable(QString& tableName)
{
    QSqlQuery sqlQuery;

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "deleted table success";
    }
}

void SqliteOperator::closeDb(void)
{
    m_database.close();
}


