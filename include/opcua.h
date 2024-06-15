#ifndef OPCUA_H
#define OPCUA_H

#include <open62541/server.h>

int opcua_run(char *host, int port);
bool opcua_get_server_status(void);

#endif //OPCUA_H