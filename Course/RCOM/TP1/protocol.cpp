//
//  protocol.cpp
//  RCOM_TP1
//
//  Created by José Ricardo de Sousa Coutinho on 02/11/14.
//  Copyright (c) 2014 José Ricardo de Sousa Coutinho. All rights reserved.
//

#include "protocol.h"

void init_unsignedchar(unsignedchar_t * uc)
{
    uc->s = NULL;
    uc->n = 0;
}


int set_unsignedchar_unsignedchar(unsignedchar_t * dst, unsignedchar_t * src)
{
    if (!dst || !src) { return 1; }
    
    int i=0;
    
    if (!(dst->s))
    {
        dst->s = (unsigned char *) malloc( sizeof(unsigned char) * src->n );
        dst->n = src->n;
    }
    else
    {
        dst->s = (unsigned char *) realloc( dst->s , sizeof(unsigned char) * src->n );
        dst->n = src->n;
    }
    
    if (!src->n) { return 0; }
    if (!(dst->s)) { return 1; }
    
    for(; i<src->n; i++)
    {
        (dst->s)[i] = (src->s)[i];
    }
    
    return 0;
}

int set_unsignedchar_char(unsignedchar_t * dst, const char * src)
{
    if (!dst || !src) { return 1; }
    
    int i=0, n=(int) strlen(src);
    
    if (!(dst->s))
    {
        dst->s = (unsigned char *) malloc( sizeof(unsigned char) * n );
        dst->n = n;
    }
    else
    {
        dst->s = (unsigned char *) realloc( dst->s , sizeof(unsigned char) * n );
        dst->n = n;
    }
    
    if (!n) { return 0; }
    if (!(dst->s)) { return 2; }
    
    for(; i<n; i++)
    {
        (dst->s)[i] = src[i];
    }
    
    return 0;
}

void print_unsignedchar(const unsignedchar_t * uc)
{
    if (!uc) { perror("Erro :: print_unsignedchar , null pointer"); return; };
    
    int i;
    for (i=0; i<(uc->n); i++)
    {
        printf("%c",(uc->s)[i]);
    }
}

void safe_free(void * ptr)
{
    if (!!ptr)
    {
        free(ptr);
    }
}
