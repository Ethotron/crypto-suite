#include "cipher.h"
#include "caesar.h"
#include "substitution.h"
#include <string.h>

static const Cipher *ciphers[] = {
  &CAESAR_CIPHER,
  &SUBSTITUTION_CIPHER,
  NULL
};

const Cipher *get_cipher(const char *name) {
  if (!name) {
    return NULL;
  }

  for (int i = 0; ciphers[i] != NULL; i++) {
    if (strcmp(ciphers[i]->name, name) == 0) {
      return ciphers[i];
    }
  }
  return NULL;
}

