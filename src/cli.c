#include "cli.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>

static bool mode_from_string(const char *str, CipherMode *cipher_mode) {
  if (str == NULL) {
    return false;
  }

  if (strcasecmp(str, "encrypt") == 0) {
    *cipher_mode = MODE_ENCRYPT;
    return true;
  }
  else if (strcasecmp(str, "decrypt") == 0) {
    *cipher_mode = MODE_DECRYPT;
    return true;
  }
  else {
    return false;
  }
}

void print_usage(void) {
    printf("Usage:\n");
    printf("  crypto-suite --cipher <name> --mode <encrypt/decrypt> [options]\n\n");
    printf("Options:\n");
    printf("  --key <key>            Key for encryption/decryption\n");
    printf("  -h, --help             Show this help message\n");
    printf("\nExamples:\n");
    printf("  crypto-suite --cipher caesar --mode encrypt --key 3\n");
    printf("  crypto-suite --cipher vigenere --mode decrypt --key LEMON\n");
}

int parse_args(int argc, char **argv, CliArgs *cli_args) {
  static struct option long_opts[] = {
    {"cipher", required_argument, 0, 'c'},
    {"mode", required_argument, 0, 'm'},
    {"key", required_argument, 0, 'k'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
  };

  int opt;
  int opt_index = 0;
  while ((opt = getopt_long(argc, argv, "c:m:k:h", long_opts, &opt_index)) != -1) {
    switch (opt) {
      case 'c':
        cli_args->cipher_name = optarg;
        break;
      case 'm':
        if (!mode_from_string(optarg, &cli_args->mode)) {
          fprintf(stderr, "Error: %s is not a valid algorithm mode.\n", optarg);
          print_usage();
          return 1;
        }
        break;
      case 'k':
        cli_args->key = optarg;
        break;
      case 'h':
        print_usage();
        return 1;
      default:
        print_usage();
        return 1;
    }
  }
  return 0;
}
