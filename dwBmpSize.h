#ifndef DWBMPSIZE_H
#define DWBMPSIZE_H

#endif // DWBMPSIZE_H
#include<QString>
#include <string>
#include <Windows.h>
#include<stdio.h>
using namespace std;

class BMPHide
{
public:
    BMPHide();
    ~BMPHide();

    bool setBmpFileName(char*);	//����Bmp�ļ���

    int getBmpWidth();	//��ȡ���
    int getBmpHeight();	//��ȡ�߶�
    int getBmpBitCount();	//��ȡBit����
    bool save();    //����������Ϣ
    char *info;
    QString myinfo;

    //�ļ�ͷ���������
    bool headhideBMP();
    bool headhideBMP1();

    //���������������
    bool hideString2BMP(char* szStr2Hide/*=NULL*/);	//����String��BMP�ļ���
    void showStringInBmp(char* szBmpFIleName=NULL);	//չʾ

    //�ļ�β��Ϣ���������
    bool hideString3BMP(char* szStr3Hide,char* sz);
    bool hideString3BMP1();
private:
    DWORD dwBmpSize;	//ͼƬ�ļ���С
    string sBmpFileName;
    LPBYTE pBuf;	//���ڴ��ͼƬ��Ϣ���ڴ�

    BITMAPFILEHEADER* m_fileHdr;
    BITMAPINFOHEADER* m_infoHdr;
};
