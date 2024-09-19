#include "AccountWindow.h"

AccountWindow::AccountWindow(QWidget *parent, QFile *credFile_in, QFile *infoFile_in, QString username_in, unsigned char *key_in) : QWidget(parent), credentialsStore(credFile_in), dataFile(infoFile_in), username(username_in), key(key_in)
{

    setWindowTitle("Account");
    this->setFixedSize(800, 800);
    welcome_text->setText("Welcome, " + username_in + "!");
    welcome_text->setFont(font_titles);
    welcome_text->adjustSize();
    int height = welcome_text->height();
    int width = welcome_text->width();
    animation->setStartValue(QRect(-650, 0, width, height));
    animation->setEndValue(QRect(20, 0, width, height));
    animation->setDuration(300);

    animation->start();

    main_layout->addWidget(welcome_text, 0, Qt::AlignCenter);

    data_model->setHorizontalHeaderLabels({"Account", "Username", "Password"});

    credentialsTable->setModel(data_model);
    credentialsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    credentialsTable->setMaximumHeight(500);
    credentialsTable->horizontalHeader()->setDefaultSectionSize(40);
    credentialsTable->adjustSize();
    main_layout->addWidget(credentialsTable);
    main_layout->addSpacerItem(push_table_up);
    add_credentials->setFixedSize(100, 30);
    Username->setPlaceholderText("Username");
    Password->setPlaceholderText("Password");
    Account->setPlaceholderText("Account");
    credentials_layout->addWidget(Account);
    credentials_layout->addWidget(Username);
    credentials_layout->addWidget(Password);
    main_layout->addLayout(credentials_layout);
    main_layout->addWidget(add_credentials, 0, Qt::AlignRight);
    main_layout->addWidget(back_to_login);
    connect(add_credentials, &QPushButton::clicked, [this]()
            {
                add_new_credentials();
                update_table(); });
    connect(back_to_login, &ClickableText::clicked, [this]()
            {
        LoginWindow *backToLogin = new LoginWindow(nullptr, dataFile, credentialsStore);
        backToLogin->show();
        this->hide(); });
}

AccountWindow::~AccountWindow()
{
    /*if (newCredentials)
    {
        // QString newdata = new_creds_tostr();
        std::cout << "ciao";
    }*/
    delete push_table_up;
    delete add_credentials;
    delete back_to_login;
    delete Account;
    delete Username;
    delete Password;
    delete newCredentials;
    delete welcome_text;
    delete animation;
    delete credentialsTable;
    delete data_model;
}

void AccountWindow::add_new_credentials()
{
    credentials cred(Account->text(), Username->text(), Password->text());
    Account->clear();
    Username->clear();
    Password->clear();
    newCredentials->append(cred);
}

void AccountWindow::update_table()
{
    QList<QStandardItem *> row;
    credentials lastCredential = newCredentials->last();
    row.append(new QStandardItem(lastCredential.accountName));
    row.append(new QStandardItem(lastCredential.username));
    row.append(new QStandardItem(lastCredential.password));

    data_model->appendRow(row);
}

QString AccountWindow::new_creds_tostr()
{
    QDomDocument doc;
    for (credentials cred : *newCredentials)
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
}
