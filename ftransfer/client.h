#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

enum CONN_STATE {IDLE, BOUND, LISTENING, CONNECTED_FROM, CONNECTED_TO, ERROR};

struct general_client
//Represents a terminal that has not yet become a client or server in a p2p connection
{
    int client_d;
    int accepted_d;
    
    struct sockaddr_in server_external; //Refers to the server when the client stays a client 
    struct sockaddr_in server_internal; //Refers to the server when the client becomes a server
	
	char is_transfering;

    enum CONN_STATE state;
};

struct connected_client
{ //Represents a terminal that has concluded as a client or server in a p2p connection
	int client_d;
};

extern char is_reciever_paused;
extern char is_sender_paused;

extern pthread_t listener_thread;
extern pthread_t sender_thread;

struct general_client create_client_pair();

void connect_to      (struct general_client *client_struct, const char *ip, int port);
void bind_as_server  (struct general_client *client_struct);
void listen_as_server(struct general_client *client_struct);
void accept_as_server(struct general_client *client_struct);
void initialize_loop (struct general_client *client);

void process_rec    (struct general_client *client, const void *data);
int get_valid_socket(struct general_client  client);

void start_request_listener(void *threadpar);
void start_command_listener(void *threadpar);

void clear_buffer();

#endif