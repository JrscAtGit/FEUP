#ifndef   NONCANON_H
#define   NONCANON_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BAUDRATE B38400
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;

typedef struct noncanon_type
{
   int fd;
   struct termios oldtio,newtio;
   char buf[255];
   char * deviceName;
} noncanon_t;

int noncanon_open(noncanon_t * nct);
int noncanon_close(noncanon_t * nct);

int noncanon_msg_send(noncanon_t * nct);
int noncanon_msg_receive(noncanon_t * nct);

void freeNCT(noncanon_t * nct);

#endif
