#include "opcua.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *host = NULL;
  int port = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--host") == 0 && i + 1 < argc) {
      host = argv[++i];
    } else if (strcmp(argv[i], "--port") == 0 && i + 1 < argc) {
      port = atoi(argv[++i]);
    } else {
      printf("Unknown or incomplete argument: %s\n", argv[i]);
      return EXIT_FAILURE;
    }
  }

  if (host == NULL || port == 0) {
    printf("Missing required arguments!\n");
    printf("Usage: opcua_server --host <hostname> --port <portnumber>\n");
    return EXIT_FAILURE;
  }

  int retVal = opcua_run(host, port);
  if (retVal != EXIT_SUCCESS) {
    return retVal;
  }

  while (get_opc_status()) {
    printf(".");
    fflush(stdout);
    sleep(1);
  };

  return EXIT_SUCCESS;
}