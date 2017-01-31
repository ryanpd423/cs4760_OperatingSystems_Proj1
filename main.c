#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "osProj1-log.h.h"

typedef struct list_struct {
    data_t item;
    struct list_struct *next;
} log_t;

static log_t* headptr = NULL;
static log_t* tailptr = NULL;

int addmsg(data_t data) {

    /*
     * If successful, addmsg will return 0.
     *
     * If unsuccessful, addmsg will return -1
     *
     * Sets errno on failure
     */

    return 0;
}

void clearlog(void) {
/*
 * Releases all the storage that has been allocated for the logged messages
 * and empties the list of logged messages
 */

}

char* getlog(void) {
/*
 * Allocates enough space for a string containing the entire log, copies that
 * log into this string, and returns a pointer to the string
 *
 * It is the responsibility of the calling program to free this memory when necessary
 *
 * A successful getlog function returns a pointer to the log string
 *
 * An unsuccessful getlog call returns NULL
 *
 * Sets errno on failure
 */

    return NULL;
}


int savelog(char* filename) {
/*
 * saves the logged messages to a disk file
 *
 * If successful, savelog will return 0.
 *
 * If unsuccessful, savelog will return -1
 *
 * Sets errno on failure
 */

    return 0;
}

int main() {

    printf("Hello, World!\n");

    /*
     * The logging utility allows the caller to save
     * a message at the end of a list (a queue that takes an array of char* pointers).
     * The logger also records the time that the message was logged
    */


    return 0;
}