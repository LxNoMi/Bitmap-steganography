#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//λͼ��д����������Ҫʵ����λͼ��ͷ�������ݲ��֣�β��������Ϣ�����������Ϣ
//code and designed by swust.��Ѷ,

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
