#include "transcode.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

TransCode::TransCode()
{
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

    if(!fileWiter.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)){
        //文件打开失败
        return;
    }
    QTextStream out(&filename);
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    out.setAutoDetectUnicode(true);

    out<<ReadFromGBK()<<endl;

    fileWiter.close();
}


void TransCode::coverUTF8toGBK(QString filename)
{
    QFile fileWiter(filename);

    if(!fileWiter.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)){
        //文件打开失败
        return;
    }
    QTextStream out(&filename);
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
