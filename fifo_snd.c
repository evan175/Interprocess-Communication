#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "fifo_funcs.h"
#include <errno.h>

// static int fd = -1;
static char * fifoPath = "fifo";


//init fd here and return it
static int init_sender() {
    // if(mkfifo(fifoPath, 0666) == -1 && errno != EEXIST){
    //     perror(("error making fifo"));
    //     return -1;
    // }

    int fd;
    if((fd = open(fifoPath, O_WRONLY)) == -1 && errno == ENOENT) {
        if(mkfifo(fifoPath, 0666) == -1 && errno != EEXIST){
            perror(("error making fifo"));
            return -1;
        }   

    } else if(fd == -1){
        printf("error opening fifo");
        return -1;
    }

    return fd;
}

int fifo_send(char * msg) {
    // if(fd < 0){
    //     init_sender();
    // }

    int fd = init_sender();

    if (strcmp(msg, "Exit") == 0) {
        write(fd, "", 0);
        cleanup_sender(fd);
        return 1;
    }

    return write(fd, msg, strlen(msg) + 1);
}

static int cleanup_sender(int fd) {
    int r = close(fd);

    return r;
}
