#ifndef XMLUTILS_H
#define XMLUTILS_H
#include <iostream>
namespace tag
{
    const QString ROOT = "Root";
    const QString ACCOUNT = "Account";
    const QString CREDENTIALS = "Credentials";
    const QString HASH_SEC_ANSW = "hash_sec_answ";
    const QString HASH_PSW = "hash_psw";
    const QString SALT_SEQ_ANSW = "salt_seq_answ";
    const QString SALT_PSW = "salt_psw";
    const QString CRIPTED_PSW = "cripted_psw";
    const QString NONCE_PSW = "nonce_psw";
    const QString NONCE_CREDS = "nonce_creds";
    const QString SALT_MASTER_KEY = "salt_master_key";
} // namespace tags

namespace attribute
{
    const QString ACCOUNT_NAME = "account_name";
    const QString USERNAME = "username";
    const QString PASSWORD = "password";
    const QString QUESTION_INDEX = "question_index";
    const QString ANSWER = "answer";
}
#endif