#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    void on_btnInitItems_clicked();

    void on_btnInitItems2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_btnToComboBox_clicked();

    void on_btnClearComboBoxList_clicked();

    void on_btnClearPlainText_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

private:
    Ui::Widget *ui;
    bool m_isCanEdit;
    bool m_isReadOnly;
};
#endif // WIDGET_H
