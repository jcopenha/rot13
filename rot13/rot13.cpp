// rot13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory.h>


void rot13encode(unsigned char* buffer, int length)
{
    unsigned char last = 0;
    for(int x = 0; x < length; x++)
    {
        unsigned char change = 13 + last;
        last = buffer[x];
        buffer[x] += change;
    }
}


void rot13decode(unsigned char* buffer, int length)
{
    unsigned char last = 0;
    for(int x = 0; x < length; x++)
    {
        unsigned char change = 13 + last;
        buffer[x] -= change;
        last = buffer[x];
    }
}

void rot13encode_asm(unsigned char* buffer, int len)
{
    __asm
    {
        mov eax, len      ;
        xor edx, edx      ; 
loop0:  cmp eax, 0        ;
        je  exit0         ;
        mov ecx, [buffer] ;
        mov ecx, [ecx]    ;
        add dl, 13        ;
        add cl, dl        ;
        mov esi, buffer   ;
        mov edx, [esi]    ;
        mov [esi], cl     ;
        inc buffer        ;
        dec eax           ;
        jmp loop0         ;
exit0:
    }
}

void rot13decode_asm(unsigned char* buffer, int len)
{
    __asm
    {
        mov eax, len      ;
        xor edx, edx      ;
loop0:  cmp eax, 0        ;
        je  exit0         ;
        mov ecx, [buffer] ;
        mov ecx, [ecx]    ;
        add dl, 13        ;
        sub cl, dl        ;
        mov esi, buffer   ;
        mov [esi], cl     ;
        mov dl, cl        ;
        inc buffer        ;
        dec eax           ;
        jmp loop0         ;
exit0:
    }
}

// rot13 with a twist.
int _tmain(int argc, _TCHAR* argv[])
{
    int x = 0;
    unsigned char buffer[1024];
    unsigned char buffer2[1024];
    for(int x = 0; x < 1024; x++)
    {
        buffer[x] = x;
        buffer2[x] = x;
    }

    rot13encode(buffer, 1024);
    rot13encode_asm(buffer2, 1024);
    if ( memcmp(buffer, buffer2, 1024) != 0 )
    {
        printf("encodings not the same\n");
    }
    
    
    rot13decode(buffer, 1024);
    rot13decode_asm(buffer2, 1024);
    if ( memcmp(buffer, buffer2, 1024) != 0 )
    {
        printf("decodings not the same\n");
    }

    for(int x = 0; x < 1024; x++)
    {
        if(buffer[x] != (unsigned char)x)
            printf("failed.. buffer[%d] = %d, expected %d", x, buffer[x], (unsigned char)x);
    }
    

    
	return 0;
}

