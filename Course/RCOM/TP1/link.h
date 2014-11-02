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
    char port[20]; // dispositivo /dev/ttySx , com x = {0,1,2,3,4,5} // esq: 4, dir: 0
    int baudrate; // velocidade de transmissao
    unsigned int sequenceNumber; // numero de sequencia da trama: 0 ou 1
    unsigned int timeout; // valor do temporizador (segundos): ex: 3
    unsigned int numTransmissions; //numero de tentativas em caso de falha
} linklayer_t;


void set_linklayer(linklayer_t * link, unsigned int s)
{
    link->sequenceNumber = s;
}

void init_linklayer(linklayer_t * link, char p[20]);

#endif /* defined(__RCOM_TP1__link__) */
