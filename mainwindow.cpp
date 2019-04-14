#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage(QString::fromLocal8Bit("浅夏沫若"));
    this->setFixedSize( this->width(),this->height());
    setWindowTitle(QString::fromLocal8Bit("位图隐写分析器/.lx"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//加载图片
void MainWindow::on_loadPictureButton_clicked()
{
    this->fileName=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("加载图片:"),QDir::currentPath());
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, QString::fromLocal8Bit("提示:"),QString::fromLocal8Bit("加载图片为空,请重新载入..."));
            return;
        }
        ui->imageLabel->setPixmap(QPixmap::fromImage(image).scaled(ui->imageLabel->size()));
    }
}

//头部处理
void MainWindow::on_fileHeadButton_clicked()
{
    ui->textEdit->clear();
    BMPHide hide;

    //读取图片
    bool isBMP=hide.setBmpFileName(this->fileName.toLatin1().data());
    if(isBMP)
    {
        ui->statusBar->showMessage(QString::fromLocal8Bit("图片读取成功！",7*1000));
    }
    else
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示:"),QString::fromLocal8Bit("图片读取错误,请重新载入..."));
        return;
    }

    //分析隐写的实现
    if(ui->checkBox->isChecked())   //分析
    {
        hide.headhideBMP1();//头检测
        ui->lineEdit->clear();
        hide.showStringInBmp("D:/images/4_2.bmp.hide.bmp");   //读取隐写信息
        QString text=(QString::fromLocal8Bit("###图片提取信息如下...###"))+"\n"
                +(QString::fromLocal8Bit("图片宽度："))+QString::number(hide.getBmpWidth())+"\n"
                +(QString::fromLocal8Bit("图片高度："))+QString::number(hide.getBmpHeight())+"\n"
                +(QString::fromLocal8Bit("图片位数："))+QString::number(hide.getBmpBitCount())+"\n"
                +(QString::fromLocal8Bit("分析结果："))+hide.myinfo;
        ui->textEdit->setText(text);
        ui->statusBar->showMessage(QString::fromLocal8Bit("图片分析成功！",7*1000));
    }
    else    //隐写
    {
        if(this->fileName.isEmpty())
            this->on_loadPictureButton_clicked();

        bool ok=hide.headhideBMP();
        hide.save();
        if(ok)
        {
            ui->statusBar->showMessage(QString::fromLocal8Bit("图片隐写成功！",7*1000));
            ui->lineEdit->clear();
        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("错误："),QString::fromLocal8Bit("信息未成功写入！"));
        }
    }
}

//数据区处理
void MainWindow::on_dataButton_clicked()
{
    ui->textEdit->clear();
    BMPHide hide;

    //读取图片
    bool isBMP=hide.setBmpFileName(this->fileName.toLatin1().data());
    if(isBMP)
    {
        ui->statusBar->showMessage(QString::fromLocal8Bit("图片读取成功！",7*1000));
    }
    else
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示:"),QString::fromLocal8Bit("图片读取错误,请重新载入..."));
    }

    //分析隐写的实现
    if(ui->checkBox->isChecked())   //分析
    {
        ui->lineEdit->clear();
        hide.showStringInBmp("D:/images/4_2.bmp.hide.bmp");   //读取隐写信息
        QString text=(QString::fromLocal8Bit("###图片信息如下...###"))+"\n"
                +(QString::fromLocal8Bit("图片宽度："))+QString::number(hide.getBmpWidth())+"\n"
                +(QString::fromLocal8Bit("图片高度："))+QString::number(hide.getBmpHeight())+"\n"
                +(QString::fromLocal8Bit("图片位数："))+QString::number(hide.getBmpBitCount())+"\n"
                +(QString::fromLocal8Bit("隐藏信息："))+QString::fromUtf8(hide.info);
        ui->textEdit->setText(text);
        ui->statusBar->showMessage(QString::fromLocal8Bit("图片分析成功！",7*1000));
    }
    else    //隐写
    {
        if(this->fileName.isEmpty())
            this->on_loadPictureButton_clicked();

        bool ok=hide.hideString2BMP(ui->lineEdit->text().toLatin1().data());
        hide.save();
        if(ok)
        {
            ui->statusBar->showMessage(QString::fromLocal8Bit("图片隐写成功！",7*1000));
            ui->lineEdit->clear();
        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("错误："),QString::fromLocal8Bit("信息未成功写入！"));
        }
    }
}


//尾部处理
void MainWindow::on_fileTarbutton_clicked()
{
    ui->textEdit->clear();
    BMPHide hide;

    //读取图片
    bool isBMP=hide.setBmpFileName(this->fileName.toLatin1().data());
    if(isBMP)
    {
        ui->statusBar->showMessage(QString::fromLocal8Bit("图片读取成功！",7*1000));
    }
    else
    {
        QMessageBox::information(this, QString::fromLocal8Bit("提示:"),QString::fromLocal8Bit("图片读取错误,请重新载入..."));
        return;
    }

    //分析隐写的实现
    if(ui->checkBox->isChecked())   //分析
    {
        ui->lineEdit->clear();
        hide.hideString3BMP1();
        QString text=(QString::fromLocal8Bit("###图片信息如下...###"))+"\n"
                +(QString::fromLocal8Bit("图片宽度："))+QString::number(hide.getBmpWidth())+"\n"
                +(QString::fromLocal8Bit("图片高度："))+QString::number(hide.getBmpHeight())+"\n"
                +(QString::fromLocal8Bit("图片位数："))+QString::number(hide.getBmpBitCount())+"\n"
                +(QString::fromLocal8Bit("分析结果："))+hide.myinfo;
        ui->textEdit->setText(text);
        ui->statusBar->showMessage(QString::fromLocal8Bit("图片分析成功！",7*1000));
    }
    else    //隐写
    {
        if(this->fileName.isEmpty())
            this->on_loadPictureButton_clicked();

        bool ok=hide.hideString3BMP(this->fileName.toLatin1().data(),ui->lineEdit->text().toLatin1().data());//尾部追加
        hide.save();
        if(ok)
        {
            ui->statusBar->showMessage(QString::fromLocal8Bit("图片隐写成功！",7*1000));
            ui->lineEdit->clear();
        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("错误："),QString::fromLocal8Bit("信息未成功写入！"));
        }
    }
}
