#include "RecoverPswWindow.h"
RecoverPswWindow::RecoverPswWindow(QWidget *parent, QFile *credFile_in, QFile *infoFile_in) : QWidget(parent), credentialsStore(credFile_in), dataFile(infoFile_in)
{

    setWindowTitle("Recover Password");
    this->setFixedSize(650, 400);

    recover_psw_layout->addWidget(username_page);
    recover_psw_layout->addWidget(answer_page);
    recover_psw_layout->addWidget(password_page);

    back_to_login->adjustSize();

    // Username page
    username_title->setAlignment(Qt::AlignCenter);
    username_title->setFont(font_titles);
    username_title->adjustSize();
    int height = username_title->height() + 22;
    username_layout->addSpacerItem(push_all_down);
    username_animation->setStartValue(QRect(-600, 63, 650, height));
    username_animation->setEndValue(QRect(0, 63, 650, height));
    username_animation->setDuration(300);
    username_animation->start();

    username_layout->addWidget(username_title);
    username_layout->addItem(continue_spacer_y);

    textField_usr->setFixedSize(200, 30);

    username_form->addRow("Username:", textField_usr);
    username_form->setContentsMargins(150, 0, 0, 0);
    username_layout->addLayout(username_form);

    continue_btn_username->setFixedSize(100, 30);
    continue_layout_username->addWidget(continue_btn_username, Qt::AlignCenter);

    empty_label_usr->setFixedHeight(16);
    error_layout_usr->addWidget(empty_label_usr);
    not_existing_usr->setFont(psw_boundaries);
    not_existing_usr->setStyleSheet("color: red;");
    not_existing_usr->adjustSize();
    error_empty_usr->setFont(psw_boundaries);
    error_empty_usr->setStyleSheet("color: red;");
    error_empty_usr->adjustSize();
    error_layout_usr->addWidget(error_empty_usr);
    error_empty_usr->setAlignment(Qt::AlignCenter);
    error_layout_usr->addWidget(not_existing_usr);
    not_existing_usr->setAlignment(Qt::AlignCenter);
    error_layout_usr->setCurrentIndex(0);
    username_layout->addLayout(error_layout_usr);
    username_layout->addSpacerItem(push_error_up);
    username_layout->addLayout(continue_layout_username);
    username_layout->addSpacerItem(push_continue_up);
    username_layout->addWidget(back_to_login);
    connect(continue_btn_username, &QPushButton::clicked, [this]()
            {
                if (textField_usr->text().isEmpty())
                {
                    error_layout_usr->setCurrentIndex(1);
                    QTimer::singleShot(3000, [this]() { error_layout_usr->setCurrentIndex(0); });
                }
                else
                    if (!find_account())
                    {
                        error_layout_usr->setCurrentIndex(2);
                        QTimer::singleShot(3000, [this]() { error_layout_usr->setCurrentIndex(0); });
                    }
                    else
                    {
                        recover_psw_layout->setCurrentIndex(1);
                        push_continue_up->changeSize(10, 20);
                        push_all_down->changeSize(20, 30);
                        answer_animation->start();
                        
                        answer_layout->addWidget(back_to_login);
                    } });

    // Answer page
    answer_title->setAlignment(Qt::AlignCenter);
    answer_title->setFont(font_titles);
    answer_title->adjustSize();
    answer_layout->addSpacerItem(push_all_down);
    answer_animation->setStartValue(QRect(-600, 30, 650, height));
    answer_animation->setEndValue(QRect(0, 30, 650, height));
    answer_animation->setDuration(300);

    answer_layout->addWidget(answer_title);
    answer_layout->addItem(continue_spacer_y);

    textField_answer->setFixedSize(200, 30);

    answer_form->addRow("Answer:", textField_answer);
    answer_form->setContentsMargins(150, 0, 0, 0);
    answer_layout->addLayout(answer_form);

    empty_label_ans->setFixedHeight(16);
    error_answer_layout->addWidget(empty_label_ans);
    wrong_answer->setFont(psw_boundaries);
    wrong_answer->setStyleSheet("color: red;");
    wrong_answer->adjustSize();
    error_empty_ans->setFont(psw_boundaries);
    error_empty_ans->setStyleSheet("color: red;");
    error_empty_ans->adjustSize();
    error_answer_layout->addWidget(error_empty_ans);
    error_empty_ans->setAlignment(Qt::AlignCenter);
    error_answer_layout->addWidget(wrong_answer);
    wrong_answer->setAlignment(Qt::AlignCenter);
    error_answer_layout->setCurrentIndex(0);
    continue_btn_answer->setFixedSize(100, 30);
    answer_layout->addWidget(continue_btn_answer, Qt::AlignCenter);
    answer_layout->addLayout(error_answer_layout);
    answer_layout->addSpacerItem(push_error_up);
    continue_layout_answer->addWidget(continue_btn_answer, Qt::AlignCenter);
    answer_layout->addLayout(continue_layout_answer);
    answer_layout->addSpacerItem(push_continue_up);

    connect(continue_btn_answer, &QPushButton::clicked, [this]()
            {
        if (textField_answer->text().isEmpty())
        {
            error_answer_layout->setCurrentIndex(1);
            QTimer::singleShot(3000, [this]() { error_answer_layout->setCurrentIndex(0); });
        }
        else
        {
            if (answer_check(textField_answer->text()))
            {
                recover_psw_layout->setCurrentIndex(2);
                push_continue_up->changeSize(10, 20);
                push_all_down->changeSize(20, 30);
                password_animation->start();
                password_layout->addWidget(back_to_login);
            }
            else
            {
                error_answer_layout->setCurrentIndex(2);
                QTimer::singleShot(3000, [this]() { error_answer_layout->setCurrentIndex(0); });
            }
        } });

    // Password page
    password_title->setAlignment(Qt::AlignCenter);
    password_title->setFont(font_titles);
    password_title->adjustSize();

    password_animation->setStartValue(QRect(-600, 30, 650, height));
    password_animation->setEndValue(QRect(0, 30, 650, height));
    password_animation->setDuration(300);

    password_layout->addSpacerItem(push_all_down);
    password_layout->addWidget(password_title);
    password_layout->addSpacerItem(continue_spacer_y);

    textField_psw->setFixedSize(200, 30);
    textField_psw->setEchoMode(QLineEdit::Password);
    textField_confirm_psw->setFixedSize(200, 30);
    textField_confirm_psw->setEchoMode(QLineEdit::Password);

    password_form->addRow("Password:", textField_psw);
    password_form->addRow("Confirm Password:", textField_confirm_psw);
    password_form->setContentsMargins(50, 0, 0, 0);
    passwordForm_layout->addLayout(password_form);
    psw_boundaries.setItalic(true);
    explanation_psw->setText("Password must contain at least:\n • 1 number \n • 1 uppercase letter \n • 1 lowercase letter \n • 1 special character(!?@#$%^&*) \n • 8 characters long");
    explanation_psw->adjustSize();
    explanation_psw->setReadOnly(true);
    explanation_psw->setStyleSheet("color: red");
    explanation_psw->setFont(psw_boundaries);
    explanation_psw->adjustSize();
    explanation_psw->setTextBackgroundColor(QColor(0, 0, 0, 0));
    passwordForm_layout->addWidget(explanation_psw);
    password_layout->addLayout(passwordForm_layout);

    incorrect_psw->setFont(psw_boundaries);
    incorrect_psw->setStyleSheet("color: red");
    incorrect_psw->adjustSize();

    error_psw_layout->addWidget(incorrect_psw, Qt::AlignCenter);
    password_layout->addLayout(error_psw_layout);
    empty_label_psw->setFixedHeight(16);
    error_password_layout->addWidget(empty_label_psw);
    error_password_layout->addWidget(incorrect_psw);
    incorrect_psw->setAlignment(Qt::AlignCenter);
    password_layout->addLayout(error_password_layout);

    change_psw_button->setFixedSize(150, 30);
    change_btn_layout_password->addWidget(change_psw_button, Qt::AlignCenter);
    password_layout->addLayout(change_btn_layout_password);
    password_layout->addSpacerItem(push_continue_up);
    error_password_layout->setCurrentIndex(0);
    connect(back_to_login, &ClickableText::clicked, [this]()
            {
        LoginWindow *login = new LoginWindow(nullptr, dataFile, credentialsStore);
        login->show();
        this->close(); });
}

RecoverPswWindow::~RecoverPswWindow()
{
    std::cout << "RecoverPswWindow deleted" << std::endl;
    delete username_page;
    delete answer_page;
    delete password_page;
    delete textField_usr;
    delete textField_answer;
    delete textField_psw;
    delete textField_confirm_psw;
    delete empty_label;
    delete username_form;
    delete password_form;
    delete answer_form;
    delete username_title;
    delete continue_layout_username;
    delete push_all_down;
    delete push_continue_up;
    delete continue_spacer_y;
    delete push_error_up;
    delete continue_btn_username;
    delete empty_label_usr;
    delete error_empty_usr;
    delete not_existing_usr;
    delete error_layout_usr;
    delete answer_title;
    delete answer_spacer;
    delete error_answer_layout;
    delete wrong_answer;
    delete error_empty_ans;
    delete empty_label_ans;
    delete error_answer_spacer;
    delete continue_layout_answer;
    delete continue_btn_answer;
    delete back_to_login;
    delete password_title;
    delete change_btn_layout_password;
    delete explanation_psw;
    delete passwordForm_layout;
    delete error_psw_layout;
    delete empty_label_psw;
    delete incorrect_psw;
    delete change_psw_button;
    delete error_password_layout;
}

bool RecoverPswWindow::find_account()
{
    int question_index = -1;
    QFile file("securityQuestions.txt");
    if (credentialsStore->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xmlReader(credentialsStore);
        while (!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if (token == QXmlStreamReader::StartElement)
                if (xmlReader.name() == tag::ACCOUNT && xmlReader.attributes().value(attribute::USERNAME) == textField_usr->text())
                    question_index = xmlReader.attributes().value(attribute::QUESTION_INDEX).toInt();
        }
        credentialsStore->close();
        if (file.open(QIODevice::ReadOnly | QIODevice::Text) and question_index >= 0)
        {
            QTextStream in(&file);
            for (int i = 0; i < question_index; i++)
                in.readLine();
            question = in.readLine();
            file.close();
            return true;
        }
        return false;
    }

    return false;
}

int RecoverPswWindow::answer_check(QString answer)
{
    bool found = false;

    unsigned char stored_salt[crypto_generichash_blake2b_SALTBYTES];
    unsigned char stored_hash[crypto_generichash_blake2b_BYTES];

    if (credentialsStore->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xmlReader(credentialsStore);
        while (!xmlReader.atEnd() && !xmlReader.hasError() && !found)
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if (token == QXmlStreamReader::StartElement)
                if (xmlReader.name() == tag::ACCOUNT && xmlReader.attributes().value(attribute::USERNAME) == textField_usr->text())
                {
                    while (!xmlReader.atEnd() && !xmlReader.hasError() && !found)
                    {
                        QXmlStreamReader::TokenType account_token = xmlReader.readNext();
                        if (account_token == QXmlStreamReader::StartElement && xmlReader.name() == tag::SALT_SEQ_ANSW)
                        {
                            QByteArray byteArray = QByteArray::fromBase64(xmlReader.readElementText().toUtf8());
                            memcpy(stored_salt, byteArray.data(), crypto_generichash_blake2b_SALTBYTES);
                        }
                        else if (account_token == QXmlStreamReader::StartElement && xmlReader.name() == tag::HASH_SEC_ANSW)
                        {
                            QByteArray hash_byte = QByteArray::fromBase64(xmlReader.readElementText().toUtf8());
                            memcpy(stored_hash, hash_byte.data(), crypto_generichash_blake2b_BYTES);
                            found = true;
                        }
                    }
                }
        }
        credentialsStore->close();
    }
    if (!found)
    {
        std::cout << "Account not found" << std::endl;
        return 0;
    }
    else
    {
        hash(&answer, stored_salt);
        QByteArray hash_ans_in = QByteArray::fromBase64(answer.toUtf8());
        return memcmp(stored_hash, hash_ans_in, crypto_generichash_blake2b_BYTES) == 0 ? 1 : 0;
    }
}
