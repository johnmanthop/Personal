#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <curses.h>

#include "ui.h"
#include "opcodes.h"
#include "client.h"
#include "sender_functions.h"
#include "reciever_functions.h"

pthread_t listener_thread, sender_thread;

struct general_client create_client_pair() 
{
    struct general_client cl_struct;

    cl_struct.state = IDLE;
	cl_struct.is_transfering = 0;

    cl_struct.client_d = socket(AF_INET, SOCK_STREAM, 0);
    if (cl_struct.client_d == -1) { 
        cl_struct.state = ERROR;
        return cl_struct;
    }

    cl_struct.server_internal.sin_family = AF_INET;
    cl_struct.server_internal.sin_addr.s_addr = INADDR_ANY;
    cl_struct.server_internal.sin_port = htons(8080);
    //server external is initialized only when the client tries to connect somewhere

    return cl_struct; 
}

void connect_to(struct general_client *cl, const char *ip, int port)
{
    cl->server_external.sin_addr.s_addr = inet_addr(ip);
    cl->server_external.sin_family = AF_INET;
    cl->server_external.sin_port = htons(port);
    cl->state = CONNECTED_TO;
    if (connect(cl->client_d, (struct sockaddr*)&cl->server_external, sizeof(cl->server_external)) < 0) {
        cl->state = ERROR;
        return;
    }

    //the server internal socket is not closed in case the user wants to change role in the future
}

void bind_as_server(struct general_client *cl)
{
    if (bind(cl->client_d, (struct sockaddr*)&cl->server_internal, sizeof(cl->server_internal)) < 0) {
        cl->state = ERROR;
        return;
    }
    cl->state = BOUND;
}

void listen_as_server(struct general_client *cl)
{
    if (listen(cl->client_d, 1) == -1) {
        cl->state = ERROR;
        return;
    }
    cl->state = LISTENING;
}

void accept_as_server(struct general_client *cl)
{
    int size = sizeof(struct sockaddr_in);
    cl->accepted_d = accept(cl->client_d, (struct sockaddr*)&cl->server_external, (socklen_t*)&size);
    if (cl->accepted_d == -1) {
        cl->state = ERROR;
        return;
    }
    cl->state = CONNECTED_FROM;
}

int get_valid_socket(struct general_client client)
{
	if (client.state == CONNECTED_FROM) {
		return client.accepted_d;
	} else if (client.state == CONNECTED_TO) {
		return client.client_d;
	} else {
		return -1;
	}
}

void process_rec(struct general_client *client, const void *data)
{
	char *data8 = (char*)data; //hopefully the opcode byte we want
	
	if (data8[0] == REQUEST) {
		//send the file name and the file size
		recv_tr_req(client, data8 + 5, *((int*)(data8 + 1)));
	} else if (data8[0] == TEXT_DATA) {
		//send the text data
		recv_text(client, data8);
	}
}

void initialize_loop(struct general_client *client)
{	
	main_loop(client);
}

