#include <stdlib.h>
#include<stdio.h>
#include "cli.h"
#include "cipher.h"

int main(int argc, char *argv[]) {
  CliArgs *cli_args = malloc(sizeof(CliArgs));
  if (!parse_args(argc, argv, cli_args)) {
    exit(EXIT_FAILURE);
  }

  const CipherStrategy *strategy = get_cipher_strategy(cli_args->cipher);

  if (!strategy) {
    fprintf(stderr, "Error: Strategy not defined for cipher.\n");
    exit(EXIT_FAILURE);
  }

  switch (cli_args->mode) {
    case MODE_ENCRYPT:
      strategy->encrypt(cli_args->key);
      break;
    case MODE_DECRYPT:
      strategy->decrypt(cli_args->key);
      break;
    case MODE_CRYPTANALYZE:
      strategy->cryptanalyze();
      break;
    default:
      fprintf(stderr, "Error: Unsupported operation.\n");
      exit(EXIT_FAILURE);
  }
  
  free(cli_args);
  exit(EXIT_SUCCESS);
}
