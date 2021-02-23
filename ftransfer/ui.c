#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"
#include "client.h"
#include "size_constants.h"
#include "sender_functions.h"
#include "queue.h"

void clear_buffer(char *buffer, int size)
{
	//clean up function
	for (int i = 0; i < size; ++i) buffer[i] = 0;
}

enum UI_STATE state = FACUM;
//state transition function for the automaton controlling the state
enum UI_STATE transition(enum UI_STATE current, char input)
{
	if (state == FACUM) {
		
		if      (input == '\n')		return FSEND;
		else if (input == '\\')     return TACUM;
		else 						return FACUM;
		
	} else if (state == FSEND) {	
		if      (input == '\\')     return TACUM;
		else 						return FACUM;
	} else if (state == TACUM) {
		
		if      (input == '\n')		return TSEND;
		else if (input == '\\')		return FACUM;
		else 						return TACUM;
		
	} else if (state == TSEND) {	
		if      (input == '\\')     return FACUM;
		else						return TACUM;
	} else if (state == INVLD) {	return INVLD; //should never be reached
	}
	return INVLD;
}

pthread_mutex_t output_lock;
pthread_mutex_t input_lock;

struct queue input_q;
struct queue output_q;

char cancel_sender;
char cancel_reciever = 0;

void ui_loop()
{
	WINDOW *com_window;
	WINDOW *text_window;
	
	input_q  = init_Q(sizeof(char));
	output_q = init_Q(sizeof(char*));
	
	initscr ();
	cbreak  ();
	noecho  ();
	nodelay (stdscr, TRUE);
	keypad  (stdscr, TRUE);
	curs_set(FALSE);
	
	com_window  = newwin(20, 35, 2, 1);
	text_window = newwin(20, 35, 2, 40);
	
	if (com_window == NULL || text_window == NULL) {
		printf("Error creating interface\n");
		return;
	}
	
	char input   = -1;
	char **msg_p = NULL;
	char  *msg   = NULL;
	
	for (;;) {
		//at each loop print the string at the top of the output q
		pthread_mutex_lock(&output_lock);
			msg_p = (char**)Q_pop_start(&output_q);
			msg   = *msg_p;
			free(msg_p);
		pthread_mutex_unlock(&output_lock);
	
		
		if (msg != NULL) {
			wprintw((msg[0] == UI_OUTPUT_COMMAND)?com_window:text_window, msg + 1);
		}
		
		if ((input = getch()) != ERR) { 
			//if the user has pressed anything at it at the input q
			pthread_mutex_lock(&input_lock);
			
				if (Q_add_end(&input_q, &input) == NULL) {
					wprintw(text_window, "error");
				}
				
			pthread_mutex_unlock(&input_lock);
		}
		
		wrefresh(com_window);
		wrefresh(text_window);
	}
} 

void sender_loop(void *args)
{
	struct general_client *client = (struct general_client*)args;
	
	unsigned buffer_counter = 0;
	char inp         = 0;
	char *in_buffer  = malloc(sizeof(char) * BUF_SIZE);
	char *out_buffer = malloc(sizeof(char) * 3);
	char *send_msg   = "c\nAttempting to send file...\n";
	
	cancel_sender = 0;
	for (;;) {
		//if the cancel flag is on clean up and exit
		if (cancel_sender) {
			free(in_buffer);
			free(out_buffer);
			return;
		}
		//otherwise read the top of the input q
		read_ui(&inp);
		if (inp == 0) continue;
		//if it is not empty go on
		//save the old state to be compared to the new state
		enum UI_STATE old = state;
		state = transition(state, inp);
		//if the states have changed without any sending clean up the buffer before going on
		//(if any sending has been done the buffer is cleared anyway)
		if ((old == FACUM && state == TACUM) || (old == TACUM && state == FACUM)) {
			clear_buffer(in_buffer, BUF_SIZE);
			buffer_counter = 0;
		}
	
		if (state == FACUM || state == TACUM) {
			//if the state is at accumulate then accumulate the input
			if (inp != '\\') in_buffer[buffer_counter++] = inp;
			
		} else if (state == FSEND) {
			//if the state is file send then print the message and start the send file chain
			write_ui(&send_msg);
			
			send_tr_req(client, in_buffer);
			
			clear_buffer(in_buffer, BUF_SIZE);
			buffer_counter = 0;
			
		} else if (state == TSEND) {
			//the same for text send
			send_text(client, in_buffer);
			
			clear_buffer(in_buffer, BUF_SIZE);
			buffer_counter = 0;
			
		}
		if (inp != '\\') 
			//if the input is not a mode change print it to the console as well
			if (state == FACUM || state == FSEND) {
				out_buffer[0] = UI_OUTPUT_COMMAND;
			} else if (state == TACUM || state == TSEND) {
				out_buffer[0] = UI_OUTPUT_TEXT;
			} 
			out_buffer[1] = inp;
			out_buffer[2] = 0;
			write_ui(&out_buffer);
		}
	}
	
	free(out_buffer);
	free(in_buffer);
}

void reciever_loop(void *args)
{
	struct general_client *client = (struct general_client*)args;
	
	char *generic_error  = "c\nError recieving data\n";
	char *overflow_error = "c\nSize overflow\n";
	void *buffer         = malloc(MAX_RECIEVABLE_SIZE);
	int desc             = get_valid_socket(*client);
	int size;

	cancel_reciever = 0;

	for (;;) {
		//if the cancel flag is set clean up and exit
		if (cancel_reciever) {
			free(buffer);
			return;
		
		//recieve data and pass it to process_rec function
		if ((size = recv(desc, buffer, MAX_RECIEVABLE_SIZE, 0)) < 0) {
			write_ui(&generic_error);
			continue;
		} else {
			if (size > MAX_RECIEVABLE_SIZE) {
				write_ui(&overflow_error);
				continue;
			}
			process_rec(client, buffer);
		}
	}
}

void main_loop(struct general_client *client) 
{
	pthread_t ui_thread;
	
	pthread_mutex_init(&output_lock, NULL);
	pthread_mutex_init(&input_lock,  NULL);
	
	pthread_create(&ui_thread,       NULL, &ui_loop, NULL);
	pthread_create(&listener_thread, NULL, &reciever_loop, (void*)client);
	pthread_create(&sender_thread,   NULL, &sender_loop,   (void*)client);

	for (;;) {  }
	
	pthread_mutex_destroy(&output_lock);
	pthread_mutex_destroy(&input_lock);
}

void write_ui(char **data)
{
	//thread safe function to add something at the output q
	pthread_mutex_lock(&output_lock);
		Q_add_end(&output_q, data);
	pthread_mutex_unlock(&output_lock);
}

void read_ui(char *data)
{
	//thread safe function to get the top of the input q
	pthread_mutex_lock(&input_lock);
		char *temp = (char*)Q_pop_start(&input_q);
		*data = *temp;
		free(temp);
	pthread_mutex_unlock(&input_lock);
}
