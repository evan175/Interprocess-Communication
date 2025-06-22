#ifndef COMMS_FUNCS
#define COMMS_FUNCS

static int init_sender();

int fifo_send(char * msg);

static int cleanup_sender();

static int init_reader();

int fifo_recv();

static int cleanup_receiver();

#endif