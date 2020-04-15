#include <QCoreApplication>
#include <QDebug>
#include <QLinkedList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

/*
 * Java 类型迭代器(QListItcrator只读迭代器 QMutableListItcrator读写迭代器)
 */
    QList<QString> list;
    list << "A" << "B" << "C" << "D";
    //正向遍历
    QListIterator<QString> i (list);
    while (i.hasNext())
        qDebug () << i.next ();

    //反向遍历
    QListIterator<QString> j (list);
    j.toBack();
    while (j.hasPrevious())
        qDebug() << j.previous();

    QList<int> list1;
    list1 << 1 << 2 << 3 << 4 << 5;
    QMutableListIterator<int> ii (list1);
    while (ii.hasNext()) {
        if (ii.next() % 2 != 0)
            ii.remove();
    }

/*
 * 关联容器类的迭代器的使用
 */
    QMap<QString, QString> map;
    map.insert("Paris", "France");
    map.insert("New York", "USA");
    map.insert("Mexico City", "USA");
    map.insert("Moscow", "Russia");

    QMapIterator<QString, QString> i3 (map);
    i3.toFront();
    while (i3.hasNext ()) {
        qDebug() << "key:" << i3.next().key();
    }

    QMapIterator<QString, QString> i4 (map);
    i4.toFront();
    while (i4.hasNext ()) {
        qDebug() << "value:" << i4.next().value();
    }

    /* 删除键（城市名称）里以“City”结尾的数据项 */
    QMutableMapIterator<QString, QString> i2 (map);
    while (i2.hasNext ()) {
        if (i2.next().key().endsWith("City"))
            i2.remove();
    }

    /* 删除map 里值为“USA”的所有数据项 */
    QMutableMapIterator<QString, QString> i5(map);
    while (i5.findNext("USA"))
        i5.remove();

    QMapIterator<QString, QString> i6 (map);
    i6.toFront();
    while (i6.hasNext ()) {
        qDebug() << "value:" << i6.next().value();
    }

/*
 * STL类型迭代器(const_iterator只读迭代器 iterator读写迭代器)
 */
    QList<QString> list2;
    list2 << "A" << "B" << "C" << "D";

    //正向遍历
    QList<QString>::const_iterator i10;
    for (i10 = list.constBegin(); i10 != list.constEnd(); ++i10){
        qDebug() << *i10;
    }

    //反向遍历
    QList<QString>::reverse_iterator i11;
    for (i11 = list.rbegin(); i11 != list.rend(); ++i11){
        *i11 = i11->toLower();
    }

/*
 * 关联容器类的迭代器的使用
 */
    QMap<int, int> map2;
    map2.insert(1, 123);
    map2.insert(2, 234);
    map2.insert(3, 345);
    map2.insert(4, 456);
    QMap<int, int>::const_iterator i12;
    for (i12 = map2.constBegin(); i12 != map2.constEnd(); ++i12)
        qDebug () << i12.key () << ':' << i12.value ();

/*
 * foreach遍历容器
 */
    QLinkedList<QString> Linkedlist;
    Linkedlist << "Apple" << "Banana" << "Carrot" << "Disk";
    QString str;
    foreach (str, Linkedlist)
        qDebug() << str;

    foreach (const QString &str, Linkedlist) {
        if (str.isEmpty())
            break;
        qDebug() << str;
    }

    /* 对于 QMap 和 QHash，foreach 会自动访问“键-值”对里的值，所以无需调用 values()。 */
    QMap<QString, int> map3;
    map3.insert("Apple", 9999);
    map3.insert("Mac", 19999);
    map3.insert("Huawei", 6999);
    map3.insert("Mi10", 5999);
    foreach (const QString &str, map3.keys())
        qDebug() << str << ':' << map3.value(str);

    /* 对于多值映射，可以使用两重 foreach 语句 */
    QMultiMap<QString, int> map4;
    map4.insert("Apple book", 19999);
    map4.insert("Mac book", 29999);
    map4.insert("Huawei pro", 7999);
    map4.insert("Mi book", 8999);
    foreach (const QString &str, map4.uniqueKeys()) {
        foreach (int i, map4.values(str))
            qDebug() << str << ':' << i;
    }

    return a.exec();
}
