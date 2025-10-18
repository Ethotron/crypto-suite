#include <stdlib.h>
#include "cli.h"

int main(int argc, char *argv[]) {
  CliArgs *cli_args = malloc(sizeof(CliArgs));
  if (!parse_args(argc, argv, cli_args)) {
    exit(EXIT_FAILURE);
  }
  else {
    exit(EXIT_SUCCESS);
  }
}
