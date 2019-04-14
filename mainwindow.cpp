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
    ui->statusBar->showMessage(QString::fromLocal8Bit("ǳ��ĭ��"));
    this->setFixedSize( this->width(),this->height());
    setWindowTitle(QString::fromLocal8Bit("λͼ��д������/.lx"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//����ͼƬ
void MainWindow::on_loadPictureButton_clicked()
{
    this->fileName=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("����ͼƬ:"),QDir::currentPath());
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, QString::fromLocal8Bit("��ʾ:"),QString::fromLocal8Bit("����ͼƬΪ��,����������..."));
            return;
        }
        ui->imageLabel->setPixmap(QPixmap::fromImage(image).scaled(ui->imageLabel->size()));
    }
}

//ͷ������
void MainWindow::on_fileHeadButton_clicked()
{
    ui->textEdit->clear();
    BMPHide hide;

    //��ȡͼƬ
    bool isBMP=hide.setBmpFileName(this->fileName.toLatin1().data());
    if(isBMP)
    {
        ui->statusBar->showMessage(QString::fromLocal8Bit("ͼƬ��ȡ�ɹ���",7*1000));
    }
    else
    {
        QMessageBox::information(this, QString::fromLocal8Bit("��ʾ:"),QString::fromLocal8Bit("ͼƬ��ȡ����,����������..."));
        return;
    }

    //������д��ʵ��
    if(ui->checkBox->isChecked())   //����
    {
        hide.headhideBMP1();//ͷ���
        ui->lineEdit->clear();
        hide.showStringInBmp("D:/images/4_2.bmp.hide.bmp");   //��ȡ��д��Ϣ
        QString text=(QString::fromLocal8Bit("###ͼƬ��ȡ��Ϣ����...###"))+"\n"
                +(QString::fromLocal8Bit("ͼƬ��ȣ�"))+QString::number(hide.getBmpWidth())+"\n"
                +(QString::fromLocal8Bit("ͼƬ�߶ȣ�"))+QString::number(hide.getBmpHeight())+"\n"
                +(QString::fromLocal8Bit("ͼƬλ����"))+QString::number(hide.getBmpBitCount())+"\n"
                +(QString::fromLocal8Bit("���������"))+hide.myinfo;
        ui->textEdit->setText(text);
        ui->statusBar->showMessage(QString::fromLocal8Bit("ͼƬ�����ɹ���",7*1000));
    }
    else    //��д
    {
        if(this->fileName.isEmpty())
            this->on_loadPictureButton_clicked();

        bool ok=hide.headhideBMP();
        hide.save();
        if(ok)
        {
            ui->statusBar->showMessage(QString::fromLocal8Bit("ͼƬ��д�ɹ���",7*1000));
            ui->lineEdit->clear();
        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("��Ϣδ�ɹ�д�룡"));
        }
    }
}

//����������
void MainWindow::on_dataButton_clicked()
{
    ui->textEdit->clear();
    BMPHide hide;

    //��ȡͼƬ
    bool isBMP=hide.setBmpFileName(this->fileName.toLatin1().data());
    if(isBMP)
    {
        ui->statusBar->showMessage(QString::fromLocal8Bit("ͼƬ��ȡ�ɹ���",7*1000));
    }
    else
    {
        QMessageBox::information(this, QString::fromLocal8Bit("��ʾ:"),QString::fromLocal8Bit("ͼƬ��ȡ����,����������..."));
    }

    //������д��ʵ��
    if(ui->checkBox->isChecked())   //����
    {
        ui->lineEdit->clear();
        hide.showStringInBmp("D:/images/4_2.bmp.hide.bmp");   //��ȡ��д��Ϣ
        QString text=(QString::fromLocal8Bit("###ͼƬ��Ϣ����...###"))+"\n"
                +(QString::fromLocal8Bit("ͼƬ��ȣ�"))+QString::number(hide.getBmpWidth())+"\n"
                +(QString::fromLocal8Bit("ͼƬ�߶ȣ�"))+QString::number(hide.getBmpHeight())+"\n"
                +(QString::fromLocal8Bit("ͼƬλ����"))+QString::number(hide.getBmpBitCount())+"\n"
                +(QString::fromLocal8Bit("������Ϣ��"))+QString::fromUtf8(hide.info);
        ui->textEdit->setText(text);
        ui->statusBar->showMessage(QString::fromLocal8Bit("ͼƬ�����ɹ���",7*1000));
    }
    else    //��д
    {
        if(this->fileName.isEmpty())
            this->on_loadPictureButton_clicked();

        bool ok=hide.hideString2BMP(ui->lineEdit->text().toLatin1().data());
        hide.save();
        if(ok)
        {
            ui->statusBar->showMessage(QString::fromLocal8Bit("ͼƬ��д�ɹ���",7*1000));
            ui->lineEdit->clear();
        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("��Ϣδ�ɹ�д�룡"));
        }
    }
}


//β������
void MainWindow::on_fileTarbutton_clicked()
{
    ui->textEdit->clear();
    BMPHide hide;

    //��ȡͼƬ
    bool isBMP=hide.setBmpFileName(this->fileName.toLatin1().data());
    if(isBMP)
    {
        ui->statusBar->showMessage(QString::fromLocal8Bit("ͼƬ��ȡ�ɹ���",7*1000));
    }
    else
    {
        QMessageBox::information(this, QString::fromLocal8Bit("��ʾ:"),QString::fromLocal8Bit("ͼƬ��ȡ����,����������..."));
        return;
    }

    //������д��ʵ��
    if(ui->checkBox->isChecked())   //����
    {
        ui->lineEdit->clear();
        hide.hideString3BMP1();
        QString text=(QString::fromLocal8Bit("###ͼƬ��Ϣ����...###"))+"\n"
                +(QString::fromLocal8Bit("ͼƬ��ȣ�"))+QString::number(hide.getBmpWidth())+"\n"
                +(QString::fromLocal8Bit("ͼƬ�߶ȣ�"))+QString::number(hide.getBmpHeight())+"\n"
                +(QString::fromLocal8Bit("ͼƬλ����"))+QString::number(hide.getBmpBitCount())+"\n"
                +(QString::fromLocal8Bit("���������"))+hide.myinfo;
        ui->textEdit->setText(text);
        ui->statusBar->showMessage(QString::fromLocal8Bit("ͼƬ�����ɹ���",7*1000));
    }
    else    //��д
    {
        if(this->fileName.isEmpty())
            this->on_loadPictureButton_clicked();

        bool ok=hide.hideString3BMP(this->fileName.toLatin1().data(),ui->lineEdit->text().toLatin1().data());//β��׷��
        hide.save();
        if(ok)
        {
            ui->statusBar->showMessage(QString::fromLocal8Bit("ͼƬ��д�ɹ���",7*1000));
            ui->lineEdit->clear();
        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("��Ϣδ�ɹ�д�룡"));
        }
    }
}
