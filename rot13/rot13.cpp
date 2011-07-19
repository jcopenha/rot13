// rot13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory.h>


void rot13encode(unsigned char* buffer, int length)
{
    for(int x = 0; x < length; x++)
        buffer[x] += 13;
}


void rot13decode(unsigned char* buffer, int length)
{
    for(int x = 0; x < length; x++)
        buffer[x] -= 13;
}

void testbuffer(unsigned char* buffer, int length, unsigned char val)
{
    for(int x = 0; x < 1024; x++)
    {
        if(buffer[x] != val)
        {
            printf("failed.. buffer[%d] = %d, expected 13", x, buffer[x], val);
        }
    }
}

void rot13encode_asm(unsigned char* buffer, int len)
{
    __asm
    {
        mov eax, len      ;
loop0:  cmp eax, 0        ;
        je  exit0         ;
        mov ecx, [buffer] ;
        mov ecx, [ecx]    ;
        add cl, 13        ;
        mov edx, buffer   ;
        mov [edx], cl     ;
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
loop0:  cmp eax, 0        ;
        je  exit0         ;
        mov ecx, [buffer] ;
        mov ecx, [ecx]    ;
        sub cl, 13        ;
        mov edx, buffer   ;
        mov [edx], cl     ;
        inc buffer        ;
        dec eax           ;
        jmp loop0         ;
exit0:
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    int x = 0;
    unsigned char buffer[1024];
    memset(buffer, 0, 1024);

    rot13encode(buffer, 1024);
    testbuffer(buffer, 1024, 13);
    
    rot13decode(buffer, 1024);
    testbuffer(buffer, 1024, 0);

    // good, the C versions work

    rot13encode_asm(buffer, 1024);
    testbuffer(buffer, 1024, 13);
    
    rot13decode_asm(buffer, 1024);
    testbuffer(buffer, 1024, 0);

    // asm version work in simple case

    memset(buffer, 250, 1024);
    rot13encode_asm(buffer, 1024);
    testbuffer(buffer, 1024, (unsigned char)(250+13));
    
    rot13decode_asm(buffer, 1024);
    testbuffer(buffer, 1024, 250);

    // asm version works in roll over case
    
	return 0;
}

