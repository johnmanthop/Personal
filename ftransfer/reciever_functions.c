#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <curses.h>
#include <unistd.h>

#include "ui.h"
#include "opcodes.h"
#include "client.h"
#include "reciever_functions.h"
#include "sender_functions.h"
#include "size_constants.h"


void handle_eof(struct general_client *client)
{
	//at eof restart the sender thread
	pthread_create(&sender_thread,  NULL, &sender_loop, (void*)client);
	client->is_transfering = 0;
}

void recv_text(struct general_client *client, char *text)
{
	char *buffer = malloc(sizeof(char) * TEXT_TRANSFER_SIZE);
	//copy the text to the buffer and print it
	sprintf(buffer, "t%s\n", text + 1);
	write_ui(&buffer);
	//wait for the writer to write the text to the window before freeing it
	usleep(100000);
	free(buffer);
}

void recv_tr_req(struct general_client *client, const char *fname, unsigned long long size)
{
	char ans = 0;
	char *lbuffer = malloc(sizeof(char) * 200);

	//close the sender thread
	cancel_sender = 1;
	client->is_transfering = 1;
	
	sprintf(lbuffer, "c\nAccept \"%s\" ? (y/n)\n", fname);
	write_ui(&lbuffer);
	
	do {//wait for answer
		read_ui(&ans);
	} while (ans != 'y' && ans != 'n');
	
	send_resp(client, ans, fname, size);
	free(lbuffer);
}

static int normalize(unsigned long long size, int limit)
{
	//normalizes the bytes to be read to the last amount of bytes to be read
	//ex: if a file is 515 kb and 512 are send at once then this function will normalize first to 512 and then to 3
	if (size >= limit) return limit;
	else 			   return size;
}

void recv_file(struct general_client *client, const char *fname, unsigned long long size)
{
	FILE *file;
	void *buffer;
	void *data;
	int recieved;
	char opcode;
	char *not_accepted_msg = "c\nTransfer not accepted\n";
	char *synch_err        = "c\nSynchronization error\n";

	
	if (!client->is_transfering) {
		write_ui(&not_accepted_msg);
		return;
	}
	
	file   = fopen(fname, "wb");
	buffer = malloc(sizeof(char) * FILE_TRANSFER_SIZE);
	
	for (recieved = 0; recieved < size; recieved += FILE_TRANSFER_SIZE - 1) {
		recv(get_valid_socket(*client), buffer, FILE_TRANSFER_SIZE, 0);
		data   =  (char*)buffer + 1;
		opcode = *(char*)buffer;
		//get data and opcode
		//if opcode is not file_data something is wrong (happens sometimes)
		if (opcode != FILE_DATA) {
			write_ui(&synch_err);
		}
		//write the data to the file
		fwrite(data, 1, normalize(size - recieved, FILE_TRANSFER_SIZE - 1), file);
	}
	//do eof
	handle_eof(client);
	
	free(buffer);
	fclose(file);
}

void recv_resp(struct general_client *client, const char *fname)
{
	void *buffer;
	char data;
	char opcode;
	char *syncer_msg  = "c\nSynchronization error\n";
	char *accept_msg  = "c\nTransfer Accepted\n";
	char *deny_msg    = "c\nTransfer Denied\n";
	char *corr_msg    = "c\nCorrupt data\n";
	
	buffer = malloc(sizeof(char) * TRANSFER_RESPONSE_SIZE);
	//recieve the response from the partner program
	recv(get_valid_socket(*client), buffer, TRANSFER_RESPONSE_SIZE, 0);
	data   = *((char*)buffer + 1);
	opcode =  *(char*)buffer;
	
	
	if (opcode != RESPOND) {
		//if response is not what we want then it is a synch error
		write_ui(&syncer_msg);
		return;
	}
	//if answer is no
	if (data == 0) {
		//print the message and restart the reciever thread
		write_ui(&deny_msg);
		pthread_create(&listener_thread, NULL, &reciever_loop, (void*)client);
		client->is_transfering = 0;
		
	} else if (data == 1) {
		//else print the message and send the file
		write_ui(&accept_msg);
		send_file(client, fname);
	} else {
		//otherwise something is wrong
		write_ui(&corr_msg);
	}
}

