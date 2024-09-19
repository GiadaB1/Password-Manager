#include "SecFunctions.h"
void gen_salt(unsigned char *salt, size_t length)
{
    randombytes_buf(salt, length);
}

void gen_nonce(unsigned char *nonce, size_t length)
{
    randombytes_buf(nonce, length);
}
void hash(QString *input, unsigned char *input_salt)
{
    unsigned char hash[crypto_generichash_blake2b_BYTES];

    QByteArray byteArray = input->toUtf8();
    QString base64String;
    const char *input_char = reinterpret_cast<const char *>(byteArray.constData());

    crypto_generichash_blake2b_state state;
    crypto_generichash_blake2b_init_salt_personal(&state, NULL, 0, crypto_generichash_blake2b_BYTES, input_salt, NULL);
    crypto_generichash_blake2b_update(&state, (const unsigned char *)input_char, byteArray.size());
    crypto_generichash_blake2b_final(&state, hash, sizeof(hash));

    byteArray = QByteArray(reinterpret_cast<const char *>(hash), crypto_generichash_blake2b_BYTES);
    base64String = byteArray.toBase64();
    input->clear();
    *input = base64String;
}

void derive_key(unsigned char *key, unsigned char *key_salt, const char *data)
{
    QByteArray byteArray = QByteArray::fromRawData(data, strlen(data));

    if (!crypto_pwhash(key, sizeof key, byteArray.constData(), byteArray.size(),
                       (const unsigned char *)key_salt,
                       crypto_pwhash_OPSLIMIT_MODERATE,
                       crypto_pwhash_MEMLIMIT_MODERATE,
                       crypto_pwhash_ALG_ARGON2ID13))
        exit(1);
}

bool encryptData(const unsigned char *key, const unsigned char *plaintext, size_t plaintext_len,
                 unsigned char *ciphertext, unsigned char *nonce)
{
    if (nonce == nullptr)
        randombytes_buf(nonce, crypto_aead_chacha20poly1305_IETF_NPUBBYTES);

    unsigned long long ciphertext_len;

    if (crypto_aead_chacha20poly1305_ietf_encrypt(ciphertext, &ciphertext_len,
                                                  plaintext, plaintext_len,
                                                  NULL, 0,
                                                  NULL, nonce, key) == 0)
        return true;

    return false;
}

bool decryptData(const unsigned char *key, const unsigned char *ciphertext, size_t ciphertext_len,
                 unsigned char *decrypted_text, unsigned char *nonce)
{
    unsigned long long decrypted_text_len;
    if (crypto_aead_chacha20poly1305_ietf_decrypt(decrypted_text, &decrypted_text_len,
                                                  NULL,
                                                  ciphertext, ciphertext_len,
                                                  NULL, 0,
                                                  nonce, key) == 0)
        return true;

    return false;
}