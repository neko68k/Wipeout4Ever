#include "binfile.h"
#include "endian_tools.h"

#include "TRV.h"

trv_vertex_t *TRV = NULL;
DWORD numverts = 0;

void TRV_Load(BINFILE *file){
	DWORD filesize = 0;
	binseek(file, 0, BIN_END);
	filesize = bintell(file);
	binseek(file, 0, SEEK_SET);

	TRV = (trv_vertex_t*)file->base;

	numverts = filesize>>4;
	for(int i = 0;i<numverts; i++){
		// need to swap endian on each of these
		SWAP_DWORD(TRV->x);
		SWAP_DWORD(TRV->y);
		SWAP_DWORD(TRV->z);
	}
}

trv_vertex_t TRF_GetVert(DWORD i){
	return(TRV[i]);
}