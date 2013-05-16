#ifndef __ENDIAN_TOOLS_H__
#define __ENDIAN_TOOLS_H__

#include <Windows.h>
#include <stdio.h>

#define SWAP_WORD(x) (x=(x>>8)|((x<<8)&0x00FF))
#define SWAP_DWORD(x) (x= (x>>24) | \
        ((x<<8) & 0x00FF0000) |\
        ((x>>8) & 0x0000FF00) |\
        (x<<24))


#endif