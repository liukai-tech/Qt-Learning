#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool openTextByIODevice(const QString &aFileName);
    bool saveTextByIODevice(const QString &aFileName);
    bool openTextByStream(const QString &aFileName);
    bool saveTextByStream(const QString &aFileName);

private slots:
    void on_actionOpenFile_triggered();

    void on_actionSaveFile_triggered();

    void on_actionOpenTextFile_triggered();

    void on_actionSaveTextFile_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
