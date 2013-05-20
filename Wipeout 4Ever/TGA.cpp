#include <Windows.h>
#include <stdio.h>
#include "binfile.h"

typedef struct TGA_HDR{
	BYTE IDlength;
	BYTE colorMapType;		// 0=none,1=present,2-127=reserved, 128-255=user
	BYTE imageType;			// 0=none,1=uncompressed indexed,2=uncompressed truecolor,
							// 3=uncompressed gray, 9=rle indexed, 10=rle truecolor,
							// 11 = rle gray
	
	// color map specification
	WORD colorMapFirstEnt;		// start index of colormap
	WORD colorMapNumEnts;	// colormap size
	WORD colorMapEntSize;	// colormap bpp
	
	// image specification
	WORD xOrigin;
	WORD yOrigin;
	WORD width;
	WORD height;
	BYTE bpp;
	BYTE imageDesc; // bits 0-3 give alpha depth, bits 4-5 give direction	
};

typedef struct TGA{
	TGA_HDR header;
	BYTE *imageID;
	BYTE *colorMap;
	BYTE *imageData;
	int imageDataSize;
	int colorMapSize;
};

BYTE TGA_Load(BINFILE *inTGA, TGA *outTGA){
	TGA *tga;
	tga = (TGA*)calloc(1, sizeof(TGA));

	binread(&tga->header, sizeof(TGA_HDR), 1, inTGA);
	if(tga->header.IDlength>0){
		tga->imageID = (BYTE*)calloc(1, tga->header.IDlength);
		binread(tga->imageID, tga->header.IDlength, 1, inTGA);
	}
	tga->colorMapSize = tga->header.colorMapNumEnts*tga->header.colorMapEntSize;
	if(tga->header.colorMapNumEnts>0){
		tga->colorMap = (BYTE*)calloc(1, tga->colorMapSize);
		binread(tga->colorMap, tga->colorMapSize, 1, inTGA);
	}
	tga->imageDataSize = tga->header.bpp*tga->header.width*tga->header.height;
	if(tga->imageDataSize<=0)
		return 0;
	tga->imageData = (BYTE*)calloc(1, tga->imageDataSize);
	outTGA = tga;
}