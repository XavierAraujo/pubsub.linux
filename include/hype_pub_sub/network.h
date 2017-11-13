
#ifndef HPB_NETWORK_H_INCLUDED_
#define HPB_NETWORK_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>

#include "sha/sha1.h"
#include "list_clients.h"
#include "constants.h"
#include "binary_utils.h"


typedef struct HpbNetwork_
{
    HpbClient *own_client;
    ListClients *network_clients;
} HpbNetwork;

HpbNetwork *hpb_network_create();

byte *hpb_network_get_service_manager_id(HpbNetwork *net, byte service_key[SHA1_BLOCK_SIZE]);

int hpb_network_update_clients(HpbNetwork *net);

bool hpb_network_is_client_online(HpbNetwork *net, byte client_id[HPB_ID_BYTE_SIZE]);

byte *hpb_network_get_own_id();

void hpb_network_destroy(HpbNetwork **net);

#endif /* HPB_NETWORK_H_INCLUDED_ */
