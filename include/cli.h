#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

typedef enum {
  MODE_ENCRYPT,
  MODE_DECRYPT,
} CipherMode;

typedef struct {
  const char *cipher_name;
  CipherMode mode;
  const char *key;
} CliArgs;

int parse_args(int argc, char *argv[], CliArgs *cli_args);

void print_usage(void);

#endif
