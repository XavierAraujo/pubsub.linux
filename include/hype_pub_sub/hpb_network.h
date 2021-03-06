
#ifndef HPB_NETWORK_H_INCLUDED_
#define HPB_NETWORK_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>

#include "sha/sha1.h"
#include "hpb_clients_list.h"
#include "hpb_constants.h"
#include "binary_utils.h"


/**
 * @brief This struct represents an HpbNetwork manager.
 */
typedef struct HpbNetwork_
{
    HpbClient *own_client; /**< Pointer to the HpbClient of this application */
    HpbClientsList *network_clients; /**< Pointer to a HpbClientsList containing all the Hype devices found in the network */
} HpbNetwork;

/**
 * @brief Allocates space for a HpbNetwork struct.
 * @param own_instance Instance of this HpbClient.
 * @return Returns a pointer to the created struct or NULL if the space could not be allocated.
 */
HpbNetwork *hpb_network_create(HypeInstance *own_instance);

/**
 * @brief Returns the ID of the hype device which is responsible for a given service. The hype device with the key closest to
 *        to the service key is responsible for that service.
 * @param net Pointer to the HpbNetwork.
 * @param service_key Key of the service to be analyzed.
 * @return Returns a byte array containing the ID of the hype device responsible for the service.
 */
HypeInstance *hpb_network_get_service_manager_id(HpbNetwork *net, HLByte service_key[SHA1_BLOCK_SIZE]);

/**
 * @brief Updates the list of known hype devices according to the InstanceFound and InstanceLost.
 * @param net Pointer to the HpbNetwork.
 * @return
 */
void hpb_network_update_clients(HpbNetwork *net);

/**
 * @brief Get the ID of this HpbClient.
 * @return Returns a byte array containing the ID of this HpbClient.
 */
HLByte *hpb_network_get_own_id();

/**
 * @brief Deallocates the space previously allocated for the given HpbNetwork struct.
 * @param net Pointer to the pointer of the HpbNetwork struct to be deallocated.
 */
void hpb_network_destroy(HpbNetwork **net);

#endif /* HPB_NETWORK_H_INCLUDED_ */
