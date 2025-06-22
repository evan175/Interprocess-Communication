#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "fifo_funcs.h"

#define MAX_MSG_LEN 30

int main() {
    char msg[MAX_MSG_LEN + 2];
    int (*sendDataFnPtr)(char *) = &fifo_send;

    while(1) {
        printf("Enter your message. Type 'Exit' to stop: ");
        // scanf("%31s", msg);

        if (fgets(msg, sizeof(msg), stdin) == NULL) {
            // EOF or read error
            printf("\nEnd of input. Exiting.\n");
            break;
        }

        size_t len = strlen(msg);

        // Check if the read line contains '\n' => means user typed less than max len
        if (len > 0 && msg[len - 1] == '\n') {
            msg[len - 1] = '\0';  
            len -= 1;              // Adjust length to exclude the newline
            
        } else {
            // No '\n' => the user typed at least MAX_MSG_LEN+1 chars before hitting Enter:
            // We must flush the rest of the line from stdin.
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                
            }
            printf("Error: input exceeds %d characters. Please try again.\n", MAX_MSG_LEN);
            continue; 
        }

        printf("sending message: %s\n", msg);
        printf("msg size: %lu\n", strlen(msg));

        // also send how many elements in array
        int sendRes = (*sendDataFnPtr)(msg);

        if(strcmp(msg, "Exit") == 0) {
            printf("Exiting..\n");
            break;
        }

        printf("Sending message..\n");
        
        if(sendRes == -1) {
            printf("Error sending message");
        }
        else {
            printf("Message Sent\n");
        }
        
    }
    
    return 0;
}
