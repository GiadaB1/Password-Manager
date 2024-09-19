#ifndef RECOVERPSWWINDOW_H
#define RECOVERPSWWINDOW_H

#include <QApplication>
#include <QString>
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
#include <iostream>
#include <QXmlStreamReader>

#include "XmlUtils.h"
#include "ClickableText.h"
#include "LoginWindow.h"

class RecoverPswWindow : public QWidget
{
    Q_OBJECT
public:
    RecoverPswWindow(QWidget *parent = nullptr, QFile *credFile_in = nullptr, QFile *infoFile_in = nullptr);
    ~RecoverPswWindow();
private slots:
    int answer_check(QString);

private:
    QFile *credentialsStore;
    QFile *dataFile;
    QString question;

    QStackedLayout *recover_psw_layout = new QStackedLayout(this);

    QWidget *username_page = new QWidget();
    QWidget *answer_page = new QWidget();
    QWidget *password_page = new QWidget();

    QLineEdit *textField_usr = new QLineEdit();
    QLineEdit *textField_answer = new QLineEdit();
    QLineEdit *textField_psw = new QLineEdit();
    QLineEdit *textField_confirm_psw = new QLineEdit();

    QLabel *empty_label = new QLabel();

    QVBoxLayout *username_layout = new QVBoxLayout(username_page);
    QVBoxLayout *answer_layout = new QVBoxLayout(answer_page);
    QVBoxLayout *password_layout = new QVBoxLayout(password_page);

    QFormLayout *username_form = new QFormLayout();
    QFormLayout *password_form = new QFormLayout();
    QFormLayout *answer_form = new QFormLayout();

    QFont font_titles = QFont("Anton", 25);

    QLabel *username_title = new QLabel("Please enter your username:");
    QPropertyAnimation *username_animation = new QPropertyAnimation(username_title, "geometry");
    QHBoxLayout *continue_layout_username = new QHBoxLayout();
    QSpacerItem *push_all_down = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *continue_spacer_y = new QSpacerItem(20, 62, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *push_continue_up = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QSpacerItem *push_error_up = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QPushButton *continue_btn_username = new QPushButton("Continue");
    QLabel *empty_label_usr = new QLabel();
    QLabel *error_empty_usr = new QLabel("Please choose a username");
    QLabel *not_existing_usr = new QLabel("Account not found");
    QStackedLayout *error_layout_usr = new QStackedLayout();

    QLabel *answer_title = new QLabel("Answer the security question:");
    QFont question_font = QFont("Anton", 11, QFont::Cursive);
    QSpacerItem *answer_spacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QPropertyAnimation *answer_animation = new QPropertyAnimation(answer_title, "geometry");
    QStackedLayout *error_answer_layout = new QStackedLayout();
    QLabel *wrong_answer = new QLabel("Wrong answer");
    QLabel *error_empty_ans = new QLabel("Please answer the security question");
    QLabel *empty_label_ans = new QLabel();
    QSpacerItem *error_answer_spacer = new QSpacerItem(100, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);
    QHBoxLayout *continue_layout_answer = new QHBoxLayout();
    QPushButton *continue_btn_answer = new QPushButton("Continue");

    ClickableText *back_to_login = new ClickableText("Back to Login", this);

    QLabel *password_title = new QLabel("Choose a valid password:");
    QPropertyAnimation *password_animation = new QPropertyAnimation(password_title, "geometry");
    QHBoxLayout *change_btn_layout_password = new QHBoxLayout();
    QTextEdit *explanation_psw = new QTextEdit();
    QHBoxLayout *passwordForm_layout = new QHBoxLayout();
    QFont psw_boundaries = QFont("Anton", 8);
    QHBoxLayout *error_psw_layout = new QHBoxLayout();
    QLabel *empty_label_psw = new QLabel();
    QLabel *incorrect_psw = new QLabel("Passwords don't match or don't meet the requirements");
    QPushButton *change_psw_button = new QPushButton("Change Password");
    QStackedLayout *error_password_layout = new QStackedLayout();

    bool find_account();
};

#endif