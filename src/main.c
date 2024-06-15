#include "opcua.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  int retVal = opcua_run("localhost", 3535);
  if (retVal != EXIT_SUCCESS) {
    return retVal;
  }

  while (get_opc_status()) {
    printf(".");
    fflush(stdout);
    sleep(1);
  };

  return retVal;
}