#ifndef OPCUA_H
#define OPCUA_H

#include <open62541/server.h>

UA_StatusCode opcua_server_loop(char *hostname, int port);
int opcua_run(char *host, int port);
bool get_opc_status(void);

#endif //OPCUA_H