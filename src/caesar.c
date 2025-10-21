#include "cipher.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

static void encrypt(const char *input_text, const char *key) {
  int shift = atoi(key);
  int input_len = strlen(input_text);
  for (int i = 0; i < input_len; i++) {
    char ch = input_text[i];
    if (isalpha(ch)) {
      ch = toupper(ch);
      char encrypted_ch = ((ch - 'A' + shift) % 26) + 'A';
      putchar(encrypted_ch);
    }
  }
  putchar('\n');
}

static void decrypt(const char *input_text, const char *key) {
  int shift = atoi(key);
  int input_len = strlen(input_text);
  for (int i = 0; i < input_len; i++) {
    char ch = input_text[i];
    if (isalpha(ch)) {
      ch = toupper(ch);
      char encrypted_ch = ((ch - 'A' + (26 - shift)) % 26) + 'A';
      putchar(encrypted_ch);
    }
  }
  putchar('\n'); 
}

static char* cryptanalyze(const char *input_text) {

  return NULL;
}

static const CipherStrategy strategy = {
  .encrypt = encrypt,
  .decrypt = decrypt,
  .cryptanalyze = cryptanalyze
};

const CipherStrategy *get_caeser_strategy(void) {
  return &strategy;
}


