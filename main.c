#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "osProj1-log.h.h"
#include <math.h>


//Node structure
typedef struct list_struct {
    data_t item; //holds our message object
    struct list_struct* next; //points to the next node (list_struct / log_t) in our linked-list implemented queue
} log_t;


static log_t* headptr = NULL; //front ptr; points to the first inserted node in the queue
static log_t* tailptr = NULL; //rear ptr; points to the last inserted node in the queue
static int n_flag = 0;
static int l_flag = 0;


int addmsg(data_t data) {

    /*
     * If successful, addmsg will return 0.
     *
     * If unsuccessful, addmsg will return -1
     *
     * Sets errno on failure
     */

    log_t* newNode;
    size_t nodesize;

    nodesize = sizeof(log_t) + strlen(data.string) + 1; //+1 for the null terminator in the data_t object's char* string pointer member variable
    if ((newNode = (log_t*)(malloc(nodesize))) == NULL) {
        perror("Memory request is unable to be made.\n");
        return(-1);
    } /*could not add a new node - - - no more memory available when malloc() returns NULL */

    newNode->item.time = data.time;

    //confused by this code: (but it's on page 44 so we are gonna stick with it)
    newNode->item.string = (char*)newNode + sizeof(log_t); //why not just newNode->item.string = (char*)(malloc(sizeof(char)) * (strlen(item.string) + 1));
    strcpy(newNode->item.string, data.string);
    newNode->next = NULL; //cap your pointers before you use them
    if(headptr == NULL)
        headptr = newNode; //
    else
        tailptr->next = newNode; //tailptr = rear ptr; it points to the "new" last inserted node in the queue
    tailptr = newNode; //the address of the newNode now becomes the address of the tailPtr because it is the "newly" last node in this linked list implemented queue
    return 0;
}

void clearlog(void) {
/*
 * Releases all the storage that has been allocated for the logged messages
 * and empties the list of logged messages
 */
    log_t* logMessages = headptr;

    static int count = 0;

    while (logMessages != NULL){
        logMessages = logMessages->next;
        free(logMessages);
        count++;
        printf("realease mem%d\n", count);
    }
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

    static char* entireLog = NULL;
    static int counter = 0;

    //This is the first log messsage
    entireLog = (char*) malloc(sizeof(headptr->item.string)+1);

    printf("size of entire log before realloc = %lu \n", sizeof(entireLog));


    log_t* nextNode = headptr;

        //right now realloc() doesn't work so we are using entireLog = realloc(entireLog, 10000); in the hoare.cs.umsl.edu file
        while (nextNode != NULL) {
            entireLog = realloc(entireLog, sizeof(nextNode->item.string)+1);
            strncat(entireLog,nextNode->item.string, strlen(nextNode->item.string)); //adding + 1 doesnt fix this error
            counter++;

            nextNode = nextNode->next;
            printf("\ntest new nodes %d\n", counter);
        }

    printf("size of entire log after realloc = %lu \n", sizeof(entireLog));

    return entireLog;

    //unsuccessful getlog function returns NULL
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

    FILE* fp = fopen(filename, "a");
    if (fp == NULL){
        return -1;
    }

    char* obtainLog = getlog();
    fprintf(fp, "%s\n", obtainLog);
    fclose(fp);

    return 0;
}

int main(int argc, char* argv[]) {

    printf("Hello, World!\n"); //just for test output
    printf("%d\n",argc);
    printf("%s\n",argv[1]);

    int c; //create a capture variable to hold the return value of getopt()
    int x = 42; //the default value for the command line parameter variable
    char* logfileName = "logfile.txt"; //is this safe?; see nodesize var in addmsg() for example of safe dynamic memory allocation
    /*
     * the logfileName variable is initialized here to the default value of logfile.txt which will be used
     * as the  name of the log file
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
                n_flag = 1;
                break;
            case 'l':
                logfileName = optarg;
                printf("The value of the logfileName variable is now %s inside the switch function\n", logfileName); //testing only
                l_flag = 1;
                break;

            case '?':
                if (optopt == 'n' || optopt == 'l') {
                    fprintf(stderr, "Option -%c needs an argument\n", optopt); //should/can this be perror()
                }
                else
                    fprintf(stderr, "Unkown option -%c.\n", optopt); //should/can this be perror()

                break;
            }
        }
    printf("The value of x is still %d inside of the main()\n", x); //testing only; '-n x' option flag
    printf("The value of the logfileName variable is still %s inside of the main()\n", logfileName); //testing only; '-l filename' option flag

//LOG OBJECT AND STRING OUTPUT MESSAGE
    data_t newMessage; //new log message object; this will eventually be passed to the addmsg() function
    time(&newMessage.time); //initialize the .time member variable of log message data_t type structure object
    printf("time in seconds = %ld\n", newMessage.time);//test data


    if (n_flag == 0 && l_flag == 0){
        printf("%s: time:%ld Error: -n flag not used (x param remains equal to 42); -l flag not used (log file = logfile.txt)\n", argv[0], newMessage.time);
    }
    else if (n_flag == 1 && l_flag == 1){
        printf("%s: time:%ld Error: -n flag changes the value x param to %d and -l flag changes log file name to %s\n", argv[0], newMessage.time, x, logfileName);
    }
    else if (n_flag == 0 && l_flag == 1){
        printf("%s: time:%ld Error: -n flag not used; -l flag changes log file name to %s\n", argv[0], newMessage.time, logfileName);
    }
    else if (n_flag == 1 && l_flag == 0){
        printf("%s: time:%ld Error: -n flag changes the value x param to %d; -l flag not used (log file = logfile.txt)\n", argv[0], newMessage.time, x);
    }

    newMessage.string = "I am not sure how to move the printf() log messages from above into this item.string pointer.#1..\n";

    //*testing*//
    printf("data_t object test:  newMessage.string = %s\n", newMessage.string); //testing creation of a log message
    printf("data_t object test:  newMessage.time = %ld\n", newMessage.time); //testing creation of a log message
    //*testing*//

    /*
     * call the addmsg() function and pass newly created log message data_t-type object struct into it as argument
     * so it can be added to a log_t queue linked list node as the data_t item member
     */

    if (addmsg(newMessage) == -1) {
        perror("Memory request is unable to be made.\n");
        exit(1);
    }


    //LOG OBJECT AND STRING OUTPUT MESSAGE
    data_t newMessage2; //new log message object; this will eventually be passed to the addmsg() function
    time(&newMessage2.time); //initialize the .time member variable of log message data_t type structure object
    printf("time in seconds = %ld\n", newMessage2.time);//test data


    newMessage2.string = "I am not sure how to move the printf() log messages from above into this item.string pointer...#2..\n";

    //*testing*//
    printf("data_t object test:  newMessage.string = %s\n", newMessage2.string); //testing creation of a log message
    printf("data_t object test:  newMessage.time = %ld\n", newMessage2.time); //testing creation of a log message
    //*testing*//


    if (addmsg(newMessage2) == -1) {
        perror("Memory request is unable to be made.\n");
        exit(1);
    }


    //LOG OBJECT AND STRING OUTPUT MESSAGE
    data_t newMessage3; //new log message object; this will eventually be passed to the addmsg() function
    time(&newMessage3.time); //initialize the .time member variable of log message data_t type structure object
    printf("time in seconds = %ld\n", newMessage3.time);//test data


    newMessage3.string = "I am not sure how to move the printf() log messages from above into this item.string pointer...#3..\n";

    //*testing*//
    printf("data_t object test:  newMessage.string = %s\n", newMessage3.string); //testing creation of a log message
    printf("data_t object test:  newMessage.time = %ld\n", newMessage3.time); //testing creation of a log message
    //*testing*//


    if (addmsg(newMessage3) == -1) {
        perror("Memory request is unable to be made.\n");
        exit(1);
    }

    printf("\nbreakpoint\n");

    //testing getlog()
    char* printLog = getlog();
    printf("%s\n", printLog);
    printf("size of printlog = %lu\n", sizeof(printLog));

    savelog(logfileName);

    clearlog();

    //you have to run this program from the command line because of the argv[0] being passed to printf()
    return 0;
}