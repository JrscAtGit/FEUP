//
//  protocol.h
//  RCOM_TP1
//
//  Created by José Ricardo de Sousa Coutinho on 02/11/14.
//  Copyright (c) 2014 José Ricardo de Sousa Coutinho. All rights reserved.
//

#ifndef __RCOM_TP1__protocol__
#define __RCOM_TP1__protocol__

#include "include.h"

#define BAUDRATE B9600
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define TIMEOUT_LIMIT 3
#define NUM_TRANSMITIONS 5

#define TRANSMITTER 1
#define RECEIVER 0

#define FALSE 0
#define TRUE 1

#define FLAG 0x7e
#define ESC 0x7d
#define Fstuffing 0x5e
#define ESCstuffing 0x5d

#define A1 0x03
#define A2 0x01

#define C_S_0 0x00
#define C_S_1 0x40

#define C_SET 0x03
#define C_UA 0x07
#define C_DISC 0x0b

#define C_RR_0 0x05
#define C_RR_1 0x85
#define C_REJ_0 0x01
#define C_REJ_1 0x81

#define MFS 256
#define MTS 600

#define Cpkg_dados 0x01
#define Cpkg_inicio 0x02
#define Cpkg_fim 0x03


typedef struct _unsignedchar {
    unsigned char * s;
    int n;
} unsignedchar_t;


void init_unsignedchar(unsignedchar_t * uc);

int set_unsignedchar_unsignedchar(unsignedchar_t * dst, unsignedchar_t * src);

int set_unsignedchar_char(unsignedchar_t * dst, const char * src);

void print_unsignedchar(const unsignedchar_t * uc);

void safe_free(void * ptr);


#endif /* defined(__RCOM_TP1__protocol__) */
