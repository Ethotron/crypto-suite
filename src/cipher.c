#include "cipher.h"
#include "cli.h"
#include <stdlib.h>

extern const CipherStrategy *get_caeser_strategy(void);

const CipherStrategy *get_cipher_strategy(CipherAlgorithm algorithm) {
  switch (algorithm) {
    case CIPHER_CAESER : return get_caeser_strategy();
    default : return NULL;
  }
}
