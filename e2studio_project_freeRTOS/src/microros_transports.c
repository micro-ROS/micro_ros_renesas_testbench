#include "net_thread.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
#include "FreeRTOS_Sockets.h"
#include <uxr/client/transport.h>
#include <uxr/client/util/time.h>

#include <rmw_microxrcedds_c/config.h>
#include <microros_transports.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#if( ipconfigUSE_DHCP != 0 )
   /* DHCP populates these IP address, Sub net mask and Gateway Address. So start with this is zeroed out values
    * The MAC address is Test MAC address.
    */
    static  uint8_t ucMACAddress[ 6 ]       = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
    static  uint8_t ucIPAddress[ 4 ]        = {0x00};
    static  uint8_t ucNetMask[ 4 ]          = {0x00};
    static  uint8_t ucGatewayAddress[ 4 ]   = {0x00};
    static  uint8_t ucDNSServerAddress[ 4 ] = {0x00};
#else
    static  uint8_t ucMACAddress[ 6 ]       = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
    static  uint8_t ucIPAddress[ 4 ]        = {192, 168, 1, 180};
    static  uint8_t ucNetMask[ 4 ]          = {255, 255, 255, 0};
    static  uint8_t ucGatewayAddress[ 4 ]   = {0, 0, 0, 0};
    static  uint8_t ucDNSServerAddress[ 4 ] = {10, 60, 1, 2};
#endif

struct freertos_sockaddr remote_addr;

bool renesas_e2_transport_open(struct uxrCustomTransport * transport){
    uxrUDPSocket *customSocket = (uxrUDPSocket *)transport->args;

    bool rv = false;

    FreeRTOS_IPInit( ucIPAddress,
                         ucNetMask,
                         ucGatewayAddress,
                         ucDNSServerAddress,
                         ucMACAddress );


    customSocket->xSocket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_DGRAM, FREERTOS_IPPROTO_UDP);
    if (FREERTOS_INVALID_SOCKET != customSocket->xSocket)
    {
        rv = true;
    }

    return rv;
}

bool renesas_e2_transport_close(struct uxrCustomTransport * transport){
    uxrUDPSocket *customSocket = (uxrUDPSocket *)transport->args;
    (void) FreeRTOS_shutdown(customSocket->xSocket, FREERTOS_SHUT_RDWR);

    /* FreeRTOS_closesocket() must be called even if FreeRTOS_shutdown() returns error.
     * FreeRTOS_closesocket() always returns 0. */
    (void) FreeRTOS_closesocket(customSocket->xSocket);
    return true;
}

size_t renesas_e2_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err){
    uxrUDPSocket *customSocket = (uxrUDPSocket *)transport->args;
    size_t rv = 0;

    // TODO: set socket send timeout?
    BaseType_t bytes_sent = FreeRTOS_sendto(customSocket->xSocket, buf, len, 0, &customSocket->remote_addr, sizeof(customSocket->remote_addr));

    /* FreeRTOS_send() returns the number of bytes queued for sending.
     * If an error or timeout occurred, FreeRTOS_send() returns a negative value. */
    if (0 <= bytes_sent)
    {
        rv = (size_t)bytes_sent;
        *err = 0;
    }
    else
    {
        *err = 1;
    }

    return rv;
}

size_t renesas_e2_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err){
    uxrUDPSocket *customSocket = (uxrUDPSocket *)transport->args;
    size_t rv = 0;

    // Set read timeout
    TickType_t timeout_ticks = pdMS_TO_TICKS(timeout);
    FreeRTOS_setsockopt(customSocket->xSocket, 0, FREERTOS_SO_RCVTIMEO, &timeout_ticks, 0);

    int32_t bytes_received = FreeRTOS_recvfrom(customSocket->xSocket, (void*)buf, len, 0, NULL, NULL);
    if (0 <= bytes_received)
    {
        rv = (size_t)bytes_received;
        *err = 0;
    }
    else
    {
        *err = 1;
    }

    return rv;
}

