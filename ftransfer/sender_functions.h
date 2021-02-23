#ifndef SENDER_FUNCTIONS_H_DEFINED
#define SENDER_FUNCTIONS_H_DEFINED

void send_text  (struct general_client *client, char *text);
void send_resp  (struct general_client *client, char res, const char *fname, unsigned long long size);
void send_file  (struct general_client *client, const char *fname);
void send_tr_req(struct general_client *client, const char *fname);
void send_eof   (struct general_client *client);

#endif 