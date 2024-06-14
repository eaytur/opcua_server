#include "opcua.h"

#include <open62541/plugin/log_stdout.h>
#include <open62541/server_config_default.h>

#include <signal.h>

static volatile UA_Boolean running = true;

static void stopHandler(int sig) {
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
  running = false;
}

UA_StatusCode opcua_server_loop(char *hostname, int port) {

  UA_String host = UA_STRING(hostname);

  signal(SIGINT, stopHandler);
  signal(SIGTERM, stopHandler);

  UA_Server *server = UA_Server_new();
  UA_ServerConfig *config = UA_Server_getConfig(server);
  UA_String_clear(&config->customHostname);
  UA_String_copy(&host, &config->customHostname);
  UA_StatusCode retVal = UA_ServerConfig_setMinimal(config, port, NULL);

  retVal = UA_Server_run(server, &running);

  UA_Server_delete(server);

  return retVal;
}