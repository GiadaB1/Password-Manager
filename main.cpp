#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <iostream>
#include <QApplication>
#include "LoginWindow.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <QXmlStreamWriter>
#include "SignUpWindow.h"
#include "XmlUtils.h"
QFile *createXmlFile(QString);
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile *dataFile;
    QFile *credentialsStore;
    dataFile = createXmlFile("data.xml");
    credentialsStore = createXmlFile("credentials_store.xml");
    LoginWindow window(nullptr, dataFile, credentialsStore);

    window.show();

    return app.exec();
}

QFile *createXmlFile(QString filename)
{
    QFile *file = new QFile(filename);
    bool already_existed = file->exists();
    if (file->open(QFile::ReadWrite))
    {
        if (!already_existed)
        {
            QXmlStreamWriter xmlWriter(file);
            xmlWriter.setAutoFormatting(true);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement(tag::ROOT);
            xmlWriter.writeStartElement(tag::ACCOUNT);
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
            xmlWriter.writeEndDocument();
        }
        file->close();
        std::cout << "Succeeded" << std::endl;
    }
    else
        std::cout << "Error opening file" << std::endl;
    return file;
}
