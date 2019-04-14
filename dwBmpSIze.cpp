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

//�����ļ���
bool BMPHide::setBmpFileName(char* szFileName)
{
    this->sBmpFileName = szFileName;
    if (pBuf)	//����Ѿ����ɾ��ͷŵ�
    {
        delete[]pBuf;
    }

    HANDLE hfile = CreateFileA(szFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    if (hfile == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    //��struct BITMAPFILEHEADER bmfh����� bfSize�Ĵ�СӦ����һ���ġ�
    dwBmpSize = GetFileSize(hfile, 0);	//��ȡ�ļ��Ĵ�С
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
    return true;	//�ɹ��������ļ������ݶ�ȡ��pBuf����
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

//ͷ�ļ���д��hell��
bool BMPHide::headhideBMP()
{
    m_fileHdr->bfReserved1=25960;
    m_fileHdr->bfReserved2=27756;
    return true;
}

//�ж�ͷ�ļ�������д
bool BMPHide::headhideBMP1()
{
    if(m_fileHdr->bfReserved1!=0|m_fileHdr->bfReserved2!=0
        |m_infoHdr->biSizeImage+54!=m_fileHdr->bfSize)
    {
        this->myinfo=QString::fromLocal8Bit("ͼ��ͷ�ļ���������д");
    }
    else
        this->myinfo=QString::fromLocal8Bit("ͼ��ͷ�ļ���������д");
    return true;
}

//����һ���ַ�����ͼƬ�У����ַ�������ֽڣ�д��ÿ�����ص�alphaͨ����
bool BMPHide::hideString2BMP(char* szStr2Hide)
{
    LPBYTE pAlpha = pBuf + m_fileHdr->bfOffBits + 3;	//��һ�����ص�ͨ��λ��
    int nHide;	//�ɹ����ص��ֽ���

    //ÿ��ѭ��д��һ���ֽڣ�����alphaͨ��
    //(pAlpha - pBuf) < m_fileHdr->bfSize������ж��ַ�����̫��ͼƬ��������
    for (nHide = 0; (pAlpha - pBuf) < m_fileHdr->bfSize && szStr2Hide[nHide] != 0; nHide++, pAlpha += 4)
    {
        *pAlpha = szStr2Hide[nHide];	//д��һ���ֽ�
    }
    return true;
}

//������������������Ϣ��ʾ����
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
        this->info="no hide information";  //�������û��������Ϣ���򷵻ء�no hide information��
        qDebug()<<"no hide information";
        return;
    }
    DWORD dwSize = GetFileSize(hfile, 0);
    LPBYTE pBuf1 = new byte[dwSize];

    DWORD dwRead = 0;

    ReadFile(hfile, pBuf1, dwSize, &dwRead, 0);
    CloseHandle(hfile);

    //�ļ����ݶ�ȡ��pBuf1��
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

    this->info=szTmp;  //��ȡ������������Ϣ
    delete[]pBuf1;
}

//β���������
bool BMPHide::hideString3BMP(char* szStr3Hide,char*sz)
{
    ofstream of(szStr3Hide,ios::app|ios::binary);//�Զ�����β��׷�ӷ�ʽ��
    of<<sz;//�������
    of.close();
    return true;
}

//�ж�β����������
bool BMPHide::hideString3BMP1()
{
    long int a=0;
    a=m_infoHdr->biSizeImage+54;//ͼƬ������+ͷ�ļ��Ĵ�С
    HANDLE hfile = CreateFileA("12_2.bmp", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ
        | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    if(hfile!=INVALID_HANDLE_VALUE)
    {
        int size=GetFileSize(hfile,NULL);//��ȡͼƬ��д��Ĵ�С
        if(a<size)
        {
            this->myinfo=QString::fromLocal8Bit("β����������Ϣ");
        }
        else
        {
            this->myinfo=QString::fromLocal8Bit("β��������������Ϣ");
        }
        CloseHandle(hfile);
    }
    else
    {
        this->myinfo="INVALID_HANDLE_VALUE";
    }
    return true;
}
