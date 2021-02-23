#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <curses.h>

#include "client.h"
#include "ui.h"

/**
 * todo:
 * send&recieve file functionality
 */

void ertest(struct general_client cl) 
{//generic error test
    if (cl.state == ERROR) {
        printf("Error\n\n");
    }
}

int main()
{	
	struct general_client client = create_client_pair();
    int c;
    scanf("%d", &c);
	
    if (c == 0) {
        ertest(client);

        bind_as_server  (&client);
        ertest(client);

        listen_as_server(&client);
        ertest(client);

        accept_as_server(&client);
        ertest(client);
		
        initialize_loop (&client);
    } else {
        ertest(client);
        connect_to(&client, "127.0.0.1", 8080);
		initialize_loop(&client);
    }
	
	close(client.client_d);
	close(client.accepted_d);
	pthread_exit(NULL);
	
	endwin();
	
    return 0; 
}