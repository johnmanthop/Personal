C program to send and recieve files and messages between two clients   
Press 0 at the start to act as server   
Press 1 at the start to act as client (that is connect to some server)   

Right now only localhost ip works

Use \ to switch between text and file modes   
At file mode type the name of the file and press enter   
At text mode type yout message and press enter   

There is room for a lot of improvment but I don't have time right now   

Note to self: Never use ncurses with multi thread programming   
Also compile with ncurses and pthread...   

Known bug: some times (at big files) there is a synchronization error message   
23/2/21
