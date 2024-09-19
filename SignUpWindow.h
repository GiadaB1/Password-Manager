#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QApplication>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QStackedLayout>
#include <QFormLayout>
#include <QFont>
#include <QPropertyAnimation>
#include <QLineEdit>
#include <Qstring>
#include <QMessageBox>
#include <QTimer>
#include <QComboBox>
#include "ClickableText.h"
#include "LoginWindow.h"
#include "SecFunctions.h"
#include <sodium.h>
#include "Utils.h"
#include <QtXml/QDomDocument>
#include <QTextStream>
class SignUpWindow : public QWidget
{
    Q_OBJECT

public:
    SignUpWindow(QWidget *parent = nullptr, QFile *in_file = nullptr, QFile *info_file = nullptr);
    ~SignUpWindow();
private slots:
    bool CheckPassword(QString password, QString confirmPassword);

private:
    QStackedLayout *signup_layout = new QStackedLayout(this);

    QWidget *username_page = new QWidget(this);
    QWidget *password_page = new QWidget(this);
    QWidget *securityQuestions_page = new QWidget(this);

    QLineEdit *textField_usr = new QLineEdit();
    QLineEdit *textField_psw = new QLineEdit();
    QLineEdit *textField_confirm_psw = new QLineEdit();

    QLabel *empty_label = new QLabel();

    QVBoxLayout *username_layout = new QVBoxLayout(username_page);
    QVBoxLayout *password_layout = new QVBoxLayout(password_page);
    QVBoxLayout *securityQuestions_layout = new QVBoxLayout(securityQuestions_page);
    QFormLayout *username_form = new QFormLayout();
    QFormLayout *password_form = new QFormLayout();

    QFont SignUp_titles = QFont("Anton", 25);

    QLabel *username_title = new QLabel("Choose a username:");
    QPropertyAnimation *username_animation = new QPropertyAnimation(username_title, "geometry");
    QHBoxLayout *continue_layout_username = new QHBoxLayout();
    QSpacerItem *push_all_down = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *continue_spacer_y = new QSpacerItem(20, 62, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *push_continue_up = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *push_error_up = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QPushButton *continue_btn_username = new QPushButton("Continue");
    QLabel *empty_label_usr = new QLabel();
    QLabel *error_empty_usr = new QLabel("Please choose a username");
    QLabel *existing_usr = new QLabel("This username already exists. Please choose another one.");
    QStackedLayout *error_layout = new QStackedLayout();

    QLabel *password_title = new QLabel("Choose a valid password:");
    QPropertyAnimation *password_animation = new QPropertyAnimation(password_title, "geometry");
    QPushButton *continue_btn_password = new QPushButton("Continue");
    QHBoxLayout *continue_layout_password = new QHBoxLayout();
    QTextEdit *explanation_psw = new QTextEdit();
    QHBoxLayout *passwordForm_layout = new QHBoxLayout();
    QFont psw_boundaries = QFont("Anton", 8);
    QHBoxLayout *error_psw_layout = new QHBoxLayout();
    QLabel *empty_label_psw = new QLabel();
    QLabel *incorrect_psw = new QLabel("Passwords don't match or don't meet the requirements");
    QStackedLayout *error_password_layout = new QStackedLayout();

    QLabel *securityQuestions_title = new QLabel("Choose a security question:");
    QFont expl_font = QFont("Anton", 11, QFont::Cursive);
    QSpacerItem *securityQuestions_spacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QLabel *securityQuestions_expl = new QLabel("Almost there...the security question will be asked if you forget your password.");
    QPropertyAnimation *securityQuestions_animation = new QPropertyAnimation(securityQuestions_title, "geometry");
    QHBoxLayout *dropdown_menu_layout = new QHBoxLayout();
    QComboBox *dropdown_menu = new QComboBox();
    QLineEdit *textField_answer = new QLineEdit();
    QStackedLayout *error_securityQuestions_layout = new QStackedLayout();
    QSpacerItem *error_securityQuestions_spacer = new QSpacerItem(100, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QLabel *error_securityQuestions = new QLabel("Please choose a security question and answer");
    QPushButton *signUp_button = new QPushButton("Sign Up");
    ClickableText *back_to_login = new ClickableText("Back to Login", this);

    QFile *dataFile;
    QFile *credentialsStore;

    void fill_dropdown_menu(QComboBox *);
    void createAccount(QString, QString, int, QString);
    int newAccount(QString, QString, QString, int, QString, QString, QString, QString);
    int existing_usr_check(QString);
};

#endif