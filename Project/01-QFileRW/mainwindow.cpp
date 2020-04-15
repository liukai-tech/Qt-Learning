#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Reference:http://c.biancheng.net/view/1877.html
 * */

void MainWindow::on_actionOpenFile_triggered()
{//打开文件
    QString curPath=QDir::currentPath();//获取系统当前目录
    QString dlgTitle="打开一个文件"; //对话框标题
    QString filter="程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;
    openTextByIODevice(aFileName);
}

bool MainWindow::openTextByIODevice(const QString &aFileName)
{//用IODevice方式打开文本文件
    QFile aFile(aFileName);
    if (!aFile.exists()) //文件不存在
        return false;
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    ui->textEditDevice->setPlainText(aFile.readAll());
    aFile.close();
    ui->tabWidget->setCurrentIndex(0);
    return  true;
}

void MainWindow::on_actionSaveFile_triggered()
{
    QString curPath=QDir::currentPath();//获取系统当前目录
    QString dlgTitle="另存为一个文件"; //对话框标题
    QString filter="h文件(*.h);;c++文件(*.cpp);;文本文件(*.txt);;所有文件(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;
    saveTextByIODevice(aFileName);
}

bool MainWindow::saveTextByIODevice(const QString &aFileName)
{ //用IODevice方式保存文本文件
    QFile aFile(aFileName);
    //aFile.setFileName(aFileName);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QString str=ui->textEditDevice->toPlainText();//整个内容作为字符串
    QByteArray  strBytes=str.toUtf8();//转换为字节数组
    //QByteArray  strBytes=str.toLocal8Bit();
    aFile.write(strBytes,strBytes.length());  //写入文件
    aFile.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

void MainWindow::on_actionOpenTextFile_triggered()
{//打开文件
    QString curPath=QDir::currentPath();//获取系统当前目录
    QString dlgTitle="打开一个文件"; //对话框标题
    QString filter="程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;
    openTextByStream(aFileName);

}

//bool MainWindow::openTextByStream(const QString &aFileName)
//{ //用 QTextStream打开文本文件
//    QFile aFile(aFileName);
//    if (!aFile.exists()) //文件不存在
//        return false;
//    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
//        return false;
//    QTextStream aStream(&aFile); //用文本流读取文件
//    ui->textEditStream->setPlainText(aStream.readAll());
//    aFile.close();//关闭文件
//    ui->tabWidget->setCurrentIndex(1);
//    return  true;
//}

bool MainWindow::openTextByStream(const QString &aFileName)
{ //用 QTextStream打开文本文件
    QFile aFile(aFileName);
    if (!aFile.exists()) //文件不存在
        return false;
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile); //用文本流读取文件
    aStream.setAutoDetectUnicode(true); //自动检测Unicode,才能正常显示文档内的汉字
//    ui->textEditStream->setPlainText(aStream.readAll());
    ui->textEditStream->clear();//清空
    while (!aStream.atEnd())
    {
        QString str= aStream.readLine();//读取文件的一行
        ui->textEditStream->append(str); //添加到文本框显示
    }
    aFile.close();//关闭文件
    ui->tabWidget->setCurrentIndex(1);
    return  true;
}

void MainWindow::on_actionSaveTextFile_triggered()
{
    QString curPath=QDir::currentPath();//获取系统当前目录
    QString dlgTitle="另存为一个文件"; //对话框标题
    QString filter="h文件(*.h);;c++文件(*.cpp);;文本文件(*.txt);;所有文件(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;
    saveTextByStream(aFileName);
}

bool MainWindow::saveTextByStream(const QString &aFileName)
{//用QTextStream保存文本文件
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile); //用文本流读取文件
    QString str=ui->textEditStream->toPlainText(); //转换为字符串
    aStream<<str; //写入文本流
    aFile.close();//关闭文件
    return  true;
}
