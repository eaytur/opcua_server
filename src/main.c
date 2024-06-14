#include "opcua.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("Open62541-lib-version: %s\n", UA_OPEN62541_VERSION);

  UA_StatusCode retVal = opcua_server_loop();

  return retVal ? EXIT_FAILURE : EXIT_SUCCESS;
}