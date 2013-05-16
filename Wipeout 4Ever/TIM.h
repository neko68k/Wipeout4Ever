#ifndef __TIM_H__
#define __TIM_H__

#include "binfile.h"

typedef struct{
	DWORD magic;	// 0x10000000
	DWORD bpp;		
	DWORD len;		// incl header
	struct PAL{
	WORD x;
	WORD y;
	WORD w;
	WORD h;}pal;
	struct IMG{
	WORD x;
	WORD y;
	WORD w;
	WORD h;}img;
}TIM_HDR;


BYTE TIM_Load(BINFILE *infile);


#endif