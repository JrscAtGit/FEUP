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
    if (!uc) { printf("Erro :: print_unsignedchar , null pointer"); return; };
    
    int i;
    for (i=0; i<(uc->n); i++)
    {
        printf("%c",(uc->s)[i]);
    }
}

void print_loadingbar(float percent)
{
    int fill = (int) (percent / 10);
    
    printf("\n\n\t\t\t[");
    
    int i;
    for (i=1; i<fill; i++)
    {
        printf("#");
    }
    
    for (; i<10; i++)
    {
        printf(" ");
    }
    
    printf("] %.2f%%\n", percent);
}

void safe_free(void * ptr)
{
    if (!!ptr)
    {
        free(ptr);
    }
}

int fsize(const char * filename)
{
    if (!filename) { printf("Erro :: get_filezise , null pointer"); return 0;}
    
    int n;
    FILE * fp;
    fp = fopen (filename,"rb");
    if (!fp) { printf("Erro :: get_filezise , fp null pointer"); return 0;}
    
    fseek(fp, 0L, SEEK_END);
    n = (int) ftell(fp);
    
    fclose (fp);
    
    return n;
}

int copy_tofile(FILE * fp, unsignedchar_t * uc)
{
    if (!fp) { printf("Erro :: copy_tofile , fp null pointer"); return 1; }
    
    int i;
    for (i=0; i<(uc->n); i++)
    {
        fputc((uc->s)[i], fp);
    }
    
    return 0;
}

unsigned char xor_fromto(unsignedchar_t * uc, int xmin, int xmax)
{
    unsigned char res = (uc->s)[xmin];
    
    int i;
    for (i=xmin+1; i<xmax; i++)
    {
        res = (res ^ (uc->s)[i]);
    }
    
    return res;
}

int count_digits(int n)
{
    int i, v=n;
    
    for (i=0; v>0; i++)
    {
        v /= 10;
    }
    
    return i;
}

// credits to: http://www.strudel.org.uk/itoa/#newest
char* itoa(int value, char* result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }
    
    char * ptr = result, * ptr1 = result, tmp_char;
    int tmp_value;
    
    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );
    
    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


