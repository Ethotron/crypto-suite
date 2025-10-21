#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

typedef enum {
  CIPHER_CAESAR
} CipherAlgorithm;

typedef enum {
  MODE_ENCRYPT,
  MODE_DECRYPT,
  MODE_CRYPTANALYZE,
} CipherMode;

typedef struct {
  CipherAlgorithm cipher;
  CipherMode mode;
  char key[128];
  bool has_key;
} CliArgs;

int parse_args(int argc, char **argv, CliArgs *cli_args);

void print_usage(void);

#endif
