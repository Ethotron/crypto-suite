#include "cipher.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

static bool is_key_valid(const char *key) {
  if (strlen(key) != ALPHABET_SIZE) {
    fprintf(stderr, "Invalid key: key must be exactly 26 alphabetic characters long.");
    return false;
  }

  bool contains_letter[ALPHABET_SIZE] = { false };

  for (int i = 0; i < ALPHABET_SIZE ; i++) {
    char letter = toupper((unsigned char)key[i]);
    if (letter < 'A' || letter > 'Z') {
      fprintf(stderr, "Invalid key: key can only contain alphabetic characters\n");
      return false;
    }

    int index = letter - 'A';
    if (contains_letter[index]) {
      fprintf(stderr, "Invalid key: alphabetic characters must be unique\n");
      return false;
    }
  }

  return true;
}

static char* encrypt_impl(const char *plain_text, const char *key) {
  if (!is_key_valid(key)) {
    return NULL;
  }

  int input_len = strlen(plain_text);
  char *cipher_text = malloc(input_len + 1);
  if (cipher_text == NULL) {
    return NULL;
  }

  char *end = cipher_text;
  for (int i = 0; i < input_len; i++) {
    char ch = plain_text[i];
    if (isalpha(ch)){
      ch = toupper(ch);
      int index = ch - 'A';
      char encrypted_ch = key[index];
      *end++ = encrypted_ch;
    }
  }

  *end = '\0';
  return cipher_text;
}

static char* decrypt_impl(const char *cipher_text, const char *key) {

}

const Cipher SUBSTITUTION_CIPHER = {
  .name = "substitution",
  .encrypt = encrypt_impl,
  .decrypt = decrypt_impl,
};

