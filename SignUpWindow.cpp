#include "SignUpWindow.h"
#include "XmlUtils.h"
#include <QXmlStreamWriter>
#include <filesystem>
#include <fstream>
SignUpWindow::SignUpWindow(QWidget *parent, QFile *in_file, QFile *info_file) : QWidget(parent), dataFile(in_file), credentialsStore(info_file)
{
    setWindowTitle("Sign Up");
    this->setFixedSize(650, 400);

    signup_layout->addWidget(username_page);
    signup_layout->addWidget(password_page);
    signup_layout->addWidget(securityQuestions_page);

    back_to_login->adjustSize();

    // Username page

    username_title->setAlignment(Qt::AlignCenter);
    username_title->setFont(SignUp_titles);
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

    empty_label_usr->setFixedHeight(16);
    error_layout->addWidget(empty_label_usr);
    existing_usr->setFont(psw_boundaries);
    existing_usr->setStyleSheet("color: red;");
    existing_usr->adjustSize();
    error_empty_usr->setFont(psw_boundaries);
    error_empty_usr->setStyleSheet("color: red;");
    error_empty_usr->adjustSize();
    error_layout->addWidget(error_empty_usr);
    error_empty_usr->setAlignment(Qt::AlignCenter);
    error_layout->addWidget(existing_usr);
    existing_usr->adjustSize();
    existing_usr->setAlignment(Qt::AlignCenter);
    error_layout->setCurrentIndex(0);
    username_layout->addLayout(error_layout);
    username_layout->addSpacerItem(push_error_up);
    username_layout->addLayout(continue_layout_username);
    username_layout->addSpacerItem(push_continue_up);
    username_layout->addWidget(back_to_login);
    connect(continue_btn_username, &QPushButton::clicked, [this]()
            {
                if (textField_usr->text().isEmpty())
                {
                    error_layout->setCurrentIndex(1);
                    QTimer::singleShot(3000, [this]() { error_layout->setCurrentIndex(0); });
                }
                else
                    if (existing_usr_check(textField_usr->text()))
                    {
                        error_layout->setCurrentIndex(2);
                        QTimer::singleShot(3000, [this]() { error_layout->setCurrentIndex(0); });
                    }
                    else
                    {
                        signup_layout->setCurrentIndex(1);
                        push_continue_up->changeSize(10, 20);
                        push_all_down->changeSize(20, 30);
                        password_animation->start();
                        password_layout->addWidget(back_to_login);
                    } });

    continue_layout_username->addWidget(continue_btn_username, Qt::AlignCenter);
    // Password page

    password_title->setAlignment(Qt::AlignCenter);
    password_title->setFont(SignUp_titles);
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

    // error_psw_layout->addItem(continue_spacer_y);
    error_psw_layout->addWidget(incorrect_psw, Qt::AlignCenter);
    password_layout->addLayout(error_psw_layout);
    empty_label_psw->setFixedHeight(16);
    error_password_layout->addWidget(empty_label_psw);
    error_password_layout->addWidget(incorrect_psw);
    incorrect_psw->setAlignment(Qt::AlignCenter);
    password_layout->addLayout(error_password_layout);
    // password_layout->addSpacerItem(push_error_up);
    continue_btn_password->setFixedSize(100, 30);
    continue_layout_password->addWidget(continue_btn_password);
    password_layout->addLayout(continue_layout_password);
    password_layout->addSpacerItem(push_continue_up);
    error_password_layout->setCurrentIndex(0);
    connect(continue_btn_password, &QPushButton::clicked, [this]()
            {
        if (SignUpWindow::CheckPassword(textField_psw->text(), textField_confirm_psw->text()))
        {
            signup_layout->setCurrentIndex(2);
            securityQuestions_animation->start();
            securityQuestions_layout->addWidget(back_to_login);
        }
        else
        {
            error_password_layout->setCurrentIndex(1);
            QTimer::singleShot(3000, [this](){error_password_layout->setCurrentIndex(0);});
        } });
    // Security questions page
    securityQuestions_title->setAlignment(Qt::AlignCenter);
    securityQuestions_title->setFont(SignUp_titles);
    securityQuestions_title->adjustSize();
    securityQuestions_animation->setStartValue(QRect(-600, 0, 650, height));
    securityQuestions_animation->setEndValue(QRect(0, 0, 650, height));
    securityQuestions_animation->setDuration(300);

    securityQuestions_layout->addWidget(securityQuestions_title);
    securityQuestions_layout->addSpacerItem(securityQuestions_spacer);
    securityQuestions_expl->setFont(expl_font);
    securityQuestions_expl->setAlignment(Qt::AlignCenter);
    securityQuestions_expl->adjustSize();
    securityQuestions_layout->addWidget(securityQuestions_expl);
    securityQuestions_layout->addSpacerItem(error_securityQuestions_spacer);
    fill_dropdown_menu(dropdown_menu);
    dropdown_menu->setMaxVisibleItems(6);
    dropdown_menu_layout->addWidget(dropdown_menu);
    textField_answer->setFixedSize(200, 30);
    textField_answer->setPlaceholderText("Answer");
    textField_answer->setStyleSheet("border: 1px solid black");
    dropdown_menu_layout->addWidget(textField_answer);
    securityQuestions_layout->addLayout(dropdown_menu_layout);

    error_securityQuestions->adjustSize();
    empty_label->setFixedHeight(16);
    error_securityQuestions_layout->addWidget(empty_label);
    error_securityQuestions->setFont(psw_boundaries);
    error_securityQuestions->setStyleSheet("color: red");
    error_securityQuestions_layout->addWidget(error_securityQuestions);
    error_securityQuestions->setAlignment(Qt::AlignCenter);

    error_securityQuestions_layout->setCurrentIndex(0);

    securityQuestions_layout->addLayout(error_securityQuestions_layout);
    signUp_button->setFixedSize(100, 30);
    signUp_button->adjustSize();
    securityQuestions_layout->addWidget(signUp_button);
    this->setLayout(signup_layout);
    connect(signUp_button, &QPushButton::clicked, [this]()
            {
        if (textField_answer->text() != NULL && dropdown_menu->currentIndex() != -1){
            createAccount(textField_usr->text(), textField_psw->text(), dropdown_menu->currentIndex(), textField_answer->text());
        }
        else
        {
            error_securityQuestions_layout->setCurrentIndex(1);
            QTimer::singleShot(3000, [this]()
            {
                error_securityQuestions_layout->setCurrentIndex(0);  // Nascondi il messaggio
                securityQuestions_layout->update();
                securityQuestions_layout->activate();
            });
        } });

    connect(back_to_login, &ClickableText::clicked, [this]()
            {
        LoginWindow *login = new LoginWindow(nullptr, dataFile, credentialsStore);
        login->show();
        this->close(); });
}

SignUpWindow::~SignUpWindow()
{
    delete push_continue_up;
    delete push_all_down;
    delete signup_layout;
    delete username_page;
    delete password_page;
    delete securityQuestions_page;
    delete textField_usr;
    delete textField_psw;
    delete textField_confirm_psw;
    delete username_form;
    delete password_form;
    delete username_title;
    delete continue_layout_username;
    delete continue_spacer_y;
    delete push_continue_up;
    delete push_error_up;
    delete empty_label_usr;
    delete error_empty_usr;
    delete existing_usr;
    delete error_layout;
    delete continue_btn_username;
    delete password_title;
    delete continue_btn_password;
    delete continue_layout_password;
    delete explanation_psw;
    delete passwordForm_layout;
    delete error_psw_layout;
    delete empty_label_psw;
    delete incorrect_psw;
    delete error_password_layout;
    delete securityQuestions_title;
    delete securityQuestions_spacer;
    delete securityQuestions_expl;
    delete dropdown_menu_layout;
    delete dropdown_menu;
    delete textField_answer;
    delete error_securityQuestions_layout;
    delete error_securityQuestions_spacer;
    delete error_securityQuestions;
    delete signUp_button;
    delete back_to_login;
}

bool SignUpWindow::CheckPassword(QString password, QString confirmPassword)
{
    if (password == confirmPassword)
    {
        if (password.length() >= 8 && password.contains(QRegExp("[0-9]")) && password.contains(QRegExp("[a-z]")) && password.contains(QRegExp("[A-Z]")) && password.contains(QRegExp("[!?@#$%^&*]")))
            return true;
        return false;
    }
    return false;
}

void SignUpWindow::fill_dropdown_menu(QComboBox *dropdown_menu)
{
    std::filesystem::path filepath = "securityQuestions.txt";
    std::fstream questions_file(filepath, std::ios::in);
    if (questions_file.is_open())
    {
        std::string line;
        while (std::getline(questions_file, line))
            dropdown_menu->addItem(QString::fromStdString(line));
        questions_file.close();
    }
}

void SignUpWindow::createAccount(QString username, QString password, int securityQuestion_index, QString answer)
{
    unsigned char *psw_salt = new unsigned char[crypto_generichash_blake2b_SALTBYTES];
    unsigned char *sec_answ_salt = new unsigned char[crypto_generichash_blake2b_SALTBYTES];
    unsigned char *key2_salt = new unsigned char[crypto_pwhash_SALTBYTES];
    unsigned char *key2 = new unsigned char[crypto_aead_chacha20poly1305_IETF_KEYBYTES];
    unsigned char *nonce_psw = new unsigned char[crypto_aead_chacha20poly1305_IETF_NPUBBYTES];

    gen_salt(psw_salt, crypto_generichash_blake2b_SALTBYTES);
    QByteArray byteArray(reinterpret_cast<const char *>(psw_salt), crypto_generichash_blake2b_SALTBYTES);
    QString psw_salt_b64 = byteArray.toBase64();

    QByteArray answer_byte = answer.toUtf8();

    QByteArray psw_byte = password.toUtf8(); // conversion from QString to QByteArray
    const unsigned char *psw = reinterpret_cast<const unsigned char *>(psw_byte.constData());
    size_t plaintext_len = psw_byte.size();
    unsigned char *crypted_psw = new unsigned char[plaintext_len + crypto_aead_chacha20poly1305_IETF_ABYTES];
    unsigned char *decrypted_text = new unsigned char[plaintext_len + 1];
    encryptData(key2, psw, plaintext_len, crypted_psw, nonce_psw);
    psw_byte = QByteArray(reinterpret_cast<const char *>(crypted_psw), plaintext_len + crypto_aead_chacha20poly1305_IETF_ABYTES);
    QString encr_psw_b64 = psw_byte.toBase64();

    QByteArray nonce_byte = QByteArray(reinterpret_cast<const char *>(nonce_psw), crypto_aead_chacha20poly1305_IETF_NPUBBYTES);
    QString nonce_b64 = nonce_byte.toBase64();

    decryptData(key2, crypted_psw, plaintext_len + crypto_aead_chacha20poly1305_IETF_ABYTES, decrypted_text, nonce_psw);
    decrypted_text[plaintext_len] = '\0';
    std::cout << "Decrypted text: " << decrypted_text << std::endl;
    hash(&password, psw_salt);

    gen_salt(sec_answ_salt, crypto_generichash_blake2b_SALTBYTES);

    byteArray = QByteArray(reinterpret_cast<const char *>(sec_answ_salt), crypto_generichash_blake2b_SALTBYTES);
    QString sec_ans_salt_b64 = byteArray.toBase64();

    hash(&answer, sec_answ_salt);

    if (newAccount(username, psw_salt_b64, password, securityQuestion_index, sec_ans_salt_b64, answer, encr_psw_b64, nonce_b64))
    {
        std::cout << "Registration succeeded" << std::endl;

        LoginWindow *LogInWindow = new LoginWindow(nullptr, dataFile, credentialsStore);
        delete psw_salt;
        delete sec_answ_salt;
        this->hide();
        LogInWindow->show();
    }
    else
    {
        delete psw_salt;
        delete sec_answ_salt;
        exit(1);
    }
}
int SignUpWindow::existing_usr_check(QString username)
{
    if (credentialsStore->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xmlReader(credentialsStore);
        while (!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            switch (token)
            {
            case QXmlStreamReader::StartElement:
                if (xmlReader.name() == tag::ACCOUNT && xmlReader.attributes().value(attribute::USERNAME) == username)
                {
                    credentialsStore->close();
                    return 1;
                }
            default:
                continue;
            }
        }
    }
    credentialsStore->close();
    return 0;
}

int SignUpWindow::newAccount(QString username, QString psw_salt_b64, QString password, int securityQuestion_index, QString sec_ans_salt_b64, QString answer, QString encr_psw_b64, QString nonce_b64)
{
    if (!credentialsStore->open(QIODevice::ReadOnly))
        return 0;
    QDomDocument *doc = new QDomDocument();
    if (!doc->setContent(credentialsStore))
    {
        credentialsStore->close();
        return 0;
    }
    credentialsStore->close();
    QDomElement root = doc->documentElement();
    QDomElement account = doc->createElement(tag::ACCOUNT);
    account.setAttribute(attribute::USERNAME, username);
    account.setAttribute(attribute::QUESTION_INDEX, securityQuestion_index);
    root.appendChild(account);

    QDomElement salt_psw = doc->createElement(tag::SALT_PSW);
    salt_psw.appendChild(doc->createTextNode(psw_salt_b64));
    account.appendChild(salt_psw);

    QDomElement hash_psw = doc->createElement(tag::HASH_PSW);
    hash_psw.appendChild(doc->createTextNode(password));
    account.appendChild(hash_psw);

    QDomElement salt_sec_ans = doc->createElement(tag::SALT_SEQ_ANSW);
    salt_sec_ans.appendChild(doc->createTextNode(sec_ans_salt_b64));
    account.appendChild(salt_sec_ans);

    QDomElement hash_sec_ans = doc->createElement(tag::HASH_SEC_ANSW);
    hash_sec_ans.appendChild(doc->createTextNode(answer));
    account.appendChild(hash_sec_ans);

    QDomElement nonce_psw = doc->createElement(tag::NONCE_PSW);
    nonce_psw.appendChild(doc->createTextNode(nonce_b64));
    account.appendChild(nonce_psw);

    QDomElement cripted_psw = doc->createElement(tag::CRIPTED_PSW);
    cripted_psw.appendChild(doc->createTextNode(encr_psw_b64));
    account.appendChild(cripted_psw);

    if (!credentialsStore->open(QIODevice::WriteOnly))
        return 0;

    QTextStream out(credentialsStore);
    out << doc->toString();
    credentialsStore->close();
    delete doc;
    return 1;
}