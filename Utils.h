#ifndef UTILS_H
#define UTILS_H
#include <QFile>
#include <QXmlStreamReader>
#include "XmlUtils.h"
int delete_root(QFile *);
struct credentials
{
    QString accountName;
    QString username;
    QString password;
    credentials(const QString &accName, const QString &user, const QString &pass) : accountName(accName), username(user), password(pass) {};
};

int get_in_xml(unsigned char *, size_t, const QString, QFile *);
#endif