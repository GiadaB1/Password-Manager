#include "Utils.h"
#include <QTextStream>
int delete_root(QFile *file)
{
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    QString content;
    QTextStream in(file);
    content = in.readAll();
    file->close();

    content.remove("</" + tag::ROOT + ">");

    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        return 1;

    QTextStream out(file);
    out << content;

    file->close();
    return 0;
}

int get_in_xml(unsigned char *res, size_t res_dim, const QString tag, QFile *file)
{
    int found = 0;
    if (file->open(QIODevice::ReadOnly | QIODevice::Text))
    {

        QXmlStreamReader xmlReader(file);

        while (!xmlReader.atEnd() && !xmlReader.hasError() && !found)
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();

            if (token == QXmlStreamReader::StartElement && xmlReader.name() == tag)
            {
                QByteArray nonceData = QByteArray::fromBase64(xmlReader.readElementText().toUtf8());
                memcpy(res, nonceData.constData(), res_dim);
                found = 1;
            }
        }
        file->close();
    }
    return found;
}