#ifndef CIPHER_H
#define CIPHER_H

#include "cli.h"
typedef struct {
  void (*encrypt)(const char *key);
  void (*decrypt)(const char *key);
  char* (*cryptanalyze)(void);
} CipherStrategy;

const CipherStrategy *get_cipher_strategy(CipherAlgorithm algorithm);

#endif
