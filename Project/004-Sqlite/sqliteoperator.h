#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

typedef struct
{
    int id;
    double posx;
    double posy;
    float height;
    float basehgt;

}gpslanddb_t;

class SqliteOperator
{
public:
    SqliteOperator();

    // 打开数据库
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    // 查询全部数据
    void queryTable();
    // 插入数据
    bool singleInsertData(gpslanddb_t &singleData); // 插入单条数据
    bool moreInsertData(QList<gpslanddb_t> &moreData); // 插入多条数据
    // 修改数据
    bool modifyData(int id, double posx, double posy, float height, float basehgt);
    // 删除数据
    bool deleteData(int id);
    //删除数据表
    void deleteTable(QString& tableName);
    // 关闭数据库
    void closeDb(void);

private:
    QSqlDatabase m_database;// 用于建立和数据库的连接

};

#endif // SQLITEOPERATOR_H
