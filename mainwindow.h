#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//位图隐写分析器，主要实现在位图的头部，数据部分，尾部加入信息或读出所加信息
//code and designed by swust.刘讯,

#include <QMainWindow>
#include<dwBmpSize.h>
#include<QFileDialog>
#include<QMessageBox>
#include<QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString fileName;
    
private slots:
    void on_loadPictureButton_clicked();

    void on_dataButton_clicked();

    void on_fileHeadButton_clicked();

    void on_fileTarbutton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
