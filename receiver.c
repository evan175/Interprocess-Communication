#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "fifo_funcs.h"

int main() {
    int (*recvDataFnPtr)() = &fifo_recv;

    
    if (recvDataFnPtr() < 0) {
        printf("sleeping\n");
        sleep(1);
    }
    
    
    
}