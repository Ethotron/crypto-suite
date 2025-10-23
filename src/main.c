#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "cipher.h"
#include "cli.h"

int main(int argc, char *argv[]) {
  CliArgs cli_args;
  if (parse_args(argc, argv, &cli_args) != 0) {
    return EXIT_FAILURE;
  }

  char buffer[4096];
  size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, stdin);
  buffer[bytes_read] = '\0';
  const Cipher *cipher = get_cipher(cli_args.cipher_name);

  if (!cipher) {
    fprintf(stderr, "Error: Strategy not defined for cipher.\n");
    return EXIT_FAILURE;
  }

  char *output;
  switch (cli_args.mode) {
    case MODE_ENCRYPT:
      output = cipher->encrypt(buffer, cli_args.key);
      break;
    case MODE_DECRYPT:
      output = cipher->decrypt(buffer, cli_args.key);
      break;
    default:
      fprintf(stderr, "Error: Unsupported operation.\n");
      return EXIT_FAILURE;
  }

  printf("%s\n", output);
  free(output);
  
  return EXIT_SUCCESS;
}
