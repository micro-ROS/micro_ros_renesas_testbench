/* generated configuration header file - do not edit */
#ifndef AWS_WIFI_CONFIG_H_
#define AWS_WIFI_CONFIG_H_
/**
 * @brief Maximum number of sockets that can be created simultaneously.
 */
#define wificonfigMAX_SOCKETS                   1

/**
 * @brief Maximum number of connection retries.
 */
#define wificonfigNUM_CONNECTION_RETRY          3

/**
 * @brief Max number of network profiles stored in Non Volatile memory,
 * set to zero if not supported.
 */
#define wificonfigMAX_NETWORK_PROFILES          0

/**
 * @brief Max SSID length
 */
#define wificonfigMAX_SSID_LEN                  32

/**
 * @brief Max BSSID length
 */
#define wificonfigMAX_BSSID_LEN                 6

/**
 * @brief Max passphrase length
 */
#define wificonfigMAX_PASSPHRASE_LEN            32

/**
 * @brief WiFi semaphore timeout
 */
#define wificonfigMAX_SEMAPHORE_WAIT_TIME_MS    60000

/* ACCESS POINT MODE IS NOT CURRENTLY SUPPORTED. */

/**
 * @brief Maximum number of connected station in Access Point mode.
 */
#define wificonfigMAX_CONNECTED_STATIONS        (4)

/**
 * @brief Soft Access point SSID
 */
#define wificonfigACCESS_POINT_SSID_PREFIX      ("Enter SSID for Soft AP")

/**
 * @brief Soft Access point Passkey
 */
#define wificonfigACCESS_POINT_PASSKEY          ("Enter Password for Soft AP")

/**
 * @brief Soft Access point Channel
 */
#define wificonfigACCESS_POINT_CHANNEL          (11)

/**
 * @brief Soft Access point security
 * WPA2 Security, see WIFISecurity_t
 * other values are - eWiFiSecurityOpen, eWiFiSecurityWEP, eWiFiSecurityWPA
 */
#define wificonfigACCESS_POINT_SECURITY         (eWiFiSecurityWPA2)

/**
 * @brief Max number of WEP keys supported.
 */

#define wificonfigMAX_WEPKEYS                   (1)

/**
 * @brief Max WEP key length
 */
#define wificonfigMAX_WEPKEY_LEN                (1)
#endif /* AWS_WIFI_CONFIG_H_ */
