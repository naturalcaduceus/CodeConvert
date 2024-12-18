#include "transcode.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

TransCode::TransCode()
{
    isNeedBackCopy = false;
}

//单例
TransCode& TransCode::instance()
{
    static TransCode mgr;
    return mgr;
}

void TransCode::coverGBKtoUTF8(QString filename)
{
    QFile fileWiter(filename);
    if(isNeedBackCopy) QFile::copy(filename,QString(filename+".coverbak"));//备份功能-cq20241218

    if(!fileWiter.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)){
        //文件打开失败
        return;
    }
    QTextStream out(&fileWiter);//fix bug -cq20241219
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    out.setAutoDetectUnicode(true);

    out<<ReadFromGBK()<<endl;

    fileWiter.close();
}


void TransCode::coverUTF8toGBK(QString filename)
{
    QFile fileWiter(filename);
    if(isNeedBackCopy) QFile::copy(filename,QString(filename+".coverbak"));//备份功能-cq20241218

    if(!fileWiter.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)){
        //文件打开失败
        return;
    }
    QTextStream out(&fileWiter);//fix bug -cq20241219
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    out.setAutoDetectUnicode(true);

    out<<ReadFromUTF8()<<endl;

    fileWiter.close();
}



void TransCode::readFile(QString filename)
{
    m_contentBYTE.clear();
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    //逐行读取
    while(!file.atEnd()){
        m_contentBYTE += file.readLine();
    }
}


QString TransCode::ReadFromGBK()
{
    QTextStream in(m_contentBYTE);
    in.setCodec(QTextCodec::codecForName("GBK"));
    in.setAutoDetectUnicode(true);
    return in.readAll();
}

QString TransCode::ReadFromUTF8()
{
    QTextStream in(m_contentBYTE);
    in.setCodec(QTextCodec::codecForName("UTF-8"));
    in.setAutoDetectUnicode(true);
    return in.readAll();
}
