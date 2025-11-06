#include "cipher.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


static char *encrypt_impl(const char *plain_text, const char *key) {
  int input_len = strlen(plain_text);
  char *cipher_text = malloc(input_len + 1);
  if (cipher_text == NULL) {
    return NULL;
  }

  int key_len = strlen(key);

  char *output = cipher_text;
  int char_count = 0;
  for (int i = 0; i < input_len; i++) {
    char ch = plain_text[i];
    if (isalpha(ch)) {
      ch = toupper(ch);
      int shift = key[char_count++ % key_len] - 'A';
      char encrypted_ch = ((ch - 'A' + shift) % 26) + 'A';
      *output++ = encrypted_ch;
    }
  }

  *output = '\0';
  return cipher_text;
}

static char *decrypt_impl(const char *cipher_text, const char *key) {

}


const Cipher VIGENERE_CIPHER = {
  .name = "vigenere",
  .encrypt = encrypt_impl,
  .decrypt = decrypt_impl,
};
