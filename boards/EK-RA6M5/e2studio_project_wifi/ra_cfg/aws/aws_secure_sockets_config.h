/* generated configuration header file - do not edit */
#ifndef AWS_SECURE_SOCKETS_CONFIG_H_
#define AWS_SECURE_SOCKETS_CONFIG_H_
#ifndef AWS_INC_SECURE_SOCKETS_CONFIG_H_
#define AWS_INC_SECURE_SOCKETS_CONFIG_H_

/**
 * @brief Byte order of the target MCU must be defined.
 *
 * Valid values are pdLITTLE_ENDIAN and pdBIG_ENDIAN.
 */
#define socketsconfigBYTE_ORDER pdLITTLE_ENDIAN

/**
 * @brief Default socket send timeout.
 *
 * The user can change the send timeout for a socket using the SOCKETS_SetSockOpt API
 * with the SOCKETS_SO_SNDTIMEO option.
 */
#ifndef socketsconfigDEFAULT_SEND_TIMEOUT
#define socketsconfigDEFAULT_SEND_TIMEOUT    (10000)
#endif

/**
 * @brief Default socket receive timeout.
 *
 * The user can change the receive timeout for a socket using the SOCKETS_SetSockOpt API
 * with the SOCKETS_SO_RCVTIMEO option.
 */
#ifndef socketsconfigDEFAULT_RECV_TIMEOUT
#define socketsconfigDEFAULT_RECV_TIMEOUT    (10000)
#endif

/**
 * @brief By default, metircs of secure socket is disabled.
 *
 */
#ifndef AWS_IOT_SECURE_SOCKETS_METRICS_ENABLED
#define AWS_IOT_SECURE_SOCKETS_METRICS_ENABLED    (0)
#endif

#endif /* AWS_INC_SECURE_SOCKETS_CONFIG_H_ */
#endif /* AWS_SECURE_SOCKETS_CONFIG_H_ */
