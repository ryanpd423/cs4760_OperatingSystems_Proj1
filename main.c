#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "osProj1-log.h.h"

//Node structure
typedef struct list_struct {
    data_t item;
    struct list_struct* next;
} log_t;


static log_t* headptr = NULL; //front ptr; points to the first inserted node in the queue
static log_t* tailptr = NULL; //rear ptr; points to the last inserted node in the queue

int addmsg(data_t data) {

    /*
     * If successful, addmsg will return 0.
     *
     * If unsuccessful, addmsg will return -1
     *
     * Sets errno on failure
     */

    /*
     * The addmsg function inserts a copy of the data_t-type data item (log message)
     * at the end of the list.
     *
     * The addmsg function appends to its internal list structure a node containing a copy of the data
     */

    /*
     * This addmsg function will allocate node for data and add to end of list ~ aka ~ insert a message
     * into the link list implemented queue
     */

    /*
     * a majority of the below code for addmsg is from page 44-45 in UNIX Systems Programming
     */
    log_t* newNode;
    int nodesize;

    nodesize = sizeof(log_t) + strlen(data.string) + 1; //+1 for the null terminator
    if ((newNode = (log_t*) (malloc(nodesize))) == NULL) /*could not add a new node */
        return -1; //see error handling in main method at addmsg() function call

    newNode->item.time = data.time;/*
 * to access the members of a structure using a pointer to that structure, you must use the -> operator as follows:
 * struct_pointer->title; //where title is a member of the struct_pointer object definition and struct_pointer is
 * a struct_pointer-object-type pointer (meaning struct_pointer could hold the address of a struct_pointer type object)
 */
    newNode->item.string = (char*)newNode + sizeof(log_t); //not sure what this is code is accomplishing; I think it is trying to copy the string value from the log message object (data_t item argument) into the newNode copied version of the log message's data_t item argument
    //why not just newNode->item.string = (char*) (malloc(sizeof(char)) * (strlen(item.string) + 1));
    strcpy(newNode->item.string, data.string);
    newNode->next = NULL;
    if(headptr == NULL)
        headptr = newNode;
    else
        tailptr->next = newNode; //tailptr = rear ptr; this is the last node is the queue's pointer; it points to the "new" last inserted node in the queue
    tailptr = newNode; //the address of the newNode now becomes the address of the tailPtr because it is the "newly" last node in this linked list implemented queue
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

    printf("Hello, World!\n"); //just for test output

    /*
     * The logging utility allows the caller to save
     * a message at the end of a list (a queue that takes an array of char* pointers).
     * The logger also records the time that the message was logged
    */

    //printf("size of log_t struct object = %lu bytes\n", sizeof(log_t)); //test data this can be deleted

    /*Error handling for the addmsg function
    if (addmsg(data_t data) == -1 && )
        perror("Failed to add another log message (node) to our linked list implemented logging utility queue");
    */


    return 0;
}