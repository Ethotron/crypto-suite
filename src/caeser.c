#include "cipher.h"
#include <stdlib.h>

static void encrypt(const char *key) {

}

static void decrypt(const char *key) {

}

static char* cryptanalyze(void) {

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


