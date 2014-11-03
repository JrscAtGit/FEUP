//
//  application.cpp
//  RCOM_TP1
//
//  Created by José Ricardo de Sousa Coutinho on 02/11/14.
//  Copyright (c) 2014 José Ricardo de Sousa Coutinho. All rights reserved.
//

#include "application.h"

applayer_t app;

void set_applayer(applayer_t * app, int f, int s)
{
    app->fileDescriptor = f;
    app->status = s;
}

void init_applayer(applayer_t * app)
{
    app->fileDescriptor = 0;
    app->status = 0;
}
