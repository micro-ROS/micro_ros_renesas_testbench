#ifndef MICROROS_TRANSPORTS__H
#define MICROROS_TRANSPORTS__H

#include <uxr/client/transport.h>

typedef struct custom_transport_args {
    ULONG agent_ip_address;
    UINT agent_port;
} custom_transport_args;

bool renesas_e2_transport_open(struct uxrCustomTransport * transport);
bool renesas_e2_transport_close(struct uxrCustomTransport * transport);
size_t renesas_e2_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * error);
size_t renesas_e2_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);

#endif  // MICROROS_TRANSPORTS__H
