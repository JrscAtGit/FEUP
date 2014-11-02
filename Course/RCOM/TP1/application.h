//
//  application.h
//  RCOM_TP1
//
//  Created by José Ricardo de Sousa Coutinho on 02/11/14.
//  Copyright (c) 2014 José Ricardo de Sousa Coutinho. All rights reserved.
//

#ifndef __RCOM_TP1__application__
#define __RCOM_TP1__application__

#include "include.h"


typedef struct _app
{
    int fileDescriptor;
    int status;
} applayer_t;


void set_applayer(applayer_t * app, int f, int s);

void init_applayer(applayer_t * app);


#endif /* defined(__RCOM_TP1__application__) */
