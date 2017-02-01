//
// Created by Ryan Patrick Davis on 1/31/17.
//

#ifndef CS4760_OPERATINGSYSTEMS_PROJ1_OSPROJ1_LOG_H_H
#define CS4760_OPERATINGSYSTEMS_PROJ1_OSPROJ1_LOG_H_H

#include <time.h>

typedef struct data_struct {
    time_t time; //The time the message is logged
    char* string;  //The logging message
} data_t;

int addmsg(data_t data);
void clearlog(void);
char* getlog(void);
int savelog(char* filename);



#endif //CS4760_OPERATINGSYSTEMS_PROJ1_OSPROJ1_LOG_H_H
