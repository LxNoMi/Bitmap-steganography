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

    bool setBmpFileName(char*);	//设置Bmp文件名

    int getBmpWidth();	//获取宽度
    int getBmpHeight();	//获取高度
    int getBmpBitCount();	//获取Bit总数
    bool save();    //保存隐藏信息
    char *info;
    QString myinfo;

    //文件头隐藏与分析
    bool headhideBMP();
    bool headhideBMP1();

    //数据区隐藏与分析
    bool hideString2BMP(char* szStr2Hide/*=NULL*/);	//隐藏String到BMP文件中
    void showStringInBmp(char* szBmpFIleName=NULL);	//展示

    //文件尾信息隐藏与分析
    bool hideString3BMP(char* szStr3Hide,char* sz);
    bool hideString3BMP1();
private:
    DWORD dwBmpSize;	//图片文件大小
    string sBmpFileName;
    LPBYTE pBuf;	//用于存放图片信息的内存

    BITMAPFILEHEADER* m_fileHdr;
    BITMAPINFOHEADER* m_infoHdr;
};
