#ifndef RECIEVER_FUNCTIONS_H_DEFINED
#define RECIEVER_FUNCTIONS_H_DEFINED

#include "client.h"

void recv_text  (struct general_client *client, char *text);
void recv_tr_req(struct general_client *client, const char *fname, unsigned long long size);
void recv_resp  (struct general_client *client, const char *fname);

#endif 