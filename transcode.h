#ifndef TRANSCODE_H
#define TRANSCODE_H
#include <QByteArray>

#define g_transfrom TransCode::instance()


class TransCode
{
public:
    TransCode();
    static TransCode& instance();

    void readFile(QString filename);
    void coverGBKtoUTF8(QString filename);
    void coverUTF8toGBK(QString filename);
    QString ReadFromGBK();
    QString ReadFromUTF8();

    bool isNeedBackCopy;

private:
    QByteArray m_contentBYTE;

};

#endif // TRANSCODE_H
