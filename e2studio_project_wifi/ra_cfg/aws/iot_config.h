/* generated configuration header file - do not edit */
#ifndef IOT_CONFIG_H_
#define IOT_CONFIG_H_
/* Include the common configuration file for FreeRTOS. */
#include <FreeRTOS.h>
#include "platform/iot_platform_types_freertos.h"

/* Build test code. */
#ifndef IOT_BUILD_TESTS
#define IOT_BUILD_TESTS    (0)
#endif

/* Logging puts function. */
#ifndef IotLogging_Puts
#define IotLogging_Puts( str )                 configPRINTF( ( "%s\r\n", str ) )
#endif

/* Enable asserts in libraries by default. */
#ifndef IOT_METRICS_ENABLE_ASSERTS
#define IOT_METRICS_ENABLE_ASSERTS         (1)
#endif
#ifndef IOT_CONTAINERS_ENABLE_ASSERTS
#define IOT_CONTAINERS_ENABLE_ASSERTS      (1)
#endif
#ifndef IOT_TASKPOOL_ENABLE_ASSERTS
#define IOT_TASKPOOL_ENABLE_ASSERTS        (1)
#endif
#ifndef IOT_MQTT_ENABLE_ASSERTS
#define IOT_MQTT_ENABLE_ASSERTS            (1)
#endif
#ifndef AWS_IOT_SHADOW_ENABLE_ASSERTS
#define AWS_IOT_SHADOW_ENABLE_ASSERTS      (1)
#endif
#ifndef AWS_IOT_DEFENDER_ENABLE_ASSERTS
#define AWS_IOT_DEFENDER_ENABLE_ASSERTS    (1)
#endif
#ifndef IOT_BLE_ENABLE_ASSERTS
#define IOT_BLE_ENABLE_ASSERTS             (1)
#endif

/* Assert functions. */
#ifndef IotMetrics_Assert
#define IotMetrics_Assert( expression )        configASSERT( expression )
#endif
#ifndef IotContainers_Assert
#define IotContainers_Assert( expression )     configASSERT( expression )
#endif
#ifndef IotTaskPool_Assert
#define IotTaskPool_Assert( expression )       configASSERT( expression )
#endif
#ifndef IotMqtt_Assert
#define IotMqtt_Assert( expression )           configASSERT( expression )
#endif
#ifndef AwsIotShadow_Assert
#define AwsIotShadow_Assert( expression )      configASSERT( expression )
#endif
#ifndef AwsIotDefender_Assert
#define AwsIotDefender_Assert( expression )    configASSERT( expression )
#endif
#ifndef IotBle_Assert
#define IotBle_Assert( expression )            configASSERT( expression )
#endif
#ifndef AWS_IOT_MQTT_ENABLE_METRICS
#define AWS_IOT_MQTT_ENABLE_METRICS            0
#endif

/* Control the usage of dynamic memory allocation. */
#ifndef IOT_STATIC_MEMORY_ONLY
#define IOT_STATIC_MEMORY_ONLY    (RA_NOT_DEFINED)
#endif

/* Memory allocation configuration. Note that these functions will not be affected
 * by IOT_STATIC_MEMORY_ONLY. */
#ifndef IotNetwork_Malloc
#define IotNetwork_Malloc    pvPortMalloc
#endif
#ifndef IotNetwork_Free
#define IotNetwork_Free      vPortFree
#endif
#ifndef IotThreads_Malloc
#define IotThreads_Malloc    pvPortMalloc
#endif
#ifndef IotThreads_Free
#define IotThreads_Free      vPortFree
#endif
#ifndef IotLogging_Malloc
#define IotLogging_Malloc    pvPortMalloc
#endif
#ifndef IotLogging_Free
#define IotLogging_Free      vPortFree
#endif
#ifndef IotBle_Malloc
#define IotBle_Malloc        pvPortMalloc
#endif
#ifndef IotBle_Free
#define IotBle_Free          vPortFree
#endif
/* #define IotLogging_StaticBufferSize */

/* Memory allocation function configuration for the MQTT and Defender library.
 * These libraries will be affected by IOT_STATIC_MEMORY_ONLY. */
#if IOT_STATIC_MEMORY_ONLY == 0
#ifndef IotMetrics_MallocTcpConnection
#define IotMetrics_MallocTcpConnection       pvPortMalloc
#endif
#ifndef IotMetrics_FreeTcpConnection
#define IotMetrics_FreeTcpConnection         vPortFree
#endif
#ifndef IotMetrics_MallocIpAddress
#define IotMetrics_MallocIpAddress           pvPortMalloc
#endif
#ifndef IotMetrics_FreeIpAddress
#define IotMetrics_FreeIpAddress             vPortFree
#endif

#ifndef IotTaskPool_MallocTaskPool
#define IotTaskPool_MallocTaskPool           pvPortMalloc
#endif
#ifndef IotTaskPool_FreeTaskPool
#define IotTaskPool_FreeTaskPool             vPortFree
#endif
#ifndef IotTaskPool_MallocJob
#define IotTaskPool_MallocJob                pvPortMalloc
#endif
#ifndef IotTaskPool_FreeJob
#define IotTaskPool_FreeJob                  vPortFree
#endif
#ifndef IotTaskPool_MallocTimerEvent
#define IotTaskPool_MallocTimerEvent         pvPortMalloc
#endif
#ifndef IotTaskPool_FreeTimerEvent
#define IotTaskPool_FreeTimerEvent           vPortFree
#endif

#ifndef IotMqtt_MallocConnection
#define IotMqtt_MallocConnection             pvPortMalloc
#endif
#ifndef IotMqtt_FreeConnection
#define IotMqtt_FreeConnection               vPortFree
#endif
#ifndef IotMqtt_MallocMessage
#define IotMqtt_MallocMessage                pvPortMalloc
#endif
#ifndef IotMqtt_FreeMessage
#define IotMqtt_FreeMessage                  vPortFree
#endif
#ifndef IotMqtt_MallocOperation
#define IotMqtt_MallocOperation              pvPortMalloc
#endif
#ifndef IotMqtt_FreeOperation
#define IotMqtt_FreeOperation                vPortFree
#endif
#ifndef IotMqtt_MallocSubscription
#define IotMqtt_MallocSubscription           pvPortMalloc
#endif
#ifndef IotMqtt_FreeSubscription
#define IotMqtt_FreeSubscription             vPortFree
#endif

#ifndef IotSerializer_MallocCborEncoder
#define IotSerializer_MallocCborEncoder      pvPortMalloc
#endif
#ifndef IotSerializer_FreeCborEncoder
#define IotSerializer_FreeCborEncoder        vPortFree
#endif
#ifndef IotSerializer_MallocCborParser
#define IotSerializer_MallocCborParser       pvPortMalloc
#endif
#ifndef IotSerializer_FreeCborParser
#define IotSerializer_FreeCborParser         vPortFree
#endif
#ifndef IotSerializer_MallocCborValue
#define IotSerializer_MallocCborValue        pvPortMalloc
#endif
#ifndef IotSerializer_FreeCborValue
#define IotSerializer_FreeCborValue          vPortFree
#endif
#ifndef IotSerializer_MallocDecoderObject
#define IotSerializer_MallocDecoderObject    pvPortMalloc
#endif
#ifndef IotSerializer_FreeDecoderObject
#define IotSerializer_FreeDecoderObject      vPortFree
#endif

#ifndef AwsIotShadow_MallocOperation
#define AwsIotShadow_MallocOperation         pvPortMalloc
#endif
#ifndef AwsIotShadow_FreeOperation
#define AwsIotShadow_FreeOperation           vPortFree
#endif
#ifndef AwsIotShadow_MallocString
#define AwsIotShadow_MallocString            pvPortMalloc
#endif
#ifndef AwsIotShadow_FreeString
#define AwsIotShadow_FreeString              vPortFree
#endif
#ifndef AwsIotShadow_MallocSubscription
#define AwsIotShadow_MallocSubscription      pvPortMalloc
#endif
#ifndef AwsIotShadow_FreeSubscription
#define AwsIotShadow_FreeSubscription        vPortFree
#endif

#ifndef AwsIotDefender_MallocReport
#define AwsIotDefender_MallocReport          pvPortMalloc
#endif
#ifndef AwsIotDefender_FreeReport
#define AwsIotDefender_FreeReport            vPortFree
#endif
#ifndef AwsIotDefender_MallocTopic
#define AwsIotDefender_MallocTopic           pvPortMalloc
#endif
#ifndef AwsIotDefender_FreeTopic
#define AwsIotDefender_FreeTopic             vPortFree
#endif
#endif /* if IOT_STATIC_MEMORY_ONLY == 0 */

/* Default platform thread stack size and priority. */
#ifndef IOT_THREAD_DEFAULT_STACK_SIZE
#define IOT_THREAD_DEFAULT_STACK_SIZE 512
#endif
#ifndef IOT_THREAD_DEFAULT_PRIORITY
#define IOT_THREAD_DEFAULT_PRIORITY 1
#endif

/* Platform network configuration. */
#ifndef IOT_NETWORK_RECEIVE_TASK_PRIORITY
#define IOT_NETWORK_RECEIVE_TASK_PRIORITY 0
#endif
#ifndef IOT_NETWORK_RECEIVE_TASK_STACK_SIZE
#define IOT_NETWORK_RECEIVE_TASK_STACK_SIZE 512
#endif

/* Platform and SDK name for AWS IoT MQTT metrics. Only used when
 * AWS_IOT_MQTT_ENABLE_METRICS is 1. */
#define IOT_SDK_NAME "FreeRTOS"
#ifndef configPLATFORM_NAME
#define configPLATFORM_NAME "Unknown"
#endif

#ifndef IOT_PLATFORM_NAME
#define IOT_PLATFORM_NAME    configPLATFORM_NAME
#endif

/* Cloud endpoint to which the device connects to. */
#ifndef IOT_CLOUD_ENDPOINT
#define IOT_CLOUD_ENDPOINT clientcredentialMQTT_BROKER_ENDPOINT
#endif

/**
 * @brief Unique identifier used to recognize a device by the cloud.
 * This could be SHA-256 of the device certificate.
 */
extern const char* getDeviceIdentifier(void);
#ifndef IOT_DEVICE_IDENTIFIER
#define IOT_DEVICE_IDENTIFIER getDeviceIdentifier()
#endif

/**
 * @brief Metrics emitted by the device.
 */
extern const char* getDeviceMetrics(void);
#ifndef AWS_IOT_METRICS_USERNAME
#define AWS_IOT_METRICS_USERNAME getDeviceMetrics()
#endif

/**
 * @brief Length of the metrics emitted by device.
 */
extern uint16_t getDeviceMetricsLength(void);
#ifndef AWS_IOT_METRICS_USERNAME_LENGTH
#define AWS_IOT_METRICS_USERNAME_LENGTH getDeviceMetricsLength()
#endif

/* Define the data type of metrics connection id as same as Socket_t in aws_secure_socket.h */
#ifndef IotMetricsConnectionId_t
#define IotMetricsConnectionId_t void *
#endif

/* Configuration for defender demo: set format to CBOR. */
#ifndef AWS_IOT_DEFENDER_FORMAT
#define AWS_IOT_DEFENDER_FORMAT AWS_IOT_DEFENDER_FORMAT_CBOR
#endif

/* Configuration for defender demo: use long tag for readable output. Please use short tag for the real application. */
#ifndef AWS_IOT_DEFENDER_USE_LONG_TAG
#define AWS_IOT_DEFENDER_USE_LONG_TAG (1)
#endif
#endif /* IOT_CONFIG_H_ */
