//
//  link.cpp
//  RCOM_TP1
//
//  Created by José Ricardo de Sousa Coutinho on 02/11/14.
//  Copyright (c) 2014 José Ricardo de Sousa Coutinho. All rights reserved.
//

#include "link.h"


void set_linklayer(linklayer_t * link, unsigned int s)
{
    link->sequenceNumber = s;
}

void init_linklayer(linklayer_t * link, char * s)
{
    copy(link->port, s);
    link->baudrate = BAUDRATE;
    link->sequenceNumber = 0;
    link->timeout = TIMEOUT_LIMIT;
    link->numTransmissions = NUM_TRANSMITIONS;
}