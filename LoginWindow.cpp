
#include "LoginWindow.h"
#include <iostream>
#include <string>
#include <QDebug>
#include <QXmlStreamReader>
#include <QString>

LoginWindow::LoginWindow(QWidget *parent, QFile *in_file, QFile *info_file) : QWidget(parent), dataFile(in_file), credentialsStore(info_file)
{
    this->setFixedSize(450, 350);
    textField_usr->setFixedSize(200, 30);
    textField_psw->setFixedSize(200, 30);
    textField_psw->setEchoMode(QLineEdit::Password);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setWindowTitle("Password Manager -Access Page");
    grid_layout->setContentsMargins(0, 0, 100, 0);
    grid_layout->addWidget(username_label, 0, 0, Qt::AlignRight);
    grid_layout->addWidget(textField_usr, 0, 1, Qt::AlignCenter);
    grid_layout->addWidget(password_label, 1, 0, Qt::AlignRight);
    grid_layout->addWidget(textField_psw, 1, 1, Qt::AlignCenter);
    LogIn_button->setFixedSize(100, 30);
    connect(LogIn_button, &QPushButton::clicked, this, &LoginWindow::LogIn_clicked);
    grid_layout->addWidget(LogIn_button, 2, 1, Qt::AlignLeft);
    grid_layout->setSpacing(0);
    LogIn_container->setFixedHeight(130);

    vbox_layout->setSpacing(0);
    vbox_layout->setContentsMargins(0, 0, 0, 0);
    vbox_layout->addWidget(LogIn_container);
    forgot_psw_layout->setContentsMargins(90, 0, 90, 0);
    forgot_psw_layout->addWidget(forgot_psw);
    forgot_psw_layout->addWidget(forgot_psw_click);
    connect(forgot_psw_click, &ClickableText::clicked, this, &LoginWindow::forgotPsw_clicked);
    sign_up_layout->setContentsMargins(90, 0, 90, 0);
    sign_up_layout->addWidget(sign_up);
    sign_up_layout->addWidget(sign_up_click);
    connect(sign_up_click, &ClickableText::clicked, this, &LoginWindow::signUp_clicked);
    vbox_layout->addLayout(forgot_psw_layout);
    vbox_layout->addLayout(sign_up_layout);

    this->setLayout(vbox_layout);
}

LoginWindow::~LoginWindow()
{
    std::cout << "LoginWindow deleted" << std::endl;
    delete LogIn_container;
    delete username_label;
    delete textField_usr;
    delete forgot_psw_layout;
    delete forgot_psw;
    delete forgot_psw_click;
    delete sign_up_layout;
    delete sign_up;
    delete sign_up_click;
    delete password_label;
    delete textField_psw;
    delete LogIn_button;
}

void LoginWindow::LogIn_clicked()
{

    // Usa variabili locali anziché puntatori per la gestione della memoria
    QString username = textField_usr->text();
    QString password = textField_psw->text();

    // Allocate memory for salt and hash
    unsigned char in_salt[crypto_generichash_blake2b_SALTBYTES];
    unsigned char in_hash[crypto_generichash_blake2b_BYTES];

    // Read credentials store
    if (!credentialsStore->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        exit(1); // Handle error properly
    }

    QXmlStreamReader xmlReader(credentialsStore);

    bool found = false;
    while (!xmlReader.atEnd() && !xmlReader.hasError() && !found)
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if (token == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == tag::ACCOUNT &&
                xmlReader.attributes().value(attribute::USERNAME) == username)
            {
                // Found the account; now read its details
                while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == tag::ACCOUNT) && !found)
                {
                    xmlReader.readNext();
                    if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xmlReader.name() == tag::SALT_PSW)
                        {
                            QByteArray saltData = QByteArray::fromBase64(xmlReader.readElementText().toUtf8());
                            memcpy(in_salt, saltData.constData(), crypto_generichash_blake2b_SALTBYTES);
                        }
                        else if (xmlReader.name() == tag::HASH_PSW)
                        {
                            QByteArray hashData = QByteArray::fromBase64(xmlReader.readElementText().toUtf8());
                            memcpy(in_hash, hashData.constData(), crypto_generichash_blake2b_BYTES);

                            found = true;
                        }
                    }
                }
            }
        }
    }
    credentialsStore->close();

    if (found)
    {
        // Verify password
        unsigned char *key = new unsigned char[crypto_aead_chacha20poly1305_IETF_KEYBYTES];
        unsigned char *nonce = new unsigned char[crypto_aead_chacha20poly1305_NPUBBYTES];
        unsigned char *salt = new unsigned char[crypto_pwhash_SALTBYTES];
        // recover_nonce_salt(nonce, salt);
        if (!get_in_xml(nonce, crypto_aead_chacha20poly1305_NPUBBYTES, tag::NONCE_CREDS, credentialsStore))
            gen_nonce(nonce, crypto_aead_chacha20poly1305_NPUBBYTES);
        if (!get_in_xml(salt, crypto_pwhash_SALTBYTES, tag::SALT_MASTER_KEY, credentialsStore))
            gen_salt(salt, crypto_pwhash_SALTBYTES);
        derive_key(key, salt, password.toUtf8().data());
        hash(&password, in_salt);
        QByteArray decodedPassword = QByteArray::fromBase64(password.toUtf8());
        if (memcmp(in_hash, decodedPassword, crypto_generichash_blake2b_BYTES) == 0)
        {
            std::cout << "Logged in successfully" << std::endl;
            AccountWindow *accountWindow = new AccountWindow(nullptr, credentialsStore, dataFile, username, key);
            /*connect(accountWindow, &AccountWindow::isHidden, this, [this, credentialsList, key, nonce]()
                    {
                if(credentialsList != nullptr){
                    QString new_data = update_data();
                    std::cout << new_data.toUtf8().data() << std::endl;
                    size_t plaintext_size = new_data.size();
                    unsigned char *plaintext = new unsigned char[plaintext_size + 1];
                    memcpy(plaintext, new_data.toUtf8().data(), plaintext_size);
                    plaintext[plaintext_size] = '\0';
                    size_t crypted_newdata_size = plaintext_size + crypto_aead_chacha20poly1305_IETF_ABYTES;
                    unsigned char *crypted_newdata = new unsigned char[crypted_newdata_size];
                    if(!encryptData(key, plaintext, plaintext_size, crypted_newdata, nonce))
                        exit(1);
                    if(!decryptData(key, crypted_newdata, crypted_newdata_size, plaintext, nonce))
                        exit(1);
                    plaintext[plaintext_size] = '\0';
                    std::cout << plaintext << std::endl;

                } });*/

            this->hide();
            accountWindow->show();
        }
        else
        {
            std::cout << "Login failed" << std::endl;
        }
    }
    else
    {
        std::cout << "Account not found" << std::endl;
    }
}

void LoginWindow::forgotPsw_clicked()
{
    RecoverPswWindow *forgotPasswordWindow = new RecoverPswWindow(nullptr, credentialsStore, dataFile);
    this->hide();
    forgotPasswordWindow->show();
}

void LoginWindow::signUp_clicked()
{
    SignUpWindow *signUpWindow = new SignUpWindow(nullptr, dataFile, credentialsStore);

    this->hide();
    signUpWindow->show();
}

/*QString LoginWindow::update_data()
{
    QDomDocument doc;
    for (credentials cred : *credentialsList)
    {
        QDomElement CredentialsElement = doc.createElement(tag::CREDENTIALS);
        CredentialsElement.setAttribute(attribute::ACCOUNT_NAME, cred.accountName);
        CredentialsElement.setAttribute(attribute::USERNAME, cred.username);
        CredentialsElement.setAttribute(attribute::PASSWORD, cred.password);
        doc.appendChild(CredentialsElement);
        std::cout << cred.accountName.toUtf8().data() << " " << cred.username.toUtf8().data() << " " << cred.password.toUtf8().data() << std::endl;
    }
    QString new_data = doc.toString();
    std::cout << new_data.toStdString() << std::endl;
    return new_data;
}*/
