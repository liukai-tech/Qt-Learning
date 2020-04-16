#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /* append() 在字符串的后面添加字符串，prepend() 在字符串的前面添加字符串。 */
    QString str1 = "Hello ", str2="World ";
    QString str3 = str1;
    str1.append(str2) ; //str1="Hello World"
    qDebug() << "append()--" << str1;
    str3.prepend(str2) ; //str3="World Hello "
    qDebug() << "prepend()--" << str3;

    /* toUpper() 将字符串内的字母全部转换为大写形式，toLower() 将字母全部转换为小写形式。 */
    QString str4="Hello, World", str5;
    str5 = str4.toUpper(); //str4="HELLO,WORLD"
    qDebug() << "toUpper()--" << str5;
    str5 = str4.toLower(); //str4="hello, world"
    qDebug() << "toLower()--" << str5;

    /* count()、size() 和 length() 都返回字符串的字符个数，这 3 个函数是相同的，但是要注意，字符串中如果有汉字，一个汉字算一个字符。 */
    QString str6="NI 好";
    int N;
    N = str6.count();  //N=3
    qDebug() << "count()--" << N;
    N=str6.size(); //N=3
    qDebug() << "size()--" << N;
    N=str6.length(); //N=3
    qDebug() << "length()--" << N;

    /* trimmed() 去掉字符串首尾的空格，simplified() 不仅去掉首尾的空格，中间连续的空格也用一个空格替换。 */
    QString str7=" Are  you  OK? ", str8;
    str8 = str7.trimmed () ; //str1="Are  you  OK? "
    qDebug() << "trimmed()--" << str8;
    str8 = str7.simplified(); //str1="Are you OK?"
    qDebug() << "simplified()--" << str8;

    /*
     * indexOf() 函数是在自身字符串内查找参数字符串 str 出现的位置，参数 from 是幵始查找的位置，Qt::CaseSensitivity cs 参数指定是否区分大小写。
     * lastIndexOf() 函数则是查找某个字符串最后出现的位置。
     */
    QString str9="Attitude determines everything. Details determine success or failure, the habit of success in life.";
    N = str9.indexOf("success");  // N=50
    qDebug() << "indexOf()--" << N;
    N = str9.lastIndexOf("th"); //N=70
    qDebug() << "lastIndexOf()--" << N;

    /*
     * isNull() 和 isEmpty()两个函数都判读字符串是否为空，但是稍有差别。如果一个空字符串，只有“\0”，isNull() 返回 false，
     * 而 isEmpty() 返回 true；只有未赋值的字符串，isNull() 才返回 true。
     * QString 只要赋值，就在字符串的末尾自动加上 "\0"，所以，如果只是要判断字符串内容是否为空，常用 isEmpty()。
     */
    QString str10, str11 = "";
    bool flag;
    flag = str10.isNull () ; // flag=true 未赋值字符串变量
    qDebug() << "isNull()--" << flag;
    flag = str11.isNull () ; // flag=false 只有"\0"的字符串，也不是 Null
    qDebug() << "isNull()--" << flag;
    flag = str10.isEmpty(); // flag=true
    qDebug() << "isEmpty()--" << flag;
    flag = str11.isEmpty(); // flag=true
    qDebug() << "isEmpty()--" << flag;

    /*
     * contains()判断字符串内是否包含某个字符串，可指定是否区分大小写。
     */
    QString str12="Life is short, i use Qt";
    bool flag1;
    flag1 = str12.contains("Qt", Qt::CaseInsensitive) ; // flag1=true,不区分大小写
    qDebug() << "contains( ,Qt::CaseInsensitive)--" << flag1;
    flag1 = str12.contains("QT", Qt::CaseSensitive) ;  // flag1=false,区分大小写
    qDebug() << "contains( ,Qt::CaseSensitive)--" << flag1;

    /*
     * startsWith() 判断是否以某个字符串幵头，endsWith() 判断是否以某个字符串结束。
     */
    QString str13 = "Talk is cheap, show me the code";
    bool flag2;
    flag2 = str13.endsWith ("code", Qt::CaseInsensitive) ; // flag2=true，不区分大小写
    qDebug() << "endsWith( ,Qt::CaseInsensitive)--" << flag2;
    flag2 = str13.endsWith ("CODE", Qt::CaseSensitive) ; // flag2=false，区分大小写
    qDebug() << "endsWith( ,Qt::CaseSensitive)--" << flag2;
    flag2 = str13.startsWith ("TA") ; // flag2=true，缺省为不区分大小写
    qDebug() << "startsWith()--" << flag2;

    /*
     * left() 表示从字符串中取左边多少个字符，right() 表示从字符串中取右边多少个字符。注意，一个汉字被当作一个字符。
     */
    QString str15, str14="学生姓名,男,1984-3-4,汉族,山东";
    int N1;
    N1 = str14.indexOf (",") ; // N1=4，第一个","出现的位置
    qDebug() << "indexOf()--" << N1;
    str15 = str14.left (N1) ; //str15="学生姓名"
    qDebug() << "left()--" << str15;
    N1 = str14.lastIndexOf (",") ; // N1=18，最后一个逗号的位置
    qDebug() << "lastIndexOf()--" << N1;
    str15 = str14.right (str14.size() - N1 - 1); //str15=”山东"，提取最后一个逗号之后的字符串
    qDebug() << "right()--" << str15;

    /*
     * section() 函数的功能是从字符串中提取以 sep 作为分隔符，从 start 端到 end 端的字符串。
     */
    QString str17, str16="学生姓名,男,1984-3-4,汉族,山东";
    str17=str16.section (",",0,0); // str17="学生姓名"， 第 1 段的编号为 0
    qDebug() << "section()--" << str17;
    str17=str16.section (",",1,1); // str17="男"
    qDebug() << "section()--" << str17;
    str17=str16.section (",",0,1); // str17="学生姓名，男"
    qDebug() << "section()--" << str17;
    str17=str16.section (",",4,4); // str17="山东"
    qDebug() << "section()--" << str17;

    return a.exec();
}
