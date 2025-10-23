#ifndef CIPHER_H
#define CIPHER_H

typedef struct {
  const char *name;
  char *(*encrypt)(const char *plain_text, const char *key);
  char *(*decrypt)(const char *cipher_text, const char *key);
} Cipher;

const Cipher *get_cipher(const char *name);

#endif
