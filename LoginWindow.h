

#ifndef LOG_WINDOW_H
#define LOG_WINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QList>
#include <iostream>
#include <QApplication>
#include <sodium.h>
#include "SecFunctions.h"
#include "ClickableText.h"
#include "SignUpWindow.h"
#include "RecoverPswWindow.h"
#include "AccountWindow.h"
#include "XmlUtils.h"

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr, QFile *in_file = nullptr, QFile *info_file = nullptr);
    ~LoginWindow();

private slots:
    void LogIn_clicked();
    void signUp_clicked();
    void forgotPsw_clicked();

private:
    QWidget *LogIn_container = new QWidget(this);
    QGridLayout *grid_layout = new QGridLayout(LogIn_container);
    QVBoxLayout *vbox_layout = new QVBoxLayout(this);
    QPushButton *LogIn_button = new QPushButton("Log In");
    QLabel *username_label = new QLabel("Username:");
    QLineEdit *textField_usr = new QLineEdit();
    QLabel *password_label = new QLabel("Password:");
    QLineEdit *textField_psw = new QLineEdit();
    QHBoxLayout *forgot_psw_layout = new QHBoxLayout();
    QLabel *forgot_psw = new QLabel("Forgot your password?");
    ClickableText *forgot_psw_click = new ClickableText("Reset Password", this);
    QHBoxLayout *sign_up_layout = new QHBoxLayout();
    QLabel *sign_up = new QLabel("Don't have an account?");
    ClickableText *sign_up_click = new ClickableText("Sign Up", this);

    QFile *dataFile;
    QFile *credentialsStore;
};

#endif