#include "opcua.h"

#include <open62541/plugin/log_stdout.h>
#include <open62541/server_config_default.h>

#include <pthread.h>
#include <signal.h>

static volatile UA_Boolean running = true;

typedef struct thread_args {
  char *hostname;
  int port;
} thread_args_t;

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

void *opcua_server_thread(void *args) {
  thread_args_t *threadArgs = (thread_args_t *)args;
  opcua_server_loop(threadArgs->hostname, threadArgs->port);

  free(threadArgs);
  return NULL;
}

int opcua_run(char *host, int port) {
  pthread_t opcThread;
  int retVal = 0;

  thread_args_t *threadArgs = (thread_args_t *)malloc(sizeof(thread_args_t));
  if (!threadArgs) {
    return EXIT_FAILURE;
  }

  threadArgs->hostname = host;
  threadArgs->port = port;

  retVal =
      pthread_create(&opcThread, NULL, opcua_server_thread, (void *)threadArgs);
  if (retVal != 0) {
    free(threadArgs);
    return EXIT_FAILURE;
  }

  retVal = pthread_detach(opcThread);
  if (retVal != 0) {
    free(threadArgs);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

bool get_opc_status(void) { return running; }