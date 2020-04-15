#include <QCoreApplication>
#include <QDebug>
#include <QLinkedList>
#include <QStack>
#include <QQueue>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

/* 顺序容器类
 * Qt 的顺序容器类有 QList、QLinkedList、QVector、QStack 和 QQueue。
 */
    QList<QString> aList;
    aList.append("Monday");
    aList.append("Tuesday");
    aList.append("Wednesday");
    qDebug() << "1.QList Test";
    for(int i = 0; i < aList.size(); i++){
        qDebug() << aList[i];
    }

    QLinkedList<QString> list;
    list << "one" << "two" << "three";
    // list: ["one", "two", "three"]
    qDebug() << endl << "2.QLinkedList Test";
    qDebug() << "first:" << list.first() << "last:" << list.last();

    QVector<QString> vector(200);
    vector.insert(0, "CK");
    vector.insert(10, "BBA");
    vector.insert(100, "Alfonso");
    qDebug() << endl << "3.QVector Test";
    for (int i = 0; i < vector.size(); ++i) {
        if (vector.at(i) == "CK")
            qDebug() << "Found CK at position " << i;
        if (vector.at(i) == "BBA")
            qDebug() << "Found BBA at position " << i;
        if (vector.at(i) == "Alfonso")
            qDebug() << "Found Alfonso at position " << i;
    }

    QStack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    qDebug() << endl << "4.QStack Test";
    while (!stack.isEmpty())
         qDebug() << stack.pop();

    QQueue<int> queue;
    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);
    qDebug() << endl << "5.QQueue Test";
    while (!queue.isEmpty())
        qDebug() << queue.dequeue();

/* 关联容器类
 * Qt 的关联容器类有 QMap、QMultiMap、QHash、QMultiHash 和 QSet。
 */

    QSet<QString> set;
    set << "dog" << "cat" << "tiger";
    qDebug() << endl << "6.QSet Test";
    if(set.contains("cat")){
        qDebug() << "Find cat in set";
    }

    QMap<QString, int> map;
    map["one"] = 1;
    map["two"] = 2;
    map["three "] = 3;

    map.insert("four", 4);
    map.remove("two");

    QList<QString> key;
    key = map.keys();
    qDebug() << endl << "7.QMap Test";
    for(int i = 0; i < key.size(); i++){
        qDebug() << i << key[i] << map.value(key[i]);
    }

    QMultiMap<QString, int> map1, map2, map3;
    map1.insert("plenty", 100);
    map1.insert("plenty", 2000); // map1.size() == 2
    map2.insert("plenty", 5000); // map2.size() == 1
    map3 = map1 + map2; // map3.size() == 3

    qDebug() << endl << "8.QMultiMap Test";
    QList<int> values = map3.values("plenty");
    for (int i = 0; i < values.size(); ++i)
        qDebug() << values.at(i);

    QHash<QString, int> hash;
    hash["jack"] = 18;
    hash["tom"] = 20;
    hash["rose"] = 25;

    QList<QString> hashkey;
    hashkey = hash.keys();
    qDebug() << endl << "9.QHash Test";
    for(int i = 0; i < hashkey.size(); i++){
        qDebug() << i << hashkey[i] << hash.value(hashkey[i]);
    }

    return a.exec();
}
