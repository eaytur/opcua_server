#include "opcua.h"

#include <open62541/plugin/log_stdout.h>
#include <open62541/server_config_default.h>

#include <signal.h>

static volatile UA_Boolean running = true;

static void stopHandler(int sig) {
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
  running = false;
}

UA_StatusCode opcua_server_loop(void) {
  signal(SIGINT, stopHandler);
  signal(SIGTERM, stopHandler);

  UA_Server *server = UA_Server_new();
  UA_StatusCode retVal =
      UA_ServerConfig_setDefault(UA_Server_getConfig(server));

  retVal = UA_Server_run(server, &running);

  UA_Server_delete(server);

  return retVal;
}