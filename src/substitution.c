#include "cipher.h"

static char* encrypt_impl(const char *plain_text, const char *key) {

}

static char* decrypt_impl(const char *cipher_text, const char *key) {

}

const Cipher SUBSTITUTION_CIPHER = {
  .name = "substitution",
  .encrypt = encrypt_impl,
  .decrypt = decrypt_impl,
};

