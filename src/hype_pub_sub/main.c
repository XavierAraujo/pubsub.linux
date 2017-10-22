#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "hype_pub_sub/hype_pub_sub.h"
#include "../external/include/sha/sha1.h"

void test_subscribers_list();
void test_service_manager();

void print_hex_char_array(unsigned char* array, size_t len);
void print_subs_list(LinkedListElement* head);

byte EXAMPLE_ID1[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
byte EXAMPLE_ID2[] = "\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11";
byte EXAMPLE_ID3[] = "\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10";
byte EXAMPLE_ID4[] = "\x10\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09";

int main()
{
    char service[] = {"HypeCoffe"};
    unsigned char service_key[SHA1_BLOCK_SIZE];

    sha1_digest((const BYTE*) service, strlen(service), service_key);
    print_hex_char_array(service_key, SHA1_BLOCK_SIZE);

    Subscription* hSubs = hype_pub_sub_subscription_create(service, strlen(service), EXAMPLE_ID1);
    printf("Service name: %s\n", hSubs->service_name);
    print_hex_char_array(hSubs->service_key, SHA1_BLOCK_SIZE);
    hype_pub_sub_subscription_destroy(hSubs);

    //test_subscribers_list();

    test_service_manager();

    return 0;
}


void test_subscribers_list()
{
    LinkedListElement* subscribers = hype_pub_sub_list_subscribers_create();
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID1);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID2);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID3);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID4);
    printf("\nAdded id1, id2, id3, id4\n");
    print_subs_list(subscribers);


    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID3);
    printf("\nRemoved id3\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID3);
    printf("\nRemoved id3 again\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID4);
    printf("\nRemoved id4\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID1);
    printf("\nRemoved id1\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID2);
    printf("\nRemoved id2\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID4);
    printf("\nAdded id4\n");
    print_subs_list(subscribers);


    printf("\nAdded id1, id2, id3, id4\n");
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID1);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID2);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID3);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID4);
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_destroy(subscribers);
}

void test_service_manager()
{
    char service[] = {"HypeCoffe"};
    byte servKey[SHA1_BLOCK_SIZE];
    sha1_digest((const byte*) service, strlen(service), servKey);

    ServiceManager* servMan = hype_pub_sub_service_manager_create(servKey);

    printf("\nAdded servMan id2\n");
    hype_pub_sub_service_manager_add_subscriber(servMan,EXAMPLE_ID2);
    print_subs_list(servMan->subscribers);

    printf("\nAdded servMan id2\n");
    hype_pub_sub_service_manager_add_subscriber(servMan,EXAMPLE_ID2);
    print_subs_list(servMan->subscribers);


    printf("\nAdded servMan id1, id3\n");
    hype_pub_sub_service_manager_add_subscriber(servMan,EXAMPLE_ID1);
    hype_pub_sub_service_manager_add_subscriber(servMan,EXAMPLE_ID3);
    print_subs_list(servMan->subscribers);

    hype_pub_sub_service_manager_destroy(servMan);
}

void print_hex_char_array(unsigned char* array, size_t len)
{
    printf("Array: ");
    for(int i=0; i<len; i++)
        printf("%.2x", array[i]);

    printf("\n");
}

void print_subs_list(LinkedListElement* head)
{
    printf("SubscriberList: \n");
    if(head == NULL || head->data == NULL)
        return;

    LinkedListElement* current_subs = head;

    do
    {
        print_hex_char_array((byte *) current_subs->data, HYPE_ID_BYTE_SIZE);
        current_subs = current_subs->next;
    }
    while(current_subs != NULL);
}

