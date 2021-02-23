#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <curses.h>

#include "ui.h"
#include "opcodes.h"
#include "client.h"
#include "reciever_functions.h"
#include "sender_functions.h"
#include "size_constants.h"

void send_text(struct general_client *client, char *text)
{
	//get appropriate descriptor
	int desc   = get_valid_socket(*client);
	char *data = malloc(sizeof(char) * TEXT_TRANSFER_SIZE);
	
	//ready up the data to be sent
	data[0] = TEXT_DATA;
	
	text[511] = 0; //For safety reasons limit to 512 bytes
	strcpy(data + 1, text); //copy the data
	//send
	send(desc, data, TEXT_TRANSFER_SIZE, 0);
	free(data);
}

static int normalize(int size, int limit)
{
	//does the same thing is reciever functions
	if (size >= limit) return limit;
	else 			   return size;
}

void send_file(struct general_client *client, const char *fname)
{	
	int   desc = get_valid_socket(*client);
	char *data = malloc(sizeof(char) * FILE_TRANSFER_SIZE);
	FILE *file;
	int size;
	int sent;
	
	file = fopen(fname, "rb");
	
	struct stat st;
	stat(fname, &st);
	size = st.st_size;
	
	data[0] = FILE_DATA;
	//more or less the same as reciever functions
	for (sent = 0; sent < size; sent += FILE_TRANSFER_SIZE - 1) {
		fread(data + 1, 1, normalize(size - sent, FILE_TRANSFER_SIZE - 1), file);
		send (desc, data, FILE_TRANSFER_SIZE, 0);
	}
	
	send_eof(client);
	
	free  (data);
	fclose(file);
}

void send_tr_req(struct general_client *client, const char *fname)
{
	int desc   = get_valid_socket(*client);
	char *data = malloc(sizeof(char) * TRANSFER_REQUEST_SIZE);
	char *file_err = malloc(sizeof(char) * 200);
	FILE *file;
	unsigned long long size;
	//ready up the file not found message just in case
	sprintf(file_err, "c\nFile '%s' not found\n", fname);
	
	cancel_reciever = 1;
	client->is_transfering = 1;

	file = fopen(fname, "rb");
	if (!file) {
		//if file is not to be found print the message, clean up and exit
		write_ui(&file_err);
		free(data);
		return;
	}
	struct stat st;
	stat(fname, &st);
	size = st.st_size;
	fclose(file);
	
	//ready up the data (1st byte is opcode, next 4 are the size and last is the name)
	data[0] = REQUEST;
	*((int*)(data + 1)) = size;
	strcpy(data + 5, fname);
	
	send(desc, data, TRANSFER_REQUEST_SIZE, 0);

	recv_resp(client, fname);
	
	free(data);
}

void send_resp(struct general_client *client, char ans, const char *fname, unsigned long long size)
{
	int desc   = get_valid_socket(*client);
	char *data = malloc(sizeof(char) * TRANSFER_RESPONSE_SIZE);
	
	data[0] = RESPOND;
	data[1] = (ans == 'y')?1:0;

	send(desc, data, TRANSFER_RESPONSE_SIZE, 0);
	
	if (ans == 'n') {
		//if the user declined restart the sender thread
		pthread_create(&sender_thread,  NULL, &sender_loop, (void*)client);
		client->is_transfering = 0;
	} else if (ans == 'y') {
		//otherwise recieve the file
		recv_file(client, fname, size);
	}
	
	free(data);
}

void send_close(struct general_client *client)
{
	int desc   = get_valid_socket(*client);
	char *data = malloc(sizeof(char) * CLOSE_CONNECTION_SIZE);
	
	data[0] = CLOSE;
	send(desc, data, CLOSE_CONNECTION_SIZE, 0);
	
	free(data);
}

void send_eof(struct general_client *client)
{
	int desc   = get_valid_socket(*client);
	char *data = malloc(sizeof(char) * EOF_SIZE);
	
	data[0] = EOFC;
	
	send(desc, data, EOF_SIZE, 0);
	
	free(data);
	pthread_create(&listener_thread,  NULL, &reciever_loop, (void*)client);
	client->is_transfering = 0;
}