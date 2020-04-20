#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "sqliteoperator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnDelete_clicked();

    void on_btnInsert_clicked();

    void on_btnUpdate_clicked();

    void on_btnQuery_clicked();

    void on_btnQueryAll_clicked();

private:
    Ui::Widget *ui;
    SqliteOperator *sqlTest;
};
#endif // WIDGET_H
