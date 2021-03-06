
#ifndef HPB_H_INCLUDED_
#define HPB_H_INCLUDED_

#include <stdlib.h>
#include <stdio.h>

#include "hpb_service_managers_list.h"
#include "hpb_subscriptions_list.h"
#include "hpb_network.h"
#include "hpb_protocol.h"

/**
 * @brief This struct represents a HypePubSub application.
 */
typedef struct HypePubSub_
{
    HpbSubscriptionsList *own_subscriptions; /**< List of subscriptions of this HypePubSub application. */
    HpbServiceManagersList *managed_services; /**< List of services managed by this HypePubSub application. */
    HpbNetwork *network; /**< Pointer to the network manager of this HypePubSub application. */
} HypePubSub;

/**
 * @brief This method returns the HypePubSub singleton. If the singleton was not previously
 *        created this methods creates it.
 * @return Returns a pointer to the HypePubSub singleton.
 */
HypePubSub *hpb_get();

/**
 * @brief Obtains the Hype client responsible for a given service through the network manager
 *        and it uses the protocol manager to send a subscribe request to that Hype client.
 * @param service_name Name of the service to be subscribed.
 * @return Return 0 in case of success and -1 otherwise.
 */
int hpb_issue_subscribe_req(char *service_name);

/**
 * @brief Obtains the Hype client responsible for a given service through the network manager
 *        and it uses the protocol manager to send a unsubscribe request to that Hype client.
 * @param service_name Name of the service to be unsubscribed.
 * @return Return 0 in case of success and -1 otherwise.
 */
int hpb_issue_unsubscribe_req(char *service_name);

/**
 * @brief Obtains the Hype client responsible for a given service through the network manager
 *        and it uses the protocol manager to send a publish request to that Hype client.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_name Name of the service in which to publish.
 * @param msg Pointer to the message to be published.
 * @param msg_length Lenght of the message to be published
 * @return Return 0 in case of success and -1 otherwise.
 */
int hpb_issue_publish_req(char *service_name, char *msg, size_t msg_length);

/**
 * @brief Processes a subscribe request to a given service. It adds the ID of the Hype client that sent the
 *        request to the list of the subscribers of the specified service. If the service does not exist in
 *        the list of managed services, it is added.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_key Key of the service to be subscribed.
 * @param requester_client_id Hype ID of the client that sent the subscribe message.
 * @return Returns 0 in case of success and < 0 otherwise.
 */
int hpb_process_subscribe_req(HLByte service_key[], HypeInstance * instance);

/**
 * @brief Processes an unsubscribe request to a given service. It removes the ID of the Hype client that sent
 *        the request from the list of the subscribers of the specified service. If the service does not exist
 *        in the list of managed services, nothing is done.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_key Key of the service to be unsubscribed.
 * @param requester_client_id Hype ID of the client that sent the unsubscribe message.
 * @return Returns 0 in case of success and < 0 otherwise.
 */
int hpb_process_unsubscribe_req(HLByte service_key[], HypeInstance * instance);

/**
 * @brief Processes a publish request to a given service. It sends the message to all the subscribers of the
 *        specified service. If the service does not exist in the list of managed services nothing is done.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_key Key of the service in which to publish.
 * @param msg Message to be sent.
 * @param msg_length Length of the message to be sent.
 * @return Returns 0 in case of success and < 0 otherwise.
 */
int hpb_process_publish_req(HLByte service_key[], char *msg, size_t msg_length);

/**
 * @brief Process an info message received.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_key Key of the service to which the message belongs.
 * @param msg Message received.
 * @param msg_length Length of the received message.
 * @return Returns 0 in case of success and < 0 otherwise.
 */
int hpb_process_info_msg(HLByte service_key[], char *msg, size_t msg_length);

/**
 * @brief This method is called when a Hype instance is resolved. Its
 *        purpose is to check if the new client has a key closer to
 *        the key of any of the services managed by this client. If this
 *        happens the new instance will be responsible for managing that
 *        service and so we can remove it from the list of managed
 *        services of this client.
 * @return
 */
int hpb_update_managed_services();

/**
 * @brief This method is called when a Hype instance is lost. Its purpose
 *        is to iterate all the services that this client manages and
 *        remove the lost instance from the list of subscribers of each
 *        one. This avoids to propagate messages to instances that
 *        are no longer reachable.
 * @param instance Instance that was lost.
 */
void hpb_remove_subscriptions_from_lost_instance(HypeInstance * instance);

/**
 * @brief This method is called when a Hype instance is lost or found. Its
 *        purpose is to review the list of subscriptions of this client to
 *        analyze if the service will be managed by a new client. If this
 *        happens a subscribe request will be issued again to the new manager.
 * @param hpb Pointer to the HypePubSub application.
 * @return Returns -1 if the HypePubSub application is NULL and 0 otherwise.
 */
int hpb_update_own_subscriptions();

/**
 * @brief Deallocates the space previously allocated for the HypePubSub singleton.
 *        This method is specially useful to clear previous states for unit tests.
 */
void hpb_destroy();

#endif /* HPB_H_INCLUDED_ */
