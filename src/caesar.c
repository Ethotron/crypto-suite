#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "cipher.h"

static char *encrypt_impl(const char *plain_text, const char *key) {
  int input_len = strlen(plain_text);
  char *cipher_text = malloc(input_len + 1);
  if (cipher_text == NULL) {
    return NULL;
  }

  int shift = atoi(key);

  char *output = cipher_text;
  for (int i = 0; i < input_len; i++) {
    char ch = plain_text[i];
    if (isalpha(ch)) {
      ch = toupper(ch);
      char encrypted_ch = ((ch - 'A' + shift) % 26) + 'A';
      *output++ = encrypted_ch;
    }
  }

  *output = '\0';
  return cipher_text;
}

static char *decrypt_impl(const char *cipher_text, const char *key) {
  int input_len = strlen(cipher_text);
  char *plain_text = malloc(input_len + 1);
  if (plain_text == NULL) {
    return NULL;
  }

  int shift = atoi(key);

  char *output = plain_text;
  for (int i = 0; i < input_len; i++) {
    char ch = cipher_text[i];
    if (isalpha(ch)) {
      ch = toupper(ch);
      char decrypted_ch = ((ch - 'A' + (26 - shift)) % 26) + 'A';
      *output++ = decrypted_ch;
    }
  }

  *output = '\0';
  return plain_text;
}

const Cipher CAESAR_CIPHER = {
  .name = "caesar",
  .encrypt = encrypt_impl,
  .decrypt = decrypt_impl,
};

