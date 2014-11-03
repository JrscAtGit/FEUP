//
//  link.h
//  RCOM_TP1
//
//  Created by José Ricardo de Sousa Coutinho on 02/11/14.
//  Copyright (c) 2014 José Ricardo de Sousa Coutinho. All rights reserved.
//

#ifndef __RCOM_TP1__link__
#define __RCOM_TP1__link__

#include "protocol.h"


typedef struct _link
{
    char port[20];
    int baudrate;
    unsigned int sequenceNumber;
    unsigned int timeout;
    unsigned int numTransmissions;
} linklayer_t;

extern linklayer_t llink;

void set_linklayer(linklayer_t * link, unsigned int seqnum);

void init_linklayer(linklayer_t * link, const char * src);

#endif /* defined(__RCOM_TP1__link__) */
