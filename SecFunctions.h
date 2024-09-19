
#include <sodium.h>
#include <QString>
#include <iostream>
void gen_salt(unsigned char *, size_t);

void gen_nonce(unsigned char *, size_t);

void hash(QString *, unsigned char *);

void derive_key(unsigned char *, unsigned char *, const char *);

bool encryptData(const unsigned char *, const unsigned char *, size_t,
                 unsigned char *, unsigned char *);
bool decryptData(const unsigned char *, const unsigned char *, size_t,
                 unsigned char *, unsigned char *);
