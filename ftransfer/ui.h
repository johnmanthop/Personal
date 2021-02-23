#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <curses.h>

#define SEND_COMMAND_BIND 's'
#define CHANGE_MODE_BIND  ';'
#define LINE_END_BIND     '\n'

#define UI_INPUT_IDLE         -1
#define UI_INPUT_REC          -2

#define UI_OUTPUT_IDLE        'i'
#define UI_OUTPUT_COMMAND     'c'
#define UI_OUTPUT_TEXT        't'

#define BUF_SIZE 1024

struct input_Q {
	char q_array[32]; //queue can handle up to 32 character inputs
	unsigned max;
	unsigned size;
};

enum UI_STATE { FACUM, FSEND, TACUM, TSEND, INVLD };
//text accumulate (data), text send
extern enum UI_STATE state;
//Models kind of a finite state machine

void main_loop();

extern WINDOW *com_window;
extern WINDOW *text_window;
extern WINDOW *current_window;

extern struct queue input_q;
extern struct queue output_q;

extern pthread_mutex_t output_lock;
extern pthread_mutex_t input_lock;

extern char cancel_sender;
extern char cancel_reciever;

void sender_loop  (void *args);
void reciever_loop(void *args);

void read_ui (char  *data);
void write_ui(char **data);

#endif