#ifndef ACCOUNT_WINDOW_H
#define ACCOUNT_WINDOW_H

#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedLayout>
#include <QPropertyAnimation>
#include <QFile>
#include <QTextStream>
#include <QFormLayout>
#include <QTextEdit>
#include <QTimer>
#include <QTableView>
#include <iostream>
#include <QXmlStreamWriter>
#include <QStandardItemModel>
#include <QHeaderView>

#include "ClickableText.h"
#include "Utils.h"
#include "LoginWindow.h"

class AccountWindow : public QWidget
{
    Q_OBJECT

public:
    AccountWindow(QWidget *parent = nullptr, QFile *credFile_in = nullptr, QFile *infoFile_in = nullptr, QString username_in = nullptr, unsigned char *key_in = nullptr);
    ~AccountWindow();
private slots:
    void add_new_credentials();
    void update_table();
    QString new_creds_tostr();
signals:
    void isHidden();

private:
    QFile *credentialsStore;
    QFile *dataFile;
    QList<credentials> *credentialsList;
    QList<credentials> *newCredentials = new QList<credentials>();
    QString username;
    unsigned char *key = new unsigned char[crypto_aead_chacha20poly1305_IETF_KEYBYTES];

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    QSpacerItem *push_table_up = new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QFont font_titles = QFont("Anton", 25);
    QFont font_headers = QFont("Anton", 11);
    QLabel *welcome_text = new QLabel();
    QPropertyAnimation *animation = new QPropertyAnimation(welcome_text, "geometry");
    QTableView *credentialsTable = new QTableView();
    QStandardItemModel *data_model = new QStandardItemModel();
    QPushButton *add_credentials = new QPushButton("Add Credentials");
    QHBoxLayout *credentials_layout = new QHBoxLayout();
    QLineEdit *Account = new QLineEdit();
    QLineEdit *Username = new QLineEdit();
    QLineEdit *Password = new QLineEdit();
    ClickableText *back_to_login = new ClickableText("Back to Login");
};
#endif