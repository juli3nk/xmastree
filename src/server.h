#ifndef SERVER_H
#define SERVER_H

#define API_PORT 80
#define JSON_BUFF_SIZE 1024
#define JSON_ERROR_SIZE 128
#define BUFF_SIZE 1024

void setupServer();
void handleAPIClient();

void handleNotFound();
void handleRoot();
void handleFileList();
void handleOn();
//void handleOff();
void handleStatus();
void handleSet();
void handlePrevAnimation();
void handleNextAnimation();

#endif
