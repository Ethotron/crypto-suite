#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "cipher.h"

static bool parse_key(const char *key_str, int *key_out) {
  if (!key_str || !isdigit(*key_str)) {
    fprintf(stderr, "Invalid Key: Caesar cipher key must be an integer.\n");
    return false;
  }

  int key = atoi(key_str);
  if (key < 0 || key > 25) {
    fprintf(stderr, "Invalid Key: Caesar cipher key must be between 0 and 25.\n");
    return false;
  }

  *key_out = key;
  return true;
}

static char *encrypt_impl(const char *plain_text, const char *key) {
  int shift;
  if (!parse_key(key, &shift)) {
    return NULL;
  }

  int input_len = strlen(plain_text);
  char *cipher_text = malloc(input_len + 1);
  if (cipher_text == NULL) {
    return NULL;
  }

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
  int shift;
  if (!parse_key(key, &shift)) {
    return NULL;
  }

  int input_len = strlen(cipher_text);
  char *plain_text = malloc(input_len + 1);
  if (plain_text == NULL) {
    return NULL;
  }

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

