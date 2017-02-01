#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "osProj1-log.h.h"
#include <math.h>




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
     * This addmsg function will allocate a node for data and add it to end of the queue ~ aka ~ insert a message
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



int main(int argc, char* argv[]) {

    printf("Hello, World!\n"); //just for test output

   /*
    * log messages created below this getopt code
    */


    int c; //create a capture variable to hold the return value of getopt()
    int x = 37; /*the default value for the command line parameter variable; if the -n
    * if the -n x option flag is passed to the command line then the value of x will
    */
    char* logfileName = "logfile.txt"; //is this safe?; see nodesize var in addmsg() for example of safe dynamic memory allocation
    /*
     * the logfileName variable is initialized here to the default value of logfile.txt which will be used
     * as the  name of the log file
     *
     */


    while ( (c = getopt(argc, argv, "hn:l:")) != -1){

        switch(c) {
            case 'h':
                printf("The '-h' flag describes the supported command line argument options.\n");
                printf("The '-n x' flag describes is a command line parameter that will set a\nvariable in this main executable to the value specifed in place of the x symbol.\nFor example: if the command line argument is followed by '-n 13, then a corresponding\n variable in the program will be set to the value 13.\nIf this flag is not used then that corresponding variable described just previously will have a\ndefault value of 37.\n");
                printf("The '-l filename' flag will set the name of the logfile to whatever is passed in place of 'filename.'\nIf this option is not passed from the command line then the default logfile name\nwill be logfile.txt.  Just insert the desired file name in place of filename\nin the '-l filename' option flag to set the logfile name as desired.\n");
                break;
            case 'n':
                x = atoi(optarg);
                printf("The value of x is now %d inside the switch function\n", x); //testing only

                break;
            case 'l':
                logfileName = optarg;
                printf("The value of the logfileName variable is now %s inside the switch function\n", logfileName); //testing only
                break;

            case '?':
                if (optopt == 'n' || optopt == 'l') {
                    fprintf(stderr, "Option -%c needs an argument\n", optopt);
                }
                else
                    fprintf(stderr, "Unkown option -%c.\n", optopt);

                break;

                /*
            default:
                //perror("getopt()"); will this function really be necessary; when could default actually occur
                 */
        }
    }

    printf("The value of x is still %d inside of the main()\n", x); //testing only; '-n x' option flag
    printf("The value of the logfileName variable is still %s inside of the main()\n", logfileName); //testing only; '-l filename' option flag


    /*
     * The logging utility allows the caller to save
     * a message at the end of a list (a queue that takes an array of char* pointers).
     * The logger also records the time that the message was logged
    */

    /*
    * create a new data_t object (item is the data_t object reference variable member in node structure object)
    * each time the program is run...then these messages (in the form of data_t objects)
    * will get sent to a file (whose name is logfile.txt by default
    * but can be changed by the '-l filename' flag)
    *
    * this data_t object (log message) will be sent to the savelog(function)
    *
    * the logfileName variable will be sent to the save log function but only once? not sure how I can get this value to persis across multiple program runs...
    *
    *
    *
   */
    data_t newMessage; //new log message object; this will eventually be passed to the addmsg() function
    newMessage.string = "log message string";
    time(&newMessage.time); //initialize the .time member variable of log message data_t type structure object
    printf("time in seconds = %ld\n", newMessage.time);
    //time_t timeInSeconds;  >>>>> can't figure out how to convert seconds to nanoseconds
    //time(&timeInSeconds); //this needs error handling (use that ISO C standard site; bookmarked on Safari)  >>>>> can't figure out how to convert seconds to nanoseconds
    //int time = pow(timeInSeconds,-9); >>>>> can't figure out how to convert seconds to nanoseconds
    //newMessage.time = time;  >>>>> can't figure out how to convert seconds to nanoseconds
    //printf("time in nanoseconds = %ld\n",newMessage.time);  >>>>> can't figure out how to convert seconds to nanoseconds
    //*testing*//
    printf("data_t object test:  newMessage.string = %s\n", newMessage.string); //testing creation of a log message
    printf("data_t object test:  newMessage.time = %ld\n", newMessage.time); //testing creation of a log message
    //*testing*//


    /*
     * call the addmsg() function and pass newly created log message data_t-type object struct into it as argument
     * so it can be added to a log_t queue linked list node as the data_t item member
     */
    if (addmsg(newMessage) == -1)
        perror("Failed to add another log message (node) to our linked list implemented logging utility queue");


    return 0;
}