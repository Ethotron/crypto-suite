#include "cli.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>

static bool cipher_from_string(const char *str, CipherAlgorithm *cipher_algorithm) {
  if (str == NULL){
    return false;
  }

  if (strcasecmp(str, "caeser") == 0) {
    *cipher_algorithm = CIPHER_CAESER;
    return true;
  }

  return false;
}

static bool mode_from_string(const char *str, CipherMode *cipher_mode) {
  if (str == NULL) {
    return false;
  }

  if (strcasecmp(str, "encrypt") == 0) {
    *cipher_mode = MODE_ENCRYPT;
    return true;
  }
  if (strcasecmp(str, "decrypt") == 0) {
    *cipher_mode = MODE_DECRYPT;
    return true;
  }
  if (strcasecmp(str, "bruteforce") == 0) {
    *cipher_mode = MODE_CRYPTANALYZE;
    return true;
  }
  
  return false;
}

void print_usage(void) {
    printf("Usage:\n");
    printf("  crypto-suite --cipher <name> --mode <encrypt|decrypt|cryptanalyze> [options]\n\n");
    printf("Options:\n");
    printf("  --key <key>            Key for encryption/decryption (not used for cryptanalyze)\n");
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
        if (!cipher_from_string(optarg, &cli_args->cipher)) {
          fprintf(stderr, "Error: %s is not a valid cipher algorithm.\n", optarg);
          print_usage();
          return 1;
        };
        break;
      case 'm':
        if (!mode_from_string(optarg, &cli_args->mode)) {
          fprintf(stderr, "Error: %s is not a valid algorithm mode.\n", optarg);
          print_usage();
          return 1;
        }
        break;
      case 'k':
        strncpy(cli_args->key, optarg, sizeof(cli_args->key) - 1);
        cli_args->has_key = true;
        break;
      case 'h':
        print_usage();
        return 0;
      default:
        print_usage();
        return 1;
    }
  }

  if ((cli_args->mode == MODE_ENCRYPT || cli_args->mode == MODE_DECRYPT) && !cli_args->has_key) {
    fprintf(stderr, "Error: --key is required for encrypt/decrypt modes.\n");
    print_usage();
    return 1;
  }

  if (cli_args->mode == MODE_CRYPTANALYZE && cli_args->has_key) {
    fprintf(stderr, "Warning: --key ignored for cryptanalyze mode.\n");
  }

  return 0;
}
