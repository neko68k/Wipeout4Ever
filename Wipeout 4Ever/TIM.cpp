
#include <Windows.h>
#include "tim.h"
//#include "vram.h"
#include "binfile.h"

// need to implement TIM to VRAM auto placement based
// on values used in WOXL

static WORD PalAutoX = 0;
static WORD PalAutoY = 0;
static WORD TimAutoX = 0;
static WORD TimAutoY = 0;


BYTE TIM_Load(BINFILE *intim, bool isLibrary){

	BYTE *TIM = intim->base;

	BYTE *pix = NULL;
	BYTE *pal = NULL;

	TIM_HDR *timHdr = (TIM_HDR*)calloc(1, sizeof(TIM_HDR));
	binread(timHdr, sizeof(TIM_HDR), 1, intim);

	BYTE mult = 2;

	//binread(&magic, 4, 1, intim);

	//binread(&timHdr2, 4, 1, intim);	
	if(timHdr->magic!=0x10000000)
		return 0;
	if(((timHdr->bpp) & 7) == 1){
		//do 8-bit
		if(timHdr->img.x==0&&timHdr->img.y==0)
			return -1;	// cant autoplace 8 bit textures
	}
	else{
		//do 4-bit		
		// 4-bit autoplace if img x/y == 0
		if(timHdr->img.x==0&&timHdr->img.y==0){		
			timHdr->pal.x=PalAutoX;	// pal x
			timHdr->pal.y=PalAutoY;	// pal y
			timHdr->pal.w=0x10;		// pal w
			timHdr->pal.h=1;			// pal h
			timHdr->img.x=TimAutoX;	// img x
			timHdr->img.y=TimAutoY;	// img y

			PalAutoX += 16;

			if(PalAutoX >= 384){
				PalAutoX = 320;
				++PalAutoY;
			}
			if(isLibrary)
				TimAutoY += 32;
			else
				TimAutoY += 128;

			if(TimAutoY >= 256){
				if(isLibrary)
					TimAutoX += 8;
				else
					TimAutoX += 32;
				TimAutoY = 0;
			}
		}
	}
	
	pal = (BYTE*)calloc(timHdr->pal.w*timHdr->pal.h, 2);
	binread(pal, timHdr->pal.w*timHdr->pal.h, 2, intim);

	pix = (BYTE*)calloc(timHdr->img.w*timHdr->img.h, mult);
	binread(pix, timHdr->img.w*timHdr->img.h, mult, intim);
	//if(timHdr2 == 9 || timHdr2 == 8)
		//VRAM_LoadTex(pix, pal, pixHdr, pixHdr.w*pixHdr.h*mult, palHdr, palHdr.w*palHdr.h*2);
	//else
		//VRAM_LoadTex(pix, pixHdr, pixHdr.w*pixHdr.h*mult);
	return 0;
}