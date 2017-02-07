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
static int x = 42;
static char* logfileName = "logfile.txt";
static int dataStringEnum = 0;

char* msgTemplate(){

    char* returningMsgTemplate;

    if (n_flag == 0 && l_flag == 0){
        char *hMessageTemplate = "\n%s: Time:%lu Error:%s\n";
        dataStringEnum = 1;
        returningMsgTemplate = hMessageTemplate;
    }
    else if (n_flag == 1 && l_flag == 0){
        char* nMessageTemplate = "\n%s: Time:%lu Error:%s - - x changed to %d\n";
        dataStringEnum = 2;
        returningMsgTemplate = nMessageTemplate;
    }
    else if (n_flag == 1 && l_flag == 1){
        char* nAndlMessageTemplate = "\n%s: Time:%lu Error:%s - - x changed to %d and logfile.txt name changed to %s\n";
        dataStringEnum = 3;
        returningMsgTemplate = nAndlMessageTemplate;
    }
    else if (n_flag == 0 && l_flag == 1){
        char* lMessageTemplate = "\n%s: Time:%lu Error:%s - - logfile.txt name changed to %s\n";
        dataStringEnum = 4;
        returningMsgTemplate = lMessageTemplate;
    }

    return returningMsgTemplate;
}

data_t createLogMessageForNode(){

    data_t newLogMessage; //create a new Log Message(data_t) object for the node(log_t) in the queued linked-list
    return newLogMessage;
}


int addmsg(data_t data, char* argv0) {
    /*
     * If successful, addmsg will return 0.
     *
     * If unsuccessful, addmsg will return -1
     *
     * Sets errno on failure
     */
    log_t* newNode;
    size_t nodesize;
    char* messageTemplate = msgTemplate();
    time(&data.time); //initialize the .time member variable of log message data_t type structure object

    if (dataStringEnum == 1){
        data.string = "c'mon atleast throw a flag";
    }
    else if (dataStringEnum == 2){
        data.string = "- - Winter is coming!";
    }
    else if (dataStringEnum == 3){
        data.string = " - - House Lannister!";
    }
    else if (dataStringEnum == 4){
        data.string = "- - House Stark!";
    }
    /*
     * snprintf is a little bit of a hack; you have to pass it data.string as its fourth argument or it doesn't work for some reason
     * I honestly just started guessing and testing and it worked...need an explanation why though...
     */
    //get message size
    int logStringSize = snprintf(NULL, 0, messageTemplate, data.string, data.time, argv0, x, logfileName); //measures the logString
    printf("size of logString is %d\n", logStringSize);//test logString size

    //include the size of the node + the logString + the null terminator
    nodesize = sizeof(log_t) + logStringSize + 1; //the +1 accounts for the NULL Terminator \0 at the end of the char*/char[]
    if ((newNode = (log_t *) (malloc(nodesize))) == NULL) {
        perror("Memory request is unable to be made.\n");
        return (-1);
    }
    newNode->item.time = data.time;
    newNode->item.string = (char*) (newNode+1); //newNode + 1 is pointer arithmetic that casts the additional allocated memory past the initial amount of the contiguous log_t-sized memory block to the newNode->item.string variable logMessage string that needs memory right after that log_t block of memory (ex: think log_t is from mem-cell 100 to mem-cell 150, and the memory calculated from the snprintf (int logString) needs mem-cell 151 to ?...to get to mem-cell 151 from mem-cell 100 we need to perform pointer arithmetic and traverse the heap memory block by the amount of log_t so we can go from mem-cell 100 to mem-cell 151 and that portion can now start reading in data from newNode->item.string...then we have to recast it as char* memory (from log_t* memory)
    newNode->next = NULL; //cap the log_t* next pointer to point to location NULL/0 for now...it's not being used here anyways...at least not until getlog() is called
    snprintf(newNode->item.string,logStringSize, messageTemplate, argv0, data.time, data.string, x, logfileName);
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
        printf("release mem%d\n", count);
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
    //int x = 42; //the default value for the command line parameter variable
    //char* logfileName = "logfile.txt"; //is this safe?; see nodesize var in addmsg() for example of safe dynamic memory allocation
    /*
     * the logfileName variable is initialized here to the default value of logfile.txt which will be used
     * as the  name of the log file
     */

    while ( (c = getopt(argc, argv, "hn:l:")) != -1){

        switch(c) {
            case 'h':
                printf("The '-h' flag is a help option one can pass as an argument through the CLI.\n"
                "The '-n x' flag is an optional argument flag that can be passed through the CLI\n"
                               "that allows the user to specify the value of a program param in place of x;\n"
                               "x will be equal to 42 by default.\n"
                               "For example: -n 12345 would set the value of the program param equal to 12345 instead of 42.\n"
                "The '-l filename' flag allows the user to specify the name of the logfile that\n"
                               "that stores the logging messages that aggregate each time the program is executed;\n"
                               "the logfile name is logfile.txt by default.\n"
                               "For example: -l catdog.txt would create .txt file and save the log messages to it.\n");
                break;
            case 'n':
                x = atoi(optarg);
                n_flag = 1;
                break;
            case 'l':
                logfileName = optarg;
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
/*
//LOG OBJECT AND STRING OUTPUT MESSAGE
    data_t newMessage; //new log message object; this will eventually be passed to the addmsg() function
    time(&newMessage.time); //initialize the .time member variable of log message data_t type structure object
    printf("time in seconds = %ld\n", newMessage.time);//test data
    newMessage.string = "testing data.string via log_t's item.string\n";
*/

/*
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
*/

    /*
     * call the addmsg() function and pass newly created log message data_t-type object struct into it as argument
     * so it can be added to a log_t queue linked list node as the data_t item member
     */

    data_t newMessage1 = createLogMessageForNode();
    if (addmsg(newMessage1, argv[0]) == -1) {
        perror("Memory request is unable to be made.\n");
        exit(1);
    }

    data_t newMessage2 = createLogMessageForNode();
    if (addmsg(newMessage2, argv[0]) == -1) {
        perror("Memory request is unable to be made.\n");
        exit(1);
    }


    data_t newMessage3 = createLogMessageForNode();
    if (addmsg(newMessage3, argv[0]) == -1) {
        perror("Memory request is unable to be made.\n");
        exit(1);
    }

    data_t newMessage4 = createLogMessageForNode();
    if (addmsg(newMessage4, argv[0]) == -1) {
        perror("Memory request is unable to be made.\n");
        exit(1);
    }

    printf("\nbreakpoint\n");

    //testing getlog()
    char* printLog = getlog();
    printf("%s\n", printLog);
    printf("size of printlog = %lu\n", sizeof(printLog));

    savelog(logfileName); //saves the log to the logfileName
    clearlog(); //frees the memory ===> not sure if this is working along with my realloc in my getlog()


    //you have to run this program from the command line because of the argv[0] being passed to printf()
    return 0;
}