#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "cli.h"
#include "cipher.h"

int main(int argc, char *argv[]) {
  CliArgs cli_args;
  if (parse_args(argc, argv, &cli_args) != 0) {
    return EXIT_FAILURE;
  }

  char buffer[4096];
  size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, stdin);
  buffer[bytes_read] = '\0';
  const CipherStrategy *strategy = get_cipher_strategy(cli_args.cipher);

  if (!strategy) {
    fprintf(stderr, "Error: Strategy not defined for cipher.\n");
    return EXIT_FAILURE;
  }

  switch (cli_args.mode) {
    case MODE_ENCRYPT:
      strategy->encrypt(buffer, cli_args.key);
      break;
    case MODE_DECRYPT:
      strategy->decrypt(buffer, cli_args.key);
      break;
    case MODE_CRYPTANALYZE:
      strategy->cryptanalyze(buffer);
      break;
    default:
      fprintf(stderr, "Error: Unsupported operation.\n");
      return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
