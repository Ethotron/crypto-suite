#ifndef CIPHER_H
#define CIPHER_H

#include "cli.h"
typedef struct {
  void (*encrypt)(const char *input_text, const char *key);
  void (*decrypt)(const char *input_text, const char *key);
  char* (*cryptanalyze)(const char *input_text);
} CipherStrategy;

const CipherStrategy *get_cipher_strategy(CipherAlgorithm algorithm);

#endif
