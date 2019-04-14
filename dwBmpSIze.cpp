#include "dwBmpSize.h"
#include<QDebug>
#include<fstream>
BMPHide::BMPHide()
{
    sBmpFileName = "";
    pBuf = 0;
    dwBmpSize = 0;
}

BMPHide::~BMPHide()
{

}

//设置文件名
bool BMPHide::setBmpFileName(char* szFileName)
{
    this->sBmpFileName = szFileName;
    if (pBuf)	//如果已经生成就释放掉
    {
        delete[]pBuf;
    }

    HANDLE hfile = CreateFileA(szFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    if (hfile == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    //和struct BITMAPFILEHEADER bmfh里面的 bfSize的大小应该是一样的。
    dwBmpSize = GetFileSize(hfile, 0);	//获取文件的大小
    pBuf = new byte[dwBmpSize];
    DWORD dwRead = 0;
    ReadFile(hfile, pBuf, dwBmpSize, &dwRead, 0);
    if (dwRead != dwBmpSize)
    {
        delete[]pBuf;
        pBuf = 0;
        return false;
    }
    CloseHandle(hfile);
    m_fileHdr = (BITMAPFILEHEADER*)pBuf;
    m_infoHdr = (BITMAPINFOHEADER*)(pBuf + sizeof(BITMAPFILEHEADER));
    return true;	//成功话就是文件的内容读取到pBuf里面
}

int BMPHide::getBmpWidth()
{
    return m_infoHdr->biWidth;
}

int BMPHide::getBmpHeight()
{
    return m_infoHdr->biHeight;
}

int BMPHide::getBmpBitCount()
{
    return m_infoHdr->biBitCount;
}

bool BMPHide::save()
{
    string sDstFileName = sBmpFileName + ".hide.bmp";
    HANDLE hfile = CreateFileA(sDstFileName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS, 0, 0);
    if (hfile == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwWritten = 0;
    WriteFile(hfile, pBuf, dwBmpSize, &dwWritten, 0);
    if (dwBmpSize != dwWritten)
    {
        return false;
    }
    CloseHandle(hfile);
    return true;
}

//头文件隐写“hell”
bool BMPHide::headhideBMP()
{
    m_fileHdr->bfReserved1=25960;
    m_fileHdr->bfReserved2=27756;
    return true;
}

//判断头文件有无隐写
bool BMPHide::headhideBMP1()
{
    if(m_fileHdr->bfReserved1!=0|m_fileHdr->bfReserved2!=0
        |m_infoHdr->biSizeImage+54!=m_fileHdr->bfSize)
    {
        this->myinfo=QString::fromLocal8Bit("图像头文件冗余有隐写");
    }
    else
        this->myinfo=QString::fromLocal8Bit("图像头文件冗余无隐写");
    return true;
}

//隐藏一个字符串到图片中，把字符串拆成字节，写入每个像素的alpha通道中
bool BMPHide::hideString2BMP(char* szStr2Hide)
{
    LPBYTE pAlpha = pBuf + m_fileHdr->bfOffBits + 3;	//第一个像素的通道位置
    int nHide;	//成功隐藏的字节数

    //每次循环写入一个字节，吸入alpha通道
    //(pAlpha - pBuf) < m_fileHdr->bfSize这个是判断字符串是太大，图片不能隐藏
    for (nHide = 0; (pAlpha - pBuf) < m_fileHdr->bfSize && szStr2Hide[nHide] != 0; nHide++, pAlpha += 4)
    {
        *pAlpha = szStr2Hide[nHide];	//写入一个字节
    }
    return true;
}

//将隐藏在数据区的信息显示出来
void BMPHide::showStringInBmp(char* szBmpFIleName/*=NULL*/)
{
    string sDstFileName="";
    if (szBmpFIleName == 0)
    {
        sDstFileName = sBmpFileName + ".hide.bmp";
    }
    else
        sDstFileName = szBmpFIleName;

    HANDLE hfile = CreateFileA(sDstFileName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING, 0, 0);
    if (hfile == INVALID_HANDLE_VALUE)
    {
        this->info="no hide information";  //如果里面没有隐藏信息，则返回“no hide information”
        qDebug()<<"no hide information";
        return;
    }
    DWORD dwSize = GetFileSize(hfile, 0);
    LPBYTE pBuf1 = new byte[dwSize];

    DWORD dwRead = 0;

    ReadFile(hfile, pBuf1, dwSize, &dwRead, 0);
    CloseHandle(hfile);

    //文件内容读取到pBuf1中
    BITMAPFILEHEADER *pHdr = (BITMAPFILEHEADER *)pBuf1;
    LPBYTE pStr = pBuf1 + pHdr->bfOffBits + 3;
    char szTmp[1280];
    RtlZeroMemory(szTmp, 1280);
    for (int i = 0; i < 1280; i++)
    {
        if (*pStr == 0 || *pStr == 0xFF)
        {
            break;
        }
        szTmp[i] = *pStr;
        pStr += 4;
    }

    this->info=szTmp;  //提取出分析到的信息
    delete[]pBuf1;
}

//尾部添加数据
bool BMPHide::hideString3BMP(char* szStr3Hide,char*sz)
{
    ofstream of(szStr3Hide,ios::app|ios::binary);//以二进制尾部追加方式打开
    of<<sz;//添加数据
    of.close();
    return true;
}

//判断尾部有无数据
bool BMPHide::hideString3BMP1()
{
    long int a=0;
    a=m_infoHdr->biSizeImage+54;//图片数据区+头文件的大小
    HANDLE hfile = CreateFileA("12_2.bmp", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ
        | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    if(hfile!=INVALID_HANDLE_VALUE)
    {
        int size=GetFileSize(hfile,NULL);//获取图片隐写后的大小
        if(a<size)
        {
            this->myinfo=QString::fromLocal8Bit("尾部有隐藏信息");
        }
        else
        {
            this->myinfo=QString::fromLocal8Bit("尾部不含有隐藏信息");
        }
        CloseHandle(hfile);
    }
    else
    {
        this->myinfo="INVALID_HANDLE_VALUE";
    }
    return true;
}
