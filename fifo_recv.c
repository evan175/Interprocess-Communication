#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "fifo_funcs.h"

// static int fd = -1;
char * fifoPath = "fifo";
// add constant for size, declare buff as global in fifo_snd.c too
#define BUFF_SIZE 30
char buff[BUFF_SIZE];

//init fd here and return it too pass around other funcs (then it could be used for multiple senders)
static int init_reader() {
    int fd;

    if((fd = open(fifoPath, O_RDONLY)) == -1) {
        return -1;
    }

    return fd;
}

int fifo_recv() {
    // if(fd < 0){
    //     init_reader();
    // }

    int fd = init_reader();

    int bytesRead;


    while((bytesRead = read(fd, buff, 30)) > 0) {
        buff[bytesRead] = '\0';

        //check if string is "Exit" to break loop
        if(strcmp(buff, "Exit") == 0) {
            cleanup_receiver(fd);
            break;
        }

        printf("Received, %s\n", buff);
        
        for(int i = 0; i < bytesRead; i++) {
            printf("i = %d buff = %d\n", i, buff[i]);
        }
    }
    
    // currently does not work, could send "Exit" from sender string to close receiver
    //cleanup_receiver();
    return -1;
}

static int cleanup_receiver(int fd) {
    int r = close(fd);
    
    return r;
}

