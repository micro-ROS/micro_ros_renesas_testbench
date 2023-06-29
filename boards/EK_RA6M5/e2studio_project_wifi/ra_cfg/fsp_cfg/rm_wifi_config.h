/* generated configuration header file - do not edit */
#ifndef RM_WIFI_CONFIG_H_
#define RM_WIFI_CONFIG_H_
#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif
#endif /* RM_WIFI_CONFIG_H_ */
