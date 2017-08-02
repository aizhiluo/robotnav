// THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
// BY HAND!!
//
// Generated by lcm-gen

#ifndef _srcl_lcm_msgs_UAVTrajectoryPoint_t_h
#define _srcl_lcm_msgs_UAVTrajectoryPoint_t_h

#include <stdint.h>
#include <stdlib.h>
#include <lcm/lcm_coretypes.h>
#include <lcm/lcm.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _srcl_lcm_msgs_UAVTrajectoryPoint_t srcl_lcm_msgs_UAVTrajectoryPoint_t;
struct _srcl_lcm_msgs_UAVTrajectoryPoint_t
{
    int8_t     point_empty;
    float      positions[3];
    float      velocities[3];
    float      accelerations[3];
    float      jerks[3];
    float      yaw;
    float      yaw_rate;
    int64_t    duration;
};

/**
 * Create a deep copy of a srcl_lcm_msgs_UAVTrajectoryPoint_t.
 * When no longer needed, destroy it with srcl_lcm_msgs_UAVTrajectoryPoint_t_destroy()
 */
srcl_lcm_msgs_UAVTrajectoryPoint_t* srcl_lcm_msgs_UAVTrajectoryPoint_t_copy(const srcl_lcm_msgs_UAVTrajectoryPoint_t* to_copy);

/**
 * Destroy an instance of srcl_lcm_msgs_UAVTrajectoryPoint_t created by srcl_lcm_msgs_UAVTrajectoryPoint_t_copy()
 */
void srcl_lcm_msgs_UAVTrajectoryPoint_t_destroy(srcl_lcm_msgs_UAVTrajectoryPoint_t* to_destroy);

/**
 * Identifies a single subscription.  This is an opaque data type.
 */
typedef struct _srcl_lcm_msgs_UAVTrajectoryPoint_t_subscription_t srcl_lcm_msgs_UAVTrajectoryPoint_t_subscription_t;

/**
 * Prototype for a callback function invoked when a message of type
 * srcl_lcm_msgs_UAVTrajectoryPoint_t is received.
 */
typedef void(*srcl_lcm_msgs_UAVTrajectoryPoint_t_handler_t)(const lcm_recv_buf_t *rbuf,
             const char *channel, const srcl_lcm_msgs_UAVTrajectoryPoint_t *msg, void *userdata);

/**
 * Publish a message of type srcl_lcm_msgs_UAVTrajectoryPoint_t using LCM.
 *
 * @param lcm The LCM instance to publish with.
 * @param channel The channel to publish on.
 * @param msg The message to publish.
 * @return 0 on success, <0 on error.  Success means LCM has transferred
 * responsibility of the message data to the OS.
 */
int srcl_lcm_msgs_UAVTrajectoryPoint_t_publish(lcm_t *lcm, const char *channel, const srcl_lcm_msgs_UAVTrajectoryPoint_t *msg);

/**
 * Subscribe to messages of type srcl_lcm_msgs_UAVTrajectoryPoint_t using LCM.
 *
 * @param lcm The LCM instance to subscribe with.
 * @param channel The channel to subscribe to.
 * @param handler The callback function invoked by LCM when a message is received.
 *                This function is invoked by LCM during calls to lcm_handle() and
 *                lcm_handle_timeout().
 * @param userdata An opaque pointer passed to @p handler when it is invoked.
 * @return 0 on success, <0 if an error occured
 */
srcl_lcm_msgs_UAVTrajectoryPoint_t_subscription_t* srcl_lcm_msgs_UAVTrajectoryPoint_t_subscribe(lcm_t *lcm, const char *channel, srcl_lcm_msgs_UAVTrajectoryPoint_t_handler_t handler, void *userdata);

/**
 * Removes and destroys a subscription created by srcl_lcm_msgs_UAVTrajectoryPoint_t_subscribe()
 */
int srcl_lcm_msgs_UAVTrajectoryPoint_t_unsubscribe(lcm_t *lcm, srcl_lcm_msgs_UAVTrajectoryPoint_t_subscription_t* hid);

/**
 * Sets the queue capacity for a subscription.
 * Some LCM providers (e.g., the default multicast provider) are implemented
 * using a background receive thread that constantly revceives messages from
 * the network.  As these messages are received, they are buffered on
 * per-subscription queues until dispatched by lcm_handle().  This function
 * how many messages are queued before dropping messages.
 *
 * @param subs the subscription to modify.
 * @param num_messages The maximum number of messages to queue
 *  on the subscription.
 * @return 0 on success, <0 if an error occured
 */
int srcl_lcm_msgs_UAVTrajectoryPoint_t_subscription_set_queue_capacity(srcl_lcm_msgs_UAVTrajectoryPoint_t_subscription_t* subs,
                              int num_messages);

/**
 * Encode a message of type srcl_lcm_msgs_UAVTrajectoryPoint_t into binary form.
 *
 * @param buf The output buffer.
 * @param offset Encoding starts at this byte offset into @p buf.
 * @param maxlen Maximum number of bytes to write.  This should generally
 *               be equal to srcl_lcm_msgs_UAVTrajectoryPoint_t_encoded_size().
 * @param msg The message to encode.
 * @return The number of bytes encoded, or <0 if an error occured.
 */
int srcl_lcm_msgs_UAVTrajectoryPoint_t_encode(void *buf, int offset, int maxlen, const srcl_lcm_msgs_UAVTrajectoryPoint_t *p);

/**
 * Decode a message of type srcl_lcm_msgs_UAVTrajectoryPoint_t from binary form.
 * When decoding messages containing strings or variable-length arrays, this
 * function may allocate memory.  When finished with the decoded message,
 * release allocated resources with srcl_lcm_msgs_UAVTrajectoryPoint_t_decode_cleanup().
 *
 * @param buf The buffer containing the encoded message
 * @param offset The byte offset into @p buf where the encoded message starts.
 * @param maxlen The maximum number of bytes to read while decoding.
 * @param msg Output parameter where the decoded message is stored
 * @return The number of bytes decoded, or <0 if an error occured.
 */
int srcl_lcm_msgs_UAVTrajectoryPoint_t_decode(const void *buf, int offset, int maxlen, srcl_lcm_msgs_UAVTrajectoryPoint_t *msg);

/**
 * Release resources allocated by srcl_lcm_msgs_UAVTrajectoryPoint_t_decode()
 * @return 0
 */
int srcl_lcm_msgs_UAVTrajectoryPoint_t_decode_cleanup(srcl_lcm_msgs_UAVTrajectoryPoint_t *p);

/**
 * Check how many bytes are required to encode a message of type srcl_lcm_msgs_UAVTrajectoryPoint_t
 */
int srcl_lcm_msgs_UAVTrajectoryPoint_t_encoded_size(const srcl_lcm_msgs_UAVTrajectoryPoint_t *p);

// LCM support functions. Users should not call these
int64_t __srcl_lcm_msgs_UAVTrajectoryPoint_t_get_hash(void);
uint64_t __srcl_lcm_msgs_UAVTrajectoryPoint_t_hash_recursive(const __lcm_hash_ptr *p);
int __srcl_lcm_msgs_UAVTrajectoryPoint_t_encode_array(void *buf, int offset, int maxlen, const srcl_lcm_msgs_UAVTrajectoryPoint_t *p, int elements);
int __srcl_lcm_msgs_UAVTrajectoryPoint_t_decode_array(const void *buf, int offset, int maxlen, srcl_lcm_msgs_UAVTrajectoryPoint_t *p, int elements);
int __srcl_lcm_msgs_UAVTrajectoryPoint_t_decode_array_cleanup(srcl_lcm_msgs_UAVTrajectoryPoint_t *p, int elements);
int __srcl_lcm_msgs_UAVTrajectoryPoint_t_encoded_array_size(const srcl_lcm_msgs_UAVTrajectoryPoint_t *p, int elements);
int __srcl_lcm_msgs_UAVTrajectoryPoint_t_clone_array(const srcl_lcm_msgs_UAVTrajectoryPoint_t *p, srcl_lcm_msgs_UAVTrajectoryPoint_t *q, int elements);

#ifdef __cplusplus
}
#endif

#endif
